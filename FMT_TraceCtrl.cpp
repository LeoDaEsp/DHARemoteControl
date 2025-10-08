//***************************************************************************
//
// Module:		FMT_TraceCtrl.cpp
//
// Description:	Controllo generico multi stato
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
//	1.0		11-01-03	M.Forzieri		First issue
// --------------------------------------------------------------------------
//***************************************************************************

#include "stdafx.h"

#ifndef FMT_TRACECTRL_H
#include "FMT_TraceCtrl.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "math.h"

// *************************************************************************************
// *************************************************************************************
//	Implementazione classe CFMT_TraceCtrl
// *************************************************************************************
// *************************************************************************************

// -----------------------------------------------------------------------------------
//	Function:	m_bRegistered = Register()
// -----------------------------------------------------------------------------------
//	Desc.	:	Consente di registrare la classe all'atto dell'allocazione della
//				variabile membro
//
//	Return	:	-
//	Params	:	-
// -----------------------------------------------------------------------------------

BOOL CFMT_TraceCtrl::m_bRegistered = Register();


// -----------------------------------------------------------------------------------
//	Function:	Register
// -----------------------------------------------------------------------------------
//	Desc.	:	Registra la classe
//
//	Return	:	TRUE se la registrazione è OK
//	Params	:	-
// -----------------------------------------------------------------------------------

BOOL CFMT_TraceCtrl::Register()
{
    // Register the window class of the control
    WNDCLASS wc;
    wc.style = CS_GLOBALCLASS
             | CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = FMT_TraceCtrlWndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = NULL;
    wc.hIcon = NULL;
    wc.hCursor = ::LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = NULL;
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "FMT_TraceCtrl";

    if (!::RegisterClass(&wc)) {
        ASSERT(0);
        return FALSE;
    } 
    return TRUE;
}

// -----------------------------------------------------------------------------------
//	Function:	CALLBACK CFMT_TraceCtrlWndProc
// -----------------------------------------------------------------------------------
//	Desc.	:	funzione callback per il subclassing
//
//	Return	:	TRUE se la registrazione è OK
//	Params	:	-
// -----------------------------------------------------------------------------------

LRESULT CALLBACK FMT_TraceCtrlWndProc(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uiMsg) 
	{
    case WM_NCCREATE: 
		{
			LPCREATESTRUCT lp=(LPCREATESTRUCT) lParam;

			char ch;
			memcpy(&ch,lp->lpszName,1);

			if (ch!='#')
			{
				// Create a C++ object to handle the messages
				CFMT_TraceCtrl* pCtl = new CFMT_TraceCtrl;
				ASSERT(pCtl);
				// Attach the window handle to the new object
				BOOL b = pCtl->SubclassWindow(hWnd);

				ASSERT(b);
				return b;
			}
			else return ::DefWindowProc(hWnd, uiMsg, wParam, lParam);
        } 
		break;
    default:
        return ::DefWindowProc(hWnd, uiMsg, wParam, lParam);
    }
}


IMPLEMENT_DYNCREATE(CFMT_TraceCtrl, CFMT_Wnd)

// =====================================================================================
//	MESSAGE MAP
// =====================================================================================

BEGIN_MESSAGE_MAP(CFMT_TraceCtrl, CFMT_Wnd)
	//{{AFX_MSG_MAP(CFMT_TraceCtrl)
	ON_WM_PAINT()
	ON_WM_NCDESTROY()
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP

	ON_FMTTRCCTL_SCROLL(OnFMTScroll)
	ON_FMTTRCCTL_ZOOM(OnFMTZoom)
	ON_FMTTRCCTL_SETAXIS(OnFMTSetAxis)
	ON_FMTTRCCTL_GETAXIS(OnFMTGetAxis)
	ON_FMTTRCCTL_BACKCOL(OnFMTBackCol)
	ON_FMTTRCCTL_TRACE(OnFMTTrace)
	ON_FMTTRCCTL_GRID(OnFMTGrid)
	ON_FMTTRCCTL_LINE(OnFMTLine)
	
	/*ON_FMTTRCCTL_SETSTYLE(OnFMTSetTCStyle)
	ON_FMTTRCCTL_GETSTYLE(OnFMTGetTCStyle)
	ON_FMTTRCCTL_MODIFYSTYLE(OnFMTModifyTCStyle)*/


END_MESSAGE_MAP()

// =====================================================================================
// COSTRUTTORI E DISTRUTTORI
// =====================================================================================


CFMT_TraceCtrl::CFMT_TraceCtrl()
{
	m_dwTCStyle=0;

	m_BackgroundColor=RGB(0,0,0);
	m_colTraceBack=RGB(0,0,0);
	m_colBorderBack=RGB(0,0,200);

	m_iPX=250;
	m_iPY=150;

	m_dSX=200.0;
	m_dSY=200.0;

	// Inizializzo assi --------------------------
	
	m_AxisX.bEnabled=TRUE;
	m_AxisX.bDrawTaps=TRUE;
	m_AxisX.bDrawSubTaps=TRUE;
	m_AxisX.bVert=FALSE;
	m_AxisX.colAxis=RGB(255,0,0);
	m_AxisX.sLabel="Sec";
	m_AxisX.btLabelFontID=0;
	m_AxisX.colLabel=RGB(0,0,0);
	m_AxisX.colBackLabel=RGB(255,200,200);
	m_AxisX.szLabelSize.cx=50;
	m_AxisX.szLabelSize.cy=25;
	m_AxisX.btLabelPos=4;
	m_AxisX.bLabelTransp=FALSE;
	m_AxisX.bDrawText=TRUE;
	m_AxisX.dScale=1.0;
	m_AxisX.dOffset=0.0;
	m_AxisX.dTapPitch=1.0;
	m_AxisX.dwSubTapNum=10;
	m_AxisX.colTap=RGB(0,255,0);
	m_AxisX.colSubTap=RGB(255,255,255);
	m_AxisX.btTapSize=8;
	m_AxisX.btSubTapSize=3;
	m_AxisX.colTapLabel=RGB(255,255,0);
	m_AxisX.colSubTapLabel=RGB(255,255,255);
	m_AxisX.bDrawTapLabels=TRUE;
	m_AxisX.bDrawSubTabLabels=FALSE;
	m_AxisX.btTapLabelFontID=0;
	m_AxisX.btSubTapLabelFontID=0;
	m_AxisX.btTapLabelSize=20;
	m_AxisX.btSubTapLabelSize=15;
	m_AxisX.btTabLabelDec=2;
	m_AxisX.btSubTabLabelDec=1;


	m_AxisY.bEnabled=TRUE;
	m_AxisY.bDrawTaps=TRUE;
	m_AxisY.bDrawSubTaps=TRUE;
	m_AxisY.bVert=TRUE;
	m_AxisY.colAxis=RGB(255,0,0);
	m_AxisY.sLabel="Ciao";
	m_AxisY.btLabelFontID=0;
	m_AxisY.colLabel=RGB(0,0,0);
	m_AxisY.colBackLabel=RGB(255,200,200);
	m_AxisY.szLabelSize.cx=50;
	m_AxisY.szLabelSize.cy=25;
	m_AxisY.btLabelPos=0;
	m_AxisY.bLabelTransp=FALSE;
	m_AxisY.bDrawText=TRUE;
	m_AxisY.dScale=1.0;
	m_AxisY.dOffset=0.0;
	m_AxisY.dTapPitch=1.0;
	m_AxisY.dwSubTapNum=10;
	m_AxisY.colTap=RGB(0,255,0);
	m_AxisY.colSubTap=RGB(255,255,0);
	m_AxisY.btTapSize=8;
	m_AxisY.btSubTapSize=4;
	m_AxisY.colTapLabel=RGB(255,255,255);
	m_AxisY.colSubTapLabel=RGB(255,255,255);
	m_AxisY.bDrawTapLabels=TRUE;
	m_AxisY.bDrawSubTabLabels=TRUE;
	m_AxisY.btTapLabelFontID=0;
	m_AxisY.btSubTapLabelFontID=0;
	m_AxisY.btTapLabelSize=40;
	m_AxisY.btSubTapLabelSize=40;
	m_AxisY.btTabLabelDec=1;
	m_AxisY.btSubTabLabelDec=1;

	m_AxisLeft.bEnabled=TRUE;
	m_AxisLeft.bDrawTaps=TRUE;
	m_AxisLeft.bDrawSubTaps=TRUE;
	m_AxisLeft.bVert=TRUE;
	m_AxisLeft.colAxis=RGB(255,0,0);
	m_AxisLeft.sLabel="Volt";
	m_AxisLeft.btLabelFontID=0;
	m_AxisLeft.colLabel=RGB(0,0,0);
	m_AxisLeft.colBackLabel=RGB(255,200,200);
	m_AxisLeft.szLabelSize.cx=50;
	m_AxisLeft.szLabelSize.cy=25;
	m_AxisLeft.btLabelPos=0;
	m_AxisLeft.bLabelTransp=FALSE;
	m_AxisLeft.bDrawText=TRUE;
	m_AxisLeft.dScale=1.0;
	m_AxisLeft.dOffset=0.0;
	m_AxisLeft.dTapPitch=1.0;
	m_AxisLeft.dwSubTapNum=10;
	m_AxisLeft.colTap=RGB(0,255,0);
	m_AxisLeft.colSubTap=RGB(255,255,255);
	m_AxisLeft.btTapSize=8;
	m_AxisLeft.btSubTapSize=3;
	m_AxisLeft.colTapLabel=RGB(255,255,255);
	m_AxisLeft.colSubTapLabel=RGB(255,255,255);
	m_AxisLeft.bDrawTapLabels=TRUE;
	m_AxisLeft.bDrawSubTabLabels=TRUE;
	m_AxisLeft.btTapLabelFontID=0;
	m_AxisLeft.btSubTapLabelFontID=0;
	m_AxisLeft.btTapLabelSize=22;
	m_AxisLeft.btSubTapLabelSize=22;
	m_AxisLeft.btTabLabelDec=1;
	m_AxisLeft.btSubTabLabelDec=1;

	m_AxisTop.bEnabled=TRUE;
	m_AxisTop.bDrawTaps=TRUE;
	m_AxisTop.bDrawSubTaps=TRUE;
	m_AxisTop.bVert=FALSE;
	m_AxisTop.colAxis=RGB(255,0,0);
	m_AxisTop.sLabel="Sec";
	m_AxisTop.btLabelFontID=0;
	m_AxisTop.colLabel=RGB(0,0,0);
	m_AxisTop.colBackLabel=RGB(255,200,200);
	m_AxisTop.szLabelSize.cx=50;
	m_AxisTop.szLabelSize.cy=25;
	m_AxisTop.btLabelPos=5;
	m_AxisTop.bLabelTransp=FALSE;
	m_AxisTop.bDrawText=TRUE;
	m_AxisTop.dScale=2;
	m_AxisTop.dOffset=0.5;
	m_AxisTop.dTapPitch=1.0;
	m_AxisTop.dwSubTapNum=10;
	m_AxisTop.colTap=RGB(255,255,255);
	m_AxisTop.colSubTap=RGB(255,255,255);
	m_AxisTop.btTapSize=8;
	m_AxisTop.btSubTapSize=3;
	m_AxisTop.colTapLabel=RGB(255,255,255);
	m_AxisTop.colSubTapLabel=RGB(255,255,255);
	m_AxisTop.bDrawTapLabels=FALSE;
	m_AxisTop.bDrawSubTabLabels=TRUE;
	m_AxisTop.btTapLabelFontID=0;
	m_AxisTop.btSubTapLabelFontID=0;
	m_AxisTop.btTapLabelSize=20;
	m_AxisTop.btSubTapLabelSize=15;
	m_AxisTop.btTabLabelDec=1;
	m_AxisTop.btSubTabLabelDec=1;

	m_AxisRight.bEnabled=TRUE;
	m_AxisRight.bDrawTaps=TRUE;
	m_AxisRight.bDrawSubTaps=TRUE;
	m_AxisRight.bVert=TRUE;
	m_AxisRight.colAxis=RGB(255,0,0);
	m_AxisRight.sLabel="Volt";
	m_AxisRight.btLabelFontID=0;
	m_AxisRight.colLabel=RGB(0,0,0);
	m_AxisRight.colBackLabel=RGB(255,200,200);
	m_AxisRight.szLabelSize.cx=50;
	m_AxisRight.szLabelSize.cy=25;
	m_AxisRight.btLabelPos=0;
	m_AxisRight.bLabelTransp=FALSE;
	m_AxisRight.bDrawText=TRUE;
	m_AxisRight.dScale=1.0;
	m_AxisRight.dOffset=0.0;
	m_AxisRight.dTapPitch=1.0;
	m_AxisRight.dwSubTapNum=10;
	m_AxisRight.colTap=RGB(0,255,0);
	m_AxisRight.colSubTap=RGB(255,255,255);
	m_AxisRight.btTapSize=8;
	m_AxisRight.btSubTapSize=3;
	m_AxisRight.colTapLabel=RGB(255,255,255);
	m_AxisRight.colSubTapLabel=RGB(255,255,255);
	m_AxisRight.bDrawTapLabels=TRUE;
	m_AxisRight.bDrawSubTabLabels=TRUE;
	m_AxisRight.btTapLabelFontID=0;
	m_AxisRight.btSubTapLabelFontID=0;
	m_AxisRight.btTapLabelSize=30;
	m_AxisRight.btSubTapLabelSize=30;
	m_AxisRight.btTabLabelDec=1;
	m_AxisRight.btSubTabLabelDec=1;

	m_AxisBottom.bEnabled=TRUE;
	m_AxisBottom.bDrawTaps=TRUE; 
	m_AxisBottom.bDrawSubTaps=TRUE;
	m_AxisBottom.bVert=FALSE;
	m_AxisBottom.colAxis=RGB(255,0,0);
	m_AxisBottom.sLabel="Sec";
	m_AxisBottom.btLabelFontID=0;
	m_AxisBottom.colLabel=RGB(0,0,0);
	m_AxisBottom.colBackLabel=RGB(255,200,200);
	m_AxisBottom.szLabelSize.cx=50;
	m_AxisBottom.szLabelSize.cy=25;
	m_AxisBottom.btLabelPos=0;
	m_AxisBottom.bLabelTransp=FALSE;
	m_AxisBottom.bDrawText=TRUE;
	m_AxisBottom.dScale=2;
	m_AxisBottom.dOffset=0.0;
	m_AxisBottom.dTapPitch=1.0;
	m_AxisBottom.dwSubTapNum=10;
	m_AxisBottom.colTap=RGB(0,255,0);
	m_AxisBottom.colSubTap=RGB(255,255,255);
	m_AxisBottom.btTapSize=8;
	m_AxisBottom.btSubTapSize=3;
	m_AxisBottom.colTapLabel=RGB(255,255,255);
	m_AxisBottom.colSubTapLabel=RGB(255,255,255);
	m_AxisBottom.bDrawTapLabels=FALSE;
	m_AxisBottom.bDrawSubTabLabels=TRUE;
	m_AxisBottom.btTapLabelFontID=0;
	m_AxisBottom.btSubTapLabelFontID=0;
	m_AxisBottom.btTapLabelSize=20;
	m_AxisBottom.btSubTapLabelSize=15;
	m_AxisBottom.btTabLabelDec=2;
	m_AxisBottom.btSubTabLabelDec=2;

	// Inizializzo griglia

	m_GridX.bEnabled=FALSE;
	m_GridX.bGrid=FALSE;
	m_GridX.bSubGrid=FALSE;
	m_GridX.btAxisID=FMTTRCCTL_AXIS_X;
	m_GridX.bVert=FALSE;
	m_GridX.colGrid=RGB(255,255,0);
	m_GridX.colSubGrid=RGB(220,220,220);
	m_GridX.iGridPenStyle=PS_SOLID;
	m_GridX.iSubGridPenStyle=PS_SOLID;

	m_GridY.bEnabled=FALSE;
	m_GridY.bGrid=FALSE;
	m_GridY.bSubGrid=FALSE;
	m_GridY.btAxisID=FMTTRCCTL_AXIS_LEFT;
	m_GridY.bVert=TRUE;
	m_GridY.colGrid=RGB(255,255,0);
	m_GridY.colSubGrid=RGB(220,220,220);
	m_GridY.iGridPenStyle=PS_SOLID;
	m_GridY.iSubGridPenStyle=PS_SOLID;


	// Carico cursore
/*	HCURSOR hCursor=AfxGetApp()->LoadCursor(IDC_ARROW);*/

}

