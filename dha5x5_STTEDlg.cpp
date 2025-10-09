// dha5x5_STTEDlg.cpp : implementation file
//
#include "stdafx.h"
#include "dha5x5_STTE.h"
#include "dha5x5_STTEDlg.h"
#include "EditIpDlg.h"
#include "StteConfigDlg.h"
#include "CnfFile.h"
#include "MMDlg.h"
#include "MaintDlg.h"
#include "BrtBuilderDlg.h"
#include "LoaderDlg.h"
#include "EnhMaintDlg.h"
#include "BtlFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CRemotePanel g_remotePnl;

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



// *************************************************************************************
// *************************************************************************************
//	Class CDha5x5_STTEDlg
// *************************************************************************************
// *************************************************************************************

// -----------------------------------------------------------------------------------
//	CDha5x5_STTEDlg::CDha5x5_STTEDlg
// -----------------------------------------------------------------------------------

CDha5x5_STTEDlg::CDha5x5_STTEDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDha5x5_STTEDlg::IDD, pParent)
{
	m_pDev = new CDhaStteDevice;

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_dwCOM=0;

	m_brReadOnly.CreateSolidBrush(STTE_COLOR_YELLOW);
	m_brOk.CreateSolidBrush(STTE_COLOR_GREEN);
	m_brFail.CreateSolidBrush(STTE_COLOR_RED);
	m_brInvalid.CreateSolidBrush(STTE_COLOR_LIGHTGREY);
	m_brWarning.CreateSolidBrush(STTE_COLOR_ORANGE);

	m_btBIT=0;
	m_bRet_BIT=FALSE;
	m_btTXBrt=0;
	m_bRet_TXBrt=FALSE;
	m_btRXBrt=0;
	m_bRet_RXBrt=FALSE;
	m_btLumSensor=0;
	m_bRet_LumSensor=FALSE;
	m_btBacklTemp=0;
	m_bRet_BacklTemp=FALSE;
	m_btHeaterMode=0;
	m_bRet_HeaterMode=FALSE;
	m_btSWVersion=0;
	m_bRet_SWVersion=FALSE;
	m_btFanMode=0;
	m_bRet_FanMode=FALSE;
	m_btLampCtrlStatus=0;
	m_bRet_LampCtrlStatus=FALSE;


	//NtcToMem("provanuovo.mem");

	/*CCnfFile	cnf;
	cnf.Save("prova_cnf.bin");*/

	//CBtlFile	f;
	//f.SetEti(0xE1E2E3E4);
	//f.Save("bitlog_empty.bin");

	//f.Load("bitlog_store.bin");
	//f.ExportTxt("bitlog.txt");

}


// -----------------------------------------------------------------------------------
//	CDha5x5_STTEDlg::~CDha5x5_STTEDlg
// -----------------------------------------------------------------------------------

CDha5x5_STTEDlg::~CDha5x5_STTEDlg()
{
	delete m_pDev;
}


// -----------------------------------------------------------------------------------
//	CDha5x5_STTEDlg Message Map
// -----------------------------------------------------------------------------------

BEGIN_MESSAGE_MAP(CDha5x5_STTEDlg, CDialog)
	//{{AFX_MSG_MAP(CDha5x5_STTEDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CHECK_STARTSTTE, OnCheckStartstte)
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BRT_TX, OnBrtTx)
	ON_BN_CLICKED(IDC_FAN_TX, OnFanTx)
	ON_BN_CLICKED(IDC_RESTART, OnRestart)
	ON_BN_CLICKED(IDC_READLUMINANCE, OnReadluminance)
	ON_BN_CLICKED(IDC_READBACKTEMP, OnReadbacktemp)
	ON_BN_CLICKED(IDC_READLAMPSTATUS, OnReadlampstatus)
	ON_BN_CLICKED(IDC_READBITSTATUS, OnReadbitstatus)
	ON_BN_CLICKED(IDC_READFANSTATUS, OnReadfanstatus)
	ON_BN_CLICKED(IDC_READHEATERSTATUS, OnReadheaterstatus)
	ON_BN_CLICKED(IDC_READSWVERSION, OnReadswversion)
	ON_BN_CLICKED(IDC_READLUMINANCELEV, OnReadluminancelev)
	//ON_BN_CLICKED(IDC_STATIC_COMPORT, OnStaticComport)
	//}}AFX_MSG_MAP
	ON_MESSAGE(DHA55_TESTMESS,OnTestMessage)

	ON_STN_CLICKED(IDC_STATIC_COMPORT, &CDha5x5_STTEDlg::OnStnClickedStaticComport)
	ON_BN_CLICKED(IDC_BUT_MM, &CDha5x5_STTEDlg::OnBnClickedButMm)
	ON_BN_CLICKED(IDC_BUT_MAINT, &CDha5x5_STTEDlg::OnBnClickedButMaint)
	ON_BN_CLICKED(IDC_INVALID_COMMAND, &CDha5x5_STTEDlg::OnBnClickedInvalidCommand)
	ON_BN_CLICKED(IDC_UNREC_COMMAND, &CDha5x5_STTEDlg::OnBnClickedUnrecCommand)
	ON_BN_CLICKED(IDC_TIMEOUT_COMMAND, &CDha5x5_STTEDlg::OnBnClickedTimeoutCommand)
	ON_BN_CLICKED(IDC_CHECK_AUTOREAD, &CDha5x5_STTEDlg::OnBnClickedCheckAutoread)
	ON_EN_CHANGE(IDC_EDIT_BRT, &CDha5x5_STTEDlg::OnEnChangeEditBrt)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_BRT, &CDha5x5_STTEDlg::OnDeltaposSpinBrt)
	ON_BN_CLICKED(IDC_CHECK_LOGON, &CDha5x5_STTEDlg::OnBnClickedCheckLogon)
	ON_STN_CLICKED(IDC_STATIC_IPADD, &CDha5x5_STTEDlg::OnStnClickedStaticIpadd)
	ON_BN_CLICKED(IDC_BUT_DEBUG, &CDha5x5_STTEDlg::OnBnClickedButDebug)
	ON_BN_CLICKED(IDC_CHECK_HTR_ENABLE, &CDha5x5_STTEDlg::OnBnClickedCheckHtrEnable)
	ON_BN_CLICKED(IDC_CHECK_DOUT_RESET, &CDha5x5_STTEDlg::OnBnClickedCheckDoutReset)
	ON_BN_CLICKED(IDC_CHECK_DOUT_SHUTDOWN, &CDha5x5_STTEDlg::OnBnClickedCheckDoutShutdown)
	ON_BN_CLICKED(IDC_CHECK_DOUT_GAMMASEL1, &CDha5x5_STTEDlg::OnBnClickedCheckDoutGammasel1)
	ON_BN_CLICKED(IDC_CHECK_DOUT_SPARE1, &CDha5x5_STTEDlg::OnBnClickedCheckDoutSpare1)
	ON_BN_CLICKED(IDC_CHECK_DOUT_GAMMASEL2, &CDha5x5_STTEDlg::OnBnClickedCheckDoutGammasel2)
	ON_BN_CLICKED(IDC_CHECK_DOUT_SPARE2, &CDha5x5_STTEDlg::OnBnClickedCheckDoutSpare2)
	ON_STN_CLICKED(IDC_STATIC_PAT_COL1, &CDha5x5_STTEDlg::OnStnClickedStaticPatCol1)
	ON_STN_CLICKED(IDC_STATIC_PAT_COL2, &CDha5x5_STTEDlg::OnStnClickedStaticPatCol2)
	ON_STN_CLICKED(IDC_STATIC_PAT_RGB1, &CDha5x5_STTEDlg::OnStnClickedStaticPatRgb1)
	ON_STN_CLICKED(IDC_STATIC_PAT_RGB2, &CDha5x5_STTEDlg::OnStnClickedStaticPatRgb2)
	ON_BN_CLICKED(IDC_RADIO_VIDEO_PATTERN_GEN, &CDha5x5_STTEDlg::OnBnClickedRadioVideoPatternGen)
	ON_BN_CLICKED(IDC_RADIO_VIDEO_EXT_PLAYER, &CDha5x5_STTEDlg::OnBnClickedRadioVideoExtPlayer)
	ON_CBN_SELENDOK(IDC_COMBO_VIDEO_PATTERN, &CDha5x5_STTEDlg::OnCbnSelendokComboVideoPattern)
	ON_BN_CLICKED(IDC_BUT_STTE_CONFIG, &CDha5x5_STTEDlg::OnBnClickedButStteConfig)
	ON_STN_CLICKED(IDC_STATIC_LOG_PATH, &CDha5x5_STTEDlg::OnStnClickedStaticLogPath)
	ON_BN_CLICKED(IDC_BUT_LOADER, &CDha5x5_STTEDlg::OnBnClickedButLoader)
	ON_BN_CLICKED(IDC_NOOP_COMMAND, &CDha5x5_STTEDlg::OnBnClickedNoopCommand)
	ON_BN_CLICKED(IDC_DEF_WARM_START_COMMAND, &CDha5x5_STTEDlg::OnBnClickedDefWarmStartCommand)
	ON_BN_CLICKED(IDC_DAY_WARM_START_COMMAND, &CDha5x5_STTEDlg::OnBnClickedDayWarmStartCommand)
	ON_BN_CLICKED(IDC_NIGHT_WARM_START_COMMAND, &CDha5x5_STTEDlg::OnBnClickedNightWarmStartCommand)
END_MESSAGE_MAP()


// -----------------------------------------------------------------------------------
//	CDha5x5_STTEDlg::OnInitDialog
// -----------------------------------------------------------------------------------

