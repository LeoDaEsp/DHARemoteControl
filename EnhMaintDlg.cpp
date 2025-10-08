// EnhMaintDlg.cpp : implementation file
//

#include "stdafx.h"
#include "dha5x5_STTE.h"
#include "EnhMaintDlg.h"
#include "ComDlg.h"
#include "BtlFile.h"
#include "BrtFbkCalibDlg.h"

// CEnhMaintDlg dialog

IMPLEMENT_DYNAMIC(CEnhMaintDlg, CDialog)

// -----------------------------------------------------------------------------------
//	CEnhMaintDlg::CEnhMaintDlg
// -----------------------------------------------------------------------------------

CEnhMaintDlg::CEnhMaintDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEnhMaintDlg::IDD, pParent)
{
	m_pDev = NULL;
	m_bReboot = FALSE;
}


// -----------------------------------------------------------------------------------
//	CEnhMaintDlg::~CEnhMaintDlg
// -----------------------------------------------------------------------------------

CEnhMaintDlg::~CEnhMaintDlg()
{
}


// -----------------------------------------------------------------------------------
//	CEnhMaintDlg Message Map
// -----------------------------------------------------------------------------------

BEGIN_MESSAGE_MAP(CEnhMaintDlg, CDialog)
	ON_STN_CLICKED(IDC_STATIC_COM2, &CEnhMaintDlg::OnStnClickedStaticCom2)
	ON_BN_CLICKED(IDC_CHECK_CONNECT, &CEnhMaintDlg::OnBnClickedCheckConnect)
	ON_WM_TIMER()
	ON_WM_HSCROLL()
	ON_CBN_SELENDOK(IDC_COMBO_POT, &CEnhMaintDlg::OnCbnSelendokComboPot)
	ON_EN_CHANGE(IDC_EDIT_DUTY, &CEnhMaintDlg::OnEnChangeEditDuty)
	ON_EN_CHANGE(IDC_EDIT_CURRENT, &CEnhMaintDlg::OnEnChangeEditCurrent)
	ON_BN_CLICKED(IDC_CHECK_DAY, &CEnhMaintDlg::OnBnClickedCheckDay)
	ON_BN_CLICKED(IDC_OPER_BRT_MODE, &CEnhMaintDlg::OnBnClickedOperBrtMode)
	ON_BN_CLICKED(IDC_CHECK_HEATER, &CEnhMaintDlg::OnBnClickedCheckHeater)
	ON_BN_CLICKED(IDC_CHECK_HTR_ENABLE, &CEnhMaintDlg::OnBnClickedCheckHtrEnable)
	ON_STN_CLICKED(IDC_STATIC_PAT_MCOL1, &CEnhMaintDlg::OnStnClickedStaticPatCol1)
	ON_STN_CLICKED(IDC_STATIC_PAT_MCOL2, &CEnhMaintDlg::OnStnClickedStaticPatCol2)
	ON_STN_CLICKED(IDC_STATIC_PAT_RGB1, &CEnhMaintDlg::OnStnClickedStaticPatRgb1)
	ON_STN_CLICKED(IDC_STATIC_PAT_RGB2, &CEnhMaintDlg::OnStnClickedStaticPatRgb2)
	ON_CBN_SELENDOK(IDC_COMBO_VIDEO_PATTERN, &CEnhMaintDlg::OnCbnSelendokComboVideoPattern)
	ON_CBN_SELENDOK(IDC_COMBO_MNT_OPERBRT, &CEnhMaintDlg::OnCbnSelendokComboMntOpBrt)
	ON_BN_CLICKED(IDC_BUT_CALIB_BRT_FEEDBACK, &CEnhMaintDlg::OnBnClickedButCalibBrtFeedback)
	ON_BN_CLICKED(IDC_BUT_REBOOT, &CEnhMaintDlg::OnBnClickedButReboot)
END_MESSAGE_MAP()


// -----------------------------------------------------------------------------------
//	CEnhMaintDlg::OnInitDialog
// -----------------------------------------------------------------------------------

