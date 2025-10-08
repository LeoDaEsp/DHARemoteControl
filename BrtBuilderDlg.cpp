// BrtBuilderDlg.cpp : implementation file
//

#include "stdafx.h"
#include "dha5x5_STTE.h"
#include "BrtBuilderDlg.h"
#include "GenerateBrtDlg.h"
//#include "DuUnit.h"

#include <math.h>


// CBrtBuilderDlg dialog

IMPLEMENT_DYNAMIC(CBrtBuilderDlg, CDialog)

#define STTE_MAX_CURVE_NODES	30




// -----------------------------------------------------------------------------------
//	CBrtBuilderDlg::CBrtBuilderDlg
// -----------------------------------------------------------------------------------

CBrtBuilderDlg::CBrtBuilderDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBrtBuilderDlg::IDD, pParent)
{
	m_dwCursorPos = 0;
	m_btBrtMode = 0;
	m_dwCurNode = 0;
	m_bEditChangeLock = FALSE;

	#if 0
	DWORD		k;
	DWORD		w;


	m_bFileNew = TRUE;
	m_sFilePath = "newbrt.bin";

	m_pbtMemBuf = new BYTE[DUUNIT_BRTMEM_TOT_BYTE_SIZE];
	memset(m_pbtMemBuf, 0, DUUNIT_BRTMEM_TOT_BYTE_SIZE);

	// --- LCD PWM Generation Parameters ------------------------

	for (k=0; k<2; k++)
	{
		m_pdLcdPwmMinStep[k] = 0.0;
		m_pdLcdPwmMaxStep[k] = 100.0;
		m_pdLcdPwmMinDuty[k] = 0.0;
		m_pdLcdPwmMaxDuty[k] = 100.0;
		m_pdLcdPwmGamma[k] = 2.0;
	}

	// --- Build default LCD Brightness Curves ------------------------
	
	for (k=0; k<2; k++)
	{
		// PWM
		m_ppLcdCurve[k][0].m_Data.Create(65536);

		for (w=0; w<65536; w++)
		{
			m_ppLcdCurve[k][0].m_Data[w].m_PX = (float)((float)w*(100.0/65535.0));
			m_ppLcdCurve[k][0].m_Data[w].m_PY = (float)((float)w*(100.0/65535.0));
		}

		// Current
		m_ppLcdCurve[k][1].m_Data.Create(2);

		m_ppLcdCurve[k][1].m_Data[0].m_PX=0;
		m_ppLcdCurve[k][1].m_Data[0].m_PY=0;

		m_ppLcdCurve[k][1].m_Data[1].m_PX = 100.0;
		m_ppLcdCurve[k][1].m_Data[1].m_PY = 100.0;
	}
	#endif
}


// -----------------------------------------------------------------------------------
//	CBrtBuilderDlg::~CBrtBuilderDlg
// -----------------------------------------------------------------------------------

CBrtBuilderDlg::~CBrtBuilderDlg()
{
	//delete[] m_pbtMemBuf;
}


// -----------------------------------------------------------------------------------
//	CBrtBuilderDlg Message Map
// -----------------------------------------------------------------------------------

BEGIN_MESSAGE_MAP(CBrtBuilderDlg, CDialog)
	ON_BN_CLICKED(IDC_BUT_INSERT_LCDBRT_NODE, &CBrtBuilderDlg::OnBnClickedButInsertnode)
	ON_BN_CLICKED(IDC_BUT_REMOVE_LCDBRT_NODE, &CBrtBuilderDlg::OnBnClickedButRemovenode)
	ON_EN_CHANGE(IDC_EDIT_LCDBRT_NODE, &CBrtBuilderDlg::OnEnChangeEditNode)
	ON_EN_CHANGE(IDC_EDIT_LCDBRT_VALUE, &CBrtBuilderDlg::OnEnChangeEditValue)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_LCDBRT_NODES, &CBrtBuilderDlg::OnLvnItemchangedListNodes)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BUT_GENERATE_LCDPWM, &CBrtBuilderDlg::OnBnClickedButGenerateLcdpwm)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_BRT_DN, &CBrtBuilderDlg::OnTcnSelchangeTabBrtDn)
	ON_COMMAND(ID_FILE_SAVE, &CBrtBuilderDlg::OnFilesSave)
	ON_COMMAND(ID_FILE_SAVEAS, &CBrtBuilderDlg::OnFilesSaveas)
	ON_COMMAND(ID_FILE_OPEN, &CBrtBuilderDlg::OnFilesOpen)
	ON_CBN_SELENDOK(IDC_COMBO_POT, &CBrtBuilderDlg::OnCbnSelendokComboPot)
	ON_EN_CHANGE(IDC_EDIT_CODE, &CBrtBuilderDlg::OnEnChangeEditCode)
	ON_EN_CHANGE(IDC_EDIT_NAME, &CBrtBuilderDlg::OnEnChangeEditName)
	ON_EN_CHANGE(IDC_EDIT_AUTHOR, &CBrtBuilderDlg::OnEnChangeEditAuthor)
	ON_EN_CHANGE(IDC_EDIT_DATE, &CBrtBuilderDlg::OnEnChangeEditDate)
	ON_BN_CLICKED(IDC_BUT_IMPORT_LCDPWM, &CBrtBuilderDlg::OnBnClickedButImportLcdpwm)
	ON_BN_CLICKED(IDC_BUT_EXPORT_LCDPWM, &CBrtBuilderDlg::OnBnClickedButExportLcdpwm)
END_MESSAGE_MAP()


