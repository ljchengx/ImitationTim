#pragma once
#include "StdAfx.h"


struct NewItem
{
	//ͷ��
	CDuiString strPic;
	//����
	CDuiString strNiceName;
	//����
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

	//���Ʒ���
	void AddItem(NewItem& itemdata);

private:
	CPaintManagerUI& paint_manager_;

	CDialogBuilder m_dlgBuilder;
};