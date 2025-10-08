// =====================================================================================
//	@file					SmartListCtrl.h
//	@date					03/02/2016
//	@author					Massimiliano Forzieri, Formatech Engineering S.R.L.
//
//	@brief					Include file for SmartListCtrl object
//
//	@version Project:		Formatech DATA C++ Library
//	@version Part number:	
//	@version Environment:	Windows, Linux and QNX
//	@version Language:		ANSI C++
// -----------------------------------------------------------------------------------
//	@version	Revision summary:
//	@version	Rev 1.1.0001	M.Forzieri		Initial Release
// =====================================================================================


#pragma once


// *************************************************************************************
// *************************************************************************************
//	Class CSmartListCtrl
// *************************************************************************************
// *************************************************************************************

class CSmartListCtrl : public CListCtrl
{
	DECLARE_DYNCREATE(CSmartListCtrl)

// =====================================================================================
//	VARIABLES
// =====================================================================================

protected:

	CFont*	m_pOldItemFont;
	CFont*	m_pOldSubItemFont;

	// Handle bitmap di background
	HBITMAP		m_hBackgroundBmp;
	COLORREF	m_colBackground;

public:

// =====================================================================================
// CONSTRUCTORS & DECTRUCTORS
// =====================================================================================

//protected:

	CSmartListCtrl();           // protected constructor used by dynamic creation
	virtual ~CSmartListCtrl();

// =====================================================================================
// FUNCTIONS
// =====================================================================================


protected:

	virtual bool		IsDraw();
	virtual bool		OnDraw(CDC* pDC, const CRect& r);
	virtual bool		IsNotifyItemDraw();
	virtual bool		IsNotifyPostPaint();
	virtual bool		IsPostDraw();
	virtual bool		OnPostDraw(CDC* pDC, const CRect& r);
	virtual CFont*		FontForItem(int nItem,UINT nState,LPARAM lParam);
	virtual COLORREF	TextColorForItem(int nItem,UINT nState,LPARAM lParam);
	virtual COLORREF	BkColorForItem(int nItem,UINT nState,LPARAM lParam);
	virtual bool		IsItemDraw(int nItem,UINT nState,LPARAM lParam);
	virtual bool		OnItemDraw(CDC* pDC,int nItem,UINT nState,LPARAM lParam);
	virtual bool		IsNotifySubItemDraw(int nItem,UINT nState,LPARAM lParam);
	virtual bool		IsNotifyItemPostPaint(int nItem,UINT nState,LPARAM lParam);
	virtual bool		IsItemPostDraw();
	virtual bool		OnItemPostDraw(CDC* pDC,int nItem,UINT nState,LPARAM lParam);
	virtual CFont*		FontForSubItem(int nItem,int nSubItem,UINT nState,LPARAM lParam);
	virtual COLORREF	TextColorForSubItem(int nItem,int nSubItem,UINT nState,LPARAM lParam);
	virtual COLORREF	BkColorForSubItem(int nItem,int nSubItem,UINT nState,LPARAM lParam);
	virtual bool		IsSubItemDraw(int nItem, int nSubItem, UINT nState, LPARAM lParam);
	virtual bool		OnSubItemDraw(CDC* pDC, int nItem,int nSubItem,UINT nState,LPARAM lParam);
	virtual bool		IsNotifySubItemPostPaint(int nItem,int nSubItem,UINT nState,LPARAM lParam);
	virtual bool		IsSubItemPostDraw();
	virtual bool		OnSubItemPostDraw(CDC* pDC, int nItem, int nSubItem,UINT nState,LPARAM lParam);

	CDC* 				GetBackBufferDC(CDC *pDC);
	CDC* 				GetBackBufferDC(CDC *pDC,int iPosX,int iPosY,DWORD dwDimX,DWORD dwDimY,HBITMAP *phBmp);
	void 				ReleaseBackBufferDC(CDC *pDC);
	void 				CopyBackBufferDC(CDC *pDDC,CDC *pSDC,CRect *pSRC = NULL);
	virtual void		DrawBackground(CDC* pDC);

public:

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};


