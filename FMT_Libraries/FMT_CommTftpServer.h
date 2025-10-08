// =====================================================================================
/**
 * @file					FMT_CommTftpServer.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					28/06/2022
 * @brief					TFTP Server
 *
 * @version	Project:		Formatech C++ Communication Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][28/06/2022]
 */
// =====================================================================================



#ifndef FMTDEF_COMM_TFTPSERVER_H
#define FMTDEF_COMM_TFTPSERVER_H

// =====================================================================================
//	INCLUDES
// =====================================================================================


#ifndef FMTDEF_CORE_H
#include "FMT_Core.h"
#endif

#ifndef FMTDEF_HDW_H
#include "FMT_Hdw.h"
#endif

#ifndef FMTDEF_COMM_TFTP_H
#include "FMT_CommTftp.h"
#endif

#ifndef FMTDEF_COMM_OBJECT_H
#include "FMT_CommObject.h"
#endif


// =====================================================================================
//	DEFINES
// =====================================================================================


// *************************************************************************************
// *************************************************************************************
//	Class CFMT_CommTftpServer
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_CommTftpServer : public CFMT_CommObject
{
// =====================================================================================
//	TYPES
// =====================================================================================

protected:

	// ---[ t_ClientState ]---------------------------------------------------

	enum t_ClientState
	{
		e_ClientState_WrRqAns           = 0,
		e_ClientState_WaitWriteData     = 1,
		e_ClientState_SendReadData      = 2,
		e_ClientState_WaitOackAck		= 3
	};


	// ---[ CClient ]---------------------------------------------------

	class FMTDEF_LIB_DLLSPEC CClient : public CFMT_Object
	{
	public:

		CFMT_CommTftpServer						*m_pServer;

		// Running flag
		t_FMT_Bool								m_bRunning;

		// Socket
		//CSocket									*m_pSocket;
		CFMT_HdwUdpSocket						*m_pSocket;

		// Data Mode
		FMT_Comm_Tftp::t_DataMode				m_DataMode;

		// Destination Address
		CFMT_IpAddress							m_DstAdd;

		// Destination Port
		t_FMT_Uint16							m_usDstPort;

		// Client State
		t_ClientState							m_ClientState;

		// TFTP RX Buffer */
		t_FMT_Uint8								m_pucRxBuf[FMTDEF_COMM_TFTP_MAX_BUF_SIZE];

		// TFTP RX Buffer Length
		t_FMT_Uint32							m_uiRxBufLen;

		// TFTP TX Buffer
		t_FMT_Uint8								m_pucTxBuf[FMTDEF_COMM_TFTP_MAX_BUF_SIZE];

		// TFTP TX Buffer Length
		t_FMT_Uint32							m_uiTxBufLen;

		// Current processing File Name
		CFMT_String                             m_sFileName;

		// Current processing File Name Mode
		CFMT_String                             m_sMode;

		// BLOCK option used flags
		t_FMT_Bool								m_bUsedBlockSize;

		// BLOCK option value
		t_FMT_Uint16							m_usBlockSize;

		// TSIZE option used flags
		t_FMT_Bool								m_bUsedTSize;

		// TSIZE option value
		t_FMT_Uint32							m_uiTSize;

		// TIMEOUT option used flags
		t_FMT_Bool								m_bUsedTimeout;

		// TIMEOUT option value in ms
		t_FMT_Uint32							m_uiTimeout;

		// Current Processing File Length
		t_FMT_Uint32							m_uiCurFileLen;

		// Current Processing File Block Number
		t_FMT_Uint32							m_uiCurFileBlock;

		// Current Processing File Total Blocks
		t_FMT_Uint32							m_uiCurFileTotBlock;

		/* Retry Counter */
		t_FMT_Uint32							m_uiRetryCnt;

		/* Starting Time for timeout operations */
		t_FMT_Uint64							m_quiStartTime;


		/* Last file block received flag */
		//t_FMT_Bool                             m_bCurFileBlockEnd;


		// Client Thread
		FMTDEF_COMM_TFTP_THREAD					m_Thread;

		// Client Thread Exit Flag
		t_FMT_Bool								m_bThreadExit;



		CClient();
		~CClient();

		t_FMT_Uint32							StopConnection();
		t_FMT_Uint32							SendPacket();
		t_FMT_Uint32							Run();
		t_FMT_Uint32							DecodeWrqRrq();
		t_FMT_Uint32							ProcClient();
		t_FMT_Uint32							Proc_WrRqAns();
		t_FMT_Uint32							Proc_WaitWriteData();
		t_FMT_Uint32							Proc_SendReadData();
		t_FMT_Uint32							Proc_WaitOackAck();

		// Client Thread Function
		#ifdef FMTDEF_COMPILE_OS_WINDOWS
		static	DWORD WINAPI					ClientThreadFunction(LPVOID lpParam);
		#endif

		#ifdef FMTDEF_COMPILE_OS_LINUX
		static	void*							ClientThreadFunction(void* lpParam);
		#endif



	    t_FMT_Bool operator==(const CClient& op)
		{
            FMTDEFM_UNUSED(op);
            return FMTDEF_FALSE;
		}
	    t_FMT_Bool operator!=(const CClient& op)
		{
            FMTDEFM_UNUSED(op);
            return FMTDEF_FALSE;
		}

	    FMTDEF_LIB_DLLSPEC friend CFMT_Buffer& operator<<(CFMT_Buffer& buf, CClient& s);
	    FMTDEF_LIB_DLLSPEC friend CFMT_Buffer& operator>>(CFMT_Buffer& buf, CClient& s);
	};

    // --- CClientVector --------------------------------------------

    class FMTDEF_LIB_DLLSPEC CClientVector : public CFMT_Vector<CClient>
    {
    };


public:

	// ---[ CParameters ]-----------------------------------------------

	class FMTDEF_LIB_DLLSPEC CParameters
	{
	public:

		// Server Port
		t_FMT_Uint16			m_usServerPort;

		// Maximum Client Connections
		t_FMT_Uint32			m_uiMaxClientConnections;

		// First port
		t_FMT_Uint16			m_usFirstClientPort;

		// Last port
		t_FMT_Uint16			m_usLastClientPort;

		// TFTP Retries
		t_FMT_Uint16			m_usTftpRetries;


		CParameters();
	};



    // =====================================================================================
    //	VARIABLES
    // =====================================================================================

protected:

	// Parameters
	CParameters							m_Params;

	// Socket
	CFMT_HdwUdpSocket					*m_pServerSocket;

	// Server Thread
	FMTDEF_COMM_TFTP_THREAD				m_ServerThread;

	// Server Thread Exit Flag
	t_FMT_Bool							m_bServerThreadExit;

	// Server Thread Run Flag
	t_FMT_Bool							m_bServerThreadRun;

    // Server TFTP RX Buffer
    t_FMT_Uint8							*m_pucServerRxBuf;

    // Server TFTP RX Buffer Length
    t_FMT_Uint32						m_uiServerRxBufLen;

	// Clients
	CClientVector						m_Clients;

public:


// =====================================================================================
// CONSTRUCTORS & DESTRUCTORS
// =====================================================================================

public:

    // Empty constructor
    CFMT_CommTftpServer();

	// Destructor
    virtual ~CFMT_CommTftpServer();


// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:

	// Server Thread Function
    #ifdef FMTDEF_COMPILE_OS_WINDOWS
	static	DWORD WINAPI		ServerThreadFunction(LPVOID lpParam);
    #endif

    #ifdef FMTDEF_COMPILE_OS_LINUX
    static	void*               ServerThreadFunction(void* lpParam);
    #endif


	// Start a TFTP Connection from server to the requiring client
	virtual t_FMT_Uint32		StartConnection(CFMT_IpAddress& ClientAdd, t_FMT_Uint16 usClientPort, FMT_Comm_Tftp::t_DataMode Mode);

	// Get a free socket binded on a free connection port
	CFMT_HdwUdpSocket*			GetSocket();


	// Process new connections
	t_FMT_Uint32				ProcConnection();

	// Open the TFTP file
	virtual t_FMT_Uint32		TftpFileOpen(CFMT_String& sFileName, FMT_Comm_Tftp::t_DataMode DataMode, t_FMT_Uint32& uiFileSize);

	// Write a data block to a TFTP file
	virtual t_FMT_Uint32		TftpFileWrite(CFMT_String& sFileName, t_FMT_Uint8 *pucDataBlock, t_FMT_Uint32 uiDataBlockSize);

	// Read a data block from a TFTP file
	virtual t_FMT_Uint32		TftpFileRead(CFMT_String& sFileName, t_FMT_Uint8 *pucDataBlock, t_FMT_Uint32 uiDataBlockSize);

	// Close a TFTP file
	virtual t_FMT_Uint32		TftpFileClose(CFMT_String& sFileName);

	// Abort a TFTP file
	virtual t_FMT_Uint32		TftpFileAbort(CFMT_String& sFileName);

public:

	// Run Server
	virtual t_FMT_Uint32		Run(CParameters& params);

	// Stop Server
	virtual void				Stop();
};



#endif







