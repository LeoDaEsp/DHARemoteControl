// =====================================================================================
/**
 * @file					FMT_HdwFmtHoeDevice.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					06/11/2021
 * @brief					Formatech Hardware-On_Ethernet Base Device
 *
 * @version	Project:		Formatech C++ Hardware Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][06/11/2021]
 */
// =====================================================================================


#ifndef FMTDEF_HDW_FMTHOEDEVICE_H
#define FMTDEF_HDW_FMTHOEDEVICE_H

// =====================================================================================
//	INCLUDES
// =====================================================================================


#ifndef FMTDEF_CORE_H
#include "FMT_Core.h"
#endif

#ifndef FMTDEF_HDW_OBJECT_H
#include "FMT_HdwObject.h"
#endif

#ifndef FMTDEF_HDW_TIMER_H
#include "FMT_HdwTimer.h"
#endif

#ifndef FMTDEF_HDW_EVENT_H
#include "FMT_HdwEvent.h"
#endif

#ifndef FMTDEF_HDW_DEVICE_H
#include "FMT_HdwDevice.h"
#endif

#ifndef FMTDEF_HDW_MANAGER_H
#include "FMT_HdwManager.h"
#endif

#ifndef FMTDEF_HDW_SIGNALSERVICE_H
#include "FMT_HdwSignalService.h"
#endif

#ifndef FMTDEF_HDW_UDPSOCKET_H
#include "FMT_HdwUdpSocket.h"
#endif


// =====================================================================================
//	DEFINES
// =====================================================================================

#ifdef FMTDEF_COMPILE_OS_WINDOWS
#define FMTDEF_HDW_HOE_THREAD			(HANDLE)
#define FMTDEF_HDW_HOE_RXTHREAD_SIZE	(0)
#endif


#define FMTDEF_HDW_HOE_MAX_PAYLOAD_BYTES		1348

#define FMTDEF_HDW_HOE_PROT_ID					0xFE0000A1
#define FMTDEF_HDW_HOE_PROT_VER					0x0001

#define FMTDEF_HDW_HOE_PCKID_DETECT				0xB0000001
#define FMTDEF_HDW_HOE_PCKID_INFO				0xB0000002
#define FMTDEF_HDW_HOE_PCKID_KEEP_ALIVE			0xB0000003
#define FMTDEF_HDW_HOE_PCKID_CRITICAL_ERROR		0xB0000004

#define FMTDEF_HDW_HOE_PCKID_UART_OPEN_CMD		0xD0000001
#define FMTDEF_HDW_HOE_PCKID_UART_OPEN_ANS		0xD0000002
#define FMTDEF_HDW_HOE_PCKID_UART_CLOSE_CMD		0xD0000003
#define FMTDEF_HDW_HOE_PCKID_UART_CLOSE_ANS		0xD0000004
#define FMTDEF_HDW_HOE_PCKID_UART_STATUS		0xD0000005
#define FMTDEF_HDW_HOE_PCKID_UART_WRITE			0xD0000006


#define FMTDEF_HDW_HOE_PCK_HDR_LEN				52

#define FMTDEF_HOE_RESPONSE_TIMEOUT				150

#define FMTDEF_HDW_HOE_TX_RETRIES				5
#define FMTDEF_HDW_HOE_TX_RETRY_TIME			5


// *************************************************************************************
// *************************************************************************************
//	Class CFMT_HdwFmtHoeDevice
// *************************************************************************************
// *************************************************************************************


class FMTDEF_LIB_DLLSPEC CFMT_HdwFmtHoeDevice : public CFMT_HdwDevice
{
	// =====================================================================================
	//	TYPES
	// =====================================================================================

protected:

	// ---[ t_HoePacket ]--------------------------------------------------

    #pragma pack(push,1)
	typedef struct t_HoePacket_Field_Struct
	{
        t_FMT_Uint32		m_uiProtId;
        t_FMT_Uint16		m_usProtVer;
        t_FMT_Uint32		m_uiDevId;
        t_FMT_Uint32		m_uiDevSn;
        t_FMT_Uint32		m_uiDevPkn;
        t_FMT_Uint32		m_uiLinkId;
        t_FMT_Uint16		m_usPortId;
        t_FMT_Uint16		m_usPortNum;
        t_FMT_Uint32		m_uiPackId;
        t_FMT_Uint16		m_usPackLen;
		t_FMT_Uint8			m_pucExtHdr[16];
        t_FMT_Uint16		m_usStatus;
        t_FMT_Uint16		m_usPckCrc;
		t_FMT_Uint8			m_pucPayData[FMTDEF_HDW_HOE_MAX_PAYLOAD_BYTES];

	} t_HoePacket_Field;
    #pragma pack(pop)

