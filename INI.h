/************************************************************
* IniFile.h:			CIniReader class
* Author:				Stafano Morrocchi
* Copyright:			Saitec s.r.l
************************************************************/
#pragma once

#include <afxcoll.h>

class CIniReader
{
public:
	// method to set INI file name, if not already specified 
	void setINIFileName(CString strINIFile);

	// methods to return the lists of section data and section names
	CStringList* getSectionData(CString strSection);
	CStringList* getSectionNames();

	// check if the section exists in the file
	BOOL sectionExists(CString strSection);

	// updates the key value, if key already exists, else creates a key-value pair
	long setKey(CString strValue, CString strKey, CString strSection);

	// give the key value for the specified key of a section
	CString getKeyValue(const CString& strSection,
		const CString& strKey,
		CString szDefault = _T(""));

	// default constructor
	CIniReader()
	{
		m_sectionList = new CStringList();
		m_sectionDataList = new CStringList();
		m_lRetValue = 0;
	}

	CIniReader(CString strFile)
	{
		m_strFileName = strFile;
		m_sectionList = new CStringList();
		m_sectionDataList = new CStringList();
		m_lRetValue = 0;
	}

	~CIniReader()
	{
		delete m_sectionList;
		m_sectionList = NULL;

		delete m_sectionDataList;
		m_sectionDataList = NULL;
	}

private:
	// lists to keep sections and section data
	CStringList* m_sectionDataList;
	CStringList* m_sectionList;

	CString			m_strSection;
	long			m_lRetValue;

	// ini file name 
	CString		 m_strFileName;
};