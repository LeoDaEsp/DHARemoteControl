//***************************************************************************
//
// Module:		FMT_Wnd.cpp
//
// Description:	Finestra base controlli FM
//				
//
// Unit:		-
// Subunit:		-
//
// Environment:	Microsoft Visual C++	
//
// Version control
//
// Rev.		Data		Author			Modified		
// --------------------------------------------------------------------------
//	1.0		26-01-03	M.Forzieri		First issue
// --------------------------------------------------------------------------
//***************************************************************************

#include "stdafx.h"

#ifndef FMTWND_CPP
#define FMTWND_CPP

#ifndef FMTWND_H
#include "FMT_Wnd.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// *************************************************************************************
// *************************************************************************************
//	Class CFMT_Wnd
// *************************************************************************************
// *************************************************************************************

IMPLEMENT_DYNCREATE(CFMT_Wnd, CWnd)

// =====================================================================================
//	MESSAGE MAP
// =====================================================================================


// =====================================================================================
// COSTRUTTORI E DISTRUTTORI
// =====================================================================================

CFMT_Wnd::CFMT_Wnd()
{
	for (DWORD i=0;i<5;i++)
		m_ppBorderPen[i]=NULL;

	m_colBorder=GetSysColor(COLOR_MENU);

	m_dwStyle=0;

	m_pBackgroundBrush=new CBrush;
	m_pBackgroundBrush->CreateSolidBrush(GetSysColor(COLOR_WINDOW));

	m_BackgroundColor=GetSysColor(COLOR_WINDOW);

//	CreatePens();

	m_dwStyle=FMTWND_COLOR_BACKGROUND;

	m_dwParamPos=0;

	m_MarginCR.SetRect(0,0,0,0);
}

CFMT_Wnd::~CFMT_Wnd()
{
	DWORD i;

	// Distrugge le penne per l'area non client
	/*for (DWORD i=0;i<5;i++)
	{
		if (m_ppBorderPen[i]!=NULL)
			delete m_ppBorderPen[i];
	}*/

	// Distrugge la lista dei font

	m_FontList.ToStart();

	for (i=0;i<!m_FontList;i++)
	{
		if (m_FontList.CurItem()->bDeletable)
			delete ((CFont*)(m_FontList.CurItem()->pItem));

		delete m_FontList.CurItem();

		m_FontList>>1;
	}

	// Distrugge il brush di background
	delete m_pBackgroundBrush;
}

// =====================================================================================
//	OPERATORI
// =====================================================================================

// =====================================================================================
//	FUNZIONI
// =====================================================================================

// -----------------------------------------------------------------------------------
//	Function:	SetFMTStyle
// -----------------------------------------------------------------------------------

BOOL CFMT_Wnd::Create(LPCTSTR lpszClassName,LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect,CWnd* pParentWnd,UINT nID,CCreateContext* pContext)

{
	return CWnd::Create(lpszClassName,lpszWindowName,dwStyle,rect,pParentWnd,nID,pContext);
}


// -----------------------------------------------------------------------------------
//	Function:	SetFMTStyle
// -----------------------------------------------------------------------------------
//	Desc.	:	Imposta lo stile FM
//
//	Return	:	-
//	Params	:	dwStyle = stile
// -----------------------------------------------------------------------------------

void CFMT_Wnd::SetFMTStyle(DWORD dwStyle,BOOL bRecalcCR) 
{
	ASSERT(::IsWindow(m_hWnd)); 
	
	if (bRecalcCR)
		::SendMessage(m_hWnd, FMTWND_SETSTYLE_MESS, (UINT)dwStyle,(long)1); 
	else ::SendMessage(m_hWnd, FMTWND_SETSTYLE_MESS, (UINT)dwStyle,(long)0); 
}

// -----------------------------------------------------------------------------------
//	Function:	GetFMTStyle
// -----------------------------------------------------------------------------------
//	Desc.	:	Ritorna lo stile FM
//
//	Return	:	-
//	Params	:	-
// -----------------------------------------------------------------------------------

DWORD CFMT_Wnd::GetFMTStyle() 
{
	ASSERT(::IsWindow(m_hWnd)); 

	DWORD dwRet=0;

	::SendMessage(m_hWnd, FMTWND_GETSTYLE_MESS, (UINT)(&dwRet),0); 

	return dwRet;
}

// -----------------------------------------------------------------------------------
//	Function:	SetBorderColor
// -----------------------------------------------------------------------------------
//	Desc.	:	Imposta il colore del bordo
//
//	Return	:	-
//	Params	:	dwStyle = stile
// -----------------------------------------------------------------------------------

void CFMT_Wnd::SetBorderColor(COLORREF col) 
{
	ASSERT(::IsWindow(m_hWnd)); 

	::SendMessage(m_hWnd, FMTWND_SETBORDERCOLOR_MESS, 0,(long)col); 
}

// -----------------------------------------------------------------------------------
//	Function:	GetBorderColor
// -----------------------------------------------------------------------------------
//	Desc.	:	Ritorna il colore del bordo
//
//	Return	:	-
//	Params	:	dwStyle = stile
// -----------------------------------------------------------------------------------

void CFMT_Wnd::GetBorderColor(COLORREF& col) 
{
	ASSERT(::IsWindow(m_hWnd)); 

	::SendMessage(m_hWnd, FMTWND_GETBORDERCOLOR_MESS, 0,(long)&col); 
}

// -----------------------------------------------------------------------------------
//	Function:	GetCRFromStyle
// -----------------------------------------------------------------------------------
//	Desc.	:	Ritorna il nuovo client rect in coordinate schermo dato uno stile
//
//	Return	:	nuovo CR con coordinate a schermo
//	Params	:	dwStyle = stile
// -----------------------------------------------------------------------------------

CRect CFMT_Wnd::GetCRFromStyle(DWORD dwStyle)
{
	CRect wr(0,0,0,0);
	GetWindowRect(&wr);

	switch (dwStyle & 0x000000FF)
	{
		case FMTWND_SIMPLE_BORDER:
		case FMTWND_SOFTRELIEF_BORDER:
		case FMTWND_SOFTSUNKEN_BORDER:

			wr.left+=1;
			wr.right-=1;
			wr.top+=1;
			wr.bottom-=1;
			break;

		case FMTWND_MEDIUMRELIEF_BORDER:

			wr.left+=1;
			wr.right-=2;
			wr.top+=1;
			wr.bottom-=2;
			break;

		case FMTWND_HARDSUNKEN_BORDER:
		case FMTWND_SOFTETCHED_BORDER:

			wr.left+=2;
			wr.right-=2;
			wr.top+=2;
			wr.bottom-=2;
			break;

		case FMTWND_HARDRELIEF_BORDER:

			wr.left+=2;
			wr.right-=3;
			wr.top+=2;
			wr.bottom-=3;
			break;

		case FMTWND_MEDIUMETCHED_BORDER:

			wr.left+=3;
			wr.right-=4;
			wr.top+=3;
			wr.bottom-=4;
			break;

		case FMTWND_HARDETCHED_BORDER:

			wr.left+=4;
			wr.right-=5;
			wr.top+=4;
			wr.bottom-=5;
			break;

		case FMTWND_SOFTRAISED_BORDER:
		
			wr.left+=4;
			wr.right-=5;
			wr.top+=4;
			wr.bottom-=5;
			break;

		case FMTWND_HARDRAISED_BORDER:

			wr.left+=7;
			wr.right-=7;
			wr.top+=7;
			wr.bottom-=7;
			break;

		case FMTWND_SOFTFRAME_BORDER:
			
			wr.left+=4;
			wr.right-=4;
			wr.top+=4;
			wr.bottom-=4;
			break;

		case FMTWND_SOFTCONVEX_BORDER:

			wr.left+=5;
			wr.right-=7;
			wr.top+=5;
			wr.bottom-=7;
			break;

		case FMTWND_HARDCONVEX_BORDER:

			wr.left+=6;
			wr.right-=7;
			wr.top+=6;
			wr.bottom-=7;
			break;

		case FMTWND_SHADED1_BORDER:

			wr.left+=1;
			wr.right-=3;
			wr.top+=1;
			wr.bottom-=3;
			break;

		case FMTWND_DOUBLE_BORDER:

			wr.left+=3;
			wr.right-=3;
			wr.top+=3;
			wr.bottom-=3;
			break;
	}

	return wr;
}

// -----------------------------------------------------------------------------------
//	Function:	SetClientRect
// -----------------------------------------------------------------------------------
//	Desc.	:	Imposta un nuovo client rect
//
//	Return	:	-
//	Params	:	pCR = nuovo client rect (coordinate a schermo)
// -----------------------------------------------------------------------------------

void CFMT_Wnd::SetClientRect(CRect *pCR)
{
	CRect wr,cr;
	GetWindowRect(&wr);

	m_MarginCR.left=pCR->left-wr.left;
	m_MarginCR.right=wr.right-pCR->right;
	m_MarginCR.top=pCR->top-wr.top;
	m_MarginCR.bottom=wr.bottom-pCR->bottom;

	SetWindowPos(NULL,0,0,0,0,
		SWP_NOZORDER|SWP_NOMOVE|SWP_NOREDRAW|SWP_NOSIZE|SWP_FRAMECHANGED);   
}

// -----------------------------------------------------------------------------------
//	Function:	RedrawFullWindow
// -----------------------------------------------------------------------------------
//	Desc.	:	Ridisegna tutta la finestra
//
//	Return	:	-
//	Params	:	dwStyle = stile
// -----------------------------------------------------------------------------------

void CFMT_Wnd::RedrawFullWindow() 
{
	ASSERT(::IsWindow(m_hWnd)); 

	::SendMessage(m_hWnd, FMTWND_REDRAWFULL_MESS, 0,0); 
}

// -----------------------------------------------------------------------------------
//	Function:	DrawSimpleBorder
// -----------------------------------------------------------------------------------
//	Desc.	:	Disegna il bordo di stile FMTWND_SIMPLE_BORDER
//
//	Return	:	-
//	Params	:	pDC = device context
// -----------------------------------------------------------------------------------

void CFMT_Wnd::DrawSimpleBorder(CDC* pDC)
{
	CRect wr,ncr;
	GetWindowRect(&wr);

	ncr.SetRect(0,0,wr.Width(),wr.Height());

	pDC->SelectObject(m_ppBorderPen[1]);
	
	pDC->MoveTo(0,0);
	pDC->LineTo(ncr.right-1,0);
	pDC->LineTo(ncr.right-1,ncr.bottom-1);
	pDC->MoveTo(0,0);
	pDC->LineTo(0,ncr.bottom-1);
	pDC->LineTo(ncr.right,ncr.bottom-1);

}

