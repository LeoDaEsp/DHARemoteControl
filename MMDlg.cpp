// MMDlg.cpp : implementation file
//

#include "stdafx.h"
#include "dha5x5_STTE.h"
#include "MMDlg.h"


// CMMDlg dialog

IMPLEMENT_DYNAMIC(CMMDlg, CDialog)

CMMDlg::CMMDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMMDlg::IDD, pParent)
{
	m_btCurDlg=0;
	m_pThread=NULL;
	m_dwThreadReturn=0;
	m_brStatusReady.CreateSolidBrush(RGB(220,255,220));
	m_brStatusProgramming.CreateSolidBrush(RGB(253,248,215));
	m_brStatusError.CreateSolidBrush(RGB(255,220,220));
	m_brRO.CreateSolidBrush(RGB(253,248,215));

	DWORD	k;
	DWORD	w;

	for (k=0;k<e_Total_Dlg;k++)
	{
		if ((k==e_VDCNight1_Dlg) || (k==e_VDCNight2_Dlg) || (k==e_VDCNight3_Dlg) || (k==e_VDCNight4_Dlg))
		{
			m_Curves[k].Create(256);

			for (w=0;w<256;w++)
			{
				m_Curves[k][w].SetX((double)w);
				m_Curves[k][w].SetY(4095.0*((double)w)/255.0);
			}
		}
		else if ((k==e_VDCDay1_Dlg) || (k==e_VDCDay2_Dlg) || (k==e_VDCDay3_Dlg) || (k==e_VDCDay4_Dlg))
		{
			m_Curves[k].Create(256);

			for (w=0;w<256;w++)
			{
				m_Curves[k][w].SetX((double)w);
				m_Curves[k][w].SetY(4095.0*((double)w)/255.0);
			}
		}
		else if ((k==e_PWMNight1_Dlg) || (k==e_PWMNight2_Dlg) || (k==e_PWMNight3_Dlg) || (k==e_PWMNight4_Dlg))
		{
			m_Curves[k].Create(256);

			for (w=0;w<256;w++)
			{
				m_Curves[k][w].SetX((double)w);
				m_Curves[k][w].SetY(4095.0*((double)w)/255.0);
			}
		}
		else if ((k==e_PWMDay1_Dlg) || (k==e_PWMDay2_Dlg) || (k==e_PWMDay3_Dlg) || (k==e_PWMDay4_Dlg))
		{
			m_Curves[k].Create(256);

			for (w=0;w<256;w++)
			{
				m_Curves[k][w].SetX((double)w);
				m_Curves[k][w].SetY(4095.0*((double)w)/255.0);
			}
		}
		else if (k==e_BackTemp_Dlg)
		{
			m_Curves[k].Create(256);

			for (w=0;w<256;w++)
			{
				m_Curves[k][w].SetX((double)w-55.0);
				m_Curves[k][w].SetY(((double)w)-55.0);
			}
		}
		else
		{
			m_Curves[k].Create(4096);

			for (w=0;w<4096;w++)
			{
				m_Curves[k][w].SetX((double)w);
				m_Curves[k][w].SetY(255.0*((double)w)/4095.0);
			}
		}
	}

	m_pBrtDlg=new CBrtDlg(this);
}

CMMDlg::~CMMDlg()
{
}

void CMMDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMMDlg, CDialog)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_GRAPH, &CMMDlg::OnTcnSelchangeTabGraph)
	ON_BN_CLICKED(IDC_BUT_PROG, &CMMDlg::OnBnClickedButProg)
	ON_BN_CLICKED(IDC_BUT_VERIFY, &CMMDlg::OnBnClickedButVerify)
	ON_BN_CLICKED(IDC_BUT_POLL, &CMMDlg::OnBnClickedButPoll)
	ON_MESSAGE(MEMORYPROGDLG_ERRORMESS,OnMessageError)
	ON_MESSAGE(MEMORYPROGDLG_ENDMESS,OnMessageEnd)
	ON_MESSAGE(MEMORYPROGDLG_PROGMESS,OnMessageChange)
	ON_WM_CTLCOLOR()
	ON_COMMAND(ID_MENUFILE_OPEN, &CMMDlg::OnMenufileOpen)
	ON_COMMAND(ID_MENUFILE_SAVE, &CMMDlg::OnMenufileSave)
	ON_COMMAND(ID_FILE_IMPORTFULL, &CMMDlg::OnFileImportfull)
	ON_BN_CLICKED(IDC_BUT_READ, &CMMDlg::OnBnClickedButRead)
	ON_CBN_SELENDOK(IDC_COMBO_SPEED, &CMMDlg::OnCbnSelendokComboSpeed)
END_MESSAGE_MAP()


// CMMDlg message handlers

BOOL CMMDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Tab Control Init ---------------------------------------------------
	TCITEM	tc;

	tc.mask = TCIF_TEXT;

	tc.pszText="VDC #1 Day";
	tc.cchTextMax = strlen(tc.pszText); 
	((CTabCtrl*)GetDlgItem(IDC_TAB_GRAPH))->InsertItem(e_VDCDay1_Dlg,&tc);

	tc.pszText="VDC #1 Night";
	tc.cchTextMax = strlen(tc.pszText); 
	((CTabCtrl*)GetDlgItem(IDC_TAB_GRAPH))->InsertItem(e_VDCNight1_Dlg,&tc);

	tc.pszText="VDC #2 Day";
	tc.cchTextMax = strlen(tc.pszText); 
	((CTabCtrl*)GetDlgItem(IDC_TAB_GRAPH))->InsertItem(e_VDCDay2_Dlg,&tc);

	tc.pszText="VDC #2 Night";
	tc.cchTextMax = strlen(tc.pszText); 
	((CTabCtrl*)GetDlgItem(IDC_TAB_GRAPH))->InsertItem(e_VDCNight2_Dlg,&tc);

	tc.pszText="VDC #3 Day";
	tc.cchTextMax = strlen(tc.pszText); 
	((CTabCtrl*)GetDlgItem(IDC_TAB_GRAPH))->InsertItem(e_VDCDay3_Dlg,&tc);

	tc.pszText="VDC #3 Night";
	tc.cchTextMax = strlen(tc.pszText); 
	((CTabCtrl*)GetDlgItem(IDC_TAB_GRAPH))->InsertItem(e_VDCNight3_Dlg,&tc);

	tc.pszText="VDC #4 Day";
	tc.cchTextMax = strlen(tc.pszText); 
	((CTabCtrl*)GetDlgItem(IDC_TAB_GRAPH))->InsertItem(e_VDCDay4_Dlg,&tc);

	tc.pszText="VDC #4 Night";
	tc.cchTextMax = strlen(tc.pszText); 
	((CTabCtrl*)GetDlgItem(IDC_TAB_GRAPH))->InsertItem(e_VDCNight4_Dlg,&tc);

	tc.pszText="PWM #1 Day";
	tc.cchTextMax = strlen(tc.pszText); 
	((CTabCtrl*)GetDlgItem(IDC_TAB_GRAPH))->InsertItem(e_PWMDay1_Dlg,&tc);

	tc.pszText="PWM #1 Night";
	tc.cchTextMax = strlen(tc.pszText); 
	((CTabCtrl*)GetDlgItem(IDC_TAB_GRAPH))->InsertItem(e_PWMNight1_Dlg,&tc);

	tc.pszText="PWM #2 Day";
	tc.cchTextMax = strlen(tc.pszText); 
	((CTabCtrl*)GetDlgItem(IDC_TAB_GRAPH))->InsertItem(e_PWMDay2_Dlg,&tc);

	tc.pszText="PWM #2 Night";
	tc.cchTextMax = strlen(tc.pszText); 
	((CTabCtrl*)GetDlgItem(IDC_TAB_GRAPH))->InsertItem(e_PWMNight2_Dlg,&tc);

	tc.pszText="PWM #3 Day";
	tc.cchTextMax = strlen(tc.pszText); 
	((CTabCtrl*)GetDlgItem(IDC_TAB_GRAPH))->InsertItem(e_PWMDay3_Dlg,&tc);

	tc.pszText="PWM #3 Night";
	tc.cchTextMax = strlen(tc.pszText); 
	((CTabCtrl*)GetDlgItem(IDC_TAB_GRAPH))->InsertItem(e_PWMNight3_Dlg,&tc);

	tc.pszText="PWM #4 Day";
	tc.cchTextMax = strlen(tc.pszText); 
	((CTabCtrl*)GetDlgItem(IDC_TAB_GRAPH))->InsertItem(e_PWMDay4_Dlg,&tc);

	tc.pszText="PWM #4 Night";
	tc.cchTextMax = strlen(tc.pszText); 
	((CTabCtrl*)GetDlgItem(IDC_TAB_GRAPH))->InsertItem(e_PWMNight4_Dlg,&tc);

	tc.pszText="Backlight Temp";
	tc.cchTextMax = strlen(tc.pszText); 
	((CTabCtrl*)GetDlgItem(IDC_TAB_GRAPH))->InsertItem(e_BackTemp_Dlg,&tc);

	tc.pszText="NVG White Feedback";
	tc.cchTextMax = strlen(tc.pszText); 
	((CTabCtrl*)GetDlgItem(IDC_TAB_GRAPH))->InsertItem(e_PhotoLow_Dlg,&tc);

	tc.pszText="Day White Feedback";
	tc.cchTextMax = strlen(tc.pszText); 
	((CTabCtrl*)GetDlgItem(IDC_TAB_GRAPH))->InsertItem(e_PhotoHigh_Dlg,&tc);

	// Create Brightness Dialog
	m_pBrtDlg->Create(IDD_BRT_DLG,this);

	// Set current dialog
	M_GETTAB(IDC_TAB_GRAPH)->SetCurSel(e_VDCDay1_Dlg);
	SetCurrentDlg(e_VDCDay1_Dlg);

	M_GETPROGRESS(IDC_PROG_STATUS)->SetRange(0,10000);
	M_GETPROGRESS(IDC_PROG_STATUS)->SetPos(0);

	M_GETEDIT(IDC_EDIT_CURROFFFAN)->SetLimitText(4);
	M_GETEDIT(IDC_EDIT_CURRONFAN_LO)->SetLimitText(4);
	M_GETEDIT(IDC_EDIT_CURRONFAN_HI)->SetLimitText(4);

	M_GETCOMBO(IDC_COMBO_SPEED)->AddString("25 MHz");
	M_GETCOMBO(IDC_COMBO_SPEED)->AddString("10 MHz");
	M_GETCOMBO(IDC_COMBO_SPEED)->AddString("5 MHz");
	M_GETCOMBO(IDC_COMBO_SPEED)->AddString("2.5 MHz");
	M_GETCOMBO(IDC_COMBO_SPEED)->AddString("1 MHz");
	M_GETCOMBO(IDC_COMBO_SPEED)->AddString("500 kHz");
	M_GETCOMBO(IDC_COMBO_SPEED)->AddString("250 kHz");
	M_GETCOMBO(IDC_COMBO_SPEED)->AddString("100 kHz");

	M_GETCOMBO(IDC_COMBO_SPEED)->SetCurSel(m_pDev->m_ucSpiSpeed);
	

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}



