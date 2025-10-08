// =====================================================================================
/**
 * @file					FMT_HdwFmtUsb2CanDevice.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					11/09/2021
 * @brief					Formatech Usb2Can Device
 *
 * @version	Project:		Formatech C++ Hardware Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][11/09/2021]
 */
// =====================================================================================

#ifndef FMTDEF_HDW_FMTUSB2CANDEVICE_H
#define FMTDEF_HDW_FMTUSB2CANDEVICE_H

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

#ifndef FMTDEF_HDW_ETHFTDIUARTBRIDGEDDEVICE_H
#include "FMT_HdwHoeFtdiUartBridgedDevice.h"
#endif

#ifndef FMTDEF_HDW_SIGNALSERVICE_H
#include "FMT_HdwSignalService.h"
#endif

#ifndef FMTDEF_HDW_CANMESSAGE_H
#include "FMT_HdwCanMessage.h"
#endif

#ifndef FMTDEF_HDW_CANPORT_H
#include "FMT_HdwCanPort.h"
#endif

#ifndef FMTDEF_HDW_CANINBUFFERSERVICE_H
#include "FMT_HdwCanInBufferService.h"
#endif

#ifndef FMTDEF_HDW_CANOUTBUFFERSERVICE_H
#include "FMT_HdwCanOutBufferService.h"
#endif


// =====================================================================================
//	DEFINES
// =====================================================================================



// *************************************************************************************
// *************************************************************************************
//	Class CFMT_HdwFmtUsb2CanDevice
// *************************************************************************************
// *************************************************************************************

#define FMTDEF_HDW_FMTUSB2CANDEVICE_RXEVENTPAYLOAD_MAX		0x100000

