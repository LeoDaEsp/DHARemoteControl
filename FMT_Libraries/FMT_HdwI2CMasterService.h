// =====================================================================================
//	@file					FMT_HdwI2CMasterService.h
//	@date					24/05/2018
//	@author					Massimiliano Forzieri, Formatech Engineering S.R.L.
//
//	@brief					Abstract Hardware Can Output Buffer Service
//
//	@version Project:		Formatech Hardware Manager C++ Library
//	@version Part number:	SWCD-0019-2014
//	@version Environment:	Windows, Linux and QNX
//	@version Language:		ANSI C++
// -----------------------------------------------------------------------------------
//	@version	Revision summary:
//	@version	Rev 1.1.0001	M.Forzieri		Initial Release
// =====================================================================================



#ifndef LFMT_HDW_I2CMASTERSERVICE_H
#define LFMT_HDW_I2CMASTERSERVICE_H

// *************************************************************************************
// *************************************************************************************
//	Class CFMT_HdwI2CMasterService
// *************************************************************************************
// *************************************************************************************

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


class FMTDEF_LIB_DLLSPEC CFMT_HdwI2CMasterService : public CFMT_HdwService
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
	
	CFMT_HdwI2CMasterService(CFMT_HdwObject *pPort);
	virtual ~CFMT_HdwI2CMasterService();

	// =====================================================================================
	//	FUNCTIONS
	// =====================================================================================

protected:

public:

	virtual t_FMT_Uint32		GetParameters(CParameters *pParameters);
	virtual t_FMT_Uint32		SetParameters(CParameters *pParameters);

	virtual t_FMT_Uint32		Start();
	virtual t_FMT_Uint32		Stop();

	virtual	t_FMT_Uint32		Write(t_FMT_Uint8 ucAdd,t_FMT_Uint8 *puiWriteBuf,t_FMT_Uint32 uiWriteSize);
	virtual	t_FMT_Uint32		Read(t_FMT_Uint8 ucAdd,t_FMT_Uint8 *puiReadBuf,t_FMT_Uint32 uiReadSize);
};

#endif







