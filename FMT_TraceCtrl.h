//***************************************************************************
//
// Module:		FMT_TraceCtrl.h
//
// Description:	Control for graphic trace
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
//	1.0		20-10-03	M.Forzieri		First issue
// --------------------------------------------------------------------------
//***************************************************************************


#ifndef FMT_TRACECTRL_H
#define FMT_TRACECTRL_H

#ifndef FMT_WND_H
#include "FMT_Wnd.h"
#endif


#define FMTTRCCTL_FROMDLG(id)	 ((CFMT_TraceCtrl*)GetDlgItem(id))

// ----- ID Axis ------------------------------------------------------

#define FMTTRCCTL_AXIS_X				0
#define FMTTRCCTL_AXIS_Y				1
#define FMTTRCCTL_AXIS_LEFT				2
#define FMTTRCCTL_AXIS_TOP				3
#define FMTTRCCTL_AXIS_RIGHT			4
#define FMTTRCCTL_AXIS_BOTTOM			5

// ----- Trace Data Types ---------------------------------------------

#define FMTTRCCTL_COUPLES_DATA			0

// ----- Tracing Styles  ---------------------------------------------

#define FMTTRCCTL_TRACE_POINTS			0x01
#define FMTTRCCTL_TRACE_JOIN			0x02
#define FMTTRCCTL_TRACE_STICKS			0x04

// ----- Stili del controllo ------------------------------------------

#define FMTTRACECTRL_TRASPBORDERAREA			0x00000001
#define FMTTRACECTRL_TRASPTRACEAREA				0x00000002
/* NO STYLE DEFINED */

// ----- Max/Min ----------------------------------------------------

//#define FMTTRACECTRL_MAXNUMFONTS			10

// ----- Notify Messages ------------------------------------------------------

//#define FMTTRCCTL_SETCAPTURE_MESS		0x00000001

#define FMTTRCCTL_END_NOTIFY_MESS_LIST	0x00000001

// ----- Internal Messages ----------------------------------------------

#define FMTTRCCTL_SCROLL_MESS				FMTWND_END_MESSAGE_LIST+0
#define FMTTRCCTL_ZOOM_MESS					FMTWND_END_MESSAGE_LIST+1
#define FMTTRCCTL_SETAXIS_MESS				FMTWND_END_MESSAGE_LIST+2
#define FMTTRCCTL_GETAXIS_MESS				FMTWND_END_MESSAGE_LIST+3
#define FMTTRCCTL_BACKCOL_MESS				FMTWND_END_MESSAGE_LIST+4
#define FMTTRCCTL_TRACE_MESS				FMTWND_END_MESSAGE_LIST+5
#define FMTTRCCTL_GRID_MESS					FMTWND_END_MESSAGE_LIST+6
#define FMTTRCCTL_LINE_MESS					FMTWND_END_MESSAGE_LIST+7

//#define FMTTRCCTL_MODIFYSTYLE_MESS			FMTWND_END_MESSAGE_LIST+0

#define FMTTRCCTL_END_MESSAGE_LIST			FMTWND_END_MESSAGE_LIST+8

// ----- Macros ------------------------------------------------------

#define	ON_FMTTRCCTL_SCROLL(funct)			ON_MESSAGE(FMTTRCCTL_SCROLL_MESS,funct)
#define	ON_FMTTRCCTL_ZOOM(funct)			ON_MESSAGE(FMTTRCCTL_ZOOM_MESS,funct)
#define	ON_FMTTRCCTL_SETAXIS(funct)			ON_MESSAGE(FMTTRCCTL_SETAXIS_MESS,funct)
#define	ON_FMTTRCCTL_GETAXIS(funct)			ON_MESSAGE(FMTTRCCTL_GETAXIS_MESS,funct)
#define	ON_FMTTRCCTL_BACKCOL(funct)			ON_MESSAGE(FMTTRCCTL_BACKCOL_MESS,funct)
#define	ON_FMTTRCCTL_TRACE(funct)			ON_MESSAGE(FMTTRCCTL_TRACE_MESS,funct)
#define	ON_FMTTRCCTL_GRID(funct)			ON_MESSAGE(FMTTRCCTL_GRID_MESS,funct)
#define	ON_FMTTRCCTL_LINE(funct)			ON_MESSAGE(FMTTRCCTL_LINE_MESS,funct)

//#define	ON_FMTTRCCTL_SETSTYLE(funct)		ON_MESSAGE(FMTTRCCTL_SETSTYLE_MESS,funct)

/*#define ON_FMTTRCCTL_SETCAPTURE(dwID,funct)		\
	ON_NOTIFY(FMTTRCCTL_SETCAPTURE_MESS,dwID,funct)*/

// *************************************************************************************
// *************************************************************************************
//	Struct SFMT_TraceCtrlAxis 
// *************************************************************************************
// *************************************************************************************

