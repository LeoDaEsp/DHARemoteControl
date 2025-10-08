#pragma once

#include "SmartListCtrl.h"

// CStatusListCtrl view

class CStatusListCtrl : public CSmartListCtrl
{
	DECLARE_DYNCREATE(CStatusListCtrl)

public:

	COLORREF		m_ppFieldColor[20][256];

	CStatusListCtrl();
	virtual ~CStatusListCtrl();

public:

	virtual COLORREF	TextColorForSubItem(int nItem,int nSubItem,UINT nState,LPARAM lParam);
	virtual CFont*		FontForSubItem(int nItem,int nSubItem,UINT nState,LPARAM lParam) ;
 	virtual COLORREF	BkColorForSubItem(int nItem,int nSubItem,UINT nState,LPARAM lParam);

protected:
	DECLARE_MESSAGE_MAP()
};


