// LoaderDlg.cpp : implementation file
//

#include "stdafx.h"
#include "dha5x5_STTE.h"
#include "LoaderDlg.h"
#include "ComDlg.h"

#include "CnfFile.h"
#include "BtlFile.h"


// *************************************************************************************
// *************************************************************************************
//	Class CLoaderDlg
// *************************************************************************************
// *************************************************************************************

IMPLEMENT_DYNAMIC(CLoaderDlg, CDialog)

// -----------------------------------------------------------------------------------
//	CLoaderDlg::CLoaderDlg
// -----------------------------------------------------------------------------------

CLoaderDlg::CLoaderDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLoaderDlg::IDD, pParent)
{
	//m_hAccelTable = LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_ACCELERATOR_LOADER));

	m_dwMode = e_Mode_Idle;
	
	m_pbtTempCfg = new BYTE[CNF_TOT_MEMORY_BYTE_SIZE];

	m_btPhase = 0;
	m_pDev = NULL;
	m_pWaitCursor = NULL;
	InitCRC16();

	/*BYTE btTemp[STTE_TOT_BTL_MEMORY_BYTE_SIZE];
	CreateEmptyBitlogMemory(btTemp);*/
}


// -----------------------------------------------------------------------------------
//	CLoaderDlg::~CLoaderDlg
// -----------------------------------------------------------------------------------

CLoaderDlg::~CLoaderDlg()
{
	delete[] m_pbtTempCfg;
	//delete[] m_pbtTempBm;


	StopWaitCursor();
}


// -----------------------------------------------------------------------------------
//	CLoaderDlg::DoDataExchange
// -----------------------------------------------------------------------------------

void CLoaderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


// -----------------------------------------------------------------------------------
//	CLoaderDlg Message Map
// -----------------------------------------------------------------------------------

BEGIN_MESSAGE_MAP(CLoaderDlg, CDialog)
	ON_WM_TIMER()

	ON_BN_CLICKED(IDC_BUT_CFG_PROGRAM, &CLoaderDlg::OnBnClickedButCfgProgram)
	ON_BN_CLICKED(IDC_BUT_CFG_VERIFY, &CLoaderDlg::OnBnClickedButCfgVerify)
	ON_BN_CLICKED(IDC_BUT_CFG_ERASE, &CLoaderDlg::OnBnClickedButCfgErase)
	ON_BN_CLICKED(IDC_BUT_CFG_READINFO_FROMFILE, &CLoaderDlg::OnBnClickedButCfgReadinfoFromfile)
	ON_BN_CLICKED(IDC_BUT_CFG_READINFO_FROMMEM, &CLoaderDlg::OnBnClickedButCfgReadinfoFrommem)
	ON_BN_CLICKED(IDC_BUT_CFG_READ, &CLoaderDlg::OnBnClickedButCfgRead)
	ON_BN_CLICKED(IDC_BUT_STOP, &CLoaderDlg::OnBnClickedButStop)
	ON_WM_SETCURSOR()
	ON_STN_CLICKED(IDC_STATIC_COM, &CLoaderDlg::OnStnClickedStaticComPort)
	ON_BN_CLICKED(IDC_BUT_BITLOG_ERASE, &CLoaderDlg::OnBnClickedButBitlogErase)
	ON_BN_CLICKED(IDC_BUT_BITLOG_READ, &CLoaderDlg::OnBnClickedButBitlogRead)
END_MESSAGE_MAP()

// -----------------------------------------------------------------------------------
//	InitCRC16
// -----------------------------------------------------------------------------------

void CLoaderDlg::InitCRC16()
{
	int		i,j,w;
	t_FMT_Uint16	crc;

	for (i=0; i<256; i++) 
	{
		crc = i<<8;

		for (j=0; j<8; j++)
		{
			crc = (crc << 1) ^ ((crc & 0x8000) ? (0x1021) : 0);
		}

		m_pwCrc16Table[i] = crc;

		m_pbtByteFlip[i]=0;

		for (w=0;w<8;w++)
		{
			if ((i & (1<<w))>0)
			{
				m_pbtByteFlip[i] |= (1<<(7-w));
			}
		}
	}
}

// -----------------------------------------------------------------------------------
//	CalcCRC16Word
// -----------------------------------------------------------------------------------

t_FMT_Uint16 CLoaderDlg::CalcCRC16Word(t_FMT_Uint16 btCrc,t_FMT_Uint8 btData)
{
	t_FMT_Uint16	wRet;

	//wRet = m_pwCrc16Table[m_pbtByteFlip[btData] ^ (btCrc >> 8)] ^ (btCrc << 8);
	wRet = m_pwCrc16Table[btData ^ (btCrc >> 8)] ^ (btCrc << 8);

	return wRet;
}

// -----------------------------------------------------------------------------------
//	CalcCRC16
// -----------------------------------------------------------------------------------

t_FMT_Uint16 CLoaderDlg::CalcCRC16(t_FMT_Uint8* pbtData,t_FMT_Uint32 dwSize)
{
	t_FMT_Uint16	wTemp;
	t_FMT_Uint32	k;

	wTemp=0xFFFF;

	for (k=0;k<dwSize;k++)
	{
		wTemp=CalcCRC16Word(wTemp,pbtData[k]);
	}

	return wTemp;
}


// -----------------------------------------------------------------------------------
//	CLoaderDlg::OnInitDialog
// -----------------------------------------------------------------------------------

BOOL CLoaderDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// --- Subclassing ------------------------------------------------------

	m_ssTargetFile.SubclassDlgItem(IDC_STATIC_TARGET,this);
	m_ssCom.SubclassDlgItem(IDC_STATIC_COM, this);


	// --- Configuration Memory ------------------------------------------------------

	M_GETLISTCTRL(IDC_LIST_CFG_INFO)->SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	M_GETLISTCTRL(IDC_LIST_CFG_INFO)->InsertColumn(0,"Field",LVCFMT_LEFT,80);
	M_GETLISTCTRL(IDC_LIST_CFG_INFO)->InsertColumn(1,"Value",LVCFMT_LEFT,250);

	M_GETLISTCTRL(IDC_LIST_CFG_INFO)->InsertItem(0,"Code");
	M_GETLISTCTRL(IDC_LIST_CFG_INFO)->InsertItem(1,"Name");
	M_GETLISTCTRL(IDC_LIST_CFG_INFO)->InsertItem(2,"Date");
	M_GETLISTCTRL(IDC_LIST_CFG_INFO)->InsertItem(3,"Author");
	M_GETLISTCTRL(IDC_LIST_CFG_INFO)->InsertItem(4,"CRC");

	// --- Status -----------------------------------------------------------

	m_ssTargetFile.SetWindowText("Ready");
	m_ssTargetFile.SetBkColor(STTE_COLOR_GREEN);

	EnableControls(TRUE);
	RefreshPort();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


