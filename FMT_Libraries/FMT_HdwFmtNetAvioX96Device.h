// =====================================================================================
/**
 * @file					FMT_HdwFmtNetAvioX16Device.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					29/04/2022
 * @brief					Formatech Multicomm Device
 *
 * @version	Project:		Formatech C++ Hardware Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][29/04/2022]
 */
// =====================================================================================


#ifndef FMTDEF_HDW_FMTNETAVIOX96DEVICE_H
#define FMTDEF_HDW_FMTNETAVIOX96DEVICE_H

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

#ifndef FMTDEF_HDW_ETHFTDIUARTBRIDGEDDEVICE_H
#include "FMT_HdwHoeFtdiUartBridgedDevice.h"
#endif

#ifndef FMTDEF_HDW_DISCRETESETPORT_H
#include "FMT_HdwDiscreteSetPort.h"
#endif

#ifndef FMTDEF_HDW_DISCRETEINSERVICE_H
#include "FMT_HdwDiscreteInService.h"
#endif

#ifndef FMTDEF_HDW_DISCRETEOUTSERVICE_H
#include "FMT_HdwDiscreteOutService.h"
#endif




// =====================================================================================
//	DEFINES
// =====================================================================================

/* Total Discretes */
#define FMTDEF_HDW_FMTNETAVIOX96DEVICE_TOT_DISCRETES					140

/* Total Discrete Inputs */
#define FMTDEF_HDW_FMTNETAVIOX96DEVICE_TOT_DIN							96

/* Total Discrete Outputs */
#define FMTDEF_HDW_FMTNETAVIOX96DEVICE_TOT_DOUT							96

/* Total Discrete Inputs per Device */
#define FMTDEF_HDW_FMTNETAVIOX96DEVICE_TOT_DIN_PER_DEVICE				(32)

/* Total Discrete Inputs Groups per Device */
#define FMTDEF_HDW_FMTNETAVIOX96DEVICE_TOT_DIN_GROUP_PER_DEVICE			(4)

/* Total Discrete Inputs Devices */
#define FMTDEF_HDW_FMTNETAVIOX96DEVICE_TOT_DIN_DEVICES					(FMTDEF_HDW_FMTNETAVIOX96DEVICE_TOT_DIN / FMTDEF_HDW_FMTNETAVIOX96DEVICE_TOT_DIN_PER_DEVICE)

/* Total Discrete Inputs Per Groups */
#define FMTDEF_HDW_FMTNETAVIOX96DEVICE_TOT_DIN_PER_GROUP				(FMTDEF_HDW_FMTNETAVIOX96DEVICE_TOT_DIN_PER_DEVICE / FMTDEF_HDW_FMTNETAVIOX96DEVICE_TOT_DIN_GROUP_PER_DEVICE)

/* Total Discrete Inputs Groups */
#define FMTDEF_HDW_FMTNETAVIOX96DEVICE_TOT_DIN_GROUP					(FMTDEF_HDW_FMTNETAVIOX96DEVICE_TOT_DIN / FMTDEF_HDW_FMTNETAVIOX96DEVICE_TOT_DIN_PER_GROUP)





// *************************************************************************************
// *************************************************************************************
//	Class CFMT_HdwFmtNetAvioX96Device
// *************************************************************************************
// *************************************************************************************

#define FMTDEF_HDW_FMTNETAVIOX96DEVICE_RXEVENTPAYLOAD_MAX		0x100000

class FMTDEF_LIB_DLLSPEC CFMT_HdwFmtNetAvioX96Device : public CFMT_HdwHoeFtdiUartBridgedDevice
{
	// =====================================================================================
	//	TYPES
	// =====================================================================================

protected:

public:

	// --- t_DiscreteRef ----------------------------------------

