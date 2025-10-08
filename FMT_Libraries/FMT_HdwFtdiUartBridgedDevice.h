// =====================================================================================
/**
 * @file					FMT_HdwFtdiUartBridgedDevice.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					10/01/2020
 * @brief					Abstract FTDI UART Bridged Device
 *
 * @version	Project:		Formatech C++ Hardware Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][10/01/2020]
 */
// =====================================================================================



#ifndef FMTDEF_HDW_FTDIUARTBRIDGEDDEVICE_H
#define FMTDEF_HDW_FTDIUARTBRIDGEDDEVICE_H

// =====================================================================================
//	INCLUDES
// =====================================================================================

#ifdef FMTDEF_COMPILE_OS_WINDOWS

#ifdef UNICODE
    #define REDEF_UNICODE
    #undef UNICODE
#endif

#endif


#ifndef FMTDEF_CORE_H
#include "FMT_Core.h"
#endif

#ifndef FMTDEF_HDW_OBJECT_H
#include "FMT_HdwObject.h"
#endif

#ifndef FMTDEF_HDW_DEVICE_H
#include "FMT_HdwDevice.h"
#endif

#ifndef FMTDEF_HDW_UARTPORT_H
#include "FMT_HdwUartPort.h"
#endif

#ifndef FMTDEF_HDW_STDUARTDEVICE_H
#include "FMT_HdwStdUartDevice.h"
#endif


#ifdef FMTDEF_COMPILE_OS_WINDOWS

#include "WinDef.h"
#include <objbase.h>
#include <initguid.h>
#include <Setupapi.h>

#endif


// =====================================================================================
//	DEFINES
// =====================================================================================



