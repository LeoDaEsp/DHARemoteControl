#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif


#include "resource.h"		// main symbols

// *************************************************************************************
// *************************************************************************************
//	Class CDha5x5_STTEApp
// *************************************************************************************
// *************************************************************************************

class CDha5x5_STTEApp : public CWinApp
{
public:
	CDha5x5_STTEApp();

	public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};


