

#include "stdafx.h"

#include "BtlFile.h"

// *************************************************************************************
// *************************************************************************************
//	Class CBtlFile
// *************************************************************************************
// *************************************************************************************

// -----------------------------------------------------------------------------------
//	CBtlFile::CBtlFile
// -----------------------------------------------------------------------------------

CBtlFile::CBtlFile()
{
	DWORD			k;

	InitCRC16();

	m_pbtMemBuf = new BYTE[BTL_TOT_MEMORY_BYTE_SIZE];
	memset(m_pbtMemBuf, 0, BTL_TOT_MEMORY_BYTE_SIZE);

	m_bNew = TRUE;
	m_bModified = FALSE;

	m_sFilePath = "NewBitlogFile.bin";

	for (k=0; k<64; k++)
	{
		m_psFaultLabel[k] = "spare                          |";
	}

	m_psFaultLabel[0]  = "I/O Expander                   |"; 
	m_psFaultLabel[1]  = "Internal Temperature Sensor    |";
	m_psFaultLabel[2]  = "Flash                          |";
	m_psFaultLabel[3]  = "FRAM                           |";
	m_psFaultLabel[4]  = "ADC1                           |";
	m_psFaultLabel[5]  = "ADC2                           |";
	m_psFaultLabel[6]  = "PS 1.0V                        |";
	m_psFaultLabel[7]  = "PS 1.5V                        |";
	m_psFaultLabel[8]  = "PS 1.8V                        |";
	m_psFaultLabel[9]  = "PS 3.3V                        |";
	m_psFaultLabel[10] = "PS 5.0V                        |";
	m_psFaultLabel[11] = "LCD 3.3V                       |";
	m_psFaultLabel[12] = "NTC #2                         |";
	m_psFaultLabel[13] = "NTC #1                         |";
	m_psFaultLabel[14] = "AD590                          |";
	m_psFaultLabel[15] = "Backlight Driver               |";
	m_psFaultLabel[16] = "Led Day Strip #1               |";
	m_psFaultLabel[17] = "Led Day Strip #2               |";
	m_psFaultLabel[18] = "Led Day Strip #3               |";
	m_psFaultLabel[19] = "Led Day Strip #4               |";
	m_psFaultLabel[20] = "Led NVG Strip #1               |";
	m_psFaultLabel[21] = "Led NVG Strip #2               |";
	m_psFaultLabel[22] = "Led NVG Strip #3               |";
	m_psFaultLabel[23] = "Led NVG Strip #4               |";
	m_psFaultLabel[24] = "Backlight Potentiometer        |";
	m_psFaultLabel[25] = "LCD                            |";
	m_psFaultLabel[26] = "Fan                            |";
	m_psFaultLabel[27] = "Serial TX                      |";
	m_psFaultLabel[28] = "Overtemperature                |";
	m_psFaultLabel[29] = "Day Luminance                  |";
	m_psFaultLabel[30] = "NVG Luminance                  |";
	m_psFaultLabel[31] = "Heater                         |";

	GenerateCrc();
}


// -----------------------------------------------------------------------------------
//	CBtlFile::~CBtlFile
// -----------------------------------------------------------------------------------

CBtlFile::~CBtlFile()
{
	delete[] m_pbtMemBuf;
}

// -----------------------------------------------------------------------------------
//	InitCRC16
// -----------------------------------------------------------------------------------

void CBtlFile::InitCRC16()
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

t_FMT_Uint16 CBtlFile::CalcCRC16Word(t_FMT_Uint16 btCrc,t_FMT_Uint8 btData)
{
	t_FMT_Uint16	wRet;

	wRet = m_pwCrc16Table[btData ^ (btCrc >> 8)] ^ (btCrc << 8);

	return wRet;
}


// -----------------------------------------------------------------------------------
//	CBtlFile::CalcCRC16
// -----------------------------------------------------------------------------------

t_FMT_Uint16 CBtlFile::CalcCRC16(t_FMT_Uint8* pbtData,t_FMT_Uint32 dwSize)
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
//	CBtlFile::SetWord
// -----------------------------------------------------------------------------------

void CBtlFile::SetWord(BYTE *pbtMem,DWORD dwAdd,WORD wValue)
{
	pbtMem[dwAdd]=(BYTE)(wValue & 0xFF);
	pbtMem[dwAdd+1]=(BYTE)((wValue>>8) & 0xFF);
}


// -----------------------------------------------------------------------------------
//	CBtlFile::GetWord
// -----------------------------------------------------------------------------------

WORD CBtlFile::GetWord(BYTE *pbtMem,DWORD dwAdd)
{
	WORD	wValue;

	wValue=(WORD)pbtMem[dwAdd];
	wValue|=(((WORD)pbtMem[dwAdd+1])<<8);

	return wValue;
}


