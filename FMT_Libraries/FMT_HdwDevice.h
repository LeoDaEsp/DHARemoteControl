// =====================================================================================
/**
 * @file					FMT_HdwDevice.h
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



#ifndef FMTDEF_HDW_DEVICE_H
#define FMTDEF_HDW_DEVICE_H

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



// *************************************************************************************
// *************************************************************************************
//	Class CFMT_HdwDevice
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_HdwDevice : public CFMT_HdwObject
{
// =====================================================================================
//	TYPES
// =====================================================================================

protected:
public:

    //! --- t_DeviceCode --------------------------------------------------

    enum t_DeviceCode
    {
        e_DeviceCode_StdUartDevice              = 0,
        e_DeviceCode_FmtUsb2Arinc429Device		= 1,
        e_DeviceCode_VectorCanCaseXLDevice		= 2,
        e_DeviceCode_FmtMulticommDevice			= 3,
        e_DeviceCode_FmtUsb2CanDevice			= 4,
        e_DeviceCode_FmtUsb2SsiDevice			= 5,
        e_DeviceCode_FmtMultiArinc429Device		= 6,
        e_DeviceCode_UdpEmulatorDevice			= 7,
		e_DeviceCode_FmtMulticommSmallDevice	= 8,
		e_DeviceCode_FmtNetAvioX96Device		= 9,
		e_DeviceCode_FmtNetArinc429x16Device	= 10,
        e_DeviceCode_FmtUsb2CanX2Device         = 11,
        e_DeviceCode_FmtUsb2Arinc429X2Device    = 12,
        e_DeviceCode_FmtNetUartX6Device         = 13,


		e_DeviceCode_FirstExternalDevice		= 10000
    };


    // --- CPortDescriptor --------------------------------------------------

    class FMTDEF_LIB_DLLSPEC CPortDescriptor : public CFMT_Object
    {
    public:

		CFMT_String         m_sChannel;
        CFMT_HdwPort		*m_pPort;
        CFMT_String			m_sManufacturer;
        CFMT_String			m_sFullName;
        t_FMT_Uint32		m_uiBusType;
        CFMT_String			m_sHardwareID;
        CFMT_String			m_sSN;
        CFMT_String			m_sRevision;
        t_FMT_Bool			m_bBridged;
        CFMT_String			m_sDescription;
        CFMT_String			m_sDevPath;

        CPortDescriptor();

	    t_FMT_Bool operator==(const CPortDescriptor& op)
		{
            FMTDEFM_UNUSED(op);
            return FMTDEF_FALSE;
		}
	    t_FMT_Bool operator!=(const CPortDescriptor& op)
		{
            FMTDEFM_UNUSED(op);
            return FMTDEF_FALSE;
		}

	    FMTDEF_LIB_DLLSPEC friend CFMT_Buffer& operator<<(CFMT_Buffer& buf, CPortDescriptor& s);
	    FMTDEF_LIB_DLLSPEC friend CFMT_Buffer& operator>>(CFMT_Buffer& buf, CPortDescriptor& s);
    };

    // --- CPortDescriptorsVector --------------------------------------------------

    class FMTDEF_LIB_DLLSPEC CPortDescriptorsVector : public CFMT_Vector<CPortDescriptor>
    {
    };

    // --- CPortDescriptorMatrix --------------------------------------------------

    class FMTDEF_LIB_DLLSPEC CPortDescriptorMatrix : public CFMT_Matrix<CPortDescriptorsVector*>
    {
    };

    // --- CPortList --------------------------------------------------

    class FMTDEF_LIB_DLLSPEC CPortList : public CFMT_List<CFMT_HdwPort*>
    {
    };

    // --- CDeviceInstance --------------------------------------------------

    class FMTDEF_LIB_DLLSPEC CDeviceInstance : public CFMT_Object
    {
    public:
        t_FMT_Bool			m_bOpen;
        CFMT_Mutex			*m_pMutex;
        CPortList			m_PortList;
        t_FMT_Uint32		m_uiType;
        CFMT_String         m_sRevision;
        CFMT_String         m_sSN;

        CDeviceInstance();
        ~CDeviceInstance();

        t_FMT_Bool              Lock();
        t_FMT_Bool              Unlock();
        virtual t_FMT_Uint32    OpenPort(CFMT_HdwPort* pPort, CFMT_HdwPort::CParameters* pParameters);
        virtual t_FMT_Uint32    ClosePort(CFMT_HdwPort* pPort);
    };

    // --- CDeviceList --------------------------------------------------

    class FMTDEF_LIB_DLLSPEC CDeviceList : public CFMT_Vector<CDeviceInstance*>
    {
    };

protected:

    // --- CPortDescriptorsList --------------------------------------------------

    class FMTDEF_LIB_DLLSPEC CPortDescriptorsList : public CFMT_List<CPortDescriptor>
    {
    };

    // --- CPortDescriptorsMatrix --------------------------------------------------

    class FMTDEF_LIB_DLLSPEC CPortDescriptorsMatrix : public CFMT_Vector<CPortDescriptorsVector>
    {
    };


    // =====================================================================================
    //	VARIABLES
    // =====================================================================================

protected:

	// Device Code
    t_FMT_Uint64					m_quiDeviceCode;

	// Device Port Descriptors
    CPortDescriptorsMatrix			m_PortDescriptors;      

	// Device Instances List
    CDeviceList						m_DeviceList;       

	// Device Full Installation Name
	CFMT_String						m_sFullInstallName;

	// Device Name
	CFMT_String						m_sName;

	// Manufacturer
	CFMT_String						m_sManufacturer;

	// Total Ports per devices
	t_FMT_Uint32					m_puiTotPortsPerType[CFMT_HdwPort::e_PortType_Total];
	
	// Link Timeout in ms (0 = no timeout check)
	t_FMT_Uint16					m_usLinkTimeout;

public:

    CFMT_HdwObject					*m_pManager;            //! The hardware manager

// =====================================================================================
// CONSTRUCTORS & DESTRUCTORS
// =====================================================================================

public:

    //! Empty constructor
    CFMT_HdwDevice();

    //! Destructor
    virtual ~CFMT_HdwDevice();


// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:

    //! Destroy all device ports
    t_FMT_Uint32			DestroyPorts();

    //! Destroy the device list
    void					DestroyDeviceList();

    //! Abort all services
    t_FMT_Uint32			AbortAllServices(t_FMT_Uint32 uiDeviceId);

public:

    //! Return the device code
    t_FMT_Uint64			GetDeviceCode() const;

    //! Return the port descriptors of a given type installed by device
    t_FMT_Uint32			GetPortDescriptor(t_FMT_Uint32 uiPortType, CPortDescriptorsVector **ppPortDescArray);

    //! Initialize the device.
    virtual	t_FMT_Uint32	Init(t_FMT_Uint32 dwTotalPortTypes = CFMT_HdwPort::e_PortType_Total);

    //! Perform auto-bridging of device
    virtual t_FMT_Uint32	Autobridge(CPortDescriptorMatrix& DevPortDesc);

    //! Run hardware management
    virtual	t_FMT_Uint32	Run();

    //! Stop the device management
    virtual	t_FMT_Uint32	Stop();

    //! Open the device
    virtual t_FMT_Uint32	Open(t_FMT_Uint32 uiDeviceId);

    //! Return FMTDEF_TRUE if the device instance can be closed
    t_FMT_Bool				CanClose(t_FMT_Uint32 uiDeviceId);

    //! Close the device
    virtual t_FMT_Uint32	Close(t_FMT_Uint32 uiDeviceId);

    //! Hardware Timer Handler
    virtual t_FMT_Uint32	HdwTimerHandler(t_FMT_Uint64 quiTimerCnt);

    //! Hardware timer handlers before service timer handlers
    virtual t_FMT_Uint32	HdwTimerStartDeviceIntanceHandler(t_FMT_Uint32 uiDeviceId, t_FMT_Uint64 quiTimerCnt);

    //! Hardware timer handlers after service timer handlers
    virtual t_FMT_Uint32	HdwTimerEndDeviceIntanceHandler(t_FMT_Uint32 uiDeviceId, t_FMT_Uint64 quiTimerCnt);

    //! Attach a port to hardware timer
    t_FMT_Uint32			AttachPortToHdwTimer(t_FMT_Uint32 uiDeviceId, CFMT_HdwPort* pPort);

    //! Detach a port from hardware timer
    t_FMT_Uint32			DetachPortFromHdwTimer(t_FMT_Uint32 uiDeviceId, CFMT_HdwPort* pPort);

    //! Lock the device
    void					DeviceLock(t_FMT_Uint32 uiDeviceId);

    //! Unlock the device
    void					DeviceUnlock(t_FMT_Uint32 uiDeviceId);

    //! Process the event handlers of a device instance
    t_FMT_Uint32			ProcessEventHandlers(t_FMT_Uint32 uiDeviceId,CFMT_HdwEvent* pEvent);

    //! Process the event handlers of a device instance and port
    t_FMT_Uint32			ProcessEventHandlers(t_FMT_Uint32 uiDeviceId,t_FMT_Uint32 uiPortType,CFMT_HdwEvent* pEvent);

    //! Return a the device instance
    CDeviceInstance*        GetDeviceInstance(t_FMT_Uint32 uiDeviceId);
	
	//! Set Link Timeout
	t_FMT_Uint32			SetLinkTimeout(t_FMT_Uint16 usTimeout);

};



#endif