// -----------------------------------------------------------------------------------
//	Function:	DrawSoftReliefBorder
// -----------------------------------------------------------------------------------
//	Desc.	:	Disegna il bordo di stile FMTWND_SOFTRELIEF_BORDER
//
//	Return	:	-
//	Params	:	pDC = device context
// -----------------------------------------------------------------------------------

void CFMT_Wnd::DrawSoftReliefBorder(CDC* pDC)
{
	CRect wr,ncr;
	GetWindowRect(&wr);

	ncr.SetRect(0,0,wr.Width(),wr.Height());

	pDC->SelectObject(m_ppBorderPen[4]);
	pDC->MoveTo(0,ncr.bottom-1);
	pDC->LineTo(0,0);
	pDC->LineTo(ncr.right-1,0);

	pDC->SelectObject(m_ppBorderPen[2]);
	pDC->MoveTo(ncr.right-1,0);
	pDC->LineTo(ncr.right-1,ncr.bottom);
	pDC->MoveTo(1,ncr.bottom-1);
	pDC->LineTo(ncr.right-1,ncr.bottom-1);
}

// -----------------------------------------------------------------------------------
//	Function:	DrawMediumReliefBorder
// -----------------------------------------------------------------------------------
//	Desc.	:	Disegna il bordo di stile FMTWND_MEDIUMRELIEF_BORDER
//
//	Return	:	-
//	Params	:	pDC = device context
// -----------------------------------------------------------------------------------

void CFMT_Wnd::DrawMediumReliefBorder(CDC* pDC)
{
	CRect wr,ncr;
	GetWindowRect(&wr);

	ncr.SetRect(0,0,wr.Width(),wr.Height());

	pDC->SelectObject(m_ppBorderPen[4]);
	pDC->MoveTo(0,ncr.bottom-1);
	pDC->LineTo(0,0);
	pDC->LineTo(ncr.right-1,0);

	pDC->SelectObject(m_ppBorderPen[2]);
	pDC->MoveTo(ncr.right-2,ncr.top+1);
	pDC->LineTo(ncr.right-2,ncr.bottom-2);
	pDC->LineTo(0,ncr.bottom-2);

	pDC->SelectObject(m_ppBorderPen[1]);
	pDC->MoveTo(ncr.right-1,0);
	pDC->LineTo(ncr.right-1,ncr.bottom);
	pDC->MoveTo(0,ncr.bottom-1);
	pDC->LineTo(ncr.right-1,ncr.bottom-1);
}

// -----------------------------------------------------------------------------------
//	Function:	DrawHardReliefBorder
// -----------------------------------------------------------------------------------
//	Desc.	:	Disegna il bordo di stile FMTWND_HARDRELIEF_BORDER
//
//	Return	:	-
//	Params	:	pDC = device context
// -----------------------------------------------------------------------------------

void CFMT_Wnd::DrawHardReliefBorder(CDC* pDC)
{
	CRect wr,ncr;
	GetWindowRect(&wr);

	ncr.SetRect(0,0,wr.Width(),wr.Height());

	pDC->SelectObject(m_ppBorderPen[4]);
	pDC->MoveTo(0,ncr.bottom-1);
	pDC->LineTo(0,0);
	pDC->LineTo(ncr.right-1,0);

	pDC->MoveTo(1,ncr.bottom-2);
	pDC->LineTo(1,1);
	pDC->LineTo(ncr.right-2,1);

	pDC->SelectObject(m_ppBorderPen[1]);
	pDC->MoveTo(ncr.right-2,ncr.top+1);
	pDC->LineTo(ncr.right-2,ncr.bottom-2);
	pDC->LineTo(0,ncr.bottom-2);

	pDC->MoveTo(ncr.right-1,0);
	pDC->LineTo(ncr.right-1,ncr.bottom);
	pDC->MoveTo(0,ncr.bottom-1);
	pDC->LineTo(ncr.right-1,ncr.bottom-1);

	pDC->SelectObject(m_ppBorderPen[2]);
	pDC->MoveTo(ncr.right-3,2);
	pDC->LineTo(ncr.right-3,ncr.bottom-3);
	pDC->LineTo(1,ncr.bottom-3);
}


// -----------------------------------------------------------------------------------
//	Function:	DrawSoftSunkenBorder
// -----------------------------------------------------------------------------------
//	Desc.	:	Disegna il bordo di stile FMTWND_SOFTSUNKEN_BORDER
//
//	Return	:	-
//	Params	:	pDC = device context
// -----------------------------------------------------------------------------------

void CFMT_Wnd::DrawSoftSunkenBorder(CDC* pDC)
{
	CRect wr,ncr;
	GetWindowRect(&wr);

	ncr.SetRect(0,0,wr.Width(),wr.Height());

	pDC->SelectObject(m_ppBorderPen[2]);
	pDC->MoveTo(0,ncr.bottom-1);
	pDC->LineTo(0,0);
	pDC->LineTo(ncr.right-1,0);

	pDC->SelectObject(m_ppBorderPen[4]);
	pDC->MoveTo(ncr.right-1,0);
	pDC->LineTo(ncr.right-1,ncr.bottom);
	pDC->MoveTo(1,ncr.bottom-1);
	pDC->LineTo(ncr.right-1,ncr.bottom-1);
}

// -----------------------------------------------------------------------------------
//	Function:	DrawMediumSunkenBorder
// -----------------------------------------------------------------------------------
//	Desc.	:	Disegna il bordo di stile FMTWND_MEDIUMSUNKEN_BORDER
//
//	Return	:	-
//	Params	:	pDC = device context
// -----------------------------------------------------------------------------------

void CFMT_Wnd::DrawMediumSunkenBorder(CDC* pDC)
{
	CRect wr,ncr;
	GetWindowRect(&wr);

	ncr.SetRect(0,0,wr.Width(),wr.Height());

	pDC->SelectObject(m_ppBorderPen[2]);
	pDC->MoveTo(0,0);
	pDC->LineTo(ncr.right-1,0);
	pDC->MoveTo(0,0);
	pDC->LineTo(0,ncr.bottom-1);
	
	pDC->SelectObject(m_ppBorderPen[1]);
	pDC->MoveTo(1,1);
	pDC->LineTo(ncr.right-2,1);
	pDC->MoveTo(1,1);
	pDC->LineTo(1,ncr.bottom-2);

	pDC->SelectObject(m_ppBorderPen[4]);
	pDC->MoveTo(0,ncr.bottom-1);
	pDC->LineTo(ncr.right,ncr.bottom-1);
	pDC->MoveTo(ncr.right-1,0);
	pDC->LineTo(ncr.right-1,ncr.bottom-1);
	
	pDC->SelectObject(m_ppBorderPen[3]);
	pDC->MoveTo(2,ncr.bottom-2);
	pDC->LineTo(ncr.right-2,ncr.bottom-2);
	pDC->MoveTo(ncr.right-2,1);
	pDC->LineTo(ncr.right-2,ncr.bottom-2);
}

// -----------------------------------------------------------------------------------
//	Function:	DrawHardSunkenBorder
// -----------------------------------------------------------------------------------
//	Desc.	:	Disegna il bordo di stile FMTWND_HARDSUNKEN_BORDER
//
//	Return	:	-
//	Params	:	pDC = device context
// -----------------------------------------------------------------------------------

void CFMT_Wnd::DrawHardSunkenBorder(CDC* pDC)
{
	CRect wr,ncr;
	GetWindowRect(&wr);

	ncr.SetRect(0,0,wr.Width(),wr.Height());

	pDC->SelectObject(m_ppBorderPen[2]);
	pDC->MoveTo(0,0);
	pDC->LineTo(0,ncr.bottom-1);
	pDC->MoveTo(0,0);
	pDC->LineTo(ncr.right-1,0);

	pDC->MoveTo(1,1);
	pDC->LineTo(1,ncr.bottom-2);
	pDC->MoveTo(1,1);
	pDC->LineTo(ncr.right-2,1);

	pDC->SelectObject(m_ppBorderPen[4]);
	pDC->MoveTo(0,ncr.bottom-1);
	pDC->LineTo(ncr.right,ncr.bottom-1);
	pDC->MoveTo(ncr.right-1,0);
	pDC->LineTo(ncr.right-1,ncr.bottom-1);

	pDC->MoveTo(1,ncr.bottom-2);
	pDC->LineTo(ncr.right-1,ncr.bottom-2);
	pDC->MoveTo(ncr.right-2,1);
	pDC->LineTo(ncr.right-2,ncr.bottom-2);
}

// -----------------------------------------------------------------------------------
//	Function:	DrawSoftEtchedBorder
// -----------------------------------------------------------------------------------
//	Desc.	:	Disegna il bordo di stile FMTWND_SOFTETCHED_BORDER
//
//	Return	:	-
//	Params	:	pDC = device context
// -----------------------------------------------------------------------------------

void CFMT_Wnd::DrawSoftEtchedBorder(CDC* pDC)
{
	CRect wr,ncr;
	GetWindowRect(&wr);

	ncr.SetRect(0,0,wr.Width(),wr.Height());

	pDC->SelectObject(m_ppBorderPen[2]);
	pDC->MoveTo(0,0);
	pDC->LineTo(0,ncr.bottom-1);
	pDC->MoveTo(0,0);
	pDC->LineTo(ncr.right-1,0);

	pDC->MoveTo(0,ncr.bottom-2);
	pDC->LineTo(ncr.right-1,ncr.bottom-2);
	pDC->MoveTo(ncr.right-2,0);
	pDC->LineTo(ncr.right-2,ncr.bottom-2);

	pDC->SelectObject(m_ppBorderPen[4]);
	pDC->MoveTo(0,ncr.bottom-1);
	pDC->LineTo(ncr.right,ncr.bottom-1);
	pDC->MoveTo(ncr.right-1,0);
	pDC->LineTo(ncr.right-1,ncr.bottom-1);

	pDC->MoveTo(1,1);
	pDC->LineTo(1,ncr.bottom-2);
	pDC->MoveTo(1,1);
	pDC->LineTo(ncr.right-2,1);
}

// -----------------------------------------------------------------------------------
//	Function:	DrawMediumEtchedBorder
// -----------------------------------------------------------------------------------
//	Desc.	:	Disegna il bordo di stile FMTWND_MEDIUMETCHED_BORDER
//
//	Return	:	-
//	Params	:	pDC = device context
// -----------------------------------------------------------------------------------

