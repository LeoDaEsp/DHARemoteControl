// MaintDlg.cpp : implementation file
//

#include "stdafx.h"
#include "dha5x5_STTE.h"
#include "MaintDlg.h"


// CMaintDlg dialog

IMPLEMENT_DYNAMIC(CMaintDlg, CDialog)

CMaintDlg::CMaintDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMaintDlg::IDD, pParent)
{
	m_btMaintReg=0;

	DWORD	k;

	m_btCycle=0;

	for (k=0;k<4;k++)
	{
		m_wPWM[k]=0;
		m_wVDC[k]=0;
	}

	for (k=0;k<11;k++)
	{
		m_wAIN[k]=0;
	}

	/*for (k=0;k<6;k++)
	{
		m_wPWMFeed[k]=0;
	}
	*/

	for (k=0;k<4;k++)
	{
		m_bPWM[k]=TRUE;
		m_bVDC[k]=TRUE;
	}


	m_dwRet = e_Return_OK;
}


CMaintDlg::~CMaintDlg()
{
}

void CMaintDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMaintDlg, CDialog)
	ON_WM_TIMER()
	ON_EN_CHANGE(IDC_EDIT_PWM1, &CMaintDlg::OnEnChangeEditPwm1)
	ON_EN_CHANGE(IDC_EDIT_PWM2, &CMaintDlg::OnEnChangeEditPwm2)
	ON_EN_CHANGE(IDC_EDIT_PWM3, &CMaintDlg::OnEnChangeEditPwm3)
	ON_EN_CHANGE(IDC_EDIT_PWM4, &CMaintDlg::OnEnChangeEditPwm4)
	ON_EN_CHANGE(IDC_EDIT_VDC1, &CMaintDlg::OnEnChangeEditVdc1)
	ON_EN_CHANGE(IDC_EDIT_VDC2, &CMaintDlg::OnEnChangeEditVdc2)
	ON_EN_CHANGE(IDC_EDIT_VDC3, &CMaintDlg::OnEnChangeEditVdc3)
	ON_EN_CHANGE(IDC_EDIT_VDC4, &CMaintDlg::OnEnChangeEditVdc4)
	ON_BN_CLICKED(IDC_CHECK_HEATER, &CMaintDlg::OnBnClickedCheckHeater)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_PWM1, &CMaintDlg::OnDeltaposSpinPwm1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_PWM2, &CMaintDlg::OnDeltaposSpinPwm2)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_PWM3, &CMaintDlg::OnDeltaposSpinPwm3)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_PWM4, &CMaintDlg::OnDeltaposSpinPwm4)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_VDC1, &CMaintDlg::OnDeltaposSpinVdc1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_VDC2, &CMaintDlg::OnDeltaposSpinVdc2)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_VDC3, &CMaintDlg::OnDeltaposSpinVdc3)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_VDC4, &CMaintDlg::OnDeltaposSpinVdc4)
END_MESSAGE_MAP()


// CMaintDlg message handlers

