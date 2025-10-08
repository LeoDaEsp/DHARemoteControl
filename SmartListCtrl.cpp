// =====================================================================================
//	@file					SmartListCtrl.cpp
//	@date					03/02/2016
//	@author					Massimiliano Forzieri, Formatech Engineering S.R.L.
//
//	@brief					Source file for SmartListCtrl object
//
//	@version Project:		Formatech DATA C++ Library
//	@version Part number:	
//	@version Environment:	Windows, Linux and QNX
//	@version Language:		ANSI C++
// -----------------------------------------------------------------------------------
//	@version	Revision summary:
//	@version	Rev 1.1.0001	M.Forzieri		Initial Release
// =====================================================================================


#include "stdafx.h"
#include "SmartListCtrl.h"

// *************************************************************************************
// *************************************************************************************
//	Class CSmartListCtrl
// *************************************************************************************
// *************************************************************************************

IMPLEMENT_DYNCREATE(CSmartListCtrl, CListCtrl)

// =====================================================================================
//	CSmartListCtrl::CSmartListCtrl
// =====================================================================================

CSmartListCtrl::CSmartListCtrl()
{
	m_colBackground = RGB(255,255,255);
}


// =====================================================================================
//	CSmartListCtrl::~CSmartListCtrl
// =====================================================================================

CSmartListCtrl::~CSmartListCtrl()
{
}


// =====================================================================================
//	CSmartListCtrl Message Map
// =====================================================================================

BEGIN_MESSAGE_MAP(CSmartListCtrl, CListCtrl)
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, &CSmartListCtrl::OnNMCustomdraw)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()



// =====================================================================================
//	CSmartListCtrl::OnNMCustomdraw
// =====================================================================================

