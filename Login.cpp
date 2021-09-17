#include "StdAfx.h"
#include "Login.h"
#include "HttpUtil.h"
#include <mutex>
#include "qrencode.h"

const string INI_LOCAL_FILE = "./bin/imitationtim.ini";
const string DB_LOCAL_FILE = "bin/tim.db";
const string HTTP_WX_LOGIN = "localhost:8080/login/getloginByWx";
const string HTTP_QQ_LOGIN = "localhost:8080/login/login";
const string HTTP_WX_POST = "localhost:8080/login/loginByWx";


LoginForm::LoginForm()
{
}

LoginForm::~LoginForm()
{
}


CDuiString LoginForm::GetSkinFolder()
{
	return _T("skin\\");
}

CDuiString LoginForm::GetSkinFile()
{
	return _T("login.xml");
}

LPCTSTR LoginForm::GetWindowClassName(void) const
{
	return _T("login");
}

void LoginForm::Notify(TNotifyUI& msg)
{
	__super::Notify(msg);
}



LRESULT LoginForm::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CDialogBuilder builder;

	CDuiString strResourcePath = m_PaintManager.GetResourcePath();
	if (strResourcePath.IsEmpty())
	{
		strResourcePath = m_PaintManager.GetInstancePath();
		strResourcePath += GetSkinFolder().GetData();
	}
	m_PaintManager.SetResourcePath(strResourcePath.GetData());

	//init
	m_PaintManager.Init(m_hWnd);

	//xml
	CControlUI* pRoot = builder.Create(GetSkinFile().GetData(), 0, NULL, &m_PaintManager);
	ASSERT(pRoot && "Failed to parse XML");

	m_PaintManager.AttachDialog(pRoot);

	m_PaintManager.AddNotifier(this);

	//init
	Init();

	return 0;
}

LRESULT LoginForm::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = TRUE;
	ShowWindow(true);
	return 0;
}

LRESULT LoginForm::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	::PostQuitMessage(0L);
	bHandled = FALSE;
	return 0;
}

//shield system bar
LRESULT LoginForm::OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (::IsIconic(*this)) bHandled = FALSE;
	return (wParam == 0) ? TRUE : FALSE;
}

LRESULT LoginForm::OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

void LoginForm::Init()
{
	//btn login
	m_pLogin = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_login")));

	//username pwd
	m_pUserName = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_username")));
	m_pPassWord = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("edit_password")));
	m_pPassWord->SetPasswordChar('*');

	//checkbox save pwd
	m_pSavePwd = static_cast<CCheckBoxUI*>(m_PaintManager.FindControl(_T("check_savepwd")));

	//select table
	m_pTabLayout = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("tab_bar")));

	//option qq
	m_pOptionQQ = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("qq")));

	//option wx
	m_pOptionWx = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("wx")));

	m_pQrImg = static_cast<CControlUI*>(m_PaintManager.FindControl(_T("qrimg")));

	m_userController = new UserController();

	//remember pwd 
	int result = GetPrivateProfileInt("data", "IsSavePwd", 0, INI_LOCAL_FILE.c_str());

	if (result == 1) {
		UserInfo user;
		//get db info
		user = m_userController->getUserInfoFromFile(DB_LOCAL_FILE);
		m_pUserName->SetText(user.getUserName().c_str());
		m_pPassWord->SetText(user.getPwd().c_str());
		m_pSavePwd->Selected(true);
	}

}




//click events
void LoginForm::OnClick(TNotifyUI& msg)
{
	CDuiString pSenderName = msg.pSender->GetName();
	if (pSenderName == _T("closebtn"))
	{
		Close(IDOK);
		PostQuitMessage(0);
		return;
	}
	else if (pSenderName == _T("btn_login"))
	{
		UserLogin();
		return;

	}
	if (pSenderName == _T("qq"))
	{
		m_pTabLayout->SelectItem(0);
		m_pOptionWx->Selected(false);


	}

	if (pSenderName == _T("wx"))
	{
		m_pTabLayout->SelectItem(1);
		m_pOptionQQ->Selected(false);

		GetQrWx();

		struct Prama* prama = new Prama;
		prama->hWnd = GetHWND();

		//child thread operation
		DWORD dwThreadID = 0;
		HANDLE hThread = CreateThread(NULL, 0, &LoginForm::UserWxLogin, (LPVOID)prama, 0, &dwThreadID);

	}

}

//login by btn
void LoginForm::UserLogin()
{

	CDuiString user_name = m_pUserName->GetText();
	CDuiString pass_word = m_pPassWord->GetText();
	CDuiString result_str;


	if (user_name == "" || pass_word == "") {
		MessageBox(GetHWND(), "请输入账号密码", "提示", 0);
		return;
	}

	string url = HTTP_QQ_LOGIN + "?userName=" + (string)user_name + "&password=" + (string)pass_word;

	//http post
	string result = HttpUtil::Get().HttpPost(url.c_str());
	if (result == "")
	{
		MessageBox(GetHWND(), "账号密码错误", "提示", 0);
		return;
	}

	UserInfo userInfo;

	//parseFromJson
	userInfo = m_userController->parseFromJson(result);

	//save info db 
	if (m_pSavePwd->GetCheck())
	{
		m_userController->saveUserInfoToFile(userInfo, DB_LOCAL_FILE);
		WritePrivateProfileString("data", "IsSavePwd", "1", INI_LOCAL_FILE.c_str());
	}
	else
	{
		WritePrivateProfileString("data", "IsSavePwd", "0", INI_LOCAL_FILE.c_str());
	}

	UserInfo* user = new UserInfo;
	user->setId(userInfo.getId());
	user->setPwd(userInfo.getPwd());
	user->setUserName(userInfo.getUserName());

	::PostMessage(GetHWND(), WM_LOGINSUCCESS, 0L, (LPARAM)user);
}



