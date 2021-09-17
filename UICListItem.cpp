#include "StdAfx.h"
#include "UICListItem.h"

UICListItem::UICListItem(CPaintManagerUI& paint_manager) :paint_manager_(paint_manager)
{
	SetItemShowHtml(true);
}

UICListItem::~UICListItem()
{
	
}

bool UICListItem::Add(CControlUI* pControl)
{

	if (!pControl) {
		return false;
	}
	if (_tcsicmp(pControl->GetClass(), DUI_CTR_LISTCONTAINERELEMENT) != 0)
		return false;

	return CListUI::Add(pControl);
}

bool UICListItem::AddAt(CControlUI* pControl, int iIndex)
{
	if (!pControl)
		return false;

	if (_tcsicmp(pControl->GetClass(), DUI_CTR_LISTCONTAINERELEMENT) != 0)
		return false;

	return CListUI::AddAt(pControl, iIndex);
}

bool UICListItem::Remove(CControlUI* pControl, bool bDoNotDestroy)
{
	if (!pControl)
		return false;

	if (_tcsicmp(pControl->GetClass(), DUI_CTR_LISTCONTAINERELEMENT) != 0)
		return false;

	return CListUI::Remove(pControl);
}

bool UICListItem::RemoveAt(int iIndex, bool bDoNotDestroy)
{
	CControlUI* pControl = GetItemAt(iIndex);
	if (!pControl)
		return false;

	if (_tcsicmp(pControl->GetClass(), DUI_CTR_LISTCONTAINERELEMENT) != 0)
		return false;

	return CListUI::RemoveAt(iIndex);
}

void UICListItem::RemoveAll()
{
	CListUI::RemoveAll();
}

void UICListItem::AddItem(NewItem& itemdata)
{
	CListContainerElementUI* pItem = NULL;
	if (!m_dlgBuilder.GetMarkup()->IsValid())
	{
		pItem = static_cast<CListContainerElementUI*>(m_dlgBuilder.Create(_T("item.xml"), 0, NULL, &paint_manager_));
	}
	else {
		pItem = static_cast<CListContainerElementUI*>(m_dlgBuilder.Create(0, &paint_manager_));
	}
	if (!pItem) return;
	this->Add(pItem);

	//设置图片
	CButtonUI* pBtn = static_cast<CButtonUI*>(pItem->FindSubControl(_T("headbtn")));
	if (pBtn)
	{
		pBtn->SetNormalImage(itemdata.strPic);
	}
	//设置名称
	CLabelUI* pNickName = static_cast<CLabelUI*>(pItem->FindSubControl(_T("nicktext")));
	if (pNickName)
	{
		pNickName->SetText(itemdata.strNiceName);
	}
	//设置内容
	CLabelUI* pDes = static_cast<CLabelUI*>(pItem->FindSubControl(_T("msgtext")));
	if (pDes)
	{
		pDes->SetText(itemdata.strDes);
	}
}
