// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__B65FFCFF_3C0F_4410_A861_7847149858D8__INCLUDED_)
#define AFX_STDAFX_H__B65FFCFF_3C0F_4410_A861_7847149858D8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT
#include <afxmt.h>


#include "FMT_Core.h"
#include "FMT_Hdw.h"
#include "FMT_Comm.h"
#include "SmartStatic.h"
#include "SmartListCtrl.h"
#include "StatusListCtrl.h"


#define STTE_CODE			"XA00095A01"
#define STTE_INTERV			"A"

//#define DHA55_COMPILE_NOHDW
//#define STTE_COMPILE_02


// ----- Control Macroes ------------------------------

#define M_GETBUTTON(id)		((CButton*)GetDlgItem(id))
#define M_GETEDIT(id)		((CEdit*)GetDlgItem(id))
#define M_GETSTATIC(id)		((CStatic*)GetDlgItem(id))
#define M_GETSLIDER(id)		((CSliderCtrl*)GetDlgItem(id))
#define M_GETCOMBO(id)		((CComboBox*)GetDlgItem(id))
#define M_GETTAB(id)		((CTabCtrl*)GetDlgItem(id))
#define M_GETLISTBOX(id)	((CListBox*)GetDlgItem(id))
#define M_GETLIST(id)		((CListCtrl*)GetDlgItem(id))
#define M_GETLISTCTRL(id)	((CListCtrl*)GetDlgItem(id))
#define M_GETPROGRESS(id)	((CProgressCtrl*)GetDlgItem(id))
#define M_GETBIT(data,bit)	((data & ((1ull)<<(bit)))>0)
#define M_GETDATEPICKER(id)	((CDateTimeCtrl*)GetDlgItem(id))
#define M_GETIPADDCTRL(id)	((CIPAddressCtrl*)GetDlgItem(id))


// --- Colors ---------------------------------------------

#define STTE_COLOR_YELLOW		RGB(253,248,215)
#define STTE_COLOR_GREEN		RGB(120,255,120)
#define STTE_COLOR_RED			RGB(255,120,120)
#define STTE_COLOR_LIGHTGREY	RGB(220,220,220)
#define STTE_COLOR_ORANGE		RGB(255,128,0)
#define STTE_COLOR_GREY			RGB(200,200,200)
#define STTE_COLOR_WHITE		RGB(255,255,255)


// --- Timing ---------------------------------------------

// General Timer
#define DHA55_REFRESHTIMER_ID			0
#define DHA55_REFRESHTIMER_TIMEOUT		300

#define DHA55_READTIMER_ID				2
#define DHA55_READTIMER_TIMEOUT			300

#define DHA55_MAINTTIMER_ID				1
#define DHA55_MAINTTIMER_TIMEOUT		200

#define DHA55_STTETIMER_ID				3
#define DHA55_STTETIMER_TIMEOUT			100

#define STTE_CFGLOADER_TIMER_ID			5
#define STTE_CFGLOADER_TIMER_VAL		200

#define STTE_BTLLOADER_TIMER_ID			6
#define STTE_BTLLOADER_TIMER_VAL		200

#define STTE_MAINT_TIMER_ID				7
#define STTE_MAINT_TIMER_VAL			100

#define DHA55_CALIBTIMER_ID				8
#define DHA55_CALIBTIMER_VAL			100

#define DHA55_TIMEOUTECHO				200
#define DHA55_RETRIES					1

#define STTE_MAINT_LINK_TIMEOUT			(1500 / DHA55_REFRESHTIMER_TIMEOUT)

#define TIMEOUTNOPARAM					3000



#define DHA5X5_BRTCURVE_SIZE	(2*0x100)	// Bytes
#define DHA5X5_TRIMCURVE_SIZE	(0x2000)	// Bytes

#define DHA5X5_CURR_OFF_FAN		(0x8000)
#define DHA5X5_CURR_ON_FAN_LO	(0x8002)
#define DHA5X5_CURR_ON_FAN_HI	(0x8004)

//#define DHA5X5_PWM_00_CURVE		0x00000
#define DHA5X5_PWM_00_CURVE		(DHA5X5_VDC_00_CURVE+8*DHA5X5_BRTCURVE_SIZE)
//#define DHA5X5_VDC_00_CURVE		(DHA5X5_PWM_00_CURVE+8*DHA5X5_BRTCURVE_SIZE)
#define DHA5X5_VDC_00_CURVE		0x00000

//#define DHA5X5_TRIM_00_CURVE	(DHA5X5_VDC_00_CURVE+8*DHA5X5_BRTCURVE_SIZE)
#define DHA5X5_TRIM_00_CURVE	(DHA5X5_PWM_00_CURVE+8*DHA5X5_BRTCURVE_SIZE)

#define DHA5X5_MEMORYSIZE		(DHA5X5_TRIM_00_CURVE+3*DHA5X5_TRIMCURVE_SIZE+8192+6)


#define DHA55_TESTMESS			WM_USER+1






int				STTE_Message(const CString& sText,int iParam, CWnd* pParent = NULL);
CString			GetLogTimeString(DWORD dwEti);
CString			GetEtiString(DWORD dwEti);


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__B65FFCFF_3C0F_4410_A861_7847149858D8__INCLUDED_)