void CFMT_Wnd::DrawMediumEtchedBorder(CDC* pDC)
{
	CRect wr,ncr;
	GetWindowRect(&wr);

	ncr.SetRect(0,0,wr.Width(),wr.Height());

	pDC->SelectObject(m_ppBorderPen[2]);
	pDC->MoveTo(0,ncr.bottom-1);
	pDC->LineTo(0,0);
	pDC->LineTo(ncr.right-1,0);

	pDC->SelectObject(m_ppBorderPen[4]);
	pDC->MoveTo(ncr.right-1,0);
	pDC->LineTo(ncr.right-1,ncr.bottom);
	pDC->MoveTo(1,ncr.bottom-1);
	pDC->LineTo(ncr.right-1,ncr.bottom-1);

	pDC->SelectObject(m_ppBorderPen[1]);
	pDC->MoveTo(1,ncr.bottom-3);
	pDC->LineTo(1,1);
	pDC->LineTo(ncr.right-3,1);
	pDC->LineTo(ncr.right-3,ncr.bottom-3);
	pDC->LineTo(1,ncr.bottom-3);

	pDC->SelectObject(m_ppBorderPen[0]);
	pDC->MoveTo(ncr.right-2,ncr.top+1);
	pDC->LineTo(ncr.right-2,ncr.bottom-2);
	pDC->LineTo(0,ncr.bottom-2);

	pDC->SelectObject(m_ppBorderPen[4]);
	pDC->MoveTo(2,ncr.bottom-4);
	pDC->LineTo(2,2);
	pDC->LineTo(ncr.right-3,2);

	pDC->SelectObject(m_ppBorderPen[2]);
	pDC->MoveTo(ncr.right-4,3);
	pDC->LineTo(ncr.right-4,ncr.bottom-4);
	pDC->MoveTo(3,ncr.bottom-4);
	pDC->LineTo(ncr.right-3,ncr.bottom-4);
}

// -----------------------------------------------------------------------------------
//	Function:	DrawHardEtchedBorder
// -----------------------------------------------------------------------------------
//	Desc.	:	Disegna il bordo di stile FMTWND_HARDETCHED_BORDER
//
//	Return	:	-
//	Params	:	pDC = device context
// -----------------------------------------------------------------------------------

void CFMT_Wnd::DrawHardEtchedBorder(CDC* pDC)
{
	CRect wr,ncr;
	GetWindowRect(&wr);

	ncr.SetRect(0,0,wr.Width(),wr.Height());

	pDC->SelectObject(m_ppBorderPen[2]);
	pDC->MoveTo(0,0);
	pDC->LineTo(0,ncr.bottom-1);
	pDC->MoveTo(0,0);
	pDC->LineTo(ncr.right-1,0);

	pDC->MoveTo(1,1);
	pDC->LineTo(1,ncr.bottom-2);
	pDC->MoveTo(1,1);
	pDC->LineTo(ncr.right-2,1);

	pDC->SelectObject(m_ppBorderPen[4]);
	pDC->MoveTo(0,ncr.bottom-1);
	pDC->LineTo(ncr.right,ncr.bottom-1);
	pDC->MoveTo(ncr.right-1,0);
	pDC->LineTo(ncr.right-1,ncr.bottom-1);

	pDC->MoveTo(1,ncr.bottom-2);
	pDC->LineTo(ncr.right-1,ncr.bottom-2);
	pDC->MoveTo(ncr.right-2,1);
	pDC->LineTo(ncr.right-2,ncr.bottom-2);

	pDC->SelectObject(m_ppBorderPen[1]);

	pDC->MoveTo(2,2);
	pDC->LineTo(2,ncr.bottom-3);
	pDC->MoveTo(2,2);
	pDC->LineTo(ncr.right-3,2);
	
	pDC->MoveTo(2,ncr.bottom-4);
	pDC->LineTo(ncr.right-4,ncr.bottom-4);
	pDC->MoveTo(ncr.right-4,2);
	pDC->LineTo(ncr.right-4,ncr.bottom-3);

	pDC->SelectObject(m_ppBorderPen[2]);
	pDC->MoveTo(4,ncr.bottom-5);
	pDC->LineTo(ncr.right-4,ncr.bottom-5);
	pDC->MoveTo(ncr.right-5,4);
	pDC->LineTo(ncr.right-5,ncr.bottom-5);

	pDC->SelectObject(m_ppBorderPen[4]);
	pDC->MoveTo(3,3);
	pDC->LineTo(3,ncr.bottom-4);
	pDC->MoveTo(3,3);
	pDC->LineTo(ncr.right-4,3);

	pDC->SelectObject(m_ppBorderPen[0]);
	pDC->MoveTo(2,ncr.bottom-3);
	pDC->LineTo(ncr.right-3,ncr.bottom-3);
	pDC->MoveTo(ncr.right-3,2);
	pDC->LineTo(ncr.right-3,ncr.bottom-2);
}

// -----------------------------------------------------------------------------------
//	Function:	DrawSoftRaisedBorder
// -----------------------------------------------------------------------------------
//	Desc.	:	Disegna il bordo di stile FMTWND_SOFTRAISED_BORDER
//
//	Return	:	-
//	Params	:	pDC = device context
// -----------------------------------------------------------------------------------

void CFMT_Wnd::DrawSoftRaisedBorder(CDC* pDC)
{
	CRect wr,ncr;
	GetWindowRect(&wr);

	ncr.SetRect(0,0,wr.Width(),wr.Height());

	pDC->SelectObject(m_ppBorderPen[0]);
	pDC->MoveTo(0,ncr.bottom-1);
	pDC->LineTo(0,0);
	pDC->LineTo(ncr.right-1,0);

	pDC->SelectObject(m_ppBorderPen[1]);
	pDC->MoveTo(ncr.right-1,0);
	pDC->LineTo(ncr.right-1,ncr.bottom);
	pDC->MoveTo(1,ncr.bottom-1);
	pDC->LineTo(ncr.right-1,ncr.bottom-1);

	pDC->SelectObject(m_ppBorderPen[4]);
	pDC->MoveTo(1,ncr.bottom-2);
	pDC->LineTo(1,1);
	pDC->LineTo(ncr.right-2,1);

	pDC->SelectObject(m_ppBorderPen[2]);
	pDC->MoveTo(ncr.right-2,1);
	pDC->LineTo(ncr.right-2,ncr.bottom-1);
	pDC->MoveTo(2,ncr.bottom-2);
	pDC->LineTo(ncr.right-2,ncr.bottom-2);

	pDC->SelectObject(m_ppBorderPen[0]);
	pDC->MoveTo(2,ncr.bottom-3);
	pDC->LineTo(2,2);
	pDC->LineTo(ncr.right-3,2);
	pDC->MoveTo(ncr.right-3,2);
	pDC->LineTo(ncr.right-3,ncr.bottom-2);
	pDC->MoveTo(3,ncr.bottom-3);
	pDC->LineTo(ncr.right-3,ncr.bottom-3);

	pDC->SelectObject(m_ppBorderPen[4]);
	pDC->MoveTo(3,ncr.bottom-4);
	pDC->LineTo(3,3);
	pDC->LineTo(ncr.right-4,3);

	pDC->SelectObject(m_ppBorderPen[1]);
	pDC->MoveTo(ncr.right-4,3);
	pDC->LineTo(ncr.right-4,ncr.bottom-3);
	pDC->MoveTo(4,ncr.bottom-4);
	pDC->LineTo(ncr.right-4,ncr.bottom-4);

	pDC->SelectObject(m_ppBorderPen[2]);
	pDC->MoveTo(ncr.right-5,4);
	pDC->LineTo(ncr.right-5,ncr.bottom-4);
	pDC->MoveTo(4,ncr.bottom-5);
	pDC->LineTo(ncr.right-5,ncr.bottom-5);
}

// -----------------------------------------------------------------------------------
//	Function:	DrawHardRaisedBorder
// -----------------------------------------------------------------------------------
//	Desc.	:	Disegna il bordo di stile FMTWND_HARDRAISED_BORDER
//
//	Return	:	-
//	Params	:	pDC = device context
// -----------------------------------------------------------------------------------

void CFMT_Wnd::DrawHardRaisedBorder(CDC* pDC)
{
	CRect wr,ncr;
	GetWindowRect(&wr);

	ncr.SetRect(0,0,wr.Width(),wr.Height());

	pDC->SelectObject(m_ppBorderPen[0]);
	pDC->MoveTo(0,ncr.bottom-2);
	pDC->LineTo(0,0);
	pDC->LineTo(ncr.right-1,0);

	pDC->SelectObject(m_ppBorderPen[4]);
	pDC->MoveTo(1,ncr.bottom-3);
	pDC->LineTo(1,1);
	pDC->LineTo(ncr.right-2,1);

	pDC->MoveTo(2,ncr.bottom-4);
	pDC->LineTo(2,2);
	pDC->LineTo(ncr.right-3,2);

	pDC->SelectObject(m_ppBorderPen[1]);
	pDC->MoveTo(ncr.right-1,-1);
	pDC->LineTo(ncr.right-1,ncr.bottom-1);
	pDC->LineTo(-1,ncr.bottom-1);

	pDC->MoveTo(ncr.right-2,1);
	pDC->LineTo(ncr.right-2,ncr.bottom-2);
	pDC->MoveTo(1,ncr.bottom-2);
	pDC->LineTo(ncr.right-1,ncr.bottom-2);
	pDC->SelectObject(m_ppBorderPen[2]);
	pDC->MoveTo(ncr.right-3,2);
	pDC->LineTo(ncr.right-3,ncr.bottom-3);
	pDC->LineTo(1,ncr.bottom-3);


	pDC->SelectObject(m_ppBorderPen[0]);
	pDC->MoveTo(3,ncr.bottom-4);
	pDC->LineTo(3,3);
	pDC->LineTo(ncr.right-4,3);
	pDC->MoveTo(ncr.right-4,3);
	pDC->LineTo(ncr.right-4,ncr.bottom-3);
	pDC->MoveTo(4,ncr.bottom-4);
	pDC->LineTo(ncr.right-4,ncr.bottom-4);

	pDC->MoveTo(4,ncr.bottom-5);
	pDC->LineTo(4,4);
	pDC->LineTo(ncr.right-5,4);
	pDC->MoveTo(ncr.right-5,4);
	pDC->LineTo(ncr.right-5,ncr.bottom-4);
	pDC->MoveTo(5,ncr.bottom-5);
	pDC->LineTo(ncr.right-5,ncr.bottom-5);

	pDC->SelectObject(m_ppBorderPen[4]);
	pDC->MoveTo(5,ncr.bottom-6);
	pDC->LineTo(5,5);
	pDC->LineTo(ncr.right-5,5);
	pDC->MoveTo(6,ncr.bottom-7);
	pDC->LineTo(6,6);
	pDC->LineTo(ncr.right-6,6);

	pDC->SelectObject(m_ppBorderPen[1]);
	pDC->MoveTo(ncr.right-6,6);
	pDC->LineTo(ncr.right-6,ncr.bottom-6);
	pDC->LineTo(5,ncr.bottom-6);
	pDC->MoveTo(ncr.right-7,7);
	pDC->LineTo(ncr.right-7,ncr.bottom-7);
	pDC->LineTo(6,ncr.bottom-7);

}

