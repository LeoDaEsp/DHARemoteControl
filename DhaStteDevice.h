#pragma once

#define DHA5X5_MAINLINK_PORT			60000
#define DHA5X5_UART_PORT				60001
#define DHA5X5_SPI_PORT					60002

#define DHASTTE_MAX_UART_PACKET_LEN		(1024)
#define DHASTTE_MAX_MAINLINK_PACKET_LEN	(1024)

#define DHASTTE_MAINLINK_ALIVE_TIMEOUT_MS	(1000)

#define DHASTTE_DEFAULT_SPI_TIMEOUT_MS	(200)

#include "MaintMpp.h"


// *************************************************************************************
// *************************************************************************************
//	Class CDhaStteDevice
// *************************************************************************************
// *************************************************************************************

class CDhaStteDevice : public CFMT_HdwObject
{
	// =====================================================================================
	//	TYPES
	// =====================================================================================

protected:

public:

	// --- [t_Code] ------------------------------------------------
	enum t_Code
	{
		e_Code_NoOperation				= 0x1F,	// No Action

		e_Code_SetDayLuminance			= 0x00,	// Write Commands
		e_Code_SetNightLuminance		= 0x0A,
		e_Code_SetFanCtrl				= 0x03,

		e_Code_ReadLuminanceSensor		= 0x30,	// Read Commands
		e_Code_ReadBacklTemp			= 0x33,
		e_Code_ReadLamp_LEDsCtrlStatus	= 0x3A,
		e_Code_ReadBITStatus			= 0x36,
		e_Code_ReadFanStatus			= 0x28,
		e_Code_ReadHeaterStatus			= 0x29,
		e_Code_ReadSWVersion			= 0x70,
		e_Code_ReadLuminanceComm		= 0x73,

		e_Code_DefaultWarmStartComm		= 0x6C,	// Restart Commands
		e_Code_DayModeWarmStartComm		= 0x69,
		e_Code_NightModeWarmStartComm	= 0x6A,
		e_Code_SW_ResetRestart_Comm		= 0x6F,

		e_Code_MaintSetPWM1High			= 0x40,	// Maintenance Commands
		e_Code_MaintSetPWM2High			= 0x41,
		e_Code_MaintSetPWM3High			= 0x42,
		e_Code_MaintSetPWM4High			= 0x43,
		e_Code_MaintSetPWM1Low			= 0x44,
		e_Code_MaintSetPWM2Low			= 0x45,
		e_Code_MaintSetPWM3Low			= 0x46,
		e_Code_MaintSetPWM4Low			= 0x47,

		e_Code_MaintSetVDC1High			= 0x48,
		e_Code_MaintSetVDC2High			= 0x49,
		e_Code_MaintSetVDC3High			= 0x4A,
		e_Code_MaintSetVDC4High			= 0x4B,
		e_Code_MaintSetVDC1Low			= 0x4C,
		e_Code_MaintSetVDC2Low			= 0x4D,
		e_Code_MaintSetVDC3Low			= 0x4E,
		e_Code_MaintSetVDC4Low			= 0x4F,
	
		e_Code_MaintRead				= 0x60,
		e_Code_MaintWrite				= 0x61
	};


	// --- [Error] ----------------------
	enum t_Error
	{
		e_Error_Unrecognized	= 0x55,
		e_Error_Invalid			= 0x49
	};


	enum t_LinkStatus
	{
		e_LinkStatus_Off			= 0,
		e_LinkStatus_Timeout		= 1,
		e_LinkStatus_On				= 2
	};

	#if 0
	// --- Control Mode ------------------------

	enum t_CtrlMode
	{
		e_CtrlMode_Idle				= 0,
		e_CtrlMode_Maintenance		= 1
	};
	#endif



	// =====================================================================================
	//	VARIABLES
	// =====================================================================================

protected:

	BOOL									m_bConnected;
	DWORD									m_dwLastMainLinkRxTime;
	CMutex									m_LogMutex;
	CFMT_File								m_LogFile;

public:

	CFMT_HdwByteInBufferService				*m_pInService;
	CFMT_HdwByteOutBufferService			*m_pOutService;