void CMMDlg::OnOK()
{
}

void CMMDlg::OnCancel()
{
	m_pBrtDlg->DestroyWindow();
	delete m_pBrtDlg;

	CDialog::OnCancel();
}

// -----------------------------------------------------------------------------------
//	SetCurrentDlg
// -----------------------------------------------------------------------------------

void CMMDlg::SetCurrentDlg(BYTE btCurDlg)
{
	m_pBrtDlg->ModifyStyle(0,WS_VISIBLE);
	m_pBrtDlg->m_btID=btCurDlg;

	m_btCurDlg=btCurDlg;
	m_pBrtDlg->m_Data=m_Curves[m_btCurDlg];

	switch (m_btCurDlg)
	{
	case e_VDCDay1_Dlg:
	case e_VDCNight1_Dlg:
	case e_VDCDay2_Dlg:
	case e_VDCNight2_Dlg:
	case e_VDCDay3_Dlg:
	case e_VDCNight3_Dlg:
	case e_VDCDay4_Dlg:
	case e_VDCNight4_Dlg:
		m_pBrtDlg->SetType(CBrtDlg::e_VDC);
	break;

	case e_PWMDay1_Dlg:
	case e_PWMNight1_Dlg:
	case e_PWMDay2_Dlg:
	case e_PWMNight2_Dlg:
	case e_PWMDay3_Dlg:
	case e_PWMNight3_Dlg:
	case e_PWMDay4_Dlg:
	case e_PWMNight4_Dlg:
		m_pBrtDlg->SetType(CBrtDlg::e_PWM);
	break;

	case e_PhotoLow_Dlg:
	case e_PhotoHigh_Dlg:
		m_pBrtDlg->SetType(CBrtDlg::e_Photo);
	break;

	case e_BackTemp_Dlg:
		m_pBrtDlg->SetType(CBrtDlg::e_Temp);
	break;
	}

	RedrawWindow();
}

void CMMDlg::OnTcnSelchangeTabGraph(NMHDR *pNMHDR, LRESULT *pResult)
{
	m_Curves[m_btCurDlg]=m_pBrtDlg->m_Data;

	int idx=M_GETTAB(IDC_TAB_GRAPH)->GetCurSel();

	SetCurrentDlg(idx);
	
	*pResult = 0;
}

// -----------------------------------------------------------------------------------
//	SetWord
// -----------------------------------------------------------------------------------

void CMMDlg::SetWord(DWORD dwAdd,WORD wValue)
{
	BOOL	bPar;
	BYTE	k;
	BYTE	w;
	BYTE	j;

	m_pbtMemory[dwAdd]=(BYTE)(wValue & 0xFF);
	m_pbtMemory[dwAdd+1]=(BYTE)((wValue>>8) & 0x0F);

	j=0;
	for (k=0;k<4;k++)
	{
		bPar=TRUE;
		for (w=0;w<3;w++)
		{
			if ((wValue & (1<<j))>0)
			{
				bPar=!bPar;
			}
			j++;
		}

		if (bPar)
		{
			m_pbtMemory[dwAdd+1]|=(1<<(4+k));
		}
	}

}

// -----------------------------------------------------------------------------------
//	GenerateCurrentFANThresh
// -----------------------------------------------------------------------------------

BOOL CMMDlg::GenerateCurrentFANThresh()
{
	CString		s;
	WORD		wTemp;

	M_GETEDIT(IDC_EDIT_CURROFFFAN)->GetWindowText(s);
	wTemp=atoi(s);
	wTemp&=0xFFF;

	SetWord(DHA5X5_CURR_OFF_FAN,wTemp);

	M_GETEDIT(IDC_EDIT_CURRONFAN_LO)->GetWindowText(s);
	wTemp=atoi(s);
	wTemp&=0xFFF;

	SetWord(DHA5X5_CURR_ON_FAN_LO,wTemp);

	M_GETEDIT(IDC_EDIT_CURRONFAN_HI)->GetWindowText(s);
	wTemp=atoi(s);
	wTemp&=0xFFF;

	SetWord(DHA5X5_CURR_ON_FAN_HI,wTemp);

	return TRUE;
}

// -----------------------------------------------------------------------------------
//	GeneratePWMData
// -----------------------------------------------------------------------------------

BOOL CMMDlg::GeneratePWMData(DWORD dwID)
{
	WORD				wTemp;
	DWORD				dwAdd;
	DWORD				k;
	DWORD				w;
	CFMT_Point<double>	pw1;
	CFMT_Point<double>	pw2;
	double				m,q,res;
	DWORD				dwCurve;

	// Generate DAY curve data -------------------------------------------------------
	dwCurve=e_PWMDay1_Dlg+2*dwID;
	dwAdd=DHA5X5_PWM_00_CURVE+(2*dwID)*DHA5X5_BRTCURVE_SIZE;

	pw1=m_Curves[dwCurve][0];
	//pw1.m_PX=pw1.m_PX;
	w=0;
	for (k=1;k<!(m_Curves[dwCurve]);k++)
	{	
		pw2=m_Curves[dwCurve][k];
		//pw2.m_PX=pw2.m_PX;

		if (pw2.GetX()==pw1.GetX())
		{
			SetWord(dwAdd+2*w,(WORD)(pw2.GetY()));
		}
		else
		{

			m=((double)(pw2.GetY())-(double)(pw1.GetY()))/((double)(pw2.GetX())-(double)(pw1.GetX()));
			q=(double)(pw2.GetY())-m*(double)(pw2.GetX());

			for (w=(WORD)(pw1.GetX());w<=(WORD)(pw2.GetX());w++)
			{
				res=((m*w+q));

				if (res<0)
				{
					wTemp=0;
				}
				else if (res>4095.0)
				{
					wTemp=4095;
				}
				else
				{
					wTemp=(WORD)(res+0.5);
				}

				SetWord(dwAdd+2*w,wTemp);
			}
		}

		pw1=pw2;
	}

	// Generate NIGHT curve data -------------------------------------------------------
	dwCurve=e_PWMNight1_Dlg+2*dwID;
	dwAdd=DHA5X5_PWM_00_CURVE+(2*dwID+1)*DHA5X5_BRTCURVE_SIZE;

	pw1=m_Curves[dwCurve][0];
	//pw1.m_PX=pw1.m_PX;
	w=0;
	for (k=1;k<!(m_Curves[dwCurve]);k++)
	{	
		pw2=m_Curves[dwCurve][k];
		//pw2.m_PX=pw2.m_PX;

		if (pw2.GetX()==pw1.GetX())
		{
			SetWord(dwAdd+2*w,(WORD)(pw2.GetY()));
		}
		else
		{

			m=((double)(pw2.GetY())-(double)(pw1.GetY()))/((double)(pw2.GetX())-(double)(pw1.GetX()));
			q=(double)(pw2.GetY())-m*(double)(pw2.GetX());

			for (w=(WORD)(pw1.GetX());w<=(WORD)(pw2.GetX());w++)
			{
				res=((m*w+q));

				if (res<0)
				{
					wTemp=0;
				}
				else if (res>4095.0)
				{
					wTemp=4095;
				}
				else
				{
					wTemp=(WORD)(res+0.5);
				}

				SetWord(dwAdd+2*w,wTemp);
			}
		}

		pw1=pw2;
	}

	return TRUE;
}

// -----------------------------------------------------------------------------------
//	GenerateVDCData
// -----------------------------------------------------------------------------------

