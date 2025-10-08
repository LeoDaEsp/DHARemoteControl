// =====================================================================================
/**
 * @file					CFMT_HdwUdpEmulatorDevice.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					22/07/2022
 * @brief					Loopback Internet Protocol Emulator Device
 *
 * @version	Project:		Formatech C++ Hardware Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][22/07/2022]
 */
// =====================================================================================

#ifndef FMTDEF_HDW_UDPEMULATORDEVICE_H
#define FMTDEF_HDW_UDPEMULATORDEVICE_H

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

#ifndef FMTDEF_HDW_BYTEINBUFFERSERVICE_H
#include "FMT_HdwByteInBufferService.h"
#endif

#ifndef FMTDEF_HDW_BYTEOUTBUFFERSERVICE_H
#include "FMT_HdwByteOutBufferService.h"
#endif

#ifndef FMTDEF_HDW_UARTPORT_H
#include "FMT_HdwUartPort.h"
#endif



// *************************************************************************************
// *************************************************************************************
//	Class CFMT_HdwUdpEmulatorDevice
// *************************************************************************************
// *************************************************************************************

// =====================================================================================
//	DEFINES
// =====================================================================================


#define FMTDEF_HDWUDPEMULATOR_MAX_PAYLOAD				1300
#define FMTDEF_HDWUDPEMULATOR_MAX_BUFFER_SIZE			2000


class FMTDEF_LIB_DLLSPEC CFMT_HdwUdpEmulatorDevice : public CFMT_HdwDevice
{
	// =====================================================================================
	//	TYPES
	// =====================================================================================

protected:

	// --- t_EmulationPacketHeader ---------------------------

    #pragma pack(push,1)
	typedef struct t_EmulationPacketHeader_Enum
	{
		t_FMT_Char			m_pchIdentifier[24];
		t_FMT_Uint32		m_uiRevision;
		t_FMT_Uint32		m_uiPortType;
		t_FMT_Uint32		m_uiPortNum;

	} t_EmulationPacketHeader;
    #pragma pack(pop)


	// --- t_EmulationPacketHeader ---------------------------

    #pragma pack(push,1)
	typedef struct t_EmulatedUartPacketHeader
	{
		t_FMT_Uint8		m_ucParity;
		t_FMT_Uint8		m_ucStopBits;
		t_FMT_Uint32	m_uiBaudRate;

	} t_EmulatedUartPacketHeader;
    #pragma pack(pop)


	// --- Emulated Port Descriptor --------------------------------------------------------------

	class FMTDEF_LIB_DLLSPEC CEmulatedPortParam : public CFMT_Object
	{
	public:

		CEmulatedPortParam();

		t_FMT_Uint32		m_uiType;
		CFMT_String			m_sName;
		CFMT_String			m_sTxIp;
		t_FMT_Uint16		m_usTxPort;
		t_FMT_Uint16		m_usRxPort;

	    CEmulatedPortParam&	operator=(const CEmulatedPortParam& op)
		{
			m_uiType = op.m_uiType;
			m_sName = op.m_sName;
			m_sTxIp = op.m_sTxIp;
			m_usTxPort = op.m_usTxPort;
			m_usRxPort = op.m_usRxPort;

			return (*this);
		}

	    t_FMT_Bool			operator==(const CEmulatedPortParam& op)
		{
            FMTDEFM_UNUSED(op);
            return FMTDEF_FALSE;
		}

	    t_FMT_Bool			operator!=(const CEmulatedPortParam& op)
		{
            FMTDEFM_UNUSED(op);
            return FMTDEF_FALSE;
		}

		FMTDEF_LIB_DLLSPEC friend CFMT_Buffer& operator<<(CFMT_Buffer& buf, CEmulatedPortParam& m);
		FMTDEF_LIB_DLLSPEC friend CFMT_Buffer& operator>>(CFMT_Buffer& buf, CEmulatedPortParam& m);
	};


	// --- CEmulationParamList --------------------------------------------

	class FMTDEF_LIB_DLLSPEC CEmulatedPortParamList : public CFMT_List<CEmulatedPortParam>
	{
	};


	// --- CEmulatedDeviceDesc ----------------------------------------------------------

	class FMTDEF_LIB_DLLSPEC CEmulatedDeviceDesc : public CFMT_Object
	{
	public:

		CFMT_String				m_sDeviceName;
		CEmulatedPortParamList	m_EmulatedPortList[CFMT_HdwPort::e_PortType_Total];

		CEmulatedDeviceDesc();

	    t_FMT_Bool		operator==(const CEmulatedDeviceDesc& op)
		{
            FMTDEFM_UNUSED(op);
            return FMTDEF_FALSE;
		}

	    t_FMT_Bool		operator!=(const CEmulatedDeviceDesc& op)
		{
            FMTDEFM_UNUSED(op);
            return FMTDEF_FALSE;
		}

		FMTDEF_LIB_DLLSPEC friend CFMT_Buffer& operator<<(CFMT_Buffer& buf, CEmulatedDeviceDesc& m);
		FMTDEF_LIB_DLLSPEC friend CFMT_Buffer& operator>>(CFMT_Buffer& buf, CEmulatedDeviceDesc& m);

	};	


	// --- CEmulatedDeviceDescList --------------------------------------------

	class FMTDEF_LIB_DLLSPEC CEmulatedDeviceDescList : public CFMT_List<CEmulatedDeviceDesc>
	{
	};


	// --- CDeviceInstance --------------------------------------------------------------

	class FMTDEF_LIB_DLLSPEC CDeviceInstance : public CFMT_HdwDevice::CDeviceInstance
	{
	public:

		CEmulatedDeviceDesc		m_EmulatedDeviceDesc;

		CDeviceInstance();
	};	


	// --- CUartByteInBufferService --------------------------------------------------------------

