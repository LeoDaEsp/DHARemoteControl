// =====================================================================================
/**
 * @file					FMT_CommModbusSlaveProtocol.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					28/06/2022
 * @brief					MODBUS Slave Protocol implementations
 *
 * @version	Project:		Formatech C++ Communication Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][28/06/2022]
 */
// =====================================================================================


#ifndef FMTDEF_COMM_MODBUSSLAVEPROTOCOL_H
#define FMTDEF_COMM_MODBUSSLAVEPROTOCOL_H


// =====================================================================================
//	INCLUDES
// =====================================================================================


#ifndef FMTDEF_CORE_H
#include "FMT_Core.h"
#endif

#ifndef FMTDEF_HDW_H
#include "FMT_Hdw.h"
#endif

#ifndef FMTDEF_COMM_TCP_SERVER_H
#include "FMT_CommTcpServer.h"
#endif

#ifndef FMTDEF_COMM_MODBUSPROTOCOL_H
#include "FMT_CommModbusProtocol.h"
#endif


// =====================================================================================
//	DEFINES
// =====================================================================================

#define FMTDEF_COMM_MODBUSRCUSLAVE_DEFAULT_TIMEOUT			500

#define FMTDEF_COMM_MODBUS_TCP_DEFAULT_PORT                 502


// *************************************************************************************
// *************************************************************************************
//	Class CFMT_CommModbusSlaveProtocol
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_CommModbusSlaveProtocol : public CFMT_CommModbusProtocol
{
	// =====================================================================================
	//	TYPES
	// =====================================================================================


protected:
public:

	// =====================================================================================
	//	VARIABLES
	// =====================================================================================

private:
protected:

	// CRC object
	CFMT_Crc				m_Crc;

	// Function Enable flags
	t_FMT_Bool				m_pbFunctionEnables[e_FunctionCode_Total];

public:

	// Slave Address
	t_FMT_Uint8				m_ucSlaveIdentifier;

	// Maximum number of read bits for command
	t_FMT_Uint32			m_uiMaxReadBits;

	// Maximum number of read registers for command
	t_FMT_Uint32			m_uiMaxReadRegisters;

	// Maximum number of write bits for command
	t_FMT_Uint32			m_uiMaxWriteBits;

	// Maximum number of write registers for command
	t_FMT_Uint32			m_uiMaxWriteRegisters;

	// Maximum number of read/write registers for command
	t_FMT_Uint32			m_uiMaxRwWriteRegisters;


	// =====================================================================================
	// CONSTRUCTORS & DESTRUCTORS
	// =====================================================================================

public:
	
    CFMT_CommModbusSlaveProtocol();
    virtual ~CFMT_CommModbusSlaveProtocol();

	// =====================================================================================
	//	FUNCTIONS
	// =====================================================================================

protected:

    // Check if the request correctly address the slave
    virtual t_FMT_Uint32		IsAddressed(t_FMT_Uint8 ucSlave);

    // Computes the length to read after the function received
    virtual t_FMT_Uint8			ComputeMetaLengthAfterFunction();

    // Computes the length to read after the meta information
    virtual t_FMT_Int32			ComputeDataLengthAfterMeta();

    // Builds Response header
	virtual t_FMT_Uint32		BuildResponseBasis();

	// Build the exception response
    virtual t_FMT_Uint32		BuildResponseException(t_FMT_Uint8 ucExcCode);

	// Extract the header parameters
	virtual void				ExtractHeaderParameter();

	// Check message integrity
	virtual t_FMT_Uint32		CheckIntegrity(t_FMT_Uint8 *pucMsg, t_FMT_Uint32 uiMsgSize);

    // Process the received RX Function
    t_FMT_Uint32				ProcessRxFunction();

	// Build a response of bits functions
	t_FMT_Uint32				BuildResponseIoStatus(t_FMT_Uint16 usNb, t_FMT_Bool *pbBits, t_FMT_Uint32 uiOffset);

	// Build a response of bits functions
	void						ExtractBits(t_FMT_Uint8 *pucBuf, t_FMT_Uint16 usNumBits, t_FMT_Bool *pbBits);

	// Builds Response footer
	virtual void				BuildResponseFooter();

	// Computes the length to read after the user function received
	virtual t_FMT_Uint8			UserComputeMetaLengthAfterFunction(t_FMT_Uint8 ucFunction);

    // Computes the length to read after the meta information of user function
    virtual t_FMT_Int32			UserComputeDataLengthAfterMeta(t_FMT_Uint8 ucFunction);

    // Process the received User Function
    virtual t_FMT_Uint32		ProcessUserFunction();

public:

    // Receive the response from a modbus slave
    virtual t_FMT_Uint32		Receive(t_FMT_Uint64 quiTimeout);

	// Process a Read Coils function
	virtual t_FMT_Uint32		ReadCoils(t_FMT_Uint16 usAddress, t_FMT_Uint16 usNumbits, t_FMT_Bool *pbCoils);

	// Process a Read Discrete Inputs function
	virtual t_FMT_Uint32		ReadDiscreteInputs(t_FMT_Uint16 usAddress, t_FMT_Uint16 usNumbits, t_FMT_Bool *pbDin);

	// Process a Read Input Registers function
	virtual t_FMT_Uint32		ReadInputRegisters(t_FMT_Uint16 usAddress, t_FMT_Uint16 usNumRegs, t_FMT_Uint16 *pusReg);

	// Process a Read Holding Registers function
	virtual t_FMT_Uint32		ReadHoldingRegisters(t_FMT_Uint16 usAddress, t_FMT_Uint16 usNumRegs, t_FMT_Uint16 *pusReg);

	// Process a Read FIFO Queue function
	virtual t_FMT_Uint32		ReadFifoQueue(t_FMT_Uint16 usFifoPointerAddress, CFMT_Uint16Vector& vReadData);
	
	// Process a Read Exception Status function
	virtual t_FMT_Uint32		ReadExceptionStatus(t_FMT_Uint8 *pucCodes);

	// Process a Write Single Coil function
	virtual t_FMT_Uint32		WriteSingleCoil(t_FMT_Uint16 usAddress, t_FMT_Bool bValue);

	// Process a Write Single Register function
	virtual t_FMT_Uint32		WriteSingleRegister(t_FMT_Uint16 usAddress, t_FMT_Uint16 usValue);

	// Process a Write Multiple Coils function
	virtual t_FMT_Uint32		WriteMultipleCoils(t_FMT_Uint16 usAddress, t_FMT_Uint16 usNumBits, t_FMT_Bool *pbCoils);

	// Process a Write Multiple Registers function
	virtual t_FMT_Uint32		WriteMultipleRegisters(t_FMT_Uint16 usAddress, t_FMT_Uint16 usNumRegs, t_FMT_Uint16 *pusRegs);

    // Process a Mask Write Register function
    virtual t_FMT_Uint32		MaskWriteRegister(t_FMT_Uint16 usAddress, t_FMT_Uint16 usAndMask, t_FMT_Uint16 usOrMask);

    // Process a Write and Read Registers function
	virtual t_FMT_Uint32		WriteAndReadRegisters(t_FMT_Uint16 usWAddress, t_FMT_Uint16 usNumWRegs, t_FMT_Uint16 usRAddress, t_FMT_Uint16 usNumRRegs, 
													t_FMT_Uint16 *pusWRegs, t_FMT_Uint16 *pusRRegs);

	// Process a Communication Event Counter function
	virtual t_FMT_Uint32		GetCommEventCounter(t_FMT_Uint16 &usStatus, t_FMT_Uint16 &usEventCnt); 

	// Process a Communication Event Log function
	virtual t_FMT_Uint32		GetCommEventLog(t_FMT_Uint16 &usStatus, t_FMT_Uint16 &usEventCnt, t_FMT_Uint16 &usMessCount, CFMT_Uint8Vector& vEvents); 

    // Process a multiple Write File Record function
    virtual t_FMT_Uint32		WriteFileRecord(CFileRecGroupVector& Groups);

    // Process a multiple Read File Record function
    virtual t_FMT_Uint32		ReadFileRecord(CFileRecGroupVector& Groups);


};



