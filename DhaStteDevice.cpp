

#include "stdafx.h"
#include "DhaStteDevice.h"

#define DHA5X5_UART_SIGNATURE				"M346_DHA5x5_UART"
#define DHA5X5_MAINLINK_DATA_SIGNATURE		"M346_DHA5x5_MAIN"
#define DHA5X5_MAINLINK_NOTIFY_SIGNATURE	"M346_DHA5x5_NOTY"
#define DHA5X5_SPI_DATA_SIGNATURE			"M346_DHA5x5_MSPI"

#define DHA5X5_MAINLINK_TX_DATA_PCK_LEN		64
#define DHA5X5_MAINLINK_RX_DATA_PCK_LEN		16
#define DHA5X5_MAINLINK_RX_NOTIFY_PCK_LEN	6

#define DHA5X5_MAX_SPI_PAYLOAD_LEN			(1024)
#define DHA5X5_MAX_SPI_DATA_PCK_LEN			(DHA5X5_MAX_SPI_PAYLOAD_LEN + 5)

// *************************************************************************************
// *************************************************************************************
//	Class CDhaStteDevice
// *************************************************************************************
// *************************************************************************************

// -----------------------------------------------------------------------------------
//	CDhaStteDevice::CDhaStteDevice
// -----------------------------------------------------------------------------------

CDhaStteDevice::CDhaStteDevice()
{
	DWORD		k;

	m_pMainLinkSocket = FMTDEF_NULL;
	m_pUartLinkSocket = FMTDEF_NULL;
	m_pSpiLinkSocket = FMTDEF_NULL;
	m_bConnected = FALSE;

	m_pMainLinkRxThread = FMTDEF_NULL;
	m_bMainLinkRxThreadStop = TRUE;

	m_pUartRxThread = FMTDEF_NULL;
	m_bUartRxThreadStop = TRUE;

	m_bRemoteAbort = FALSE;

	m_bHtrEnable = FALSE;

	m_bDoutReset = FALSE;
	m_bDoutShutdown = FALSE;

	for (k=0; k<2; k++)
	{
		m_pbDoutSpare[k] = FALSE;
		m_pbDoutGamma[k] = FALSE;
		m_pbHtrStat[k] = FALSE;
	}

	m_bDinBitOut = FALSE;
	m_bDinBitEvent = FALSE;

	m_pPatCol[0].SetRGB(255, 0, 0);
	m_pPatCol[1].SetRGB(0, 0, 0);

	m_bLvdsSel = FALSE;
	m_btPatternNum = 0;

	m_wAd590 = 0;

	m_sStteUartPort = "";
	m_pStteUartPort = NULL;

	m_StteUartParameters.m_uiPortNum = 0;
	m_StteUartParameters.m_ucParity = CFMT_HdwUartPort::e_Parity_Odd;
	m_StteUartParameters.m_ucStopBits = CFMT_HdwUartPort::e_StopBits_1Bit;
	m_StteUartParameters.m_uiBaudRate = 115200;
	m_StteUartParameters.m_ucByteSize = 8 ;
	m_StteUartParameters.m_ucFlowCtrl = CFMT_HdwUartPort::e_FlowControl_NoControl;



	m_sMaintLinkComPort = "";
	m_pMaintPort = NULL;

	m_MaintUartParameters.m_uiPortNum = 0;
	m_MaintUartParameters.m_ucParity = CFMT_HdwUartPort::e_Parity_Odd;
	m_MaintUartParameters.m_ucStopBits = CFMT_HdwUartPort::e_StopBits_1Bit;
	m_MaintUartParameters.m_uiBaudRate = 921600;
	m_MaintUartParameters.m_ucByteSize = 8 ;
	m_MaintUartParameters.m_ucFlowCtrl = CFMT_HdwUartPort::e_FlowControl_NoControl;
	m_btMaintLinkStatus = e_LinkStatus_Off;
	m_dwMaintLinkAlive = 0;



	m_HdwManager.AttachDevice(&m_StdUartDevice);
	m_HdwManager.Enumerate();


	m_ucSpiSpeed = 4;

	m_bLogEnable = FALSE;

	m_pMaintDataReg[CMaintMpp::e_MppReg_Brt].SetField(28, 7, 64);

	m_pMaintDataReg[CMaintMpp::e_MppReg_Pat].SetField(1, 4, 0);
	m_pMaintDataReg[CMaintMpp::e_MppReg_Pat].SetField(8, 8, 0xFF);
	m_pMaintDataReg[CMaintMpp::e_MppReg_Pat].SetField(16, 8, 0x00);
	m_pMaintDataReg[CMaintMpp::e_MppReg_Pat].SetField(24, 8, 0x00);
	m_pMaintDataReg[CMaintMpp::e_MppReg_Pat].SetField(32, 8, 0xFF);
	m_pMaintDataReg[CMaintMpp::e_MppReg_Pat].SetField(40, 8, 0xFF);
	m_pMaintDataReg[CMaintMpp::e_MppReg_Pat].SetField(48, 8, 0x00);
}



// -----------------------------------------------------------------------------------
//	CDhaStteDevice::~CDhaStteDevice
// -----------------------------------------------------------------------------------

CDhaStteDevice::~CDhaStteDevice()
{
	Disconnect();
}




// -----------------------------------------------------------------------------------
//	CDhaStteDevice::IsConnected
// -----------------------------------------------------------------------------------

BOOL CDhaStteDevice::IsConnected()
{
	return m_bConnected;
}


// -----------------------------------------------------------------------------------
//	CDhaStteDevice::IsTimeout
// -----------------------------------------------------------------------------------

BOOL CDhaStteDevice::IsTimeout()
{
	return (::GetTickCount() - m_dwLastMainLinkRxTime > DHASTTE_MAINLINK_ALIVE_TIMEOUT_MS);
}


// -----------------------------------------------------------------------------------
//	CDhaStteDevice::UartResetRx
// -----------------------------------------------------------------------------------

DWORD CDhaStteDevice::UartResetRx()
{
	m_UartRxMutex.Lock();

	m_UartRxBuffer.DeleteAll();

	m_UartRxMutex.Unlock();

	if (m_bRemoteAbort)
	{
		return e_Return_DeviceError;
	}

	return e_Return_OK;
}


// -----------------------------------------------------------------------------------
//	CDhaStteDevice::UartWrite
// -----------------------------------------------------------------------------------

DWORD CDhaStteDevice::UartWrite(BYTE *pbtBuf, DWORD dwBufLen)
{
	DWORD	ret;

	if (!m_bConnected || (m_pUartLinkSocket == NULL))
	{
		return e_Return_NotAllowed;
	}

	if (dwBufLen > 256)
	{
		return e_Return_InvalidParameter;
	}

	if (m_bRemoteAbort)
	{
		return e_Return_DeviceError;
	}

	// --- Send packet ---------------------------------------------

	BYTE				*pbtTxBuf;
	t_FMT_Uint32		uiSentBytes;

	pbtTxBuf = new BYTE[dwBufLen + 16];

	memcpy(pbtTxBuf, DHA5X5_UART_SIGNATURE, 16);
	memcpy(pbtTxBuf + 16, pbtBuf, dwBufLen);

	ret = m_pUartLinkSocket->SendDatagram(pbtTxBuf, 16 + dwBufLen, (CFMT_String)m_sIpAdd, DHA5X5_UART_PORT, &uiSentBytes);

	Log(pbtBuf, dwBufLen, TRUE);


	delete[] pbtTxBuf;

	return ret;
}


// -----------------------------------------------------------------------------------
//	CDhaStteDevice::UartGetRxLength
// -----------------------------------------------------------------------------------

DWORD CDhaStteDevice::UartGetRxLength()
{
	DWORD		dwRet;

	m_UartRxMutex.Lock();

	dwRet = m_UartRxBuffer.GetLength();

	m_UartRxMutex.Unlock();
	
	return dwRet;
}


