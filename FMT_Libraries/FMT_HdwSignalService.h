// =====================================================================================
/**
 * @file					FMT_HdwSignalService.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					06/09/2021
 * @brief					Abstract Hardware Signal Service
 *
 * @version	Project:		Formatech C++ Hardware Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][06/09/2021]
 */
// =====================================================================================



#ifndef FMTDEF_HDW_SIGNALSERVICE_H
#define FMTDEF_HDW_SIGNALSERVICE_H

// =====================================================================================
//	INCLUDES
// =====================================================================================


#ifndef FMTDEF_CORE_H
#include "FMT_Core.h"
#endif

#ifndef FMTDEF_HDW_OBJECT_H
#include "FMT_HdwObject.h"
#endif

#ifndef FMTDEF_HDW_EVENT_H
#include "FMT_HdwEvent.h"
#endif

#ifndef FMTDEF_HDW_SERVICE_H
#include "FMT_HdwService.h"
#endif

#ifndef FMTDEF_HDW_UARTPORT_H
#include "FMT_HdwUartPort.h"
#endif

#ifndef FMTDEF_HDW_ARINC429RXPORT_H
#include "FMT_HdwArinc429RxPort.h"
#endif

#ifndef FMTDEF_HDW_ARINC429TXPORT_H
#include "FMT_HdwArinc429TxPort.h"
#endif

#ifndef FMTDEF_HDW_MILSTD1553PORT_H
#include "FMT_HdwMilStd1553Port.h"
#endif

#ifndef FMTDEF_HDW_ARINC429MESSAGE_H
#include "FMT_HdwArinc429Message.h"
#endif

#ifndef FMTDEF_HDW_CANMESSAGE_H
#include "FMT_HdwCanMessage.h"
#endif

#ifndef FMTDEF_HDW_CANPORT_H
#include "FMT_HdwCanPort.h"
#endif

#ifndef FMTDEF_HDW_DISCRETESETPORT_H
#include "FMT_HdwDiscreteSetPort.h"
#endif


// =====================================================================================
//	DEFINES
// =====================================================================================



