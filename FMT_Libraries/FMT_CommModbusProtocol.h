// =====================================================================================
/**
 * @file					FMT_CommModbusProtocol.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					28/06/2022
 * @brief					MODBUS base protocol
 *
 * @version	Project:		Formatech C++ Communication Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][28/06/2022]
 */
// =====================================================================================


#ifndef FMTDEF_COMM_MODBUSPROTOCOL_H
#define FMTDEF_COMM_MODBUSPROTOCOL_H


// =====================================================================================
//	INCLUDES
// =====================================================================================


#ifndef FMTDEF_CORE_H
#include "FMT_Core.h"
#endif

#ifndef FMTDEF_HDW_H
#include "FMT_Hdw.h"
#endif

#ifndef FMTDEF_COMM_OBJECT_H
#include "FMT_CommObject.h"
#endif


// =====================================================================================
//	DEFINES
// =====================================================================================


#define FMTDEF_COMM_MODBUS_RXBUFFERSIZE					0x10000
#define FMTDEF_COMM_MODBUS_TXBUFFERSIZE					0x10000

#define FMTDEF_COMM_MODBUS_MSG_LENGTH_UNDEFINED			(-1)


#ifdef FMTDEF_COMPILE_OS_WINDOWS
#define FMTDEF_COMM_MODBUS_THREAD                       HANDLE
#endif

#ifdef FMTDEF_COMPILE_OS_LINUX
#define FMTDEF_COMM_MODBUS_THREAD                       pthread_t
#endif