BOOL CDha5x5_STTEDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// Load Settings
	m_pDev->LoadSettings();

	// Subclassing
	m_ssIpAdd.SubclassDlgItem(IDC_STATIC_IPADD, this);

	m_ssDinBitOut.SubclassDlgItem(IDC_STATIC_DIN_BIT_OUT, this);
	m_ssDinBitEvent.SubclassDlgItem(IDC_STATIC_DIN_BIT_EVENT, this);
	m_pssHtrStat[0].SubclassDlgItem(IDC_STATIC_HTR_STAT1, this);
	m_pssHtrStat[1].SubclassDlgItem(IDC_STATIC_HTR_STAT2, this);
	m_pssPatCol[0].SubclassDlgItem(IDC_STATIC_PAT_COL1, this);
	m_pssPatCol[1].SubclassDlgItem(IDC_STATIC_PAT_COL2, this);
	m_pssPatRgb[0].SubclassDlgItem(IDC_STATIC_PAT_RGB1, this);
	m_pssPatRgb[1].SubclassDlgItem(IDC_STATIC_PAT_RGB2, this);
	m_ssAd590Hex.SubclassDlgItem(IDC_STATIC_AD590_HEX, this);
	m_ssAd590Temp.SubclassDlgItem(IDC_STATIC_AD590_TEMP, this);
	m_ssLogFilePath.SubclassDlgItem(IDC_STATIC_LOG_PATH, this);

	EnableControls(FALSE);

	m_ssIpAdd.SetWindowText(m_pDev->m_sIpAdd);
	m_ssIpAdd.SetBkColor(STTE_COLOR_GREEN);

	M_GETBUTTON(IDC_RADIO_NIGHT)->SetCheck(TRUE);
	M_GETBUTTON(IDC_RADIO_FANAUTO)->SetCheck(TRUE);
	M_GETEDIT(IDC_EDIT_BRT)->SetWindowText("0");

	M_GETBUTTON(IDC_CHECK_HTR_ENABLE)->SetCheck(m_pDev->m_bHtrEnable);

	M_GETBUTTON(IDC_CHECK_DOUT_RESET)->SetCheck(m_pDev->m_bDoutReset);
	M_GETBUTTON(IDC_CHECK_DOUT_SHUTDOWN)->SetCheck(m_pDev->m_bDoutShutdown);
	M_GETBUTTON(IDC_CHECK_DOUT_GAMMASEL1)->SetCheck(m_pDev->m_pbDoutGamma[0]);
	M_GETBUTTON(IDC_CHECK_DOUT_GAMMASEL2)->SetCheck(m_pDev->m_pbDoutGamma[1]);
	M_GETBUTTON(IDC_CHECK_DOUT_SPARE1)->SetCheck(m_pDev->m_pbDoutSpare[0]);
	M_GETBUTTON(IDC_CHECK_DOUT_SPARE2)->SetCheck(m_pDev->m_pbDoutSpare[1]);

	M_GETBUTTON(IDC_RADIO_VIDEO_PATTERN_GEN)->SetCheck(!m_pDev->m_bLvdsSel);
	M_GETBUTTON(IDC_RADIO_VIDEO_EXT_PLAYER)->SetCheck(m_pDev->m_bLvdsSel);

	M_GETCOMBO(IDC_COMBO_VIDEO_PATTERN)->AddString("Solid");
	M_GETCOMBO(IDC_COMBO_VIDEO_PATTERN)->AddString("Border");
	M_GETCOMBO(IDC_COMBO_VIDEO_PATTERN)->AddString("Crosshair");
	M_GETCOMBO(IDC_COMBO_VIDEO_PATTERN)->AddString("Flicker");
	M_GETCOMBO(IDC_COMBO_VIDEO_PATTERN)->AddString("Horizontal Color Bar");
	M_GETCOMBO(IDC_COMBO_VIDEO_PATTERN)->AddString("Vertical Color Bar");
	M_GETCOMBO(IDC_COMBO_VIDEO_PATTERN)->AddString("Horizontal White Greyscale");
	M_GETCOMBO(IDC_COMBO_VIDEO_PATTERN)->AddString("Horizontal Red Greyscale");
	M_GETCOMBO(IDC_COMBO_VIDEO_PATTERN)->AddString("Horizontal Green Greyscale");
	M_GETCOMBO(IDC_COMBO_VIDEO_PATTERN)->AddString("Horizontal Blu Greyscale");
	M_GETCOMBO(IDC_COMBO_VIDEO_PATTERN)->AddString("Top-Left Rect");
	M_GETCOMBO(IDC_COMBO_VIDEO_PATTERN)->SetCurSel(m_pDev->m_btPatternNum);

	if (m_dwUnitRev == 2)
	{
		M_GETSTATIC(IDC_STATIC_BIT6_LABEL)->SetWindowText("Power Supply Failure:");
	}
	else
	{
		M_GETSTATIC(IDC_STATIC_BIT6_LABEL)->SetWindowText("Spare:");
	}


	RefreshPatColor(0, m_pDev->m_pPatCol[0]);
	RefreshPatColor(1, m_pDev->m_pPatCol[1]);
	

	g_remotePnl.SetParams(this);
	g_remotePnl.Create(IDD_CRemotePanel, this);
	// g_remotePnl.SetParams(this);
	// g_remotePnl.SubclassDlgItem(IDD_CRemotePanel, this);
	g_remotePnl.ShowWindow(1);


	#ifdef HIDE_MAIN_SW
		this->MoveWindow(2000, 2000, 2000, 2000);
	#endif

	m_ssLogFilePath.SetWindowText(m_pDev->m_sLogFilePath.GetStringC());
	m_ssLogFilePath.SetBkColor(STTE_COLOR_YELLOW);



	SetTimer(DHA55_REFRESHTIMER_ID, DHA55_REFRESHTIMER_TIMEOUT, NULL); //Creo il timer generale

	RefreshData();

	return TRUE;  // return TRUE  unless you set the focus to a control
}


// -----------------------------------------------------------------------------------
//	CDha5x5_STTEDlg::RefreshData
// -----------------------------------------------------------------------------------

void CDha5x5_STTEDlg::RefreshData()
{
	DWORD		k;
	CString		s;
	double		d;

	if (!m_pDev->IsConnected())
	{
		m_ssDinBitOut.SetBkColor(STTE_COLOR_LIGHTGREY);
		m_ssDinBitOut.SetWindowText("---");

		m_ssDinBitEvent.SetBkColor(STTE_COLOR_LIGHTGREY);
		m_ssDinBitEvent.SetWindowText("---");

		for (k=0; k<2; k++)
		{
			m_pssHtrStat[k].SetBkColor(STTE_COLOR_LIGHTGREY);
			m_pssHtrStat[k].SetWindowText("---");
		}

		m_ssAd590Hex.SetBkColor(STTE_COLOR_LIGHTGREY);
		m_ssAd590Hex.SetWindowText("---");

		m_ssAd590Temp.SetBkColor(STTE_COLOR_LIGHTGREY);
		m_ssAd590Temp.SetWindowText("---");
	}
	else if (m_pDev->IsTimeout())
	{
		m_ssDinBitOut.SetBkColor(STTE_COLOR_ORANGE);
		m_ssDinBitOut.SetWindowText("---");

		m_ssDinBitEvent.SetBkColor(STTE_COLOR_ORANGE);
		m_ssDinBitEvent.SetWindowText("---");

		for (k=0; k<2; k++)
		{
			m_pssHtrStat[k].SetBkColor(STTE_COLOR_ORANGE);
			m_pssHtrStat[k].SetWindowText("---");
		}

		m_ssAd590Hex.SetBkColor(STTE_COLOR_ORANGE);
		m_ssAd590Hex.SetWindowText("---");

		m_ssAd590Temp.SetBkColor(STTE_COLOR_ORANGE);
		m_ssAd590Temp.SetWindowText("---");
	}
	else
	{
		if (m_pDev->m_bDinBitOut)
		{
			m_ssDinBitOut.SetBkColor(STTE_COLOR_GREEN);
			m_ssDinBitOut.SetWindowText("OK");
		}
		else
		{
			m_ssDinBitOut.SetBkColor(STTE_COLOR_RED);
			m_ssDinBitOut.SetWindowText("FAIL");
		}

		if (m_pDev->m_bDinBitEvent)
		{
			m_ssDinBitEvent.SetBkColor(STTE_COLOR_GREEN);
			m_ssDinBitEvent.SetWindowText("ON");
		}
		else
		{
			m_ssDinBitEvent.SetBkColor(STTE_COLOR_GREY);
			m_ssDinBitEvent.SetWindowText("OFF");
		}

		for (k=0; k<2; k++)
		{
			if (m_pDev->m_pbHtrStat[k])
			{
				m_pssHtrStat[k].SetBkColor(STTE_COLOR_GREEN);
				m_pssHtrStat[k].SetWindowText("ON");
			}
			else
			{
				m_pssHtrStat[k].SetBkColor(STTE_COLOR_GREY);
				m_pssHtrStat[k].SetWindowText("OFF");
			}
		}

		m_pDev->m_MainLinkMutex.Lock();

		s.Format("0x%04X", m_pDev->m_wAd590);
		m_ssAd590Hex.SetWindowText(s);

		d = ((double)m_pDev->m_wAd590) * 0.212765957 - 272.9787234;
		s.Format("%.1f°C", d+0.05);

		m_ssAd590Temp.SetWindowText(s);
		m_pDev->m_MainLinkMutex.Unlock();

		if ((d < -50.0) || (d > 120.0))
		{
			m_ssAd590Hex.SetBkColor(STTE_COLOR_RED);
			m_ssAd590Temp.SetBkColor(STTE_COLOR_RED);
		}
		else
		{
			m_ssAd590Hex.SetBkColor(STTE_COLOR_GREEN);
			m_ssAd590Temp.SetBkColor(STTE_COLOR_GREEN);
		}
	}
}


// -----------------------------------------------------------------------------------
//	CDha5x5_STTEDlg::RefreshPatColor
// -----------------------------------------------------------------------------------

void CDha5x5_STTEDlg::RefreshPatColor(BYTE btIdx, CFMT_Color& col)
{
	CString		s;

	m_pssPatCol[btIdx].SetBkColor(m_pDev->m_pPatCol[btIdx]);

	s.Format("%d,%d,%d", m_pDev->m_pPatCol[btIdx].GetR(), m_pDev->m_pPatCol[btIdx].GetG(), m_pDev->m_pPatCol[btIdx].GetB());
	m_pssPatRgb[btIdx].SetBkColor(STTE_COLOR_YELLOW);
	m_pssPatRgb[btIdx].SetWindowText(s);
}


// -----------------------------------------------------------------------------------
//	CDha5x5_STTEDlg::OnSysCommand
// -----------------------------------------------------------------------------------

void CDha5x5_STTEDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}


// -----------------------------------------------------------------------------------
//	CDha5x5_STTEDlg::OnPaint
// -----------------------------------------------------------------------------------

void CDha5x5_STTEDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}


// -----------------------------------------------------------------------------------
//	CDha5x5_STTEDlg::OnQueryDragIcon
// -----------------------------------------------------------------------------------

HCURSOR CDha5x5_STTEDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


// -----------------------------------------------------------------------------------
//	CDha5x5_STTEDlg::OnOK
// -----------------------------------------------------------------------------------

void CDha5x5_STTEDlg::OnOK() 
{
}




// -----------------------------------------------------------------------------------
//	CDha5x5_STTEDlg::OnStnClickedStaticIpadd
// -----------------------------------------------------------------------------------

void CDha5x5_STTEDlg::OnStnClickedStaticIpadd()
{
	if (m_pDev->IsConnected())
	{
		return;
	}

	CEditIpDlg		d;

	d.m_sIpAddress = m_pDev->m_sIpAdd;

	if (d.DoModal() == IDOK)
	{
		m_pDev->m_sIpAdd = d.m_sIpAddress;
		m_pDev->SaveSettings();
		m_ssIpAdd.SetWindowText(m_pDev->m_sIpAdd);
	}
}


