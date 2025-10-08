// =====================================================================================
/**
 * @file					FMT_CommMppClient.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					28/06/2022
 * @brief					Maintenance Point To Point Protocol Client
 *
 * @version	Project:		Formatech C++ Communication Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][28/06/2022]
 */
// =====================================================================================


#ifndef FMTDEF_COMM_MPPCLIENT_H
#define FMTDEF_COMM_MPPCLIENT_H

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
//	Class CFMT_CommMppClient
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_CommMppClient : public CFMT_CommMpp
{
	// =====================================================================================
	//	TYPES
	// =====================================================================================

protected:
public:


	// =====================================================================================
	//	VARIABLES
	// =====================================================================================

protected:

	// Current Buffer Transfer Status
	SBufferTransferStatus			m_BtpStatus;

	// Current Buffer Transfer Length
	t_FMT_Uint32					m_uiBtpBufLength;

	// Current Buffer Transfer Properties
	SBufferTransferProperty			m_BtpProperty;

	// Exit flag for Buffer Transfer thread 
	t_FMT_Bool						m_bBtpThreadExit;

	// Working Thread
	FMTDEF_COMM_MPP_THREAD			m_BtpThread;

	// Current Buffer Transfer Buffer
	t_FMT_Uint8						*m_pucBtpBuf;

	// Status Mutex
	CFMT_Mutex						m_StatusMutex;

public:



	// =====================================================================================
	// CONSTRUCTORS & DESTRUCTORS
	// =====================================================================================

public:

	CFMT_CommMppClient();
	virtual ~CFMT_CommMppClient();


	// =====================================================================================
	//	FUNCTIONS
	// =====================================================================================

protected:

	// Process a command list without BTP status checking
	virtual t_FMT_Uint32	ProcCommandListNoBtpCheck(t_FMT_Uint32 uiUnitAdd, t_FMT_Uint8 ucDevNum, SCommand* pComList, t_FMT_Uint32 uiNoc, 
														t_FMT_Uint32 uiTimeout, t_FMT_Uint32 uiRetries=0);

	// Receive a status packet
	virtual t_FMT_Uint32	ReceiveStatus(t_FMT_Uint32 uiUnitAdd, t_FMT_Uint8 ucDevNum, SCommand* pComList, t_FMT_Uint32 uiNoc, t_FMT_Uint32 uiTimeout);


	// Buffer Transfer Thread Functions
    #ifdef FMTDEF_COMPILE_OS_WINDOWS
	static	DWORD WINAPI	BufferWriteThreadFunction(LPVOID lpParam);
	static	DWORD WINAPI	BufferReadThreadFunction(LPVOID pParam);
	static	DWORD WINAPI	BufferEraseThreadFunction(LPVOID pParam);
    #endif

    #ifdef FMTDEF_COMPILE_OS_LINUX
    static	void*			BufferWriteThreadFunction(void* lpParam);
    static	void*			BufferReadThreadFunction(void* lpParam);
    static	void*			BufferEraseThreadFunction(void* lpParam);
    #endif

public:

	// Process a command list
	virtual t_FMT_Uint32	ProcCommandList(t_FMT_Uint32 uiUnitAdd, t_FMT_Uint8 ucDevNum, SCommand* pComList, t_FMT_Uint32 uiNoc, 
													t_FMT_Uint32 uiTimeout, t_FMT_Uint32 uiRetries = 0);

	// Create a buffer for buffer transfer
	virtual t_FMT_Uint8*	CreateTransferBuffer(t_FMT_Uint32 uiLength);

	virtual t_FMT_Uint8*	GetTransferBuffer();
	virtual t_FMT_Uint32	GetTransferBufferSize();
	virtual t_FMT_Uint32	GetBufferTransferStatus(SBufferTransferStatus *pStatus);
	virtual t_FMT_Uint32	GetBufferTransferProperty(SBufferTransferProperty *pBufferTransferProperty);

	// Write a memory buffer
	virtual t_FMT_Uint32	WriteMemoryBuffer(t_FMT_Uint32 uiUnitAdd, t_FMT_Uint8 ucDevNum, SBufferTransferProperty *pBufferTransferProperty);

	// Read a memory buffer
	virtual t_FMT_Uint32	ReadMemoryBuffer(t_FMT_Uint32 uiUnitAdd, t_FMT_Uint8 ucDevNum, SBufferTransferProperty *pBufferTransferProperty);

	// Erase a memory buffer
	virtual t_FMT_Uint32	EraseMemoryBuffer(t_FMT_Uint32 uiUnitAdd, t_FMT_Uint8 ucDevNum, SBufferTransferProperty *pBufferTransferProperty);

	// Stop a buffer transfer
	virtual t_FMT_Uint32	StopBufferOperation(t_FMT_Uint32 uiTimeout);

	// Check if all command of the provided list are correctly processed
	static t_FMT_Bool		CheckAllCommandStatus(CFMT_CommMpp::SCommand *pComs, t_FMT_Uint32 uiNC);

};

#endif