// *************************************************************************************
// *************************************************************************************
//	Class CFMT_CommModbusProtocol
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_CommModbusProtocol : public CFMT_HdwProtocol, public CFMT_CommObject
{
	// =====================================================================================
	//	TYPES
	// =====================================================================================


protected:

    // --- RX States --------------------------------

    enum t_RxState
    {
        e_RxState_Function	= 0,
        e_RxState_Meta		= 1,
        e_RxState_Data		= 2
    };


    // --- Message Type -----------------------------

    enum t_MsgType
    {
        e_MsgType_Indication        = 0,
        e_MsgType_Confirmation      = 1
    };


    // --- Function Codes ----------------------------

    enum t_FunctionCode
    {
        e_FunctionCode_ReadCoils						= 0x01,
        e_FunctionCode_ReadDiscreteInputs				= 0x02,
        e_FunctionCode_ReadHoldingRegisters				= 0x03,
        e_FunctionCode_ReadInputRegisters				= 0x04,
        e_FunctionCode_WriteSingleCoil					= 0x05,
        e_FunctionCode_WriteSingleRegister				= 0x06,
        e_FunctionCode_ReadExceptionStatus				= 0x07,
        e_FunctionCode_Diagnostics						= 0x08,
		e_FunctionCode_GetCommEventCounter				= 0x0B,
		e_FunctionCode_GetCommEventLog					= 0x0C,
        e_FunctionCode_WriteMultipleCoils				= 0x0F,
        e_FunctionCode_WriteMultipleRegisters			= 0x10,
        e_FunctionCode_ReportServerID					= 0x11,
        e_FunctionCode_ReadFileRecord					= 0x14,
        e_FunctionCode_WriteFileRecord					= 0x15,
        e_FunctionCode_MaskWriteRegister				= 0x16,
        e_FunctionCode_WriteAndReadRegisters			= 0x17,
        e_FunctionCode_ReadFifoQueue					= 0x18,

        e_FunctionCode_Total							= 0x80
	};


    // --- Protocol exceptions ------------------------------
    enum t_Exceptions
    {
        e_Exception_OK							= 0x00,

        e_Exception_IllegalFunction             = 0x01,
        e_Exception_IllegalDataAddress          = 0x02,
        e_Exception_IllegalDataValue            = 0x03,
        e_Exception_SlaveOrServerFailure        = 0x04,
        e_Exception_Acknowledge                 = 0x05,
        e_Exception_SlaveOrServerBusy           = 0x06,
        e_Exception_NegativeAcknowledge         = 0x07,
        e_Exception_MemoryParity                = 0x08,
        e_Exception_NotDefined                  = 0x09,
        e_Exception_GatewayPath                 = 0x0A,
        e_Exception_GatewayTarget               = 0x0B,

        e_Exception_Tot                         = 0x0C
    };


public:

    class FMTDEF_LIB_DLLSPEC CFileRecGroup
    {
    public:
        t_FMT_Uint16        m_usFileNum;
        t_FMT_Uint16        m_usRecNum;
        CFMT_Uint16Vector   m_vusData;

        CFileRecGroup();

		//! Comparison operator
		t_FMT_Bool		operator==(const CFileRecGroup& op);

		//! Comparison operator
		t_FMT_Bool		operator!=(const CFileRecGroup& op);

		FMTDEF_LIB_DLLSPEC friend CFMT_Buffer& operator<<(CFMT_Buffer& buf, CFileRecGroup& m);
		FMTDEF_LIB_DLLSPEC friend CFMT_Buffer& operator>>(CFMT_Buffer& buf, CFileRecGroup& m);
	};

    class FMTDEF_LIB_DLLSPEC CFileRecGroupList : public CFMT_List<CFileRecGroup>
    {
    };

    class FMTDEF_LIB_DLLSPEC CFileRecGroupVector : public CFMT_Vector<CFileRecGroup>
    {
	public:

		//! Assignment from an homogeneous list
		CFileRecGroupVector& operator=(CFileRecGroupList& op);
		CFileRecGroupVector& operator=(CFMT_List<CFileRecGroup>& op);
    };


	// =====================================================================================
	//	VARIABLES
	// =====================================================================================

private:


protected:

    // Byte I/O Service
    CFMT_HdwByteInBufferService     *m_pInService;
    CFMT_HdwByteOutBufferService    *m_pOutService;

    // Header Length
    t_FMT_Uint32                    m_uiHeaderLength;

    // Checksum Length
    t_FMT_Uint32                    m_uiChecksumLength;

    // RX Buffer
    t_FMT_Uint8                     *m_pucRxBuf;

    // RX Bytes
    t_FMT_Uint32                    m_uiRxBytes;

	// TX Buffer
    t_FMT_Uint8                     *m_pucTxBuf;

    // TX Bytes
    t_FMT_Uint32                    m_uiTxBytes;
	
	// RX State
    t_RxState                       m_RxState;

    // Total RX META Bytes
    t_FMT_Uint8                     m_ucRxMetaLength;

    // Total RX DATA Bytes
    t_FMT_Uint32                    m_uiRxDataLength;

    // Received Slave identifier
    t_FMT_Uint8                     m_ucRxSlave;

    // Received Function
    t_FMT_Uint32                    m_ucRxFunction;

    // Received Address
    t_FMT_Uint16                    m_usRxAddress;


public:

	// =====================================================================================
	// CONSTRUCTORS & DESTRUCTORS
	// =====================================================================================

public:
	
    CFMT_CommModbusProtocol();
    virtual ~CFMT_CommModbusProtocol();

	// =====================================================================================
	//	FUNCTIONS
	// =====================================================================================

protected:

    // Reset reception parameters
    void					ResetRxParameters();

	// Sends a request/response
	virtual t_FMT_Uint32	SendMsg();


#if 0
	// *** NON CANCELLARE FINO A QUANDO NON SPOSTATA LA VERSIONE "CONFIRMATION" SU MASTER ***

    // Prepare the response TID
	// *** NON CANCELLARE FINO A QUANDO NON SPOSTATA SU MASTER /  TCP ***
    virtual t_FMT_Uint16    PrepareResponseTid(t_FMT_Uint8 *req, t_FMT_Uint32 *req_length);

	// Check confirmation packet
	virtual t_FMT_Uint32	CheckConfirmation(t_FMT_Uint8 *pucExcCode);

	// Preliminary Check confirmation packet
	virtual t_FMT_Uint32	PreCheckConfirmation();
	#endif



public:

    // Mount the protocol on an I/O Service
    virtual t_FMT_Uint32	Mount(CFMT_HdwByteInBufferService *pInService, CFMT_HdwByteOutBufferService *pOutService);
};

#endif

