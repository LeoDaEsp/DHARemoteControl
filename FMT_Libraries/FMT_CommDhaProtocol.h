// =====================================================================================
/**
 * @file					FMT_CommDhaProtocol.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					19/09/2022
 * @brief					DHA base protocol
 *
 * @version	Project:		Formatech C++ Communication Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][19/09/2022]
 */
// =====================================================================================


#ifndef FMTDEF_COMM_DHAPROTOCOL_H
#define FMTDEF_COMM_DHAPROTOCOL_H


// =====================================================================================
//	INCLUDES
// =====================================================================================


#ifndef FMTDEF_CORE_H
#include "FMT_Core.h"
#endif

#ifndef FMTDEF_HDW_H
#include "FMT_Hdw.h"
#endif

// =====================================================================================
//	DEFINES
// =====================================================================================


#define FMTDEF_COMM_DHAPROTOCOL_SOF						0x75
#define FMTDEF_COMM_DHAPROTOCOL_EOF						0x7E
#define FMTDEF_COMM_DHAPROTOCOL_STUFF					0x78

#define FMTDEF_COMM_DHAPROTOCOL_CMDRSP_FRAME_ID			0xAA

#define FMTDEF_COMM_DHAPROTOCOL_LOOPBACK_CMD			0x0
#define FMTDEF_COMM_DHAPROTOCOL_BCASTENABLE_CMD			0x1
#define FMTDEF_COMM_DHAPROTOCOL_READREG_CMD				0x2
#define FMTDEF_COMM_DHAPROTOCOL_WRITEREG_CMD			0x3
#define FMTDEF_COMM_DHAPROTOCOL_RESCTRL_CMD				0x4
#define FMTDEF_COMM_DHAPROTOCOL_READNVM_CMD				0x8
#define FMTDEF_COMM_DHAPROTOCOL_WRITENVM_CMD			0x9
#define FMTDEF_COMM_DHAPROTOCOL_ERASENVM_CMD			0xA
#define FMTDEF_COMM_DHAPROTOCOL_DUMPREG_CMD				0xB

#define FMTDEF_COMM_DHAPROTOCOL_DEF_TIMEOUT             500


// *************************************************************************************
// *************************************************************************************
//	Class CFMT_CommDhaProtocol
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_CommDhaProtocol : public CFMT_HdwProtocol
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

    // Byte I/O Service
    CFMT_HdwByteInBufferService     *m_pInService;
    CFMT_HdwByteOutBufferService    *m_pOutService;

    // CRC object
    CFMT_Crc                        m_Crc;

    // TX Buffer
    t_FMT_Uint8                     *m_pucTxBuf;

    // TX Buffer Length
    t_FMT_Uint32                    m_uiTxLen;

    // RX Buffers
    t_FMT_Uint8                     *m_pucRxBuf;
    t_FMT_Uint8                     *m_pucRxRawBuf;

    // RX Buffer Length
    t_FMT_Uint32                    m_uiRxLen;
    t_FMT_Uint32                    m_uiRxRawLen;

    // RX On Flag
    t_FMT_Bool                      m_bRxOn;

    // RX Stuff Flag
    t_FMT_Bool                      m_bRxStuff;


public:

	// =====================================================================================
	// CONSTRUCTORS & DESTRUCTORS
	// =====================================================================================

public:
	
    CFMT_CommDhaProtocol();
    virtual ~CFMT_CommDhaProtocol();
	

	// =====================================================================================
	//	FUNCTIONS
	// =====================================================================================

protected:

    // Stuff a packet
    void					StuffPacket(t_FMT_Uint8 *pucPayBuf, t_FMT_Uint32 uiPayLen, t_FMT_Uint8 *pucDestBuf, t_FMT_Uint32& uiDstLen);

    // Complete a TX Packet
    void                    CompleteTxPacket(t_FMT_Uint8 *pucPayBuf, t_FMT_Uint32 uiPayLen);

    // Reset RX Parameters
    void                    ResetRxParameters();

    // Check the CRC of the receive packet
    t_FMT_Bool              CheckRxCrc();

    // LOG the received raw packet
    virtual void            LogRxRawPacket(t_FMT_Bool bValid);


public:

    // Mount the protocol on an I/O Service
    virtual t_FMT_Uint32	Mount(CFMT_HdwByteInBufferService *pInService, CFMT_HdwByteOutBufferService *pOutService);
};


// *************************************************************************************
// *************************************************************************************
//	Class CFMT_CommDhaSlaveProtocol
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_CommDhaSlaveProtocol : public CFMT_CommDhaProtocol
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

    CFMT_CommDhaSlaveProtocol();
    virtual ~CFMT_CommDhaSlaveProtocol();


    // =====================================================================================
    //	FUNCTIONS
    // =====================================================================================

protected:

public:

};


// *************************************************************************************
// *************************************************************************************
//	Class CFMT_CommDhaMasterProtocol
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_CommDhaMasterProtocol : public CFMT_CommDhaProtocol
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

    CFMT_CommDhaMasterProtocol();
    virtual ~CFMT_CommDhaMasterProtocol();


    // =====================================================================================
    //	FUNCTIONS
    // =====================================================================================

protected:

    // Receive a valid packet
    t_FMT_Uint32            ReceivePacket(t_FMT_Uint16 usTimeoutMs);


public:

    // Write a Non-Volatile Register
    t_FMT_Uint32            WriteNonVolatileregister(t_FMT_Uint8 ucTargetId, t_FMT_Uint8 ucResourceId, t_FMT_Uint8 ucRegisterId, t_FMT_Uint16 usData,
                                                    t_FMT_Uint8& ucStatus, t_FMT_Uint16 usTimeoutMs = FMTDEF_COMM_DHAPROTOCOL_DEF_TIMEOUT);

};


#endif