CFMT_TraceCtrl::~CFMT_TraceCtrl()
{
	DestroyTraces();
	DestroyLines();
}

// =====================================================================================
//	OPERATORI
// =====================================================================================

// =====================================================================================
//	FUNZIONI
// =====================================================================================

// -----------------------------------------------------------------------------------
//	Function:	GetSuperWndProcAddr
// -----------------------------------------------------------------------------------
//	Desc.	:	-
//
//	Return	:	Puntatore alla windows procedure
//	Params	:	-
// -----------------------------------------------------------------------------------

WNDPROC* CFMT_TraceCtrl::GetSuperWndProcAddr()
{
    // Provide a place for MFC's subclassing
    // mechanism to store the super-class pointer
    static WNDPROC NEAR pfnSuper = NULL;
    return &pfnSuper;
}


// -----------------------------------------------------------------------------------
//	Function:	Create
// -----------------------------------------------------------------------------------
//	Desc.	:	Crea la finestra
//
//	Return	:	TRUE = Creazione OK
//	Params	:	dwWndStyle = Windows Style
//				dwTabStyle = FMTableCtrl Style
//				rect = dimensione finestra
//				pParentWnd = finestra padre
//				nID = Windows ID
// -----------------------------------------------------------------------------------

BOOL CFMT_TraceCtrl::Create(DWORD dwWndStyle,
						   DWORD dwTCStyle,const RECT &rect,CWnd *pParentWnd, DWORD dwID)
{
	CString s;
	s.Format("0x%x",dwTCStyle);

	return Create("FMT_TraceCtrl",dwWndStyle,s,rect,pParentWnd,dwID);
}

// -----------------------------------------------------------------------------------
//	Function:	Create
// -----------------------------------------------------------------------------------
//	Desc.	:	Crea la finestra
//
//	Return	:	TRUE = Creazione OK
//	Params	:	dwWndStyle = Windows Style
//				dwTabStyle = FMTableCtrl Style
//				rect = dimensione finestra
//				pParentWnd = finestra padre
//				nID = Windows ID
// -----------------------------------------------------------------------------------

BOOL CFMT_TraceCtrl::Create(CString sClassName, DWORD dwWndStyle,
						   CString sCaption,const RECT &rect,CWnd *pParentWnd, DWORD dwID)
{
	// Forzo la creazione con flag local create
	CString sTempCaption="#"+sCaption;

	// Creazione finestra

	HWND hWnd=::CreateWindow(sClassName,sTempCaption,dwWndStyle,
		rect.left,rect.top,rect.right-rect.left,rect.bottom-rect.top,pParentWnd->m_hWnd,
		(HMENU)dwID,AfxGetInstanceHandle(),NULL);

	if (!SubclassWindow(hWnd))
		return FALSE;

	InitControl(sCaption);

	return TRUE;
}

// -----------------------------------------------------------------------------------
//	Function:	InitControl
// -----------------------------------------------------------------------------------
//	Desc.	:	Inizializza controllo
//
//	Return	:	-
//	Params	:	sCaption = caption params
//				
//	Formato sCaption:
//	
//	1		-	DWORD		-	TC Style
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::InitControl(CString sCaption)
{
	CString s;
	int iTemp;
	DWORD dwTCStyle;
	DWORD dwFMTStyle;

	// Alloco font di default
	CFont f;
	f.CreatePointFont(100,"MS Sanserif");
	InsertFont(0,&f);

	// ----- Estrae i parametri dal caption -----------------------------------------------
	
	// Estrae lo stile TC
	if (GetFirstParam(sCaption,&iTemp))	
	{
		dwTCStyle=(DWORD)iTemp;
	}
	else dwTCStyle=0;

	// Estrae lo stile FMT
	if (GetNextParam(sCaption,&iTemp))	
	{
		dwFMTStyle=(DWORD)iTemp;
	}
	else dwFMTStyle=FMTWND_SOFTSUNKEN_BORDER|FMTWND_COLOR_BACKGROUND;

	// ----- Atre impostazioni -----------------------------------

	// Imposta lo stile del pulsante
	m_dwTCStyle=dwTCStyle;

	SetFMTStyle(dwFMTStyle);

	CalcRects();
}

// -----------------------------------------------------------------------------------
//	Function:	ModifyTCStyle
// -----------------------------------------------------------------------------------
//	Desc.	:	Modifica lo stile del controllo
//
//	Return	:	-
//	Params	:	dwDelStyle = stile da rimuovere
//				dwInsStyle = stile da inserire
// -----------------------------------------------------------------------------------

/*void CFMT_TraceCtrl::ModifyTCStyle(DWORD dwDelStyle, DWORD dwInsStyle)
{
	ASSERT(::IsWindow(m_hWnd)); 

	::SendMessage(m_hWnd, FMTMSC_MODIFYSTYLE_MESS, (UINT)dwDelStyle, (long)dwInsStyle); 
}*/

// -----------------------------------------------------------------------------------
//	Function:	SetTCStyle
// -----------------------------------------------------------------------------------
//	Desc.	:	Modifica lo stile del controllo
//
//	Return	:	-
//	Params	:	dwTCStyle = nuovo stile
// -----------------------------------------------------------------------------------

/*void CFMT_TraceCtrl::SetTCStyle(DWORD dwTCStyle)
{
	ASSERT(::IsWindow(m_hWnd)); 

	::SendMessage(m_hWnd, FMTMSC_SETSTYLE_MESS, 0, (long)dwMSCStyle); 
}*/

// -----------------------------------------------------------------------------------
//	Function:	GetTCStyle
// -----------------------------------------------------------------------------------
//	Desc.	:	Ritorna lo stile del controllo
//
//	Return	:	-
//	Params	:	dwTCStyle = nuovo stile
// -----------------------------------------------------------------------------------

/*DWORD CFMT_TraceCtrl::GetTCStyle()
{
	ASSERT(::IsWindow(m_hWnd)); 

	DWORD dwRet=0;

	::SendMessage(m_hWnd, FMTMSC_GETSTYLE_MESS, 0, (long)&dwRet); 

	return dwRet;
}*/

// -----------------------------------------------------------------------------------
//	Function:	SendSetCaptureMess
// -----------------------------------------------------------------------------------
//	Desc.	:	invia un messaggio FMCONTROLS_SETCAPTURE_MESS
//
//	Return	:	risultato messaggio di notifica
//	Params	:	p = punto di azione mouse
// -----------------------------------------------------------------------------------

/**LRESULT CFMT_TraceCtrl::SendSetCaptureMess(CPoint p)
{
	SFMT_Control_Notify param;
	param.hdr.code=FMTMSC_SETCAPTURE_MESS;
	param.hdr.hwndFrom=m_hWnd;
	param.hdr.idFrom=0;
	param.point=p;
	param.dwFlags=(DWORD)m_btOwnState;
	param.wVKey=0;
	param.wVKeySpecial=0;
	param.dwStatus=m_dwUserState;

	if (GetParent()!=NULL)
	{
		return ::SendMessage(GetParent()->m_hWnd,WM_NOTIFY,
			GetDlgCtrlID(),(long)(&param));
	}

	return 0;
}*/



// -----------------------------------------------------------------------------------
//	Function:	DestroyWindow
// -----------------------------------------------------------------------------------
//	Desc.	:	Distrugge la finestra
//
//	Return	:	-
//	Params	:	-
// -----------------------------------------------------------------------------------

BOOL CFMT_TraceCtrl::DestroyWindow() 
{

	return TRUE;
}

// -----------------------------------------------------------------------------------
//	Function:	DestroyTraces
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::DestroyTraces()
{
	DWORD k;
	SFMT_TraceCtrlData *pData;

	m_Traces.ToStart();
	for (k=0;k<!m_Traces;k++)
	{
		pData=m_Traces>>1;
		delete pData;
	}

	m_Traces.DeleteAll();
}

// -----------------------------------------------------------------------------------
//	Function:	DestroyLines
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::DestroyLines()
{
	DWORD k;
	SFMT_TraceCtrlLine *pLine;

	m_Lines.ToStart();
	for (k=0;k<!m_Lines;k++)
	{
		pLine=m_Lines>>1;
		delete pLine;
	}

	m_Lines.DeleteAll();
}

// -----------------------------------------------------------------------------------
//	Function:	CalcRects
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::CalcRects() 
{
	CRect cr;
	
	GetClientRect(&cr);

	m_TraceRect.left=cr.left+50;
	m_TraceRect.right=cr.right-40;
	m_TraceRect.top=cr.top+30;
	m_TraceRect.bottom=cr.bottom-40;
}

// -----------------------------------------------------------------------------------
//	Function:	GetAxis
// -----------------------------------------------------------------------------------

SFMT_TraceCtrlAxis* CFMT_TraceCtrl::GetAxis(DWORD dwID)
{
	SFMT_TraceCtrlAxis *pA=NULL;

	switch (dwID)
	{
	case FMTTRCCTL_AXIS_X:
		pA=&m_AxisX;
	break;

	case FMTTRCCTL_AXIS_Y:
		pA=&m_AxisY;
	break;

	case FMTTRCCTL_AXIS_LEFT:
		pA=&m_AxisLeft;
	break;

	case FMTTRCCTL_AXIS_TOP:
		pA=&m_AxisTop;
	break;

	case FMTTRCCTL_AXIS_RIGHT:
		pA=&m_AxisRight;
	break;

	case FMTTRCCTL_AXIS_BOTTOM:
		pA=&m_AxisBottom;
	break;
	}

	return pA;
}


// -----------------------------------------------------------------------------------
//	Function:	DrawAxis
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::DrawAxis(CDC *pDC,BYTE btAxisID)
{
	SFMT_TraceCtrlAxis *pA=GetAxis(btAxisID);

	if (pA->bVert)
		DrawAxisVert(pDC,btAxisID,pA);
	else DrawAxisHorz(pDC,btAxisID,pA);
}

// -----------------------------------------------------------------------------------
//	Function:	DrawAxisVert
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::DrawAxisVert(CDC *pDC,BYTE btAxisID,SFMT_TraceCtrlAxis *pA)
{
	// Determina se eseguire o no la visualizzazione
	if (!pA->bEnabled)
		return;

	int iTemp;

	iTemp=m_TraceRect.right-m_iPX;
	if ((btAxisID==FMTTRCCTL_AXIS_Y) &&
		
		((iTemp<m_TraceRect.left) || (iTemp>m_TraceRect.right)))
		return;

	// Crea oggetti grafici per il disegno
	CPen	*pPen;
	CPen	*pOldPen;

	int		iPos;

	// Disegno asse -------------------------------------------

	pPen=new CPen;
	pPen->CreatePen(PS_SOLID,1,pA->colAxis);

	pOldPen=pDC->SelectObject(pPen);

	switch (btAxisID)
	{
	case FMTTRCCTL_AXIS_Y:
		iPos=m_TraceRect.left+m_iPX;
	break;

	case FMTTRCCTL_AXIS_LEFT:
		iPos=m_TraceRect.left;
	break;

	case FMTTRCCTL_AXIS_RIGHT:
		iPos=m_TraceRect.right;
	break;
	}

	pDC->MoveTo(iPos,m_TraceRect.top);
	pDC->LineTo(iPos,m_TraceRect.bottom);
	
	pDC->SelectObject(pOldPen);
	delete pPen;
}

// -----------------------------------------------------------------------------------
//	Function:	DrawAxisHorz
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::DrawAxisHorz(CDC *pDC,BYTE btAxisID,SFMT_TraceCtrlAxis *pA)
{
	// Determina se eseguire o no la visualizzazione
	if (!pA->bEnabled)
		return;

	int iTemp;

	iTemp=m_TraceRect.bottom-m_iPY;
	if ((btAxisID==FMTTRCCTL_AXIS_X) &&
		
		((iTemp<m_TraceRect.top) || (iTemp>m_TraceRect.bottom)))
		return;

	// Crea oggetti grafici per il disegno
	CPen	*pPen;
	CPen	*pOldPen;

	int		iPos;

	// Disegno asse -------------------------------------------

	pPen=new CPen;
	pPen->CreatePen(PS_SOLID,1,pA->colAxis);

	pOldPen=pDC->SelectObject(pPen);

	switch (btAxisID)
	{
	case FMTTRCCTL_AXIS_X:
		iPos=m_TraceRect.bottom-m_iPY;
	break;

	case FMTTRCCTL_AXIS_TOP:
		iPos=m_TraceRect.top;
	break;

	case FMTTRCCTL_AXIS_BOTTOM:
		iPos=m_TraceRect.bottom;
	break;
	}

	pDC->MoveTo(m_TraceRect.left,iPos);
	pDC->LineTo(m_TraceRect.right,iPos);
	
	pDC->SelectObject(pOldPen);
	delete pPen;
}

// -----------------------------------------------------------------------------------
//	Function:	DrawAxisTaps
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::DrawAxisTaps(CDC *pDC,BYTE btAxisID)
{
	SFMT_TraceCtrlAxis *pA=GetAxis(btAxisID);

	if (pA->bVert)
		DrawAxisTapsVert(pDC,btAxisID,pA);
	else DrawAxisTapsHorz(pDC,btAxisID,pA);
}

