// =====================================================================================
/**
 * @file					FMT_CommRftpClient.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					03/09/2025
 * @brief					Reliable indexed File Transfer Protocol Client
 *
 * @version	Project:		Formatech C++ Communication Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][03/09/2025]
 */
// =====================================================================================


#ifndef FMTDEF_COMM_RFTP_CLIENT_H
#define FMTDEF_COMM_RFTP_CLIENT_H

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
//	Class CFMT_CommRftpClient
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_CommRftpClient : public CFMT_CommRftp
{
	// =====================================================================================
	//	TYPES
	// =====================================================================================

private:

protected:

public:

	// =====================================================================================
	//	VARIABLES
	// =====================================================================================

private:

protected:

public:



	// =====================================================================================
	// CONSTRUCTORS & DESTRUCTORS
	// =====================================================================================

public:

	CFMT_CommRftpClient();
	virtual ~CFMT_CommRftpClient();


	// =====================================================================================
	//	FUNCTIONS
	// =====================================================================================

private:


protected:


public:

	// Set the packet number
	void				SetPkn(t_FMT_Uint16 usPkn);

	// Process a loopback command
	t_FMT_Uint32		ProcessLoopback(t_FMT_Uint8 ucDid, t_FMT_Uint16 usPybSize, t_FMT_Uint32 uiRxTimeout);

	// Process a file erase command
	t_FMT_Uint32		ProcessFileErase(t_FMT_Uint8 ucDid, t_FMT_Uint8 ucFileId, t_FMT_Uint32 uiRxTimeout);

	// Process a file close command
	t_FMT_Uint32		ProcessFileClose(t_FMT_Uint8 ucDid, t_FMT_Uint8 ucFileId, t_FMT_Uint32 uiRxTimeout);

	// Process a file open-to-write command
	t_FMT_Uint32		ProcessFileWriteOpen(t_FMT_Uint8 ucDid, t_FMT_Uint8 ucFileId, t_FMT_Uint16 usFileCode, t_FMT_Uint32 uiFileSize, t_FMT_Uint32 uiFileCrc,
														t_FMT_Uint64& quiTimeStamp, t_FMT_Uint8* pucExtraBytes, t_FMT_Uint32 uiRxTimeout);

	// Process a file open-to-read command
	t_FMT_Uint32		ProcessFileReadOpen(t_FMT_Uint8 ucDid, t_FMT_Uint8 ucFileId, t_FMT_Uint16& usFileCode, t_FMT_Uint32& uiFileSize, t_FMT_Uint32& uiFileCrc,
														t_FMT_Uint64& quiTimeStamp, t_FMT_Uint8* pucExtraBytes, t_FMT_Uint32 uiRxTimeout);

	// Process a file write data command
	t_FMT_Uint32		ProcessFileWriteData(t_FMT_Uint8 ucDid, t_FMT_Uint8 ucFileId, t_FMT_Uint8* pucFileBuffer, t_FMT_Uint32 uiBlockSize, t_FMT_Uint32 uiRxTimeout);
	
	// Process a file read data command
	t_FMT_Uint32		ProcessFileReadData(t_FMT_Uint8 ucDid, t_FMT_Uint8 ucFileId, t_FMT_Uint8* pucFileBuffer, t_FMT_Uint32& uiReadSize, t_FMT_Uint32 uiRxTimeout);

};

#endif
