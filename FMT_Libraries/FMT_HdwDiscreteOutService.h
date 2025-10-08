// =====================================================================================
/**
 * @file					FMT_HdwDiscreteOutService.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					28/04/2022
 * @brief					Abstract Hardware Discrete Output Service
 *
 * @version	Project:		Formatech C++ Core Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][28/04/2022]
 */
// =====================================================================================



#ifndef FMTDEF_HDW_DISCRETEOUTSERVICE_H
#define FMTDEF_HDW_DISCRETEOUTSERVICE_H

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
//	Class CFMT_HdwDiscreteOutService
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_HdwDiscreteOutService : public CFMT_HdwService
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
    CFMT_HdwDiscreteOutService(CFMT_HdwObject *pPort);

    //! Destructor
    virtual ~CFMT_HdwDiscreteOutService();


// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:
public:

    //! Return the service parameters
    virtual t_FMT_Uint32		GetParameters(CParameters *pParameters);

    //! Set the service parameters
    virtual t_FMT_Uint32		SetParameters(CParameters *pParameters);

    //! Set a discrete output status
    virtual t_FMT_Uint32		SetDoutStatus(t_FMT_Uint32 uiIndex, t_DiscreteStatus status, t_FMT_Bool bImmediate = FMTDEF_FALSE);

    //! Get a discrete output status
    virtual t_FMT_Uint32		GetDoutStatus(t_FMT_Uint32 uiIndex, t_DiscreteStatus& status);
};



#endif







