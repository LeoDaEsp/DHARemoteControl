// =====================================================================================
/**
 * @file					FMT_CommTftp.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					28/06/2022
 * @brief					Basic items for TFTP Client/Server
 *
 * @version	Project:		Formatech C++ Communication Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][28/06/2022]
 */
// =====================================================================================



#ifndef FMTDEF_COMM_FMTTFTP_H
#define FMTDEF_COMM_FMTTFTP_H

// =====================================================================================
//	INCLUDES
// =====================================================================================


#ifndef FMTDEF_CORE_H
#include "FMT_Core.h"
#endif

#ifndef FMTDEF_HDW_H
#include "FMT_Hdw.h"
#endif

// =====================================================================================
//	DEFINES
// =====================================================================================

// Thread type according to OS
#ifdef FMTDEF_COMPILE_OS_WINDOWS
#define FMTDEF_COMM_TFTP_THREAD                   		HANDLE
#define FMTDEF_COMM_TFTP_THREAD_SIZE					(0)
#endif

#ifdef FMTDEF_COMPILE_OS_LINUX
#define FMTDEF_COMM_TFTP_THREAD                   		pthread_t
#endif

// Maximum data buffer size
#define FMTDEF_COMM_TFTP_MAX_BUF_SIZE					1300

// Maximum file name length
#define FMTDEF_COMM_TFTP_MAX_FILENAME_LEN				200


// Nominal timeout
#define FMTDEF_COMM_TFTP_NOM_TIMEOUT					3000

// Minimum timeout
#define FMTDEF_COMM_TFTP_MIN_TIMEOUT					1000

// Maximum timeout
#define FMTDEF_COMM_TFTP_MAX_TIMEOUT					10000


// Nominal block size
#define FMTDEF_COMM_TFTP_NOM_BLOCK_SIZE					512

// Maximum block size
#define FMTDEF_COMM_TFTP_MAX_BLOCK_SIZE					(FMTDEF_COMM_TFTP_MAX_BUF_SIZE - 4)

// Minimum block size
#define FMTDEF_COMM_TFTP_MIN_BLOCK_SIZE					64



// Limits for TFTP TSIZE option
#define FMTDEF_COMM_TFTP_MIN_TSIZE						1
#define FMTDEF_COMM_TFTP_MAX_TSIZE						0x7FFFFFFF



// TFTP Opcodes
#define FMTDEF_COMM_TFTP_OPCODE_RRQ						0x0001
#define FMTDEF_COMM_TFTP_OPCODE_WRQ						0x0002
#define FMTDEF_COMM_TFTP_OPCODE_DATA					0x0003
#define FMTDEF_COMM_TFTP_OPCODE_ACK						0x0004
#define FMTDEF_COMM_TFTP_OPCODE_ERR						0x0005
#define FMTDEF_COMM_TFTP_OPCODE_OACK					0x0006

// TFTP Error Codes
#define FMTDEF_COMM_TFTP_ERRCODE_NOT_DEFINED            0
#define FMTDEF_COMM_TFTP_ERRCODE_FILE_NOT_FOUND         1
#define FMTDEF_COMM_TFTP_ERRCODE_ACCESS_VIOLATION       2
#define FMTDEF_COMM_TFTP_ERRCODE_DISK_FULL              3
#define FMTDEF_COMM_TFTP_ERRCODE_QUOTA_EXCEEDED         3
#define FMTDEF_COMM_TFTP_ERRCODE_ILLEGAL_TFTP_OPERATION 4
#define FMTDEF_COMM_TFTP_ERRCODE_UNKNOWN_PORT_NUMBER    5
#define FMTDEF_COMM_TFTP_ERRCODE_FILE_EXISTS            6

/* Limits for TFTP parameters */
#define FMTDEF_COMM_TFTP_ERRORSTRING_LEN				(512-4)
#define FMTDEF_COMM_TFTP_FILENAME_LEN					(50)
#define FMTDEF_COMM_TFTP_MODE_LEN						(50)
#define FMTDEF_COMM_TFTP_OPTNAME_LEN					(50)
#define FMTDEF_COMM_TFTP_OPTVAL_LEN						(50)



// =====================================================================================
//	GLOBAL FUNCTIONS
// =====================================================================================


namespace FMT_Comm_Tftp
{
	// TFTP Data Modes
	enum t_DataMode
	{
		e_DataMode_Write        = 0,
		e_DataMode_Read         = 1
	};

	// Check if a string exists into the buffer
	t_FMT_Uint32 FMTDEF_LIB_DLLSPEC TftpGetString(t_FMT_Uint8 *pucBuf, t_FMT_Uint32 uiMaxLen, t_FMT_Uint32 *puiStrLen);

	// Build a TFTP Error Message */
    void FMTDEF_LIB_DLLSPEC			TftpBuildErrorPacket(t_FMT_Uint8 *pucBuf, t_FMT_Uint32 *puiLen, t_FMT_Uint16 usErrorCode, const t_FMT_Char *pchErrorString);

	// Build a TFTP ACK Message */
	void FMTDEF_LIB_DLLSPEC			TftpBuildAckPacket(t_FMT_Uint8 *pucBuf, t_FMT_Uint32 *puiLen, t_FMT_Uint16 usAckBlock);
}

#endif







