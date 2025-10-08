

#include "stdafx.h"

#include "CnfFile.h"


// *************************************************************************************
// *************************************************************************************
//	Class CCnfFile::CCurve
// *************************************************************************************
// *************************************************************************************



// =====================================================================================
// CONSTRUCTORS & DESTRUCTORS
// =====================================================================================


// -----------------------------------------------------------------------------------
//	CCnfFile::CCurve::CCurve
// -----------------------------------------------------------------------------------

CCnfFile::CCurve::CCurve()
{
}

CCnfFile::CCurve::CCurve(const CCurve& op)
{
	DataCopy(op);
}


// -----------------------------------------------------------------------------------
//	CCnfFile::CCurve::~CCurve
// -----------------------------------------------------------------------------------

CCnfFile::CCurve::~CCurve()
{
}



// =====================================================================================
//	FUNCTIONS
// =====================================================================================

// -----------------------------------------------------------------------------------
//	CCnfFile::CCurve::operator=
// -----------------------------------------------------------------------------------

CCnfFile::CCurve& CCnfFile::CCurve::operator=(const CCurve& op)
{
	DataCopy(op);

	return (*this);
}

// -----------------------------------------------------------------------------------
//	CCnfFile::CCurve::DataCopy
// -----------------------------------------------------------------------------------

void CCnfFile::CCurve::DataCopy(const CCurve& op)
{
	m_Data = op.m_Data;
}

 


// *************************************************************************************
// *************************************************************************************
//	Class CCnfFile
// *************************************************************************************
// *************************************************************************************

// -----------------------------------------------------------------------------------
//	CCnfFile::CCnfFile
// -----------------------------------------------------------------------------------

CCnfFile::CCnfFile()
{
	DWORD			k;
	DWORD			w;
	DWORD			j;

	InitCRC16();

	m_pbtBrtPot[0] = m_pbtBrtPot[1] = 0x7F;
	m_pbtBrtFbkThresh[0] = m_pbtBrtFbkThresh[1] = 0x3F;

	m_pbtMemBuf = new BYTE[CNF_TOT_MEMORY_BYTE_SIZE];
	memset(m_pbtMemBuf, 0, CNF_TOT_MEMORY_BYTE_SIZE);

	m_bNew = TRUE;
	m_bModified = FALSE;

	m_sFilePath = "NewBrtFile.bin";

	// --- Potentiometer Levels ------------------------

	for (k=0; k<2; k++)
	{
		m_pbtBrtPot[k] = 64;
	}

	// --- LCD PWM Generation Parameters ------------------------

	for (k=0; k<2; k++)
	{
		m_pwLcdPwmMinStep[k] = 0;
		m_pwLcdPwmMaxStep[k] = 255;
		m_pwLcdPwmMinDuty[k] = 0;
		m_pwLcdPwmMaxDuty[k] = 65535;
		m_pdLcdPwmGamma[k] = 2.0;
	}

	// --- Build default LCD Brightness Curves ------------------------
	
	for (k=0; k<2; k++)
	{
		// PWM
		m_ppLcdCurve[k][0].m_Data.Create(256);

		for (w=0; w<256; w++)
		{
			m_ppLcdCurve[k][0].m_Data[w].SetX((float)w);
			m_ppLcdCurve[k][0].m_Data[w].SetY((float)(w*(65535.0/255.0)));
		}

		// Current
		m_ppLcdCurve[k][1].m_Data.Create(2);

		m_ppLcdCurve[k][1].m_Data[0].SetX(0);
		m_ppLcdCurve[k][1].m_Data[0].SetY(0);

		m_ppLcdCurve[k][1].m_Data[1].SetX(255.0);
		m_ppLcdCurve[k][1].m_Data[1].SetY(4095.0);
	}

	// --- Build default LCD Brightness Feedback Curve ------------------------
	
	for (k=0; k<2; k++)
	{
		for (j=0; j<2; j++)
		{
			for (w=0; w<256; w++)
			{
				m_pppucBrtFbkLut[k][j][w] = 0;
			}
		}
	}

}


// -----------------------------------------------------------------------------------
//	CCnfFile::~CCnfFile
// -----------------------------------------------------------------------------------

CCnfFile::~CCnfFile()
{
	delete[] m_pbtMemBuf;
}

// -----------------------------------------------------------------------------------
//	InitCRC16
// -----------------------------------------------------------------------------------