// -----------------------------------------------------------------------------------
//	CDha5x5_STTEDlg::OnCheckStartstte
// -----------------------------------------------------------------------------------

void CDha5x5_STTEDlg::OnCheckStartstte()
{
	t_FMT_Uint32		ret;

	if (M_GETBUTTON(IDC_CHECK_STARTSTTE)->GetCheck())
	{
		ret = m_pDev->Connect();

		if (ret == e_Return_FileError)
		{
			STTE_Message("Cannot open LOG file", MB_ICONSTOP);
			M_GETBUTTON(IDC_CHECK_STARTSTTE)->SetCheck(FALSE);
			return;
		}

		if (ret != e_Return_OK)
		{
			STTE_Message("Cannot connect UUT", MB_ICONSTOP);
			M_GETBUTTON(IDC_CHECK_STARTSTTE)->SetCheck(FALSE);
			return;
		}

		SetTimer(DHA55_STTETIMER_ID, DHA55_STTETIMER_TIMEOUT, NULL);

		EnableControls(TRUE);
	}
	else
	{
		KillTimer(DHA55_READTIMER_ID);
		KillTimer(DHA55_STTETIMER_ID);

		m_pDev->Disconnect();

		EnableControls(FALSE);

		m_bRet_BIT=FALSE;
		m_bRet_TXBrt=FALSE;
		m_bRet_RXBrt=FALSE;
		m_bRet_LumSensor=FALSE;
		m_bRet_BacklTemp=FALSE;
		m_bRet_HeaterMode=FALSE;
		m_bRet_SWVersion=FALSE;
		m_bRet_FanMode=FALSE;
		m_bRet_LampCtrlStatus=FALSE;

		M_GETSTATIC(IDC_STATIC_LUMINANCE_SENSOR)->SetWindowText("-----");
		M_GETSTATIC(IDC_STATIC_BACKLIGHT_TEMPERATURE)->SetWindowText("-----");
		M_GETSTATIC(IDC_STATIC_LAMP_CONTROL_STATUS)->SetWindowText("-----");
		M_GETSTATIC(IDC_STATIC_FAN_STATUS)->SetWindowText("-----");
		M_GETSTATIC(IDC_STATIC_HEATER_STATUS)->SetWindowText("-----");
		M_GETSTATIC(IDC_STATIC_SW_VERSION)->SetWindowText("-----");
		M_GETSTATIC(IDC_STATIC_LUMINANCE_LEVEL)->SetWindowText("-----");
		M_GETSTATIC(IDC_STATIC_BIT1)->SetWindowText("-----");
		M_GETSTATIC(IDC_STATIC_BIT2)->SetWindowText("-----");
		M_GETSTATIC(IDC_STATIC_BIT3)->SetWindowText("-----");
		M_GETSTATIC(IDC_STATIC_BIT4)->SetWindowText("-----");
		M_GETSTATIC(IDC_STATIC_BIT5)->SetWindowText("-----");
		M_GETSTATIC(IDC_STATIC_BIT6)->SetWindowText("-----");
		M_GETSTATIC(IDC_STATIC_BIT7)->SetWindowText("-----");
		M_GETSTATIC(IDC_STATIC_BIT8)->SetWindowText("-----");

		M_GETBUTTON(IDC_BUT_MM)->ModifyStyle(WS_DISABLED, 0);

		RedrawWindow();
	}
}


// -----------------------------------------------------------------------------------
//	CDha5x5_STTEDlg::CommMessage
// -----------------------------------------------------------------------------------

BOOL CDha5x5_STTEDlg::CommMessage(DWORD dwRet) 
{
	switch (dwRet)
	{
	case e_Return_OK:
		return TRUE;
	break;

	case e_Return_ProtocolError:
		AbortAutoRead();
		STTE_Message("Invalid Echo Received", MB_ICONSTOP, this);
		return FALSE;
	break;

	case e_Return_Timeout:
		AbortAutoRead();
		STTE_Message("Communication Timeout", MB_ICONSTOP, this);
		return FALSE;
	break;

	case e_Return_Fail:
	case e_Return_DriverError:
		AbortAutoRead();
		STTE_Message("Communication Failure", MB_ICONSTOP, this);
		return FALSE;
	break;

	default:
		AbortAutoRead();
		STTE_Message("Unknown error", MB_ICONSTOP, this);
		return FALSE;
	break;
	}

	return FALSE;
}


// -----------------------------------------------------------------------------------
//	CDha5x5_STTEDlg::AbortAutoRead
// -----------------------------------------------------------------------------------

void CDha5x5_STTEDlg::AbortAutoRead() 
{
	KillTimer(DHA55_READTIMER_ID);
	EnableAutoReadControls(FALSE);
	M_GETBUTTON(IDC_CHECK_AUTOREAD)->SetCheck(FALSE);
}


// -----------------------------------------------------------------------------------
//	CDha5x5_STTEDlg::EnableAutoReadControls
// -----------------------------------------------------------------------------------

void CDha5x5_STTEDlg::EnableAutoReadControls(BOOL bEnable)
{
	if (bEnable)
	{
		M_GETBUTTON(IDC_READFANSTATUS)->ModifyStyle(WS_DISABLED, 0);
		M_GETBUTTON(IDC_READLUMINANCELEV)->ModifyStyle(WS_DISABLED, 0);
		M_GETBUTTON(IDC_READLUMINANCE)->ModifyStyle(WS_DISABLED, 0);
		M_GETBUTTON(IDC_READBACKTEMP)->ModifyStyle(WS_DISABLED, 0);
		M_GETBUTTON(IDC_READLAMPSTATUS)->ModifyStyle(WS_DISABLED, 0);
		M_GETBUTTON(IDC_READHEATERSTATUS)->ModifyStyle(WS_DISABLED, 0);
		M_GETBUTTON(IDC_READSWVERSION)->ModifyStyle(WS_DISABLED, 0);
		M_GETBUTTON(IDC_READBITSTATUS)->ModifyStyle(WS_DISABLED, 0);
		M_GETBUTTON(IDC_BRT_TX)->ModifyStyle(WS_DISABLED, 0);
		M_GETBUTTON(IDC_FAN_TX)->ModifyStyle(WS_DISABLED, 0);
	}
	else
	{
		M_GETBUTTON(IDC_READFANSTATUS)->ModifyStyle(0, WS_DISABLED);
		M_GETBUTTON(IDC_READLUMINANCELEV)->ModifyStyle(0, WS_DISABLED);
		M_GETBUTTON(IDC_READLUMINANCE)->ModifyStyle(0, WS_DISABLED);
		M_GETBUTTON(IDC_READBACKTEMP)->ModifyStyle(0, WS_DISABLED);
		M_GETBUTTON(IDC_READLAMPSTATUS)->ModifyStyle(0, WS_DISABLED);
		M_GETBUTTON(IDC_READHEATERSTATUS)->ModifyStyle(0, WS_DISABLED);
		M_GETBUTTON(IDC_READSWVERSION)->ModifyStyle(0, WS_DISABLED);
		M_GETBUTTON(IDC_READBITSTATUS)->ModifyStyle(0, WS_DISABLED);
		M_GETBUTTON(IDC_BRT_TX)->ModifyStyle(0, WS_DISABLED);
		M_GETBUTTON(IDC_FAN_TX)->ModifyStyle(0, WS_DISABLED);
	}

	M_GETBUTTON(IDC_READFANSTATUS)->Invalidate();
	M_GETBUTTON(IDC_READLUMINANCELEV)->Invalidate();
	M_GETBUTTON(IDC_READLUMINANCE)->Invalidate();
	M_GETBUTTON(IDC_READBACKTEMP)->Invalidate();
	M_GETBUTTON(IDC_READLAMPSTATUS)->Invalidate();
	M_GETBUTTON(IDC_READHEATERSTATUS)->Invalidate();
	M_GETBUTTON(IDC_READSWVERSION)->Invalidate();
	M_GETBUTTON(IDC_READBITSTATUS)->Invalidate();
	M_GETBUTTON(IDC_BRT_TX)->Invalidate();
	M_GETBUTTON(IDC_FAN_TX)->Invalidate();
}


// -----------------------------------------------------------------------------------
//	CDha5x5_STTEDlg::EnableControls
// -----------------------------------------------------------------------------------