	enum t_DiscreteRef
	{
		e_DIN_G1_1				= 0,
		e_DIN_G1_2				= 1,
		e_DIN_G1_3				= 2,
		e_DIN_G1_4				= 3,
		e_DIN_G1_5				= 4,
		e_DIN_G1_6				= 5,
		e_DIN_G1_7				= 6,
		e_DIN_G1_8				= 7,
		e_DIN_G2_9				= 8,
		e_DIN_G2_10				= 9,
		e_DIN_G2_11				= 10,
		e_DIN_G2_12				= 11,
		e_DIN_G2_13				= 12,
		e_DIN_G2_14				= 13,
		e_DIN_G2_15				= 14,
		e_DIN_G2_16				= 15,
		e_DIN_G3_17				= 16,
		e_DIN_G3_18				= 17,
		e_DIN_G3_19				= 18,
		e_DIN_G3_20				= 19,
		e_DIN_G3_21				= 20,
		e_DIN_G3_22				= 21,
		e_DIN_G3_23				= 22,
		e_DIN_G3_24				= 23,		
		e_DIN_G4_25				= 24,
		e_DIN_G4_26				= 25,
		e_DIN_G4_27				= 26,
		e_DIN_G4_28				= 27,
		e_DIN_G4_29				= 28,
		e_DIN_G4_30				= 29,
		e_DIN_G4_31				= 30,
		e_DIN_G4_32				= 31,
		e_DIN_G5_33				= 32,
		e_DIN_G5_34				= 33,
		e_DIN_G5_35				= 34,
		e_DIN_G5_36				= 35,
		e_DIN_G5_37				= 36,
		e_DIN_G5_38				= 37,
		e_DIN_G5_39				= 38,
		e_DIN_G5_40				= 39,
		e_DIN_G6_41				= 40,
		e_DIN_G6_42				= 41,
		e_DIN_G6_43				= 42,
		e_DIN_G6_44				= 43,
		e_PDIS_IN45_G6_OVOUT1	= 44,
		e_PDIS_IN46_G6_OVOUT2	= 45,
		e_PDIS_IN47_G6_OVOUT3	= 46,
		e_PDIS_IN48_G6_OVOUT4	= 47,
		e_DOGOUT1				= 48,
		e_DOGOUT2				= 49,
		e_DOGOUT3				= 50,
		e_DOGOUT4				= 51,
		e_DOGOUT5				= 52,
		e_DOGOUT6				= 53,
		e_DOGOUT7				= 54,
		e_DOGOUT8				= 55,
		e_DOGOUT9				= 56,
		e_DOGOUT10				= 57,
		e_DOGOUT11				= 58,
		e_DOGOUT12				= 59,
		e_DOGOUT13				= 60,
		e_DOGOUT14				= 61,
		e_DOGOUT15				= 62,
		e_DOGOUT16				= 63,
		e_DOGOUT17				= 64,
		e_DOGOUT18				= 65,
		e_DOGOUT19				= 66,
		e_DOGOUT20				= 67,
		e_DOGOUT21				= 68,
		e_DOGOUT22				= 69,
		e_DOGOUT23				= 70,
		e_DOGOUT24				= 71,
		e_DOGOUT25				= 72,
		e_DOGOUT26				= 73,
		e_DOGOUT27				= 74,
		e_DOGOUT28				= 75,
		e_DOGOUT29				= 76,
		e_DOGOUT30				= 77,
		e_DOGOUT31				= 78,
		e_DOGOUT32				= 79,
		e_DOGOUT33				= 80,
		e_DOGOUT34				= 81,
		e_DOGOUT35				= 82,
		e_DOGOUT36				= 83,
		e_DOVOUT5				= 84,
		e_DOVOUT6				= 85,
		e_DOVOUT7				= 86,
		e_DOVOUT8				= 87,
		e_DOGOUT37				= 88,
		e_DOGOUT38				= 89,
		e_DOGOUT39				= 90,
		e_DOGOUT40				= 91,
		e_PDIS_IN49_G7_OVOUT9	= 92,
		e_PDIS_IN50_G7_OVOUT10	= 93,
		e_PDIS_IN51_G7_OVOUT11	= 94,
		e_PDIS_IN52_G7_OVOUT12	= 95,
		e_PDIS_IN53_G7_OGOUT41	= 96,
		e_PDIS_IN54_G7_OGOUT42	= 97,
		e_PDIS_IN55_G7_OGOUT43	= 98,
		e_PDIS_IN56_G7_OGOUT44	= 99,
		e_PDIS_IN57_G8_OGOUT45	= 100,
		e_PDIS_IN58_G8_OGOUT46	= 101,
		e_PDIS_IN59_G8_OGOUT47	= 102,
		e_PDIS_IN60_G8_OGOUT48	= 103,
		e_PDIS_IN61_G8_OVOUT13	= 104,
		e_PDIS_IN62_G8_OVOUT14	= 105,
		e_PDIS_IN63_G8_OVOUT15	= 106,
		e_PDIS_IN64_G8_OVOUT16	= 107,
		e_PDIS_IN65_G9_OVOUT17	= 108,
		e_PDIS_IN66_G9_OVOUT18	= 109,
		e_PDIS_IN67_G9_OVOUT19	= 110,
		e_PDIS_IN68_G9_OVOUT20	= 111,
		e_PDIS_IN69_G9_OVOUT21	= 112,
		e_PDIS_IN70_G9_OVOUT22	= 113,
		e_PDIS_IN71_G9_OVOUT23	= 114,
		e_PDIS_IN72_G9_OVOUT24	= 115,
		e_PDIS_IN73_G10_OVOUT25	= 116,
		e_PDIS_IN74_G10_OVOUT26	= 117,
		e_PDIS_IN75_G10_OVOUT27	= 118,
		e_PDIS_IN76_G10_OVOUT28	= 119,
		e_PDIS_IN77_G10_OVOUT29	= 120,
		e_PDIS_IN78_G10_OVOUT30	= 121,
		e_PDIS_IN79_G10_OVOUT31	= 122,
		e_PDIS_IN80_G10_OVOUT32	= 123,
		e_PDIS_IN81_G11_OVOUT33	= 124,
		e_PDIS_IN82_G11_OVOUT34	= 125,
		e_PDIS_IN83_G11_OVOUT35	= 126,
		e_PDIS_IN84_G11_OVOUT36	= 127,
		e_PDIS_IN85_G11_OVOUT37	= 128,
		e_PDIS_IN86_G11_OVOUT38	= 129,
		e_PDIS_IN87_G11_OVOUT39	= 130,
		e_PDIS_IN88_G11_OVOUT40	= 131,
		e_PDIS_IN89_G12_OVOUT41	= 132,
		e_PDIS_IN90_G12_OVOUT42 = 133,
		e_PDIS_IN91_G12_OVOUT43 = 134,
		e_PDIS_IN92_G12_OVOUT44 = 135,
		e_PDIS_IN93_G12_OVOUT45 = 136,
		e_PDIS_IN94_G12_OVOUT46 = 137,
		e_PDIS_IN95_G12_OVOUT47 = 138,
		e_PDIS_IN96_G12_OVOUT48 = 139
	};