// -----------------------------------------------------------------------------------
//	CBrtBuilderDlg::OnInitDialog
// -----------------------------------------------------------------------------------

BOOL CBrtBuilderDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	TCITEM		tc;
	CString		s;
	DWORD		k;


	// --- Subclassing -----------------------------

	m_ssLcdPwmStep.SubclassDlgItem(IDC_STATIC_LCDPWM_STEP,this);
	m_ssLcdPwmDuty.SubclassDlgItem(IDC_STATIC_LCDPWM_DUTY,this);
	m_ssLcdCurr.SubclassDlgItem(IDC_STATIC_LCDCURR,this);
	m_ssFilePath.SubclassDlgItem(IDC_STATIC_FILE_PATH,this);



	// --- Tab Control -----------------------------

	tc.mask = TCIF_TEXT;

	tc.pszText = "NVG";
	tc.cchTextMax = strlen(tc.pszText); 
	M_GETTAB(IDC_TAB_BRT_DN)->InsertItem(0,&tc);

	tc.pszText = "Day";
	tc.cchTextMax = strlen(tc.pszText); 
	M_GETTAB(IDC_TAB_BRT_DN)->InsertItem(1,&tc);


	m_ppTrace[0] = ((CFMT_TraceCtrl*)GetDlgItem(IDC_TRACE_LCDPWM));
	m_ppTrace[1] = ((CFMT_TraceCtrl*)GetDlgItem(IDC_TRACE_LCDVOLT));

	M_GETSLIDER(IDC_SLIDER_LCDBRT_CURSOR)->SetRange(0, 255);
	M_GETSLIDER(IDC_SLIDER_LCDBRT_CURSOR)->SetPos(m_dwCursorPos);

	m_ppTrace[0]->InsertLine(0, FMTTRCCTL_AXIS_LEFT, (double)(m_CnfFile.m_ppLcdCurve[m_btBrtMode][0].m_Data[m_dwCursorPos].GetY()),
									FALSE, RGB(255,0,0), PS_SOLID, 1);
	m_ppTrace[0]->InsertLine(0, FMTTRCCTL_AXIS_BOTTOM, (double)m_dwCursorPos,TRUE,RGB(255,0,0), PS_SOLID, 1);

	m_ppTrace[1]->InsertLine(0, FMTTRCCTL_AXIS_LEFT, (double)(m_CnfFile.m_ppLcdCurve[m_btBrtMode][1].m_Data[m_dwCursorPos].GetY()),
									FALSE, RGB(255,0,0), PS_SOLID, 1);
	m_ppTrace[1]->InsertLine(0, FMTTRCCTL_AXIS_BOTTOM, (double)m_dwCursorPos, TRUE, RGB(255,0,0), PS_SOLID, 1);

	UpdateCursors();

	// --- Init List Control -----------------------------------------------------------

	M_GETLISTCTRL(IDC_LIST_LCDBRT_NODES)->SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	M_GETLISTCTRL(IDC_LIST_LCDBRT_NODES)->InsertColumn(0,"Node", LVCFMT_LEFT, 40);
	M_GETLISTCTRL(IDC_LIST_LCDBRT_NODES)->InsertColumn(1,"Dim", LVCFMT_LEFT, 60);
	M_GETLISTCTRL(IDC_LIST_LCDBRT_NODES)->InsertColumn(2,"Value", LVCFMT_LEFT, 60);

	m_ssLcdPwmStep.SetBkColor(STTE_COLOR_YELLOW);
	m_ssLcdPwmDuty.SetBkColor(STTE_COLOR_YELLOW);
	m_ssLcdCurr.SetBkColor(STTE_COLOR_YELLOW);


	m_ssFilePath.SetWindowText(m_CnfFile.m_sFilePath);
	m_ssFilePath.SetBkColor(STTE_COLOR_GREEN);

	for (k=0; k<128; k++)
	{
		s.Format("%d", k);
		M_GETCOMBO(IDC_COMBO_POT)->AddString(s);
	}

	M_GETEDIT(IDC_EDIT_CODE)->SetLimitText(CNF_CODE_LENGTH);
	M_GETEDIT(IDC_EDIT_NAME)->SetLimitText(CNF_NAME_LENGTH);
	M_GETEDIT(IDC_EDIT_AUTHOR)->SetLimitText(CNF_AUTHOR_LENGTH);
	M_GETEDIT(IDC_EDIT_DATE)->SetLimitText(CNF_DATE_LENGTH);


	RefreshData();
	RefreshInfo();

	M_GETLISTCTRL(IDC_LIST_LCDBRT_NODES)->SetItemState(0,LVIS_SELECTED|LVIS_FOCUSED,LVIS_SELECTED|LVIS_FOCUSED);

	return TRUE;
}


// -----------------------------------------------------------------------------------
//	CBrtBuilderDlg::RefreshInfo
// -----------------------------------------------------------------------------------

void CBrtBuilderDlg::RefreshInfo()
{
	M_GETEDIT(IDC_EDIT_CODE)->SetWindowText(m_CnfFile.m_sCode);
	M_GETEDIT(IDC_EDIT_NAME)->SetWindowText(m_CnfFile.m_sName);
	M_GETEDIT(IDC_EDIT_AUTHOR)->SetWindowText(m_CnfFile.m_sAuthor);
	M_GETEDIT(IDC_EDIT_DATE)->SetWindowText(m_CnfFile.m_sDate);
}


// -----------------------------------------------------------------------------------
//	CBrtBuilderDlg::UpdateCursors
// -----------------------------------------------------------------------------------