// -----------------------------------------------------------------------------------
//	Function:	DrawAxisTapsVert
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::DrawAxisTapsVert(CDC *pDC,BYTE btAxisID,SFMT_TraceCtrlAxis *pA)
{
	// Determina se eseguire o no la visualizzazione
	if (!pA->bEnabled)
		return;

	int iTemp;

	iTemp=m_TraceRect.right-m_iPX;
	if ((btAxisID==FMTTRCCTL_AXIS_Y) &&
		((iTemp<m_TraceRect.left) || (iTemp>m_TraceRect.right)))
	return;

	// Crea oggetti grafici per il disegno

	CPen	*pPen;
	CPen	*pSubPen;
	CPen	*pOldPen;
	BOOL	bAgain;
	double	dTemp;
	int		iPos;
	double	dPitch;
	double	dOff;
	DWORD	k;


	// Disegno asse -------------------------------------------

	switch (btAxisID)
	{
	case FMTTRCCTL_AXIS_Y:
		iPos=m_TraceRect.left+m_iPX;
	break;

	case FMTTRCCTL_AXIS_LEFT:
		iPos=m_TraceRect.left;
	break;

	case FMTTRCCTL_AXIS_RIGHT:
		iPos=m_TraceRect.right;
	break;
	}

	// Disegno subtaps ---------------------------------------------

	dPitch=(pA->dTapPitch*pA->dScale)/(double)pA->dwSubTapNum;
	dOff=m_iPY+pA->dOffset*m_dSY;

	pPen=new CPen;
	pPen->CreatePen(PS_SOLID,1,pA->colTap);

	pSubPen=new CPen;
	pSubPen->CreatePen(PS_SOLID,1,pA->colSubTap);

	pOldPen=pDC->SelectObject(pPen);
	
	bAgain=TRUE;
	dTemp=0;

	if (dOff<0)
	{
		dTemp=(double)(-dOff)/(dPitch*m_dSY);
		iTemp=(int)dTemp;
		k=iTemp+1;
		dTemp=k*dPitch;
	}
	else
	{
		dTemp=0;
		k=0;
	}

	while (bAgain)
	{
		iTemp=m_TraceRect.bottom-(int)(dOff+m_dSY*dTemp/*+(double)m_TraceRect.top*/);

		if (iTemp<m_TraceRect.top)
		{
			bAgain=FALSE;
		}
		else
		{
			if ((k % pA->dwSubTapNum)==0)
			{
				if (pA->bDrawTaps)
				{
					pDC->SelectObject(pPen);

					pDC->MoveTo(iPos+pA->btTapSize,iTemp);
					pDC->LineTo(iPos-pA->btTapSize-1,iTemp);
				}
				else if (pA->bDrawSubTaps)
				{
					pDC->SelectObject(pSubPen);

					pDC->MoveTo(iPos+pA->btSubTapSize,iTemp);
					pDC->LineTo(iPos-pA->btSubTapSize-1,iTemp);
				}
			}
			else
			{
				if (pA->bDrawSubTaps)
				{
					pDC->SelectObject(pSubPen);

					pDC->MoveTo(iPos+pA->btSubTapSize,iTemp);
					pDC->LineTo(iPos-pA->btSubTapSize-1,iTemp);
				}
			}
		}

		dTemp+=dPitch;
		k++;
	}

	bAgain=TRUE;
	dTemp=0;

	if (dOff>m_TraceRect.Height())
	{
		dTemp=(double)(dOff-m_TraceRect.Height())/(dPitch*m_dSY);
		iTemp=(int)dTemp+1;
		dTemp=-(iTemp*dPitch);
		k=iTemp;
	}
	else
	{
		dTemp=0;
		k=0;
	}

	while (bAgain)
	{
		iTemp=m_TraceRect.bottom-(int)(dOff+m_dSY*dTemp/*+(double)m_TraceRect.top*/);

		if (iTemp>m_TraceRect.bottom)
		{
			bAgain=FALSE;
		}
		else
		{
			if ((k % pA->dwSubTapNum)==0)
			{
				if (pA->bDrawTaps)
				{
					pDC->SelectObject(pPen);

					pDC->MoveTo(iPos+pA->btTapSize,iTemp);
					pDC->LineTo(iPos-pA->btTapSize-1,iTemp);
				}
				else if (pA->bDrawSubTaps)
				{
					pDC->SelectObject(pSubPen);

					pDC->MoveTo(iPos+pA->btSubTapSize,iTemp);
					pDC->LineTo(iPos-pA->btSubTapSize-1,iTemp);
				}
			}
			else
			{
				if (pA->bDrawSubTaps)
				{
					pDC->SelectObject(pSubPen);

					pDC->MoveTo(iPos+pA->btSubTapSize,iTemp);
					pDC->LineTo(iPos-pA->btSubTapSize-1,iTemp);
				}
			}

		}

		dTemp-=dPitch;
		k++;
	}

	pDC->SelectObject(pOldPen);
	delete pPen;
	delete pSubPen;
}

// -----------------------------------------------------------------------------------
//	Function:	DrawAxisTapsHorz
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::DrawAxisTapsHorz(CDC *pDC,BYTE btAxisID,SFMT_TraceCtrlAxis *pA)
{
	// Determina se eseguire o no la visualizzazione
	if (!pA->bEnabled)
		return;

	int iTemp;

	iTemp=m_TraceRect.bottom-m_iPY;
	if ((btAxisID==FMTTRCCTL_AXIS_X) &&
		((iTemp<m_TraceRect.top) || (iTemp>m_TraceRect.bottom)))
	return;

	// Crea oggetti grafici per il disegno

	CPen	*pPen;
	CPen	*pSubPen;
	CPen	*pOldPen;
	BOOL	bAgain;
	double	dTemp;
	int		iPos;
	double	dPitch;
	double	dOff;
	DWORD	k;

	// Disegno asse -------------------------------------------

	switch (btAxisID)
	{
	case FMTTRCCTL_AXIS_X:
		iPos=m_TraceRect.bottom-m_iPY;
	break;

	case FMTTRCCTL_AXIS_TOP:
		iPos=m_TraceRect.top;
	break;

	case FMTTRCCTL_AXIS_BOTTOM:
		iPos=m_TraceRect.bottom;
	break;
	}

	// Disegno subtaps ---------------------------------------------

	dPitch=(pA->dTapPitch*pA->dScale)/(double)pA->dwSubTapNum;
	dOff=(double)m_iPX+pA->dOffset*m_dSX;

	pPen=new CPen;
	pPen->CreatePen(PS_SOLID,1,pA->colTap);

	pSubPen=new CPen;
	pSubPen->CreatePen(PS_SOLID,1,pA->colSubTap);

	pOldPen=pDC->SelectObject(pPen);
	
	bAgain=TRUE;
	dTemp=0;

	if (dOff<0)
	{
		dTemp=(double)(-dOff)/(dPitch*m_dSX);
		iTemp=(int)dTemp;
		k=iTemp+1;
		dTemp=k*dPitch;
	}
	else
	{
		dTemp=0;
		k=0;
	}

	while (bAgain)
	{
		iTemp=(int)((double)dOff+m_dSX*dTemp+(double)m_TraceRect.left);

		if (iTemp>m_TraceRect.right)
		{
			bAgain=FALSE;
		}
		else
		{
			if ((k % pA->dwSubTapNum)==0)
			{
				if (pA->bDrawTaps)
				{
					pDC->SelectObject(pPen);

					pDC->MoveTo(iTemp,iPos+pA->btTapSize);
					pDC->LineTo(iTemp,iPos-pA->btTapSize-1);
				}
				else if (pA->bDrawSubTaps)
				{
					pDC->SelectObject(pSubPen);

					pDC->MoveTo(iTemp,iPos+pA->btSubTapSize);
					pDC->LineTo(iTemp,iPos-pA->btSubTapSize-1);
				}
			}
			else
			{
				if (pA->bDrawSubTaps)
				{
					pDC->SelectObject(pSubPen);

					pDC->MoveTo(iTemp,iPos+pA->btSubTapSize);
					pDC->LineTo(iTemp,iPos-pA->btSubTapSize-1);
				}
			}
		}

		dTemp+=dPitch;
		k++;
	}

	bAgain=TRUE;
	dTemp=0;

	if (dOff>m_TraceRect.Width())
	{
		dTemp=(double)(dOff-m_TraceRect.Width())/(dPitch*m_dSX);
		iTemp=(int)dTemp+1;
		dTemp=-(iTemp*dPitch);
		k=iTemp;
	}
	else
	{
		dTemp=0;
		k=0;
	}

	while (bAgain)
	{
		iTemp=(int)(dOff+m_dSX*dTemp+(double)m_TraceRect.left);

		if (iTemp<m_TraceRect.left)
		{
			bAgain=FALSE;
		}
		else
		{
			if ((k % pA->dwSubTapNum)==0)
			{
				if (pA->bDrawTaps)
				{
					pDC->SelectObject(pPen);

					pDC->MoveTo(iTemp,iPos+pA->btTapSize);
					pDC->LineTo(iTemp,iPos-pA->btTapSize-1);
				}
				else if (pA->bDrawSubTaps)
				{
					pDC->SelectObject(pSubPen);

					pDC->MoveTo(iTemp,iPos+pA->btSubTapSize);
					pDC->LineTo(iTemp,iPos-pA->btSubTapSize-1);
				}
			}
			else
			{
				if (pA->bDrawSubTaps)
				{
					pDC->SelectObject(pSubPen);

					pDC->MoveTo(iTemp,iPos+pA->btSubTapSize);
					pDC->LineTo(iTemp,iPos-pA->btSubTapSize-1);
				}
			}

		}

		dTemp-=dPitch;
		k++;
	}	

	pDC->SelectObject(pOldPen);
	delete pPen;
	delete pSubPen;
}

// -----------------------------------------------------------------------------------
//	Function:	DrawAxisLabels
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::DrawAxisLabels(CDC *pDC,BYTE btAxisID)
{
	SFMT_TraceCtrlAxis *pA=GetAxis(btAxisID);

	if (pA->bVert)
		DrawAxisLabelsVert(pDC,btAxisID,pA);
	else DrawAxisLabelsHorz(pDC,btAxisID,pA);
}

// -----------------------------------------------------------------------------------
//	Function:	DrawAxisLabelsVert
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::DrawAxisLabelsVert(CDC *pDC,BYTE btAxisID,SFMT_TraceCtrlAxis *pA)
{
	// Determina se eseguire o no la visualizzazione
	if (!pA->bEnabled)
		return;

	int iTemp;

	iTemp=m_TraceRect.right-m_iPX;
	if ((btAxisID==FMTTRCCTL_AXIS_Y) &&
		((iTemp<m_TraceRect.left) || (iTemp>m_TraceRect.right)))
	return;

	BOOL	bAgain;
	double	dTemp;
	int		iPos;
	double	dPitch;
	double	dOff;
	CRect	r,rs;
	CString	s;
	CString	sft,sfst;
	BYTE	btAlign;

	// Crea oggetti grafici per il disegno

	switch (btAxisID)
	{
	case FMTTRCCTL_AXIS_Y:
		iPos=m_TraceRect.left+m_iPX;

		r.left=iPos+(pA->btTapSize)+2;
		r.right=r.left+pA->btTapLabelSize;

		rs.left=iPos+(pA->btSubTapSize)+2;
		rs.right=rs.left+pA->btSubTapLabelSize;

		btAlign=DT_LEFT;
	break;

	case FMTTRCCTL_AXIS_LEFT:
		iPos=m_TraceRect.left;

		r.right=iPos-(pA->btTapSize)-2;
		r.left=r.left-pA->btTapLabelSize;
		rs.right=iPos-(pA->btSubTapSize)-2;
		rs.left=rs.right-pA->btSubTapLabelSize;

		btAlign=DT_RIGHT;
	break;

	case FMTTRCCTL_AXIS_RIGHT:
		iPos=m_TraceRect.right;

		r.left=iPos+(pA->btTapSize)+2;
		r.right=r.left+pA->btTapLabelSize;
		rs.left=iPos+(pA->btSubTapSize)+2;
		rs.right=rs.left+pA->btSubTapLabelSize;

		btAlign=DT_LEFT;
	break;
	}

	// Disegno labels ---------------------------------------------

	dPitch=(pA->dTapPitch*pA->dScale)/(double)pA->dwSubTapNum;
	dOff=m_iPY+pA->dOffset*m_dSY;

	sft.Format("%%.%df",pA->btTabLabelDec);
	sfst.Format("%%.%df",pA->btSubTabLabelDec);

	bAgain=TRUE;
	dTemp=0;

	DWORD k;

	if (dOff<0)
	{
		dTemp=(double)(-dOff)/(dPitch*m_dSY);
		iTemp=(int)dTemp;
		k=iTemp+1;
		dTemp=k*dPitch;
	}
	else
	{
		dTemp=0;

		k=0;
	}

	while (bAgain)
	{
		iTemp=m_TraceRect.bottom-(int)(dOff+m_dSY*dTemp/*+(double)m_TraceRect.top*/);

		if (pA->bDrawSubTabLabels)
		{
			rs.top=(int)(iTemp-dPitch*m_dSY/2)+1;
			rs.bottom=(int)(iTemp+dPitch*m_dSY/2)-1;

			r.top=rs.top;
			r.bottom=rs.bottom;
		}
		else
		{
			r.top=(int)(iTemp-dPitch*pA->dwSubTapNum*m_dSY/2)+1;
			r.bottom=(int)(iTemp+dPitch*(double)pA->dwSubTapNum*m_dSY/2)-1;
		}

		if (iTemp<m_TraceRect.top)
		{
			bAgain=FALSE;
		}
		else
		{
			if ((k % pA->dwSubTapNum)==0)
			{
				if (pA->bDrawTapLabels)
				{
					pDC->SetBkMode(TRANSPARENT);
					pDC->SetTextColor(pA->colTapLabel);
					pDC->SelectObject(GetFont(pA->btTapLabelFontID));

					s.Format(sft,dTemp);
					pDC->DrawText(s,&r,DT_VCENTER|btAlign|DT_SINGLELINE);
				}
				else if (pA->bDrawSubTabLabels)
				{
					pDC->SetBkMode(TRANSPARENT);
					pDC->SetTextColor(pA->colSubTapLabel);
					pDC->SelectObject(GetFont(pA->btSubTapLabelFontID));

					s.Format(sfst,dTemp);
					pDC->DrawText(s,&rs,DT_VCENTER|btAlign|DT_SINGLELINE);
				}
			}
			else
			{
				if (pA->bDrawSubTabLabels)
				{
					pDC->SetBkMode(TRANSPARENT);
					pDC->SetTextColor(pA->colSubTapLabel);
					pDC->SelectObject(GetFont(pA->btSubTapLabelFontID));

					s.Format(sfst,dTemp);
					pDC->DrawText(s,&rs,DT_VCENTER|btAlign|DT_SINGLELINE);
				}
			}
		}

		dTemp+=dPitch;
		k++;
	}

	bAgain=TRUE;
	dTemp=0;

	if (dOff>m_TraceRect.Height())
	{
		dTemp=(double)(dOff-m_TraceRect.Height())/(dPitch*m_dSY);
		iTemp=(int)dTemp+1;
		dTemp=-(iTemp*dPitch);
		k=iTemp;
	}
	else
	{
		dTemp=0;
		k=0;
	}

	while (bAgain)
	{
		iTemp=m_TraceRect.bottom-(int)(dOff+m_dSY*dTemp/*+(double)m_TraceRect.top*/);

		if (pA->bDrawSubTabLabels)
		{
			rs.top=(int)(iTemp-dPitch*m_dSY/2)+1;
			rs.bottom=(int)(iTemp+dPitch*m_dSY/2)-1;

			r.top=rs.top;
			r.bottom=rs.bottom;

		}
		else
		{
			r.top=(int)(iTemp-dPitch*pA->dwSubTapNum*m_dSY/2)+1;
			r.bottom=(int)(iTemp+dPitch*(double)pA->dwSubTapNum*m_dSY/2)-1;
		}

		if (iTemp>m_TraceRect.bottom)
		{
			bAgain=FALSE;
		}
		else
		{
			if ((k % pA->dwSubTapNum)==0)
			{
				if (pA->bDrawTapLabels)
				{
					pDC->SetBkMode(TRANSPARENT);
					pDC->SetTextColor(pA->colTapLabel);
					pDC->SelectObject(GetFont(pA->btTapLabelFontID));

					s.Format(sft,dTemp);
					pDC->DrawText(s,&r,DT_VCENTER|btAlign|DT_SINGLELINE);
				}
				else if (pA->bDrawSubTabLabels)
				{
					pDC->SetBkMode(TRANSPARENT);
					pDC->SetTextColor(pA->colSubTapLabel);
					pDC->SelectObject(GetFont(pA->btSubTapLabelFontID));

					s.Format(sfst,dTemp);
					pDC->DrawText(s,&rs,DT_VCENTER|btAlign|DT_SINGLELINE);
				}
			}
			else
			{
				if (pA->bDrawSubTabLabels)
				{
					pDC->SetBkMode(TRANSPARENT);
					pDC->SetTextColor(pA->colSubTapLabel);
					pDC->SelectObject(GetFont(pA->btSubTapLabelFontID));

					s.Format(sfst,dTemp);
					pDC->DrawText(s,&rs,DT_VCENTER|btAlign|DT_SINGLELINE);
				}
			}
		}

		dTemp-=dPitch;
		k++;
	}	
}