// -----------------------------------------------------------------------------------
//	Function:	DrawSoftFrameBorder
// -----------------------------------------------------------------------------------
//	Desc.	:	Disegna il bordo di stile FMTWND_SOFTFRAME_BORDER
//
//	Return	:	-
//	Params	:	pDC = device context
// -----------------------------------------------------------------------------------

void CFMT_Wnd::DrawSoftFrameBorder(CDC* pDC)
{
	CRect wr,ncr;
	GetWindowRect(&wr);

	ncr.SetRect(0,0,wr.Width(),wr.Height());

	pDC->SelectObject(m_ppBorderPen[0]);
	pDC->MoveTo(0,ncr.bottom-1);
	pDC->LineTo(0,0);
	pDC->LineTo(ncr.right-1,0);

	pDC->SelectObject(m_ppBorderPen[1]);
	pDC->MoveTo(ncr.right-1,0);
	pDC->LineTo(ncr.right-1,ncr.bottom);
	pDC->MoveTo(1,ncr.bottom-1);
	pDC->LineTo(ncr.right-1,ncr.bottom-1);

	pDC->SelectObject(m_ppBorderPen[4]);
	pDC->MoveTo(1,ncr.bottom-2);
	pDC->LineTo(1,1);
	pDC->LineTo(ncr.right-2,1);

	pDC->SelectObject(m_ppBorderPen[2]);
	pDC->MoveTo(ncr.right-2,1);
	pDC->LineTo(ncr.right-2,ncr.bottom-1);
	pDC->MoveTo(2,ncr.bottom-2);
	pDC->LineTo(ncr.right-2,ncr.bottom-2);

	pDC->SelectObject(m_ppBorderPen[0]);
	pDC->MoveTo(2,ncr.bottom-3);
	pDC->LineTo(2,2);
	pDC->LineTo(ncr.right-3,2);
	pDC->MoveTo(ncr.right-3,2);
	pDC->LineTo(ncr.right-3,ncr.bottom-2);
	pDC->MoveTo(3,ncr.bottom-3);
	pDC->LineTo(ncr.right-3,ncr.bottom-3);

	pDC->SelectObject(m_ppBorderPen[2]);
	pDC->MoveTo(3,ncr.bottom-4);
	pDC->LineTo(3,3);
	pDC->LineTo(ncr.right-4,3);

	pDC->SelectObject(m_ppBorderPen[4]);
	pDC->MoveTo(ncr.right-4,3);
	pDC->LineTo(ncr.right-4,ncr.bottom-3);
	pDC->MoveTo(4,ncr.bottom-4);
	pDC->LineTo(ncr.right-4,ncr.bottom-4);

}

// -----------------------------------------------------------------------------------
//	Function:	DrawHardFrameBorder
// -----------------------------------------------------------------------------------
//	Desc.	:	Disegna il bordo di stile FMTWND_HARDFRAME_BORDER
//
//	Return	:	-
//	Params	:	pDC = device context
// -----------------------------------------------------------------------------------

void CFMT_Wnd::DrawHardFrameBorder(CDC* pDC)
{
	ASSERT(0);
}

// -----------------------------------------------------------------------------------
//	Function:	DrawSoftConvexBorder
// -----------------------------------------------------------------------------------
//	Desc.	:	Disegna il bordo di stile FMTWND_SOFTCONVEX_BORDER
//
//	Return	:	-
//	Params	:	pDC = device context
// -----------------------------------------------------------------------------------

void CFMT_Wnd::DrawSoftConvexBorder(CDC* pDC)
{
	CRect wr,ncr;
	GetWindowRect(&wr);

	ncr.SetRect(0,0,wr.Width(),wr.Height());

	pDC->SelectObject(m_ppBorderPen[0]);
	pDC->MoveTo(0,ncr.bottom-1);
	pDC->LineTo(0,0);
	pDC->LineTo(ncr.right-1,0);

	pDC->SelectObject(m_ppBorderPen[1]);
	pDC->MoveTo(ncr.right-1,0);
	pDC->LineTo(ncr.right-1,ncr.bottom);
	pDC->MoveTo(1,ncr.bottom-1);
	pDC->LineTo(ncr.right-1,ncr.bottom-1);

	pDC->SelectObject(m_ppBorderPen[4]);
	pDC->MoveTo(1,ncr.bottom-2);
	pDC->LineTo(1,1);
	pDC->LineTo(ncr.right-2,1);

	pDC->SelectObject(m_ppBorderPen[2]);
	pDC->MoveTo(ncr.right-2,1);
	pDC->LineTo(ncr.right-2,ncr.bottom-1);
	pDC->MoveTo(2,ncr.bottom-2);
	pDC->LineTo(ncr.right-2,ncr.bottom-2);

	pDC->SelectObject(m_ppBorderPen[0]);
	pDC->MoveTo(2,ncr.bottom-3);
	pDC->LineTo(2,2);
	pDC->LineTo(ncr.right-3,2);
	pDC->MoveTo(ncr.right-3,2);
	pDC->LineTo(ncr.right-3,ncr.bottom-2);
	pDC->MoveTo(3,ncr.bottom-3);
	pDC->LineTo(ncr.right-3,ncr.bottom-3);

	pDC->SelectObject(m_ppBorderPen[2]);
	pDC->MoveTo(3,ncr.bottom-4);
	pDC->LineTo(3,3);
	pDC->LineTo(ncr.right-4,3);

	pDC->SelectObject(m_ppBorderPen[4]);
	pDC->MoveTo(ncr.right-4,3);
	pDC->LineTo(ncr.right-4,ncr.bottom-3);
	pDC->MoveTo(4,ncr.bottom-4);
	pDC->LineTo(ncr.right-4,ncr.bottom-4);

	pDC->SelectObject(m_ppBorderPen[1]);
	pDC->MoveTo(4,ncr.bottom-6);
	pDC->LineTo(4,4);
	pDC->LineTo(ncr.right-5,4);
	pDC->MoveTo(ncr.right-6,5);
	pDC->LineTo(ncr.right-6,ncr.bottom-6);
	pDC->MoveTo(5,ncr.bottom-6);
	pDC->LineTo(ncr.right-5,ncr.bottom-6);

	pDC->SelectObject(m_ppBorderPen[4]);
	pDC->MoveTo(5,ncr.bottom-7);
	pDC->LineTo(5,5);
	pDC->LineTo(ncr.right-6,5);

	pDC->SelectObject(m_ppBorderPen[2]);
	pDC->MoveTo(ncr.right-7,6);
	pDC->LineTo(ncr.right-7,ncr.bottom-7);
	pDC->MoveTo(6,ncr.bottom-7);
	pDC->LineTo(ncr.right-6,ncr.bottom-7);

	pDC->SelectObject(m_ppBorderPen[0]);
	pDC->MoveTo(ncr.right-5,4);
	pDC->LineTo(ncr.right-5,ncr.bottom-5);
	pDC->MoveTo(4,ncr.bottom-5);
	pDC->LineTo(ncr.right-4,ncr.bottom-5);
}

// -----------------------------------------------------------------------------------
//	Function:	DrawHardConvexBorder
// -----------------------------------------------------------------------------------
//	Desc.	:	Disegna il bordo di stile FMTWND_HARDCONVEX_BORDER
//
//	Return	:	-
//	Params	:	pDC = device context
// -----------------------------------------------------------------------------------

void CFMT_Wnd::DrawHardConvexBorder(CDC* pDC)
{
	ASSERT(0);
	CRect wr,ncr;
	GetWindowRect(&wr);

	ncr.SetRect(0,0,wr.Width(),wr.Height());
}

// -----------------------------------------------------------------------------------
//	Function:	DrawShaded1Border
// -----------------------------------------------------------------------------------
//	Desc.	:	Disegna il bordo di stile FMTWND_SHADED1_BORDER
//
//	Return	:	-
//	Params	:	pDC = device context
// -----------------------------------------------------------------------------------

void CFMT_Wnd::DrawShaded1Border(CDC* pDC)
{
	CRect wr,ncr;
	GetWindowRect(&wr);

	ncr.SetRect(0,0,wr.Width(),wr.Height());

	pDC->SelectObject(m_ppBorderPen[1]);
	pDC->MoveTo(0,0);
	pDC->LineTo(ncr.right-3,0);
	pDC->LineTo(ncr.right-3,ncr.bottom-3);
	pDC->LineTo(0,ncr.bottom-3);
	pDC->LineTo(0,0);

	pDC->SelectObject(m_ppBorderPen[2]);
	pDC->MoveTo(2,ncr.bottom-2);
	pDC->LineTo(ncr.right-1,ncr.bottom-2);
	pDC->MoveTo(2,ncr.bottom-1);
	pDC->LineTo(ncr.right-1,ncr.bottom-1);

	pDC->MoveTo(ncr.right-2,ncr.top+2);
	pDC->LineTo(ncr.right-2,ncr.bottom-1);
	pDC->MoveTo(ncr.right-1,ncr.top+2);
	pDC->LineTo(ncr.right-1,ncr.bottom-1);
}

// -----------------------------------------------------------------------------------
//	Function:	DrawDoubleBorder
// -----------------------------------------------------------------------------------
//	Desc.	:	Disegna il bordo di stile FMTWND_DOUBLE_BORDER
//
//	Return	:	-
//	Params	:	pDC = device context
// -----------------------------------------------------------------------------------