void CBrtBuilderDlg::UpdateCursors()
{
	CString		s;
	double		dAmp;
	double		dPos;

	//dPos = (double)m_dwCursorPos / 65535.0 * 100.0;
	dPos = (double)m_dwCursorPos;

	m_ppTrace[0]->MoveLine(0, dPos);
	m_ppTrace[0]->MoveLine(1, (double)(m_CnfFile.m_ppLcdCurve[m_btBrtMode][0].m_Data[m_dwCursorPos].GetY()));
	m_ppTrace[0]->RedrawWindow();

	dAmp = GetAmpCurveValue(m_dwCursorPos);

	m_ppTrace[1]->MoveLine(0, dPos);
	m_ppTrace[1]->MoveLine(1, dAmp);
	m_ppTrace[1]->RedrawWindow();

	s.Format("%.2f", dPos);
	m_ssLcdPwmStep.SetWindowText(s);

	s.Format("%.2f", m_CnfFile.m_ppLcdCurve[m_btBrtMode][0].m_Data[m_dwCursorPos].GetY());
	m_ssLcdPwmDuty.SetWindowText(s);

	s.Format("%.2f", dAmp);
	m_ssLcdCurr.SetWindowText(s);
}


// -----------------------------------------------------------------------------------
//	CBrtBuilderDlg::GetAmpCurveValue
// -----------------------------------------------------------------------------------

double CBrtBuilderDlg::GetAmpCurveValue(DWORD dwPos)
{
	double	dVal;
	double	m,q;
	DWORD	pdwNodes[2];
	int		k;
	double	dPos;

	dPos = (double)dwPos;

	// Find limiting nodes
	pdwNodes[0] = 0;

	pdwNodes[1] = (!m_CnfFile.m_ppLcdCurve[m_btBrtMode][1].m_Data)-1;

	for (k=0; k<(int)!m_CnfFile.m_ppLcdCurve[m_btBrtMode][1].m_Data; k++)
	{
		if (m_CnfFile.m_ppLcdCurve[m_btBrtMode][1].m_Data[k].GetX() <= dPos)
		{
			pdwNodes[0] = k;
		}
	}

	for (k=(int)!m_CnfFile.m_ppLcdCurve[m_btBrtMode][1].m_Data-1; k>=0; k--)
	{
		if (m_CnfFile.m_ppLcdCurve[m_btBrtMode][1].m_Data[k].GetX() >= dPos)
		{
			pdwNodes[1] = k;
		}
	}

	// Compute value

	if (pdwNodes[0] == pdwNodes[1])
	{
		dVal = (double)m_CnfFile.m_ppLcdCurve[m_btBrtMode][1].m_Data[pdwNodes[1]].GetY();
	}
	else
	{
		m = (m_CnfFile.m_ppLcdCurve[m_btBrtMode][1].m_Data[pdwNodes[1]].GetY() - m_CnfFile.m_ppLcdCurve[m_btBrtMode][1].m_Data[pdwNodes[0]].GetY())/
			(m_CnfFile.m_ppLcdCurve[m_btBrtMode][1].m_Data[pdwNodes[1]].GetX() - m_CnfFile.m_ppLcdCurve[m_btBrtMode][1].m_Data[pdwNodes[0]].GetX());

		q = m_CnfFile.m_ppLcdCurve[m_btBrtMode][1].m_Data[pdwNodes[1]].GetY() - m*m_CnfFile.m_ppLcdCurve[m_btBrtMode][1].m_Data[pdwNodes[1]].GetX();

		dVal = m*((double)dPos)+q;
	}

	return dVal;
}


// -----------------------------------------------------------------------------------
//	CBrtBuilderDlg::RefreshData
// -----------------------------------------------------------------------------------

void CBrtBuilderDlg::RefreshData()
{
	RefreshCurve();
	RefreshNodeList();
	RefreshNode(m_dwCurNode);
	UpdateCursors();

	M_GETCOMBO(IDC_COMBO_POT)->SetCurSel(m_CnfFile.m_pbtBrtPot[m_btBrtMode]);

}


// -----------------------------------------------------------------------------------
//	CBrtBuilderDlg::RefreshCurve
// -----------------------------------------------------------------------------------

