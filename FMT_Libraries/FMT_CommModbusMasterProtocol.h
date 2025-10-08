// =====================================================================================
/**
 * @file					FMT_CommModbusMaster.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					28/06/2022
 * @brief					MODBUS Master implementations
 *
 * @version	Project:		Formatech C++ Communication Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][28/06/2022]
 */
// =====================================================================================


#ifndef FMTDEF_COMM_MODBUSMASTERPROTOCOL_H
#define FMTDEF_COMM_MODBUSMASTERPROTOCOL_H



// =====================================================================================
//	INCLUDES
// =====================================================================================


#ifndef FMTDEF_CORE_H
#include "FMT_Core.h"
#endif

#ifndef FMTDEF_HDW_H
#include "FMT_Hdw.h"
#endif

#ifndef FMTDEF_COMM_MODBUSPROTOCOL_H
#include "FMT_CommModbusProtocol.h"
#endif

#include "string.h"

// =====================================================================================
//	DEFINES
// =====================================================================================


#define FMTDEF_COMM_MODBUSRCUMASTER_DEFAULT_TIMEOUT			500


// *************************************************************************************
// *************************************************************************************
//	Class CFMT_CommModbusMasterProtocol
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_CommModbusMasterProtocol : public CFMT_CommModbusProtocol
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
	CFMT_Crc			m_Crc;


public:


	// =====================================================================================
	// CONSTRUCTORS & DESTRUCTORS
	// =====================================================================================

public:
	
    CFMT_CommModbusMasterProtocol();
    virtual ~CFMT_CommModbusMasterProtocol();

	// =====================================================================================
	//	FUNCTIONS
	// =====================================================================================

protected:

    // Build the basic request of a function
    virtual t_FMT_Uint32        BuildRequestHeader(t_FMT_Uint8 ucSlaveId);

    // Build the basic request of a function
    virtual t_FMT_Uint32		BuildRequestIoBasis(t_FMT_Uint8 ucSlaveId, t_FMT_Uint8 ucFunction, t_FMT_Uint16 usAddress, t_FMT_Uint16 usNumItems);

    // Builds Request CRC
    virtual void                BuildRequestFooter();

    // Computes the length to read after the function received
    virtual t_FMT_Uint8         ComputeMetaLengthAfterFunction();

    // Computes the length to read after the meta information (address, count, etc)
    virtual t_FMT_Int32         ComputeDataLengthAfterMeta();

    // Computes the length to read after the user function received
    virtual t_FMT_Uint8			UserComputeMetaLengthAfterFunction(t_FMT_Uint8 ucFunction);

    // Computes the length to read after the meta information of user function
    virtual t_FMT_Int32			UserComputeDataLengthAfterMeta(t_FMT_Uint8 ucFunction);

    // Receive the response from a modbus slave
    virtual t_FMT_Uint32		Receive(t_FMT_Uint64 quiTimeout);

    // Check message integrity
    virtual t_FMT_Uint32		CheckIntegrity(t_FMT_Uint8 *pucMsg, t_FMT_Uint32 uiMsgSize);

    // Extract the header parameters
    virtual void				ExtractHeaderParameter();

    // Preliminary check packet confirmation
    virtual t_FMT_Uint32        PreCheckConfirmation(t_FMT_Uint8 ucSlaveId);

    // Check confirmation packet
    virtual t_FMT_Uint32        CheckConfirmation(t_FMT_Uint8 ucSlaveId, t_FMT_Uint8 *pucExcCode);

    // Return the response length according to the request
    t_FMT_Int32                 ComputeResponseLengthFromRequest();

    // Process basic transaction steps
    t_FMT_Uint32                ProcessBasicTransaction(t_FMT_Uint8 ucSlaveId, t_FMT_Uint8 *pucExcCode, t_FMT_Uint64 quiTimeout);

    // Process a Read Coils function
    virtual t_FMT_Uint32		ReadBits(t_FMT_Uint8 ucFunction, t_FMT_Uint8 ucSlaveId, t_FMT_Uint16 usAddress, t_FMT_Uint16 usNumbits, t_FMT_Bool *pbCoils,
                                                t_FMT_Uint8 *pucExcCode, t_FMT_Uint64 quiTimeout = FMTDEF_COMM_MODBUSRCUMASTER_DEFAULT_TIMEOUT);

    // Process a Read registers function
    virtual t_FMT_Uint32        ReadRegisters(t_FMT_Uint8 ucFunction, t_FMT_Uint8 ucSlaveId, t_FMT_Uint16 usAddress, t_FMT_Uint16 usNumRegs, t_FMT_Uint16 *pusReg,
                                                              t_FMT_Uint8 *pucExcCode, t_FMT_Uint64 quiTimeout = FMTDEF_COMM_MODBUSRCUMASTER_DEFAULT_TIMEOUT);


