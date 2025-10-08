// =====================================================================================
/**
 * @file					CFMT_HdwCanOutBufferService.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					04/09/2025
 * @brief					Abstract Hardware CAN Output Byte Buffer Service
 *
 * @version	Project:		Formatech C++ Hardware Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][04/09/2025]
 */
// =====================================================================================

#ifndef FMTDEF_HDW_CANBYTEOUTBUFFERSERVICE_H
#define FMTDEF_HDW_CANBYTEOUTBUFFERSERVICE_H

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

#ifndef FMTDEF_HDW_BYTEOUTBUFFERSERVICE_H
#include "FMT_HdwByteOutBufferService.h"
#endif

#ifndef FMTDEF_HDW_CANOUTBUFFERSERVICE_H
#include "FMT_HdwCanOutBufferService.h"
#endif



// =====================================================================================
//	DEFINES
// =====================================================================================



// *************************************************************************************
// *************************************************************************************
//	Class CFMT_HdwCanByteOutBufferService
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_HdwCanByteOutBufferService : public CFMT_HdwByteOutBufferService
{

	// =====================================================================================
	//	TYPES
	// =====================================================================================

protected:

public:

	// t_DataLayer
	enum t_DataLayer
	{
		e_DataLayer_Raw		= 0
	};


	// CParameters
	class FMTDEF_LIB_DLLSPEC CParameters : public CFMT_HdwByteOutBufferService::CParameters
	{
	public:

		t_FMT_Uint32			m_uiDataLayer;

		t_FMT_Bool				m_bRawExtendedFrame;
		t_FMT_Uint32			m_uiRawId;


		CParameters();
	};


	// =====================================================================================
	//	VARIABLES
	// =====================================================================================

protected:

	// Output Buffer Service
	CFMT_HdwCanOutBufferService*			m_pOutBufferService;

	// Data Layer
	t_FMT_Uint32							m_uiDataLayer;

	// Raw Data Layer Parameters
	t_FMT_Bool								m_bRawExtendedFrame;
	t_FMT_Uint32							m_uiRawId;


public:

	// =====================================================================================
	// CONSTRUCTORS & DESTRUCTORS
	// =====================================================================================

public:

	// Base Constructor
	CFMT_HdwCanByteOutBufferService(CFMT_HdwObject *pPort);

	// Destructor
	~CFMT_HdwCanByteOutBufferService();

	// =====================================================================================
	//	FUNCTIONS
	// =====================================================================================

protected:

	// Get the buffer size in bytes
	t_FMT_Uint32				GetCanBufferSize(t_FMT_Uint32 uiByteSize);

	// Converts the received CAN frames into bytes, according to data layer RAW
	t_FMT_Uint32				ProcessCanFrames_Raw(t_FMT_Uint8* pucBytebuf, t_FMT_Uint32 uiByteBufLen, CFMT_HdwCanMessage** ppMess, t_FMT_Uint32& uiMessLen);

	// Converts a byte buffer into CAN frame buffer into bytes, according to data layer
	t_FMT_Uint32				ProcessCanFrames(t_FMT_Uint8* pucBytebuf, t_FMT_Uint32 uiByteBufLen, CFMT_HdwCanMessage** ppMess, t_FMT_Uint32& uiMessLen);

public:

	// Return the service parameters
	virtual t_FMT_Uint32		GetParameters(CParameters* pParameters);

	// Set the service parameters
	virtual t_FMT_Uint32		SetParameters(CParameters* pParameters);

	// Hardware Timer handler
	virtual t_FMT_Uint32		HdwTimerHandler(t_FMT_Uint64 quiTimerCnt);

	// Process a hardware event
	virtual t_FMT_Uint32		ProcessEvent(CFMT_HdwEvent* pEvent);

	// Start the service
	virtual t_FMT_Uint32		Start();

	// Stop the service
	virtual t_FMT_Uint32		Stop();

	// Write dwSize bytes to the output buffer
	virtual t_FMT_Uint32		Write(t_FMT_Uint8 *pbtBuf,t_FMT_Uint32 dwSize,t_FMT_Uint32 dwTimeout);

	// Return the number of bytes to be written
	virtual t_FMT_Uint32		GetBytesToBeWritten(t_FMT_Uint32& uiNob);

	// Reset the output buffer
	virtual t_FMT_Uint32		ResetWriteBuffer();

};

#endif