void CCnfFile::InitCRC16()
{
	int		i,j,w;
	t_FMT_Uint16	crc;

	for (i=0; i<256; i++) 
	{
		crc = i<<8;

		for (j=0; j<8; j++)
		{
			crc = (crc << 1) ^ ((crc & 0x8000) ? (0x1021) : 0);
		}

		m_pwCrc16Table[i] = crc;
		m_pbtByteFlip[i]=0;

		for (w=0;w<8;w++)
		{
			if ((i & (1<<w))>0)
			{
				m_pbtByteFlip[i] |= (1<<(7-w));
			}
		}
	}
}


// -----------------------------------------------------------------------------------
//	CalcCRC16Word
// -----------------------------------------------------------------------------------

t_FMT_Uint16 CCnfFile::CalcCRC16Word(t_FMT_Uint16 btCrc,t_FMT_Uint8 btData)
{
	t_FMT_Uint16	wRet;

	wRet = m_pwCrc16Table[btData ^ (btCrc >> 8)] ^ (btCrc << 8);

	return wRet;
}


// -----------------------------------------------------------------------------------
//	CCnfFile::CalcCRC16
// -----------------------------------------------------------------------------------

t_FMT_Uint16 CCnfFile::CalcCRC16(t_FMT_Uint8* pbtData,t_FMT_Uint32 dwSize)
{
	t_FMT_Uint16	wTemp;
	t_FMT_Uint32	k;

	wTemp = 0xFFFF;

	for (k=0; k<dwSize; k++)
	{
		wTemp = CalcCRC16Word(wTemp,pbtData[k]);
	}

	return wTemp;
}


// -----------------------------------------------------------------------------------
//	CCnfFile::SetWord
// -----------------------------------------------------------------------------------

void CCnfFile::SetWord(BYTE *pbtMem,DWORD dwAdd,WORD wValue)
{
	pbtMem[dwAdd]=(BYTE)(wValue & 0xFF);
	pbtMem[dwAdd+1]=(BYTE)((wValue>>8) & 0xFF);
}


// -----------------------------------------------------------------------------------
//	CCnfFile::GetWord
// -----------------------------------------------------------------------------------

WORD CCnfFile::GetWord(BYTE *pbtMem,DWORD dwAdd)
{
	WORD	wValue;

	wValue=(WORD)pbtMem[dwAdd];
	wValue|=(((WORD)pbtMem[dwAdd+1])<<8);

	return wValue;
}


// -----------------------------------------------------------------------------------
//	CCnfFile::SetDWord
// -----------------------------------------------------------------------------------

void CCnfFile::SetDWord(BYTE *pbtMem,DWORD dwAdd,DWORD dwValue)
{
	pbtMem[dwAdd]=(BYTE)(dwValue & 0xFF);
	pbtMem[dwAdd+1]=(BYTE)((dwValue>>8) & 0xFF);
	pbtMem[dwAdd+2]=(BYTE)((dwValue>>16) & 0xFF);
	pbtMem[dwAdd+3]=(BYTE)((dwValue>>24) & 0xFF);
}


// -----------------------------------------------------------------------------------
//	CCnfFile::GetDWord
// -----------------------------------------------------------------------------------

DWORD CCnfFile::GetDWord(BYTE *pbtMem,DWORD dwAdd)
{
	DWORD	dwValue;

	dwValue=(DWORD)pbtMem[dwAdd];
	dwValue|=(((DWORD)pbtMem[dwAdd+1])<<8);
	dwValue|=(((DWORD)pbtMem[dwAdd+2])<<16);
	dwValue|=(((DWORD)pbtMem[dwAdd+3])<<24);

	return dwValue;
}



// -----------------------------------------------------------------------------------
//	CCnfFile::Save
// -----------------------------------------------------------------------------------

DWORD CCnfFile::Save(const CString& sFilePath)
{
	m_sFilePath = sFilePath;

	return Save();
}


// -----------------------------------------------------------------------------------
//	CCnfFile::Save
// -----------------------------------------------------------------------------------

DWORD CCnfFile::Save()
{
	CFile	f;

	if (!f.Open(m_sFilePath,CFile::modeCreate|CFile::modeWrite))
	{
		return e_Return_FileError;
	}

	GenerateMemory();

	try
	{
		f.Write(m_pbtMemBuf, CNF_TOT_MEMORY_BYTE_SIZE);
	}
	catch(...)
	{
		f.Close();
		return e_Return_FileError;
	}


	f.Close();

	m_bModified=FALSE;
	m_bNew=FALSE;

	return e_Return_OK;
}




// -----------------------------------------------------------------------------------
//	CCnfFile::GenerateInfo
// -----------------------------------------------------------------------------------