public:

	// Process a Read Coils function
	virtual t_FMT_Uint32		ReadCoils(t_FMT_Uint8 ucSlaveId, t_FMT_Uint16 usAddress, t_FMT_Uint16 usNumbits, t_FMT_Bool *pbCoils, 
												t_FMT_Uint8 *pucExcCode, t_FMT_Uint64 quiTimeout = FMTDEF_COMM_MODBUSRCUMASTER_DEFAULT_TIMEOUT);

    // Process a Read Discrete Inputs function
    virtual t_FMT_Uint32		ReadDiscreteInputs(t_FMT_Uint8 ucSlaveId, t_FMT_Uint16 usAddress, t_FMT_Uint16 usNumbits, t_FMT_Bool *pbDin,
                                                t_FMT_Uint8 *pucExcCode, t_FMT_Uint64 quiTimeout = FMTDEF_COMM_MODBUSRCUMASTER_DEFAULT_TIMEOUT);

    // Process a Read Input Registers function
    virtual t_FMT_Uint32		ReadInputRegisters(t_FMT_Uint8 ucSlaveId, t_FMT_Uint16 usAddress, t_FMT_Uint16 usNumRegs, t_FMT_Uint16 *pusReg,
                                                t_FMT_Uint8 *pucExcCode, t_FMT_Uint64 quiTimeout = FMTDEF_COMM_MODBUSRCUMASTER_DEFAULT_TIMEOUT);

    // Process a Read Holding Registers function
    virtual t_FMT_Uint32		ReadHoldingRegisters(t_FMT_Uint8 ucSlaveId, t_FMT_Uint16 usAddress, t_FMT_Uint16 usNumRegs, t_FMT_Uint16 *pusReg,
                                                t_FMT_Uint8 *pucExcCode, t_FMT_Uint64 quiTimeout = FMTDEF_COMM_MODBUSRCUMASTER_DEFAULT_TIMEOUT);

    // Process a Read Exception Status function
    virtual t_FMT_Uint32		ReadExceptionStatus(t_FMT_Uint8 ucSlaveId, t_FMT_Uint8 *pucCodes,
                                                        t_FMT_Uint8 *pucExcCode, t_FMT_Uint64 quiTimeout = FMTDEF_COMM_MODBUSRCUMASTER_DEFAULT_TIMEOUT);

    // Process a Read FIFO Queue function
    virtual t_FMT_Uint32		ReadFifoQueue(t_FMT_Uint8 ucSlaveId, t_FMT_Uint16 usAddress, CFMT_Uint16Vector& vReadData,
                                                        t_FMT_Uint8 *pucExcCode, t_FMT_Uint64 quiTimeout = FMTDEF_COMM_MODBUSRCUMASTER_DEFAULT_TIMEOUT);


    // Process a Write Single Coil function
    virtual t_FMT_Uint32		WriteSingleCoil(t_FMT_Uint8 ucSlaveId, t_FMT_Uint16 usAddress, t_FMT_Bool bValue,
                                                t_FMT_Uint8 *pucExcCode, t_FMT_Uint64 quiTimeout = FMTDEF_COMM_MODBUSRCUMASTER_DEFAULT_TIMEOUT);

    // Process a Write Multiple Coils function
    virtual t_FMT_Uint32		WriteMultipleCoils(t_FMT_Uint8 ucSlaveId, t_FMT_Uint16 usAddress, t_FMT_Uint16 usNumBits, t_FMT_Bool *pbCoils,
                                                t_FMT_Uint8 *pucExcCode, t_FMT_Uint64 quiTimeout = FMTDEF_COMM_MODBUSRCUMASTER_DEFAULT_TIMEOUT);

    // Process a Write Single Register function
    virtual t_FMT_Uint32		WriteSingleRegister(t_FMT_Uint8 ucSlaveId, t_FMT_Uint16 usAddress, t_FMT_Uint16 usValue,
                                                t_FMT_Uint8 *pucExcCode, t_FMT_Uint64 quiTimeout = FMTDEF_COMM_MODBUSRCUMASTER_DEFAULT_TIMEOUT);

    // Process a Write Multiple Registers function
    virtual t_FMT_Uint32		WriteMultipleRegisters(t_FMT_Uint8 ucSlaveId, t_FMT_Uint16 usAddress, t_FMT_Uint16 usNumRegs, t_FMT_Uint16 *pusRegs,
                                                t_FMT_Uint8 *pucExcCode, t_FMT_Uint64 quiTimeout = FMTDEF_COMM_MODBUSRCUMASTER_DEFAULT_TIMEOUT);

    // Process a Mask Write Register function
    virtual t_FMT_Uint32		MaskWriteRegister(t_FMT_Uint8 ucSlaveId, t_FMT_Uint16 usAddress, t_FMT_Uint16 usAndMask, t_FMT_Uint16 usOrMask,
                                                  t_FMT_Uint8 *pucExcCode, t_FMT_Uint64 quiTimeout = FMTDEF_COMM_MODBUSRCUMASTER_DEFAULT_TIMEOUT);

    // Process a Write and Read Registers function
    virtual t_FMT_Uint32        WriteAndReadRegisters(t_FMT_Uint8 ucSlaveId, t_FMT_Uint16 usWAddress, t_FMT_Uint16 usNumWRegs, t_FMT_Uint16 usRAddress,
                                                     t_FMT_Uint16 usNumRRegs, t_FMT_Uint16 *pusWRegs, t_FMT_Uint16 *pusRRegs,
                                                     t_FMT_Uint8 *pucExcCode, t_FMT_Uint64 quiTimeout = FMTDEF_COMM_MODBUSRCUMASTER_DEFAULT_TIMEOUT);

    // Process a Get Comm Event Counter function
    virtual t_FMT_Uint32		GetCommEventCounter(t_FMT_Uint8 ucSlaveId, t_FMT_Uint16& usStatus, t_FMT_Uint16& usEventCount,
                                                    t_FMT_Uint8 *pucExcCode, t_FMT_Uint64 quiTimeout = FMTDEF_COMM_MODBUSRCUMASTER_DEFAULT_TIMEOUT);

    // Process a Get Comm Event Counter function
    virtual t_FMT_Uint32		GetCommEventLog(t_FMT_Uint8 ucSlaveId, t_FMT_Uint16& usStatus, t_FMT_Uint16& usEventCount,
                                                    t_FMT_Uint16& usMessCount, CFMT_Uint8Vector& vEvents,
                                                    t_FMT_Uint8 *pucExcCode, t_FMT_Uint64 quiTimeout = FMTDEF_COMM_MODBUSRCUMASTER_DEFAULT_TIMEOUT);

    // Process a multiple Write File Record function
    virtual t_FMT_Uint32		WriteMultipleFileRecord(t_FMT_Uint8 ucSlaveId,
                                                            CFileRecGroupVector& Groups,
                                                            t_FMT_Uint8 *pucExcCode, t_FMT_Uint64 quiTimeout = FMTDEF_COMM_MODBUSRCUMASTER_DEFAULT_TIMEOUT);

    // Process a single Write File Record function
    virtual t_FMT_Uint32		WriteSingleFileRecord(t_FMT_Uint8 ucSlaveId, t_FMT_Uint16 usFileNum, t_FMT_Uint16 usRecNum, t_FMT_Uint16 usRecLen, t_FMT_Uint16 *pusDataBuf,
                                                            t_FMT_Uint8 *pucExcCode, t_FMT_Uint64 quiTimeout = FMTDEF_COMM_MODBUSRCUMASTER_DEFAULT_TIMEOUT);

    // Process a single Read File Record function
    virtual t_FMT_Uint32		ReadSingleFileRecord(t_FMT_Uint8 ucSlaveId, t_FMT_Uint16 usFileNum, t_FMT_Uint16 usRecNum, t_FMT_Uint16 usRecLen, t_FMT_Uint16 *pusDataBuf,
                                                            t_FMT_Uint8 *pucExcCode, t_FMT_Uint64 quiTimeout = FMTDEF_COMM_MODBUSRCUMASTER_DEFAULT_TIMEOUT);

    // Process a multiple Read File Record function
    virtual t_FMT_Uint32		ReadMultipleFileRecord(t_FMT_Uint8 ucSlaveId,
                                                           CFileRecGroupVector& Groups,
                                                            t_FMT_Uint8 *pucExcCode, t_FMT_Uint64 quiTimeout = FMTDEF_COMM_MODBUSRCUMASTER_DEFAULT_TIMEOUT);


    #if 0
    // Process a Write Single Register function
    virtual t_FMT_Uint32		Diagnostics(t_FMT_Uint8 ucSlaveId, t_FMT_Uint16 usSubFunction, CFMT_Uint8Vector& vTxData, CFMT_Uint8Vector& vRxData,
                                                            t_FMT_Uint8 *pucExcCode, t_FMT_Uint64 quiTimeout = FMTDEF_COMM_MODBUSRCUMASTER_DEFAULT_TIMEOUT);
    // Process a Get Comm Event Counter function
    virtual t_FMT_Uint32		ReportServerID(t_FMT_Uint8 ucSlaveId, CFMT_Uint8Vector& vData,
                                                            t_FMT_Uint8 *pucExcCode, t_FMT_Uint64 quiTimeout = FMTDEF_COMM_MODBUSRCUMASTER_DEFAULT_TIMEOUT);
    #endif
};




// *************************************************************************************
// *************************************************************************************
//	Class CFMT_CommModbusRtuMasterProtocol
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_CommModbusRtuMasterProtocol : public CFMT_CommModbusMasterProtocol
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
	
    CFMT_CommModbusRtuMasterProtocol();
    virtual ~CFMT_CommModbusRtuMasterProtocol();

	// =====================================================================================
	//	FUNCTIONS
	// =====================================================================================

protected:

    // Build the basic request of a function
    virtual t_FMT_Uint32        BuildRequestHeader(t_FMT_Uint8 ucSlaveId);

    // Builds Request CRC
    virtual void                BuildRequestFooter();

    // Check message integrity
    virtual t_FMT_Uint32		CheckIntegrity(t_FMT_Uint8 *pucMsg, t_FMT_Uint32 uiMsgSize);

    // Extract the header parameters
    virtual void				ExtractHeaderParameter();

public:

};


#endif

