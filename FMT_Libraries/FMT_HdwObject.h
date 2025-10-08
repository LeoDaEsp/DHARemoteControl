// =====================================================================================
/**
 * @file					FMT_HdwObject.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					10/01/2020
 * @brief					Base hardware object
 *
 * @version	Project:		Formatech C++ Hardware Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][10/01/2020]
 */
// =====================================================================================



#ifndef FMTDEF_HDW_OBJECT_H
#define FMTDEF_HDW_OBJECT_H

// =====================================================================================
//	INCLUDES
// =====================================================================================


#ifndef FMTDEF_CORE_H
#include "FMT_Core.h"
#endif

#ifdef FMTDEF_COMPILE_OS_WINDOWS
#include <winsock2.h>
#include <windows.h>
#include <Mmsystem.h>
#include <objbase.h>
#include <initguid.h>
#include <math.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <Setupapi.h>
#endif


// =====================================================================================
//	DEFINES
// =====================================================================================

#ifndef IP_TTL
#define IP_TTL              4           /* set/get IP Time To Live          */
#endif

// *************************************************************************************
// *************************************************************************************
//	Class CFMT_HdwObject
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_HdwObject : public CFMT_Object
{
// =====================================================================================
//	TYPES
// =====================================================================================

protected:
public:

    //! Bus Type Enumerator
    enum t_BusType
    {
        e_BusType_Internal				= 0,
        e_BusType_Isa					= 1,
        e_BusType_Eisa					= 2,
        e_BusType_MicroChannel			= 3,
        e_BusType_TurboChannel			= 4,
        e_BusType_PCIBus				= 5,
        e_BusType_VMEBus				= 6,
        e_BusType_NuBus					= 7,
        e_BusType_PCMCIABus				= 8,
        e_BusType_CBus					= 9,
        e_BusType_MPIBus				= 10,
        e_BusType_MPSABus				= 11,
        e_BusType_ProcessorInternal		= 12,
        e_BusType_InternalPowerBus		= 13,
        e_BusType_PNPISABus				= 14,
        e_BusType_PNPBus				= 15,
        e_BusType_Vmcs					= 16,
        e_BusType_ACPIBus				= 17,
        e_BusType_MaximumInterfaceType	= 18,

        e_BusType_EthernetType			= 1000,
        e_BusType_USB                   = 1001,

        e_BusType_Unknown				= 0xFFFFFFFF,
    };


    // --- Discrete Type --------------------------------------------------

	enum t_DiscreteType
	{
		e_DiscreteType_OpenGnd		= 0,
		e_DiscreteType_SupplyOpen	= 1
	};



    // --- t_DiscreteStatus ----------------------------------------------------

	enum t_DiscreteStatus
	{
		e_DiscreteStatus_Open           = 0,
		e_DiscreteStatus_Gnd            = 1,
		e_DiscreteStatus_Supply         = 2,
		e_DiscreteStatus_Overcurrent    = 3,
		e_DiscreteStatus_Fail           = 4
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
    CFMT_HdwObject();

    //! Destructor
    virtual ~CFMT_HdwObject();


// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:
public:

    //! Return the bus type according to the value read by OS
    static t_FMT_Uint32		GetBusType(void* pvType);

    //! Return the bus type name
    static CFMT_String		GetBusName(t_FMT_Uint32 dwBusType);

};



#endif