	// --- t_Command ----------------------------------------

	enum t_Command
	{
		e_Command_Invalid		= 0x00,
		e_Command_Session		= 0x01,
		e_Command_Config		= 0x02,
		e_Command_SetDout		= 0x03,
		e_Command_KeepAlive		= 0x04
	};

	// --- t_EventType ----------------------------------------

	enum t_EventType
	{
		e_EventType_ComEcho				= 0,
		e_EventType_CriticalFail		= 1,
		e_EventType_Status				= 2,

		e_EventType_Total				= 3,
		e_EventType_Undefined			= 255
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


	// --- t_EventRate ----------------------------------------

	enum t_EventRate
	{
		e_EventRate_10ms		= 0
	};


	// --- CEvent ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CEvent : public CFMT_HdwEvent
	{
	public:

		CEvent();

		t_FMT_Uint32			ExtractTimeStamp(t_FMT_Uint8 *pucBuf);
		virtual t_FMT_Uint32	ExtractData(t_FMT_Uint8 *pucBuf,t_FMT_Uint32 uiSize);
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


	// --- CEventPosList ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CEventPosList : public CFMT_List<t_FMT_Uint32>
	{
	};


	// --- CEchoWaiting ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CEchoWaiting : public CFMT_Object
	{
	public:
		t_FMT_Uint16		m_usComNumber;
		t_FMT_Uint64		m_quiSendTime;

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


	// --- CComEchoEvent ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CComEchoEvent : public CEvent
	{
	public:
		t_FMT_Uint16		m_usComNumber;

		CComEchoEvent();

		virtual t_FMT_Uint32	ExtractData(t_FMT_Uint8 *pucBuf,t_FMT_Uint32 uiSize);
	};


	// --- CStatusEvent ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CStatusEvent : public CEvent
	{
	public:

		t_DiscreteStatus	m_pDinStatus[FMTDEF_HDW_FMTNETAVIOX96DEVICE_TOT_DIN];
		t_DiscreteStatus	m_pDoutStatus[FMTDEF_HDW_FMTNETAVIOX96DEVICE_TOT_DOUT];

		CStatusEvent();

		virtual t_FMT_Uint32		ExtractData(t_FMT_Uint8 *pucBuf, t_FMT_Uint32 uiSize);
	};


	// --- CCriticalFailureEvent ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CCriticalFailureEvent : public CEvent
	{
	public:

		t_FMT_Uint32		m_uiFailureCode;

		CCriticalFailureEvent();

		virtual t_FMT_Uint32		ExtractData(t_FMT_Uint8 *pucBuf, t_FMT_Uint32 uiSize);
	};


	// --- CCommandEchoList ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CCommandEchoList : public CFMT_List<CEchoWaiting>
	{
	};


	// --- CConfigCtrl ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CConfigCtrl : public CFMT_Object
	{
	public:

		CFMT_HdwDiscreteSetPort::t_DiscreteType		m_pDinType[FMTDEF_HDW_FMTNETAVIOX96DEVICE_TOT_DIN_GROUP];
		t_FMT_Bool									m_pbDoutEnable[FMTDEF_HDW_FMTNETAVIOX96DEVICE_TOT_DOUT];
		t_FMT_Uint8									m_pucDinOpenGndCenterThresh[FMTDEF_HDW_FMTNETAVIOX96DEVICE_TOT_DIN_DEVICES];
		t_FMT_Uint8									m_pucDinOpenGndHystThresh[FMTDEF_HDW_FMTNETAVIOX96DEVICE_TOT_DIN_DEVICES];
		t_FMT_Uint8									m_pucDinSupplyOpenCenterThresh[FMTDEF_HDW_FMTNETAVIOX96DEVICE_TOT_DIN_DEVICES];
		t_FMT_Uint8									m_pucDinSupplyOpenHystThresh[FMTDEF_HDW_FMTNETAVIOX96DEVICE_TOT_DIN_DEVICES];

		CConfigCtrl();
	};



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
		t_FMT_Uint8				m_pucRxEventPayload[FMTDEF_HDW_FMTNETAVIOX96DEVICE_RXEVENTPAYLOAD_MAX];
		CEventPosList			m_RxEventPosList;
		t_FMT_Uint32			m_uiMaxRxBufferSize;

		CCommandEchoList		m_CommandEcholist;
		t_FMT_Uint32			m_uiCommandBufferNdw;

		CConfigCtrl				m_ConfigCtrl;

		t_FMT_Uint64			m_quiLastTxTime;													// Last TX Time


        CDeviceInstance();
        virtual ~CDeviceInstance();

		void 		Reset();
		void		ResetRxState();
	};


	// --- CDiscreteSetPort ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CDiscreteSetPort : public CFMT_HdwDiscreteSetPort
	{
	protected:

		static t_FMT_Bool			CanBeDiscreteInput(t_FMT_Uint32 idx);
		static t_FMT_Bool			CanBeDiscreteOutput(t_FMT_Uint32 idx);
		static t_FMT_Uint32			GetDinIndexPerGroup(t_FMT_Uint32 idx, t_FMT_Uint32 group);
		t_FMT_Bool					IsValidBidirectionalAssignment(CDiscreteSetPort::CParameters *pParam, t_FMT_Uint32 idx, CFMT_HdwDiscreteSetPort::t_DiscreteType type);
		t_FMT_Uint32				CheckParameters(CDiscreteSetPort::CParameters *pParam);

	public:
		
		CDiscreteSetPort(CFMT_HdwObject *pDevice,t_FMT_Uint32 uiDeviceId, const CFMT_String& sChannelId);
		//static t_FMT_Uint32			GetDoutAbsIndex(t_FMT_Uint32 idx);

		virtual t_FMT_Uint32		EnableService(t_FMT_Uint32 dwServiceType, CFMT_HdwService **ppService, CFMT_HdwService::CParameters *pParam = FMTDEF_NULL);
		virtual t_FMT_Uint32		Open(CFMT_HdwPort::CParameters *pParameters);
		virtual t_FMT_Uint32		OnOpening(CFMT_HdwPort::CParameters *pParameters);
		virtual t_FMT_Uint32		Close();
		virtual t_FMT_Uint32		ProcessEvent(CFMT_HdwEvent *pEvent);
		virtual t_FMT_Uint32		HdwTimerHandler(t_FMT_Uint64 quiTimerCnt);

	};


	// --- CDiscreteInService ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CDiscreteInService : public CFMT_HdwDiscreteInService
	{
	protected:

		t_DiscreteStatus			m_pDinStatus[FMTDEF_HDW_FMTNETAVIOX96DEVICE_TOT_DISCRETES];

	public:
		
		CDiscreteInService(CFMT_HdwObject *pPort);

		virtual t_FMT_Uint32		HdwTimerHandler(t_FMT_Uint64 quiTimerCnt);
		virtual t_FMT_Uint32		ProcessEvent(CFMT_HdwEvent* pEvent);

		virtual t_FMT_Uint32		Start();
		virtual t_FMT_Uint32		Stop();

		virtual t_FMT_Uint32		GetDinStatus(t_FMT_Uint32 uiIndex, t_DiscreteStatus& status);
	};


	// --- CDiscreteOutService ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CDiscreteOutService : public CFMT_HdwDiscreteOutService
	{
	protected:

		t_DiscreteStatus			m_pDoutCmd[FMTDEF_HDW_FMTNETAVIOX96DEVICE_TOT_DISCRETES];
		t_DiscreteStatus			m_pDoutStatus[FMTDEF_HDW_FMTNETAVIOX96DEVICE_TOT_DISCRETES];

	public:
		
		CDiscreteOutService(CFMT_HdwObject *pPort);

		virtual t_FMT_Uint32		HdwTimerHandler(t_FMT_Uint64 quiTimerCnt);
		virtual t_FMT_Uint32		ProcessEvent(CFMT_HdwEvent* pEvent);

		virtual t_FMT_Uint32		Start();
		virtual t_FMT_Uint32		Stop();

		virtual t_FMT_Uint32		SetDoutStatus(t_FMT_Uint32 uiIndex, t_DiscreteStatus status, t_FMT_Bool bImmediate = FMTDEF_FALSE);
	    virtual t_FMT_Uint32		GetDoutStatus(t_FMT_Uint32 uiIndex, t_DiscreteStatus& status);

	};

	// ---[ CSignalService ]-----------------------------------------------------

	class FMTDEF_LIB_DLLSPEC CSignalService : public CFMT_HdwSignalService
	{
	protected:

	public:
		
		friend class CFMT_HdwFmtNetAvioX96Device;
		friend class CDiscreteSetPort;

		CSignalService(CFMT_HdwObject *pPort);
		virtual t_FMT_Uint32		Start();
		virtual t_FMT_Uint32		Stop();
		virtual t_FMT_Uint32		ProcessEvent(CFMT_HdwEvent* pEvent);
	};

	// =====================================================================================
	//	VARIABLES
	// =====================================================================================

protected:

	static t_FMT_Uint32		m_puiDinAbs2PinMap[FMTDEF_HDW_FMTNETAVIOX96DEVICE_TOT_DIN];			// Discrete Input Map from absolute to pin number
	static t_FMT_Uint32		m_puiDoutAbs2PinMap[FMTDEF_HDW_FMTNETAVIOX96DEVICE_TOT_DOUT];		// Discrete Output Map from absolute to pin number
	
	static t_FMT_Uint32		m_puiDinPin2AbsMap[FMTDEF_HDW_FMTNETAVIOX96DEVICE_TOT_DISCRETES];	// Discrete Input Map from pin number to absolute
	static t_FMT_Uint32		m_puiDoutPin2AbsMap[FMTDEF_HDW_FMTNETAVIOX96DEVICE_TOT_DISCRETES];	// Discrete Output Map from pin number to absolute

	t_FMT_Uint16			m_pusCrc16Table[256];												// CRC Table

	t_FMT_Uint8				m_ucEventRate;														// Event rate
	t_FMT_Uint64			m_quiResponseTimeout;												// Response Timeout


public:

	// =====================================================================================
	// CONSTRUCTORS & DESTRUCTORS
	// =====================================================================================
	
	CFMT_HdwFmtNetAvioX96Device();
	virtual ~CFMT_HdwFmtNetAvioX96Device();

	// =====================================================================================
	//	FUNCTIONS
	// =====================================================================================

protected:

    //! Called when extra UART port has been found, not used for bridging
    void                        IdentifyAddictionalUart(CPortDescriptor& pd);

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

			t_FMT_Uint16		GetLastCommandNum(CDeviceInstance *pInst);
			t_FMT_Uint16		GetLastCommandNum(t_FMT_Uint32 uiDeviceId);

			t_FMT_Uint32		ProcessCommandList(CDeviceInstance *pInst);
			t_FMT_Uint32		ProcessCommandList(t_FMT_Uint32 uiDeviceId);

			t_FMT_Uint32		ProcessUartEchoReception(CDeviceInstance *pInst);
			t_FMT_Uint32		ProcessReception(t_FMT_Uint32 uiDeviceId);

			t_FMT_Uint32		ProcessEventPayload(t_FMT_Uint32 uiDeviceId);

			t_FMT_Uint32		AttachSessionCommand(CDeviceInstance *pInst, t_FMT_Bool bStop);
			t_FMT_Uint32		AttachSessionCommand(t_FMT_Uint32 uiDeviceId, t_FMT_Bool bStop);

			t_FMT_Uint32		AttachKeepAliveCommand(CDeviceInstance *pInst);
			t_FMT_Uint32		AttachKeepAliveCommand(t_FMT_Uint32 uiDeviceId);

			t_FMT_Uint32		AttachConfigCommand(CDeviceInstance *pInst, CConfigCtrl& Config);
			t_FMT_Uint32		AttachConfigCommand(t_FMT_Uint32 uiDeviceId, CConfigCtrl& Config);

			t_FMT_Uint32		AttachSetDoutCommand(CDeviceInstance *pInst, t_FMT_Uint32 uiIndex, t_DiscreteStatus status);
			t_FMT_Uint32		AttachSetDoutCommand(t_FMT_Uint32 uiDeviceId, t_FMT_Uint32 uiIndex, t_DiscreteStatus status);

			t_FMT_Uint32		ProcessEventComEcho(t_FMT_Uint32 uiDeviceId,t_FMT_Uint8 ucChannel,t_FMT_Uint8 ucSize,t_FMT_Uint8 *pucBuf);
			t_FMT_Uint32		ProcessEventCriticalFailure(t_FMT_Uint32 uiDeviceId, t_FMT_Uint8 ucChannel, t_FMT_Uint8 ucSize, t_FMT_Uint8 *pucBuf);
			t_FMT_Uint32		ProcessEventStatus(t_FMT_Uint32 uiDeviceId,t_FMT_Uint8 ucChannel,t_FMT_Uint8 ucSize,t_FMT_Uint8 *pucBuf);

			t_FMT_Uint32		WaitAllCommandEchoes(t_FMT_Uint32 uiDeviceId,t_FMT_Uint32 uiTimeout);

public:

	static t_FMT_Uint32			GetDinIdx(t_FMT_Uint32 uiDinNum);
	static t_FMT_Uint32			GetDoutIdx(t_FMT_Uint32 uiDoutNum);

	static t_FMT_Uint32			ComputeDinOpenGndThesholds(t_FMT_Double dLoThreshold, t_FMT_Double dHiThreshold,
												t_FMT_Uint8& ucCenter, t_FMT_Uint8& ucHyst);
	static t_FMT_Uint32			ComputeDinSupplyOpenThesholds(t_FMT_Double dLoThreshold, t_FMT_Double dHiThreshold,
												t_FMT_Uint8& ucCenter, t_FMT_Uint8& ucHyst);

	void						GetDefaultParameters(CDiscreteSetPort::CParameters& Param);

	virtual t_FMT_Uint32		Open(t_FMT_Uint32 uiDeviceId);
	virtual t_FMT_Uint32		Close(t_FMT_Uint32 uiDeviceId);

	virtual t_FMT_Uint32		OnClosing(t_FMT_Uint32 uiDeviceId);

	virtual t_FMT_Uint32		HdwTimerStartDeviceIntanceHandler(t_FMT_Uint32 uiDeviceId, t_FMT_Uint64 quiTimerCnt);
	virtual t_FMT_Uint32		HdwTimerEndDeviceIntanceHandler(t_FMT_Uint32 uiDeviceId, t_FMT_Uint64 quiTimerCnt);

};




#endif







