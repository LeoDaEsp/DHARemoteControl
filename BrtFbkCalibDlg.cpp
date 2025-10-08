// BrtFbkCalibDlg.cpp : implementation file
//

#include "stdafx.h"
#include "dha5x5_STTE.h"
#include "BrtFbkCalibDlg.h"
#include "CnfFile.h"


// CBrtFbkCalibDlg dialog

IMPLEMENT_DYNAMIC(CBrtFbkCalibDlg, CDialog)

// -----------------------------------------------------------------------------------
//	CBrtFbkCalibDlg::CBrtFbkCalibDlg
// -----------------------------------------------------------------------------------

CBrtFbkCalibDlg::CBrtFbkCalibDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBrtFbkCalibDlg::IDD, pParent)
{
	DWORD		k;

	m_dwPhase = 0;
	m_btBrtStep = 0;
	m_dwDelCnt = 0;

	m_dwTotSamples = 0;

	for (k=0; k<256; k++)
	{
		m_pwDayCurHi[k] = 0;
		m_pwDayCurLo[k] = 0;
		m_pwNvgCurHi[k] = 0;
		m_pwNvgCurLo[k] = 0;
	}
}


// -----------------------------------------------------------------------------------
//	CBrtFbkCalibDlg::~CBrtFbkCalibDlg
// -----------------------------------------------------------------------------------

CBrtFbkCalibDlg::~CBrtFbkCalibDlg()
{
}


// -----------------------------------------------------------------------------------
//	CBrtFbkCalibDlg Message Map
// -----------------------------------------------------------------------------------

BEGIN_MESSAGE_MAP(CBrtFbkCalibDlg, CDialog)
	ON_WM_TIMER()
END_MESSAGE_MAP()

// -----------------------------------------------------------------------------------
//	CBrtFbkCalibDlg::OnOK
// -----------------------------------------------------------------------------------

void CBrtFbkCalibDlg::OnOK()
{
}


// -----------------------------------------------------------------------------------
//	CBrtFbkCalibDlg::OnCancel
// -----------------------------------------------------------------------------------

void CBrtFbkCalibDlg::OnCancel()
{
	KillTimer(DHA55_CALIBTIMER_ID);

	if (STTE_Message("Do you want to abort calibration?", MB_ICONQUESTION | MB_YESNO) != IDYES)
	{
		SetTimer(DHA55_CALIBTIMER_ID, DHA55_CALIBTIMER_VAL, NULL);
		return;
	}

	KillTimer(STTE_MAINT_TIMER_ID);
	CDialog::OnCancel();
}


// -----------------------------------------------------------------------------------
//	CBrtFbkCalibDlg::OnInitDialog
// -----------------------------------------------------------------------------------

BOOL CBrtFbkCalibDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	M_GETPROGRESS(IDC_PROG_CALIB)->SetRange(0, 511);
	M_GETPROGRESS(IDC_PROG_CALIB)->SetPos(0);

	M_GETSTATIC(IDC_STATIC_STATUS)->SetWindowText("");

	SetTimer(STTE_MAINT_TIMER_ID, STTE_MAINT_TIMER_VAL, NULL);
	SetTimer(DHA55_CALIBTIMER_ID, DHA55_CALIBTIMER_VAL, NULL);

	return TRUE;
}


// -----------------------------------------------------------------------------------
//	CBrtFbkCalibDlg::OnTimer
// -----------------------------------------------------------------------------------

void CBrtFbkCalibDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == STTE_MAINT_TIMER_ID)
	{
		if (!MaintTimerActions())
		{
		}

		M_GETPROGRESS(IDC_PROG_CALIB)->SetPos(256 * m_dwPhase + m_btBrtStep);

		CString			s;
		s.Format("Calibrating brightness step %d...",m_btBrtStep);

		if (m_dwPhase == 0)
		{
			s += " in Day mode";
		}
		else
		{
			s += " in NVG mode";
		}

		M_GETSTATIC(IDC_STATIC_STATUS)->SetWindowText(s);
	}
	else if (nIDEvent == DHA55_CALIBTIMER_ID)
	{
		if (CalibTimerActions() != e_Return_OK)
		{
		}
	}

	CDialog::OnTimer(nIDEvent);
}