void CBrtBuilderDlg::RefreshCurve()
{
	DWORD		k;
	DWORD		dwStyle;

	for (k=0; k<2; k++)
	{
		if (k==0)
		{
			dwStyle = FMTTRCCTL_TRACE_JOIN;
		}
		else
		{
			dwStyle = FMTTRCCTL_TRACE_JOIN | FMTTRCCTL_TRACE_POINTS;
		}

		m_ppTrace[k]->SetBackgroundColor(RGB(255,255,255));

		m_ppTrace[k]->EnableAxis(FMTTRCCTL_AXIS_TOP,FALSE);
		m_ppTrace[k]->EnableAxis(FMTTRCCTL_AXIS_X,FALSE);
		m_ppTrace[k]->EnableAxis(FMTTRCCTL_AXIS_Y,FALSE);
		m_ppTrace[k]->EnableAxis(FMTTRCCTL_AXIS_RIGHT,FALSE);

		m_ppTrace[k]->EnableAxisText(FMTTRCCTL_AXIS_BOTTOM,FALSE);
		m_ppTrace[k]->EnableAxisText(FMTTRCCTL_AXIS_X,FALSE);
		m_ppTrace[k]->EnableAxisText(FMTTRCCTL_AXIS_Y,FALSE);
		m_ppTrace[k]->EnableAxisText(FMTTRCCTL_AXIS_RIGHT,TRUE);
		m_ppTrace[k]->EnableAxisText(FMTTRCCTL_AXIS_TOP,TRUE);
		m_ppTrace[k]->EnableAxisText(FMTTRCCTL_AXIS_LEFT,FALSE);

		m_ppTrace[k]->SetGridHorz(FALSE,FMTTRCCTL_AXIS_BOTTOM,RGB(255,0,0),PS_SOLID);
		m_ppTrace[k]->SetSubGridHorz(TRUE,RGB(220,220,220),PS_SOLID);
		m_ppTrace[k]->EnableGridHorz(TRUE);
		m_ppTrace[k]->SetGridVert(FALSE,FMTTRCCTL_AXIS_LEFT,RGB(255,0,0),PS_SOLID);
		m_ppTrace[k]->SetSubGridVert(TRUE,RGB(220,220,220),PS_SOLID);
		m_ppTrace[k]->EnableGridVert(TRUE);

		m_ppTrace[k]->EnableAxisSubTap(FMTTRCCTL_AXIS_BOTTOM,TRUE);
		m_ppTrace[k]->EnableAxisTapLabel(FMTTRCCTL_AXIS_BOTTOM,TRUE);
		m_ppTrace[k]->EnableAxisSubTapLabel(FMTTRCCTL_AXIS_BOTTOM,FALSE);

		m_ppTrace[k]->EnableAxisTap(FMTTRCCTL_AXIS_LEFT,TRUE);
		m_ppTrace[k]->EnableAxisSubTap(FMTTRCCTL_AXIS_LEFT,TRUE);
		m_ppTrace[k]->EnableAxisTapLabel(FMTTRCCTL_AXIS_LEFT,TRUE);
		m_ppTrace[k]->EnableAxisSubTapLabel(FMTTRCCTL_AXIS_LEFT,FALSE);

		m_ppTrace[k]->SetAxis(FMTTRCCTL_AXIS_BOTTOM,RGB(0,0,0),1,1.0,0.0);
		m_ppTrace[k]->SetAxis(FMTTRCCTL_AXIS_LEFT,RGB(0,0,0),1,1.0,0.0);

		m_ppTrace[k]->SetAxisText(FMTTRCCTL_AXIS_RIGHT,"Steps",CSize(35,20),RGB(0,0,0),RGB(255,255,255),0,5,FALSE);

		m_ppTrace[k]->SetAxisTap(FMTTRCCTL_AXIS_BOTTOM,RGB(0,0,0), 5, 32);
		m_ppTrace[k]->SetAxisSubTap(FMTTRCCTL_AXIS_BOTTOM,RGB(0,0,0),3,8);
		m_ppTrace[k]->SetAxisTapLabel(FMTTRCCTL_AXIS_BOTTOM,RGB(0,0,0),0,0,30);
		m_ppTrace[k]->SetAxisSubTapLabel(FMTTRCCTL_AXIS_BOTTOM,RGB(0,0,0),0,0,30);


		if (k==0)
		{
			m_ppTrace[k]->SetAxisText(FMTTRCCTL_AXIS_TOP,"Duty",CSize(55,20),RGB(0,0,0),RGB(255,255,255),0,0,FALSE);

			m_ppTrace[k]->SetAxisTap(FMTTRCCTL_AXIS_LEFT,RGB(0,0,0), 5, 8192.0);
			m_ppTrace[k]->SetAxisSubTap(FMTTRCCTL_AXIS_LEFT,RGB(0,0,0), 3, 5);
			m_ppTrace[k]->SetAxisTapLabel(FMTTRCCTL_AXIS_LEFT,RGB(0,0,0),0, 0, 50);
			m_ppTrace[k]->SetAxisSubTapLabel(FMTTRCCTL_AXIS_LEFT,RGB(0,0,0), 1, 0, 50);
	
			m_ppTrace[k]->SetScale(1.4, 0.0025);
		}
		else
		{
			m_ppTrace[k]->SetAxisText(FMTTRCCTL_AXIS_TOP,"Current",CSize(55,20),RGB(0,0,0),RGB(255,255,255),0,0,FALSE);

			m_ppTrace[k]->SetAxisTap(FMTTRCCTL_AXIS_LEFT,RGB(0,0,0), 5, 1024.0);
			m_ppTrace[k]->SetAxisSubTap(FMTTRCCTL_AXIS_LEFT,RGB(0,0,0), 3 ,5);
			m_ppTrace[k]->SetAxisTapLabel(FMTTRCCTL_AXIS_LEFT,RGB(0,0,0), 0, 0, 50);
			m_ppTrace[k]->SetAxisSubTapLabel(FMTTRCCTL_AXIS_LEFT,RGB(0,0,0), 1, 0, 50);

			m_ppTrace[k]->SetScale(1.4, 0.04);
		}

		m_ppTrace[k]->ScrollTo(0,0);

		if (m_ppTrace[k]->GetNumTraces()>0)
		{
			m_ppTrace[k]->ReplaceTrace(0,RGB(0,0,255), dwStyle,
								FMTTRCCTL_COUPLES_DATA,
								!m_CnfFile.m_ppLcdCurve[m_btBrtMode][k].m_Data,
								m_CnfFile.m_ppLcdCurve[m_btBrtMode][k].m_Data.GetBuf(),1,PS_SOLID);
		}
		else
		{
			m_ppTrace[k]->InsertTrace(0,RGB(0,0,255),dwStyle,
								FMTTRCCTL_COUPLES_DATA,
								!m_CnfFile.m_ppLcdCurve[m_btBrtMode][k].m_Data,
								m_CnfFile.m_ppLcdCurve[m_btBrtMode][k].m_Data.GetBuf(),1,PS_SOLID);
		}


		m_ppTrace[k]->RedrawWindow();
	
	}
}