// -----------------------------------------------------------------------------------
//	Function:	DrawAxisLabelsHorz
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::DrawAxisLabelsHorz(CDC *pDC,BYTE btAxisID,SFMT_TraceCtrlAxis *pA)
{
	// Determina se eseguire o no la visualizzazione
	if (!pA->bEnabled)
		return;

	int iTemp;

	iTemp=m_TraceRect.bottom-m_iPY;
	if ((btAxisID==FMTTRCCTL_AXIS_X) &&
		((iTemp<m_TraceRect.top) || (iTemp>m_TraceRect.bottom)))
	return;

	BOOL	bAgain;
	double	dTemp;
	int		iPos;
	double	dPitch;
	double	dOff;
	CRect	r,rs;
	CString	s;
	CString	sft,sfst;

	// Crea oggetti grafici per il disegno

	switch (btAxisID)
	{
	case FMTTRCCTL_AXIS_X:
		iPos=m_TraceRect.bottom-m_iPY;
		r.top=iPos+(pA->btTapSize)+2;
		r.bottom=r.top+pA->btTapLabelSize;
		rs.top=iPos+(pA->btSubTapSize)+2;
		rs.bottom=rs.top+pA->btSubTapLabelSize;
	break;

	case FMTTRCCTL_AXIS_TOP:
		iPos=m_TraceRect.top;
		r.bottom=iPos-(pA->btTapSize)-2;
		r.top=r.bottom-pA->btTapLabelSize;
		rs.bottom=iPos-(pA->btSubTapSize)-2;
		rs.top=rs.bottom-pA->btSubTapLabelSize;
	break;

	case FMTTRCCTL_AXIS_BOTTOM:
		iPos=m_TraceRect.bottom;
		r.top=iPos+(pA->btTapSize)+2;
		r.bottom=r.top+pA->btTapLabelSize;
		rs.top=iPos+(pA->btSubTapSize)+2;
		rs.bottom=rs.top+pA->btSubTapLabelSize;
	break;
	}

	// Disegno labels ---------------------------------------------

	dPitch=(pA->dTapPitch*pA->dScale)/(double)pA->dwSubTapNum;
	dOff=m_iPX+pA->dOffset*m_dSX;

	sft.Format("%%.%df",pA->btTabLabelDec);
	sfst.Format("%%.%df",pA->btSubTabLabelDec);

	bAgain=TRUE;
	dTemp=0;

	DWORD k;

	if (dOff<0)
	{
		dTemp=(double)(-dOff)/(dPitch*m_dSX);
		iTemp=(int)dTemp;
		k=iTemp+1;
		dTemp=k*dPitch;
	}
	else
	{
		dTemp=0;

		k=0;
	}

	while (bAgain)
	{
		iTemp=(int)((double)dOff+m_dSX*dTemp+(double)m_TraceRect.left);

		if (pA->bDrawSubTabLabels)
		{
			rs.left=(int)(iTemp-dPitch*m_dSX/2)+1;
			rs.right=(int)(iTemp+dPitch*m_dSX/2)-1;

			r.left=rs.left;
			r.right=rs.right;
		}
		else
		{
			r.left=(int)(iTemp-dPitch*pA->dwSubTapNum*m_dSX/2)+1;
			r.right=(int)(iTemp+dPitch*(double)pA->dwSubTapNum*m_dSX/2)-1;
		}

		if (iTemp>m_TraceRect.right)
		{
			bAgain=FALSE;
		}
		else
		{
			if ((k % pA->dwSubTapNum)==0)
			{
				if (pA->bDrawTapLabels)
				{
					pDC->SetBkMode(TRANSPARENT);
					pDC->SetTextColor(pA->colTapLabel);
					pDC->SelectObject(GetFont(pA->btTapLabelFontID));

					s.Format(sft,dTemp);
					pDC->DrawText(s,&r,DT_VCENTER|DT_CENTER|DT_SINGLELINE);
				}
				else if (pA->bDrawSubTabLabels)
				{
					pDC->SetBkMode(TRANSPARENT);
					pDC->SetTextColor(pA->colSubTapLabel);
					pDC->SelectObject(GetFont(pA->btSubTapLabelFontID));

					s.Format(sfst,dTemp);
					pDC->DrawText(s,&rs,DT_VCENTER|DT_CENTER|DT_SINGLELINE);
				}
			}
			else
			{
				if (pA->bDrawSubTabLabels)
				{
					pDC->SetBkMode(TRANSPARENT);
					pDC->SetTextColor(pA->colSubTapLabel);
					pDC->SelectObject(GetFont(pA->btSubTapLabelFontID));

					s.Format(sfst,dTemp);
					pDC->DrawText(s,&rs,DT_VCENTER|DT_CENTER|DT_SINGLELINE);
				}
			}
		}

		dTemp+=dPitch;
		k++;
	}

	bAgain=TRUE;
	dTemp=0;

	if (dOff>m_TraceRect.Width())
	{
		dTemp=(double)(dOff-m_TraceRect.Width())/(dPitch*m_dSX);
		iTemp=(int)dTemp+1;
		dTemp=-(iTemp*dPitch);
		k=iTemp;
	}
	else
	{
		dTemp=0;
		k=0;
	}

	while (bAgain)
	{
		iTemp=(int)(dOff+m_dSX*dTemp+(double)m_TraceRect.left);

		if (pA->bDrawSubTabLabels)
		{
			rs.left=(int)(iTemp-dPitch*m_dSX/2)+1;
			rs.right=(int)(iTemp+dPitch*m_dSX/2)-1;

			r.left=rs.left;
			r.right=rs.right;

		}
		else
		{
			r.left=(int)(iTemp-dPitch*pA->dwSubTapNum*m_dSX/2)+1;
			r.right=(int)(iTemp+dPitch*(double)pA->dwSubTapNum*m_dSX/2)-1;
		}

		if (iTemp<m_TraceRect.left)
		{
			bAgain=FALSE;
		}
		else
		{
			if ((k % pA->dwSubTapNum)==0)
			{
				if (pA->bDrawTapLabels)
				{
					pDC->SetBkMode(TRANSPARENT);
					pDC->SetTextColor(pA->colTapLabel);
					pDC->SelectObject(GetFont(pA->btTapLabelFontID));

					s.Format(sft,dTemp);
					pDC->DrawText(s,&r,DT_VCENTER|DT_CENTER|DT_SINGLELINE);
				}
				else if (pA->bDrawSubTabLabels)
				{
					pDC->SetBkMode(TRANSPARENT);
					pDC->SetTextColor(pA->colSubTapLabel);
					pDC->SelectObject(GetFont(pA->btSubTapLabelFontID));

					s.Format(sfst,dTemp);
					pDC->DrawText(s,&rs,DT_VCENTER|DT_CENTER|DT_SINGLELINE);
				}
			}
			else
			{
				if (pA->bDrawSubTabLabels)
				{
					pDC->SetBkMode(TRANSPARENT);
					pDC->SetTextColor(pA->colSubTapLabel);
					pDC->SelectObject(GetFont(pA->btSubTapLabelFontID));

					s.Format(sfst,dTemp);
					pDC->DrawText(s,&rs,DT_VCENTER|DT_CENTER|DT_SINGLELINE);
				}
			}
		}

		dTemp-=dPitch;
		k++;
	}	
}


// -----------------------------------------------------------------------------------
//	Function:	DrawBorderBackground
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::DrawBorderBackground(CDC *pDC)
{
	// Fill border area background
	if ((m_dwTCStyle & FMTTRACECTRL_TRASPBORDERAREA)==0)
	{
		CRect cr,r;
		GetClientRect(&cr);

		r.left=cr.left;
		r.top=cr.top;
		r.right=cr.right;
		r.bottom=m_TraceRect.top;

		pDC->FillSolidRect(&r,m_colBorderBack);

		r.left=cr.left;
		r.top=m_TraceRect.top;
		r.right=m_TraceRect.left;
		r.bottom=cr.bottom;

		pDC->FillSolidRect(&r,m_colBorderBack);

		r.left=m_TraceRect.left;
		r.top=m_TraceRect.bottom;
		r.right=cr.right;
		r.bottom=cr.bottom;

		pDC->FillSolidRect(&r,m_colBorderBack);

		r.left=m_TraceRect.right;
		r.top=m_TraceRect.top;
		r.right=cr.right;
		r.bottom=m_TraceRect.bottom;

		pDC->FillSolidRect(&r,m_colBorderBack);
	}
}

// -----------------------------------------------------------------------------------
//	Function:	DrawTraceBackground
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::DrawTraceBackground(CDC *pDC)
{
	// Fill trace area background
	if ((m_dwTCStyle & FMTTRACECTRL_TRASPTRACEAREA)==0)
	{
		pDC->FillSolidRect(&m_TraceRect,m_colTraceBack);
	}
}


// -----------------------------------------------------------------------------------
//	Function:	DrawAxisText
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::DrawAxisText(CDC *pDC,BYTE btAxisID)
{
	SFMT_TraceCtrlAxis *pA=GetAxis(btAxisID);

	if (pA->bVert)
		DrawAxisTextVert(pDC,btAxisID,pA);
	else DrawAxisTextHorz(pDC,btAxisID,pA);
}

// -----------------------------------------------------------------------------------
//	Function:	DrawAxisTextHorz
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::DrawAxisTextHorz(CDC *pDC,BYTE btAxisID,SFMT_TraceCtrlAxis *pA)
{
	if (!pA->bDrawText)
		return;

	CRect	r;
	int		iPos;

	switch (btAxisID)
	{
	case FMTTRCCTL_AXIS_X:
		iPos=m_TraceRect.bottom-m_iPY;
	break;

	case FMTTRCCTL_AXIS_TOP:
		iPos=m_TraceRect.top;
	break;

	case FMTTRCCTL_AXIS_BOTTOM:
		iPos=m_TraceRect.bottom;
	break;

	}

	switch (pA->btLabelPos)
	{
	case 0:
		r.bottom=iPos-3;
		r.top=r.bottom-pA->szLabelSize.cy;
		r.left=m_TraceRect.left+2;
		r.right=r.left+pA->szLabelSize.cx;
	break;

	case 1:
		r.bottom=iPos-3;
		r.top=r.bottom-pA->szLabelSize.cy;
		r.left=m_TraceRect.left+(m_TraceRect.Width()-pA->szLabelSize.cx)/2;
		r.right=r.left+pA->szLabelSize.cx;
	break;

	case 2:
		r.bottom=iPos-3;
		r.top=r.bottom-pA->szLabelSize.cy;
		r.right=m_TraceRect.right-2;
		r.left=r.right-pA->szLabelSize.cx;
	break;

	case 3:
		r.top=iPos+3;
		r.bottom=r.top+pA->szLabelSize.cy;
		r.left=m_TraceRect.left+2;
		r.right=r.left+pA->szLabelSize.cx;
	break;

	case 4:
		r.top=iPos+3;
		r.bottom=r.top+pA->szLabelSize.cy;
		r.left=m_TraceRect.left+(m_TraceRect.Width()-pA->szLabelSize.cx)/2;
		r.right=r.left+pA->szLabelSize.cx;
	break;

	case 5:
		r.top=iPos+3;
		r.bottom=r.top+pA->szLabelSize.cy;
		r.right=m_TraceRect.right-2;
		r.left=r.right-pA->szLabelSize.cx;
	break;
	}

	pDC->SetBkMode(TRANSPARENT);

	if (!pA->bLabelTransp)
		pDC->FillSolidRect(r,pA->colBackLabel);

	pDC->SetTextColor(pA->colLabel);
	pDC->SelectObject(GetFont(pA->btLabelFontID));

	pDC->DrawText(pA->sLabel,&r,DT_VCENTER|DT_CENTER|DT_SINGLELINE);

}

// -----------------------------------------------------------------------------------
//	Function:	DrawAxisTextVert
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::DrawAxisTextVert(CDC *pDC,BYTE btAxisID,SFMT_TraceCtrlAxis *pA)
{
	if (!pA->bDrawText)
		return;

	CRect	r;
	int		iPos;

	switch (btAxisID)
	{
	case FMTTRCCTL_AXIS_Y:
		iPos=m_TraceRect.left+m_iPX;
	break;

	case FMTTRCCTL_AXIS_LEFT:
		iPos=m_TraceRect.left;
	break;

	case FMTTRCCTL_AXIS_RIGHT:
		iPos=m_TraceRect.right;
	break;

	}

	switch (pA->btLabelPos)
	{
	case 0:
		r.right=iPos-3;
		r.left=r.right-pA->szLabelSize.cx;
		r.top=m_TraceRect.top+2;
		r.bottom=r.top+pA->szLabelSize.cy;
	break;

	case 1:
		r.right=iPos-3;
		r.left=r.right-pA->szLabelSize.cx;
		r.top=m_TraceRect.top+(m_TraceRect.Height()-pA->szLabelSize.cy)/2;
		r.bottom=r.top+pA->szLabelSize.cy;
	break;

	case 2:
		r.right=iPos-3;
		r.left=r.right-pA->szLabelSize.cx;
		r.bottom=m_TraceRect.bottom-2;
		r.top=r.bottom-pA->szLabelSize.cy;
	break;

	case 3:
		r.left=iPos+3;
		r.right=r.left+pA->szLabelSize.cx;
		r.top=m_TraceRect.top+2;
		r.bottom=r.top+pA->szLabelSize.cy;
	break;

	case 4:
		r.left=iPos+3;
		r.right=r.left+pA->szLabelSize.cx;
		r.top=m_TraceRect.top+(m_TraceRect.Height()-pA->szLabelSize.cy)/2;
		r.bottom=r.top+pA->szLabelSize.cy;
	break;

	case 5:
		r.left=iPos+3;
		r.right=r.left+pA->szLabelSize.cx;
		r.bottom=m_TraceRect.bottom-2;
		r.top=r.bottom-pA->szLabelSize.cy;
	break;
	}

	pDC->SetBkMode(TRANSPARENT);

	if (!pA->bLabelTransp)
		pDC->FillSolidRect(r,pA->colBackLabel);

	pDC->SetTextColor(pA->colLabel);
	pDC->SelectObject(GetFont(pA->btLabelFontID));

	pDC->DrawText(pA->sLabel,&r,DT_VCENTER|DT_CENTER|DT_SINGLELINE);
}

