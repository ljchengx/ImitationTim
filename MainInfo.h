#pragma once
#include "StdAfx.h"
#include "UserInfo.h"

class MainInfo:public WindowImplBase
{

public:
	MainInfo();
	~MainInfo();
private:
	// Í¨¹ý WindowImplBase ¼Ì³Ð
	virtual CDuiString GetSkinFolder() override;

	virtual CDuiString GetSkinFile() override;

	virtual LPCTSTR GetWindowClassName(void) const override;

	virtual void Notify(TNotifyUI& msg) override;

	virtual void OnClick(TNotifyUI& msg);


	void Init();

public:

	void setUserInfo(UserInfo cuserinfo);

private:
	UserInfo cuserinfo;
};

