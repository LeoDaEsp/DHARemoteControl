// =====================================================================================
/**
 * @file					FMT_FileBuffer.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					24/03/2018
 * @brief					Memory Buffer
 *
 * @version	Project:		Formatech C++ Core Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][24/03/2018]
 */
// =====================================================================================



#ifndef FMTDEF_FILEBUFFER_H
#define FMTDEF_FILEBUFFER_H

// =====================================================================================
//	INCLUDES
// =====================================================================================


#ifndef FMTDEF_GLOBAL_H
#include "FMT_Global.h"
#endif

#ifndef FMTDEF_BASICCONTAINERS_H
#include "FMT_BasicContainers.h"
#endif

#ifndef FMTDEF_BUFFER_H
#include "FMT_Buffer.h"
#endif

#ifndef FMTDEF_FILE_H
#include "FMT_File.h"
#endif


// =====================================================================================
//	DEFINES
// =====================================================================================



// *************************************************************************************
// *************************************************************************************
//	Class CFMT_FileBuffer
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_FileBuffer : public CFMT_Buffer
{
// =====================================================================================
//	TYPES
// =====================================================================================

protected:

public:



// =====================================================================================
//	VARIABLES
// =====================================================================================

protected:

    //! Current block pointer
    t_FMT_Uint64		m_quiBlockPointer;

    //! Absolute file pointer
    t_FMT_Uint64		m_quiAbsPointer;

    //! Current block
    t_FMT_Uint8			*m_pucCurBlock;

    //! File associated to the buffer
    CFMT_File			*m_pFile;

    //! Last read block size
    t_FMT_Uint64		m_quiLastReadBlockSize;


public:

// =====================================================================================
// CONSTRUCTORS & DESTRUCTORS
// =====================================================================================

public:

    //! Empty Constructor
    CFMT_FileBuffer(t_FMT_Uint32 uiDataBlockSize = 1024);

    //! Destructor
    virtual ~CFMT_FileBuffer();


// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:

public:

    //! Get absolute pointer position
    virtual t_FMT_Uint64	GetAbsPosition();

    //! Set the pointer at the beginning of the buffer
    virtual void            ToStart();

    //! Set the pointer at the end of the buffer
    virtual void            ToEnd();

    //! Attach the file for serialization
    virtual t_FMT_Uint32	AttachFile(CFMT_File *pFile, t_Access access);

    //! Flushes unwritten data and disconnects from the file
    virtual void			Close();

    //! Disconnects from the file without flushing unwritten data
    virtual void			Abort();

    //! Append a byte block of uiSize
    virtual void            AppendData(void *pvData, t_FMT_Uint32 uiSize);

    //! Read a byte block of uiSize
    virtual void            RetrieveData(void *pvData, t_FMT_Uint32 uiSize);

};



#endif







