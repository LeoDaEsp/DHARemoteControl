// =====================================================================================
/**
 * @file					FMT_HdwFtdiUartBridgedDevice.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					23/04/2022
 * @brief					Abstract Configurable HOE / FTDI UART Bridged Device
 *
 * @version	Project:		Formatech C++ Hardware Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][23/04/2022]
 */
// =====================================================================================



#ifndef FMTDEF_HDW_HOEFTDIUARTBRIDGEDDEVICE_H
#define FMTDEF_HDW_HOEFTDIUARTBRIDGEDDEVICE_H

// =====================================================================================
//	INCLUDES
// =====================================================================================


#ifdef FMTDEF_COMPILE_OS_WINDOWS

#ifdef UNICODE
    #define REDEF_UNICODE
    #undef UNICODE
#endif

#endif




#ifndef FMTDEF_CORE_H
#include "FMT_Core.h"
#endif

#ifndef FMTDEF_HDW_OBJECT_H
#include "FMT_HdwObject.h"
#endif

#ifndef FMTDEF_HDW_DEVICE_H
#include "FMT_HdwDevice.h"
#endif

#ifndef FMTDEF_HDW_UARTPORT_H
#include "FMT_HdwUartPort.h"
#endif

#ifndef FMTDEF_HDW_FTDIUARTBRIDGEDDEVICE_H
#include "FMT_HdwFtdiUartBridgedDevice.h"
#endif

#ifndef FMTDEF_HDW_UDPSOCKET_H
#include "FMT_HdwUdpSocket.h"
#endif

#ifndef FMTDEF_HDW_HOE_H
#include "FMT_HdwHoe.h"
#endif


#ifdef FMTDEF_COMPILE_OS_WINDOWS

#include "WinDef.h"
#include <objbase.h>
#include <initguid.h>
#include <Setupapi.h>

#endif


// =====================================================================================
//	DEFINES
// =====================================================================================




