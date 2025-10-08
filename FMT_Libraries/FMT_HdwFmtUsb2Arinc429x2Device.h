// =====================================================================================
/**
 * @file					FMT_HdwFmtUsb2Arinc429x2Device.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					02/04/2025
 * @brief					Formatech USB to Arinc429 x2 Device
 *
 * @version	Project:		Formatech C++ Hardware Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][02/04/2025]
 */
// =====================================================================================


#ifndef FMTDEF_HDW_FMTUSB2ARINC429X2DEVICE_H
#define FMTDEF_HDW_FMTUSB2ARINC429X2DEVICE_H

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

#ifndef FMTDEF_HDW_FTDIUARTBRIDGEDDEVICE_H
#include "FMT_HdwFtdiUartBridgedDevice.h"
#endif

#ifndef FMTDEF_HDW_DATAGENERATORSERVICE_H
#include "FMT_HdwDataGeneratorService.h"
#endif

#ifndef FMTDEF_HDW_ARINC429MESSAGE_H
#include "FMT_HdwArinc429Message.h"
#endif

#ifndef FMTDEF_HDW_ARINC429RXPORT_H
#include "FMT_HdwArinc429RxPort.h"
#endif

#ifndef FMTDEF_HDW_ARINC429TXPORT_H
#include "FMT_HdwArinc429TxPort.h"
#endif

#ifndef FMTDEF_HDW_ARINC429INBUFFERSERVICE_H
#include "FMT_HdwArinc429InBufferService.h"
#endif

#ifndef FMTDEF_HDW_ARINC429OUTBUFFERSERVICE_H
#include "FMT_HdwArinc429OutBufferService.h"
#endif

#ifndef FMTDEF_HDW_ARINC429OUTLBLSERVICE_H
#include "FMT_HdwArinc429OutLbloService.h"
#endif

#ifndef FMTDEF_HDW_ARINC429INLBLSERVICE_H
#include "FMT_HdwArinc429InLbloService.h"
#endif

#ifndef FMTDEF_HDW_ARINC429BYTEINBUFFERSERVICE_H
#include "FMT_HdwArinc429ByteInBufferService.h"
#endif

#ifndef FMTDEF_HDW_ARINC429BYTEOUTBUFFERSERVICE_H
#include "FMT_HdwArinc429ByteOutBufferService.h"
#endif

#ifndef FMTDEF_HDW_SIGNALSERVICE_H
#include "FMT_HdwSignalService.h"
#endif

// =====================================================================================
//	DEFINES
// =====================================================================================



// *************************************************************************************
// *************************************************************************************
//	Class CFMT_HdwFmtUsb2Arinc429x2Device
// *************************************************************************************
// *************************************************************************************

#define FMTDEF_HDW_FMTUSB2ARINC429X2DEVICE_RXEVENTPAYLOAD_MAX		0x100000

class FMTDEF_LIB_DLLSPEC CFMT_HdwFmtUsb2Arinc429x2Device : public CFMT_HdwFtdiUartBridgedDevice
{
	// =====================================================================================
	//	TYPES
	// =====================================================================================

protected:

	// --- t_Command ----------------------------------------

	enum t_Command
	{
		e_Command_Invalid		= 0x00,
		e_Command_Session		= 0x01,
		e_Command_StatusRequest	= 0x02,

		e_Command_AtxCtxCtrl	= 0x10,
		e_Command_AtxCtxData	= 0x11,
		e_Command_AtxCtxReset	= 0x12,

		e_Command_AtxConfig1	= 0x14,
		e_Command_AtxConfig2	= 0x15,

		e_Command_ArxConfig1	= 0x18,
		e_Command_ArxConfig2	= 0x19,
	};

	// --- t_EventType ----------------------------------------

	enum t_EventType
	{
		e_EventType_ComEcho				= 0,
		e_EventType_CriticalFail		= 1,
		e_EventType_A429Rx				= 2,
		e_EventType_A429Tx				= 3,
		e_EventType_Status				= 4,