// -----------------------------------------------------------------------------------
//	CBtlFile::SetDWord
// -----------------------------------------------------------------------------------

void CBtlFile::SetDWord(BYTE *pbtMem,DWORD dwAdd,DWORD dwValue)
{
	pbtMem[dwAdd]=(BYTE)(dwValue & 0xFF);
	pbtMem[dwAdd+1]=(BYTE)((dwValue>>8) & 0xFF);
	pbtMem[dwAdd+2]=(BYTE)((dwValue>>16) & 0xFF);
	pbtMem[dwAdd+3]=(BYTE)((dwValue>>24) & 0xFF);
}


// -----------------------------------------------------------------------------------
//	CBtlFile::GetDWord
// -----------------------------------------------------------------------------------

DWORD CBtlFile::GetDWord(BYTE *pbtMem,DWORD dwAdd)
{
	DWORD	dwValue;

	dwValue=(DWORD)pbtMem[dwAdd];
	dwValue|=(((DWORD)pbtMem[dwAdd+1])<<8);
	dwValue|=(((DWORD)pbtMem[dwAdd+2])<<16);
	dwValue|=(((DWORD)pbtMem[dwAdd+3])<<24);

	return dwValue;
}



// -----------------------------------------------------------------------------------
//	CBtlFile::Save
// -----------------------------------------------------------------------------------

DWORD CBtlFile::Save(const CString& sFilePath)
{
	m_sFilePath = sFilePath;

	return Save();
}


// -----------------------------------------------------------------------------------
//	CBtlFile::Save
// -----------------------------------------------------------------------------------