void CFMT_Wnd::DrawDoubleBorder(CDC* pDC)
{
	CRect wr,ncr;
	GetWindowRect(&wr);

	ncr.SetRect(0,0,wr.Width(),wr.Height());

	pDC->SelectObject(m_ppBorderPen[1]);
	pDC->MoveTo(0,0);
	pDC->LineTo(ncr.right-1,0);
	pDC->LineTo(ncr.right-1,ncr.bottom-1);
	pDC->LineTo(0,ncr.bottom-1);
	pDC->LineTo(0,0);

	pDC->SelectObject(m_ppBorderPen[4]);
	pDC->MoveTo(1,1);
	pDC->LineTo(ncr.right-2,1);
	pDC->LineTo(ncr.right-2,ncr.bottom-2);
	pDC->LineTo(1,ncr.bottom-2);
	pDC->LineTo(1,1);

	pDC->SelectObject(m_ppBorderPen[1]);
	pDC->MoveTo(2,2);
	pDC->LineTo(ncr.right-3,2);
	pDC->LineTo(ncr.right-3,ncr.bottom-3);
	pDC->LineTo(2,ncr.bottom-3);
	pDC->LineTo(2,2);
}

// -----------------------------------------------------------------------------------
//	Function:	DrawNcArea
// -----------------------------------------------------------------------------------
//	Desc.	:	Disegna l'area non-client
//
//	Return	:	-
//	Params	:	pDC = device context
// -----------------------------------------------------------------------------------

void CFMT_Wnd::DrawNcArea(CDC* pDC)
{
	CreatePens();

	switch (m_dwStyle & 0x000000FF)
	{
	case FMTWND_SIMPLE_BORDER:

		DrawSimpleBorder(pDC);
		break;

	case FMTWND_SOFTRELIEF_BORDER:

		DrawSoftReliefBorder(pDC);
		break;

	case FMTWND_MEDIUMRELIEF_BORDER:

		DrawMediumReliefBorder(pDC);
		break;

	case FMTWND_HARDRELIEF_BORDER:

		DrawHardReliefBorder(pDC);
		break;

	case FMTWND_SOFTSUNKEN_BORDER:

		DrawSoftSunkenBorder(pDC);
		break;

	case FMTWND_MEDIUMSUNKEN_BORDER:

		DrawMediumSunkenBorder(pDC);
		break;

	case FMTWND_HARDSUNKEN_BORDER:

		DrawHardSunkenBorder(pDC);
		break;

	case FMTWND_SOFTETCHED_BORDER:

		DrawSoftEtchedBorder(pDC);
		break;

	case FMTWND_MEDIUMETCHED_BORDER:

		DrawMediumEtchedBorder(pDC);
		break;

	case FMTWND_HARDETCHED_BORDER:

		DrawHardEtchedBorder(pDC);
		break;

	case FMTWND_SOFTRAISED_BORDER:

		DrawSoftRaisedBorder(pDC);
		break;

	case FMTWND_HARDRAISED_BORDER:

		DrawHardRaisedBorder(pDC);
		break;

	case FMTWND_SOFTFRAME_BORDER:

		DrawSoftFrameBorder(pDC);
		break;

	case FMTWND_HARDFRAME_BORDER:

		DrawHardFrameBorder(pDC);
		break;

	case FMTWND_SOFTCONVEX_BORDER:

		DrawSoftConvexBorder(pDC);
		break;

	case FMTWND_HARDCONVEX_BORDER:

		DrawHardConvexBorder(pDC);
		break;

	case FMTWND_SHADED1_BORDER:

		DrawShaded1Border(pDC);
		break;

	case FMTWND_DOUBLE_BORDER:

		DrawDoubleBorder(pDC);
		break;
	}

	DeletePens();
}

// -----------------------------------------------------------------------------------
//	Function:	CreatePens
// -----------------------------------------------------------------------------------
//	Desc.	:	Crea le penne per il disegno
//
//	Return	:	-
//	Params	:	-
// -----------------------------------------------------------------------------------

void CFMT_Wnd::CreatePens() 
{
	for (DWORD i=0;i<5;i++)
	{
		m_ppBorderPen[i]=new CPen();
	}

	t_FMT_Uint8 btH,btL,btS;
	CFMT_Color col;

	m_colBorder.GetHLS(btH, btL, btS);

	// Main Border color
	m_ppBorderPen[0]->CreatePen(PS_SOLID,1,m_colBorder);

	// Hard dark color
	
	if (btL>120)
		col.SetHLS(btH,60,min(btS,70));
	else if (btL>60)
		col.SetHLS(btH,btL-60,min(btS,70));
	else col.SetHLS(btH,0,min(btS,70));

	m_ppBorderPen[1]->CreatePen(PS_SOLID,1,col);

	// Soft dark color

	if (btL>168)
		col.SetHLS(btH,128,min(btS,70));
	else if (btL>40)
		col.SetHLS(btH,btL-40,min(btS,70));
	else col.SetHLS(btH,0,min(btS,70)); 

	m_ppBorderPen[2]->CreatePen(PS_SOLID,1,col);

	// Soft bright color
	if (btL<170)
		col.SetHLS(btH,200,btS);
	else col.SetHLS(btH,btL,btS); 

	m_ppBorderPen[3]->CreatePen(PS_SOLID,1,col);

	// Hard bright color
	if (btL<150)
		col.SetHLS(btH,180,btS);
	else if (btL<210)
		col.SetHLS(btH,btL+30,btS);
	else col.SetHLS(btH,240,btS); 

	m_ppBorderPen[4]->CreatePen(PS_SOLID,1,col);
}

// -----------------------------------------------------------------------------------
//	Function:	DeletePens
// -----------------------------------------------------------------------------------
//	Desc.	:	Distrugge le penne per il disegno
//
//	Return	:	-
//	Params	:	-
// -----------------------------------------------------------------------------------

void CFMT_Wnd::DeletePens() 
{
	for (DWORD i=0;i<5;i++)
	{
		if (m_ppBorderPen[i]!=NULL)
		{
			delete m_ppBorderPen[i];
			m_ppBorderPen[i]=NULL;
		}
	}
}

// -----------------------------------------------------------------------------------
//	Function:	InsertFont
// -----------------------------------------------------------------------------------
//	Desc.	:	Inserisce un font nella lista, con creazione
//
//	Return	:	Puntatore al nuovo font
//	Params	:	dwIdx = indice del font da inserire
//				pFont = puntatore al font da inserire
// -----------------------------------------------------------------------------------

void CFMT_Wnd::InsertFont(DWORD dwIdx,CFont *pFont)
{
	ASSERT(::IsWindow(m_hWnd)); 
	
	::SendMessage(m_hWnd, FMTWND_ADDFONT_MESS, dwIdx, (LPARAM)(pFont)); 
}

// -----------------------------------------------------------------------------------
//	Function:	AttachFont
// -----------------------------------------------------------------------------------
//	Desc.	:	Inserisce un font nella lista senza creazione
//
//	Return	:	pFont
//	Params	:	dwIdx = indice del font da inserire
//				pFont = puntatore al font da inserire
// -----------------------------------------------------------------------------------

void CFMT_Wnd::AttachFont(DWORD dwIdx,CFont *pFont)
{
	ASSERT(::IsWindow(m_hWnd)); 
	
	::SendMessage(m_hWnd, FMTWND_ATTACHFONT_MESS, dwIdx, (LPARAM)(pFont)); 
}

// -----------------------------------------------------------------------------------
//	Function:	DeleteFont
// -----------------------------------------------------------------------------------
//	Desc.	:	Cancella un font dalla lista
//
//	Return	:	font cancellato
//	Params	:	dwIdx = indice del font da inserire
//				pFont = puntatore al font da inserire
// -----------------------------------------------------------------------------------

void CFMT_Wnd::DeleteFont(DWORD dwIdx)
{
	ASSERT(::IsWindow(m_hWnd)); 
	
	::SendMessage(m_hWnd, FMTWND_DELETEFONT_MESS, dwIdx, 0); 
}

// -----------------------------------------------------------------------------------
//	Function:	GetNumFonts
// -----------------------------------------------------------------------------------
//	Desc.	:	Ritorna il numero di fonts della finestra
//
//	Return	:	numero di fonts
//	Params	:	-
// -----------------------------------------------------------------------------------

DWORD CFMT_Wnd::GetNumFonts()
{
	ASSERT(::IsWindow(m_hWnd)); 
	
	DWORD dwRet=0;

	::SendMessage(m_hWnd, FMTWND_GETNUMFONTS_MESS, 0, (long)&dwRet); 

	return dwRet;
}

// -----------------------------------------------------------------------------------
//	Function:	GetFont
// -----------------------------------------------------------------------------------
//	Desc.	:	Ritorna il font di indice dwIdx
//
//	Return	:	font
//	Params	:	-
// -----------------------------------------------------------------------------------

CFont* CFMT_Wnd::GetFont(DWORD dwIdx)		
{	
	if (dwIdx<!m_FontList)  
		return (CFont*)(m_FontList[dwIdx]->pItem);
	else return NULL;		
};

// -----------------------------------------------------------------------------------
//	Function:	GetFont
// -----------------------------------------------------------------------------------
//	Desc.	:	Ritorna il font di indice dwIdx
//
//	Return	:	font
//	Params	:	-
// -----------------------------------------------------------------------------------

void CFMT_Wnd::GetFont(DWORD dwIdx,LOGFONT* pFont)		
{	
	ASSERT(::IsWindow(m_hWnd)); 
	
	::SendMessage(m_hWnd, FMTWND_GETFONT_MESS, (WPARAM)dwIdx, (long)(pFont)); 

};

// -----------------------------------------------------------------------------------
//	Function:	SetBackgroundColor
// -----------------------------------------------------------------------------------
//	Desc.	:	Imposta il brush di background con colore uniforme
//
//	Return	:	-
//	Params	:	col = colore
// -----------------------------------------------------------------------------------

void CFMT_Wnd::SetBackgroundColor(COLORREF col)
{
	ASSERT(::IsWindow(m_hWnd)); 
	
	::SendMessage(m_hWnd, FMTWND_SETBACKGROUNDCOLOR_MESS, 0, (LPARAM)col); 
}

// -----------------------------------------------------------------------------------
//	Function:	SetBackgroundBrush
// -----------------------------------------------------------------------------------
//	Desc.	:	Imposta il brush di background 
//
//	Return	:	-
//	Params	:	pBrush = brush da copiare
// -----------------------------------------------------------------------------------

void CFMT_Wnd::SetBackgroundBrush(CBrush *pBrush)
{
	ASSERT(::IsWindow(m_hWnd)); 
	
	::SendMessage(m_hWnd, FMTWND_SETBACKGROUNDBRUSH_MESS, 0, (LPARAM)pBrush); 
}

// -----------------------------------------------------------------------------------
//	Function:	SetBackgroundBrush
// -----------------------------------------------------------------------------------
//	Desc.	:	Imposta il brush di background 
//
//	Return	:	-
//	Params	:	pBrush = brush da copiare
// -----------------------------------------------------------------------------------