// -----------------------------------------------------------------------------------
//	CBrtBuilderDlg::RefreshNodeList
// -----------------------------------------------------------------------------------

void CBrtBuilderDlg::RefreshNodeList()
{
	M_GETLISTCTRL(IDC_LIST_LCDBRT_NODES)->DeleteAllItems();	
	
	DWORD	k;
	CString	s;

	for (k=0;k<!(m_CnfFile.m_ppLcdCurve[m_btBrtMode][1].m_Data);k++)
	{
		s.Format("%d",k + 1);
		M_GETLISTCTRL(IDC_LIST_LCDBRT_NODES)->InsertItem(k, s);

		s.Format("%.2f", m_CnfFile.m_ppLcdCurve[m_btBrtMode][1].m_Data[k].GetX());
		M_GETLISTCTRL(IDC_LIST_LCDBRT_NODES)->SetItemText(k, 1, s);

		s.Format("%.2f", m_CnfFile.m_ppLcdCurve[m_btBrtMode][1].m_Data[k].GetY());
		M_GETLISTCTRL(IDC_LIST_LCDBRT_NODES)->SetItemText(k, 2, s);
	}
}


// -----------------------------------------------------------------------------------
//	CBrtBuilderDlg::RefreshNode
// -----------------------------------------------------------------------------------

void CBrtBuilderDlg::RefreshNode(DWORD dwNode)
{
	CString s;

	s.Format("%.2f", m_CnfFile.m_ppLcdCurve[m_btBrtMode][1].m_Data[dwNode].GetX());
	SetCtrlText(IDC_EDIT_LCDBRT_NODE,s);

	s.Format("%.2f", m_CnfFile.m_ppLcdCurve[m_btBrtMode][1].m_Data[dwNode].GetY());
	SetCtrlText(IDC_EDIT_LCDBRT_VALUE,s);
}


// -----------------------------------------------------------------------------------
//	CBrtBuilderDlg::SetCtrlText
// -----------------------------------------------------------------------------------

void CBrtBuilderDlg::SetCtrlText(DWORD dwID,CString s)
{
	CWnd *pW = GetDlgItem(dwID);

	m_bEditChangeLock = TRUE;
	pW->SetWindowText(s);
	pW->GetWindowText(s);
	m_bEditChangeLock = FALSE;
}


// -----------------------------------------------------------------------------------
//	CBrtBuilderDlg::OnBnClickedButInsertnode
// -----------------------------------------------------------------------------------

void CBrtBuilderDlg::OnBnClickedButInsertnode()
{
	if (!m_CnfFile.m_ppLcdCurve[m_btBrtMode][1].m_Data >= STTE_MAX_CURVE_NODES)
	{
		STTE_Message("Maximum nodes number reached.",MB_ICONSTOP, this);
		return;
	}

	CString				s;
	DWORD				k;
	CFMT_Point<double>	pd;

	// Insert the node into data array
	pd = m_CnfFile.m_ppLcdCurve[m_btBrtMode][1].m_Data[m_dwCurNode];

	m_CnfFile.m_ppLcdCurve[m_btBrtMode][1].m_Data.InsertItems(m_dwCurNode, pd, 1, TRUE);


	// Insert the node into the table
	s.Format("%d" ,m_dwCurNode+1);
	M_GETLISTCTRL(IDC_LIST_LCDBRT_NODES)->InsertItem(m_dwCurNode, s);

	for (k = m_dwCurNode; k<!(m_CnfFile.m_ppLcdCurve[m_btBrtMode][1].m_Data); k++)
	{
		UpdateTableItem(k);
	}


	// Update Trace Control
	m_ppTrace[1]->ReplaceTrace(0,RGB(0,0,255),FMTTRCCTL_TRACE_POINTS|FMTTRCCTL_TRACE_JOIN,
							FMTTRCCTL_COUPLES_DATA,
							!(m_CnfFile.m_ppLcdCurve[m_btBrtMode][1].m_Data),
							m_CnfFile.m_ppLcdCurve[m_btBrtMode][1].m_Data.GetBuf(),1,PS_SOLID);

	UpdateCursors();
	m_ppTrace[1]->RedrawWindow();
}


// -----------------------------------------------------------------------------------
//	CBrtBuilderDlg::OnBnClickedButRemovenode
// -----------------------------------------------------------------------------------

void CBrtBuilderDlg::OnBnClickedButRemovenode()
{
	CString	s;

	if ((m_dwCurNode==0) || (m_dwCurNode>=!(m_CnfFile.m_ppLcdCurve[m_btBrtMode][1].m_Data)-1))
	{
		STTE_Message("Cannot remove starting and ending nodes",MB_ICONSTOP, this);
		return;
	}

	s.Format("Node %d will be deleted. Confirm deletion?",m_dwCurNode+1);
	
	if (STTE_Message(s, MB_ICONWARNING|MB_YESNO, this)!=IDYES)
	{
		return;
	}

	DWORD k;

	m_CnfFile.m_ppLcdCurve[m_btBrtMode][1].m_Data.DeleteItems(m_dwCurNode,1,TRUE);

	M_GETLISTCTRL(IDC_LIST_LCDBRT_NODES)->DeleteItem(m_dwCurNode);

	for (k=m_dwCurNode;k<!(m_CnfFile.m_ppLcdCurve[m_btBrtMode][1].m_Data);k++)
	{
		UpdateTableItem(k);
	}

	m_ppTrace[1]->ReplaceTrace(0,RGB(0,0,255),FMTTRCCTL_TRACE_POINTS|FMTTRCCTL_TRACE_JOIN,
							FMTTRCCTL_COUPLES_DATA,
							!(m_CnfFile.m_ppLcdCurve[m_btBrtMode][1].m_Data),
							m_CnfFile.m_ppLcdCurve[m_btBrtMode][1].m_Data.GetBuf(),1,PS_SOLID);

	UpdateCursors();
	m_ppTrace[1]->RedrawWindow();
}


