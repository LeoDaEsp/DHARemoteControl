// =====================================================================================
/**
 * @file					FMT_HdwFmtMulticommDevice.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					11/09/2021
 * @brief					Formatech Multicomm Device
 *
 * @version	Project:		Formatech C++ Hardware Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][11/09/2021]
 */
// =====================================================================================


#ifndef FMTDEF_HDW_FMTMULTICOMMDEVICE_H
#define FMTDEF_HDW_FMTMULTICOMMDEVICE_H

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

#ifndef FMTDEF_HDW_HOEFTDIUARTBRIDGEDDEVICE_H
#include "FMT_HdwHoeFtdiUartBridgedDevice.h"
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

#ifndef FMTDEF_HDW_MILSTD1553SINGLERTSERVICE_H
#include "FMT_HdwMilStd1553SingleRtService.h"
#endif

#ifndef FMTDEF_HDW_MILSTD1553BCSERVICE_H
#include "FMT_HdwMilStd1553BcService.h"
#endif


// =====================================================================================
//	DEFINES
// =====================================================================================




// *************************************************************************************
// *************************************************************************************
//	Class CFMT_HdwFmtMulticommDevice
// *************************************************************************************
// *************************************************************************************

#define FMTDEF_HDW_FMTMULTICOMMDEVICE_RXEVENTPAYLOAD_MAX		0x100000