LRESULT LoginForm::LoginSuccess(LPARAM parameter)
{
	MainHome* mainHome = new MainHome;

	mainHome->Create(NULL, _T("Tim"), UI_WNDSTYLE_FRAME, WS_EX_STATICEDGE | WS_EX_APPWINDOW);
	mainHome->CenterWindow();
	mainHome->ShowWindow();

	UserInfo* user = (UserInfo*)(parameter);

	mainHome->setUserInfo(*user);

	mainHome->ShowWindow();
	this->ShowWindow(SW_HIDE);

	delete user;

	return 0;
}

DWORD WINAPI  LoginForm::UserWxLogin(LPVOID lpParameter)
{
	try
	{
		struct Prama* prama = (struct Prama*)lpParameter;
		string result;

		Sleep(1000);

		while (true)
		{
			result = HttpUtil::Get().HttpGet(HTTP_WX_LOGIN.c_str());
			if (result == "true")
			{
				UserInfo* userInfo = new UserInfo;
				userInfo->setId("123213");
				userInfo->setPwd("pwd");
				userInfo->setUserName("zhangsan");

				//PostMessage  UI Change
				::PostMessage(prama->hWnd, WM_LOGINSUCCESS, 0L, (LPARAM)userInfo);

				delete prama;
				break;
			}
			Sleep(1000);
		}


	}
	catch (const std::exception&)
	{
		return 0;
	}
}

void LoginForm::GetQrWx()
{
	QRcode* code = QRcode_encodeString(HTTP_WX_POST.c_str(), 0, QR_ECLEVEL_H, QR_MODE_8, 1);

	FILE* pf = fopen("bin/qrcode.bmp", "wb");
	if (NULL == pf)
	{
		printf("file open fail.\n");
		fclose(pf);
	}
	int width = code->width;
	int height = code->width;
	int biCount = 24;//真彩色
	int lineByte = (width * biCount / 8 + 3) / 4 * 4; //每line字节数必须为4的倍数
	//位图文件头
	BITMAPFILEHEADER bitMapFileHeader;
	bitMapFileHeader.bfType = 0x4D42;
	bitMapFileHeader.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + lineByte * height;
	bitMapFileHeader.bfReserved1 = 0;
	bitMapFileHeader.bfReserved2 = 0;
	bitMapFileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	//位图信息头
	BITMAPINFOHEADER bitMapInfoHeader;
	bitMapInfoHeader.biBitCount = biCount;
	bitMapInfoHeader.biClrImportant = 0;
	bitMapInfoHeader.biClrUsed = 0;
	bitMapInfoHeader.biCompression = 0;
	bitMapInfoHeader.biHeight = height;
	bitMapInfoHeader.biPlanes = 1;
	bitMapInfoHeader.biSize = 40;
	bitMapInfoHeader.biSizeImage = lineByte * height;
	bitMapInfoHeader.biWidth = width;
	bitMapInfoHeader.biXPelsPerMeter = 0;
	bitMapInfoHeader.biYPelsPerMeter = 0;
	//写文件头进文件
	fwrite(&bitMapFileHeader, sizeof(BITMAPFILEHEADER), 1, pf);
	//写位图信息头进文件
	fwrite(&bitMapInfoHeader, sizeof(BITMAPINFOHEADER), 1, pf);
	unsigned char* pBMPData = new unsigned char[lineByte * height];
	memset(pBMPData, 255, lineByte * height);

	unsigned char* qrData = code->data;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < lineByte / 3; j++)
		{
			if (*(qrData) & 1)
			{
				//设置rgb颜色，可自定义设置，这里设为黑色。
				*(pBMPData + lineByte * i + 3 * j) = 0;
				*(pBMPData + lineByte * i + 3 * j + 1) = 0;
				*(pBMPData + lineByte * i + 3 * j + 2) = 0;
			}
			qrData++;
		}
	}

	//写数据进文件
	fwrite(pBMPData, sizeof(unsigned char), lineByte * height, pf);
	fclose(pf);
	delete[] pBMPData;
	pBMPData = NULL;

	QRcode_free(code);

	Gdiplus::Bitmap btm(L"bin/qrcode.bmp");

	HBITMAP hBitmap = NULL;
	if (Gdiplus::Ok == btm.GetHBITMAP(NULL, &hBitmap))
	{
		CDuiString sCtrlKey = _T("qrimg");

		if (m_pQrImg)
		{
			m_PaintManager.RemoveImage(sCtrlKey);
			m_PaintManager.AddImage(sCtrlKey, hBitmap, 33, 33, false);		//w图片宽度  h图片高度
			m_pQrImg->SetBkImage(sCtrlKey);
		}

	}

}

LRESULT LoginForm::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;
	BOOL bHandled = TRUE;
	switch (uMsg) {
	case WM_LOGINSUCCESS:   lRes = LoginSuccess(lParam); break;
	case WM_CREATE:        lRes = OnCreate(uMsg, wParam, lParam, bHandled); break;
	case WM_CLOSE:         lRes = OnClose(uMsg, wParam, lParam, bHandled); break;
	case WM_DESTROY:       lRes = OnDestroy(uMsg, wParam, lParam, bHandled); break;
	case WM_NCACTIVATE:    lRes = OnNcActivate(uMsg, wParam, lParam, bHandled); break;
	case WM_NCCALCSIZE:    lRes = OnNcCalcSize(uMsg, wParam, lParam, bHandled); break;
	default:
		bHandled = FALSE;
	}
	if (bHandled) return lRes;
	if (m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes)) return lRes;
	return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
}



