// =====================================================================================
/**
 * @file					FMT_HdwDataGeneratorService.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					10/01/2020
 * @brief					Abstract Hardware Data Generator Service
 *
 * @version	Project:		Formatech C++ Hardware Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][10/01/2020]
 */
// =====================================================================================



#ifndef FMTDEF_HDW_DATAGENERATORSERVICE_H
#define FMTDEF_HDW_DATAGENERATORSERVICE_H

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

#ifndef FMTDEF_HDW_SERVICE_H
#include "FMT_HdwService.h"
#endif

// =====================================================================================
//	DEFINES
// =====================================================================================



// *************************************************************************************
// *************************************************************************************
//	Class CFMT_HdwDataGeneratorService
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_HdwDataGeneratorService : public CFMT_HdwService
{
// =====================================================================================
//	TYPES
// =====================================================================================

protected:
public:

    // --- t_GeneratorMode ----------------------------------------------------

    enum t_GeneratorMode
    {
        e_GeneratorMode_Counter			= 0,
        e_GeneratorMode_Shifter			= 1,
        e_GeneratorMode_Random			= 2
    };

    // --- CParameters ---------------------------------------------------------

    class FMTDEF_LIB_DLLSPEC CParameters : public CFMT_HdwService::CParameters
    {
    public:

        t_FMT_Uint32			m_uiStartBit;
        t_FMT_Uint32			m_uiNumberOfBits;
        t_GeneratorMode			m_GeneratorMode;

        CParameters();
    };


    // =====================================================================================
    //	VARIABLES
    // =====================================================================================

protected:

    t_FMT_Uint32			m_uiStartBit;
    t_FMT_Uint32			m_uiNumberOfBits;
    t_GeneratorMode			m_GeneratorMode;

public:


// =====================================================================================
// CONSTRUCTORS & DESTRUCTORS
// =====================================================================================

public:

    //! Empty constructor
    CFMT_HdwDataGeneratorService(CFMT_HdwObject *pPort);

    //! Destructor
    virtual ~CFMT_HdwDataGeneratorService();


// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:
public:

    //! Return the service parameters
    virtual t_FMT_Uint32		GetParameters(CParameters *pParameters);

    //! Set the service parameters
    virtual t_FMT_Uint32		SetParameters(CParameters *pParameters);

    //! Enable the data generator
    virtual t_FMT_Uint32		Enable();

    //! Disable the data generator
    virtual t_FMT_Uint32		Disable();

    //! Reset the data generator
    virtual t_FMT_Uint32		Reset();

};



#endif