DWORD CCnfFile::GenerateInfo()
{
	CString		s;

	// Code
	memset(m_pbtMemBuf + CNF_CODE_BO, 0x20, CNF_CODE_LENGTH);
	memcpy(m_pbtMemBuf + CNF_CODE_BO, m_sCode, strlen(m_sCode));

	// Name
	memset(m_pbtMemBuf + CNF_NAME_BO, 0x20, CNF_NAME_LENGTH);
	memcpy(m_pbtMemBuf + CNF_NAME_BO, m_sName, strlen(m_sName));

	// Date
	memset(m_pbtMemBuf + CNF_DATE_BO, 0x20, CNF_DATE_LENGTH);
	memcpy(m_pbtMemBuf + CNF_DATE_BO, m_sDate, strlen(m_sDate));

	// Author
	memset(m_pbtMemBuf + CNF_AUTHOR_BO, 0x20, CNF_AUTHOR_LENGTH);
	memcpy(m_pbtMemBuf + CNF_AUTHOR_BO, m_sAuthor, strlen(m_sAuthor));
	
	return e_Return_OK;
}

// -----------------------------------------------------------------------------------
//	CCnfFile::ImportInfo
// -----------------------------------------------------------------------------------

DWORD CCnfFile::ImportInfo()
{
	CString		s;
	char		pchTemp[200];

	// Code
	memcpy(pchTemp,m_pbtMemBuf + CNF_CODE_BO, CNF_CODE_LENGTH);
	pchTemp[CNF_CODE_LENGTH] = '\0';
	m_sCode.Format("%s",pchTemp);
	m_sCode.Trim();

	// Name
	memcpy(pchTemp,m_pbtMemBuf + CNF_NAME_BO, CNF_NAME_LENGTH);
	pchTemp[CNF_NAME_LENGTH] = '\0';
	m_sName.Format("%s",pchTemp);
	m_sName.Trim();

	// Date
	memcpy(pchTemp, m_pbtMemBuf + CNF_DATE_BO, CNF_DATE_LENGTH);
	pchTemp[CNF_DATE_LENGTH] = '\0';
	m_sDate.Format("%s",pchTemp);
	m_sDate.Trim();

	// Author
	memcpy(pchTemp,m_pbtMemBuf + CNF_AUTHOR_BO, CNF_AUTHOR_LENGTH);
	pchTemp[CNF_AUTHOR_LENGTH] = '\0';
	m_sAuthor.Format("%s",pchTemp);
	m_sAuthor.Trim();

	return e_Return_OK;
}



// -----------------------------------------------------------------------------------
//	CCnfFile::GenerateParams
// -----------------------------------------------------------------------------------

DWORD CCnfFile::GenerateParams()
{
	m_pbtMemBuf[CNF_BRT_NVG_POT_BO] = m_pbtBrtPot[0];
	m_pbtMemBuf[CNF_BRT_DAY_POT_BO] = m_pbtBrtPot[1];

	m_pbtMemBuf[CNF_BRTFBK_NVG_THRESH_BO] = m_pbtBrtFbkThresh[0];
	m_pbtMemBuf[CNF_BRTFBK_DAY_THRESH_BO] = m_pbtBrtFbkThresh[1];

	return e_Return_OK;
}


// -----------------------------------------------------------------------------------
//	CCnfFile::GeneratePointCurve
// -----------------------------------------------------------------------------------

void CCnfFile::GeneratePointCurve(CCurve& curve, DWORD dwPoints, DWORD dwWordAdd, double dMaxY, double dMaxDig)
{
	DWORD		k;
	WORD		wTemp;
	DWORD		dwAdd;

	//dwAdd = 2*(dwWordAdd);
	dwAdd = dwWordAdd;

	for (k=0; k<dwPoints; k++)
	{
		wTemp = (WORD)((curve.m_Data[k].GetY() / dMaxY) * dMaxDig);

		if (wTemp > (WORD)dMaxDig)
		{
			wTemp = (WORD)dMaxDig;
		}

		SetWord(m_pbtMemBuf, dwAdd + 4*k, wTemp);
	}
}

// -----------------------------------------------------------------------------------
//	CCnfFile::GenerateNodesCurve
// -----------------------------------------------------------------------------------