// -----------------------------------------------------------------------------------
//	CDhaStteDevice::UartRead
// -----------------------------------------------------------------------------------

DWORD CDhaStteDevice::UartRead(BYTE *pbtBuf, DWORD dwBufLen, DWORD& dwReadLen)
{
	DWORD		dwLen;
	DWORD		k;

	if (!m_bConnected)
	{
		return e_Return_NotAllowed;
	}

	if (m_bRemoteAbort)
	{
		dwReadLen = 0;
		return e_Return_DeviceError;
	}


	m_UartRxMutex.Lock();

	dwLen = m_UartRxBuffer.GetLength();

	dwReadLen = min(dwLen, dwBufLen);

	for (k=0; k<dwReadLen; k++)
	{
		m_UartRxBuffer.ToStart();
		pbtBuf[k] = m_UartRxBuffer.CurItem();
		m_UartRxBuffer.DeleteItem();
	}

	Log(pbtBuf, dwReadLen, FALSE);


	m_UartRxMutex.Unlock();

	return e_Return_OK;
}


// -----------------------------------------------------------------------------------
//	CDhaStteDevice::WriteCommand
// -----------------------------------------------------------------------------------

DWORD CDhaStteDevice::WriteCommand(BYTE btCommand, BYTE btParam, DWORD dwTimeout, DWORD dwRetries)
{
	BYTE		btTXBuf;
	BYTE		btRXBuf;
	BOOL		bRet;
	DWORD		dwNRB;
	int			iStart;
	int			iEnd;
	BOOL		bAgain;
	DWORD		dwReadLen;
	DWORD		r;

	for (r=0; r<dwRetries; r++)
	{
	
		UartResetRx();


		// Send Operation Command ----------------------------	

		btTXBuf = btCommand;
		bRet = UartWrite(&btTXBuf, 1);

		iStart = ::GetTickCount();
		iEnd = iStart;
		bAgain = TRUE;

		while (bAgain && (iEnd - iStart < (int)dwTimeout))
		{
			dwNRB = UartGetRxLength();

			if (dwNRB > 0)
			{
				UartRead(&btRXBuf, 1, dwReadLen);

				if (btTXBuf == btRXBuf)
				{
					bAgain = FALSE;
				}
				else
				{
					Sleep(dwTimeout / 2);
					goto l_Retry;
				}
			}
			else
			{
				iEnd = ::GetTickCount();
			}
		}

		if (bAgain)
		{
			goto l_Retry;
		}



		// Send Parameter Command ----------------------------	

		btTXBuf = btParam;
		bRet = UartWrite(&btTXBuf, 1);

		iStart = ::GetTickCount();
		iEnd = iStart;
		bAgain = TRUE;

		while (bAgain && (iEnd - iStart < (int)dwTimeout))
		{
			dwNRB = UartGetRxLength();

			if (dwNRB>0)
			{
				UartRead(&btRXBuf, 1, dwReadLen);

				if (btTXBuf == btRXBuf)
				{
					bAgain = FALSE;
				}
				else
				{
					Sleep(dwTimeout / 2);
					goto l_Retry;
				}
			}
			else
			{
				iEnd = ::GetTickCount();
			}
		}

		if (bAgain)
		{
			goto l_Retry;
		}

		return e_Return_OK;



		l_Retry:
			CString			s;
			s.Format("WriteCommand retry %d\n", r+1);
			OutputDebugString(s);
	}

	return e_Return_Timeout;
}


// -----------------------------------------------------------------------------------
//	CDhaStteDevice::ReadCommand
// -----------------------------------------------------------------------------------

DWORD CDhaStteDevice::ReadCommand(BYTE btCommand, BYTE *pbtParam, DWORD dwTimeout, DWORD dwRetries)
{
	BYTE		btTXBuf;
	BYTE		pbtRXBuf[2];
	BOOL		bRet;
	DWORD		dwNRB;
	int			iStart;
	int			iEnd;
	BOOL		bAgain;
	DWORD		dwReadLen;
	DWORD		r;
	
	for (r=0; r<dwRetries + 1; r++)
	{
		UartResetRx();

		// Send Operation Command ----------------------------	
		btTXBuf = btCommand;
		bRet = UartWrite(&btTXBuf, 1);

		iStart = ::GetTickCount();
		iEnd = iStart;
		bAgain = TRUE;

		while (bAgain && (iEnd - iStart < (int)dwTimeout))
		{
			dwNRB = UartGetRxLength();

			if (dwNRB > 1)
			{
				UartRead(pbtRXBuf, 2, dwReadLen);

				if (btTXBuf == pbtRXBuf[0])
				{
					bAgain = FALSE;
				}
				else
				{
					Sleep(dwTimeout / 2);
					goto l_Retry;
				}
			}
			else
			{
				iEnd = ::GetTickCount();
			}
		}

		if (bAgain)
		{
			goto l_Retry;
		}

		*pbtParam = pbtRXBuf[1];

		return e_Return_OK;

		l_Retry:
			CString			s;
			s.Format("ReadCommand retry %d\n", r+1);
			OutputDebugString(s);
	}

	return e_Return_Timeout;
}


// -----------------------------------------------------------------------------------
//	CDhaStteDevice::TestNoParamCommand
// -----------------------------------------------------------------------------------

DWORD CDhaStteDevice::TestNoParamCommand(BYTE btCommand, DWORD dwTimeout)
{
	BYTE		btTXBuf;
	BYTE		btRXBuf[5];
	BOOL		bRet;
	DWORD		dwNRB;
	int			iStart;
	int			iEnd;
	BOOL		bAgain;
	DWORD		dwReadLen;

	UartResetRx();

	// Send Operation Command ----------------------------	

	btTXBuf = btCommand;
	bRet = UartWrite(&btTXBuf, 1);

	iStart = ::GetTickCount();
	iEnd = iStart;
	bAgain = TRUE;

	while (bAgain && (iEnd - iStart < (int)dwTimeout))
	{
		dwNRB = UartGetRxLength();

		if (dwNRB > 2)
		{
			UartRead(btRXBuf, 3, dwReadLen);

			if (btRXBuf[1] == '?')
			{
				if (btRXBuf[2] == e_Error_Unrecognized)
				{
					return e_Return_NotDefined;
				}
				else if (btRXBuf[2] == e_Error_Invalid)
				{
					return e_Return_InvalidObject;
				}
			}
		}
		else
		{
			iEnd = ::GetTickCount();
		}
	}

	if (bAgain)
	{
		return e_Return_Timeout;
	}

	return e_Return_OK;
}


// -----------------------------------------------------------------------------------
//	CDhaStteDevice::DoubleCommand
// -----------------------------------------------------------------------------------

DWORD CDhaStteDevice::DoubleCommand(BYTE btCommand, DWORD dwTimeout)
{
	BYTE		btTXBuf[2];
	BYTE		btRXBuf[5];
	BOOL		bRet;
	DWORD		dwNRB;
	int			iStart;
	int			iEnd;
	BOOL		bAgain;
	DWORD		dwReadLen;
	
	UartResetRx();

	// Send Operation Command ----------------------------	

	btTXBuf[0] = btCommand;
	btTXBuf[1] = btCommand;
	UartResetRx();
	bRet = UartWrite(btTXBuf, 2);

	iStart = ::GetTickCount();
	iEnd = iStart;
	bAgain = TRUE;

	while (bAgain && (iEnd - iStart < (int)dwTimeout))
	{
		dwNRB = UartGetRxLength();

		if (dwNRB > 1)
		{
			UartRead(btRXBuf, 2, dwReadLen);

			if (btRXBuf[0] == '?')
			{
				if (btRXBuf[1] == e_Error_Unrecognized)
				{
					return e_Return_NotDefined;
				}
				else if (btRXBuf[1] == e_Error_Invalid)
				{
					return e_Return_InvalidObject;
				}
			}
		}
		else
		{
			iEnd = ::GetTickCount();
		}
	}

	if (bAgain)
	{
		return e_Return_Timeout;
	}

	return e_Return_OK;
}