BOOL CMMDlg::GenerateVDCData(DWORD dwID)
{
	WORD				wTemp;
	DWORD				dwAdd;
	DWORD				k;
	DWORD				w;
	CFMT_Point<double>	pw1;
	CFMT_Point<double>	pw2;
	double				m,q,res;
	DWORD				dwCurve;

	// Generate DAY curve data -------------------------------------------------------
	dwCurve=e_VDCDay1_Dlg+2*dwID;
	dwAdd=DHA5X5_VDC_00_CURVE+(2*dwID)*DHA5X5_BRTCURVE_SIZE;

	pw1=m_Curves[dwCurve][0];
	//pw1.m_PX=pw1.m_PX;
	w=0;
	for (k=1;k<!(m_Curves[dwCurve]);k++)
	{	
		pw2=m_Curves[dwCurve][k];
		//pw2.m_PX=pw2.m_PX;

		if (pw2.GetX() == pw1.GetX())
		{
			SetWord(dwAdd+2*w, (WORD)(pw2.GetY()));
		}
		else
		{

			m=((double)(pw2.GetY())-(double)(pw1.GetY()))/((double)(pw2.GetX())-(double)(pw1.GetX()));
			q=(double)(pw2.GetY())-m*(double)(pw2.GetX());

			for (w=(WORD)(pw1.GetX());w<=(WORD)(pw2.GetX());w++)
			{
				res=((m*w+q));

				if (res<0)
				{
					wTemp=0;
				}
				else if (res>4095.0)
				{
					wTemp=4095;
				}
				else
				{
					wTemp=(WORD)(res+0.5);
				}

				SetWord(dwAdd+2*w,wTemp);
			}
		}

		pw1=pw2;
	}

	// Generate NIGHT curve data -------------------------------------------------------
	dwCurve=e_VDCNight1_Dlg+2*dwID;
	dwAdd=DHA5X5_VDC_00_CURVE+(2*dwID+1)*DHA5X5_BRTCURVE_SIZE;

	pw1=m_Curves[dwCurve][0];
	//pw1.m_PX=pw1.m_PX;
	w=0;
	for (k=1;k<!(m_Curves[dwCurve]);k++)
	{	
		pw2=m_Curves[dwCurve][k];
		//pw2.m_PX=pw2.m_PX;

		if (pw2.GetX()==pw1.GetX())
		{
			SetWord(dwAdd+2*w,(WORD)(pw2.GetY()));
		}
		else
		{

			m=((double)(pw2.GetY())-(double)(pw1.GetY()))/((double)(pw2.GetX())-(double)(pw1.GetX()));
			q=(double)(pw2.GetY())-m*(double)(pw2.GetX());

			for (w=(WORD)(pw1.GetX());w<=(WORD)(pw2.GetX());w++)
			{
				res=((m*w+q));

				if (res<0)
				{
					wTemp=0;
				}
				else if (res>4095.0)
				{
					wTemp=4095;
				}
				else
				{
					wTemp=(WORD)(res+0.5);
				}

				SetWord(dwAdd+2*w,wTemp);
			}
		}

		pw1=pw2;
	}

	return TRUE;
}

// -----------------------------------------------------------------------------------
//	GenerateHeaterTempTrimData
// -----------------------------------------------------------------------------------

/*BOOL CMMDlg::GenerateHeaterTempTrimData()
{
	WORD				wTemp;
	DWORD				dwAdd;
	DWORD				k;
	DWORD				w;
	CFMT_Point<double>	pw1;
	CFMT_Point<double>	pw2;
	double				m,q,res;
	DWORD				dwCurve;

	dwCurve=e_HeaterTemp_Dlg;
	dwAdd=DHA5X5_TRIM_00_CURVE;

	pw1=m_Curves[dwCurve][0];
	pw1.m_PX=pw1.m_PX;
	w=0;
	for (k=1;k<!(m_Curves[dwCurve]);k++)
	{	
		pw2=m_Curves[dwCurve][k];
		pw2.m_PX=pw2.m_PX;

		if (pw2.m_PX==pw1.m_PX)
		{
			SetWord(dwAdd+2*w,(WORD)(pw2.m_PY));
		}
		else
		{

			m=((double)(pw2.m_PY)-(double)(pw1.m_PY))/((double)(pw2.m_PX)-(double)(pw1.m_PX));
			q=(double)(pw2.m_PY)-m*(double)(pw2.m_PX);

			for (w=(WORD)(pw1.m_PX);w<=(WORD)(pw2.m_PX);w++)
			{
				res=(((m*w+q)+55.0)*4095.0/255.0);

				if (res<0)
				{
					wTemp=0;
				}
				else if (res>4095.0)
				{
					wTemp=4095;
				}
				else
				{
					wTemp=(WORD)(res+0.5);
				}

				SetWord(dwAdd+2*w,wTemp);
			}
		}

		pw1=pw2;
	}

	return TRUE;
}*/

// -----------------------------------------------------------------------------------
//	GeneratePhotoLoTrimData
// -----------------------------------------------------------------------------------

BOOL CMMDlg::GeneratePhotoLoTrimData()
{
	WORD				wTemp;
	DWORD				dwAdd;
	DWORD				k;
	DWORD				w;
	CFMT_Point<double>	pw1;
	CFMT_Point<double>	pw2;
	double				m,q,res;
	DWORD				dwCurve;

	dwCurve=e_PhotoLow_Dlg;
	dwAdd=DHA5X5_TRIM_00_CURVE+0x2000;

	pw1=m_Curves[dwCurve][0];
	//pw1.m_PX=pw1.m_PX;
	w=0;
	for (k=1;k<!(m_Curves[dwCurve]);k++)
	{	
		pw2=m_Curves[dwCurve][k];
		//pw2.m_PX=pw2.m_PX;

		if (pw2.GetX()==pw1.GetX())
		{
			SetWord(dwAdd+2*w,(WORD)(pw2.GetY()));
		}
		else
		{

			m=((double)(pw2.GetY())-(double)(pw1.GetY()))/((double)(pw2.GetX())-(double)(pw1.GetX()));
			q=(double)(pw2.GetY())-m*(double)(pw2.GetX());

			for (w=(WORD)(pw1.GetX());w<=(WORD)(pw2.GetX());w++)
			{
				res=(m*w+q);

				if (res<0)
				{
					wTemp=0;
				}
				else if (res>255.0)
				{
					wTemp=255;
				}
				else
				{
					wTemp=(WORD)(res+0.5);
				}

				SetWord(dwAdd+2*w,wTemp);
			}
		}

		pw1=pw2;
	}

	return TRUE;
}

// -----------------------------------------------------------------------------------
//	GeneratePhotoHiTrimData
// -----------------------------------------------------------------------------------

BOOL CMMDlg::GeneratePhotoHiTrimData()
{
	WORD				wTemp;
	DWORD				dwAdd;
	DWORD				k;
	DWORD				w;
	CFMT_Point<double>	pw1;
	CFMT_Point<double>	pw2;
	double				m,q,res;
	DWORD				dwCurve;

	dwCurve=e_PhotoHigh_Dlg;
	dwAdd=DHA5X5_TRIM_00_CURVE+0x4000;

	pw1=m_Curves[dwCurve][0];
	//pw1.m_PX=pw1.m_PX;
	w=0;
	for (k=1;k<!(m_Curves[dwCurve]);k++)
	{	
		pw2=m_Curves[dwCurve][k];
		//pw2.m_PX=pw2.m_PX;

		if (pw2.GetX()==pw1.GetX())
		{
			SetWord(dwAdd+2*w,(WORD)(pw2.GetY()));
		}
		else
		{

			m=((double)(pw2.GetY())-(double)(pw1.GetY()))/((double)(pw2.GetX())-(double)(pw1.GetX()));
			q=(double)(pw2.GetY())-m*(double)(pw2.GetX());

			for (w=(WORD)(pw1.GetX());w<=(WORD)(pw2.GetX());w++)
			{
				res=(m*w+q);

				if (res<0)
				{
					wTemp=0;
				}
				else if (res>255.0)
				{
					wTemp=255;
				}
				else
				{
					wTemp=(WORD)(res+0.5);
				}

				SetWord(dwAdd+2*w,wTemp);
			}
		}

		pw1=pw2;
	}

	return TRUE;
}

WORD CMMDlg::CalcCRC16Word(BYTE btData,WORD wOld)
{
	WORD	wCRC;
	DWORD	k;

	BOOL	bC[16];
	BOOL	bCRC[16];
	BOOL	bData[8];

	for (k=0;k<16;k++)
	{
		bC[k]=((wOld & (1<<k))>0);
	}

	for (k=0;k<8;k++)
	{
		bData[k]=((btData & (1<<k))>0);
	}

	bCRC[15]=bC[7] ^ bData[4] ^ bC[11] ^ bData[0] ^ bC[15];
	bCRC[14]=bC[6] ^ bData[5] ^ bC[10] ^ bData[1] ^ bC[14];
	bCRC[13]=bC[5] ^ bData[6] ^ bC[9] ^ bData[2] ^ bC[13];
	bCRC[12]=bC[4] ^ bData[0] ^ bC[15] ^ bData[7] ^ bC[8] ^ bData[3] ^ bC[12];
	bCRC[11]=bC[3] ^ bData[1] ^ bC[14];
	bCRC[10]=bC[2] ^ bData[2] ^ bC[13];
	bCRC[9]=bC[1] ^ bData[3] ^ bC[12];
	bCRC[8]=bC[0] ^ bData[4] ^ bC[11] ^ bData[0] ^ bC[15];
	bCRC[7]=bData[0] ^ bC[15] ^ bData[5] ^ bC[10] ^ bData[1] ^ bC[14];
	bCRC[6]=bData[1] ^ bC[14] ^ bData[6] ^ bC[9] ^ bData[2] ^ bC[13];
	bCRC[5]=bData[2] ^ bC[13] ^ bData[7] ^ bC[8] ^ bData[3] ^ bC[12];
	bCRC[4]=bData[3] ^ bC[12];
	bCRC[3]=bData[4] ^ bC[11] ^ bData[0] ^ bC[15];
	bCRC[2]=bData[5] ^ bC[10] ^ bData[1] ^ bC[14];
	bCRC[1]=bData[6] ^ bC[9] ^ bData[2] ^ bC[13];
	bCRC[0]=bData[7] ^ bC[8] ^ bData[3] ^ bC[12];

	wCRC=0;
	for (k=0;k<16;k++)
	{
		if (bCRC[k])
		{
			wCRC+=(1<<k);
		}
	}

	return wCRC;
}

WORD CMMDlg::CalcCRC(BYTE* pbtData, DWORD dwNB)
{
	DWORD	k;
	WORD	wCRC;

	wCRC=0xFFFF;

	for (k=0;k<dwNB;k++)
	{
		wCRC=CalcCRC16Word(pbtData[k],wCRC);
	}

	return wCRC;
	
}

void CMMDlg::GenerateCRC()
{
	WORD wCRC;
	wCRC=CalcCRC(m_pbtMemory,DHA5X5_MEMORYSIZE-8192);

	m_pbtMemory[DHA5X5_MEMORYSIZE-8192]=(BYTE)(wCRC & 0xFF);
	m_pbtMemory[DHA5X5_MEMORYSIZE-8191]=(BYTE)((wCRC>>8) & 0xFF);
}

