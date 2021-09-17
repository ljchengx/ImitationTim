// ImitationTim.cpp : 定义应用程序的入口点。
//
#include "StdAfx.h"
#include "Login.h"
#include "DuiLib\UIlib.h"


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
   CPaintManagerUI::SetInstance(hInstance);

   LoginForm* loginFrom = new LoginForm();
   if (loginFrom == NULL) return 0;

   loginFrom->Create(NULL, _T("ImitationTim"), UI_WNDSTYLE_FRAME, WS_EX_STATICEDGE | WS_EX_APPWINDOW, 0);

   loginFrom->CenterWindow();//居中窗口位置

   loginFrom->ShowModal();

   CPaintManagerUI::MessageLoop();//开启duilib的消息循环，通用做法，Windows是基于消息机制的操作系统

   return 0;
}

