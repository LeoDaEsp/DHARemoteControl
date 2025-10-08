// =====================================================================================
/**
 * @file					FMT_HdwCanInBufferService.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					10/01/2020
 * @brief					Abstract Hardware Can Input Buffer Service
 *
 * @version	Project:		Formatech C++ Hardware Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][10/01/2020]
 */
// =====================================================================================



#ifndef FMTDEF_HDW_CANINBUFFERSERVICE_H
#define FMTDEF_HDW_CANINBUFFERSERVICE_H

// =====================================================================================
//	INCLUDES
// =====================================================================================


#ifndef FMTDEF_CORE_H
#include "FMT_Core.h"
#endif

#ifndef FMTDEF_HDW_CANPORT_H
#include "FMT_HdwCanPort.h"
#endif

#ifndef FMTDEF_HDW_SERVICE_H
#include "FMT_HdwService.h"
#endif

#ifndef FMTDEF_HDW_CANMESSAGE_H
#include "FMT_HdwCanMessage.h"
#endif


// =====================================================================================
//	DEFINES
// =====================================================================================



// *************************************************************************************
// *************************************************************************************
//	Class CFMT_HdwCanInBufferService
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_HdwCanInBufferService : public CFMT_HdwService
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


    // --- CMessageBuffer ---------------------------------------------------------

    class FMTDEF_LIB_DLLSPEC CMessageBuffer : public CFMT_List<CFMT_HdwCanMessage>
    {
    };

    // =====================================================================================
    //	VARIABLES
    // =====================================================================================

protected:

    t_FMT_Uint32						m_uiBufferSize;
    CMessageBuffer						m_Buffer;
    t_FMT_Bool							m_bEnableRx;

public:

// =====================================================================================
// CONSTRUCTORS & DESTRUCTORS
// =====================================================================================

public:

    //! Empty constructor
    CFMT_HdwCanInBufferService(CFMT_HdwObject *pPort);

    //! Destructor
    virtual ~CFMT_HdwCanInBufferService();


// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:
public:

    virtual t_FMT_Uint32		GetParameters(CParameters *pParameters);
    virtual t_FMT_Uint32		SetParameters(CParameters *pParameters);
            t_FMT_Uint32		GetBufferSize() const;

    virtual t_FMT_Uint32		Start();
    virtual t_FMT_Uint32		Stop();

    virtual t_FMT_Uint32		GetFaultStatus(CFMT_HdwCanPort::CFaultStatus *pStatus);

    virtual t_FMT_Uint32		GetReadMessagesNumber(t_FMT_Uint32& uiNom);
    virtual t_FMT_Uint32		Read(CFMT_HdwCanMessage *pMess, t_FMT_Uint32 uiSize, t_FMT_Uint32& uiReadSize);

    virtual t_FMT_Uint32		EnableRx();
    virtual t_FMT_Uint32		DisableRx();
    virtual t_FMT_Uint32		ResetRx();


};



#endif