DWORD CBtlFile::Save()
{
	CFile	f;

	if (!f.Open(m_sFilePath,CFile::modeCreate|CFile::modeWrite))
	{
		return e_Return_FileError;
	}

	GenerateCrc();

	try
	{
		f.Write(m_pbtMemBuf, BTL_TOT_MEMORY_BYTE_SIZE);
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
//	CBtlFile::GenerateCrc
// -----------------------------------------------------------------------------------

DWORD CBtlFile::GenerateCrc()
{
	WORD	wCRC;

	wCRC = CalcCRC16(m_pbtMemBuf, BTL_CRC_BO);
	SetWord(m_pbtMemBuf, BTL_CRC_BO, wCRC);

	return e_Return_OK;
}


// -----------------------------------------------------------------------------------
//	CBtlFile::CheckCrc
// -----------------------------------------------------------------------------------

DWORD CBtlFile::CheckCrc(BYTE *pbtBuf)
{
	WORD	wCRC;

	wCRC = CalcCRC16(pbtBuf, BTL_CRC_BO);

	if (wCRC != GetWord(pbtBuf, BTL_CRC_BO))
	{
		return e_Return_Fail;
	}

	return e_Return_OK;
}


// -----------------------------------------------------------------------------------
//	CBtlFile::Load
// -----------------------------------------------------------------------------------

DWORD CBtlFile::Load(const CString& sFilePath)
{
	CFile	f;
	BYTE	*pbtTempBuf;

	if (!f.Open(sFilePath, CFile::modeRead))
	{
		return e_Return_FileError;
	}

	pbtTempBuf = new BYTE[BTL_TOT_MEMORY_BYTE_SIZE];

	try
	{
		f.Read(pbtTempBuf, BTL_TOT_MEMORY_BYTE_SIZE);
	}
	catch(...)
	{
		f.Close();
		delete[] pbtTempBuf;
		return e_Return_FileError;
	}


	f.Close();

	memcpy(m_pbtMemBuf, pbtTempBuf, BTL_TOT_MEMORY_BYTE_SIZE);
	delete[] pbtTempBuf;

	m_bModified = FALSE;
	m_bNew = FALSE;
	m_sFilePath = sFilePath;

	return e_Return_OK;
}



// -----------------------------------------------------------------------------------
//	CBtlFile::ExportMIF
// -----------------------------------------------------------------------------------

DWORD CBtlFile::ExportMIF(const CString& sPath)
{
	CFMT_File		f;
	CString			s;
	DWORD			w;

	if (f.Open((CFMT_String)sPath,CFMT_File::e_OpenMode_Overwrite|CFMT_File::e_OpenMode_Write)!=e_Return_OK)
	{
		return e_Return_FileError;
	}

	GenerateCrc();

	try
	{
		s.Format("DEPTH = %d;",BTL_TOT_MEMORY_BYTE_SIZE);
		f.WriteTextLine(s);
		f.WriteTextLine("WIDTH = 8;");
		f.WriteTextLine("ADDRESS_RADIX = HEX;");
		f.WriteTextLine("DATA_RADIX = HEX;");
		f.WriteTextLine(" ");
		f.WriteTextLine("CONTENT");
		f.WriteTextLine(" ");
		f.WriteTextLine("BEGIN");
		f.WriteTextLine(" ");
		
		for (w=0;w<BTL_TOT_MEMORY_BYTE_SIZE;w++)
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
//	CBtlFile::SetQWord
// -----------------------------------------------------------------------------------

void CBtlFile::SetQWord(BYTE *pbtMem,DWORD dwAdd,t_FMT_Uint64 qwValue)
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
//	CBtlFile::SetFloat
// -----------------------------------------------------------------------------------

void CBtlFile::SetFloat(BYTE *pbtMem,DWORD dwAdd,float fValue)
{
	DWORD	dwValue;

	dwValue=*((DWORD*)(&fValue));

	SetDWord(pbtMem,dwAdd,dwValue);
}


// -----------------------------------------------------------------------------------
//	CBtlFile::SetDouble
// -----------------------------------------------------------------------------------

void CBtlFile::SetDouble(BYTE *pbtMem,DWORD dwAdd,double dValue)
{
	t_FMT_Uint64	quiValue;

	quiValue=*((t_FMT_Uint64*)(&dValue));

	SetQWord(pbtMem,dwAdd,quiValue);
}


// -----------------------------------------------------------------------------------
//	CBtlFile::GetQWord
// -----------------------------------------------------------------------------------

t_FMT_Uint64 CBtlFile::GetQWord(BYTE *pbtMem,DWORD dwAdd)
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
//	CBtlFile::GetFloat
// -----------------------------------------------------------------------------------

float CBtlFile::GetFloat(BYTE *pbtMem,DWORD dwAdd)
{
	DWORD	dwValue;
	float	fValue;

	dwValue=GetDWord(pbtMem,dwAdd);

	fValue=*((float*)(&dwValue));

	return fValue;
}


// -----------------------------------------------------------------------------------
//	CBtlFile::GetDouble
// -----------------------------------------------------------------------------------

double CBtlFile::GetDouble(BYTE *pbtMem,DWORD dwAdd)
{
	t_FMT_Uint64	quiValue;
	double			dValue;

	quiValue=GetQWord(pbtMem,dwAdd);

	dValue=*((double*)(&quiValue));

	return dValue;
}


// -----------------------------------------------------------------------------------
//	CBtlFile::SetEti
// -----------------------------------------------------------------------------------

void CBtlFile::SetEti(DWORD dwEti)
{
	SetDWord(m_pbtMemBuf, 0, dwEti);
}


// -----------------------------------------------------------------------------------
//	CBtlFile::ExportTxt
// -----------------------------------------------------------------------------------

DWORD CBtlFile::ExportTxt(const CString& sPath)
{
	CFMT_File		f;
	CString			s;
	CString			sh;
	DWORD			dwTemp;
	DWORD			k;
	DWORD			dwAdd;
	CString			sLastEti;

	if (f.Open((CFMT_String)sPath, CFMT_File::e_OpenMode_Overwrite | CFMT_File::e_OpenMode_Write) != e_Return_OK)
	{
		return e_Return_FileError;
	}

	try
	{
		// --- ETI ---------------------
		
		dwTemp = GetDWord(m_pbtMemBuf, 0);
		s = "ETI = " + GetEtiString(dwTemp);
		f.WriteTextLine(s);
		f.WriteTextLine("");


		// --- Faults ---------------------

		s = "----|-------------------------------|-------|------|------|-----------------------------------";  
		f.WriteTextLine(s);
		s = " ID | Fault                         | Count | PBIT | CBIT | Last ETI       ";  
		f.WriteTextLine(s);
		s = "----|-------------------------------|-------|------|------|-----------------------------------";  
		f.WriteTextLine(s);

		//     1 | PS 1.0V                  | 65535 | YES  | NO   | 16789203

		dwAdd = 8;

		for (k=0; k<64; k++)
		{
			s.Format(" %02d |", k + 1);
			s += m_psFaultLabel[k];

			// Count
			sh.Format(" %5d |", GetWord(m_pbtMemBuf, dwAdd));
			s += sh;
			dwAdd += 2;

			sLastEti = GetEtiString(GetDWord(m_pbtMemBuf, dwAdd));
			dwAdd += 4;

			if (FMT::GetBit(m_pbtMemBuf[dwAdd], 0))
			{
				sh = " Yes  |";
			}
			else
			{
				sh = "  No  |";
			}
			s += sh;
			
			if (FMT::GetBit(m_pbtMemBuf[dwAdd], 1))
			{
				sh = " Yes  |";
			}
			else
			{
				sh = "  No  |";
			}
			s += sh;

			s += sLastEti;
			dwAdd += 2;

			f.WriteTextLine(s);
		}

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


