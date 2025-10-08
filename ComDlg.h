#pragma once

// CComDlg dialog

class CComDlg : public CDialog
{
	DECLARE_DYNAMIC(CComDlg)

public:
	CComDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CComDlg();

// Dialog Data
	enum { IDD = IDD_COM_DLG };

	CFMT_HdwManager						*m_pHdwManager;
	CFMT_HdwManager::CPortInfoVector	m_UartList;
	CFMT_String							m_sCOM;

	void PopulateList();
	void RefreshPortList();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
	virtual void OnCancel();
public:
	afx_msg void OnBnClickedButRescan();
	afx_msg void OnNMDblclkListComs(NMHDR *pNMHDR, LRESULT *pResult);
};
