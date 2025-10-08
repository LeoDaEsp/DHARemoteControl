// =====================================================================================
/**
 * @file					FMT_HdwTcpServerSocket.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					07/09/2022
 * @brief					TCP Server Socket
 *
 * @version	Project:		Formatech C++ Hardware Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][07/09/2022]
 */
// =====================================================================================



#ifndef FMTDEF_HDW_TCPSERVERSOCKET_H
#define FMTDEF_HDW_TCPSERVERSOCKET_H

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
//	Class CFMT_HdwTcpServerSocket
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_HdwTcpServerSocket : public CFMT_HdwSocket
{
// =====================================================================================
//	TYPES
// =====================================================================================

protected:
public:

    class FMTDEF_LIB_DLLSPEC CConnectedSocket : public CFMT_HdwSocket
    {
    public:
        CFMT_IpAddress          m_IpAddress;
        t_FMT_Uint16            m_usPort;

        CConnectedSocket(FMTDEF_HDW_SOCKET sock);
        ~CConnectedSocket();

        //! Send a data buffer
        t_FMT_Uint32	Send(const t_FMT_Uint8 *pucData, t_FMT_Uint32 uiSize, t_FMT_Uint32 *puiSentBytes);

        //! Receive a data buffer
        t_FMT_Uint32	Receive(t_FMT_Uint8 *pucData, t_FMT_Uint32 uiMaxSize, t_FMT_Uint32 *puiRcvBytes, t_FMT_Uint32 uiMsTimeout = FMTDEF_HDW_SOCKET_INFINITE_TIMEOUT);

        #if 0
        //! Check if at least one datagram is waiting to be read
        t_FMT_Bool		HasPendingBuffer() const;

        //! Returns the size of the first pending buffer
        t_FMT_Uint32	GetPendingBufferSize() const;
        #endif
    };


    class FMTDEF_LIB_DLLSPEC CConnectedSocketList : public CFMT_List<CConnectedSocket*>
    {

    };


    // =====================================================================================
    //	VARIABLES
    // =====================================================================================

protected:

    // Mutex to access client list
    CFMT_Mutex                      m_Mutex;

    //Client list
    CConnectedSocketList            m_ClientList;

public:


// =====================================================================================
// CONSTRUCTORS & DESTRUCTORS
// =====================================================================================

public:

    //! Empty constructor
    CFMT_HdwTcpServerSocket();

    //! Destructor
    virtual ~CFMT_HdwTcpServerSocket();


// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:
public:

    //! Marks the socket as a passive socket, that is, as a socket that will be used to accept incoming connection requests
    t_FMT_Uint32        Listen(t_FMT_Uint32 uiMaxQueueLen);

    //! Extracts the first connection request on the queue of pending connections, creates and return the new connected socket
    CConnectedSocket*   Accept();

    //! Shutdown a client connection
    t_FMT_Uint32        Shutdown(CConnectedSocket *pClient);

};



#endif