// -----------------------------------------------------------------------------------
//	Function:	DrawTraceCouplesData
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::DrawTraceCouplesData(CDC *pDC,BYTE btMode,SFMT_TraceCtrlData *pData)
{
	DWORD k;
	int x,y;
	int xo,yo;
	BOOL bFirst;
	CFMT_DoublePoint *pD;
	CPen *pPen;
	CPen *pOldPen;

	pD=(CFMT_DoublePoint*)pData->pData;

	pPen=new CPen;
	pPen->CreatePen(pData->iPenStyle,pData->btPenSize,pData->colTrace);

	pOldPen=pDC->SelectObject(pPen);

	bFirst=TRUE;
	for (k=0;k<pData->dwSize;k++)
	{
		x=(int)(m_TraceRect.left+m_iPX+pD[k].GetX()*m_dSX);
		y=(int)(m_TraceRect.bottom-m_iPY-pD[k].GetY()*m_dSY);

		// Disegno segmenti
		if ((btMode & FMTTRCCTL_TRACE_JOIN)>0)
		{
			if (!bFirst)
			{
				pDC->MoveTo(xo,yo);
				pDC->LineTo(x,y);
			}
		}

		// Disegno nodi
		if ((btMode & FMTTRCCTL_TRACE_POINTS)>0)
		{
			if ((x>=m_TraceRect.left) && (x<=m_TraceRect.right) &&
				(y>=m_TraceRect.top) && (y<=m_TraceRect.bottom))
			{
				CRect tr;
				tr.left=x-2;
				tr.top=y-2;
				tr.right=x+3;
				tr.bottom=y+3;
				pDC->FillSolidRect(&tr,pData->colTrace);
			}
		}

		bFirst=FALSE;
		xo=x;
		yo=y;
	}

	pDC->SelectObject(pOldPen);
	delete pPen;
}

// -----------------------------------------------------------------------------------
//	Function:	DrawTraces
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::DrawTraces(CDC *pDC)
{
	DWORD k;
	SFMT_TraceCtrlData *pData;

	m_Traces.ToStart();

	for (k=0;k<!m_Traces;k++)
	{
		pData=m_Traces>>1;

		switch (pData->btDataType)
		{
		case FMTTRCCTL_COUPLES_DATA:

			DrawTraceCouplesData(pDC,pData->btTraceMode,pData);

		break;
		}
	}
}

// -----------------------------------------------------------------------------------
//	Function:	DrawLines
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::DrawLines(CDC *pDC)
{
	DWORD k;
	SFMT_TraceCtrlLine *pLine;
	CPen	*pPen;
	CPen	*pOldPen;

	SFMT_TraceCtrlAxis *pA;
	int iTemp;
	double dOff;

	m_Lines.ToStart();

	for (k=0;k<!m_Lines;k++)
	{
		pLine=m_Lines>>1;

		pA=GetAxis(pLine->btAxisID);

		pPen=new CPen;
		pPen->CreatePen(pLine->iPenStyle,pLine->iPenSize,pLine->colLine);

		pOldPen=pDC->SelectObject(pPen);

		if (pLine->bVert)
		{
			dOff=(double)m_iPX+pA->dOffset*m_dSX;
			iTemp=(int)((double)dOff+m_dSX*pLine->dPos+(double)m_TraceRect.left);

			if ((iTemp>m_TraceRect.left) && (iTemp<m_TraceRect.right))
			{
				pDC->MoveTo(iTemp,m_TraceRect.top);
				pDC->LineTo(iTemp,m_TraceRect.bottom);
			}
		}
		else
		{
			dOff=(double)m_iPY+pA->dOffset*m_dSY;
			iTemp=m_TraceRect.bottom-(int)(dOff+m_dSY*pLine->dPos);

			if ((iTemp>m_TraceRect.top) && (iTemp<m_TraceRect.bottom))
			{
				pDC->MoveTo(m_TraceRect.left,iTemp);
				pDC->LineTo(m_TraceRect.right,iTemp);
			}
		}

		delete pPen;
		pDC->SelectObject(pOldPen);
	}
}


// -----------------------------------------------------------------------------------
//	Function:	DrawGridHorz
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::DrawGridHorz(CDC *pDC,BYTE btAxisID)
{
	// Determina se eseguire o no la visualizzazione
	if (!m_GridX.bEnabled)
		return;

	int iTemp;

	iTemp=m_TraceRect.bottom-m_iPY;
	if ((btAxisID==FMTTRCCTL_AXIS_X) &&
		((iTemp<m_TraceRect.top) || (iTemp>m_TraceRect.bottom)))
	return;

	// Crea oggetti grafici per il disegno

	CPen	*pPen;
	CPen	*pSubPen;
	CPen	*pOldPen;
	BOOL	bAgain;
	double	dTemp;
	int		iPos;
	double	dPitch;
	double	dOff;
	DWORD	k;
	CRect	cr;

	SFMT_TraceCtrlAxis *pA=GetAxis(m_GridX.btAxisID);

	// Disegno asse -------------------------------------------

	switch (btAxisID)
	{
	case FMTTRCCTL_AXIS_X:
		iPos=m_TraceRect.bottom-m_iPY;
	break;

	case FMTTRCCTL_AXIS_TOP:
		iPos=m_TraceRect.top;
	break;

	case FMTTRCCTL_AXIS_BOTTOM:
		iPos=m_TraceRect.bottom;
	break;
	}

	// Disegno subtaps ---------------------------------------------

	dPitch=(pA->dTapPitch*pA->dScale)/(double)pA->dwSubTapNum;
	dOff=(double)m_iPX+pA->dOffset*m_dSX;

	pPen=new CPen;
	pPen->CreatePen(m_GridX.iGridPenStyle,1,m_GridX.colGrid);

	pSubPen=new CPen;
	pSubPen->CreatePen(m_GridX.iSubGridPenStyle,1,m_GridX.colSubGrid);

	pOldPen=pDC->SelectObject(pPen);
	
	bAgain=TRUE;
	dTemp=0;

	if (dOff<0)
	{
		dTemp=(double)(-dOff)/(dPitch*m_dSX);
		iTemp=(int)dTemp;
		k=iTemp+1;
		dTemp=k*dPitch;
	}
	else
	{
		dTemp=0;
		k=0;
	}

	while (bAgain)
	{
		iTemp=(int)((double)dOff+m_dSX*dTemp+(double)m_TraceRect.left);

		if (iTemp>m_TraceRect.right)
		{
			bAgain=FALSE;
		}
		else
		{
			if ((k % pA->dwSubTapNum)==0)
			{
				if (m_GridX.bGrid)
				{
					pDC->SelectObject(pPen);

					pDC->MoveTo(iTemp,m_TraceRect.top);
					pDC->LineTo(iTemp,m_TraceRect.bottom);
				}
				else if (m_GridX.bSubGrid)
				{
					pDC->SelectObject(pSubPen);

					pDC->MoveTo(iTemp,m_TraceRect.top);
					pDC->LineTo(iTemp,m_TraceRect.bottom);
				}
			}
			else
			{
				if (m_GridX.bSubGrid)
				{
					pDC->SelectObject(pSubPen);

					pDC->MoveTo(iTemp,m_TraceRect.top);
					pDC->LineTo(iTemp,m_TraceRect.bottom);
				}
			}
		}

		dTemp+=dPitch;
		k++;
	}

	bAgain=TRUE;
	dTemp=0;

	if (dOff>m_TraceRect.Width())
	{
		dTemp=(double)(dOff-m_TraceRect.Width())/(dPitch*m_dSX);
		iTemp=(int)dTemp+1;
		dTemp=-(iTemp*dPitch);
		k=iTemp;
	}
	else
	{
		dTemp=0;
		k=0;
	}

	while (bAgain)
	{
		iTemp=(int)(dOff+m_dSX*dTemp+(double)m_TraceRect.left);

		if (iTemp<m_TraceRect.left)
		{
			bAgain=FALSE;
		}
		else
		{
			if ((k % pA->dwSubTapNum)==0)
			{
				if (m_GridX.bGrid)
				{
					pDC->SelectObject(pPen);

					pDC->MoveTo(iTemp,m_TraceRect.top);
					pDC->LineTo(iTemp,m_TraceRect.bottom);
				}
				else if (m_GridX.bSubGrid)
				{
					pDC->SelectObject(pSubPen);

					pDC->MoveTo(iTemp,m_TraceRect.top);
					pDC->LineTo(iTemp,m_TraceRect.bottom);
				}
			}
			else
			{
				if (m_GridX.bSubGrid)
				{
					pDC->SelectObject(pSubPen);

					pDC->MoveTo(iTemp,m_TraceRect.top);
					pDC->LineTo(iTemp,m_TraceRect.bottom);
				}
			}
		}

		dTemp-=dPitch;
		k++;
	}	

	pDC->SelectObject(pOldPen);
	delete pPen;
	delete pSubPen;
}

// -----------------------------------------------------------------------------------
//	Function:	DrawGridVert
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::DrawGridVert(CDC *pDC,BYTE btAxisID)
{
	// Determina se eseguire o no la visualizzazione
	if (!m_GridY.bEnabled)
		return;

	int iTemp;

	iTemp=m_TraceRect.right-m_iPX;
	if ((btAxisID==FMTTRCCTL_AXIS_Y) &&
		((iTemp<m_TraceRect.left) || (iTemp>m_TraceRect.right)))
	return;

	// Crea oggetti grafici per il disegno

	CPen	*pPen;
	CPen	*pSubPen;
	CPen	*pOldPen;
	BOOL	bAgain;
	double	dTemp;
	int		iPos;
	double	dPitch;
	double	dOff;
	DWORD	k;
	CRect	cr;

	SFMT_TraceCtrlAxis *pA=GetAxis(m_GridY.btAxisID);

	// Disegno asse -------------------------------------------

	switch (btAxisID)
	{
	case FMTTRCCTL_AXIS_Y:
		iPos=m_TraceRect.left+m_iPX;
	break;

	case FMTTRCCTL_AXIS_LEFT:
		iPos=m_TraceRect.left;
	break;

	case FMTTRCCTL_AXIS_RIGHT:
		iPos=m_TraceRect.right;
	break;
	}

	// Disegno subtaps ---------------------------------------------

	dPitch=(pA->dTapPitch*pA->dScale)/(double)pA->dwSubTapNum;
	dOff=m_iPY+pA->dOffset*m_dSY;

	pPen=new CPen;
	pPen->CreatePen(m_GridY.iGridPenStyle,1,m_GridY.colGrid);

	pSubPen=new CPen;
	pSubPen->CreatePen(m_GridY.iSubGridPenStyle,1,m_GridY.colSubGrid);

	pOldPen=pDC->SelectObject(pPen);
	
	bAgain=TRUE;
	dTemp=0;

	if (dOff<0)
	{
		dTemp=(double)(-dOff)/(dPitch*m_dSY);
		iTemp=(int)dTemp;
		k=iTemp+1;
		dTemp=k*dPitch;
	}
	else
	{
		dTemp=0;
		k=0;
	}

	while (bAgain)
	{
		iTemp=m_TraceRect.bottom-(int)(dOff+m_dSY*dTemp);

		if (iTemp<m_TraceRect.top)
		{
			bAgain=FALSE;
		}
		else
		{
			if ((k % pA->dwSubTapNum)==0)
			{
				if (m_GridY.bGrid)
				{
					pDC->SelectObject(pPen);

					pDC->MoveTo(m_TraceRect.left,iTemp);
					pDC->LineTo(m_TraceRect.right,iTemp);
				}
				else if (m_GridY.bSubGrid)
				{
					pDC->SelectObject(pSubPen);

					pDC->MoveTo(m_TraceRect.left,iTemp);
					pDC->LineTo(m_TraceRect.right,iTemp);
				}
			}
			else
			{
				if (m_GridY.bSubGrid)
				{
					pDC->SelectObject(pSubPen);

					pDC->MoveTo(m_TraceRect.left,iTemp);
					pDC->LineTo(m_TraceRect.right,iTemp);
				}
			}
		}

		dTemp+=dPitch;
		k++;
	}

	bAgain=TRUE;
	dTemp=0;

	if (dOff>m_TraceRect.Height())
	{
		dTemp=(double)(dOff-m_TraceRect.Height())/(dPitch*m_dSY);
		iTemp=(int)dTemp+1;
		dTemp=-(iTemp*dPitch);
		k=iTemp;
	}
	else
	{
		dTemp=0;
		k=0;
	}

	while (bAgain)
	{
		iTemp=m_TraceRect.bottom-(int)(dOff+m_dSY*dTemp);

		if (iTemp>m_TraceRect.bottom)
		{
			bAgain=FALSE;
		}
		else
		{
			if ((k % pA->dwSubTapNum)==0)
			{
				if (m_GridY.bGrid)
				{
					pDC->SelectObject(pPen);

					pDC->MoveTo(m_TraceRect.left,iTemp);
					pDC->LineTo(m_TraceRect.right,iTemp);
				}
				else if (m_GridY.bSubGrid)
				{
					pDC->SelectObject(pSubPen);

					pDC->MoveTo(m_TraceRect.left,iTemp);
					pDC->LineTo(m_TraceRect.right,iTemp);
				}
			}
			else
			{
				if (m_GridY.bSubGrid)
				{
					pDC->SelectObject(pSubPen);

					pDC->MoveTo(m_TraceRect.left,iTemp);
					pDC->LineTo(m_TraceRect.right,iTemp);
				}
			}
		}

		dTemp-=dPitch;
		k++;
	}

	pDC->SelectObject(pOldPen);
	delete pPen;
	delete pSubPen;
}

// -----------------------------------------------------------------------------------
//	Function:	DrawGrid
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::DrawGrid(CDC *pDC,BYTE btHAxisID,BYTE btVAxisID)
{
	DrawGridHorz(pDC,btHAxisID);
	DrawGridVert(pDC,btVAxisID);
}

