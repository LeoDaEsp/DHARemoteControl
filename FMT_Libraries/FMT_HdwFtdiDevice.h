// =====================================================================================
/**
 * @file					FMT_HdwFmtFtdiDevice.h
 * @author					M.Forzieri, Formatech Engineering S.R.L.
 * @date					05/09/2021
 * @brief					Base FTDI Device
 *
 * @version	Project:		Formatech C++ Hardware Library
 * @version	Language:		ANSI C++
 * -----------------------------------------------------------------------------------
 * @version	Revision summary:
 * @version	1.1.0001		[Initial Release][M.Forzieri][05/09/2021]
 */
// =====================================================================================



#ifndef FMTDEF_HDW_FMTFTDIDEVICE_H
#define FMTDEF_HDW_FMTFTDIDEVICE_H

// =====================================================================================
//	INCLUDES
// =====================================================================================


#ifndef FMTDEF_CORE_H
#include "FMT_Core.h"
#endif

#ifndef FMTDEF_HDW_OBJECT_H
#include "FMT_HdwObject.h"
#endif

#ifndef FMTDEF_HDW_DEVICE_H
#include "FMT_HdwDevice.h"
#endif



// =====================================================================================
//	DEFINES
// =====================================================================================

#define	FMTDEF_HDW_FTDIDEVICE_CAL_CONV	__stdcall
#define FMTDEF_HDW_FTDIDEVICE_GET_FUNC(libHandle,symbol) GetProcAddress((HMODULE)libHandle,symbol)


// *************************************************************************************
// *************************************************************************************
//	Class CFMT_HdwFtdiDevice
// *************************************************************************************
// *************************************************************************************

class FMTDEF_LIB_DLLSPEC CFMT_HdwFtdiDevice : public CFMT_HdwDevice
{
	// =====================================================================================
	//	TYPES
	// =====================================================================================

protected:

public:

	// ---[ t_FT_Status ]-----------------------------------------------------

    typedef t_FMT_Uint32		t_FT_Status;

	// ---[ t_FT_Handle ]-----------------------------------------------------

	typedef void*				t_FT_Handle;

	// ---[ t_FT_Device ]-----------------------------------------------------

	typedef t_FMT_Uint32		t_FT_Device;


	// ---[ t_FT_DeviceListInfoNode ]-----------------------------------------------------

	typedef struct t_FT_DeviceListInfoNode_Tag
	{
        t_FMT_Uint32		m_ulFlags;
        t_FMT_Uint32		m_ulType;
        t_FMT_Uint32		m_ulID;
        t_FMT_Uint32		m_dwLocId;
        t_FMT_Char			m_pchSerialNumber[16];
        t_FMT_Char			m_pchDescription[64];
		t_FT_Handle			m_ftHandle;

	} t_FT_DeviceListInfoNode;


	// ---[ t_pFT_Func_GetLibraryVersion ]-----------------------------------------------------

    typedef t_FT_Status (FMTDEF_HDW_FTDIDEVICE_CAL_CONV *t_pFT_Func_GetLibraryVersion)(t_FMT_Uint32* lpdwVersion);

	// ---[ t_pFT_Func_m_pFT_CreateDeviceInfoList ]-----------------------------------------------------

    typedef t_FT_Status (FMTDEF_HDW_FTDIDEVICE_CAL_CONV *t_pFT_Func_CreateDeviceInfoList)(t_FMT_Uint32* lpdwNumDevs);

	// ---[ t_pFT_Func_GetDeviceInfoList ]-----------------------------------------------------

    typedef t_FT_Status (FMTDEF_HDW_FTDIDEVICE_CAL_CONV *t_pFT_Func_GetDeviceInfoList)(t_FT_DeviceListInfoNode *pDest, t_FMT_Uint32* lpdwNumDevs);

	// ---[ t_pFT_Func_Open ]-----------------------------------------------------

    typedef t_FT_Status (FMTDEF_HDW_FTDIDEVICE_CAL_CONV *t_pFT_Func_Open)(t_FMT_Int32 iDevice,t_FT_Handle *ftHandle);

	// ---[ t_pFT_Func_OpenEx ]-----------------------------------------------------

    typedef t_FT_Status (FMTDEF_HDW_FTDIDEVICE_CAL_CONV *t_pFT_Func_OpenEx)(void* pArg,t_FMT_Uint32 uiFlags,t_FT_Handle *ftHandle);