// *************************************************************************************
// *************************************************************************************
//	Class CFMT_CommModbusRtuSlaveProtocol
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_CommModbusRtuSlaveProtocol : public CFMT_CommModbusSlaveProtocol
{
	// =====================================================================================
	//	TYPES
	// =====================================================================================


protected:
public:

	// =====================================================================================
	//	VARIABLES
	// =====================================================================================

private:
protected:

public:



	// =====================================================================================
	// CONSTRUCTORS & DESTRUCTORS
	// =====================================================================================

public:
	
    CFMT_CommModbusRtuSlaveProtocol();
    virtual ~CFMT_CommModbusRtuSlaveProtocol();

	// =====================================================================================
	//	FUNCTIONS
	// =====================================================================================

protected:

    // Builds Response header
	virtual t_FMT_Uint32		BuildResponseBasis();

	// Extract the header parameters
	virtual void				ExtractHeaderParameter();

	// Check message integrity
	virtual t_FMT_Uint32		CheckIntegrity(t_FMT_Uint8 *pucMsg, t_FMT_Uint32 uiMsgSize);

	// Builds Response footer
	virtual void				BuildResponseFooter();


public:

};


// *************************************************************************************
// *************************************************************************************
//	Class CFMT_CommModbusTcpSlaveProtocol
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_CommModbusTcpSlaveProtocol : public CFMT_CommModbusSlaveProtocol
{
    // =====================================================================================
    //	TYPES
    // =====================================================================================


protected:
public:

    // =====================================================================================
    //	VARIABLES
    // =====================================================================================

private:
protected:

    // Received TID
    t_FMT_Uint16                    m_usRxTid;

    // Received Protocol Identifier
    t_FMT_Uint16                    m_usRxProtocolId;

    // Received Packet Length
    t_FMT_Uint16                    m_usRxLength;

public:

    // =====================================================================================
    // CONSTRUCTORS & DESTRUCTORS
    // =====================================================================================

public:

    CFMT_CommModbusTcpSlaveProtocol();
    virtual ~CFMT_CommModbusTcpSlaveProtocol();

    // =====================================================================================
    //	FUNCTIONS
    // =====================================================================================

protected:

    // Builds Response header
    virtual t_FMT_Uint32		BuildResponseBasis();

    // Extract the header parameters
    virtual void				ExtractHeaderParameter();

    // Check message integrity
    virtual t_FMT_Uint32		CheckIntegrity(t_FMT_Uint8 *pucMsg, t_FMT_Uint32 uiMsgSize);

    // Builds Response footer
    virtual void				BuildResponseFooter();

    // Check if the request correctly address the slave
    virtual t_FMT_Uint32		IsAddressed(t_FMT_Uint8 ucSlave);

public:

};