// -----------------------------------------------------------------------------------
//	Function:	Draw
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::Draw(CDC *pDC)
{
	// Draw backgrounds
	
	DrawTraceBackground(pDC);

	DrawGrid(pDC,FMTTRCCTL_AXIS_BOTTOM,FMTTRCCTL_AXIS_LEFT);

	DrawAxis(pDC,FMTTRCCTL_AXIS_X);
	DrawAxis(pDC,FMTTRCCTL_AXIS_Y);
	DrawAxisTaps(pDC,FMTTRCCTL_AXIS_X);
	DrawAxisTaps(pDC,FMTTRCCTL_AXIS_Y);
	DrawAxisLabels(pDC,FMTTRCCTL_AXIS_X);
	DrawAxisLabels(pDC,FMTTRCCTL_AXIS_Y);
	DrawAxisText(pDC,FMTTRCCTL_AXIS_X);
	DrawAxisText(pDC,FMTTRCCTL_AXIS_Y);


	DrawTraces(pDC);

	DrawBorderBackground(pDC);

	DrawAxis(pDC,FMTTRCCTL_AXIS_TOP);
	DrawAxis(pDC,FMTTRCCTL_AXIS_LEFT);
	DrawAxis(pDC,FMTTRCCTL_AXIS_RIGHT);
	DrawAxis(pDC,FMTTRCCTL_AXIS_BOTTOM);

	DrawAxisTaps(pDC,FMTTRCCTL_AXIS_TOP);
	DrawAxisTaps(pDC,FMTTRCCTL_AXIS_LEFT);
	DrawAxisTaps(pDC,FMTTRCCTL_AXIS_RIGHT);
	DrawAxisTaps(pDC,FMTTRCCTL_AXIS_BOTTOM);

	DrawAxisLabels(pDC,FMTTRCCTL_AXIS_TOP);
	DrawAxisLabels(pDC,FMTTRCCTL_AXIS_LEFT);
	DrawAxisLabels(pDC,FMTTRCCTL_AXIS_RIGHT);
	DrawAxisLabels(pDC,FMTTRCCTL_AXIS_BOTTOM);

	DrawAxisText(pDC,FMTTRCCTL_AXIS_TOP);
	DrawAxisText(pDC,FMTTRCCTL_AXIS_BOTTOM);
	DrawAxisText(pDC,FMTTRCCTL_AXIS_LEFT);
	DrawAxisText(pDC,FMTTRCCTL_AXIS_RIGHT);



	DrawLines(pDC);

}

// -----------------------------------------------------------------------------------
//	Function:	ScrollTo
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::ScrollTo(int iPx,int iPy)
{
	ASSERT(::IsWindow(m_hWnd)); 

	struct SCommand
	{
		int iX;
		int iY;
	} com;

	com.iX=iPx;
	com.iY=iPy;

	::SendMessage(m_hWnd, FMTTRCCTL_SCROLL_MESS, 0, (long)(&com)); 
}

// -----------------------------------------------------------------------------------
//	Function:	ScrollX
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::ScrollX(int iDx)
{
	ASSERT(::IsWindow(m_hWnd)); 

	struct SCommand
	{
		int iX;
		int iY;
	} com;

	com.iX=iDx;

	::SendMessage(m_hWnd, FMTTRCCTL_SCROLL_MESS, 1, (long)(&com)); 
}

// -----------------------------------------------------------------------------------
//	Function:	ScrollY
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::ScrollY(int iDy)
{
	ASSERT(::IsWindow(m_hWnd)); 

	struct SCommand
	{
		int iX;
		int iY;
	} com;

	com.iY=iDy;

	::SendMessage(m_hWnd, FMTTRCCTL_SCROLL_MESS, 2, (long)(&com)); 
}

// -----------------------------------------------------------------------------------
//	Function:	GetScrollPos
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::GetScrollPos(int *piPx,int *piPy)
{
	ASSERT(::IsWindow(m_hWnd)); 

	struct SCommand
	{
		int iX;
		int iY;
	} com;

	::SendMessage(m_hWnd, FMTTRCCTL_SCROLL_MESS, 3, (long)(&com)); 

	(*piPx)=com.iX;
	(*piPy)=com.iY;
}

// -----------------------------------------------------------------------------------
//	Function:	Scroll
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::Scroll(int iDx,int iDy)
{
	ASSERT(::IsWindow(m_hWnd)); 

	struct SCommand
	{
		int iX;
		int iY;
	} com;

	com.iX=iDx;
	com.iY=iDy;

	::SendMessage(m_hWnd, FMTTRCCTL_SCROLL_MESS, 4, (long)(&com)); 
}

// -----------------------------------------------------------------------------------
//	Function:	SetScale
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::SetScale(double dSX,double dSY)
{
	ASSERT(::IsWindow(m_hWnd)); 

	struct SCommand
	{
		double dX;
		double dY;
	} com;

	com.dX=dSX;
	com.dY=dSY;

	::SendMessage(m_hWnd, FMTTRCCTL_ZOOM_MESS, 0, (long)(&com)); 
}

// -----------------------------------------------------------------------------------
//	Function:	ZoomX
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::ZoomX(double dZX)
{
	ASSERT(::IsWindow(m_hWnd)); 

	struct SCommand
	{
		double dX;
		double dY;
	} com;

	com.dX=dZX;

	::SendMessage(m_hWnd, FMTTRCCTL_ZOOM_MESS, 1, (long)(&com)); 
}

// -----------------------------------------------------------------------------------
//	Function:	ZoomY
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::ZoomY(double dZY)
{
	ASSERT(::IsWindow(m_hWnd)); 

	struct SCommand
	{
		double dX;
		double dY;
	} com;

	com.dY=dZY;

	::SendMessage(m_hWnd, FMTTRCCTL_ZOOM_MESS, 2, (long)(&com)); 
}

// -----------------------------------------------------------------------------------
//	Function:	Zoom
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::Zoom(double dZX,double dZY)
{
	ASSERT(::IsWindow(m_hWnd)); 

	struct SCommand
	{
		double dX;
		double dY;
	} com;

	com.dX=dZX;
	com.dY=dZY;

	::SendMessage(m_hWnd, FMTTRCCTL_ZOOM_MESS, 3, (long)(&com)); 
}

// -----------------------------------------------------------------------------------
//	Function:	Zoom
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::Zoom(double dZ)
{
	ASSERT(::IsWindow(m_hWnd)); 

	struct SCommand
	{
		double dX;
		double dY;
	} com;

	com.dX=dZ;

	::SendMessage(m_hWnd, FMTTRCCTL_ZOOM_MESS, 4, (long)(&com)); 
}

// -----------------------------------------------------------------------------------
//	Function:	GetScale
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::GetScale(double *pdSX,double *pdSY)
{
	ASSERT(::IsWindow(m_hWnd)); 

	struct SCommand
	{
		double dX;
		double dY;
	} com;

	::SendMessage(m_hWnd, FMTTRCCTL_ZOOM_MESS, 5, (long)(&com)); 

	(*pdSX)=com.dX;
	(*pdSY)=com.dY;
}

// -----------------------------------------------------------------------------------
//	Function:	EnableAxis
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::EnableAxis(BYTE btID,BOOL bEnable)
{
	ASSERT(::IsWindow(m_hWnd)); 

	struct SCommand
	{
		BYTE btID;
		SFMT_TraceCtrlAxis a;
	} com;

	com.btID=btID;
	com.a.bEnabled=bEnable;

	::SendMessage(m_hWnd, FMTTRCCTL_SETAXIS_MESS, 0, (long)(&com)); 
}

// -----------------------------------------------------------------------------------
//	Function:	EnableAxisTap
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::EnableAxisTap(BYTE btID,BOOL bEnable)
{
	ASSERT(::IsWindow(m_hWnd)); 

	struct SCommand
	{
		BYTE btID;
		SFMT_TraceCtrlAxis a;
	} com;

	com.btID=btID;
	com.a.bDrawTaps=bEnable;

	::SendMessage(m_hWnd, FMTTRCCTL_SETAXIS_MESS, 2, (long)(&com)); 
}

// -----------------------------------------------------------------------------------
//	Function:	EnableAxisSubTap
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::EnableAxisSubTap(BYTE btID,BOOL bEnable)
{
	ASSERT(::IsWindow(m_hWnd)); 

	struct SCommand
	{
		BYTE btID;
		SFMT_TraceCtrlAxis a;
	} com;

	com.btID=btID;
	com.a.bDrawSubTaps=bEnable;

	::SendMessage(m_hWnd, FMTTRCCTL_SETAXIS_MESS, 4, (long)(&com)); 
}

// -----------------------------------------------------------------------------------
//	Function:	EnableAxisTapLabel
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::EnableAxisTapLabel(BYTE btID,BOOL bEnable)
{
	ASSERT(::IsWindow(m_hWnd)); 

	struct SCommand
	{
		BYTE btID;
		SFMT_TraceCtrlAxis a;
	} com;

	com.btID=btID;
	com.a.bDrawTapLabels=bEnable;

	::SendMessage(m_hWnd, FMTTRCCTL_SETAXIS_MESS, 6, (long)(&com)); 
}

// -----------------------------------------------------------------------------------
//	Function:	EnableAxisSubTapLabel
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::EnableAxisSubTapLabel(BYTE btID,BOOL bEnable)
{
	ASSERT(::IsWindow(m_hWnd)); 

	struct SCommand
	{
		BYTE btID;
		SFMT_TraceCtrlAxis a;
	} com;

	com.btID=btID;
	com.a.bDrawSubTabLabels=bEnable;

	::SendMessage(m_hWnd, FMTTRCCTL_SETAXIS_MESS, 8, (long)(&com)); 
}

// -----------------------------------------------------------------------------------
//	Function:	EnableAxisText
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::EnableAxisText(BYTE btID,BOOL bEnable)
{
	ASSERT(::IsWindow(m_hWnd)); 

	struct SCommand
	{
		BYTE btID;
		SFMT_TraceCtrlAxis a;
	} com;

	com.btID=btID;
	com.a.bDrawText=bEnable;

	::SendMessage(m_hWnd, FMTTRCCTL_SETAXIS_MESS, 10, (long)(&com)); 
}

// -----------------------------------------------------------------------------------
//	Function:	SetAxis
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::SetAxis(BYTE btID,COLORREF col,BYTE btSize,double dScale,double dOffset)
{
	ASSERT(::IsWindow(m_hWnd)); 

	struct SCommand
	{
		BYTE btID;
		SFMT_TraceCtrlAxis a;
	} com;

	com.btID=btID;
	com.a.colAxis=col;
	com.a.dScale=dScale;
	com.a.dOffset=dOffset;

	::SendMessage(m_hWnd, FMTTRCCTL_SETAXIS_MESS, 1, (long)(&com)); 
}

// -----------------------------------------------------------------------------------
//	Function:	SetAxisTap
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::SetAxisTap(BYTE btID,COLORREF col,BYTE btSize,double dPitch)
{
	ASSERT(::IsWindow(m_hWnd)); 

	struct SCommand
	{
		BYTE btID;
		SFMT_TraceCtrlAxis a;
	} com;

	com.btID=btID;
	com.a.colTap=col;
	com.a.btTapSize=btSize;
	com.a.dTapPitch=dPitch;

	::SendMessage(m_hWnd, FMTTRCCTL_SETAXIS_MESS, 3, (long)(&com)); 
}

// -----------------------------------------------------------------------------------
//	Function:	SetAxisSubTap
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::SetAxisSubTap(BYTE btID,COLORREF col,BYTE btSize, DWORD dwNum)
{
	ASSERT(::IsWindow(m_hWnd)); 

	struct SCommand
	{
		BYTE btID;
		SFMT_TraceCtrlAxis a;
	} com;

	com.btID=btID;
	com.a.colSubTap=col;
	com.a.btSubTapSize=btSize;
	com.a.dwSubTapNum=dwNum;

	::SendMessage(m_hWnd, FMTTRCCTL_SETAXIS_MESS, 5, (long)(&com)); 
}

// -----------------------------------------------------------------------------------
//	Function:	SetAxisTapLabel
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::SetAxisTapLabel(BYTE btID,COLORREF col,BYTE btDec,BYTE btFontID,BYTE btSize)
{
	ASSERT(::IsWindow(m_hWnd)); 

	struct SCommand
	{
		BYTE btID;
		SFMT_TraceCtrlAxis a;
	} com;

	com.btID=btID;
	com.a.colTapLabel=col;
	com.a.btTabLabelDec=btDec;
	com.a.btTapLabelFontID=btFontID;
	com.a.btTapLabelSize=btSize;

	::SendMessage(m_hWnd, FMTTRCCTL_SETAXIS_MESS, 7, (long)(&com)); 
}

// -----------------------------------------------------------------------------------
//	Function:	SetAxisSubTapLabel
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::SetAxisSubTapLabel(BYTE btID,COLORREF col,BYTE btDec,BYTE btFontID,BYTE btSize)
{
	ASSERT(::IsWindow(m_hWnd)); 

	struct SCommand
	{
		BYTE btID;
		SFMT_TraceCtrlAxis a;
	} com;

	com.btID=btID;
	com.a.colSubTapLabel=col;
	com.a.btSubTabLabelDec=btDec;
	com.a.btSubTapLabelFontID=btFontID;
	com.a.btSubTapLabelSize=btSize;

	::SendMessage(m_hWnd, FMTTRCCTL_SETAXIS_MESS, 9, (long)(&com)); 
}

// -----------------------------------------------------------------------------------
//	Function:	SetAxisText
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::SetAxisText(BYTE btID,CString sText,CSize size,
								 COLORREF col,COLORREF colBack,BYTE btFontID,BYTE btPos,BOOL bTransp)
{
	ASSERT(::IsWindow(m_hWnd)); 

	struct SCommand
	{
		BYTE btID;
		SFMT_TraceCtrlAxis a;
	} com;

	com.btID=btID;
	com.a.szLabelSize=size;
	com.a.sLabel=sText;
	com.a.colLabel=col;
	com.a.colBackLabel=colBack;
	com.a.btLabelFontID=btFontID;
	com.a.btLabelPos=btPos;
	com.a.bLabelTransp=bTransp;

	::SendMessage(m_hWnd, FMTTRCCTL_SETAXIS_MESS, 11, (long)(&com)); 
}

// -----------------------------------------------------------------------------------
//	Function:	SetBorderAreaBackColor
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::SetBorderAreaBackColor(COLORREF col)
{
	ASSERT(::IsWindow(m_hWnd)); 

	::SendMessage(m_hWnd, FMTTRCCTL_BACKCOL_MESS, 0, (long)(col)); 
}

// -----------------------------------------------------------------------------------
//	Function:	SetTraceAreaBackColor
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::SetTraceAreaBackColor(COLORREF col)
{
	ASSERT(::IsWindow(m_hWnd)); 

	::SendMessage(m_hWnd, FMTTRCCTL_BACKCOL_MESS, 1, (long)(col)); 
}











// -----------------------------------------------------------------------------------
//	Function:	GetAxis
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::GetAxis(BYTE btID,COLORREF& col,BYTE& btSize,double& dScale,double& dOffset)
{
	ASSERT(::IsWindow(m_hWnd)); 

	struct SCommand
	{
		BYTE btID;
		SFMT_TraceCtrlAxis a;
	} com;

	com.btID=btID;

	::SendMessage(m_hWnd, FMTTRCCTL_GETAXIS_MESS, 1, (long)(&com)); 

	col=com.a.colAxis;
	dScale=com.a.dScale;
	dOffset=com.a.dOffset;
}

// -----------------------------------------------------------------------------------
//	Function:	GetAxisTap
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::GetAxisTap(BYTE btID,COLORREF& col,BYTE& btSize,double& dPitch)
{
	ASSERT(::IsWindow(m_hWnd)); 

	struct SCommand
	{
		BYTE btID;
		SFMT_TraceCtrlAxis a;
	} com;

	com.btID=btID;

	::SendMessage(m_hWnd, FMTTRCCTL_GETAXIS_MESS, 3, (long)(&com)); 

	col=com.a.colTap;
	btSize=com.a.btTapSize;
	dPitch=com.a.dTapPitch;
}

