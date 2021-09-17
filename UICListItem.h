#pragma once
#include "StdAfx.h"


struct NewItem
{
	//头像
	CDuiString strPic;
	//名称
	CDuiString strNiceName;
	//描述
	CDuiString strDes;
};

class UICListItem :public CListUI {

public:
	enum { SCROLL_TIMERID = 10 };

	UICListItem(CPaintManagerUI& paint_manager);

	~UICListItem();

	bool Add(CControlUI* pControl);

	bool AddAt(CControlUI* pControl, int iIndex);

	bool Remove(CControlUI* pControl, bool bDoNotDestroy = false);

	bool RemoveAt(int iIndex, bool bDoNotDestroy);

	void RemoveAll();

	//定制方法
	void AddItem(NewItem& itemdata);

private:
	CPaintManagerUI& paint_manager_;

	CDialogBuilder m_dlgBuilder;
};