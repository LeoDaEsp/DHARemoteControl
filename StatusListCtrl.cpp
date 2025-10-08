// FM_FaultView.cpp : implementation file
//

#include "stdafx.h"
#include "StatusListCtrl.h"

// CStatusListCtrl

IMPLEMENT_DYNCREATE(CStatusListCtrl, CSmartListCtrl)

CStatusListCtrl::CStatusListCtrl()
{
	DWORD		k;
	DWORD		w;

	for (w=0;w<20;w++)
	{
		for (k=0;k<256;k++)
		{
			m_ppFieldColor[w][k] = STTE_COLOR_WHITE;
		}
	}
}

CStatusListCtrl::~CStatusListCtrl()
{
}

BEGIN_MESSAGE_MAP(CStatusListCtrl, CSmartListCtrl)
END_MESSAGE_MAP()



// -----------------------------------------------------------------------------------
//	TextColorForSubItem
// -----------------------------------------------------------------------------------

 COLORREF CStatusListCtrl::TextColorForSubItem(int nItem,int nSubItem,UINT nState,LPARAM lParam) 
 { 
	 /*if (nSubItem>1)
	 {
		if (m_ppFaults[nItem][nSubItem-2])
		{
			return STTE_COLOR_RED;
		}
		else
		{
			return RGB(0,0,0);
		}
	 }
	else
	{
		return RGB(0,0,0);
	}*/
	return RGB(0,0,0);
 }

// =====================================================================================
//	CStatusListCtrl::BkColorForSubItem
// =====================================================================================

COLORREF CStatusListCtrl::BkColorForSubItem(int nItem,int nSubItem,UINT nState,LPARAM lParam) 
{
	 if (nSubItem>0)
	 {
		return m_ppFieldColor[nSubItem][nItem];
	 }
	else
	{
		return STTE_COLOR_WHITE;
	}
}


// -----------------------------------------------------------------------------------
//	FontForSubItem
// -----------------------------------------------------------------------------------

CFont* CStatusListCtrl::FontForSubItem(int nItem,int nSubItem,UINT nState,LPARAM lParam) 
{
	//if (DOC->m_pppFault[m_dwUnit][m_btType][nItem].m_btMode==CFaultItem::e_Mode_Disabled)
	{
		return NULL;
	}
	/*else
	{
		return &m_SelFont;
	}*/
}