void CDha5x5_STTEDlg::EnableControls(BOOL bEnable)
{
	if (m_dwUnitRev == 2)
	{
		M_GETBUTTON(IDC_BUT_LOADER)->ModifyStyle(0, WS_VISIBLE);
	}
	else
	{
		M_GETBUTTON(IDC_BUT_LOADER)->ModifyStyle(WS_VISIBLE, 0);
	}

	if (bEnable)
	{
		M_GETBUTTON(IDC_RESTART)->ModifyStyle(WS_DISABLED, 0);
		M_GETBUTTON(IDC_BRT_TX)->ModifyStyle(WS_DISABLED, 0);
		M_GETBUTTON(IDC_FAN_TX)->ModifyStyle(WS_DISABLED, 0);
		M_GETBUTTON(IDC_READLUMINANCE)->ModifyStyle(WS_DISABLED, 0);
		M_GETBUTTON(IDC_READBACKTEMP)->ModifyStyle(WS_DISABLED, 0);
		M_GETBUTTON(IDC_READLAMPSTATUS)->ModifyStyle(WS_DISABLED, 0);
		M_GETBUTTON(IDC_READBITSTATUS)->ModifyStyle(WS_DISABLED, 0);
		M_GETBUTTON(IDC_READFANSTATUS)->ModifyStyle(WS_DISABLED, 0);
		M_GETBUTTON(IDC_READHEATERSTATUS)->ModifyStyle(WS_DISABLED, 0);
		M_GETBUTTON(IDC_READSWVERSION)->ModifyStyle(WS_DISABLED, 0);
		M_GETBUTTON(IDC_READLUMINANCELEV)->ModifyStyle(WS_DISABLED, 0);	
		M_GETBUTTON(IDC_INVALID_COMMAND)->ModifyStyle(WS_DISABLED, 0);
		M_GETBUTTON(IDC_UNREC_COMMAND)->ModifyStyle(WS_DISABLED, 0);
		M_GETBUTTON(IDC_TIMEOUT_COMMAND)->ModifyStyle(WS_DISABLED, 0);
		M_GETBUTTON(IDC_CHECK_AUTOREAD)->ModifyStyle(WS_DISABLED, 0);
		M_GETBUTTON(IDC_NOOP_COMMAND)->ModifyStyle(WS_DISABLED, 0);
		M_GETBUTTON(IDC_DAY_WARM_START_COMMAND)->ModifyStyle(WS_DISABLED, 0);
		M_GETBUTTON(IDC_NIGHT_WARM_START_COMMAND)->ModifyStyle(WS_DISABLED, 0);

		if (m_dwUnitRev == 2)
		{
			M_GETBUTTON(IDC_BUT_MAINT)->ModifyStyle(WS_DISABLED, 0);
			M_GETBUTTON(IDC_BUT_LOADER)->ModifyStyle(WS_DISABLED, 0);
		}
		else
		{
			M_GETBUTTON(IDC_BUT_MAINT)->ModifyStyle(WS_DISABLED, 0);
		}
	}
	else
	{
		M_GETBUTTON(IDC_RESTART)->ModifyStyle(0, WS_DISABLED);
		M_GETBUTTON(IDC_BRT_TX)->ModifyStyle(0, WS_DISABLED);
		M_GETBUTTON(IDC_FAN_TX)->ModifyStyle(0, WS_DISABLED);
		M_GETBUTTON(IDC_READLUMINANCE)->ModifyStyle(0, WS_DISABLED);
		M_GETBUTTON(IDC_READBACKTEMP)->ModifyStyle(0, WS_DISABLED);
		M_GETBUTTON(IDC_READLAMPSTATUS)->ModifyStyle(0, WS_DISABLED);
		M_GETBUTTON(IDC_READBITSTATUS)->ModifyStyle(0, WS_DISABLED);
		M_GETBUTTON(IDC_READFANSTATUS)->ModifyStyle(0, WS_DISABLED);
		M_GETBUTTON(IDC_READHEATERSTATUS)->ModifyStyle(0, WS_DISABLED);
		M_GETBUTTON(IDC_READSWVERSION)->ModifyStyle(0, WS_DISABLED);
		M_GETBUTTON(IDC_READLUMINANCELEV)->ModifyStyle(0, WS_DISABLED);
		M_GETBUTTON(IDC_INVALID_COMMAND)->ModifyStyle(0, WS_DISABLED);
		M_GETBUTTON(IDC_UNREC_COMMAND)->ModifyStyle(0, WS_DISABLED);
		M_GETBUTTON(IDC_TIMEOUT_COMMAND)->ModifyStyle(0, WS_DISABLED);
		M_GETBUTTON(IDC_CHECK_AUTOREAD)->ModifyStyle(0, WS_DISABLED);
		M_GETBUTTON(IDC_NOOP_COMMAND)->ModifyStyle(0, WS_DISABLED);
		M_GETBUTTON(IDC_DAY_WARM_START_COMMAND)->ModifyStyle(0, WS_DISABLED);
		M_GETBUTTON(IDC_NIGHT_WARM_START_COMMAND)->ModifyStyle(0, WS_DISABLED);

		if (m_dwUnitRev == 2)
		{
			M_GETBUTTON(IDC_BUT_MAINT)->ModifyStyle(0, WS_DISABLED);
			M_GETBUTTON(IDC_BUT_LOADER)->ModifyStyle(0, WS_DISABLED);
		}
		else
		{
			M_GETBUTTON(IDC_BUT_MAINT)->ModifyStyle(0, WS_DISABLED);
		}
	}

	M_GETBUTTON(IDC_RESTART)->Invalidate();
	M_GETBUTTON(IDC_BRT_TX)->Invalidate();
	M_GETBUTTON(IDC_FAN_TX)->Invalidate();
	M_GETBUTTON(IDC_CHECK_STARTSTTE)->Invalidate();
	M_GETBUTTON(IDC_READLUMINANCE)->Invalidate();
	M_GETBUTTON(IDC_READBACKTEMP)->Invalidate();
	M_GETBUTTON(IDC_READLAMPSTATUS)->Invalidate();
	M_GETBUTTON(IDC_READBITSTATUS)->Invalidate();
	M_GETBUTTON(IDC_READFANSTATUS)->Invalidate();
	M_GETBUTTON(IDC_READHEATERSTATUS)->Invalidate();
	M_GETBUTTON(IDC_READSWVERSION)->Invalidate();
	M_GETBUTTON(IDC_READLUMINANCELEV)->Invalidate();
	M_GETBUTTON(IDC_BUT_MAINT)->Invalidate();
	M_GETBUTTON(IDC_INVALID_COMMAND)->Invalidate();
	M_GETBUTTON(IDC_UNREC_COMMAND)->Invalidate();
	M_GETBUTTON(IDC_TIMEOUT_COMMAND)->Invalidate();
	M_GETBUTTON(IDC_CHECK_AUTOREAD)->Invalidate();
	M_GETBUTTON(IDC_BUT_LOADER)->Invalidate();
	M_GETBUTTON(IDC_NOOP_COMMAND)->Invalidate();
	M_GETBUTTON(IDC_DAY_WARM_START_COMMAND)->Invalidate();
	M_GETBUTTON(IDC_NIGHT_WARM_START_COMMAND)->Invalidate();
}	



// -----------------------------------------------------------------------------------
//	CDha5x5_STTEDlg::OnBrtTx
// -----------------------------------------------------------------------------------

void CDha5x5_STTEDlg::OnBrtTx() 
{
	CString				s;
	DWORD				dwRet;

	if (!m_pDev->IsConnected())
	{
		return;
	}

	CWaitCursor		WaitCursor;
	
	EnableControls(FALSE);

	if (m_btTXBrt <= 0xFF)
	{
		if (M_GETBUTTON(IDC_RADIO_DAY)->GetCheck())
		{
			dwRet = m_pDev->SetDayLuminance(m_btTXBrt, DHA55_TIMEOUTECHO);
		}
		else
		{
			dwRet = m_pDev->SetNightLuminance(m_btTXBrt, DHA55_TIMEOUTECHO);
		}

		m_bRet_TXBrt = CommMessage(dwRet);
	}

	EnableControls(TRUE);
}


// -----------------------------------------------------------------------------------
//	CDha5x5_STTEDlg::OnFanTx
// -----------------------------------------------------------------------------------

void CDha5x5_STTEDlg::OnFanTx() 
{
	CString				s;
	BYTE				btFan;
	DWORD				dwRet;

	if (!m_pDev->IsConnected())
	{
		return;
	}

	CWaitCursor		WaitCursor;

	EnableControls(FALSE);

	if (M_GETBUTTON(IDC_RADIO_FANAUTO)->GetCheck())
	{
		if (M_GETBUTTON(IDC_CHECK_FANONOFF)->GetCheck())
		{
			btFan = 0x02;
		}
		else
		{
			btFan = 0x00;
		}
	}

	else
	{
		if (M_GETBUTTON(IDC_CHECK_FANONOFF)->GetCheck())
		{
			btFan = 0x03;
		}
		else
		{
			btFan = 0x01;
		}
	}

	dwRet = m_pDev->SetFanCtrl(btFan, DHA55_TIMEOUTECHO);
	CommMessage(dwRet);

	EnableControls(TRUE);
}


// -----------------------------------------------------------------------------------
//	CDha5x5_STTEDlg::OnBnClickedCheckHtrEnable
// -----------------------------------------------------------------------------------

void CDha5x5_STTEDlg::OnBnClickedCheckHtrEnable()
{
	m_pDev->m_bHtrEnable = (BOOL)(M_GETBUTTON(IDC_CHECK_HTR_ENABLE)->GetCheck());
}


// -----------------------------------------------------------------------------------
//	CDha5x5_STTEDlg::OnBnClickedCheckDoutReset
// -----------------------------------------------------------------------------------

void CDha5x5_STTEDlg::OnBnClickedCheckDoutReset()
{
	m_pDev->m_bDoutReset = (BOOL)(M_GETBUTTON(IDC_CHECK_DOUT_RESET)->GetCheck());
}


// -----------------------------------------------------------------------------------
//	CDha5x5_STTEDlg::OnBnClickedCheckDoutShutdown
// -----------------------------------------------------------------------------------

void CDha5x5_STTEDlg::OnBnClickedCheckDoutShutdown()
{
	m_pDev->m_bDoutShutdown = (BOOL)(M_GETBUTTON(IDC_CHECK_DOUT_SHUTDOWN)->GetCheck());
}


// -----------------------------------------------------------------------------------
//	CDha5x5_STTEDlg::OnBnClickedCheckDoutGammasel1
// -----------------------------------------------------------------------------------

void CDha5x5_STTEDlg::OnBnClickedCheckDoutGammasel1()
{
	m_pDev->m_pbDoutGamma[0] = (BOOL)(M_GETBUTTON(IDC_CHECK_DOUT_GAMMASEL1)->GetCheck());
}


// -----------------------------------------------------------------------------------
//	CDha5x5_STTEDlg::OnBnClickedCheckDoutSpare1
// -----------------------------------------------------------------------------------

void CDha5x5_STTEDlg::OnBnClickedCheckDoutSpare1()
{
	m_pDev->m_pbDoutSpare[0] = (BOOL)(M_GETBUTTON(IDC_CHECK_DOUT_SPARE1)->GetCheck());
}


// -----------------------------------------------------------------------------------
//	CDha5x5_STTEDlg::OnBnClickedCheckDoutGammasel2
// -----------------------------------------------------------------------------------

void CDha5x5_STTEDlg::OnBnClickedCheckDoutGammasel2()
{
	m_pDev->m_pbDoutGamma[1] = (BOOL)(M_GETBUTTON(IDC_CHECK_DOUT_GAMMASEL2)->GetCheck());
}


// -----------------------------------------------------------------------------------
//	CDha5x5_STTEDlg::OnBnClickedCheckDoutSpare2
// -----------------------------------------------------------------------------------

void CDha5x5_STTEDlg::OnBnClickedCheckDoutSpare2()
{
	m_pDev->m_pbDoutSpare[1] = (BOOL)(M_GETBUTTON(IDC_CHECK_DOUT_SPARE2)->GetCheck());
}


// -----------------------------------------------------------------------------------
//	CDha5x5_STTEDlg::OnStnClickedStaticPatCol1
// -----------------------------------------------------------------------------------

void CDha5x5_STTEDlg::OnStnClickedStaticPatCol1()
{
	CColorDialog	d(m_pDev->m_pPatCol[0]);

	if (d.DoModal() == IDOK)
	{
		m_pDev->m_pPatCol[0] = d.GetColor();
		RefreshPatColor(0, m_pDev->m_pPatCol[0]);
	}
}


// -----------------------------------------------------------------------------------
//	CDha5x5_STTEDlg::OnStnClickedStaticPatCol2
// -----------------------------------------------------------------------------------

void CDha5x5_STTEDlg::OnStnClickedStaticPatCol2()
{
	CColorDialog	d(m_pDev->m_pPatCol[1]);

	if (d.DoModal() == IDOK)
	{
		m_pDev->m_pPatCol[1] = d.GetColor();
		RefreshPatColor(1, m_pDev->m_pPatCol[1]);
	}
}


// -----------------------------------------------------------------------------------
//	CDha5x5_STTEDlg::OnStnClickedStaticPatRgb1
// -----------------------------------------------------------------------------------

