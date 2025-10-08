// =====================================================================================
/**
 * @file					FMT_HdwCanOutBufferService.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					10/01/2020
 * @brief					Abstract Hardware Can Output Buffer Service
 *
 * @version	Project:		Formatech C++ Hardware Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][10/01/2020]
 */
// =====================================================================================



#ifndef FMTDEF_HDW_CANOUTBUFFERSERVICE_H
#define FMTDEF_HDW_CANOUTBUFFERSERVICE_H

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

#define FMTDEF_HDW_CANOUTBUFFERSERVICE_BE_INFINITE				0xFFFF
#define FMTDEF_HDW_CANOUTBUFFERSERVICE_TIMEOUT_INFINITE			0xFFFF


// *************************************************************************************
// *************************************************************************************
//	Class CFMT_HdwCanOutBufferService
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_HdwCanOutBufferService : public CFMT_HdwService
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
        t_FMT_Uint16			m_usMaxBusErrors;
        t_FMT_Uint16			m_usTimeout;

        CParameters();
    };

    class FMTDEF_LIB_DLLSPEC CMessageBuffer : public CFMT_List<CFMT_HdwCanMessage*>
    {
    };

    enum t_TxStatus
    {
        e_TxStatus_Idle						= 0,
        e_TxStatus_InTransmission			= 1,
        e_TxStatus_StoppedByTimeout			= 2,
        e_TxStatus_StoppedByBusError		= 3,
        e_TxStatus_StoppedByServiceFailure	= 4
        //e_TxStatus_StoppedByBusOff			= 4,
    };

    // =====================================================================================
    //	VARIABLES
    // =====================================================================================

protected:

    t_FMT_Uint32						m_uiBufferSize;
    CMessageBuffer						m_Buffer;
    t_FMT_Uint32						m_uiTxStatus;
    t_FMT_Uint32						m_uiMaxPacketSize;
    t_FMT_Uint16						m_usMaxBusErrors;
    t_FMT_Uint16						m_usTimeout;

    CMessageBuffer						m_CurPacket;

public:

// =====================================================================================
// CONSTRUCTORS & DESTRUCTORS
// =====================================================================================

public:

    //! Empty constructor
    CFMT_HdwCanOutBufferService(CFMT_HdwObject *pPort);

    //! Destructor
    virtual ~CFMT_HdwCanOutBufferService();


// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:

    //! Destroy a message buffer
    void						DestroyMessageBuffer(CMessageBuffer& mb);

public:

    //! Return the service parameters
    virtual t_FMT_Uint32		GetParameters(CParameters *pParameters);

    //! Set the service parameters
    virtual t_FMT_Uint32		SetParameters(CParameters *pParameters);

    //! Return the size of output buffer
    t_FMT_Uint32                GetBufferSize() const;

    //! Start the service
    virtual t_FMT_Uint32		Start();

    //! Stop the service
    virtual t_FMT_Uint32		Stop();

    //! Return the status related to fault confinement of the port
    virtual t_FMT_Uint32		GetFaultStatus(CFMT_HdwCanPort::CFaultStatus *pStatus);

    //! Reset the output buffer
    virtual t_FMT_Uint32		ResetWriteBuffer();

    //! Write dwSize Can messages to the output buffer
    virtual t_FMT_Uint32		Write(CFMT_HdwCanMessage *pMess, t_FMT_Uint32 dwSize, t_FMT_Bool bImmediate=FMTDEF_FALSE);

    //! Return the number of messages stored into output buffer
    virtual t_FMT_Uint32		GetMessagesToBeWritten(t_FMT_Uint32& uiNom);

    //! Return the transmission status
    virtual t_FMT_Uint32		GetTxStatus(t_FMT_Uint32& uiTxStatus);

};



#endif







