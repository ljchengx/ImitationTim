#include "StdAfx.h"
#include "MainHome.h"




CDuiString MainHome::GetSkinFolder()
{
	return _T("skin\\");
}

CDuiString MainHome::GetSkinFile()
{
	return _T("NewMain.xml");
}

LPCTSTR MainHome::GetWindowClassName(void) const
{
	return _T("MainHome");
}

CControlUI* MainHome::CreateControl(LPCTSTR pstrClass)
{
	//custom xml
	if (_tcsicmp(pstrClass, _T("NewList")) == 0)
	{
		return new UICListItem(m_PaintManager);
	}
	return NULL;
}

void MainHome::Init()
{
	chatlist = static_cast<UICListItem*>(m_PaintManager.FindControl(_T("chatlist")));

	NewItem item1;
	item1.strPic = _T("images/tb.png");
	item1.strNiceName = _T(cuserinfo.getUserName().c_str());
	item1.strDes = _T(cuserinfo.getId().c_str());

	NewItem item2;
	item2.strPic = _T("images/tb.png");
	item2.strNiceName = _T("张三");
	item2.strDes = _T("123");


	chatlist->AddItem(item1);
	chatlist->AddItem(item2);


}


void MainHome::ShowInfo()
{
	MainInfo* mainInfo = new MainInfo;

	mainInfo->Create(NULL, _T("TimInfo"), UI_WNDSTYLE_FRAME, WS_EX_STATICEDGE | WS_EX_APPWINDOW);
	mainInfo->CenterWindow();
	mainInfo->ShowWindow();

}

void MainHome::ShowList()
{

}


void MainHome::OnClick(TNotifyUI& msg)
{
	CDuiString pSenderName = msg.pSender->GetName();
	if (pSenderName == _T("closebtn"))
	{
		if (MessageBox(GetHWND(), TEXT("确认退出？"), TEXT("提示"), MB_YESNO | MB_ICONINFORMATION) == IDNO)
		{
			return;
		}

		PostQuitMessage(0);
	}
	else if (pSenderName == _T("minbtn"))
	{
		SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, NULL);
	}
	else if (pSenderName == _T("maxbtn"))
	{
		SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, NULL);
	}
	else if (pSenderName == _T("restorebtn"))
	{
		SendMessage(WM_SYSCOMMAND, SC_RESTORE, NULL);
	}
	else if (pSenderName == _T("chatbtn"))
	{
		CTabLayoutUI* pTabLayout = (CTabLayoutUI*)m_PaintManager.FindControl(_T("tab_bar"));
		pTabLayout->SelectItem(0);
	}
	else if (pSenderName == _T("contactsbtn"))
	{
		CTabLayoutUI* pTabLayout = (CTabLayoutUI*)m_PaintManager.FindControl(_T("tab_bar"));
		pTabLayout->SelectItem(1);
	}
	else if (pSenderName == _T("filebtn"))
	{
		CTabLayoutUI* pTabLayout = (CTabLayoutUI*)m_PaintManager.FindControl(_T("tab_bar"));
		pTabLayout->SelectItem(2);
	}
	else if (pSenderName == _T("friendsbtn"))
	{
		CTabLayoutUI* pTabLayout = (CTabLayoutUI*)m_PaintManager.FindControl(_T("tab_contacts_bar"));
		pTabLayout->SelectItem(0);
	}
	else if (pSenderName == _T("groupbtn"))
	{
		CTabLayoutUI* pTabLayout = (CTabLayoutUI*)m_PaintManager.FindControl(_T("tab_contacts_bar"));
		pTabLayout->SelectItem(1);
	}
	else if (pSenderName == _T("mutilchatbtn"))
	{
		CTabLayoutUI* pTabLayout = (CTabLayoutUI*)m_PaintManager.FindControl(_T("tab_contacts_bar"));
		pTabLayout->SelectItem(2);
	}
	else if (pSenderName == _T("showbtn"))
	{
		ShowInfo();
	}
}

void MainHome::Notify(TNotifyUI& msg)
{

	if (msg.sType == _T("windowinit"))
	{
		Init();
	}
	else if (msg.sType == _T("itemclick"))
	{
	}
	__super::Notify(msg);

}

void MainHome::setUserInfo(UserInfo cuserinfo)
{
	this->cuserinfo = cuserinfo;
}
