// =====================================================================================
/**
 * @file					FMT_CommTcpServer.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					17/09/2022
 * @brief					Basic TCP Server
 *
 * @version	Project:		Formatech C++ Communication Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][17/09/2022]
 */
// =====================================================================================


#ifndef FMTDEF_COMM_TCP_SERVER_H
#define FMTDEF_COMM_TCP_SERVER_H


// =====================================================================================
//	INCLUDES
// =====================================================================================


#ifndef FMTDEF_CORE_H
#include "FMT_Core.h"
#endif

#ifndef FMTDEF_HDW_H
#include "FMT_Hdw.h"
#endif

#ifndef FMTDEF_COMM_OBJECT_H
#include "FMT_CommObject.h"
#endif


// =====================================================================================
//	DEFINES
// =====================================================================================


#ifdef FMTDEF_COMPILE_OS_WINDOWS
#define FMTDEF_COMM_SERVER_THREAD                       HANDLE
#endif

#ifdef FMTDEF_COMPILE_OS_LINUX
#define FMTDEF_COMM_SERVER_THREAD                       pthread_t
#endif


// *************************************************************************************
// *************************************************************************************
//	Class CFMT_CommTcpServer
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_CommTcpServer : public CFMT_CommObject
{
    // =====================================================================================
    //	TYPES
    // =====================================================================================

protected:

    // ---[ CClient ] ----------------------------------

    class FMTDEF_LIB_DLLSPEC CClient
    {
        friend class CFMT_CommTcpServer;

    public:

        // Server
        CFMT_CommTcpServer                        		*m_pServer;

        // Client socket
        CFMT_HdwTcpServerSocket::CConnectedSocket       *m_pSocket;

        // Client Thread
        FMTDEF_COMM_SERVER_THREAD                       m_ClientThread;

        // Client Thread Stop Command
        t_FMT_Bool                                      m_bClientThreadExit;

        // Client Thread Running Flag
        t_FMT_Bool                                      m_bClientRunning;

        // Constructor
        CClient();

        // Destructor
        virtual ~CClient();

        // Client Start Actions
        virtual t_FMT_Uint32            StartActions();

        // Client Stop Actions
        virtual void                    StopActions();

        // Client Thread Actions
        virtual t_FMT_Uint32            ClientActions();
    };


    // ---[ CClientList ] ----------------------------------

    class FMTDEF_LIB_DLLSPEC CClientVector : public CFMT_Vector<CClient*>
    {
    };

public:

    // =====================================================================================
    //	VARIABLES
    // =====================================================================================

private:
protected:

    // Server Socket
    CFMT_HdwTcpServerSocket                         *m_pServerSocket;

    // Server Port
    t_FMT_Uint16                                    m_usServerPort;

    // Maximum number of client connections
    t_FMT_Uint16                                    m_usMaxConnections;

    // Server Thread
    FMTDEF_COMM_SERVER_THREAD                       m_ServerThread;

    // Server Thread Stop Command
    t_FMT_Bool                                      m_bServerThreadExit;

    // Server Thread Running Flag
    t_FMT_Bool                                      m_bServerRunning;

    // Connected Client List
    CClientVector                                   m_vClients;

    // Server actions mutex
    CFMT_Mutex                                      m_ServerMutex;


public:

    // =====================================================================================
    // CONSTRUCTORS & DESTRUCTORS
    // =====================================================================================

public:

    CFMT_CommTcpServer();
    virtual ~CFMT_CommTcpServer();

    // =====================================================================================
    //	FUNCTIONS
    // =====================================================================================

protected:

    // Server Thread Function
    #ifdef FMTDEF_COMPILE_OS_WINDOWS
    static DWORD WINAPI         ServerThreadFunction(LPVOID lpParam);
    #endif
    #ifdef FMTDEF_COMPILE_OS_LINUX
    static void*                ServerThreadFunction(void* lpParam);
    #endif

    // Get a new client
    virtual CClient*            GetNewClient();

    // Destroy clients
    virtual void                DestroyClients();

    // Find a free client
    CClient*                    FindFreeClient();

    // Start new client connection
    t_FMT_Uint32                StartClient(CFMT_CommTcpServer::CClient *pClient, CFMT_HdwTcpServerSocket::CConnectedSocket *pNewClient);

    // Abort a client connection
    //t_FMT_Uint32                AbortClientConnection(CClient *pClient);

    // Client Thread Function
    #ifdef FMTDEF_COMPILE_OS_WINDOWS
    static DWORD WINAPI         ClientThreadFunction(LPVOID lpParam);
    #endif
    #ifdef FMTDEF_COMPILE_OS_LINUX
    static void*                ClientThreadFunction(void* lpParam);
    #endif


public:

    // Start Server
    virtual t_FMT_Uint32        StartServer(t_FMT_Uint16 usPort, t_FMT_Uint16 usMaxConnections);

    // Stop Server
    virtual t_FMT_Uint32        StopServer();

};


#endif

