#pragma once

#include "DhaStteDevice.h"

// *************************************************************************************
// *************************************************************************************
//	Class CBrtFbkCalibDlg
// *************************************************************************************
// *************************************************************************************

class CBrtFbkCalibDlg : public CDialog
{
	DECLARE_DYNAMIC(CBrtFbkCalibDlg)

	// =====================================================================================
	//	TYPES
	// =====================================================================================

protected:
public:
// Dialog Data
	enum { IDD = IDD_BRTFBK_CALIB_DLG };


	// =====================================================================================
	//	VARIABLES
	// =====================================================================================

protected:
public:

	CDhaStteDevice			*m_pDev;

	DWORD					m_dwPhase;
	BYTE					m_btBrtStep;
	DWORD					m_dwDelCnt;

	WORD					m_pwDayCurHi[256];
	WORD					m_pwDayCurLo[256];
	WORD					m_pwNvgCurHi[256];
	WORD					m_pwNvgCurLo[256];

	DWORD					m_dwTotSamples;
	double					m_dHi;
	double					m_dLo;

	CString					m_sCnfPath;


	// =====================================================================================
	// CONSTRUCTORS & DESTRUCTORS
	// =====================================================================================


public:
	CBrtFbkCalibDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CBrtFbkCalibDlg();


	// =====================================================================================
	//	FUNCTIONS
	// =====================================================================================

protected:

	DECLARE_MESSAGE_MAP()

public:
	
	BOOL	MaintTimerActions();
	BOOL	CalibTimerActions();
	
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);


protected:
	virtual void OnOK();
	virtual void OnCancel();

};