BOOL CMaintDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	M_GETLISTCTRL(IDC_LIST_ANALOGS)->SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	M_GETLISTCTRL(IDC_LIST_ANALOGS)->InsertColumn(0,"Signal",LVCFMT_LEFT,130);
	M_GETLISTCTRL(IDC_LIST_ANALOGS)->InsertColumn(1,"Value",LVCFMT_LEFT,70);

	M_GETLISTCTRL(IDC_LIST_ANALOGS)->InsertItem(0,"Fan Current Sense");
	M_GETLISTCTRL(IDC_LIST_ANALOGS)->InsertItem(1,"Heater Current Sense");
	M_GETLISTCTRL(IDC_LIST_ANALOGS)->InsertItem(2,"Heater Temperature");
	M_GETLISTCTRL(IDC_LIST_ANALOGS)->InsertItem(3,"VOUT_NW");
	M_GETLISTCTRL(IDC_LIST_ANALOGS)->InsertItem(4,"VOUT_DW");
	M_GETLISTCTRL(IDC_LIST_ANALOGS)->InsertItem(5,"Int.Board Temperature");
	M_GETLISTCTRL(IDC_LIST_ANALOGS)->InsertItem(6,"Ctrl.Board Temperature");
	M_GETLISTCTRL(IDC_LIST_ANALOGS)->InsertItem(7,"Backlight Temperature");

	M_GETLISTCTRL(IDC_LIST_ANALOGS)->InsertItem(8,"PWM White Day #1");
	M_GETLISTCTRL(IDC_LIST_ANALOGS)->InsertItem(9,"PWM White Day #2");
	M_GETLISTCTRL(IDC_LIST_ANALOGS)->InsertItem(10,"PWM White Nvg #1");
	M_GETLISTCTRL(IDC_LIST_ANALOGS)->InsertItem(11,"PWM White Nvg #2");
	M_GETLISTCTRL(IDC_LIST_ANALOGS)->InsertItem(12,"PWM Red Nvg #1");
	M_GETLISTCTRL(IDC_LIST_ANALOGS)->InsertItem(13,"PWM Red Nvg #2");

	M_GETLISTCTRL(IDC_LIST_ANALOGS)->InsertItem(14,"VOUT_NR");
	M_GETLISTCTRL(IDC_LIST_ANALOGS)->InsertItem(15,"VFIN_DW1");
	M_GETLISTCTRL(IDC_LIST_ANALOGS)->InsertItem(16,"VFIN_DW2");

	M_GETEDIT(IDC_EDIT_PWM1)->SetLimitText(4);
	M_GETEDIT(IDC_EDIT_PWM1)->SetWindowText("0");
	M_GETEDIT(IDC_EDIT_PWM2)->SetLimitText(4);
	M_GETEDIT(IDC_EDIT_PWM2)->SetWindowText("0");
	M_GETEDIT(IDC_EDIT_PWM3)->SetLimitText(4);
	M_GETEDIT(IDC_EDIT_PWM3)->SetWindowText("0");
	M_GETEDIT(IDC_EDIT_PWM4)->SetLimitText(4);
	M_GETEDIT(IDC_EDIT_PWM4)->SetWindowText("0");
	M_GETEDIT(IDC_EDIT_VDC1)->SetLimitText(4);
	M_GETEDIT(IDC_EDIT_VDC1)->SetWindowText("0");
	M_GETEDIT(IDC_EDIT_VDC2)->SetLimitText(4);
	M_GETEDIT(IDC_EDIT_VDC2)->SetWindowText("0");
	M_GETEDIT(IDC_EDIT_VDC3)->SetLimitText(4);
	M_GETEDIT(IDC_EDIT_VDC3)->SetWindowText("0");
	M_GETEDIT(IDC_EDIT_VDC4)->SetLimitText(4);
	M_GETEDIT(IDC_EDIT_VDC4)->SetWindowText("0");

	m_btCycle=0;
	SetTimer(DHA55_MAINTTIMER_ID,DHA55_MAINTTIMER_TIMEOUT,NULL);
	SetTimer(DHA55_REFRESHTIMER_ID,DHA55_REFRESHTIMER_TIMEOUT,NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CMaintDlg::OnOK()
{
	KillTimer(DHA55_MAINTTIMER_ID);
	KillTimer(DHA55_REFRESHTIMER_ID);

	CDialog::OnOK();
}

void CMaintDlg::OnCancel()
{
	KillTimer(DHA55_MAINTTIMER_ID);
	KillTimer(DHA55_REFRESHTIMER_ID);

	m_pDev->SetMaintReg(0, DHA55_TIMEOUTECHO);

	CDialog::OnCancel();
}

void CMaintDlg::OnTimer(UINT_PTR nIDEvent)
{
	CString		s;
	DWORD		k;
	DWORD		dwRet;

	if (nIDEvent==DHA55_REFRESHTIMER_ID)
	{

		for (k=0;k<2;k++)
		{
			s.Format("%d",m_wAIN[k]>>8);
			M_GETLISTCTRL(IDC_LIST_ANALOGS)->SetItemText(k,1,s);
		}

		for (k=2;k<5;k++)
		{
			s.Format("%d",m_wAIN[k]>>4);
			M_GETLISTCTRL(IDC_LIST_ANALOGS)->SetItemText(k,1,s);
		}

		for (k=5;k<7;k++)
		{
			s.Format("%d",m_wAIN[k]);
			M_GETLISTCTRL(IDC_LIST_ANALOGS)->SetItemText(k,1,s);
		}

		/*char	ch;
		BYTE	btTemp;

		btTemp=(BYTE)(m_wAIN[7]>>4);
		ch=*((char*)(&btTemp));
		s.Format("%d°C",ch);
		M_GETLISTCTRL(IDC_LIST_ANALOGS)->SetItemText(7,1,s);

		for (k=0;k<6;k++)
		{
			s.Format("%d",m_wPWMFeed[k]);
			M_GETLISTCTRL(IDC_LIST_ANALOGS)->SetItemText(k+8,1,s);
		}

		for (k=0;k<3;k++)
		{
			s.Format("%d",m_wAIN[k+8]>>4);
			M_GETLISTCTRL(IDC_LIST_ANALOGS)->SetItemText(k+14,1,s);
		}
		*/
	}
	else
	{
		dwRet = e_Return_OK;

		for (k=0;k<4;k++)
		{
			if (m_bPWM[k])
			{
				m_bPWM[k]=FALSE;

				dwRet = m_pDev->SetPWM(k, m_wPWM[k], DHA55_TIMEOUTECHO);
				
				if (dwRet != e_Return_OK)
				{
					m_dwRet = dwRet;
					OnCancel();
				}
			}
		}

		for (k=0;k<4;k++)
		{
			if (m_bVDC[k])
			{
				m_bVDC[k]=FALSE;

				dwRet = m_pDev->SetVDC(k, m_wVDC[k], DHA55_TIMEOUTECHO);
				if (dwRet != e_Return_OK)
				{
					m_dwRet = dwRet;
					OnCancel();
				}
			}
		}

		//dwRet = m_pDev->ReadAnalogs(m_wAIN, m_wPWMFeed, DHA55_TIMEOUTECHO);
		dwRet = m_pDev->ReadAnalogs(m_wAIN, DHA55_TIMEOUTECHO);
		if (dwRet != e_Return_OK)
		{
			m_dwRet = dwRet;
			OnCancel();
		}

	}

	CDialog::OnTimer(nIDEvent);
}

void CMaintDlg::OnEnChangeEditPwm1()
{
	CString		s;

	M_GETEDIT(IDC_EDIT_PWM1)->GetWindowText(s);
	m_wPWM[0]=atoi(s);

	m_bPWM[0]=TRUE;
}

void CMaintDlg::OnEnChangeEditPwm2()
{
	CString		s;

	M_GETEDIT(IDC_EDIT_PWM2)->GetWindowText(s);
	m_wPWM[1]=atoi(s);

	m_bPWM[1]=TRUE;
}

void CMaintDlg::OnEnChangeEditPwm3()
{
	CString		s;

	M_GETEDIT(IDC_EDIT_PWM3)->GetWindowText(s);
	m_wPWM[2]=atoi(s);

	m_bPWM[2]=TRUE;
}

void CMaintDlg::OnEnChangeEditPwm4()
{
	CString		s;

	M_GETEDIT(IDC_EDIT_PWM4)->GetWindowText(s);
	m_wPWM[3]=atoi(s);

	m_bPWM[3]=TRUE;
}

void CMaintDlg::OnEnChangeEditVdc1()
{
	CString		s;

	M_GETEDIT(IDC_EDIT_VDC1)->GetWindowText(s);
	m_wVDC[0]=atoi(s);

	m_bVDC[0]=TRUE;
}

void CMaintDlg::OnEnChangeEditVdc2()
{
	CString		s;

	M_GETEDIT(IDC_EDIT_VDC2)->GetWindowText(s);
	m_wVDC[1]=atoi(s);

	m_bVDC[1]=TRUE;
}

void CMaintDlg::OnEnChangeEditVdc3()
{
	CString		s;

	M_GETEDIT(IDC_EDIT_VDC3)->GetWindowText(s);
	m_wVDC[2]=atoi(s);

	m_bVDC[2]=TRUE;
}

void CMaintDlg::OnEnChangeEditVdc4()
{
	CString		s;

	M_GETEDIT(IDC_EDIT_VDC4)->GetWindowText(s);
	m_wVDC[3]=atoi(s);

	m_bVDC[3]=TRUE;
}

void CMaintDlg::OnBnClickedCheckHeater()
{
	/*
	DWORD	dwRet;

	if (M_GETBUTTON(IDC_CHECK_HEATER)->GetCheck())
	{
		m_btMaintReg|=0x01;
	}
	else
	{
		m_btMaintReg&=0xFE;
	}

	dwRet=m_pDevice->SetMaintReg(m_btMaintReg,DHA55_TIMEOUTECHO);
	if (dwRet!=CDhaStteDevice::e_Ret_OK)
	{
		m_dwRet=dwRet;
		OnCancel();
	}
	*/
}

void CMaintDlg::OnDeltaposSpinPwm1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	CString	s;

	if (pNMUpDown->iDelta<0)
	{
		if (pNMUpDown->iDelta>-5)
		{
			if (m_wPWM[0]<4095)
				m_wPWM[0]++;
			else m_wPWM[0]=4095;
		}
		else if (pNMUpDown->iDelta>-20)
		{
			if (m_wPWM[0]<4095-10)
				m_wPWM[0]+=10;
			else m_wPWM[0]=4095;
		}
		else 
		{
			if (m_wPWM[0]<4095-100)
				m_wPWM[0]+=100;
			else m_wPWM[0]=4095;
		}
	}
	else if (pNMUpDown->iDelta>0)
	{
		if (pNMUpDown->iDelta<5)
		{
			if (m_wPWM[0]>1)
				m_wPWM[0]--;
			else m_wPWM[0]=0;
		}
		else if (pNMUpDown->iDelta<20)
		{
			if (m_wPWM[0]>10)
				m_wPWM[0]-=10;
			else m_wPWM[0]=0;
		}
		else 
		{
			if (m_wPWM[0]>100)
				m_wPWM[0]-=100;
			else m_wPWM[0]=0;
		}

	}

	s.Format("%d",m_wPWM[0]);
	M_GETEDIT(IDC_EDIT_PWM1)->SetWindowText(s);

	m_bPWM[0]=TRUE;

	*pResult = 0;
}