// -----------------------------------------------------------------------------------
//	CBrtBuilderDlg::OnEnChangeEditNode
// -----------------------------------------------------------------------------------

void CBrtBuilderDlg::OnEnChangeEditNode()
{
	if ((m_dwCurNode==0) || (m_dwCurNode==!(m_CnfFile.m_ppLcdCurve[m_btBrtMode][1].m_Data)-1))
	{
		return;
	}

	if (m_bEditChangeLock)
	{
		return;
	}

	CString s;
	double d,d1,d2;

	GetDlgItem(IDC_EDIT_LCDBRT_NODE)->GetWindowText(s);
	d=atof(s);

	d1 = m_CnfFile.m_ppLcdCurve[m_btBrtMode][1].m_Data[m_dwCurNode-1].GetX();
	d2 = m_CnfFile.m_ppLcdCurve[m_btBrtMode][1].m_Data[m_dwCurNode+1].GetX();

	if (d<d1)
	{
		d=d1;
	}
	else if (d>d2)
	{
		d=d2;
	}

	if (m_CnfFile.m_ppLcdCurve[m_btBrtMode][1].m_Data[m_dwCurNode].GetX() == d)
	{
		return;
	}

	m_CnfFile.m_ppLcdCurve[m_btBrtMode][1].m_Data[m_dwCurNode].SetX(d);

	s.Format("%.2f",m_CnfFile.m_ppLcdCurve[m_btBrtMode][1].m_Data[m_dwCurNode].GetX());
	M_GETLISTCTRL(IDC_LIST_LCDBRT_NODES)->SetItemText(m_dwCurNode,1,s);
	
	m_ppTrace[1]->ReplaceTrace(0,RGB(0,0,255),FMTTRCCTL_TRACE_POINTS|FMTTRCCTL_TRACE_JOIN,
						FMTTRCCTL_COUPLES_DATA,
						!m_CnfFile.m_ppLcdCurve[m_btBrtMode][1].m_Data,
						m_CnfFile.m_ppLcdCurve[m_btBrtMode][1].m_Data.GetBuf(),1,PS_SOLID);

	UpdateCursors();
	m_ppTrace[1]->RedrawWindow();
}


// -----------------------------------------------------------------------------------
//	CBrtBuilderDlg::OnEnChangeEditValue
// -----------------------------------------------------------------------------------

void CBrtBuilderDlg::OnEnChangeEditValue()
{
	if (m_bEditChangeLock)
	{
		return;
	}

	CString s;
	double d;

	GetDlgItem(IDC_EDIT_LCDBRT_VALUE)->GetWindowText(s);

	d=atof(s);

	if (d<0.0)
	{
		d=0.0;
	}

	if (d>4095.0)
	{
		d=4095.0;
	}

	if (m_CnfFile.m_ppLcdCurve[m_btBrtMode][1].m_Data[m_dwCurNode].GetY() == d)
	{
		return;
	}

	m_CnfFile.m_ppLcdCurve[m_btBrtMode][1].m_Data[m_dwCurNode].SetY(d);

	s.Format("%.2f",m_CnfFile.m_ppLcdCurve[m_btBrtMode][1].m_Data[m_dwCurNode].GetY());
	M_GETLISTCTRL(IDC_LIST_LCDBRT_NODES)->SetItemText(m_dwCurNode,2,s);

	m_ppTrace[1]->ReplaceTrace(0,RGB(0,0,255),FMTTRCCTL_TRACE_POINTS|FMTTRCCTL_TRACE_JOIN,
						FMTTRCCTL_COUPLES_DATA,
						!m_CnfFile.m_ppLcdCurve[m_btBrtMode][1].m_Data,
						m_CnfFile.m_ppLcdCurve[m_btBrtMode][1].m_Data.GetBuf(),1,PS_SOLID);

	UpdateCursors();
	m_ppTrace[1]->RedrawWindow();
}


// -----------------------------------------------------------------------------------
//	CBrtBuilderDlg::OnLvnItemchangedListNodes
// -----------------------------------------------------------------------------------

void CBrtBuilderDlg::OnLvnItemchangedListNodes(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	POSITION pos;
	CString s;

	pos=M_GETLISTCTRL(IDC_LIST_LCDBRT_NODES)->GetFirstSelectedItemPosition();

	if (pos==NULL)
	{
		return;
	}

	m_dwCurNode=M_GETLISTCTRL(IDC_LIST_LCDBRT_NODES)->GetNextSelectedItem(pos);

	RefreshNode(m_dwCurNode);

	*pResult = 0;
}


// -----------------------------------------------------------------------------------
//	CBrtBuilderDlg::UpdateTableItem
// -----------------------------------------------------------------------------------

