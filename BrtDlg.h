#pragma once


// CBrtDlg dialog

class CBrtDlg : public CDialog
{
	DECLARE_DYNAMIC(CBrtDlg)

public:

	enum tType
	{
		e_PWM		= 0,
		e_VDC		= 1,
		e_Temp		= 2,
		e_Photo		= 3
	};

	BYTE	m_btType;
	BYTE	m_btID;

	DWORD	m_dwCurNode;
	BOOL	m_bEditChangeLock;

	CFMT_Vector< CFMT_Point<double> > m_Data;


	CBrtDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CBrtDlg();

	void SetType(BYTE btType);
	void RefreshList();
	void RefreshNode(DWORD dwNode);
	void SetCtrlText(DWORD dwID,CString s);
	void UpdateCurve();
	void UpdateTableItem(DWORD dwNode);
	BOOL ImportFile(CString sPath,CFMT_Vector< CFMT_Point<double> >& data,BYTE btType);

// Dialog Data
	enum { IDD = IDD_BRT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
	virtual void OnCancel();
public:
	afx_msg void OnLvnItemchangedListNodes(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButInsert();
	afx_msg void OnBnClickedButRemove();
	afx_msg void OnEnChangeEditNode();
	afx_msg void OnEnChangeEditValue();
};