void CSmartListCtrl::OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult)
{
	// first, lets extract data from
	// the message for ease of use later
	NMLVCUSTOMDRAW* pNMLVCUSTOMDRAW = (NMLVCUSTOMDRAW*)pNMHDR;
 
	// we'll copy the device context into hdc 
	// but won't convert it to a pDC* until (and if)
	// we need it as this requires a bit of work
	// internally for MFC to create temporary CDC
	// objects

	HDC hdc = pNMLVCUSTOMDRAW->nmcd.hdc;
	CDC* pDC = NULL;
 
	// here is the item info
	// note that we don't get the subitem
	// number here, as this may not be
	// valid data except when we are
	// handling a sub item notification
	// so we'll do that separately in
	// the appropriate case statements
	// below.

	int nItem = pNMLVCUSTOMDRAW->nmcd.dwItemSpec;
	UINT nState = pNMLVCUSTOMDRAW->nmcd.uItemState;
	LPARAM lParam = pNMLVCUSTOMDRAW->nmcd.lItemlParam;
 
	// next we set up flags that will control
	// the return value for *pResult

	bool bNotifyPostPaint = false;
	bool bNotifyItemDraw = false;
	bool bNotifySubItemDraw = false;
	bool bSkipDefault = false;
	bool bNewFont = false;
 
	// what we do next depends on the
	// drawing stage we are processing

	switch (pNMLVCUSTOMDRAW->nmcd.dwDrawStage) 
	{
		case CDDS_PREPAINT:
		{
			// PrePaint
			m_pOldItemFont = NULL;
			m_pOldSubItemFont = NULL;
	   
			bNotifyPostPaint = IsNotifyPostPaint();
			bNotifyItemDraw = IsNotifyItemDraw();
	  
			// do we want to draw the control ourselves?
			if (IsDraw()) 
			{
				if (! pDC) 
				{
					pDC = CDC::FromHandle(hdc);
				}

				CRect r(pNMLVCUSTOMDRAW->nmcd.rc);
	   
				// do the drawing

				if (OnDraw(pDC,r)) 
				{
					// we drew it all ourselves
					// so don't do default
					bSkipDefault = true;
				}
			}
		}
		break;
	 
		case CDDS_ITEMPREPAINT:
		{
			// Item PrePaint
			m_pOldItemFont = NULL;
	  
			bNotifyPostPaint = IsNotifyItemPostPaint(nItem,nState,lParam);
			bNotifySubItemDraw = IsNotifySubItemDraw(nItem,nState,lParam);
	 
			// set up the colors to use
			pNMLVCUSTOMDRAW->clrText = TextColorForItem(nItem,nState,lParam);
	 
			pNMLVCUSTOMDRAW->clrTextBk = BkColorForItem(nItem,nState,lParam);
	 
			// set up a different font to use, if any
			CFont* pNewFont = FontForItem(nItem,nState,lParam);

			if (pNewFont) 
			{
				if (! pDC) 
				{
					pDC = CDC::FromHandle(hdc);
				}

				m_pOldItemFont = pDC->SelectObject(pNewFont);
	 
				bNotifyPostPaint = true; // need to restore font
			}
	 
			// do we want to draw the item ourselves?
			if (IsItemDraw(nItem,nState,lParam)) 
			{
				if (! pDC)
				{
					pDC = CDC::FromHandle(hdc);
				}
	   
				if (OnItemDraw(pDC,nItem,nState,lParam)) 
				{
					// we drew it all ourselves
					// so don't do default
					bSkipDefault = true;
				}
			}
		}
		break;
	 
		case CDDS_ITEMPREPAINT|CDDS_SUBITEM:
		{
			// Sub Item PrePaint
			// set sub item number (data will be valid now)
			int nSubItem = pNMLVCUSTOMDRAW->iSubItem;
	  
			m_pOldSubItemFont = NULL;
	  
			bNotifyPostPaint = IsNotifySubItemPostPaint(nItem, nSubItem, nState, lParam);
	 
			// set up the colors to use
			pNMLVCUSTOMDRAW->clrText = TextColorForSubItem(nItem,nSubItem,nState,lParam);
	 
			pNMLVCUSTOMDRAW->clrTextBk = BkColorForSubItem(nItem,nSubItem,nState,lParam);
	 
			// set up a different font to use, if any
			CFont* pNewFont = FontForSubItem(nItem, nSubItem, nState, lParam);
	 
			if (pNewFont)
			{
				if (! pDC)
				{
					pDC = CDC::FromHandle(hdc);
				}

				m_pOldSubItemFont = pDC->SelectObject(pNewFont);
	   
				bNotifyPostPaint = true;    // need to restore font
			}
	   
			// do we want to draw the item ourselves?
			if (IsSubItemDraw(nItem,nSubItem,nState,lParam))
			{
				if (! pDC)
				{
					pDC = CDC::FromHandle(hdc);
				}

				if (OnSubItemDraw(pDC,nItem,nSubItem,nState,lParam))
				{
					// we drew it all ourselves
					// so don't do default
					bSkipDefault = true;
				}
			}
		}
		break;
	 
		case CDDS_ITEMPOSTPAINT|CDDS_SUBITEM:
		{
			// Sub Item PostPaint
			// set sub item number (data will be valid now)

			int nSubItem = pNMLVCUSTOMDRAW->iSubItem;
	  
			// restore old font if any
			if (m_pOldSubItemFont)
			{
				if (! pDC)
				{
					pDC = CDC::FromHandle(hdc);
				}

				pDC->SelectObject(m_pOldSubItemFont);
	  
				m_pOldSubItemFont = NULL;
			}
	  
			// do we want to do any extra drawing?
			if (IsSubItemPostDraw())
			{
				if (! pDC)
				{
					pDC = CDC::FromHandle(hdc);
				}

				OnSubItemPostDraw(pDC,nItem,nSubItem,nState,lParam);
			}
		}
		break;
	 
		case CDDS_ITEMPOSTPAINT:
		{
			// Item PostPaint
			// restore old font if any

			if (m_pOldItemFont)
			{
				if (! pDC)
				{
					pDC = CDC::FromHandle(hdc);
				}

				pDC->SelectObject(m_pOldItemFont);
				m_pOldItemFont = NULL;
			}
	  
			// do we want to do any extra drawing?
			if (IsItemPostDraw())
			{
				if (! pDC)
				{
					pDC = CDC::FromHandle(hdc);
				}

				OnItemPostDraw(pDC,nItem,nState,lParam);
			}
		}
		break;
	 
		case CDDS_POSTPAINT:
		{
			// Item PostPaint
			// do we want to do any extra drawing?

			if (IsPostDraw())
			{
				if (! pDC)
				{
					pDC = CDC::FromHandle(hdc);
				}

				CRect r(pNMLVCUSTOMDRAW->nmcd.rc);
	 
				OnPostDraw(pDC,r);
			}
		}
		break;
	}
 
	ASSERT(CDRF_DODEFAULT==0);
	*pResult = 0;

	if (bNotifyPostPaint)
	{
		*pResult |= CDRF_NOTIFYPOSTPAINT;
	}
 
	if (bNotifyItemDraw)
	{
		*pResult |= CDRF_NOTIFYITEMDRAW;
	}
 
	if (bNotifySubItemDraw)
	{
		*pResult |= CDRF_NOTIFYSUBITEMDRAW;
	}
 
	if (bNewFont)
	{
		*pResult |= CDRF_NEWFONT;
	}
 
	if (bSkipDefault)
	{
		*pResult |= CDRF_SKIPDEFAULT;
	}
 
	if (*pResult == 0)
	{
		// redundant as CDRF_DODEFAULT==0 anyway
		// but shouldn't depend on this in our code
		*pResult = CDRF_DODEFAULT;
	}
}
	