// *************************************************************************************
// *************************************************************************************
//	Class CFMT_HdwSignalService
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_HdwSignalService : public CFMT_HdwService
{
	// =====================================================================================
	//	TYPES
	// =====================================================================================

protected:
public:

	// --- t_SignalType ----------------------------------------

	enum t_SignalType
	{
		e_SignalType_System					= 0,

		e_SignalType_CanRx					= 1,
		e_SignalType_CanTx					= 2,
		e_SignalType_CanBusError			= 3,
		e_SignalType_CanArbitrationLost		= 4,
		e_SignalType_CanChangeStatus		= 5,
		e_SignalType_CanChangeErrReg		= 6,
		e_SignalType_CanTranceiverError		= 7,
		e_SignalType_CanTxAbort				= 8,
		e_SignalType_Arinc429Rx				= 9,
		e_SignalType_Arinc429Tx				= 10,
		e_SignalType_MilStd1553Message		= 11,
		e_SignalType_DiscreteInputStatus	= 12,
		e_SignalType_DiscreteOutputStatus	= 13,

		e_SignalType_Tot					= 14
	};

	// --- CParameters ---------------------------------------------------------

	class FMTDEF_LIB_DLLSPEC CParameters : public CFMT_HdwService::CParameters
	{
	public:
		t_FMT_Bool			m_pbEnableSignals[e_SignalType_Tot];

		CParameters();
	};


	// --- CSignal ------------------------------------------------------------

	class FMTDEF_LIB_DLLSPEC CSignal : public CFMT_HdwObject
	{
	public:

		t_FMT_Uint32		m_uiSignalType;

		CSignal();
	};

	// --- CMilStd1553MessageSignal ------------------------------------------------------------

	class FMTDEF_LIB_DLLSPEC CMilStd1553MessageSignal : public CSignal
	{
	public:

		CFMT_HdwMilStd1553Port			*m_pPort;

		t_FMT_Uint32					m_uiIndex;
		t_FMT_Uint16					m_pusData[32];
		t_FMT_Uint16					m_pusStatus[3];
		t_FMT_Uint8						m_ucSize;
		t_FMT_Uint64					m_quiTimeStamp;

		CMilStd1553MessageSignal();
	};

	// --- CCanRxSignal ------------------------------------------------------------

	class FMTDEF_LIB_DLLSPEC CCanRxSignal : public CSignal
	{
	public:

		CFMT_HdwCanMessage		m_Message;
		CFMT_HdwCanPort			*m_pPort;

		CCanRxSignal();
	};

	// --- CCanTxSignal ------------------------------------------------------------

	class FMTDEF_LIB_DLLSPEC CCanTxSignal : public CSignal
	{
	public:

		CFMT_HdwCanMessage		m_Message;
		CFMT_HdwCanPort			*m_pPort;

		CCanTxSignal();
	};


	// --- CCanStatusSignal ------------------------------------------------------------

	class FMTDEF_LIB_DLLSPEC CCanStatusSignal : public CSignal
	{
	public:

		t_FMT_Uint64						m_quiTimeTag;
		CFMT_HdwCanPort::CFaultStatus		m_FaultStatus;
		CFMT_HdwCanPort						*m_pPort;

		CCanStatusSignal();
	};


	// --- CCanBusErrorSignal ------------------------------------------------------------

	class FMTDEF_LIB_DLLSPEC CCanBusErrorSignal : public CCanStatusSignal
	{
	public:

		CCanBusErrorSignal();
	};


	// --- CCanArbitrationLostSignal ------------------------------------------------------------

	class FMTDEF_LIB_DLLSPEC CCanArbitrationLostSignal : public CCanStatusSignal
	{
	public:

		CCanArbitrationLostSignal();
	};


	// --- CCanChangeStatusSignal ------------------------------------------------------------

	class FMTDEF_LIB_DLLSPEC CCanChangeStatusSignal : public CCanStatusSignal
	{
	public:

		CCanChangeStatusSignal();
	};


	// --- CCanChangeErrSignal ------------------------------------------------------------

	class FMTDEF_LIB_DLLSPEC CCanChangeErrSignal : public CCanStatusSignal
	{
	public:

		CCanChangeErrSignal();
	};


	// --- CCanTranceiverErrorSignal ------------------------------------------------------------

	class FMTDEF_LIB_DLLSPEC CCanTranceiverErrorSignal : public CCanStatusSignal
	{
	public:

		CCanTranceiverErrorSignal();
	};


	// --- CCanTxAbortSignal ------------------------------------------------------------

	class FMTDEF_LIB_DLLSPEC CCanTxAbortSignal : public CCanStatusSignal
	{
	public:

		CCanTxAbortSignal();
	};


	// --- CArinc429RxSignal ------------------------------------------------------------

	class FMTDEF_LIB_DLLSPEC CArinc429RxSignal : public CSignal
	{
	public:

		CFMT_HdwArinc429Message		m_Message;
		CFMT_HdwArinc429RxPort		*m_pPort;

		CArinc429RxSignal();
	};

	// --- CArinc429TxSignal ------------------------------------------------------------

	class FMTDEF_LIB_DLLSPEC CArinc429TxSignal : public CSignal
	{
	public:

		CFMT_HdwArinc429Message		m_Message;
		CFMT_HdwArinc429TxPort		*m_pPort;

		CArinc429TxSignal();
	};

	// --- CDiscreteInputStatusSignal ---------------------------------------------------------

	class FMTDEF_LIB_DLLSPEC CDiscreteInputStatusSignal : public CSignal
	{
	public:
		
		t_FMT_Uint64				m_quiTimeStamp;
		t_FMT_Uint32				m_uiTotItems;
		t_DiscreteStatus			*m_pPinStatus;
		CFMT_HdwDiscreteSetPort		*m_pPort;

		CDiscreteInputStatusSignal();
		virtual ~CDiscreteInputStatusSignal();
	};

	// --- CDiscreteOutputStatusSignal ---------------------------------------------------------

	class FMTDEF_LIB_DLLSPEC CDiscreteOutputStatusSignal : public CSignal
	{
	public:
		
		t_FMT_Uint64				m_quiTimeStamp;
		t_FMT_Uint32				m_uiTotItems;
		t_DiscreteStatus			*m_pPinStatus;
		CFMT_HdwDiscreteSetPort		*m_pPort;

		CDiscreteOutputStatusSignal();
		virtual ~CDiscreteOutputStatusSignal();
	};



	// --- CSignalList --------------------------------------------------

	class FMTDEF_LIB_DLLSPEC CSignalList : public CFMT_List<CSignal*>
	{
	};


	// --- CSignalQueue --------------------------------------------------

	class FMTDEF_LIB_DLLSPEC CSignalQueue : public CFMT_HdwObject
	{
	protected:

		CSignalList			m_SignalList;
		CFMT_Mutex			*m_pMutex;

		t_FMT_Bool			Lock();
		t_FMT_Bool			Unlock();
		void				Push(CSignal* pSignal);

	public:

		friend class CFMT_HdwSignalService;

		CSignalQueue();
		~CSignalQueue();

		void				Clear();
		t_FMT_Uint32		GetTotalSignals();
		CSignal*			Pop();
	};


	// --- CQueueList --------------------------------------------------

	class FMTDEF_LIB_DLLSPEC CQueueList : public CFMT_List<CSignalQueue*>
	{
	};


	// =====================================================================================
	//	VARIABLES
	// =====================================================================================

protected:

	CParameters			m_Params;
	CQueueList			m_QueueList;


public:


	// =====================================================================================
	// CONSTRUCTORS & DESTRUCTORS
	// =====================================================================================
	
	CFMT_HdwSignalService(CFMT_HdwObject *pPort);
	virtual ~CFMT_HdwSignalService();

	// =====================================================================================
	//	FUNCTIONS
	// =====================================================================================

protected:

	t_FMT_Uint32				DispatchCanRxSignal(CFMT_HdwCanPort *pPort,CFMT_HdwCanMessage *pMessage);
	t_FMT_Uint32				DispatchCanTxSignal(CFMT_HdwCanPort *pPort,CFMT_HdwCanMessage *pMessage);
	t_FMT_Uint32				DispatchCanBusErrorSignal(CFMT_HdwCanPort *pPort,CFMT_HdwCanPort::CFaultStatus& fs,t_FMT_Uint64 quiTimeTag);
	t_FMT_Uint32				DispatchCanArbitrationLostSignal(CFMT_HdwCanPort *pPort,CFMT_HdwCanPort::CFaultStatus& fs,t_FMT_Uint64 quiTimeTag);
	t_FMT_Uint32				DispatchCanChangeStatusSignal(CFMT_HdwCanPort *pPort,CFMT_HdwCanPort::CFaultStatus& fs,t_FMT_Uint64 quiTimeTag);
	t_FMT_Uint32				DispatchCanChangeErrRegSignal(CFMT_HdwCanPort *pPort,CFMT_HdwCanPort::CFaultStatus& fs,t_FMT_Uint64 quiTimeTag);
	t_FMT_Uint32				DispatchCanTranceiverErrorSignal(CFMT_HdwCanPort *pPort,CFMT_HdwCanPort::CFaultStatus& fs,t_FMT_Uint64 quiTimeTag);
	t_FMT_Uint32				DispatchCanTxAbortSignal(CFMT_HdwCanPort *pPort,CFMT_HdwCanPort::CFaultStatus& fs,t_FMT_Uint64 quiTimeTag);

	t_FMT_Uint32				DispatchArinc429RxSignal(CFMT_HdwArinc429RxPort *pPort,CFMT_HdwArinc429Message *pMessage);
	t_FMT_Uint32				DispatchArinc429TxSignal(CFMT_HdwArinc429TxPort *pPort,CFMT_HdwArinc429Message *pMessage);

	t_FMT_Uint32				DispatchMilStd1553MessageSignal(CFMT_HdwMilStd1553Port *pPort, t_FMT_Uint16 usMsdIdx,t_FMT_Uint16 *pusStatus,
																	t_FMT_Uint8 ucBufSize,t_FMT_Uint16 *pusBuffer, t_FMT_Uint64 quiTimeTag);

	t_FMT_Uint32				DispatchDiscreteInputStatusSignal(CFMT_HdwDiscreteSetPort *pPort, t_FMT_Uint64 quiTimeStamp,
																	t_FMT_Uint32 uiTotItems, t_DiscreteStatus *pDinStatus);
	t_FMT_Uint32				DispatchDiscreteOutputStatusSignal(CFMT_HdwDiscreteSetPort *pPort, t_FMT_Uint64 quiTimeStamp,
																	t_FMT_Uint32 uiTotItems, t_DiscreteStatus *pDoutStatus);

public:

	virtual t_FMT_Uint32		GetParameters(CParameters *pParameters);
	virtual t_FMT_Uint32		SetParameters(CParameters *pParameters);

	virtual t_FMT_Uint32		Start();
	virtual t_FMT_Uint32		Stop();
	virtual t_FMT_Uint32		Abort();

	t_FMT_Bool					IsSignalEnabled(t_FMT_Uint32 uiType);
	t_FMT_Uint32				AttachQueue(CSignalQueue *pQueue);
};


#endif