class FMTDEF_LIB_DLLSPEC CFMT_HdwFmtMulticommDevice : public CFMT_HdwHoeFtdiUartBridgedDevice
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

		e_Command_SramWrite		= 0x04,

		e_Command_AtxCtxCtrl	= 0x10,
		e_Command_AtxCtxData	= 0x11,
		e_Command_AtxCtxReset	= 0x12,

		e_Command_AtxConfig1	= 0x14,
		e_Command_AtxConfig2	= 0x15,
		e_Command_AtxConfig3	= 0x16,
		e_Command_AtxConfig4	= 0x17,
		e_Command_ArxConfig1	= 0x18,
		e_Command_ArxConfig2	= 0x19,
		e_Command_ArxConfig3	= 0x1A,
		e_Command_ArxConfig4	= 0x1B,
	
		e_Command_UartCtxData	= 0x21,
		e_Command_UartConfig1	= 0x22,
		e_Command_UartConfig2	= 0x23,

		e_Command_CanConfig1	= 0x30,
		e_Command_CanConfig2	= 0x31,
		e_Command_CanCtxData1	= 0x32,
		e_Command_CanCtxData2	= 0x33,

		e_Command_M1553_Config1	= 0x34,
		e_Command_M1553_Config2	= 0x35
	};

	// --- t_EventType ----------------------------------------

	enum t_EventType
	{
		e_EventType_ComEcho				= 0,
		e_EventType_CriticalFail		= 1,
		e_EventType_A429Rx				= 2,
		e_EventType_A429Tx				= 3,
		e_EventType_Status				= 5,
		e_EventType_CanRx				= 6,
		e_EventType_CanTx				= 7,
		e_EventType_MilStd1553			= 8,

		e_EventType_UartRx				= 9,
		e_EventType_UartTx				= 10,

		e_EventType_Total				= 11,
		e_EventType_Undefined			= 255
	};

	// --- t_UartRxSubType ----------------------------------------

	enum t_UartRxSubType
	{
		e_UartRxSubType_TimeOutPacket	= 0,
		e_UartRxSubType_NextPacket		= 1
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
		e_StatusRequestType_Arinc429Tx		= 1,
		e_StatusRequestType_CanTx			= 2,
		e_StatusRequestType_CanPort			= 3
	};

	// --- t_StatusEventType ----------------------------------------

	enum t_StatusEventType
	{
		e_StatusEventType_Arinc429Tx		= 1,
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


	// --- CCriticalFailureEvent ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CCriticalFailureEvent : public CEvent
	{
	public:

		CCriticalFailureEvent();
	};


	// --- CUartRxEvent ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CUartRxEvent : public CEvent
	{
	public:

		t_FMT_Uint8		m_ucSubType;
		t_FMT_Uint32	m_uiLength;
		t_FMT_Uint8		*m_pucByteBuf;

		CUartRxEvent();
		virtual ~CUartRxEvent();
		virtual t_FMT_Uint32	ExtractData(t_FMT_Uint8 *pucBuf,t_FMT_Uint32 uiSize);
	};


	// --- CUartTxEvent ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CUartTxEvent : public CEvent
	{
	public:

		t_FMT_Uint32	m_uiTag;
		t_FMT_Uint16	m_usNdw;

		CUartTxEvent();
		virtual ~CUartTxEvent();
		virtual t_FMT_Uint32	ExtractData(t_FMT_Uint8 *pucBuf, t_FMT_Uint32 uiSize);
	};


	// --- CArinc429RxEvent ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CArinc429RxEvent : public CEvent
	{
	public:
		CFMT_HdwArinc429Message		m_Arinc429Message;
		t_FMT_Uint32				m_uiIntergap;

		CArinc429RxEvent();
		virtual t_FMT_Uint32		ExtractData(t_FMT_Uint8 *pucBuf,t_FMT_Uint32 uiSize);
	};


	// --- CArinc429TxEvent ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CArinc429TxEvent : public CEvent
	{
	public:
		CFMT_HdwArinc429Message		m_Arinc429Message;

		CArinc429TxEvent();
		virtual t_FMT_Uint32		ExtractData(t_FMT_Uint8 *pucBuf,t_FMT_Uint32 uiSize);
	};


	// --- CCanRxEvent ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CCanRxEvent : public CEvent
	{
	public:
		CFMT_HdwCanMessage			m_CanMessage;

		CCanRxEvent();
		virtual t_FMT_Uint32		ExtractData(t_FMT_Uint8 *pucBuf,t_FMT_Uint32 uiSize);
	};

	// --- CCanTxEvent ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CCanTxEvent : public CEvent
	{
	public:
		CFMT_HdwCanMessage			m_CanMessage;

		CCanTxEvent();
		virtual t_FMT_Uint32		ExtractData(t_FMT_Uint8 *pucBuf,t_FMT_Uint32 uiSize);
	};


	// --- CStatusEvent ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CStatusEvent : public CEvent
	{
	public:
		t_FMT_Uint8				m_ucStatusType;
		t_FMT_Uint32			m_uiStatus;

		CStatusEvent();
		virtual t_FMT_Uint32	ExtractData(t_FMT_Uint8 *pucBuf,t_FMT_Uint32 uiSize);
	};

	
	// --- CMilStd1553Event ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CMilStd1553Event : public CEvent
	{
	public:

		t_FMT_Uint8		m_ucMode;
		
		t_FMT_Uint32	m_uiBufSize;
		t_FMT_Uint16	*m_pusBuf;

		t_FMT_Uint16	m_pusStatus[3];
		t_FMT_Uint16	m_usIndex;

		t_FMT_Uint8		m_ucMessageType;
		t_FMT_Uint8		m_ucRtAdd;
		t_FMT_Uint8		m_ucSubadd;
		t_FMT_Uint8		m_ucChannel;
		t_FMT_Bool		m_bBroadcast;
		t_FMT_Uint8		m_ucModeCode;

		CMilStd1553Event();
		virtual ~CMilStd1553Event();
		virtual t_FMT_Uint32	ExtractData(t_FMT_Uint8 *pucBuf,t_FMT_Uint32 uiSize);
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

	// --- t_MilStd1553_Mode ----------------------------------------

	enum t_MilStd1553_Mode
	{
		e_MilStd1553_Mode_Idle				= 0,
		e_MilStd1553_Mode_Bc				= 1,
		e_MilStd1553_Mode_Rt				= 2,
		e_MilStd1553_Mode_Mt				= 3
	};

	// --- t_MilStd1553_RtEventMsgType ----------------------------------------

	enum t_MilStd1553_RtEventMsgType
	{
		e_MilStd1553_RtEventMsgType_Bc2Rt		= 0,
		e_MilStd1553_RtEventMsgType_Rt2Bc		= 1,
		e_MilStd1553_RtEventMsgType_Rt2RtTx		= 2,
		e_MilStd1553_RtEventMsgType_Rt2RtRx		= 3,
		e_MilStd1553_RtEventMsgType_ModeCode	= 4
	};


	// --- CMilStd1553Config ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CMilStd1553Config : public CFMT_Object
	{
	public:

		t_FMT_Uint8		m_ucRtAdd;
		t_FMT_Bool		m_bRtTf;
		t_FMT_Bool		m_bRtSrb;
		t_FMT_Uint8		m_ucRtResponseDelay;
		
		t_FMT_Bool		m_bMsgEventEnable;

		t_FMT_Bool		m_bRtRxBufEventEnable;
		t_FMT_Uint16	m_usRtVectorWord;
		t_FMT_Uint16	m_usRtBuiltInWord;

		t_FMT_Uint16	m_usBcMinFrameDiv;
		t_FMT_Bool		m_bBcTxBufEnable;
		t_FMT_Bool		m_bBcRtRtBufEnable;

		t_FMT_Bool		m_bRun;
		t_FMT_Uint8		m_ucMode;
		t_FMT_Uint8		m_ucBcMajorFrameNum;

		CMilStd1553Config();
	};


	// --- CUartCtrlStatus ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CUartCtrlStatus : public CFMT_Object
	{
	public:
		
		t_FMT_Bool		m_bTxEnable;
		t_FMT_Bool		m_bRxEnable;


		t_FMT_Uint32	m_uiTxFifoNdw;
		t_FMT_Uint32	m_uiTxStatusMarker;

		t_FMT_Uint8		m_uiRxLatencyTimer;

		
		CUartCtrlStatus();
	};



public:

	// --- CDeviceInstance ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CDeviceInstance : public CFMT_HdwHoeFtdiUartBridgedDevice::CDeviceInstance
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
		t_FMT_Uint8				m_pucRxEventPayload[FMTDEF_HDW_FMTMULTICOMMDEVICE_RXEVENTPAYLOAD_MAX];
		CEventPosList			m_RxEventPosList;
		t_FMT_Uint32			m_uiMaxRxBufferSize;

		CCommandEchoList		m_CommandEcholist;
		t_FMT_Uint32			m_uiCommandBufferNdw;

		CArinc429TxCtrlStatus	m_AtxCtrlStatus[4];
		CArinc429RxCtrlStatus	m_ArxCtrlStatus[4];
		CCanCtrlStatus			m_CanCtrlStatus[2];

		CMilStd1553Config		m_MilStd1553Config[2];

		CUartCtrlStatus			m_UartCtrlStatus[2];

		CDeviceInstance();
		~CDeviceInstance();

		void ResetRxState();
		void Reset();
	};
	


	// --- CArinc429TxPort ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CArinc429TxPort : public CFMT_HdwArinc429TxPort
	{
	protected:

	public:
		
		CArinc429TxPort(CFMT_HdwObject *pDevice,t_FMT_Uint32 uiDeviceId, const CFMT_String& sChannelId);

		virtual t_FMT_Uint32		EnableService(t_FMT_Uint32 dwServiceType,CFMT_HdwService **ppService,CFMT_HdwService::CParameters *pParam= FMTDEF_NULL);

		virtual t_FMT_Uint32		Open(CFMT_HdwPort::CParameters *pParameters);
		virtual t_FMT_Uint32		OnOpening(CFMT_HdwPort::CParameters *pParameters);
		virtual t_FMT_Uint32		Close();

	};

	// --- CArinc429RxPort ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CArinc429RxPort : public CFMT_HdwArinc429RxPort
	{
	protected:

	public:
		
		CArinc429RxPort(CFMT_HdwObject *pDevice,t_FMT_Uint32 uiDeviceId, const CFMT_String& sChannelId);

		virtual t_FMT_Uint32		EnableService(t_FMT_Uint32 dwServiceType,CFMT_HdwService **ppService,CFMT_HdwService::CParameters *pParam= FMTDEF_NULL);

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

		virtual t_FMT_Uint32		Write(CFMT_HdwArinc429Message *pMess,t_FMT_Uint32 uiSize,t_FMT_Bool bImmediate=FMTDEF_FALSE);
		virtual t_FMT_Uint32		ResetWriteBuffer();
		virtual t_FMT_Uint32		GetMessagesToBeWritten(t_FMT_Uint32& uiNom);

	};

	// --- CArinc429InBufferService ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CArinc429InBufferService : public CFMT_HdwArinc429InBufferService
	{
	protected:

		t_FMT_Bool					ApplyFilter(CFMT_HdwArinc429Message& mess,t_FMT_Uint16 *pusMessageFilter);

	public:
		
		CArinc429InBufferService(CFMT_HdwObject *pPort);

		virtual t_FMT_Uint32		ProcessEvent(CFMT_HdwEvent* pEvent);

		virtual t_FMT_Uint32		Start();
		virtual t_FMT_Uint32		Stop();

		virtual t_FMT_Uint32		GetReadMessagesNumber(t_FMT_Uint32& uiNom);
		virtual t_FMT_Uint32		Read(CFMT_HdwArinc429Message *pMess,t_FMT_Uint32 uiSize,t_FMT_Uint32& uiReadSize);
		virtual t_FMT_Uint32		EnableRx();
		virtual t_FMT_Uint32		DisableRx();
		virtual t_FMT_Uint32		ResetRx();
		virtual t_FMT_Uint32		AcceptAllMessages();
		virtual t_FMT_Uint32		DiscardAllMessages();
		virtual t_FMT_Uint32		AcceptMessage(t_FMT_Uint8 ucLabel,t_FMT_Uint8 ucSDI,t_FMT_Uint8 ucSSM);
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

		virtual t_FMT_Uint32		EnableTx(t_FMT_Bool bImmediate=FMTDEF_FALSE);
		virtual t_FMT_Uint32		DisableTx(t_FMT_Bool bImmediate=FMTDEF_FALSE);
		virtual t_FMT_Uint32		SetLabelsCtrl(CLabelCtrl *pLabelCtrl,t_FMT_Uint32 uiSize,t_FMT_Bool bImmediate=FMTDEF_FALSE);
		virtual t_FMT_Uint32		UpdateMessages(CFMT_HdwArinc429Message *pMess,t_FMT_Uint32 uiSize,t_FMT_Bool bImmediate=FMTDEF_FALSE);
		virtual t_FMT_Uint32		ResetTx(t_FMT_Bool bImmediate=FMTDEF_FALSE);
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
		
		friend class CFMT_HdwFmtMulticommDevice;
		friend class CCanOutBufferService;
		friend class CCanInBufferService;
		friend class CSignalService;

		CCanPort(CFMT_HdwObject *pDevice, t_FMT_Uint32 uiDeviceId, const CFMT_String& sChannelId);

		static t_FMT_Uint32			CheckTimingParameters(CFMT_HdwCanPort::CParameters *pParam);

		virtual t_FMT_Uint32		EnableService(t_FMT_Uint32 dwServiceType,CFMT_HdwService **ppService,CFMT_HdwService::CParameters *pParam= FMTDEF_NULL);
		virtual t_FMT_Uint32		Open(CFMT_HdwPort::CParameters *pParameters);
		virtual t_FMT_Uint32		OnOpening(CFMT_HdwPort::CParameters *pParameters);
		virtual t_FMT_Uint32		Close();
		virtual t_FMT_Uint32		ProcessEvent(CFMT_HdwEvent *pEvent);
		virtual t_FMT_Uint32		HdwTimerHandler(t_FMT_Uint64 quiTimerCnt);
	};


	// ---[ CMilStd1553Port ]-----------------------------------------------------

	class CMilStd1553BcService;

	class FMTDEF_LIB_DLLSPEC CMilStd1553Port : public CFMT_HdwMilStd1553Port
	{
	protected:

	public:
		
		friend class CFMT_HdwFmtMulticommDevice;

		CMilStd1553Port(CFMT_HdwObject *pDevice, t_FMT_Uint32 uiDeviceId, const CFMT_String& sChannelId);

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

		CFMT_HdwCanPort::CFaultStatus					m_CanLastFaultStatus;

	public:
		
		friend class CFMT_HdwFmtMulticommDevice;
		friend class CCanPort;
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
		
		friend class CFMT_HdwFmtMulticommDevice;
		friend class CArinc429TxPort;

		CArinc429TxDataGeneratorService(CFMT_HdwObject *pPort);

		virtual t_FMT_Uint32		Start();
		virtual t_FMT_Uint32		Stop();

		virtual t_FMT_Uint32		Enable();
		virtual t_FMT_Uint32		Disable();
		virtual t_FMT_Uint32		Reset();
	};



	// ---[ CMilStd1553BcService ]-----------------------------------------------------

	class FMTDEF_LIB_DLLSPEC CMilStd1553BcService : public CFMT_HdwMilStd1553BcService
	{
	protected:

		CFMT_HdwMilStd1553Buffer			**m_ppBuffers;
		CFMT_HdwMilStd1553Message			**m_ppMessages;
		CFMT_HdwMilStd1553MinorFrame		**m_ppMinorFrames;

		t_FMT_Uint32						m_uiTotBuffers;
		t_FMT_Uint32						m_uiTotMessages;
		t_FMT_Uint32						m_uiTotMinorFrames;
		t_FMT_Uint32						m_uiTotMajorFrames;

		t_FMT_Uint32						BuildConfiguration(t_FMT_Uint32 uiTotMajorFrames, CFMT_HdwMilStd1553MajorFrame *pMjrFrames);
		t_FMT_Uint32						BuildSramMemoryCommands(t_FMT_Uint32 uiTotMajorFrames, CFMT_HdwMilStd1553MajorFrame *pMjrFrames);
		t_FMT_Uint32						DestroyConfiguration();

	public:
		
		friend class CFMT_HdwFmtMulticommDevice;
		friend class CMilStd1553Port;

		CMilStd1553BcService(CFMT_HdwObject *pPort);
		~CMilStd1553BcService();

		virtual t_FMT_Uint32		ProcessEvent(CFMT_HdwEvent* pEvent);
		virtual t_FMT_Uint32		HdwTimerHandler(t_FMT_Uint64 quiTimerCnt);
		virtual t_FMT_Uint32		Start();
		virtual t_FMT_Uint32		Stop();
		virtual t_FMT_Uint32		LoadConfiguration(t_FMT_Uint32 uiTotMajorFrames, CFMT_HdwMilStd1553MajorFrame *pMjrFrames);
		virtual t_FMT_Uint32		RunBc(t_FMT_Uint32 uiMajorFrameIdx,t_FMT_Uint32 uiMinorFrameTime);
		virtual t_FMT_Uint32		StopBc();
		virtual t_FMT_Uint32		ChangeMajorFrame(t_FMT_Uint32 uiMajorFrameIdx,t_FMT_Uint32 uiMinorFrameTime);
	};


	// ---[ CMilStd1553SingleRtService ]-----------------------------------------------------

	class FMTDEF_LIB_DLLSPEC CMilStd1553SingleRtService : public CFMT_HdwMilStd1553SingleRtService
	{
	protected:
		
		t_FMT_Uint32				m_uiTotBuffers;
		CFMT_HdwMilStd1553Buffer	**m_ppBuffers;

		t_FMT_Uint32				BuildSubaddressConfiguration();
		t_FMT_Uint32				BuildBufferInit();

        t_FMT_Uint32				DestroyConfiguration();

	public:
		
		friend class CFMT_HdwFmtMulticommDevice;
		friend class CMilStd1553Port;

		CMilStd1553SingleRtService(CFMT_HdwObject *pPort);
		~CMilStd1553SingleRtService();

		virtual t_FMT_Uint32		ProcessEvent(CFMT_HdwEvent* pEvent);
		virtual t_FMT_Uint32		HdwTimerHandler(t_FMT_Uint64 quiTimerCnt);
		virtual t_FMT_Uint32		Start();
		virtual t_FMT_Uint32		Stop();

		virtual t_FMT_Uint32		RunRt(t_FMT_Uint8 ucRtAdd);
		virtual t_FMT_Uint32		StopRt();
	};


	// --- CUartPort ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CUartPort : public CFMT_HdwUartPort
	{
	protected:

	public:
		
		CUartPort(CFMT_HdwObject *pDevice, t_FMT_Uint32 uiDeviceId, const CFMT_String& sChannelId);

		virtual t_FMT_Uint32		EnableService(t_FMT_Uint32 dwServiceType, CFMT_HdwService **ppService, CFMT_HdwService::CParameters *pParam = FMTDEF_NULL);

		virtual t_FMT_Uint32		Open(CFMT_HdwPort::CParameters *pParameters);
		virtual t_FMT_Uint32		OnOpening(CFMT_HdwPort::CParameters *pParameters);
		virtual t_FMT_Uint32		Close();

	};


	// --- CUartByteInBufferService ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CUartByteInBufferService : public CFMT_HdwByteInBufferService
	{
	protected:

		CFMT_Uint8List					m_Buffer;

	public:
		
		friend class CUartPort;

		CUartByteInBufferService(CFMT_HdwObject *pPort);

		virtual t_FMT_Uint32		Start();
		virtual t_FMT_Uint32		Stop();

		virtual t_FMT_Uint32		Read(BYTE *pbtBuf,t_FMT_Uint32 dwSize, t_FMT_Uint32& dwReadSize);
		virtual t_FMT_Uint32		GetReadBufferBytes(t_FMT_Uint32& uiNob);
		virtual t_FMT_Uint32		ResetReadBuffer();

		virtual t_FMT_Uint32		ProcessEvent(CFMT_HdwEvent* pEvent);

	};


	// --- CUartByteOutBufferService ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CUartByteOutBufferService : public CFMT_HdwByteOutBufferService
	{
	protected:

		CFMT_Uint8List				m_Buffer;
		t_FMT_Bool					m_bStatusRequest;
		t_FMT_Uint32				SendImmediate();

	public:
		
		friend class CUartPort;

		CUartByteOutBufferService(CFMT_HdwObject *pPort);

		virtual t_FMT_Uint32		Start();
		virtual t_FMT_Uint32		Stop();

		virtual t_FMT_Uint32		Write(BYTE *pbtBuf, t_FMT_Uint32 dwSize, t_FMT_Uint32 dwTimeout);
		virtual t_FMT_Uint32		GetBytesToBeWritten(t_FMT_Uint32& uiNob);
		virtual t_FMT_Uint32		ResetWriteBuffer();

		virtual t_FMT_Uint32		ProcessEvent(CFMT_HdwEvent* pEvent);
		virtual t_FMT_Uint32		HdwTimerHandler(t_FMT_Uint32 uiTimerCnt);

	};



	// =====================================================================================
	//	VARIABLES
	// =====================================================================================

protected:

	t_FMT_Uint8				m_ucEventRate;				// Event rate
	t_FMT_Uint16			m_pusCrc16Table[256];		// CRC Table
	t_FMT_Uint32			m_uiResponseTimeout;		// Response Timeout



public:

	// =====================================================================================
	// CONSTRUCTORS & DESTRUCTORS
	// =====================================================================================
	
	CFMT_HdwFmtMulticommDevice();
	virtual ~CFMT_HdwFmtMulticommDevice();

	// =====================================================================================
	//	FUNCTIONS
	// =====================================================================================

protected:

	//! Create a device instance
	virtual CFMT_HdwFtdiUartBridgedDevice::CDeviceInstance*	CreateDeviceInstance();

	//! Create a port
	virtual CFMT_HdwPort*		CreatePort(t_FMT_Uint32 uiType, CFMT_HdwObject *pDevice, t_FMT_Uint32 uiDeviceId, const CFMT_String& sChannelId);

	//! Check the bridged UART link
			t_FMT_Uint32		CheckUartLink(const CFMT_String& sChannel);

	//! Select a COM port from multi-port device
			t_FMT_Uint32		ProcessHardwareID(CFMT_StringVector& svHardwareID);

			void				BuildCrc16Table();
			t_FMT_Uint16		CalcCRC16Word(t_FMT_Uint16 usCrc,t_FMT_Uint8 ucData);
			t_FMT_Uint16		CalcCRC16(t_FMT_Uint8* pucData,t_FMT_Uint32 uiNB);


	static	t_FMT_Uint32		ExtractArinc429TxBaudRateParameters(t_FMT_Uint32 uiBaudrate,t_FMT_Bool& bSlope,t_FMT_Uint16& usDataBitTime,t_FMT_Uint16& usRtzBitTime);

			t_FMT_Uint16		GetLastCommandNum(CDeviceInstance *pInst);
			t_FMT_Uint16		GetLastCommandNum(t_FMT_Uint32 uiDeviceId);

			t_FMT_Uint32		ProcessCommandList(CDeviceInstance *pInst);
			t_FMT_Uint32		ProcessCommandList(t_FMT_Uint32 uiDeviceId);

			t_FMT_Uint32		ProcessUartEchoReception(CDeviceInstance *pInst);
			t_FMT_Uint32		ProcessReception(t_FMT_Uint32 uiDeviceId);

			t_FMT_Uint32		ProcessEventPayload(t_FMT_Uint32 uiDeviceId);

			t_FMT_Uint32		AttachSessionCommand(CDeviceInstance *pInst, t_FMT_Bool bStop);
			t_FMT_Uint32		AttachSessionCommand(t_FMT_Uint32 uiDeviceId,t_FMT_Bool bStop);
			t_FMT_Uint32		AttachStatusRequestCommand(t_FMT_Uint32 uiDeviceId,t_FMT_Uint32 uiChannelId,t_FMT_Uint32 uiStatusType);
			t_FMT_Uint32		AttachAtxConfigCommand(t_FMT_Uint32 uiDeviceId,t_FMT_Uint32 uiChannelId,CArinc429TxPort::CParameters *pParam);
			t_FMT_Uint32		AttachAtxPushCommand(t_FMT_Uint32 uiDeviceId,t_FMT_Uint32 uiChannelId,CFMT_HdwArinc429Message **pMessages,t_FMT_Uint32 uiSize);
			t_FMT_Uint32		AttachArxConfigCommand(t_FMT_Uint32 uiDeviceId,t_FMT_Uint32 uiChannelId,CArinc429RxPort::CParameters *pParam,t_FMT_Uint16 *pusMessageFilter=FMTDEF_NULL);
			t_FMT_Uint32		AttachAtxCtxCtrlCommand(t_FMT_Uint32 uiDeviceId,t_FMT_Uint32 uiChannelId,CFMT_HdwArinc429OutLbloService::CLabelCtrl *pLabelCtrl);
			t_FMT_Uint32		AttachAtxCtxDataCommand(t_FMT_Uint32 uiDeviceId,t_FMT_Uint32 uiChannelId,CFMT_HdwArinc429Message *pMess);
			t_FMT_Uint32		AttachAtxCtxResetCommand(t_FMT_Uint32 uiDeviceId,t_FMT_Uint32 uiChannelId);
			t_FMT_Uint32		AttachCanConfigCommand(t_FMT_Uint32 uiDeviceId,t_FMT_Uint32 uiChannelId,CCanCtrlStatus *pConfig);
			t_FMT_Uint32		AttachCanPushCommand(t_FMT_Uint32 uiDeviceId,t_FMT_Uint32 uiChannelId,CFMT_HdwCanMessage **pMessages,t_FMT_Uint32 uiSize);
			t_FMT_Uint32		AttachSramWriteCommand(t_FMT_Uint32 uiDeviceId,t_FMT_Uint32 uiAdd,t_FMT_Uint16 *pusMemBuf,t_FMT_Uint32 uiSize);
			t_FMT_Uint32		Attach1553ConfigCommand(t_FMT_Uint32 uiDeviceId,t_FMT_Uint32 uiChannelId);
			t_FMT_Uint32		AttachUartConfigCommand(t_FMT_Uint32 uiDeviceId, t_FMT_Uint32 uiChannelId, CUartPort::CParameters *pParam);
			t_FMT_Uint32		AttachUartTxPushCommand(t_FMT_Uint32 uiDeviceId, t_FMT_Uint32 uiChannelId, t_FMT_Uint8 *pucBuf, t_FMT_Uint32 uiSize);

			t_FMT_Uint32		ProcessEventComEcho(t_FMT_Uint32 uiDeviceId,t_FMT_Uint8 ucChannel,t_FMT_Uint8 ucSize,t_FMT_Uint8 *pucBuf);
			t_FMT_Uint32		ProcessEventStatus(t_FMT_Uint32 uiDeviceId,t_FMT_Uint8 ucChannel,t_FMT_Uint8 ucSize,t_FMT_Uint8 *pucBuf);
			t_FMT_Uint32		ProcessEventA429Rx(t_FMT_Uint32 uiDeviceId,t_FMT_Uint8 ucChannel,t_FMT_Uint8 ucSize,t_FMT_Uint8 *pucBuf);
			t_FMT_Uint32		ProcessEventA429Tx(t_FMT_Uint32 uiDeviceId,t_FMT_Uint8 ucChannel,t_FMT_Uint8 ucSize,t_FMT_Uint8 *pucBuf);
			t_FMT_Uint32		ProcessEventCanRx(t_FMT_Uint32 uiDeviceId,t_FMT_Uint8 ucChannel,t_FMT_Uint8 ucSize,t_FMT_Uint8 *pucBuf);
			t_FMT_Uint32		ProcessEventCanTx(t_FMT_Uint32 uiDeviceId,t_FMT_Uint8 ucChannel,t_FMT_Uint8 ucSize,t_FMT_Uint8 *pucBuf);
			t_FMT_Uint32		ProcessEventMilStd1553(t_FMT_Uint32 uiDeviceId,t_FMT_Uint8 ucChannel,t_FMT_Uint8 ucSize,t_FMT_Uint8 *pucBuf);
			t_FMT_Uint32		ProcessEventUartRx(t_FMT_Uint32 uiDeviceId, t_FMT_Uint8 ucChannel, t_FMT_Uint8 ucSize, t_FMT_Uint8 *pucBuf);
			t_FMT_Uint32		ProcessEventUartTx(t_FMT_Uint32 uiDeviceId, t_FMT_Uint8 ucChannel, t_FMT_Uint8 ucSize, t_FMT_Uint8 *pucBuf);
			t_FMT_Uint32		ProcessEventCriticalFailure(t_FMT_Uint32 uiDeviceId, t_FMT_Uint8 ucChannel, t_FMT_Uint8 ucSize, t_FMT_Uint8 *pucBuf);

			t_FMT_Uint32		WaitAllCommandEchoes(t_FMT_Uint32 uiDeviceId,t_FMT_Uint32 uiTimeout);

public:

	static	t_FMT_Uint32		ExtractUartBaudRateParameters(t_FMT_Uint32 uiBaudrate, t_FMT_Uint8& ucSmpSel, t_FMT_Uint16& usBaudRateDiv);

	virtual t_FMT_Uint32		Open(t_FMT_Uint32 uiDeviceId);
	virtual t_FMT_Uint32		Close(t_FMT_Uint32 uiDeviceId);

	virtual t_FMT_Uint32		OnClosing(t_FMT_Uint32 uiDeviceId);

	virtual t_FMT_Uint32		HdwTimerStartDeviceIntanceHandler(t_FMT_Uint32 uiDeviceId,t_FMT_Uint64 quiTimerCnt);
	virtual t_FMT_Uint32		HdwTimerEndDeviceIntanceHandler(t_FMT_Uint32 uiDeviceId,t_FMT_Uint64 quiTimerCnt);


	virtual t_FMT_Uint32		Stop();

	// Compute CAN timing parameters
	static t_FMT_Uint32		ExtractCanTimingParameters(t_FMT_Uint32 uiBaudRate, t_FMT_Double dSmpPoint, t_FMT_Uint8& ucPrescaler, t_FMT_Uint8& ucTseg1, t_FMT_Uint8& ucTseg2);

};




#endif