// =====================================================================================
//	CSmartListCtrl::IsDraw
//
//	Do we want to do the drawing ourselves?
// =====================================================================================

bool CSmartListCtrl::IsDraw()
{
	return false;
}
 
// =====================================================================================
//	CSmartListCtrl::OnDraw

//	if we are doing the drawing ourselves override and put the code in here
//	and return TRUE if we did indeed do all the drawing ourselves
// =====================================================================================

bool CSmartListCtrl::OnDraw(CDC* pDC, const CRect& r) 
{
	return false;
}
 
// =====================================================================================
//	CSmartListCtrl::IsNotifyItemDraw
//
//	Do we want to handle custom draw for individual items
// =====================================================================================

bool CSmartListCtrl::IsNotifyItemDraw()
{
	return true;
}
 
// =====================================================================================
//	CSmartListCtrl::IsNotifyPostPaint
//
//	Do we want to be notified when the painting has finished
// =====================================================================================

bool CSmartListCtrl::IsNotifyPostPaint()
{
	return false;
}
 
// =====================================================================================
//	CSmartListCtrl::IsPostDraw
//
//	Do we want to do any drawing after the list control is finished
// =====================================================================================
 
bool CSmartListCtrl::IsPostDraw()
{
	return false;
}
 
// =====================================================================================
//	CSmartListCtrl::OnPostDraw
//
//	If we are doing the drawing afterwards ourselves override and put the code in here
//	the return value is not used here
// =====================================================================================

bool CSmartListCtrl::OnPostDraw(CDC* pDC, const CRect& r) 
{
	return false;
}
	
// =====================================================================================
//	CSmartListCtrl::FontForItem
//
//	Return a pointer to the font to use for this item.
//	Return NULL to use default
// =====================================================================================

CFont* CSmartListCtrl::FontForItem(int nItem,UINT nState,LPARAM lParam) 
{
	return NULL;
}
 
// =====================================================================================
//	CSmartListCtrl::TextColorForItem
//
//	Return the text color to use for this item
//	Return CLR_DEFAULT to use default
// =====================================================================================

COLORREF CSmartListCtrl::TextColorForItem(int nItem,UINT nState,LPARAM lParam) 
{ 
	return CLR_DEFAULT; 
}
 
// =====================================================================================
//	CSmartListCtrl::BkColorForItem
//
//	Return the background color to use for this item
//	Return CLR_DEFAULT to use default
// =====================================================================================

COLORREF CSmartListCtrl::BkColorForItem(int nItem,UINT nState,LPARAM lParam) 
{
	return CLR_DEFAULT;
}
 
// =====================================================================================
//	CSmartListCtrl::IsItemDraw
//
//	Do we want to do the drawing for this item ourselves?
// =====================================================================================

bool CSmartListCtrl::IsItemDraw(int nItem,UINT nState,LPARAM lParam) 
{
	return false;
}
 
// =====================================================================================
//	CSmartListCtrl::OnItemDraw
//
//	If we are doing the drawing ourselves override and put the code in here
//	and return TRUE if we did indeed do all the drawing ourselves
// =====================================================================================

bool CSmartListCtrl::OnItemDraw(CDC* pDC,int nItem,UINT nState,LPARAM lParam) 
{
	return false;
}


// =====================================================================================
//	CSmartListCtrl::IsNotifySubItemDraw
//
//	Do we want to handle custom draw for individual sub items
// =====================================================================================

bool CSmartListCtrl::IsNotifySubItemDraw(int nItem,UINT nState,LPARAM lParam) 
{
	return true;
}

// =====================================================================================
//	CSmartListCtrl::IsNotifyItemPostPaint
//
//	Do we want to be notified when the painting has finished
// =====================================================================================

bool CSmartListCtrl::IsNotifyItemPostPaint(int nItem,UINT nState,LPARAM lParam) 
{
	return false;
}
 
// =====================================================================================
//	CSmartListCtrl::IsItemPostDraw
//
//	Do we want to do any drawing after the list control is finished
// =====================================================================================

bool CSmartListCtrl::IsItemPostDraw()
{
	return false;
}
 
// =====================================================================================
//	CSmartListCtrl::OnItemPostDraw
//
//	If we are doing the drawing afterwards ourselves override and put the code in here
//	the return value is not used here
// =====================================================================================

