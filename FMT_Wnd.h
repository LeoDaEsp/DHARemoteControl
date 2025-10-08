//***************************************************************************
//
// Module:		FMT_Wnd.h
//
// Description:	Base class for custom controls
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


#ifndef FMT_WND_H
#define FMT_WND_H

#ifndef FMT_DIB_H
#include "FMT_DIB.h"
#endif



// *************************************************************************************
// *************************************************************************************
//	Class CFMT_Wnd
// *************************************************************************************
// *************************************************************************************

// Styles

#define FMTWND_NO_BORDER					0x00000000
#define FMTWND_SIMPLE_BORDER				0x00000001
#define FMTWND_SOFTRELIEF_BORDER			0x00000002
#define FMTWND_MEDIUMRELIEF_BORDER			0x00000003
#define FMTWND_HARDRELIEF_BORDER			0x00000004
#define FMTWND_SOFTSUNKEN_BORDER			0x00000005
#define FMTWND_MEDIUMSUNKEN_BORDER			0x00000006
#define FMTWND_HARDSUNKEN_BORDER			0x00000007
#define FMTWND_SOFTETCHED_BORDER			0x00000008
#define FMTWND_MEDIUMETCHED_BORDER			0x00000009
#define FMTWND_HARDETCHED_BORDER			0x0000000A
#define FMTWND_SOFTRAISED_BORDER			0x0000000B
#define FMTWND_HARDRAISED_BORDER			0x0000000C
#define FMTWND_SOFTFRAME_BORDER				0x0000000D
#define FMTWND_HARDFRAME_BORDER				0x0000000E
#define FMTWND_SOFTCONVEX_BORDER			0x0000000F
#define FMTWND_HARDCONVEX_BORDER			0x00000010

#define FMTWND_SHADED1_BORDER				0x00000011

#define FMTWND_DOUBLE_BORDER				0x0000001A

#define FMTWND_NO_BACKGROUND				0x00000000
#define FMTWND_COLOR_BACKGROUND				0x00000100
#define FMTWND_BRUSH_BACKGROUND				0x00000200
#define FMTWND_BMP_BACKGROUND				0x00000300
#define FMTWND_TRANSPARENT_BACKGROUND		0x00000400


// ----- Base FMWND Command ---------------------------------------------------

#define FMTWND_SETSTYLE_MESS				WM_USER+1
#define FMTWND_GETSTYLE_MESS				WM_USER+2
#define FMTWND_MODIFYSTYLE_MESS				WM_USER+3
#define FMTWND_SETBACKGROUNDCOLOR_MESS		WM_USER+4
#define FMTWND_GETBACKGROUNDCOLOR_MESS		WM_USER+5
#define FMTWND_ADDFONT_MESS					WM_USER+6
#define FMTWND_ATTACHFONT_MESS				WM_USER+7
#define FMTWND_DELETEFONT_MESS				WM_USER+8
#define FMTWND_GETNUMFONTS_MESS				WM_USER+9
#define FMTWND_GETFONT_MESS					WM_USER+10
#define FMTWND_SETBACKGROUNDBRUSH_MESS		WM_USER+11
#define FMTWND_GETBACKGROUNDBRUSH_MESS		WM_USER+12
#define FMTWND_SETBORDERCOLOR_MESS			WM_USER+13
#define FMTWND_GETBORDERCOLOR_MESS			WM_USER+14
#define FMTWND_REDRAWFULL_MESS				WM_USER+15
#define FMTWND_LOADBACKGROUNDBMP_MESS		WM_USER+16
#define FMTWND_SETBACKGROUNDBMP_MESS		WM_USER+17
#define FMTWND_GETBACKGROUNDBMP_MESS		WM_USER+18

#define FMTWND_END_MESSAGE_LIST				WM_USER+19

// ----- Macros ------------------------------------------------------