void CCnfFile::GenerateNodesCurve(CCurve& curve,DWORD dwPoints,DWORD dwWordAdd,double dMaxX,double dMaxY, double dMaxDig)
{
	WORD				wTemp;
	DWORD				dwAdd;
	DWORD				k;
	DWORD				w;
	CFMT_Point<double>	pw1;
	CFMT_Point<double>	pw2;
	double				m,q,res;

	// Generate curve data -------------------------------------------------------

	//dwAdd = 2*(dwWordAdd) + 2;
	dwAdd = dwWordAdd + 2;

	pw1 = curve.m_Data[0];
	pw1.SetX(min((float)(pw1.GetX() / dMaxX*(dwPoints-1)), dwPoints));
	pw1.SetY(min((float)(pw1.GetY() / dMaxY*dMaxDig), (float)dMaxDig));
	w = 0;
	for (k=1; k<!(curve.m_Data), w<dwPoints; k++)
	{	
		pw2 = curve.m_Data[k];
		pw2.SetX(min((float)(pw2.GetX() / dMaxX*(dwPoints-1)), dwPoints));
		pw2.SetY(min((float)(pw2.GetY() / dMaxY*dMaxDig), (float)dMaxDig));

		if (pw2.GetX() == pw1.GetX())
		{
			wTemp = (WORD)pw2.GetY();

			SetWord(m_pbtMemBuf, dwAdd + 4*w, wTemp);
		}
		else
		{
			m = ((double)(pw2.GetY())-(double)(pw1.GetY())) / ((double)(pw2.GetX())-(double)(pw1.GetX()));
			q = (double)(pw2.GetY()) - m*(double)(pw2.GetX());

			for (w=(WORD)(pw1.GetX()); w<=(WORD)(pw2.GetX()); w++)
			{
				res = (m*w+q);

				if (res < 0)
				{
					wTemp = 0;
				}
				else if (res > dMaxDig)
				{
					wTemp = (WORD)dMaxDig;
				}
				else
				{
					wTemp = (WORD)(res+0.5);
				}
			
				SetWord(m_pbtMemBuf, dwAdd + 4*w, wTemp);
			}
		}

		pw1 = pw2;
	}
}



// -----------------------------------------------------------------------------------
//	CCnfFile::ImportParams
// -----------------------------------------------------------------------------------

DWORD CCnfFile::ImportParams()
{
	m_pbtBrtPot[0] = m_pbtMemBuf[CNF_BRT_NVG_POT_BO];
	m_pbtBrtPot[1] = m_pbtMemBuf[CNF_BRT_DAY_POT_BO];

	m_pbtBrtFbkThresh[0] = m_pbtMemBuf[CNF_BRTFBK_NVG_THRESH_BO];
	m_pbtBrtFbkThresh[1] = m_pbtMemBuf[CNF_BRTFBK_DAY_THRESH_BO];

	return e_Return_OK;
}


// -----------------------------------------------------------------------------------
//	CCnfFile::GenerateCrc
// -----------------------------------------------------------------------------------

DWORD CCnfFile::GenerateCrc()
{
	WORD	wCRC;

	wCRC = CalcCRC16(m_pbtMemBuf, CNF_CRC_BO);
	SetWord(m_pbtMemBuf, CNF_CRC_BO, wCRC);

	return e_Return_OK;
}


// -----------------------------------------------------------------------------------
//	CCnfFile::CheckCrc
// -----------------------------------------------------------------------------------

DWORD CCnfFile::CheckCrc(BYTE *pbtBuf)
{
	WORD	wCRC;

	wCRC = CalcCRC16(pbtBuf, CNF_CRC_BO);

	if (wCRC != GetWord(pbtBuf, CNF_CRC_BO))
	{
		return e_Return_Fail;
	}

	return e_Return_OK;
}


// -----------------------------------------------------------------------------------
//	CCnfFile::Load
// -----------------------------------------------------------------------------------

DWORD CCnfFile::Load(const CString& sFilePath)
{
	CFile	f;
	BYTE	*pbtTempBuf;

	if (!f.Open(sFilePath, CFile::modeRead))
	{
		return e_Return_FileError;
	}

	pbtTempBuf = new BYTE[CNF_TOT_MEMORY_BYTE_SIZE];

	try
	{
		f.Read(pbtTempBuf, CNF_TOT_MEMORY_BYTE_SIZE);
	}
	catch(...)
	{
		f.Close();
		delete[] pbtTempBuf;
		return e_Return_FileError;
	}


	f.Close();

	memcpy(m_pbtMemBuf, pbtTempBuf, CNF_TOT_MEMORY_BYTE_SIZE);
	delete[] pbtTempBuf;

	if (ImportMemory() != e_Return_OK)
	{
		return e_Return_FileError;
	}


	m_bModified = FALSE;
	m_bNew = FALSE;
	m_sFilePath = sFilePath;

	return e_Return_OK;
}