void CBrtBuilderDlg::UpdateTableItem(DWORD dwNode)
{
	CString s;

	s.Format("%d",dwNode+1);
	M_GETLISTCTRL(IDC_LIST_LCDBRT_NODES)->SetItemText(dwNode,0,s);

	s.Format("%.2f", m_CnfFile.m_ppLcdCurve[m_btBrtMode][1].m_Data[dwNode].GetX());
	M_GETLISTCTRL(IDC_LIST_LCDBRT_NODES)->SetItemText(dwNode,1,s);

	s.Format("%.2f", m_CnfFile.m_ppLcdCurve[m_btBrtMode][1].m_Data[dwNode].GetY());
	M_GETLISTCTRL(IDC_LIST_LCDBRT_NODES)->SetItemText(dwNode,2,s);
}


// -----------------------------------------------------------------------------------
//	CBrtBuilderDlg::OnHScroll
// -----------------------------------------------------------------------------------

void CBrtBuilderDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CString	s;

	if (pScrollBar == GetDlgItem(IDC_SLIDER_LCDBRT_CURSOR))
	{
		m_dwCursorPos = (DWORD)M_GETSLIDER(IDC_SLIDER_LCDBRT_CURSOR)->GetPos();

		UpdateCursors();
	}		


	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}


// -----------------------------------------------------------------------------------
//	CBrtBuilderDlg::OnBnClickedButGenerateLcdpwm
// -----------------------------------------------------------------------------------

void CBrtBuilderDlg::OnBnClickedButGenerateLcdpwm()
{
	CGenerateBrtDlg	d;

	d.m_wDutyMax = m_CnfFile.m_pwLcdPwmMaxDuty[m_btBrtMode];

	if (d.DoModal() == IDOK)
	{
		m_CnfFile.m_pwLcdPwmMaxDuty[m_btBrtMode] = d.m_wDutyMax;

		GenerateLcdBrtPwm();
	}
}



// -----------------------------------------------------------------------------------
//	CBrtBuilderDlg::GenerateLcdBrtPwm
// -----------------------------------------------------------------------------------

void CBrtBuilderDlg::GenerateLcdBrtPwm()
{
	double		dMax;
	double		d;
	DWORD		k;
	double		dFactor;


	dMax = (double)m_CnfFile.m_pwLcdPwmMaxDuty[m_btBrtMode];

	if (m_btBrtMode == 0)	// NVG
	{
		dFactor = dMax / 12.32000075;

		for (k=0; k<256; k++)
		{
			d = dFactor * 12.0 * (1.0 / 800.0) * pow(800.0, ((double)k / 254.0) );
			d = min(65535.0, d);
			m_CnfFile.m_ppLcdCurve[m_btBrtMode][0].m_Data[k].SetY(d);
		}
	}
	else		// DAY
	{
		dFactor = dMax / 692.0470768;

		for (k=0; k<256; k++)
		{
			d = dFactor * 685.0 * pow(((double)k / (254.0) +0.152) / 1.152 , 3.0);
			d = min(65535.0, d);
			m_CnfFile.m_ppLcdCurve[m_btBrtMode][0].m_Data[k].SetY(d);
		}
	}

	RefreshCurve();
	UpdateCursors();
}


// -----------------------------------------------------------------------------------
//	CBrtBuilderDlg::GenerateLcdBrtPwm
// -----------------------------------------------------------------------------------
#if 0
void CBrtBuilderDlg::GenerateLcdBrtPwm()
{
	DWORD		k;
	double		p;
	double		r;
	double		dMin;
	double		dMax;
	double		dDeltaSteps;

	dMin = (double)m_CnfFile.m_pwLcdPwmMinDuty[m_btBrtMode];
	dMax = (double)m_CnfFile.m_pwLcdPwmMaxDuty[m_btBrtMode];
	dDeltaSteps = (double)(m_CnfFile.m_pwLcdPwmMaxStep[m_btBrtMode] - m_CnfFile.m_pwLcdPwmMinStep[m_btBrtMode]);

	double	emax;
	double	k1;

	emax = exp(m_CnfFile.m_pdLcdPwmGamma[m_btBrtMode])-1;
	k1 = (dMax-dMin)/emax;

	for (k=0; k<256; k++)
	{
		if (k < m_CnfFile.m_pwLcdPwmMinStep[m_btBrtMode])
		{
			m_CnfFile.m_ppLcdCurve[m_btBrtMode][0].m_Data[k].SetY(dMin);
		}
		else if (k > m_CnfFile.m_pwLcdPwmMaxStep[m_btBrtMode])
		{
			m_CnfFile.m_ppLcdCurve[m_btBrtMode][0].m_Data[k].SetY(dMax);
		}
		else
		{
			p = exp( m_CnfFile.m_pdLcdPwmGamma[m_btBrtMode] * (((double)(k - m_CnfFile.m_pwLcdPwmMinStep[m_btBrtMode]))/dDeltaSteps)) - 1;

			r = dMin + k1*p;

			m_CnfFile.m_ppLcdCurve[m_btBrtMode][0].m_Data[k].SetY(r);
		}
	}

	RefreshCurve();
	UpdateCursors();
}
#endif

// -----------------------------------------------------------------------------------
//	CBrtBuilderDlg::OnTcnSelchangeTabBrtDn
// -----------------------------------------------------------------------------------

void CBrtBuilderDlg::OnTcnSelchangeTabBrtDn(NMHDR *pNMHDR, LRESULT *pResult)
{
	m_btBrtMode = (BYTE)M_GETTAB(IDC_TAB_BRT_DN)->GetCurSel();
	m_dwCurNode = 0;

	RefreshData();

	*pResult = 0;
}


