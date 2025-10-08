// =====================================================================================
/**
 * @file					FMT_HdwSocket.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					06/11/2021
 * @brief					Abstract Socket
 *
 * @version	Project:		Formatech C++ Hardware Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][06/11/2021]
 */
// =====================================================================================



#ifndef FMTDEF_HDW_SOCKET_H
#define FMTDEF_HDW_SOCKET_H

// =====================================================================================
//	INCLUDES
// =====================================================================================


#ifndef FMTDEF_CORE_H
#include "FMT_Core.h"
#endif

#ifndef FMTDEF_HDW_OBJECT_H
#include "FMT_HdwObject.h"
#endif


#ifdef FMTDEF_COMPILE_OS_LINUX
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <errno.h>
#include <net/route.h>
#include <netinet/tcp.h>
#endif



// =====================================================================================
//	DEFINES
// =====================================================================================

#ifdef FMTDEF_COMPILE_OS_WINDOWS

#define FMTDEF_HDW_SOCKET_INVALID_SOCKET		(INVALID_SOCKET)
#define FMTDEF_HDW_SOCKET_SOCKET_ERROR			(SOCKET_ERROR)

#define FMTDEF_HDW_SOCKET_IPPROTO_UDP			(IPPROTO_UDP)
#define FMTDEF_HDW_SOCKET_IPPROTO_TCP			(IPPROTO_TCP)

#define FMTDEF_HDW_SOCKET_SOCK_DGRAM			(SOCK_DGRAM)			// datagram socket
#define FMTDEF_HDW_SOCKET_SOCK_STREAM			(SOCK_STREAM)			// stream socket

#define FMTDEF_HDW_SOCKET_AF_UNSPEC				(AF_UNSPEC)				// unspecified
#define FMTDEF_HDW_SOCKET_AF_INET				(AF_INET)				// internetwork: UDP, TCP, etc.

#define FMTDEF_HDW_SOCKET_INADDR_IPV4_ANY		(INADDR_ANY)
#define FMTDEF_HDW_SOCKET_INPORT_ANY			(0)

#define FMTDEF_HDW_SOCKET                       SOCKET

#endif

#ifdef FMTDEF_COMPILE_OS_LINUX

#define FMTDEF_HDW_SOCKET_INVALID_SOCKET		(-1)
#define FMTDEF_HDW_SOCKET_SOCKET_ERROR			(-1)

#define FMTDEF_HDW_SOCKET_IPPROTO_UDP			(IPPROTO_UDP)
#define FMTDEF_HDW_SOCKET_IPPROTO_TCP			(IPPROTO_TCP)

#define FMTDEF_HDW_SOCKET_SOCK_DGRAM			(SOCK_DGRAM)			// datagram socket
#define FMTDEF_HDW_SOCKET_SOCK_STREAM			(SOCK_STREAM)			// stream socket

#define FMTDEF_HDW_SOCKET_AF_UNSPEC				(AF_UNSPEC)				// unspecified
#define FMTDEF_HDW_SOCKET_AF_INET				(AF_INET)				// internetwork: UDP, TCP, etc.

#define FMTDEF_HDW_SOCKET_INADDR_IPV4_ANY		(INADDR_ANY)
#define FMTDEF_HDW_SOCKET_INPORT_ANY			(0)

#define FMTDEF_HDW_SOCKET                       t_FMT_Int32

#endif


#define FMTDEF_HDW_SOCKET_INFINITE_TIMEOUT		(0xFFFFFFFF)


// *************************************************************************************
// *************************************************************************************
//	Class CFMT_HdwSocket
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_HdwSocket : public CFMT_Object
{
// =====================================================================================
//	TYPES
// =====================================================================================

protected:
public:

	//! Socket Type
	enum t_SocketType
	{
		e_SocketType_Udp		= 0,
		e_SocketType_Tcp		= 1,
		e_SocketType_Unknown	= 65535,
	};

	//! Bind Modes
	enum t_BindMode
	{
		e_BindMode_ShareAddress			= 0,
		e_BindMode_DontShareAddress		= 1
	};



    // =====================================================================================
    //	VARIABLES
    // =====================================================================================

protected:

	#ifdef FMTDEF_COMPILE_OS_WINDOWS
	// WinSocket start-up flag
	static	t_FMT_Bool		m_bWinSocketStartup;

	// Socket counter
	static	t_FMT_Uint64	m_quiSocketCnt;
	#endif

	// Socket Type
	t_SocketType			m_SockType;

    // Socket
    FMTDEF_HDW_SOCKET       m_Socket;


public:


// =====================================================================================
// CONSTRUCTORS & DESTRUCTORS
// =====================================================================================

public:

    //! Empty constructor
    CFMT_HdwSocket(t_SocketType SockType);

    //! Destructor
    virtual ~CFMT_HdwSocket();


// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:
public:

	//! Set TTL
    t_FMT_Uint32			SetTtl(t_FMT_Uint8 ucTtl);

    //! Set/Clear TCP_NODELAY option
    t_FMT_Uint32			SetTcpNoDelayOption(t_FMT_Bool bSet);

    //! Get Local Port
    t_FMT_Uint16			GetLocalPort();

    //! Binds to address on port
    t_FMT_Uint32			Bind(const CFMT_IpAddress& Address, t_FMT_Uint16 usPort = 0, CFMT_HdwSocket::t_BindMode Mode = e_BindMode_ShareAddress);

    //! Binds to any address on port
    t_FMT_Uint32			Bind(t_FMT_Uint16 usPort, CFMT_HdwSocket::t_BindMode Mode = e_BindMode_ShareAddress);

	//! Send an ARP request and return the MAC of inquired IP
	static t_FMT_Uint32		WhoIs(const CFMT_IpAddress& DestAdd, t_FMT_Uint64& quiMac);
};



#endif