// *************************************************************************************
// *************************************************************************************
//	Class CFMT_CommModbusTcpServer
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_CommModbusTcpServer : public CFMT_CommTcpServer
{
    // =====================================================================================
    //	TYPES
    // =====================================================================================

protected:

    // ---[ CModbusTcpOutService ] ----------------------------------

    class FMTDEF_LIB_DLLSPEC CModbusTcpOutService : public CFMT_HdwByteOutBufferService
    {
    public:

        CFMT_HdwTcpServerSocket::CConnectedSocket       *m_pSocket;

        CModbusTcpOutService(CFMT_HdwTcpServerSocket::CConnectedSocket *pSocket);

        virtual t_FMT_Uint32		Write(t_FMT_Uint8 *pbtBuf,t_FMT_Uint32 dwSize,t_FMT_Uint32 dwTimeout);
        virtual t_FMT_Uint32		ResetWriteBuffer();
    };

    // ---[ CModbusTcpInService ] ----------------------------------

    class FMTDEF_LIB_DLLSPEC CModbusTcpInService : public CFMT_HdwByteInBufferService
    {
    public:
        CFMT_HdwTcpServerSocket::CConnectedSocket       *m_pSocket;

        CModbusTcpInService(CFMT_HdwTcpServerSocket::CConnectedSocket *pSocket);

        virtual t_FMT_Uint32		Read(t_FMT_Uint8 *pbtBuf, t_FMT_Uint32 dwSize, t_FMT_Uint32& dwReadSize);
        virtual t_FMT_Uint32		ResetReadBuffer();
    };


    // ---[ CModbusTcpSlaveProtocol ] ----------------------------------

    class FMTDEF_LIB_DLLSPEC CModbusTcpSlaveProtocol : public CFMT_CommModbusTcpSlaveProtocol
    {
        friend class CFMT_CommModbusTcpServer;

    public:
        // Modbus Server
        CFMT_CommModbusTcpServer    *m_pServer;

        // Process a Read Coils function
        virtual t_FMT_Uint32		ReadCoils(t_FMT_Uint16 usAddress, t_FMT_Uint16 usNumbits, t_FMT_Bool *pbCoils);

        // Process a Read Discrete Inputs function
        virtual t_FMT_Uint32		ReadDiscreteInputs(t_FMT_Uint16 usAddress, t_FMT_Uint16 usNumbits, t_FMT_Bool *pbDin);

        // Process a Read Input Registers function
        virtual t_FMT_Uint32		ReadInputRegisters(t_FMT_Uint16 usAddress, t_FMT_Uint16 usNumRegs, t_FMT_Uint16 *pusReg);

        // Process a Read Holding Registers function
        virtual t_FMT_Uint32		ReadHoldingRegisters(t_FMT_Uint16 usAddress, t_FMT_Uint16 usNumRegs, t_FMT_Uint16 *pusReg);

        // Process a Read FIFO Queue function
        virtual t_FMT_Uint32		ReadFifoQueue(t_FMT_Uint16 usFifoPointerAddress, CFMT_Uint16Vector& vReadData);

        // Process a Write Single Coil function
        virtual t_FMT_Uint32		WriteSingleCoil(t_FMT_Uint16 usAddress, t_FMT_Bool bValue);

        // Process a Write Single Register function
        virtual t_FMT_Uint32		WriteSingleRegister(t_FMT_Uint16 usAddress, t_FMT_Uint16 usValue);

        // Process a Write Multiple Coils function
        virtual t_FMT_Uint32		WriteMultipleCoils(t_FMT_Uint16 usAddress, t_FMT_Uint16 usNumBits, t_FMT_Bool *pbCoils);

        // Process a Write Multiple Registers function
        virtual t_FMT_Uint32		WriteMultipleRegisters(t_FMT_Uint16 usAddress, t_FMT_Uint16 usNumRegs, t_FMT_Uint16 *pusRegs);

        // Process a Mask Write Register function
        virtual t_FMT_Uint32		MaskWriteRegister(t_FMT_Uint16 usAddress, t_FMT_Uint16 usAndMask, t_FMT_Uint16 usOrMask);

        // Process a Write and Read Registers function
        virtual t_FMT_Uint32		WriteAndReadRegisters(t_FMT_Uint16 usWAddress, t_FMT_Uint16 usNumWRegs, t_FMT_Uint16 usRAddress, t_FMT_Uint16 usNumRRegs,
                                                        t_FMT_Uint16 *pusWRegs, t_FMT_Uint16 *pusRRegs);

        // Process a multiple Write File Record function
        virtual t_FMT_Uint32		WriteFileRecord(CFileRecGroupVector& Groups);

        // Process a multiple Read File Record function
        virtual t_FMT_Uint32		ReadFileRecord(CFileRecGroupVector& Groups);
    };


    // ---[ CModbusTcpClient ] ----------------------------------

    class FMTDEF_LIB_DLLSPEC CModbusTcpClient : public CClient
    {
        friend class CFMT_CommModbusTcpServer;

    public:

        CModbusTcpOutService            *m_pOutService;
        CModbusTcpInService             *m_pInService;
        CModbusTcpSlaveProtocol         m_ModbusSlaveProt;

        // Constructor
        CModbusTcpClient();

        // Destructor
        virtual ~CModbusTcpClient();

        // Client Thread Actions
        virtual t_FMT_Uint32            ClientActions();

        // Client Start Actions
        virtual t_FMT_Uint32            StartActions();

        // Client Stop Actions
        virtual void                    StopActions();
    };


public:

    // =====================================================================================
    //	VARIABLES
    // =====================================================================================

private:
protected:


public:

    // =====================================================================================
    // CONSTRUCTORS & DESTRUCTORS
    // =====================================================================================

public:

    CFMT_CommModbusTcpServer();
    virtual ~CFMT_CommModbusTcpServer();

    // =====================================================================================
    //	FUNCTIONS
    // =====================================================================================

protected:

    // Get a new client
    virtual CClient*            GetNewClient();

public:

    // Start Server
    virtual t_FMT_Uint32        StartServer();

    // Process a Read Coils function
    virtual t_FMT_Uint32		ReadCoils(t_FMT_Uint16 usAddress, t_FMT_Uint16 usNumbits, t_FMT_Bool *pbCoils);

    // Process a Read Discrete Inputs function
    virtual t_FMT_Uint32		ReadDiscreteInputs(t_FMT_Uint16 usAddress, t_FMT_Uint16 usNumbits, t_FMT_Bool *pbDin);

    // Process a Read Input Registers function
    virtual t_FMT_Uint32		ReadInputRegisters(t_FMT_Uint16 usAddress, t_FMT_Uint16 usNumRegs, t_FMT_Uint16 *pusReg);

    // Process a Read Holding Registers function
    virtual t_FMT_Uint32		ReadHoldingRegisters(t_FMT_Uint16 usAddress, t_FMT_Uint16 usNumRegs, t_FMT_Uint16 *pusReg);

    // Process a Read FIFO Queue function
    virtual t_FMT_Uint32		ReadFifoQueue(t_FMT_Uint16 usFifoPointerAddress, CFMT_Uint16Vector& vReadData);

    // Process a Write Single Coil function
    virtual t_FMT_Uint32		WriteSingleCoil(t_FMT_Uint16 usAddress, t_FMT_Bool bValue);

    // Process a Write Single Register function
    virtual t_FMT_Uint32		WriteSingleRegister(t_FMT_Uint16 usAddress, t_FMT_Uint16 usValue);

    // Process a Write Multiple Coils function
    virtual t_FMT_Uint32		WriteMultipleCoils(t_FMT_Uint16 usAddress, t_FMT_Uint16 usNumBits, t_FMT_Bool *pbCoils);

    // Process a Write Multiple Registers function
    virtual t_FMT_Uint32		WriteMultipleRegisters(t_FMT_Uint16 usAddress, t_FMT_Uint16 usNumRegs, t_FMT_Uint16 *pusRegs);

    // Process a Mask Write Register function
    virtual t_FMT_Uint32		MaskWriteRegister(t_FMT_Uint16 usAddress, t_FMT_Uint16 usAndMask, t_FMT_Uint16 usOrMask);

    // Process a Write and Read Registers function
    virtual t_FMT_Uint32		WriteAndReadRegisters(t_FMT_Uint16 usWAddress, t_FMT_Uint16 usNumWRegs, t_FMT_Uint16 usRAddress, t_FMT_Uint16 usNumRRegs,
                                                    t_FMT_Uint16 *pusWRegs, t_FMT_Uint16 *pusRRegs);

    // Process a multiple Write File Record function
    virtual t_FMT_Uint32		WriteFileRecord(CFMT_CommModbusSlaveProtocol::CFileRecGroupVector& Groups);

    // Process a multiple Read File Record function
    virtual t_FMT_Uint32		ReadFileRecord(CFMT_CommModbusSlaveProtocol::CFileRecGroupVector& Groups);
};


#endif

