// =====================================================================================
/**
 * @file					FMT_HdwCanPort.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					10/01/2020
 * @brief					Abstract Can Port
 *
 * @version	Project:		Formatech C++ Hardware Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][10/01/2020]
 */
// =====================================================================================



#ifndef FMTDEF_HDW_CANPORT_H
#define FMTDEF_HDW_CANPORT_H

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

#define FMTDEF_HDW_CANPORT_PORTNUM_INVALID		0


// *************************************************************************************
// *************************************************************************************
//	Class CFMT_HdwCanPort
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_HdwCanPort : public CFMT_HdwPort
{
// =====================================================================================
//	TYPES
// =====================================================================================

protected:
public:

    // --- t_Mode ----------------------------------------------------------

    enum t_Mode
    {
        e_Mode_Normal           = 0,
        e_Mode_ListenOnly       = 1,
        e_Mode_Loopback         = 2
    };


    // --- CParameters ----------------------------------------------------

    class FMTDEF_LIB_DLLSPEC CParameters : public CFMT_HdwPort::CParameters
    {
    public:

        t_Mode          m_Mode;
        t_FMT_Uint32	m_uiBitRate;
        t_FMT_Double    m_dSamplePoint;
        t_FMT_Uint8		m_ucSjw;
        t_FMT_Bool		m_bSam;

        CParameters();
    };


    // --- t_BusStatus ----------------------------------------------------

    enum t_BusStatus
    {
        e_BusStatus_BusOff			= 0,
        e_BusStatus_ErrorPassive	= 1,
        e_BusStatus_ErrorWarning	= 2,
        e_BusStatus_ErrorActive		= 3
    };

    // --- CFaultStatus ----------------------------------------------------

    class FMTDEF_LIB_DLLSPEC CFaultStatus : public CFMT_Object
    {
    public:

        t_FMT_Uint32	m_uiBusStatus;
        t_FMT_Uint8		m_ucTxErrorCounter;
        t_FMT_Uint8		m_ucRxErrorCounter;

        CFaultStatus();
        t_FMT_Bool		operator==(const CFaultStatus& op);
        t_FMT_Bool		operator!=(const CFaultStatus& op);

    };

    // =====================================================================================
    //	VARIABLES
    // =====================================================================================

protected:

    CFaultStatus				m_FaultStatus;
    CParameters					m_Parameters;

public:

// =====================================================================================
// CONSTRUCTORS & DESTRUCTORS
// =====================================================================================

public:

    //! Empty constructor
    CFMT_HdwCanPort(CFMT_HdwObject *pDevice, t_FMT_Uint32 uiDeviceId, const CFMT_String& sChannelId);

    //! Destructor
    virtual ~CFMT_HdwCanPort();


// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:
public:

    //! Open the port
    virtual t_FMT_Uint32		Open(CFMT_HdwPort::CParameters *pParameters);

    //! Close the port
    virtual t_FMT_Uint32		Close();

    //! Return the port parameters
    virtual t_FMT_Uint32		GetParameters(CParameters *pParameters);

    //! Enable a service on the port
    virtual t_FMT_Uint32		EnableService(t_FMT_Uint32 dwServiceType,CFMT_HdwService **ppService,CFMT_HdwService::CParameters *pParam);

    //! Return the status related to fault confinement of the port
    virtual t_FMT_Uint32		GetFaultStatus(CFaultStatus *pStatus);

};



#endif