struct SFMT_TraceCtrlAxis
{
	BOOL		bEnabled;
	BOOL		bVert;

	double		dScale;
	double		dOffset;

	COLORREF	colAxis;
	CString		sLabel;
	BYTE		btLabelFontID;
	COLORREF	colLabel;
	COLORREF	colBackLabel;
	CSize		szLabelSize;
	BYTE		btLabelPos;
	BOOL		bLabelTransp;
	BOOL		bDrawText;

	double		dTapPitch;
	DWORD		dwSubTapNum;
	BOOL		bDrawTaps;
	BOOL		bDrawSubTaps;
	COLORREF	colTap;
	COLORREF	colSubTap;
	BYTE		btTapSize;
	BYTE		btSubTapSize;

	COLORREF	colTapLabel;
	COLORREF	colSubTapLabel;
	BOOL		bDrawTapLabels;
	BOOL		bDrawSubTabLabels;
	BYTE		btTapLabelFontID;
	BYTE		btSubTapLabelFontID;
	BYTE		btTapLabelSize;
	BYTE		btSubTapLabelSize;
	BYTE		btTabLabelDec;
	BYTE		btSubTabLabelDec;
};

// *************************************************************************************
// *************************************************************************************
//	Struct SFMT_TraceCtrlGrid 
// *************************************************************************************
// *************************************************************************************

struct SFMT_TraceCtrlGrid
{
	BOOL		bEnabled;
	BOOL		bVert;

	BYTE		btAxisID;

	BOOL		bGrid;
	BOOL		bSubGrid;

	COLORREF	colSubGrid;
	COLORREF	colGrid;
	
	int			iSubGridPenStyle;
	int			iGridPenStyle;
};

// *************************************************************************************
//	Struct SFMT_TraceCtrlLine
// *************************************************************************************
// *************************************************************************************

struct SFMT_TraceCtrlLine
{
	BOOL		bVert;
	COLORREF	colLine;
	BYTE		btAxisID;
	double		dPos;
	int			iPenStyle;
	int			iPenSize;
};

// *************************************************************************************
// *************************************************************************************
//	Struct SFMT_TraceCtrlData 
// *************************************************************************************
// *************************************************************************************

struct SFMT_TraceCtrlData
{
	COLORREF	colTrace;
	BYTE		btTraceMode;
	BYTE		btDataType;
	void		*pData;
	DWORD		dwSize;
	BYTE		btPenSize;
	int			iPenStyle;
};

// *************************************************************************************
// *************************************************************************************
//	Class CFMT_TraceCtrl 
// *************************************************************************************
// *************************************************************************************

class CFMT_TraceCtrl : public CFMT_Wnd
{

	DECLARE_DYNCREATE(CFMT_TraceCtrl)

// =====================================================================================
//	VARIABILI
// =====================================================================================

protected:

	// ----- Miscellanous -------------------------------

	// Control style
	DWORD m_dwTCStyle;

	// Trace area
	CRect m_TraceRect;

	// Trace area color
	COLORREF m_colTraceBack;

	// Border area color
	COLORREF m_colBorderBack;

	// Trace area center
	int m_iPX;
	int m_iPY;

	// Trace area scale
	double m_dSX;
	double m_dSY;

	// Axis descriptors
	SFMT_TraceCtrlAxis	m_AxisX;
	SFMT_TraceCtrlAxis	m_AxisY;
	SFMT_TraceCtrlAxis	m_AxisTop;
	SFMT_TraceCtrlAxis	m_AxisBottom;
	SFMT_TraceCtrlAxis	m_AxisLeft;
	SFMT_TraceCtrlAxis	m_AxisRight;

	// Grid
	SFMT_TraceCtrlGrid	m_GridX;
	SFMT_TraceCtrlGrid	m_GridY;

	// Traces
	CFMT_List<SFMT_TraceCtrlData*> m_Traces;	

	// Lines
	CFMT_List<SFMT_TraceCtrlLine*> m_Lines;


public:

// =====================================================================================
// COSTRUTTORI E DISTRUTTORI
// =====================================================================================

public:
	CFMT_TraceCtrl();
	virtual ~CFMT_TraceCtrl();


// =====================================================================================
//	FUNZIONI
// =====================================================================================

private:
    static BOOL m_bRegistered;

protected:

	// Inizializza controllo
	void InitControl(CString sCaption);

	// Compute internal object rects
	void CalcRects();

	// Ritorna il descrittore a partire dall'ID
	SFMT_TraceCtrlAxis* GetAxis(DWORD dwID);

	// Draw backgrounds
	void DrawBorderBackground(CDC *pDC);
	void DrawTraceBackground(CDC *pDC);