		e_EventType_Total				= 5,
		e_EventType_Undefined			= 255
	};

	// --- t_EventRate ----------------------------------------

	enum t_EventRate
	{
		e_EventRate_10ms		= 0
	};

	// --- t_RxState ----------------------------------------

	enum t_RxState
	{
		e_RxState_Start				= 0,
		e_RxState_SeqLow			= 1,
		e_RxState_SeqHigh			= 2,
		e_RxState_NdeLow			= 3,
		e_RxState_NdeHigh			= 4,
		e_RxState_EventLen			= 5,
		e_RxState_EventPayload		= 6,
		e_RxState_CrcLow			= 7,
		e_RxState_CrcHigh			= 8
	};

	// --- CCommand ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CCommand : public CFMT_Object
	{
	public:
		t_FMT_Uint8		m_ucType;
		t_FMT_Uint16	m_usCommandNumber;
		t_FMT_Bool		m_bEchoed;
		t_FMT_Uint32	m_uiTXB;
		t_FMT_Uint8		*m_pucTXBuf;

		CCommand();
		~CCommand();

		void Destroy();

	    t_FMT_Bool		operator==(const CCommand& op)
		{
            FMTDEFM_UNUSED(op);
            return FMTDEF_FALSE;
		}

	    t_FMT_Bool		operator!=(const CCommand& op)
		{
            FMTDEFM_UNUSED(op);
            return FMTDEF_FALSE;
		}

		FMTDEF_LIB_DLLSPEC friend CFMT_Buffer& operator<<(CFMT_Buffer& buf, CCommand& m);
		FMTDEF_LIB_DLLSPEC friend CFMT_Buffer& operator>>(CFMT_Buffer& buf, CCommand& m);

	};

	// --- CCommandList ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CCommandList : public CFMT_List<CCommand>
	{
	};

	// --- t_StatusRequestType ----------------------------------------

	enum t_StatusRequestType
	{
		e_StatusRequestType_Arinc429Tx		= 1
	};

	// --- t_StatusEventType ----------------------------------------

	enum t_StatusEventType
	{
		e_StatusEventType_Arinc429Tx		= 1
	};

	// --- CEventPosList ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CEventPosList : public CFMT_List<t_FMT_Uint32>
	{
	};

	// --- CEchoWaiting ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CEchoWaiting : public CFMT_Object
	{
	public:
		t_FMT_Uint16		m_usComNumber;
		t_FMT_Int32			m_uiSendTime;

		CEchoWaiting();

	    t_FMT_Bool		operator==(const CEchoWaiting& op)
		{
            FMTDEFM_UNUSED(op);
            return FMTDEF_FALSE;
		}

	    t_FMT_Bool		operator!=(const CEchoWaiting& op)
		{
            FMTDEFM_UNUSED(op);
            return FMTDEF_FALSE;
		}

		FMTDEF_LIB_DLLSPEC friend CFMT_Buffer& operator<<(CFMT_Buffer& buf, CEchoWaiting& m);
		FMTDEF_LIB_DLLSPEC friend CFMT_Buffer& operator>>(CFMT_Buffer& buf, CEchoWaiting& m);
	};

	// --- CCommandEchoList ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CCommandEchoList : public CFMT_List<CEchoWaiting>
	{
	};

	// --- CEvent ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CEvent : public CFMT_HdwEvent
	{
	public:
		//CCommand			*m_pCommand;

		CEvent();

		t_FMT_Uint32			ExtractTimeStamp(t_FMT_Uint8 *pucBuf);
		virtual t_FMT_Uint32	ExtractData(t_FMT_Uint8 *pucBuf, t_FMT_Uint32 uiSize);
	};


