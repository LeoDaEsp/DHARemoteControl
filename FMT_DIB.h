#ifndef FMT_DIB_H
#define FMT_DIB_H


// *************************************************************************************
// *************************************************************************************
//	Class CFMT_DIB
// *************************************************************************************
// *************************************************************************************

#define MAXREAD  32768                 /* Number of bytes to be read during */
                                       /* each read operation.              */

/* Header signatutes for various resources */
#define BFT_ICON   0x4349   /* 'IC' */
#define BFT_BITMAP 0x4d42   /* 'BM' */
#define BFT_CURSOR 0x5450   /* 'PT' */

/* macro to determine if resource is a DIB */
#define ISDIB(bft) ((bft) == BFT_BITMAP)

/* Macro to determine to round off the given value to the closest byte */
#define WIDTHBYTES(i)   ((i+31)/32*4)

#define SIZEOF_BITMAPFILEHEADER_PACKED  (   \
    sizeof(WORD) +      /* bfType      */   \
    sizeof(DWORD) +     /* bfSize      */   \
    sizeof(WORD) +      /* bfReserved1 */   \
    sizeof(WORD) +      /* bfReserved2 */   \
    sizeof(DWORD))      /* bfOffBits   */

class CFMT_DIB : public CObject
{

	DECLARE_DYNCREATE(CFMT_DIB)

// =====================================================================================
//	VARIABILI
// =====================================================================================



protected:

	HANDLE m_hHandle;

public:

// =====================================================================================
// COSTRUTTORI E DISTRUTTORI
// =====================================================================================

public:
	CFMT_DIB();

	virtual ~CFMT_DIB();

// =====================================================================================
// OPERATORI
// =====================================================================================

public:

	CFMT_DIB& operator=(CFMT_DIB& dib);

// =====================================================================================
// FUNZIONI
// =====================================================================================

private:


protected:

	void ReadBmpHeaderDwordAlign(CFile *pf, LPBITMAPFILEHEADER pbf, LPDWORD lpdwoff);
	void WriteFileHeaderDwordAlign(CFile *pf, LPBITMAPFILEHEADER pbf);
	HANDLE ReadDibBitmapInfo(CFile *pf);

	BOOL WriteFile(CFile *pf);
	BOOL ReadFile(CFile *pf);

	BOOL DibInfo (HANDLE hbi,LPBITMAPINFOHEADER lpbi);

public:

	BOOL IsValid();
	
	BOOL GetInfo(LPBITMAPINFOHEADER lpbi);

	int GetWidth();
	int GetHeight();

	WORD DibNumColors (void FAR * pv);
	WORD PaletteSize (void* pv);

	BOOL LoadFile(CString szFile);
	BOOL SaveFile(CString szFile);

	BOOL Blt(CDC *pDC,int x0,int y0,int dx,int dy,int x1,int y1,LONG rop);
	BOOL Blt(CDC *pDC,CRect& dr,CPoint& ps,LONG rop);

	BOOL StretchBlt(CDC *pDC,int x,int y,int dx,int dy,int x0,int y0,int dx0,int dy0,LONG rop);
	BOOL StretchBlt(CDC *pDC,CRect& dr,CRect& sr,LONG rop);

	void SetPixel(DWORD row, DWORD col,COLORREF color);
	COLORREF GetPixel(DWORD row, DWORD col);




	BOOL CopyTo(CFMT_DIB& dest);

	HBITMAP GetBitmapHandle(HPALETTE hpal);

	BOOL SetMonochrome(COLORREF MonoCol,COLORREF TranspCol=0xFFFFFFFF);
	BOOL SetMonochrome(COLORREF MonoCol,CRect dr,COLORREF TranspCol=0xFFFFFFFF);

	BOOL ChangeLuminosity(double dLumFact,COLORREF TranspCol=0xFFFFFFFF);
	BOOL ChangeLuminosity(double dLumFact,CRect dr,COLORREF TranspCol=0xFFFFFFFF);

	BOOL ChangeSaturation(double dLumFact,COLORREF TranspCol=0xFFFFFFFF);
	BOOL ChangeSaturation(double dLumFact,CRect dr,COLORREF TranspCol=0xFFFFFFFF);

	friend CArchive& AFXAPI operator<<(CArchive& ar, CFMT_DIB& dib);
	friend CArchive& AFXAPI operator>>(CArchive& ar, CFMT_DIB& dib);
};

#endif

