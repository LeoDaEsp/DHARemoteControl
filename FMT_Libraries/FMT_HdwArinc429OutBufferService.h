// =====================================================================================
/**
 * @file					FMT_HdwArinc429OutBufferService.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					10/01/2020
 * @brief					Abstract Hardware Arinc429 Byte Output Buffer Service
 *
 * @version	Project:		Formatech C++ Hardware Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][10/01/2020]
 */
// =====================================================================================



#ifndef FMTDEF_HDW_ARINC429OUTBUFFERSERVICE_H
#define FMTDEF_HDW_ARINC429OUTBUFFERSERVICE_H

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


#ifndef FMTDEF_HDW_SERVICE_H
#include "FMT_HdwService.h"
#endif

#ifndef FMTDEF_HDW_ARINC429MESSAGE_H
#include "FMT_HdwArinc429Message.h"
#endif


// =====================================================================================
//	DEFINES
// =====================================================================================



// *************************************************************************************
// *************************************************************************************
//	Class CFMT_HdwArinc429OutBufferService
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_HdwArinc429OutBufferService : public CFMT_HdwService
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

    t_FMT_Uint32						m_uiBufferSize;     //! Buffer Size
    CFMT_HdwArinc429MessageList			m_Buffer;           //! Buffer

public:


// =====================================================================================
// CONSTRUCTORS & DESTRUCTORS
// =====================================================================================

public:

    //! Empty constructor
    CFMT_HdwArinc429OutBufferService(CFMT_HdwObject *pPort);

    //! Destructor
    virtual ~CFMT_HdwArinc429OutBufferService();


// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:
public:

    //! Return the service parameters
    virtual t_FMT_Uint32		GetParameters(CParameters *pParameters);

    //! Set the service parameters
    virtual t_FMT_Uint32		SetParameters(CParameters *pParameters);

    //! Return the number of words into buffer
    t_FMT_Uint32                GetBufferSize() const;

    //! Start the service
    virtual t_FMT_Uint32		Start();

    //! Stop the service
    virtual t_FMT_Uint32		Stop();

    //! Write dwSize Arinc429 messages to the output buffer
    virtual t_FMT_Uint32		Write(CFMT_HdwArinc429Message *pMess, t_FMT_Uint32 dwSize, t_FMT_Bool bImmediate = FMTDEF_FALSE);

    //! Reset the output buffer
    virtual t_FMT_Uint32		ResetWriteBuffer();

    //! Return the number of messages stored into output buffer
    virtual t_FMT_Uint32		GetMessagesToBeWritten(t_FMT_Uint32& uiNom);


};



#endif