	// Draw Axis
	void DrawAxis(CDC *pDC,BYTE btAxisID);
	void DrawAxisHorz(CDC *pDC,BYTE btAxisID,SFMT_TraceCtrlAxis *pA);
	void DrawAxisVert(CDC *pDC,BYTE btAxisID,SFMT_TraceCtrlAxis *pA);

	void DrawAxisTaps(CDC *pDC,BYTE btAxisID);
	void DrawAxisTapsHorz(CDC *pDC,BYTE btAxisID,SFMT_TraceCtrlAxis *pA);
	void DrawAxisTapsVert(CDC *pDC,BYTE btAxisID,SFMT_TraceCtrlAxis *pA);

	void DrawAxisLabels(CDC *pDC,BYTE btAxisID);
	void DrawAxisLabelsHorz(CDC *pDC,BYTE btAxisID,SFMT_TraceCtrlAxis *pA);
	void DrawAxisLabelsVert(CDC *pDC,BYTE btAxisID,SFMT_TraceCtrlAxis *pA);

	void DrawAxisText(CDC *pDC,BYTE btAxisID);
	void DrawAxisTextHorz(CDC *pDC,BYTE btAxisID,SFMT_TraceCtrlAxis *pA);
	void DrawAxisTextVert(CDC *pDC,BYTE btAxisID,SFMT_TraceCtrlAxis *pA);

	void DrawGridHorz(CDC *pDC,BYTE btAxisID);
	void DrawGridVert(CDC *pDC,BYTE btAxisID);
	void DrawGrid(CDC *pDC,BYTE btHAxisID,BYTE btVAxisID);
	
	void DrawTraceCouplesData(CDC *pDC,BYTE btMode,SFMT_TraceCtrlData *pData);
	void DrawTraces(CDC *pDC);

	void DrawLines(CDC *pDC);

	// Main draw function
	void Draw(CDC *pDC); 

	// Distrugge le traccie
	void DestroyTraces();

	// Distrugge le linee
	void DestroyLines();

// **************************************************************************************
//	FUNZIONI PUBBLICHE
// **************************************************************************************

public:

    virtual WNDPROC* GetSuperWndProcAddr();
    static BOOL Register();

	// ---- Inizializzazione -----------------------

	// Creazione
	BOOL Create(CString sClassName, DWORD dwWndStyle,CString sCaption,const RECT &rect,CWnd *pParentWnd, DWORD dwID);
	BOOL Create(DWORD dwWndStyle, DWORD dwTCStyle,const RECT &rect,CWnd *pParentWnd, DWORD dwID);

	// ---- Scroll --------------------------

	void ScrollTo(int iPx,int iPy);
	void ScrollX(int iDx);
	void ScrollY(int iDy);
	void GetScrollPos(int *piPx,int *piPy);
	void Scroll(int iDx,int iDy);

	// ---- Zoom --------------------------

	void SetScale(double dSX,double dSY);
	void GetScale(double *pdSX,double *pdSY);
	void ZoomX(double dZX);
	void ZoomY(double dZY);
	void Zoom(double dZX,double dZY);
	void Zoom(double dZ);

	// ---- Axis --------------------------

	void EnableAxis(BYTE btID,BOOL bEnable);
	void EnableAxisTap(BYTE btID,BOOL bEnable);
	void EnableAxisSubTap(BYTE btID,BOOL bEnable);
	void EnableAxisTapLabel(BYTE btID,BOOL bEnable);
	void EnableAxisSubTapLabel(BYTE btID,BOOL bEnable);
	void EnableAxisText(BYTE btID,BOOL bEnable);

	void SetAxis(BYTE btID,COLORREF col,BYTE btSize,double dScale,double dOffset);
	void SetAxisTap(BYTE btID,COLORREF col,BYTE btSize,double dPitch);
	void SetAxisSubTap(BYTE btID,COLORREF col,BYTE btSize, DWORD dwNum);
	void SetAxisTapLabel(BYTE btID,COLORREF col,BYTE btDec,BYTE btFontID,BYTE btSize);
	void SetAxisSubTapLabel(BYTE btID,COLORREF col,BYTE btDec,BYTE btFontID,BYTE btSize);
	void SetAxisText(BYTE btID,CString sText,CSize size,
					COLORREF col,COLORREF colBack,BYTE btFontID,BYTE btPos,BOOL bTransp);

	void GetAxis(BYTE btID,COLORREF& col,BYTE& btSize,double& dScale,double& dOffset);
	void GetAxisTap(BYTE btID,COLORREF& col,BYTE& btSize,double& dPitch);
	void GetAxisSubTap(BYTE btID,COLORREF& col,BYTE& btSize, DWORD& dwNum);
	void GetAxisTapLabel(BYTE btID,COLORREF& col,BYTE& btDec,BYTE& btFontID,BYTE& btSize);
	void GetAxisSubTapLabel(BYTE btID,COLORREF& col,BYTE& btDec,BYTE& btFontID,BYTE& btSize);
	void GetAxisText(BYTE btID,CString& sText,CSize& size,
					COLORREF& col,COLORREF& colBack,BYTE& btFontID,BYTE& btPos,BOOL& bTransp);