// -----------------------------------------------------------------------------------
//	CDhaStteDevice::UnrecognizedCommand
// -----------------------------------------------------------------------------------

DWORD CDhaStteDevice::UnrecognizedCommand(BYTE btCommand, DWORD dwTimeout)
{
	BYTE		btTXBuf;
	BYTE		btRXBuf[5];
	BOOL		bRet;
	DWORD		dwNRB;
	int			iStart;
	int			iEnd;
	BOOL		bAgain;
	DWORD		dwReadLen;

	UartResetRx();

	// Send Operation Command ----------------------------	
	btTXBuf = btCommand;
	bRet = UartWrite(&btTXBuf, 1);

	iStart = ::GetTickCount();
	iEnd = iStart;
	bAgain = TRUE;

	while (bAgain && (iEnd - iStart < (int)dwTimeout))
	{
		dwNRB = UartGetRxLength();

		if (dwNRB > 1)
		{
			UartRead(btRXBuf, 2, dwReadLen);

			if (btRXBuf[0] == '?')
			{
				if (btRXBuf[1] == e_Error_Unrecognized)
				{
					return e_Return_NotDefined;
				}
				else if (btRXBuf[1] == e_Error_Invalid)
				{
					return e_Return_InvalidObject;
				}
			}
		}
		else
		{
			iEnd = ::GetTickCount();
		}
	}

	if (bAgain)
	{
		return e_Return_Timeout;
	}

	return e_Return_OK;
}




// -----------------------------------------------------------------------------------
//	CDhaStteDevice::OneMessCommand
// -----------------------------------------------------------------------------------

DWORD CDhaStteDevice::OneMessCommand(BYTE btCommand, DWORD dwTimeout)
{
	BYTE		btTXBuf;
	BYTE		btRXBuf;
	BOOL		bRet;
	DWORD		dwNRB;
	int			iStart;
	int			iEnd;
	BOOL		bAgain;
	DWORD		dwReadLen;

	// Send Operation Command ----------------------------	

	btTXBuf = btCommand;
	UartResetRx();
	bRet = UartWrite(&btTXBuf, 1);

	iStart = ::GetTickCount();
	iEnd = iStart;
	bAgain = TRUE;

	while (bAgain && (iEnd - iStart < (int)dwTimeout))
	{
		dwNRB = UartGetRxLength();

		if (dwNRB > 0)
		{
			UartRead(&btRXBuf, 1, dwReadLen);

			if (btTXBuf == btRXBuf)
			{
				bAgain = FALSE;
			}
			else
			{
				return e_Return_ProtocolError;

			}
		}
		else
		{
			iEnd = ::GetTickCount();
		}
	}

	if (bAgain)
	{
		return e_Return_Timeout;
	}

	return e_Return_OK;
}


// -------------------------------------------------------------
//	CDhaStteDevice::MainLinkRxThreadFunction
// -------------------------------------------------------------

UINT CDhaStteDevice::MainLinkRxThreadFunction(LPVOID pParam)
{
	CDhaStteDevice*		pMe = (CDhaStteDevice*)pParam;

	while (!pMe->m_bMainLinkRxThreadStop)
	{
		pMe->PerformMainLinkRx();
	}
	
	return 0;
}


// -------------------------------------------------------------
//	CDhaStteDevice::UartRxThreadFunction
// -------------------------------------------------------------

UINT CDhaStteDevice::UartRxThreadFunction(LPVOID pParam)
{
	CDhaStteDevice*		pMe = (CDhaStteDevice*)pParam;

	while (!pMe->m_bUartRxThreadStop)
	{
		pMe->PerformUartRx();
	}
	
	return 0;
}


// -------------------------------------------------------------
//	CDhaStteDevice::PerformUartRx
// -------------------------------------------------------------

DWORD CDhaStteDevice::PerformUartRx()
{
	CFMT_IpAddress		SrcAdd;
	t_FMT_Uint16		usSrcPort;
	t_FMT_Uint32		uiRcvBytes;
	t_FMT_Uint32		ret;
	DWORD				k;

	ret = m_pUartLinkSocket->ReadDatagram(m_pucUartRxPacket, DHASTTE_MAX_UART_PACKET_LEN, &SrcAdd, &usSrcPort, &uiRcvBytes, 10);

	if (ret != e_Return_OK)
	{
		return e_Return_OK;
	}

	if (m_sIpAdd != SrcAdd.ToString())
	{
		return e_Return_OK;
	}

	if (uiRcvBytes <= 16)
	{
		return e_Return_OK;
	}

	if (memcmp(m_pucUartRxPacket, DHA5X5_UART_SIGNATURE, 16) != 0)
	{
		return e_Return_OK;
	}


	m_UartRxMutex.Lock();

	for (k=0; k<uiRcvBytes - 16; k++)
	{
		m_UartRxBuffer += m_pucUartRxPacket[16 + k];
	}

	m_UartRxMutex.Unlock();

	return e_Return_OK;
}


// -------------------------------------------------------------
//	CDhaStteDevice::PerformMainLinkRx
// -------------------------------------------------------------

DWORD CDhaStteDevice::PerformMainLinkRx()
{
	CFMT_IpAddress		SrcAdd;
	t_FMT_Uint16		usSrcPort;
	t_FMT_Uint32		uiRcvBytes;
	t_FMT_Uint32		ret;

	ret = m_pMainLinkSocket->ReadDatagram(m_pucMainLinkRxPacket, DHASTTE_MAX_MAINLINK_PACKET_LEN, &SrcAdd, &usSrcPort, &uiRcvBytes, 50);

	if (ret != e_Return_OK)
	{
		return e_Return_OK;
	}

	if (m_sIpAdd != SrcAdd.ToString())
	{
		return e_Return_OK;
	}

	if (uiRcvBytes <= 16)
	{
		return e_Return_OK;
	}

	if (memcmp(m_pucMainLinkRxPacket, DHA5X5_MAINLINK_DATA_SIGNATURE, 16) == 0)
	{
		ProcessMainLinkRxDataPacket();
	}
	else if (memcmp(m_pucMainLinkRxPacket, DHA5X5_MAINLINK_NOTIFY_SIGNATURE, 16) == 0)
	{
		ProcessMainLinkRxNotifyPacket();
	}

	return e_Return_OK;
}


// -------------------------------------------------------------
//	CDhaStteDevice::SetDayLuminance
// -------------------------------------------------------------

DWORD CDhaStteDevice::SetDayLuminance(BYTE btBrt, DWORD dwTimeout)
{
	return WriteCommand(e_Code_SetDayLuminance, btBrt, dwTimeout);
}


// -------------------------------------------------------------
//	CDhaStteDevice::SetNightLuminance
// -------------------------------------------------------------

DWORD CDhaStteDevice::SetNightLuminance(BYTE btBrt, DWORD dwTimeout)
{
	return WriteCommand(e_Code_SetNightLuminance, btBrt, dwTimeout);
}


// -------------------------------------------------------------
//	CDhaStteDevice::SetMaintReg
// -------------------------------------------------------------

DWORD CDhaStteDevice::SetMaintReg(BOOL bHeater, DWORD dwTimeout)
{
	BYTE	btData;

	btData = 0;

	if (bHeater)
	{
		btData|=0x01;
	}

	return WriteCommand(e_Code_MaintWrite, btData, dwTimeout);
}


// -------------------------------------------------------------
//	CDhaStteDevice::SetFanCtrl
// -------------------------------------------------------------

