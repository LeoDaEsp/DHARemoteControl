// =====================================================================================
/**
 * @file					FMT_HdwHoe.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					24/04/2022
 * @brief					Formatech Hardware-On_Ethernet Basic Items
 *
 * @version	Project:		Formatech C++ Hardware Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][24/04/2022]
 */
// =====================================================================================


#ifndef FMTDEF_HDW_HOE_H
#define FMTDEF_HDW_HOE_H

// =====================================================================================
//	INCLUDES
// =====================================================================================


#ifndef FMTDEF_CORE_H
#include "FMT_Core.h"
#endif

#ifndef FMTDEF_HDW_OBJECT_H
#include "FMT_HdwObject.h"
#endif



// =====================================================================================
//	DEFINES
// =====================================================================================

#ifdef FMTDEF_COMPILE_OS_WINDOWS
#define FMTDEF_HDW_HOE_THREAD                   HANDLE
#define FMTDEF_HDW_HOE_RXTHREAD_SIZE            (0)
#endif

#ifdef FMTDEF_COMPILE_OS_LINUX
#define FMTDEF_HDW_HOE_THREAD                   pthread_t
//#define FMTDEF_HDW_HOE_RXTHREAD_SIZE            (0)
#endif


#define FMTDEF_HDW_HOE_TARGET_BASE_PORT			55000


#define FMTDEF_HDW_HOE_PCK_HDR_LEN				64
#define FMTDEF_HDW_HOE_MAX_PAYLOAD_BYTES		(1350)

#define FMTDEF_HDW_HOE_PROT_ID					0xFE0000A1
#define FMTDEF_HDW_HOE_PROT_VER					0x0001

#define FMTDEF_HDW_HOE_PCKID_DETECT				0xF0000001
#define FMTDEF_HDW_HOE_PCKID_INFO				0xF0000002

#define FMTDEF_HDW_HOE_PCKID_CONNECT_REQ		0xC0000001
#define FMTDEF_HDW_HOE_PCKID_CONNECT_ANS		0xC0000002
#define FMTDEF_HDW_HOE_PCKID_DISCONNECT_REQ		0xC0000003
#define FMTDEF_HDW_HOE_PCKID_DISCONNECT_ANS		0xC0000004
#define FMTDEF_HDW_HOE_PCKID_CMD_DATA			0xC0000005
#define FMTDEF_HDW_HOE_PCKID_EVENT_DATA			0xC0000006

#define FMTDEF_HDW_HOE_PCKID_PORT_OPEN_REQ		0xA0000001
#define FMTDEF_HDW_HOE_PCKID_PORT_OPEN_ANS		0xA0000002
#define FMTDEF_HDW_HOE_PCKID_PORT_CLOSE_REQ		0xA0000003
#define FMTDEF_HDW_HOE_PCKID_PORT_CLOSE_ANS		0xA0000004
#define FMTDEF_HDW_HOE_PCKID_PORT_KEEP_ALIVE	0xA0000005
#define FMTDEF_HDW_HOE_PCKID_PORT_DATABUF		0xA0000006
#define FMTDEF_HDW_HOE_PCKID_PORT_STATUS		0xA0000007
#define FMTDEF_HDW_HOE_PCKID_PORT_CCTX_REQ		0xA0000008
#define FMTDEF_HDW_HOE_PCKID_PORT_CCTX_ANS		0xA0000009
#define FMTDEF_HDW_HOE_PCKID_PORT_RSTTX_REQ		0xA000000A
#define FMTDEF_HDW_HOE_PCKID_PORT_RSTTX_ANS		0xA000000B
#define FMTDEF_HDW_HOE_PCKID_PORT_RSTRX_REQ		0xA000000C
#define FMTDEF_HDW_HOE_PCKID_PORT_RSTRX_ANS		0xA000000D
#define FMTDEF_HDW_HOE_PCKID_PORT_DCTX_REQ		0xA000000E
#define FMTDEF_HDW_HOE_PCKID_PORT_DCTX_ANS		0xA000000F
#define FMTDEF_HDW_HOE_PCKID_PORT_CFG_REQ		0xA0000010
#define FMTDEF_HDW_HOE_PCKID_PORT_CFG_ANS		0xA0000011