	// --- CArinc429RxEvent ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CArinc429RxEvent : public CEvent
	{
	public:
		CFMT_HdwArinc429Message		m_Arinc429Message;
		t_FMT_Uint32				m_uiIntergap;

		CArinc429RxEvent();
		virtual t_FMT_Uint32	ExtractData(t_FMT_Uint8 *pucBuf, t_FMT_Uint32 uiSize);
	};


	// --- CArinc429TxEvent ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CArinc429TxEvent : public CEvent
	{
	public:
		CFMT_HdwArinc429Message		m_Arinc429Message;

		CArinc429TxEvent();
		virtual t_FMT_Uint32	ExtractData(t_FMT_Uint8 *pucBuf, t_FMT_Uint32 uiSize);
	};


	// --- CStatusEvent ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CStatusEvent : public CEvent
	{
	public:
		t_FMT_Uint8			m_ucStatusType;
		t_FMT_Uint32		m_uiStatus;

		CStatusEvent();
		virtual t_FMT_Uint32	ExtractData(t_FMT_Uint8 *pucBuf, t_FMT_Uint32 uiSize);
	};

	// --- CComEchoEvent ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CComEchoEvent : public CEvent
	{
	public:
		t_FMT_Uint16		m_usComNumber;

		CComEchoEvent();

		virtual t_FMT_Uint32	ExtractData(t_FMT_Uint8 *pucBuf, t_FMT_Uint32 uiSize);
	};


	// --- t_TxMode ----------------------------------------

	enum t_TxMode
	{
		e_TxMode_Fifo			= 0,
		e_TxMode_Advanced		= 1
	};


	// --- t_Arinc429_TxMode ----------------------------------------

	enum t_Arinc429_TxMode
	{
		e_Arinc429_TxMode_Fifo		= 0,
		e_Arinc429_TxMode_Advanced	= 1
	};


	// --- t_Arinc429_TxDataGenMode ----------------------------------------

	enum t_Arinc429_TxDataGenMode
	{
		e_Arinc429_TxDataGenMode_Counter	= 0,
		e_Arinc429_TxDataGenMode_Shifter	= 1,
		e_Arinc429_TxDataGenMode_Random		= 2
	};

	// --- CArinc429TxCtrlStatus ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CArinc429TxCtrlStatus : public CFMT_Object
	{
	public:
		t_FMT_Bool		m_bEnable;
		t_FMT_Uint8		m_ucMode;
		t_FMT_Bool		m_bDataGenEnable;
		t_FMT_Bool		m_bDataGenReset;
		t_FMT_Uint8		m_ucDataGenStartBit;
		t_FMT_Uint8		m_ucDataGenNob;
		t_FMT_Uint8		m_ucDataGenMode;
		t_FMT_Bool		m_bTxEventEnable;
		t_FMT_Uint32	m_uiFifoNdw;
		t_FMT_Uint8		m_ucTotBits;

		CArinc429TxCtrlStatus();
	};

	// --- CArinc429RxCtrlStatus ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CArinc429RxCtrlStatus : public CFMT_Object
	{
	public:
		t_FMT_Bool		m_bEnable;

		CArinc429RxCtrlStatus();
	};


public:

	// --- CDeviceInstance ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CDeviceInstance : public CFMT_HdwFtdiUartBridgedDevice::CDeviceInstance
	{
	public:
		CCommandList			m_CommandList;
		t_FMT_Uint16			m_usCurCommandNumber;

		t_RxState				m_RxState;
		t_FMT_Uint8				*m_pucRxBuffer;
		t_FMT_Uint32			m_uiCurRxBufferPos;
		t_FMT_Uint32			m_uiRxCurSeq;
		t_FMT_Uint32			m_uiRxNde;
		t_FMT_Uint32			m_uiRxNdeCnt;
		t_FMT_Uint32			m_uiRxCurPayloadPos;
		t_FMT_Uint32			m_uiRxPayloadByte;
		t_FMT_Uint32			m_uiRxCurPayloadLen;
		t_FMT_Uint32			m_uiRxCrc;
		t_FMT_Uint8				m_pucRxEventPayload[FMTDEF_HDW_FMTUSB2ARINC429X2DEVICE_RXEVENTPAYLOAD_MAX];
		CEventPosList			m_RxEventPosList;
		t_FMT_Uint32			m_uiMaxRxBufferSize;

		CCommandEchoList		m_CommandEcholist;
		t_FMT_Uint32			m_uiCommandBufferNdw;

		CArinc429TxCtrlStatus	m_AtxCtrlStatus[8];
		CArinc429RxCtrlStatus	m_ArxCtrlStatus[8];

		CDeviceInstance();
		~CDeviceInstance();

		void ResetRxState();
		void Reset();
	};
	

