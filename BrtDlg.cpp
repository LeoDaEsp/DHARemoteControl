// BrtDlg.cpp : implementation file
//

#include "stdafx.h"
#include "dha5x5_STTE.h"
#include "BrtDlg.h"
#include "MMDlg.h"

#ifndef FMT_TRACECTRL_H
#include "FMT_TraceCtrl.h"
#endif

#define MAX_CURVE_NODES		100
#define	GRAPH				((CFMT_TraceCtrl*)GetDlgItem(IDC_TRACE))
#define MAINDLG				((CMMDlg*)GetParent())

// CBrtDlg dialog

IMPLEMENT_DYNAMIC(CBrtDlg, CDialog)

CBrtDlg::CBrtDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBrtDlg::IDD, pParent)
{
	m_dwCurNode=0;
	m_btType=e_PWM;
	m_btID=0;
	m_bEditChangeLock=FALSE;

	m_Data.Create(2);
	m_Data[0].SetX(0);
	m_Data[0].SetY(0);
	m_Data[1].SetX(255.0);
	m_Data[1].SetY(100.0);
}

CBrtDlg::~CBrtDlg()
{
}

void CBrtDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CBrtDlg, CDialog)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_NODES, &CBrtDlg::OnLvnItemchangedListNodes)
	ON_BN_CLICKED(IDC_BUT_INSERT, &CBrtDlg::OnBnClickedButInsert)
	ON_BN_CLICKED(IDC_BUT_REMOVE, &CBrtDlg::OnBnClickedButRemove)
	ON_EN_CHANGE(IDC_EDIT_NODE, &CBrtDlg::OnEnChangeEditNode)
	ON_EN_CHANGE(IDC_EDIT_VALUE, &CBrtDlg::OnEnChangeEditValue)
END_MESSAGE_MAP()


// CBrtDlg message handlers