#define	ON_FMTWND_SETSTYLE(funct)				ON_MESSAGE(FMTWND_SETSTYLE_MESS,funct)
#define	ON_FMTWND_GETSTYLE(funct)				ON_MESSAGE(FMTWND_GETSTYLE_MESS,funct)
#define	ON_FMTWND_SETBACKGROUNDCOLOR(funct)		ON_MESSAGE(FMTWND_SETBACKGROUNDCOLOR_MESS,funct)
#define	ON_FMTWND_GETBACKGROUNDCOLOR(funct)		ON_MESSAGE(FMTWND_GETBACKGROUNDCOLOR_MESS,funct)
#define	ON_FMTWND_MODIFYSTYLE(funct)			ON_MESSAGE(FMTWND_MODIFYSTYLE_MESS,funct)
#define	ON_FMTWND_ADDFONT(funct)				ON_MESSAGE(FMTWND_ADDFONT_MESS,funct)
#define	ON_FMTWND_ATTACHFONT(funct)				ON_MESSAGE(FMTWND_ATTACHFONT_MESS,funct)
#define	ON_FMTWND_DELETEFONT(funct)				ON_MESSAGE(FMTWND_DELETEFONT_MESS,funct)
#define	ON_FMTWND_GETNUMFONTS(funct)			ON_MESSAGE(FMTWND_GETNUMFONTS_MESS,funct)
#define	ON_FMTWND_GETFONT(funct)				ON_MESSAGE(FMTWND_GETFONT_MESS,funct)
#define	ON_FMTWND_SETBACKGROUNDBRUSH(funct)		ON_MESSAGE(FMTWND_SETBACKGROUNDBRUSH_MESS,funct)
#define	ON_FMTWND_GETBACKGROUNDBRUSH(funct)		ON_MESSAGE(FMTWND_GETBACKGROUNDBRUSH_MESS,funct)
#define	ON_FMTWND_SETBORDERCOLOR(funct)			ON_MESSAGE(FMTWND_SETBORDERCOLOR_MESS,funct)
#define	ON_FMTWND_GETBORDERCOLOR(funct)			ON_MESSAGE(FMTWND_GETBORDERCOLOR_MESS,funct)
#define	ON_FMTWND_REDRAWFULL(funct)				ON_MESSAGE(FMTWND_REDRAWFULL_MESS,funct)
#define	ON_FMTWND_LOADBACKGROUNDBMP(funct)		ON_MESSAGE(FMTWND_LOADBACKGROUNDBMP_MESS,funct)
#define	ON_FMTWND_SETBACKGROUNDBMP(funct)		ON_MESSAGE(FMTWND_SETBACKGROUNDBMP_MESS,funct)
#define	ON_FMTWND_GETBACKGROUNDBMP(funct)		ON_MESSAGE(FMTWND_GETBACKGROUNDBMP_MESS,funct)

// *************************************************************************************
// *************************************************************************************
//	Struct SFMT_Control_Notify
// *************************************************************************************
// *************************************************************************************

struct SFMT_Control_Notify
{
    NMHDR hdr;   
    WORD wVKey;  
	WORD wVKeySpecial;
    DWORD dwFlags; 
	CPoint point;
	CSize size;
	DWORD dwStatus;
};

class CFMT_Wnd : public CWnd
{
	DECLARE_DYNCREATE(CFMT_Wnd)

// =====================================================================================
//	VARIABILI
// =====================================================================================

	struct SFMT_WndRemovableItem
	{
		void* pItem;
		BOOL bDeletable;
	};

protected:
	
	// FM Style per non client area
	DWORD m_dwStyle;

	// Colore per il bordo
	CFMT_Color m_colBorder;

	// Brush per background
	CBrush *m_pBackgroundBrush;

	// Bitmap per background
	CFMT_DIB m_BackgroundBmp;

	// Colore per background
	COLORREF m_BackgroundColor;

	// Penne per il disegno della non client area
	CPen *m_ppBorderPen[5];

	// Lista di fonts della finestra
	CFMT_List<SFMT_WndRemovableItem*> m_FontList;

	// Handle bitmap di background
	HBITMAP m_hBackgroundBmp;

	// Appoggio per calcolo parametri
	DWORD m_dwParamPos;

	// Appoggio per calcolo client rect
	CRect m_MarginCR;

public:

// =====================================================================================
// COSTRUTTORI E DISTRUTTORI
// =====================================================================================

public:
	
	CFMT_Wnd();
	virtual ~CFMT_Wnd();

// =====================================================================================
// FUNZIONI
// =====================================================================================

private:

	// Disegno 
	void DrawSimpleBorder(CDC *pDC);
	void DrawSoftReliefBorder(CDC *pDC);
	void DrawMediumReliefBorder(CDC *pDC);
	void DrawHardReliefBorder(CDC *pDC);
	void DrawSoftSunkenBorder(CDC *pDC);
	void DrawMediumSunkenBorder(CDC *pDC);
	void DrawHardSunkenBorder(CDC *pDC);
	void DrawSoftEtchedBorder(CDC *pDC);
	void DrawMediumEtchedBorder(CDC *pDC);
	void DrawHardEtchedBorder(CDC *pDC);
	void DrawSoftRaisedBorder(CDC *pDC);
	void DrawHardRaisedBorder(CDC *pDC);
	void DrawSoftFrameBorder(CDC *pDC);
	void DrawHardFrameBorder(CDC *pDC);
	void DrawSoftConvexBorder(CDC *pDC);
	void DrawHardConvexBorder(CDC *pDC);
	void DrawShaded1Border(CDC *pDC);
	void DrawDoubleBorder(CDC *pDC);

	// Inizializzazione
	void CreatePens();
	void DeletePens();

	// Disegno della non client area
	void DrawNcArea(CDC *pDC);

protected:
	