void CFMT_Wnd::SetBackgroundBrush(LOGBRUSH *pBrush)
{
	ASSERT(::IsWindow(m_hWnd)); 
	
	::SendMessage(m_hWnd, FMTWND_SETBACKGROUNDBRUSH_MESS, 1, (LPARAM)pBrush); 

}


// -----------------------------------------------------------------------------------
//	Function:	LoadBackgroundBmp
// -----------------------------------------------------------------------------------
//	Desc.	:	Carica la bitmap di background da file
//
//	Return	:	-
//	Params	:	-
// -----------------------------------------------------------------------------------

BOOL CFMT_Wnd::LoadBackgroundBmp(CString sName)
{
	ASSERT(::IsWindow(m_hWnd)); 

	struct STemp
	{
		CString sName;
		int iRet;
	} temp;

	temp.sName=sName;
	temp.iRet=0;
	
	::SendMessage(m_hWnd, FMTWND_LOADBACKGROUNDBMP_MESS, 0, (LPARAM)&temp); 

	return temp.iRet;
}

// -----------------------------------------------------------------------------------
//	Function:	SetBackgroundBmp
// -----------------------------------------------------------------------------------
//	Desc.	:	Imposta la bitmap di background
//
//	Return	:	-
//	Params	:	col = colore
// -----------------------------------------------------------------------------------

void CFMT_Wnd::SetBackgroundBmp(CFMT_DIB *pBmp)
{
	ASSERT(::IsWindow(m_hWnd)); 
	
	::SendMessage(m_hWnd, FMTWND_SETBACKGROUNDBMP_MESS, 0, (LPARAM)pBmp); 
}

// -----------------------------------------------------------------------------------
//	Function:	GetBackgroundBmp
// -----------------------------------------------------------------------------------
//	Desc.	:	Ritorna la bitmap di background
//
//	Return	:	-
//	Params	:	-
// -----------------------------------------------------------------------------------

CFMT_DIB* CFMT_Wnd::GetBackgroundBmp()
{
	ASSERT(::IsWindow(m_hWnd)); 

	CFMT_DIB* pDIB;
	
	::SendMessage(m_hWnd, FMTWND_GETBACKGROUNDBMP_MESS, 0, (LPARAM)(&pDIB)); 

	return pDIB;
}

// -----------------------------------------------------------------------------------
//	Function:	GetBackBufferDC
// -----------------------------------------------------------------------------------
//	Desc.	:	Ritorna un device context da usare come backbuffer
//
//	Return	:	back buffer
//	Params	:	
// -----------------------------------------------------------------------------------

CDC* CFMT_Wnd::GetBackBufferDC(CDC *pDC)
{
	CRect cr;
	GetClientRect(&cr);

	return GetBackBufferDC(pDC,0,0,cr.Width(),cr.Height(),&m_hBackgroundBmp);
}

// -----------------------------------------------------------------------------------
//	Function:	GetBackBufferDC
// -----------------------------------------------------------------------------------
//	Desc.	:	Ritorna un device context da usare come backbuffer
//
//	Return	:	back buffer
//	Params	:	
// -----------------------------------------------------------------------------------