class FMTDEF_LIB_DLLSPEC CFMT_HdwFmtUsb2CanDevice : public CFMT_HdwFtdiUartBridgedDevice
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

		e_Command_CanConfig1	= 0x10,
		e_Command_CanConfig2	= 0x11,
		e_Command_CanConfig3	= 0x12,
		e_Command_CanConfig4	= 0x13,

		e_Command_CanCtxData1	= 0x18,
		e_Command_CanCtxData2	= 0x19,
		e_Command_CanCtxData3	= 0x1A,
		e_Command_CanCtxData4	= 0x1B
	};


	// --- t_EventType ----------------------------------------

	enum t_EventType
	{
		e_EventType_ComEcho				= 0,
		e_EventType_CriticalFail		= 1,
		e_EventType_Status				= 5,
		e_EventType_CanRx				= 6,
		e_EventType_CanTx				= 7,

		e_EventType_Total				= 8,
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
		e_StatusRequestType_CanTx			= 2,
		e_StatusRequestType_CanPort			= 3
	};


	// --- t_StatusEventType ----------------------------------------

	enum t_StatusEventType
	{
		e_StatusEventType_Can				= 2
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

		CEvent();

		t_FMT_Uint32			ExtractTimeStamp(t_FMT_Uint8 *pucBuf);
		virtual t_FMT_Uint32	ExtractData(t_FMT_Uint8 *pucBuf,t_FMT_Uint32 uiSize);
	};


	// --- t_CanSubType ----------------------------------------

	enum t_CanSubType
	{
		e_CanSubType_Be					= 0,
		e_CanSubType_Al					= 1,
		e_CanSubType_TxStatus			= 2,
		e_CanSubType_PortStatus			= 3,
		e_CanSubType_Abort				= 4,
		e_CanSubType_FaultChanged		= 5,
		e_CanSubType_TranceiverFault	= 6
	};


	// --- t_CanAbortType ----------------------------------------

	enum t_CanAbortTypeBit
	{
		e_CanAbortTypeFlag_Be			= 0,
		e_CanAbortTypeFlag_Timeout		= 1,
		e_CanAbortTypeFlag_TxReset		= 2
	};


	// --- CComEchoEvent ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CComEchoEvent : public CEvent
	{
	public:
		t_FMT_Uint16		m_usComNumber;

		CComEchoEvent();

		virtual t_FMT_Uint32	ExtractData(t_FMT_Uint8 *pucBuf,t_FMT_Uint32 uiSize);
	};


	// --- CCanRxEvent ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CCanRxEvent : public CEvent
	{
	public:
		CFMT_HdwCanMessage			m_CanMessage;

		CCanRxEvent();
		virtual t_FMT_Uint32	ExtractData(t_FMT_Uint8 *pucBuf,t_FMT_Uint32 uiSize);
	};


	// --- CCanTxEvent ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CCanTxEvent : public CEvent
	{
	public:
		CFMT_HdwCanMessage			m_CanMessage;

		CCanTxEvent();
		virtual t_FMT_Uint32	ExtractData(t_FMT_Uint8 *pucBuf,t_FMT_Uint32 uiSize);
	};

	// --- CStatusEvent ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CStatusEvent : public CEvent
	{
	public:
		t_FMT_Uint8			m_ucStatusType;
		t_FMT_Uint32		m_uiStatus;

		CStatusEvent();
		virtual t_FMT_Uint32	ExtractData(t_FMT_Uint8 *pucBuf,t_FMT_Uint32 uiSize);
	};
	

	// --- CCanCtrlStatus ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CCanCtrlStatus : public CFMT_Object
	{
	public:

		t_FMT_Uint32	m_uiBitRate;
		t_FMT_Uint8		m_ucSjw;
		t_FMT_Uint8		m_ucTseg1;
		t_FMT_Uint8		m_ucTseg2;
		t_FMT_Bool		m_bSam;
		t_FMT_Uint8		m_ucPrescaler;
		t_FMT_Bool		m_bResetMode;
		t_FMT_Bool		m_bListenOnlyMode;
		t_FMT_Bool		m_bSelfTestMode;
		t_FMT_Uint32	m_uiAccCode;
		t_FMT_Uint32	m_uiAccMask;
		t_FMT_Uint8		m_ucErrorWarningLimit;
		t_FMT_Bool		m_bAccFilterMode;
		t_FMT_Bool		m_bBusErrorEventEnable;
		t_FMT_Bool		m_bArbitrationLostEventEnable;
		t_FMT_Uint16	m_usMaxBusErrors;
		t_FMT_Uint16	m_usTxTimeout;
		t_FMT_Bool		m_bTxReset;

		t_FMT_Uint32	m_uiTxFifoNdw;

		t_FMT_Bool		m_bTxEventEnable;
		t_FMT_Bool		m_bTxTrancErrorEnable;

		CCanCtrlStatus();
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
		t_FMT_Uint8				m_pucRxEventPayload[FMTDEF_HDW_FMTUSB2CANDEVICE_RXEVENTPAYLOAD_MAX];
		CEventPosList			m_RxEventPosList;
		t_FMT_Uint32			m_uiMaxRxBufferSize;

		CCommandEchoList		m_CommandEcholist;
		t_FMT_Uint32			m_uiCommandBufferNdw;

		CCanCtrlStatus			m_CanCtrlStatus[4];

		CDeviceInstance();
		~CDeviceInstance();

		void ResetRxState();
		void Reset();
	};
	
	// ---[ CCanPort ]-----------------------------------------------------

	class CCanOutBufferService;
	class CCanInBufferService;
	class CSignalService;

	class FMTDEF_LIB_DLLSPEC CCanPort : public CFMT_HdwCanPort
	{

	protected:

		t_FMT_Uint8					GetPrescaler(CCanPort::CParameters *pParameters);

	public:
		
		friend class CFMT_HdwFmtUsb2CanDevice;
		friend class CCanOutBufferService;
		friend class CCanInBufferService;
		friend class CSignalService;

		CCanPort(CFMT_HdwObject *pDevice, t_FMT_Uint32 uiDeviceId, const CFMT_String& sChannelId);

		virtual t_FMT_Uint32		EnableService(t_FMT_Uint32 dwServiceType,CFMT_HdwService **ppService,CFMT_HdwService::CParameters *pParam= FMTDEF_NULL);
		virtual t_FMT_Uint32		Open(CFMT_HdwPort::CParameters *pParameters);
		virtual t_FMT_Uint32		OnOpening(CFMT_HdwPort::CParameters *pParameters);
		virtual t_FMT_Uint32		Close();
		virtual t_FMT_Uint32		ProcessEvent(CFMT_HdwEvent *pEvent);
		virtual t_FMT_Uint32		HdwTimerHandler(t_FMT_Uint64 quiTimerCnt);
	};


	// ---[ CCanOutBufferService ]-----------------------------------------------------

	class FMTDEF_LIB_DLLSPEC CCanOutBufferService : public CFMT_HdwCanOutBufferService
	{
	protected:

		t_FMT_Bool					m_bStatusRequest;

		virtual t_FMT_Uint32		SendImmediate();

	public:
		
		friend class CFMT_HdwFmtMulticommDevice;
		friend class CCanPort;

		CCanOutBufferService(CFMT_HdwObject *pPort);

		virtual t_FMT_Uint32		ProcessEvent(CFMT_HdwEvent* pEvent);
		virtual t_FMT_Uint32		HdwTimerHandler(t_FMT_Uint64 quiTimerCnt);
		virtual t_FMT_Uint32		Start();
		virtual t_FMT_Uint32		Stop();
		virtual t_FMT_Uint32		Write(CFMT_HdwCanMessage *pMess,t_FMT_Uint32 dwSize,t_FMT_Bool bImmediate);
		virtual t_FMT_Uint32		ResetWriteBuffer();
	};

	// ---[ CCanInBufferService ]-----------------------------------------------------

	class FMTDEF_LIB_DLLSPEC CCanInBufferService : public CFMT_HdwCanInBufferService
	{
	protected:

	public:
		
		CCanInBufferService(CFMT_HdwObject *pPort);

		virtual t_FMT_Uint32		ProcessEvent(CFMT_HdwEvent* pEvent);

		virtual t_FMT_Uint32		Start();
		virtual t_FMT_Uint32		Stop();
		virtual t_FMT_Uint32		Read(CFMT_HdwCanMessage *pMess,t_FMT_Uint32 uiSize,t_FMT_Uint32& uiReadSize);
		virtual t_FMT_Uint32		EnableRx();
		virtual t_FMT_Uint32		DisableRx();
		virtual t_FMT_Uint32		ResetRx();
	};



	// ---[ CSignalService ]-----------------------------------------------------

	class FMTDEF_LIB_DLLSPEC CSignalService : public CFMT_HdwSignalService
	{
	protected:

		CFMT_HdwCanPort::CFaultStatus					m_LastFaultStatus;

	public:
		
		friend class CFMT_HdwFmtUsb2CanDevice;
		friend class CCanPort;

		CSignalService(CFMT_HdwObject *pPort);
		virtual t_FMT_Uint32		Start();
		virtual t_FMT_Uint32		ProcessEvent(CFMT_HdwEvent* pEvent);
	};


	// =====================================================================================
	//	VARIABLES
	// =====================================================================================