BOOL CBrtDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	// --- Init Trace Control -------------------------------------------

	GRAPH->SetBackgroundColor(RGB(255,255,255));

	GRAPH->EnableAxis(FMTTRCCTL_AXIS_TOP,FALSE);
	GRAPH->EnableAxis(FMTTRCCTL_AXIS_X,FALSE);
	GRAPH->EnableAxis(FMTTRCCTL_AXIS_Y,FALSE);
	GRAPH->EnableAxis(FMTTRCCTL_AXIS_RIGHT,FALSE);

	GRAPH->EnableAxisText(FMTTRCCTL_AXIS_BOTTOM,FALSE);
	GRAPH->EnableAxisText(FMTTRCCTL_AXIS_X,FALSE);
	GRAPH->EnableAxisText(FMTTRCCTL_AXIS_Y,FALSE);
	GRAPH->EnableAxisText(FMTTRCCTL_AXIS_RIGHT,TRUE);
	GRAPH->EnableAxisText(FMTTRCCTL_AXIS_TOP,TRUE);
	GRAPH->EnableAxisText(FMTTRCCTL_AXIS_LEFT,FALSE);

	GRAPH->SetAxis(FMTTRCCTL_AXIS_BOTTOM,RGB(0,0,0),1,1.0,0.0);
	GRAPH->SetAxis(FMTTRCCTL_AXIS_LEFT,RGB(0,0,0),1,1.0,0.0);

	GRAPH->SetGridHorz(FALSE,FMTTRCCTL_AXIS_BOTTOM,RGB(255,0,0),PS_SOLID);
	GRAPH->SetSubGridHorz(TRUE,RGB(220,220,220),PS_SOLID);
	GRAPH->EnableGridHorz(TRUE);
	GRAPH->SetGridVert(FALSE,FMTTRCCTL_AXIS_LEFT,RGB(255,0,0),PS_SOLID);
	GRAPH->SetSubGridVert(TRUE,RGB(220,220,220),PS_SOLID);
	GRAPH->EnableGridVert(TRUE);

	GRAPH->EnableAxisSubTap(FMTTRCCTL_AXIS_BOTTOM,TRUE);
	GRAPH->EnableAxisTapLabel(FMTTRCCTL_AXIS_BOTTOM,TRUE);
	GRAPH->EnableAxisSubTapLabel(FMTTRCCTL_AXIS_BOTTOM,FALSE);

	GRAPH->EnableAxisTap(FMTTRCCTL_AXIS_LEFT,FALSE);
	GRAPH->EnableAxisSubTap(FMTTRCCTL_AXIS_LEFT,TRUE);
	GRAPH->EnableAxisTapLabel(FMTTRCCTL_AXIS_LEFT,FALSE);
	GRAPH->EnableAxisSubTapLabel(FMTTRCCTL_AXIS_LEFT,TRUE);


	GRAPH->SetAxisText(FMTTRCCTL_AXIS_TOP,"PWM(%)",CSize(55,20),RGB(0,0,0),RGB(255,255,255),0,0,FALSE);
	GRAPH->SetAxisText(FMTTRCCTL_AXIS_RIGHT,"Steps",CSize(35,20),RGB(0,0,0),RGB(255,255,255),0,5,FALSE);
		
	GRAPH->SetAxisTap(FMTTRCCTL_AXIS_BOTTOM,RGB(0,0,0),5,100.0);
	GRAPH->SetAxisSubTap(FMTTRCCTL_AXIS_BOTTOM,RGB(0,0,0),3,5);
	GRAPH->SetAxisTapLabel(FMTTRCCTL_AXIS_BOTTOM,RGB(0,0,0),0,0,30);
	GRAPH->SetAxisSubTapLabel(FMTTRCCTL_AXIS_BOTTOM,RGB(0,0,0),0,0,30);

	GRAPH->SetAxisTap(FMTTRCCTL_AXIS_LEFT,RGB(0,0,0),5,100);
	GRAPH->SetAxisSubTap(FMTTRCCTL_AXIS_LEFT,RGB(0,0,0),3,10);
	GRAPH->SetAxisTapLabel(FMTTRCCTL_AXIS_LEFT,RGB(0,0,0),0,0,50);
	GRAPH->SetAxisSubTapLabel(FMTTRCCTL_AXIS_LEFT,RGB(0,0,0),1,0,50);

	GRAPH->SetScale(1.3,1.8);
	GRAPH->ScrollTo(0,0);

	GRAPH->InsertTrace(0, RGB(0,0,255), FMTTRCCTL_TRACE_POINTS|FMTTRCCTL_TRACE_JOIN,
						FMTTRCCTL_COUPLES_DATA,
						!m_Data,
						m_Data.GetBuf(), 1, PS_SOLID);

	// --- Init List Control -----------------------------------------------------------

	M_GETLISTCTRL(IDC_LIST_NODES)->SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	M_GETLISTCTRL(IDC_LIST_NODES)->InsertColumn(0,"Node",LVCFMT_LEFT,40);
	M_GETLISTCTRL(IDC_LIST_NODES)->InsertColumn(1,"Dim",LVCFMT_LEFT,65);
	M_GETLISTCTRL(IDC_LIST_NODES)->InsertColumn(2,"Level",LVCFMT_LEFT,65);
	RefreshList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CBrtDlg::OnOK()
{
	//CDialog::OnOK();
}

void CBrtDlg::OnCancel()
{
	//CDialog::OnCancel();
}