BOOL CEnhMaintDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	DWORD		k;
	CString		s;

	// -- Subclassing --------------------------------------------

	m_ssCom.SubclassDlgItem(IDC_STATIC_COM2, this);
	m_slAnalogs.SubclassDlgItem(IDC_LIST_ANALOGS, this);
	m_slBit.SubclassDlgItem(IDC_LIST_BIT, this);
	m_ssEti.SubclassDlgItem(IDC_STATIC_ETI, this);
	m_ssHtrStatus.SubclassDlgItem(IDC_STATIC_HEATER_STATUS,this);
	m_pssPatCol[0].SubclassDlgItem(IDC_STATIC_PAT_MCOL1, this);
	m_pssPatCol[1].SubclassDlgItem(IDC_STATIC_PAT_MCOL2, this);
	m_pssPatRgb[0].SubclassDlgItem(IDC_STATIC_PAT_RGB1, this);
	m_pssPatRgb[1].SubclassDlgItem(IDC_STATIC_PAT_RGB2, this);

	// Analog Inputs
	m_slAnalogs.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_slAnalogs.InsertColumn(0, "Field", LVCFMT_CENTER, 120);
	m_slAnalogs.InsertColumn(1, "Hex", LVCFMT_CENTER, 80);
	m_slAnalogs.InsertColumn(2, "Value", LVCFMT_CENTER, 80);

	m_slAnalogs.InsertItem(0, "PS 1.0V");
	m_slAnalogs.InsertItem(1, "PS 1.5V");
	m_slAnalogs.InsertItem(2, "PS 1.8V");
	m_slAnalogs.InsertItem(3, "PS 3.3V");
	m_slAnalogs.InsertItem(4, "PS 5.0V");
	m_slAnalogs.InsertItem(5, "LCD 3.3V");
	m_slAnalogs.InsertItem(6, "Fan Current");
	m_slAnalogs.InsertItem(7, "NTC #2");
	m_slAnalogs.InsertItem(8, "NTC #1");
	m_slAnalogs.InsertItem(9, "AD590");
	m_slAnalogs.InsertItem(10, "Bkl Current NVG HI");
	m_slAnalogs.InsertItem(11, "Bkl Current NVG LO");
	m_slAnalogs.InsertItem(12, "Bkl Current Day HI");
	m_slAnalogs.InsertItem(13, "Bkl Current Day LO");
	m_slAnalogs.InsertItem(14, "Int.Temperature");


	// BIT
	m_slBit.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_slBit.InsertColumn(0, "Field", LVCFMT_CENTER, 126);
	m_slBit.InsertColumn(1, "Status", LVCFMT_CENTER, 80);

	m_slBit.InsertItem(0, "I/O Expander");
	m_slBit.InsertItem(1, "Int.Temp.Sensor");
	m_slBit.InsertItem(2, "Flash");
	m_slBit.InsertItem(3, "FRAM");
	m_slBit.InsertItem(4, "ADC #1");
	m_slBit.InsertItem(5, "ADC #2");
	m_slBit.InsertItem(6, "PS 1.0V");
	m_slBit.InsertItem(7, "PS 1.5V");
	m_slBit.InsertItem(8, "PS 1.8V");
	m_slBit.InsertItem(9, "PS 3.3V");
	m_slBit.InsertItem(10, "PS 5.0V");
	m_slBit.InsertItem(11, "LCD 3.3V");
	m_slBit.InsertItem(12, "NTC #2");
	m_slBit.InsertItem(13, "NTC #1");
	m_slBit.InsertItem(14, "AD590");
	m_slBit.InsertItem(15, "Backlight Driver");
	m_slBit.InsertItem(16, "Open Led Day Strip #1");
	m_slBit.InsertItem(17, "Open Led Day Strip #2");
	m_slBit.InsertItem(18, "Open Led Day Strip #3");
	m_slBit.InsertItem(19, "Open Led Day Strip #4");
	m_slBit.InsertItem(20, "Open Led NVG Strip #1");
	m_slBit.InsertItem(21, "Open Led NVG Strip #2");
	m_slBit.InsertItem(22, "Open Led NVG Strip #3");
	m_slBit.InsertItem(23, "Open Led NVG Strip #4");
	m_slBit.InsertItem(24, "Backlight Potentiometer");
	m_slBit.InsertItem(25, "LCD");
	m_slBit.InsertItem(26, "Fan");
	m_slBit.InsertItem(27, "Serial TX");
	m_slBit.InsertItem(28, "Overtemperature");
	m_slBit.InsertItem(29, "Day Luminance");
	m_slBit.InsertItem(30, "Nvg Luminance");
	m_slBit.InsertItem(31, "Heater");
	m_slBit.InsertItem(32, "Video RAM");


	// --- Brightness ----------------------

	M_GETSLIDER(IDC_SLIDER_DUTY)->SetRange(0, 65535);
	M_GETSLIDER(IDC_SLIDER_DUTY)->SetPos((int)(m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Brt].GetField(0, 16)));
	s.Format("%d", (int)(m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Brt].GetField(0, 16)));
	M_GETEDIT(IDC_EDIT_DUTY)->SetWindowText(s);

	M_GETSLIDER(IDC_SLIDER_CURRENT)->SetRange(0, 4095);
	M_GETSLIDER(IDC_SLIDER_CURRENT)->SetPos((int)(m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Brt].GetField(16, 12)));
	s.Format("%d", (int)(m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Brt].GetField(16, 12)));
	M_GETEDIT(IDC_EDIT_CURRENT)->SetWindowText(s);

	for (k=0; k<128; k++)
	{
		s.Format("%d", k);
		M_GETCOMBO(IDC_COMBO_POT)->AddString(s);
	}
	M_GETCOMBO(IDC_COMBO_POT)->SetCurSel((int)(m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Brt].GetField(28, 7)));

	M_GETBUTTON(IDC_CHECK_DAY)->SetCheck((int)(m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Brt].GetBit(35)));

	M_GETBUTTON(IDC_OPER_BRT_MODE)->SetCheck((int)(m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Brt].GetBit(36)));

	for (k=0; k<256; k++)
	{
		s.Format("%d", k);
		M_GETCOMBO(IDC_COMBO_MNT_OPERBRT)->AddString(s);
	}
	M_GETCOMBO(IDC_COMBO_MNT_OPERBRT)->SetCurSel((int)(m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Brt].GetField(37, 8)));

	// --- Heater -----------------------

	M_GETBUTTON(IDC_CHECK_HEATER)->SetCheck((int)(m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Ctrl].GetBit(1)));
	M_GETBUTTON(IDC_CHECK_HTR_ENABLE)->SetCheck(m_pDev->m_bHtrEnable);


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
	M_GETCOMBO(IDC_COMBO_VIDEO_PATTERN)->AddString("Center Rect");
	M_GETCOMBO(IDC_COMBO_VIDEO_PATTERN)->SetCurSel((int)(m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Pat].GetField(4, 4)));

	RefreshPatColor(0);
	RefreshPatColor(1);



	RefreshPort();
	RefreshData();

	EnableControls(FALSE);

	SetTimer(DHA55_REFRESHTIMER_ID, DHA55_REFRESHTIMER_TIMEOUT, NULL);

	return TRUE;
}


