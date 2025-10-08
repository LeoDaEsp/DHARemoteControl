// =====================================================================================
/**
 * @file					FMT_HdwArinc429InBufferService.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					10/01/2020
 * @brief					Abstract Hardware Arinc429 Input Buffer Service
 *
 * @version	Project:		Formatech C++ Hardware Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][10/01/2020]
 */
// =====================================================================================



#ifndef LFMT_HDW_SPIMASTERSERVICE_H
#define LFMT_HDW_SPIMASTERSERVICE_H

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

#ifndef FMTDEF_HDW_SERVICE_H
#include "FMT_HdwService.h"
#endif


// *************************************************************************************
// *************************************************************************************
//	Class CFMT_HdwSpiMasterService
// *************************************************************************************
// *************************************************************************************


class FMTDEF_LIB_DLLSPEC CFMT_HdwSpiMasterService : public CFMT_HdwService
{
	// =====================================================================================
	//	TYPES
	// =====================================================================================

protected:
public:

	// --- CParameters ---------------------------------------------------------

	class FMTDEF_LIB_DLLSPEC CParameters : public CFMT_HdwService::CParameters
	{
	public:
		
		CParameters();
	};

	// =====================================================================================
	//	VARIABLES
	// =====================================================================================

protected:

public:


	// =====================================================================================
	// CONSTRUCTORS & DESTRUCTORS
	// =====================================================================================
	
	CFMT_HdwSpiMasterService(CFMT_HdwObject *pPort);
	virtual ~CFMT_HdwSpiMasterService();

	// =====================================================================================
	//	FUNCTIONS
	// =====================================================================================

protected:

public:

	virtual t_FMT_Uint32		GetParameters(CParameters *pParameters);
	virtual t_FMT_Uint32		SetParameters(CParameters *pParameters);

	virtual t_FMT_Uint32		Start();
	virtual t_FMT_Uint32		Stop();

	virtual	t_FMT_Uint32		Write(t_FMT_Uint8 *puiWriteBuf,t_FMT_Uint32 uiWriteSize, t_FMT_Uint32 uiTimeout = 500);
	virtual	t_FMT_Uint32		Read(t_FMT_Uint8 *puiReadBuf,t_FMT_Uint32 uiReadSize, t_FMT_Uint32 uiTimeout = 500);
	virtual	t_FMT_Uint32		WriteRead(t_FMT_Uint8 *puiWriteBuf,t_FMT_Uint32 uiWriteSize,t_FMT_Uint8 *puiReadBuf,t_FMT_Uint32 uiReadSize, t_FMT_Uint32 uiTimeout = 500);
};

#endif