bool CSmartListCtrl::OnItemPostDraw(CDC* pDC,int nItem,UINT nState,LPARAM lParam) 
{
	return false;
}
 
// =====================================================================================
//	CSmartListCtrl::FontForSubItem
//
//	Return a pointer to the font to use for this sub item.
//	Return NULL to use default
// =====================================================================================

CFont* CSmartListCtrl::FontForSubItem(int nItem,int nSubItem,UINT nState,LPARAM lParam) 
{
	return NULL;
}
 
// =====================================================================================
//	CSmartListCtrl::TextColorForSubItem
//
//	Return the text color to use for this sub item
//	Return CLR_DEFAULT to use default
// =====================================================================================

COLORREF CSmartListCtrl::TextColorForSubItem(int nItem,int nSubItem,UINT nState,LPARAM lParam) 
{ 
	return CLR_DEFAULT; 
}
 
// =====================================================================================
//	CSmartListCtrl::BkColorForSubItem
//
//	Return the background color to use for this sub item
//	Return CLR_DEFAULT to use default
// =====================================================================================

COLORREF CSmartListCtrl::BkColorForSubItem(int nItem,int nSubItem,UINT nState,LPARAM lParam) 
{
	return CLR_DEFAULT;
}
 
// =====================================================================================
//	CSmartListCtrl::IsSubItemDraw
//
//	Do we want to do the drawing for this sub item ourselves?
// =====================================================================================

bool CSmartListCtrl::IsSubItemDraw(int nItem,int nSubItem,UINT nState,LPARAM lParam) 
{
	return false;
}
 
// =====================================================================================
//	CSmartListCtrl::OnSubItemDraw
//
//	If we are doing the drawing ourselves override and put the code in here
//	and return TRUE if we did indeed do all the drawing ourselves
// =====================================================================================

bool CSmartListCtrl::OnSubItemDraw(CDC* pDC,int nItem,int nSubItem,UINT nState,LPARAM lParam) 
{
	return false;
}
 
// =====================================================================================
//	CSmartListCtrl::IsNotifySubItemPostPaint
//
//	Do we want to be notified when the painting has finished
// =====================================================================================

bool CSmartListCtrl::IsNotifySubItemPostPaint(int nItem,int nSubItem,UINT nState,LPARAM lParam) 
{
	return false;
}
 
// =====================================================================================
//	CSmartListCtrl::IsSubItemPostDraw
//
//	Do we want to do any drawing after the list control is finished
// =====================================================================================

bool CSmartListCtrl::IsSubItemPostDraw()
{
	return false;
}
 
// =====================================================================================
//	CSmartListCtrl::OnSubItemPostDraw
//
//	If we are doing the drawing afterwards ourselves override and put the code in here
//	the return value is not used here
// =====================================================================================

bool CSmartListCtrl::OnSubItemPostDraw(CDC* pDC, int nItem,int nSubItem,UINT nState,LPARAM lParam) 
{
	return false;
}








// -----------------------------------------------------------------------------------
//	Function:	GetBackBufferDC
// -----------------------------------------------------------------------------------

CDC* CSmartListCtrl::GetBackBufferDC(CDC *pDC)
{
	CRect cr;
	GetClientRect(&cr);

	return GetBackBufferDC(pDC,0,0,cr.Width(),cr.Height(),&m_hBackgroundBmp);
}

// -----------------------------------------------------------------------------------
//	Function:	GetBackBufferDC
// -----------------------------------------------------------------------------------