// -----------------------------------------------------------------------------------
//	CBrtBuilderDlg::OnFilesSave
// -----------------------------------------------------------------------------------

void CBrtBuilderDlg::OnFilesSave()
{
	if (m_CnfFile.m_bNew)
	{
		OnFilesSaveas();
		return;
	}

	m_CnfFile.Save();
}


// -----------------------------------------------------------------------------------
//	CBrtBuilderDlg::OnFilesSaveas
// -----------------------------------------------------------------------------------

void CBrtBuilderDlg::OnFilesSaveas()
{
	CString			sPath;

	CFileDialog *pDlg=new CFileDialog(FALSE,"bin",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_PATHMUSTEXIST,
		"Binary File (*.bin) | *.bin|",this);
	
	if (pDlg->DoModal()==IDOK)
	{
		sPath=pDlg->GetPathName();

		delete pDlg;
	}
	else
	{
		delete pDlg;
		return;
	}

	m_CnfFile.Save(sPath);
	m_ssFilePath.SetWindowText(m_CnfFile.m_sFilePath);
}


// -----------------------------------------------------------------------------------
//	CBrtBuilderDlg::OnFilesOpen
// -----------------------------------------------------------------------------------

void CBrtBuilderDlg::OnFilesOpen()
{
	CString		sPath;
	CString		s;

	CFileDialog* pDlg=new CFileDialog(TRUE,"bin",NULL,OFN_HIDEREADONLY,
		"Binary Files (*.bin) | *.bin|",this);

	s="Select Brightness File";

	pDlg->m_ofn.lpstrTitle=s;
	
	if (pDlg->DoModal()==IDOK)
	{
		sPath=pDlg->GetPathName();

		delete pDlg;
	}
	else
	{
		delete pDlg;
		return;
	}

	if (m_CnfFile.Load(sPath) != e_Return_OK)
	{
		STTE_Message("Cannot load Brightness File",MB_ICONSTOP, this);
		return;
	}

	m_dwCurNode = 0;

	RefreshData();
	RefreshInfo();

	m_ssFilePath.SetWindowText(sPath);

	STTE_Message("Brightness File correctly loaded", MB_ICONINFORMATION, this);
}


// -----------------------------------------------------------------------------------
//	CBrtBuilderDlg::OnCbnSelendokComboPot
// -----------------------------------------------------------------------------------

void CBrtBuilderDlg::OnCbnSelendokComboPot()
{
	m_CnfFile.m_pbtBrtPot[m_btBrtMode] = (BYTE)(M_GETCOMBO(IDC_COMBO_POT)->GetCurSel());
}


// -----------------------------------------------------------------------------------
//	CBrtBuilderDlg::OnEnChangeEditCode
// -----------------------------------------------------------------------------------

void CBrtBuilderDlg::OnEnChangeEditCode()
{
	M_GETEDIT(IDC_EDIT_CODE)->GetWindowText(m_CnfFile.m_sCode);
}


// -----------------------------------------------------------------------------------
//	CBrtBuilderDlg::OnEnChangeEditName
// -----------------------------------------------------------------------------------

void CBrtBuilderDlg::OnEnChangeEditName()
{
	M_GETEDIT(IDC_EDIT_NAME)->GetWindowText(m_CnfFile.m_sName);
}


// -----------------------------------------------------------------------------------
//	CBrtBuilderDlg::OnEnChangeEditAuthor
// -----------------------------------------------------------------------------------

void CBrtBuilderDlg::OnEnChangeEditAuthor()
{
	M_GETEDIT(IDC_EDIT_AUTHOR)->GetWindowText(m_CnfFile.m_sAuthor);
}


// -----------------------------------------------------------------------------------
//	CBrtBuilderDlg::OnEnChangeEditDate
// -----------------------------------------------------------------------------------

void CBrtBuilderDlg::OnEnChangeEditDate()
{
	M_GETEDIT(IDC_EDIT_DATE)->GetWindowText(m_CnfFile.m_sDate);
}


// -----------------------------------------------------------------------------------
//	CBrtBuilderDlg::OnEnChangeEditDate
// -----------------------------------------------------------------------------------

void CBrtBuilderDlg::OnBnClickedButImportLcdpwm()
{
	CString			sPath;

	CFileDialog* pDlg=new CFileDialog(TRUE,"txt",NULL,OFN_HIDEREADONLY,
		"Text Files (*.txt) | *.txt|",this);
	
	if (pDlg->DoModal()==IDOK)
	{
		sPath=pDlg->GetPathName();

		delete pDlg;
	}
	else
	{
		delete pDlg;
		return;
	}

	m_CnfFile.ImportPwmCurve(sPath, m_btBrtMode);
	RefreshData();
}


// -----------------------------------------------------------------------------------
//	CBrtBuilderDlg::OnEnChangeEditDate
// -----------------------------------------------------------------------------------

void CBrtBuilderDlg::OnBnClickedButExportLcdpwm()
{
	CString			sPath;

	CFileDialog *pDlg=new CFileDialog(FALSE, "txt", NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_PATHMUSTEXIST,
		"Text File (*.txt) | *.txt|",this);
	
	if (pDlg->DoModal()==IDOK)
	{
		sPath=pDlg->GetPathName();

		delete pDlg;
	}
	else
	{
		delete pDlg;
		return;
	}

	m_CnfFile.ExportPwmCurve(sPath, m_btBrtMode);
}