void CBrtDlg::SetType(BYTE btType)
{
	m_btType=btType;

	switch (btType)
	{
	case e_PWM:

		M_GETBUTTON(IDC_BUT_INSERT)->SetWindowText("Import");
		M_GETBUTTON(IDC_BUT_REMOVE)->ModifyStyle(WS_VISIBLE,0);

		GRAPH->SetAxis(FMTTRCCTL_AXIS_BOTTOM,RGB(0,0,0),1,1.0,0.0);
		GRAPH->SetAxis(FMTTRCCTL_AXIS_LEFT,RGB(0,0,0),1,1.0,0.0);

		GRAPH->SetAxisTap(FMTTRCCTL_AXIS_BOTTOM,RGB(0,0,0),5,100.0);
		GRAPH->SetAxisSubTap(FMTTRCCTL_AXIS_BOTTOM,RGB(0,0,0),3,5);
		GRAPH->SetAxisTapLabel(FMTTRCCTL_AXIS_BOTTOM,RGB(0,0,0),0,0,30);
		GRAPH->SetAxisSubTapLabel(FMTTRCCTL_AXIS_BOTTOM,RGB(0,0,0),0,0,30);

		GRAPH->SetAxisTap(FMTTRCCTL_AXIS_LEFT,RGB(0,0,0),5,4000);
		GRAPH->SetAxisSubTap(FMTTRCCTL_AXIS_LEFT,RGB(0,0,0),3,10);
		GRAPH->SetAxisTapLabel(FMTTRCCTL_AXIS_LEFT,RGB(0,0,0),0,0,50);
		GRAPH->SetAxisSubTapLabel(FMTTRCCTL_AXIS_LEFT,RGB(0,0,0),1,0,50);

		GRAPH->SetAxisText(FMTTRCCTL_AXIS_TOP,"PWM(%)",CSize(55,20),RGB(0,0,0),RGB(255,255,255),0,0,FALSE);
		GRAPH->SetScale(1.3,0.04);
		GRAPH->ScrollTo(0,0);
	break;

	case e_VDC:
		M_GETBUTTON(IDC_BUT_INSERT)->SetWindowText("Import");
		M_GETBUTTON(IDC_BUT_REMOVE)->ModifyStyle(WS_VISIBLE,0);

		GRAPH->SetAxis(FMTTRCCTL_AXIS_BOTTOM,RGB(0,0,0),1,1.0,0.0);
		GRAPH->SetAxis(FMTTRCCTL_AXIS_LEFT,RGB(0,0,0),1,1.0,0.0);

		GRAPH->SetAxisTap(FMTTRCCTL_AXIS_BOTTOM,RGB(0,0,0),5,100.0);
		GRAPH->SetAxisSubTap(FMTTRCCTL_AXIS_BOTTOM,RGB(0,0,0),3,5);
		GRAPH->SetAxisTapLabel(FMTTRCCTL_AXIS_BOTTOM,RGB(0,0,0),0,0,30);
		GRAPH->SetAxisSubTapLabel(FMTTRCCTL_AXIS_BOTTOM,RGB(0,0,0),0,0,30);

		GRAPH->SetAxisTap(FMTTRCCTL_AXIS_LEFT,RGB(0,0,0),5,4000);
		GRAPH->SetAxisSubTap(FMTTRCCTL_AXIS_LEFT,RGB(0,0,0),3,10);
		GRAPH->SetAxisTapLabel(FMTTRCCTL_AXIS_LEFT,RGB(0,0,0),0,0,50);
		GRAPH->SetAxisSubTapLabel(FMTTRCCTL_AXIS_LEFT,RGB(0,0,0),1,0,50);

		GRAPH->SetAxisText(FMTTRCCTL_AXIS_TOP,"VDC(V)",CSize(55,20),RGB(0,0,0),RGB(255,255,255),0,0,FALSE);
		GRAPH->SetScale(1.3,0.04);
		GRAPH->ScrollTo(0,0);
	break;

	case e_Temp:
		GRAPH->SetAxis(FMTTRCCTL_AXIS_BOTTOM,RGB(0,0,0),1,1.0,0.0);
		GRAPH->SetAxis(FMTTRCCTL_AXIS_LEFT,RGB(0,0,0),1,1.0,0.0);

		/*GRAPH->SetAxisTap(FMTTRCCTL_AXIS_BOTTOM,RGB(0,0,0),5,1000);
		GRAPH->SetAxisSubTap(FMTTRCCTL_AXIS_BOTTOM,RGB(0,0,0),3,5);
		GRAPH->SetAxisTapLabel(FMTTRCCTL_AXIS_BOTTOM,RGB(0,0,0),0,0,30);
		GRAPH->SetAxisSubTapLabel(FMTTRCCTL_AXIS_BOTTOM,RGB(0,0,0),0,0,30);*/

		GRAPH->SetAxisTap(FMTTRCCTL_AXIS_BOTTOM,RGB(0,0,0),5,50);
		GRAPH->SetAxisSubTap(FMTTRCCTL_AXIS_BOTTOM,RGB(0,0,0),3,5);
		GRAPH->SetAxisTapLabel(FMTTRCCTL_AXIS_BOTTOM,RGB(0,0,0),0,0,50);
		GRAPH->SetAxisSubTapLabel(FMTTRCCTL_AXIS_BOTTOM,RGB(0,0,0),1,0,50);

		GRAPH->SetAxisTap(FMTTRCCTL_AXIS_LEFT,RGB(0,0,0),5,250);
		GRAPH->SetAxisSubTap(FMTTRCCTL_AXIS_LEFT,RGB(0,0,0),3,5);
		GRAPH->SetAxisTapLabel(FMTTRCCTL_AXIS_LEFT,RGB(0,0,0),0,0,50);
		GRAPH->SetAxisSubTapLabel(FMTTRCCTL_AXIS_LEFT,RGB(0,0,0),1,0,50);

		GRAPH->SetAxisText(FMTTRCCTL_AXIS_TOP,"T(°C)",CSize(55,20),RGB(0,0,0),RGB(255,255,255),0,0,FALSE);
		GRAPH->SetAxisText(FMTTRCCTL_AXIS_RIGHT,"T(°C)",CSize(35,20),RGB(0,0,0),RGB(255,255,255),0,5,FALSE);
		//GRAPH->SetScale(0.08,0.75);
		GRAPH->SetScale(1.3,0.5);
		//GRAPH->ScrollTo(0,60);
		GRAPH->ScrollTo(100,60);
	break;

	case e_Photo:

		GRAPH->SetAxis(FMTTRCCTL_AXIS_BOTTOM,RGB(0,0,0),1,1.0,0.0);
		GRAPH->SetAxis(FMTTRCCTL_AXIS_LEFT,RGB(0,0,0),1,1.0,0.0);

		GRAPH->SetAxisTap(FMTTRCCTL_AXIS_BOTTOM,RGB(0,0,0),5,1000);
		GRAPH->SetAxisSubTap(FMTTRCCTL_AXIS_BOTTOM,RGB(0,0,0),3,5);
		GRAPH->SetAxisTapLabel(FMTTRCCTL_AXIS_BOTTOM,RGB(0,0,0),0,0,30);
		GRAPH->SetAxisSubTapLabel(FMTTRCCTL_AXIS_BOTTOM,RGB(0,0,0),0,0,30);

		GRAPH->SetAxisTap(FMTTRCCTL_AXIS_LEFT,RGB(0,0,0),5,500);
		GRAPH->SetAxisSubTap(FMTTRCCTL_AXIS_LEFT,RGB(0,0,0),3,10);
		GRAPH->SetAxisTapLabel(FMTTRCCTL_AXIS_LEFT,RGB(0,0,0),0,0,50);
		GRAPH->SetAxisSubTapLabel(FMTTRCCTL_AXIS_LEFT,RGB(0,0,0),1,0,50);

		GRAPH->SetAxisText(FMTTRCCTL_AXIS_TOP,"Brt Step",CSize(55,20),RGB(0,0,0),RGB(255,255,255),0,0,FALSE);
		GRAPH->SetScale(0.08,0.65);
		GRAPH->ScrollTo(0,0);
	break;
	}

	GRAPH->ReplaceTrace(0,RGB(0,0,255),FMTTRCCTL_TRACE_POINTS|FMTTRCCTL_TRACE_JOIN,
							FMTTRCCTL_COUPLES_DATA,
							!m_Data,
							m_Data.GetBuf(), 1, PS_SOLID);
	RefreshList();
}

