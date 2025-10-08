// =====================================================================================
/**
 * @file					FMT_HdwFmtUsb2Arinc429Device.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					05/09/2021
 * @brief					Formatech USB to Arinc429 Device
 *
 * @version	Project:		Formatech C++ Hardware Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][05/09/2021]
 */
// =====================================================================================



#ifndef FMTDEF_HDW_FMTUSB2ARINC429DEVICE_H
#define FMTDEF_HDW_FMTUSB2ARINC429DEVICE_H

// =====================================================================================
//	INCLUDES
// =====================================================================================


#ifndef FMTDEF_CORE_H
#include "FMT_Core.h"
#endif

#ifndef FMTDEF_HDW_OBJECT_H
#include "FMT_HdwObject.h"
#endif

#ifndef FMTDEF_HDW_FMTFTDIDEVICE_H
#include "FMT_HdwFtdiDevice.h"
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




// =====================================================================================
//	DEFINES
// =====================================================================================



// *************************************************************************************
// *************************************************************************************
//	Class CFMT_HdwFmtUsb2Arinc429Device
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_HdwFmtUsb2Arinc429Device : public CFMT_HdwFtdiDevice
{
	// =====================================================================================
	//	TYPES
	// =====================================================================================

protected:

	// --- t_DeviceType ---------------------------------------------

	enum t_DeviceType
	{
		e_DeviceType_Invalid			= 0,
		e_DeviceType_Rev_10				= 1,
		e_DeviceType_Opto_Rev_10		= 2,
		e_DeviceType_Rev_20				= 3,
		e_DeviceType_Opto_Rev_20		= 4
	};

	// --- t_CommandType ---------------------------------------------

	enum t_CommandType
	{
		e_Comm_SetTXGlobalCtrlReg		= 0x00,
		e_Comm_SetTXGlobalConfigReg		= 0x02,
		e_Comm_SetRXGlobalCtrlReg		= 0x20,
		e_Comm_SetRXGlobalConfigReg		= 0x22,

		e_Comm_SetRXTimeMarkReg			= 0x30,

		e_Comm_SetDiscReg				= 0x32,
		e_Comm_SetPwmReg				= 0x34,
		
		e_Comm_GetTXGlobalCtrlReg		= 0x40,
		e_Comm_GetRXGlobalCtrlReg		= 0x60,
		e_Comm_SetTXLabelDataReg		= 0x80,
		e_Comm_PushTXData				= 0x82,
		e_Comm_SetTXLabelCtrlReg		= 0x84,
		e_Comm_SetRXLabelCtrlReg		= 0xA4,
		e_Comm_GetRXLabelDataReg		= 0xE0,
		e_Comm_PopRXData				= 0xE2
	};

	// --- CCommand ---------------------------------------------

	class FMTDEF_LIB_DLLSPEC CCommand : public CFMT_HdwObject
	{
	public:
		t_FMT_Uint8			m_ucCommand;
		t_FMT_Uint32		m_uiTxSize;
		t_FMT_Uint32		m_uiRxSize;
		t_FMT_Uint8			*m_pucTxBuf;
		t_FMT_Uint8			*m_pucRxBuf;

		CCommand();
		~CCommand();

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

	// --- CCommandList ---------------------------------------------

	class FMTDEF_LIB_DLLSPEC CCommandList : public CFMT_List<CCommand>
	{
	};

	// --- CDeviceInstance ---------------------------------------------

	class FMTDEF_LIB_DLLSPEC CDeviceInstance : public CFMT_HdwDevice::CDeviceInstance
	{
	public:
		t_FMT_Uint32		m_uiLocID;
		CFMT_String			m_sSN;
		CFMT_String			m_sFullName;
		void*				m_hDevice;
		t_FMT_Uint32		m_uiTxFifoSamples[2];
		t_FMT_Uint32		m_uiRxFifoSamples[2];
		CCommandList		m_CommandList;
		t_FMT_Bool			m_bTxEnable[2];
		t_FMT_Bool			m_bRxEnable[2];

		CDeviceInstance();
	};


	// --- CArinc429TxPort ---------------------------------------------
	
	class FMTDEF_LIB_DLLSPEC CArinc429TxPort : public CFMT_HdwArinc429TxPort
	{
	protected:

	public:
		
		CArinc429TxPort(CFMT_HdwObject *pDevice, t_FMT_Uint32 uiDeviceId, const CFMT_String& sChannelId);

		virtual t_FMT_Uint32		EnableService(t_FMT_Uint32 dwServiceType, CFMT_HdwService **ppService, CFMT_HdwService::CParameters *pParam = FMTDEF_NULL);

		virtual t_FMT_Uint32		Open(CFMT_HdwPort::CParameters *pParameters);
		virtual t_FMT_Uint32		Close();

	};


	// --- CArinc429RxPort ---------------------------------------------

	class FMTDEF_LIB_DLLSPEC CArinc429RxPort : public CFMT_HdwArinc429RxPort
	{
	protected:

	public:
		
		CArinc429RxPort(CFMT_HdwObject *pDevice, t_FMT_Uint32 uiDeviceId, const CFMT_String& sChannelId);

		virtual t_FMT_Uint32		EnableService(t_FMT_Uint32 dwServiceType, CFMT_HdwService **ppService, CFMT_HdwService::CParameters *pParam = FMTDEF_NULL);

		virtual t_FMT_Uint32		Open(CFMT_HdwPort::CParameters *pParameters);
		virtual t_FMT_Uint32		Close();

	};


	// --- CArinc429OutBufferService ---------------------------------------------

	class FMTDEF_LIB_DLLSPEC CArinc429OutBufferService : public CFMT_HdwArinc429OutBufferService
	{
	protected:

		virtual t_FMT_Uint32		SendImmediate();

	public:
		
		CArinc429OutBufferService(CFMT_HdwObject *pPort);

		virtual t_FMT_Uint32		HdwTimerHandler(t_FMT_Uint64 quiTimerCnt);

		virtual t_FMT_Uint32		Start();
		virtual t_FMT_Uint32		Stop();

		virtual t_FMT_Uint32		Write(CFMT_HdwArinc429Message *pMess, t_FMT_Uint32 uiSize, t_FMT_Bool bImmediate = FMTDEF_FALSE);
		virtual t_FMT_Uint32		ResetWriteBuffer();
		virtual t_FMT_Uint32		GetMessagesToBeWritten(t_FMT_Uint32& uiNom);

	};


	// --- CArinc429InBufferService ---------------------------------------------

	class FMTDEF_LIB_DLLSPEC CArinc429InBufferService : public CFMT_HdwArinc429InBufferService
	{
	public:
		
		CArinc429InBufferService(CFMT_HdwObject *pPort);

		virtual t_FMT_Uint32		HdwTimerHandler(t_FMT_Uint64 quiTimerCnt);

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


	// --- CArinc429InLbloService ---------------------------------------------

	class FMTDEF_LIB_DLLSPEC CArinc429InLbloService : public CFMT_HdwArinc429InLbloService
	{

	protected:

	public:
		
		CArinc429InLbloService(CFMT_HdwObject *pPort);
		~CArinc429InLbloService();

		virtual t_FMT_Uint32		HdwTimerHandler(t_FMT_Uint64 quiTimerCnt);

		virtual t_FMT_Uint32		Start();
		virtual t_FMT_Uint32		Stop();

		virtual t_FMT_Uint32		EnableRx();
		virtual t_FMT_Uint32		DisableRx();
		virtual t_FMT_Uint32		ResetRx();
		virtual t_FMT_Uint32		EnableLabel(t_FMT_Uint8 ucLabel, t_FMT_Uint32 uiDepth);
		virtual t_FMT_Uint32		DisableLabel(t_FMT_Uint8 ucLabel);
		virtual t_FMT_Uint32		ReadMessages(t_FMT_Uint8 ucLabel, CFMT_HdwArinc429Message *pMess, t_FMT_Uint32 uiSize, t_FMT_Uint32 *puiReadSize);
		virtual t_FMT_Uint32		ReadLastMessage(t_FMT_Uint8 ucLabel, CFMT_HdwArinc429Message *pMess);
		virtual t_FMT_Uint32		GetLabelNumMessages(t_FMT_Uint8 ucLabel, t_FMT_Uint32 *puiQueueSize);
	};


	// --- CArinc429OutLbloService ---------------------------------------------

	class FMTDEF_LIB_DLLSPEC CArinc429OutLbloService : public CFMT_HdwArinc429OutLbloService
	{
	public:
		
		CArinc429OutLbloService(CFMT_HdwObject *pPort);

		virtual t_FMT_Uint32		HdwTimerHandler(t_FMT_Uint64 quiTimerCnt);
		virtual t_FMT_Uint32		Start();
		virtual t_FMT_Uint32		Stop();

		virtual t_FMT_Uint32		EnableTx(t_FMT_Bool bImmediate = FMTDEF_FALSE);
		virtual t_FMT_Uint32		DisableTx(t_FMT_Bool bImmediate = FMTDEF_FALSE);
		virtual t_FMT_Uint32		EnableLabel(t_FMT_Uint8 ucLabel, t_FMT_Uint32 uiRate, t_FMT_Bool bImmediate = FMTDEF_FALSE);
		virtual t_FMT_Uint32		DisableLabel(t_FMT_Uint8 ucLabel, t_FMT_Bool bImmediate = FMTDEF_FALSE);
		virtual t_FMT_Uint32		SetLabelsCtrl(CLabelCtrl *pLabelCtrl, t_FMT_Uint32 uiSize, t_FMT_Bool bImmediate = FMTDEF_FALSE);
		virtual t_FMT_Uint32		UpdateMessages(CFMT_HdwArinc429Message *pMess, t_FMT_Uint32 uiSize, t_FMT_Bool bImmediate = FMTDEF_FALSE);
		virtual t_FMT_Uint32		ResetTx(t_FMT_Bool bImmediate = FMTDEF_FALSE);
	};


	// --- CArinc429ByteInBufferService ---------------------------------------------

	class FMTDEF_LIB_DLLSPEC CArinc429ByteInBufferService : public CFMT_HdwArinc429ByteInBufferService
	{
	public:
		
		CArinc429ByteInBufferService(CFMT_HdwObject *pPort);
		~CArinc429ByteInBufferService();
	};


	// --- CArinc429ByteOutBufferService ---------------------------------------------

	class FMTDEF_LIB_DLLSPEC CArinc429ByteOutBufferService : public CFMT_HdwArinc429ByteOutBufferService
	{
	protected:

	public:
		
		CArinc429ByteOutBufferService(CFMT_HdwObject *pPort);
		~CArinc429ByteOutBufferService();
	};


	// =====================================================================================
	//	VARIABLES
	// =====================================================================================

protected:

public:

	// =====================================================================================
	// CONSTRUCTORS & DESTRUCTORS
	// =====================================================================================
	
	//! Base constructor
	CFMT_HdwFmtUsb2Arinc429Device();

	//! Destructor
	virtual ~CFMT_HdwFmtUsb2Arinc429Device();

	// =====================================================================================
	//	FUNCTIONS
	// =====================================================================================

protected:

    //! Called when extra UART port has been found, not used for bridging
    void                    IdentifyAddictionalUart(CPortDescriptor& pd);

	//! Apply the filter on an Arinc429 message
	t_FMT_Bool				ApplyFilter(CFMT_HdwArinc429Message& mess, t_FMT_Uint16 *pusMessageFilter);


public:

	//! Get high baud rate divisor
	static t_FMT_Uint8		HighBaud(t_FMT_Uint32 uiDevType, t_FMT_Bool bTX);

	//! Get low baud rate divisor
	static t_FMT_Uint8		LowBaud(t_FMT_Uint32 uiDevType, t_FMT_Bool bTX);

	//! Return the device type
	t_FMT_Uint32			GetDeviceType(t_FMT_Uint32 uiDeviceId);

	//! Initialize the device
	virtual	t_FMT_Uint32	Init(t_FMT_Uint32 uiTotalPortTypes = CFMT_HdwPort::e_PortType_Total);

	//! Open the device
	virtual t_FMT_Uint32	Open(t_FMT_Uint32 uiDeviceId);

	//! Close the device
	virtual t_FMT_Uint32	Close(t_FMT_Uint32 uiDeviceId);

	//! Hardware timer handlers before service timer handlers
	virtual t_FMT_Uint32	HdwTimerStartDeviceIntanceHandler(t_FMT_Uint32 uiDeviceId, t_FMT_Uint64 quiTimerCnt);

	//! Hardware timer handlers after service timer handlers
	virtual t_FMT_Uint32	HdwTimerEndDeviceIntanceHandler(t_FMT_Uint32 uiDeviceId, t_FMT_Uint64 quiTimerCnt);

	//! Write a byte buffer to a device
	t_FMT_Uint32			Write(t_FMT_Uint32 uiDeviceId, void* pBuf, t_FMT_Uint32 uiSize, t_FMT_Uint32* puiBW);

	//! Read a byte buffer from a device
	t_FMT_Uint32			Read(t_FMT_Uint32 uiDeviceId, void* pBuf, t_FMT_Uint32 uiSize, t_FMT_Uint32* puiBR);

	//! Read a device status
	t_FMT_Uint32			ReadDeviceStatus(t_FMT_Uint32 uiDeviceId);

	//! Enable a TX in FIFO mode
	t_FMT_Uint32			EnableTxFifoMode(t_FMT_Uint32 uiDeviceId, t_FMT_Uint8 btChannelId, CFMT_HdwArinc429TxPort::CParameters *pParam);

	//! Configure a TX in POST mode and keep it disabled
	t_FMT_Uint32			ConfigTxPostMode(t_FMT_Uint32 uiDeviceId, t_FMT_Uint8 btChannelId, CFMT_HdwArinc429TxPort::CParameters *pParam);

	//! Disable a TX
	t_FMT_Uint32			DisableTx(t_FMT_Uint32 uiDeviceId, t_FMT_Uint8 btChannelId);

	//! Push a messages set to TX FIFO
	t_FMT_Uint32			PushTxMessages(t_FMT_Uint32 uiDeviceId, t_FMT_Uint8 btChannelId, CFMT_HdwArinc429Message **pMessages, t_FMT_Uint32 uiSize);

	//! Enable a RX in FIFO mode
	t_FMT_Uint32			EnableRx(t_FMT_Uint32 uiDeviceId, t_FMT_Uint8 btChannelId, t_FMT_Uint16 *pusMessageFilter);

	//! Configure a RX in FIFO mode
	t_FMT_Uint32			ConfigRxFifoMode(t_FMT_Uint32 uiDeviceId, t_FMT_Uint8 btChannelId, CFMT_HdwArinc429RxPort::CParameters *pParam, t_FMT_Uint16 *pusMessageFilter);

	//! Reset the RX
	t_FMT_Uint32			ResetRx(t_FMT_Uint32 uiDeviceId, t_FMT_Uint8 btChannelId, t_FMT_Uint16 *pusMessageFilter);

	//! Disable a RX
	t_FMT_Uint32			DisableRx(t_FMT_Uint32 uiDeviceId, t_FMT_Uint8 btChannelId);

	//! Pop RX messages from the device
	t_FMT_Uint32			PopRxMessages(t_FMT_Uint32 uiDeviceId, t_FMT_Uint8 btChannelId, CFMT_HdwArinc429MessageList& buffer, t_FMT_Uint16 *pusMessageFilter, t_FMT_Uint32 uiMaxDepth);

	//! Pop RX messages from the device
	t_FMT_Uint32			PopRxMessages(t_FMT_Uint32 uiDeviceId, t_FMT_Uint8 btChannelId, CFMT_HdwArinc429MessageList& buffer);

	//! Flush the pending commands for a device instance
	t_FMT_Uint32			FlushPendingCommands(t_FMT_Uint32 uiDeviceId);

};

#endif
