// =====================================================================================
/**
 * @file					FMT_HdwFmtEthUartXDevice.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					06/11/2021
 * @brief					Formatech ETHUARTX3 Device
 *
 * @version	Project:		Formatech C++ Hardware Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][06/11/2021]
 */
// =====================================================================================


#ifndef FMTDEF_HDW_FMTETHUARTXDEVICE_H
#define FMTDEF_HDW_FMTETHUARTXDEVICE_H

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

#ifndef FMTDEF_HDW_FMTHOEDEVICE_H
#include "FMT_HdwFmtHoeDevice.h"
#endif

#ifndef FMTDEF_HDW_UARTPORT_H
#include "FMT_HdwUartPort.h"
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
//	Class CFMT_HdwFmtEthUartXDevice
// *************************************************************************************
// *************************************************************************************


class FMTDEF_LIB_DLLSPEC CFMT_HdwFmtEthUartXDevice : public CFMT_HdwFmtHoeDevice
{
	// =====================================================================================
	//	TYPES
	// =====================================================================================

protected:

    // --- CLinkTimer --------------------------------------------------------------

	class FMTDEF_LIB_DLLSPEC CLinkTimer : public CFMT_Object
    {
    protected:
		t_FMT_Uint64		m_quiTimer;
		CFMT_Mutex			m_Mutex;
    public:

		CLinkTimer();
		void			Update();
		t_FMT_Uint64	GetElapsedTime();
		t_FMT_Uint64	Now();
	};


    // --- CUartByteInBufferService --------------------------------------------------------------

    class FMTDEF_LIB_DLLSPEC CUartByteInBufferService : public CFMT_HdwByteInBufferService
    {
    public:

        friend class CUartPort;

		// Data Buffer
		CFMT_Uint8List				m_Buffer;

        CUartByteInBufferService(CFMT_HdwObject *pPort);

        //! Start the service
        virtual t_FMT_Uint32		Start();

        //! Read dwSize bytes from the input buffer
        virtual t_FMT_Uint32		Read(t_FMT_Uint8 *pbtBuf,t_FMT_Uint32 dwSize,t_FMT_Uint32& dwReadSize);

        //! Return the number of bytes stored into input buffer
        virtual t_FMT_Uint32		GetReadBufferBytes(t_FMT_Uint32& uiNob);
        virtual t_FMT_Uint32		ResetReadBuffer();

	    //! Process a hardware event
	    virtual t_FMT_Uint32		ProcessEvent(CFMT_HdwEvent* pEvent);
    };


    // --- CUartByteOutBufferService --------------------------------------------------------------

    class FMTDEF_LIB_DLLSPEC CUartByteOutBufferService : public CFMT_HdwByteOutBufferService
    {
    public:

        friend class CUartPort;

		CFMT_Uint8List				m_Buffer;
		CFMT_Mutex					m_Mutex;

        CUartByteOutBufferService(CFMT_HdwObject *pPort);

        //! Start the service
        virtual t_FMT_Uint32		Start();

        //! Write dwSize bytes to the output buffer
        virtual t_FMT_Uint32		Write(t_FMT_Uint8 *pbtBuf,t_FMT_Uint32 dwSize,t_FMT_Uint32 dwTimeout);

        //! Return the number of bytes stored into output buffer
        virtual t_FMT_Uint32		GetBytesToBeWritten(t_FMT_Uint32& uiNob);

        //! Reset the output buffer
        virtual t_FMT_Uint32		ResetWriteBuffer();

	    //! Process a hardware event
	    virtual t_FMT_Uint32		ProcessEvent(CFMT_HdwEvent* pEvent);

		//! Write a data block
		virtual t_FMT_Uint32		WriteDataBlock();
	};


    // --- CUartPort --------------------------------------------------------------

    class FMTDEF_LIB_DLLSPEC CUartPort : public CFMT_HdwUartPort
    {
    protected:

		//! Link Identifier
		t_FMT_Uint32				m_uiLinkIdentifier;