	// Disegno 
	CDC* GetBackBufferDC(CDC *pDC);
	CDC* GetBackBufferDC(CDC *pDC,int iPosX,int iPosY, DWORD dwDimX, DWORD dwDimY,HBITMAP *phBmp);
	void ReleaseBackBufferDC(CDC *pDC);
	void CopyBackBufferDC(CDC *pDDC,CDC *pSDC,CRect *pSRC=NULL);

	// Parametri caption
	BOOL GetFirstParam(CString sCaption,CString *psParam);
	BOOL GetFirstParam(CString sCaption,int *piParam);
	BOOL GetFirstParam(CString sCaption,COLORREF *pColor);

	BOOL GetNextParam(CString sCaption,CString *psParam);
	BOOL GetNextParam(CString sCaption,int *piParam);
	BOOL GetNextParam(CString sCaption,COLORREF *pColor);

	// Miscellaneous
	void SetClientRect(CRect *pCR);
	CRect GetCRFromStyle(DWORD dwStyle);
	CFont* GetFont(DWORD dwIdx);

public:

	// ---- Inizializzazione -------------------------------

	virtual BOOL Create(LPCTSTR lpszClassName,LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect,CWnd* pParentWnd,UINT nID,CCreateContext* pContext=NULL);

	// Styles -----------------------------------------------
	
	void SetFMTStyle(DWORD dwStyle,BOOL bRecalcCR=TRUE);	
	DWORD GetFMTStyle();	
	void ModifyFMTStyle(DWORD dwDelStyle, DWORD dwInsStyle);

	// ---- Gestione non client area ----------------------------

	void SetBorderColor(COLORREF col);
	void GetBorderColor(COLORREF& col);

	// ---- Disegno -------------------------------------------

	void RedrawFullWindow();
	
	// ---- Gestione fonts  --------------------------------------
	
	virtual void InsertFont(DWORD dwIdx,CFont *pFont);
	virtual void AttachFont(DWORD dwIdx,CFont *pFont); 
	virtual void DeleteFont(DWORD dwIdx); 
	DWORD GetNumFonts();
	void GetFont(DWORD dwIdx,LOGFONT* pFont);

	// Gestione background ---------------------------------------

	virtual void SetBackgroundColor(COLORREF col);	
	virtual COLORREF GetBackgroundColor();
	
	virtual void SetBackgroundBrush(CBrush *pBrush);
	virtual void SetBackgroundBrush(LOGBRUSH *pBrush);
	virtual void GetBackgroundBrush(CBrush *pBrush);
	virtual void GetBackgroundBrush(LOGBRUSH *pBrush);
	
	virtual BOOL LoadBackgroundBmp(CString sName);
	virtual void SetBackgroundBmp(CFMT_DIB *pBmp);
	virtual CFMT_DIB* GetBackgroundBmp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFMT_Wnd)
	//}}AFX_VIRTUAL

// Implementation
public:

	LRESULT OnNewNcPaint(UINT wParam,LONG lParam);
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CFMT_Wnd)
	afx_msg BOOL OnNcCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
	//}}AFX_MSG

	afx_msg LRESULT OnFMSetStyle(UINT wParam,LONG lParam);
	afx_msg LRESULT OnFMGetStyle(UINT wParam,LONG lParam);
	afx_msg LRESULT OnFMModifyStyle(UINT wParam,LONG lParam);
	afx_msg LRESULT OnFMSetBackgroundColor(UINT wParam,LONG lParam);
	afx_msg LRESULT OnFMGetBackgroundColor(UINT wParam,LONG lParam);
	afx_msg virtual LRESULT OnFMSetBackgroundBrush(UINT wParam,LONG lParam);
	afx_msg LRESULT OnFMGetBackgroundBrush(UINT wParam,LONG lParam);
	afx_msg LRESULT OnFMAddFont(UINT wParam,LONG lParam);
	afx_msg LRESULT OnFMAttachFont(UINT wParam,LONG lParam);
	afx_msg LRESULT OnFMDeleteFont(UINT wParam,LONG lParam);
	afx_msg LRESULT OnFMGetNumFonts(UINT wParam,LONG lParam);
	afx_msg LRESULT OnFMGetFont(UINT wParam,LONG lParam);
	afx_msg LRESULT OnFMSetBorderColor(UINT wParam,LONG lParam);
	afx_msg LRESULT OnFMGetBorderColor(UINT wParam,LONG lParam);
	afx_msg LRESULT OnFMRedrawFullWindow(UINT wParam,LONG lParam);

	afx_msg LRESULT OnFMTLoadBackBmp(UINT wParam,LONG lParam);
	afx_msg LRESULT OnFMTSetBackBmp(UINT wParam,LONG lParam);
	afx_msg LRESULT OnFMTGetBackBmp(UINT wParam,LONG lParam);

	DECLARE_MESSAGE_MAP()
};

#endif



