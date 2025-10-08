// =====================================================================================
/**
 * @file					FMT_HdwMilStd1553Port.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					10/01/2020
 * @brief					Abstract Mil-Std-1553 Port
 *
 * @version	Project:		Formatech C++ Hardware Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][10/01/2020]
 */
// =====================================================================================



#ifndef FMTDEF_HDW_MILSTD1553PORT_H
#define FMTDEF_HDW_MILSTD1553PORT_H

// =====================================================================================
//	INCLUDES
// =====================================================================================


#ifndef FMTDEF_CORE_H
#include "FMT_Core.h"
#endif

#ifndef FMTDEF_HDW_OBJECT_H
#include "FMT_HdwObject.h"
#endif

#ifndef FMTDEF_HDW_PORT_H
#include "FMT_HdwPort.h"
#endif


// =====================================================================================
//	DEFINES
// =====================================================================================

#define FMTDEF_HDW_MILSTD1553PORT_PORTNUM_INVALID		0


// *************************************************************************************
// *************************************************************************************
//	Class CFMT_HdwMilStd1553Port
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_HdwMilStd1553Port : public CFMT_HdwPort
{
// =====================================================================================
//	TYPES
// =====================================================================================

protected:
public:

    // --- CParameters ----------------------------------------------------

    class FMTDEF_LIB_DLLSPEC CParameters : public CFMT_HdwPort::CParameters
    {
    public:

        CParameters();
    };

    // =====================================================================================
    //	VARIABLES
    // =====================================================================================

protected:

    CParameters					m_Parameters;

public:

// =====================================================================================
// CONSTRUCTORS & DESTRUCTORS
// =====================================================================================

public:

    //! Empty constructor
    CFMT_HdwMilStd1553Port(CFMT_HdwObject *pDevice, t_FMT_Uint32 uiDeviceId, const CFMT_String& sChannelId);

    //! Destructor
    virtual ~CFMT_HdwMilStd1553Port();


// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:
public:

    virtual t_FMT_Uint32		Open(CFMT_HdwPort::CParameters *pParameters);
    virtual t_FMT_Uint32		Close();
    virtual t_FMT_Uint32		GetParameters(CParameters *pParameters);
    virtual t_FMT_Uint32		EnableService(t_FMT_Uint32 dwServiceType, CFMT_HdwService **ppService, CFMT_HdwService::CParameters *pParam);

};



#endif