// -----------------------------------------------------------------------------------
//	RefreshList
// -----------------------------------------------------------------------------------

void CBrtDlg::RefreshList()
{
	M_GETLISTCTRL(IDC_LIST_NODES)->DeleteAllItems();	
	
	DWORD	k;
	CString	s;

	for (k=0;k<!m_Data;k++)
	{
		s.Format("%d",k+1);
		M_GETLISTCTRL(IDC_LIST_NODES)->InsertItem(k,s);

		s.Format("%.2f",m_Data[k].GetX());
		M_GETLISTCTRL(IDC_LIST_NODES)->SetItemText(k,1,s);

		s.Format("%.2f",m_Data[k].GetY());
		M_GETLISTCTRL(IDC_LIST_NODES)->SetItemText(k,2,s);
	}
}

void CBrtDlg::OnLvnItemchangedListNodes(NMHDR *pNMHDR, LRESULT *pResult)
{
	POSITION pos;
	CString s;

	pos=M_GETLISTCTRL(IDC_LIST_NODES)->GetFirstSelectedItemPosition();

	if (pos==NULL)
		return;

	m_dwCurNode=M_GETLISTCTRL(IDC_LIST_NODES)->GetNextSelectedItem(pos);

	RefreshNode(m_dwCurNode);
	
	*pResult = 0;
}

