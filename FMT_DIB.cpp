//***************************************************************************
//
// Module:		FMT_DIB.cpp
//
// Description:	Single color management
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
//	1.0		19-01-03	M.Forzieri		First issue
// --------------------------------------------------------------------------
//***************************************************************************

#include "stdafx.h"

#ifndef FMT_DIB_H
#include "FMT_DIB.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// *************************************************************************************
// *************************************************************************************
//	Implementazione classe CFMT_DIB
// *************************************************************************************
// *************************************************************************************

IMPLEMENT_DYNCREATE(CFMT_DIB, CObject)

// =====================================================================================
// COSTRUTTORI E DISTRUTTORI
// =====================================================================================

CFMT_DIB::CFMT_DIB()
{
	m_hHandle=NULL;
}

CFMT_DIB::~CFMT_DIB()
{
	if (m_hHandle!=NULL)
	{
		GlobalFree(m_hHandle);
	}
}

// =====================================================================================
//	OPERATORI
// =====================================================================================

CFMT_DIB& CFMT_DIB::operator=(CFMT_DIB& dib)
{
	dib.CopyTo(*this);

	return (*this);
}


// -----------------------------------------------------------------------------------
//	Function:	operator <<
// -----------------------------------------------------------------------------------

CArchive& AFXAPI operator <<(CArchive& ar, CFMT_DIB& dib)
{
	CFile *pf=ar.GetFile();

	dib.WriteFile(pf);

	return ar;
}

// -----------------------------------------------------------------------------------
//	Function:	operator >>
// -----------------------------------------------------------------------------------

CArchive& AFXAPI operator >>(CArchive& ar, CFMT_DIB& dib)
{
	CFile *pf=ar.GetFile();

	dib.ReadFile(pf);

	return ar;
}

// =====================================================================================
//	FUNZIONI
// =====================================================================================


// -----------------------------------------------------------------------------------
//	Function:	IsValid
// -----------------------------------------------------------------------------------

BOOL CFMT_DIB::IsValid()
{
	return (m_hHandle != NULL);
}

// -----------------------------------------------------------------------------------
//	Function:	DibInfo
// -----------------------------------------------------------------------------------
//  PURPOSE    : Retrieves the DIB info associated with a CF_DIB           
//              format memory block.                                       
//                                                                          
//  RETURNS    : TRUE  - if successful.                                     
//               FALSE - otherwise                                          
// -----------------------------------------------------------------------------------
 
BOOL CFMT_DIB::DibInfo(HANDLE hbi,LPBITMAPINFOHEADER lpbi)
{
    if (hbi)
	{
        *lpbi = *(LPBITMAPINFOHEADER)GlobalLock (hbi);

        /* fill in the default fields */
        if (lpbi->biSize != sizeof (BITMAPCOREHEADER))
		{
            if (lpbi->biSizeImage == 0L)
                                lpbi->biSizeImage = WIDTHBYTES(lpbi->biWidth*lpbi->biBitCount) * lpbi->biHeight;

            if (lpbi->biClrUsed == 0L)
                                lpbi->biClrUsed = DibNumColors (lpbi);
		}
        GlobalUnlock (hbi);
        return TRUE;
    }
    return FALSE;
}

// -----------------------------------------------------------------------------------
//	Function:	GetInfo
// -----------------------------------------------------------------------------------
//  PURPOSE    : Retrieves the DIB info associated with a CF_DIB           
//              format memory block.                                       
//                                                                          
//  RETURNS    : TRUE  - if successful.                                     
//               FALSE - otherwise                                          
// -----------------------------------------------------------------------------------
 
BOOL CFMT_DIB::GetInfo(LPBITMAPINFOHEADER lpbi)
{
	return DibInfo(m_hHandle,lpbi);
}

// -----------------------------------------------------------------------------------
//	Function:	GetWidth
// -----------------------------------------------------------------------------------
//  PURPOSE    : Retrieves the DIB width                                   
//                                                                          
//  RETURNS    : TRUE  - if successful.                                     
//               FALSE - otherwise                                          
// -----------------------------------------------------------------------------------

int CFMT_DIB::GetWidth()
{
	BITMAPINFOHEADER info;

	if (!DibInfo(m_hHandle,&info))
		return -1;

	return info.biWidth;
}

