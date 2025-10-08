// stdafx.cpp : source file that includes just the standard includes
//	dha5x5_STTE.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

// -----------------------------------------------------------------------------------
//	::STTE_Message
// -----------------------------------------------------------------------------------

int STTE_Message(const CString& sText,int iParam, CWnd* pParent)
{
	if (pParent == NULL)
	{
		return ::MessageBox(0, sText, "DHA5x5 STTE", iParam);
	}
	else
	{
		return ::MessageBox(pParent->m_hWnd, sText, "DHA5x5 STTE", iParam);
	}
}


// -----------------------------------------------------------------------------------
//	::GetEtiString
// -----------------------------------------------------------------------------------

CString	GetEtiString(DWORD dwEti)
{
	DWORD		dwSec;
	DWORD		dwMin;
	DWORD		dwHour;
	DWORD		dwTemp;
	CString		s;

	dwTemp=dwEti;

	dwHour=dwTemp/3600;
	dwMin=dwTemp/60-dwHour*60;
	dwSec=dwTemp-dwHour*3600-dwMin*60;

	s.Format("%dh:%02dm:%02ds",dwHour,dwMin,dwSec);

	return s;
}


// -----------------------------------------------------------------------------------
//	::GetLogTimeString
// -----------------------------------------------------------------------------------

CString	GetLogTimeString(DWORD dwEti)
{
	DWORD		dwSec;
	DWORD		dwMin;
	DWORD		dwHour;
	DWORD		dwMs;
	DWORD		dwTemp;
	CString		s;

	dwTemp=dwEti;

	dwHour = (dwTemp/3600000);
	dwMin = (dwTemp/60000) - (dwHour*60);
	dwSec = (dwTemp/1000) - (dwHour*3600) - (dwMin*60);
	dwMs = dwTemp - (dwHour*3600000) - (dwMin*60000) - (dwSec*1000);

	s.Format("%dh:%02dm:%02ds:%03dms", dwHour, dwMin, dwSec, dwMs);

	return s;
}