	// --- CByteList ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CByteList : public CFMT_List<t_FMT_Uint8>
	{
	};


	// --- CArinc429TxPort ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CArinc429TxPort : public CFMT_HdwArinc429TxPort
	{
	protected:

	public:
		
		CArinc429TxPort(CFMT_HdwObject *pDevice, t_FMT_Uint32 uiDeviceId, const CFMT_String& sChannelId);

		virtual t_FMT_Uint32		EnableService(t_FMT_Uint32 dwServiceType, CFMT_HdwService **ppService, CFMT_HdwService::CParameters *pParam = FMTDEF_NULL);

		virtual t_FMT_Uint32		Open(CFMT_HdwPort::CParameters *pParameters);
		virtual t_FMT_Uint32		OnOpening(CFMT_HdwPort::CParameters *pParameters);
		virtual t_FMT_Uint32		Close();

	};

	// --- CArinc429RxPort ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CArinc429RxPort : public CFMT_HdwArinc429RxPort
	{
	protected:

	public:
		
		CArinc429RxPort(CFMT_HdwObject *pDevice, t_FMT_Uint32 uiDeviceId, const CFMT_String& sChannelId);

		virtual t_FMT_Uint32		EnableService(t_FMT_Uint32 dwServiceType, CFMT_HdwService **ppService, CFMT_HdwService::CParameters *pParam = FMTDEF_NULL);

		virtual t_FMT_Uint32		Open(CFMT_HdwPort::CParameters *pParameters);
		virtual t_FMT_Uint32		OnOpening(CFMT_HdwPort::CParameters *pParameters);
		virtual t_FMT_Uint32		Close();

	};

	// --- CArinc429OutBufferService ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CArinc429OutBufferService : public CFMT_HdwArinc429OutBufferService
	{
	protected:

		t_FMT_Bool					m_bStatusRequest;

		virtual t_FMT_Uint32		SendImmediate();

	public:
		
		CArinc429OutBufferService(CFMT_HdwObject *pPort);

		virtual t_FMT_Uint32		HdwTimerHandler(t_FMT_Uint64 quiTimerCnt);
		virtual t_FMT_Uint32		ProcessEvent(CFMT_HdwEvent* pEvent);

		virtual t_FMT_Uint32		Start();
		virtual t_FMT_Uint32		Stop();

		virtual t_FMT_Uint32		Write(CFMT_HdwArinc429Message *pMess, t_FMT_Uint32 uiSize, t_FMT_Bool bImmediate = FMTDEF_FALSE);
		virtual t_FMT_Uint32		ResetWriteBuffer();
		virtual t_FMT_Uint32		GetMessagesToBeWritten(t_FMT_Uint32& uiNom);

	};