	// STTE COM
	CFMT_String								m_sStteUartPort;
	CFMT_HdwPort							*m_pStteUartPort;
	CFMT_HdwUartPort::CParameters			m_StteUartParameters;

	// Maintenance COM
	CFMT_String								m_sMaintLinkComPort;
	CFMT_HdwPort							*m_pMaintPort;
	CFMT_HdwUartPort::CParameters			m_MaintUartParameters;


	// Hardware Management
	CFMT_HdwManager							m_HdwManager;
	CFMT_HdwStdUartDevice					m_StdUartDevice;

	// Target IP Address
	CString									m_sIpAdd;

	// Main Link Socket
	CFMT_HdwUdpSocket						*m_pMainLinkSocket;

	// Uart Link Socket
	CFMT_HdwUdpSocket						*m_pUartLinkSocket;

	// SPI Link Socket
	CFMT_HdwUdpSocket						*m_pSpiLinkSocket;

	// Remote Aborted Flag
	BOOL									m_bRemoteAbort;

	// Main Link RX Packet Buffer
	BYTE									m_pucMainLinkRxPacket[DHASTTE_MAX_MAINLINK_PACKET_LEN];

	// UART RX Packet Buffer
	BYTE									m_pucUartRxPacket[DHASTTE_MAX_UART_PACKET_LEN];

	// UART RX Buffer
	CFMT_List<BYTE>							m_UartRxBuffer;

	// Main Link RX Mutex
	CMutex									m_MainLinkRxMutex;

	// Main Link RX Thread
	CWinThread								*m_pMainLinkRxThread;

	// Main Link RX Thread Stop Flag
	BOOL									m_bMainLinkRxThreadStop;

	// UART RX Buffer Mutex
	CMutex									m_UartRxMutex;

	// UART RX Thread
	CWinThread								*m_pUartRxThread;

	// UART RX Thread Stop Flag
	BOOL									m_bUartRxThreadStop;

	// Main Link Data Mutex
	CMutex									m_MainLinkMutex;

	// Heater Enable/Status
	BOOL									m_bHtrEnable;
	BOOL									m_pbHtrStat[2];

	// Discrete Outputs
	BOOL									m_bDoutReset;
	BOOL									m_bDoutShutdown;
	BOOL									m_pbDoutSpare[2];
	BOOL									m_pbDoutGamma[2];

	// Discrete Inputs
	BOOL									m_bDinBitOut;
	BOOL									m_bDinBitEvent;

	// Pattern Test Colors
	CFMT_Color								m_pPatCol[2];

	// External / Internal Video Generation
	BOOL									m_bLvdsSel;	

	// Pattern Test Number
	BYTE									m_btPatternNum;

	// AD590 Temperature
	WORD									m_wAd590;

	// SPI Speed
	BYTE									m_ucSpiSpeed;

	BOOL									m_bLogEnable;
	CFMT_String								m_sLogFilePath;



	CMaintMpp									m_MaintMpp;
	CMaintMpp::SBufferTransferProperty			m_CfgBtp;
	CFMT_Register								m_pMaintDataReg[256];
	BYTE										m_btMaintLinkStatus;
	DWORD										m_dwMaintLinkAlive;


	// =====================================================================================
	// CONSTRUCTORS & DESTRUCTORS
	// =====================================================================================

public:

	CDhaStteDevice();
	virtual ~CDhaStteDevice();

	// =====================================================================================
	//	FUNCTIONS
	// =====================================================================================

protected:

	DWORD			UartResetRx();
	static UINT		MainLinkRxThreadFunction(LPVOID pParam);
	DWORD			PerformMainLinkRx();
	static UINT		UartRxThreadFunction(LPVOID pParam);
	DWORD			PerformUartRx();

	DWORD			WriteCommand(BYTE btCommand,BYTE btParam, DWORD dwTimeout, DWORD dwRetries = DHA55_RETRIES);
	DWORD			ReadCommand(BYTE btCommand,BYTE *pbtParam, DWORD dwTimeout, DWORD dwRetries = DHA55_RETRIES);
	DWORD			OneMessCommand(BYTE btCommand, DWORD dwTimeout);