// -----------------------------------------------------------------------------------
//	Function:	GetAxisSubTap
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::GetAxisSubTap(BYTE btID,COLORREF& col,BYTE& btSize, DWORD& dwNum)
{
	ASSERT(::IsWindow(m_hWnd)); 

	struct SCommand
	{
		BYTE btID;
		SFMT_TraceCtrlAxis a;
	} com;

	com.btID=btID;

	::SendMessage(m_hWnd, FMTTRCCTL_GETAXIS_MESS, 5, (long)(&com)); 

	col=com.a.colSubTap;
	btSize=com.a.btSubTapSize;
	dwNum=com.a.dwSubTapNum;
}

// -----------------------------------------------------------------------------------
//	Function:	GetAxisTapLabel
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::GetAxisTapLabel(BYTE btID,COLORREF& col,BYTE& btDec,BYTE& btFontID,BYTE& btSize)
{
	ASSERT(::IsWindow(m_hWnd)); 

	struct SCommand
	{
		BYTE btID;
		SFMT_TraceCtrlAxis a;
	} com;

	com.btID=btID;

	::SendMessage(m_hWnd, FMTTRCCTL_GETAXIS_MESS, 7, (long)(&com)); 

	col=com.a.colTapLabel;
	btDec=com.a.btTabLabelDec;
	btFontID=com.a.btTapLabelFontID;
	btSize=com.a.btTapLabelSize;
}

// -----------------------------------------------------------------------------------
//	Function:	GetAxisSubTapLabel
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::GetAxisSubTapLabel(BYTE btID,COLORREF& col,BYTE& btDec,BYTE& btFontID,BYTE& btSize)
{
	ASSERT(::IsWindow(m_hWnd)); 

	struct SCommand
	{
		BYTE btID;
		SFMT_TraceCtrlAxis a;
	} com;

	com.btID=btID;

	::SendMessage(m_hWnd, FMTTRCCTL_GETAXIS_MESS, 9, (long)(&com)); 

	col=com.a.colSubTapLabel;
	btDec=com.a.btSubTabLabelDec;
	btFontID=com.a.btSubTapLabelFontID;
	btSize=com.a.btSubTapLabelSize;
}

// -----------------------------------------------------------------------------------
//	Function:	GetAxisText
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::GetAxisText(BYTE btID,CString& sText,CSize& size,
								 COLORREF& col,COLORREF& colBack,BYTE& btFontID,BYTE& btPos,BOOL& bTransp)
{
	ASSERT(::IsWindow(m_hWnd)); 

	struct SCommand
	{
		BYTE btID;
		SFMT_TraceCtrlAxis a;
	} com;

	com.btID=btID;

	::SendMessage(m_hWnd, FMTTRCCTL_GETAXIS_MESS, 11, (long)(&com)); 

	size=com.a.szLabelSize;
	sText=com.a.sLabel;
	col=com.a.colLabel;
	colBack=com.a.colBackLabel;
	btFontID=com.a.btLabelFontID;
	btPos=com.a.btLabelPos;
	bTransp=com.a.bLabelTransp;
}

// -----------------------------------------------------------------------------------
//	Function:	GetNumTraces
// -----------------------------------------------------------------------------------

DWORD CFMT_TraceCtrl::GetNumTraces()
{
	ASSERT(::IsWindow(m_hWnd)); 

	struct SCommand
	{
		DWORD dwRet;
		int iNum;
		SFMT_TraceCtrlData data;
	} com;

	::SendMessage(m_hWnd, FMTTRCCTL_TRACE_MESS, 0, (long)(&com)); 

	return com.dwRet;
}

// -----------------------------------------------------------------------------------
//	Function:	InsertTrace
// -----------------------------------------------------------------------------------

BOOL CFMT_TraceCtrl::InsertTrace(DWORD dwNum,COLORREF col,BYTE btMode,BYTE btType, DWORD dwSize,void *pData,BYTE btPenSize,int iPenStyle)
{
	ASSERT(::IsWindow(m_hWnd)); 

	if (dwNum>!m_Traces)
		return FALSE;

	struct SCommand
	{
		DWORD dwRet;
		int iNum;
		SFMT_TraceCtrlData data;
	} com;

	com.data.btDataType=btType;
	com.data.btTraceMode=btMode;
	com.data.colTrace=col;
	com.data.pData=pData;
	com.data.dwSize=dwSize;
	com.data.btPenSize=btPenSize;
	com.data.iPenStyle=iPenStyle;

	com.iNum=dwNum;

	::SendMessage(m_hWnd, FMTTRCCTL_TRACE_MESS, 1, (long)(&com)); 

	return TRUE;
}

// -----------------------------------------------------------------------------------
//	Function:	ReplaceTrace
// -----------------------------------------------------------------------------------

BOOL CFMT_TraceCtrl::ReplaceTrace(DWORD dwNum,COLORREF col,BYTE btMode,BYTE btType, DWORD dwSize,void *pData,BYTE btPenSize,int iPenStyle)
{
	ASSERT(::IsWindow(m_hWnd)); 

	if (dwNum>!m_Traces)
		return FALSE;

	struct SCommand
	{
		DWORD dwRet;
		int iNum;
		SFMT_TraceCtrlData data;
	} com;

	com.iNum=dwNum;

	com.data.btDataType=btType;
	com.data.btTraceMode=btMode;
	com.data.colTrace=col;
	com.data.pData=pData;
	com.data.dwSize=dwSize;
	com.data.btPenSize=btPenSize;
	com.data.iPenStyle=iPenStyle;

	::SendMessage(m_hWnd, FMTTRCCTL_TRACE_MESS, 2, (long)(&com)); 

	return TRUE;
}



// -----------------------------------------------------------------------------------
//	Function:	EnableGridHorz
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::EnableGridHorz(BOOL bEnable)
{
	ASSERT(::IsWindow(m_hWnd)); 

	struct SCommand
	{
		BOOL		bVert;
		BOOL		bEnable;
		COLORREF	col; 
		int			iStyle;
		BYTE		btID;
	} com;

	com.bVert=FALSE;
	com.bEnable=bEnable;

	::SendMessage(m_hWnd, FMTTRCCTL_GRID_MESS, 0, (long)(&com)); 
}

// -----------------------------------------------------------------------------------
//	Function:	SetGridHorz
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::SetGridHorz(BOOL bEnable,BYTE btID,COLORREF col,int iStyle)
{
	ASSERT(::IsWindow(m_hWnd)); 

	struct SCommand
	{
		BOOL		bVert;
		BOOL		bEnable;
		COLORREF	col; 
		int			iStyle;
		BYTE		btID;
	} com;

	com.bVert=FALSE;
	com.bEnable=bEnable;
	com.col=col;
	com.iStyle=iStyle;
	com.btID=btID;

	::SendMessage(m_hWnd, FMTTRCCTL_GRID_MESS, 1, (long)(&com)); 
}

// -----------------------------------------------------------------------------------
//	Function:	SetSubGridHorz
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::SetSubGridHorz(BOOL bEnable,COLORREF col,int iStyle)
{
	ASSERT(::IsWindow(m_hWnd)); 

	struct SCommand
	{
		BOOL		bVert;
		BOOL		bEnable;
		COLORREF	col; 
		int			iStyle;
		BYTE		btID;
	} com;

	com.bVert=FALSE;
	com.bEnable=bEnable;
	com.col=col;
	com.iStyle=iStyle;

	::SendMessage(m_hWnd, FMTTRCCTL_GRID_MESS, 2, (long)(&com)); 
}

// -----------------------------------------------------------------------------------
//	Function:	GetGridHorz
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::GetGridHorz(BOOL& bEnable,BYTE& btID,COLORREF& col,int& iStyle)
{
	ASSERT(::IsWindow(m_hWnd)); 

	struct SCommand
	{
		BOOL		bVert;
		BOOL		bEnable;
		COLORREF	col; 
		int			iStyle;
		BYTE		btID;
	} com;

	com.bVert=FALSE;

	::SendMessage(m_hWnd, FMTTRCCTL_GRID_MESS, 3, (long)(&com)); 
	
	bEnable=com.bEnable;
	col=com.col;
	iStyle=com.iStyle;
	btID=com.btID;
}

// -----------------------------------------------------------------------------------
//	Function:	GetSubGridHorz
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::GetSubGridHorz(BOOL& bEnable,COLORREF& col,int& iStyle)
{
	ASSERT(::IsWindow(m_hWnd)); 

	struct SCommand
	{
		BOOL		bVert;
		BOOL		bEnable;
		COLORREF	col; 
		int			iStyle;
		BYTE		btID;
	} com;

	com.bVert=FALSE;

	::SendMessage(m_hWnd, FMTTRCCTL_GRID_MESS, 4, (long)(&com)); 
	
	bEnable=com.bEnable;
	col=com.col;
	iStyle=com.iStyle;
}

// -----------------------------------------------------------------------------------
//	Function:	EnableGridVert
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::EnableGridVert(BOOL bEnable)
{
	ASSERT(::IsWindow(m_hWnd)); 

	struct SCommand
	{
		BOOL		bVert;
		BOOL		bEnable;
		COLORREF	col; 
		int			iStyle;
		BYTE		btID;
	} com;

	com.bVert=TRUE;
	com.bEnable=bEnable;

	::SendMessage(m_hWnd, FMTTRCCTL_GRID_MESS, 0, (long)(&com)); 
}

// -----------------------------------------------------------------------------------
//	Function:	SetGridVert
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::SetGridVert(BOOL bEnable,BYTE btID,COLORREF col,int iStyle)
{
	ASSERT(::IsWindow(m_hWnd)); 

	struct SCommand
	{
		BOOL		bVert;
		BOOL		bEnable;
		COLORREF	col; 
		int			iStyle;
		BYTE		btID;
	} com;

	com.bVert=TRUE;
	com.bEnable=bEnable;
	com.col=col;
	com.iStyle=iStyle;
	com.btID=btID;

	::SendMessage(m_hWnd, FMTTRCCTL_GRID_MESS, 1, (long)(&com)); 
}

// -----------------------------------------------------------------------------------
//	Function:	SetSubGridVert
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::SetSubGridVert(BOOL bEnable,COLORREF col,int iStyle)
{
	ASSERT(::IsWindow(m_hWnd)); 

	struct SCommand
	{
		BOOL		bVert;
		BOOL		bEnable;
		COLORREF	col; 
		int			iStyle;
		BYTE		btID;
	} com;

	com.bVert=TRUE;
	com.bEnable=bEnable;
	com.col=col;
	com.iStyle=iStyle;

	::SendMessage(m_hWnd, FMTTRCCTL_GRID_MESS, 2, (long)(&com)); 
}

// -----------------------------------------------------------------------------------
//	Function:	GetGridVert
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::GetGridVert(BOOL& bEnable,BYTE& btID,COLORREF& col,int& iStyle)
{
	ASSERT(::IsWindow(m_hWnd)); 

	struct SCommand
	{
		BOOL		bVert;
		BOOL		bEnable;
		COLORREF	col; 
		int			iStyle;
		BYTE		btID;
	} com;

	com.bVert=TRUE;

	::SendMessage(m_hWnd, FMTTRCCTL_GRID_MESS, 3, (long)(&com)); 
	
	bEnable=com.bEnable;
	col=com.col;
	iStyle=com.iStyle;
	btID=com.btID;
}

// -----------------------------------------------------------------------------------
//	Function:	GetSubGridVert
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::GetSubGridVert(BOOL& bEnable,COLORREF& col,int& iStyle)
{
	ASSERT(::IsWindow(m_hWnd)); 

	struct SCommand
	{
		BOOL		bVert;
		BOOL		bEnable;
		COLORREF	col; 
		int			iStyle;
		BYTE		btID;
	} com;

	com.bVert=TRUE;

	::SendMessage(m_hWnd, FMTTRCCTL_GRID_MESS, 4, (long)(&com)); 
	
	bEnable=com.bEnable;
	col=com.col;
	iStyle=com.iStyle;
}

// -----------------------------------------------------------------------------------
//	Function:	InsertLine
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::InsertLine(DWORD dwNum,BYTE btID,double dPos,BOOL bVert,COLORREF col,int iStyle,int iWidth)
{
	struct SCommand
	{
		BOOL		bVert;
		COLORREF	col; 
		int			iStyle;
		int			iWidth;
		BYTE		btID;
		double		dPos;
		DWORD		dwNum;
	} com;

	com.dwNum=dwNum;
	com.btID=btID;
	com.dPos=dPos;
	com.bVert=bVert;
	com.col=col;
	com.iStyle=iStyle;
	com.iWidth=iWidth;

	::SendMessage(m_hWnd, FMTTRCCTL_LINE_MESS, 0, (long)(&com)); 
}

// -----------------------------------------------------------------------------------
//	Function:	RemoveLine
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::RemoveLine(DWORD dwNum)
{
	struct SCommand
	{
		BOOL		bVert;
		COLORREF	col; 
		int			iStyle;
		BYTE		btID;
		double		dPos;
		DWORD		dwNum;
	} com;

	com.dwNum=dwNum;

	::SendMessage(m_hWnd, FMTTRCCTL_LINE_MESS, 1, (long)(&com)); 
}

// -----------------------------------------------------------------------------------
//	Function:	RemoveAllLines
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::RemoveAllLines()
{
	struct SCommand
	{
		BOOL		bVert;
		COLORREF	col; 
		int			iStyle;
		BYTE		btID;
		double		dPos;
		DWORD		dwNum;
	} com;

	::SendMessage(m_hWnd, FMTTRCCTL_LINE_MESS, 2, (long)(&com)); 
}


/////////////////////////////////////////////////////////////////////////////
// CFMT_TraceCtrl message handlers
/////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------------
//	Function:	OnPaint
// -----------------------------------------------------------------------------------
//	Desc.	:	Handler WM_PAINT
//
//	Return	:	-
//	Params	:	-
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	CRect cr;
	GetClientRect(&cr);

	// Creo il DC compatibile per la costruzione dell'immagine -------------
	CDC *pHDC;

	// Disegno il controllo sul DC compatibile -----------------------------
	pHDC=GetBackBufferDC(&dc);

	// OVR -----------------
	Draw(pHDC);
	// ---------------------
	
	CopyBackBufferDC(&dc,pHDC);
	ReleaseBackBufferDC(pHDC);
}

// -----------------------------------------------------------------------------------
//	Function:	OnNcDestroy
// -----------------------------------------------------------------------------------
//	Desc.	:	Handler messaggio WM_NCDESTROY
//
//	Return	:	-
//	Params	:	-
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::OnNcDestroy() 
{
    CFMT_Wnd::OnNcDestroy();
    // Make sure the window was destroyed
    ASSERT(m_hWnd == NULL);
    // Destroy this object since it won't be destroyed otherwise
    delete this;
}

// -----------------------------------------------------------------------------------
//	Function:	OnCreate
// -----------------------------------------------------------------------------------
//	Desc.	:	Handler messaggio WM_CREATE
//
//	Return	:	-
//	Params	:	lpCreateStruct = struttura di creazione
// -----------------------------------------------------------------------------------

int CFMT_TraceCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFMT_Wnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	InitControl(lpCreateStruct->lpszName);

	return 0;
}

// -----------------------------------------------------------------------------------
//	Function:	OnEraseBkgnd
// -----------------------------------------------------------------------------------
//	Desc.	:	Handler messaggio WM_ERASEBKGND
//
//	Return	:	TRUE se OK
//	Params	:	pDC = device context
// -----------------------------------------------------------------------------------

BOOL CFMT_TraceCtrl::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE;
}

