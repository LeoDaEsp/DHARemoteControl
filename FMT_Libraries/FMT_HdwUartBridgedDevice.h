// =====================================================================================
/**
 * @file					FMT_HdwUartBridgedDevice.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					10/01/2020
 * @brief					Abstract UART Bridged Device
 *
 * @version	Project:		Formatech C++ Hardware Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][10/01/2020]
 */
// =====================================================================================



#ifndef FMTDEF_HDW_UARTBRIDGEDDEVICE_H
#define FMTDEF_HDW_UARTBRIDGEDDEVICE_H

// =====================================================================================
//	INCLUDES
// =====================================================================================


#ifndef FMTDEF_GLOBAL_H
#include "FMT_Global.h"
#endif

#ifndef FMTDEF_OBJECT_H
#include "FMT_Object.h"
#endif

#ifndef FMTDEF_EXCEPTION_H
#include "FMT_Exception.h"
#endif

#ifndef FMTDEF_STRING_H
#include "FMT_String.h"
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

#ifdef UNICODE
    #define REDEF_UNICODE
    #undef UNICODE
#endif

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
//	Class CFMT_HdwUartBridgedDevice
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_HdwUartBridgedDevice : public CFMT_HdwDevice
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

        #ifdef FMTDEF_COMPILE_OS_WINDOWS
        CFMT_HdwWindowUart      m_WinUart;
        #endif

        CDeviceInstance();
    };

protected:

    // =====================================================================================
    //	VARIABLES
    // =====================================================================================

protected:

    CFMT_HdwUartPort::CParameters		m_ComParameters;
    t_FMT_Uint32						m_uiWriteTimeout;

public:

    // =====================================================================================
    // CONSTRUCTORS & DESTRUCTORS
    // =====================================================================================

public:

    CFMT_HdwUartBridgedDevice();
    virtual ~CFMT_HdwUartBridgedDevice();

    // =====================================================================================
    //	FUNCTIONS
    // =====================================================================================

protected:

    //! Open the COM port of device instance
    t_FMT_Uint32	Com_Open(t_FMT_Uint32 uiDeviceId);

    //! Close the COM port of device instance
    t_FMT_Uint32	Com_Close(t_FMT_Uint32 uiDeviceId);

    //! Write dwSize bytes to the port
    t_FMT_Uint32	Com_Write(t_FMT_Uint32 uiDeviceId,t_FMT_Uint8 *pucBuf,t_FMT_Uint32 uiSize);

    //! Read dwSize bytes from the port
    t_FMT_Uint32	Com_Read(t_FMT_Uint32 uiDeviceId,t_FMT_Uint8 *pucBuf,t_FMT_Uint32 uiSize,t_FMT_Uint32& uiReadSize);

    //! Return the port output buffer
    t_FMT_Uint32	Com_ResetWriteBuffer(t_FMT_Uint32 uiDeviceId);

    //! Return the number of bytes stored into the COM
    t_FMT_Uint32	Com_GetReadBufferBytes(t_FMT_Uint32 uiDeviceId,t_FMT_Uint32& uiNob);

    //! Reset the port input buffer
    t_FMT_Uint32	Com_ResetReadBuffer(t_FMT_Uint32 uiDeviceId);

	//! Extract REG_MULTI_SZ strings
	void			ExtractRegMultiSz(TCHAR *ptchString, CFMT_StringVector& StringVect, t_FMT_Uint32 uiMaxLen);

public:

    //! Open the device
    virtual t_FMT_Uint32	Open(t_FMT_Uint32 uiDeviceId);

    //! Close the device
    virtual t_FMT_Uint32	Close(t_FMT_Uint32 uiDeviceId);

    //! Perform actions after COM opening
    virtual t_FMT_Uint32	OnOpening(t_FMT_Uint32 uiDeviceId);

    //! Perform actions before COM closing
    virtual t_FMT_Uint32	OnClosing(t_FMT_Uint32 uiDeviceId);

};



#endif