void CMaintDlg::OnDeltaposSpinPwm2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	CString	s;

	if (pNMUpDown->iDelta<0)
	{
		if (pNMUpDown->iDelta>-5)
		{
			if (m_wPWM[1]<4095)
				m_wPWM[1]++;
			else m_wPWM[1]=4095;
		}
		else if (pNMUpDown->iDelta>-20)
		{
			if (m_wPWM[1]<4095-10)
				m_wPWM[1]+=10;
			else m_wPWM[1]=4095;
		}
		else 
		{
			if (m_wPWM[1]<4095-100)
				m_wPWM[1]+=100;
			else m_wPWM[1]=4095;
		}
	}
	else if (pNMUpDown->iDelta>0)
	{
		if (pNMUpDown->iDelta<5)
		{
			if (m_wPWM[1]>1)
				m_wPWM[1]--;
			else m_wPWM[1]=0;
		}
		else if (pNMUpDown->iDelta<20)
		{
			if (m_wPWM[1]>10)
				m_wPWM[1]-=10;
			else m_wPWM[1]=0;
		}
		else 
		{
			if (m_wPWM[1]>100)
				m_wPWM[1]-=100;
			else m_wPWM[1]=0;
		}

	}

	s.Format("%d",m_wPWM[1]);
	M_GETEDIT(IDC_EDIT_PWM2)->SetWindowText(s);

	m_bPWM[1]=TRUE;

	*pResult = 0;
}

