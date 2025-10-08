// =====================================================================================
/**
 * @file					FMT_HdwMilStd1553Buffer.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					10/01/2020
 * @brief					Mil-Std-1553 Data Buffer
 *
 * @version	Project:		Formatech C++ Hardware Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][10/01/2020]
 */
// =====================================================================================



#ifndef FMTDEF_HDW_MILSTD1553BUFFER_H
#define FMTDEF_HDW_MILSTD1553BUFFER_H

// =====================================================================================
//	INCLUDES
// =====================================================================================


#ifndef FMTDEF_CORE_H
#include "FMT_Core.h"
#endif


// =====================================================================================
//	DEFINES
// =====================================================================================



// *************************************************************************************
// *************************************************************************************
//	Class CFMT_HdwMilStd1553Buffer
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_HdwMilStd1553Buffer : public CFMT_Object
{
// =====================================================================================
//	TYPES
// =====================================================================================

public:

    friend class CFMT_HdwMilStd1553BcService;
    friend class CFMT_HdwMilStd1553SingleRtService;

protected:

    t_FMT_Uint32	m_uiIndex;
    t_FMT_Uint16	m_pusData[32];
    CFMT_Mutex		*m_pMutex;
    t_FMT_Bool		m_bUpdated;

public:


    // =====================================================================================
    //	VARIABLES
    // =====================================================================================

protected:
public:

// =====================================================================================
// CONSTRUCTORS & DESTRUCTORS
// =====================================================================================

public:

    //! Empty constructor
    CFMT_HdwMilStd1553Buffer();

    //! Destructor
    virtual ~CFMT_HdwMilStd1553Buffer();


// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:

    //! Lock buffer access
    t_FMT_Uint32		Lock();

    //! Unlock buffer access
    t_FMT_Uint32		Unlock();

public:

    //! Return updated flag
    t_FMT_Bool			IsUpdated() const;

    //! Set a word inside the buffer
    t_FMT_Uint32		SetWord(t_FMT_Uint8 ucIdx, t_FMT_Uint16 usData);

    //! Get a word from the buffer
    t_FMT_Uint32		GetWord(t_FMT_Uint8 ucIdx, t_FMT_Uint16 *pusData, t_FMT_Bool bResetUpdateFlag = FMTDEF_TRUE);

    //! Set a buffer word interval
    t_FMT_Uint32		SetBuffer(t_FMT_Uint8 ucStart, t_FMT_Uint8 ucSize, t_FMT_Uint16 *pusData);

    //! Get a buffer word interval
    t_FMT_Uint32		GetBuffer(t_FMT_Uint8 ucStart, t_FMT_Uint8 ucSize, t_FMT_Uint16 *pusData, t_FMT_Bool bResetUpdateFlag = FMTDEF_TRUE);


};



#endif