void CDha5x5_STTEDlg::OnStnClickedStaticPatRgb1()
{
	OnStnClickedStaticPatCol1();
}


// -----------------------------------------------------------------------------------
//	CDha5x5_STTEDlg::OnStnClickedStaticPatRgb2
// -----------------------------------------------------------------------------------

void CDha5x5_STTEDlg::OnStnClickedStaticPatRgb2()
{
	OnStnClickedStaticPatCol2();
}


// -----------------------------------------------------------------------------------
//	CDha5x5_STTEDlg::OnBnClickedRadioVideoPatternGen
// -----------------------------------------------------------------------------------

void CDha5x5_STTEDlg::OnBnClickedRadioVideoPatternGen()
{
	m_pDev->m_bLvdsSel = FALSE;

	M_GETBUTTON(IDC_RADIO_VIDEO_PATTERN_GEN)->SetCheck(!m_pDev->m_bLvdsSel);
	M_GETBUTTON(IDC_RADIO_VIDEO_EXT_PLAYER)->SetCheck(m_pDev->m_bLvdsSel);
}


// -----------------------------------------------------------------------------------
//	CDha5x5_STTEDlg::OnBnClickedRadioVideoExtPlayer
// -----------------------------------------------------------------------------------

void CDha5x5_STTEDlg::OnBnClickedRadioVideoExtPlayer()
{
	m_pDev->m_bLvdsSel = TRUE;

	M_GETBUTTON(IDC_RADIO_VIDEO_PATTERN_GEN)->SetCheck(!m_pDev->m_bLvdsSel);
	M_GETBUTTON(IDC_RADIO_VIDEO_EXT_PLAYER)->SetCheck(m_pDev->m_bLvdsSel);
}


// -----------------------------------------------------------------------------------
//	CDha5x5_STTEDlg::OnCbnSelendokComboVideoPattern
// -----------------------------------------------------------------------------------

void CDha5x5_STTEDlg::OnCbnSelendokComboVideoPattern()
{
	m_pDev->m_btPatternNum = (BYTE)M_GETCOMBO(IDC_COMBO_VIDEO_PATTERN)->GetCurSel();
}


// -----------------------------------------------------------------------------------
//	CDha5x5_STTEDlg::OnBnClickedButDebug
// -----------------------------------------------------------------------------------

void CDha5x5_STTEDlg::OnBnClickedButDebug()
{
	t_FMT_Uint32		uiRet;
	
	uiRet = m_pDev->ConnectSpi();

	t_FMT_Uint8			pbtTxBuf[64];
	t_FMT_Uint8			pbtRxBuf[64];

	pbtTxBuf[0] = 0xA1;
	pbtTxBuf[1] = 0xA2;
	pbtTxBuf[2] = 0xA3;

	uiRet = m_pDev->PerformSpiTransfer(pbtTxBuf, 3, pbtRxBuf, 10, 3);


	uiRet = m_pDev->DisconnectSpi();

	return;

	 
	#if 0
	DWORD		dwTestCycles;
	BYTE		*pbtTxBuf;
	BYTE		*pbtRxBuf;
	DWORD		c;
	DWORD		dwLen;
	DWORD		k;
	DWORD		dwAnsTime;
	DWORD		dwError;
	DWORD		dwReadLen;
	CString		s;

	pbtTxBuf = new BYTE[256];
	pbtRxBuf = new BYTE[256];

	dwTestCycles = 100;
	dwError = 0;

	for (c=0; c<dwTestCycles; c++)
	{
		s.Format(">> TEST CYCLE %d\n", c+1);
		OutputDebugString(s);

		memset(pbtTxBuf, 0, 256);
		memset(pbtRxBuf, 0, 256);

		dwLen = (DWORD)((WORD)(rand() % 255) + 1);
		//dwLen = 20;

		for (k=0; k<dwLen; k++)
		{
			pbtTxBuf[k] = (BYTE)(rand() % 255);
		}

		dwAnsTime = (DWORD)(((1.0 / 9600.0) * dwLen * 11 * 1.8) * 1000.0);

		m_pDev->UartWrite(pbtTxBuf, dwLen);

		//Sleep(dwAnsTime);
		Sleep(1000);

		if (m_pDev->UartGetRxLength() != dwLen)
		{
			dwError++;
		}
		else
		{
			m_pDev->UartRead(pbtRxBuf, dwLen, dwReadLen);

			if (memcmp(pbtTxBuf, pbtRxBuf, dwLen) != 0)
			{
				dwError++;
			}
		}

	}
	#endif
}


// -----------------------------------------------------------------------------------
//	CDha5x5_STTEDlg::OnTimer
// -----------------------------------------------------------------------------------

void CDha5x5_STTEDlg::OnTimer(UINT nIDEvent) // aggiorna i dati letti
{
	if (nIDEvent == DHA55_STTETIMER_ID)
	{
		m_pDev->SendMainLinkPacket();
	}
	else if (nIDEvent == DHA55_REFRESHTIMER_ID)
	{
		RefreshData();
	}
	else if (nIDEvent == DHA55_READTIMER_ID)
	{
		DWORD	dwRet;
		int		iTemp;
		CString	s;
		BYTE	btFan;

		// Read Luminance
		dwRet = m_pDev->ReadLuminanceComm(&m_btRXBrt,DHA55_TIMEOUTECHO);

		if (!CommMessage(dwRet))
		{
			s="-----";
			m_bRet_RXBrt=FALSE;
			return;
		}
		else
		{
			s.Format("%d",m_btRXBrt);
			m_bRet_RXBrt=TRUE;
		}
		M_GETSTATIC(IDC_STATIC_LUMINANCE_LEVEL)->SetWindowText(s);

		// Read Luminance Sensor
		dwRet = m_pDev->ReadLuminanceSensor(&m_btLumSensor,DHA55_TIMEOUTECHO);

		if (!CommMessage(dwRet))
		{
			s="-----";
			m_bRet_LumSensor=FALSE;
			return;
		}
		else
		{
			s.Format("%d",m_btLumSensor);
			m_bRet_LumSensor=TRUE;
		}
		M_GETSTATIC(IDC_STATIC_LUMINANCE_SENSOR)->SetWindowText(s);

		// Read Fan Status
		dwRet = m_pDev->ReadFanStatus(&m_btFanMode,DHA55_TIMEOUTECHO);

		if (!CommMessage(dwRet))
		{
			s="-----";
			m_bRet_FanMode=FALSE;
			return;
		}
		else
		{
			s.Format("0x%X",m_btFanMode);
			m_bRet_FanMode=TRUE;
		}
		M_GETSTATIC(IDC_STATIC_FAN_STATUS)->SetWindowText(s);

		// Read backligh temperature
		dwRet = m_pDev->ReadBacklTemp(&m_btBacklTemp,DHA55_TIMEOUTECHO);

		if (!CommMessage(dwRet))
		{
			s="-----";
			m_bRet_BacklTemp=FALSE;
			return;
		}
		else
		{
			iTemp=(int)(m_btBacklTemp)-55;
			s.Format("%d°C",iTemp);
			m_bRet_BacklTemp=TRUE;
		}
		M_GETSTATIC(IDC_STATIC_BACKLIGHT_TEMPERATURE)->SetWindowText(s);

		// Read Lamp Status
		dwRet = m_pDev->ReadLampLEDsCtrlStatus(&m_btLampCtrlStatus,DHA55_TIMEOUTECHO);

		if (!CommMessage(dwRet))
		{
			s="-----";
			m_bRet_LampCtrlStatus=FALSE;
			return;
		}
		else
		{
			s.Format("0x%02X",m_btLampCtrlStatus);
			m_bRet_LampCtrlStatus=TRUE;
		}
		M_GETSTATIC(IDC_STATIC_LAMP_CONTROL_STATUS)->SetWindowText(s);

		// Read heater status
		dwRet = m_pDev->ReadHeaterStatus(&m_btHeaterMode,DHA55_TIMEOUTECHO);

		if (!CommMessage(dwRet))
		{
			s="-----";
			m_bRet_HeaterMode=FALSE;
			return;
		}
		else
		{
			s.Format("0x%02X",m_btHeaterMode);
			m_bRet_HeaterMode=TRUE;
		}
		M_GETSTATIC(IDC_STATIC_HEATER_STATUS)->SetWindowText(s);

		// Read software version
		dwRet = m_pDev->ReadSWVersion(&m_btSWVersion,DHA55_TIMEOUTECHO);

		if (!CommMessage(dwRet))
		{
			s="-----";
			m_bRet_SWVersion=FALSE;
			return;
		}
		else
		{
			s.Format("0x%02X",m_btSWVersion);
			m_bRet_SWVersion=TRUE;
		}
		M_GETSTATIC(IDC_STATIC_SW_VERSION)->SetWindowText(s);

		// Read BIT Status
		dwRet = m_pDev->ReadBITStatus(&m_btBIT,DHA55_TIMEOUTECHO);

		if (!CommMessage(dwRet))
		{	
			M_GETSTATIC(IDC_STATIC_BIT1)->SetWindowText("-----");
			M_GETSTATIC(IDC_STATIC_BIT2)->SetWindowText("-----");
			M_GETSTATIC(IDC_STATIC_BIT3)->SetWindowText("-----");
			M_GETSTATIC(IDC_STATIC_BIT4)->SetWindowText("-----");
			M_GETSTATIC(IDC_STATIC_BIT5)->SetWindowText("-----");
			M_GETSTATIC(IDC_STATIC_BIT6)->SetWindowText("-----");
			M_GETSTATIC(IDC_STATIC_BIT7)->SetWindowText("-----");
			M_GETSTATIC(IDC_STATIC_BIT8)->SetWindowText("-----");
			m_bRet_BIT=FALSE;
			return;
		}
		else
		{
			m_bRet_BIT=TRUE;

			if (M_GETBIT(m_btBIT,0))
			{
				M_GETSTATIC(IDC_STATIC_BIT1)->SetWindowText("OK");
			}
			else
			{
				M_GETSTATIC(IDC_STATIC_BIT1)->SetWindowText("FAIL");
			}

			if (M_GETBIT(m_btBIT,1))
			{
				M_GETSTATIC(IDC_STATIC_BIT2)->SetWindowText("OK");
			}
			else
			{
				M_GETSTATIC(IDC_STATIC_BIT2)->SetWindowText("FAIL");
			}

			if (M_GETBIT(m_btBIT,2))
			{
				M_GETSTATIC(IDC_STATIC_BIT3)->SetWindowText("OK");
			}
			else
			{
				M_GETSTATIC(IDC_STATIC_BIT3)->SetWindowText("FAIL");
			}

			if (M_GETBIT(m_btBIT,3))
			{
				M_GETSTATIC(IDC_STATIC_BIT4)->SetWindowText("OK");
			}
			else
			{
				M_GETSTATIC(IDC_STATIC_BIT4)->SetWindowText("FAIL");
			}

			if (M_GETBIT(m_btBIT,4))
			{
				M_GETSTATIC(IDC_STATIC_BIT5)->SetWindowText("OK");
			}
			else
			{
				M_GETSTATIC(IDC_STATIC_BIT5)->SetWindowText("FAIL");
			}

			if (M_GETBIT(m_btBIT,5))
			{
				M_GETSTATIC(IDC_STATIC_BIT6)->SetWindowText("OK");
			}
			else
			{
				M_GETSTATIC(IDC_STATIC_BIT6)->SetWindowText("FAIL");
			}

			if (M_GETBIT(m_btBIT,6))
			{
				M_GETSTATIC(IDC_STATIC_BIT7)->SetWindowText("OK");
			}
			else
			{
				M_GETSTATIC(IDC_STATIC_BIT7)->SetWindowText("FAIL");
			}

			if (M_GETBIT(m_btBIT,7))
			{
				M_GETSTATIC(IDC_STATIC_BIT8)->SetWindowText("OK");
			}
			else
			{
				M_GETSTATIC(IDC_STATIC_BIT8)->SetWindowText("FAIL");
			}
		}

		if (m_btTXBrt <= 0xFF)
		{
			if (M_GETBUTTON(IDC_RADIO_DAY)->GetCheck())
			{
				dwRet = m_pDev->SetDayLuminance(m_btTXBrt, DHA55_TIMEOUTECHO);
			}
			else
			{
				dwRet = m_pDev->SetNightLuminance(m_btTXBrt, DHA55_TIMEOUTECHO);
			}

			m_bRet_TXBrt = CommMessage(dwRet);
		}

		if (M_GETBUTTON(IDC_RADIO_FANAUTO)->GetCheck())
		{
			if (M_GETBUTTON(IDC_CHECK_FANONOFF)->GetCheck())
			{
				btFan = 0x02;
			}
			else
			{
				btFan = 0x00;
			}
		}

		else
		{
			if (M_GETBUTTON(IDC_CHECK_FANONOFF)->GetCheck())
			{
				btFan = 0x03;
			}
			else
			{
				btFan = 0x01;
			}
		}

		dwRet = m_pDev->SetFanCtrl(btFan, DHA55_TIMEOUTECHO);
		CommMessage(dwRet);
	}


	CDialog::OnTimer(nIDEvent);
}