protected:

	t_FMT_Uint8				m_ucEventRate;
	t_FMT_Uint16			m_pusCrc16Table[256];
	t_FMT_Uint32			m_uiResponseTimeout;



public:

	// =====================================================================================
	// CONSTRUCTORS & DESTRUCTORS
	// =====================================================================================
	
	CFMT_HdwFmtUsb2CanDevice();
	virtual ~CFMT_HdwFmtUsb2CanDevice();

	// =====================================================================================
	//	FUNCTIONS
	// =====================================================================================

protected:

	//! Create a device instance
	virtual CFMT_HdwFtdiUartBridgedDevice::CDeviceInstance*	CreateDeviceInstance();

	//! Create a port
	virtual CFMT_HdwPort*	CreatePort(t_FMT_Uint32 uiType, CFMT_HdwObject *pDevice, t_FMT_Uint32 uiDeviceId, const CFMT_String& sChannelId);

	//! Check the bridged UART link
	t_FMT_Uint32			CheckUartLink(const CFMT_String& sChannel);

			void			BuildCrc16Table();
			t_FMT_Uint16	CalcCRC16Word(t_FMT_Uint16 usCrc,t_FMT_Uint8 ucData);
			t_FMT_Uint16	CalcCRC16(t_FMT_Uint8* pucData,t_FMT_Uint32 uiNB);

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
			t_FMT_Uint32	AttachSessionCommand(t_FMT_Uint32 uiDeviceId,t_FMT_Bool bStop);

			t_FMT_Uint32	AttachStatusRequestCommand(t_FMT_Uint32 uiDeviceId,t_FMT_Uint32 uiChannelId,t_FMT_Uint32 uiStatusType);
			t_FMT_Uint32	AttachCanConfigCommand(t_FMT_Uint32 uiDeviceId,t_FMT_Uint32 uiChannelId,CCanCtrlStatus *pConfig);
			t_FMT_Uint32	AttachCanPushCommand(t_FMT_Uint32 uiDeviceId,t_FMT_Uint32 uiChannelId,CFMT_HdwCanMessage **pMessages,t_FMT_Uint32 uiSize);

			t_FMT_Uint32	ProcessEventComEcho(t_FMT_Uint32 uiDeviceId,t_FMT_Uint8 ucChannel,t_FMT_Uint8 ucSize,t_FMT_Uint8 *pucBuf);
			t_FMT_Uint32	ProcessEventStatus(t_FMT_Uint32 uiDeviceId,t_FMT_Uint8 ucChannel,t_FMT_Uint8 ucSize,t_FMT_Uint8 *pucBuf);
			t_FMT_Uint32	ProcessEventCanRx(t_FMT_Uint32 uiDeviceId,t_FMT_Uint8 ucChannel,t_FMT_Uint8 ucSize,t_FMT_Uint8 *pucBuf);
			t_FMT_Uint32	ProcessEventCanTx(t_FMT_Uint32 uiDeviceId,t_FMT_Uint8 ucChannel,t_FMT_Uint8 ucSize,t_FMT_Uint8 *pucBuf);

			t_FMT_Uint32	WaitAllCommandEchoes(t_FMT_Uint32 uiDeviceId,t_FMT_Uint32 uiTimeout);
public:

	virtual t_FMT_Uint32	Open(t_FMT_Uint32 uiDeviceId);
	virtual t_FMT_Uint32	Close(t_FMT_Uint32 uiDeviceId);

	virtual t_FMT_Uint32	OnClosing(t_FMT_Uint32 uiDeviceId);

	//! Hardware timer handlers before service timer handlers
	virtual t_FMT_Uint32	HdwTimerStartDeviceIntanceHandler(t_FMT_Uint32 uiDeviceId, t_FMT_Uint64 quiTimerCnt);

	//! Hardware timer handlers after service timer handlers
	virtual t_FMT_Uint32	HdwTimerEndDeviceIntanceHandler(t_FMT_Uint32 uiDeviceId, t_FMT_Uint64 quiTimerCnt);

	// Compute CAN timing parameters
	static t_FMT_Uint32		ExtractCanTimingParameters(t_FMT_Uint32 uiBaudRate, t_FMT_Double dSmpPoint, t_FMT_Uint8& ucPrescaler, t_FMT_Uint8& ucTseg1, t_FMT_Uint8& ucTseg2);

};



#endif







