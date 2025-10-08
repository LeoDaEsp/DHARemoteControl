#pragma once

#include "DhaStteDevice.h"
#include "MaintMpp.h"

// *************************************************************************************
// *************************************************************************************
//	Class CLoaderDlg
// *************************************************************************************
// *************************************************************************************

class CLoaderDlg : public CDialog
{
	DECLARE_DYNAMIC(CLoaderDlg)

	// =====================================================================================
	//	TYPES
	// =====================================================================================

public:

	enum t_Mode
	{
		e_Mode_Idle					= 0,
		e_Mode_Program				= 1,
		e_Mode_VerifyAfterProgram	= 2,
		e_Mode_Verify				= 3,
		e_Mode_Read					= 4,
		e_Mode_Erase				= 5
	};


	// =====================================================================================
	//	VARIABLES
	// =====================================================================================

public:

// Dialog Data
	enum { IDD = IDD_LOADER_DLG };

	HACCEL										m_hAccelTable;


	CDhaStteDevice								*m_pDev;


	CString										m_sFilePath;
	CString										m_sFileName;
	CString										m_sReadFilePath;

	CSmartStatic								m_ssTargetFile;
	CSmartStatic								m_ssCom;

	DWORD										m_dwMode;

	CMaintMpp::SBufferTransferStatus			m_BtpStatus;

	BYTE										*m_pbtTempCfg;
	BYTE										*m_pbtTempBm;

	BYTE										m_btPhase;

	CWaitCursor									*m_pWaitCursor;

	t_FMT_Uint16								m_pwCrc16Table[256];
	t_FMT_Uint8									m_pbtByteFlip[256];

	// =====================================================================================
	// CONSTRUCTORS & DESTRUCTORS
	// =====================================================================================

public:
	CLoaderDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLoaderDlg();

	// =====================================================================================
	//	FUNCTIONS
	// =====================================================================================

	t_FMT_Uint16	CalcCRC16Word(t_FMT_Uint16 btCrc,t_FMT_Uint8 btData);
	void			InitCRC16();
	t_FMT_Uint16	CalcCRC16(t_FMT_Uint8* pbtData,t_FMT_Uint32 dwNB);

	void			EnableControls(BOOL bEnable);


	BOOL			CheckCfgFile(CFile& f);
	void			RefreshCfgFileInfo(BYTE *pbtInfo,DWORD dwCrc);	
	void			Timer_CfgLoader();
	void			Timer_BtlLoader();
	void			StartWaitCursor();
	void			StopWaitCursor();

	void			RefreshPort();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	afx_msg void OnBnClickedButStop();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);

	afx_msg void OnBnClickedButCfgProgram();
	afx_msg void OnBnClickedButCfgVerify();
	afx_msg void OnBnClickedButCfgErase();
	afx_msg void OnBnClickedButCfgReadinfoFromfile();
	afx_msg void OnBnClickedButCfgReadinfoFrommem();
	afx_msg void OnBnClickedButCfgRead();
	afx_msg void OnStnClickedStaticComPort();
	afx_msg void OnBnClickedButBitlogErase();
	afx_msg void OnBnClickedButBitlogRead();
};
