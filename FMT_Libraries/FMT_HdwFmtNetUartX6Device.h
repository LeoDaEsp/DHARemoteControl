// =====================================================================================
/**
 * @file					FMT_HdwFmtNetUartX6Device.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					09/05/2025
 * @brief					Formatech NetUartX6 Device
 *
 * @version	Project:		Formatech C++ Hardware Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][09/05/2025]
 */
// =====================================================================================


#ifndef FMTDEF_HDW_FMTNETUARTX6DEVICE_H
#define FMTDEF_HDW_FMTNETUARTX6DEVICE_H

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

#ifndef FMTDEF_HDW_HOEDDEVICE_H
#include "FMT_HdwHoeDevice.h"
#endif

#ifndef FMTDEF_HDW_BYTEINBUFFERSERVICE_H
#include "FMT_HdwByteInBufferService.h"
#endif

#ifndef FMTDEF_HDW_BYTEOUTBUFFERSERVICE_H
#include "FMT_HdwByteOutBufferService.h"
#endif



// =====================================================================================
//	DEFINES
// =====================================================================================




// *************************************************************************************
// *************************************************************************************
//	Class CFMT_HdwFmtNetUartX6Device
// *************************************************************************************
// *************************************************************************************

//#define FMTDEF_HDW_FMTMULTICOMMDEVICE_RXEVENTPAYLOAD_MAX		0x100000

class FMTDEF_LIB_DLLSPEC CFMT_HdwFmtNetUartX6Device : public CFMT_HdwHoeDevice
{
	// =====================================================================================
	//	TYPES
	// =====================================================================================

protected:


public:

	// ---[ t_UartOpenReq_Field ]--------------------------------------------------

#pragma pack(push,1)
	typedef struct t_UartOpenReq_Field_Struct
	{
		t_FMT_Uint8                    m_ucParity;
		t_FMT_Uint8                    m_ucStopLength;
		t_FMT_Uint8                    m_ucSmpSel;
		t_FMT_Uint16                   m_usBaudDiv;
		t_FMT_Uint8                    m_ucDataLength;
		t_FMT_Uint16                   m_usLatencyTimeout;
		t_FMT_Uint16                   m_usLinkTimeout;
		t_FMT_Bool                     m_bHalfDuplex;
		t_FMT_Bool                     m_bTerminationEnable;

	} t_UartOpenReq_Field;
#pragma pack(pop)



	// ---[ t_HoePacket_UartOpenAns_Field ]--------------------------------------------------

#pragma pack(push,1)
	typedef struct t_UartOpenAns_Field_Struct
	{
		t_FMT_Uint16					m_usPort;

	} t_UartOpenAns_Field;
#pragma pack(pop)


	// ---[ t_UartStatus_Field ]--------------------------------------------------

#pragma pack(push,1)
	typedef struct t_UartStatus_Field_Struct
	{
		t_FMT_Uint32                       m_uiTxBufNob;

	} t_UartStatus_Field;
#pragma pack(pop)


	// ---[ t_Device_HoePacket_Payload ]--------------------------------------------------

#pragma pack(push,1)
	typedef union t_Device_HoePacket_Payload_Union
	{
		t_UartOpenReq_Field				m_UartOpenReqFields;
		t_UartOpenAns_Field				m_UartOpenAnsFields;
		t_UartStatus_Field				m_UartStatusFields;
		t_FMT_Uint8						m_pucPayData[FMTDEF_HDW_HOE_MAX_PAYLOAD_BYTES];

	} t_Device_HoePacket_Payload;
#pragma pack(pop)


	// --- CDeviceInstance ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CDeviceInstance : public CFMT_HdwHoeDevice::CDeviceInstance
	{
	public:
		CDeviceInstance();
		~CDeviceInstance();

		virtual void	GetOpenPortPayload(CFMT_HdwPort* pPort, CFMT_HdwPort::CParameters* pParameters, t_HoePacket& Pck);
	};


	// --- CUartPort ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CUartPort : public CFMT_HdwUartPort
	{
	protected:

	public:
		
		CUartPort(CFMT_HdwObject *pDevice, t_FMT_Uint32 uiDeviceId, const CFMT_String& sChannelId);
		virtual t_FMT_Uint32		EnableService(t_FMT_Uint32 dwServiceType, CFMT_HdwService** ppService, CFMT_HdwService::CParameters* pParam = FMTDEF_NULL);
		virtual t_FMT_Uint32		Open(CFMT_HdwPort::CParameters* pParameters);
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

		t_FMT_Uint32				m_uiFifoNob;
		t_FMT_Uint32				m_uiPckNum;
		CFMT_Uint8List				m_Buffer;
		t_FMT_Bool					m_bStatusRequest;

		t_FMT_Uint32				SendDataBuffer();

	public:
		
		friend class CUartPort;

		CUartByteOutBufferService(CFMT_HdwObject *pPort);

		virtual t_FMT_Uint32		Start();
		virtual t_FMT_Uint32		Stop();

		virtual t_FMT_Uint32		Write(BYTE *pbtBuf, t_FMT_Uint32 dwSize, t_FMT_Uint32 dwTimeout);
		virtual t_FMT_Uint32		GetBytesToBeWritten(t_FMT_Uint32& uiNob);
		virtual t_FMT_Uint32		ResetWriteBuffer();

		virtual t_FMT_Uint32		ProcessEvent(CFMT_HdwEvent* pEvent);
		virtual t_FMT_Uint32		HdwTimerHandler(t_FMT_Uint64 quiTimerCnt);

	};



	// =====================================================================================
	//	VARIABLES
	// =====================================================================================

protected:


public:

	// =====================================================================================
	// CONSTRUCTORS & DESTRUCTORS
	// =====================================================================================
	
	CFMT_HdwFmtNetUartX6Device();
	virtual ~CFMT_HdwFmtNetUartX6Device();

	// =====================================================================================
	//	FUNCTIONS
	// =====================================================================================

protected:

	// Create a device instance
	virtual CFMT_HdwDevice::CDeviceInstance*	CreateDeviceInstance();

	// Create a port
	virtual CFMT_HdwPort*						CreatePort(t_FMT_Uint32 uiType, CFMT_HdwObject* pDevice, t_FMT_Uint32 uiDeviceId, const CFMT_String& sChannelId);

public:

	static	t_FMT_Uint32						ExtractUartBaudRateParameters(t_FMT_Uint32 uiBaudrate, t_FMT_Uint8& ucSmpSel, t_FMT_Uint16& usBaudRateDiv);

};




#endif







