// =====================================================================================
/**
 * @file					FMT_HdwMilStd1553MajorFrame.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					10/01/2020
 * @brief					Abstract Hardware Device
 *
 * @version	Project:		Formatech C++ Hardware Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][10/01/2020]
 */
// =====================================================================================



#ifndef FMTDEF_HDW_MILSTD1553MAJORFRAME_H
#define FMTDEF_HDW_MILSTD1553MAJORFRAME_H

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

#ifndef FMTDEF_HDW_MILSTD1553MINORFRAME_H
#include "FMT_HdwMilStd1553MinorFrame.h"
#endif

#ifndef FMTDEF_HDW_MILSTD1553MAJORFRAME_H
#include "FMT_HdwMilStd1553MajorFrame.h"
#endif


// =====================================================================================
//	DEFINES
// =====================================================================================



// *************************************************************************************
// *************************************************************************************
//	Class CFMT_HdwMilStd1553MajorFrame
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_HdwMilStd1553MajorFrame : public CFMT_Object
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

    t_FMT_Uint32					m_uiTotMinorFrames;
    CFMT_HdwMilStd1553MinorFrame	**m_ppMinorFrames;

public:

// =====================================================================================
// CONSTRUCTORS & DESTRUCTORS
// =====================================================================================

public:

    //! Empty constructor
    CFMT_HdwMilStd1553MajorFrame();

    //! Destructor
    virtual ~CFMT_HdwMilStd1553MajorFrame();


// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:
public:

    //! Reset the major frame
    t_FMT_Uint32					Reset();

    //! Create a major frame and set its size
    t_FMT_Uint32					Create(t_FMT_Uint32 uiTotMinorFrames);

    //! Set a minor frame
    t_FMT_Uint32					Set(t_FMT_Uint32 uiIdx,CFMT_HdwMilStd1553MinorFrame *pMinorFrame);

    //! Get a minor frame
    CFMT_HdwMilStd1553MinorFrame*	Get(t_FMT_Uint32 uiIdx);

    //! Return the total number of minor frames
    t_FMT_Uint32					GetSize() const;

};



#endif