	DWORD			ProcessMainLinkRxDataPacket();
	DWORD			ProcessMainLinkRxNotifyPacket();

	DWORD			ConnectStteUart();
	DWORD			DisconnectStteUart();
	
	DWORD			OpenLog();
	void			CloseLog();



public:

	void			LoadSettings();
	void			SaveSettings();


	t_FMT_Uint32	Connect();
	t_FMT_Uint32	Disconnect();

	BOOL			IsConnected();
	BOOL			IsTimeout();

	DWORD			SendMainLinkPacket();

	DWORD			UartWrite(BYTE *pbtBuf, DWORD dwBufLen);
	DWORD			UartRead(BYTE *pbtBuf, DWORD dwBufLen, DWORD& dwReadLen);
	DWORD			UartGetRxLength();


	DWORD			SetDayLuminance(BYTE btBrt, DWORD dwTimeout);
	DWORD			SetNightLuminance(BYTE btBrt, DWORD dwTimeout);
	DWORD			SetFanCtrl(BYTE btFanOnOff, DWORD dwTimeout);

	DWORD			ReadLuminanceSensor(BYTE* pbtLEDLuminance, DWORD dwTimeout);
	DWORD			ReadBacklTemp(BYTE* pbtBacklTemp, DWORD dwTimeout);
	DWORD			ReadLampLEDsCtrlStatus(BYTE* pbtLampCtrlMode, DWORD dwTimeout);
	DWORD			ReadBITStatus(BYTE* pbtBIT_Status, DWORD dwTimeout);
	DWORD			ReadFanStatus(BYTE* pbtFanMode, DWORD dwTimeout);
	DWORD			ReadHeaterStatus(BYTE* pbtHeaterMode, DWORD dwTimeout);
	DWORD			ReadSWVersion(BYTE* pbtSWVersion, DWORD dwTimeout);
	DWORD			ReadLuminanceComm(BYTE* pbtLuminance, DWORD dwTimeout);
	
	DWORD			DefaultWarmStartComm(DWORD dwTimeout);
	DWORD			DayModeWarmStartComm(BYTE btBacklLum, DWORD dwTimeout);
	DWORD			NightModeWarmStartComm(BYTE btBacklLum, DWORD dwTimeout);
	DWORD			SW_ResetRestart_Comm(DWORD dwTimeout);

	DWORD			SetPWM(BYTE btNum, WORD wPWM, DWORD dwTimeout);
	DWORD			SetVDC(BYTE btNum, WORD wVDC, DWORD dwTimeout);
	DWORD			ReadAnalogs(WORD* pwAIN, DWORD dwTimeout);
	DWORD			SetMaintReg(BOOL bHeater, DWORD dwTimeout);

	DWORD			ProgramIp(BYTE *pbtIP);
	DWORD			ProgramSn(BYTE btSn);

	DWORD			ConnectSpi();
	DWORD			DisconnectSpi();
	DWORD			PerformSpiTransfer(BYTE *pbtTxBuf, WORD wTxLen, BYTE *pbtRxBuf, WORD wRxLen, BYTE btSpeed, DWORD dwTimeoutMs = DHASTTE_DEFAULT_SPI_TIMEOUT_MS);

	DWORD			EnableLog(BOOL bEnable);
	void			Log(BYTE *pbtBuf, DWORD dwSize, BOOL bTx);

	DWORD			UnrecognizedCommand(BYTE btCommand, DWORD dwTimeout);
	DWORD			DoubleCommand(BYTE btCommand, DWORD dwTimeout);
	DWORD			TestNoParamCommand(BYTE btCommand, DWORD dwTimeout);
	DWORD			NoopCommand(DWORD dwTimeout);
	DWORD			DefaultWarmStartCommand(DWORD dwTimeout);
	DWORD			DayModeWarmStartCommand(BYTE btBrt, DWORD dwTimeout);
	DWORD			NightModeWarmStartCommand(BYTE btBrt, DWORD dwTimeout);

	BOOL			ConnectMaintenance();
	BOOL			DisconnectMaintenance(BOOL bReboot = FALSE);
};
