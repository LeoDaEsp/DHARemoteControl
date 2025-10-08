// =====================================================================================
/**
 * @file					FMT_MemoryBuffer.h
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



#ifndef FMTDEF_MEMORYBUFFER_H
#define FMTDEF_MEMORYBUFFER_H

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


// =====================================================================================
//	DEFINES
// =====================================================================================



// *************************************************************************************
// *************************************************************************************
//	Class CFMT_MemoryBuffer
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_MemoryBuffer : public CFMT_Buffer
{
// =====================================================================================
//	TYPES
// =====================================================================================

protected:

public:

    //! Memory Blocks
    class FMTDEF_LIB_DLLSPEC CBlockList : public CFMT_List<CFMT_Uint8Vector>
    {
    };


// =====================================================================================
//	VARIABLES
// =====================================================================================

protected:

    //! Current position inside current block
    t_FMT_Uint32				m_uiPointer;

    //! Current block
    CFMT_Uint8Vector			*m_pCurBlock;

    //! Current block index
    t_FMT_Uint32				m_uiCurBlock;

    //! Memory block list
    CBlockList					m_BlockList;

public:

// =====================================================================================
// CONSTRUCTORS & DESTRUCTORS
// =====================================================================================

public:

    //! Empty constructor
    CFMT_MemoryBuffer(t_FMT_Uint32 uiDataBlockSize = 1024);

    //! Destructor
    virtual ~CFMT_MemoryBuffer();


// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:

	//virtual void        DataCopy(const CFMT_MemoryBuffer& op);

public:

    //! Get absolute pointer position
    virtual t_FMT_Uint64	GetAbsPosition();

    //! Empty the buffer
    virtual void            DeleteAll();

    //! Set the pointer at the beginning of the buffer
    virtual void            ToStart();

    //! Set the pointer at the end of the buffer
    virtual void            ToEnd();

    //! Append a byte block of uiSize
    virtual void            AppendData(void *pvData,t_FMT_Uint32 uiSize);

    //! Read a byte block of uiSize
    virtual void            RetrieveData(void *pvData, t_FMT_Uint32 uiSize);



};



#endif







