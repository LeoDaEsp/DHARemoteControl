// =====================================================================================
/**
 * @file					FMT_HdwPort.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					10/01/2020
 * @brief					Abstract Hardware Port
 *
 * @version	Project:		Formatech C++ Hardware Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][10/01/2020]
 */
// =====================================================================================



#ifndef FMTDEF_HDW_PORT_H
#define FMTDEF_HDW_PORT_H

// =====================================================================================
//	INCLUDES
// =====================================================================================


#ifndef FMTDEF_CORE_H
#include "FMT_Core.h"
#endif

#ifndef FMTDEF_HDW_OBJECT_H
#include "FMT_HdwObject.h"
#endif

#ifndef FMTDEF_HDW_SERVICE_H
#include "FMT_HdwService.h"
#endif

#ifndef FMTDEF_HDW_EVENT_H
#include "FMT_HdwEvent.h"
#endif


// =====================================================================================
//	DEFINES
// =====================================================================================



// *************************************************************************************
// *************************************************************************************
//	Class CFMT_HdwPort
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_HdwPort : public CFMT_HdwObject
{
// =====================================================================================
//	TYPES
// =====================================================================================

protected:
public:

    // --- t_PortType -----------------------------------------------------

    enum t_PortType
    {
        e_PortType_Undefined			= 0,
        e_PortType_Uart					= 1,
        e_PortType_Arinc429Tx			= 2,
        e_PortType_Arinc429Rx			= 3,
        e_PortType_Can					= 4,
        e_PortType_Spi					= 5,
        e_PortType_MilStd1553			= 6,
        e_PortType_I2C					= 7,
        e_PortType_DiscreteSet			= 8,
        e_PortType_Total				= 9
    };

    // --- CServiceList -----------------------------------------------------

    class FMTDEF_LIB_DLLSPEC CServiceList : public CFMT_List<CFMT_HdwService*>
    {
	};

    // --- CParameters -----------------------------------------------------

    class FMTDEF_LIB_DLLSPEC CParameters : public CFMT_Object
    {
    public:

        t_FMT_Uint32            m_uiPortNum;                    // Port Number
        t_FMT_Uint64		    m_quiLinkTimeout;				// Link timeout

        CParameters();
    };


    // =====================================================================================
    //	VARIABLES
    // =====================================================================================

protected:

    t_FMT_Uint32				m_uiPortType;           // Port Type
    t_FMT_Bool					m_bIsOpen;              // Open Flag
    CFMT_HdwObject				*m_pDevice;             // Parent Device
    t_FMT_Uint32				m_uiDeviceId;           // Parent Device ID
    CFMT_String                 m_sChannelId;           // Parent Device Relative Port Number
    t_FMT_Uint32				m_uiPortNum;            // Parent Device Absolute Port Number
    CServiceList				m_ServiceList;          // Associated Services

public:

    t_FMT_Uint32				m_uiLinkId;             // Link identifier
    t_FMT_Uint64                m_quiLinkTimeout;       // Link Timeout
    t_FMT_Uint64                m_quiLastLinkRxTime;    // Last Link Reception Time
    t_FMT_Uint64                m_quiLastLinkTxTime;    // Last Link Reception Time


// =====================================================================================
// CONSTRUCTORS & DESTRUCTORS
// =====================================================================================

public:

    //! Unique constructor
    CFMT_HdwPort(CFMT_HdwObject *pDevice, t_FMT_Uint32 uiDeviceId, const CFMT_String& sChannelId);

    //! Destructor
    virtual ~CFMT_HdwPort();


// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:
public:

protected:

    //! Attach hardware timer to port
    t_FMT_Uint32				AttachHdwTimerToPort();

    //! Detach hardware timer from port
    t_FMT_Uint32				DetachHdwTimerFromPort();

public:

    //! Return the port type
    t_FMT_Uint32				GetPortType() const;

    //! Return the port number
    t_FMT_Uint32				GetPortNum() const;

    //! Return the device where the port is installed
    CFMT_HdwObject*				GetDevice();

    //! Return the device ID where the port is installed
    t_FMT_Uint32				GetDeviceId() const;

    //! Return the channel ID where the port is installed
    CFMT_String                 GetChannelId() const;

    //! Return if the port is open
    t_FMT_Bool					IsOpen() const;

    //! Open the port
    virtual t_FMT_Uint32		Open(CFMT_HdwPort::CParameters *pParameters);

    //!	Perform dedicated opening actions, after device instance opening and before starting services
    virtual t_FMT_Uint32		OnOpening(CFMT_HdwPort::CParameters *pParameters);

    //! Close the port
    virtual t_FMT_Uint32		Close();

    //! Enable a service on the port
    virtual t_FMT_Uint32		EnableService(t_FMT_Uint32 dwServiceType, CFMT_HdwService **ppService , CFMT_HdwService::CParameters *pParam = FMTDEF_NULL);

    //! Disable a service on the port
    virtual t_FMT_Uint32		DisableService(CFMT_HdwService *pService);

    //! Disable all port services
    virtual t_FMT_Uint32		DisableAllServices();

    //! Abort all port services
    virtual t_FMT_Uint32		AbortAllServices();

    //! Return the port parameters
    virtual t_FMT_Uint32		GetParameters(CParameters *pParameters);

    //! Hardware Timer handler
    virtual t_FMT_Uint32		HdwTimerHandler(t_FMT_Uint64 quiTimerCnt);

    //! Process a hardware event
    virtual t_FMT_Uint32		ProcessEvent(CFMT_HdwEvent *pEvent);

    //! Lock the device when port is open
    void						DeviceLock();

    //! Unlock the device when port is running
    void						DeviceUnlock();
};




#endif







