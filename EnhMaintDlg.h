#pragma once

#include "DhaStteDevice.h"
#include "CRemotePanel.h"

// *************************************************************************************
// *************************************************************************************
//	Class CEnhMaintDlg
// *************************************************************************************
// *************************************************************************************

class CEnhMaintDlg : public CDialog
{
	friend class CRemotePanel;
	DECLARE_DYNAMIC(CEnhMaintDlg)

	// =====================================================================================
	//	TYPES
	// =====================================================================================

protected:
public:

// Dialog Data
	enum { IDD = IDD_ENH_MAINT_DLG };

	// =====================================================================================
	//	VARIABLES
	// =====================================================================================

protected:
public:

	CDhaStteDevice			*m_pDev;
	
	CSmartStatic			m_ssCom;
	CSmartStatic			m_ssEti;
	CSmartStatic			m_ssHtrStatus;
	CSmartStatic			m_pssPatCol[2];
	CSmartStatic			m_pssPatRgb[2];

	CStatusListCtrl			m_slAnalogs;
	CStatusListCtrl			m_slBit;

	BOOL					m_bReboot;

	// =====================================================================================
	// CONSTRUCTORS & DESTRUCTORS
	// =====================================================================================

public:
	CEnhMaintDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CEnhMaintDlg();

	// =====================================================================================
	//	FUNCTIONS
	// =====================================================================================

public:

	void	RefreshPort();
	BOOL	MaintTimerActions();
	void	RefreshAnalogs();
	void	RefreshBIT();
	void	RefreshETI();
	void	RefreshHeater();
	void	RefreshData();
	void	RefreshPatColor(BYTE btIdx);
	void	EnableControls(BOOL bEnable);

protected:


	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
	virtual void OnCancel();
public:
	afx_msg void OnStnClickedStaticCom2();
	afx_msg void OnBnClickedCheckConnect();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnCbnSelendokComboPot();
	afx_msg void OnCbnSelendokComboMntOpBrt();
	afx_msg void OnEnChangeEditDuty();
	afx_msg void OnEnChangeEditCurrent();
	afx_msg void OnBnClickedCheckDay();
	afx_msg void OnBnClickedOperBrtMode();
	afx_msg void OnBnClickedCheckHeater();
	afx_msg void OnBnClickedCheckHtrEnable();

	afx_msg void OnStnClickedStaticPatCol1();
	afx_msg void OnStnClickedStaticPatCol2();
	afx_msg void OnStnClickedStaticPatRgb1();
	afx_msg void OnStnClickedStaticPatRgb2();
	afx_msg void OnCbnSelendokComboVideoPattern();

	afx_msg void OnBnClickedButCalibBrtFeedback();
	afx_msg void OnBnClickedButReboot();
};