// -----------------------------------------------------------------------------------
//	RefreshNode
// -----------------------------------------------------------------------------------

void CBrtDlg::RefreshNode(DWORD dwNode)
{
	CString s;

	s.Format("%.2f",m_Data[dwNode].GetX());
	SetCtrlText(IDC_EDIT_NODE,s);

	s.Format("%.2f",m_Data[dwNode].GetY());
	SetCtrlText(IDC_EDIT_VALUE,s);
}

// -----------------------------------------------------------------------------------
//	SetCtrlText
// -----------------------------------------------------------------------------------

void CBrtDlg::SetCtrlText(DWORD dwID,CString s)
{
	CWnd *pW=GetDlgItem(dwID);

	m_bEditChangeLock=TRUE;
	pW->SetWindowText(s);
	pW->GetWindowText(s);
	m_bEditChangeLock=FALSE;

}

// -----------------------------------------------------------------------------------
//	ImportFile
// -----------------------------------------------------------------------------------

BOOL CBrtDlg::ImportFile(CString sPath,CFMT_Vector< CFMT_Point<double> >& data,BYTE btType)
{
	CFMT_File		f;
	CFMT_String		s;
	DWORD			k;

	s=sPath;

	if (!f.Open(s, CFMT_File::e_OpenMode_Read))
	{
		return FALSE;
	}

	try
	{
		k=0;
		while (!(f.IsEOF()))
		{
			f.ReadTextLine(s);

			switch (btType)
			{
			case e_PWM:
			case e_VDC:
			case e_Photo:
				data[k].SetX((double)k);
				data[k].SetY(atof(s.GetStringC()));
			break;

			case e_Temp:
				data[k].SetX((double)k-55.0);
				data[k].SetY(atof(s.GetStringC()));
			break;

			}

			k++;
		}
	}
	catch(...)
	{
		f.Close();
		return FALSE;
	}

	f.Close();

	return TRUE;

}

