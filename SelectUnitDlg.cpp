// SelectUnitDlg.cpp : implementation file
//

#include "stdafx.h"
#include "dha5x5_STTE.h"
#include "SelectUnitDlg.h"
#include "dha5x5_STTEDlg.h"


// CSelectUnitDlg dialog

IMPLEMENT_DYNAMIC(CSelectUnitDlg, CDialog)

CSelectUnitDlg::CSelectUnitDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSelectUnitDlg::IDD, pParent)
{

}

CSelectUnitDlg::~CSelectUnitDlg()
{
}

void CSelectUnitDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSelectUnitDlg, CDialog)
	ON_BN_CLICKED(IDC_BUT_UNIT1, &CSelectUnitDlg::OnBnClickedButUnit1)
	ON_BN_CLICKED(IDC_BUT_UNIT2, &CSelectUnitDlg::OnBnClickedButUnit2)
END_MESSAGE_MAP()


// CSelectUnitDlg message handlers

void CSelectUnitDlg::OnBnClickedButUnit1()
{
	CDha5x5_STTEDlg			d;

	d.m_dwUnitRev = 1;
	d.DoModal();
}

void CSelectUnitDlg::OnBnClickedButUnit2()
{
	CDha5x5_STTEDlg			d;

	d.m_dwUnitRev = 2;
	d.DoModal();
}