// -----------------------------------------------------------------------------------
//	Function:	GetHeight
// -----------------------------------------------------------------------------------
//  PURPOSE    : Retrieves the DIB height
//                                                                          
//  RETURNS    : TRUE  - if successful.                                     
//               FALSE - otherwise                                          
// -----------------------------------------------------------------------------------

int CFMT_DIB::GetHeight()
{
	BITMAPINFOHEADER info;

	if (!DibInfo(m_hHandle,&info))
		return -1;

	return info.biHeight;
}

// -----------------------------------------------------------------------------------
//	Function:	DibNumColors
// -----------------------------------------------------------------------------------
//  PURPOSE    : Determines the number of colors in the DIB by looking at          
//               the BitCount filed in the info block.                   
//                                                                          
//  RETURNS    : The number of colors in the DIB.                                    
// -----------------------------------------------------------------------------------

WORD CFMT_DIB::DibNumColors (void FAR * pv)
{
    INT                 bits;
    LPBITMAPINFOHEADER  lpbi;
    LPBITMAPCOREHEADER  lpbc;

    lpbi = ((LPBITMAPINFOHEADER)pv);
    lpbc = ((LPBITMAPCOREHEADER)pv);

    /*  With the BITMAPINFO format headers, the size of the palette
     *  is in biClrUsed, whereas in the BITMAPCORE - style headers, it
     *  is dependent on the bits per pixel ( = 2 raised to the power of
     *  bits/pixel).
     */
    if (lpbi->biSize != sizeof(BITMAPCOREHEADER)){
        if (lpbi->biClrUsed != 0)
            return (WORD)lpbi->biClrUsed;
        bits = lpbi->biBitCount;
    }
    else
        bits = lpbc->bcBitCount;

    switch (bits){
        case 1:
                return 2;
        case 4:
                return 16;
        case 8:
                return 256;
        default:
                /* A 24 bitcount DIB has no color table */
                return 0;
    }
}

// -----------------------------------------------------------------------------------
//	Function:	PaletteSize
// -----------------------------------------------------------------------------------
//  PURPOSE    :	Calculates the palette size in bytes. If the info. block 
//					is of the BITMAPCOREHEADER type, the number of colors is 
//					multiplied by 3 to give the palette size, otherwise the  
//					number of colors is multiplied by 4.                                                                                
//  RETURNS    :	The number of colors in the DIB.                                    
// -----------------------------------------------------------------------------------

WORD CFMT_DIB::PaletteSize (void* pv)
{
    LPBITMAPINFOHEADER lpbi;
    WORD               NumColors;

    lpbi      = (LPBITMAPINFOHEADER)pv;
    NumColors = DibNumColors(lpbi);

    if (lpbi->biSize == sizeof(BITMAPCOREHEADER))
        return (WORD)(NumColors * sizeof(RGBTRIPLE));
    else
        return (WORD)(NumColors * sizeof(RGBQUAD));
}

// -----------------------------------------------------------------------------------
//	Function:	ReadBmpHeaderDwordAlign
// -----------------------------------------------------------------------------------
//  PURPOSE    :	read file header (which is packed) and convert into unpacked 
//					BITMAPFILEHEADER strucutre                                                                                
//  RETURNS    :	-
// -----------------------------------------------------------------------------------

void CFMT_DIB::ReadBmpHeaderDwordAlign(CFile *pf, LPBITMAPFILEHEADER pbf, LPDWORD lpdwoff)
{
	DWORD off;

	off = (DWORD)(pf->Seek(0L, CFile::current));
	*lpdwoff = off;

	/* read in bfType*/
	pf->Read((LPSTR) &pbf->bfType, sizeof(WORD));
	/* read in last 3 dwords*/
	pf->Read((LPSTR) &pbf->bfSize, sizeof(DWORD) * 3);
}