	// --- CArinc429InBufferService ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CArinc429InBufferService : public CFMT_HdwArinc429InBufferService
	{
	protected:

		t_FMT_Bool					ApplyFilter(CFMT_HdwArinc429Message& mess, t_FMT_Uint16 *pusMessageFilter);

	public:
		
		CArinc429InBufferService(CFMT_HdwObject *pPort);

		virtual t_FMT_Uint32		ProcessEvent(CFMT_HdwEvent* pEvent);

		virtual t_FMT_Uint32		Start();
		virtual t_FMT_Uint32		Stop();

		virtual t_FMT_Uint32		GetReadMessagesNumber(t_FMT_Uint32& uiNom);
		virtual t_FMT_Uint32		Read(CFMT_HdwArinc429Message *pMess, t_FMT_Uint32 uiSize, t_FMT_Uint32& uiReadSize);
		virtual t_FMT_Uint32		EnableRx();
		virtual t_FMT_Uint32		DisableRx();
		virtual t_FMT_Uint32		ResetRx();
		virtual t_FMT_Uint32		AcceptAllMessages();
		virtual t_FMT_Uint32		DiscardAllMessages();
		virtual t_FMT_Uint32		AcceptMessage(t_FMT_Uint8 ucLabel, t_FMT_Uint8 ucSDI, t_FMT_Uint8 ucSSM);
	};

	// --- CArinc429ByteInBufferService ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CArinc429ByteInBufferService : public CFMT_HdwArinc429ByteInBufferService
	{
	public:
		
		CArinc429ByteInBufferService(CFMT_HdwObject *pPort);
		~CArinc429ByteInBufferService();
	};

	// --- CArinc429ByteOutBufferService ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CArinc429ByteOutBufferService : public CFMT_HdwArinc429ByteOutBufferService
	{
	protected:

	public:
		
		CArinc429ByteOutBufferService(CFMT_HdwObject *pPort);
		~CArinc429ByteOutBufferService();
	};

	// --- CArinc429OutLbloService ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CArinc429OutLbloService : public CFMT_HdwArinc429OutLbloService
	{
	public:
		
		CArinc429OutLbloService(CFMT_HdwObject *pPort);

		virtual t_FMT_Uint32		Start();
		virtual t_FMT_Uint32		Stop();

		virtual t_FMT_Uint32		EnableTx(t_FMT_Bool bImmediate = FMTDEF_FALSE);
		virtual t_FMT_Uint32		DisableTx(t_FMT_Bool bImmediate = FMTDEF_FALSE);
		virtual t_FMT_Uint32		SetLabelsCtrl(CLabelCtrl *pLabelCtrl, t_FMT_Uint32 uiSize, t_FMT_Bool bImmediate = FMTDEF_FALSE);
		virtual t_FMT_Uint32		UpdateMessages(CFMT_HdwArinc429Message *pMess, t_FMT_Uint32 uiSize, t_FMT_Bool bImmediate = FMTDEF_FALSE);
		virtual t_FMT_Uint32		ResetTx(t_FMT_Bool bImmediate = FMTDEF_FALSE);
	};

	// ---[ CSignalService ]-----------------------------------------------------

	class FMTDEF_LIB_DLLSPEC CSignalService : public CFMT_HdwSignalService
	{
	protected:

	public:
		
		friend class CFMT_HdwFmtUsb2Arinc429x2Device;
		friend class CArinc429RxPort;
		friend class CArinc429TxPort;

		CSignalService(CFMT_HdwObject *pPort);
		virtual t_FMT_Uint32		Start();
		virtual t_FMT_Uint32		Stop();
		virtual t_FMT_Uint32		ProcessEvent(CFMT_HdwEvent* pEvent);
	};


	// ---[ CArinc429TxDataGeneratorService ]-----------------------------------------------------

	class FMTDEF_LIB_DLLSPEC CArinc429TxDataGeneratorService : public CFMT_HdwDataGeneratorService
	{
	protected:

	public:
		
		friend class CFMT_HdwFmtUsb2Arinc429x2Device;
		friend class CArinc429TxPort;

		CArinc429TxDataGeneratorService(CFMT_HdwObject *pPort);

		virtual t_FMT_Uint32		Start();
		virtual t_FMT_Uint32		Stop();

		virtual t_FMT_Uint32		Enable();
		virtual t_FMT_Uint32		Disable();
		virtual t_FMT_Uint32		Reset();
	};


