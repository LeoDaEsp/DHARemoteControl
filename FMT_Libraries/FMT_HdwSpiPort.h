// =====================================================================================
//	@file					FMT_HdwSpiPort.h
//	@date					14/04/2015
//	@author					Massimiliano Forzieri, Formatech Engineering S.R.L.
//
//	@brief					Abstract SPI Port
//
//	@version Project:		Formatech Hardware Manager C++ Library
//	@version Part number:	SWCD-0019-2014
//	@version Environment:	Windows, Linux and QNX
//	@version Language:		ANSI C++
// -----------------------------------------------------------------------------------
//	@version	Revision summary:
//	@version	Rev 1.1.0001	M.Forzieri		Initial Release
// =====================================================================================

#ifndef FMTDEF_HDW_SPIPORT_H
#define FMTDEF_HDW_SPIPORT_H


// =====================================================================================
//	INCLUDES
// =====================================================================================


#ifndef FMTDEF_GLOBAL_H
#include "FMT_Global.h"
#endif

#ifndef FMTDEF_OBJECT_H
#include "FMT_Object.h"
#endif

#ifndef FMTDEF_EXCEPTION_H
#include "FMT_Exception.h"
#endif

#ifndef FMTDEF_STRING_H
#include "FMT_String.h"
#endif

#ifndef FMTDEF_HDW_OBJECT_H
#include "FMT_HdwObject.h"
#endif

#ifndef FMTDEF_HDW_PORT_H
#include "FMT_HdwPort.h"
#endif


// *************************************************************************************
// *************************************************************************************
//	Class CFMT_HdwSpiPort
// *************************************************************************************
// *************************************************************************************

#define FMTDEF_HDW_SPIPORT_PORTNUM_INVALID		0

class FMTDEF_LIB_DLLSPEC CFMT_HdwSpiPort : public CFMT_HdwPort
{
	// =====================================================================================
	//	TYPES
	// =====================================================================================

protected:
public:

	// ---[ t_SpiMode ]-----------------------------------------------------

	enum t_SpiMode
	{
		e_SpiMode0	= 0,
		e_SpiMode1	= 1,
		e_SpiMode2	= 2,
		e_SpiMode3	= 3
	};


	// --- CParameters ----------------------------------------------------

	class FMTDEF_LIB_DLLSPEC CParameters : public CFMT_HdwPort::CParameters
	{
	public:

		t_FMT_Uint32	m_uiClockFrequency;
		t_SpiMode		m_SpiMode;
		t_FMT_Bool		m_bWriteAndRead;
		t_FMT_Bool		m_bCsContinuous;
		t_FMT_Bool		m_bCsLevel;
		t_FMT_Bool		m_bTxBitOrder;
		t_FMT_Bool		m_bRxBitOrder;
		t_FMT_Bool		m_bAutoStartBit;
		t_FMT_Bool		m_bStartBitLevel;
		t_FMT_Bool		m_bAlwaysRunClock;

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
	
	CFMT_HdwSpiPort(CFMT_HdwObject *pDevice, t_FMT_Uint32 uiDeviceId, const CFMT_String& sChannelId);
	virtual ~CFMT_HdwSpiPort();

	// =====================================================================================
	//	FUNCTIONS
	// =====================================================================================

protected:

	CParameters					m_Parameters;

public:

	virtual t_FMT_Uint32		Open(CFMT_HdwPort::CParameters *pParameters);
	virtual t_FMT_Uint32		Close();
	virtual t_FMT_Uint32		GetParameters(CParameters *pParameters);
	virtual t_FMT_Uint32		EnableService(t_FMT_Uint32 dwServiceType,CFMT_HdwService **ppService,CFMT_HdwService::CParameters *pParam);
};

#endif







