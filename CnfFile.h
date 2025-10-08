
#pragma once


#define CNF_TOT_MEMORY_BYTE_SIZE		0x04B02

#define CNF_CODE_BO						0x00000
#define CNF_NAME_BO						0x00010
#define CNF_DATE_BO						0x00038
#define CNF_AUTHOR_BO					0x00042

#define CNF_BRT_NVG_POT_BO				0x00100	
#define CNF_BRT_DAY_POT_BO				0x00101
#define CNF_BRTFBK_NVG_THRESH_BO		0x00102
#define CNF_BRTFBK_DAY_THRESH_BO		0x00103

#define CNF_BRT_WORKSPACE_START_BO		0x00200	
#define CNF_BRT_GEN_PARAM_WO			(CNF_BRT_WORKSPACE_START_BO / 2)	
#define CNF_BRT_CURR_NODES_WO			((CNF_BRT_WORKSPACE_START_BO + 32) / 2)	

#define CNF_BRT_LUT_START_BO			0x00300	

#define CNF_BRTFBK_LUT_START_BO			0x00B00	

#define CNF_CRC_BO						0x04B00

#define CNF_CODE_LENGTH					14
#define CNF_NAME_LENGTH					40
#define CNF_DATE_LENGTH					10
#define CNF_AUTHOR_LENGTH				20

#define CNF_MAX_CURVE_NODES				15


// *************************************************************************************
// *************************************************************************************
//	Class CCnfFile
// *************************************************************************************
// *************************************************************************************

class CCnfFile : public CFMT_HdwObject
{
	// =====================================================================================
	//	TYPES
	// =====================================================================================

protected:

public:

	// --- CCurve ---------------------------------------------

	class CCurve : public CObject
	{
	public:

		CFMT_Vector< CFMT_Point<double> > m_Data;
		//CFMT_Vector<SPoint>	m_Data;
		CCurve();
		CCurve(const CCurve& op);
		~CCurve();
		virtual void DataCopy(const CCurve& op);
		virtual CCurve& operator=(const CCurve& op);
	};


	// =====================================================================================
	//	VARIABLES
	// =====================================================================================

protected:

	BYTE				*m_pbtMemBuf;

public:

	BOOL				m_bNew;
	BOOL				m_bModified;
	CString				m_sFilePath;

	CString				m_sCode;
	CString				m_sName;
	CString				m_sDate;
	CString				m_sAuthor;

	BYTE				m_pbtBrtPot[2];
	BYTE				m_pbtBrtFbkThresh[2];

	t_FMT_Uint8			m_pppucBrtFbkLut[2][2][4096];

	t_FMT_Uint16		m_pwCrc16Table[256];
	t_FMT_Uint8			m_pbtByteFlip[256];

	CCurve				m_ppLcdCurve[2][2];

	WORD				m_pwLcdPwmMinStep[2];
	WORD				m_pwLcdPwmMaxStep[2];
	WORD				m_pwLcdPwmMinDuty[2];
	WORD				m_pwLcdPwmMaxDuty[2];
	double				m_pdLcdPwmGamma[2];


	// =====================================================================================
	// CONSTRUCTORS & DESTRUCTORS
	// =====================================================================================


public:

	CCnfFile();
	virtual ~CCnfFile();

	// =====================================================================================
	//	FUNCTIONS
	// =====================================================================================

protected:

	t_FMT_Uint16		CalcCRC16Word(t_FMT_Uint16 btCrc,t_FMT_Uint8 btData);
	void				InitCRC16();
	t_FMT_Uint16		CalcCRC16(t_FMT_Uint8* pbtData,t_FMT_Uint32 dwNB);
	DWORD				GenerateInfo();
	DWORD				GenerateParams();
	void				GeneratePointCurve(CCurve& curve,DWORD dwPoints,DWORD dwWordAdd,double dMaxY, double dMaxDig);
	void				GenerateNodesCurve(CCurve& curve,DWORD dwPoints,DWORD dwWordAdd,double dMaxX,double dMaxY, double dMaxDig);
	void				GenerateNodes(CCurve& curve, DWORD dwWordAdd);
	DWORD				GenerateCurves();
	void				GenerateWorkspace();
	void				GenerateBrtFbkCurves();
	DWORD				GenerateCrc();
	DWORD				ImportInfo();
	DWORD				ImportParams();
	DWORD				ImportCurves();
	void				ImportWorkspace();
	void				ImportBrtFbkCurves();
	void				ImportNodes(CCurve& curve, DWORD dwWordAdd);
	DWORD				CheckCrc(BYTE *pbtBuf);
	void				SetWord(BYTE *pbtMem,DWORD dwAdd,WORD wValue);
	WORD				GetWord(BYTE *pbtMem,DWORD dwAdd);
	void				SetDWord(BYTE *pbtMem,DWORD dwAdd,DWORD dwValue);
	DWORD				GetDWord(BYTE *pbtMem,DWORD dwAdd);
	void				SetQWord(BYTE *pbtMem,DWORD dwAdd,t_FMT_Uint64 qwValue);
	t_FMT_Uint64		GetQWord(BYTE *pbtMem,DWORD dwAdd);
	void				SetFloat(BYTE *pbtMem,DWORD dwAdd,float fValue);
	float				GetFloat(BYTE *pbtMem,DWORD dwAdd);
	void				SetDouble(BYTE *pbtMem,DWORD dwAdd,double dValue);
	double				GetDouble(BYTE *pbtMem,DWORD dwAdd);



public:

	DWORD				GenerateMemory();
	DWORD				ImportMemory();
	DWORD				Save(const CString& sFilePath);
	DWORD				Save();
	DWORD				Load(const CString& sFilePath);
	DWORD				ExportMIF(const CString& sPath);
	DWORD				ExportPwmCurve(const CString& sPath, BYTE btBrtMode);
	DWORD				ImportPwmCurve(const CString& sPath, BYTE btBrtMode);

	DWORD				CreateFbkBrt(BOOL bDay, t_FMT_Uint16* pusHiCurve, t_FMT_Uint16* pusLoCurve);


};