// -----------------------------------------------------------------------------------
//	CLoaderDlg::EnableControls
// -----------------------------------------------------------------------------------

void CLoaderDlg::EnableControls(BOOL bEnable)
{
	if (bEnable)
	{
		M_GETBUTTON(IDC_BUT_CFG_PROGRAM)->ModifyStyle(WS_DISABLED,0);
		M_GETBUTTON(IDC_BUT_CFG_VERIFY)->ModifyStyle(WS_DISABLED,0);
		M_GETBUTTON(IDC_BUT_CFG_ERASE)->ModifyStyle(WS_DISABLED,0);
		M_GETBUTTON(IDC_BUT_CFG_READINFO_FROMFILE)->ModifyStyle(WS_DISABLED,0);
		M_GETBUTTON(IDC_BUT_CFG_READINFO_FROMMEM)->ModifyStyle(WS_DISABLED,0);
		M_GETBUTTON(IDC_BUT_CFG_READ)->ModifyStyle(WS_DISABLED,0);

		/*M_GETBUTTON(IDC_BUT_CNFUSR_PROGRAM)->ModifyStyle(WS_DISABLED,0);
		M_GETBUTTON(IDC_BUT_CNFUSR_VERIFY)->ModifyStyle(WS_DISABLED,0);
		M_GETBUTTON(IDC_BUT_CNFUSR_ERASE)->ModifyStyle(WS_DISABLED,0);
		M_GETBUTTON(IDC_BUT_CNFUSR_READ)->ModifyStyle(WS_DISABLED,0);
		*/

		M_GETBUTTON(IDC_BUT_STOP)->ModifyStyle(0,WS_DISABLED);
	}
	else
	{
		M_GETBUTTON(IDC_BUT_CFG_PROGRAM)->ModifyStyle(0,WS_DISABLED);
		M_GETBUTTON(IDC_BUT_CFG_VERIFY)->ModifyStyle(0,WS_DISABLED);
		M_GETBUTTON(IDC_BUT_CFG_ERASE)->ModifyStyle(0,WS_DISABLED);
		M_GETBUTTON(IDC_BUT_CFG_READINFO_FROMFILE)->ModifyStyle(0,WS_DISABLED);
		M_GETBUTTON(IDC_BUT_CFG_READINFO_FROMMEM)->ModifyStyle(0,WS_DISABLED);
		M_GETBUTTON(IDC_BUT_CFG_READ)->ModifyStyle(0,WS_DISABLED);

		/*
		M_GETBUTTON(IDC_BUT_CNFUSR_PROGRAM)->ModifyStyle(0,WS_DISABLED);
		M_GETBUTTON(IDC_BUT_CNFUSR_VERIFY)->ModifyStyle(0,WS_DISABLED);
		M_GETBUTTON(IDC_BUT_CNFUSR_ERASE)->ModifyStyle(0,WS_DISABLED);
		M_GETBUTTON(IDC_BUT_CNFUSR_READ)->ModifyStyle(0,WS_DISABLED);
		*/

		M_GETBUTTON(IDC_BUT_STOP)->ModifyStyle(WS_DISABLED,0);
	}

	M_GETBUTTON(IDC_BUT_CFG_PROGRAM)->Invalidate();
	M_GETBUTTON(IDC_BUT_CFG_VERIFY)->Invalidate();
	M_GETBUTTON(IDC_BUT_CFG_ERASE)->Invalidate();
	M_GETBUTTON(IDC_BUT_CFG_READINFO_FROMFILE)->Invalidate();
	M_GETBUTTON(IDC_BUT_CFG_READINFO_FROMMEM)->Invalidate();
	M_GETBUTTON(IDC_BUT_CFG_READ)->Invalidate();

	/*
	M_GETBUTTON(IDC_BUT_CNFUSR_PROGRAM)->Invalidate();
	M_GETBUTTON(IDC_BUT_CNFUSR_VERIFY)->Invalidate();
	M_GETBUTTON(IDC_BUT_CNFUSR_ERASE)->Invalidate();
	M_GETBUTTON(IDC_BUT_CNFUSR_READ)->Invalidate();
	*/

	M_GETBUTTON(IDC_BUT_STOP)->Invalidate();
}


// -----------------------------------------------------------------------------------
//	CLoaderDlg::CheckCfgFile
// -----------------------------------------------------------------------------------

BOOL CLoaderDlg::CheckCfgFile(CFile& f)
{
	if (f.GetLength() != CNF_TOT_MEMORY_BYTE_SIZE)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}


// -----------------------------------------------------------------------------------
//	CLoaderDlg::OnBnClickedButCfgProgram
// -----------------------------------------------------------------------------------

void CLoaderDlg::OnBnClickedButCfgProgram()
{
	CFile			f;
	DWORD			dwRet;
	BYTE			*pbtBuf;
	CString			s;
	DWORD			dwCrc;

	CFileDialog* pDlg=new CFileDialog(TRUE,"bin",NULL,OFN_HIDEREADONLY,
		"Binary Files (*.bin) | *.bin|",this);

	if (pDlg->DoModal()==IDOK)
	{
		m_sFilePath=pDlg->GetPathName();
		m_sFileName=pDlg->GetFileName();
		delete pDlg;
	}
	else
	{
		delete pDlg;
		return;
	}

	// Read the file ------------------------------------------

	if (!f.Open(m_sFilePath,CFile::modeRead))
	{
		STTE_Message("Cannot read selected file", MB_ICONSTOP, this);
		return;
	}

	if (!CheckCfgFile(f))
	{
		STTE_Message("Invalid Configuration Factory Memory file", MB_ICONSTOP, this);
		f.Close();
		return;
	}

	dwCrc = 0;

	pbtBuf = m_pDev->m_MaintMpp.CreateTransferBuffer(CNF_TOT_MEMORY_BYTE_SIZE);

	try
	{
		f.Read(pbtBuf, CNF_TOT_MEMORY_BYTE_SIZE);
		memcpy(m_pbtTempCfg, pbtBuf, CNF_TOT_MEMORY_BYTE_SIZE);

		dwCrc = ((DWORD)(*((WORD*)(pbtBuf + CNF_CRC_BO))));
	}
	catch(...)
	{
		STTE_Message("Cannot read selected file", MB_ICONSTOP, this);
		f.Close();
		return;
	}

	f.Close();

	RefreshCfgFileInfo(pbtBuf, dwCrc);

	M_GETPROGRESS(IDC_PROG_LOADER)->SetRange(0,10000);
	M_GETPROGRESS(IDC_PROG_LOADER)->SetPos(0);

	EnableControls(FALSE);

	if (!m_pDev->ConnectMaintenance())
	{
		STTE_Message("Cannot open Loader Port.",MB_ICONSTOP, this);

		EnableControls(TRUE);
		return;
	}

	// Execute file transfer ----------------------------------

	m_pDev->m_CfgBtp.m_bEraseAll = FALSE;
	m_pDev->m_CfgBtp.m_bErasePage = FALSE;
	m_pDev->m_CfgBtp.m_uiMaxNumItemPerTransfer = 6;
	m_pDev->m_CfgBtp.m_uiPageSize = 0x100;
	m_pDev->m_CfgBtp.m_uiEraseSize = 0x10000;
	m_pDev->m_CfgBtp.m_uiRetries = 3;
	m_pDev->m_CfgBtp.m_uiStartMemAddress = MEM_CNF_MPP_START_ADDRESS;
	m_pDev->m_CfgBtp.m_uiTimeout = 3000;
	m_pDev->m_CfgBtp.m_uiTransferSize = CNF_TOT_MEMORY_BYTE_SIZE;

	StartWaitCursor();

	dwRet = m_pDev->m_MaintMpp.EraseMemoryBuffer(&m_pDev->m_CfgBtp);

	if (dwRet != e_Return_OK)
	{
		STTE_Message("Hardware communication error.", MB_ICONSTOP, this);
		EnableControls(TRUE);
		m_pDev->DisconnectMaintenance();
		StopWaitCursor();
		return;
	}

	s = "Erasing target Configuration Memory...";
	m_ssTargetFile.SetWindowText(s);
	m_ssTargetFile.SetBkColor(STTE_COLOR_YELLOW);

	m_dwMode = e_Mode_Program;
	m_btPhase = 0;
	SetTimer(STTE_CFGLOADER_TIMER_ID, STTE_CFGLOADER_TIMER_VAL, NULL);
}


