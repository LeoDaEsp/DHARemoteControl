// EditIpDlg.cpp : implementation file
//

#include "stdafx.h"
#include "dha5x5_STTE.h"
#include "EditIpDlg.h"


// CEditIpDlg dialog

IMPLEMENT_DYNAMIC(CEditIpDlg, CDialog)

CEditIpDlg::CEditIpDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEditIpDlg::IDD, pParent)
{

}

CEditIpDlg::~CEditIpDlg()
{
}

void CEditIpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CEditIpDlg, CDialog)
END_MESSAGE_MAP()


// CEditIpDlg message handlers

BOOL CEditIpDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	BYTE		pbtNum[4];
	int			pos;
	CString		s;

	s=m_sIpAddress;

	pos=s.Find(".");
	pbtNum[0]=atoi(s.Left(pos));
	s=s.Right(s.GetLength()-pos-1);

	pos=s.Find(".");
	pbtNum[1]=atoi(s.Left(pos));
	s=s.Right(s.GetLength()-pos-1);

	pos=s.Find(".");
	pbtNum[2]=atoi(s.Left(pos));
	s=s.Right(s.GetLength()-pos-1);

	pbtNum[3]=atoi(s);

	M_GETIPADDCTRL(IDC_IPADDRESS)->SetAddress(pbtNum[0],pbtNum[1],pbtNum[2],pbtNum[3]);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CEditIpDlg::OnOK()
{
	BYTE		pbtNum[4];

	M_GETIPADDCTRL(IDC_IPADDRESS)->GetAddress(pbtNum[0],pbtNum[1],pbtNum[2],pbtNum[3]);

	m_sIpAddress.Format("%d.%d.%d.%d",pbtNum[0],pbtNum[1],pbtNum[2],pbtNum[3]);

	CDialog::OnOK();
}
