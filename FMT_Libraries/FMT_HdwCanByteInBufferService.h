// =====================================================================================
/**
 * @file					FMT_HdwCanByteInBufferService.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					05/09/2021
 * @brief					Abstract CAN Byte Input Buffer Service
 *
 * @version	Project:		Formatech C++ Hardware Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][05/09/2021]
 */
// =====================================================================================



#ifndef FMTDEF_HDW_CANBYTEINBUFFERSERVICE_H
#define FMTDEF_HDW_CANBYTEINBUFFERSERVICE_H

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

#ifndef FMTDEF_HDW_CANINBUFFERSERVICE_H
#include "FMT_HdwCanInBufferService.h"
#endif



// =====================================================================================
//	DEFINES
// =====================================================================================



// *************************************************************************************
// *************************************************************************************
//	Class CFMT_HdwCanByteInBufferService
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_HdwCanByteInBufferService : public CFMT_HdwByteInBufferService
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
	class FMTDEF_LIB_DLLSPEC CParameters : public CFMT_HdwByteInBufferService::CParameters
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

	// Input buffer service
	CFMT_HdwCanInBufferService				*m_pInBufferService;

	// Data Layer
	t_FMT_Uint32							m_uiDataLayer;

	// Raw Data Layer Parameters
	t_FMT_Bool								m_bRawExtendedFrame;
	t_FMT_Uint32							m_uiRawId;

	// Byte Buffer
	CFMT_Uint8List							m_ByteBuffer;

public:


	// =====================================================================================
	// CONSTRUCTORS & DESTRUCTORS
	// =====================================================================================
	
	// Base Constructor
	CFMT_HdwCanByteInBufferService(CFMT_HdwObject *pPort);

	// Desctructor
	virtual ~CFMT_HdwCanByteInBufferService();

	// =====================================================================================
	//	FUNCTIONS
	// =====================================================================================

protected:

	// Get the buffer size in bytes
	t_FMT_Uint32				GetCanBufferSize(t_FMT_Uint32 uiByteSize);

	// Set the filter on CAN frames according to data layer
	void						SetCanFramesFilter();

	// Converts the received CAN frames into bytes, according to data layer RAW
	t_FMT_Uint32				ProcessCanFrames_Raw();

	// Converts the received CAN frames into bytes, according to data layer
	t_FMT_Uint32				ProcessCanFrames();

public:

	// Return the service parameters
	virtual t_FMT_Uint32		GetParameters(CParameters *pParameters);

	// Set the service parameters
	virtual t_FMT_Uint32		SetParameters(CParameters *pParameters);

	// Hardware Timer handler
	virtual t_FMT_Uint32		HdwTimerHandler(t_FMT_Uint64 quiTimerCnt);

	// Process a hardware event
	virtual t_FMT_Uint32		ProcessEvent(CFMT_HdwEvent* pEvent);

	// Start the service
	virtual t_FMT_Uint32		Start();

	// Stop the service
	virtual t_FMT_Uint32		Stop();

	// Read dwSize bytes from the input buffer
	virtual t_FMT_Uint32		Read(t_FMT_Uint8 *pbtBuf,t_FMT_Uint32 dwSize,t_FMT_Uint32& dwReadSize);

	// Return the number of bytes stored into input buffer
	virtual t_FMT_Uint32		GetReadBufferBytes(t_FMT_Uint32& uiNob);

	// Reset the input buffer
	virtual t_FMT_Uint32		ResetReadBuffer();
};

#endif

