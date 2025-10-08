// =====================================================================================
/**
 * @file					FMT_CommTftpClient.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					28/06/2022
 * @brief					TFTP Client
 *
 * @version	Project:		Formatech C++ Communication Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][28/06/2022]
 */
// =====================================================================================



#ifndef FMTDEF_COMM_TFTPCLIENT_H
#define FMTDEF_COMM_TFTPCLIENT_H

// =====================================================================================
//	INCLUDES
// =====================================================================================


#ifndef FMTDEF_CORE_H
#include "FMT_Core.h"
#endif

#ifndef FMTDEF_HDW_H
#include "FMT_Hdw.h"
#endif

#ifndef FMTDEF_COMM_FMTTFTP_H
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
//	Class CFMT_CommTftpClient
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_CommTftpClient : public CFMT_CommObject
{
// =====================================================================================
//	TYPES
// =====================================================================================

protected:

	// ---[ t_SrcDstMode ]---------------------------------------------

	enum t_SrcDstMode
	{
		e_SrcDstMode_File		= 0,
		e_SrcDstMode_Buffer		= 1,
		e_SrcDstMode_Vector		= 2
	};


	// ---[ t_Operation ]---------------------------------------------

	enum t_Operation
	{
		e_Operation_Write		= 0,
		e_Operation_Read		= 1
	};


public:

	// ---[ CParameters ]-----------------------------------------------

	class FMTDEF_LIB_DLLSPEC CParameters
	{
	public:

		// Server IP Address
		CFMT_IpAddress			m_ServerAdd;

		// Server Port
		t_FMT_Uint16			m_usServerPort;

		// First port
		t_FMT_Uint16			m_usFirstClientPort;

		// Last port
		t_FMT_Uint16			m_usLastClientPort;

		// Desired Block Size in transfer
		t_FMT_Uint16			m_usDesiredBlockSize;

		// Max Retries
		t_FMT_Uint8				m_ucMaxRetries;

		// Timeout in ms
		t_FMT_Uint64			m_quiTimeout;

		CParameters();
	};

	// ---[ CTransferStatus ]-----------------------------------------------

	class FMTDEF_LIB_DLLSPEC CTransferStatus
	{
	public:

		// File Name
		CFMT_String							m_sFileName;

	    // File Length */
	    t_FMT_Uint32						m_uiFileLen;

	    // Block Number
	    t_FMT_Uint32						m_uiFileBlock;

		// File Total Blocks
		t_FMT_Uint32						m_uiFileTotBlock;

		// Last Error Code
		t_FMT_Uint16						m_usTftpErrorCode;

		// Last Error Message
		CFMT_String							m_sTftpErrMessage;

		// Processing Code
		t_FMT_Uint32						m_uiProcStatus;

		// Busy Status
		t_FMT_Bool							m_bBusy;


		CTransferStatus();
	};


    // =====================================================================================
    //	VARIABLES
    // =====================================================================================

protected:

	// Parameters
	CParameters							m_Params;

	// Socket
	CFMT_HdwUdpSocket					*m_pSocket;

	// Working client port
	t_FMT_Uint16						m_usClientPort;

	// Current disk file
	CFMT_File							m_DiskFile;

	// Source data buffer
	t_FMT_Uint8							*m_pucSrcDataBuffer;

	// Source data vector
	CFMT_Uint8Vector					*m_pSrcDataVector;

	// Destination Memory List
	CFMT_Uint8List						m_DstMemList;

	// Destination Memory Buffer
	t_FMT_Uint8							**m_ppucDstBuf;

	// Source Mode
	t_SrcDstMode						m_SrcDstMode;

	// Operation
	t_Operation							m_Operation;

	// Working Thread
	FMTDEF_COMM_TFTP_THREAD				m_WorkingThread;

	// Working Thread Exit Flag
	t_FMT_Bool							m_bWorkingThreadExit;

    // TFTP TX Buffer
    t_FMT_Uint8							*m_pucTxBuf;

    // TFTP TX Buffer Length
    t_FMT_Uint32						m_uiTxBufLen;

    // TFTP RX Buffer
    t_FMT_Uint8							*m_pucRxBuf;

    // TFTP RX Buffer Length
    t_FMT_Uint32						m_uiRxBufLen;

	// Start time for timeout operations
	t_FMT_Uint64						m_quiStartTime;

	// Working Server port
	t_FMT_Uint16						m_usServerPort;

	// Current timeout
	t_FMT_Uint64						m_quiTimeout;

    // Current Block Size
    t_FMT_Uint16						m_usBlockSize;

	// Options active in transfer
	t_FMT_Bool							m_bOptions;

    // Last file block received flag
    t_FMT_Bool							m_bLastBlockReceived;

	// Current Transfer Status
	CTransferStatus						m_Status;

	// Mutex
	CFMT_Mutex							m_Mutex;

	// Retries Counter
	t_FMT_Uint8							m_ucRetryCnt;

	// Data Received Flag
	t_FMT_Bool							m_bDataReceived;


public:



// =====================================================================================
// CONSTRUCTORS & DESTRUCTORS
// =====================================================================================

public:

    // Empty constructor
    CFMT_CommTftpClient();

	// Destructor
    virtual ~CFMT_CommTftpClient();


// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:

	// Get a free socket binded on a free client port
	t_FMT_Uint32				GetSocket();

	// Send the current TX packet
	t_FMT_Uint32				SendPacket(t_FMT_Uint16 usDestPort);

	// Working Thread Function
    #ifdef FMTDEF_COMPILE_OS_WINDOWS
	static	DWORD WINAPI		WorkingThreadFunction(LPVOID lpParam);
    #endif

    #ifdef FMTDEF_COMPILE_OS_LINUX
    static	void*               WorkingThreadFunction(void* lpParam);
    #endif

	// Process a received OACK packet
	t_FMT_Uint32				ProcessOAck();

	// Start file writing
	t_FMT_Uint32				WriteStart();
	
	// Wait for Write Connection
	t_FMT_Uint32				WaitWriteConnection();

	// Write a data block
	t_FMT_Uint32				WriteData();

	// Wait for Write DATA ackownledge
	t_FMT_Uint32				WaitWriteDataAck();

	// Write procedure
	t_FMT_Uint32 				WriteProc();

	// Start file reading
	t_FMT_Uint32				ReadStart();

	// Wait for Read Connection
	t_FMT_Uint32				WaitReadConnection();

	// Wait for Read Data
	t_FMT_Uint32				WaitReadData();

	// Read procedure
	t_FMT_Uint32 				ReadProc();


public:

	// Set Parameters 
	t_FMT_Uint32				SetParam(CParameters& param);

	// Check if the client is busy
	t_FMT_Bool					IsBusy() const;

	// Get Transfer Status
	t_FMT_Bool					GetTransferStatus(CTransferStatus& status);

	// Write a file from disk
	t_FMT_Uint32				WriteFile(const CFMT_String& sPath, const CFMT_String& sName, t_FMT_Bool bBlocking = FMTDEF_FALSE);

	// Write a file from memory buffer
	t_FMT_Uint32				WriteFile(const CFMT_String& sName, t_FMT_Uint8 *pucBuf, t_FMT_Uint32 uiLen, t_FMT_Bool bBlocking = FMTDEF_FALSE);
	
	// Write a file from memory vector
	t_FMT_Uint32				WriteFile(const CFMT_String& sName, CFMT_Uint8Vector& Buf, t_FMT_Bool bBlocking = FMTDEF_FALSE);

	// Read a file to disk
	t_FMT_Uint32				ReadFile(const CFMT_String& sPath, const CFMT_String& sName, t_FMT_Bool bBlocking = FMTDEF_FALSE);

	// Read a file to memory buffer
	t_FMT_Uint32				ReadFile(const CFMT_String& sName, t_FMT_Uint8 **ppucBuf, t_FMT_Bool bBlocking = FMTDEF_FALSE);

	// Read a file to memory vector
	t_FMT_Uint32				ReadFile(const CFMT_String& sName, CFMT_Uint8Vector& Buf, t_FMT_Bool bBlocking = FMTDEF_FALSE);

};



#endif







