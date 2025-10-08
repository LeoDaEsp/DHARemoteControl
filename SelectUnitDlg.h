#pragma once

// CSelectUnitDlg dialog

class CSelectUnitDlg : public CDialog
{
	DECLARE_DYNAMIC(CSelectUnitDlg)

public:
	CSelectUnitDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSelectUnitDlg();

// Dialog Data
	enum { IDD = IDD_UNIT_SEL_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButUnit1();
	afx_msg void OnBnClickedButUnit2();
};