// -----------------------------------------------------------------------------------
//	Function:	ReadDibBitmapInfo
// -----------------------------------------------------------------------------------
//  PURPOSE    :	Will read a file in DIB format and return a global HANDLE 
//					to it's BITMAPINFO.  This function will work with both    
//					"old" (BITMAPCOREHEADER) and "new" (BITMAPINFOHEADER)     
//					bitmap formats, but will always return a "new" BITMAPINFO 
//					read file header (which is packed) and convert into unpacked 
//					BITMAPFILEHEADER strucutre                                                                                
//  RETURNS    : A handle to the BITMAPINFO of the DIB in the file.         
// -----------------------------------------------------------------------------------

HANDLE CFMT_DIB::ReadDibBitmapInfo(CFile *pf)
{
    DWORD     off;
    HANDLE    hbi = NULL;
    INT       size;
    INT       i;
    WORD      nNumColors;

    RGBQUAD FAR       *pRgb;
    BITMAPINFOHEADER   bi;
    BITMAPCOREHEADER   bc;
    LPBITMAPINFOHEADER lpbi;
    BITMAPFILEHEADER   bf;
    DWORD              dwWidth = 0;
    DWORD              dwHeight = 0;
    WORD               wPlanes, wBitCount;

    /*if (fh == -1)
        return NULL;*/
	if (pf==NULL)
		return NULL;

#ifdef FIXDWORDALIGNMENT
    /* Reset file pointer and read file header */
    //off = _llseek(fh, 0L, (UINT)SEEK_CUR);
    off = pf->Seek(0L, CFile::current);


    if ((SIZEOF_BITMAPFILEHEADER_PACKED)  != _lread(fh, (LPSTR)&bf, (UINT)sizeof (SIZEOF_BITMAPFILEHEADER_PACKED)))
        return FALSE;
#else
//        ReadBitMapFileHeaderandConvertToDwordAlign(fh, &bf, &off);
        ReadBmpHeaderDwordAlign(pf, &bf, &off);
        /* at this point we have read the file into bf*/
#endif

    /* Do we have a RC HEADER? */
    if (!ISDIB (bf.bfType)) 
	{    
        bf.bfOffBits = 0L;               
        
		pf->Seek(off, CFile::begin); /*seek back to beginning of file*/

		//_llseek(fh, off, (UINT)SEEK_SET); /*seek back to beginning of file*/
    }
/*    if (sizeof (bi) != _lread(fh, (LPSTR)&bi, (UINT)sizeof(bi)))
        return FALSE;*/
    if (sizeof (bi) != pf->Read((LPSTR)&bi, (UINT)sizeof(bi)))
        return FALSE;

    nNumColors = DibNumColors (&bi);

    /* Check the nature (BITMAPINFO or BITMAPCORE) of the info. block
     * and extract the field information accordingly. If a BITMAPCOREHEADER,
     * transfer it's field information to a BITMAPINFOHEADER-style block
     */
    switch (size = (INT)bi.biSize){
        case sizeof (BITMAPINFOHEADER):
            break;

        case sizeof (BITMAPCOREHEADER):

            bc = *(BITMAPCOREHEADER*)&bi;

            dwWidth   = (DWORD)bc.bcWidth;
            dwHeight  = (DWORD)bc.bcHeight;
            wPlanes   = bc.bcPlanes;
            wBitCount = bc.bcBitCount;

        bi.biSize           = sizeof(BITMAPINFOHEADER);
            bi.biWidth              = dwWidth;
            bi.biHeight             = dwHeight;
            bi.biPlanes             = wPlanes;
            bi.biBitCount           = wBitCount;

            bi.biCompression        = BI_RGB;
            bi.biSizeImage          = 0;
            bi.biXPelsPerMeter      = 0;
            bi.biYPelsPerMeter      = 0;
            bi.biClrUsed            = nNumColors;
            bi.biClrImportant       = nNumColors;

//            _llseek(fh, (LONG)sizeof (BITMAPCOREHEADER) - sizeof (BITMAPINFOHEADER), (UINT)SEEK_CUR);
            pf->Seek((LONG)sizeof (BITMAPCOREHEADER) - sizeof (BITMAPINFOHEADER), CFile::current);
            break;

        default:
            /* Not a DIB! */
            return NULL;
    }

    /*  Fill in some default values if they are zero */
    if (bi.biSizeImage == 0){
        bi.biSizeImage = WIDTHBYTES ((DWORD)bi.biWidth * bi.biBitCount)
                         * bi.biHeight;
    }
    if (bi.biClrUsed == 0)
        bi.biClrUsed = DibNumColors(&bi);

    /* Allocate for the BITMAPINFO structure and the color table. */
    hbi = GlobalAlloc (GHND, (LONG)bi.biSize + nNumColors * sizeof(RGBQUAD));
    if (!hbi)
        return NULL;
    lpbi = (LPBITMAPINFOHEADER)GlobalLock (hbi);
    *lpbi = bi;

    /* Get a pointer to the color table */
    pRgb = (RGBQUAD FAR *)((LPSTR)lpbi + bi.biSize);
    if (nNumColors){
        if (size == sizeof(BITMAPCOREHEADER)){
            /* Convert a old color table (3 byte RGBTRIPLEs) to a new
             * color table (4 byte RGBQUADs)
             */
//            _lread(fh, (LPSTR)pRgb, (UINT)nNumColors * sizeof(RGBTRIPLE));
            pf->Read((LPSTR)pRgb, (UINT)nNumColors * sizeof(RGBTRIPLE));

            for (i = nNumColors - 1; i >= 0; i--){
                RGBQUAD rgb;

                rgb.rgbRed      = ((RGBTRIPLE FAR *)pRgb)[i].rgbtRed;
                rgb.rgbBlue     = ((RGBTRIPLE FAR *)pRgb)[i].rgbtBlue;
                rgb.rgbGreen    = ((RGBTRIPLE FAR *)pRgb)[i].rgbtGreen;
                rgb.rgbReserved = (BYTE)0;

                pRgb[i] = rgb;
            }
        }
        else
		{
//            _lread(fh, (LPSTR)pRgb, (UINT)nNumColors * sizeof(RGBQUAD));
            pf->Read((LPSTR)pRgb, (UINT)nNumColors * sizeof(RGBQUAD));
		}
    }

    if (bf.bfOffBits != 0L)
	{
        //_llseek(fh, off + bf.bfOffBits, (UINT)SEEK_SET);
        pf->Seek(off + bf.bfOffBits, CFile::begin);
      }
    GlobalUnlock(hbi);
    return hbi;
}

