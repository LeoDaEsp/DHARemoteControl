#pragma once

#include "FMT_TraceCtrl.h"
#include "CnfFile.h"
#include "DhaStteDevice.h"


// *************************************************************************************
// *************************************************************************************
//	Class CBrtBuilderDlg
// *************************************************************************************
// *************************************************************************************

class CBrtBuilderDlg : public CDialog
{
	DECLARE_DYNAMIC(CBrtBuilderDlg)

	// =====================================================================================
	//	TYPES
	// =====================================================================================

public:

// Dialog Data
	enum { IDD = IDD_BRT_BUILDER_DLG };


	// =====================================================================================
	//	VARIABLES
	// =====================================================================================

public:

	CCnfFile			m_CnfFile;
	CDhaStteDevice		*m_pDev;
	CFMT_TraceCtrl		*m_ppTrace[2];
	DWORD				m_dwCursorPos;
	BYTE				m_btBrtMode;
	DWORD				m_dwCurNode;
	BOOL				m_bEditChangeLock;

	CSmartStatic		m_ssLcdPwmStep;
	CSmartStatic		m_ssLcdPwmDuty;
	CSmartStatic		m_ssLcdCurr;
	CSmartStatic		m_ssFilePath;



	// =====================================================================================
	// CONSTRUCTORS & DESTRUCTORS
	// =====================================================================================

public:
	CBrtBuilderDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CBrtBuilderDlg();


	// =====================================================================================
	//	FUNCTIONS
	// =====================================================================================

public:

	void			UpdateCursors();
	double			GetAmpCurveValue(DWORD dwPos);
	virtual void	RefreshData();
	void			RefreshCurve();
	void			RefreshNodeList();
	void			RefreshNode(DWORD dwNode);
	void			SetCtrlText(DWORD dwID,CString s);
	void			UpdateTableItem(DWORD dwNode);
	void			GenerateLcdBrtPwm();
	void			RefreshInfo();

protected:

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL	OnInitDialog();
	afx_msg void	OnBnClickedButInsertnode();
	afx_msg void	OnBnClickedButRemovenode();
	afx_msg void	OnEnChangeEditNode();
	afx_msg void	OnEnChangeEditValue();
	afx_msg void	OnLvnItemchangedListNodes(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void	OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void	OnBnClickedButGenerateLcdpwm();
	afx_msg void	OnTcnSelchangeTabBrtDn(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void	OnFilesSave();
	afx_msg void	OnFilesSaveas();
	afx_msg void	OnFilesOpen();
	afx_msg void	OnCbnSelendokComboPot();
	afx_msg void	OnEnChangeEditCode();
	afx_msg void	OnEnChangeEditName();
	afx_msg void	OnEnChangeEditAuthor();
	afx_msg void	OnEnChangeEditDate();

	afx_msg void OnBnClickedButImportLcdpwm();
	afx_msg void OnBnClickedButExportLcdpwm();
};
