// =====================================================================================
/**
 * @file					FMT_HdwArinc429RxPort.h
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



#ifndef FMTDEF_HDW_ARINC429RXPORT_H
#define FMTDEF_HDW_ARINC429RXPORT_H

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

#ifndef FMTDEF_HDW_OBJECT_H
#include "FMT_HdwObject.h"
#endif

#ifndef FMTDEF_HDW_PORT_H
#include "FMT_HdwPort.h"
#endif


// =====================================================================================
//	DEFINES
// =====================================================================================

#define FMTDEF_HDW_ARINC429RXPORT_PORTNUM_INVALID		0


// *************************************************************************************
// *************************************************************************************
//	Class CFMT_HdwArinc429RxPort
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_HdwArinc429RxPort : public CFMT_HdwPort
{
// =====================================================================================
//	TYPES
// =====================================================================================

protected:
public:

    // --- t_Parity ------------------------------------------

    enum t_Parity
    {
        e_Parity_Odd			= 0,
        e_Parity_Even			= 1,
        e_Parity_NoParity		= 2
    };

    // --- t_BaudRate ----------------------------------------

    enum t_BaudRate
    {
        e_BaudRate_Low			= 12500,
        e_BaudRate_High			= 100000
    };

    // --- CParameters ----------------------------------------------------

    class FMTDEF_LIB_DLLSPEC CParameters : public CFMT_HdwPort::CParameters
    {
    public:

        t_FMT_Uint8		m_ucParity;
        t_FMT_Uint32	m_uiBaudRate;

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
    CFMT_HdwArinc429RxPort(CFMT_HdwObject *pDevice, t_FMT_Uint32 uiDeviceId, const CFMT_String& sChannelId);

    //! Destructor
    virtual ~CFMT_HdwArinc429RxPort();


// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:
public:

    virtual t_FMT_Uint32		Open(CFMT_HdwPort::CParameters *pParameters);
    virtual t_FMT_Uint32		Close();
    virtual t_FMT_Uint32		GetParameters(CParameters *pParameters);
    virtual t_FMT_Uint32		EnableService(t_FMT_Uint32 dwServiceType,CFMT_HdwService **ppService,CFMT_HdwService::CParameters *pParam);

    //! Dynamically set baud rate
    virtual t_FMT_Uint32		SetBaudRate(t_FMT_Uint32 uiBaudRate);
};



#endif