// -----------------------------------------------------------------------------------
//	Function:	ReadFile
// -----------------------------------------------------------------------------------

BOOL CFMT_DIB::ReadFile(CFile *pf)
{
    BITMAPINFOHEADER    bi;
    LPBITMAPINFOHEADER  lpbi;
    DWORD               dwLen = 0;
    DWORD               dwBits;
    HANDLE              hdib;
    HANDLE              h;

	// If DIB is just created, destroy it
	if (m_hHandle!=NULL)
	{
		GlobalFree(m_hHandle);
	}

	//    hdib = ReadDibBitmapInfo(fh);
    hdib = ReadDibBitmapInfo(pf);
    if (!hdib)
        return FALSE;
    
	DibInfo(hdib,&bi);

    // Calculate the memory needed to hold the DIB
    dwBits = bi.biSizeImage;
    dwLen  = bi.biSize + (DWORD)PaletteSize (&bi) + dwBits;

    // Try to increase the size of the bitmap info. buffer to hold the DIB
    h = GlobalReAlloc(hdib, dwLen, GHND);
    if (!h)
	{
        GlobalFree(hdib);
        hdib = NULL;
    }
    else
	{
        hdib = h;
	}

    // Read in the bits
    if (hdib)
	{
        lpbi = (LPBITMAPINFOHEADER)GlobalLock(hdib);
	
		pf->Read( (LPSTR)lpbi + (WORD)lpbi->biSize + PaletteSize(lpbi),dwBits);
        //lread(fh, (LPSTR)lpbi + (WORD)lpbi->biSize + PaletteSize(lpbi), dwBits);
        GlobalUnlock(hdib);
    }
	// Set the new handle of DIB
	m_hHandle=hdib;

	return TRUE;    
}

// -----------------------------------------------------------------------------------
//	Function:	LoadFile
// -----------------------------------------------------------------------------------
//  PURPOSE    :Open a DIB file and create a MEMORY DIB, a memory handle    
//              containing BITMAPINFO, palette data and the bits.           
//                                                                          
//  RETURNS    :TRUE = OK
// -----------------------------------------------------------------------------------