		//! TX Packet Number
		t_FMT_Uint32				m_uiTxPacketNumber;

		//! Last Write Packet Number
		t_FMT_Uint32				m_uiLastWritePacketNumber;

		//! Last RX Packet Number
		t_FMT_Uint32				m_uiLastRxPacketNumber;

		//! Number of bytes of Remote Write Buffer 
		t_FMT_Uint32				m_uiRemTxNob;

		//! Write Buffer Depth
		t_FMT_Uint32				m_uiWriteBufferDepth;

		//! Read Buffer Depth
		t_FMT_Uint32				m_uiReadBufferDepth;

		//! Link Timer
		CLinkTimer					m_LinkTimer;

		//! Hardware Timer Handler
		virtual t_FMT_Uint32		HdwTimerHandler(t_FMT_Uint64 quiTimerCnt);

		//! Process a hardware event
		t_FMT_Uint32				ProcessEvent(CFMT_HdwEvent *pEvent);

    public:

        friend class CUartByteInBufferService;
        friend class CUartByteOutBufferService;

        CUartPort(CFMT_HdwObject *pDevice, t_FMT_Uint32 uiDeviceId, const CFMT_String& sChannelId);

        //! Open the port
        virtual t_FMT_Uint32		Open(CFMT_HdwPort::CParameters *pParameters);

        //! Perform dedicated opening actions, after device instance opening and before starting services
        virtual t_FMT_Uint32		OnOpening(CFMT_HdwPort::CParameters *pParameters);

        //! Close the port
        virtual t_FMT_Uint32		Close();

        //! Enable a service on the port
        virtual t_FMT_Uint32		EnableService(t_FMT_Uint32 dwServiceType,CFMT_HdwService **ppService,CFMT_HdwService::CParameters *pParam=NULL);

        //! Change the port parity
        virtual t_FMT_Uint32		SetParity(t_FMT_Uint8 ucParity);

        //! Write dwSize bytes to the port
        t_FMT_Uint32				Write(t_FMT_Uint8 *pbtBuf,t_FMT_Uint32 dwSize,t_FMT_Uint32 dwTimeout);

        //! Read dwSize bytes from the port
        t_FMT_Uint32				Read(t_FMT_Uint8 *pbtBuf,t_FMT_Uint32 dwSize,t_FMT_Uint32& dwReadSize);

        //! Return the number of bytes to be written
        t_FMT_Uint32				GetBytesToBeWritten(t_FMT_Uint32& uiNob);

        //! Return the number of bytes stored into the port
        t_FMT_Uint32				GetReadBufferBytes(t_FMT_Uint32& uiNob);

        //! Reset the output buffer
        t_FMT_Uint32				ResetWriteBuffer();

        //! Reset the port input buffer
        t_FMT_Uint32				ResetReadBuffer();

    };


public:

	// --- CDeviceInstance ----------------------------------------

	class FMTDEF_LIB_DLLSPEC CDeviceInstance : public CFMT_HdwFmtHoeDevice::CDeviceInstance
	{
	public:

		CDeviceInstance(const CInstanceIpConfig& IpConfig, CFMT_HdwFmtHoeDevice *pHoeDev);
		//~CDeviceInstance();
	
		//! Validate current RX Packet
		virtual t_FMT_Uint32	ValidatePacket();

	};
	

	// =====================================================================================
	//	VARIABLES
	// =====================================================================================

protected:

public:

	// =====================================================================================
	// CONSTRUCTORS & DESTRUCTORS
	// =====================================================================================
	
	CFMT_HdwFmtEthUartXDevice();
	virtual ~CFMT_HdwFmtEthUartXDevice();

	// =====================================================================================
	//	FUNCTIONS
	// =====================================================================================

protected:

public:

	//! Initialize the device
	virtual	t_FMT_Uint32	Init(t_FMT_Uint32 uiTotalPortTypes = CFMT_HdwPort::e_PortType_Total);

};


#endif

