// =====================================================================================
/**
 * @file					FMT_HdwStdUartDevice.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					10/01/2020
 * @brief					Standard UARTs device
 *
 * @version	Project:		Formatech C++ Core Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][10/01/2020]
 */
// =====================================================================================



#ifndef FMTDEF_HDW_STDUARTDEVICE_H
#define FMTDEF_HDW_STDUARTDEVICE_H

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
//	Class CUart
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CUart : public CFMT_HdwObject
{
    // =====================================================================================
    //	TYPES
    // =====================================================================================
protected:
public:

    // =====================================================================================
    //	VARIABLES
    // =====================================================================================

protected:
public:

    #ifdef FMTDEF_COMPILE_OS_WINDOWS
    HANDLE                          m_hComDev;              //! Device Handle
    OVERLAPPED                      m_osWrite;              //! Overlapper Write
    OVERLAPPED                      m_osRead;               //! Overlapper Read
    t_FMT_Uint32                    m_uiInputBufferSize;    //! Input Buffer Size
    t_FMT_Uint32                    m_uiOutputBufferSize;   //! Input Buffer Size
    #endif

    #ifdef FMTDEF_COMPILE_OS_LINUX
    t_FMT_Int32                     m_iFileDesc;
    #endif

    CFMT_HdwUartPort::CParameters   m_Param;                //! UART Parameters


    // =====================================================================================
    // CONSTRUCTORS & DESTRUCTORS
    // =====================================================================================

public:

    CUart();

    //! Open the port
    virtual t_FMT_Uint32		Open(const CFMT_String& sCom, CFMT_HdwUartPort::CParameters *pParam);

    //! Close the port
    virtual t_FMT_Uint32		Close();

    #ifdef FMTDEF_COMPILE_OS_LINUX
    t_FMT_Int32                 TranslateBaudRate(t_FMT_Uint32 inrate);

    //! Return the standard baud rate if applicable.
    t_FMT_Uint32                SetBaudRate(t_FMT_Uint32 uiBaud);
    #endif

    //! Change the port parity
    t_FMT_Uint32                SetParity(t_FMT_Uint8 ucParity);

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




// *************************************************************************************
// *************************************************************************************
//	Class CFMT_HdwStdUartDevice
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_HdwStdUartDevice : public CFMT_HdwDevice
{
// =====================================================================================
//	TYPES
// =====================================================================================

protected:

    // --- CUartByteInBufferService --------------------------------------------------------------

    class FMTDEF_LIB_DLLSPEC CUartByteInBufferService : public CFMT_HdwByteInBufferService
    {
    public:

        friend class CUartPort;

        CUartByteInBufferService(CFMT_HdwObject *pPort);

        //! Start the service
        virtual t_FMT_Uint32		Start();

        //! Read dwSize bytes from the input buffer
        virtual t_FMT_Uint32		Read(t_FMT_Uint8 *pbtBuf,t_FMT_Uint32 dwSize,t_FMT_Uint32& dwReadSize);

        //! Return the number of bytes stored into input buffer
        virtual t_FMT_Uint32		GetReadBufferBytes(t_FMT_Uint32& uiNob);
        virtual t_FMT_Uint32		ResetReadBuffer();

    };

    // --- CUartByteOutBufferService --------------------------------------------------------------

    class FMTDEF_LIB_DLLSPEC CUartByteOutBufferService : public CFMT_HdwByteOutBufferService
    {
    public:

        friend class CUartPort;

        CUartByteOutBufferService(CFMT_HdwObject *pPort);

        //! Start the service
        virtual t_FMT_Uint32		Start();

        //! Write dwSize bytes to the output buffer
        virtual t_FMT_Uint32		Write(t_FMT_Uint8 *pbtBuf,t_FMT_Uint32 dwSize,t_FMT_Uint32 dwTimeout);

        //! Return the number of bytes stored into output buffer
        virtual t_FMT_Uint32		GetBytesToBeWritten(t_FMT_Uint32& uiNob);

        //! Reset the output buffer
        virtual t_FMT_Uint32		ResetWriteBuffer();

    };


    // --- CUartPort --------------------------------------------------------------

    class FMTDEF_LIB_DLLSPEC CUartPort : public CFMT_HdwUartPort
    {
    protected:

        CUart                       m_Uart;


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
        virtual t_FMT_Uint32		EnableService(t_FMT_Uint32 dwServiceType,CFMT_HdwService **ppService,CFMT_HdwService::CParameters *pParam= FMTDEF_NULL);

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


    // =====================================================================================
    //	VARIABLES
    // =====================================================================================

protected:
public:

// =====================================================================================
// CONSTRUCTORS & DESTRUCTORS
// =====================================================================================

public:

    //! Empty constructor
    CFMT_HdwStdUartDevice();

    //! Destructor
    virtual ~CFMT_HdwStdUartDevice();


// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:

    //! Enumerates the installed system UART ports.
    t_FMT_Uint32			EnumUartPortList(CPortDescriptorsList& list);

    #ifdef FMTDEF_COMPILE_OS_WINDOWS
    t_FMT_Uint32			EnumWindowsLegacyUartPortList(CPortDescriptorsList& list);
    t_FMT_Uint32			EnumWindowsMoxaUartPortList(CPortDescriptorsList& list);
    #endif

    #ifdef FMTDEF_COMPILE_OS_LINUX
    t_FMT_Uint32            EnumLinuxLegacyUartPortList(CPortDescriptorsList& list);
    t_FMT_Uint32            GetChannelFromPath(const CFMT_String& sPath, CFMT_String& sSN);
    void                    GetSerialNumberFromPath(const CFMT_String& sPath, t_FMT_Uint32 pos, CFMT_String& sChannel);
    t_FMT_Uint32            IdentifyFtdiDevice(CPortDescriptor& pd);
    t_FMT_Uint32            IdentifyUnknownDevice(CPortDescriptor& pd);
    #endif

    //! Initialize and enumerates the UART ports.
    t_FMT_Uint32			InitUartPortList();

public:

    //! Initialize the device
    virtual	t_FMT_Uint32	Init(t_FMT_Uint32 dwTotalPortTypes = CFMT_HdwPort::e_PortType_Total);
};





#endif