BOOL CFMT_DIB::LoadFile(CString szFile)
{
	CFile				fb;

    // Open the file and read the DIB information 
	if (!fb.Open(szFile,CFile::modeRead))
	{
		return FALSE;
	}

	ReadFile(&fb);

	fb.Close();

    return TRUE;
}

// -----------------------------------------------------------------------------------
//	Function:	WriteFileHeaderDwordAlign
// -----------------------------------------------------------------------------------
//  PURPOSE    : write header structure (which NOT packed) and write it PACKED
//                                                                          
//  RETURNS    : -
// -----------------------------------------------------------------------------------

void CFMT_DIB::WriteFileHeaderDwordAlign(CFile *pf, LPBITMAPFILEHEADER pbf)
{
	/* write bfType*/
    pf->Write((LPSTR)&pbf->bfType, (UINT)sizeof (WORD));
	/* now pass over extra word, and only write next 3 DWORDS!*/
	pf->Write((LPSTR)&pbf->bfSize, sizeof(DWORD) * 3);
}

// -----------------------------------------------------------------------------------
//	Function:	WriteFile
// -----------------------------------------------------------------------------------

BOOL CFMT_DIB::WriteFile(CFile *pf)
{
    BITMAPFILEHEADER    hdr;
    LPBITMAPINFOHEADER  lpbi;

    lpbi = (LPBITMAPINFOHEADER)GlobalLock (m_hHandle);

    /* Fill in the fields of the file header */
    hdr.bfType          = BFT_BITMAP;
    hdr.bfSize          = GlobalSize (m_hHandle) + SIZEOF_BITMAPFILEHEADER_PACKED;
    hdr.bfReserved1     = 0;
    hdr.bfReserved2     = 0;
    hdr.bfOffBits       = (DWORD) (SIZEOF_BITMAPFILEHEADER_PACKED + lpbi->biSize +
                          PaletteSize(lpbi));
    /* Write the file header */
	#ifdef  FIXDWORDALIGNMENT
		pf->Write((LPSTR)&hdr, (UINT)(SIZEOF_BITMAPFILEHEADER_PACKED));
	#else
        WriteFileHeaderDwordAlign(pf, &hdr);
	#endif

    /* this struct already DWORD aligned!*/
    /* Write the DIB header and the bits */
    pf->Write((LPSTR)lpbi, GlobalSize (m_hHandle));

    GlobalUnlock (m_hHandle);

	return TRUE;
}

// -----------------------------------------------------------------------------------
//	Function:	SaveFile
// -----------------------------------------------------------------------------------
//  PURPOSE    : Write a global handle in CF_DIB format to a file.          
//                                                                          
//  RETURNS    : TRUE  - if successful.                                     
//               FALSE - otherwise                                          
// -----------------------------------------------------------------------------------

BOOL CFMT_DIB::SaveFile (CString szFile)
{
	CFile	fb;

    if (!m_hHandle)
        return FALSE;

	if (!fb.Open(szFile,CFile::modeCreate|CFile::modeWrite))
		return FALSE;

	WriteFile(&fb);

	fb.Close();

    return TRUE;
}

// -----------------------------------------------------------------------------------
//	Function:	Blt
// -----------------------------------------------------------------------------------
//  PURPOSE    : Draws a bitmap in CF_DIB format, using SetDIBits to device.
//               taking the same parameters as BitBlt().                    
//                                                                          
//  RETURNS    : TRUE  - if function succeeds.                              
//               FALSE - otherwise.                                         
// -----------------------------------------------------------------------------------

BOOL CFMT_DIB::Blt(CDC *pDC,int x0,int y0,int dx,int dy,int x1,int y1,LONG rop)
{
    LPBITMAPINFOHEADER   lpbi;
    LPSTR                pBuf;

    if (!m_hHandle)
        return PatBlt(pDC->m_hDC,x0,y0,dx,dy,rop);

    lpbi = (LPBITMAPINFOHEADER)GlobalLock(m_hHandle);

    if (!lpbi)
        return FALSE;

	pBuf = (LPSTR)lpbi + (WORD)lpbi->biSize + PaletteSize(lpbi)+3*lpbi->biWidth*y1;
    
	::SetDIBitsToDevice (pDC->m_hDC, x0, y0, dx, dy,
                       x1,y1,
                       y1,
                       dy,
                       pBuf, (LPBITMAPINFO)lpbi,
                       DIB_RGB_COLORS );

    GlobalUnlock(m_hHandle);
    return TRUE;
}