/////////////////////////////////////////////////////////////////////////////
// OnCtlColor
/////////////////////////////////////////////////////////////////////////////

HBRUSH CDha5x5_STTEDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	switch (pWnd->GetDlgCtrlID())
	{
	case IDC_STATIC_COMPORT:
		pDC->SetBkMode(TRANSPARENT);
		hbr=m_brReadOnly; 
	break;

	case IDC_STATIC_LUMINANCE_SENSOR:
		if (m_bRet_LumSensor)
		{
			hbr=m_brReadOnly; 
		}
		else
		{
			hbr=m_brInvalid; 
		}
		pDC->SetBkMode(TRANSPARENT);
	break;

	case IDC_STATIC_BACKLIGHT_TEMPERATURE:
		if (m_bRet_BacklTemp)
		{
			hbr=m_brReadOnly; 
		}
		else
		{
			hbr=m_brInvalid; 
		}
		pDC->SetBkMode(TRANSPARENT);
	break;

	case IDC_STATIC_LAMP_CONTROL_STATUS:
		if (m_bRet_LampCtrlStatus)
		{
			hbr=m_brReadOnly; 
		}
		else
		{
			hbr=m_brInvalid; 
		}
		pDC->SetBkMode(TRANSPARENT);
	break;

	case IDC_STATIC_FAN_STATUS:
		if (m_bRet_FanMode)
		{
			hbr=m_brReadOnly; 
		}
		else
		{
			hbr=m_brInvalid; 
		}
		pDC->SetBkMode(TRANSPARENT);
	break;
	
	case IDC_STATIC_HEATER_STATUS:
		if (m_bRet_HeaterMode)
		{
			hbr=m_brReadOnly; 
		}
		else
		{
			hbr=m_brInvalid; 
		}
		pDC->SetBkMode(TRANSPARENT);
	break;
	
	case IDC_STATIC_SW_VERSION:
		if (m_bRet_SWVersion)
		{
			hbr=m_brReadOnly; 
		}
		else
		{
			hbr=m_brInvalid; 
		}
		pDC->SetBkMode(TRANSPARENT);
	break;
	
	case IDC_STATIC_LUMINANCE_LEVEL:
		if (m_bRet_RXBrt)
		{
			hbr=m_brReadOnly; 
		}
		else
		{
			hbr=m_brInvalid; 
		}
		pDC->SetBkMode(TRANSPARENT);
	break;

	case IDC_STATIC_BIT1:

		if (m_bRet_BIT)
		{
			if (M_GETBIT(m_btBIT,0))
			{
				hbr=m_brOk; 
			}
			else
			{
				hbr=m_brFail; 
			}
		}
		else
		{
			hbr=m_brInvalid; 
		}
		pDC->SetBkMode(TRANSPARENT);
	break;

	case IDC_STATIC_BIT2:

		if (m_bRet_BIT)
		{
			if (M_GETBIT(m_btBIT,1))
			{
				hbr=m_brOk; 
			}
			else
			{
				hbr=m_brFail; 
			}
		}
		else
		{
			hbr=m_brInvalid; 
		}
		pDC->SetBkMode(TRANSPARENT);
	break;

	case IDC_STATIC_BIT3:

		if (m_bRet_BIT)
		{
			if (M_GETBIT(m_btBIT,2))
			{
				hbr=m_brOk; 
			}
			else
			{
				hbr=m_brFail; 
			}
		}
		else
		{
			hbr=m_brInvalid; 
		}
		pDC->SetBkMode(TRANSPARENT);
	break;

	case IDC_STATIC_BIT4:

		if (m_bRet_BIT)
		{
			if (M_GETBIT(m_btBIT,3))
			{
				hbr=m_brOk; 
			}
			else
			{
				hbr=m_brFail; 
			}
		}
		else
		{
			hbr=m_brInvalid; 
		}
		pDC->SetBkMode(TRANSPARENT);
	break;

	case IDC_STATIC_BIT5:

		if (m_bRet_BIT)
		{
			if (M_GETBIT(m_btBIT,4))
			{
				hbr=m_brOk; 
			}
			else
			{
				hbr=m_brFail; 
			}
		}
		else
		{
			hbr=m_brInvalid; 
		}
		pDC->SetBkMode(TRANSPARENT);
	break;

	case IDC_STATIC_BIT6:

		if (m_bRet_BIT)
		{
			if (M_GETBIT(m_btBIT,5))
			{
				hbr=m_brOk; 
			}
			else
			{
				hbr=m_brFail; 
			}
		}
		else
		{
			hbr=m_brInvalid; 
		}
		pDC->SetBkMode(TRANSPARENT);
	break;

	case IDC_STATIC_BIT7:

		if (m_bRet_BIT)
		{
			if (M_GETBIT(m_btBIT,6))
			{
				hbr=m_brOk; 
			}
			else
			{
				hbr=m_brFail; 
			}
		}
		else
		{
			hbr=m_brInvalid; 
		}
		pDC->SetBkMode(TRANSPARENT);
	break;

	case IDC_STATIC_BIT8:

		if (m_bRet_BIT)
		{
			if (M_GETBIT(m_btBIT,7))
			{
				hbr=m_brOk; 
			}
			else
			{
				hbr=m_brFail; 
			}
		}
		else
		{
			hbr=m_brInvalid; 
		}
		pDC->SetBkMode(TRANSPARENT);
	break;

	}
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

// -----------------------------------------------------------------------------------
//	CDha5x5_STTEDlg::OnCancel
// -----------------------------------------------------------------------------------

void CDha5x5_STTEDlg::OnCancel()
{
	m_pDev->Disconnect();
	/*
	m_pDev->Close();

	SaveSettings();
	*/

	CDialog::OnCancel();
}



// -----------------------------------------------------------------------------------
//	CDha5x5_STTEDlg::OnRestart
// -----------------------------------------------------------------------------------

void CDha5x5_STTEDlg::OnRestart() 
{
	if (!m_pDev->IsConnected())
	{
		return;
	}

	CWaitCursor			WaitCursor;
	DWORD				dwRet;
	
	EnableControls(FALSE);

	dwRet = m_pDev->SW_ResetRestart_Comm(DHA55_TIMEOUTECHO);
	CommMessage(dwRet);

	EnableControls(TRUE);

}

/////////////////////////////////////////////////////////////////////////////
// OnTestMessage
/////////////////////////////////////////////////////////////////////////////
LRESULT CDha5x5_STTEDlg::OnTestMessage(UINT wParam,LONG lParam) 
{
	CString s;

	AfxGetApp()->DoWaitCursor(0);

	switch (wParam)
	{
	case 0:
		STTE_Message("Test FAILED", MB_ICONSTOP);
	break;

	case 1:
		STTE_Message("Test OK", MB_ICONINFORMATION);
	break;

	case 2:
		STTE_Message("Brightness Error Value", MB_ICONWARNING);
	break;

	}

	EnableControls(TRUE);

	return 0;
}





/////////////////////////////////////////////////////////////////////////////
// ReturnEcho
/////////////////////////////////////////////////////////////////////////////
CString CDha5x5_STTEDlg::ReturnEcho(DWORD dwReturn) 
{
	CString s;

	switch(dwReturn)
	{
		case 0:
			s = "OK";
		break;

		case 1:
			s="Fail";
		break;

		case 2:
			s="Invalid Echo";
		break;

		case 3:
			s="Timeout";
		break;

		default:
			s="Fail";
		break;
	}

	return s;
}


// -----------------------------------------------------------------------------------
//	CDha5x5_STTEDlg::OnReadluminance
// -----------------------------------------------------------------------------------

void CDha5x5_STTEDlg::OnReadluminance() 
{
	if (!m_pDev->IsConnected())
	{
		return;
	}

	CString		s;
	DWORD		dwRet;

	EnableControls(FALSE);

	dwRet = m_pDev->ReadLuminanceSensor(&m_btLumSensor, DHA55_TIMEOUTECHO);

	if (!CommMessage(dwRet))
	{
		s = "-----";
		m_bRet_LumSensor = FALSE;
	}
	else
	{
		s.Format("%d", m_btLumSensor);
		m_bRet_LumSensor = TRUE;
	}
	M_GETSTATIC(IDC_STATIC_LUMINANCE_SENSOR)->SetWindowText(s);
	
	EnableControls(TRUE);
}


// -----------------------------------------------------------------------------------
//	CDha5x5_STTEDlg::OnReadbacktemp
// -----------------------------------------------------------------------------------