BOOL CMMDlg::GenerateMemory()
{	
	DWORD	k;
	DWORD	dwMS=DHA5X5_MEMORYSIZE;

	for (k=0;k<DHA5X5_MEMORYSIZE/2;k++)
	{
		SetWord(2*k,0);
	}
	

	// Generate Brightness Unit
	for (k=0;k<4;k++)
	{
		GenerateVDCData(k);
	}
	
	for (k=0;k<4;k++)
	{
		GeneratePWMData(k);
	}
	
	// Generate Trimming Data
	GeneratePhotoLoTrimData();
	GeneratePhotoHiTrimData();
	GenerateBackTempTrimData();

	GenerateCurrentFANThresh();

	// Calc CRC
	GenerateCRC();

	return TRUE;
}

// -----------------------------------------------------------------------------------
//	GenerateBackTempTrimData
// -----------------------------------------------------------------------------------

BOOL CMMDlg::GenerateBackTempTrimData()
{
	WORD				wTemp;
	DWORD				dwAdd;
	DWORD				k;
	int					w;
	CFMT_Point<double>	pw1;
	CFMT_Point<double>	pw2;
	double				m,q,res;
	DWORD				dwCurve;

	dwCurve=e_BackTemp_Dlg;
	dwAdd=DHA5X5_TRIM_00_CURVE;

	pw1=m_Curves[dwCurve][0];
	//pw1.m_PX=pw1.m_PX;
	w=0;
	for (k=1;k<!(m_Curves[dwCurve]);k++)
	{	
		pw2=m_Curves[dwCurve][k];
		//pw2.m_PX=pw2.m_PX;

		if (pw2.GetX()==pw1.GetX())
		{
			SetWord(dwAdd+2*w,(WORD)(pw2.GetY()));
		}
		else
		{

			m=((double)(pw2.GetY())-(double)(pw1.GetY()))/((double)(pw2.GetX())-(double)(pw1.GetX()));
			q=(double)(pw2.GetY())-m*(double)(pw2.GetX());

			for (w=(int)(pw1.GetX());w<=(int)(pw2.GetX());w++)
			{
				res=(((m*w+q)+55.0));

				if (res<0)
				{
					wTemp=0;
				}
				else if (res>255.0)
				{
					wTemp=255;
				}
				else
				{
					wTemp=(WORD)(res+0.5);
				}

				SetWord(dwAdd+2*(w+55),wTemp);
			}
		}

		pw1=pw2;
	}

	return TRUE;
}

void CMMDlg::OnBnClickedButProg()
{
	CString	s;

	SaveMemoryImage("write.bin");
	GenerateMemory();
	GenerateMIF();

	//EnableControls(FALSE);

	SetTimer(0,100,NULL);
	SetProgProgress(0);

	s="Writing into Flash Memory...";
	UpdateStatus(s,e_Status_Programming);

	// Lancio il thread
	m_dwThreadReturn=0;

	m_pThread=AfxBeginThread(ProgramThread,this);
}

void CMMDlg::OnBnClickedButVerify()
{
	CString	s;

	//SaveMemoryImage("mem.bin");
	GenerateMemory();

	//EnableControls(FALSE);

	SetTimer(0,100,NULL);
	SetProgProgress(0);

	s="Verifying Flash Memory...";
	UpdateStatus(s,e_Status_Programming);

	// Lancio il thread
	m_dwThreadReturn=0;

	m_pThread=AfxBeginThread(VerifyThread,this);
}

// -----------------------------------------------------------------------------------
//	SaveMemoryImage
// -----------------------------------------------------------------------------------

BOOL CMMDlg::SaveMemoryImage(const CString& sImageName)
{
	CFile	f;

	GenerateMemory();

	if (!f.Open(sImageName,CFile::modeWrite|CFile::modeCreate))
	{
		return FALSE;
	}

	TRY
	{
		f.Write(m_pbtMemory,DHA5X5_MEMORYSIZE);
		f.Close();
	}
	CATCH(CFileException, e)
	{
		return FALSE;
	}
	END_CATCH

	return TRUE;
}


// -----------------------------------------------------------------------------------
//	PollThread
// -----------------------------------------------------------------------------------

UINT CMMDlg::PollThread(LPVOID pParam) 
{
	t_FMT_Uint32		uiRet;

	CMMDlg *pMe = (CMMDlg*)pParam;

	uiRet = pMe->m_pDev->ConnectSpi();

	if (uiRet != e_Return_OK)
	{
		pMe->m_dwThreadReturn = 1;
		::PostMessage(pMe->m_hWnd, MEMORYPROGDLG_ERRORMESS, e_Ret_ConnectErr, 0);

		return 0;
	}

	t_FMT_Uint8			pbtTxBuf[5];
	t_FMT_Uint8			pbtRxBuf[5];

	pbtTxBuf[0] = 0x9F;

	uiRet = pMe->m_pDev->PerformSpiTransfer(pbtTxBuf, 1, pbtRxBuf, 3, pMe->m_pDev->m_ucSpiSpeed, 500);

	if (uiRet != e_Return_OK)
	{
		pMe->m_pDev->DisconnectSpi();
		pMe->m_dwThreadReturn = 1;
		::PostMessage(pMe->m_hWnd, MEMORYPROGDLG_ERRORMESS, e_Ret_CommErr, 0);

		return 0;
	}

	pMe->m_pDev->DisconnectSpi();

	if ((pbtRxBuf[0] != 0x20) || (pbtRxBuf[1] != 0x40) || (pbtRxBuf[2] != 0x12))
	{
		pMe->m_dwThreadReturn = 1;
		::PostMessage(pMe->m_hWnd, MEMORYPROGDLG_ERRORMESS, e_Ret_DeviceErr, 0);
		return 0;
	}

	pMe->m_dwThreadReturn = 0;
	::PostMessage(pMe->m_hWnd, MEMORYPROGDLG_ENDMESS, 0, 0);

	return 0;
	

	#if 0
	CMMDlg *pMe=(CMMDlg*)pParam;

	BYTE						btBuf[10];
	CUSB2SSIDevice::SCommand	com[10];
	BOOL						bRet;

	// ----- Connect to the device ------------------------------

	if (!pMe->m_Device.Connect())
	{
		pMe->m_Device.Disconnect();
		pMe->m_dwThreadReturn=1;
		::PostMessage(pMe->m_hWnd,MEMORYPROGDLG_ERRORMESS,e_Ret_ConnectErr,0);

		return 0;
	}

	// ----- Configure and verify connected device -----------------------------------

	btBuf[0]=0x9F;

	com[0].CreateConfigCommand(CUSB2SSIDevice::e_BaudRate_200kHz,CUSB2SSIDevice::e_BaudRate_2kHz,
		CUSB2SSIDevice::e_BaudRate_2kHz,TRUE,FALSE,FALSE,FALSE,FALSE,0xFF,TRUE);

	com[1].CreateDiscoutCommand(0x30);
	com[2].CreateDelayCommand(100);

	com[3].CreateSPIWriteThenReadCommand(FALSE,TRUE,0,0,FALSE,
				CUSB2SSIDevice::e_WordLength_8bits,
				1,btBuf,3);

	bRet=pMe->m_Device.ProcCommandList(com,4);

	if (!bRet)
	{
		pMe->m_Device.Disconnect();
		pMe->m_dwThreadReturn=1;
		::PostMessage(pMe->m_hWnd,MEMORYPROGDLG_ERRORMESS,e_Ret_CommErr,0);
		return 0;
	}

	if ((com[3].GetRXData(0)!=0x20) || (com[3].GetRXData(1)!=0x40) || (com[3].GetRXData(2)!=0x12))
	{
		com[0].CreateConfigCommand(CUSB2SSIDevice::e_BaudRate_200kHz,CUSB2SSIDevice::e_BaudRate_2kHz,
			CUSB2SSIDevice::e_BaudRate_2kHz,FALSE,FALSE,FALSE,FALSE,FALSE,0xFF,FALSE);

		com[1].CreateDiscoutCommand(0x00);
		com[2].CreateDelayCommand(100);

		bRet=pMe->m_Device.ProcCommandList(com,3);

		pMe->m_Device.Disconnect();
		pMe->m_dwThreadReturn=1;
		::PostMessage(pMe->m_hWnd,MEMORYPROGDLG_ERRORMESS,e_Ret_DeviceErr,0);
		return 0;
	}

	// Led off and three state ------------------------------------------------------------------

	com[0].CreateConfigCommand(CUSB2SSIDevice::e_BaudRate_200kHz,CUSB2SSIDevice::e_BaudRate_2kHz,
		CUSB2SSIDevice::e_BaudRate_2kHz,FALSE,FALSE,FALSE,FALSE,FALSE,0xFF,FALSE);

	com[1].CreateDiscoutCommand(0x00);
	com[2].CreateDelayCommand(100);

	bRet=pMe->m_Device.ProcCommandList(com,3);

	if (!bRet)
	{
		pMe->m_Device.Disconnect();
		pMe->m_dwThreadReturn=1;
		::PostMessage(pMe->m_hWnd,MEMORYPROGDLG_ERRORMESS,e_Ret_CommErr,0);
		return 0;
	}
	
	//=== End of operation ================================


	
	pMe->m_Device.Disconnect();

	pMe->m_dwThreadReturn=0;
	::PostMessage(pMe->m_hWnd,MEMORYPROGDLG_ENDMESS,0,0);
	return 0;
#endif

}


// -----------------------------------------------------------------------------------
//	ProgramThread
// -----------------------------------------------------------------------------------