BOOL CFMT_DIB::Blt(CDC *pDC,CRect& dr,CPoint& ps,LONG rop)
{
	return Blt(pDC,dr.left,dr.top,dr.Width(),dr.Height(),ps.x,ps.y,rop);
}

// -----------------------------------------------------------------------------------
//	Function:	StretchBlt
// -----------------------------------------------------------------------------------
//  PURPOSE    : Draws a bitmap in CF_DIB format, using StretchDIBits()     
//               taking the same parameters as StretchBlt().                
//                                                                          
//  RETURNS    : TRUE  - if function succeeds.                              
//               FALSE - otherwise.                                         
// -----------------------------------------------------------------------------------

BOOL CFMT_DIB::StretchBlt(CDC *pDC,int x,int y,int dx,int dy,int x0,int y0,int dx0,int dy0,LONG rop)
{
    LPBITMAPINFOHEADER lpbi;
    LPSTR        pBuf;
    BOOL         f;

    if (!m_hHandle)
        return PatBlt(pDC->m_hDC,x,y,dx,dy,rop);

    lpbi = (LPBITMAPINFOHEADER)GlobalLock(m_hHandle);

    if (!lpbi)
        return FALSE;

    pBuf = (LPSTR)lpbi + (WORD)lpbi->biSize + PaletteSize(lpbi);

	SetStretchBltMode(pDC->m_hDC,COLORONCOLOR);

    f = ::StretchDIBits (pDC->m_hDC,
                        x, y,
                        dx, dy,
                        x0, y0,
                        dx0, dy0,
                        pBuf, (LPBITMAPINFO)lpbi,
                        DIB_RGB_COLORS,
                        rop);

    GlobalUnlock(m_hHandle);
    return f;
}

BOOL CFMT_DIB::StretchBlt(CDC *pDC,CRect& dr,CRect& sr,LONG rop)
{
	return StretchBlt(pDC,dr.left,dr.top,dr.Width(),dr.Height(),
							sr.left,sr.top,sr.Width(),sr.Height(),rop);
}

// -----------------------------------------------------------------------------------
//	Function:	SetPixel
// -----------------------------------------------------------------------------------

void CFMT_DIB::SetPixel(DWORD row, DWORD col,COLORREF color)
{
    LPBITMAPINFOHEADER lpbi;
    BYTE*        pBuf;
	CFMT_Color ct=color;

    if (!m_hHandle)
        return;

    lpbi = (LPBITMAPINFOHEADER)GlobalLock(m_hHandle);

    pBuf = (BYTE*)((LPSTR)lpbi + (WORD)lpbi->biSize + PaletteSize(lpbi) + 3*(row*lpbi->biWidth+col));

	pBuf[0]=ct.GetB();
	pBuf[1]=ct.GetG();
	pBuf[2]=ct.GetR();

    GlobalUnlock(m_hHandle);
}

// -----------------------------------------------------------------------------------
//	Function:	GetPixel
// -----------------------------------------------------------------------------------

COLORREF CFMT_DIB::GetPixel(DWORD row, DWORD col)
{
    LPBITMAPINFOHEADER lpbi;
    BYTE*        pBuf;
	COLORREF ct;

    if (!m_hHandle)
        return (COLORREF)-1;

    lpbi = (LPBITMAPINFOHEADER)GlobalLock(m_hHandle);

    pBuf = (BYTE*)((LPSTR)lpbi + (WORD)lpbi->biSize + PaletteSize(lpbi) + 3*(row*lpbi->biWidth+col));

	ct=RGB(pBuf[2],pBuf[1],pBuf[0]);

    GlobalUnlock(m_hHandle);

	return ct;
}

// -----------------------------------------------------------------------------------
//	Function:	CopyTo
// -----------------------------------------------------------------------------------