	// =====================================================================================
	//	VARIABLES
	// =====================================================================================

protected:

	t_FMT_Uint8				m_ucEventRate;
	t_FMT_Uint16			m_usWdgTimeout;
	t_FMT_Bool				m_bWdgEnable;

	t_FMT_Uint16			m_pusCrc16Table[256];
	t_FMT_Uint32			m_uiResponseTimeout;



public:

	// =====================================================================================
	// CONSTRUCTORS & DESTRUCTORS
	// =====================================================================================
	
	CFMT_HdwFmtUsb2Arinc429x2Device();
	virtual ~CFMT_HdwFmtUsb2Arinc429x2Device();

	// =====================================================================================
	//	FUNCTIONS
	// =====================================================================================

protected:

	//! Check the bridged UART link
	t_FMT_Uint32			CheckUartLink(const CFMT_String& sChannel);

	//! Build the CRC-16 Table
			void			BuildCrc16Table();

	//! Compute CRC from a single byte
			t_FMT_Uint16	CalcCRC16Word(t_FMT_Uint16 usCrc, t_FMT_Uint8 ucData);

	//! Compute CRC from a single byte
			t_FMT_Uint16	CalcCRC16(t_FMT_Uint8* pucData, t_FMT_Uint32 uiNB);

	//! Extract device parameters in order to configure Arinc429 baud rate
	static	t_FMT_Uint32	ExtractArinc429TxBaudRateParameters(t_FMT_Uint32 uiBaudrate, t_FMT_Bool& bSlope, t_FMT_Uint16& usDataBitTime, t_FMT_Uint16& usRtzBitTime);

	//! Return the last command number
			t_FMT_Uint16	GetLastCommandNum(CDeviceInstance* pInst);
			t_FMT_Uint16	GetLastCommandNum(t_FMT_Uint32 uiDeviceId);

	//! Send the command list to device
			t_FMT_Uint32	ProcessCommandList(CDeviceInstance* pInst);
			t_FMT_Uint32	ProcessCommandList(t_FMT_Uint32 uiDeviceId);

	//! Process the UART recepion for ECHO event
			t_FMT_Uint32	ProcessUartEchoReception(CDeviceInstance *pInst);

	//! Process the event reception of a device instance
			t_FMT_Uint32	ProcessReception(t_FMT_Uint32 uiDeviceId);

	//! Process the event payload of a device instance
			t_FMT_Uint32	ProcessEventPayload(t_FMT_Uint32 uiDeviceId);

	//! Attach a Start/Stop Session Command to Command List
			t_FMT_Uint32	AttachSessionCommand(CDeviceInstance* pInst, t_FMT_Bool bStop);
			t_FMT_Uint32	AttachSessionCommand(t_FMT_Uint32 uiDeviceId, t_FMT_Bool bStop);

	//! Attach a Status Request Command to Command List
			t_FMT_Uint32	AttachStatusRequestCommand(t_FMT_Uint32 uiDeviceId, t_FMT_Uint32 uiChannelId, t_FMT_Uint32 uiStatusType);

	//! Attach an Arinc429 Tx Configuration Command to Command List
			t_FMT_Uint32	AttachAtxConfigCommand(t_FMT_Uint32 uiDeviceId, t_FMT_Uint32 uiChannelId, CArinc429TxPort::CParameters *pParam);

	//! Attach an Arinc429 Tx Push Command to Command List
			t_FMT_Uint32	AttachAtxPushCommand(t_FMT_Uint32 uiDeviceId, t_FMT_Uint32 uiChannelId, CFMT_HdwArinc429Message **pMessages, t_FMT_Uint32 uiSize);

	//! Attach an Arinc429 Rx Configuration Command to Command List
			t_FMT_Uint32	AttachArxConfigCommand(t_FMT_Uint32 uiDeviceId, t_FMT_Uint32 uiChannelId, CArinc429RxPort::CParameters *pParam, t_FMT_Uint16 *pusMessageFilter = FMTDEF_NULL);

