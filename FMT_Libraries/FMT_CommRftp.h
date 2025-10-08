// =====================================================================================
/**
 * @file					FMT_CommRftp.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					03/09/2025
 * @brief					Reliable indexed File Transfer Protocol Basic Items
 *
 * @version	Project:		Formatech C++ Communication Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][03/09/2025]
 */
// =====================================================================================


#ifndef FMTDEF_COMM_RFTP_H
#define FMTDEF_COMM_RFTP_H

// =====================================================================================
//	DEFINES
// =====================================================================================

// Extra bytes in File  Info
#define FMTDEF_RFTP_FILEINFO_EXTRABYTES					15

// Extra bytes returned in OPEN ANS
#define FMTDEF_FILE_READ_OPEN_ANS_EXTRA_BYTES			32


// Payload byte index
#define FMTDEF_RTFP_PCK_PAYLOAD_IDX				        8

// DID byte index
#define FMTDEF_RTFP_PCK_DID_IDX					        1

// SID byte index
#define FMTDEF_RTFP_PCK_SID_IDX					        2

// PID byte index
#define FMTDEF_RTFP_PCK_PID_IDX					        3

// PKN byte index
#define FMTDEF_RTFP_PCK_PKN_IDX					        4

// PYB byte index
#define FMTDEF_RTFP_PCK_PYB_IDX					        6

// Absolute Maximum packet length
#define FMTDEF_COMM_RFTP_MAX_PACKETSIZE				    0x100000

// Total overhead bytes
#define FMTDEF_RTFP_PCK_OVERHEAD_BYTES			        10

// PIDs
#define FMTDEF_RTFP_PID_LOOPBACK_COM					0x01
#define FMTDEF_RTFP_PID_LOOPBACK_ANS					0x10

#define FMTDEF_RTFP_PID_FILE_WRITE_OPEN_COM				0x02
#define FMTDEF_RTFP_PID_FILE_WRITE_OPEN_ANS				0x20

#define FMTDEF_RTFP_PID_FILE_WRITE_DATA_COM				0x03
#define FMTDEF_RTFP_PID_FILE_WRITE_DATA_ANS				0x30

#define FMTDEF_RTFP_PID_FILE_READ_OPEN_COM				0x04
#define FMTDEF_RTFP_PID_FILE_READ_OPEN_ANS				0x40

#define FMTDEF_RTFP_PID_FILE_CLOSE_COM					0x05
#define FMTDEF_RTFP_PID_FILE_CLOSE_ANS					0x50

#define FMTDEF_RTFP_PID_FILE_READ_DATA_COM				0x06
#define FMTDEF_RTFP_PID_FILE_READ_DATA_ANS				0x60

#define FMTDEF_RTFP_PID_FILE_ERASE_COM					0x07
#define FMTDEF_RTFP_PID_FILE_ERASE_ANS					0x70


// Status
#define FMTDEF_RTFP_STAT_OK								0x00
#define FMTDEF_RTFP_STAT_INVALID_FILE					0xE1
#define FMTDEF_RTFP_STAT_ACCESS_DENIED					0xE2
#define FMTDEF_RTFP_STAT_FILE_ERROR						0xE3
#define FMTDEF_RTFP_STAT_HDW_ERROR						0xE4
#define FMTDEF_RTFP_STAT_FILE_NOT_FOUND					0xE5




// Return the packet len from payload size
#define FMTDEFM_RTFP_GET_PACKET_LEN(pyb)		(pyb + 10)

// Return the CRC byte index from payload size
#define FMTDEFM_RTFP_PCK_CRC_IDX(pyb)			(pyb + 8)

// Return handler SID
#define FMTDEFM_RTFP_GET_SID(buf)				(*(buf + FMTDEF_RTFP_PCK_SID_IDX))

// Return handler DID
#define FMTDEFM_RTFP_GET_DID(buf)				(*(buf + FMTDEF_RTFP_PCK_DID_IDX))

// Return handler PID
#define	FMTDEFM_RTFP_GET_PID(buf)				(*(buf + FMTDEF_RTFP_PCK_PID_IDX))

// Return handler Payload Number of Bytes
#define FMTDEFM_RTFP_GET_PYB(buf)				(FMT::Uint16FromBuf(buf + FMTDEF_RTFP_PCK_PYB_IDX, FMT::e_ByteOrdering_LittleEndian))

// Return handler PKN
#define FMTDEFM_RTFP_GET_PKN(buf)         		(FMT::Uint16FromBuf(buf + FMTDEF_RTFP_PCK_PKN_IDX, FMT::e_ByteOrdering_LittleEndian))