// *************************************************************************************
// *************************************************************************************
//	Class CFMT_HdwHoeFtdiUartBridgedDevice
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_HdwHoeFtdiUartBridgedDevice : public CFMT_HdwFtdiUartBridgedDevice, public CFMT_HdwHoe
{
    // =====================================================================================
    //	TYPES
    // =====================================================================================

protected:
public:

	// --- t_WorkingMode ------------------------------------

	enum t_WorkingMode
	{
		e_WorkingMode_Usb			= 0,
		e_WorkingMode_Ethernet		= 1
	};


	// --- CWaitPacketEvent ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CWaitPacketEvent : public CFMT_Object
	{
		public:

		t_FMT_Bool			m_bWaiting;
        t_FMT_Uint32		m_uiPackId;
		t_HoePacket			*m_pPacket;

		CWaitPacketEvent();

		t_FMT_Bool			operator==(const CWaitPacketEvent& op);
		t_FMT_Bool			operator!=(const CWaitPacketEvent& op);

	    FMTDEF_LIB_DLLSPEC friend CFMT_Buffer& operator<<(CFMT_Buffer& buf, CWaitPacketEvent& s);
	    FMTDEF_LIB_DLLSPEC friend CFMT_Buffer& operator>>(CFMT_Buffer& buf, CWaitPacketEvent& s);
	};

	// --- CWaitPacketEventList ----------------------------------------
	class FMTDEF_LIB_DLLSPEC CWaitPacketEventList : public CFMT_List<CWaitPacketEvent*>
	{
	};

	// --- CIpConfig ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CIpConfig : public CFMT_Object
	{
	public:

		CFMT_IpAddress			m_IpAddress;
		t_FMT_Uint16			m_usTargetPort;
		t_FMT_Uint16			m_usSourcePort;

		CIpConfig();

		t_FMT_Bool				operator==(const CIpConfig& op);
		t_FMT_Bool				operator!=(const CIpConfig& op);

	    FMTDEF_LIB_DLLSPEC friend CFMT_Buffer& operator<<(CFMT_Buffer& buf, CIpConfig& s);
	    FMTDEF_LIB_DLLSPEC friend CFMT_Buffer& operator>>(CFMT_Buffer& buf, CIpConfig& s);
	};


	// --- CStaticInstanceDescList ----------------------------------------
	class FMTDEF_LIB_DLLSPEC CIpConfigList : public CFMT_List<CIpConfig>
	{
	};


	// --- CPortInfo ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CPortInfo : public CFMT_Object
	{
	public:
        t_FMT_Uint16		m_usType;
        t_FMT_Uint16		m_usNum;
        t_FMT_Uint8			m_ucStatus;
        t_FMT_Uint32		m_uiFlags;

		CPortInfo();

		t_FMT_Bool				operator==(const CPortInfo& op);
		t_FMT_Bool				operator!=(const CPortInfo& op);

	    FMTDEF_LIB_DLLSPEC friend CFMT_Buffer& operator<<(CFMT_Buffer& buf, CPortInfo& s);
	    FMTDEF_LIB_DLLSPEC friend CFMT_Buffer& operator>>(CFMT_Buffer& buf, CPortInfo& s);
	};


	// --- CPortInfoList ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CPortInfoList : public CFMT_List<CPortInfo>
	{
	};


    // --- CDeviceInstance --------------------------------------------------

    class FMTDEF_LIB_DLLSPEC CDeviceInstance : public CFMT_HdwFtdiUartBridgedDevice::CDeviceInstance
    {
    public:

		t_WorkingMode				m_WorkingMode;				//! Working Mode
		CIpConfig					m_IpConfig;					//! IP Configuration
		CFMT_HdwUdpSocket			*m_pSocket;					//! Socket
	    CFMT_HdwObject				*m_pManager;				//! The hardware manager
		FMTDEF_HDW_HOE_THREAD		m_RxThread;					//! RX Thread
		t_FMT_Bool					m_bRxThreadRun;				//! RX Thread Running Flag
		t_FMT_Bool					m_bRxThreadExit;			//! RX Thread Stop Command
		t_HoePacket					*m_pRxPacket;				//! HOE RX Packet
		CFMT_HdwHoe					*m_pHoe;					//! HOE interface
		CWaitPacketEventList		m_HoeWaitPacketEventList;	//! Waiting HOE Event List
		CFMT_Mutex					m_HoeTxMutex;				//! HOE TX Mutex
		CFMT_Mutex					m_HoeRxMutex;				//! HOE RX Mutex
		t_FMT_Uint32				m_uiSN;						//! Serial Number
		t_FMT_Uint32				m_uiSourceId;				//! Source Identifier
		t_FMT_Uint16				m_usHardwareVersion;		//! Hardware Version
		t_FMT_Uint16				m_usFirmwareVersion;		//! Firmware Version
		CPortInfoList				m_PortInfoList;				//! Port Info
		CFMT_Mutex					m_EventBufferMutex;			//! Event Buffer Mutex
		CFMT_Uint8List				m_lsEventBuffer;			//! Event Buffer


        CDeviceInstance();
        virtual ~CDeviceInstance();

		t_FMT_Uint32				SendPacket(t_HoePacket &pck);
		t_FMT_Uint32				CreateEthernetLink();
		virtual t_FMT_Uint32		EthRxProc();
		virtual t_FMT_Uint32		EthProcessRxPacket();
		virtual t_FMT_Uint32		EthValidatePacket();
		t_FMT_Uint32				EthDetect();
		t_FMT_Uint32				EthConnect(t_HoePacket_Connect_Field& Params);
		t_FMT_Uint32				EthDisconnect();
		t_FMT_Uint32				EthSendCmd(t_FMT_Uint8 *pucBuf, t_FMT_Uint16 usSize);
		virtual t_FMT_Uint32		EthProcessHoePacket(t_HoePacket *pPacket);
		virtual t_FMT_Uint32		EthProcessHoeEventDataPacket(t_HoePacket *pPacket);

        #ifdef FMTDEF_COMPILE_OS_WINDOWS
		static	DWORD WINAPI		EthRxThreadFunction(LPVOID lpParam);
        #endif

        #ifdef FMTDEF_COMPILE_OS_LINUX
        static	void*               EthRxThreadFunction(void* lpParam);
        #endif
    };


protected:

    // =====================================================================================
    //	VARIABLES
    // =====================================================================================

protected:

	//! Enable the USB/UART Mode
	t_FMT_Bool					m_bEnableUsbMode;

	//! Enable the Ethernet Mode
	t_FMT_Bool					m_bEnableEthernetMode;

	//! List of static IP address allowed for device
	CFMT_IpAddressList			m_IpAddressList;

	//! Target Port
	t_FMT_Uint16				m_usTargetPort;


public:

    // =====================================================================================
    // CONSTRUCTORS & DESTRUCTORS
    // =====================================================================================

public:

    CFMT_HdwHoeFtdiUartBridgedDevice();
    virtual ~CFMT_HdwHoeFtdiUartBridgedDevice();

    // =====================================================================================
    //	FUNCTIONS
    // =====================================================================================

protected:


public:

	//! Enable/Disable USB/UART Mode
	virtual void				EnableUsbMode(t_FMT_Bool bEnable);

	//! Enable/Disable Ethernet Mode
	virtual void				EnableEthernetMode(t_FMT_Bool bEnable);

	//! Initialize the device
	virtual	t_FMT_Uint32		Init(t_FMT_Uint32 uiTotalPortTypes = CFMT_HdwPort::e_PortType_Total);

	//! Perform auto-bridging of device
	virtual t_FMT_Uint32		Autobridge(CPortDescriptorMatrix& DevPortDesc);

	//! Add a static IP configuration
	virtual t_FMT_Uint32		AddStaticIpConfig(const CFMT_IpAddress& IpAdd);

	//! Remove a static IP configuration
	virtual t_FMT_Uint32		RemoveStaticIpConfig(const CFMT_IpAddress& IpAdd);

	//! Remove all static IP configurations
	virtual t_FMT_Uint32		RemoveAllStaticIpConfig();

	//! Open the device
    virtual t_FMT_Uint32		Open(t_FMT_Uint32 uiDeviceId);

    //! Close the device
    virtual t_FMT_Uint32		Close(t_FMT_Uint32 uiDeviceId);


    //! Close the link of device instance
	t_FMT_Uint32				LinkClose(CDeviceInstance *pInst);
    t_FMT_Uint32				LinkClose(t_FMT_Uint32 uiDeviceId);

	//! Write bytes to the device
    t_FMT_Uint32				LinkWrite(CDeviceInstance *pInst, t_FMT_Uint8 *pucBuf, t_FMT_Uint32 uiSize);
    t_FMT_Uint32				LinkWrite(t_FMT_Uint32 uiDeviceId, t_FMT_Uint8 *pucBuf, t_FMT_Uint32 uiSize);

    //! Read bytes from the device
    t_FMT_Uint32				LinkRead(CDeviceInstance *pInst, t_FMT_Uint8 *pucBuf, t_FMT_Uint32 uiSize, t_FMT_Uint32& uiReadSize);
    t_FMT_Uint32				LinkRead(t_FMT_Uint32 uiDeviceId, t_FMT_Uint8 *pucBuf, t_FMT_Uint32 uiSize, t_FMT_Uint32& uiReadSize);

    //! Return the number of bytes stored into the read buffer
    t_FMT_Uint32				LinkGetReadBufferBytes(CDeviceInstance *pInst, t_FMT_Uint32& uiNob);
    t_FMT_Uint32				LinkGetReadBufferBytes(t_FMT_Uint32 uiDeviceId, t_FMT_Uint32& uiNob);
};



#endif







