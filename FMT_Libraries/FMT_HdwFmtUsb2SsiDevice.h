// =====================================================================================
//	@file					FMT_HdwFmtUsb2SsiDevice.cpp
//	@date					23/05/2018
//	@author					Massimiliano Forzieri, Formatech Engineering S.R.L.
//
//	@brief					Formatech USB to SSI Device
//
//	@version Project:		Formatech Hardware Manager C++ Library
//	@version Part number:	SWCD-0019-2014
//	@version Environment:	Windows, Linux and QNX
//	@version Language:		ANSI C++
// -----------------------------------------------------------------------------------
//	@version	Revision summary:
//	@version	Rev 1.1.0001	M.Forzieri		Initial Release
// =====================================================================================

#ifndef FMTDEF_HDW_FMTUSB2SSIDEVICE_H
#define FMTDEF_HDW_FMTUSB2SSIDEVICE_H

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

#ifndef FMTDEF_HDW_I2CPORT_H
#include "FMT_HdwI2CPort.h"
#endif

#ifndef FMTDEF_HDW_SPIPORT_H
#include "FMT_HdwSpiPort.h"
#endif

#ifndef LFMT_HDW_I2CMASTERSERVICE_H
#include "FMT_HdwI2CMasterService.h"
#endif

#ifndef LFMT_HDW_SPIMASTERSERVICE_H
#include "FMT_HdwSpiMasterService.h"
#endif



// =====================================================================================
//	DEFINES
// =====================================================================================

// *************************************************************************************
// *************************************************************************************
//	Class CFMT_HdwFmtUsb2SsiDevice
// *************************************************************************************
// *************************************************************************************


class FMTDEF_LIB_DLLSPEC CFMT_HdwFmtUsb2SsiDevice : public CFMT_HdwHoeFtdiUartBridgedDevice
{
	// =====================================================================================
	//	TYPES
	// =====================================================================================

protected:

	// --- t_Command ----------------------------------------

	enum t_Command
	{
		e_Command_SpiConfig		= 0x00,
		e_Command_I2CConfig1	= 0x01,
		e_Command_I2CConfig2	= 0x02,
		e_Command_I2CConfig3	= 0x03,

		e_Command_SpiIo			= 0x10,

		e_Command_I2CIo1		= 0x21,
		e_Command_I2CIo2		= 0x22,
		e_Command_I2CIo3		= 0x23,

		e_Command_I2CIoComb1	= 0x31,
		e_Command_I2CIoComb2	= 0x32,
		e_Command_I2CIoComb3	= 0x33,

		e_Command_Invalid		= 0xFF,
	};

	// --- t_RxState ----------------------------------------

	enum t_RxState
	{
		e_RxState_Start				= 0,
		e_RxState_Command			= 1,
		e_RxState_PckNobLo			= 2,
		e_RxState_PckNobHi			= 3,
		e_RxState_Payload			= 4,
		e_RxState_CrcLow			= 5,
		e_RxState_CrcHigh			= 6
	};

public:

	// --- CDeviceInstance ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CDeviceInstance : public CFMT_HdwHoeFtdiUartBridgedDevice::CDeviceInstance
	{
	public:
		t_RxState				m_RxState;
		t_FMT_Uint8				*m_pucRxBuffer;
		t_FMT_Uint32			m_uiMaxRxBufferSize;
		t_FMT_Uint32			m_uiCurRxBufferPos;
		t_FMT_Uint32			m_uiRxCurPayloadLen;
		t_FMT_Uint32			m_uiRxCurPayloadPos;
		t_FMT_Uint16			m_usRxCrc;

		CDeviceInstance();
		~CDeviceInstance();

		void ResetRxState();
		void Reset();
	};
	
	// --- CI2CPort ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CI2CPort : public CFMT_HdwI2CPort
	{
	protected:

	public:
		
		CI2CPort(CFMT_HdwObject *pDevice, t_FMT_Uint32 uiDeviceId, const CFMT_String& sChannelId);

		virtual t_FMT_Uint32		EnableService(t_FMT_Uint32 dwServiceType,CFMT_HdwService **ppService,CFMT_HdwService::CParameters *pParam=NULL);

		virtual t_FMT_Uint32		Open(CFMT_HdwPort::CParameters *pParameters);
		virtual t_FMT_Uint32		OnOpening(CFMT_HdwPort::CParameters *pParameters);
		virtual t_FMT_Uint32		Close();

	};