void CDha5x5_STTEDlg::OnReadbacktemp() 
{
	if (!m_pDev->IsConnected())
	{
		return;
	}

	CString		s;
	int			iTemp;
	DWORD		dwRet;

	EnableControls(FALSE);

	dwRet = m_pDev->ReadBacklTemp(&m_btBacklTemp, DHA55_TIMEOUTECHO);

	if (!CommMessage(dwRet))
	{
		s = "-----";
		m_bRet_BacklTemp = FALSE;
	}
	else
	{
		iTemp = (int)(m_btBacklTemp)-55;
		s.Format("%d°C", iTemp);
		m_bRet_BacklTemp = TRUE;
	}
	M_GETSTATIC(IDC_STATIC_BACKLIGHT_TEMPERATURE)->SetWindowText(s);
	
	EnableControls(TRUE);
}


// -----------------------------------------------------------------------------------
//	CDha5x5_STTEDlg::OnReadlampstatus
// -----------------------------------------------------------------------------------

void CDha5x5_STTEDlg::OnReadlampstatus() 
{
	if (!m_pDev->IsConnected())
	{
		return;
	}

	CString		s;
	DWORD		dwRet;

	EnableControls(FALSE);

	dwRet = m_pDev->ReadLampLEDsCtrlStatus(&m_btLampCtrlStatus, DHA55_TIMEOUTECHO);

	if (!CommMessage(dwRet))
	{
		s = "-----";
		m_bRet_LampCtrlStatus = FALSE;
	}
	else
	{
		s.Format("0x%02X", m_btLampCtrlStatus);
		m_bRet_LampCtrlStatus = TRUE;
	}
	M_GETSTATIC(IDC_STATIC_LAMP_CONTROL_STATUS)->SetWindowText(s);
	
	EnableControls(TRUE);
}

// -----------------------------------------------------------------------------------
//	CDha5x5_STTEDlg::OnReadbitstatus
// -----------------------------------------------------------------------------------

void CDha5x5_STTEDlg::OnReadbitstatus() 
{
	if (!m_pDev->IsConnected())
	{
		return;
	}

	CString		s;
	DWORD		dwRet;

	EnableControls(FALSE);

	dwRet = m_pDev->ReadBITStatus(&m_btBIT, DHA55_TIMEOUTECHO);

	if (!CommMessage(dwRet))
	{	
		M_GETSTATIC(IDC_STATIC_BIT1)->SetWindowText("-----");
		M_GETSTATIC(IDC_STATIC_BIT2)->SetWindowText("-----");
		M_GETSTATIC(IDC_STATIC_BIT3)->SetWindowText("-----");
		M_GETSTATIC(IDC_STATIC_BIT4)->SetWindowText("-----");
		M_GETSTATIC(IDC_STATIC_BIT5)->SetWindowText("-----");
		M_GETSTATIC(IDC_STATIC_BIT6)->SetWindowText("-----");
		M_GETSTATIC(IDC_STATIC_BIT7)->SetWindowText("-----");
		M_GETSTATIC(IDC_STATIC_BIT8)->SetWindowText("-----");
		m_bRet_BIT = FALSE;
	}
	else
	{
		m_bRet_BIT = TRUE;

		if (M_GETBIT(m_btBIT, 0))
		{
			M_GETSTATIC(IDC_STATIC_BIT1)->SetWindowText("OK");
		}
		else
		{
			M_GETSTATIC(IDC_STATIC_BIT1)->SetWindowText("FAIL");
		}

		if (M_GETBIT(m_btBIT, 1))
		{
			M_GETSTATIC(IDC_STATIC_BIT2)->SetWindowText("OK");
		}
		else
		{
			M_GETSTATIC(IDC_STATIC_BIT2)->SetWindowText("FAIL");
		}

		if (M_GETBIT(m_btBIT, 2))
		{
			M_GETSTATIC(IDC_STATIC_BIT3)->SetWindowText("OK");
		}
		else
		{
			M_GETSTATIC(IDC_STATIC_BIT3)->SetWindowText("FAIL");
		}

		if (M_GETBIT(m_btBIT, 3))
		{
			M_GETSTATIC(IDC_STATIC_BIT4)->SetWindowText("OK");
		}
		else
		{
			M_GETSTATIC(IDC_STATIC_BIT4)->SetWindowText("FAIL");
		}

		if (M_GETBIT(m_btBIT, 4))
		{
			M_GETSTATIC(IDC_STATIC_BIT5)->SetWindowText("OK");
		}
		else
		{
			M_GETSTATIC(IDC_STATIC_BIT5)->SetWindowText("FAIL");
		}

		if (M_GETBIT(m_btBIT, 5))
		{
			M_GETSTATIC(IDC_STATIC_BIT6)->SetWindowText("OK");
		}
		else
		{
			M_GETSTATIC(IDC_STATIC_BIT6)->SetWindowText("FAIL");
		}

		if (M_GETBIT(m_btBIT, 6))
		{
			M_GETSTATIC(IDC_STATIC_BIT7)->SetWindowText("OK");
		}
		else
		{
			M_GETSTATIC(IDC_STATIC_BIT7)->SetWindowText("FAIL");
		}

		if (M_GETBIT(m_btBIT, 7))
		{
			M_GETSTATIC(IDC_STATIC_BIT8)->SetWindowText("OK");
		}
		else
		{
			M_GETSTATIC(IDC_STATIC_BIT8)->SetWindowText("FAIL");
		}
	}

	EnableControls(TRUE);
}


// -----------------------------------------------------------------------------------
//	CDha5x5_STTEDlg::OnReadfanstatus
// -----------------------------------------------------------------------------------

void CDha5x5_STTEDlg::OnReadfanstatus() 
{
	if (!m_pDev->IsConnected())
	{
		return;
	}

	CString		s;
	DWORD		dwRet;

	EnableControls(FALSE);

	dwRet = m_pDev->ReadFanStatus(&m_btFanMode, DHA55_TIMEOUTECHO);

	if (!CommMessage(dwRet))
	{
		s = "-----";
		m_bRet_FanMode = FALSE;
	}
	else
	{
		s.Format("0x%X", m_btFanMode);
		m_bRet_FanMode = TRUE;
	}
	M_GETSTATIC(IDC_STATIC_FAN_STATUS)->SetWindowText(s);
	
	EnableControls(TRUE);
}


// -----------------------------------------------------------------------------------
//	CDha5x5_STTEDlg::OnReadheaterstatus
// -----------------------------------------------------------------------------------

void CDha5x5_STTEDlg::OnReadheaterstatus() 
{
	if (!m_pDev->IsConnected())
	{
		return;
	}

	CString		s;
	DWORD		dwRet;

	EnableControls(FALSE);

	dwRet = m_pDev->ReadHeaterStatus(&m_btHeaterMode, DHA55_TIMEOUTECHO);

	if (!CommMessage(dwRet))
	{
		s = "-----"; 
		m_bRet_HeaterMode = FALSE;
	}
	else
	{
		s.Format("0x%02X", m_btHeaterMode);
		m_bRet_HeaterMode=TRUE;
	}
	M_GETSTATIC(IDC_STATIC_HEATER_STATUS)->SetWindowText(s);
	
	EnableControls(TRUE);
}


// -----------------------------------------------------------------------------------
//	CDha5x5_STTEDlg::OnReadswversion
// -----------------------------------------------------------------------------------

void CDha5x5_STTEDlg::OnReadswversion() 
{
	if (!m_pDev->IsConnected())
	{
		return;
	}

	CString		s;
	DWORD		dwRet;

	EnableControls(FALSE);

	dwRet = m_pDev->ReadSWVersion(&m_btSWVersion, DHA55_TIMEOUTECHO);

	if (!CommMessage(dwRet))
	{
		s = "-----";
		m_bRet_SWVersion = FALSE;
	}
	else
	{
		s.Format("0x%02X", m_btSWVersion);
		m_bRet_SWVersion = TRUE;
	}
	M_GETSTATIC(IDC_STATIC_SW_VERSION)->SetWindowText(s);
	
	EnableControls(TRUE);
}


// -----------------------------------------------------------------------------------
//	CDha5x5_STTEDlg::OnReadluminancelev
// -----------------------------------------------------------------------------------

void CDha5x5_STTEDlg::OnReadluminancelev() 
{
	if (!m_pDev->IsConnected())
	{
		return;
	}

	CString		s;
	DWORD		dwRet;

	EnableControls(FALSE);

	dwRet = m_pDev->ReadLuminanceComm(&m_btRXBrt, DHA55_TIMEOUTECHO);

	if (!CommMessage(dwRet))
	{
		s = "-----";
		m_bRet_RXBrt = FALSE;
	}
	else
	{
		s.Format("%d", m_btRXBrt);
		m_bRet_RXBrt = TRUE;
	}
	M_GETSTATIC(IDC_STATIC_LUMINANCE_LEVEL)->SetWindowText(s);
	
	EnableControls(TRUE);

}


// -----------------------------------------------------------------------------------
//	CDha5x5_STTEDlg::OnBnClickedCheckAutoread
// -----------------------------------------------------------------------------------

void CDha5x5_STTEDlg::OnBnClickedCheckAutoread()
{
	if (M_GETBUTTON(IDC_CHECK_AUTOREAD)->GetCheck())
	{
		EnableAutoReadControls(FALSE);

		SetTimer(DHA55_READTIMER_ID, DHA55_READTIMER_TIMEOUT, NULL);
	}
	else
	{
		KillTimer(DHA55_READTIMER_ID);

		EnableAutoReadControls(TRUE);
	}
}



void CDha5x5_STTEDlg::OnStnClickedStaticComport()
{
	/*
	CCOMSelDlg	c;
		
	if (c.DoModal()==IDOK)
	{
		m_dwCOM=c.m_dwCOM;	// preleva il numero della porta COM selezionata dalla COMSELDlg
		SaveSettings();
	}
	*/
}

void CDha5x5_STTEDlg::OnBnClickedButMm()
{
	if (m_dwUnitRev == 2)
	{
		CBrtBuilderDlg	dlg;

		dlg.m_pDev = m_pDev;

		dlg.DoModal();
	}
	else
	{
		CMMDlg	dlg;

		dlg.m_pDev = m_pDev;

		dlg.DoModal();
	}
}


// -----------------------------------------------------------------------------------
//	CDha5x5_STTEDlg::OnBnClickedButMaint
// -----------------------------------------------------------------------------------

void CDha5x5_STTEDlg::OnBnClickedButMaint()
{
	if (m_dwUnitRev == 2)
	{
		CEnhMaintDlg	dlg;
		dlg.m_pDev = m_pDev;
		dlg.DoModal();
	}
	else
	{
		CMaintDlg	dlg;
		dlg.m_pDev = m_pDev;
		dlg.DoModal();
		CommMessage(dlg.m_dwRet);
	}
}