// -----------------------------------------------------------------------------------
//	CCnfFile::ImportMemory
// -----------------------------------------------------------------------------------

DWORD CCnfFile::ImportMemory()
{
	DWORD	dwRet;

	dwRet = CheckCrc(m_pbtMemBuf);

	if (dwRet != e_Return_OK)
	{
		return dwRet;
	}

	ImportInfo();
	ImportParams();
	ImportCurves();
	ImportBrtFbkCurves();
	ImportWorkspace();

	return e_Return_OK;
}


// -----------------------------------------------------------------------------------
//	CCnfFile::ExportMIF
// -----------------------------------------------------------------------------------

DWORD CCnfFile::ExportMIF(const CString& sPath)
{
	CFMT_File		f;
	CString			s;
	DWORD			w;

	if (f.Open((CFMT_String)sPath,CFMT_File::e_OpenMode_Overwrite|CFMT_File::e_OpenMode_Write)!=e_Return_OK)
	{
		return e_Return_FileError;
	}

	GenerateMemory();

	try
	{
		s.Format("DEPTH = %d;",CNF_TOT_MEMORY_BYTE_SIZE);
		f.WriteTextLine(s);
		f.WriteTextLine("WIDTH = 8;");
		f.WriteTextLine("ADDRESS_RADIX = HEX;");
		f.WriteTextLine("DATA_RADIX = HEX;");
		f.WriteTextLine(" ");
		f.WriteTextLine("CONTENT");
		f.WriteTextLine(" ");
		f.WriteTextLine("BEGIN");
		f.WriteTextLine(" ");
		
		for (w=0;w<CNF_TOT_MEMORY_BYTE_SIZE;w++)
		{
			s.Format("%05X: %02X;",w,m_pbtMemBuf[w]);
			f.WriteTextLine(s);
		}


		f.WriteTextLine(" ");
		f.WriteTextLine("END");

		f.Close();
	}
	catch(...)
	{
		f.Close();
		return e_Return_FileError;
	}


	f.Close();

	return e_Return_OK;
}


// -----------------------------------------------------------------------------------
//	CCnfFile::SetQWord
// -----------------------------------------------------------------------------------

void CCnfFile::SetQWord(BYTE *pbtMem,DWORD dwAdd,t_FMT_Uint64 qwValue)
{
	pbtMem[dwAdd]=(BYTE)(qwValue & 0xFF);
	pbtMem[dwAdd+1]=(BYTE)((qwValue>>8) & 0xFF);
	pbtMem[dwAdd+2]=(BYTE)((qwValue>>16) & 0xFF);
	pbtMem[dwAdd+3]=(BYTE)((qwValue>>24) & 0xFF);
	pbtMem[dwAdd+4]=(BYTE)((qwValue>>32) & 0xFF);
	pbtMem[dwAdd+5]=(BYTE)((qwValue>>40) & 0xFF);
	pbtMem[dwAdd+6]=(BYTE)((qwValue>>48) & 0xFF);
	pbtMem[dwAdd+7]=(BYTE)((qwValue>>56) & 0xFF);
}


// -----------------------------------------------------------------------------------
//	CCnfFile::SetFloat
// -----------------------------------------------------------------------------------

void CCnfFile::SetFloat(BYTE *pbtMem,DWORD dwAdd,float fValue)
{
	DWORD	dwValue;

	dwValue=*((DWORD*)(&fValue));

	SetDWord(pbtMem,dwAdd,dwValue);
}


// -----------------------------------------------------------------------------------
//	CCnfFile::SetDouble
// -----------------------------------------------------------------------------------

void CCnfFile::SetDouble(BYTE *pbtMem,DWORD dwAdd,double dValue)
{
	t_FMT_Uint64	quiValue;

	quiValue=*((t_FMT_Uint64*)(&dValue));

	SetQWord(pbtMem,dwAdd,quiValue);
}


// -----------------------------------------------------------------------------------
//	CCnfFile::GetQWord
// -----------------------------------------------------------------------------------