	// --- CSpiPort ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CSpiPort : public CFMT_HdwSpiPort
	{
	protected:

	public:
		
		CSpiPort(CFMT_HdwObject *pDevice, t_FMT_Uint32 uiDeviceId, const CFMT_String& sChannelId);

		virtual t_FMT_Uint32		EnableService(t_FMT_Uint32 dwServiceType,CFMT_HdwService **ppService,CFMT_HdwService::CParameters *pParam=NULL);

		virtual t_FMT_Uint32		Open(CFMT_HdwPort::CParameters *pParameters);
		virtual t_FMT_Uint32		OnOpening(CFMT_HdwPort::CParameters *pParameters);
		virtual t_FMT_Uint32		Close();

	};


	// --- CI2CMasterService ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CI2CMasterService : public CFMT_HdwI2CMasterService
	{
	protected:

	public:
		
		CI2CMasterService(CFMT_HdwObject *pPort);

		virtual	t_FMT_Uint32		Write(t_FMT_Uint8 ucAdd,t_FMT_Uint8 *puiWriteBuf,t_FMT_Uint32 uiWriteSize);
		virtual	t_FMT_Uint32		Read(t_FMT_Uint8 ucAdd,t_FMT_Uint8 *puiReadBuf,t_FMT_Uint32 uiReadSize);
	};


	// --- CSpiMasterService ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CSpiMasterService : public CFMT_HdwSpiMasterService
	{
	protected:

	public:
		
		CSpiMasterService(CFMT_HdwObject *pPort);

		virtual	t_FMT_Uint32		Write(t_FMT_Uint8 *puiWriteBuf,t_FMT_Uint32 uiWriteSize, t_FMT_Uint32 uiTimeout = 500);
		virtual	t_FMT_Uint32		Read(t_FMT_Uint8 *puiReadBuf,t_FMT_Uint32 uiReadSize, t_FMT_Uint32 uiTimeout = 500);
		virtual	t_FMT_Uint32		WriteRead(t_FMT_Uint8 *puiWriteBuf,t_FMT_Uint32 uiWriteSize,t_FMT_Uint8 *puiReadBuf,t_FMT_Uint32 uiReadSize, t_FMT_Uint32 uiTimeout = 500);
	};



	// =====================================================================================
	//	VARIABLES
	// =====================================================================================

protected:

	t_FMT_Uint32			m_uiResponseTimeout;
	t_FMT_Uint16			m_pusCrc16Table[256];

public:

	// =====================================================================================
	// CONSTRUCTORS & DESTRUCTORS
	// =====================================================================================
	
	CFMT_HdwFmtUsb2SsiDevice();
	virtual ~CFMT_HdwFmtUsb2SsiDevice();

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


			t_FMT_Uint16	CalcCRC16Word(t_FMT_Uint16 btCrc,t_FMT_Uint8 btData);
			t_FMT_Uint16	CalcCRC16(t_FMT_Uint8* pbtData,t_FMT_Uint32 dwSize);

			void			BuildCrc16Table();

			t_FMT_Uint32	WaitResponse(t_FMT_Uint32 uiDeviceId,t_FMT_Uint32 uiTimeout);
			t_FMT_Uint8*	GetPayloadBuffer(t_FMT_Uint32 uiDeviceId,t_FMT_Uint32& uiSize);

			t_FMT_Uint32	ConfigI2C(t_FMT_Uint32 uiDeviceId,t_FMT_Uint32 uiChannelId,CI2CPort::CParameters *pParam);
			t_FMT_Uint32	ConfigSpi(t_FMT_Uint32 uiDeviceId,CSpiPort::CParameters *pParam);

	static	t_FMT_Uint32	GetI2CBaudRateDivisor(t_FMT_Uint32 uiBaudRate,t_FMT_Uint16& usDivisor);
	static	t_FMT_Uint32	GetSpiBaudRateDivisor(t_FMT_Uint32 uiBaudRate,t_FMT_Uint16& usDivisor);

public:

	virtual t_FMT_Uint32	Open(t_FMT_Uint32 uiDeviceId);
	virtual t_FMT_Uint32	Close(t_FMT_Uint32 uiDeviceId);

	virtual t_FMT_Uint32	OnClosing(t_FMT_Uint32 uiDeviceId);

	virtual t_FMT_Uint32	HdwTimerStartDeviceIntanceHandler(t_FMT_Uint32 uiDeviceId,t_FMT_Uint32 uiTimerCnt);
	virtual t_FMT_Uint32	HdwTimerEndDeviceIntanceHandler(t_FMT_Uint32 uiDeviceId,t_FMT_Uint32 uiTimerCnt);

};


#endif