DWORD CDhaStteDevice::SetFanCtrl(BYTE btFanOnOff, DWORD dwTimeout)
{
	return WriteCommand(e_Code_SetFanCtrl, btFanOnOff, dwTimeout);
}


// -------------------------------------------------------------
//	CDhaStteDevice::ReadLuminanceSensor
// -------------------------------------------------------------

DWORD CDhaStteDevice::ReadLuminanceSensor(BYTE *pbtLEDLuminance, DWORD dwTimeout)
{
	return ReadCommand(e_Code_ReadLuminanceSensor, pbtLEDLuminance, dwTimeout);
}


// -------------------------------------------------------------
//	CDhaStteDevice::ReadBacklTemp
// -------------------------------------------------------------

DWORD CDhaStteDevice::ReadBacklTemp(BYTE *pbtBacklTemp, DWORD dwTimeout)
{
	return ReadCommand(e_Code_ReadBacklTemp, pbtBacklTemp, dwTimeout);
}


// -------------------------------------------------------------
//	CDhaStteDevice::ReadLampLEDsCtrlStatus
// -------------------------------------------------------------

DWORD CDhaStteDevice::ReadLampLEDsCtrlStatus(BYTE *pbtLampCtrlStatus, DWORD dwTimeout)
{
	return ReadCommand(e_Code_ReadLamp_LEDsCtrlStatus, pbtLampCtrlStatus, dwTimeout);
}


// -------------------------------------------------------------
//	CDhaStteDevice::ReadBITStatus
// -------------------------------------------------------------

DWORD CDhaStteDevice::ReadBITStatus(BYTE *pbtBIT_Status, DWORD dwTimeout)
{
	return ReadCommand(e_Code_ReadBITStatus, pbtBIT_Status, dwTimeout);
}


// -------------------------------------------------------------
//	CDhaStteDevice::ReadFanStatus
// -------------------------------------------------------------

DWORD CDhaStteDevice::ReadFanStatus(BYTE *pbtFanMode, DWORD dwTimeout)
{
	return ReadCommand(e_Code_ReadFanStatus, pbtFanMode, dwTimeout);
}


// -------------------------------------------------------------
//	CDhaStteDevice::ReadHeaterStatus
// -------------------------------------------------------------

DWORD CDhaStteDevice::ReadHeaterStatus(BYTE *pbtHeaterMode, DWORD dwTimeout)
{
	return ReadCommand(e_Code_ReadHeaterStatus, pbtHeaterMode, dwTimeout);
}


// -------------------------------------------------------------
//	CDhaStteDevice::ReadSWVersion
// -------------------------------------------------------------

DWORD CDhaStteDevice::ReadSWVersion(BYTE *pbtSWVersion, DWORD dwTimeout)
{
	return ReadCommand(e_Code_ReadSWVersion, pbtSWVersion, dwTimeout);
}


// -------------------------------------------------------------
//	CDhaStteDevice::ReadLuminanceComm
// -------------------------------------------------------------

DWORD CDhaStteDevice::ReadLuminanceComm(BYTE *pbtLuminance, DWORD dwTimeout)
{
	return ReadCommand(e_Code_ReadLuminanceComm, pbtLuminance, dwTimeout);
}


// -------------------------------------------------------------
//	CDhaStteDevice::DefaultWarmStartComm
// -------------------------------------------------------------

DWORD CDhaStteDevice::DefaultWarmStartComm(DWORD dwTimeout)
{
	return OneMessCommand(e_Code_DefaultWarmStartComm, dwTimeout);
}


// -------------------------------------------------------------
//	CDhaStteDevice::DayModeWarmStartComm
// -------------------------------------------------------------

DWORD CDhaStteDevice::DayModeWarmStartComm(BYTE btBacklLum, DWORD dwTimeout)
{
	return WriteCommand(e_Code_DayModeWarmStartComm, btBacklLum, dwTimeout);
}


// -------------------------------------------------------------
//	CDhaStteDevice::NightModeWarmStartComm
// -------------------------------------------------------------

DWORD CDhaStteDevice::NightModeWarmStartComm(BYTE btBacklLum, DWORD dwTimeout)
{
	return WriteCommand(e_Code_NightModeWarmStartComm, btBacklLum, dwTimeout);
}


// -------------------------------------------------------------
//	CDhaStteDevice::NightModeWarmStartComm
// -------------------------------------------------------------

DWORD CDhaStteDevice::SW_ResetRestart_Comm(DWORD dwTimeout)
{
	return OneMessCommand(e_Code_SW_ResetRestart_Comm, dwTimeout);
}


// -------------------------------------------------------------
//	CDhaStteDevice::SetPWM
// -------------------------------------------------------------

DWORD CDhaStteDevice::SetPWM(BYTE btNum, WORD wPWM, DWORD dwTimeout)
{
	DWORD	dwRet;
	BYTE	btCom;
	BYTE	btParam;

	btCom = e_Code_MaintSetPWM1Low + btNum;
	btParam = (BYTE)wPWM;
	dwRet = WriteCommand(btCom, btParam, dwTimeout);

	if (dwRet != e_Return_OK)
	{
		return dwRet;
	}

	btCom = btCom - 4;
	btParam = (BYTE)(wPWM >> 8);

	return WriteCommand(btCom, btParam, dwTimeout);
}


// -------------------------------------------------------------
//	CDhaStteDevice::SetVDC
// -------------------------------------------------------------

DWORD CDhaStteDevice::SetVDC(BYTE btNum, WORD wVDC, DWORD dwTimeout)
{
	DWORD	dwRet;
	BYTE	btCom;
	BYTE	btParam;

	btCom = e_Code_MaintSetVDC1Low + btNum;
	btParam = (BYTE)wVDC;
	dwRet = WriteCommand(btCom, btParam, dwTimeout);

	if (dwRet != e_Return_OK)
	{
		return dwRet;
	}

	btCom = btCom - 4;
	btParam=(BYTE)(wVDC >> 8);

	return WriteCommand(btCom, btParam, dwTimeout);
}


// -------------------------------------------------------------
//	CDhaStteDevice::ReadAnalogs
// -------------------------------------------------------------

DWORD CDhaStteDevice::ReadAnalogs(WORD* pwAIN, DWORD dwTimeout)
{
	BYTE		btTXBuf;
	BYTE		pbtRXBuf[50];
	BOOL		bRet;
	DWORD		dwNRB;
	DWORD		k;
	int			iStart;
	int			iEnd;
	BOOL		bAgain;
	DWORD		dwReadLen;

	// Send Operation Command ----------------------------	
	UartResetRx();
	btTXBuf = e_Code_MaintRead;
	bRet = UartWrite(&btTXBuf, 1);

	iStart = ::GetTickCount();
	iEnd = iStart;
	bAgain = TRUE;

	while (bAgain && (iEnd - iStart < (int)dwTimeout))
	{
		dwNRB = UartGetRxLength();

		if (dwNRB > 16)
		{
			UartRead(pbtRXBuf, 17, dwReadLen);

			if (btTXBuf == pbtRXBuf[0])
			{
				bAgain = FALSE;
			}
			else
			{
				return e_Return_ProtocolError;
			}
		}
		else
		{
			iEnd=::GetTickCount();
		}
	}

	if (bAgain)
	{
		return e_Return_Timeout;
	}

	for (k=0; k<8; k++)
	{
		pwAIN[k] = (WORD)pbtRXBuf[2*k + 1];
		pwAIN[k] |= (((WORD)(pbtRXBuf[2*k + 2])) << 8);
	}

	return e_Return_OK;
}


// -------------------------------------------------------------
//	CDhaStteDevice::SendMainLinkPacket
// -------------------------------------------------------------