// -----------------------------------------------------------------------------------
//	CEnhMaintDlg::OnOK
// -----------------------------------------------------------------------------------

void CEnhMaintDlg::OnOK()
{
}


// -----------------------------------------------------------------------------------
//	CEnhMaintDlg::OnCancel
// -----------------------------------------------------------------------------------

void CEnhMaintDlg::OnCancel()
{
	KillTimer(STTE_MAINT_TIMER_ID);
	KillTimer(DHA55_REFRESHTIMER_ID);

	m_pDev->DisconnectMaintenance();

	CDialog::OnCancel();
}

// -----------------------------------------------------------------------------------
//	CEnhMaintDlg::OnStnClickedStaticCom2
// -----------------------------------------------------------------------------------

void CEnhMaintDlg::OnStnClickedStaticCom2()
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
//	CEnhMaintDlg::RefreshPort
// -----------------------------------------------------------------------------------

void CEnhMaintDlg::RefreshPort()
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
//	CEnhMaintDlg::OnBnClickedCheckConnect
// -----------------------------------------------------------------------------------

void CEnhMaintDlg::OnBnClickedCheckConnect()
{
	if (M_GETBUTTON(IDC_CHECK_CONNECT)->GetCheck())
	{
		m_bReboot = FALSE;
 
		if (!m_pDev->ConnectMaintenance())
		{
			STTE_Message("Cannot open Maintenance Link.", MB_ICONSTOP, this);
			//SetControlMode(CDhaStteDevice::e_CtrlMode_Idle);
			M_GETBUTTON(IDC_CHECK_CONNECT)->SetCheck(FALSE);

			return;
		}

		//SetControlMode(CDhaStteDevice::e_CtrlMode_Maintenance);

		m_pDev->m_dwMaintLinkAlive = STTE_MAINT_LINK_TIMEOUT;
		m_pDev->m_btMaintLinkStatus = CDhaStteDevice::e_LinkStatus_Timeout;

		EnableControls(TRUE);

		SetTimer(STTE_MAINT_TIMER_ID, STTE_MAINT_TIMER_VAL,NULL);
	}
	else
	{
		EnableControls(FALSE);

		KillTimer(STTE_MAINT_TIMER_ID);
		m_pDev->DisconnectMaintenance();
		
		//SetControlMode(CDhaStteDevice::e_CtrlMode_Idle);

		m_pDev->m_btMaintLinkStatus = CDhaStteDevice::e_LinkStatus_Off;
	}
}


// -----------------------------------------------------------------------------------
//	CEnhMaintDlg::OnTimer
// -----------------------------------------------------------------------------------

void CEnhMaintDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == DHA55_REFRESHTIMER_ID)
	{
		RefreshData();

		if (m_pDev->m_btMaintLinkStatus == CDhaStteDevice::e_LinkStatus_On)
		{
			m_pDev->m_dwMaintLinkAlive++;

			if (m_pDev->m_dwMaintLinkAlive > STTE_MAINT_LINK_TIMEOUT)
			{
				m_pDev->m_btMaintLinkStatus = CDhaStteDevice::e_LinkStatus_Timeout;
				m_pDev->m_dwMaintLinkAlive=0;
			}
		}
	}
	else if (nIDEvent == STTE_MAINT_TIMER_ID)
	{
		if (MaintTimerActions())
		{
			m_pDev->m_btMaintLinkStatus = CDhaStteDevice::e_LinkStatus_On;
			m_pDev->m_dwMaintLinkAlive = 0;
		}

		if (m_bReboot)
		{
			m_bReboot = FALSE;

			EnableControls(FALSE);

			KillTimer(STTE_MAINT_TIMER_ID);
			m_pDev->DisconnectMaintenance();
			
			m_pDev->m_btMaintLinkStatus = CDhaStteDevice::e_LinkStatus_Off;
			M_GETBUTTON(IDC_CHECK_CONNECT)->SetCheck(FALSE);
		}
	}


	CDialog::OnTimer(nIDEvent);
}


// -----------------------------------------------------------------------------------
//	CEnhMaintDlg::MaintTimerActions
// -----------------------------------------------------------------------------------

