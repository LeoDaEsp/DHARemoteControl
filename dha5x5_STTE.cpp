// dha5x5_STTE.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "dha5x5_STTE.h"
#include "dha5x5_STTEDlg.h"
#include "SelectUnitDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDha5x5_STTEApp

BEGIN_MESSAGE_MAP(CDha5x5_STTEApp, CWinApp)
	//{{AFX_MSG_MAP(CDha5x5_STTEApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDha5x5_STTEApp construction

CDha5x5_STTEApp::CDha5x5_STTEApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CDha5x5_STTEApp object

CDha5x5_STTEApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CDha5x5_STTEApp initialization

BOOL CDha5x5_STTEApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Leonardo"));

	CFMT_String		sAppPath;
	CFMT_String		sLicFile;
	CFMT_String		sAppFile;
	t_FMT_Uint32	uiPos;

	sAppPath = (CStringA)m_pszHelpFilePath;

	if (sAppPath.FindFromEnd('\\', &uiPos))
	{
		sAppPath = sAppPath.Left(uiPos);
	}


	sLicFile = sAppPath + "\\DllAuthCode.lic";
	sAppFile = sAppPath + "\\dha5x5_STTE.exe";

	LFMT_Comm_LoadLicense(sLicFile, sAppFile);

	#ifdef STTE_COMPILE_02
	CDha5x5_STTEDlg dlg;
	dlg.m_dwUnitRev = 2;
	#else
	CSelectUnitDlg		dlg;
	#endif

	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;


}