void CMaintDlg::OnDeltaposSpinPwm3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	CString	s;

	if (pNMUpDown->iDelta<0)
	{
		if (pNMUpDown->iDelta>-5)
		{
			if (m_wPWM[2]<4095)
				m_wPWM[2]++;
			else m_wPWM[2]=4095;
		}
		else if (pNMUpDown->iDelta>-20)
		{
			if (m_wPWM[2]<4095-10)
				m_wPWM[2]+=10;
			else m_wPWM[2]=4095;
		}
		else 
		{
			if (m_wPWM[2]<4095-100)
				m_wPWM[2]+=100;
			else m_wPWM[2]=4095;
		}
	}
	else if (pNMUpDown->iDelta>0)
	{
		if (pNMUpDown->iDelta<5)
		{
			if (m_wPWM[2]>1)
				m_wPWM[2]--;
			else m_wPWM[2]=0;
		}
		else if (pNMUpDown->iDelta<20)
		{
			if (m_wPWM[2]>10)
				m_wPWM[2]-=10;
			else m_wPWM[2]=0;
		}
		else 
		{
			if (m_wPWM[2]>100)
				m_wPWM[2]-=100;
			else m_wPWM[2]=0;
		}

	}

	s.Format("%d",m_wPWM[2]);
	M_GETEDIT(IDC_EDIT_PWM3)->SetWindowText(s);

	m_bPWM[2]=TRUE;

	*pResult = 0;
}

