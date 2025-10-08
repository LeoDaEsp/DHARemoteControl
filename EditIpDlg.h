#pragma once


// CEditIpDlg dialog

class CEditIpDlg : public CDialog
{
	DECLARE_DYNAMIC(CEditIpDlg)

public:
	CEditIpDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CEditIpDlg();

	CString		m_sIpAddress;

// Dialog Data
	enum { IDD = IDD_EDIT_IP_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
};
