#pragma once

#include "DhaStteDevice.h"
#include "CRemotePanel.h"

// *************************************************************************************
// *************************************************************************************
//	Class CDha5x5_STTEDlg
// *************************************************************************************
// *************************************************************************************

class CDha5x5_STTEDlg : public CDialog
{
	friend class CRemotePanel;
	// =====================================================================================
	//	TYPES
	// =====================================================================================

protected:

public:

	

	enum { IDD = IDD_DHA5X5_STTE_DIALOG };


	// =====================================================================================
	//	VARIABLES
	// =====================================================================================

protected:

	HICON m_hIcon;

public:

	CDhaStteDevice		*m_pDev;

	CSmartStatic		m_ssIpAdd;
	CSmartStatic		m_ssDinBitOut;
	CSmartStatic		m_ssDinBitEvent;
	CSmartStatic		m_pssHtrStat[2];
	CSmartStatic		m_pssPatCol[2];
	CSmartStatic		m_pssPatRgb[2];
	CSmartStatic		m_ssAd590Hex;
	CSmartStatic		m_ssAd590Temp;
	CSmartStatic		m_ssLogFilePath;

	DWORD				m_dwUnitRev;


	//CDhaStteDevice m_CommDevice;
	DWORD			m_dwCOM;
	//BYTE			m_btPortOpen;


	BYTE			m_btBIT;
	BOOL			m_bRet_BIT;

	BYTE			m_btTXBrt;
	BOOL			m_bRet_TXBrt;

	BYTE			m_btRXBrt;
	BOOL			m_bRet_RXBrt;

	BYTE			m_btLumSensor;
	BOOL			m_bRet_LumSensor;

	BYTE			m_btBacklTemp;
	BOOL			m_bRet_BacklTemp;

	BYTE			m_btHeaterMode;
	BOOL			m_bRet_HeaterMode;

	BYTE			m_btSWVersion;
	BOOL			m_bRet_SWVersion;

	BYTE			m_btFanMode;
	BOOL			m_bRet_FanMode;

	BYTE			m_btLampCtrlStatus;
	BOOL			m_bRet_LampCtrlStatus;

	CBrush			m_brReadOnly;
	CBrush			m_brOk;
	CBrush			m_brFail;
	CBrush			m_brWarning;
	CBrush			m_brInvalid;

	CWinThread		*m_pThread;



	// =====================================================================================
	// CONSTRUCTORS & DESTRUCTORS
	// =====================================================================================

public:

	CDha5x5_STTEDlg(CWnd* pParent = NULL);	// standard constructor
	~CDha5x5_STTEDlg();

	// =====================================================================================
	//	FUNCTIONS
	// =====================================================================================

protected:
public:

	void	RefreshData();
	void	RefreshPatColor(BYTE btIdx, CFMT_Color& col);

	void	EnableControls(BOOL bEnable);

	BOOL	CommMessage(DWORD dwRet);

	CString ReturnEcho(DWORD dwReturn);
	
	void	EnableAutoReadControls(BOOL bEnable);
	void	AbortAutoRead();
	
	void	NtcToMem(const CFMT_String& sPath);



protected:

	// Generated message map functions
	//{{AFX_MSG(CDha5x5_STTEDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnCheckStartstte();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBrtTx();
	afx_msg void OnFanTx();
	afx_msg void OnRead();
	afx_msg void OnRestart();
	afx_msg void OnReadluminance();
	afx_msg void OnReadbacktemp();
	afx_msg void OnReadlampstatus();
	afx_msg void OnReadbitstatus();
	afx_msg void OnReadfanstatus();
	afx_msg void OnReadheaterstatus();
	afx_msg void OnReadswversion();
	afx_msg void OnReadluminancelev();
	afx_msg void OnStaticComport();
	//}}AFX_MSG
	afx_msg LRESULT OnTestMessage(UINT wParam,LONG lParam);
	DECLARE_MESSAGE_MAP()
	virtual void OnCancel();
public:
	afx_msg void OnStnClickedStaticComport();
	afx_msg void OnBnClickedButMm();
	afx_msg void OnBnClickedButMaint();
	afx_msg void OnBnClickedInvalidCommand();
	afx_msg void OnBnClickedUnrecCommand();
	afx_msg void OnBnClickedTimeoutCommand();
	afx_msg void OnBnClickedCheckAutoread();
	afx_msg void OnEnChangeEditBrt();
	afx_msg void OnDeltaposSpinBrt(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedCheckLogon();
	afx_msg void OnStnClickedStaticIpadd();
	afx_msg void OnBnClickedButDebug();
	afx_msg void OnBnClickedCheckHtrEnable();
	afx_msg void OnBnClickedCheckDoutReset();
	afx_msg void OnBnClickedCheckDoutShutdown();
	afx_msg void OnBnClickedCheckDoutGammasel1();
	afx_msg void OnBnClickedCheckDoutSpare1();
	afx_msg void OnBnClickedCheckDoutGammasel2();
	afx_msg void OnBnClickedCheckDoutSpare2();
	afx_msg void OnStnClickedStaticPatCol1();
	afx_msg void OnStnClickedStaticPatCol2();
	afx_msg void OnStnClickedStaticPatRgb1();
	afx_msg void OnStnClickedStaticPatRgb2();
	afx_msg void OnBnClickedRadioVideoPatternGen();
	afx_msg void OnBnClickedRadioVideoExtPlayer();
	afx_msg void OnCbnSelendokComboVideoPattern();
	afx_msg void OnBnClickedButStteConfig();
	afx_msg void OnStnClickedStaticLogPath();
	afx_msg void OnBnClickedButLoader();
	afx_msg void OnBnClickedNoopCommand();
	afx_msg void OnBnClickedDefWarmStartCommand();
	afx_msg void OnBnClickedDayWarmStartCommand();
	afx_msg void OnBnClickedNightWarmStartCommand();
};