void CMaintDlg::OnDeltaposSpinPwm4(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	CString	s;

	if (pNMUpDown->iDelta<0)
	{
		if (pNMUpDown->iDelta>-5)
		{
			if (m_wPWM[3]<4095)
				m_wPWM[3]++;
			else m_wPWM[3]=4095;
		}
		else if (pNMUpDown->iDelta>-20)
		{
			if (m_wPWM[3]<4095-10)
				m_wPWM[3]+=10;
			else m_wPWM[3]=4095;
		}
		else 
		{
			if (m_wPWM[3]<4095-100)
				m_wPWM[3]+=100;
			else m_wPWM[3]=4095;
		}
	}
	else if (pNMUpDown->iDelta>0)
	{
		if (pNMUpDown->iDelta<5)
		{
			if (m_wPWM[3]>1)
				m_wPWM[3]--;
			else m_wPWM[3]=0;
		}
		else if (pNMUpDown->iDelta<20)
		{
			if (m_wPWM[3]>10)
				m_wPWM[3]-=10;
			else m_wPWM[3]=0;
		}
		else 
		{
			if (m_wPWM[3]>100)
				m_wPWM[3]-=100;
			else m_wPWM[3]=0;
		}

	}

	s.Format("%d",m_wPWM[3]);
	M_GETEDIT(IDC_EDIT_PWM4)->SetWindowText(s);

	m_bPWM[3]=TRUE;

	*pResult = 0;
}

void CMaintDlg::OnDeltaposSpinVdc1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	CString	s;

	if (pNMUpDown->iDelta<0)
	{
		if (pNMUpDown->iDelta>-5)
		{
			if (m_wVDC[0]<4095)
				m_wVDC[0]++;
			else m_wVDC[0]=4095;
		}
		else if (pNMUpDown->iDelta>-20)
		{
			if (m_wVDC[0]<4095-10)
				m_wVDC[0]+=10;
			else m_wVDC[0]=4095;
		}
		else 
		{
			if (m_wVDC[0]<4095-100)
				m_wVDC[0]+=100;
			else m_wVDC[0]=4095;
		}
	}
	else if (pNMUpDown->iDelta>0)
	{
		if (pNMUpDown->iDelta<5)
		{
			if (m_wVDC[0]>1)
				m_wVDC[0]--;
			else m_wVDC[0]=0;
		}
		else if (pNMUpDown->iDelta<20)
		{
			if (m_wVDC[0]>10)
				m_wVDC[0]-=10;
			else m_wVDC[0]=0;
		}
		else 
		{
			if (m_wVDC[0]>100)
				m_wVDC[0]-=100;
			else m_wVDC[0]=0;
		}

	}

	s.Format("%d",m_wVDC[0]);
	M_GETEDIT(IDC_EDIT_VDC1)->SetWindowText(s);

	m_bVDC[0]=TRUE;

	*pResult = 0;
}