t_FMT_Uint64 CCnfFile::GetQWord(BYTE *pbtMem,DWORD dwAdd)
{
	t_FMT_Uint64	qwValue;

	qwValue=(t_FMT_Uint64)pbtMem[dwAdd];
	qwValue|=(((t_FMT_Uint64)pbtMem[dwAdd+1])<<8);
	qwValue|=(((t_FMT_Uint64)pbtMem[dwAdd+2])<<16);
	qwValue|=(((t_FMT_Uint64)pbtMem[dwAdd+3])<<24);
	qwValue|=(((t_FMT_Uint64)pbtMem[dwAdd+4])<<32);
	qwValue|=(((t_FMT_Uint64)pbtMem[dwAdd+5])<<40);
	qwValue|=(((t_FMT_Uint64)pbtMem[dwAdd+6])<<48);
	qwValue|=(((t_FMT_Uint64)pbtMem[dwAdd+7])<<56);

	return qwValue;
}


// -----------------------------------------------------------------------------------
//	CCnfFile::GetFloat
// -----------------------------------------------------------------------------------

float CCnfFile::GetFloat(BYTE *pbtMem,DWORD dwAdd)
{
	DWORD	dwValue;
	float	fValue;

	dwValue=GetDWord(pbtMem,dwAdd);

	fValue=*((float*)(&dwValue));

	return fValue;
}


// -----------------------------------------------------------------------------------
//	CCnfFile::GetDouble
// -----------------------------------------------------------------------------------

double CCnfFile::GetDouble(BYTE *pbtMem,DWORD dwAdd)
{
	t_FMT_Uint64	quiValue;
	double			dValue;

	quiValue=GetQWord(pbtMem,dwAdd);

	dValue=*((double*)(&quiValue));

	return dValue;
}




// -----------------------------------------------------------------------------------
//	CCnfFile::GenerateCurves
// -----------------------------------------------------------------------------------

DWORD CCnfFile::GenerateCurves()
{
	DWORD		c;

	for (c=0; c<2; c++)
	{
		GeneratePointCurve(m_ppLcdCurve[c][0], 256, CNF_BRT_LUT_START_BO + 0x400*c, 65535.0, 65535);
		GenerateNodesCurve(m_ppLcdCurve[c][1], 256, CNF_BRT_LUT_START_BO + 0x400*c, 255.0, 4095.0, 4095.0);
	}

	return e_Return_OK;
}



// -----------------------------------------------------------------------------------
//	CCnfFile::ImportCurves
// -----------------------------------------------------------------------------------

DWORD CCnfFile::ImportCurves()
{
	WORD				wTemp;
	DWORD				dwAdd;
	DWORD				k;
	DWORD				c;

	for (c=0; c<2; c++)
	{
		dwAdd = CNF_BRT_LUT_START_BO + 0x400*c;

		for (k=0; k<256; k++)
		{
			wTemp = GetWord(m_pbtMemBuf, dwAdd + 4*k);
			m_ppLcdCurve[c][0].m_Data[k].SetY(((double)wTemp));
		}
	}

	return e_Return_OK;
}



// -----------------------------------------------------------------------------------
//	CCnfFile::GenerateMemory
// -----------------------------------------------------------------------------------

DWORD CCnfFile::GenerateMemory()
{
	memset(m_pbtMemBuf, CNF_TOT_MEMORY_BYTE_SIZE, 0);

	GenerateInfo();
	GenerateParams();
	GenerateCurves();
	GenerateWorkspace();
	GenerateBrtFbkCurves();
	GenerateCrc();

	return e_Return_OK;
}


// -----------------------------------------------------------------------------------
//	CCnfFile::GenerateWorkspace
// -----------------------------------------------------------------------------------

void CCnfFile::GenerateWorkspace()
{
	DWORD		k;

	// --- LCD PWM Generation Parameters ------------------------

	for (k=0; k<2; k++)
	{
		SetWord(m_pbtMemBuf,(2*(CNF_BRT_GEN_PARAM_WO + k*8 + 0)), m_pwLcdPwmMinStep[k]);
		SetWord(m_pbtMemBuf,(2*(CNF_BRT_GEN_PARAM_WO + k*8 + 1)), m_pwLcdPwmMaxStep[k]);
		SetWord(m_pbtMemBuf,(2*(CNF_BRT_GEN_PARAM_WO + k*8 + 2)), m_pwLcdPwmMinDuty[k]);
		SetWord(m_pbtMemBuf,(2*(CNF_BRT_GEN_PARAM_WO + k*8 + 3)), m_pwLcdPwmMaxDuty[k]);
		SetDouble(m_pbtMemBuf,(2*(CNF_BRT_GEN_PARAM_WO + k*8 + 4)),m_pdLcdPwmGamma[k]);
	}

	// Curve Nodes
	for (k=0; k<2; k++)
	{
		GenerateNodes(m_ppLcdCurve[k][1], CNF_BRT_CURR_NODES_WO + 64*k);
	}
}


