// =====================================================================================
/**
 * @file					FMT_HdwArinc429ByteInBufferService.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					05/09/2021
 * @brief					Abstract Arinc429 Byte Input Buffer Service
 *
 * @version	Project:		Formatech C++ Hardware Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][05/09/2021]
 */
// =====================================================================================



#ifndef FMTDEF_HDW_ARINC429BYTEINBUFFERSERVICE_H
#define FMTDEF_HDW_ARINC429BYTEINBUFFERSERVICE_H

// =====================================================================================
//	INCLUDES
// =====================================================================================


#ifndef FMTDEF_CORE_H
#include "FMT_Core.h"
#endif

#ifndef FMTDEF_HDW_OBJECT_H
#include "FMT_HdwObject.h"
#endif

#ifndef FMTDEF_HDW_TIMER_H
#include "FMT_HdwTimer.h"
#endif

#ifndef FMTDEF_HDW_EVENT_H
#include "FMT_HdwEvent.h"
#endif

#ifndef FMTDEF_HDW_BYTEINBUFFERSERVICE_H
#include "FMT_HdwByteInBufferService.h"
#endif

#ifndef FMTDEF_HDW_ARINC429INBUFFERSERVICE_H
#include "FMT_HdwArinc429InBufferService.h"
#endif



// =====================================================================================
//	DEFINES
// =====================================================================================



// *************************************************************************************
// *************************************************************************************
//	Class CFMT_HdwArinc429ByteInBufferService
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_HdwArinc429ByteInBufferService : public CFMT_HdwByteInBufferService
{
	// =====================================================================================
	//	TYPES
	// =====================================================================================

protected:

public:

	//! t_DataLayer
	enum t_DataLayer
	{
		e_DataLayer_Arinc429p3_BitOriented		= 0
	};

	//! t_Arinc429p3_BitOriented_Status
	enum t_Arinc429p3_BitOriented_Status
	{
		e_Arinc429p3_BitOriented_Status_SOF		= 0,
		e_Arinc429p3_BitOriented_Status_Data	= 1,
		e_Arinc429p3_BitOriented_Status_EOF		= 2
	};

	//! t_CrcFunction
	typedef t_FMT_Uint32 (t_CrcFunction)(t_FMT_Uint8 *pucBuf, t_FMT_Uint32 uiSize);

	//! CParameters
	class FMTDEF_LIB_DLLSPEC CParameters : public CFMT_HdwByteInBufferService::CParameters
	{
	public:
		t_FMT_Uint32							m_uiDataLayer;
		t_FMT_Uint8								m_ucSAL;
		t_CrcFunction							*m_pCrcFunction;

		CParameters();
	};

	//! CByteBuffer
	class FMTDEF_LIB_DLLSPEC CByteBuffer : public CFMT_List<t_FMT_Uint8>
	{
	};

	// =====================================================================================
	//	VARIABLES
	// =====================================================================================

protected:

	//! Input buffer service
	CFMT_HdwArinc429InBufferService			*m_pInBufferService;

	//! Data Layer
	t_FMT_Uint32							m_uiDataLayer;

	//! SAL
	t_FMT_Uint8								m_ucSAL;

	//! CRC Function
	t_CrcFunction							*m_pCrcFunction;

	//! Byte Buffer
	CByteBuffer								m_ByteBuffer;

	//! Byte Packet Service
	t_FMT_Uint8								*m_pucPacketBuffer;

	//! Packet Byte Position
	t_FMT_Uint32							m_uiPacketPos;

	//! Packet Status
	t_FMT_Uint32							m_uiPacketStatus;

	//! Packet Number of Messages
	t_FMT_Uint32							m_uiPacketNom;

	//! Half Byte Flag
	t_FMT_Bool								m_bHalfByte;

	//! Packet CRC
	t_FMT_Uint32							m_uiPacketCrc;


public:


	// =====================================================================================
	// CONSTRUCTORS & DESTRUCTORS
	// =====================================================================================
	
	//! Base Constructor
	CFMT_HdwArinc429ByteInBufferService(CFMT_HdwObject *pPort);

	//! Desctructor
	virtual ~CFMT_HdwArinc429ByteInBufferService();

	// =====================================================================================
	//	FUNCTIONS
	// =====================================================================================

protected:

	//! Get the buffer size in bytes
	t_FMT_Uint32				GetArinc429BufferSize(t_FMT_Uint32 uiByteSize);

	//! Get the packet buffer size in bytes
	t_FMT_Uint32				GetPacketBufferSize();

	//! Process an Arinc429 Message packet
	t_FMT_Uint32				ProcessPacket_Arinc429p3_BitOriented(CFMT_HdwArinc429Message *pMess,t_FMT_Uint32 uiNom);

	//! Process an Arinc429 Message packet
	t_FMT_Uint32				ProcessPacket(CFMT_HdwArinc429Message *pMess,t_FMT_Uint32 uiNom);

	//! Store the received packet into byte buffer
	t_FMT_Uint32				StorePacket();

public:

	//! Return the service parameters
	virtual t_FMT_Uint32		GetParameters(CParameters *pParameters);

	//! Set the service parameters
	virtual t_FMT_Uint32		SetParameters(CParameters *pParameters);

	//! Hardware Timer handler
	virtual t_FMT_Uint32		HdwTimerHandler(t_FMT_Uint64 quiTimerCnt);

	//! Process a hardware event
	virtual t_FMT_Uint32		ProcessEvent(CFMT_HdwEvent* pEvent);

	//! Start the service
	virtual t_FMT_Uint32		Start();

	//! Stop the service
	virtual t_FMT_Uint32		Stop();

	//! Read dwSize bytes from the input buffer
	virtual t_FMT_Uint32		Read(t_FMT_Uint8 *pbtBuf,t_FMT_Uint32 dwSize,t_FMT_Uint32& dwReadSize);

	//! Return the number of bytes stored into input buffer
	virtual t_FMT_Uint32		GetReadBufferBytes(t_FMT_Uint32& uiNob);

	//! Reset the input buffer
	virtual t_FMT_Uint32		ResetReadBuffer();
};

#endif

