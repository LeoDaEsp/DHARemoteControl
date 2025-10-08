// =====================================================================================
/**
 * @file					FMT_HdwMilStd1553MinorFrame.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					10/01/2020
 * @brief					Mil-Std-1553 Minor Frame
 *
 * @version	Project:		Formatech C++ Hardware Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][10/01/2020]
 */
// =====================================================================================



#ifndef FMTDEF_HDW_MILSTD1553MINORFRAME_H
#define FMTDEF_HDW_MILSTD1553MINORFRAME_H

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

#ifndef FMTDEF_HDW_MILSTD1553MESSAGE_H
#include "FMT_HdwMilStd1553Message.h"
#endif


// =====================================================================================
//	DEFINES
// =====================================================================================



// *************************************************************************************
// *************************************************************************************
//	Class CFMT_HdwMilStd1553MinorFrame
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_HdwMilStd1553MinorFrame : public CFMT_Object
{
// =====================================================================================
//	TYPES
// =====================================================================================

public:

    friend class CFMT_HdwMilStd1553BcService;

protected:

    t_FMT_Uint32					m_uiIndex;
    t_FMT_Uint32					m_uiTotMessages;
    CFMT_HdwMilStd1553Message		**m_ppMessages;

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
    CFMT_HdwMilStd1553MinorFrame();

    //! Destructor
    virtual ~CFMT_HdwMilStd1553MinorFrame();


// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:
public:

    //! Reset the minor frame
    t_FMT_Uint32				Reset();

    //! Create a minor frame
    t_FMT_Uint32				Create(t_FMT_Uint32 uiTotMessages);

    //! Set a minor frame
    t_FMT_Uint32				Set(t_FMT_Uint32 uiIdx,CFMT_HdwMilStd1553Message *pMessage);

    //! Get a message of the frame
    CFMT_HdwMilStd1553Message*	Get(t_FMT_Uint32 uiIdx);

    //! Return the total number of messages
    t_FMT_Uint32				GetSize() const;

};



#endif







