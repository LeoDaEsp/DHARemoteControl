// ComDlg.cpp : implementation file
//

#include "stdafx.h"
#include "dha5x5_STTE.h"
#include "ComDlg.h"


// CComDlg dialog

IMPLEMENT_DYNAMIC(CComDlg, CDialog)

CComDlg::CComDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CComDlg::IDD, pParent)
{
}

CComDlg::~CComDlg()
{
}

void CComDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CComDlg, CDialog)
	ON_BN_CLICKED(IDC_BUT_RESCAN, &CComDlg::OnBnClickedButRescan)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_COMS, &CComDlg::OnNMDblclkListComs)
END_MESSAGE_MAP()


// CComDlg message handlers

BOOL CComDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	DWORD	k;
	int		idx;

	// --- Populate list -----------------------------------------------

	M_GETLISTCTRL(IDC_LIST_COMS)->SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	M_GETLISTCTRL(IDC_LIST_COMS)->InsertColumn(0,"Num.",LVCFMT_LEFT,50);
	M_GETLISTCTRL(IDC_LIST_COMS)->InsertColumn(1,"Description",LVCFMT_LEFT,250);
	M_GETLISTCTRL(IDC_LIST_COMS)->InsertColumn(2,"Manufacturer",LVCFMT_LEFT,160);

	// --- Get Port List -----------------------------------------------

	RefreshPortList();

	// --- Find Current COM --------------------------------------------

	idx=-1;
	for (k=0; k < !m_UartList; k++)
	{
		if (m_UartList[k].m_sIntChannel == m_sCOM)
		{
			idx = k;
		}
	}

	if (idx>=0)
	{
		M_GETLISTCTRL(IDC_LIST_COMS)->SetItemState(idx,LVIS_SELECTED,LVIS_SELECTED);
	}

	M_GETLISTCTRL(IDC_LIST_COMS)->SetFocus();


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CComDlg::RefreshPortList()
{
	m_pHdwManager->Enumerate();
	//m_pHdwManager->Init();
	m_pHdwManager->GetPortList(CFMT_HdwPort::e_PortType_Uart,m_UartList);
	PopulateList();
}

void CComDlg::PopulateList()
{
	DWORD		k;
	CString		s;

	M_GETLISTCTRL(IDC_LIST_COMS)->DeleteAllItems();

	for (k=0;k<!m_UartList;k++)
	{
		s = m_UartList[k].m_sIntChannel.GetStringC();
		M_GETLISTCTRL(IDC_LIST_COMS)->InsertItem(k,s);

		M_GETLISTCTRL(IDC_LIST_COMS)->SetItemText(k,1,m_UartList[k].m_sFullName.GetStringC());
		M_GETLISTCTRL(IDC_LIST_COMS)->SetItemText(k,2,m_UartList[k].m_sManufacturer.GetStringC());
	}

}

void CComDlg::OnOK()
{
	int			idx;
	POSITION	pos;

	pos=M_GETLISTCTRL(IDC_LIST_COMS)->GetFirstSelectedItemPosition();

	if (pos==NULL)
	{
		STTE_Message("No COM Port Selected", MB_ICONWARNING, this);
		return;
	}

	idx=M_GETLISTCTRL(IDC_LIST_COMS)->GetNextSelectedItem(pos);

	if (idx<0)
	{
		STTE_Message("No COM Port Selected", MB_ICONWARNING, this);
		return;
	}

	m_sCOM = m_UartList[idx].m_sIntChannel;

	CDialog::OnOK();
}

void CComDlg::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialog::OnCancel();
}


void CComDlg::OnBnClickedButRescan()
{
	//m_pHdwManager->Init();
	m_pHdwManager->Enumerate();
	m_pHdwManager->GetPortList(CFMT_HdwPort::e_PortType_Uart,m_UartList);
	PopulateList();
}

void CComDlg::OnNMDblclkListComs(NMHDR *pNMHDR, LRESULT *pResult)
{
	CComDlg::OnOK();

	*pResult = 0;
}
