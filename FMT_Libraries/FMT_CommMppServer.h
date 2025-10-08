// =====================================================================================
/**
 * @file					FMT_CommMppServer.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					28/06/2022
 * @brief					Maintenance Point To Point Protocol Server
 *
 * @version	Project:		Formatech C++ Communication Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][28/06/2022]
 */
// =====================================================================================


#ifndef FMTDEF_COMM_MPPSERVER_H
#define FMTDEF_COMM_MPPSERVER_H

// =====================================================================================
//	DEFINES
// =====================================================================================


// =====================================================================================
//	INCLUDES
// =====================================================================================

#ifndef FMTDEF_CORE_H
#include "FMT_Core.h"
#endif

#ifndef FMTDEF_HDW_H
#include "FMT_Hdw.h"
#endif

#ifndef FMTDEF_COMM_MPP_H
#include "FMT_CommMpp.h"
#endif


// *************************************************************************************
// *************************************************************************************
//	Class CFMT_CommMppServer
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_CommMppServer : public CFMT_CommMpp
{
	// =====================================================================================
	//	TYPES
	// =====================================================================================

protected:

    // --- CStatusList --------------------------------------------

    class FMTDEF_LIB_DLLSPEC CStatusList : public CFMT_List<CFMT_Uint8Vector*>
    {
    };


public:


	// =====================================================================================
	//	VARIABLES
	// =====================================================================================

protected:

public:

	// Info Descriptor
	SInfoDescriptor					*m_pInfoDescriptor;


	// =====================================================================================
	// CONSTRUCTORS & DESTRUCTORS
	// =====================================================================================

public:

	CFMT_CommMppServer();
	virtual ~CFMT_CommMppServer();

	// =====================================================================================
	//	FUNCTIONS
	// =====================================================================================

protected:

	// Format the status byte
	static t_FMT_Uint8		FormatStatusByte(t_FMT_Uint8 ucCmd, t_FMT_Uint8 ucStatus);

	// Send the status packet
	virtual t_FMT_Uint32	SendStatusPacket(t_FMT_Uint8 ucDevice, CStatusList& statuslist, t_FMT_Bool bIsBroadcast);

	// Process a command packet payload
	virtual t_FMT_Uint32	ProcessRxPayload(t_FMT_Uint8 ucDevice);

	// Process a write register command
	virtual t_FMT_Uint32	ProcessWriteRegister(t_FMT_Uint8 ucDevice, t_FMT_Uint8 ucRegAdd, t_FMT_Uint8 ucBen, t_FMT_Uint64 quiRegData);

	// Process a read register command
	virtual t_FMT_Uint32	ProcessReadRegister(t_FMT_Uint8 ucDevice,t_FMT_Uint8 ucRegAdd, t_FMT_Uint8 ucBen, t_FMT_Uint64& quiRegData);

	// Process a write memory command
	virtual t_FMT_Uint32	ProcessWriteMemory(t_FMT_Uint8 ucDevice,t_FMT_Uint32 uiMemAdd, t_FMT_Uint32 uiMemSize, t_FMT_Uint8 *pbtBuf);

	// Process a read memory command
	virtual t_FMT_Uint32	ProcessReadMemory(t_FMT_Uint8 ucDevice, t_FMT_Uint32 uiMemAdd, t_FMT_Uint32 uiMemSize, t_FMT_Uint8 *pbtBuf);
	
	// Process a erase memory command
	virtual t_FMT_Uint32	ProcessEraseMemory(t_FMT_Uint8 ucDevice, t_FMT_Uint32 uiMemAdd);

public:

	// Server receive
	virtual t_FMT_Uint32	Receive();
};


#endif
