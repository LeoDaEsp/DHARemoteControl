// =====================================================================================
/**
 * @file					FMT_HdwHoeDevice.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					09/05/2025
 * @brief					Abstract Configurable HOE Device
 *
 * @version	Project:		Formatech C++ Hardware Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][09/05/2025]
 */
// =====================================================================================



#ifndef FMTDEF_HDW_HOEDDEVICE_H
#define FMTDEF_HDW_HOEDDEVICE_H

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
#include "FMT_HdwHoeDevice.h"
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
//	Class CFMT_HdwHoeDevice
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_HdwHoeDevice : public CFMT_HdwDevice, public CFMT_HdwHoe
{
    // =====================================================================================
    //	TYPES
    // =====================================================================================

protected:
public:

	// --- CWaitPacketEvent ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CWaitPacketEvent : public CFMT_Object
	{
		public:

		t_FMT_Bool			m_bWaiting;
        t_FMT_Uint32		m_uiPackId;
		t_FMT_Uint32		m_uiPackNum;
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


	// --- CIpConfigList ----------------------------------------

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



	// --- t_EventType ----------------------------------------

	enum t_EventType
	{
		e_EventType_Hoe				= 0,
		e_EventType_CriticalFail	= 1,

		e_EventType_Total			= 2,

		e_EventType_Undefined		= 255
	};


	// --- CHoeEvent ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CHoeEvent : public CFMT_HdwEvent
	{
	public:

		t_HoePacket*		m_pPacket;

		CHoeEvent();
	};


	// --- CTxNomEvent ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CTxNomEvent : public CFMT_HdwEvent
	{
	public:
		t_FMT_Uint32		m_uiNom;

		CTxNomEvent();
		//virtual t_FMT_Uint32	ExtractData(t_FMT_Uint8* pucBuf, t_FMT_Uint32 uiSize);
	};



    // --- CDeviceInstance --------------------------------------------------

    class FMTDEF_LIB_DLLSPEC CDeviceInstance : public CFMT_HdwDevice::CDeviceInstance
    {
    public:

		CFMT_String					m_sFullName;											// Full device name
		CFMT_HdwObject*				m_pManager;												// The hardware manager
		CFMT_HdwHoe*				m_pHoe;													// HOE interface
		t_FMT_Uint32				m_uiSourceId;											// Source Identifier
		CIpConfig					m_ServerIpConfig;										// Server IP Configuration
		CFMT_HdwUdpSocket*			m_pServerSocket;										// Server Socket
		FMTDEF_HDW_HOE_THREAD		m_RxServerThread;										// Server RX Thread
		t_FMT_Bool					m_bServerRxThreadRun;									// Server RX Thread Running Flag
		volatile t_FMT_Bool			m_bServerRxThreadExit;									// Server RX Thread Stop Command
		t_HoePacket*				m_pServerRxPacket;										// Server HOE RX Packet
		CFMT_Mutex					m_ServerRxMutex;										// Server HOE RX Mutex
		CWaitPacketEventList		m_ServerWaitPacketEventList;							// Server Waiting HOE Event List
		CPortInfoList				m_PortInfoList;											// Port Info
		t_FMT_Uint32				m_uiSN;													// Serial Number
		t_FMT_Uint16				m_usHardwareVersion;									// Hardware Version
		t_FMT_Uint16				m_usFirmwareVersion;									// Firmware Version
		t_FMT_Uint32				m_puiTotPortsPerType[CFMT_HdwPort::e_PortType_Total];	// Total ports per port type

		CFMT_Mutex					m_PknMutex;												// Packet Number Mutex
		t_FMT_Uint32				m_uiPkn;												// Last Packet Number


        CDeviceInstance();
        virtual ~CDeviceInstance();

		t_FMT_Uint32				NextPkn();

		t_FMT_Uint32				CreateServerLink();
		virtual t_FMT_Bool			MatchServerAdd(CFMT_IpAddress& SrcAdd);
		virtual t_FMT_Uint32		ServerRxProc();
		t_FMT_Uint32				Detect();
		virtual void				UpdateFullName();
		CFMT_HdwPort*				GetHoePort(t_HoePacket* pPacket);
		virtual t_FMT_Uint32		ProcessServerRxPacket(CFMT_IpAddress& SrcAdd, t_FMT_Uint16 usSrcPort);
		virtual t_FMT_Uint32		ProcessServerHoePacket(t_FMT_Uint16 usSrcPort, t_HoePacket* pPacket);
		virtual t_FMT_Uint32		ProcessPortKeepAliveReception(t_HoePacket* pPacket);
		virtual t_FMT_Uint32		ProcessPortReception(t_HoePacket* pPacket);

		// Send a HOE packet
		virtual t_FMT_Uint32		SendPacket(CFMT_HdwUdpSocket* pSocket, CIpConfig& IpConfig, t_HoePacket& pck);

		virtual t_FMT_Uint32		Connect();
		virtual t_FMT_Uint32		Disconnect();

		virtual t_FMT_Uint32		OpenPort(CFMT_HdwPort* pPort, CFMT_HdwPort::CParameters* pParameters);
		virtual t_FMT_Uint32		ClosePort(CFMT_HdwPort* pPort);
		
		virtual void				GetOpenPortPayload(CFMT_HdwPort* pPort, CFMT_HdwPort::CParameters* pParameters, t_HoePacket& Pck);

		virtual void				PerformCyclicOperation();
		virtual void				CheckPortLink(CFMT_HdwPort* pPort);


		virtual void				SendLinkKeepAlive(CFMT_HdwPort* pPort);
		virtual void				SendDataBuf(CFMT_HdwPort* pPort, t_FMT_Uint8* pucBuf, t_FMT_Uint32 uiLen, t_FMT_Uint32 uiPckNum);
		virtual t_FMT_Uint32		SendRstTx(CFMT_HdwPort* pPort, t_FMT_Uint32 uiRetries = FMTDEF_HDW_HOE_CMD_RETRIES);
		virtual t_FMT_Uint32		SendRstRx(CFMT_HdwPort* pPort, t_FMT_Uint32 uiRetries = FMTDEF_HDW_HOE_CMD_RETRIES);
		virtual t_FMT_Uint32		SendConfig(CFMT_HdwPort* pPort, t_FMT_Uint8* pucBuf, t_FMT_Uint32 uiLen, t_FMT_Uint32 uiRetries = FMTDEF_HDW_HOE_CMD_RETRIES);
		virtual t_FMT_Uint32		SendCctx(CFMT_HdwPort* pPort, t_FMT_Uint8* pucBuf, t_FMT_Uint32 uiLen, t_FMT_Uint32 uiRetries = FMTDEF_HDW_HOE_CMD_RETRIES);
		virtual t_FMT_Uint32		SendDctx(CFMT_HdwPort* pPort, t_FMT_Uint8* pucBuf, t_FMT_Uint32 uiLen, t_FMT_Uint32 uiRetries = FMTDEF_HDW_HOE_CMD_RETRIES);

        #ifdef FMTDEF_COMPILE_OS_WINDOWS
		static	DWORD WINAPI		ServerRxThreadFunction(LPVOID lpParam);
        #endif

        #ifdef FMTDEF_COMPILE_OS_LINUX
        static	void* ServerRxThreadFunction(void* lpParam);
        #endif
    };

	// --- CDeviceInstancePointerList ----------------------------------------
	class FMTDEF_LIB_DLLSPEC CDeviceInstancePointerList : public CFMT_List<CDeviceInstance*>
	{
	};


    // =====================================================================================
    //	VARIABLES
    // =====================================================================================

protected:

	// Broadcast Detection Mode Flag
	t_FMT_Bool					m_bBroadcastDetectFlag;

	// List of static IP address allowed for device
	CFMT_IpAddressList			m_IpAddressList;

	// Target Port
	t_FMT_Uint16				m_usServerPort;

	// Detect Timeout
	t_FMT_Uint32				m_uiDetectTimeoutMs;


public:

    // =====================================================================================
    // CONSTRUCTORS & DESTRUCTORS
    // =====================================================================================

public:

    CFMT_HdwHoeDevice();
    virtual ~CFMT_HdwHoeDevice();

    // =====================================================================================
    //	FUNCTIONS
    // =====================================================================================

protected:

	// Create a device instance
	virtual CFMT_HdwDevice::CDeviceInstance*	CreateDeviceInstance();

	// Create a port
	virtual CFMT_HdwPort*						CreatePort(t_FMT_Uint32 uiType, CFMT_HdwObject *pDevice, t_FMT_Uint32 uiDeviceId, const CFMT_String& sChannelId);

	// Send a HOE packet
	virtual t_FMT_Uint32						SendPacket(CFMT_HdwUdpSocket* pSocket, CIpConfig& IpConfig, t_HoePacket& pck);


	// Perform broadcast detection
	virtual t_FMT_Uint32						DetectBroadcast(const CFMT_IpAddress& IpAdd, CDeviceInstancePointerList& list, t_FMT_Uint32* puiTotPorts);

public:

	// Initialize the device
	virtual	t_FMT_Uint32						Init(t_FMT_Uint32 uiTotalPortTypes = CFMT_HdwPort::e_PortType_Total);

	// Add a static IP configuration
	virtual t_FMT_Uint32						AddStaticIpConfig(const CFMT_IpAddress& IpAdd);

	// Remove a static IP configuration
	virtual t_FMT_Uint32						RemoveStaticIpConfig(const CFMT_IpAddress& IpAdd);

	// Remove all static IP configurations
	virtual t_FMT_Uint32						RemoveAllStaticIpConfig();

	// Open the device
	virtual t_FMT_Uint32						Open(t_FMT_Uint32 uiDeviceId);

	// Close the device
	virtual t_FMT_Uint32						Close(t_FMT_Uint32 uiDeviceId);

	// Perform actions after opening
	virtual t_FMT_Uint32						OnOpening(t_FMT_Uint32 uiDeviceId);

	// Perform actions before closing
	virtual t_FMT_Uint32						OnClosing(t_FMT_Uint32 uiDeviceId);

	// Hardware timer handlers after service timer handlers
	virtual t_FMT_Uint32						HdwTimerEndDeviceIntanceHandler(t_FMT_Uint32 uiDeviceId, t_FMT_Uint64 quiTimerCnt);

	// Get port refresh time
	static t_FMT_Uint64							GetRefreshTime(t_FMT_Uint64 quiTimeout);

	// Dump a HOE TX/RX packet
	virtual t_FMT_Uint32						DumpPacket(CFMT_IpAddress& IpAdd, t_FMT_Uint16 usPort, t_HoePacket* pPacket, t_FMT_Bool bTx);

};



#endif