UINT CMMDlg::ProgramThread(LPVOID pParam) 
{
	t_FMT_Uint32				uiRet;
	DWORD						dwAdd;
	DWORD						dwTot;
	DWORD						k,w;
	t_FMT_Uint8					*pbtTxBuf;
	t_FMT_Uint8					*pbtRxBuf;
	CString						s;
	BOOL						bCheck;
	CFMT_File					f;

	pbtTxBuf = new BYTE[MEMPROG_BYTE_PER_PAGE + 4];
	pbtRxBuf = new BYTE[DHA5X5_MEMORYSIZE];

	CMMDlg *pMe = (CMMDlg*)pParam;

	uiRet = pMe->m_pDev->ConnectSpi();

	if (uiRet != e_Return_OK)
	{
		pMe->m_dwThreadReturn = 1;
		::PostMessage(pMe->m_hWnd, MEMORYPROGDLG_ERRORMESS, e_Ret_ConnectErr, 0);
		goto l_Return;
	}

	int x;

	x = DHA5X5_MEMORYSIZE;
	x = MEMPROG_NUM_PAGES;


	// === Program operation ==============================

	// ----- PROGRAMMING -----------------------------------------------------------

	f.Open("write.bin", CFMT_File::e_OpenMode_Overwrite|CFMT_File::e_OpenMode_Write);
	f.Write(pMe->m_pbtMemory, DHA5X5_MEMORYSIZE);
	f.Close();


	dwAdd = 0;
	dwTot = 0;

	for (k=0; k<MEMPROG_NUM_PAGES; k++)
	{

		// --- Write Enable --------

		pbtTxBuf[0] = 0x06;

		uiRet = pMe->m_pDev->PerformSpiTransfer(pbtTxBuf, 1, pbtRxBuf, 0, pMe->m_pDev->m_ucSpiSpeed, 500);

		if (uiRet != e_Return_OK)
		{
			pMe->m_dwThreadReturn = 1;
			::PostMessage(pMe->m_hWnd, MEMORYPROGDLG_ERRORMESS, e_Ret_CommErr, 0);

			goto l_Return;
		}

		// --- Program Page --------

		pbtTxBuf[0] = 0x0A;

		pbtTxBuf[1] = (BYTE)(dwAdd>>16);
		pbtTxBuf[2] = (BYTE)(dwAdd>>8);
		pbtTxBuf[3] = (BYTE)(dwAdd);

		memcpy(pbtTxBuf + 4, pMe->m_pbtMemory + dwAdd, MEMPROG_BYTE_PER_PAGE);

		uiRet = pMe->m_pDev->PerformSpiTransfer(pbtTxBuf, 4 + MEMPROG_BYTE_PER_PAGE, pbtRxBuf, 0, pMe->m_pDev->m_ucSpiSpeed, 500);

		if (uiRet != e_Return_OK)
		{
			pMe->m_dwThreadReturn = 1;
			::PostMessage(pMe->m_hWnd, MEMORYPROGDLG_ERRORMESS, e_Ret_CommErr, 0);

			goto l_Return;
		}

		if (!pMe->WaitEndOfProcess(500))
		{
			pMe->m_dwThreadReturn = 1;
			::PostMessage(pMe->m_hWnd, MEMORYPROGDLG_ERRORMESS, e_Ret_CommErr, 0);

			goto l_Return;
		}

		/*btBuf[0]=0x04;
		com[0].CreateSPIWriteCommand(FALSE,TRUE,0,0,FALSE,
					CUSB2SSIDevice::e_WordLength_8bits,1,btBuf);

		com[1].CreateDelayCommand(1);

		bRet=pMe->m_Device.ProcCommandList(com,2);

		if (!bRet)
		{
			pMe->m_Device.Disconnect();
			pMe->m_dwThreadReturn=1;
			::PostMessage(pMe->m_hWnd,MEMORYPROGDLG_ERRORMESS,e_Ret_CommErr,0);
			return 0;
		}*/

		dwAdd += MEMPROG_BYTE_PER_PAGE;
		dwTot += MEMPROG_BYTE_PER_PAGE;

		::PostMessage(pMe->m_hWnd,
			MEMORYPROGDLG_PROGMESS, 0, 
			(LONG)((double)(dwTot) * 10000.0 / (double)DHA5X5_MEMORYSIZE));
	}


	// ----- VERIFYING -----------------------------------------------------------

	s = "Verifying Flash Memory...";
	pMe->UpdateStatus(s, e_Status_Programming);

	bCheck = TRUE;

	// === Read operation ==============================

	dwAdd = 0;
	dwTot = 0;
	memset(pbtRxBuf, 0xAA, DHA5X5_MEMORYSIZE);


	for (k=0; k < MEMPROG_NUM_PAGES / MEMPROG_PAGE_PER_CYCLE; k++)
	{
		// --- Read Page --------

		pbtTxBuf[0] = 0x03;

		for (w=0; w < MEMPROG_PAGE_PER_CYCLE; w++)
		{
			pbtTxBuf[1] = (BYTE)(dwAdd >> 16);
			pbtTxBuf[2] = (BYTE)(dwAdd >> 8);
			pbtTxBuf[3] = (BYTE)(dwAdd);

			uiRet = pMe->m_pDev->PerformSpiTransfer(pbtTxBuf, 4, pbtRxBuf + dwAdd, MEMPROG_BYTE_PER_PAGE, pMe->m_pDev->m_ucSpiSpeed, 500);

			if (uiRet != e_Return_OK)
			{
				pMe->m_dwThreadReturn = 1;
				::PostMessage(pMe->m_hWnd, MEMORYPROGDLG_ERRORMESS, e_Ret_CommErr, 0);

				goto l_Return;
			}
			dwAdd += MEMPROG_BYTE_PER_PAGE;
			dwTot += MEMPROG_BYTE_PER_PAGE;
		}

		::PostMessage(pMe->m_hWnd,
			MEMORYPROGDLG_PROGMESS, 0, 
			(LONG)((double)(dwTot) * 10000.0 / (double)DHA5X5_MEMORYSIZE));
	}

	if (memcmp(pMe->m_pbtMemory, pbtRxBuf, MEMPROG_NUM_PAGES * MEMPROG_BYTE_PER_PAGE) != 0)
	{
		bCheck = FALSE;
	}

	f.Open("read.bin", CFMT_File::e_OpenMode_Overwrite|CFMT_File::e_OpenMode_Write);
	f.Write(pbtRxBuf, DHA5X5_MEMORYSIZE);
	f.Close();


	if (bCheck)
	{
		::PostMessage(pMe->m_hWnd, MEMORYPROGDLG_ENDMESS, 3, 0);
	}
	else
	{
		::PostMessage(pMe->m_hWnd, MEMORYPROGDLG_ERRORMESS, e_Ret_VerifyErr, 0);
	}

	pMe->m_dwThreadReturn = 0;


l_Return:

	delete[] pbtTxBuf;
	delete[] pbtRxBuf;
	pMe->m_pDev->DisconnectSpi();

	return 0;


	#if 0
	CMMDlg *pMe=(CMMDlg*)pParam;

	BYTE						btBuf[1200];
	BYTE						btRXBuf[256];
	CUSB2SSIDevice::SCommand	com[2*MEMPROG_PAGE_PER_CYCLE];
	BOOL						bRet;
	BOOL						bCheck;

	DWORD						k,w;
	DWORD						dwAdd;
	DWORD						dwTot;

	CFile						fd;

	DWORD dwMS=DHA5X5_MEMORYSIZE;
	DWORD dwNP=MEMPROG_NUM_PAGES;

	// ----- Connect to the device ------------------------------

	if (!pMe->m_Device.Connect())
	{
		pMe->m_Device.Disconnect();
		pMe->m_dwThreadReturn=1;
		::PostMessage(pMe->m_hWnd,MEMORYPROGDLG_ERRORMESS,e_Ret_ConnectErr,0);

		return 0;
	}

	// ----- Configure and verify connected device -----------------------------------

	com[0].CreateConfigCommand(CUSB2SSIDevice::e_BaudRate_200kHz,CUSB2SSIDevice::e_BaudRate_2kHz,
		CUSB2SSIDevice::e_BaudRate_2kHz,TRUE,FALSE,FALSE,FALSE,FALSE,0xFF,TRUE);

	com[1].CreateDiscoutCommand(0x30);
	com[2].CreateDelayCommand(100);

	bRet=pMe->m_Device.ProcCommandList(com,3);

	if (!bRet)
	{
		pMe->m_Device.Disconnect();
		pMe->m_dwThreadReturn=1;
		::PostMessage(pMe->m_hWnd,MEMORYPROGDLG_ERRORMESS,e_Ret_CommErr,0);
		return 0;
	}

	// === Program operation ==============================

	// ----- PROGRAMMING -----------------------------------------------------------

	dwAdd=0;
	dwTot=0;

	for (k=0;k<MEMPROG_NUM_PAGES;k++)
	{

		// --- Write Enable --------

		btBuf[0]=0x06;

		com[0].CreateSPIWriteCommand(FALSE,TRUE,0,0,FALSE,
					CUSB2SSIDevice::e_WordLength_8bits,1,btBuf);
		com[1].CreateDelayCommand(1);

		// --- Program Page --------

		btBuf[0]=0x0A;

		btBuf[1]=(BYTE)(dwAdd>>16);
		btBuf[2]=(BYTE)(dwAdd>>8);
		btBuf[3]=(BYTE)(dwAdd);

		memcpy(btBuf+4,pMe->m_pbtMemory+dwAdd,MEMPROG_BYTE_PER_PAGE);

		com[2].CreateSPIWriteCommand(FALSE,TRUE,0,0,FALSE,
				CUSB2SSIDevice::e_WordLength_8bits,MEMPROG_BYTE_PER_PAGE+4,btBuf);

		// --- Write Disable --------

		bRet=pMe->m_Device.ProcCommandList(com,3);

		if (!bRet)
		{
			pMe->m_Device.Disconnect();
			pMe->m_dwThreadReturn=1;
			::PostMessage(pMe->m_hWnd,MEMORYPROGDLG_ERRORMESS,e_Ret_CommErr,0);
			return 0;
		}

		if (!WaitEndOfProcess(pMe))
		{
			com[0].CreateConfigCommand(CUSB2SSIDevice::e_BaudRate_200kHz,CUSB2SSIDevice::e_BaudRate_2kHz,
				CUSB2SSIDevice::e_BaudRate_2kHz,FALSE,FALSE,FALSE,FALSE,FALSE,0xFF,FALSE);

			com[1].CreateDiscoutCommand(0x00);
			com[2].CreateDelayCommand(100);

			bRet=pMe->m_Device.ProcCommandList(com,3);

			pMe->m_Device.Disconnect();
			pMe->m_dwThreadReturn=1;
			::PostMessage(pMe->m_hWnd,MEMORYPROGDLG_ERRORMESS,e_Ret_CommErr,0);
			return 0;
		}

		btBuf[0]=0x04;
		com[0].CreateSPIWriteCommand(FALSE,TRUE,0,0,FALSE,
					CUSB2SSIDevice::e_WordLength_8bits,1,btBuf);

		com[1].CreateDelayCommand(1);

		bRet=pMe->m_Device.ProcCommandList(com,2);

		if (!bRet)
		{
			pMe->m_Device.Disconnect();
			pMe->m_dwThreadReturn=1;
			::PostMessage(pMe->m_hWnd,MEMORYPROGDLG_ERRORMESS,e_Ret_CommErr,0);
			return 0;
		}

		dwAdd+=MEMPROG_BYTE_PER_PAGE;
		dwTot+=MEMPROG_BYTE_PER_PAGE;

		::PostMessage(pMe->m_hWnd,
			MEMORYPROGDLG_PROGMESS,0, 
			(LONG)((double)(dwTot)*10000.0/(double)DHA5X5_MEMORYSIZE));
	}

	// ----- VERIFYING -----------------------------------------------------------

	CString s;
	s="Verifying Flash Memory...";
	pMe->UpdateStatus(s,e_Status_Programming);

	bCheck=TRUE;

	// === Read operation ==============================

	dwAdd=0;
	dwTot=0;

	for (k=0;k<MEMPROG_NUM_PAGES/MEMPROG_PAGE_PER_CYCLE;k++)
	{

		// --- Read Page --------

		btBuf[0]=0x03;

		for (w=0;w<MEMPROG_PAGE_PER_CYCLE;w++)
		{

			btBuf[1]=(BYTE)(dwAdd>>16);
			btBuf[2]=(BYTE)(dwAdd>>8);
			btBuf[3]=(BYTE)(dwAdd);

			com[2*w].CreateSPIWriteThenReadCommand(FALSE,TRUE,0,0,FALSE,
					CUSB2SSIDevice::e_WordLength_8bits,4,btBuf,MEMPROG_BYTE_PER_PAGE);

			com[2*w+1].CreateDelayCommand(1);

			dwAdd+=MEMPROG_BYTE_PER_PAGE;
			dwTot+=MEMPROG_BYTE_PER_PAGE;
		}

		bRet=pMe->m_Device.ProcCommandList(com,2*MEMPROG_PAGE_PER_CYCLE);

		if (!bRet)
		{
			pMe->m_Device.Disconnect();
			pMe->m_dwThreadReturn=1;
			::PostMessage(pMe->m_hWnd,MEMORYPROGDLG_ERRORMESS,e_Ret_CommErr,0);
			return 0;
		}

		for (w=0;w<MEMPROG_PAGE_PER_CYCLE;w++)
		{
			if (memcmp(com[2*w].GetRXBuf(),&(pMe->m_pbtMemory[k*MEMPROG_BYTE_PER_PAGE*MEMPROG_PAGE_PER_CYCLE+w*MEMPROG_BYTE_PER_PAGE]),MEMPROG_BYTE_PER_PAGE)!=0)
			{
				bCheck=FALSE;
			}

		}


		::PostMessage(pMe->m_hWnd,
			MEMORYPROGDLG_PROGMESS,0, 
			(LONG)((double)(dwTot)*10000.0/(double)DHA5X5_MEMORYSIZE));
	}

	/*fd.Close();
	fs.Close();*/

	// Led off and three state ------------------------------------------------------------------

	com[0].CreateConfigCommand(CUSB2SSIDevice::e_BaudRate_200kHz,CUSB2SSIDevice::e_BaudRate_2kHz,
		CUSB2SSIDevice::e_BaudRate_2kHz,FALSE,FALSE,FALSE,FALSE,FALSE,0xFF,FALSE);

	com[1].CreateDiscoutCommand(0x00);
	com[2].CreateDelayCommand(100);

	bRet=pMe->m_Device.ProcCommandList(com,3);

	if (!bRet)
	{
		pMe->m_Device.Disconnect();
		pMe->m_dwThreadReturn=1;
		::PostMessage(pMe->m_hWnd,MEMORYPROGDLG_ERRORMESS,e_Ret_CommErr,0);
		return 0;
	}

	//=== End of operation ================================

	pMe->m_Device.Disconnect();

	if (bCheck)
	{
		::PostMessage(pMe->m_hWnd,MEMORYPROGDLG_ENDMESS,3,0);
	}
	else
	{
		::PostMessage(pMe->m_hWnd,MEMORYPROGDLG_ERRORMESS,e_Ret_VerifyErr,0);
	}

	pMe->m_dwThreadReturn=0;

	#endif

	return 0;
	
}

