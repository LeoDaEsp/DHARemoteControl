// =====================================================================================
/**
 * @file					FMT_HdwByteOutBufferService.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					10/01/2020
 * @brief					Abstract Hardware Byte Output Buffer Service
 *
 * @version	Project:		Formatech C++ Core Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][10/01/2020]
 */
// =====================================================================================



#ifndef FMTDEF_HDW_BYTEOUTBUFFERSERVICE_H
#define FMTDEF_HDW_BYTEOUTBUFFERSERVICE_H

// =====================================================================================
//	INCLUDES
// =====================================================================================


#ifndef FMTDEF_CORE_H
#include "FMT_Core.h"
#endif

#ifndef FMTDEF_HDW_SERVICE_H
#include "FMT_HdwService.h"
#endif


// =====================================================================================
//	DEFINES
// =====================================================================================



// *************************************************************************************
// *************************************************************************************
//	Class CFMT_HdwByteOutBufferService
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_HdwByteOutBufferService : public CFMT_HdwService
{
// =====================================================================================
//	TYPES
// =====================================================================================

protected:
public:

    // --- CParameters ---------------------------------------------------------

    class FMTDEF_LIB_DLLSPEC CParameters : public CFMT_HdwService::CParameters
    {
    public:
        t_FMT_Uint32			m_uiBufferSize;

        CParameters();
    };


    // =====================================================================================
    //	VARIABLES
    // =====================================================================================

protected:

    t_FMT_Uint32				m_uiBufferSize;     //! Buffer Size

public:

// =====================================================================================
// CONSTRUCTORS & DESTRUCTORS
// =====================================================================================

public:

    //! Empty constructor
    CFMT_HdwByteOutBufferService(CFMT_HdwObject *pPort);

    //! Destructor
    virtual ~CFMT_HdwByteOutBufferService();


// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:
public:

    //! Return the service parameters
    virtual t_FMT_Uint32		GetParameters(CParameters *pParameters);

    //! Set the service parameters
    virtual t_FMT_Uint32		SetParameters(CParameters *pParameters);

    //! Return the size of input buffer
    t_FMT_Uint32                GetBufferSize();

    //! Write dwSize bytes to the output buffer
    virtual t_FMT_Uint32		Write(t_FMT_Uint8 *pbtBuf, t_FMT_Uint32 dwSize, t_FMT_Uint32 dwTimeout);

    //! Return the number of bytes stored into output buffer
    virtual t_FMT_Uint32		GetBytesToBeWritten(t_FMT_Uint32& uiNob);

    //! Reset the output buffer
    virtual t_FMT_Uint32		ResetWriteBuffer();

};



#endif