BOOL CEnhMaintDlg::MaintTimerActions()
{
	CFMT_CommMpp::SCommand		comlist[200];
	DWORD						c;
	BYTE						k;
	WORD						wTemp;
	t_FMT_Uint32				dwTemp;
	t_FMT_Uint64				qwTemp;
	//t_FMT_Uint8					btTemp;
	CString						s;

	c = 0;

	// Create Read Commands --------------------------------------------------

	// MNR_ADCx
	for (k=0; k<14; k++)
	{
		comlist[c].CreateRegisterRead16Command(CMaintMpp::e_MppReg_Adc1 + k);
		c++;
	}

	// MNR_TEMP
	comlist[c].CreateRegisterRead32Command(CMaintMpp::e_MppReg_Temp);
	c++;

	// MNR_STATUS
	comlist[c].CreateRegisterRead64Command(CMaintMpp::e_MppReg_Stat);
	c++;

	// MNR_ETI
	comlist[c].CreateRegisterRead32Command(CMaintMpp::e_MppReg_Eti);
	c++;


	// Create Write Commands ---------------------------------------------------

	if (m_bReboot)
	{
		m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Ctrl].SetBit(7, FMTDEF_TRUE);
	}
	else
	{
		m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Ctrl].SetBit(7, FMTDEF_FALSE);
	}


	// MNR_CTRL
	m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Ctrl].SetBit(0, TRUE);
	comlist[c].CreateRegisterWrite8Command(CMaintMpp::e_MppReg_Ctrl, (t_FMT_Uint8)(m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Ctrl].GetField(0, 8)));
	c++;

	// MNR_BRT
	comlist[c].CreateRegisterWrite64Command(CMaintMpp::e_MppReg_Brt, (m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Brt].GetField(0, 64)));
	c++;

	// MNR_PAT
	m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Pat].SetBit(0, TRUE);
	comlist[c].CreateRegisterWrite64Command(CMaintMpp::e_MppReg_Pat, (m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Pat].GetField(0, 64)));
	c++;

	// Process Commands -------------------------------------------------------------
	
	if ((m_pDev->m_MaintMpp.ProcCommandList(comlist, c, 300)) != e_Return_OK)
	{
		return FALSE;
	}

	if (m_bReboot)
	{
		return TRUE;
	}


	m_bReboot = FALSE;

	// Check all commands return

	if (!CFMT_CommMppClient::CheckAllCommandStatus(comlist, c))
	{
		return FALSE;
	}


	// Get Read Data ----------------------------------------------------

	c = 0;

	// MNR_ADCx
	for (k=0; k<14; k++)
	{
		comlist[c].GetReadRegisterData16(&wTemp);
		m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Adc1+k].SetField(0, 12, wTemp);
		c++;
	}

	// MNR_TEMP
	comlist[c].GetReadRegisterData32(&dwTemp);
	m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Temp].SetField(0, 32, dwTemp);
	c++;

	// MNR_STAT
	comlist[c].GetReadRegisterData64(&qwTemp);
	m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Stat].SetField(0, 64, qwTemp);
	c++;

	// MNR_ETI
	comlist[c].GetReadRegisterData32(&dwTemp);
	m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Eti].SetField(0, 32, dwTemp);
	c++;

	return TRUE;
}


// -----------------------------------------------------------------------------------
//	CEnhMaintDlg::RefreshData
// -----------------------------------------------------------------------------------

void CEnhMaintDlg::RefreshData()
{
	RefreshAnalogs();
	RefreshBIT();
	RefreshETI();
	RefreshHeater();
}

// -----------------------------------------------------------------------------------
//	CEnhMaintDlg::RefreshAnalogs
// -----------------------------------------------------------------------------------