// -----------------------------------------------------------------------------------
//	WaitEndOfProcess
// -----------------------------------------------------------------------------------

BOOL CMMDlg::WaitEndOfProcess(int iTimeout) 
{
	t_FMT_Uint32				uiRet;
	t_FMT_Uint8					pbtTxBuf[5];
	t_FMT_Uint8					pbtRxBuf[5];
	int							iStart;


	iStart = ::GetTickCount();

	while (::GetTickCount() - iStart < iTimeout)
	{
		pbtTxBuf[0] = 0x05;

		uiRet = m_pDev->PerformSpiTransfer(pbtTxBuf, 1, pbtRxBuf, 1, m_pDev->m_ucSpiSpeed, 500);

		if (uiRet != e_Return_OK)
		{
			return FALSE;
		}

		if ((pbtRxBuf[0] & 0x01)==0)
		{
			return TRUE;
		}

		Sleep(10);
	}

	return FALSE;


	#if 0

	BYTE						btTXBuf;
	BYTE						btTemp;
	CUSB2SSIDevice::SCommand	com[32];
	BOOL						bAgain;
	BOOL						bRet;
	DWORD						k;

	btTXBuf=0x05;
	bAgain=TRUE;

	for (k=0;k<16;k++)
	{
		com[2*k].CreateSPIWriteThenReadCommand(FALSE,TRUE,0,0,FALSE,
					CUSB2SSIDevice::e_WordLength_8bits,1,&btTXBuf,1);

		com[2*k+1].CreateDelayCommand(1);

	}

	while (bAgain)
	{
		bRet=pMe->m_Device.ProcCommandList(com,32);
	
		if (!bRet)
		{
			return FALSE;
		}

		for (k=0;k<16;k++)
		{
			btTemp=com[2*k].GetRXData(0);

			if ((btTemp & 0x01)==0)
			{
				return TRUE;
			}
			else
			{
			}
		}

		Sleep(20);
	}
	
	#endif

	return TRUE;

}


// -----------------------------------------------------------------------------------
//	VerifyThread
// -----------------------------------------------------------------------------------

