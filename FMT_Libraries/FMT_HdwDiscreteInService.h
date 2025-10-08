// =====================================================================================
/**
 * @file					FMT_HdwDiscreteInService.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					28/04/2022
 * @brief					Abstract Hardware Discrete Input Service
 *
 * @version	Project:		Formatech C++ Core Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][28/04/2022]
 */
// =====================================================================================



#ifndef FMTDEF_HDW_DISCRETEINSERVICE_H
#define FMTDEF_HDW_DISCRETEINSERVICE_H

// =====================================================================================
//	INCLUDES
// =====================================================================================


#ifndef FMTDEF_CORE_H
#include "FMT_Core.h"
#endif

#ifndef FMTDEF_HDW_SERVICE_H
#include "FMT_HdwService.h"
#endif

// =====================================================================================
//	DEFINES
// =====================================================================================



// *************************************************************************************
// *************************************************************************************
//	Class CFMT_HdwDiscreteInService
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_HdwDiscreteInService : public CFMT_HdwService
{
// =====================================================================================
//	TYPES
// =====================================================================================

protected:
public:

    // --- CParameters ---------------------------------------------------------

    class FMTDEF_LIB_DLLSPEC CParameters : public CFMT_HdwService::CParameters
    {
    public:

        CParameters();
    };



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
    CFMT_HdwDiscreteInService(CFMT_HdwObject *pPort);

    //! Destructor
    virtual ~CFMT_HdwDiscreteInService();


// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:
public:

    //! Return the service parameters
    virtual t_FMT_Uint32			GetParameters(CParameters *pParameters);

    //! Set the service parameters
    virtual t_FMT_Uint32			SetParameters(CParameters *pParameters);

	//! Get the status of a discrete input
    virtual t_FMT_Uint32			GetDinStatus(t_FMT_Uint32 uiIndex, t_DiscreteStatus& status);


};



#endif