void CEnhMaintDlg::RefreshAnalogs()
{
	DWORD			k;
	CString			s;
	WORD			wTemp;
	double			d;
	int				iTemp;

	if (m_pDev->m_btMaintLinkStatus == CDhaStteDevice::e_LinkStatus_Off)
	{
		for (k=0; k<15; k++)
		{
			m_slAnalogs.SetItemText(k, 1, "---");
			m_slAnalogs.SetItemText(k, 2, "---");

			m_slAnalogs.m_ppFieldColor[1][k] = STTE_COLOR_LIGHTGREY;
			m_slAnalogs.m_ppFieldColor[2][k] = STTE_COLOR_LIGHTGREY;
		}
	}
	else if (m_pDev->m_btMaintLinkStatus == CDhaStteDevice::e_LinkStatus_Timeout)
	{
		for (k=0; k<15; k++)
		{
			m_slAnalogs.SetItemText(k, 1, "---");
			m_slAnalogs.SetItemText(k, 2, "---");

			m_slAnalogs.m_ppFieldColor[1][k] = STTE_COLOR_ORANGE;
			m_slAnalogs.m_ppFieldColor[2][k] = STTE_COLOR_ORANGE;
		}
	}
	else
	{
		// PS 1.0V
		wTemp = (WORD)(m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Adc1 + 0].GetField(0, 12));
		d = 0.00061050061050061 * (double)wTemp;

		s.Format("0x%03X", wTemp);
		m_slAnalogs.SetItemText(0, 1, s);

		s.Format("%.2fV", d);
		m_slAnalogs.SetItemText(0, 2, s);

		m_slAnalogs.m_ppFieldColor[1][0] = STTE_COLOR_GREEN;
		m_slAnalogs.m_ppFieldColor[2][0] = STTE_COLOR_GREEN;


		// PS 1.5V
		wTemp = (WORD)(m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Adc1 + 1].GetField(0, 12));
		d = 0.00061050061050061 * (double)wTemp;

		s.Format("0x%03X", wTemp);
		m_slAnalogs.SetItemText(1, 1, s);

		s.Format("%.2fV", d);
		m_slAnalogs.SetItemText(1, 2, s);

		m_slAnalogs.m_ppFieldColor[1][1] = STTE_COLOR_GREEN;
		m_slAnalogs.m_ppFieldColor[2][1] = STTE_COLOR_GREEN;


		// PS 1.8V
		wTemp = (WORD)(m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Adc1 + 2].GetField(0, 12));
		d = 0.00061050061050061 * (double)wTemp;

		s.Format("0x%03X", wTemp);
		m_slAnalogs.SetItemText(2, 1, s);

		s.Format("%.2fV", d);
		m_slAnalogs.SetItemText(2, 2, s);

		m_slAnalogs.m_ppFieldColor[1][2] = STTE_COLOR_GREEN;
		m_slAnalogs.m_ppFieldColor[2][2] = STTE_COLOR_GREEN;


		// PS 3.3V
		wTemp = (WORD)(m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Adc1 + 3].GetField(0, 12));
		d = 0.00101750101750102 * (double)wTemp;

		s.Format("0x%03X", wTemp);
		m_slAnalogs.SetItemText(3, 1, s);

		s.Format("%.2fV", d);
		m_slAnalogs.SetItemText(3, 2, s);

		m_slAnalogs.m_ppFieldColor[1][3] = STTE_COLOR_GREEN;
		m_slAnalogs.m_ppFieldColor[2][3] = STTE_COLOR_GREEN;


		// PS 5V
		wTemp = (WORD)(m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Adc1 + 4].GetField(0, 12));
		d = 0.00152625152625153 * (double)wTemp;

		s.Format("0x%03X", wTemp);
		m_slAnalogs.SetItemText(4, 1, s);

		s.Format("%.2fV", d);
		m_slAnalogs.SetItemText(4, 2, s);

		m_slAnalogs.m_ppFieldColor[1][4] = STTE_COLOR_GREEN;
		m_slAnalogs.m_ppFieldColor[2][4] = STTE_COLOR_GREEN;


		// LCD 3.3V
		wTemp = (WORD)(m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Adc1 + 5].GetField(0, 12));
		d = 0.00101750101750102 * (double)wTemp;

		s.Format("0x%03X", wTemp);
		m_slAnalogs.SetItemText(5, 1, s);

		s.Format("%.2fV", d);
		m_slAnalogs.SetItemText(5, 2, s);

		m_slAnalogs.m_ppFieldColor[1][5] = STTE_COLOR_GREEN;
		m_slAnalogs.m_ppFieldColor[2][5] = STTE_COLOR_GREEN;


		// FAN Current
		wTemp = (WORD)(m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Adc1 + 6].GetField(0, 12));
		d = max(0.000147607 * (double)wTemp - 0.113636364, 0.0);

		s.Format("0x%03X", wTemp);
		m_slAnalogs.SetItemText(6, 1, s);

		s.Format("%.0fmA", d * 1000.0 + 0,5);
		m_slAnalogs.SetItemText(6, 2, s);

		m_slAnalogs.m_ppFieldColor[1][6] = STTE_COLOR_GREEN;
		m_slAnalogs.m_ppFieldColor[2][6] = STTE_COLOR_GREEN;



		// NTC Day #2
		wTemp = (WORD)(m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Adc1 + 7].GetField(0, 12));

		s.Format("0x%03X", wTemp);
		m_slAnalogs.SetItemText(7, 1, s);

		//iTemp = (int)(m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Temp].GetField(0, 8)) - 55;
		iTemp = (int)(m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Temp].GetField(8, 8)) - 55;
		s.Format("%d°C", iTemp);
		m_slAnalogs.SetItemText(7, 2, s);

		m_slAnalogs.m_ppFieldColor[1][7] = STTE_COLOR_GREEN;
		m_slAnalogs.m_ppFieldColor[2][7] = STTE_COLOR_GREEN;


		// NTC Day #1
		wTemp = (WORD)(m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Adc1 + 8].GetField(0, 12));
		s.Format("0x%03X", wTemp);
		m_slAnalogs.SetItemText(8, 1, s);

		//iTemp = (int)(m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Temp].GetField(8, 8)) - 55;
		iTemp = (int)(m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Temp].GetField(0, 8)) - 55;
		s.Format("%d°C", iTemp);
		m_slAnalogs.SetItemText(8, 2, s);

		m_slAnalogs.m_ppFieldColor[1][8] = STTE_COLOR_GREEN;
		m_slAnalogs.m_ppFieldColor[2][8] = STTE_COLOR_GREEN;


		// AD590
		wTemp = (WORD)(m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Adc1 + 9].GetField(0, 12));

		s.Format("0x%03X", wTemp);
		m_slAnalogs.SetItemText(9, 1, s);

		d = ((double)wTemp) * 0.107066381 - 272.9122056;
		s.Format("%.1f°C", d+0.05);
		m_slAnalogs.SetItemText(9, 2, s);

		m_slAnalogs.m_ppFieldColor[1][9] = STTE_COLOR_GREEN;
		m_slAnalogs.m_ppFieldColor[2][9] = STTE_COLOR_GREEN;


		// Backlight Current NVG HI
		wTemp = (WORD)(m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Adc1 + 10].GetField(0, 12));
		d = (5.08751E-07) * (double)wTemp;

		s.Format("0x%03X", wTemp);
		m_slAnalogs.SetItemText(10, 1, s);

		//s.Format("%.3fmA", d * 1000.0);
		s = "---";
		m_slAnalogs.SetItemText(10, 2, s);

		m_slAnalogs.m_ppFieldColor[1][10] = STTE_COLOR_GREEN;
		m_slAnalogs.m_ppFieldColor[2][10] = STTE_COLOR_GREEN;


		// Backlight Current NVG LO
		wTemp = (WORD)(m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Adc1 + 11].GetField(0, 12));
		d = (8.14001E-06) * (double)wTemp;

		s.Format("0x%03X", wTemp);
		m_slAnalogs.SetItemText(11, 1, s);

		//s.Format("%.1fmA", d * 1000.0);
		s = "---";
		m_slAnalogs.SetItemText(11, 2, s);

		m_slAnalogs.m_ppFieldColor[1][11] = STTE_COLOR_GREEN;
		m_slAnalogs.m_ppFieldColor[2][11] = STTE_COLOR_GREEN;


		// Backlight Current Day HI
		wTemp = (WORD)(m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Adc1 + 12].GetField(0, 12));
		d = (5.08751E-06) * (double)wTemp;

		s.Format("0x%03X", wTemp);
		m_slAnalogs.SetItemText(12, 1, s);

		//s.Format("%.3fmA", d * 1000.0);
		s = "---";
		m_slAnalogs.SetItemText(12, 2, s);

		m_slAnalogs.m_ppFieldColor[1][12] = STTE_COLOR_GREEN;
		m_slAnalogs.m_ppFieldColor[2][12] = STTE_COLOR_GREEN;


		// Backlight Current Day LO
		wTemp = (WORD)(m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Adc1 + 13].GetField(0, 12));
		d = (8.14001E-05) * (double)wTemp;

		s.Format("0x%03X", wTemp);
		m_slAnalogs.SetItemText(13, 1, s);

		//s.Format("%.1fmA", d * 1000.0);
		s = "---";
		m_slAnalogs.SetItemText(13, 2, s);

		m_slAnalogs.m_ppFieldColor[1][13] = STTE_COLOR_GREEN;
		m_slAnalogs.m_ppFieldColor[2][13] = STTE_COLOR_GREEN;


		// Internal Temperature
		wTemp = (WORD)(m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Temp].GetField(16, 8));

		s.Format("0x%02X", wTemp);
		m_slAnalogs.SetItemText(14, 1, s);

		iTemp = (int)(FMT::GetSignedField(wTemp, 0, 8));
		s.Format("%d°C", iTemp);
		m_slAnalogs.SetItemText(14, 2, s);

		m_slAnalogs.m_ppFieldColor[1][14] = STTE_COLOR_GREEN;
		m_slAnalogs.m_ppFieldColor[2][14] = STTE_COLOR_GREEN;
	}
}