BOOL CFMT_DIB::CopyTo(CFMT_DIB& dest)
{
    BITMAPINFOHEADER    info;
	HANDLE				h;
	void				*pvD,*pvS;
	
	DibInfo(m_hHandle,&info);

    // Calculate the memory needed to hold the DIB
    DWORD dwBits = info.biSizeImage;
    DWORD dwLen  = info.biSize + (DWORD)PaletteSize (&info) + dwBits;

    // Try to increase the size of the bitmap info. buffer to hold the DIB

	if (dest.m_hHandle==NULL)
	{
		h=GlobalAlloc(GHND,dwLen);

		if (!h)
		{
			return FALSE;
		}
		else
		{
			dest.m_hHandle=h;
		}
	}
	else
	{
		GlobalFree(dest.m_hHandle);

		h = GlobalAlloc(GHND,dwLen);

		if (!h)
		{
			return FALSE;
		}
		else
		{
			dest.m_hHandle=h;
		}
	}

	// Copy data

	pvD=GlobalLock(dest.m_hHandle);
	pvS=GlobalLock(m_hHandle);

	::CopyMemory(pvD,pvS,dwLen);

	GlobalUnlock(m_hHandle);
	GlobalUnlock(dest.m_hHandle);

	return TRUE;
}

// ------------------------------------------------------
//	SetMonochrome
// ------------------------------------------------------

BOOL CFMT_DIB::SetMonochrome(COLORREF MonoCol,CRect dr,COLORREF TranspCol)
{
	CFMT_Color col;
	BYTE btNewH;
	BYTE btL,btS;
	BYTE btR,btG,btB;
	int j,k;
	LPBITMAPINFOHEADER lpbi;
	BYTE *pbtStart;
	BITMAPINFOHEADER bmpinfo;
	BYTE *pbtData;;

	GetInfo(&bmpinfo);

	if (bmpinfo.biBitCount!=24)
		return FALSE;

	if ((dr.left<0) || (dr.right>bmpinfo.biWidth) || (dr.top<0) || (dr.bottom>bmpinfo.biHeight))
		return FALSE;

	CFMT_Color temp(MonoCol);
	btNewH=temp.GetHue();

	lpbi=(LPBITMAPINFOHEADER)GlobalLock(m_hHandle);

	pbtStart=(BYTE*)((LPSTR)lpbi + (WORD)lpbi->biSize + PaletteSize(lpbi));

	for (k=dr.bottom-1;k>=dr.top;k--)
	{
		pbtData=(BYTE*)(pbtStart+3*((bmpinfo.biHeight-k-1)*bmpinfo.biWidth+dr.left));

		for (j=dr.left;j<dr.right;j++)
		{
			btB=pbtData[0];
			btG=pbtData[1];
			btR=pbtData[2];

			col=RGB(btR,btG,btB);

			if (col!=TranspCol)
			{
				btL=col.GetLuminosity();
				btS=col.GetSaturation();

				col.SetHLS(btNewH,btL,temp.GetSaturation());

				pbtData[0]=col.GetB();
				pbtData[1]=col.GetG();
				pbtData[2]=col.GetR();
			}

			pbtData+=3;

		}
	}

	GlobalUnlock(m_hHandle);

	return TRUE;

}

BOOL CFMT_DIB::SetMonochrome(COLORREF MonoCol,COLORREF TranspCol)
{
	BITMAPINFOHEADER bmpinfo;

	GetInfo(&bmpinfo);

	if (bmpinfo.biBitCount!=24)
		return FALSE;

	CRect dr;
	dr.left=0;
	dr.right=bmpinfo.biWidth;
	dr.top=0;
	dr.bottom=bmpinfo.biHeight;
	
	return SetMonochrome(MonoCol,dr,TranspCol);

}

// ------------------------------------------------------
//	ChangeLuminosity
// ------------------------------------------------------