DWORD CDhaStteDevice::SendMainLinkPacket()
{
	if (m_pMainLinkSocket == NULL)
	{
		return e_Return_OK;
	}

	BYTE				pbtTxBuf[DHA5X5_MAINLINK_TX_DATA_PCK_LEN + 16];
	t_FMT_Uint32		uiSentBytes;


	memset(pbtTxBuf, 0, DHA5X5_MAINLINK_TX_DATA_PCK_LEN + 16);

	// Connect Flag
	if (m_bConnected)
	{	
		pbtTxBuf[16 + 0] = 0x01;
	}
	else
	{	
		pbtTxBuf[16 + 0] = 0x00;
	}

	// Use UART with inverted pin logic
	pbtTxBuf[16 + 0] |= 0x02;

	// Heater Enable
	FMT::SetBit(pbtTxBuf[16 + 1], 0, m_bHtrEnable);

	///FMT::SetField(pbtTxBuf[16 + 1], 1, 3, 2);
	FMT::SetField(pbtTxBuf[16 + 1], 1, 3, 7);

	// Discretes
	FMT::SetBit(pbtTxBuf[16 + 2], 0, m_bDoutReset);
	FMT::SetBit(pbtTxBuf[16 + 2], 1, m_bDoutShutdown);
	FMT::SetBit(pbtTxBuf[16 + 2], 2, m_pbDoutGamma[0]);
	FMT::SetBit(pbtTxBuf[16 + 2], 3, m_pbDoutGamma[1]);
	FMT::SetBit(pbtTxBuf[16 + 2], 4, m_pbDoutSpare[0]);
	FMT::SetBit(pbtTxBuf[16 + 2], 5, m_pbDoutSpare[1]);

	// Video
	FMT::SetBit(pbtTxBuf[16 + 3], 0, m_bLvdsSel);
	FMT::SetField(pbtTxBuf[16 + 3], 1, 6, m_btPatternNum);
	
	pbtTxBuf[16 + 4] = m_pPatCol[0].GetR();
	pbtTxBuf[16 + 5] = m_pPatCol[0].GetG();
	pbtTxBuf[16 + 6] = m_pPatCol[0].GetB();

	pbtTxBuf[16 + 7] = m_pPatCol[1].GetR();
	pbtTxBuf[16 + 8] = m_pPatCol[1].GetG();
	pbtTxBuf[16 + 9] = m_pPatCol[1].GetB();

	// Complete the packet

	memcpy(pbtTxBuf, DHA5X5_MAINLINK_DATA_SIGNATURE, 16);

	return m_pMainLinkSocket->SendDatagram(pbtTxBuf, DHA5X5_MAINLINK_TX_DATA_PCK_LEN + 16, (CFMT_String)m_sIpAdd, DHA5X5_MAINLINK_PORT, &uiSentBytes);
}


// -------------------------------------------------------------
//	CDhaStteDevice::ProcessMainLinkRxDataPacket
// -------------------------------------------------------------

DWORD CDhaStteDevice::ProcessMainLinkRxDataPacket()
{
	m_dwLastMainLinkRxTime = ::GetTickCount();

	m_MainLinkMutex.Lock();

	m_bDinBitOut = FMT::GetBit(m_pucMainLinkRxPacket[16 + 1], 0);
	m_bDinBitEvent = FMT::GetBit(m_pucMainLinkRxPacket[16 + 1], 1);
	m_pbHtrStat[0] = FMT::GetBit(m_pucMainLinkRxPacket[16 + 1], 2);
	m_pbHtrStat[1] = FMT::GetBit(m_pucMainLinkRxPacket[16 + 1], 3);

	m_wAd590 = FMT::Uint16FromBuf(&m_pucMainLinkRxPacket[16 + 2]);

	m_MainLinkMutex.Unlock();

	return e_Return_OK;
}


// -------------------------------------------------------------
//	CDhaStteDevice::ProcessMainLinkRxNotifyPacket
// -------------------------------------------------------------

DWORD CDhaStteDevice::ProcessMainLinkRxNotifyPacket()
{
	if (m_pucMainLinkRxPacket[16 + 0] == 0xE0)
	{
		m_bRemoteAbort = TRUE;
	}

	return e_Return_OK;
}


// -----------------------------------------------------------------------------------
//	CDhaStteDevice::LoadSettings
// -----------------------------------------------------------------------------------

void CDhaStteDevice::LoadSettings()
{
	CString sSection;
	CString sItem;

	sSection=_T("Hardware");

	sItem=_T("IP_ADD");
	m_sIpAdd = (AfxGetApp()->GetProfileString(sSection, sItem, "192.168.1.65"));

	sItem=_T("STTE_COM");
	m_sStteUartPort = (AfxGetApp()->GetProfileString(sSection, sItem, ""));

	sItem=_T("MAINT_COM");
	m_sMaintLinkComPort = (AfxGetApp()->GetProfileString(sSection, sItem, ""));

	sSection=_T("Data");

	sItem=_T("LOG_PATH");
	m_sLogFilePath = (AfxGetApp()->GetProfileString(sSection, sItem, ""));

	// DEBUG
	m_sLogFilePath = "prova.txt";
}


// -----------------------------------------------------------------------------------
//	CDhaStteDevice::SaveSettings
// -----------------------------------------------------------------------------------

void CDhaStteDevice::SaveSettings()
{
	CString sSection;
	CString sItem;

	sSection=_T("Hardware");

	sItem=_T("IP_ADD");
	AfxGetApp()->WriteProfileString(sSection, sItem, m_sIpAdd);

	sItem=_T("STTE_COM");
	AfxGetApp()->WriteProfileString(sSection, sItem, m_sStteUartPort.GetStringC());

	sItem=_T("MAINT_COM");
	AfxGetApp()->WriteProfileString(sSection, sItem, m_sMaintLinkComPort.GetStringC());

	sSection=_T("Data");

	sItem=_T("LOG_PATH");
	AfxGetApp()->WriteProfileString(sSection, sItem, m_sLogFilePath.GetStringC());
}


// -----------------------------------------------------------------------------------
//	CDhaStteDevice::ProgramIp
// -----------------------------------------------------------------------------------

DWORD CDhaStteDevice::ProgramIp(BYTE *pbtIP)
{
	DWORD			ret;
	BYTE			pbtTxBuf[20];
	BYTE			pbtRxBuf[20];
	CFMT_Crc		Crc;
	WORD			wCalcCrc;
	t_FMT_Uint32	dwReadSize;

	Crc.Create(CFMT_Crc::e_StdCrc_Crc16_CcittFalse);

	ret = ConnectStteUart();
	if (ret != e_Return_OK)
	{
		return ret;
	}

	pbtTxBuf[0] = 0xA5;
	pbtTxBuf[1] = 0xC1;

	pbtTxBuf[5] = pbtIP[0];
	pbtTxBuf[4] = pbtIP[1];
	pbtTxBuf[3] = pbtIP[2];
	pbtTxBuf[2] = pbtIP[3];

	Crc.Compute((t_FMT_Uint8*)pbtTxBuf, 6, &wCalcCrc);

	FMT::Uint16ToBuf(wCalcCrc, &pbtTxBuf[6]);

	ret = m_pInService->ResetReadBuffer();
	if (ret != e_Return_OK)
	{
		goto l_HdwFail;
	}

	ret = m_pOutService->Write(pbtTxBuf, 8, 1000);
	if (ret != e_Return_OK)
	{
		goto l_HdwFail;
	}

	Sleep(200);
	ret = m_pInService->Read(pbtRxBuf, 4, dwReadSize);

	if (ret != e_Return_OK)
	{
		goto l_HdwFail;
	}

	if (dwReadSize != 4)
	{
		goto l_DevFail;
	}

	if (pbtRxBuf[0] != 0xA5)
	{
		goto l_DevFail;
	}

	Crc.Compute((t_FMT_Uint8*)pbtRxBuf, 2, &wCalcCrc);

	if (wCalcCrc != FMT::Uint16FromBuf(pbtRxBuf + 2))
	{
		goto l_DevFail;
	}

	if (pbtRxBuf[1] != 0xE0)
	{
		goto l_MemFail;
	}

	DisconnectStteUart();
	return e_Return_OK;


l_HdwFail:

	DisconnectStteUart();
	return e_Return_HardwareError;


l_DevFail:

	DisconnectStteUart();
	return e_Return_DeviceError;


l_MemFail:

	DisconnectStteUart();
	return e_Return_WriteError;
}


