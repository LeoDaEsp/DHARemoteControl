#include "stdafx.h"

#include "IniFileMng.h"

//IniSection Def

static type_stcIniEntry IniTbCfgMap[NUM_OF_INI_CFG] =
{
	{ _T("CFG_MAINT"),		_T("IPADDR"),			_T("192.168.1.77") },
	{ _T("CFG_MAINT"),		_T("PORT"),				_T("3040") }		,
	{ _T("CFG_MAINT"),		_T("COM"),				_T("COM1") }		,

	{ _T("CFG_LOAD"),		_T("LOAD_DEF_FILE_PATH"),	_T("C:\\Users\\ING_TEST\\Desktop\\DHA5x5\\Dha5x5_STTE_r777\\Dha5x5_STTE_Srcs_r777\\Release\\") }	,

	{ _T("CFG_CALFILE"),	_T("LOAD_CAL_FILE_PATH"),	_T("C:\\Users\\saitec\\Desktop\\TSD_PROJECT\\SMC_LUT_CAL.bin") },
	{ _T("CFG_CALFILE"),	_T("LOAD_CAL_PN"),			_T("PBR-0723/01.01 A04") }	,
	{ _T("CFG_CALFILE"),	_T("LOAD_CAL_NAME"),		_T("SMC init file, LCD BCKL, AL OK, ANN OK") },
	{ _T("CFG_CALFILE"),	_T("LOAD_CAL_AUTHOR"),		_T("F. Liberatori") }

};


void CIniFileMng::LoadDefaultCfg() {

	for (unsigned int i = 0; i < NUM_OF_INI_CFG; i++)
	{
		m_arIniTbCfgSzData[i] = IniTbCfgMap[i].szDefault;
	}

}


CIniFileMng::CIniFileMng()
{


}


CIniFileMng::~CIniFileMng()
{
}


int	CIniFileMng::LoadCfgFileINI(CString strFilePath)
{

	CIniFileMng::LoadDefaultCfg();


	bool bExist = ::PathFileExists(strFilePath);
	if (bExist == false)
	{
		AfxMessageBox(_T("Setup file missing...\nDefault Setup will be Applied"), MB_ICONWARNING);
	}

	CIniReader* pFileIni = new CIniReader(strFilePath);

	if (bExist == false)
	{
		for (unsigned int i = 0; i < NUM_OF_INI_CFG; i++)
		{
			pFileIni->setKey(IniTbCfgMap[i].szDefault, IniTbCfgMap[i].szName, IniTbCfgMap[i].szSection);
		}
	}

	for (unsigned int i = 0; i < NUM_OF_INI_CFG; i++)
	{
		m_arIniTbCfgSzData[i] = pFileIni->getKeyValue(IniTbCfgMap[i].szSection, IniTbCfgMap[i].szName, IniTbCfgMap[i].szDefault);
	}

	delete pFileIni;

	if (bExist)
		return 0;
	else
		return 1;
}