// =====================================================================================
/**
 * @file					FMT_WinBitmapData.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					07/08/2021
 * @brief					Manages data of Windows Bitmap
 *
 * @version	Project:		Formatech C++ Core Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][07/08/2021]
 */
// =====================================================================================



#ifndef FMTDEF_WINBITMAPDATA_H
#define FMTDEF_WINBITMAPDATA_H

// =====================================================================================
//	INCLUDES
// =====================================================================================


#ifndef FMTDEF_GLOBAL_H
#include "FMT_Global.h"
#endif

#ifndef FMTDEF_OBJECT_H
#include "FMT_Object.h"
#endif

#ifndef FMTDEF_EXCEPTION_H
#include "FMT_Exception.h"
#endif

#ifndef FMTDEF_STRING_H
#include "FMT_String.h"
#endif

#ifndef FMTDEF_FILE_H
#include "FMT_File.h"
#endif

#ifndef FMTDEF_BASICCONTAINERS_H
#include "FMT_BasicContainers.h"
#endif

using namespace FMT;


// =====================================================================================
//	DEFINES
// =====================================================================================



// *************************************************************************************
// *************************************************************************************
//	Class CFMT_WinBitmapData
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_WinBitmapData : public CFMT_Object
{
    // =====================================================================================
    //	TYPES
    // =====================================================================================

public:


    // =====================================================================================
    //	VARIABLES
    // =====================================================================================

protected:

public:

    struct FMTDEF_LIB_DLLSPEC SInfoHeader
    {
        t_FMT_Uint32        m_uiSize;
        t_FMT_Int32         m_iWidth;
        t_FMT_Int32         m_iHeight;
        t_FMT_Uint16        m_usPlanes;
        t_FMT_Uint16        m_usBitCount;
        t_FMT_Uint32        m_uiCompression;
        t_FMT_Uint32        m_uiSizeImage;
        t_FMT_Int32         m_iXPelsPerMeter;
        t_FMT_Int32         m_iYPelsPerMeter;
        t_FMT_Uint32        m_uiClrUsed;
        t_FMT_Uint32        m_uiClrImportant;
    };

    enum t_Version
    {
        e_Version_3     = 0x28,
        e_Version_4     = 0x6C,
        e_Version_5     = 0x7C
    };

    enum t_Compression
    {
        e_Compression_BI_RGB        = 0,
        e_Compression_BI_RLE8       = 1,
        e_Compression_BI_RLE4       = 2,
        e_Compression_BI_BITFIELDS  = 3,
        e_Compression_BI_JPEG       = 4,
        e_Compression_BI_PNG        = 5
    };


// =====================================================================================
// CONSTRUCTORS & DESTRUCTORS
// =====================================================================================

public:

    //! Empty constructor
    CFMT_WinBitmapData();

    //! Destructor
    virtual ~CFMT_WinBitmapData();

// =====================================================================================
// VARIABLES
// =====================================================================================

protected:

    SInfoHeader         m_Info;
    t_FMT_Uint32        m_uiDataOffset;
    CFMT_Uint32Vector   m_Palette;
    t_FMT_Uint32        m_uiAlignment;
    t_FMT_Uint32        m_uiRowBufferLen;

public:

    CFMT_Uint8Vector    m_DataBuffer;

// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:

    static t_FMT_Uint32     ReadInfoFromFile(CFMT_File& SrcFile, CFMT_WinBitmapData::SInfoHeader& info, t_FMT_Uint32 *puiDataOffset = FMTDEF_NULL);
    t_FMT_Uint32            GetPixelColorIndexNoCheck(t_FMT_Uint32 uiCol, t_FMT_Uint32 uiRow, t_FMT_Uint32& colidx);
    void                    SetIntParams();


public:

    //! Read the info header of a bitmap from file
    static t_FMT_Uint32     ReadInfoFromFile(const CFMT_String& sFilePath, CFMT_WinBitmapData::SInfoHeader& info, t_FMT_Uint32 *puiDataOffset = FMTDEF_NULL);

    //! Load a bitmap from file
    t_FMT_Uint32            LoadFromFile(const CFMT_String& sFilePath);

    //! Get the info of the bitmap
    const SInfoHeader*      GetInfo();

    //! Destroy data content
    void                    Destroy();


    //! Get the number of palette entries from a info structure
    static t_FMT_Uint32     GetPaletteDepth(CFMT_WinBitmapData::SInfoHeader& info);

    //! Get the number of palette entries of the bitmap
    t_FMT_Uint32            GetPaletteDepth();

    //! Get a palette entry
    t_FMT_Uint32            GetPaletteEntry(t_FMT_Uint32 uiIndex);

    //! Get Pixel Color
    t_FMT_Uint32            GetPixelColor(t_FMT_Uint32 uiCol, t_FMT_Uint32 uiRow, t_WinRgbQuad& rgbcol);

    //! Get Pixel Color Index
    t_FMT_Uint32            GetPixelColorIndex(t_FMT_Uint32 uiCol, t_FMT_Uint32 uiRow, t_FMT_Uint32& colidx);
};



#endif