#define FMTDEF_HOE_RESPONSE_TIMEOUT				150

#define FMTDEF_HDW_HOE_TX_RETRIES				5
#define FMTDEF_HDW_HOE_TX_RETRY_TIME			5

#define FMTDEF_HDW_HOE_CMD_RETRIES				2

#define FMTDEF_HDW_HOE_TOT_DETECT_COMMANDS		3


// *************************************************************************************
// *************************************************************************************
//	Class CFMT_HdwHoe
// *************************************************************************************
// *************************************************************************************


class FMTDEF_LIB_DLLSPEC CFMT_HdwHoe
{
	// =====================================================================================
	//	TYPES
	// =====================================================================================

protected:
public:

	// ---[ t_HoePacket_Connect_Field ]--------------------------------------------------

#pragma pack(push,1)
	typedef struct t_HoePacket_Connect_Field_Struct
	{
		t_FMT_Uint16					m_usTimeout;	//! Timeout in ms (0=no timeout check)

	} t_HoePacket_Connect_Field;
#pragma pack(pop)


	// ---[ t_HoePacket_OpenAns_Field ]--------------------------------------------------

#pragma pack(push,1)
	typedef struct t_HoePacket_OpenAns_Struct
	{
		t_FMT_Uint16					m_usPort;

	} t_HoePacket_OpenAns_Field;
#pragma pack(pop)


	// ---[ t_HoePacketPayload ]--------------------------------------------------

#pragma pack(push,1)
	typedef union t_HoePacketPayload_Union
	{
		t_HoePacket_Connect_Field			m_ConnectFields;
		t_HoePacket_OpenAns_Field			m_OpenAnsFields;
		t_FMT_Uint8							m_pucPayData[FMTDEF_HDW_HOE_MAX_PAYLOAD_BYTES];

	} t_HoePacketPayload;
#pragma pack(pop)


	// ---[ t_HoePacket ]--------------------------------------------------

#pragma pack(push,1)
	typedef struct t_HoePacket_Field_Struct
	{
		t_FMT_Uint32		m_uiProtId;				//! HOE Protocol Identifier
		t_FMT_Uint16		m_usProtVer;			//! HOE Protocol Version
		t_FMT_Uint32		m_uiDevId;				//! Target Device Identifier
		t_FMT_Uint32		m_uiDevSn;				//! Target Device Serial Number
		t_FMT_Uint32		m_uiSrcId;				//! Source Identifier
		t_FMT_Uint32		m_uiLinkId;				//! Link Identifier
		t_FMT_Uint32		m_uiPkn;				//! Packet Number
		t_FMT_Uint16		m_usPortId;				//! Port Identifier
		t_FMT_Uint16		m_usPortNum;			//! Port Number
		t_FMT_Uint16		m_usStatus;				//! Status Field
		t_FMT_Uint32		m_uiPackId;				//! Packet Identifier
		t_FMT_Uint16		m_usPackLen;			//! Payload Number of bytes
		t_FMT_Uint64		m_quiTimeStamp;			//! Time Stamp
		t_FMT_Uint8			m_pucExtHdr[16];		//! Spare header bytes
		t_FMT_Uint16		m_usPckCrc;				//! Packet CRC
		t_HoePacketPayload	m_Payload;				//! Packet Payload

	} t_HoePacket_Field;
#pragma pack(pop)

#pragma pack(push,1)
	typedef union t_HoePacket_Union
	{
		t_HoePacket_Field		m_Fields;
		t_FMT_Uint8				m_pucBytes[sizeof(t_HoePacket_Field)];

	} t_HoePacket;
#pragma pack(pop)


	// --- HOE Status --------------------------------------

	typedef enum t_HoeStatus_Enum
	{
		e_HoeStatus_OK = 0,
		e_HoeStatus_Busy = 1,
		e_HoeStatus_HdwError = 2,
		e_HoeStatus_InvalidParam = 3,
		e_HoeStatus_ProtocolError = 4,
		e_HoeStatus_Timeout = 5

	} t_HoeStatus;

public:

	// =====================================================================================
	//	VARIABLES
	// =====================================================================================

protected:

	//! CRC Table
	static CFMT_Crc					s_Crc16;


public:

	// Device ID
	t_FMT_Uint32					m_uiHoeDeviceId;


	// =====================================================================================
	// CONSTRUCTORS & DESTRUCTORS
	// =====================================================================================
	
	CFMT_HdwHoe();
	virtual ~CFMT_HdwHoe();

	// =====================================================================================
	//	FUNCTIONS
	// =====================================================================================

protected:
public:

	// Compute CRC packet
	static t_FMT_Uint16		ComputeCrc(t_HoePacket &pck);

	// Check if the packet is a broadcast one
	static t_FMT_Bool		IsBroadcastPacket(t_FMT_Uint32 uiPacketId);

	// Build Detect packet
	void					BuildDetectPacket(t_FMT_Uint32 uiSrcId, t_HoePacket &pck);

	// Build Connect packet
	void					BuildConnectPacket(t_FMT_Uint32 uiSrcId, t_FMT_Uint32 uiSN, t_HoePacket_Connect_Field& Params, t_HoePacket &pck);

	// Build Disconnect packet
	void					BuildDisconnectPacket(t_FMT_Uint32 uiSrcId, t_FMT_Uint32 uiSN, t_HoePacket &pck);

	// Build Send Command packet
	void					BuildSendCmdPacket(t_FMT_Uint32 uiSrcId, t_FMT_Uint32 uiSN, t_FMT_Uint8 *pucBuf, t_FMT_Uint16 usSize, t_HoePacket &pck);

	// Build Open Port packet
	void					BuildOpenPortPacket(t_FMT_Uint32 uiSrcId, t_FMT_Uint32 uiPortID, t_FMT_Uint32 uiPortNum, t_FMT_Uint32 uiSN, t_HoePacket& pck);

	// Build Close Port packet
	void					BuildClosePortPacket(t_FMT_Uint32 uiSrcId, t_FMT_Uint32 uiPortID, t_FMT_Uint32 uiPortNum, t_FMT_Uint32 uiSN, t_HoePacket& pck);

	// Build Keep Alive Port packet
	void					BuildKeepAlivePortPacket(t_FMT_Uint32 uiSrcId, t_FMT_Uint32 uiPortID, t_FMT_Uint32 uiPortNum, t_FMT_Uint32 uiSN, t_HoePacket& pck);

	// Build Data Buffer Port packet
	void					BuildDataBufPortPacket(t_FMT_Uint32 uiSrcId, t_FMT_Uint32 uiPortID, t_FMT_Uint32 uiPortNum, t_FMT_Uint32 uiSN, t_HoePacket& pck);

	// Build Reset TX Port packet
	void					BuildRstTxPortPacket(t_FMT_Uint32 uiSrcId, t_FMT_Uint32 uiPortID, t_FMT_Uint32 uiPortNum, t_FMT_Uint32 uiSN, t_HoePacket& pck);

	// Build Reset RX Port packet
	void					BuildRstRxPortPacket(t_FMT_Uint32 uiSrcId, t_FMT_Uint32 uiPortID, t_FMT_Uint32 uiPortNum, t_FMT_Uint32 uiSN, t_HoePacket& pck);

	// Build Configuration Port Packet
	void					BuildCfgPortPacket(t_FMT_Uint32 uiSrcId, t_FMT_Uint32 uiPortID, t_FMT_Uint32 uiPortNum, t_FMT_Uint32 uiSN, t_HoePacket& pck);

	// Build Control Context Port Packet
	void					BuildCctxPortPacket(t_FMT_Uint32 uiSrcId, t_FMT_Uint32 uiPortID, t_FMT_Uint32 uiPortNum, t_FMT_Uint32 uiSN, t_HoePacket& pck);

	// Build Data Context Port Packet
	void					BuildDctxPortPacket(t_FMT_Uint32 uiSrcId, t_FMT_Uint32 uiPortID, t_FMT_Uint32 uiPortNum, t_FMT_Uint32 uiSN, t_HoePacket& pck);
};

#endif