void CMaintDlg::OnDeltaposSpinVdc2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	CString	s;

	if (pNMUpDown->iDelta<0)
	{
		if (pNMUpDown->iDelta>-5)
		{
			if (m_wVDC[1]<4095)
				m_wVDC[1]++;
			else m_wVDC[1]=4095;
		}
		else if (pNMUpDown->iDelta>-20)
		{
			if (m_wVDC[1]<4095-10)
				m_wVDC[1]+=10;
			else m_wVDC[1]=4095;
		}
		else 
		{
			if (m_wVDC[1]<4095-100)
				m_wVDC[1]+=100;
			else m_wVDC[1]=4095;
		}
	}
	else if (pNMUpDown->iDelta>0)
	{
		if (pNMUpDown->iDelta<5)
		{
			if (m_wVDC[1]>1)
				m_wVDC[1]--;
			else m_wVDC[1]=0;
		}
		else if (pNMUpDown->iDelta<20)
		{
			if (m_wVDC[1]>10)
				m_wVDC[1]-=10;
			else m_wVDC[1]=0;
		}
		else 
		{
			if (m_wVDC[1]>100)
				m_wVDC[1]-=100;
			else m_wVDC[1]=0;
		}

	}

	s.Format("%d",m_wVDC[1]);
	M_GETEDIT(IDC_EDIT_VDC2)->SetWindowText(s);

	m_bVDC[1]=TRUE;

	*pResult = 0;
}

void CMaintDlg::OnDeltaposSpinVdc3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	CString	s;

	if (pNMUpDown->iDelta<0)
	{
		if (pNMUpDown->iDelta>-5)
		{
			if (m_wVDC[2]<4095)
				m_wVDC[2]++;
			else m_wVDC[2]=4095;
		}
		else if (pNMUpDown->iDelta>-20)
		{
			if (m_wVDC[2]<4095-10)
				m_wVDC[2]+=10;
			else m_wVDC[2]=4095;
		}
		else 
		{
			if (m_wVDC[2]<4095-100)
				m_wVDC[2]+=100;
			else m_wVDC[2]=4095;
		}
	}
	else if (pNMUpDown->iDelta>0)
	{
		if (pNMUpDown->iDelta<5)
		{
			if (m_wVDC[2]>1)
				m_wVDC[2]--;
			else m_wVDC[2]=0;
		}
		else if (pNMUpDown->iDelta<20)
		{
			if (m_wVDC[2]>10)
				m_wVDC[2]-=10;
			else m_wVDC[2]=0;
		}
		else 
		{
			if (m_wVDC[2]>100)
				m_wVDC[2]-=100;
			else m_wVDC[2]=0;
		}

	}

	s.Format("%d",m_wVDC[2]);
	M_GETEDIT(IDC_EDIT_VDC3)->SetWindowText(s);

	m_bVDC[2]=TRUE;

	*pResult = 0;
}

void CMaintDlg::OnDeltaposSpinVdc4(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);


	CString	s;

	if (pNMUpDown->iDelta<0)
	{
		if (pNMUpDown->iDelta>-5)
		{
			if (m_wVDC[3]<4095)
				m_wVDC[3]++;
			else m_wVDC[3]=4095;
		}
		else if (pNMUpDown->iDelta>-20)
		{
			if (m_wVDC[3]<4095-10)
				m_wVDC[3]+=10;
			else m_wVDC[3]=4095;
		}
		else 
		{
			if (m_wVDC[3]<4095-100)
				m_wVDC[3]+=100;
			else m_wVDC[3]=4095;
		}
	}
	else if (pNMUpDown->iDelta>0)
	{
		if (pNMUpDown->iDelta<5)
		{
			if (m_wVDC[3]>1)
				m_wVDC[3]--;
			else m_wVDC[3]=0;
		}
		else if (pNMUpDown->iDelta<20)
		{
			if (m_wVDC[3]>10)
				m_wVDC[3]-=10;
			else m_wVDC[3]=0;
		}
		else 
		{
			if (m_wVDC[3]>100)
				m_wVDC[3]-=100;
			else m_wVDC[3]=0;
		}

	}

	s.Format("%d",m_wVDC[3]);
	M_GETEDIT(IDC_EDIT_VDC4)->SetWindowText(s);

	m_bVDC[3]=TRUE;


	*pResult = 0;
}
