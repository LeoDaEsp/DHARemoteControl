#pragma once

#include "DhaStteDevice.h"

// *************************************************************************************
// *************************************************************************************
//	Class CStteConfigDlg
// *************************************************************************************
// *************************************************************************************

class CStteConfigDlg : public CDialog
{
	DECLARE_DYNAMIC(CStteConfigDlg)

	// =====================================================================================
	//	TYPES
	// =====================================================================================

protected:

// Dialog Data
	enum { IDD = IDD_STTE_CONFIG_DLG };

public:

	// =====================================================================================
	//	VARIABLES
	// =====================================================================================

protected:
public:

	CDhaStteDevice		*m_pDev;
	CSmartStatic		m_ssCom;

	// =====================================================================================
	// CONSTRUCTORS & DESTRUCTORS
	// =====================================================================================

public:
	CStteConfigDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CStteConfigDlg();

	// =====================================================================================
	//	FUNCTIONS
	// =====================================================================================


protected:
public:

	void	RefreshPort();

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	afx_msg void OnStnClickedStaticCom();
	afx_msg void OnBnClickedButSetIp();
	afx_msg void OnBnClickedButSetSn();
protected:
	virtual void OnOK();
};