// Return handler CRC
#define FMTDEFM_RTFP_GET_CRC(buf, len)			(FMT::Uint16FromBuf(buf + len - 2, FMT::e_ByteOrdering_LittleEndian))




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

// CRC Seed
#define FMTDEF_RFTP_CRC_SEED					0xFFFF




// *************************************************************************************
// *************************************************************************************
//	Class CFMT_CommRftp
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_CommRftp : public CFMT_HdwProtocol, public CFMT_CommObject
{
	// =====================================================================================
	//	TYPES
	// =====================================================================================

protected:

	// --- [t_RxState] --------------------------------------

	enum t_RxState
	{
		e_RxState_Start		= 0,
		e_RxState_Did		= 1,
		e_RxState_Sid		= 2,
		e_RxState_Pid		= 3,
		e_RxState_PknLo		= 4,
		e_RxState_PknHi		= 5,
		e_RxState_PybLo		= 6,
		e_RxState_PybHi		= 7,
		e_RxState_Payload	= 8,
		e_RxState_CrcLo		= 9,
		e_RxState_CrcHi		= 10
	};


public:


	// =====================================================================================
	//	VARIABLES
	// =====================================================================================

protected:

	// Identifier
	t_FMT_Uint8                             m_ucID;

	// Input Byte Service
	CFMT_HdwByteInBufferService				*m_pInService;

	// Output Byte Service
	CFMT_HdwByteOutBufferService			*m_pOutService;

	// CRC
	static CFMT_Crc							s_Crc;

	// CRC
	static CFMT_Crc							s_FileCrc;

	// RX Packet buffer
	t_FMT_Uint8*							m_pucRxPacket;

	// TX Packet buffer
	t_FMT_Uint8*							m_pucTxPacket;

	// RX State
	t_RxState								m_RxState;

	// Number of RX bytes
	t_FMT_Uint32                            m_uiRxNdw;

	// Number of TX bytes
	t_FMT_Uint32                            m_uiTxNdw;


	// RX Payload Number of Bytes
	t_FMT_Uint16                            m_usRxPyb;

	// RX Watchdog Timer
	t_FMT_Uint64                            m_quiRxTimer;

	// Current Computed CRC
	t_FMT_Uint16                            m_usRxCurrentCrc;

	// Last Packet Number
	t_FMT_Uint16							m_usLastPkn;

public:

	// Write Timeout
	t_FMT_Uint64							m_quiRxByteTimeout;


	// Write Timeout
	t_FMT_Uint32							m_uiWriteTimeout;


	// =====================================================================================
	// CONSTRUCTORS & DESTRUCTORS
	// =====================================================================================

public:

	CFMT_CommRftp();
	virtual ~CFMT_CommRftp();


	// =====================================================================================
	//	FUNCTIONS
	// =====================================================================================

protected:

	// Reset RFTP RX Parameters
	void					ResetRxParam();

	// Process data reception
	t_FMT_Uint32			Receive();

	// Process valid packet reception
	t_FMT_Uint32			ReceivePacket(t_FMT_Uint32 uiTimeoutMs);

	// Build basic answer packet into local buffer
	void					BuildBasicAnsPacket(t_FMT_Uint8 ucPid);

	// Build basic command packet into local buffer
	void					BuildBasicComPacket(t_FMT_Uint8 ucDid, t_FMT_Uint8 ucPid);

	// Build loopback command packet into local buffer
	void					BuildLoopbackComPacket(t_FMT_Uint8 ucDid, t_FMT_Uint16 usPybSize);

	// Build file erase command packet into local buffer
	void					BuildFileEraseComPacket(t_FMT_Uint8 ucDid, t_FMT_Uint8 ucFileId);

	void					BuildFileReadDataComPacket(t_FMT_Uint8 ucDid, t_FMT_Uint8 ucFileId);
	void					BuildFileCloseComPacket(t_FMT_Uint8 ucDid, t_FMT_Uint8 ucFileId);
	void					BuildFileReadOpenComPacket(t_FMT_Uint8 ucDid, t_FMT_Uint8 ucFileId);
	void					BuildFileWriteDataComPacket(t_FMT_Uint8 ucDid, t_FMT_Uint8 ucFileId, t_FMT_Uint8* pucDataBuffer, t_FMT_Uint32 uiBufferSize);
	void					BuildFileWriteOpenComPacket(t_FMT_Uint8 ucDid, t_FMT_Uint8 ucFileId, t_FMT_Uint16 usFileCode, t_FMT_Uint32 uiFileSize, t_FMT_Uint32 uiFileCrc,
																t_FMT_Uint64 quiTimeStamp, t_FMT_Uint8* pucExtraBytes);


	// Compute file CRC
	t_FMT_Uint32            FileCalcCrc(t_FMT_Uint32 uiOldCrc, t_FMT_Uint8* pucBuf, t_FMT_Uint32 uiBuflen);

	// Notify valid packet reception
	virtual void			NotifyRxPacket(t_FMT_Uint8* pucBuf, t_FMT_Uint32 uiLen);

	// Notify valid packet transmission
	virtual void			NotifyTxPacket(t_FMT_Uint8* pucBuf, t_FMT_Uint32 uiLen);

	// Send a packet
	t_FMT_Uint32 			SendPacket(t_FMT_Uint8* pucBuf, t_FMT_Uint32 uiLen, t_FMT_Uint32 uiTimeout);

	// Build the time stamp string
	static CFMT_String		GetLogTimeString(t_FMT_Uint64 quiTimeStamp);

	// Return the status string
	static CFMT_String		GetResultString(t_FMT_Uint8 ucStatus);

	// Check if character is ASCII printable
	static t_FMT_Bool		IsPrintableAscii(t_FMT_Uint8 ucData, CFMT_String& sText);

	// Decode Commands 
	static void				DecodeLoopbackCommand(t_FMT_Uint8* pucPacket, t_FMT_Uint32 uiSize, CFMT_StringList& slDecodedBuf);
	static void				DecodeFileWriteOpenCommand(t_FMT_Uint8* pucPacket, t_FMT_Uint32 uiSize, CFMT_StringList& slDecodedBuf);
	static void				DecodeFileReadOpenCommand(t_FMT_Uint8* pucPacket, t_FMT_Uint32 uiSize, CFMT_StringList& slDecodedBuf);
	static void				DecodeFileWriteDataCommand(t_FMT_Uint8* pucPacket, t_FMT_Uint32 uiSize, CFMT_StringList& slDecodedBuf);
	static void				DecodeFileReadDataCommand(t_FMT_Uint8* pucPacket, t_FMT_Uint32 uiSize, CFMT_StringList& slDecodedBuf);
	static void				DecodeFileCloseCommand(t_FMT_Uint8* pucPacket, t_FMT_Uint32 uiSize, CFMT_StringList& slDecodedBuf);
	static void				DecodeFileEraseCommand(t_FMT_Uint8* pucPacket, t_FMT_Uint32 uiSize, CFMT_StringList& slDecodedBuf);

	// Decode Answers
	static void				DecodeLoopbackAnswer(t_FMT_Uint8* pucPacket, t_FMT_Uint32 uiSize, CFMT_StringList& slDecodedBuf);
	static void				DecodeFileWriteOpenAnswer(t_FMT_Uint8* pucPacket, t_FMT_Uint32 uiSize, CFMT_StringList& slDecodedBuf);
	static void				DecodeFileReadOpenAnswer(t_FMT_Uint8* pucPacket, t_FMT_Uint32 uiSize, CFMT_StringList& slDecodedBuf);
	static void				DecodeFileWriteDataAnswer(t_FMT_Uint8* pucPacket, t_FMT_Uint32 uiSize, CFMT_StringList& slDecodedBuf);
	static void				DecodeFileReadDataAnswer(t_FMT_Uint8* pucPacket, t_FMT_Uint32 uiSize, CFMT_StringList& slDecodedBuf);
	static void				DecodeFileCloseAnswer(t_FMT_Uint8* pucPacket, t_FMT_Uint32 uiSize, CFMT_StringList& slDecodedBuf);
	static void				DecodeFileEraseAnswer(t_FMT_Uint8* pucPacket, t_FMT_Uint32 uiSize, CFMT_StringList& slDecodedBuf);

public:

	// Compute file CRC
	static t_FMT_Uint32     GetFileCrc(t_FMT_Uint8* pucBuf, t_FMT_Uint32 uiBuflen);

	// Set Identifier
	void                    SetID(t_FMT_Uint8 ucID);

	// Get Identifier
	t_FMT_Uint8             GetID();

	// Get the last packet number
	t_FMT_Uint16			GetLastPkn()  const;

	// Mount protocol services
	virtual t_FMT_Uint32	Mount(CFMT_HdwByteInBufferService *pInService, CFMT_HdwByteOutBufferService *pOutService);

	// Decode RFTP packet and buil a string list
	static void				DecodePacket(t_FMT_Uint8* pucPacket, t_FMT_Uint32 uiSize, t_FMT_Uint64 quiTimeStamp, t_FMT_Bool bTX, CFMT_StringList& slDecodedBuf);


};

#endif