// -----------------------------------------------------------------------------------
//	CCnfFile::GenerateBrtFbkCurves
// -----------------------------------------------------------------------------------

void CCnfFile::GenerateBrtFbkCurves()
{
	DWORD		day;
	DWORD		hl;
	DWORD		k;
	DWORD		pos;

	for (day = 0; day < 2; day++)
	{
		for (hl = 0; hl < 2; hl++)
		{
			for (k = 0; k < 4096; k++)
			{
				pos = CNF_BRTFBK_LUT_START_BO + (day * 8192) + (hl * 4096) + k;
				m_pbtMemBuf[pos] = m_pppucBrtFbkLut[day][hl][k];
			}
		}

		m_pbtMemBuf[CNF_BRTFBK_NVG_THRESH_BO + day] = m_pbtBrtFbkThresh[day];
	}
}


// -----------------------------------------------------------------------------------
//	CCnfFile::ImportBrtFbkCurves
// -----------------------------------------------------------------------------------

void CCnfFile::ImportBrtFbkCurves()
{
	DWORD		day;
	DWORD		hl;
	DWORD		k;
	DWORD		pos;

	for (day = 0; day < 2; day++)
	{
		for (hl = 0; hl < 2; hl++)
		{
			for (k = 0; k < 4096; k++)
			{
				pos = CNF_BRTFBK_LUT_START_BO + (day * 8912) + (hl * 4096) + k;
				m_pppucBrtFbkLut[day][hl][k] = m_pbtMemBuf[pos];
			}
		}

		m_pbtBrtFbkThresh[day] = m_pbtMemBuf[CNF_BRTFBK_NVG_THRESH_BO + day];
	}
}


// -----------------------------------------------------------------------------------
//	CCnfFile::ImportWorkspace
// -----------------------------------------------------------------------------------

void CCnfFile::ImportWorkspace()
{
	DWORD		k;

	// --- LCD PWM Generation Parameters ------------------------

	for (k=0; k<2; k++)
	{
		m_pwLcdPwmMinStep[k] = GetWord(m_pbtMemBuf,(2*(CNF_BRT_GEN_PARAM_WO + k*8 + 0)));
		m_pwLcdPwmMaxStep[k] = GetWord(m_pbtMemBuf,(2*(CNF_BRT_GEN_PARAM_WO + k*8 + 1)));
		m_pwLcdPwmMinDuty[k] = GetWord(m_pbtMemBuf,(2*(CNF_BRT_GEN_PARAM_WO + k*8 + 2)));
		m_pwLcdPwmMaxDuty[k] = GetWord(m_pbtMemBuf,(2*(CNF_BRT_GEN_PARAM_WO + k*8 + 3)));
		m_pdLcdPwmGamma[k] = GetDouble(m_pbtMemBuf,(2*(CNF_BRT_GEN_PARAM_WO + k*8 + 4)));
	}

	// Curve Nodes
	for (k=0; k<2; k++)
	{
		ImportNodes(m_ppLcdCurve[k][1], CNF_BRT_CURR_NODES_WO + 64*k);
	}
}


// -----------------------------------------------------------------------------------
//	CCnfFile::GenerateNodes
// -----------------------------------------------------------------------------------

void CCnfFile::GenerateNodes(CCurve& curve, DWORD dwWordAdd)
{
	DWORD	dwAdd;
	DWORD	k;

	dwAdd = 2*dwWordAdd;

	SetWord(m_pbtMemBuf, dwAdd, !curve.m_Data);
	dwAdd+=2;

	for (k=0; k<CNF_MAX_CURVE_NODES; k++)
	{
		if (k < !curve.m_Data)
		{
			SetFloat(m_pbtMemBuf, dwAdd, (float)curve.m_Data[k].GetX());
			dwAdd+=4;
			SetFloat(m_pbtMemBuf,dwAdd, (float)curve.m_Data[k].GetY());
			dwAdd+=4;
		}
		else
		{
		}
	}
}


// -----------------------------------------------------------------------------------
//	CCnfFile::ImportNodes
// -----------------------------------------------------------------------------------

void CCnfFile::ImportNodes(CCurve& curve, DWORD dwWordAdd)
{
	DWORD	dwAdd;
	DWORD	k;
	WORD	wTemp;

	dwAdd = 2*dwWordAdd;

	wTemp = min(GetWord(m_pbtMemBuf, dwAdd), CNF_MAX_CURVE_NODES);
	curve.m_Data.DeleteAll();
	curve.m_Data.Create(wTemp);
	dwAdd+=2;

	for (k=0; k<!curve.m_Data; k++)
	{
		curve.m_Data[k].SetX(GetFloat(m_pbtMemBuf,dwAdd));
		dwAdd+=4;
		curve.m_Data[k].SetY(GetFloat(m_pbtMemBuf,dwAdd));
		dwAdd+=4;
	}
}