CDC* CFMT_Wnd::GetBackBufferDC(CDC *pDC,int iPosX,int iPosY, DWORD dwDimX, DWORD dwDimY,HBITMAP *phBmp)
{
	if ((m_dwStyle & 0x00000F00)==FMTWND_TRANSPARENT_BACKGROUND)
	{
		CRect pwr,cwr;
		GetClientRect(&cwr);
		ClientToScreen(&cwr);

		GetParent()->GetClientRect(&pwr);
		GetParent()->ClientToScreen(&pwr);

		return ((CFMT_Wnd*)(GetParent()))->
			GetBackBufferDC(pDC,cwr.left-pwr.left,cwr.top-pwr.top,dwDimX,dwDimY,phBmp);
	}

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

	if ((m_dwStyle & 0x00000F00)==FMTWND_COLOR_BACKGROUND)
	{
		pTDC->FillSolidRect(&cr,m_BackgroundColor);
	}
	else if ((m_dwStyle & 0x00000F00)==FMTWND_BRUSH_BACKGROUND)
	{
		pTDC->FillRect(&cr,m_pBackgroundBrush);
	}
	else if (((m_dwStyle & 0x00000F00)==FMTWND_BMP_BACKGROUND) && (m_BackgroundBmp.IsValid()))
	{
		
		m_BackgroundBmp.StretchBlt(pTDC,cr,
			CRect(0,0,m_BackgroundBmp.GetWidth(),m_BackgroundBmp.GetHeight()),
			SRCCOPY);
		//pTDC->FillRect(&cr,m_pBackgroundBrush);
	}

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
//	Function:	GetBackgroundColor
// -----------------------------------------------------------------------------------
//	Desc.	:	Ritorna il colore di background
//
//	Return	:	-
//	Params	:	colore
// -----------------------------------------------------------------------------------

COLORREF CFMT_Wnd::GetBackgroundColor()
{
	ASSERT(::IsWindow(m_hWnd)); 
	
	COLORREF col;
	
	::SendMessage(m_hWnd, FMTWND_GETBACKGROUNDCOLOR_MESS, 0, (LPARAM)(&col)); 
	
	return col;
}

// -----------------------------------------------------------------------------------
//	Function:	GetBackgroundBrush
// -----------------------------------------------------------------------------------
//	Desc.	:	Ritorna il brush di backbuffer
//
//	Return	:	-
//	Params	:	pBr = brush di ritorno
// -----------------------------------------------------------------------------------

void CFMT_Wnd::GetBackgroundBrush(CBrush *pBrush)
{
	ASSERT(::IsWindow(m_hWnd)); 
	
	::SendMessage(m_hWnd, FMTWND_GETBACKGROUNDBRUSH_MESS, 0, (LPARAM)pBrush); 
}

// -----------------------------------------------------------------------------------
//	Function:	GetBackgroundBrush
// -----------------------------------------------------------------------------------
//	Desc.	:	Ritorna il brush di backbuffer
//
//	Return	:	-
//	Params	:	pBr = brush di ritorno
// -----------------------------------------------------------------------------------

void CFMT_Wnd::GetBackgroundBrush(LOGBRUSH *pBrush)
{
	ASSERT(::IsWindow(m_hWnd)); 
	
	::SendMessage(m_hWnd, FMTWND_GETBACKGROUNDBRUSH_MESS, 1, (LPARAM)pBrush); 
}

// -----------------------------------------------------------------------------------
//	Function:	ReleaseBackBufferDC
// -----------------------------------------------------------------------------------
//	Desc.	:	Rilascia il backbuffer
//
//	Return	:	-
//	Params	:	pDC = device context frontbuffer 
// -----------------------------------------------------------------------------------

void CFMT_Wnd::ReleaseBackBufferDC(CDC *pDC)
{
	//hOld=(HBITMAP)(pDC->SelectObject(hBmp));
	DeleteObject(m_hBackgroundBmp);
	delete pDC;
}

// -----------------------------------------------------------------------------------
//	Function:	CopyBackBufferDC
// -----------------------------------------------------------------------------------
//	Desc.	:	Copia il backbuffer sul front buffer
//
//	Return	:	-
//	Params	:	pSDC = device context frontbuffer 
//				pDDC = device context frontbuffer 
// -----------------------------------------------------------------------------------

void CFMT_Wnd::CopyBackBufferDC(CDC *pDDC,CDC *pSDC,CRect *pSRC)
{
	if (pSRC==NULL)
	{
		CRect cr;
		GetClientRect(&cr);

		pDDC->BitBlt(cr.left,cr.top,cr.Width(),cr.Height(),pSDC,0,0,SRCCOPY);
	}
	else
	{
		pDDC->BitBlt(pSRC->left,pSRC->top,pSRC->Width(),pSRC->Height(),pSDC,pSRC->left,pSRC->top,SRCCOPY);
	}
}

// -----------------------------------------------------------------------------------
//	Function:	ModifyFMTStyle
// -----------------------------------------------------------------------------------
//	Desc.	:	Modifica lo stile della finestra
//
//	Return	:	-
//	Params	:	dwDelStyle = stile da rimuovere
//				dwInsStyle = stile da inserire
// -----------------------------------------------------------------------------------

void CFMT_Wnd::ModifyFMTStyle(DWORD dwDelStyle, DWORD dwInsStyle)
{
	ASSERT(::IsWindow(m_hWnd)); 

	::SendMessage(m_hWnd, FMTWND_MODIFYSTYLE_MESS, (UINT)dwDelStyle,(long)dwInsStyle); 
}

// -----------------------------------------------------------------------------------
//	Function:	GetFirstParam
// -----------------------------------------------------------------------------------
//	Desc.	:	Ritorna il primo parametro del caption
//
//	Return	:	-
//	Params	:	sCaption = caption
//				psParam = parametro di ritorno
// -----------------------------------------------------------------------------------

BOOL CFMT_Wnd::GetFirstParam(CString sCaption,CString *psParam)
{
	m_dwParamPos=0;
	return GetNextParam(sCaption,psParam);
}

// -----------------------------------------------------------------------------------
//	Function:	GetFirstParam
// -----------------------------------------------------------------------------------
//	Desc.	:	Ritorna il primo parametro del caption
//
//	Return	:	-
//	Params	:	sCaption = caption
//				pdwParam = parametro di ritorno
// -----------------------------------------------------------------------------------

BOOL CFMT_Wnd::GetFirstParam(CString sCaption,int *piParam)
{
	m_dwParamPos=0;
	return GetNextParam(sCaption,piParam);
}

// -----------------------------------------------------------------------------------
//	Function:	GetFirstParam
// -----------------------------------------------------------------------------------
//	Desc.	:	Ritorna il primo parametro del caption
//
//	Return	:	-
//	Params	:	sCaption = caption
//				pColor = parametro di ritorno
// -----------------------------------------------------------------------------------

BOOL CFMT_Wnd::GetFirstParam(CString sCaption,COLORREF *pColor)
{
	m_dwParamPos=0;
	return GetNextParam(sCaption,pColor);
}

// -----------------------------------------------------------------------------------
//	Function:	GetNextParam
// -----------------------------------------------------------------------------------
//	Desc.	:	Ritorna il primo parametro del caption
//
//	Return	:	-
//	Params	:	sCaption = caption
//				pColor = parametro di ritorno
// -----------------------------------------------------------------------------------

BOOL CFMT_Wnd::GetNextParam(CString sCaption,COLORREF *pColor)
{
	sCaption.TrimLeft();

	if (sCaption.GetLength()<(int)(m_dwParamPos+1))
		return FALSE;

	BOOL bAgain=TRUE;
	int i=(int)m_dwParamPos;
	CString s;

	while (bAgain && (i<sCaption.GetLength()))
	{
		if (sCaption.GetAt(i)==';')
			bAgain=FALSE;
		else i++;
	}

	if (!bAgain)
	{
		s=sCaption.Left(i);
		s=s.Right(s.GetLength()-m_dwParamPos);
	}
	else 
	{
		s=sCaption.Right(sCaption.GetLength()-m_dwParamPos);
	}

	if ((s.Left(4)=="RGB(") && (s.GetAt(s.GetLength()-1)==')'))
	{
		int idx;
		DWORD dwR,dwG,dwB;
			
		s=s.Right(s.GetLength()-4);
		s=s.Left(s.GetLength()-1);

		idx=s.Find(',',0);
		dwR=atoi(s.Left(idx));
		s=s.Right(s.GetLength()-idx-1);

		idx=s.Find(',',0);
		dwG=atoi(s.Left(idx));
		s=s.Right(s.GetLength()-idx-1);

		dwB=atoi(s);

		(*pColor)=RGB(dwR,dwG,dwB);
	}
	else
	{
		(*pColor)=RGB(0,0,0);
		m_dwParamPos=i+1;
		return FALSE;
	}

	m_dwParamPos=i+1;

	return TRUE;
}

// -----------------------------------------------------------------------------------
//	Function:	GetNextParam
// -----------------------------------------------------------------------------------
//	Desc.	:	Ritorna il parametro successivo del caption
//
//	Return	:	-
//	Params	:	sCaption = caption
//				psParam = parametro di ritorno
// -----------------------------------------------------------------------------------

BOOL CFMT_Wnd::GetNextParam(CString sCaption,CString *psParam)
{
	sCaption.TrimLeft();

	if (sCaption.GetLength()<(int)(m_dwParamPos+1))
		return FALSE;

	BOOL bAgain=TRUE;
	int i=(int)m_dwParamPos;
	CString s;

	while (bAgain && (i<sCaption.GetLength()))
	{
		if (sCaption.GetAt(i)==';')
			bAgain=FALSE;
		else i++;
	}

	if (!bAgain)
	{
		s=sCaption.Left(i);
		s=s.Right(s.GetLength()-m_dwParamPos);
	}
	else 
	{
		s=sCaption.Right(sCaption.GetLength()-m_dwParamPos);
	}
		
	if ((s.GetAt(0)=='"') && (s.GetAt(s.GetLength()-1)=='"'))
	{
		s=s.Right(s.GetLength()-1);
		(*psParam)=s.Left(s.GetLength()-1);
	}
	else 
	{
		(*psParam)="";
		m_dwParamPos=i+1;
		return FALSE;
	}

	m_dwParamPos=i+1;

	return TRUE;
}

// -----------------------------------------------------------------------------------
//	Function:	GetNextParam
// -----------------------------------------------------------------------------------
//	Desc.	:	Ritorna il parametro successivo del caption
//
//	Return	:	-
//	Params	:	sCaption = caption
//				pdwParam = parametro di ritorno
// -----------------------------------------------------------------------------------

BOOL CFMT_Wnd::GetNextParam(CString sCaption,int *piParam)
{
	sCaption.TrimLeft();

	if (sCaption.GetLength()<(int)(m_dwParamPos+1))
		return FALSE;

	BOOL bAgain=TRUE;
	int i=(int)m_dwParamPos;
	CString s;

	while (bAgain && (i<sCaption.GetLength()))
	{
		if (sCaption.GetAt(i)==';')
			bAgain=FALSE;
		else i++;
	}

	if (!bAgain)
	{
		s=sCaption.Left(i);
		s=s.Right(s.GetLength()-m_dwParamPos);
	}
	else 
	{
		s=sCaption.Right(sCaption.GetLength()-m_dwParamPos);
	}
		
	if (s.GetLength()==0)
	{
		(*piParam)=0;
		m_dwParamPos=i+1;
		return FALSE;
	}
	else if ((s.Left(2)=="0x") || (s.Left(2)=="0X"))
	{
		(*piParam)=strtol(s.Right(s.GetLength()-2),NULL,16);
	}
	else
	{
		(*piParam)=atoi(s);
	}

	m_dwParamPos=i+1;

	return TRUE;
}

// =====================================================================================
//	MESSAGE MAP
// =====================================================================================

BEGIN_MESSAGE_MAP(CFMT_Wnd, CWnd)
	//{{AFX_MSG_MAP(CFMT_Wnd)
	ON_WM_NCCREATE()
	ON_WM_NCCALCSIZE()
	ON_WM_NCCALCSIZE()
	ON_MESSAGE(WM_NCPAINT,OnNewNcPaint)
	//}}AFX_MSG_MAP

	ON_FMTWND_SETSTYLE(OnFMSetStyle)
	ON_FMTWND_GETSTYLE(OnFMGetStyle)
	ON_FMTWND_MODIFYSTYLE(OnFMModifyStyle)
	ON_FMTWND_SETBACKGROUNDCOLOR(OnFMSetBackgroundColor)
	ON_FMTWND_GETBACKGROUNDCOLOR(OnFMGetBackgroundColor)
	ON_FMTWND_SETBACKGROUNDBRUSH(OnFMSetBackgroundBrush)
	ON_FMTWND_GETBACKGROUNDBRUSH(OnFMGetBackgroundBrush)
	ON_FMTWND_LOADBACKGROUNDBMP(OnFMTLoadBackBmp)
	ON_FMTWND_SETBACKGROUNDBMP(OnFMTSetBackBmp)
	ON_FMTWND_SETBACKGROUNDBMP(OnFMTGetBackBmp)
	ON_FMTWND_ADDFONT(OnFMAddFont)
	ON_FMTWND_ATTACHFONT(OnFMAttachFont)
	ON_FMTWND_DELETEFONT(OnFMDeleteFont)
	ON_FMTWND_GETNUMFONTS(OnFMGetNumFonts)
	ON_FMTWND_SETBORDERCOLOR(OnFMSetBorderColor)
	ON_FMTWND_GETBORDERCOLOR(OnFMGetBorderColor)
	ON_FMTWND_REDRAWFULL(OnFMRedrawFullWindow)


END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFMT_Wnd message handlers
/////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------------
//	Function:	OnNewNcPaint
// -----------------------------------------------------------------------------------
//	Desc.	:	Handler messaggio WM_NCPAINT
//
//	Return	:	-
//	Params	:	-
// -----------------------------------------------------------------------------------

LRESULT CFMT_Wnd::OnNewNcPaint(UINT wParam,LONG lParam)
{
	CWindowDC dc(this);

	CRgn *pRgn=CRgn::FromHandle((HRGN)wParam);

	CRect wr;
	GetWindowRect(&wr);

	pRgn->OffsetRgn(-wr.left,-wr.top);
	dc.SelectClipRgn(pRgn);

	DrawNcArea(&dc);

	return 0;
}

// -----------------------------------------------------------------------------------
//	Function:	OnNcCreate
// -----------------------------------------------------------------------------------
//	Desc.	:	Handler messaggio WM_NCCREATE
//
//	Return	:	-
//	Params	:	-
// -----------------------------------------------------------------------------------

BOOL CFMT_Wnd::OnNcCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (!CWnd::OnNcCreate(lpCreateStruct))
		return FALSE;
	
	return TRUE;
}

// -----------------------------------------------------------------------------------
//	Function:	OnNcCalcSize
// -----------------------------------------------------------------------------------
//	Desc.	:	Handler messaggio WM_NCCALCSIZE
//
//	Return	:	-
//	Params	:	bCalcValidRects = rect idx 1,2 validi
//				lpncsp = array rects
// -----------------------------------------------------------------------------------

void CFMT_Wnd::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp) 
{
	lpncsp->rgrc[0].left+=m_MarginCR.left;
	lpncsp->rgrc[0].right-=m_MarginCR.right;
	lpncsp->rgrc[0].top+=m_MarginCR.top;
	lpncsp->rgrc[0].bottom-=m_MarginCR.bottom;
}

// -----------------------------------------------------------------------------------
//	Function:	OnFMSetBackgroundColor
// -----------------------------------------------------------------------------------
//	Desc.	:	Handler messaggio FMTWND_SETBACKGROUNDCOLOR_MESS
//
//	Return	:	-
//	Params	:	
//				
// -----------------------------------------------------------------------------------

LRESULT CFMT_Wnd::OnFMSetBackgroundColor(UINT wParam,LONG lParam)
{
	m_BackgroundColor=(COLORREF)lParam;

	return 0;
}

// -----------------------------------------------------------------------------------
//	Function:	OnFMGetBackgroundColor
// -----------------------------------------------------------------------------------
//	Desc.	:	Handler messaggio FMTWND_GETBACKGROUNDCOLOR_MESS
//
//	Return	:	-
//	Params	:	
//				
// -----------------------------------------------------------------------------------

LRESULT CFMT_Wnd::OnFMGetBackgroundColor(UINT wParam,LONG lParam)
{
	(*((COLORREF*)lParam))=m_BackgroundColor;

	return 0;
}

// -----------------------------------------------------------------------------------
//	Function:	OnFMSetStyle
// -----------------------------------------------------------------------------------
//	Desc.	:	Handler messaggio FMTWND_SETSTYLE_MESS
//
//	Return	:	-
//	Params	:	
//				
// -----------------------------------------------------------------------------------

LRESULT CFMT_Wnd::OnFMSetStyle(UINT wParam,LONG lParam)
{
	m_dwStyle=(DWORD)wParam;

	if (((DWORD)lParam & 0x00000001)>0)
	{
		CRect ncr;
		ncr=GetCRFromStyle(m_dwStyle);

		SetClientRect(&ncr);
	}

	return 0;
}

// -----------------------------------------------------------------------------------
//	Function:	OnFMGetStyle
// -----------------------------------------------------------------------------------
//	Desc.	:	Handler messaggio FMTWND_GETSTYLE_MESS
//
//	Return	:	-
//	Params	:	
//				
// -----------------------------------------------------------------------------------

LRESULT CFMT_Wnd::OnFMGetStyle(UINT wParam,LONG lParam)
{
	(*((DWORD*)wParam))=m_dwStyle;

	return 0;
}

