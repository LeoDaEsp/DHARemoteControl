/************************************************************
* IniFile.cpp:			implementation of the CIniReader class
* Author:				Stafano Morrocchi
* Copyright:			Saitec s.r.l
************************************************************/
#include "stdafx.h"
#include "INI.h"
#include <afxcoll.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

/****************************************************************************
* CString CIniReader::getKeyValue(CString strKey,CString strSection)
*
* Used to retrieve a value give the section and key
***************************************************************************/
CString CIniReader::getKeyValue(const CString& strSection,
	const CString& strKey,
	CString strDefault /*=_T("")*/)
{
	TCHAR ac_Result[255];

	// Get the info from the .ini file	
	m_lRetValue = GetPrivateProfileString((LPCTSTR)strSection, (LPCTSTR)strKey,
		(LPCTSTR)strDefault, ac_Result, 255, (LPCTSTR)m_strFileName);

	CString strResult(ac_Result);
	return strResult;
}

/****************************************************************************
* long CIniReader::setKey(CString strValue, CString strKey, CString strSection)
*
* Used to add or set a key value pair to a section
***************************************************************************/
long CIniReader::setKey(CString strValue, CString strKey, CString strSection)
{
	m_lRetValue = WritePrivateProfileString(strSection, strKey,
		strValue, m_strFileName);

	return m_lRetValue;
}
/****************************************************************************
* BOOL CIniReader::sectionExists(CString strSection)
*
* Used to find out if a given section exists
***************************************************************************/
BOOL CIniReader::sectionExists(CString strSection)
{
	TCHAR ac_Result[100];
	CString csAux;
	// Get the info from the .ini file	
	m_lRetValue = GetPrivateProfileString((LPCTSTR)strSection, NULL,
		_T(""), ac_Result, 90, (LPCTSTR)m_strFileName);
	// Return if we could retrieve any info from that section
	return (m_lRetValue > 0);
}
/****************************************************************************
* CStringList* CIniReader::getSectionNames()
*
* Used to retrieve all of the  section names in the ini file
* returns collection of section names
***************************************************************************/
CStringList* CIniReader::getSectionNames()
{
	TCHAR ac_Result[2000];
	m_sectionList->RemoveAll();

	m_lRetValue = GetPrivateProfileSectionNames(ac_Result, 2000, (LPCTSTR)m_strFileName);

	CString strSectionName;
	for (int i = 0; i < m_lRetValue; i++)
	{
		if (ac_Result[i] != '\0') {
			strSectionName = strSectionName + ac_Result[i];
		}
		else {
			if (strSectionName != _T("")) {
				m_sectionList->InsertAfter(m_sectionList->GetTailPosition(), strSectionName);
			}
			strSectionName = _T("");
		}
	}

	return m_sectionList;
}
/****************************************************************************
* CStringList* CIniReader::getSectionData(CString strSection)
*
* Used to retrieve all key/value pairs of a given section.
***************************************************************************/
CStringList* CIniReader::getSectionData(CString strSection)
{
	TCHAR ac_Result[2000];  //change size depending on needs
	m_sectionDataList->RemoveAll();
	m_lRetValue = GetPrivateProfileSection((LPCTSTR)strSection, ac_Result, 2000, (LPCTSTR)m_strFileName);

	CString strSectionData;
	for (int i = 0; i < m_lRetValue; i++)
	{
		if (ac_Result[i] != '\0') {
			strSectionData = strSectionData + ac_Result[i];
		}
		else {
			if (strSectionData != _T("")) {
				m_sectionDataList->InsertAfter(m_sectionDataList->GetTailPosition(), strSectionData);
			}
			strSectionData = _T("");
		}
	}

	return m_sectionDataList;
}
/****************************************************************************
* void CIniReader::setINIFileName(CString strINIFile)
*
*
***************************************************************************/
void CIniReader::setINIFileName(CString strINIFile)
{
	m_strFileName = strINIFile;
}