// -----------------------------------------------------------------------------------
//	CCnfFile::ExportPwmCurve
// -----------------------------------------------------------------------------------

DWORD CCnfFile::ExportPwmCurve(const CString& sPath, BYTE btBrtMode)
{
	CFMT_File		f;
	DWORD			k;
	CFMT_String		s;
	
	if (f.Open((CFMT_String)sPath, CFMT_File::e_OpenMode_Overwrite | CFMT_File::e_OpenMode_Write) != e_Return_OK)
	{
		return e_Return_FileError;
	}

	for (k=0; k < 256; k++)
	{
		s.Format("%d", (int)(m_ppLcdCurve[btBrtMode][0].m_Data[k].GetY()));
		f.WriteTextLine(s);
	}



	f.Close();

	return e_Return_OK;
}


// -----------------------------------------------------------------------------------
//	CCnfFile::ImportPwmCurve
// -----------------------------------------------------------------------------------

DWORD CCnfFile::ImportPwmCurve(const CString& sPath, BYTE btBrtMode)
{
	CFMT_File		f;
	DWORD			k;
	CFMT_String		s;
	
	if (f.Open((CFMT_String)sPath, CFMT_File::e_OpenMode_Read) != e_Return_OK)
	{
		return e_Return_FileError;
	}

	for (k=0; k < 256; k++)
	{
		m_ppLcdCurve[btBrtMode][0].m_Data[k].SetY(0.0);
	}

	for (k=0; k < 256; k++)
	{
		f.ReadTextLine(s);
		m_ppLcdCurve[btBrtMode][0].m_Data[k].SetY((double)(s.ToUnsigned(10)));
	}


	f.Close();

	return e_Return_OK;
}


// -----------------------------------------------------------------------------------
//	CCnfFile::CreateFbkBrt
// -----------------------------------------------------------------------------------

DWORD CCnfFile::CreateFbkBrt(BOOL bDay, t_FMT_Uint16* pusHiCurve, t_FMT_Uint16* pusLoCurve)
{
	t_FMT_Uint16*			pusCurve;
	DWORD					hl;
	DWORD					p;
	WORD					wPrec;
	WORD					wSucc;
	WORD					wThresh;
	WORD					wOldThresh;
	DWORD					k;
	BYTE					ucMaxStep;
	WORD					usMaxLevel;

	
	// --- Generate Feedback Brightness Curve ------------------------------------------------

	wOldThresh = 0;
	usMaxLevel = 0;
	ucMaxStep = 0;

	//for (hl=1; hl<2; hl++)
	//for (hl=0; hl<1; hl++)
	for (hl=0; hl<2; hl++)
	{
		if (hl == 0)
		{
			pusCurve = pusLoCurve;
		}
		else
		{
			pusCurve = pusHiCurve;
		}

		for (p=0; p<256; p++)
		{
			if (p > 0)
			{
				wPrec = pusCurve[p - 1];
				wSucc = pusCurve[p];

				if (hl == 1)
				{
					if (wPrec < 4000)
					{
						m_pbtBrtFbkThresh[bDay] = (BYTE)(p - 1);
					}

					if (wSucc < 4000)
					{
						m_pbtBrtFbkThresh[bDay] = (BYTE)(p);
					}
				}
				
				wThresh = (wSucc + wPrec) / 2;

				for (k = wOldThresh; k < wThresh; k++)
				{
					m_pppucBrtFbkLut[bDay][hl][k] = (BYTE)(p - 1);

					if (k > usMaxLevel)
					{
						ucMaxStep = (BYTE)(p - 1);
					}
				}

				wOldThresh = wThresh;
			}
		}

		for (k = wOldThresh; k < 4096; k++)
		{
			m_pppucBrtFbkLut[bDay][hl][k] = 255;
			//m_pppucBrtFbkLut[bDay][hl][k] = ucMaxStep;
		}



		// DUMP (debug)
		CString			s;

		for (k=0; k<4096; k++)
		{
			s.Format("[0x%03X] = %d\n", k, m_pppucBrtFbkLut[bDay][hl][k]);
			OutputDebugString(s);
		}

		
		// --- Check Feedback Brightness Curve ------------------------------------------------

	}


	return e_Return_OK;
}