// -----------------------------------------------------------------------------------
//	Function:	OnFMModifyStyle
// -----------------------------------------------------------------------------------
//	Desc.	:	Handler messaggio FMTWND_MODIFYSTYLE_MESS
//
//	Return	:	-
//	Params	:	
//				
// -----------------------------------------------------------------------------------

LRESULT CFMT_Wnd::OnFMModifyStyle(UINT wParam,LONG lParam)
{
	DWORD dwNewStyle;
	CRect ncr;

	if ((((DWORD)wParam) & 0x000000FF)>0)
		m_dwStyle&=0xFFFFFF00;

	if ((((DWORD)wParam) & 0x00000F00)>0)
		m_dwStyle&=0xFFFFF0FF;

	dwNewStyle=(m_dwStyle & (~(((DWORD)wParam) & 0xFFFFF000))) | ((DWORD)lParam);

	m_dwStyle=dwNewStyle;

	ncr=GetCRFromStyle(m_dwStyle);

	SetClientRect(&ncr);

	return 0;
}

// -----------------------------------------------------------------------------------
//	Function:	OnFMAddFont
// -----------------------------------------------------------------------------------
//	Desc.	:	Handler messaggio FMTWND_ADDFONT_MESS
//
//	Return	:	-
//	Params	:	
//				
// -----------------------------------------------------------------------------------

LRESULT CFMT_Wnd::OnFMAddFont(UINT wParam,LONG lParam)
{
	DWORD dwIdx=(DWORD)wParam;
	CFont *pFont=(CFont*)lParam;

	if (dwIdx>(!m_FontList))
	{
		return 0;
	}
	else
	{
		LOGFONT lf;
		SFMT_WndRemovableItem *pItem=new SFMT_WndRemovableItem;
		CFont *pNewFont=new CFont();

		pFont->GetLogFont(&lf);
		pNewFont->CreateFontIndirect(&lf);

		pItem->bDeletable=TRUE;
		pItem->pItem=pNewFont;

		if (dwIdx==(!m_FontList))
		{
			m_FontList+=pItem;
		}
		else
		{
			m_FontList.ToStart();
			m_FontList>>dwIdx;
			m_FontList.InsertItem(pItem);
		}
	}

	return 0;
}

// -----------------------------------------------------------------------------------
//	Function:	OnFMAttachFont
// -----------------------------------------------------------------------------------
//	Desc.	:	Handler messaggio FMTWND_ATTACHFONT_MESS
//
//	Return	:	-
//	Params	:	
//				
// -----------------------------------------------------------------------------------

LRESULT CFMT_Wnd::OnFMAttachFont(UINT wParam,LONG lParam)
{
	CFont *pFont=(CFont*)lParam;

	if (wParam>(!m_FontList))
		return 0;

	SFMT_WndRemovableItem *pItem=new SFMT_WndRemovableItem;

	pItem->bDeletable=FALSE;
	pItem->pItem=pFont;

	if (wParam==(!m_FontList))
	{
		m_FontList+=pItem;
	}
	else
	{
		m_FontList.ToStart();
		m_FontList>>wParam;
		m_FontList.InsertItem(pItem);
	}

	return 0;
}

// -----------------------------------------------------------------------------------
//	Function:	OnFMDeleteFont
// -----------------------------------------------------------------------------------
//	Desc.	:	Handler messaggio FMTWND_DELETEFONT_MESS
//
//	Return	:	-
//	Params	:	
//				
// -----------------------------------------------------------------------------------

LRESULT CFMT_Wnd::OnFMDeleteFont(UINT wParam,LONG lParam)
{
	if (wParam>=(!m_FontList))
		return 0;

	m_FontList.ToStart();
	m_FontList>>wParam;

	CFont *pRet=(CFont*)(m_FontList.CurItem()->pItem);

	if (m_FontList.CurItem()->bDeletable)
		delete ((CFont*)(m_FontList.CurItem()->pItem));

	delete m_FontList.CurItem();

	m_FontList.DeleteItem();

	return 0;
}

// -----------------------------------------------------------------------------------
//	Function:	OnFMGetNumFonts
// -----------------------------------------------------------------------------------
//	Desc.	:	Handler messaggio FMTWND_GETNUMFONTS_MESS
//
//	Return	:	-
//	Params	:	
//				
// -----------------------------------------------------------------------------------

LRESULT CFMT_Wnd::OnFMGetNumFonts(UINT wParam,LONG lParam)
{
	*((DWORD*)lParam)=!m_FontList;

	return 0;
}

// -----------------------------------------------------------------------------------
//	Function:	OnFMGetFont
// -----------------------------------------------------------------------------------
//	Desc.	:	Handler messaggio FMTWND_GETFONT_MESS
//
//	Return	:	-
//	Params	:	
//				
// -----------------------------------------------------------------------------------

LRESULT CFMT_Wnd::OnFMGetFont(UINT wParam,LONG lParam)
{
	LOGFONT *plog;
	CFont *pFont;

	plog=(LOGFONT*)lParam;

	pFont=GetFont(wParam);

	pFont->GetLogFont(plog);

	return 0;
}

// -----------------------------------------------------------------------------------
//	Function:	OnFMSetBackgroundBrush
// -----------------------------------------------------------------------------------
//	Desc.	:	Handler messaggio FMTWND_SETBACKGROUNDBRUSH_MESS
//
//	Return	:	-
//	Params	:	
//				
// -----------------------------------------------------------------------------------

LRESULT CFMT_Wnd::OnFMSetBackgroundBrush(UINT wParam,LONG lParam)
{
	switch (wParam)
	{
		case 0:
		{
			CBrush *pBrush=(CBrush*)lParam;

			LOGBRUSH lb;
			pBrush->GetLogBrush(&lb);

			delete m_pBackgroundBrush;
	
			m_pBackgroundBrush=new CBrush;
			m_pBackgroundBrush->CreateBrushIndirect(&lb);
		}
		break;

		case 1:
		{
			LOGBRUSH *pBrush=(LOGBRUSH*)lParam;

			delete m_pBackgroundBrush;
	
			m_pBackgroundBrush=new CBrush;
			m_pBackgroundBrush->CreateBrushIndirect(pBrush);
		}
		break;

	}

	return 0;
}

// -----------------------------------------------------------------------------------
//	Function:	OnFMGetBackgroundBrush
// -----------------------------------------------------------------------------------
//	Desc.	:	Handler messaggio FMTWND_GETBACKGROUNDBRUSH_MESS
//
//	Return	:	-
//	Params	:	
//				
// -----------------------------------------------------------------------------------

LRESULT CFMT_Wnd::OnFMGetBackgroundBrush(UINT wParam,LONG lParam)
{
	switch (wParam)
	{
		case 0:
		{
			CBrush *pBrush=(CBrush*)lParam;
	
			pBrush=m_pBackgroundBrush;
		}
		break;

		case 1:
		{
			LOGBRUSH *pBrush=(LOGBRUSH*)lParam;
	
			m_pBackgroundBrush->GetLogBrush(pBrush);
		}
		break;
	}

	return 0;
}

// -----------------------------------------------------------------------------------
//	Function:	OnFMSetBorderColor
// -----------------------------------------------------------------------------------
//	Desc.	:	Handler messaggio FMTWND_SETBORDERCOLOR_MESS
//
//	Return	:	-
//	Params	:	
//				
// -----------------------------------------------------------------------------------

LRESULT CFMT_Wnd::OnFMSetBorderColor(UINT wParam,LONG lParam)
{
	m_colBorder=(COLORREF)lParam;
	

	return 0;
}

// -----------------------------------------------------------------------------------
//	Function:	OnFMGetBorderColor
// -----------------------------------------------------------------------------------
//	Desc.	:	Handler messaggio FMTWND_GETBORDERCOLOR_MESS
//
//	Return	:	-
//	Params	:	
//				
// -----------------------------------------------------------------------------------

LRESULT CFMT_Wnd::OnFMGetBorderColor(UINT wParam,LONG lParam)
{
	*((COLORREF*)lParam)=m_colBorder;

	return 0;
}

// -----------------------------------------------------------------------------------
//	Function:	OnFMRedrawFullWindow
// -----------------------------------------------------------------------------------
//	Desc.	:	Handler messaggio FMTWND_REDRAWFULL_MESS
//
//	Return	:	-
//	Params	:	
//				
// -----------------------------------------------------------------------------------

LRESULT CFMT_Wnd::OnFMRedrawFullWindow(UINT wParam,LONG lParam)
{
	SetWindowPos(NULL,0,0,0,0,
		SWP_NOZORDER|SWP_NOMOVE|SWP_NOSIZE|SWP_SHOWWINDOW|SWP_DRAWFRAME);
	RedrawWindow();

	return 0;
}

// -----------------------------------------------------------------------------------
//	Function:	OnFMTLoadBackBmp
// -----------------------------------------------------------------------------------
//	Desc.	:	Handler messaggio FMTWND_LOADBACKBMP_MESS
//
//	Return	:	-
//	Params	:	
//				
// -----------------------------------------------------------------------------------

LRESULT CFMT_Wnd::OnFMTLoadBackBmp(UINT wParam,LONG lParam)
{
	struct STemp
	{
		CString sName;
		int iRet;
	} *pTemp;

	pTemp=(STemp*)lParam;

	if (m_BackgroundBmp.LoadFile(pTemp->sName))
	{
		pTemp->iRet=0;
	}
	else
	{
		pTemp->iRet=-1;
	}
	
	return 0;
}

// -----------------------------------------------------------------------------------
//	Function:	OnFMTSetBackBmp
// -----------------------------------------------------------------------------------
//	Desc.	:	Handler messaggio FMTWND_SETBACKBMP_MESS
//
//	Return	:	-
//	Params	:	
//				
// -----------------------------------------------------------------------------------

LRESULT CFMT_Wnd::OnFMTSetBackBmp(UINT wParam,LONG lParam)
{
	CFMT_DIB *pBmp=(CFMT_DIB*)lParam;

	m_BackgroundBmp=(*pBmp);

	return 0;
}

// -----------------------------------------------------------------------------------
//	Function:	OnFMTGetBackBmp
// -----------------------------------------------------------------------------------
//	Desc.	:	Handler messaggio FMTWND_GETBACKBMP_MESS
//
//	Return	:	-
//	Params	:	
//				
// -----------------------------------------------------------------------------------

LRESULT CFMT_Wnd::OnFMTGetBackBmp(UINT wParam,LONG lParam)
{
	*((CFMT_DIB**)lParam)=&m_BackgroundBmp;

	return 0;
}

#endif