// -----------------------------------------------------------------------------------
//	CBrtFbkCalibDlg::MaintTimerActions
// -----------------------------------------------------------------------------------

BOOL CBrtFbkCalibDlg::MaintTimerActions()
{
	CFMT_CommMpp::SCommand		comlist[200];
	DWORD						c;
	BYTE						k;
	WORD						wTemp;
	t_FMT_Uint32				dwTemp;
	t_FMT_Uint64				qwTemp;
	CString						s;

	c = 0;

	// Create Read Commands --------------------------------------------------

	// MNR_ADCx
	for (k=0; k<14; k++)
	{
		comlist[c].CreateRegisterRead16Command(CMaintMpp::e_MppReg_Adc1 + k);
		c++;
	}

	// MNR_TEMP
	comlist[c].CreateRegisterRead32Command(CMaintMpp::e_MppReg_Temp);
	c++;

	// MNR_STATUS
	comlist[c].CreateRegisterRead64Command(CMaintMpp::e_MppReg_Stat);
	c++;

	// MNR_ETI
	comlist[c].CreateRegisterRead32Command(CMaintMpp::e_MppReg_Eti);
	c++;


	// Create Write Commands ---------------------------------------------------

	// MNR_CTRL
	m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Ctrl].SetBit(0, TRUE);
	comlist[c].CreateRegisterWrite8Command(CMaintMpp::e_MppReg_Ctrl, (t_FMT_Uint8)(m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Ctrl].GetField(0, 8)));
	c++;

	// MNR_BRT
	comlist[c].CreateRegisterWrite64Command(CMaintMpp::e_MppReg_Brt, (m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Brt].GetField(0, 64)));
	c++;

	// MNR_PAT
	m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Pat].SetBit(0, TRUE);
	comlist[c].CreateRegisterWrite64Command(CMaintMpp::e_MppReg_Pat, (m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Pat].GetField(0, 64)));
	c++;

	// Process Commands -------------------------------------------------------------
	
	if ((m_pDev->m_MaintMpp.ProcCommandList(comlist, c, 300)) != e_Return_OK)
	{
		return FALSE;
	}

	// Check all commands return

	if (!CFMT_CommMppClient::CheckAllCommandStatus(comlist, c))
	{
		return FALSE;
	}


	// Get Read Data ----------------------------------------------------

	c = 0;

	// MNR_ADCx
	for (k=0; k<14; k++)
	{
		comlist[c].GetReadRegisterData16(&wTemp);
		m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Adc1+k].SetField(0, 12, wTemp);
		c++;
	}

	// MNR_TEMP
	comlist[c].GetReadRegisterData32(&dwTemp);
	m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Temp].SetField(0, 32, dwTemp);
	c++;

	// MNR_STAT
	comlist[c].GetReadRegisterData64(&qwTemp);
	m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Stat].SetField(0, 64, qwTemp);
	c++;

	// MNR_ETI
	comlist[c].GetReadRegisterData32(&dwTemp);
	m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Eti].SetField(0, 32, dwTemp);
	c++;

	return TRUE;
}



// -----------------------------------------------------------------------------------
//	CBrtFbkCalibDlg::CalibTimerActions
// -----------------------------------------------------------------------------------