    #pragma pack(push,1)
	typedef union t_HoePacket_Union
	{
        t_HoePacket_Field		m_Fields;
		t_FMT_Uint8				m_pucBytes[sizeof(t_HoePacket_Field)];

	} t_HoePacket;
    #pragma pack(pop)


	// --- CWaitPacketEvent ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CWaitPacketEvent : public CFMT_Object
	{
		public:
		t_FMT_Bool			m_bWaiting;
        t_FMT_Uint32		m_uiPackId;
		t_HoePacket			*m_pPacket;

		CWaitPacketEvent();

		t_FMT_Bool				operator==(const CWaitPacketEvent& op);
		t_FMT_Bool				operator!=(const CWaitPacketEvent& op);

	    FMTDEF_LIB_DLLSPEC friend CFMT_Buffer& operator<<(CFMT_Buffer& buf, CWaitPacketEvent& s);
	    FMTDEF_LIB_DLLSPEC friend CFMT_Buffer& operator>>(CFMT_Buffer& buf, CWaitPacketEvent& s);
	};


	// --- t_PortStatus ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CPortInfo : public CFMT_Object
	{
	public:
        t_FMT_Uint16		m_usType;
        t_FMT_Uint16		m_usNum;
        t_FMT_Uint8			m_ucStatus;
        t_FMT_Uint64		m_quiFlags;

		CPortInfo();

		t_FMT_Bool				operator==(const CPortInfo& op);
		t_FMT_Bool				operator!=(const CPortInfo& op);

	    FMTDEF_LIB_DLLSPEC friend CFMT_Buffer& operator<<(CFMT_Buffer& buf, CPortInfo& s);
	    FMTDEF_LIB_DLLSPEC friend CFMT_Buffer& operator>>(CFMT_Buffer& buf, CPortInfo& s);
	};


	// --- CDeviceInstance ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CInstanceIpConfig : public CFMT_Object
	{
	public:

		CFMT_IpAddress			m_IpAddress;
		t_FMT_Uint16			m_usTxPort;
		t_FMT_Uint16			m_usRxPort;

		CInstanceIpConfig();

		t_FMT_Bool				operator==(const CInstanceIpConfig& op);
		t_FMT_Bool				operator!=(const CInstanceIpConfig& op);

	    FMTDEF_LIB_DLLSPEC friend CFMT_Buffer& operator<<(CFMT_Buffer& buf, CInstanceIpConfig& s);
	    FMTDEF_LIB_DLLSPEC friend CFMT_Buffer& operator>>(CFMT_Buffer& buf, CInstanceIpConfig& s);
	};


	// --- CStaticInstanceDescList ----------------------------------------
	class FMTDEF_LIB_DLLSPEC CStaticInstanceDescList : public CFMT_List<CInstanceIpConfig>
	{
	};


	// --- CPortInfoList ----------------------------------------
	class FMTDEF_LIB_DLLSPEC CPortInfoList : public CFMT_List<CPortInfo>
	{
	};

	// --- CWaitPacketEventList ----------------------------------------
	class FMTDEF_LIB_DLLSPEC CWaitPacketEventList : public CFMT_List<CWaitPacketEvent*>
	{
	};


	// --- HOE Status --------------------------------------
	typedef enum t_HoeStatus_Enum
	{
		e_HoeStatus_OK                  = 0,
		e_HoeStatus_Busy                = 1,
		e_HoeStatus_HdwError            = 2,
		e_HoeStatus_InvalidParam        = 3,
		e_HoeStatus_ProtocolError       = 4,
		e_HoeStatus_Timeout             = 5

	} t_HoeStatus;


	// --- Event Type --------------------------------------
	typedef enum t_EventType_Enum
	{
		e_EventType_Undefined			= 0,
		e_EventType_RxPacket			= 1

	} t_EventType;


	// --- CRxEvent ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CRxEvent : public CFMT_HdwEvent
	{
	public:

		t_HoePacket		*m_pRxPacket;

		CRxEvent();
	};


public:

	// --- CDeviceInstance ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CDeviceInstance : public CFMT_HdwDevice::CDeviceInstance
	{
	public:

		CFMT_HdwFmtHoeDevice		*m_pHoeDev;
		CInstanceIpConfig			m_IpConfig;
		CFMT_String					m_sFullName;
		t_FMT_Uint32				m_uiSN;
		
		t_FMT_Uint16				m_usHdwVersion;

		CFMT_HdwUdpSocket			m_TxSocket;
		CFMT_HdwUdpSocket			m_RxSocket;
		t_HoePacket					*m_pRxPacket;

		FMTDEF_HDW_HOE_THREAD		m_RxThread;
		t_FMT_Bool					m_bRxThreadRun;
		t_FMT_Bool					m_bRxThreadExit;
		
		CWaitPacketEventList		m_WaitPacketEventList;
		CFMT_Mutex					m_TxMutex;
		CFMT_Mutex					m_RxMutex;
		CPortInfoList				m_PortInfoList;

		CDeviceInstance(const CInstanceIpConfig& IpConfig, CFMT_HdwFmtHoeDevice *pHoeDev);
		~CDeviceInstance();

		t_FMT_Uint32				SendPacket(t_HoePacket &pck);

		virtual t_FMT_Uint32		Connect();
		virtual t_FMT_Uint32		Detect();
		virtual t_FMT_Uint32		RxProc();
		virtual t_FMT_Uint32		ProcessRxPacket();
		virtual t_FMT_Uint32		ValidatePacket();

		#ifdef FMTDEF_COMPILE_OS_WINDOWS
		static	DWORD WINAPI RxThreadFunction(LPVOID lpParam);
		#endif
	};
	

	// =====================================================================================
	//	VARIABLES
	// =====================================================================================

protected:

	//! Device ID
	t_FMT_Uint32					m_uiHoeDeviceId;

	//! Static Instance Descriptors List
	CStaticInstanceDescList			m_StaticInstanceDescList;

	//! CRC Table
	static CFMT_Crc					s_Crc16;



public:

	// =====================================================================================
	// CONSTRUCTORS & DESTRUCTORS
	// =====================================================================================
	
	CFMT_HdwFmtHoeDevice();
	virtual ~CFMT_HdwFmtHoeDevice();

	// =====================================================================================
	//	FUNCTIONS
	// =====================================================================================

protected:

	//! Compute CRC packet
	static t_FMT_Uint16		ComputeCrc(t_HoePacket &pck);

	//! Build Detect packet
	void					BuildDetectPacket(t_HoePacket &pck);

	//! Build Base Keep Alive packet
	void					BuildBaseKeepAlivePacket(t_HoePacket &pck, t_FMT_Uint32 uiPortId, t_FMT_Uint32 uiChannelId);

	//! Build UART Open packet
	void					BuildBaseUartOpenPacket(t_HoePacket &pck, t_FMT_Uint32 uiChannelId, CFMT_HdwUartPort::CParameters &param);

	//! Build UART Close packet
	void					BuildBaseUartClosePacket(t_HoePacket &pck, t_FMT_Uint32 uiChannelId);

	//! Build UART Write packet
	void					BuildBaseUartWritePacket(t_HoePacket &pck, t_FMT_Uint32 uiChannelId);

	//! Check if the packet is a broadcast one
	static t_FMT_Bool		IsBroadcastPacket(t_FMT_Uint32 uiPacketId);

	//! Get Packet ID String (fo logging)
	static CFMT_String		GetPacketIdString(t_FMT_Uint32 uiPacketId);

	//! Dump HOE Packet
	static void				DumpPacket(t_HoePacket &pck, t_FMT_Bool bTX);


public:

    //! Open the device
    virtual t_FMT_Uint32	Open(t_FMT_Uint32 uiDeviceId);

    //! Close the device
    virtual t_FMT_Uint32	Close(t_FMT_Uint32 uiDeviceId);

    //! Perform actions after COM opening
    virtual t_FMT_Uint32	OnOpening(t_FMT_Uint32 uiDeviceId);

    //! Perform actions before COM closing
    virtual t_FMT_Uint32	OnClosing(t_FMT_Uint32 uiDeviceId);

	//! Add a static instance
	virtual t_FMT_Uint32	AddStaticInstance(const CFMT_IpAddress IpAdd, t_FMT_Uint16 usTxPort, t_FMT_Uint16 usRxPort);


};


#endif