// *************************************************************************************
// *************************************************************************************
//	Class CFMT_HdwFtdiUartBridgedDevice
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_HdwFtdiUartBridgedDevice : public CFMT_HdwDevice
{
    // =====================================================================================
    //	TYPES
    // =====================================================================================

protected:
public:

    // --- CDeviceInstance --------------------------------------------------

    class FMTDEF_LIB_DLLSPEC CDeviceInstance : public CFMT_HdwDevice::CDeviceInstance
    {
    public:

        CFMT_String             m_sChannelId;
		CFMT_String				m_sFullName;

        CUart                   m_Uart;

        CDeviceInstance();
    };

protected:

    // =====================================================================================
    //	VARIABLES
    // =====================================================================================

protected:

	//! Bridged UART parameters
    CFMT_HdwUartPort::CParameters		m_ComParameters;

	//! Write Timeout
    t_FMT_Uint32						m_uiWriteTimeout;


    #ifdef FMTDEF_COMPILE_OS_WINDOWS
	//! Vendor ID
	CFMT_String							m_sVid;

	//! Product ID
	CFMT_String							m_sPid;
    #endif

    #ifdef FMTDEF_COMPILE_OS_LINUX
    CFMT_String							m_sDevPathIdentifier;
    #endif


	//! COM Index
	t_FMT_Uint32						m_uiComIndex;

	//! Use Own Driver
	t_FMT_Bool							m_bUseOwnDriver;



public:

    // =====================================================================================
    // CONSTRUCTORS & DESTRUCTORS
    // =====================================================================================

public:

    CFMT_HdwFtdiUartBridgedDevice();
    virtual ~CFMT_HdwFtdiUartBridgedDevice();

    // =====================================================================================
    //	FUNCTIONS
    // =====================================================================================

protected:

    //! Open the COM port of device instance
	t_FMT_Uint32				Com_Open(CDeviceInstance *pInst);
    t_FMT_Uint32				Com_Open(t_FMT_Uint32 uiDeviceId);

    //! Close the COM port of device instance
	t_FMT_Uint32				Com_Close(CDeviceInstance *pInst);
    t_FMT_Uint32				Com_Close(t_FMT_Uint32 uiDeviceId);

    //! Write dwSize bytes to the port
    t_FMT_Uint32				Com_Write(CDeviceInstance *pInst, t_FMT_Uint8 *pucBuf, t_FMT_Uint32 uiSize);
    t_FMT_Uint32				Com_Write(t_FMT_Uint32 uiDeviceId, t_FMT_Uint8 *pucBuf, t_FMT_Uint32 uiSize);

    //! Read dwSize bytes from the port
    t_FMT_Uint32				Com_Read(CDeviceInstance *pInst, t_FMT_Uint8 *pucBuf, t_FMT_Uint32 uiSize, t_FMT_Uint32& uiReadSize);
    t_FMT_Uint32				Com_Read(t_FMT_Uint32 uiDeviceId, t_FMT_Uint8 *pucBuf, t_FMT_Uint32 uiSize, t_FMT_Uint32& uiReadSize);

    //! Return the port output buffer
    t_FMT_Uint32				Com_ResetWriteBuffer(CDeviceInstance *pInst);
    t_FMT_Uint32				Com_ResetWriteBuffer(t_FMT_Uint32 uiDeviceId);

    //! Return the number of bytes stored into the COM
    t_FMT_Uint32				Com_GetReadBufferBytes(CDeviceInstance *pInst, t_FMT_Uint32& uiNob);
    t_FMT_Uint32				Com_GetReadBufferBytes(t_FMT_Uint32 uiDeviceId, t_FMT_Uint32& uiNob);

    //! Reset the port input buffer
    t_FMT_Uint32				Com_ResetReadBuffer(CDeviceInstance *pInst);
    t_FMT_Uint32				Com_ResetReadBuffer(t_FMT_Uint32 uiDeviceId);

    #ifdef FMTDEF_COMPILE_OS_WINDOWS
    //! Extract REG_MULTI_SZ strings
	void						ExtractRegMultiSz(TCHAR *ptchString, CFMT_StringVector& StringVect, t_FMT_Uint32 uiMaxLen);
    #endif

    virtual void                IdentifyAddictionalUart(CPortDescriptor& pd);

	//! Extract port index number from path
	virtual t_FMT_Uint32		ExtractComIndex(const CFMT_String& sPath, t_FMT_Uint32& uiPortIdx);

	//! Get the device path identifier
	virtual CFMT_String			GetDevPathIndentifier();

    //! Extract the device serial number from path
    virtual t_FMT_Uint32        ExtractSerialNumberFromPath(const CFMT_String& sPath, CFMT_String& sSN);

    //! Extract the device revision from path
	virtual t_FMT_Uint32        ExtractRevisionFromPath(const CFMT_String& sPath, CFMT_String& sRevision);

	//! Extract device ID from serial number
	virtual t_FMT_Uint32		ExtractDeviceIdFromSerialNumber(const CFMT_String& sPath, t_FMT_Uint32& uiDeviceId);

	//! Select a COM port from multi-port device
	virtual t_FMT_Uint32		ProcessHardwareID(CFMT_StringVector& svHardwareID);

	//! Create a device instance
	virtual CDeviceInstance*	CreateDeviceInstance();

	//! Create a port
	virtual CFMT_HdwPort*		CreatePort(t_FMT_Uint32 uiType, CFMT_HdwObject *pDevice, t_FMT_Uint32 uiDeviceId, const CFMT_String& sChannelId);

	//! Check the bridged UART link
	virtual t_FMT_Uint32		CheckUartLink(const CFMT_String& sChannel);

public:

	//! Perform auto-bridging of device
	virtual t_FMT_Uint32		Autobridge(CPortDescriptorMatrix& DevPortDesc);

    //! Open the device
    virtual t_FMT_Uint32		Open(t_FMT_Uint32 uiDeviceId);

    //! Close the device
    virtual t_FMT_Uint32		Close(t_FMT_Uint32 uiDeviceId);

    //! Perform actions after COM opening
    virtual t_FMT_Uint32		OnOpening(t_FMT_Uint32 uiDeviceId);

    //! Perform actions before COM closing
    virtual t_FMT_Uint32		OnClosing(t_FMT_Uint32 uiDeviceId);

};



#endif