BOOL CBrtFbkCalibDlg::CalibTimerActions()
{
	CString			s;
	DWORD			dwHi;
	DWORD			dwLo;

	m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Brt].SetBit(36, TRUE);		// Use Curve

	if (m_dwPhase == 0)
	{
		m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Brt].SetBit(35, TRUE);		// Set Day
	}
	else
	{
		m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Brt].SetBit(35, FALSE);		// Set NVG
	}

	m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Brt].SetField(37, 8, m_btBrtStep);	// Set Brightness Step



	if (m_dwDelCnt < 9) 
	{
		m_dHi = 0.0;
		m_dLo = 0.0;
		m_dwTotSamples = 0;

		m_dwDelCnt++;
	}
	else
	{
		if (m_dwPhase == 0)
		{
			dwHi = (m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Adc1 + 12].GetField(0, 12));
			dwLo = (m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Adc1 + 13].GetField(0, 12));

			m_dHi += (double)(m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Adc1 + 12].GetField(0, 12));
			m_dLo += (double)(m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Adc1 + 13].GetField(0, 12));
		}
		else
		{
			m_dHi += (double)(m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Adc1 + 10].GetField(0, 12));
			m_dLo += (double)(m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Adc1 + 11].GetField(0, 12));
		}

		m_dwTotSamples++;

		if (m_dwTotSamples >= 10)
		{
			m_dwDelCnt = 0;

			if (m_dwPhase == 0)
			{
				m_pwDayCurHi[m_btBrtStep] = (WORD)((m_dHi / m_dwTotSamples) + 0.5);
				m_pwDayCurLo[m_btBrtStep] = (WORD)((m_dLo / m_dwTotSamples) + 0.5);

				//#if 0
				s.Format("Day step[%3d] = 0x%03X, 0x%03X\n", 
							m_btBrtStep, 
							m_pwDayCurHi[m_btBrtStep],
							m_pwDayCurLo[m_btBrtStep]);
				OutputDebugString(s);
				//#endif

			}
			else
			{
				m_pwNvgCurHi[m_btBrtStep] = (WORD)((m_dHi / m_dwTotSamples) + 0.5);
				m_pwNvgCurLo[m_btBrtStep] = (WORD)((m_dLo / m_dwTotSamples) + 0.5);

				//#if 0
				s.Format("NVG step[%3d] = 0x%03X, 0x%03X\n", 
							m_btBrtStep, 
							m_pwNvgCurHi[m_btBrtStep],
							m_pwNvgCurLo[m_btBrtStep]);
				OutputDebugString(s);
				//#endif
			}

			if (m_btBrtStep < 255)
			{
				m_btBrtStep++;
			}
			else
			{
				m_btBrtStep = 0;

				if (m_dwPhase == 0)
				{
					m_dwPhase = 1;
				}
				else
				{
					KillTimer(DHA55_CALIBTIMER_ID);



					// --- Store debug file ----------------------------------------------------------------------

					CFMT_File		f;
					DWORD			k;

					f.Open("LastBrtFbkCalib.txt", CFMT_File::e_OpenMode_Overwrite | CFMT_File::e_OpenMode_Write);
					f.WriteTextLine("--- Day -------------------------------------");
					f.WriteTextLine("");
					for (k=0; k<256; k++)
					{
						s.Format("[%3d] 0x%03X  0x%03X", k, m_pwDayCurLo[k], m_pwDayCurHi[k]);
						f.WriteTextLine(s);
					}
					f.WriteTextLine("");
				
					f.WriteTextLine("--- NVG -------------------------------------");
					f.WriteTextLine("");
					for (k=0; k<256; k++)
					{
						s.Format("[%3d] 0x%03X  0x%03X", k, m_pwNvgCurLo[k], m_pwNvgCurHi[k]);
						f.WriteTextLine(s);
					}
					f.WriteTextLine("");


					f.Close();


					// --- Update Configuration file ----------------------------------------------------------------------
					

					CCnfFile		cnf;
					if (cnf.Load(m_sCnfPath) != e_Return_OK)
					{
						STTE_Message("Cannot load Configuration File", MB_ICONSTOP);
						return e_Return_Fail;
					}

					cnf.CreateFbkBrt(FALSE, m_pwNvgCurHi, m_pwNvgCurLo);
					cnf.CreateFbkBrt(TRUE, m_pwDayCurHi, m_pwDayCurLo);

					if (cnf.Save(m_sCnfPath) != e_Return_OK)
					{
						STTE_Message("Cannot save Configuration File", MB_ICONSTOP);
						return e_Return_Fail;
					}


					STTE_Message("Configuration File correctly updated", MB_ICONINFORMATION);


					KillTimer(STTE_MAINT_TIMER_ID);
					CDialog::OnCancel();
				}
			}
		}
	}
	

	return e_Return_OK;
}