	// ---[ t_pFT_Func_Close ]-----------------------------------------------------

	typedef t_FT_Status (FMTDEF_HDW_FTDIDEVICE_CAL_CONV *t_pFT_Func_Close)(t_FT_Handle ftHandle);

	// ---[ t_pFT_Func_ResetDevice ]-----------------------------------------------------

	typedef t_FT_Status (FMTDEF_HDW_FTDIDEVICE_CAL_CONV *t_pFT_Func_ResetDevice) (t_FT_Handle ftHandle);

	// ---[ t_pFT_Func_Purge ]-----------------------------------------------------

    typedef t_FT_Status (FMTDEF_HDW_FTDIDEVICE_CAL_CONV *t_pFT_Func_Purge)(t_FT_Handle ftHandle,t_FMT_Uint32 dwMask);

	// ---[ t_pFT_Func_SetUSBParameters ]-----------------------------------------------------

    typedef t_FT_Status (FMTDEF_HDW_FTDIDEVICE_CAL_CONV *t_pFT_Func_SetUSBParameters)(t_FT_Handle ftHandle, t_FMT_Uint32 dwInTransferSize, t_FMT_Uint32 dwOutTransferSize);

	// ---[ t_pFT_Func_SetChars ]-----------------------------------------------------

    typedef t_FT_Status (FMTDEF_HDW_FTDIDEVICE_CAL_CONV *t_pFT_Func_SetChars)(t_FT_Handle ftHandle,t_FMT_Uint8 uEventCh, t_FMT_Uint8 uEventChEn, t_FMT_Uint8 uErrorCh, t_FMT_Uint8 uErrorChEn);

	// ---[ t_pFT_Func_SetTimeouts ]-----------------------------------------------------

    typedef t_FT_Status (FMTDEF_HDW_FTDIDEVICE_CAL_CONV *t_pFT_Func_SetTimeouts)(t_FT_Handle ftHandle,t_FMT_Uint32 dwReadTimeout, t_FMT_Uint32 dwWriteTimeout);

	// ---[ t_pFT_Func_SetLatencyTimer ]-----------------------------------------------------

    typedef t_FT_Status (FMTDEF_HDW_FTDIDEVICE_CAL_CONV *t_pFT_Func_SetLatencyTimer)(t_FT_Handle ftHandle,t_FMT_Uint8 ucTimer);

	// ---[ t_pFT_Func_SetBitmode ]-----------------------------------------------------

    typedef t_FT_Status (FMTDEF_HDW_FTDIDEVICE_CAL_CONV *t_pFT_Func_SetBitmode)(t_FT_Handle ftHandle,t_FMT_Uint8 ucMask, t_FMT_Uint8 ucMode);

	// ---[ t_pFT_Func_GetQueueStatus ]-----------------------------------------------------

    typedef t_FT_Status (FMTDEF_HDW_FTDIDEVICE_CAL_CONV *t_pFT_Func_GetQueueStatus) (t_FT_Handle ftHandle,t_FMT_Uint32* lpdwAmountInRxQueue);

	// ---[ t_pFT_Func_Read ]-----------------------------------------------------

    typedef t_FT_Status (FMTDEF_HDW_FTDIDEVICE_CAL_CONV *t_pFT_Func_Read) (t_FT_Handle ftHandle,void* lpBuffer, t_FMT_Uint32 dwBytesToRead,t_FMT_Uint32* lpdwBytesReturned);

	// ---[ t_pFT_Func_Write ]-----------------------------------------------------

    typedef t_FT_Status (FMTDEF_HDW_FTDIDEVICE_CAL_CONV *t_pFT_Func_Write) (t_FT_Handle ftHandle, void* lpBuffer, t_FMT_Uint32 dwBytesToWrite,t_FMT_Uint32* lpdwBytesWritten);

	// ---[ t_pFT_Func_GetDeviceInfo ]-----------------------------------------------------

    typedef t_FT_Status (FMTDEF_HDW_FTDIDEVICE_CAL_CONV *t_pFT_Func_GetDeviceInfo)(t_FT_Handle ftHandle,t_FT_Device *lpftDevice,t_FMT_Uint32* lpdwID,t_FMT_Int8* SerialNumber,t_FMT_Int8* Description, void* Dummy);

	// ---[ t_DriverFunctionPtrLst ]-----------------------------------------------------