// -----------------------------------------------------------------------------------
//	CDhaStteDevice::ProgramSn
// -----------------------------------------------------------------------------------

DWORD CDhaStteDevice::ProgramSn(BYTE btSn)
{
	DWORD			ret;
	BYTE			pbtTxBuf[20];
	BYTE			pbtRxBuf[20];
	CFMT_Crc		Crc;
	WORD			wCalcCrc;
	t_FMT_Uint32	dwReadSize;

	Crc.Create(CFMT_Crc::e_StdCrc_Crc16_CcittFalse);

	ret = ConnectStteUart();
	if (ret != e_Return_OK)
	{
		return ret;
	}

	pbtTxBuf[0] = 0xA5;
	pbtTxBuf[1] = 0xC2;
	pbtTxBuf[2] = btSn;

	Crc.Compute((t_FMT_Uint8*)pbtTxBuf, 3, &wCalcCrc);

	FMT::Uint16ToBuf(wCalcCrc, &pbtTxBuf[3]);

	ret = m_pInService->ResetReadBuffer();
	if (ret != e_Return_OK)
	{
		goto l_HdwFail;
	}

	ret = m_pOutService->Write(pbtTxBuf, 5, 1000);
	if (ret != e_Return_OK)
	{
		goto l_HdwFail;
	}

	Sleep(200);
	ret = m_pInService->Read(pbtRxBuf, 4, dwReadSize);

	if (ret != e_Return_OK)
	{
		goto l_HdwFail;
	}

	if (dwReadSize != 4)
	{
		goto l_DevFail;
	}

	if (pbtRxBuf[0] != 0xA5)
	{
		goto l_DevFail;
	}

	Crc.Compute((t_FMT_Uint8*)pbtRxBuf, 2, &wCalcCrc);

	if (wCalcCrc != FMT::Uint16FromBuf(pbtRxBuf + 2))
	{
		goto l_DevFail;
	}

	if (pbtRxBuf[1] != 0xE0)
	{
		goto l_MemFail;
	}

	DisconnectStteUart();
	return e_Return_OK;


l_HdwFail:

	DisconnectStteUart();
	return e_Return_HardwareError;


l_DevFail:

	DisconnectStteUart();
	return e_Return_DeviceError;


l_MemFail:

	DisconnectStteUart();
	return e_Return_WriteError;
}


// -----------------------------------------------------------------------------------
//	CDhaStteDevice::ConnectStteUart
// -----------------------------------------------------------------------------------

DWORD CDhaStteDevice::ConnectStteUart()
{
	CFMT_HdwService								*pService;
	CFMT_HdwByteOutBufferService::CParameters	outparam;
	CFMT_HdwByteInBufferService::CParameters	inparam;
	DWORD										dwRet;
	DWORD										j;
	CFMT_HdwManager::CPortInfoVector			uartlist;
	BOOL										bAgain;

	dwRet = m_HdwManager.Enumerate();

	if (dwRet != e_Return_OK)
	{
		goto l_Fail;
	}

	m_HdwManager.GetPortList(CFMT_HdwPort::e_PortType_Uart, uartlist);

	dwRet = m_HdwManager.Run();
	if (dwRet != e_Return_OK)
	{
		goto l_Fail;
	}

	bAgain=TRUE;
	j=0;
	while (bAgain && (j < !uartlist))
	{
		if (uartlist[j].m_sIntChannel == m_sStteUartPort)
		{
			m_StteUartParameters.m_uiPortNum = uartlist[j].m_uiPortNum;
			bAgain = FALSE;
		}
		else
		{
			j++;
		}
	}

	if (bAgain)
	{
		goto l_Fail;
	}



	m_pStteUartPort = m_HdwManager.GetPort(CFMT_HdwPort::e_PortType_Uart, m_StteUartParameters.m_uiPortNum);

	if (m_pStteUartPort == NULL)
	{
		goto l_Fail;
	}

	outparam.m_uiBufferSize = 0x100000;
	inparam.m_uiBufferSize = 0x100000;

	dwRet = m_pStteUartPort->EnableService(CFMT_HdwService::e_Service_ByteOutBuffer, &pService, &outparam);
	if (dwRet != e_Return_OK)
	{
		goto l_Fail;
	}
	
	m_pOutService = (CFMT_HdwByteOutBufferService*)pService;

	dwRet = m_pStteUartPort->EnableService(CFMT_HdwService::e_Service_ByteInBuffer, &pService, &inparam);
	if (dwRet != e_Return_OK)
	{
		goto l_Fail;
	}

	m_pInService = (CFMT_HdwByteInBufferService*)pService;

	dwRet = m_pStteUartPort->Open(&m_StteUartParameters);

	if (dwRet != e_Return_OK)
	{
        goto l_Fail;
	}
	return e_Return_OK;


l_Fail:

	if (m_pStteUartPort != NULL)
	{
		m_pStteUartPort->Close();
		m_pStteUartPort->DisableAllServices();
		m_HdwManager.Stop();
	}

	m_pStteUartPort = NULL;

	return e_Return_Fail;
}


// -----------------------------------------------------------------------------------
//	CDhaStteDevice::DisconnectStteUart
// -----------------------------------------------------------------------------------

DWORD CDhaStteDevice::DisconnectStteUart()
{
	if (m_pStteUartPort != NULL)
	{
		m_pStteUartPort->Close();
		m_pStteUartPort->DisableAllServices();
		m_pStteUartPort = NULL;
	}

	m_HdwManager.Stop();

	return e_Return_OK;
}


// -----------------------------------------------------------------------------------
//	CDhaStteDevice::ConnectSpi
// -----------------------------------------------------------------------------------

DWORD CDhaStteDevice::ConnectSpi()
{
	t_FMT_Uint32		ret;

	m_pSpiLinkSocket = new CFMT_HdwUdpSocket();

	ret = m_pSpiLinkSocket->Bind(DHA5X5_SPI_PORT, CFMT_HdwUdpSocket::e_BindMode_DontShareAddress);

	if (ret != e_Return_OK)
	{
		ret = e_Return_HardwareError;
	}

	return e_Return_OK;
}


// -----------------------------------------------------------------------------------
//	CDhaStteDevice::DisconnectSpi
// -----------------------------------------------------------------------------------

DWORD CDhaStteDevice::DisconnectSpi()
{
	if (m_pSpiLinkSocket != FMTDEF_NULL)
	{
		delete m_pSpiLinkSocket;
		m_pSpiLinkSocket = FMTDEF_NULL;
	}

	return e_Return_OK;
}


// -----------------------------------------------------------------------------------
//	CDhaStteDevice::PerformSpiTransfer
// -----------------------------------------------------------------------------------

