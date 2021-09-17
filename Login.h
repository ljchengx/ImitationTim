#pragma once

#include "StdAfx.h"
#include "MainHome.h"
#include "UserInfoController.h"

#define WM_LOGINSUCCESS WM_USER + 55



struct Prama
{
	HWND hWnd;	
};

class LoginForm:public WindowImplBase
{
public:
	LoginForm();
	~LoginForm();
private:


	// 通过 WindowImplBase 继承
	virtual CDuiString GetSkinFolder() override;
	
	virtual CDuiString GetSkinFile() override;

	virtual LPCTSTR GetWindowClassName(void) const override;

	virtual void Notify(TNotifyUI& msg);

	virtual void OnClick(TNotifyUI& msg);

	virtual LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	virtual LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	virtual LRESULT OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	virtual LRESULT OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	//初始化
	void Init();

	//用户登录操作
	void UserLogin();

	//获取微信登录二维码
	void GetQrWx();

	//登录成功
	LRESULT LoginSuccess(LPARAM parameter);

	//模拟获取微信登录状态
	static DWORD WINAPI  UserWxLogin(LPVOID lpParameter);

	
private:
	CButtonUI* m_pLogin;
	CEditUI* m_pUserName;
	CEditUI* m_pPassWord;
	CCheckBoxUI* m_pSavePwd;
	CTabLayoutUI* m_pTabLayout;
	COptionUI* m_pOptionQQ;
	COptionUI* m_pOptionWx;
	CControlUI* m_pQrImg;

	UserController* m_userController;

	int status;
};