// -----------------------------------------------------------------------------------
//	CLoaderDlg::OnBnClickedButCfgVerify
// -----------------------------------------------------------------------------------

void CLoaderDlg::OnBnClickedButCfgVerify()
{
	CFile			f;
	DWORD			dwRet;
	CString			s;
	DWORD			dwCrc;

	CFileDialog* pDlg=new CFileDialog(TRUE,"bin",NULL,OFN_HIDEREADONLY,
		"Binary Files (*.bin) | *.bin|",this);

	if (pDlg->DoModal()==IDOK)
	{
		m_sFilePath=pDlg->GetPathName();
		m_sFileName=pDlg->GetFileName();
		delete pDlg;
	}
	else
	{
		delete pDlg;
		return;
	}

	// Read the file ------------------------------------------

	if (!f.Open(m_sFilePath,CFile::modeRead))
	{
		STTE_Message("Cannot read selected file", MB_ICONSTOP, this);
		return;
	}

	if (!CheckCfgFile(f))
	{
		STTE_Message("Invalid Configuration Factory Memory file",MB_ICONSTOP, this);
		f.Close();
		return;
	}

	dwCrc=0;
	try
	{
		f.Read(m_pbtTempCfg, CNF_TOT_MEMORY_BYTE_SIZE);

		dwCrc=((DWORD)(*((WORD*)(m_pbtTempCfg + CNF_CRC_BO))));
	}
	catch(...)
	{
		STTE_Message("Cannot read selected file",MB_ICONSTOP, this);
		f.Close();
		return;
	}

	f.Close();

	RefreshCfgFileInfo(m_pbtTempCfg,dwCrc);

	M_GETPROGRESS(IDC_PROG_LOADER)->SetRange(0,10000);
	M_GETPROGRESS(IDC_PROG_LOADER)->SetPos(0);

	EnableControls(FALSE);

	if (!m_pDev->ConnectMaintenance())
	{
		STTE_Message("Cannot open Loader Port.",MB_ICONSTOP, this);
		EnableControls(TRUE);
		return;
	}

	// Execute file transfer ----------------------------------
	m_pDev->m_CfgBtp.m_bEraseAll = FALSE;
	m_pDev->m_CfgBtp.m_bErasePage = FALSE;
	m_pDev->m_CfgBtp.m_uiMaxNumItemPerTransfer = 1;
	m_pDev->m_CfgBtp.m_uiPageSize = 0x100;
	m_pDev->m_CfgBtp.m_uiEraseSize = 0x10000;
	m_pDev->m_CfgBtp.m_uiRetries = 3;
	m_pDev->m_CfgBtp.m_uiStartMemAddress = MEM_CNF_MPP_START_ADDRESS;
	m_pDev->m_CfgBtp.m_uiTimeout = 500;
	m_pDev->m_CfgBtp.m_uiTransferSize = CNF_TOT_MEMORY_BYTE_SIZE;

	StartWaitCursor();

	m_btPhase=0;
	dwRet=m_pDev->m_MaintMpp.ReadMemoryBuffer(&m_pDev->m_CfgBtp);

	if (dwRet != e_Return_OK)
	{
		STTE_Message("Hardware communication error.",MB_ICONSTOP, this);
		m_pDev->DisconnectMaintenance();
		EnableControls(TRUE);
		StopWaitCursor();
		return;
	}

	s="Verifying "+m_sFileName+"...";
	m_ssTargetFile.SetWindowText(s);
	m_ssTargetFile.SetBkColor(STTE_COLOR_YELLOW);

	m_dwMode=e_Mode_Verify;
	SetTimer(STTE_CFGLOADER_TIMER_ID,STTE_CFGLOADER_TIMER_VAL,NULL);
}





// -----------------------------------------------------------------------------------
//	CLoaderDlg::OnBnClickedButCfgReadinfoFrommem
// -----------------------------------------------------------------------------------