void CBrtDlg::OnBnClickedButInsert()
{
	CString	sPath;

	CFileDialog *pDlg=new CFileDialog(TRUE,"txt",NULL,OFN_HIDEREADONLY,
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

	if (!ImportFile(sPath,m_Data,m_btType))
	{
		STTE_Message("File error",MB_ICONSTOP);
		return;
	}

	// Update Trace Control
	RefreshList();

	GRAPH->ReplaceTrace(0,RGB(0,0,255),FMTTRCCTL_TRACE_POINTS|FMTTRCCTL_TRACE_JOIN,
							FMTTRCCTL_COUPLES_DATA,
							!m_Data,
							m_Data.GetBuf(), 1, PS_SOLID);

	GRAPH->RedrawWindow();

	UpdateCurve();
}

void CBrtDlg::OnBnClickedButRemove()
{
	CString s;

	if ((m_dwCurNode==0) || (m_dwCurNode>=!m_Data-1))
	{
		STTE_Message("Cannot remove starting and ending nodes",MB_ICONSTOP);
		return;
	}

	s.Format("Node %d will be deleted. Confirm deletion?",m_dwCurNode+1);
	
	if (STTE_Message(s,MB_ICONWARNING|MB_YESNO)!=IDYES)
	{
		return;
	}

	DWORD k;

	m_Data.DeleteItems(m_dwCurNode,1,TRUE);

	M_GETLISTCTRL(IDC_LIST_NODES)->DeleteItem(m_dwCurNode);

	for (k=m_dwCurNode;k<!m_Data;k++)
	{
		UpdateTableItem(k);
	}


	GRAPH->ReplaceTrace(0,RGB(0,0,255),FMTTRCCTL_TRACE_POINTS|FMTTRCCTL_TRACE_JOIN,
							FMTTRCCTL_COUPLES_DATA,
							!m_Data,
							m_Data.GetBuf(), 1, PS_SOLID);

	GRAPH->RedrawWindow();

	UpdateCurve();
}

// -----------------------------------------------------------------------------------
//	UpdateCurve
// -----------------------------------------------------------------------------------

void CBrtDlg::UpdateCurve()
{
	MAINDLG->m_Curves[m_btID]=m_Data;
}

// -----------------------------------------------------------------------------------
//	UpdateTableItem
// -----------------------------------------------------------------------------------

void CBrtDlg::UpdateTableItem(DWORD dwNode)
{
	CString s;

	s.Format("%d",dwNode+1);
	M_GETLISTCTRL(IDC_LIST_NODES)->SetItemText(dwNode,0,s);

	s.Format("%.2f",m_Data[dwNode].GetX());
	M_GETLISTCTRL(IDC_LIST_NODES)->SetItemText(dwNode,1,s);

	s.Format("%.2f",m_Data[dwNode].GetY());
	M_GETLISTCTRL(IDC_LIST_NODES)->SetItemText(dwNode,2,s);
}


// -----------------------------------------------------------------------------------
//	OnEnChangeEditNode
// -----------------------------------------------------------------------------------

void CBrtDlg::OnEnChangeEditNode()
{
	if ((m_dwCurNode==0) || (m_dwCurNode==!m_Data-1))
	{
		return;
	}

	if (m_bEditChangeLock)
		return;

	CString s;
	double d,d1,d2;

	GetDlgItem(IDC_EDIT_NODE)->GetWindowText(s);
	d=atof(s);

	d1=m_Data[m_dwCurNode-1].GetX();
	d2=m_Data[m_dwCurNode+1].GetX();

	if (d<d1)
		d=d1;
	else if (d>d2)
		d=d2;

	m_Data[m_dwCurNode].SetX(d);

	s.Format("%.2f",m_Data[m_dwCurNode].GetX());
	M_GETLISTCTRL(IDC_LIST_NODES)->SetItemText(m_dwCurNode,1,s);
	
	GRAPH->RedrawWindow();

	UpdateCurve();
}


// -----------------------------------------------------------------------------------
//	OnEnChangeEditValue
// -----------------------------------------------------------------------------------

void CBrtDlg::OnEnChangeEditValue()
{
	if (m_bEditChangeLock)
		return;

	CString s;
	double d,d1,d2;

	GetDlgItem(IDC_EDIT_VALUE)->GetWindowText(s);
	d=atof(s);

	switch (m_btType)
	{
	case e_PWM:
		d1=0;
		d2=100.0;
	break;

	case e_VDC:
		d1=0;
		d2=5.0;
	break;

	case e_Temp:
		d1=-55.0;
		d2=180.0;
	break;

	case e_Photo:
		d1=0.0;
		d2=255.0;
	break;
	}

	if (d<d1)
		d=d1;
	else if (d>d2)
		d=d2;

	m_Data[m_dwCurNode].SetY(d);

	s.Format("%.2f",m_Data[m_dwCurNode].GetY());
	M_GETLISTCTRL(IDC_LIST_NODES)->SetItemText(m_dwCurNode,2,s);

	GRAPH->RedrawWindow();

	UpdateCurve();
}