BOOL CFMT_DIB::ChangeLuminosity(double dLumFact,CRect dr,COLORREF TranspCol)
{
	CFMT_Color col;
	BYTE btR,btG,btB;
	int j,k;
	LPBITMAPINFOHEADER lpbi;
	BYTE *pbtStart;
	BITMAPINFOHEADER bmpinfo;
	BYTE *pbtData;;

	GetInfo(&bmpinfo);

	if (bmpinfo.biBitCount!=24)
		return FALSE;

	if ((dr.left<0) || (dr.right>bmpinfo.biWidth) || (dr.top<0) || (dr.bottom>bmpinfo.biHeight))
		return FALSE;

	lpbi=(LPBITMAPINFOHEADER)GlobalLock(m_hHandle);

	pbtStart=(BYTE*)((LPSTR)lpbi + (WORD)lpbi->biSize + PaletteSize(lpbi));

	for (k=dr.bottom-1;k>=dr.top;k--)
	{
		pbtData=(BYTE*)(pbtStart+3*((bmpinfo.biHeight-k-1)*bmpinfo.biWidth+dr.left));

		for (j=dr.left;j<dr.right;j++)
		{
			btB=pbtData[0];
			btG=pbtData[1];
			btR=pbtData[2];

			col=RGB(btR,btG,btB);

			if (col!=TranspCol)
			{
				col.SetLuminosity((BYTE)(min(col.GetLuminosity()*dLumFact,240)));

				pbtData[0]=col.GetB();
				pbtData[1]=col.GetG();
				pbtData[2]=col.GetR();
			}

			pbtData+=3;

		}
	}

	GlobalUnlock(m_hHandle);

	return TRUE;
}

BOOL CFMT_DIB::ChangeLuminosity(double dLumFact,COLORREF TranspCol)
{
	BITMAPINFOHEADER bmpinfo;

	GetInfo(&bmpinfo);

	if (bmpinfo.biBitCount!=24)
		return FALSE;

	CRect dr;
	dr.left=0;
	dr.right=bmpinfo.biWidth;
	dr.top=0;
	dr.bottom=bmpinfo.biHeight;
	
	return ChangeLuminosity(dLumFact,dr,TranspCol);

}

// ------------------------------------------------------
//	ChangeSaturation
// ------------------------------------------------------

BOOL CFMT_DIB::ChangeSaturation(double dLumFact,CRect dr,COLORREF TranspCol)
{
	CFMT_Color col;
	BYTE btR,btG,btB;
	int j,k;
	LPBITMAPINFOHEADER lpbi;
	BYTE *pbtStart;
	BITMAPINFOHEADER bmpinfo;
	BYTE *pbtData;;

	GetInfo(&bmpinfo);

	if (bmpinfo.biBitCount!=24)
		return FALSE;

	if ((dr.left<0) || (dr.right>bmpinfo.biWidth) || (dr.top<0) || (dr.bottom>bmpinfo.biHeight))
		return FALSE;

	lpbi=(LPBITMAPINFOHEADER)GlobalLock(m_hHandle);

	pbtStart=(BYTE*)((LPSTR)lpbi + (WORD)lpbi->biSize + PaletteSize(lpbi));

	for (k=dr.bottom-1;k>=dr.top;k--)
	{
		pbtData=(BYTE*)(pbtStart+3*((bmpinfo.biHeight-k-1)*bmpinfo.biWidth+dr.left));

		for (j=dr.left;j<dr.right;j++)
		{
			btB=pbtData[0];
			btG=pbtData[1];
			btR=pbtData[2];

			col=RGB(btR,btG,btB);

			if (col!=TranspCol)
			{
				col.SetSaturation((BYTE)(min(col.GetSaturation()*dLumFact,240)));

				pbtData[0]=col.GetB();
				pbtData[1]=col.GetG();
				pbtData[2]=col.GetR();
			}

			pbtData+=3;

		}
	}

	GlobalUnlock(m_hHandle);

	return TRUE;
}

BOOL CFMT_DIB::ChangeSaturation(double dLumFact,COLORREF TranspCol)
{
	BITMAPINFOHEADER bmpinfo;

	GetInfo(&bmpinfo);

	if (bmpinfo.biBitCount!=24)
		return FALSE;

	CRect dr;
	dr.left=0;
	dr.right=bmpinfo.biWidth;
	dr.top=0;
	dr.bottom=bmpinfo.biHeight;
	
	return ChangeSaturation(dLumFact,dr,TranspCol);

}
