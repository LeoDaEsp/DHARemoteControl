// =====================================================================================
/**
 * @file					FMT_CommTftpFileServer.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					28/06/2022
 * @brief					TFTP File Server
 *
 * @version	Project:		Formatech C++ Communication Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][28/06/2022]
 */
// =====================================================================================



#ifndef FMTDEF_COMM_TFTPFILESERVER_H
#define FMTDEF_COMM_TFTPFILESERVER_H

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

#ifndef FMTDEF_COMM_TFTPSERVER_H
#include "FMT_CommTftpServer.h"
#endif

// =====================================================================================
//	DEFINES
// =====================================================================================


// *************************************************************************************
// *************************************************************************************
//	Class CFMT_CommTftpFileServer
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_CommTftpFileServer : public CFMT_CommTftpServer
{
// =====================================================================================
//	TYPES
// =====================================================================================

protected:

public:

	// ---[ CParameters ]-----------------------------------------------

	class FMTDEF_LIB_DLLSPEC CParameters : public CFMT_CommTftpServer::CParameters
	{
	public:

		CFMT_String			m_sWorkingFolder;

		CParameters();
	};


    // --- CFileList --------------------------------------------

    class FMTDEF_LIB_DLLSPEC CFileList : public CFMT_List<CFMT_File*>
    {
    };


    // =====================================================================================
    //	VARIABLES
    // =====================================================================================

protected:

	// Parameters
	CParameters							m_Params;

	// File List
	CFileList							m_FileList;

	// File Access Mutex
	CFMT_Mutex							m_Mutex;


public:


// =====================================================================================
// CONSTRUCTORS & DESTRUCTORS
// =====================================================================================

public:

    // Empty constructor
    CFMT_CommTftpFileServer();

	// Destructor
    virtual ~CFMT_CommTftpFileServer();


// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:

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
};



#endif







