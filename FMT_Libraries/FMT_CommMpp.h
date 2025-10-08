// =====================================================================================
/**
 * @file					FMT_CommMpp.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					28/06/2022
 * @brief					Maintenance Point To Point Protocol Basic Items
 *
 * @version	Project:		Formatech C++ Communication Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][28/06/2022]
 */
// =====================================================================================


#ifndef FMTDEF_COMM_MPP_H
#define FMTDEF_COMM_MPP_H

// =====================================================================================
//	DEFINES
// =====================================================================================

#define FMTDEF_COMM_MPP_PACKETSIZE			0x100000
#define FMTDEF_COMM_MPP_BROADCAST_ADD		0x000000

// Thread type according to OS
#ifdef FMTDEF_COMPILE_OS_WINDOWS
#define FMTDEF_COMM_MPP_THREAD                   		HANDLE
#define FMTDEF_COMM_MPP_THREAD_SIZE						(0)
#endif

#ifdef FMTDEF_COMPILE_OS_LINUX
#define FMTDEF_COMM_MPP_THREAD                   		pthread_t
#endif


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


// *************************************************************************************
// *************************************************************************************
//	Class CFMT_CommMpp
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_CommMpp : public CFMT_HdwProtocol, public CFMT_CommObject
{
	// =====================================================================================
	//	TYPES
	// =====================================================================================

protected:

public:

	// --- t_CommandType ---------------------------------------

	enum t_CommandType
	{
		e_CommandType_RegisterWrite			= 0x01,
		e_CommandType_RegisterRead			= 0x02,
		e_CommandType_MemoryErase			= 0x04,
		e_CommandType_MemoryWrite			= 0x05,
		e_CommandType_MemoryRead			= 0x06,
		e_CommandType_ReadInfo				= 0x08,
		e_CommandType_Invalid				= 0xFF
	};


	// --- t_CommandStatus -------------------------------------

	enum t_CommandStatus
	{
		e_CommandStatus_NotCreated			= 0,
		e_CommandStatus_NotProcessed		= 1,
		e_CommandStatus_Sent				= 2,
		e_CommandStatus_Processed			= 3
	};


	// --- t_MppStatus -----------------------------------------

	enum t_MppStatus
	{
		e_MppStatus_OK						= 0,
		e_MppStatus_ReadOnly				= 1,
		e_MppStatus_FormatError				= 2,
		e_MppStatus_TimeoutError			= 3,
		e_MppStatus_NotDefined				= 4,
		e_MppStatus_CommandError			= 5,
		e_MppStatus_MemoryError				= 6,
		e_MppStatus_ByteEnableError			= 7
	};


	// --- t_RxState -------------------------------------------

	enum t_RxState
	{
		e_RxState_Start			= 0x00,
		e_RxState_DevAdd1		= 0x01,
		e_RxState_DevAdd2		= 0x02,
		e_RxState_DevAdd3		= 0x03,
		e_RxState_DevNum		= 0x04,
		e_RxState_PayBytes1		= 0x05,
		e_RxState_PayBytes2		= 0x06,
		e_RxState_Payload		= 0x07,
		e_RxState_Crc1			= 0x08,
		e_RxState_Crc2			= 0x09
	};


	// --- SInfoDescriptor -------------------------------------

	struct FMTDEF_LIB_DLLSPEC SInfoDescriptor
	{
		t_FMT_Uint32		m_uiUnitAdd;
		t_FMT_Uint16		m_usDeviceEnable;
		t_FMT_Char			m_pchUnitPN[21];
		t_FMT_Char			m_pchFirmwarePN[21];
		t_FMT_Char			m_pchUnitDescription[61];

		SInfoDescriptor();
	};


	// --- SBufferTransferProperty -----------------------------

	struct FMTDEF_LIB_DLLSPEC SBufferTransferProperty
	{
		t_FMT_Uint32		m_uiStartMemAddress;
		t_FMT_Uint32		m_uiPageSize;
		t_FMT_Uint32		m_uiEraseSize;
		t_FMT_Uint32		m_uiMaxNumItemPerTransfer;
		t_FMT_Uint32		m_uiTimeout;
		t_FMT_Bool			m_bErasePage;
		t_FMT_Bool			m_bEraseAll;
		t_FMT_Uint32		m_uiRetries;
		t_FMT_Uint32		m_uiTransferSize;
		t_FMT_Bool			m_bNoAddressInc;

		SBufferTransferProperty();
	};


	// --- SBufferTransferStatus -------------------------------

	struct FMTDEF_LIB_DLLSPEC SBufferTransferStatus
	{
		t_FMT_Bool			m_bOn;
		t_FMT_Uint32		m_uiStatus;
		t_FMT_Uint32		m_uiUnitAdd;
		t_FMT_Uint8			m_ucDevNum;
		t_FMT_Uint32		m_uiCurrentPage;
		t_FMT_Uint32		m_uiTotPages;
		t_FMT_Uint32		m_uiCurrentSize;

		SBufferTransferStatus();
	};


	// --- SCommand ------------------------------------------

	struct FMTDEF_LIB_DLLSPEC SCommand
	{
	protected:

	public:

		t_FMT_Uint32	m_uiTXB;
		t_FMT_Uint32	m_uiRXB;
		t_FMT_Uint8		*m_pucTXBuf;
		t_FMT_Uint8		*m_pucRXBuf;
		t_FMT_Uint32	m_uiComStatus;	
		t_FMT_Uint8		m_ucCommandType;

		SCommand();
		SCommand(const SCommand& com);
		~SCommand();

		void			DataCopy(const SCommand& com);
		SCommand&		operator=(const SCommand& com);
		t_FMT_Uint8		GetTXData(t_FMT_Uint32 uiIdx);
		void			SetTXData(t_FMT_Uint32 uiIdx,t_FMT_Uint8 ucData);
		t_FMT_Uint8		GetRXData(t_FMT_Uint32 uiIdx);
		t_FMT_Uint8*	GetTXBuf();
		t_FMT_Uint8*	GetRXBuf();
		void			Destroy();

		t_FMT_Uint32	GetResult(t_FMT_Uint8 &ucResult);
		t_FMT_Uint32	GetReadRegisterData(t_FMT_Uint8 ucNob,t_FMT_Uint8 *pucReadData);
		t_FMT_Uint32	GetReadRegisterData8(t_FMT_Uint8 *pucReadData);
		t_FMT_Uint32	GetReadRegisterData16(t_FMT_Uint16 *pusReadData);
		t_FMT_Uint32	GetReadRegisterData32(t_FMT_Uint32 *pdwReadData);
		t_FMT_Uint32	GetReadRegisterData64(t_FMT_Uint64 *pquiReadData);

		t_FMT_Uint32	GetReadMemoryData(t_FMT_Uint32 uiNob,t_FMT_Uint8 *pucReadData);
		t_FMT_Uint32	GetReadMemoryData8(t_FMT_Uint8 *pucReadData);
		t_FMT_Uint32	GetReadMemoryData16(t_FMT_Uint16 *pusReadData);
		t_FMT_Uint32	GetReadMemoryData32(t_FMT_Uint32 *pdwReadData);
		t_FMT_Uint32	GetReadMemoryData64(t_FMT_Uint64 *pquiReadData);
		t_FMT_Uint32	GetReadMemoryDataSize(t_FMT_Uint32& uiNob);

		t_FMT_Uint32	GetReadInfo(SInfoDescriptor *pInfo);
		t_FMT_Uint8*	GetReadMemoryBuffer();

		t_FMT_Uint32	CreateReadInfoCommand();

		t_FMT_Uint32	CreateRegisterWriteCommand(t_FMT_Uint8 ucAdd,t_FMT_Uint8* pucData,t_FMT_Uint8 ucNob);
		t_FMT_Uint32	CreateRegisterWrite8Command(t_FMT_Uint8 ucAdd,t_FMT_Uint8 ucData);
		t_FMT_Uint32	CreateRegisterWrite16Command(t_FMT_Uint8 ucAdd,t_FMT_Uint16 usData);
		t_FMT_Uint32	CreateRegisterWrite32Command(t_FMT_Uint8 ucAdd,t_FMT_Uint32 uiData);
		t_FMT_Uint32	CreateRegisterWrite64Command(t_FMT_Uint8 ucAdd,t_FMT_Uint64 quiData);

		t_FMT_Uint32	CreateRegisterReadCommand(t_FMT_Uint8 ucAdd,t_FMT_Uint8 ucNob);
		t_FMT_Uint32	CreateRegisterRead8Command(t_FMT_Uint8 ucAdd);
		t_FMT_Uint32	CreateRegisterRead16Command(t_FMT_Uint8 ucAdd);
		t_FMT_Uint32	CreateRegisterRead32Command(t_FMT_Uint8 ucAdd);
		t_FMT_Uint32	CreateRegisterRead64Command(t_FMT_Uint8 ucAdd);

		t_FMT_Uint32	CreateMemoryWriteCommand(t_FMT_Uint32 uiAdd,t_FMT_Uint8* pucData,t_FMT_Uint32 uiNob);
		t_FMT_Uint32	CreateMemoryReadCommand(t_FMT_Uint32 uiAdd,t_FMT_Uint32 uiNob);
		t_FMT_Uint32	CreateMemoryEraseCommand(t_FMT_Uint32 uiAdd);
	};


	// =====================================================================================
	//	VARIABLES
	// =====================================================================================

protected:

	// Input Byte Service
	CFMT_HdwByteInBufferService		*m_pInService;

	// Output Byte Service
	CFMT_HdwByteOutBufferService	*m_pOutService;

	// CRC
	static CFMT_Crc					s_Crc;

	// RX state
	t_FMT_Uint32					m_uiRxState;

	// Computed RX packet CRC
	t_FMT_Uint16					m_usCalcRxCrc;

	// RX packet Address
	t_FMT_Uint32					m_uiRxAdd;

	// Number of payload bytes of RX packet 
	t_FMT_Uint32					m_uiRxTotalPayBytes;

	// RX Packet payload bytes
	CFMT_Uint8Vector				m_RxPayload;

	// Payload bytes counte of RX packet
	t_FMT_Uint32					m_uiRxPayBytes;

	// RX Packet CRC
	t_FMT_Uint16					m_usRxCrc;

	// RX Packet device number
	t_FMT_Uint8						m_ucRxDevNum;

	// RX Packet Broadcast flag
	t_FMT_Bool						m_bIsRxBroadcast;

	// RX Packet buffer
	t_FMT_Uint8						*m_pucRxPacket;

public:

	// Write Timeout
	t_FMT_Uint32					m_uiWriteTimeout;


	// =====================================================================================
	// CONSTRUCTORS & DESTRUCTORS
	// =====================================================================================

public:

	CFMT_CommMpp();
	virtual ~CFMT_CommMpp();


	// =====================================================================================
	//	FUNCTIONS
	// =====================================================================================

protected:

	// Convert a info structure into byte buffer
	static void				InfoToBytes(SInfoDescriptor *pInfo, t_FMT_Uint8 *pucBuf);

	// Convert a byte buffer into info structure
	static void				BytesToInfo(t_FMT_Uint8 *pucBuf, SInfoDescriptor *pInfo);

	// Reset RX Parameters
	void					ResetRxParameters();

public:

	// Mount protocol services
	virtual t_FMT_Uint32	Mount(CFMT_HdwByteInBufferService *pInService, CFMT_HdwByteOutBufferService *pOutService);
};

#endif
