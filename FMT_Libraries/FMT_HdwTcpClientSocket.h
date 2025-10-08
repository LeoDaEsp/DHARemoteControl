// =====================================================================================
/**
 * @file					FMT_HdwTcpClientSocket.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					07/09/2022
 * @brief					TCP Client Socket
 *
 * @version	Project:		Formatech C++ Hardware Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][07/09/2022]
 */
// =====================================================================================



#ifndef FMTDEF_HDW_TCPCLIENTSOCKET_H
#define FMTDEF_HDW_TCPCLIENTSOCKET_H

// =====================================================================================
//	INCLUDES
// =====================================================================================


#ifndef FMTDEF_CORE_H
#include "FMT_Core.h"
#endif

#ifndef FMTDEF_HDW_OBJECT_H
#include "FMT_HdwObject.h"
#endif

#ifndef FMTDEF_HDW_SOCKET_H
#include "FMT_HdwSocket.h"
#endif

// =====================================================================================
//	DEFINES
// =====================================================================================



// *************************************************************************************
// *************************************************************************************
//	Class CFMT_HdwTcpClientSocket
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_HdwTcpClientSocket : public CFMT_HdwSocket
{
// =====================================================================================
//	TYPES
// =====================================================================================

protected:
public:


    // =====================================================================================
    //	VARIABLES
    // =====================================================================================

protected:
public:


// =====================================================================================
// CONSTRUCTORS & DESTRUCTORS
// =====================================================================================

public:

    //! Empty constructor
    CFMT_HdwTcpClientSocket();

    //! Destructor
    virtual ~CFMT_HdwTcpClientSocket();


// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:
public:

	//! Connect to a server
	t_FMT_Uint32	Connect(const CFMT_IpAddress& SrvAdd, t_FMT_Uint16 usSrvPort, t_FMT_Uint32 uiTimeoutMs = 2000, t_FMT_Uint32 uiRetries = 0);

	//! Receive a data buffer
	t_FMT_Uint32	Receive(t_FMT_Uint8 *pucData, t_FMT_Uint32 uiMaxSize, t_FMT_Uint32 *puiRcvBytes, t_FMT_Uint32 uiMsTimeout = FMTDEF_HDW_SOCKET_INFINITE_TIMEOUT);
	
	//! Send a data buffer
	t_FMT_Uint32	Send(const t_FMT_Uint8 *pucData, t_FMT_Uint32 uiSize, t_FMT_Uint32 *puiSentBytes);
};



#endif