	class FMTDEF_LIB_DLLSPEC CUartByteInBufferService : public CFMT_HdwByteInBufferService
	{
	public:
		
		friend class CUartPort;

		CUartByteInBufferService(CFMT_HdwObject *pPort);

		virtual t_FMT_Uint32		Start();

		virtual t_FMT_Uint32		Read(BYTE *pbtBuf, t_FMT_Uint32 dwSize, t_FMT_Uint32& dwReadSize);
		virtual t_FMT_Uint32		GetReadBufferBytes(t_FMT_Uint32& uiNob);
		virtual t_FMT_Uint32		ResetReadBuffer();

		virtual t_FMT_Uint32		HdwTimerHandler(t_FMT_Uint32 uiTimerCnt);
	};


	// --- CUartByteOutBufferService --------------------------------------------------------------

	class FMTDEF_LIB_DLLSPEC CUartByteOutBufferService : public CFMT_HdwByteOutBufferService
	{
	public:
		
		friend class CUartPort;

		CUartByteOutBufferService(CFMT_HdwObject *pPort);

		virtual t_FMT_Uint32		Start();

		virtual t_FMT_Uint32		Write(BYTE *pbtBuf, t_FMT_Uint32 dwSize, t_FMT_Uint32 dwTimeout);
		virtual t_FMT_Uint32		GetBytesToBeWritten(t_FMT_Uint32& uiNob);
		virtual t_FMT_Uint32		ResetWriteBuffer();

		virtual t_FMT_Uint32		HdwTimerHandler(t_FMT_Uint32 uiTimerCnt);

	};


	// --- CUartPort --------------------------------------------------------------

	class FMTDEF_LIB_DLLSPEC CUartPort : public CFMT_HdwUartPort
	{
	protected:

		CEmulatedPortParam		m_EmulatedPortParam;
		CFMT_HdwUdpSocket		*m_pTxSocket;
		CFMT_HdwUdpSocket		*m_pRxSocket;
		t_FMT_Uint8				*m_pucRxUdpPacket;
		CFMT_Uint8List			m_RxBuffer;

	public:
		
		friend class CUartByteInBufferService;
		friend class CUartByteOutBufferService;

		CUartPort(CFMT_HdwObject *pDevice, t_FMT_Uint32 uiDeviceId, const CFMT_String& sChannelId, CEmulatedPortParam& ep);
		virtual ~CUartPort();

		virtual t_FMT_Uint32		Open(CFMT_HdwPort::CParameters *pParameters);
		virtual t_FMT_Uint32		OnOpening(CFMT_HdwPort::CParameters *pParameters);
		virtual t_FMT_Uint32		Close();
		virtual t_FMT_Uint32		EnableService(t_FMT_Uint32 dwServiceType, CFMT_HdwService **ppService, CFMT_HdwService::CParameters *pParam = FMTDEF_NULL);
		virtual t_FMT_Uint32		SetParity(t_FMT_Uint8 ucParity);

		t_FMT_Uint32				Write(BYTE *pbtBuf, t_FMT_Uint32 dwSize, t_FMT_Uint32 dwTimeout);
		t_FMT_Uint32				Read(BYTE *pbtBuf, t_FMT_Uint32 dwSize, t_FMT_Uint32& dwReadSize);
		t_FMT_Uint32				GetBytesToBeWritten(t_FMT_Uint32& uiNob);
		t_FMT_Uint32				GetReadBufferBytes(t_FMT_Uint32& uiNob);
		t_FMT_Uint32				WaitEndOfTransmission();

		t_FMT_Uint32				ResetWriteBuffer();
		t_FMT_Uint32				ResetReadBuffer();

		t_FMT_Uint32				CheckEmulationUartPacket(t_FMT_Uint32 uiPortType, t_FMT_Uint8* pucRxBuf, t_FMT_Uint32 uiBufSize);
		t_FMT_Uint32				ProcessUdpRxPacket(t_FMT_Uint8 *ucRxUdpPacket, t_FMT_Uint32 uiBufSize);
		virtual t_FMT_Uint32		HdwTimerHandler(t_FMT_Uint64 quiTimerCnt);
	};


	// =====================================================================================
	//	VARIABLES
	// =====================================================================================

protected:

	CEmulatedDeviceDescList			m_EmulatedDeviceDescList;


public:

	// =====================================================================================
	// CONSTRUCTORS & DESTRUCTORS
	// =====================================================================================
	
public:

	CFMT_HdwUdpEmulatorDevice();
	virtual ~CFMT_HdwUdpEmulatorDevice();

	// =====================================================================================
	//	FUNCTIONS
	// =====================================================================================

protected:

	static void				FillEmulationPacketHeader(t_FMT_Uint32 uiPortType, t_FMT_Uint32 uiPortNum, t_FMT_Uint8* pucTxBuf);
	static t_FMT_Uint32		CheckEmulationPacketHeader(t_FMT_Uint32 uiPortType, t_FMT_Uint8* pucRxBuf, t_FMT_Uint32 uiBufSize);

	virtual	t_FMT_Uint32	Open(t_FMT_Uint32 uiDeviceId);
	virtual	t_FMT_Uint32	Close(t_FMT_Uint32 uiDeviceId);

public:

	virtual	t_FMT_Uint32	Init(t_FMT_Uint32 dwTotalPortTypes = CFMT_HdwPort::e_PortType_Total);
	virtual t_FMT_Uint32	AttachDeviceInstance(const CFMT_String& sName);

	virtual t_FMT_Uint32	AttachUartPort(t_FMT_Uint32 uiDevIdx, const CFMT_String& sName,
														const CFMT_String& sTxIp, t_FMT_Uint16 usTxPort, t_FMT_Uint16 usRxPort
														);

};


#endif