UINT CMMDlg::VerifyThread(LPVOID pParam) 
{
	t_FMT_Uint32				uiRet;
	DWORD						dwAdd;
	DWORD						dwTot;
	DWORD						k,w;
	t_FMT_Uint8					*pbtTxBuf;
	t_FMT_Uint8					*pbtRxBuf;
	CString						s;
	BOOL						bCheck;

	pbtTxBuf = new BYTE[MEMPROG_BYTE_PER_PAGE + 4];
	pbtRxBuf = new BYTE[DHA5X5_MEMORYSIZE];

	CMMDlg *pMe = (CMMDlg*)pParam;

	uiRet = pMe->m_pDev->ConnectSpi();

	if (uiRet != e_Return_OK)
	{
		pMe->m_dwThreadReturn = 1;
		::PostMessage(pMe->m_hWnd, MEMORYPROGDLG_ERRORMESS, e_Ret_ConnectErr, 0);
		goto l_Return;
	}

	// === Read operation ==============================

	dwAdd = 0;
	dwTot = 0;
	bCheck = TRUE;

	for (k=0; k < MEMPROG_NUM_PAGES / MEMPROG_PAGE_PER_CYCLE; k++)
	{
		// --- Read Page --------

		pbtTxBuf[0] = 0x03;

		for (w=0; w < MEMPROG_PAGE_PER_CYCLE; w++)
		{
			pbtTxBuf[1] = (BYTE)(dwAdd >> 16);
			pbtTxBuf[2] = (BYTE)(dwAdd >> 8);
			pbtTxBuf[3] = (BYTE)(dwAdd);

			uiRet = pMe->m_pDev->PerformSpiTransfer(pbtTxBuf, 4, pbtRxBuf + dwAdd, MEMPROG_BYTE_PER_PAGE, pMe->m_pDev->m_ucSpiSpeed, 500);

			if (uiRet != e_Return_OK)
			{
				pMe->m_dwThreadReturn = 1;
				::PostMessage(pMe->m_hWnd, MEMORYPROGDLG_ERRORMESS, e_Ret_CommErr, 0);

				goto l_Return;
			}
			dwAdd += MEMPROG_BYTE_PER_PAGE;
			dwTot += MEMPROG_BYTE_PER_PAGE;
		}

		::PostMessage(pMe->m_hWnd,
			MEMORYPROGDLG_PROGMESS, 0, 
			(LONG)((double)(dwTot) * 10000.0 / (double)DHA5X5_MEMORYSIZE));
	}

	if (memcmp(pMe->m_pbtMemory, pbtRxBuf, MEMPROG_NUM_PAGES * MEMPROG_BYTE_PER_PAGE) != 0)
	{
		bCheck = FALSE;
	}

	if (bCheck)
	{
		::PostMessage(pMe->m_hWnd, MEMORYPROGDLG_ENDMESS, 3, 0);
	}
	else
	{
		::PostMessage(pMe->m_hWnd, MEMORYPROGDLG_ERRORMESS, e_Ret_VerifyErr, 0);
	}

	pMe->m_dwThreadReturn = 0;




l_Return:

	delete[] pbtTxBuf;
	delete[] pbtRxBuf;
	pMe->m_pDev->DisconnectSpi();

	return 0;


#if 0
	CMMDlg *pMe=(CMMDlg*)pParam;

	BYTE						btBuf[4];
	BYTE						btRXBuf[256];
	CUSB2SSIDevice::SCommand	com[2*MEMPROG_PAGE_PER_CYCLE];
	//CUSB2SSIDevice::SCommand	com[1000];
	BOOL						bRet;

	DWORD						k,w;
	DWORD						dwAdd;
	DWORD						dwTot;

	BOOL						bCheck;

	bCheck=TRUE;

	// ----- Connect to the device ------------------------------

	if (!pMe->m_Device.Connect())
	{
		pMe->m_Device.Disconnect();
		pMe->m_dwThreadReturn=1;
		::PostMessage(pMe->m_hWnd,MEMORYPROGDLG_ERRORMESS,e_Ret_ConnectErr,0);

		return 0;
	}

	// ----- Configure and verify connected device -----------------------------------

	com[0].CreateConfigCommand(CUSB2SSIDevice::e_BaudRate_200kHz,CUSB2SSIDevice::e_BaudRate_2kHz,
		CUSB2SSIDevice::e_BaudRate_2kHz,TRUE,FALSE,FALSE,FALSE,FALSE,0xFF,TRUE);

	com[1].CreateDiscoutCommand(0x30);
	com[2].CreateDelayCommand(100);

	bRet=pMe->m_Device.ProcCommandList(com,3);

	if (!bRet)
	{
		pMe->m_Device.Disconnect();
		pMe->m_dwThreadReturn=1;
		::PostMessage(pMe->m_hWnd,MEMORYPROGDLG_ERRORMESS,e_Ret_CommErr,0);
		return 0;
	}

	// === Read operation ==============================

	dwTot=0;

	CFile fd;
	fd.Open("read.bin",CFile::modeWrite|CFile::modeCreate);

	dwAdd=0;
	for (k=0;k<MEMPROG_NUM_PAGES/MEMPROG_PAGE_PER_CYCLE;k++)
	{

		// --- Read Page --------

		btBuf[0]=0x03;

		for (w=0;w<MEMPROG_PAGE_PER_CYCLE;w++)
		{

			btBuf[1]=(BYTE)(dwAdd>>16);
			btBuf[2]=(BYTE)(dwAdd>>8);
			btBuf[3]=(BYTE)(dwAdd);

			com[2*w].CreateSPIWriteThenReadCommand(FALSE,TRUE,0,0,FALSE,
					CUSB2SSIDevice::e_WordLength_8bits,4,btBuf,MEMPROG_BYTE_PER_PAGE);

			com[2*w+1].CreateDelayCommand(1);

			dwAdd+=MEMPROG_BYTE_PER_PAGE;
			dwTot+=MEMPROG_BYTE_PER_PAGE;
		}

		bRet=pMe->m_Device.ProcCommandList(com,2*MEMPROG_PAGE_PER_CYCLE);

		if (!bRet)
		{
			pMe->m_Device.Disconnect();
			pMe->m_dwThreadReturn=1;
			::PostMessage(pMe->m_hWnd,MEMORYPROGDLG_ERRORMESS,e_Ret_CommErr,0);
			return 0;
		}

		for (w=0;w<MEMPROG_PAGE_PER_CYCLE;w++)
		{
			if (memcmp(com[2*w].GetRXBuf(),&(pMe->m_pbtMemory[k*MEMPROG_BYTE_PER_PAGE*MEMPROG_PAGE_PER_CYCLE+w*MEMPROG_BYTE_PER_PAGE]),MEMPROG_BYTE_PER_PAGE)!=0)
			{
				bCheck=FALSE;
			}

			fd.Write(com[2*w].GetRXBuf(),MEMPROG_BYTE_PER_PAGE);
		}


		::PostMessage(pMe->m_hWnd,
			MEMORYPROGDLG_PROGMESS,0, 
			(LONG)((double)(dwTot)*10000.0/(double)DHA5X5_MEMORYSIZE));
	}

	fd.Close();

	// Led off and three state ------------------------------------------------------------------

	com[0].CreateConfigCommand(CUSB2SSIDevice::e_BaudRate_200kHz,CUSB2SSIDevice::e_BaudRate_2kHz,
		CUSB2SSIDevice::e_BaudRate_2kHz,FALSE,FALSE,FALSE,FALSE,FALSE,0xFF,FALSE);

	com[1].CreateDiscoutCommand(0x00);
	com[2].CreateDelayCommand(100);

	bRet=pMe->m_Device.ProcCommandList(com,3);

	if (!bRet)
	{
		pMe->m_Device.Disconnect();
		pMe->m_dwThreadReturn=1;
		::PostMessage(pMe->m_hWnd,MEMORYPROGDLG_ERRORMESS,e_Ret_CommErr,0);
		return 0;
	}

	//=== End of operation ================================

	pMe->m_Device.Disconnect();

	if (bCheck)
	{
		::PostMessage(pMe->m_hWnd,MEMORYPROGDLG_ENDMESS,3,0);
	}
	else
	{
		::PostMessage(pMe->m_hWnd,MEMORYPROGDLG_ERRORMESS,e_Ret_VerifyErr,0);
	}

	pMe->m_dwThreadReturn=0;
	#endif
	return 0;
}

void CMMDlg::OnBnClickedButPoll()
{
	CString s;
	s="Polling memory...";
	UpdateStatus(s,e_Status_Programming);

	// Lancio il thread
	m_dwThreadReturn=0;

	m_pThread=AfxBeginThread(PollThread,this);
}

// -----------------------------------------------------------------------------------
//	UpdateStatus
// -----------------------------------------------------------------------------------

void CMMDlg::UpdateStatus(const CString& sMess, DWORD dwStatus) 
{
	m_dwStatus=dwStatus;
	M_GETSTATIC(IDC_STATIC_STATUS)->SetWindowText(sMess);
	M_GETSTATIC(IDC_STATIC_STATUS)->RedrawWindow();
}

// -----------------------------------------------------------------------------------
//	OnMessageEnd
// -----------------------------------------------------------------------------------

LRESULT CMMDlg::OnMessageEnd(UINT wParam,LONG lParam) 
{
	CString s;

	KillTimer(0);

	switch (wParam)
	{
	case 0:
		s="Flash Memory device connected.";
		UpdateStatus(s,e_Status_Ready);
	break;

	case 1:
		s="Flash Memory correctly programmed.";
		UpdateStatus(s,e_Status_Ready);
	break;

	case 2:
		s="Flash Memory correctly read.";
		UpdateStatus(s,e_Status_Ready);
	break;

	case 3:
		s="Flash Memory correctly verified.";
		UpdateStatus(s,e_Status_Ready);
	break;

	case 4:
		s="Flash Memory correctly erased.";
		UpdateStatus(s,e_Status_Ready);
	break;

	case 5:
		s="Flash Memory correctly erased.";
		UpdateStatus(s,e_Status_Ready);
	break;
	}

	STTE_Message(s,MB_ICONINFORMATION);

	//EnableControls(TRUE);
	Invalidate();
	

	return 0;
}

// -----------------------------------------------------------------------------------
//	OnMessageError
// -----------------------------------------------------------------------------------

LRESULT CMMDlg::OnMessageError(UINT wParam,LONG lParam) 
{
	CString s;

	KillTimer(0);

	s=GetErrString((BYTE)wParam);
	UpdateStatus(s,e_Status_Error);

	STTE_Message(s,MB_ICONSTOP);

	//EnableControls(TRUE);

	Invalidate();

	return 0;
}


// -----------------------------------------------------------------------------------
//	OnMessageChange
// -----------------------------------------------------------------------------------

LRESULT CMMDlg::OnMessageChange(UINT wParam,LONG lParam) 
{
	SetProgProgress(lParam);

	return 0;
}

// -----------------------------------------------------------------------------------
//	GetErrString
// -----------------------------------------------------------------------------------

CString CMMDlg::GetErrString(BYTE btRet)
{
	switch (btRet)
	{
		case e_Ret_OK:
			return "OK";
		break;

		case e_Ret_DeviceErr:
			return "Invalid Device";
		break;

		case e_Ret_ConnectErr:
			return "Connection error";
		break;

		case e_Ret_CommErr:
			return "Communication error";
		break;

		case e_Ret_VerifyErr:
			return "Verification error";
		break;

		default:
			return "Unknown error";
		break;

	}
}

// -----------------------------------------------------------------------------------
//	SetProgProgress
// -----------------------------------------------------------------------------------

void CMMDlg::SetProgProgress(DWORD dwPos) 
{
	CString s;

	M_GETPROGRESS(IDC_PROG_STATUS)->SetPos(dwPos);

	/*s.Format("%.2f%%",(double)dwPos/100.0);
	M_GETSTATIC(IDC_STATIC_PROG)->SetWindowText(s);*/
}


HBRUSH CMMDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	switch (pWnd->GetDlgCtrlID())
	{
	case IDC_STATIC_STATUS:

		if (m_dwStatus==e_Status_Ready)
		{
			hbr=m_brStatusReady; 
		}
		else if (m_dwStatus==e_Status_Programming)
		{
			hbr=m_brStatusProgramming; 
		}
		else if (m_dwStatus==e_Status_Error)
		{
			hbr=m_brStatusError; 
		}
		else 
		{
			hbr=m_brStatusReady; 
		}

		pDC->SetBkMode(TRANSPARENT);
	break;

	}

	// TODO:  Return a different brush if the default is not desired
	return hbr;
}

