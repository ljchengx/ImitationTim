#include "StdAfx.h"
#include "MainInfo.h"

MainInfo::MainInfo()
{
}

MainInfo::~MainInfo()
{
}

CDuiString MainInfo::GetSkinFolder()
{
	return _T("skin\\");
}

CDuiString MainInfo::GetSkinFile()
{
	return _T("MainInfo.xml");
}

LPCTSTR MainInfo::GetWindowClassName(void) const
{
	return _T("MainInfo");
}


void MainInfo::Init()
{

}

void MainInfo::setUserInfo(UserInfo cuserinfo)
{
	this->cuserinfo = cuserinfo;
}

void MainInfo::Notify(TNotifyUI& msg)
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

void MainInfo::OnClick(TNotifyUI& msg)
{
	CDuiString pSenderName = msg.pSender->GetName();
	if (pSenderName == _T("closebtn"))
	{

		Close();
	}
}