DWORD CDhaStteDevice::PerformSpiTransfer(BYTE *pbtTxBuf, WORD wTxLen, BYTE *pbtRxBuf, WORD wRxLen, BYTE btSpeed, DWORD dwTimeoutMs)
{
	if (m_pSpiLinkSocket == FMTDEF_NULL)
	{
		return e_Return_NotOpen;
	}

	BYTE				*pbtUdpBuf;
	t_FMT_Uint32		uiSentBytes;
	t_FMT_Uint32		uiTxBytes;
	t_FMT_Uint32		uiRet;
	CFMT_IpAddress		SrcAdd;
	t_FMT_Uint16		usSrcPort;
	t_FMT_Uint32		uiRcvBytes;

	pbtUdpBuf = new BYTE[DHA5X5_MAX_SPI_DATA_PCK_LEN + 16];

	memset(pbtUdpBuf, 0, DHA5X5_MAX_SPI_DATA_PCK_LEN + 16);

	switch (btSpeed)
	{
	case 0:
		pbtUdpBuf[16 + 0] = 3;
		break;

	case 1:
		pbtUdpBuf[16 + 0] = 9;
		break;

	case 2:
		pbtUdpBuf[16 + 0] = 19;
		break;

	case 3:
		pbtUdpBuf[16 + 0] = 49;
		break;

	case 4:
		pbtUdpBuf[16 + 0] = 99;
		break;

	case 5:
		pbtUdpBuf[16 + 0] = 199;
		break;

	default:
		pbtUdpBuf[16 + 0] = 499;
		break;
	}

	pbtUdpBuf[16 + 1] = (BYTE)wTxLen;
	pbtUdpBuf[16 + 2] = (BYTE)(wTxLen >> 8);
	pbtUdpBuf[16 + 3] = (BYTE)wRxLen;
	pbtUdpBuf[16 + 4] = (BYTE)(wRxLen >> 8);

	memcpy(pbtUdpBuf + 16 + 5, pbtTxBuf, wTxLen);

	uiTxBytes = 16 + 5 + wTxLen;


	// Complete the packet

	memcpy(pbtUdpBuf, DHA5X5_SPI_DATA_SIGNATURE, 16);

	// Send the packet
	uiRet = m_pSpiLinkSocket->SendDatagram(pbtUdpBuf, uiTxBytes, (CFMT_String)m_sIpAdd, DHA5X5_SPI_PORT, &uiSentBytes);

	// Response reception

	BOOL				bAgain;
	int					iStartTime;

	bAgain = FMTDEF_TRUE;
	memset(pbtUdpBuf, 0, DHA5X5_MAX_SPI_DATA_PCK_LEN + 16);
	

	iStartTime = ::GetTickCount();

	while (bAgain && (::GetTickCount() - iStartTime < dwTimeoutMs))
	{
		uiRet = m_pSpiLinkSocket->ReadDatagram(pbtUdpBuf, DHA5X5_MAX_SPI_DATA_PCK_LEN + 16, &SrcAdd, &usSrcPort, &uiRcvBytes, 50);

		if (uiRet != e_Return_OK)
		{
			continue;
		}

		if (m_sIpAdd != SrcAdd.ToString())
		{
			continue;
		}

		if (uiRcvBytes != 16 + wRxLen)
		{
			continue;
		}

		if (memcmp(pbtUdpBuf, DHA5X5_SPI_DATA_SIGNATURE, 16) != 0)
		{
			continue;
		}

		memcpy(pbtRxBuf, pbtUdpBuf + 16, wRxLen);

		bAgain = FMTDEF_FALSE;
	}

	delete[] pbtUdpBuf;

	if (bAgain)
	{
		return e_Return_Timeout;
	}

	return e_Return_OK;
}


// -----------------------------------------------------------------------------------
//	CDhaStteDevice::EnableLog
// -----------------------------------------------------------------------------------

DWORD CDhaStteDevice::EnableLog(BOOL bEnable)
{
	if (m_bLogEnable == bEnable)
	{
		return e_Return_OK;
	}

	m_LogMutex.Lock();

	if (bEnable)
	{
		if (m_LogFile.Open(m_sLogFilePath, CFMT_File::e_OpenMode_Write | CFMT_File::e_OpenMode_Overwrite) != e_Return_OK)
		{
			return e_Return_FileError;
		}

		m_bLogEnable = TRUE;
	}
	else
	{
		m_LogFile.Close();
		m_bLogEnable = FALSE;
	}
	
	m_LogMutex.Unlock();
}


// -----------------------------------------------------------------------------------
//	CDhaStteDevice::OpenLog
// -----------------------------------------------------------------------------------

DWORD CDhaStteDevice::OpenLog()
{
	m_LogMutex.Lock();

	if (m_LogFile.Open(m_sLogFilePath, CFMT_File::e_OpenMode_Write | CFMT_File::e_OpenMode_Overwrite) != e_Return_OK)
	{
		return e_Return_FileError;
	}
	
	m_LogMutex.Unlock();

	return e_Return_OK;
}


// -----------------------------------------------------------------------------------
//	CDhaStteDevice::CloseLog
// -----------------------------------------------------------------------------------

void CDhaStteDevice::CloseLog()
{
	m_LogMutex.Lock();

	m_LogFile.Close();
	
	m_LogMutex.Unlock();
}


// -----------------------------------------------------------------------------------
//	CDhaStteDevice::Log
// -----------------------------------------------------------------------------------

void CDhaStteDevice::Log(BYTE *pbtBuf, DWORD dwSize, BOOL bTx)
{
	if (!m_bLogEnable)
	{
		return;
	}

	CFMT_String		sLine;
	DWORD			k;

	m_LogMutex.Lock();

	if (bTx)
	{
		sLine = "[" + GetLogTimeString(m_dwLastMainLinkRxTime) + "] >>> TX -------------------------------------";
		m_LogFile.WriteTextLine(sLine);
	}
	else
	{
		sLine = "[" + GetLogTimeString(m_dwLastMainLinkRxTime) + "] <<< RX -------------------------------------";
		m_LogFile.WriteTextLine(sLine);
	}

	for (k=0; k<dwSize; k++)
	{
		sLine.Format("   [%02d]: 0x%02X", k, pbtBuf[k]);
		m_LogFile.WriteTextLine(sLine);
	}

	m_LogMutex.Unlock();
}


// -----------------------------------------------------------------------------------
//	CDhaStteDevice::Connect
// -----------------------------------------------------------------------------------

t_FMT_Uint32 CDhaStteDevice::Connect()
{
	t_FMT_Uint32		ret;

	if (m_bLogEnable)
	{
		if (OpenLog() != e_Return_OK)
		{
			return e_Return_FileError;
		}
	}

	m_pUartLinkSocket = new CFMT_HdwUdpSocket();

	ret = m_pUartLinkSocket->Bind(DHA5X5_UART_PORT, CFMT_HdwUdpSocket::e_BindMode_DontShareAddress);

	if (ret != e_Return_OK)
	{
		ret = e_Return_HardwareError;
		goto l_Fail;
	}


	m_pMainLinkSocket = new CFMT_HdwUdpSocket();

	ret = m_pMainLinkSocket->Bind(DHA5X5_MAINLINK_PORT, CFMT_HdwUdpSocket::e_BindMode_DontShareAddress);

	if (ret != e_Return_OK)
	{
		ret = e_Return_HardwareError;
		goto l_Fail;
	}

	m_bRemoteAbort = FALSE;

	m_bMainLinkRxThreadStop = FALSE;
	m_pMainLinkRxThread = AfxBeginThread(MainLinkRxThreadFunction, this);

	m_bUartRxThreadStop = FALSE;
	m_pUartRxThread = AfxBeginThread(UartRxThreadFunction, this);

	m_bConnected = TRUE;
	SendMainLinkPacket();

	m_dwLastMainLinkRxTime = ::GetTickCount();


	return e_Return_OK;

l_Fail:

	if (m_pUartLinkSocket != FMTDEF_NULL)
	{
		delete m_pUartLinkSocket;
		m_pUartLinkSocket = FMTDEF_NULL;
	}

	if (m_pMainLinkSocket != FMTDEF_NULL)
	{
		delete m_pMainLinkSocket;
		m_pMainLinkSocket = FMTDEF_NULL;
	}

	return ret;
}