void CMMDlg::OnMenufileOpen()
{
	CString	sPath;

	CFileDialog *pDlg=new CFileDialog(TRUE,"bin",NULL,OFN_HIDEREADONLY,
		"Binary Files (*.bin) | *.bin|",this);
	
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

	CFile		f;
	DWORD		k;
	DWORD		w;
	DWORD		dwTemp;
	CString		s;
	WORD		wTemp;
	double		d;
	
	try
	{
		f.Open(sPath,CFile::modeRead);

		for (k=0;k<e_Total_Dlg;k++)
		{
			f.Read(&dwTemp,4);
			m_Curves[k].DeleteAll();
			m_Curves[k].Create(dwTemp);

			for (w=0;w<dwTemp;w++)
			{
				f.Read(&d, sizeof(double));
				m_Curves[k][w].SetX(d);
				f.Read(&d, sizeof(double));
				m_Curves[k][w].SetY(d);
			}
		}
	
		f.Read(&wTemp,2);
		s.Format("%d",wTemp);
		M_GETEDIT(IDC_EDIT_CURROFFFAN)->SetWindowText(s);

		f.Read(&wTemp,2);
		s.Format("%d",wTemp);
		M_GETEDIT(IDC_EDIT_CURRONFAN_LO)->SetWindowText(s);

		f.Read(&wTemp,2);
		s.Format("%d",wTemp);
		M_GETEDIT(IDC_EDIT_CURRONFAN_HI)->SetWindowText(s);

		f.Close();
	}
	catch(...)
	{
		STTE_Message("File error.",MB_ICONSTOP);
		return;
	}

	STTE_Message("File correctly loaded.",MB_ICONINFORMATION);
	SetCurrentDlg(m_btCurDlg);
}


void CMMDlg::OnMenufileSave()
{
	CString		sPath;
	CString		s;
	WORD		wTemp;

	CFileDialog *pDlg=new CFileDialog(FALSE,"bin",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
		"Binary Files (*.bin) | *.bin|",this);
	
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

	CFile	f;
	DWORD	k;
	DWORD	w;
	DWORD	dwTemp;
	double	d;
	
	try
	{
		f.Open(sPath,CFile::modeCreate|CFile::modeWrite);

		for (k=0;k<e_Total_Dlg;k++)
		{
			dwTemp=!(m_Curves[k]);
			f.Write(&dwTemp,4);

			for (w=0;w<dwTemp;w++)
			{
				d = m_Curves[k][w].GetX();
				f.Write(&d, sizeof(double));
				d = m_Curves[k][w].GetY();
				f.Write(&d, sizeof(double));
			}
		}

		M_GETEDIT(IDC_EDIT_CURROFFFAN)->GetWindowText(s);
		wTemp=atoi(s);
		wTemp&=0xFFF;
		f.Write(&wTemp,2);

		M_GETEDIT(IDC_EDIT_CURRONFAN_LO)->GetWindowText(s);
		wTemp=atoi(s);
		wTemp&=0xFFF;
		f.Write(&wTemp,2);
	
		M_GETEDIT(IDC_EDIT_CURRONFAN_HI)->GetWindowText(s);
		wTemp=atoi(s);
		wTemp&=0xFFF;
		f.Write(&wTemp,2);

		f.Close();
	}
	catch(...)
	{
		STTE_Message("File error.",MB_ICONSTOP);
		return;
	}

	STTE_Message("File correctly saved.",MB_ICONINFORMATION);
}


// -----------------------------------------------------------------------------------
//	GenerateMIF
// -----------------------------------------------------------------------------------

BOOL CMMDlg::GenerateMIF()
{
	CFMT_File		f;
	DWORD			k;
	CString			s;

	if (!f.Open("flashmem_tool.mif", CFMT_File::e_OpenMode_Overwrite | CFMT_File::e_OpenMode_Write))
	{
		return FALSE;
	}


	try
	{
		// Header -------------------------------------------

		f.WriteTextLine("DEPTH = 262144;");
		f.WriteTextLine("WIDTH = 8;");
		f.WriteTextLine("ADDRESS_RADIX = HEX;");
		f.WriteTextLine("DATA_RADIX = HEX;");
		f.WriteTextLine(" ");
		f.WriteTextLine("CONTENT");
		f.WriteTextLine(" ");
		f.WriteTextLine("BEGIN");
		f.WriteTextLine(" ");

		for (k=0;k<DHA5X5_MEMORYSIZE;k++)
		{
			s.Format("%05x: %02x;",k,m_pbtMemory[k]);
			f.WriteTextLine(s);
		}

		DWORD dw1,dw2;

		dw1=DHA5X5_MEMORYSIZE;
		dw2=262143;

		s.Format("[%05x..%05x]: 00;",dw1,dw2);
		f.WriteTextLine(s);

		f.WriteTextLine(" ");
		f.WriteTextLine("END");

		f.Close();
	}
	catch(...)
	{
		return FALSE;
	}
	//END_CATCH

	return TRUE;
}

// -----------------------------------------------------------------------------------
//	OnFileImportfull
// -----------------------------------------------------------------------------------

void CMMDlg::OnFileImportfull()
{
	CString	sPath;

	CFileDialog *pDlg=new CFileDialog(TRUE,"txt",NULL,OFN_HIDEREADONLY,
		"Text Files (*.txt) | *.txt|",this);
	
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
}


// -----------------------------------------------------------------------------------
//	OnCbnSelendokComboSpeed
// -----------------------------------------------------------------------------------

void CMMDlg::OnCbnSelendokComboSpeed()
{
	m_pDev->m_ucSpiSpeed = (BYTE)(M_GETCOMBO(IDC_COMBO_SPEED)->GetCurSel());
}


// -----------------------------------------------------------------------------------
//	OnBnClickedButRead
// -----------------------------------------------------------------------------------

void CMMDlg::OnBnClickedButRead()
{
	CFileDialog *pDlg = new CFileDialog(FALSE, "bin", NULL, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
		"Binary Files (*.bin) | *.bin|", this);
	
	if (pDlg->DoModal()==IDOK)
	{
		m_sReadFilePath = pDlg->GetPathName();

		delete pDlg;
	}
	else
	{
		delete pDlg;
		return;
	}

	SetTimer(0,100,NULL);
	SetProgProgress(0);

	CString		s;

	s = "Reading Flash Memory...";
	UpdateStatus(s, e_Status_Programming);

	// Lancio il thread
	m_dwThreadReturn = 0;

	m_pThread = AfxBeginThread(ReadThread, this);
}


// -----------------------------------------------------------------------------------
//	ReadThread
// -----------------------------------------------------------------------------------

UINT CMMDlg::ReadThread(LPVOID pParam) 
{
	t_FMT_Uint32				uiRet;
	DWORD						dwAdd;
	DWORD						dwTot;
	DWORD						k,w;
	t_FMT_Uint8					*pbtTxBuf;
	t_FMT_Uint8					*pbtRxBuf;
	CString						s;
	CFMT_File					f;

	pbtTxBuf = new BYTE[MEMPROG_BYTE_PER_PAGE + 4];
	pbtRxBuf = new BYTE[DHA5X5_MEMORYSIZE];

	CMMDlg *pMe = (CMMDlg*)pParam;

	uiRet = pMe->m_pDev->ConnectSpi();

	if (uiRet != e_Return_OK)
	{
		pMe->m_dwThreadReturn = 1;
		::PostMessage(pMe->m_hWnd, MEMORYPROGDLG_ERRORMESS, e_Ret_ConnectErr, 0);
		goto l_Return;
	}

	// === Read operation ==============================

	dwAdd = 0;
	dwTot = 0;

	for (k=0; k < MEMPROG_NUM_PAGES / MEMPROG_PAGE_PER_CYCLE; k++)
	{
		// --- Read Page --------

		pbtTxBuf[0] = 0x03;

		for (w=0; w < MEMPROG_PAGE_PER_CYCLE; w++)
		{
			pbtTxBuf[1] = (BYTE)(dwAdd >> 16);
			pbtTxBuf[2] = (BYTE)(dwAdd >> 8);
			pbtTxBuf[3] = (BYTE)(dwAdd);

			uiRet = pMe->m_pDev->PerformSpiTransfer(pbtTxBuf, 4, pbtRxBuf + dwAdd, MEMPROG_BYTE_PER_PAGE, pMe->m_pDev->m_ucSpiSpeed, 500);

			if (uiRet != e_Return_OK)
			{
				pMe->m_dwThreadReturn = 1;
				::PostMessage(pMe->m_hWnd, MEMORYPROGDLG_ERRORMESS, e_Ret_CommErr, 0);

				goto l_Return;
			}
			dwAdd += MEMPROG_BYTE_PER_PAGE;
			dwTot += MEMPROG_BYTE_PER_PAGE;
		}

		::PostMessage(pMe->m_hWnd,
			MEMORYPROGDLG_PROGMESS, 0, 
			(LONG)((double)(dwTot) * 10000.0 / (double)DHA5X5_MEMORYSIZE));
	}

	f.Open((CFMT_String)(pMe->m_sReadFilePath), CFMT_File::e_OpenMode_Overwrite | CFMT_File::e_OpenMode_Write);
	f.Write(pbtRxBuf, DHA5X5_MEMORYSIZE);
	f.Close();

	::PostMessage(pMe->m_hWnd, MEMORYPROGDLG_ENDMESS, 2, 0);

	pMe->m_dwThreadReturn = 0;


l_Return:

	delete[] pbtTxBuf;
	delete[] pbtRxBuf;
	pMe->m_pDev->DisconnectSpi();

	return 0;
}