// -----------------------------------------------------------------------------------
//	CDha5x5_STTEDlg::OnBnClickedInvalidCommand
// -----------------------------------------------------------------------------------

void CDha5x5_STTEDlg::OnBnClickedInvalidCommand()
{
	#ifndef DHA55_COMPILE_NOHDW

	DWORD	dwRet;

	EnableControls(FALSE);

	dwRet = m_pDev->DoubleCommand(0x80, DHA55_TIMEOUTECHO);

	if (dwRet == e_Return_InvalidObject)
	{
		STTE_Message("Invalid Code correctly received", MB_ICONINFORMATION);
	}
	else
	{
		STTE_Message("Invalid Code not received", MB_ICONERROR);
	}

	EnableControls(TRUE);

	#endif 
}


// -----------------------------------------------------------------------------------
//	CDha5x5_STTEDlg::OnBnClickedInvalidCommand
// -----------------------------------------------------------------------------------

void CDha5x5_STTEDlg::OnBnClickedUnrecCommand()
{
	#ifndef DHA55_COMPILE_NOHDW

	DWORD	dwRet;

	EnableControls(FALSE);

	dwRet = m_pDev->UnrecognizedCommand(0x80, DHA55_TIMEOUTECHO);

	if (dwRet == e_Return_NotDefined)
	{
		STTE_Message("Unrecognized Code correctly received", MB_ICONINFORMATION);
	}
	else
	{
		STTE_Message("Unrecognized Code not received", MB_ICONERROR);
	}

	EnableControls(TRUE);

	#endif 
}


// -----------------------------------------------------------------------------------
//	CDha5x5_STTEDlg::OnBnClickedTimeoutCommand
// -----------------------------------------------------------------------------------

void CDha5x5_STTEDlg::OnBnClickedTimeoutCommand()
{
	#ifndef DHA55_COMPILE_NOHDW

	DWORD	dwRet;

	EnableControls(FALSE);

	dwRet = m_pDev->TestNoParamCommand(CDhaStteDevice::e_Code_SetDayLuminance, TIMEOUTNOPARAM);

	if (dwRet == e_Return_InvalidObject)
	{
		STTE_Message("Invalid Code correctly received", MB_ICONINFORMATION);
	}
	else
	{
		STTE_Message("Invalid Code not received", MB_ICONERROR);
	}

	EnableControls(TRUE);

	#endif
}

void CDha5x5_STTEDlg::OnStaticComport() 
{
	// TODO: Add your control notification handler code here
	
}




void CDha5x5_STTEDlg::OnEnChangeEditBrt()
{
	CString s;

	M_GETEDIT(IDC_EDIT_BRT)->GetWindowText(s);
	m_btTXBrt = atoi(s);
}

void CDha5x5_STTEDlg::OnDeltaposSpinBrt(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	CString	s;

	if (pNMUpDown->iDelta<0)
	{
		if (pNMUpDown->iDelta>-5)
		{
			if (m_btTXBrt<255)
				m_btTXBrt++;
			else m_btTXBrt=255;
		}
		else if (pNMUpDown->iDelta>-20)
		{
			if (m_btTXBrt<255-10)
				m_btTXBrt+=10;
			else m_btTXBrt=255;
		}
		else 
		{
			if (m_btTXBrt<255-100)
				m_btTXBrt+=100;
			else m_btTXBrt=255;
		}
	}
	else if (pNMUpDown->iDelta>0)
	{
		if (pNMUpDown->iDelta<5)
		{
			if (m_btTXBrt>1)
				m_btTXBrt--;
			else m_btTXBrt=0;
		}
		else if (pNMUpDown->iDelta<20)
		{
			if (m_btTXBrt>10)
				m_btTXBrt-=10;
			else m_btTXBrt=0;
		}
		else 
		{
			if (m_btTXBrt>100)
				m_btTXBrt-=100;
			else m_btTXBrt=0;
		}

	}

	s.Format("%d",m_btTXBrt);
	M_GETEDIT(IDC_EDIT_BRT)->SetWindowText(s);


	*pResult = 0;
}


// -----------------------------------------------------------------------------------
//	CDha5x5_STTEDlg::OnBnClickedCheckLogon
// -----------------------------------------------------------------------------------

void CDha5x5_STTEDlg::OnBnClickedCheckLogon()
{
	if (M_GETBUTTON(IDC_CHECK_LOGON)->GetCheck())
	{
		m_pDev->EnableLog(TRUE);
	}
	else
	{
		m_pDev->EnableLog(FALSE);
	}
}


// -----------------------------------------------------------------------------------
//	CDha5x5_STTEDlg::OnBnClickedButStteConfig
// -----------------------------------------------------------------------------------

void CDha5x5_STTEDlg::OnBnClickedButStteConfig()
{
	CStteConfigDlg		d;
	d.m_pDev = m_pDev;

	d.DoModal();
}



// -----------------------------------------------------------------------------------
//	CDha5x5_STTEDlg::NtcToMem
// -----------------------------------------------------------------------------------

void CDha5x5_STTEDlg::NtcToMem(const CFMT_String& sPath)
{
	DWORD			k;
	double			dAdcRef;
	double			v;
	DWORD			dwLutMax;
	double			dB_Param;
	double			dT0;
	double			dPullup;
	double			dNtcSupply;
	CFMT_File		f;
	CString			s;
	double			d;
	double			dR0;
	t_FMT_Uint8		ucVal;


	f.Open(sPath, CFMT_File::e_OpenMode_Write | CFMT_File::e_OpenMode_Overwrite);

	dAdcRef = 2.5;
	dwLutMax = 4096;
	dB_Param = 3380.0;
	dT0 = 25.0;
	dPullup = 15000.0;
	dNtcSupply = 2.5;
	dR0 = 10000.0;

	for (k=0; k<dwLutMax; k++)
	{
		if (k == 2674)
		{
			int a = 1;
		}

		v = ((double)k) * dAdcRef / (dwLutMax - 1);

		if (v >= dNtcSupply)
		{
			d = -100.0;
		}
		else
		{
			if (v == 0)
			{
				d = 126.75;	
			}
			else
			{
				d = (dB_Param / ((dB_Param / (dT0 + 273.0)) + log(((v*dPullup) / (dNtcSupply - v)) * (1/dR0)))) - 273.0;	
			}
		}

		d = (d + 0.5) + 55.0;

		d = max(d, 0.0);
		//d = min(d, 115.0);
		d = min(d, (double)0xAA);

		ucVal = (t_FMT_Uint8)d;
		s.Format("%02X", ucVal);
		f.WriteTextLine(s);
	}


	f.Close();

	STTE_Message("MEM correctly generated.",MB_ICONINFORMATION);
}


// -----------------------------------------------------------------------------------
//	CDha5x5_STTEDlg::OnStnClickedStaticLogPath
// -----------------------------------------------------------------------------------

void CDha5x5_STTEDlg::OnStnClickedStaticLogPath()
{
	if (m_pDev->IsConnected())
	{
		return;
	}

	CString		sPath;

	CFileDialog *pDlg=new CFileDialog(FALSE,"txt",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
		"Log Files (*.txt) | *.txt|",this);
	
	if (pDlg->DoModal()==IDOK)
	{
		sPath=pDlg->GetPathName();

		delete pDlg;
	}
	else
	{
		delete pDlg;
		return;
	}

	m_pDev->m_sLogFilePath = sPath;	
	m_pDev->SaveSettings();

	m_ssLogFilePath.SetWindowText(m_pDev->m_sLogFilePath.GetStringC());
}


// -----------------------------------------------------------------------------------
//	CDha5x5_STTEDlg::OnBnClickedButLoader
// -----------------------------------------------------------------------------------

void CDha5x5_STTEDlg::OnBnClickedButLoader()
{
	CLoaderDlg	d;

	d.m_pDev = m_pDev;

	d.DoModal();
}


// -----------------------------------------------------------------------------------
//	CDha5x5_STTEDlg::OnBnClickedNoopCommand
// -----------------------------------------------------------------------------------

void CDha5x5_STTEDlg::OnBnClickedNoopCommand()
{
	#ifndef DHA55_COMPILE_NOHDW

	DWORD	dwRet;

	EnableControls(FALSE);

	dwRet = m_pDev->NoopCommand(DHA55_TIMEOUTECHO);

	if (dwRet == e_Return_OK)
	{
		STTE_Message("Noop response correctly received", MB_ICONINFORMATION);
	}
	else
	{
		STTE_Message("Invalid Code not received", MB_ICONERROR);
	}

	EnableControls(TRUE);

	#endif 
}


// -----------------------------------------------------------------------------------
//	CDha5x5_STTEDlg::OnBnClickedDefWarmStartCommand
// -----------------------------------------------------------------------------------

void CDha5x5_STTEDlg::OnBnClickedDefWarmStartCommand()
{
	#ifndef DHA55_COMPILE_NOHDW

	DWORD	dwRet;

	EnableControls(FALSE);

	dwRet = m_pDev->DefaultWarmStartCommand(DHA55_TIMEOUTECHO);

	CommMessage(dwRet);

	EnableControls(TRUE);

	#endif 
}


// -----------------------------------------------------------------------------------
//	CDha5x5_STTEDlg::OnBnClickedDayWarmStartCommand
// -----------------------------------------------------------------------------------

void CDha5x5_STTEDlg::OnBnClickedDayWarmStartCommand()
{
	CString				s;
	DWORD				dwRet;

	if (!m_pDev->IsConnected())
	{
		return;
	}

	CWaitCursor		WaitCursor;
	
	EnableControls(FALSE);

	if (m_btTXBrt <= 0xFF)
	{
		dwRet = m_pDev->DayModeWarmStartCommand(m_btTXBrt, DHA55_TIMEOUTECHO);

		m_bRet_TXBrt = CommMessage(dwRet);
	}

	EnableControls(TRUE);
}


// -----------------------------------------------------------------------------------
//	CDha5x5_STTEDlg::OnBnClickedNightWarmStartCommand
// -----------------------------------------------------------------------------------

void CDha5x5_STTEDlg::OnBnClickedNightWarmStartCommand()
{
	CString				s;
	DWORD				dwRet;

	if (!m_pDev->IsConnected())
	{
		return;
	}

	CWaitCursor		WaitCursor;
	
	EnableControls(FALSE);

	if (m_btTXBrt <= 0xFF)
	{
		dwRet = m_pDev->NightModeWarmStartCommand(m_btTXBrt, DHA55_TIMEOUTECHO);

		m_bRet_TXBrt = CommMessage(dwRet);
	}

	EnableControls(TRUE);
}


BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	GetDlgItem(IDC_STATIC_CODE)->SetWindowText(STTE_CODE);
	GetDlgItem(IDC_STATIC_INTREV)->SetWindowText(STTE_INTERV);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