// -----------------------------------------------------------------------------------
//	Function:	OnDestroy
// -----------------------------------------------------------------------------------
//	Desc.	:	Handler WM_DESTROY
//
//	Return	:	-
//	Params	:	-
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::OnDestroy() 
{
	CFMT_Wnd::OnDestroy();
	
}

// -----------------------------------------------------------------------------------
//	Function:	OnFMTScroll
// -----------------------------------------------------------------------------------

LRESULT CFMT_TraceCtrl::OnFMTScroll(UINT wParam,LONG lParam)
{
	struct SCommand
	{
		int iX;
		int iY;
	} *pCom;

	pCom=(SCommand*)lParam;

	switch (wParam)
	{
	case 0:		// ScrollTo
		m_iPX=pCom->iX;
		m_iPY=pCom->iY;
	break;

	case 1:		// ScrollX
		m_iPX+=pCom->iX;
	break;

	case 2:		// ScrollY
		m_iPY+=pCom->iY;
	break;

	case 3:		// GetScrollPos
		pCom->iX=m_iPX;
		pCom->iY=m_iPY;
	break;

	case 4:		// Scroll
		m_iPX+=pCom->iX;
		m_iPY+=pCom->iY;
	break;
	}

	return 0;
}

// -----------------------------------------------------------------------------------
//	Function:	OnFMTZoom
// -----------------------------------------------------------------------------------

LRESULT CFMT_TraceCtrl::OnFMTZoom(UINT wParam,LONG lParam)
{
	struct SCommand
	{
		double dX;
		double dY;
	} *pCom;

	pCom=(SCommand*)lParam;

	switch (wParam)
	{
	case 0:		// SetScale
		m_dSX=pCom->dX;
		m_dSY=pCom->dY;
	break;

	case 1:		// ZoomX
		m_dSX*=pCom->dX;
	break;

	case 2:		// ZoomY
		m_dSY*=pCom->dY;
	break;

	case 3:		// Zoom 2 par.
		m_dSX*=pCom->dX;
		m_dSY*=pCom->dY;
	break;

	case 4:		// Zoom 1 par.
		m_dSX*=pCom->dX;
		m_dSY*=pCom->dX;
	break;
	
	case 5:		// GetScale
		pCom->dX=m_dSX;
		pCom->dY=m_dSY;
	break;

	}

	return 0;
}

// -----------------------------------------------------------------------------------
//	Function:	OnFMTSetAxis
// -----------------------------------------------------------------------------------

LRESULT CFMT_TraceCtrl::OnFMTSetAxis(UINT wParam,LONG lParam)
{
	struct SCommand
	{
		BYTE btID;
		SFMT_TraceCtrlAxis a;
	} *pCom;

	pCom=(SCommand*)lParam;

	switch (wParam)
	{
	case 0:		// EnableAxis
		GetAxis(pCom->btID)->bEnabled=pCom->a.bEnabled;
	break;

	case 1:		// SetAxis
		GetAxis(pCom->btID)->colAxis=pCom->a.colAxis;
		GetAxis(pCom->btID)->dScale=pCom->a.dScale;
		GetAxis(pCom->btID)->dOffset=pCom->a.dOffset;
	break;

	case 2:		// Enable Tap
		GetAxis(pCom->btID)->bDrawTaps=pCom->a.bDrawTaps;
	break;

	case 3:		// Set axis taps
		GetAxis(pCom->btID)->colTap=pCom->a.colTap;
		GetAxis(pCom->btID)->btTapSize=pCom->a.btTapSize;
		GetAxis(pCom->btID)->dTapPitch=pCom->a.dTapPitch;
	break;

	case 4:		// Enable sub-tap
		GetAxis(pCom->btID)->bDrawSubTaps=pCom->a.bDrawSubTaps;
	break;
	
	case 5:		// Set axis sub-taps
		GetAxis(pCom->btID)->colSubTap=pCom->a.colSubTap;
		GetAxis(pCom->btID)->btSubTapSize=pCom->a.btSubTapSize;
		GetAxis(pCom->btID)->dwSubTapNum=pCom->a.dwSubTapNum;
	break;

	case 6:		// Enable tap label
		GetAxis(pCom->btID)->bDrawTapLabels=pCom->a.bDrawTapLabels;
	break;

	case 7:		// Set axis tap labels
		GetAxis(pCom->btID)->colTapLabel=pCom->a.colTapLabel;
		GetAxis(pCom->btID)->btTabLabelDec=pCom->a.btTabLabelDec;
		GetAxis(pCom->btID)->btTapLabelFontID=pCom->a.btTapLabelFontID;
		GetAxis(pCom->btID)->btTapLabelSize=pCom->a.btTapLabelSize;
	break;

	case 8:		// Enable sub tap label
		GetAxis(pCom->btID)->bDrawSubTabLabels=pCom->a.bDrawSubTabLabels;
	break;

	case 9:		// Set axis sub tap labels
		GetAxis(pCom->btID)->colSubTapLabel=pCom->a.colSubTapLabel;
		GetAxis(pCom->btID)->btSubTabLabelDec=pCom->a.btSubTabLabelDec;
		GetAxis(pCom->btID)->btSubTapLabelFontID=pCom->a.btSubTapLabelFontID;
		GetAxis(pCom->btID)->btSubTapLabelSize=pCom->a.btSubTapLabelSize;
	break;

	case 10:		// Enable axis text
		GetAxis(pCom->btID)->bDrawText=pCom->a.bDrawText;
	break;

	case 11:		// Set axis text
		GetAxis(pCom->btID)->sLabel=pCom->a.sLabel;
		GetAxis(pCom->btID)->szLabelSize=pCom->a.szLabelSize;
		GetAxis(pCom->btID)->colLabel=pCom->a.colLabel;
		GetAxis(pCom->btID)->colBackLabel=pCom->a.colBackLabel;
		GetAxis(pCom->btID)->btLabelFontID=pCom->a.btLabelFontID;
		GetAxis(pCom->btID)->btLabelPos=pCom->a.btLabelPos;
		GetAxis(pCom->btID)->bLabelTransp=pCom->a.bLabelTransp;
	break;
	}

	return 0;
}

// -----------------------------------------------------------------------------------
//	Function:	OnFMTGetAxis
// -----------------------------------------------------------------------------------

LRESULT CFMT_TraceCtrl::OnFMTGetAxis(UINT wParam,LONG lParam)
{
	struct SCommand
	{
		BYTE btID;
		SFMT_TraceCtrlAxis a;
	} *pCom;

	pCom=(SCommand*)lParam;

	switch (wParam)
	{
	case 0:		// Unused
	break;

	case 1:		// GetAxis
		pCom->a.colAxis=GetAxis(pCom->btID)->colAxis;
		pCom->a.dScale=GetAxis(pCom->btID)->dScale;
		pCom->a.dOffset=GetAxis(pCom->btID)->dOffset;
	break;

	case 2:		// Unused
	break;

	case 3:		// Get axis taps
		pCom->a.colTap=GetAxis(pCom->btID)->colTap;
		pCom->a.btTapSize=GetAxis(pCom->btID)->btTapSize;
		pCom->a.dTapPitch=GetAxis(pCom->btID)->dTapPitch;
	break;

	case 4:		// Unused
	break;
	
	case 5:		// Get axis sub-taps
		pCom->a.colSubTap=GetAxis(pCom->btID)->colSubTap;
		pCom->a.btSubTapSize=GetAxis(pCom->btID)->btSubTapSize;
		pCom->a.dwSubTapNum=GetAxis(pCom->btID)->dwSubTapNum;
	break;

	case 6:		// Unused
	break;

	case 7:		// Get axis tap labels
		pCom->a.colTapLabel=GetAxis(pCom->btID)->colTapLabel;
		pCom->a.btTabLabelDec=GetAxis(pCom->btID)->btTabLabelDec;
		pCom->a.btTapLabelFontID=GetAxis(pCom->btID)->btTapLabelFontID;
		pCom->a.btTapLabelSize=GetAxis(pCom->btID)->btTapLabelSize;
	break;

	case 8:		// Unused
	break;

	case 9:		// Get axis sub tap labels
		pCom->a.colSubTapLabel=GetAxis(pCom->btID)->colSubTapLabel;
		pCom->a.btSubTabLabelDec=GetAxis(pCom->btID)->btSubTabLabelDec;
		pCom->a.btSubTapLabelFontID=GetAxis(pCom->btID)->btSubTapLabelFontID;
		pCom->a.btSubTapLabelSize=GetAxis(pCom->btID)->btSubTapLabelSize;
	break;

	case 10:		// Unused
	break;

	case 11:		// Get axis text
		pCom->a.sLabel=GetAxis(pCom->btID)->sLabel;
		pCom->a.szLabelSize=GetAxis(pCom->btID)->szLabelSize;
		pCom->a.colLabel=GetAxis(pCom->btID)->colLabel;
		pCom->a.colBackLabel=GetAxis(pCom->btID)->colBackLabel;
		pCom->a.btLabelFontID=GetAxis(pCom->btID)->btLabelFontID;
		pCom->a.btLabelPos=GetAxis(pCom->btID)->btLabelPos;
		pCom->a.bLabelTransp=GetAxis(pCom->btID)->bLabelTransp;
	break;
	}

	return 0;
}

// -----------------------------------------------------------------------------------
//	Function:	OnFMTBackCol
// -----------------------------------------------------------------------------------

LRESULT CFMT_TraceCtrl::OnFMTBackCol(UINT wParam,LONG lParam)
{
	COLORREF col;

	col=(COLORREF)lParam;

	switch (wParam)
	{
	case 0:		// Border Area
		m_colBorderBack=col;
	break;

	case 1:		// Trace Area
		m_colTraceBack=col;
	break;
	}

	return 0;
}

// -----------------------------------------------------------------------------------
//	Function:	OnFMTTrace
// -----------------------------------------------------------------------------------

LRESULT CFMT_TraceCtrl::OnFMTTrace(UINT wParam,LONG lParam)
{
	struct SCommand
	{
		DWORD dwRet;
		int iNum;
		SFMT_TraceCtrlData data;
	} *pCom;

	pCom=(SCommand*)lParam;

	switch (wParam)
	{
	case 0:		// GetNumTraces
		pCom->dwRet=!m_Traces;
	break;

	case 1:		// InsertTrace
	{
		SFMT_TraceCtrlData *pData;

		pData=new SFMT_TraceCtrlData;

		pData->btDataType=pCom->data.btDataType;
		pData->btTraceMode=pCom->data.btTraceMode;
		pData->colTrace=pCom->data.colTrace;
		pData->pData=pCom->data.pData;
		pData->dwSize=pCom->data.dwSize;
		pData->iPenStyle=pCom->data.iPenStyle;
		pData->btPenSize=pCom->data.btPenSize;

		if (!m_Traces==0)
		{
			m_Traces+=pData;
		}
		else
		{
			m_Traces+=pData;
			/*m_Traces[pCom->iNum];
			m_Traces+pData;*/
		}
	}
	break;

	case 2:		// ReplaceTrace
	{
		SFMT_TraceCtrlData *pData;

		pData=m_Traces[pCom->iNum];

		pData->btDataType=pCom->data.btDataType;
		pData->btTraceMode=pCom->data.btTraceMode;
		pData->colTrace=pCom->data.colTrace;
		pData->pData=pCom->data.pData;
		pData->dwSize=pCom->data.dwSize;

	}
	break;

	}

	return 0;
}

// -----------------------------------------------------------------------------------
//	Function:	OnFMTGrid
// -----------------------------------------------------------------------------------

LRESULT CFMT_TraceCtrl::OnFMTGrid(UINT wParam,LONG lParam)
{
	struct SCommand
	{
		BOOL		bVert;
		BOOL		bEnable;
		COLORREF	col; 
		int			iStyle;
		BYTE		btID;
	} *pCom;

	pCom=(SCommand*)lParam;
	SFMT_TraceCtrlGrid *pGrid;

	if (pCom->bVert)
	{
		pGrid=&m_GridY;
	}
	else
	{
		pGrid=&m_GridX;
	}

	switch (wParam)
	{
	case 0:		// Enable
		pGrid->bEnabled=pCom->bEnable;
	break;

	case 1:		// SetGrid
		pGrid->bGrid=pCom->bEnable;
		pGrid->colGrid=pCom->col;
		pGrid->btAxisID=pCom->btID;
		pGrid->iGridPenStyle=pCom->iStyle;
	break;

	case 2:		// SetSubGrid
		pGrid->bSubGrid=pCom->bEnable;
		pGrid->colSubGrid=pCom->col;
		pGrid->iSubGridPenStyle=pCom->iStyle;
	break;

	case 3:		// GetGrid
		pCom->bEnable=pGrid->bGrid;
		pCom->col=pGrid->colGrid;
		pCom->btID=pGrid->btAxisID;
		pCom->iStyle=pGrid->iGridPenStyle;
	break;

	case 4:		// GetSubGrid
		pCom->bEnable=pGrid->bSubGrid;
		pCom->col=pGrid->colSubGrid;
		pCom->iStyle=pGrid->iSubGridPenStyle;
	break;
	}

	return 0;
}

// -----------------------------------------------------------------------------------
//	Function:	OnFMTLine
// -----------------------------------------------------------------------------------

LRESULT CFMT_TraceCtrl::OnFMTLine(UINT wParam,LONG lParam)
{
	struct SCommand
	{
		BOOL		bVert;
		COLORREF	col; 
		int			iStyle;
		int			iWidth;
		BYTE		btID;
		double		dPos;
		DWORD		dwNum;
	} *pCom;

	pCom=(SCommand*)lParam;
	SFMT_TraceCtrlLine *pLine;

	switch (wParam)
	{
	case 0:		// InsertLine

		pLine=new SFMT_TraceCtrlLine;

		pLine->btAxisID=pCom->btID;
		pLine->bVert=pCom->bVert;
		pLine->colLine=pCom->col;
		pLine->iPenStyle=pCom->iStyle;
		pLine->dPos=pCom->dPos;
		pLine->iPenSize=pCom->iWidth;

		if (!((m_Lines.GetLength()==0) && (pCom->dwNum==0)))
		{
			m_Lines[pCom->dwNum];
		}

		m_Lines.InsertItem(pLine);

	break;

	case 1:		// RemoveLine
		pLine=m_Lines[pCom->dwNum];
		delete pLine;
		m_Lines.DeleteItem();
	break;

	case 2:		// RemoveAllLines
		DestroyLines();
	break;

	case 3:		// MoveLine

		pLine=m_Lines[pCom->dwNum];
		pLine->dPos=pCom->dPos;

	break;
	}

	return 0;
}



// -----------------------------------------------------------------------------------
//	Function:	MoveLine
// -----------------------------------------------------------------------------------

void CFMT_TraceCtrl::MoveLine(DWORD dwNum,double dPos)
{
	struct SCommand
	{
		BOOL		bVert;
		COLORREF	col; 
		int			iStyle;
		int			iWidth;
		BYTE		btID;
		double		dPos;
		DWORD		dwNum;
	} com;

	com.dwNum=dwNum;
	com.btID=0;
	com.dPos=dPos;
	com.bVert=FALSE;
	com.col=0;
	com.iStyle=0;

	::SendMessage(m_hWnd, FMTTRCCTL_LINE_MESS, 3, (long)(&com)); 
}


