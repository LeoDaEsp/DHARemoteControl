#pragma once

#include "DhaStteDevice.h"

// CMaintDlg dialog

class CMaintDlg : public CDialog
{
	DECLARE_DYNAMIC(CMaintDlg)

public:

	WORD	m_wPWM[4];
	WORD	m_wVDC[4];
	WORD	m_wAIN[11];
	//WORD	m_wPWMFeed[6];
	BYTE	m_btCycle;
	DWORD	m_dwRet;

	BOOL	m_bPWM[4];
	BOOL	m_bVDC[4];

	CMaintDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMaintDlg();

	CDhaStteDevice	*m_pDev;
	BYTE			m_btMaintReg;

// Dialog Data
	enum { IDD = IDD_MAINT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
	virtual void OnCancel();
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnEnChangeEditPwm1();
	afx_msg void OnEnChangeEditPwm2();
	afx_msg void OnEnChangeEditPwm3();
	afx_msg void OnEnChangeEditPwm4();
	afx_msg void OnEnChangeEditVdc1();
	afx_msg void OnEnChangeEditVdc2();
	afx_msg void OnEnChangeEditVdc3();
	afx_msg void OnEnChangeEditVdc4();
	afx_msg void OnBnClickedCheckHeater();
	afx_msg void OnDeltaposSpinPwm1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinPwm2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinPwm3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinPwm4(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinVdc1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinVdc2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinVdc3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinVdc4(NMHDR *pNMHDR, LRESULT *pResult);
};