void CLoaderDlg::OnBnClickedButCfgReadinfoFrommem()
{
	CMaintMpp::SCommand		comlist[10];
	DWORD					k;
	DWORD					dwRet;
	BYTE					btTemp;
	DWORD					dwCrc;
	WORD					wTemp;

	EnableControls(FALSE);

	M_GETPROGRESS(IDC_PROG_LOADER)->SetPos(0);

	if (!m_pDev->ConnectMaintenance())
	{
		STTE_Message("Cannot open Loader Port.",MB_ICONSTOP, this);
		EnableControls(TRUE);
		return;
	}

	m_ssTargetFile.SetWindowText("Reading file info...");
	m_ssTargetFile.SetBkColor(STTE_COLOR_YELLOW);

	m_pDev->m_CfgBtp.m_uiTimeout = 500;

	dwCrc = 0;
	comlist[0].CreateMemoryReadCommand(MEM_CNF_MPP_START_ADDRESS, 0x80);
	comlist[1].CreateMemoryReadCommand(MEM_CNF_MPP_START_ADDRESS + CNF_CRC_BO, 2);

	// Process Commands -------------------------------------------------------------
	
	if (m_pDev->m_MaintMpp.ProcCommandList(comlist, 2, 2000) != e_Return_OK)
	{
		STTE_Message("Hardware communication error.",MB_ICONSTOP, this);
		m_ssTargetFile.SetWindowText("Ready");
		m_ssTargetFile.SetBkColor(STTE_COLOR_GREEN);
		m_pDev->DisconnectMaintenance();
		EnableControls(TRUE);
		return;
	}

	// Check all commands return

	for (k=0; k<2; k++)
	{
		dwRet = comlist[k].GetResult(btTemp);

		if ((dwRet != e_Return_OK) || (btTemp != CMaintMpp::e_MppStatus_OK))
		{
			STTE_Message("Hardware communication error.",MB_ICONSTOP, this);
			m_ssTargetFile.SetWindowText("Ready");
			m_ssTargetFile.SetBkColor(STTE_COLOR_GREEN);
			m_pDev->DisconnectMaintenance();
			EnableControls(TRUE);
			return;
		}
	}

	m_pDev->DisconnectMaintenance();

	wTemp = *((WORD*)(comlist[1].GetReadMemoryBuffer()));
	dwCrc = ((DWORD)wTemp);

	M_GETPROGRESS(IDC_PROG_LOADER)->SetPos(0);

	// Extract Data

	RefreshCfgFileInfo(comlist[0].GetReadMemoryBuffer(),dwCrc);

	m_dwMode=e_Mode_Idle;

	m_ssTargetFile.SetWindowText("Ready");
	m_ssTargetFile.SetBkColor(STTE_COLOR_GREEN);

	M_GETPROGRESS(IDC_PROG_LOADER)->SetPos(10000);
	EnableControls(TRUE);
}


// -----------------------------------------------------------------------------------
//	CLoaderDlg::OnBnClickedButCfgReadinfoFromfile
// -----------------------------------------------------------------------------------

void CLoaderDlg::OnBnClickedButCfgReadinfoFromfile()
{
	CFile			f;
	CString			s;
	DWORD			dwCrc;

	CFileDialog* pDlg=new CFileDialog(TRUE,"bin",NULL,OFN_HIDEREADONLY,
		"Binary Files (*.bin) | *.bin|",this);

	if (pDlg->DoModal()==IDOK)
	{
		m_sFilePath=pDlg->GetPathName();
		m_sFileName=pDlg->GetFileName();
		delete pDlg;
	}
	else
	{
		delete pDlg;
		return;
	}

	// Read the file ------------------------------------------

	if (!f.Open(m_sFilePath,CFile::modeRead))
	{
		STTE_Message("Cannot read selected file",MB_ICONSTOP, this);
		return;
	}

	if (!CheckCfgFile(f))
	{
		STTE_Message("Invalid Configuration Factory Memory file",MB_ICONSTOP, this);
		f.Close();
		return;
	}

	try
	{
		f.Read(m_pbtTempCfg, CNF_TOT_MEMORY_BYTE_SIZE);
	}
	catch(...)
	{
		STTE_Message("Cannot read selected file",MB_ICONSTOP, this);
		f.Close();
		return;
	}

	f.Close();

	dwCrc = ((DWORD)(*((WORD*)(m_pbtTempCfg + CNF_CRC_BO))));

	RefreshCfgFileInfo(m_pbtTempCfg, dwCrc);
}


// -----------------------------------------------------------------------------------
//	CLoaderDlg::Timer_CfgLoader
// -----------------------------------------------------------------------------------

