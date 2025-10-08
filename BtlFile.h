
#pragma once


#define BTL_TOT_MEMORY_BYTE_SIZE		522

#define BTL_CRC_BO						(BTL_TOT_MEMORY_BYTE_SIZE - 2)

#define BTL_TOT_ACTIVE_FAULTS			33


// *************************************************************************************
// *************************************************************************************
//	Class CBtlFile
// *************************************************************************************
// *************************************************************************************

class CBtlFile : public CFMT_HdwObject
{
	// =====================================================================================
	//	TYPES
	// =====================================================================================

protected:

public:

	// =====================================================================================
	//	VARIABLES
	// =====================================================================================

protected:


public:

	BYTE				*m_pbtMemBuf;
	t_FMT_Uint16		m_pwCrc16Table[256];
	t_FMT_Uint8			m_pbtByteFlip[256];

	BOOL				m_bNew;
	BOOL				m_bModified;
	CString				m_sFilePath;

	CString				m_psFaultLabel[64];


	// =====================================================================================
	// CONSTRUCTORS & DESTRUCTORS
	// =====================================================================================


public:

	CBtlFile();
	virtual ~CBtlFile();

	// =====================================================================================
	//	FUNCTIONS
	// =====================================================================================

protected:

	t_FMT_Uint16	CalcCRC16Word(t_FMT_Uint16 btCrc,t_FMT_Uint8 btData);
	void			InitCRC16();
	t_FMT_Uint16	CalcCRC16(t_FMT_Uint8* pbtData,t_FMT_Uint32 dwNB);
	DWORD			GenerateCrc();
	DWORD			CheckCrc(BYTE *pbtBuf);
	void			SetWord(BYTE *pbtMem,DWORD dwAdd,WORD wValue);
	WORD			GetWord(BYTE *pbtMem,DWORD dwAdd);
	void			SetDWord(BYTE *pbtMem,DWORD dwAdd,DWORD dwValue);
	DWORD			GetDWord(BYTE *pbtMem,DWORD dwAdd);
	void			SetQWord(BYTE *pbtMem,DWORD dwAdd,t_FMT_Uint64 qwValue);
	t_FMT_Uint64	GetQWord(BYTE *pbtMem,DWORD dwAdd);
	void			SetFloat(BYTE *pbtMem,DWORD dwAdd,float fValue);
	float			GetFloat(BYTE *pbtMem,DWORD dwAdd);
	void			SetDouble(BYTE *pbtMem,DWORD dwAdd,double dValue);
	double			GetDouble(BYTE *pbtMem,DWORD dwAdd);



public:

	DWORD				Save(const CString& sFilePath);
	DWORD				Save();
	DWORD				Load(const CString& sFilePath);
	DWORD				ExportMIF(const CString& sPath);
	DWORD				ExportTxt(const CString& sPath);

	void				SetEti(DWORD dwEti);


};