// -----------------------------------------------------------------------------------
//	CEnhMaintDlg::RefreshBIT
// -----------------------------------------------------------------------------------

void CEnhMaintDlg::RefreshBIT()
{
	DWORD			k;
	CString			s;

	if (m_pDev->m_btMaintLinkStatus == CDhaStteDevice::e_LinkStatus_Off)
	{
		for (k=0; k<BTL_TOT_ACTIVE_FAULTS; k++)
		{
			m_slBit.SetItemText(k, 1, "---");
			m_slBit.m_ppFieldColor[1][k] = STTE_COLOR_LIGHTGREY;
		}
	}
	else if (m_pDev->m_btMaintLinkStatus == CDhaStteDevice::e_LinkStatus_Timeout)
	{
		for (k=0; k<BTL_TOT_ACTIVE_FAULTS; k++)
		{
			m_slBit.SetItemText(k, 1, "---");
			m_slBit.m_ppFieldColor[1][k] = STTE_COLOR_ORANGE;
		}
	}
	else
	{
		for (k=0; k<BTL_TOT_ACTIVE_FAULTS; k++)
		{
			if (m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Stat].GetBit(k))
			{
				m_slBit.SetItemText(k, 1, "FAIL");
				m_slBit.m_ppFieldColor[1][k] = STTE_COLOR_RED;
			}
			else
			{
				m_slBit.SetItemText(k, 1, "OK");
				m_slBit.m_ppFieldColor[1][k] = STTE_COLOR_GREEN;
			}
		}
	}
}


// -----------------------------------------------------------------------------------
//	CEnhMaintDlg::OnHScroll
// -----------------------------------------------------------------------------------

void CEnhMaintDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CString		s;
	if (pScrollBar == GetDlgItem(IDC_SLIDER_DUTY))
	{
		m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Brt].SetField(0, 16, M_GETSLIDER(IDC_SLIDER_DUTY)->GetPos());
		s.Format("%d", (int)(m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Brt].GetField(0, 16)));
		M_GETEDIT(IDC_EDIT_DUTY)->SetWindowText(s);
	}
	else if (pScrollBar == GetDlgItem(IDC_SLIDER_CURRENT))
	{
		m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Brt].SetField(16, 12, M_GETSLIDER(IDC_SLIDER_CURRENT)->GetPos());
		s.Format("%d", (int)(m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Brt].GetField(16, 12)));
		M_GETEDIT(IDC_EDIT_CURRENT)->SetWindowText(s);
	}

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}


// -----------------------------------------------------------------------------------
//	CEnhMaintDlg::OnCbnSelendokComboPot
// -----------------------------------------------------------------------------------

void CEnhMaintDlg::OnCbnSelendokComboPot()
{
	m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Brt].SetField(28, 7, M_GETCOMBO(IDC_COMBO_POT)->GetCurSel());
}


// -----------------------------------------------------------------------------------
//	CEnhMaintDlg::OnBnClickedCheckDay
// -----------------------------------------------------------------------------------

void CEnhMaintDlg::OnBnClickedCheckDay()
{
	m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Brt].SetBit(35, M_GETBUTTON(IDC_CHECK_DAY)->GetCheck());
}