	//! Attach an Arinc429 Context Control Command to Command List
			t_FMT_Uint32	AttachAtxCtxCtrlCommand(t_FMT_Uint32 uiDeviceId, t_FMT_Uint32 uiChannelId, CFMT_HdwArinc429OutLbloService::CLabelCtrl *pLabelCtrl);

	//! Attach an Arinc429 Tx Context Data Command to Command List
			t_FMT_Uint32	AttachAtxCtxDataCommand(t_FMT_Uint32 uiDeviceId, t_FMT_Uint32 uiChannelId, CFMT_HdwArinc429Message *pMess);

	//! Attach an Arinc429 Tx Context Memory Reset Command to Command List
			t_FMT_Uint32	AttachAtxCtxResetCommand(t_FMT_Uint32 uiDeviceId, t_FMT_Uint32 uiChannelId);

	//! Process the ComEchoevent payload of a device instance
			t_FMT_Uint32	ProcessEventComEcho(t_FMT_Uint32 uiDeviceId, t_FMT_Uint8 ucChannel, t_FMT_Uint8 ucSize, t_FMT_Uint8 *pucBuf);

	//! Process the Status event payload of a device instance
			t_FMT_Uint32	ProcessEventStatus(t_FMT_Uint32 uiDeviceId, t_FMT_Uint8 ucChannel, t_FMT_Uint8 ucSize, t_FMT_Uint8 *pucBuf);

	//! Process the Arinc429 Rx event payload of a device instance
			t_FMT_Uint32	ProcessEventA429Rx(t_FMT_Uint32 uiDeviceId, t_FMT_Uint8 ucChannel, t_FMT_Uint8 ucSize, t_FMT_Uint8 *pucBuf);

	//! Process the Arinc429 Tx event payload of a device instance
			t_FMT_Uint32	ProcessEventA429Tx(t_FMT_Uint32 uiDeviceId, t_FMT_Uint8 ucChannel, t_FMT_Uint8 ucSize, t_FMT_Uint8 *pucBuf);

	//! Process the Status event payload of a device instance
			t_FMT_Uint32	WaitAllCommandEchoes(t_FMT_Uint32 uiDeviceId, t_FMT_Uint32 uiTimeout);


	//! Create a device instance
	virtual CFMT_HdwFtdiUartBridgedDevice::CDeviceInstance*	CreateDeviceInstance();

	//! Create a port
	virtual CFMT_HdwPort*		CreatePort(t_FMT_Uint32 uiType, CFMT_HdwObject *pDevice, t_FMT_Uint32 uiDeviceId, const CFMT_String& sChannelId);

public:

	//! Initialize the device.
	virtual	t_FMT_Uint32	Init(t_FMT_Uint32 dwTotalPortTypes  =CFMT_HdwPort::e_PortType_Total);

	//! Perform auto-bridging of device
	//virtual t_FMT_Uint32	Autobridge(CPortDescriptorMatrix& DevPortDesc);

	//! Open the device
	virtual t_FMT_Uint32	Open(t_FMT_Uint32 uiDeviceId);

	//! Close the device
	virtual t_FMT_Uint32	Close(t_FMT_Uint32 uiDeviceId);

	//! Perform actions before COM closing
	virtual t_FMT_Uint32	OnClosing(t_FMT_Uint32 uiDeviceId);

	//! Hardware timer handlers before service timer handlers
	virtual t_FMT_Uint32	HdwTimerStartDeviceIntanceHandler(t_FMT_Uint32 uiDeviceId, t_FMT_Uint64 quiTimerCnt);

	//! Hardware timer handlers after service timer handlers
	virtual t_FMT_Uint32	HdwTimerEndDeviceIntanceHandler(t_FMT_Uint32 uiDeviceId, t_FMT_Uint64 quiTimerCnt);

};


#endif

