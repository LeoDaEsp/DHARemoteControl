// =====================================================================================
/**
 * @file					FMT_File.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					28/03/2018
 * @brief					File Management
 *
 * @version	Project:		Formatech C++ Core Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][28/03/2018]
 */
// =====================================================================================


#ifndef FMTDEF_FILE_H
#define FMTDEF_FILE_H


// =====================================================================================
//	INCLUDES
// =====================================================================================


#ifndef FMTDEF_GLOBAL_H
#include "FMT_Global.h"
#endif

#ifndef FMTDEF_OBJECT_H
#include "FMT_Object.h"
#endif

#ifndef FMTDEF_EXCEPTION_H
#include "FMT_Exception.h"
#endif

#ifndef FMTDEF_STRING_H
#include "FMT_String.h"
#endif


using namespace FMT;


// =====================================================================================
//	DEFINES
// =====================================================================================

#define FMTDEF_FILE_DEFAULT_COPYBUFFER_SIZE     0x10000


// *************************************************************************************
// *************************************************************************************
//	Class CFMT_File
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_File : public CFMT_Object
{
// =====================================================================================
//	TYPES
// =====================================================================================

public:

    //! Open Flags
    enum t_OpenMode
    {
        e_OpenMode_None					= 0x0000,
        e_OpenMode_Write				= 0x0001,
        e_OpenMode_Read					= 0x0002,
        e_OpenMode_ReadWrite			= 0x0003,
        e_OpenMode_Overwrite            = 0x0004
    };

    //! Seek starting modes
	enum t_Seek
	{
		e_Seek_FromCur			= 0,
		e_Seek_FromStart		= 1,
		e_Seek_FromEnd			= 2
	};

    //! End of text line modes
    enum t_EndLineMode
	{
		e_EOS			= 0x01,	// \0
		e_EOL			= 0x02,	// \n
		e_EOR			= 0x04	// \r
    };


// =====================================================================================
//	VARIABLES
// =====================================================================================

public:

protected:

    //! File handle
    t_FMT_File			*m_pFile;

    //! Opening Flags
    t_FMT_Uint32		m_uiOpenFlags;

    //! Opening File Path
    CFMT_String         m_sOpenPath;



// =====================================================================================
// CONSTRUCTORS & DESTRUCTORS
// =====================================================================================

public:

	CFMT_File();
	~CFMT_File();

// =====================================================================================
//	FUNCTIONS
// =====================================================================================

protected:

public:

    //! Get full file path from path
    static CFMT_String	GetFullPathFromPath(const CFMT_String& sPath);

	//! Extract file path from path
    static CFMT_String	GetPathFromPath(const CFMT_String& sPath);

	//! Extract file name from path
    static CFMT_String	GetNameFromPath(const CFMT_String& sPath);


	
	// Open/close ----------------------------------------------------------

    //! Open the file
    t_FMT_Uint32		Open(const CFMT_String& sPath, t_FMT_Uint32 mode);

    //! Close the file
    void				Close();


    // Properties ----------------------------------------------------------

    //! Return the open flags
    t_FMT_Uint32		GetOpenFlags() const;

    //! Check if the file is already open
    t_FMT_Bool			IsOpen() const;

    //! Return the file length
    t_FMT_Uint64		GetLength() const;

    //! Return the file position
    t_FMT_Uint64		GetPos() const;

    //! Check if the file pointer is at the end
    t_FMT_Bool			IsEOF() const;

    //! Verify if a file is present
    static t_FMT_Bool 	IsPresent(const CFMT_String& sFileName);

    //! Return the file name
    CFMT_String         GetName()  const;

    //! Return the file name
    CFMT_String         GetPath()  const;

    //! Return the file full pathc
    CFMT_String         GetFullPath()  const;


    // Random access -------------------------------------------------------

    //! Set the file pointer to the begin
    t_FMT_Uint32		ToStart();

    //! Set the file pointer to the end
    t_FMT_Uint32		ToEnd();

    //! Set the file pointer to the qwPos according sk direction
    t_FMT_Uint32		To(t_FMT_Uint64 quiPos, t_FMT_Uint32 sk = e_Seek_FromCur);


    // Binary Write/Read ---------------------------------------------------

    //! Forces any data remaining in the file buffer to be written to the file.
    t_FMT_Uint32		Flush();

    //! Writes (unbuffered) data in a file to the current file position.
    t_FMT_Uint32		Write(void *pBuf, t_FMT_Uint64 quiSize, t_FMT_Bool bFlush = FMTDEF_TRUE);

    //! Reads (unbuffered) data from a file at the current file position.
    t_FMT_Uint32		Read(void *pBuf, t_FMT_Uint64 quiSize);

    // File Management ---------------------------------------------------------

    //! Copy a file
    static t_FMT_Uint32 CopyFile(const CFMT_String& sDstPath, const CFMT_String& sSrcPath, t_FMT_Uint32 uiCopyBlockSize = FMTDEF_FILE_DEFAULT_COPYBUFFER_SIZE);

    //! Remnve a file
    static t_FMT_Uint32 DeleteFile(const CFMT_String& sPath);

    // Text file access -------------------------------------------------------

    //! Read a C-Style string from the file
    t_FMT_Uint32		ReadTextLine(t_FMT_Char *pchString, t_FMT_Uint32 uiMaxSize);

    //! Read a string from the file
    t_FMT_Uint32        ReadTextLine(CFMT_String& s);

    //! Write a C-Style string to file
    t_FMT_Uint32        WriteText(const t_FMT_Char *pchString);

    //! Write a C-Style string to file adding end of line
    t_FMT_Uint32        WriteTextLine(const t_FMT_Char *pchString, t_FMT_Uint32 lm=e_EOL|e_EOR);

    //! Write a string to file
    t_FMT_Uint32        WriteText(const CFMT_String& s);

    //! Write a string to file adding end of line
    t_FMT_Uint32        WriteTextLine(const CFMT_String& s, t_FMT_Uint32 lm=e_EOL|e_EOR);

};


#endif