// -----------------------------------------------------------------------------------
//	CEnhMaintDlg::OnBnClickedOperBrtMode
// -----------------------------------------------------------------------------------

void CEnhMaintDlg::OnBnClickedOperBrtMode()
{
	m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Brt].SetBit(36, M_GETBUTTON(IDC_OPER_BRT_MODE)->GetCheck());
}


// -----------------------------------------------------------------------------------
//	CEnhMaintDlg::OnCbnSelendokComboMntOpBrt
// -----------------------------------------------------------------------------------

void CEnhMaintDlg::OnCbnSelendokComboMntOpBrt()
{
	m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Brt].SetField(37, 8, M_GETCOMBO(IDC_COMBO_MNT_OPERBRT)->GetCurSel());
}


// -----------------------------------------------------------------------------------
//	CEnhMaintDlg::OnEnChangeEditDuty
// -----------------------------------------------------------------------------------

void CEnhMaintDlg::OnEnChangeEditDuty()
{
	CString			s;
	int				iTemp;

	M_GETEDIT(IDC_EDIT_DUTY)->GetWindowText(s);

	iTemp = atoi(s);

	iTemp = max(iTemp, 0);
	iTemp = min(iTemp, 65535);

	m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Brt].SetField(0, 16, iTemp);
	M_GETSLIDER(IDC_SLIDER_DUTY)->SetPos(iTemp);
}


// -----------------------------------------------------------------------------------
//	CEnhMaintDlg::OnEnChangeEditCurrent
// -----------------------------------------------------------------------------------

void CEnhMaintDlg::OnEnChangeEditCurrent()
{
	CString			s;
	int				iTemp;

	M_GETEDIT(IDC_EDIT_CURRENT)->GetWindowText(s);

	iTemp = atoi(s);

	iTemp = max(iTemp, 0);
	iTemp = min(iTemp, 4095);

	m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Brt].SetField(16, 12, iTemp);
	M_GETSLIDER(IDC_SLIDER_CURRENT)->SetPos(iTemp);
}


// -----------------------------------------------------------------------------------
//	CEnhMaintDlg::RefreshETI
// -----------------------------------------------------------------------------------

void CEnhMaintDlg::RefreshETI()
{
	CString			s;

	if (m_pDev->m_btMaintLinkStatus == CDhaStteDevice::e_LinkStatus_Off)
	{
		m_ssEti.SetWindowText("---");
		m_ssEti.SetBkColor(STTE_COLOR_LIGHTGREY);
	}
	else if (m_pDev->m_btMaintLinkStatus == CDhaStteDevice::e_LinkStatus_Timeout)
	{
		m_ssEti.SetWindowText("---");
		m_ssEti.SetBkColor(STTE_COLOR_ORANGE);
	}
	else
	{
		s= ::GetEtiString((DWORD)(m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Eti].GetField(0, 32)));
		m_ssEti.SetWindowText(s);
		m_ssEti.SetBkColor(STTE_COLOR_GREEN);
	}
}


// -----------------------------------------------------------------------------------
//	CEnhMaintDlg::OnBnClickedCheckHeater
// -----------------------------------------------------------------------------------

void CEnhMaintDlg::OnBnClickedCheckHeater()
{
	m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Ctrl].SetBit(1, M_GETBUTTON(IDC_CHECK_HEATER)->GetCheck());
}


// -----------------------------------------------------------------------------------
//	CEnhMaintDlg::RefreshHeater
// -----------------------------------------------------------------------------------

void CEnhMaintDlg::RefreshHeater()
{
	CString			s;

	if (m_pDev->m_btMaintLinkStatus == CDhaStteDevice::e_LinkStatus_Off)
	{
		m_ssHtrStatus.SetWindowText("---");
		m_ssHtrStatus.SetBkColor(STTE_COLOR_LIGHTGREY);
	}
	else if (m_pDev->m_btMaintLinkStatus == CDhaStteDevice::e_LinkStatus_Timeout)
	{
		m_ssHtrStatus.SetWindowText("---");
		m_ssEti.SetBkColor(STTE_COLOR_ORANGE);
	}
	else
	{
		if (m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Stat].GetBit(56))
		{
			m_ssHtrStatus.SetWindowText("ON");
			m_ssHtrStatus.SetBkColor(STTE_COLOR_GREEN);
		}
		else
		{
			m_ssHtrStatus.SetWindowText("OFF");
			m_ssHtrStatus.SetBkColor(STTE_COLOR_GREY);
		}
	}
}


// -----------------------------------------------------------------------------------
//	CEnhMaintDlg::OnBnClickedCheckHtrEnable
// -----------------------------------------------------------------------------------

void CEnhMaintDlg::OnBnClickedCheckHtrEnable()
{
	m_pDev->m_bHtrEnable = (BOOL)(M_GETBUTTON(IDC_CHECK_HTR_ENABLE)->GetCheck());
}



// -----------------------------------------------------------------------------------
//	CEnhMaintDlg::RefreshPatColor
// -----------------------------------------------------------------------------------

