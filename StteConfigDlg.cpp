// StteConfigDlg.cpp : implementation file
//

#include "stdafx.h"
#include "dha5x5_STTE.h"
#include "StteConfigDlg.h"
#include "Dha5x5_STTEDlg.h"
#include "ComDlg.h"

// CStteConfigDlg dialog

IMPLEMENT_DYNAMIC(CStteConfigDlg, CDialog)

// *************************************************************************************
// *************************************************************************************
//	Class CStteConfigDlg
// *************************************************************************************
// *************************************************************************************

// -----------------------------------------------------------------------------------
//	CStteConfigDlg::CStteConfigDlg
// -----------------------------------------------------------------------------------

CStteConfigDlg::CStteConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStteConfigDlg::IDD, pParent)
{

}


// -----------------------------------------------------------------------------------
//	CStteConfigDlg::~CStteConfigDlg
// -----------------------------------------------------------------------------------

CStteConfigDlg::~CStteConfigDlg()
{
}


// -----------------------------------------------------------------------------------
//	CStteConfigDlg Message Map
// -----------------------------------------------------------------------------------

BEGIN_MESSAGE_MAP(CStteConfigDlg, CDialog)
	ON_STN_CLICKED(IDC_STATIC_COM, &CStteConfigDlg::OnStnClickedStaticCom)
	ON_BN_CLICKED(IDC_BUT_SET_IP, &CStteConfigDlg::OnBnClickedButSetIp)
	ON_BN_CLICKED(IDC_BUT_SET_SN, &CStteConfigDlg::OnBnClickedButSetSn)
END_MESSAGE_MAP()


// -----------------------------------------------------------------------------------
//	CStteConfigDlg::OnInitDialog
// -----------------------------------------------------------------------------------

BOOL CStteConfigDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here

	m_ssCom.SubclassDlgItem(IDC_STATIC_COM, this);

	M_GETIPADDCTRL(IDC_IPADD_STTE)->SetAddress(192,168,1,65);

	RefreshPort();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


// -----------------------------------------------------------------------------------
//	CStteConfigDlg::OnStnClickedStaticCom
// -----------------------------------------------------------------------------------

void CStteConfigDlg::OnStnClickedStaticCom()
{
	CComDlg		d;

	d.m_sCOM = m_pDev->m_sStteUartPort;
	d.m_pHdwManager = &(m_pDev->m_HdwManager);
	
	if (d.DoModal() == IDOK)
	{
		m_pDev->m_sStteUartPort = d.m_sCOM;
		m_pDev->SaveSettings();
		RefreshPort();
	}
}


// -----------------------------------------------------------------------------------
//	CStteConfigDlg::OnOK
// -----------------------------------------------------------------------------------

void CStteConfigDlg::OnOK()
{
}


// -----------------------------------------------------------------------------------
//	CStteConfigDlg::RefreshPort
// -----------------------------------------------------------------------------------

void CStteConfigDlg::RefreshPort()
{
	CString		s;

	if (m_pDev->m_sStteUartPort.GetLength() > 0)
	{
		s = m_pDev->m_sStteUartPort.GetStringC();
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
//	CStteConfigDlg::OnBnClickedButSetIp
// -----------------------------------------------------------------------------------

void CStteConfigDlg::OnBnClickedButSetIp()
{
	DWORD	ret;
	BYTE	pbtNum[4];
	CString	sIp;
	CString	s;


	M_GETIPADDCTRL(IDC_IPADD_STTE)->GetAddress(pbtNum[0],pbtNum[1],pbtNum[2],pbtNum[3]);
	sIp.Format("%d.%d.%d.%d", pbtNum[0], pbtNum[1], pbtNum[2], pbtNum[3]);

	s = "Confirm new IP = " + sIp + "?";

	if (STTE_Message(s, MB_ICONQUESTION | MB_YESNO) != IDYES)
	{
		return;
	}

	ret = m_pDev->ProgramIp(pbtNum);

	if (ret == e_Return_OK)
	{
		STTE_Message("IP correctly programmed.", MB_ICONINFORMATION);
	}
	else
	{
		STTE_Message("Hardware communication error.", MB_ICONSTOP);
	}
}


// -----------------------------------------------------------------------------------
//	CStteConfigDlg::OnBnClickedButSetSn
// -----------------------------------------------------------------------------------

void CStteConfigDlg::OnBnClickedButSetSn()
{
	DWORD		ret;
	DWORD		dwTemp;
	CString		s;

	M_GETEDIT(IDC_EDIT_SN)->GetWindowText(s);

	dwTemp = (DWORD)atoi(s);

	if ((dwTemp > 255) || (dwTemp == 0))
	{
		STTE_Message("Invalid S/N", MB_ICONSTOP);
		return;
	}

	s.Format("Confirm new S/N = %d?", dwTemp);

	if (STTE_Message(s, MB_ICONQUESTION | MB_YESNO) != IDYES)
	{
		return;
	}

	ret = m_pDev->ProgramSn((BYTE)dwTemp);

	if (ret == e_Return_OK)
	{
		STTE_Message("S/N correctly programmed.", MB_ICONINFORMATION);
	}
	else if (ret == e_Return_HardwareError)
	{
		STTE_Message("Hardware communication error.", MB_ICONSTOP);
	}
	else if (ret == e_Return_DeviceError)
	{
		STTE_Message("Hardware communication error.", MB_ICONSTOP);
	}
	else
	{
		STTE_Message("Memory programming error.", MB_ICONSTOP);
	}
}

