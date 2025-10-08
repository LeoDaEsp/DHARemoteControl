// =====================================================================================
/**
 * @file					FMT_HdwUartPort.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					10/01/2020
 * @brief					Abstract Hardware UART Port
 *
 * @version	Project:		Formatech C++ Core Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][10/01/2020]
 */
// =====================================================================================



#ifndef FMTDEF_HDW_UARTPORT_H
#define FMTDEF_HDW_UARTPORT_H

// =====================================================================================
//	INCLUDES
// =====================================================================================


#ifndef FMTDEF_CORE_H
#include "FMT_Core.h"
#endif

#ifndef FMTDEF_HDW_OBJECT_H
#include "FMT_HdwObject.h"
#endif

#ifndef FMTDEF_HDW_PORT_H
#include "FMT_HdwPort.h"
#endif

// =====================================================================================
//	DEFINES
// =====================================================================================

#define FMTDEF_HDW_UARTPORT_PORTNUM_INVALID         0


// *************************************************************************************
// *************************************************************************************
//	Class CFMT_HdwUartPort
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_HdwUartPort : public CFMT_HdwPort
{
// =====================================================================================
//	TYPES
// =====================================================================================

protected:
public:

    // --- t_Parity ----------------------------------------------------

    enum t_Parity
    {
        e_Parity_NoParity		= 0,
        e_Parity_Odd			= 1,
        e_Parity_Even			= 2,
        e_Parity_Mark			= 3,
        e_Parity_Space			= 4
    };

    // --- t_StopBits ----------------------------------------------------

    enum t_StopBits
    {
        e_StopBits_1Bit			= 0,
        e_StopBits_1p5Bit		= 1,
        e_StopBits_2Bits		= 2
    };

    // --- t_FlowControl ----------------------------------------------------

    enum t_FlowControl
    {
        e_FlowControl_NoControl		= 0x00,
        e_FlowControl_DtrDsr		= 0x01,
        e_FlowControl_RtsCts		= 0x02,
        e_FlowControl_XonXoff		= 0x04
    };

    // --- t_AsciiChars ----------------------------------------------------

    enum t_AsciiChars
    {
        e_AsciiChars_BEL			= 0x07,
        e_AsciiChars_BS				= 0x08,
        e_AsciiChars_LF				= 0x0A,
        e_AsciiChars_CR				= 0x0D,
        e_AsciiChars_XON			= 0x11,
        e_AsciiChars_XOFF			= 0x13
    };

    // --- t_Interface ----------------------------------------------------

    enum t_Interface
    {
        e_Interface_Default			= 0x00,
        e_Interface_Rs232			= 0x01,
        e_Interface_Rs422			= 0x02,
        e_Interface_Rs485			= 0x03,
        e_Interface_Ttl				= 0x04
    };


    // --- CParameters ----------------------------------------------------

    class FMTDEF_LIB_DLLSPEC CParameters : public CFMT_HdwPort::CParameters
    {
    public:

        t_FMT_Uint8			m_ucParity;						//! UART Parity
        t_FMT_Uint8			m_ucStopBits;					//! UART Stop Bits
        t_FMT_Uint32		m_uiBaudRate;					//! UART Baud Rate
        t_FMT_Uint8			m_ucByteSize;					//! UART Byte Size
        t_FMT_Uint8			m_ucFlowCtrl;					//! UART Flow Control
		t_Interface			m_Interface;					//! UART Interface Type
		t_FMT_Bool			m_bUseTerminationResistor;		//! Use Termination Resistor
		t_FMT_Bool			m_bUseBusPolarization;			//! Use Bus Polarization
		t_FMT_Uint32		m_uiLatencyTimer;				//! Latency Timer in ms

        CParameters();
    };


    // =====================================================================================
    //	VARIABLES
    // =====================================================================================

protected:

    CParameters					m_Parameters;       //! Port Parameters

public:

// =====================================================================================
// CONSTRUCTORS & DESTRUCTORS
// =====================================================================================

public:

    //! Empty constructor
    CFMT_HdwUartPort(CFMT_HdwObject *pDevice, t_FMT_Uint32 uiDeviceId, const CFMT_String& sChannelId);

    //! Destructor
    virtual ~CFMT_HdwUartPort();


// =====================================================================================
// FUNCTIONS
// =====================================================================================

protected:
public:

    //! Open the port
    virtual t_FMT_Uint32		Open(CFMT_HdwPort::CParameters *pParameters);

    //! Close the port
    virtual t_FMT_Uint32		Close();

    //! Enable a service on the port
    virtual t_FMT_Uint32		EnableService(t_FMT_Uint32 dwServiceType, CFMT_HdwService **ppService, CFMT_HdwService::CParameters *pParam = FMTDEF_NULL);

    //! Return the port parameters
    virtual t_FMT_Uint32		GetParameters(CParameters *pParameters);

    //! Change the port parity
    virtual t_FMT_Uint32		SetParity(t_FMT_Uint8 ucParity);

};



#endif