void CLoaderDlg::Timer_CfgLoader()
{
	double		d;
	DWORD		dwRet;
	CString		s;

	if (m_dwMode==e_Mode_Program)
	{
		if (m_btPhase==0)
		{
			m_pDev->m_MaintMpp.GetBufferTransferStatus(&m_BtpStatus);

			if (!m_BtpStatus.m_bOn)
			{
				KillTimer(STTE_CFGLOADER_TIMER_ID);

				if (m_BtpStatus.m_uiStatus==e_Return_OK)
				{
					m_pDev->m_CfgBtp.m_uiMaxNumItemPerTransfer=6;
					m_pDev->m_CfgBtp.m_uiTimeout=500;

					m_btPhase=1;
					dwRet=m_pDev->m_MaintMpp.WriteMemoryBuffer(&m_pDev->m_CfgBtp);

					if (dwRet!=e_Return_OK)
					{
						STTE_Message("Hardware communication error.",MB_ICONSTOP, this);
						m_pDev->DisconnectMaintenance();
						EnableControls(TRUE);
						StopWaitCursor();
						return;
					}
					else
					{
						s="Programming "+m_sFileName+"...";
						m_ssTargetFile.SetWindowText(s);
						m_ssTargetFile.SetBkColor(STTE_COLOR_YELLOW);

						SetTimer(STTE_CFGLOADER_TIMER_ID,STTE_CFGLOADER_TIMER_VAL,NULL);
					}
				}
				else
				{
					m_dwMode=e_Mode_Idle;

					if (m_BtpStatus.m_uiStatus==e_Return_Halted)
					{
						STTE_Message("Operation stopped by the user.",MB_ICONWARNING, this);
					}
					else
					{
						STTE_Message("Hardware communication error.",MB_ICONSTOP, this);
					}

					m_ssTargetFile.SetWindowText("Ready");
					m_ssTargetFile.SetBkColor(STTE_COLOR_GREEN);

					m_pDev->DisconnectMaintenance();
					EnableControls(TRUE);
					StopWaitCursor();
				}

			}
			else
			{
				d=((double)(m_BtpStatus.m_uiCurrentPage))/((double)(3*m_BtpStatus.m_uiTotPages))*10000.0;
				M_GETPROGRESS(IDC_PROG_LOADER)->SetPos((int)d);
			}
		}
		else
		{
			m_pDev->m_MaintMpp.GetBufferTransferStatus(&m_BtpStatus);
		
			if (!m_BtpStatus.m_bOn)
			{
				KillTimer(STTE_CFGLOADER_TIMER_ID);

				if (m_BtpStatus.m_uiStatus==e_Return_OK)
				{
					m_btPhase=0;

					s="Verifying "+m_sFileName+"...";
					m_ssTargetFile.SetWindowText(s);
					m_ssTargetFile.SetBkColor(STTE_COLOR_YELLOW);

					dwRet=m_pDev->m_MaintMpp.ReadMemoryBuffer(&m_pDev->m_CfgBtp);

					m_dwMode=e_Mode_VerifyAfterProgram;

					SetTimer(STTE_CFGLOADER_TIMER_ID,STTE_CFGLOADER_TIMER_VAL,NULL);
				}
				else
				{
					m_dwMode=e_Mode_Idle;

					if (m_BtpStatus.m_uiStatus==e_Return_Halted)
					{
						STTE_Message("Operation stopped by the user.",MB_ICONWARNING, this);
					}
					else
					{
						STTE_Message("Hardware communication error.",MB_ICONSTOP, this);
					}

					m_ssTargetFile.SetWindowText("Ready");
					m_ssTargetFile.SetBkColor(STTE_COLOR_GREEN);

					m_pDev->DisconnectMaintenance();
					EnableControls(TRUE);
					StopWaitCursor();
				}
			}
			else
			{
				d=((double)(m_BtpStatus.m_uiCurrentPage+m_BtpStatus.m_uiTotPages))/((double)(3*m_BtpStatus.m_uiTotPages))*10000.0;
				M_GETPROGRESS(IDC_PROG_LOADER)->SetPos((int)d);
			}
		}
	}
	else if (m_dwMode==e_Mode_VerifyAfterProgram)
	{
		m_pDev->m_MaintMpp.GetBufferTransferStatus(&m_BtpStatus);

		if (!m_BtpStatus.m_bOn)
		{
			KillTimer(STTE_CFGLOADER_TIMER_ID);

			m_dwMode=e_Mode_Idle;

			if (m_BtpStatus.m_uiStatus==e_Return_OK)
			{
				M_GETPROGRESS(IDC_PROG_LOADER)->SetPos(10000);

				if (memcmp(m_pDev->m_MaintMpp.GetTransferBuffer(),m_pbtTempCfg,m_pDev->m_CfgBtp.m_uiTransferSize)==0)
				{
					STTE_Message("File correctly written.",MB_ICONINFORMATION, this);
				}
				else
				{
					STTE_Message("File verification error.",MB_ICONSTOP, this);
				}
			}
			else
			{
				if (m_BtpStatus.m_uiStatus==e_Return_Halted)
				{
					STTE_Message("Operation stopped by the user.",MB_ICONWARNING, this);
				}
				else
				{
					STTE_Message("Hardware communication error.",MB_ICONSTOP, this);
				}
			}

			m_ssTargetFile.SetWindowText("Ready");
			m_ssTargetFile.SetBkColor(STTE_COLOR_GREEN);

			M_GETPROGRESS(IDC_PROG_LOADER)->SetPos(10000);

			m_pDev->DisconnectMaintenance();
			EnableControls(TRUE);
			StopWaitCursor();
		}
		else
		{
			d=((double)(m_BtpStatus.m_uiCurrentPage+2*m_BtpStatus.m_uiTotPages))/((double)(3*m_BtpStatus.m_uiTotPages))*10000.0;
			M_GETPROGRESS(IDC_PROG_LOADER)->SetPos((int)d);
		}
	}
	else if (m_dwMode==e_Mode_Verify)
	{
		m_pDev->m_MaintMpp.GetBufferTransferStatus(&m_BtpStatus);

		if (!m_BtpStatus.m_bOn)
		{
			KillTimer(STTE_CFGLOADER_TIMER_ID);

			m_dwMode=e_Mode_Idle;

			if (m_BtpStatus.m_uiStatus==e_Return_OK)
			{
				M_GETPROGRESS(IDC_PROG_LOADER)->SetPos(10000);

				if (memcmp(m_pDev->m_MaintMpp.GetTransferBuffer(),m_pbtTempCfg,m_pDev->m_CfgBtp.m_uiTransferSize)==0)
				{
					STTE_Message("File correctly verified.",MB_ICONINFORMATION, this);
				}
				else
				{
					STTE_Message("File verification error.",MB_ICONSTOP, this);
				}
			}
			else
			{
				if (m_BtpStatus.m_uiStatus==e_Return_Halted)
				{
					STTE_Message("Operation stopped by the user.",MB_ICONWARNING, this);
				}
				else
				{
					STTE_Message("Hardware communication error.",MB_ICONSTOP, this);
				}
			}

			m_ssTargetFile.SetWindowText("Ready");
			m_ssTargetFile.SetBkColor(STTE_COLOR_GREEN);

			m_pDev->DisconnectMaintenance();
			EnableControls(TRUE);
			StopWaitCursor();
		}
		else
		{
			d=((double)(m_BtpStatus.m_uiCurrentPage))/((double)(m_BtpStatus.m_uiTotPages))*10000.0;
			M_GETPROGRESS(IDC_PROG_LOADER)->SetPos((int)d);
		}
	}
	else if (m_dwMode==e_Mode_Read)
	{
		m_pDev->m_MaintMpp.GetBufferTransferStatus(&m_BtpStatus);

		if (!m_BtpStatus.m_bOn)
		{
			KillTimer(STTE_CFGLOADER_TIMER_ID);

			m_dwMode=e_Mode_Idle;

			if (m_BtpStatus.m_uiStatus==e_Return_OK)
			{
				CFile			f;

				M_GETPROGRESS(IDC_PROG_LOADER)->SetPos(10000);

				if (!f.Open(m_sFilePath,CFile::modeCreate|CFile::modeWrite))
				{
					STTE_Message("Cannot save read file.",MB_ICONSTOP, this);
				}
				else
				{
					try
					{
						f.Write(m_pDev->m_MaintMpp.GetTransferBuffer(),m_pDev->m_CfgBtp.m_uiTransferSize);
						f.Close();
						STTE_Message("File correctly saved.",MB_ICONINFORMATION, this);
					}
					catch(...)
					{
						f.Close();
						STTE_Message("Cannot save read file.",MB_ICONSTOP, this);
					}

				}

			}
			else
			{
				if (m_BtpStatus.m_uiStatus==e_Return_Halted)
				{
					STTE_Message("Operation stopped by the user.",MB_ICONWARNING, this);
				}
				else
				{
					STTE_Message("Hardware communication error.",MB_ICONSTOP, this);
				}
			}

			m_ssTargetFile.SetWindowText("Ready");
			m_ssTargetFile.SetBkColor(STTE_COLOR_GREEN);

			m_pDev->DisconnectMaintenance();
			EnableControls(TRUE);
			StopWaitCursor();
		}
		else
		{
			d=((double)(m_BtpStatus.m_uiCurrentPage))/((double)(m_BtpStatus.m_uiTotPages))*10000.0;
			M_GETPROGRESS(IDC_PROG_LOADER)->SetPos((int)d);
		}
	}
	else if (m_dwMode==e_Mode_Erase)
	{
		m_pDev->m_MaintMpp.GetBufferTransferStatus(&m_BtpStatus);

		if (!m_BtpStatus.m_bOn)
		{
			KillTimer(STTE_CFGLOADER_TIMER_ID);

			m_dwMode=e_Mode_Idle;

			if (m_BtpStatus.m_uiStatus==e_Return_OK)
			{
				M_GETPROGRESS(IDC_PROG_LOADER)->SetPos(10000);
				STTE_Message("Memory correcly erased.",MB_ICONINFORMATION, this);
			}
			else
			{
				if (m_BtpStatus.m_uiStatus==e_Return_Halted)
				{
					STTE_Message("Operation stopped by the user.",MB_ICONWARNING, this);
				}
				else
				{
					STTE_Message("Hardware communication error.",MB_ICONSTOP, this);
				}
			}

			m_ssTargetFile.SetWindowText("Ready");
			m_ssTargetFile.SetBkColor(STTE_COLOR_GREEN);

			m_pDev->DisconnectMaintenance();
			EnableControls(TRUE);
			StopWaitCursor();
		}
		else
		{
			d=((double)(m_BtpStatus.m_uiCurrentPage))/((double)(m_BtpStatus.m_uiTotPages))*10000.0;
			M_GETPROGRESS(IDC_PROG_LOADER)->SetPos((int)d);
		}
	}
}