	// ---- Back colors --------------------

	void SetBorderAreaBackColor(COLORREF col);
	void SetTraceAreaBackColor(COLORREF col);

	// ---- Grids --------------------------

	void EnableGridHorz(BOOL bEnable);
	void SetGridHorz(BOOL bEnable,BYTE btID,COLORREF col,int iStyle);
	void SetSubGridHorz(BOOL bEnable,COLORREF col,int iStyle);
	void GetGridHorz(BOOL& bEnable,BYTE& btID,COLORREF& col,int& iStyle);
	void GetSubGridHorz(BOOL& bEnable,COLORREF& col,int& iStyle);

	void EnableGridVert(BOOL bEnable);
	void SetGridVert(BOOL bEnable,BYTE btID,COLORREF col,int iStyle);
	void SetSubGridVert(BOOL bEnable,COLORREF col,int iStyle);
	void GetGridVert(BOOL& bEnable,BYTE& btID,COLORREF& col,int& iStyle);
	void GetSubGridVert(BOOL& bEnable,COLORREF& col,int& iStyle);

	// ---- Traces -------------------------

	DWORD GetNumTraces();
	BOOL InsertTrace(DWORD dwNum,COLORREF col,BYTE btMode,BYTE btType, DWORD dwSize,void *pData,BYTE btPenSize,int iPenStyle);
	BOOL ReplaceTrace(DWORD dwNum,COLORREF col,BYTE btMode,BYTE btType, DWORD dwSize,void *pData,BYTE btPenSize,int iPenStyle);
	//BOOL ReplaceTrace(DWORD dwNum,COLORREF col,BYTE btMode,BYTE btType, DWORD dwSize,void *pData);
	//BOOL ReplaceTrace(DWORD dwNum, DWORD dwSize,void *pData);
	//void* GetTraceData(DWORD dwNum);
	//void RemoveTrace(DWORD dwNum);
	//void RemoveAllTraces();

	// ---- Lines -------------------------

	void InsertLine(DWORD dwNum,BYTE btID,double dPos,BOOL bVert,COLORREF col,int iStyle,int iWidth);
	void RemoveLine(DWORD dwNum);
	void RemoveAllLines();
	void MoveLine(DWORD dwNum,double dPos);


	// ---- Labels -------------------------

	// void InsertLabel(DWORD dwNum,CRect r,CString sText,COLORREF col,COLORREF colBack,BYTE btFontID);
	// void RemoveLabel(DWORD dwNum);
	// void RemoveAllLabels();

	// ---- Gestione Stile --------------------------

	// void SetTCStyle(DWORD dwTCStyle);
	// DWORD GetTCStyle();
	// void ModifyTCStyle(DWORD dwDelStyle, DWORD dwInsStyle);

	// ---- Gestione cursore -----------------------

/*	HCURSOR SetCursor(HCURSOR hCursor)
	{
		return ::SetCursor(hCursor);
	};*/

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFMT_TraceCtrl)
	public:
	virtual BOOL DestroyWindow();
	//}}AFX_VIRTUAL

// *********************************************************************************

// Implementation

	// Generated message map functions
protected:
	//{{AFX_MSG(CFMT_TraceCtrl)
	afx_msg void OnPaint();
	afx_msg void OnNcDestroy();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	afx_msg LRESULT OnFMTScroll(UINT wParam,LONG lParam);
	afx_msg LRESULT OnFMTZoom(UINT wParam,LONG lParam);
	afx_msg LRESULT OnFMTSetAxis(UINT wParam,LONG lParam);
	afx_msg LRESULT OnFMTGetAxis(UINT wParam,LONG lParam);
	afx_msg LRESULT OnFMTBackCol(UINT wParam,LONG lParam);
	afx_msg LRESULT OnFMTTrace(UINT wParam,LONG lParam);
	afx_msg LRESULT OnFMTGrid(UINT wParam,LONG lParam);
	afx_msg LRESULT OnFMTLine(UINT wParam,LONG lParam);

	/*afx_msg void OnFMTSetTCStyle(UINT wParam,LONG lParam);
	afx_msg void OnFMTGetTCStyle(UINT wParam,LONG lParam);
	afx_msg void OnFMTModifyTCStyle(UINT wParam,LONG lParam);*/

	DECLARE_MESSAGE_MAP()
};

// static initialization functions
#ifdef __cplusplus
extern "C" {
#endif
LRESULT CALLBACK FMT_TraceCtrlWndProc(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam);
#ifdef __cplusplus
}
#endif
/////////////////////////////////////////////////////////////////////////////







#endif