// -----------------------------------------------------------------------------------
//	CDhaStteDevice::Disconnect
// -----------------------------------------------------------------------------------

t_FMT_Uint32 CDhaStteDevice::Disconnect()
{
	if (!m_bConnected)
	{
		return e_Return_OK;
	}

	CloseLog();

	m_bConnected = FALSE;
	SendMainLinkPacket();


	m_bUartRxThreadStop = TRUE;

	if (m_pUartRxThread != NULL)
	{
		::WaitForSingleObject(m_pUartRxThread->m_hThread, INFINITE);
		m_pUartRxThread = NULL;
	}


	m_bMainLinkRxThreadStop = TRUE;

	if (m_pMainLinkRxThread != NULL)
	{
		::WaitForSingleObject(m_pMainLinkRxThread->m_hThread, INFINITE);
		m_pMainLinkRxThread = NULL;
	}


	if (m_pUartLinkSocket != FMTDEF_NULL)
	{
		delete m_pUartLinkSocket;
		m_pUartLinkSocket = FMTDEF_NULL;
	}
	

	if (m_pMainLinkSocket != FMTDEF_NULL)
	{
		delete m_pMainLinkSocket;
		m_pMainLinkSocket = FMTDEF_NULL;
	}

	return e_Return_OK;
}


// -----------------------------------------------------------------------------------
//	CDhaStteDevice::ConnectMaintenance
// -----------------------------------------------------------------------------------

BOOL CDhaStteDevice::ConnectMaintenance()
{
	#ifdef DHA55_COMPILE_NOHDW
	return TRUE;
	#endif

	CFMT_HdwByteOutBufferService				*pOutService;
	CFMT_HdwByteInBufferService					*pInService;
	CFMT_HdwService								*pService;
	CFMT_HdwByteOutBufferService::CParameters	outparam;
	CFMT_HdwByteInBufferService::CParameters	inparam;
	DWORD										dwRet;
	DWORD										j;
	CFMT_HdwManager::CPortInfoVector			uartlist;
	BOOL										bAgain;
	DWORD										k;
	CFMT_CommMpp::SCommand						comlist[3];

	dwRet = m_HdwManager.Enumerate();

	if (dwRet != e_Return_OK)
	{
		return FALSE;
	}

	m_HdwManager.GetPortList(CFMT_HdwPort::e_PortType_Uart, uartlist);

	dwRet = m_HdwManager.Run();
	if (dwRet != e_Return_OK)
	{
		return FALSE;
	}


	// --- Connect Maintenance Link ---------------------------------------------------

	bAgain = TRUE;
	j=0;
	while (bAgain && (j<!uartlist))
	{
		if (uartlist[j].m_sIntChannel == m_sMaintLinkComPort)
		{
			m_MaintUartParameters.m_uiPortNum = uartlist[j].m_uiPortNum;
			bAgain = FALSE;
		}
		else
		{
			j++;
		}
	}

	if (bAgain)
	{
		goto l_Abort;
	}



	m_pMaintPort = m_HdwManager.GetPort(CFMT_HdwPort::e_PortType_Uart, m_MaintUartParameters.m_uiPortNum);

	if (m_pMaintPort == NULL)
	{
		goto l_Abort;
	}

	outparam.m_uiBufferSize = 0x100000;
	inparam.m_uiBufferSize = 0x100000;

	dwRet = m_pMaintPort->EnableService(CFMT_HdwService::e_Service_ByteOutBuffer, &pService, &outparam);
	if (dwRet != e_Return_OK)
	{
		goto l_Abort;
	}
	
	pOutService = (CFMT_HdwByteOutBufferService*)pService;

	dwRet = m_pMaintPort->EnableService(CFMT_HdwService::e_Service_ByteInBuffer, &pService, &inparam);
	if (dwRet != e_Return_OK)
	{
		goto l_Abort;
	}

	pInService = (CFMT_HdwByteInBufferService*)pService;

	dwRet = m_pMaintPort->Open(&m_MaintUartParameters);

	if (dwRet != e_Return_OK)
	{
		goto l_Abort;
	}

	if (m_MaintMpp.Mount(pInService, pOutService) != e_Return_OK)
	{
		goto l_Abort;
	}

	m_MaintMpp.Init();


	// --- Set Maintenance Mode on MNR_CTRL ------------------------

	// MNR_CTRL
	m_pMaintDataReg[CMaintMpp::e_MppReg_Ctrl].SetBit(0, TRUE);
	m_pMaintDataReg[CMaintMpp::e_MppReg_Ctrl].SetBit(7, FMTDEF_FALSE);

	for (k=0; k<3; k++)
	{
		comlist[k].CreateRegisterWrite8Command(CMaintMpp::e_MppReg_Ctrl, (t_FMT_Uint8)(m_pMaintDataReg[CMaintMpp::e_MppReg_Ctrl].GetField(0, 8)));
	}

	// Process Commands -------------------------------------------------------------
	
	if ((m_MaintMpp.ProcCommandList(comlist, 3, 300)) != e_Return_OK)
	{
		goto l_Abort;
	}

	return TRUE;


l_Abort:

	DisconnectMaintenance();

	return FALSE;

}



// -----------------------------------------------------------------------------------
//	CDhaStteDevice::DisconnectMaintenance
// -----------------------------------------------------------------------------------

BOOL CDhaStteDevice::DisconnectMaintenance(BOOL bReboot)
{
	#ifdef DHA55_COMPILE_NOHDW
	return TRUE;
	#endif

	DWORD	k;
	BYTE	btCom;

	if (m_pMaintPort != NULL)
	{
		// --- Reset Maintenance Mode on MNR_CTRL ------------------------
		CFMT_CommMpp::SCommand		comlist[3];

		btCom = 0;

		if (bReboot)
		{
			btCom = 0x80;
		}

		for (k=0; k<3; k++)
		{
			comlist[k].CreateRegisterWrite8Command(CMaintMpp::e_MppReg_Ctrl, btCom);
		}

		// Process Commands -------------------------------------------------------------
		
		m_MaintMpp.ProcCommandList(comlist, 3, 300);


		m_pMaintPort->Close();
		m_pMaintPort->DisableAllServices();
		m_pMaintPort = NULL;
	}

	m_HdwManager.Stop();

	return TRUE;
}


// -----------------------------------------------------------------------------------
//	CDhaStteDevice::DisconnectMaintenance
// -----------------------------------------------------------------------------------

DWORD CDhaStteDevice::NoopCommand(DWORD dwTimeout)
{
	DWORD	dwRet;

	dwRet = OneMessCommand(e_Code_NoOperation, dwTimeout);

	return dwRet;
}


// -----------------------------------------------------------------------------------
//	CDhaStteDevice::DefaultWarmStartCommand
// -----------------------------------------------------------------------------------

DWORD CDhaStteDevice::DefaultWarmStartCommand(DWORD dwTimeout)
{
	DWORD	dwRet;

	dwRet = OneMessCommand(e_Code_DefaultWarmStartComm, dwTimeout);

	return dwRet;
}


// -------------------------------------------------------------
//	CDhaStteDevice::DayModeWarmStartCommand
// -------------------------------------------------------------

DWORD CDhaStteDevice::DayModeWarmStartCommand(BYTE btBrt, DWORD dwTimeout)
{
	return WriteCommand(e_Code_DayModeWarmStartComm, btBrt, dwTimeout);
}


// -------------------------------------------------------------
//	CDhaStteDevice::NightModeWarmStartCommand
// -------------------------------------------------------------

DWORD CDhaStteDevice::NightModeWarmStartCommand(BYTE btBrt, DWORD dwTimeout)
{
	return WriteCommand(e_Code_NightModeWarmStartComm, btBrt, dwTimeout);
}