CDC* CSmartListCtrl::GetBackBufferDC(CDC *pDC,int iPosX,int iPosY,DWORD dwDimX,DWORD dwDimY,HBITMAP *phBmp)
{
	CRect cr;
	GetClientRect(&cr);

	// Creo il DC compatibile per la costruzione dell'immagine -------------

	HBITMAP hTBmp,delbmp;
	CDC *pOwnDC=GetDC();
	CDC *pTDC=new CDC();

	if (!(pTDC->CreateCompatibleDC(pOwnDC)))
		ASSERT(0);

	BITMAP bmp;         // bitmap data structure 

	bmp.bmBitsPixel=(BYTE)(pOwnDC->GetDeviceCaps(BITSPIXEL)); 
	bmp.bmPlanes=(BYTE)(pOwnDC->GetDeviceCaps(PLANES)); 
	bmp.bmWidth=(pOwnDC->GetDeviceCaps(HORZRES)); 
	bmp.bmHeight=(pOwnDC->GetDeviceCaps(VERTRES)); 
 
	bmp.bmWidthBytes = ((bmp.bmWidth + 15) &~15)/8; 
 
	hTBmp=CreateBitmap(bmp.bmWidth,bmp.bmHeight, 
							bmp.bmPlanes,bmp.bmBitsPixel,(CONST VOID *) NULL); 
 
	delbmp=(HBITMAP)(pTDC->SelectObject(hTBmp));
	pTDC->SetMapMode(pOwnDC->GetMapMode());

	// Creo il back buffer di ritorno
	
	CDC *pHDC=new CDC();
	HBITMAP hHBmp;

	if (!(pHDC->CreateCompatibleDC(pDC)))
		ASSERT(0);

	bmp.bmBitsPixel=(BYTE)(pDC->GetDeviceCaps(BITSPIXEL)); 
	bmp.bmPlanes=(BYTE)(pDC->GetDeviceCaps(PLANES)); 
	bmp.bmWidth=(pDC->GetDeviceCaps(HORZRES)); 
	bmp.bmHeight=(pDC->GetDeviceCaps(VERTRES)); 
 
	bmp.bmWidthBytes = ((bmp.bmWidth + 15) &~15)/8; 
 
	hHBmp=CreateBitmap(bmp.bmWidth,bmp.bmHeight, 
							bmp.bmPlanes,bmp.bmBitsPixel,(CONST VOID *) NULL); 
 
	pHDC->SelectObject(hHBmp);
	pHDC->BitBlt(0,0,dwDimX,dwDimY,pTDC,iPosX,iPosY,SRCCOPY);

	pTDC->SelectObject(delbmp);
	DeleteObject(hTBmp);
	delete pTDC;

	ReleaseDC(pOwnDC);

	(*phBmp)=hHBmp;
	return pHDC;
}

// -----------------------------------------------------------------------------------
//	Function:	ReleaseBackBufferDC
// -----------------------------------------------------------------------------------

void CSmartListCtrl::ReleaseBackBufferDC(CDC *pDC)
{
	DeleteObject(m_hBackgroundBmp);
	delete pDC;
}

// -----------------------------------------------------------------------------------
//	CopyBackBufferDC
// -----------------------------------------------------------------------------------

void CSmartListCtrl::CopyBackBufferDC(CDC *pDDC, CDC *pSDC, CRect *pSRC)
{

	pDDC->BitBlt(pSRC->left, pSRC->top, pSRC->Width(), pSRC->Height(), pSDC, pSRC->left, pSRC->top, SRCCOPY);
	



	/*if (pSRC==NULL)
	{
		CRect cr;
		GetClientRect(&cr);

		pDDC->BitBlt(cr.left,cr.top,cr.Width(),cr.Height(),pSDC,0,0,SRCCOPY);
	}
	else
	{
		pDDC->BitBlt(pSRC->left,pSRC->top,pSRC->Width(),pSRC->Height(),pSDC,pSRC->left,pSRC->top,SRCCOPY);
	}*/
}




// -----------------------------------------------------------------------------------
//	CSmartListCtrl::OnPaint
// -----------------------------------------------------------------------------------

void CSmartListCtrl::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CListCtrl::OnPaint() for painting messages

	CRect	cr;
	CRgn	rgn;
	CRect	dr;
	CRect	hr;

	GetClientRect(&cr);
	dr = dc.m_ps.rcPaint;

	rgn.CreateRectRgnIndirect(&cr);

	// Creo il DC compatibile per la costruzione dell'immagine -------------
	CDC *pHDC;

	// Disegno il controllo sul DC compatibile -----------------------------
	pHDC = GetBackBufferDC(&dc);

	DrawBackground(pHDC);

	DefWindowProc(WM_PAINT, (WPARAM)pHDC->m_hDC, (LPARAM)0);
	
	CopyBackBufferDC(&dc, pHDC, &dr);
	ReleaseBackBufferDC(pHDC);

	hr = dr;
	ClientToScreen(&hr);
	GetHeaderCtrl()->ScreenToClient(&hr);
	GetHeaderCtrl()->RedrawWindow(&hr);
}

// -----------------------------------------------------------------------------------
//	CSmartListCtrl::DrawBackground
// -----------------------------------------------------------------------------------

void CSmartListCtrl::DrawBackground(CDC* pDC)
{
	CRect		cr;

	GetClientRect(&cr);

	pDC->FillSolidRect(&cr, m_colBackground);

}


// -----------------------------------------------------------------------------------
//	CSmartListCtrl::OnEraseBkgnd
// -----------------------------------------------------------------------------------

BOOL CSmartListCtrl::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	//return CListCtrl::OnEraseBkgnd(pDC);
	return FALSE;
}
