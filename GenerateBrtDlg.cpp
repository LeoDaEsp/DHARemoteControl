// *************************************************************************************
// *************************************************************************************
//	Class CGenerateBrtDlg
// *************************************************************************************
// *************************************************************************************

#include "stdafx.h"
#include "dha5x5_STTE.h"
#include "GenerateBrtDlg.h"


// -----------------------------------------------------------------------------------
//	CGenerateBrtDlg::CGenerateBrtDlg
// -----------------------------------------------------------------------------------

IMPLEMENT_DYNAMIC(CGenerateBrtDlg, CDialog)

CGenerateBrtDlg::CGenerateBrtDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGenerateBrtDlg::IDD, pParent)
{
	m_wDutyMax = 65535;
}

// -----------------------------------------------------------------------------------
//	CGenerateBrtDlg::~CGenerateBrtDlg
// -----------------------------------------------------------------------------------

CGenerateBrtDlg::~CGenerateBrtDlg()
{
}

// -----------------------------------------------------------------------------------
//	CGenerateBrtDlg::DoDataExchange
// -----------------------------------------------------------------------------------

void CGenerateBrtDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


// -----------------------------------------------------------------------------------
//	CGenerateBrtDlg Message Map
// -----------------------------------------------------------------------------------

BEGIN_MESSAGE_MAP(CGenerateBrtDlg, CDialog)
END_MESSAGE_MAP()


// -----------------------------------------------------------------------------------
//	CGenerateBrtDlg::OnInitDialog
// -----------------------------------------------------------------------------------

BOOL CGenerateBrtDlg::OnInitDialog()
{
	CDialog::OnInitDialog();


	CString		s;

	s.Format("%d", m_wDutyMax);
	M_GETEDIT(IDC_EDIT_MAX_DUTY)->SetWindowText(s);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


// -----------------------------------------------------------------------------------
//	CGenerateBrtDlg::OnOK
// -----------------------------------------------------------------------------------

void CGenerateBrtDlg::OnOK()
{
	CString		s;

	M_GETEDIT(IDC_EDIT_MAX_DUTY)->GetWindowText(s);
	m_wDutyMax=atoi(s);

	if (m_wDutyMax > 65535)
	{
		STTE_Message("Duty max must be between 0 and 65535",MB_ICONSTOP,this);
		return;
	}


	CDialog::OnOK();
}