// -----------------------------------------------------------------------------------
//	CLoaderDlg::OnSetCursor
// -----------------------------------------------------------------------------------

BOOL CLoaderDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
    if (m_pWaitCursor!=NULL)
    {
        // We are showing the wait cursor
        RestoreWaitCursor();
        return TRUE;
    }

	return CDialog::OnSetCursor(pWnd, nHitTest, message);
}


// -----------------------------------------------------------------------------------
//	CLoaderDlg::OnTimer
// -----------------------------------------------------------------------------------

void CLoaderDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == STTE_CFGLOADER_TIMER_ID)
	{
		Timer_CfgLoader();
	}
	else if (nIDEvent == STTE_BTLLOADER_TIMER_ID)
	{
		Timer_BtlLoader();
	}

	CDialog::OnTimer(nIDEvent);
}


// -----------------------------------------------------------------------------------
//	CLoaderDlg::RefreshCfgFileInfo
// -----------------------------------------------------------------------------------

void CLoaderDlg::RefreshCfgFileInfo(BYTE *pbtInfo,DWORD dwCrc)
{
	CString		s;
	char		pchTemp[200];

	// Code
	memcpy(pchTemp, pbtInfo + CNF_CODE_BO, CNF_CODE_LENGTH);
	pchTemp[CNF_CODE_LENGTH] = '\0';
	s.Format("%s", pchTemp);
	s.Trim();
	M_GETLISTCTRL(IDC_LIST_CFG_INFO)->SetItemText(0, 1, s);

	// Name
	memcpy(pchTemp, pbtInfo + CNF_NAME_BO, CNF_NAME_LENGTH);
	pchTemp[CNF_NAME_LENGTH] = '\0';
	s.Format("%s", pchTemp);
	s.Trim();
	M_GETLISTCTRL(IDC_LIST_CFG_INFO)->SetItemText(1, 1, s);

	// Date
	memcpy(pchTemp,pbtInfo + CNF_DATE_BO, CNF_DATE_LENGTH);
	pchTemp[CNF_DATE_LENGTH] = '\0';
	s.Format("%s", pchTemp);
	s.Trim();
	M_GETLISTCTRL(IDC_LIST_CFG_INFO)->SetItemText(2,1,s);

	// Author
	memcpy(pchTemp,pbtInfo + CNF_AUTHOR_BO, CNF_AUTHOR_LENGTH);
	pchTemp[CNF_AUTHOR_LENGTH] = '\0';
	s.Format("%s", pchTemp);
	s.Trim();
	M_GETLISTCTRL(IDC_LIST_CFG_INFO)->SetItemText(3, 1, s);
	
	// CRC
	s.Format("0x%04X", dwCrc);
	M_GETLISTCTRL(IDC_LIST_CFG_INFO)->SetItemText(4, 1, s);
}
	

// -----------------------------------------------------------------------------------
//	CLoaderDlg::OnBnClickedButStop
// -----------------------------------------------------------------------------------

void CLoaderDlg::OnBnClickedButStop()
{
	m_pDev->m_MaintMpp.StopBufferOperation(2000);
}


// -----------------------------------------------------------------------------------
//	CLoaderDlg::StartWaitCursor
// -----------------------------------------------------------------------------------

void CLoaderDlg::StartWaitCursor()
{
	if (m_pWaitCursor==NULL)
	{
		m_pWaitCursor=new CWaitCursor();
	}
}


// -----------------------------------------------------------------------------------
//	CLoaderDlg::StartWaitCursor
// -----------------------------------------------------------------------------------

void CLoaderDlg::StopWaitCursor()
{
	if (m_pWaitCursor!=NULL)
	{
		delete m_pWaitCursor;
		m_pWaitCursor=NULL;
	}
}


// -----------------------------------------------------------------------------------
//	CLoaderDlg::OnStnClickedStaticComPort
// -----------------------------------------------------------------------------------

void CLoaderDlg::OnStnClickedStaticComPort()
{
	CComDlg		d;

	d.m_sCOM = m_pDev->m_sMaintLinkComPort;
	d.m_pHdwManager = &(m_pDev->m_HdwManager);
	
	if (d.DoModal() == IDOK)
	{
		m_pDev->m_sMaintLinkComPort = d.m_sCOM;
		m_pDev->SaveSettings();
		RefreshPort();
	}
}



// -----------------------------------------------------------------------------------
//	CLoaderDlg::RefreshPort
// -----------------------------------------------------------------------------------

void CLoaderDlg::RefreshPort()
{
	CString		s;

	if (m_pDev->m_sMaintLinkComPort.GetLength() > 0)
	{
		s = m_pDev->m_sMaintLinkComPort.GetStringC();
		m_ssCom.SetBkColor(STTE_COLOR_GREEN);
		m_ssCom.SetWindowText(s);
	}
	else
	{
		m_ssCom.SetWindowText("No Port");
		m_ssCom.SetBkColor(STTE_COLOR_RED);
	}
}


// -----------------------------------------------------------------------------------
//	CLoaderDlg::OnBnClickedButCfgErase
// -----------------------------------------------------------------------------------

void CLoaderDlg::OnBnClickedButCfgErase()
{
	DWORD			dwRet;
	CString			s;

	if (STTE_Message("Confirm Configuration Memory erasing?", MB_YESNO|MB_ICONQUESTION, this)!=IDYES)
	{
		return;
	}


	M_GETPROGRESS(IDC_PROG_LOADER)->SetRange(0,10000);
	M_GETPROGRESS(IDC_PROG_LOADER)->SetPos(0);

	EnableControls(FALSE);

	if (!m_pDev->ConnectMaintenance())
	{
		STTE_Message("Cannot open Loader Port.",MB_ICONSTOP, this);

		EnableControls(TRUE);
		return;
	}

	// Execute file transfer ----------------------------------

	m_pDev->m_CfgBtp.m_bEraseAll = FALSE;
	m_pDev->m_CfgBtp.m_bErasePage = FALSE;
	m_pDev->m_CfgBtp.m_uiMaxNumItemPerTransfer=1;
	m_pDev->m_CfgBtp.m_uiPageSize = 0x100;
	m_pDev->m_CfgBtp.m_uiEraseSize = 0x10000;
	m_pDev->m_CfgBtp.m_uiRetries=3;
	m_pDev->m_CfgBtp.m_uiStartMemAddress = MEM_CNF_MPP_START_ADDRESS;
	m_pDev->m_CfgBtp.m_uiTimeout=1500;
	m_pDev->m_CfgBtp.m_uiTransferSize = CNF_TOT_MEMORY_BYTE_SIZE;

	StartWaitCursor();

	dwRet=m_pDev->m_MaintMpp.EraseMemoryBuffer(&m_pDev->m_CfgBtp);

	if (dwRet!=e_Return_OK)
	{
		STTE_Message("Hardware communication error.",MB_ICONSTOP, this);
		EnableControls(TRUE);
		StopWaitCursor();
		return;
	}

	s="Erasing target Configuration Memory...";
	m_ssTargetFile.SetWindowText(s);
	m_ssTargetFile.SetBkColor(STTE_COLOR_YELLOW);

	m_dwMode=e_Mode_Erase;
	m_btPhase=0;
	SetTimer(STTE_CFGLOADER_TIMER_ID,STTE_CFGLOADER_TIMER_VAL,NULL);
}


