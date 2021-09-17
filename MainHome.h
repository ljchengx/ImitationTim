#pragma once
#include "StdAfx.h"
#include "UICListItem.h"
#include "MainInfo.h"
#include "UserInfo.h"

class MainHome :public WindowImplBase
{
public:

	MainHome() {
	};

	~MainHome() {
	};

private:

	// Í¨¹ý WindowImplBase ¼Ì³Ð
	virtual CDuiString GetSkinFolder() override;

	virtual CDuiString GetSkinFile() override;

	virtual LPCTSTR GetWindowClassName(void) const override;

	virtual CControlUI* CreateControl(LPCTSTR pstrClass);

	void Init();

	void ShowList();

	void ShowInfo();

	virtual void OnClick(TNotifyUI& msg);

	virtual void Notify(TNotifyUI& msg) override;

public:
	void setUserInfo(UserInfo cuserinfo);

private:
	UICListItem* chatlist;
	CListUI* firendslist;
	CListUI* grouplist;
	CListUI* multiplayerlist;

	UserInfo cuserinfo;

};