#pragma once

#include "BrtDlg.h"
#include "DhaStteDevice.h"


#define MEMORYPROGDLG_PROGMESS		WM_USER
#define MEMORYPROGDLG_ERRORMESS		WM_USER+1
#define MEMORYPROGDLG_ENDMESS		WM_USER+2

#define MEMPROG_BYTE_PER_PAGE		256
#define MEMPROG_NUM_PAGES			((DHA5X5_MEMORYSIZE)/MEMPROG_BYTE_PER_PAGE)
#define MEMPROG_WRITE_DELAY			40
#define MEMPROG_PAGE_PER_CYCLE		32
#define MEMPROG_ERASE_DELAY			255
#define MEMPROG_BYTE_PER_SECTOR		0x10000

// CMMDlg dialog

class CMMDlg : public CDialog
{
	DECLARE_DYNAMIC(CMMDlg)

public:

	enum tDialogID
	{
		e_VDCDay1_Dlg		= 0,
		e_VDCNight1_Dlg		= 1,
		e_VDCDay2_Dlg		= 2,
		e_VDCNight2_Dlg		= 3,
		e_VDCDay3_Dlg		= 4,
		e_VDCNight3_Dlg		= 5,
		e_VDCDay4_Dlg		= 6,
		e_VDCNight4_Dlg		= 7,
		e_PWMDay1_Dlg		= 8,
		e_PWMNight1_Dlg		= 9,
		e_PWMDay2_Dlg		= 10,
		e_PWMNight2_Dlg		= 11,
		e_PWMDay3_Dlg		= 12,
		e_PWMNight3_Dlg		= 13,
		e_PWMDay4_Dlg		= 14,
		e_PWMNight4_Dlg		= 15,
		e_BackTemp_Dlg		= 16,
		e_PhotoLow_Dlg		= 17,
		e_PhotoHigh_Dlg		= 18,
		e_Total_Dlg			= 19
	};

	enum tReturn
	{
		e_Ret_OK				= 0,
		e_Ret_DeviceErr			= 1,
		e_Ret_ConnectErr		= 2,
		e_Ret_CommErr			= 3,
		e_Ret_FileErr			= 4,
		e_Ret_VerifyErr			= 5
	};

	enum tStatus
	{
		e_Status_Ready			= 0,
		e_Status_Programming	= 1,
		e_Status_Error			= 2
	};

	CBrtDlg			*m_pBrtDlg;
	BYTE			m_btCurDlg;
	BYTE			m_pbtMemory[DHA5X5_MEMORYSIZE];
	CDhaStteDevice	*m_pDev;
	CWinThread		*m_pThread;
	DWORD			m_dwThreadReturn;
	DWORD			m_dwStatus;
	CBrush			m_brStatusReady;
	CBrush			m_brStatusProgramming;
	CBrush			m_brStatusError;
	CBrush			m_brRO;
	CString			m_sReadFilePath;

	CFMT_Vector< CFMT_Point<double> > m_Curves[e_Total_Dlg];

	CMMDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMMDlg();

	WORD CalcCRC(BYTE* pbtData, DWORD dwNB);
	void SetWord(DWORD dwAdd,WORD wValue);
	void SetCurrentDlg(BYTE btCurDlg);
	BOOL GeneratePWMData(DWORD dwID);
	BOOL GenerateVDCData(DWORD dwID);
	//BOOL GenerateHeaterTempTrimData();
	BOOL GeneratePhotoLoTrimData();
	BOOL GeneratePhotoHiTrimData();
	BOOL GenerateBackTempTrimData();
	BOOL GenerateCurrentFANThresh();
	WORD CalcCRC16Word(BYTE btData,WORD wOld);
	void GenerateCRC();
	BOOL GenerateMemory();
	BOOL SaveMemoryImage(const CString& sImageName);
	BOOL GenerateMIF();
	void UpdateStatus(const CString& sMess, DWORD dwStatus);
	CString GetErrString(BYTE btRet);
	void SetProgProgress(DWORD dwPos);

	BOOL		WaitEndOfProcess(int iTimeout);
	static UINT PollThread(LPVOID pParam);
	static UINT ProgramThread(LPVOID pParam);
	static UINT VerifyThread(LPVOID pParam);
	static UINT ReadThread(LPVOID pParam);

// Dialog Data
	enum { IDD = IDD_MM_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
	virtual void OnCancel();
public:
	afx_msg void OnTcnSelchangeTabGraph(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButProg();
	afx_msg void OnBnClickedButVerify();
	afx_msg void OnBnClickedButPoll();
	LRESULT OnMessageEnd(UINT wParam,LONG lParam);
	LRESULT OnMessageError(UINT wParam,LONG lParam);
	LRESULT OnMessageChange(UINT wParam,LONG lParam);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnMenufileOpen();
	afx_msg void OnMenufileSave();
	afx_msg void OnFileImportfull();
	afx_msg void OnBnClickedButRead();
	afx_msg void OnCbnSelendokComboSpeed();
};