// -----------------------------------------------------------------------------------
//	CLoaderDlg::OnBnClickedButBitlogErase
// -----------------------------------------------------------------------------------

void CLoaderDlg::OnBnClickedButBitlogErase()
{
	DWORD			dwRet;
	CString			s;
	BYTE			*pbtBuf;

	if (STTE_Message("Confirm Bitlog Memory erasing?", MB_YESNO|MB_ICONQUESTION, this)!=IDYES)
	{
		return;
	}


	M_GETPROGRESS(IDC_PROG_LOADER)->SetRange(0,10000);
	M_GETPROGRESS(IDC_PROG_LOADER)->SetPos(0);

	EnableControls(FALSE);

	CBtlFile	btlfile;

	pbtBuf = m_pDev->m_MaintMpp.CreateTransferBuffer(BTL_TOT_MEMORY_BYTE_SIZE);
	memcpy(pbtBuf, btlfile.m_pbtMemBuf, BTL_TOT_MEMORY_BYTE_SIZE);

	if (!m_pDev->ConnectMaintenance())
	{
		STTE_Message("Cannot open Loader Port.",MB_ICONSTOP, this);

		EnableControls(TRUE);
		return;
	}

	// Execute file transfer ----------------------------------

	m_pDev->m_CfgBtp.m_bEraseAll = FALSE;
	m_pDev->m_CfgBtp.m_bErasePage = FALSE;
	m_pDev->m_CfgBtp.m_uiMaxNumItemPerTransfer=1;
	m_pDev->m_CfgBtp.m_uiPageSize = 0x100;
	m_pDev->m_CfgBtp.m_uiEraseSize = 0x10000;
	m_pDev->m_CfgBtp.m_uiRetries=3;
	m_pDev->m_CfgBtp.m_uiStartMemAddress = MEM_BLG_MPP_START_ADDRESS;
	m_pDev->m_CfgBtp.m_uiTimeout=1500;
	m_pDev->m_CfgBtp.m_uiTransferSize = BTL_TOT_MEMORY_BYTE_SIZE;

	StartWaitCursor();

	dwRet=m_pDev->m_MaintMpp.WriteMemoryBuffer(&m_pDev->m_CfgBtp);

	if (dwRet!=e_Return_OK)
	{
		STTE_Message("Hardware communication error.",MB_ICONSTOP, this);
		EnableControls(TRUE);
		StopWaitCursor();
		return;
	}

	s="Erasing target Bitlog Memory...";
	m_ssTargetFile.SetWindowText(s);
	m_ssTargetFile.SetBkColor(STTE_COLOR_YELLOW);

	m_dwMode=e_Mode_Erase;
	m_btPhase=0;
	SetTimer(STTE_BTLLOADER_TIMER_ID, STTE_BTLLOADER_TIMER_VAL, NULL);
}


// -----------------------------------------------------------------------------------
//	CLoaderDlg::OnBnClickedButCfgRead
// -----------------------------------------------------------------------------------

void CLoaderDlg::OnBnClickedButCfgRead()
{
	CFile			f;
	DWORD			dwRet;

	CString			s;

	CFileDialog *pDlg=new CFileDialog(FALSE,"bin",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_PATHMUSTEXIST,
			"Binary Files (*.bin) | *.bin|",this);

	if (pDlg->DoModal()==IDOK)
	{
		m_sFilePath=pDlg->GetPathName();
		m_sFileName=pDlg->GetFileName();
		delete pDlg;
	}
	else
	{
		delete pDlg;
		return;
	}

	M_GETPROGRESS(IDC_PROG_LOADER)->SetRange(0,10000);
	M_GETPROGRESS(IDC_PROG_LOADER)->SetPos(0);

	EnableControls(FALSE);

	if (!m_pDev->ConnectMaintenance())
	{
		STTE_Message("Cannot open Loader Port.",MB_ICONSTOP, this);
		EnableControls(TRUE);
		return;
	}

	// Execute file transfer ----------------------------------
	m_pDev->m_CfgBtp.m_bEraseAll = FALSE;
	m_pDev->m_CfgBtp.m_bErasePage = FALSE;
	m_pDev->m_CfgBtp.m_uiMaxNumItemPerTransfer = 1;
	m_pDev->m_CfgBtp.m_uiPageSize = 0x100;
	m_pDev->m_CfgBtp.m_uiEraseSize = 0x10000;
	m_pDev->m_CfgBtp.m_uiRetries = 3;
	m_pDev->m_CfgBtp.m_uiStartMemAddress = MEM_CNF_MPP_START_ADDRESS;
	m_pDev->m_CfgBtp.m_uiTimeout = 500;
	m_pDev->m_CfgBtp.m_uiTransferSize = CNF_TOT_MEMORY_BYTE_SIZE;

	StartWaitCursor();

	dwRet = m_pDev->m_MaintMpp.ReadMemoryBuffer(&m_pDev->m_CfgBtp);

	if (dwRet != e_Return_OK)
	{
		STTE_Message("Hardware communication error.",MB_ICONSTOP, this);
		EnableControls(TRUE);
		StopWaitCursor();
		return;
	}

	s="Reading target file as "+m_sFileName+"...";
	m_ssTargetFile.SetWindowText(s);
	m_ssTargetFile.SetBkColor(STTE_COLOR_YELLOW);

	m_dwMode=e_Mode_Read;
	m_btPhase=0;
	SetTimer(STTE_CFGLOADER_TIMER_ID,STTE_CFGLOADER_TIMER_VAL,NULL);
}


// -----------------------------------------------------------------------------------
//	CLoaderDlg::OnBnClickedButBitlogRead
// -----------------------------------------------------------------------------------

