// =====================================================================================
/**
 * @file					FMT_HdwUdpSocket.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					06/11/2021
 * @brief					UDP Socket
 *
 * @version	Project:		Formatech C++ Hardware Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][06/11/2021]
 */
// =====================================================================================



#ifndef FMTDEF_HDW_UDPSOCKET_H
#define FMTDEF_HDW_UDPSOCKET_H

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
//	Class CFMT_HdwUdpSocket
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_HdwUdpSocket : public CFMT_HdwSocket
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
    CFMT_HdwUdpSocket();

    //! Destructor
    virtual ~CFMT_HdwUdpSocket();


// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:
public:

	//! Send a datagram
	t_FMT_Uint32	SendDatagram(const t_FMT_Uint8 *pucData, t_FMT_Uint32 uiSize, const CFMT_IpAddress& DestAdd, t_FMT_Uint16 usPort, t_FMT_Uint32 *puiSentBytes);

    //! Read a datagram
	t_FMT_Uint32	ReadDatagram(t_FMT_Uint8 *pucData, t_FMT_Uint32 uiMaxSize, CFMT_IpAddress *pSrcAdd, t_FMT_Uint16 *pusSrcPort, 
									t_FMT_Uint32 *puiRcvBytes, t_FMT_Uint32 uiMsTimeout = FMTDEF_HDW_SOCKET_INFINITE_TIMEOUT);

	//! Check if at least one datagram is waiting to be read
	t_FMT_Bool		HasPendingDatagrams() const;

	//! Returns the size of the first pending UDP datagram
	t_FMT_Uint32	GetPendingDatagramSize() const;
};



#endif