	typedef struct SDriverFunctionPtrLst_Tag
	{
		t_pFT_Func_GetLibraryVersion		m_pFT_GetLibraryVersion;
		t_pFT_Func_CreateDeviceInfoList		m_pFT_CreateDeviceInfoList;
		t_pFT_Func_GetDeviceInfoList		m_pFT_GetDeviceInfoList;
		t_pFT_Func_Open						m_pFT_Open;
		t_pFT_Func_OpenEx					m_pFT_OpenEx;
		t_pFT_Func_Close					m_pFT_Close;
		t_pFT_Func_ResetDevice				m_pFT_ResetDevice;
		t_pFT_Func_Purge					m_pFT_Purge;
		t_pFT_Func_SetUSBParameters			m_pFT_SetUSBParameters;
		t_pFT_Func_SetChars					m_pFT_SetChars;
		t_pFT_Func_SetTimeouts				m_pFT_SetTimeouts;
		t_pFT_Func_SetLatencyTimer			m_pFT_SetLatencyTimer;
		t_pFT_Func_SetBitmode				m_pFT_SetBitmode;
		t_pFT_Func_GetQueueStatus			m_pFT_GetQueueStatus;
		t_pFT_Func_Read						m_pFT_Read;
		t_pFT_Func_Write					m_pFT_Write;
		t_pFT_Func_GetDeviceInfo			m_pFT_GetDeviceInfo;
	} t_DriverFunctionPtrLst;


	// ---[ t_FT_Return ]-----------------------------------------------------

	enum t_FT_Return
	{
		e_FT_OK,
		e_FT_INVALID_HANDLE,
		e_FT_DEVICE_NOT_FOUND,
		e_FT_DEVICE_NOT_OPENED,
		e_FT_IO_ERROR,
		e_FT_INSUFFICIENT_RESOURCES,
		e_FT_INVALID_PARAMETER,
		e_FT_INVALID_BAUD_RATE,
		e_FT_DEVICE_NOT_OPENED_FOR_ERASE,
		e_FT_DEVICE_NOT_OPENED_FOR_WRITE,
		e_FT_FAILED_TO_WRITE_DEVICE,
		e_FT_EEPROM_READ_FAILED,
		e_FT_EEPROM_WRITE_FAILED,
		e_FT_EEPROM_ERASE_FAILED,
		e_FT_EEPROM_NOT_PRESENT,
		e_FT_EEPROM_NOT_PROGRAMMED,
		e_FT_INVALID_ARGS,
		e_FT_NOT_SUPPORTED,
		e_FT_OTHER_ERROR,
		e_FT_DEVICE_LIST_NOT_READY,
	};

	// ---[ t_FT_OpenEx_Flags ]-----------------------------------------------------

	enum t_FT_OpenEx_Flags
	{
		e_FT_OpenEx_OpenBySerialNumber		= 1,
		e_FT_OpenEx_OpenByDescription		= 2,
		e_FT_OpenEx_OpenByLocation			= 4,
		e_FT_OpenEx_ListNumberOnly			= 0x80000000,
		e_FT_OpenEx_ListByIndex				= 0x40000000,
		e_FT_OpenEx_ListAll					= 0x20000000
	};

	// ---[ t_FT_PurgeBufferIndex ]-----------------------------------------------------

	enum t_FT_PurgeBufferIndex
	{
		e_FT_PurgeBufferIndex_Rx			= 1,
		e_FT_PurgeBufferIndex_Tx			= 2
	};

	// =====================================================================================
	//	VARIABLES
	// =====================================================================================

protected:

	//! DLL Function Pointers List
	t_DriverFunctionPtrLst					m_VarFunctionPtrLst;

	// Handle to D2XX driver
	#ifdef _WIN32
		static HANDLE m_hD2xx;
	#endif

	#ifdef __linux__
		static void *m_hD2xx;
	#endif

public:

	// =====================================================================================
	// CONSTRUCTORS & DESTRUCTORS
	// =====================================================================================
	
	//! Base Constructor
	CFMT_HdwFtdiDevice();

	//! Destructor
	virtual ~CFMT_HdwFtdiDevice();

	// =====================================================================================
	//	FUNCTIONS
	// =====================================================================================

protected:

	//! Initialize FTDI library
	t_FMT_Uint32	InitLibrary();

	//! Release FTDI library
	t_FMT_Uint32	ReleaseLibrary();

public:


};

#endif