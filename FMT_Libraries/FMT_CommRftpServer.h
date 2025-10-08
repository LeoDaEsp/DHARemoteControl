// =====================================================================================
/**
 * @file					FMT_CommRftpServer.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					03/09/2025
 * @brief					Reliable indexed File Transfer Protocol Server
 *
 * @version	Project:		Formatech C++ Communication Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][03/09/2025]
 */
// =====================================================================================


#ifndef FMTDEF_COMM_RFTP_SERVER_H
#define FMTDEF_COMM_RFTP_SERVER_H

// =====================================================================================
//	DEFINES
// =====================================================================================



// =====================================================================================
//	INCLUDES
// =====================================================================================

#ifndef FMTDEF_CORE_H
#include "FMT_Core.h"
#endif

#ifndef FMTDEF_HDW_H
#include "FMT_Hdw.h"
#endif

#ifndef FMTDEF_COMM_RFTP_H
#include "FMT_CommRftp.h"
#endif


// *************************************************************************************
// *************************************************************************************
//	Class CFMT_CommRftpServer
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_CommRftpServer : public CFMT_CommRftp
{
	// =====================================================================================
	//	TYPES
	// =====================================================================================

private:


    // --- [t_ServerState] -----------------------------------

    enum t_ServerState
    {
        e_ServerState_Reset          = 0,
        e_ServerState_Rx             = 1,
        e_ServerState_ProcRxPacket   = 2,
        e_ServerState_Tx             = 3,
        e_ServerState_FileOpenWrite  = 4,
        e_ServerState_FileWrite      = 5,
        e_ServerState_FileClose      = 6,
        e_ServerState_OpenFileRead   = 7,
        e_ServerState_FileRead       = 8,
        e_ServerState_FileErase      = 9,
    };

protected:

public:

    // --- [CFileFilter] -----------------------------------

    class FMTDEF_LIB_DLLSPEC CFileFilter
    {
    public:

        // Write Enable Flag
        t_FMT_Bool                          m_bWriteEnable;

        // Read Enable Flag
        t_FMT_Bool                          m_bReadEnable;

        // Erase Enable Flag
        t_FMT_Bool                          m_bEraseEnable;

        CFileFilter();
    };


    // --- [t_File_Info] -----------------------------------

    class FMTDEF_LIB_DLLSPEC CFileInfo
    {
    public:
        t_FMT_Uint16				m_usCode;											// File Code
        t_FMT_Uint32				m_uiCrc;											// File CRC
        t_FMT_Uint32				m_uiSize;											// File Size
        t_FMT_Uint8					m_ucStatus;											// File Status
        t_FMT_Uint64				m_quiTimestamp;										// File TimeStamp
        t_FMT_Uint8					m_pExtraBytes[FMTDEF_RFTP_FILEINFO_EXTRABYTES];		// Extra bytes

        CFileInfo();
        void Reset();
    };


	// =====================================================================================
	//	VARIABLES
	// =====================================================================================

private:

	// Server State
	t_ServerState                           m_ServerState;

	// Transfer File Open Flag
	t_FMT_Bool                              m_bFileOpen;

    // File transfer starting time
    t_FMT_Uint64                            m_quiFileStartTime;

    // Computed File CRC
    t_FMT_Uint32                            m_uiComputedCrc;

    // Current file size
    t_FMT_Uint32                            m_uiCurSize;

    // Current Block Length
    t_FMT_Uint16                            m_usCurBlockLen;

protected:

    // File Transfer Timeout
    t_FMT_Uint64                            m_quiFileTransferTimeout;

    // Maximum File Read Packet Length
    t_FMT_Uint32                            m_uiReadFileMaxPacketLength;

    // Configuratio Filter
    CFileFilter                             m_pFileFilter[256];

    // ID of Transfer File
    t_FMT_Uint8                             m_ucFileId;

    // Current File Descriptor
    CFileInfo								m_FileInfo;

    // File Write Mode Flag
    t_FMT_Bool								m_bFileWriteMode;

    // Current Client Identifier
    t_FMT_Uint8                             m_ucClientID;

public:



	// =====================================================================================
	// CONSTRUCTORS & DESTRUCTORS
	// =====================================================================================

public:

	CFMT_CommRftpServer();
	virtual ~CFMT_CommRftpServer();


	// =====================================================================================
	//	FUNCTIONS
	// =====================================================================================

private:


    // Process RESET State
    t_FMT_Uint32					ProcessStateReset();

    // Process RX State
    t_FMT_Uint32                    ProcessStateRx();

    // Process RX Packet State
    t_FMT_Uint32                    ProcessStateProcRxPacket();

    // Process TX WCET State
    t_FMT_Uint32                    ProcessStateTx();

    // Process OPEN FILE WRITE START WCET State
    t_FMT_Uint32                    ProcessStateOpenFileWrite();

    // Process OPEN FILE WRITE WCET State
    t_FMT_Uint32                    ProcessStateFileWrite();

    // Process OPEN FILE CLOSE WCET State
    t_FMT_Uint32                    ProcessStateFileClose();

    // Process OPEN FILE READ WCET State
    t_FMT_Uint32                    ProcessStateOpenFileRead();

    // Process FILE READ WCET State
    t_FMT_Uint32                    ProcessStateFileRead();

    // Process FILE ERASE WCET State
    t_FMT_Uint32                    ProcessStateFileErase();

    // Process Loopback Command
    t_FMT_Uint32                    ProcLoopbackCom();

    // Send a single byte answer packet
    t_FMT_Uint32                    SendSimpleAnswer(t_FMT_Uint8 ucPid, t_FMT_Uint8 ucStatus, t_FMT_Uint16 usExtraBytes);



protected:

    // Map File Identifier
    virtual t_FMT_Uint8             MapFileID(t_FMT_Uint8 ucId);


    // File Abort Event
    virtual void                    OnFileAbort();

    // File Close Event
    virtual t_FMT_Uint32            OnFileClose();

    // File Erase Event
    virtual t_FMT_Uint32            OnFileErase();

    // File Open-To-Write Event
    virtual t_FMT_Uint32            OnFileOpenToWrite();

    // File Open-To-Read Event
    virtual t_FMT_Uint32            OnFileOpenToRead(CFileInfo* pInfo);

    // File Write Event
    virtual t_FMT_Uint32            OnFileWrite(t_FMT_Uint8* pucBuf, t_FMT_Uint32 uiLen);

    // File Read Event
    virtual t_FMT_Uint32            OnFileRead(t_FMT_Uint8* pucBuf, t_FMT_Uint32 uiLen);

public:

    // Set Read Maximum Packet Length
    void                            SetReadMaxPacketLength(t_FMT_Uint32 uiMaxLen);

    // Set File Filter Entry
    void                            SetFileFilter(t_FMT_Uint8 ucIdx, t_FMT_Bool bErase, t_FMT_Bool bWrite, t_FMT_Bool bRead);

	// Performs Server actions
	virtual t_FMT_Uint32			ProcessActions();


};

#endif