void CEnhMaintDlg::RefreshPatColor(BYTE btIdx)
{
	CString		s;
	CFMT_Color	col;

	col.SetR((BYTE)(m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Pat].GetField(24*btIdx + 8, 8)));
	col.SetG((BYTE)(m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Pat].GetField(24*btIdx + 16, 8)));
	col.SetB((BYTE)(m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Pat].GetField(24*btIdx + 24, 8)));

	m_pssPatCol[btIdx].SetBkColor(col);

	s.Format("%d,%d,%d", col.GetR(), col.GetG(), col.GetB());
	m_pssPatRgb[btIdx].SetBkColor(STTE_COLOR_YELLOW);
	m_pssPatRgb[btIdx].SetWindowText(s);
}


// -----------------------------------------------------------------------------------
//	CEnhMaintDlg::OnStnClickedStaticPatCol1
// -----------------------------------------------------------------------------------

void CEnhMaintDlg::OnStnClickedStaticPatCol1()
{
	CFMT_Color	col;

	col.SetR((BYTE)(m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Pat].GetField(8, 8)));
	col.SetG((BYTE)(m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Pat].GetField(16, 8)));
	col.SetB((BYTE)(m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Pat].GetField(24, 8)));

	CColorDialog	d(col);

	if (d.DoModal() == IDOK)
	{
		col = d.GetColor();

		m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Pat].SetField(8, 8, col.GetR());
		m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Pat].SetField(16, 8, col.GetG());
		m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Pat].SetField(24, 8, col.GetB());

		RefreshPatColor(0);
	}
}


// -----------------------------------------------------------------------------------
//	CEnhMaintDlg::OnStnClickedStaticPatCol2
// -----------------------------------------------------------------------------------

void CEnhMaintDlg::OnStnClickedStaticPatCol2()
{
	CFMT_Color	col;

	col.SetR((BYTE)(m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Pat].GetField(32, 8)));
	col.SetG((BYTE)(m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Pat].GetField(40, 8)));
	col.SetB((BYTE)(m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Pat].GetField(48, 8)));

	CColorDialog	d(col);

	if (d.DoModal() == IDOK)
	{
		col = d.GetColor();

		m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Pat].SetField(32, 8, col.GetR());
		m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Pat].SetField(40, 8, col.GetG());
		m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Pat].SetField(48, 8, col.GetB());

		RefreshPatColor(1);
	}
}


// -----------------------------------------------------------------------------------
//	CEnhMaintDlg::OnStnClickedStaticPatRgb1
// -----------------------------------------------------------------------------------

void CEnhMaintDlg::OnStnClickedStaticPatRgb1()
{
	OnStnClickedStaticPatCol1();
}


// -----------------------------------------------------------------------------------
//	CEnhMaintDlg::OnStnClickedStaticPatRgb2
// -----------------------------------------------------------------------------------

void CEnhMaintDlg::OnStnClickedStaticPatRgb2()
{
	OnStnClickedStaticPatCol2();
}


// -----------------------------------------------------------------------------------
//	CEnhMaintDlg::OnCbnSelendokComboVideoPattern
// -----------------------------------------------------------------------------------

void CEnhMaintDlg::OnCbnSelendokComboVideoPattern()
{
	m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Pat].SetField(4, 4, M_GETCOMBO(IDC_COMBO_VIDEO_PATTERN)->GetCurSel() & 0xF);
}


// -----------------------------------------------------------------------------------
//	CEnhMaintDlg::EnableControls
// -----------------------------------------------------------------------------------

void CEnhMaintDlg::EnableControls(BOOL bEnable)
{
	if (bEnable)
	{
		M_GETBUTTON(IDC_BUT_CALIB_BRT_FEEDBACK)->ModifyStyle(WS_DISABLED, 0);
		M_GETBUTTON(IDC_BUT_REBOOT)->ModifyStyle(WS_DISABLED, 0);
	}
	else
	{
		M_GETBUTTON(IDC_BUT_CALIB_BRT_FEEDBACK)->ModifyStyle(0, WS_DISABLED);
		M_GETBUTTON(IDC_BUT_REBOOT)->ModifyStyle(0, WS_DISABLED);
	}

	M_GETBUTTON(IDC_BUT_CALIB_BRT_FEEDBACK)->Invalidate();
	M_GETBUTTON(IDC_BUT_REBOOT)->Invalidate();
}


// -----------------------------------------------------------------------------------
//	CEnhMaintDlg::OnBnClickedButReboot
// -----------------------------------------------------------------------------------

void CEnhMaintDlg::OnBnClickedButReboot()
{
	m_bReboot = TRUE;
}


// -----------------------------------------------------------------------------------
//	CEnhMaintDlg::OnBnClickedButCalibBrtFeedback
// -----------------------------------------------------------------------------------

void CEnhMaintDlg::OnBnClickedButCalibBrtFeedback()
{
	CBrtFbkCalibDlg		dlg;

	KillTimer(STTE_MAINT_TIMER_ID);


	// --- Select Configuration file ----------------------------------------------------------------------
	
	CString			sPath;

	CFileDialog *pDlg = new CFileDialog(FALSE, "bin", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST,
		"Binary File (*.bin) | *.bin|",this);

	pDlg->m_ofn.lpstrTitle = "Select Configuration File to update";
	
	if (pDlg->DoModal() == IDOK)
	{
		sPath = pDlg->GetPathName();

		delete pDlg;
	}
	else
	{
		delete pDlg;
		return;
	}



	dlg.m_pDev = m_pDev;
	dlg.m_sCnfPath = sPath;

	dlg.DoModal();

	SetTimer(STTE_MAINT_TIMER_ID, STTE_MAINT_TIMER_VAL,NULL);
}


