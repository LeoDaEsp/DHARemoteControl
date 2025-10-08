#pragma once
#include <cstring>

#include "INI.h"


typedef struct stcIniEntry
{
	CString szSection;
	CString szName;
	CString szDefault;

}type_stcIniEntry;

typedef enum enmSetupTestBenchCfgIniList
{
	//Configuration files
	INI_TB_MAINT_IPADDR = 0,
	INI_TB_MAINT_REMPORT,
	INI_TB_MAINT_COM,

	INI_TB_CFG__LOAD_DEF_FILE_PATH,

	INI_TB_CFG__LOAD_CAL_FILE_PATH,
	INI_TB_CFG__LOAD_CAL_ADDPAR_PN,
	INI_TB_CFG__LOAD_CAL_ADDPAR_NAME,
	INI_TB_CFG__LOAD_CAL_ADDPAR_AUTHOR,




	NUM_OF_INI_CFG

}type_enmSetupTestBenchCfgIniList;








class CIniFileMng
{

public:


	int	LoadCfgFileINI(CString strFilePath);
	CString	m_arIniTbCfgSzData[NUM_OF_INI_CFG];

	CIniFileMng();
	~CIniFileMng();

	void LoadDefaultCfg();
	


};

