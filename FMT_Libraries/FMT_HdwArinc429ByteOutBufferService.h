// =====================================================================================
/**
 * @file					FMT_HdwArinc429InBufferService.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					04/09/2021
 * @brief					Abstract Hardware Arinc429 Input Byte Buffer Service
 *
 * @version	Project:		Formatech C++ Hardware Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][04/09/2021]
 */
// =====================================================================================

#ifndef FMTDEF_HDW_ARINC429BYTEOUTBUFFERSERVICE_H
#define FMTDEF_HDW_ARINC429BYTEOUTBUFFERSERVICE_H

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

#ifndef FMTDEF_HDW_ARINC429OUTBUFFERSERVICE_H
#include "FMT_HdwArinc429OutBufferService.h"
#endif



// =====================================================================================
//	DEFINES
// =====================================================================================



// *************************************************************************************
// *************************************************************************************
//	Class CFMT_HdwArinc429ByteOutBufferService
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_HdwArinc429ByteOutBufferService : public CFMT_HdwByteOutBufferService
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

	//! t_CrcFunction
	typedef t_FMT_Uint32 (t_CrcFunction)(t_FMT_Uint8 *pucBuf,t_FMT_Uint32 uiSize);



	// =====================================================================================
	//	VARIABLES
	// =====================================================================================

protected:

	//! Output Buffer Service
	CFMT_HdwArinc429OutBufferService		*m_pOutBufferService;

	//! Data Layer
	t_FMT_Uint32							m_uiDataLayer;

	//! SAL
	t_FMT_Uint8								m_ucSAL;

	//! CRC Function
	t_CrcFunction							*m_pCrcFunction;

public:

	// =====================================================================================
	// CONSTRUCTORS & DESTRUCTORS
	// =====================================================================================

public:

	//! Base Constructor
	CFMT_HdwArinc429ByteOutBufferService(CFMT_HdwObject *pPort);

	//! Destructor
	~CFMT_HdwArinc429ByteOutBufferService();

	// =====================================================================================
	//	FUNCTIONS
	// =====================================================================================

protected:

	//! Convert a byte buffer into Arinc429 words according to the data layer
	t_FMT_Uint32 ConvertBytesIntoLabels(t_FMT_Uint8 *pbtBuf,t_FMT_Uint32 uiSize,CFMT_HdwArinc429Message **ppMess,t_FMT_Uint32 *puiNom);

	//! Return the size of Arinc429 buffer in order to store uiByteSize bytes and according to data layer
	t_FMT_Uint32 GetArinc429BufferSize(t_FMT_Uint32 uiByteSize);

public:
	
	//! Hardware Timer handler
	virtual t_FMT_Uint32		HdwTimerHandler(t_FMT_Uint64 quiTimerCnt);

	//! Process a hardware event
	virtual t_FMT_Uint32		ProcessEvent(CFMT_HdwEvent* pEvent);

	//! Start the service
	virtual t_FMT_Uint32		Start();

	//! Stop the service
	virtual t_FMT_Uint32		Stop();

	//! Write dwSize bytes to the output buffer
	virtual t_FMT_Uint32		Write(t_FMT_Uint8 *pbtBuf,t_FMT_Uint32 dwSize,t_FMT_Uint32 dwTimeout);

	//! Return the number of bytes to be written
	virtual t_FMT_Uint32		GetBytesToBeWritten(t_FMT_Uint32& uiNob);

	//! Reset the output buffer
	virtual t_FMT_Uint32		ResetWriteBuffer();

};

#endif