void CLoaderDlg::OnBnClickedButBitlogRead()
{
	CFile			f;
	DWORD			dwRet;

	CString			s;

	CFileDialog *pDlg=new CFileDialog(FALSE, "txt", NULL, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_PATHMUSTEXIST,
			"Text Files (*.txt) | *.txt|Binary Files (*.bin) | *.bin|",this);

	if (pDlg->DoModal()==IDOK)
	{
		m_sFilePath=pDlg->GetPathName();
		m_sFileName=pDlg->GetFileName();
		delete pDlg;
	}
	else
	{
		delete pDlg;
		return;
	}

	M_GETPROGRESS(IDC_PROG_LOADER)->SetRange(0,10000);
	M_GETPROGRESS(IDC_PROG_LOADER)->SetPos(0);

	EnableControls(FALSE);

	if (!m_pDev->ConnectMaintenance())
	{
		STTE_Message("Cannot open Loader Port.",MB_ICONSTOP, this);
		EnableControls(TRUE);
		return;
	}

	// Execute file transfer ----------------------------------

	m_pDev->m_CfgBtp.m_bEraseAll = FALSE;
	m_pDev->m_CfgBtp.m_bErasePage = FALSE;
	m_pDev->m_CfgBtp.m_uiMaxNumItemPerTransfer = 1;
	m_pDev->m_CfgBtp.m_uiPageSize = 0x100;
	m_pDev->m_CfgBtp.m_uiEraseSize = 0x10000;
	m_pDev->m_CfgBtp.m_uiRetries = 3;
	m_pDev->m_CfgBtp.m_uiStartMemAddress = MEM_BLG_MPP_START_ADDRESS;
	m_pDev->m_CfgBtp.m_uiTimeout = 500;
	m_pDev->m_CfgBtp.m_uiTransferSize = BTL_TOT_MEMORY_BYTE_SIZE;

	StartWaitCursor();

	dwRet = m_pDev->m_MaintMpp.ReadMemoryBuffer(&m_pDev->m_CfgBtp);

	if (dwRet != e_Return_OK)
	{
		STTE_Message("Hardware communication error.",MB_ICONSTOP, this);
		EnableControls(TRUE);
		StopWaitCursor();
		return;
	}

	s="Reading target file as " + m_sFileName + "...";
	m_ssTargetFile.SetWindowText(s);
	m_ssTargetFile.SetBkColor(STTE_COLOR_YELLOW);

	m_dwMode=e_Mode_Read;
	m_btPhase=0;
	SetTimer(STTE_BTLLOADER_TIMER_ID, STTE_BTLLOADER_TIMER_VAL,NULL);
}


// -----------------------------------------------------------------------------------
//	CLoaderDlg::Timer_BtlLoader
// -----------------------------------------------------------------------------------

void CLoaderDlg::Timer_BtlLoader()
{
	double		d;
	DWORD		dwRet;
	CString		s;

	if (m_dwMode==e_Mode_Read)
	{
		m_pDev->m_MaintMpp.GetBufferTransferStatus(&m_BtpStatus);

		if (!m_BtpStatus.m_bOn)
		{
			KillTimer(STTE_BTLLOADER_TIMER_ID);

			m_dwMode=e_Mode_Idle;

			if (m_BtpStatus.m_uiStatus == e_Return_OK)
			{
				CFile			f;

				M_GETPROGRESS(IDC_PROG_LOADER)->SetPos(10000);

				s = m_sFilePath;
				s.MakeUpper();
				s.Trim();

				if (s.Right(4) == ".TXT")
				{
					CBtlFile		bitlog;
					memcpy(bitlog.m_pbtMemBuf, m_pDev->m_MaintMpp.GetTransferBuffer(), m_pDev->m_CfgBtp.m_uiTransferSize); 

					if (bitlog.ExportTxt(m_sFilePath) != e_Return_OK)
					{
						STTE_Message("Cannot save read file.", MB_ICONSTOP, this);
					}
					else
					{
						STTE_Message("File correctly saved.", MB_ICONINFORMATION, this);
					}
				}
				else
				{
					if (!f.Open(m_sFilePath,CFile::modeCreate|CFile::modeWrite))
					{
						STTE_Message("Cannot save read file.", MB_ICONSTOP, this);
					}
					else
					{
						try
						{
							f.Write(m_pDev->m_MaintMpp.GetTransferBuffer(), m_pDev->m_CfgBtp.m_uiTransferSize);
							f.Close();
							STTE_Message("File correctly saved.", MB_ICONINFORMATION, this);
						}
						catch(...)
						{
							f.Close();
							STTE_Message("Cannot save read file.", MB_ICONSTOP, this);
						}
					}
				}
			}
			else
			{
				if (m_BtpStatus.m_uiStatus==e_Return_Halted)
				{
					STTE_Message("Operation stopped by the user.",MB_ICONWARNING, this);
				}
				else
				{
					STTE_Message("Hardware communication error.",MB_ICONSTOP, this);
				}
			}

			m_ssTargetFile.SetWindowText("Ready");
			m_ssTargetFile.SetBkColor(STTE_COLOR_GREEN);

			m_pDev->DisconnectMaintenance();
			EnableControls(TRUE);
			StopWaitCursor();
		}
		else
		{
			d=((double)(m_BtpStatus.m_uiCurrentPage))/((double)(m_BtpStatus.m_uiTotPages))*10000.0;
			M_GETPROGRESS(IDC_PROG_LOADER)->SetPos((int)d);
		}
	}
	else if (m_dwMode==e_Mode_Erase)
	{
		m_pDev->m_MaintMpp.GetBufferTransferStatus(&m_BtpStatus);

		if (!m_BtpStatus.m_bOn)
		{
			KillTimer(STTE_BTLLOADER_TIMER_ID);

			m_dwMode=e_Mode_Idle;
			m_pDev->DisconnectMaintenance(TRUE);

			if (m_BtpStatus.m_uiStatus==e_Return_OK)
			{
				M_GETPROGRESS(IDC_PROG_LOADER)->SetPos(10000);
				STTE_Message("Memory correcly erased.",MB_ICONINFORMATION, this);
			}
			else
			{
				if (m_BtpStatus.m_uiStatus==e_Return_Halted)
				{
					STTE_Message("Operation stopped by the user.",MB_ICONWARNING, this);
				}
				else
				{
					STTE_Message("Hardware communication error.",MB_ICONSTOP, this);
				}
			}

			m_ssTargetFile.SetWindowText("Ready");
			m_ssTargetFile.SetBkColor(STTE_COLOR_GREEN);

			EnableControls(TRUE);
			StopWaitCursor();
		}
		else
		{
			d=((double)(m_BtpStatus.m_uiCurrentPage))/((double)(m_BtpStatus.m_uiTotPages))*10000.0;
			M_GETPROGRESS(IDC_PROG_LOADER)->SetPos((int)d);
		}
	}
}
