// =====================================================================================
/**
 * @file					FMT_CsvFile.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					03/11/2024
 * @brief					CSV File Management
 *
 * @version	Project:		Formatech C++ Core Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][03/11/2024]
 */
// =====================================================================================


#ifndef FMTDEF_CSVFILE_H
#define FMTDEF_CSVFILE_H


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

#ifndef FMTDEF_FILE_H
#include "FMT_File.h"
#endif

using namespace FMT;


// =====================================================================================
//	DEFINES
// =====================================================================================



// *************************************************************************************
// *************************************************************************************
//	Class CFMT_CsvFile
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_CsvFile : protected CFMT_File
{
// =====================================================================================
//	TYPES
// =====================================================================================

public:


// =====================================================================================
//	VARIABLES
// =====================================================================================

public:

protected:

    // Number of fields per record
    t_FMT_Uint32        m_uiNumFields;

    // Field Separator
    t_FMT_Char          m_chSep;

    // End-of-Line type
    t_FMT_Uint32        m_uiLm;


// =====================================================================================
// CONSTRUCTORS & DESTRUCTORS
// =====================================================================================

public:

	CFMT_CsvFile(t_FMT_Uint32 uiNumFields, t_FMT_Char chSep = ',', t_FMT_Uint32 lm = e_EOL | e_EOR);
	~CFMT_CsvFile();

// =====================================================================================
//	FUNCTIONS
// =====================================================================================

protected:

    // Format a string as CSV field
    CFMT_String         FormatField(const CFMT_String& sField);

public:

    // Open/close ----------------------------------------------------------

    // Open the file
    t_FMT_Uint32		Open(const CFMT_String& sPath, t_FMT_Uint32 mode);

    // Close the file
    void				Close();


    // Write/Read ----------------------------------------------------------

    // Write a record
    t_FMT_Uint32        WriteRecord(CFMT_StringList& lsRec);
    t_FMT_Uint32        WriteRecord(CFMT_StringVector& vcRec);

    // Read all file
    CFMT_StringVector* ReadFile(const CFMT_String& sPath, t_FMT_Uint32& uiNumRec);


};


#endif
