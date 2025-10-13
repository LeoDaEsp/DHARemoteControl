#include "stdafx.h"
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "CRemotePanel.h"
#include "dha5x5_STTEDlg.h"
#include "EnhMaintDlg.h"
#include "ComDlg.h"








#define MY_DEBUG
#define DHA (CDha5x5_STTEDlg*)m_pMainDlg

static CStringA s_szRemCmds[CRemotePanel::NUM_OF__CMD] =
{
	"SYS_CONNECT",					//_cmd_CMD__SYS_CONNECT
	"CONNECT_COM",					//_cmd_CMD__CONNECT_COM

	//Finestra MAINTENANCE
	"IDC_OPER_BRT_MODE",			//_cmd_CMD__IDC_OPER_BRT_MODE
	"OPR_CRV_BRIGHTNESS_SET",		//_cmd_CMD__OPR_CRV_BRIGHTNESS_SET
	"BRIG_DUTY",					//_cmd_CMD__BRIG_DUTY
	"BRIG_CURRENT",					//_cmd_CMD__BRIG_CURRENT
	"BRIG_POTENTIOMETER",			//_cmd_CMD__BRIG_POTENTIOMETER		
	"BRIG_DAY",						//_cmd_CMD__CMD__BRIG_DAY
	"LCD_PATTERN",					//_cmd_CMD__CMD__LCD_PATTERN
	"LCD_PATTERN_COLOR_1", 			//_cmd_CMD__CMD__LCD_PATTERN_COLOR_1
	"LCD_PATTERN_COLOR_2",			//_cmd_CMD__LCD_PATTERN_COLOR_2
	"REBOOT",						//_cmd_CMD__REBOOT



	/*
	"prova_disconnect",				//_cmd_CMD__prova_disconnect
	"prova_connect_heater",			//_cmd_CMD__prova_connect_heater
	"prova_destroy_win",			//_cmd_CMD__prova_destroy_win
	"prova_free_resources",			//_cmd_CMD__prova_free_resources
	"prova_disconnect_heater",		//_cmd_CMD__prova_disconnect_heater
	*/
	"LDR_READ",						//_cmd_CMD__LDR_READ
	"LDR_WRITE",					//_cmd_CMD__LDR_WRITE
	"BUILDER_OPEN",					//_cmd_CMD__BUILDER_OPEN
	"BUILDER_SAVE",					//_cmd_CMD__BUILDER_SAVE
	"BUILDER_GET_MIN_DUTY_NVG",		//_cmd_CMD__BUILDER_GET_MIN_DUTY_NVG
	"BUILDER_SET_MIN_DUTY_NVG",		//_cmd_CMD__BUILDER_SET_MIN_DUTY_NVG
	"BUILDER_GET_MAX_DUTY_NVG",		//_cmd_CMD__BUILDER_GET_MAX_DUTY_NVG
	"BUILDER_SET_MAX_DUTY_NVG",		//_cmd_CMD__BUILDER_SET_MAX_DUTY_NVG
	"BUILDER_GET_MIN_DUTY_DAY",		//_cmd_CMD__BUILDER_GET_MIN_DUTY_DAY
	"BUILDER_SET_MIN_DUTY_DAY",		//_cmd_CMD__BUILDER_SET_MIN_DUTY_DAY
	"BUILDER_GET_MAX_DUTY_DAY",		//_cmd_CMD__BUILDER_GET_MAX_DUTY_DAY
	"BUILDER_SET_MAX_DUTY_DAY",		//_cmd_CMD__BUILDER_SET_MAX_DUTY_DAY
	"BUILDER_INFO_CODE",			//_cmd_CMD__BUILDER_INFO_CODE
	"BUILDER_INFO_DATE",			//_cmd_CMD__BUILDER_INFO_DATE
	"FREE_RSC"						//_cmd_CMD__FREE_RSC
};


// Finestra di dialogo CRemotePanel
IMPLEMENT_DYNAMIC(CRemotePanel, CDialogEx)

CRemotePanel::CRemotePanel(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CRemotePanel, pParent)
{
	m_tmrState = TMR_STATE_IDLE;
	m_pMainDlg = NULL;
	m_szLastCmdParams = "";
	m_pMaint = NULL;

}



void CRemotePanel::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: aggiungere qui il codice del gestore di messaggi e/o chiamare il codice predefinito
	switch (m_tmrState)
	{
	case TMR_STATE_PROCESSING_CMD:
	{
		m_lastCmd = NUM_OF__CMD;
		for (int i = 0; i < NUM_OF__CMD; i++)
		{
			if (m_szLastCmdParams.Find(s_szRemCmds[i]) >= 0)
			{
				m_lastCmd = (enmRemCmds_t)i;
			}
		}



		if (m_lastCmd == CMD__SYS_CONNECT)
		{
			// M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("Dario: connect"));
			CStringA params = m_szLastCmdParams;
			params.Replace(CStringA(s_SeparatorId), "");
			params.Replace(s_szRemCmds[CMD__SYS_CONNECT], "");
			if(params != "")
			{

				bool bOn = false;
				// if (params == "On")
				// {
				// 	bOn = true;
				// }
				bOn = true;

				if (_cmd_CMD__SYS_CONNECT(bOn))
				{
					_replyOk();
					m_tmrState = TMR_STATE_IDLE;
					break;
				}
			}
			
			_replyFail();
			m_tmrState = TMR_STATE_IDLE;
		}

		if (m_lastCmd == CMD__CONNECT_COM)
		{
			// M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("Dario: connect"));
			CStringA params = m_szLastCmdParams;
			params.Replace(CStringA(s_SeparatorId), "");
			params.Replace(s_szRemCmds[CMD__CONNECT_COM], "");
			if (params != "")
			{
				bool bOn = false;
				if (params == "On")
				{
					bOn = true;
				}

				if (_cmd_CMD__CONNECT_COM(bOn))
				{
					_replyOk();
					m_tmrState = TMR_STATE_IDLE;
					break;
				}
			}
			_replyFail();
			m_tmrState = TMR_STATE_IDLE;
		}



		if (m_lastCmd == CMD__IDC_OPER_BRT_MODE)
		{
			// M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("Dario: connect"));
			CStringA params = m_szLastCmdParams;
			params.Replace(CStringA(s_SeparatorId), "");
			params.Replace(s_szRemCmds[CMD__IDC_OPER_BRT_MODE], "");
			if (params != "")
			{
				bool bOn = false;
				if (params == "On")
				{
					bOn = true;
				}

				if (_cmd_CMD__IDC_OPER_BRT_MODE(bOn))
				{
					_replyOk();
					m_tmrState = TMR_STATE_IDLE;
					break;
				}
			}
			_replyFail();
			m_tmrState = TMR_STATE_IDLE;
		}


		if (m_lastCmd == CMD__OPR_CRV_BRIGHTNESS_SET)
		{
			CStringA params = m_szLastCmdParams;
			params.Replace(CStringA(s_SeparatorId), "");
			params.Replace(s_szRemCmds[CMD__OPR_CRV_BRIGHTNESS_SET], "");
			if (params != "")
			{
				int index = atoi(params);
				if (_cmd_CMD__OPR_CRV_BRIGHTNESS_SET(index))
				{
					_replyOk();
					m_tmrState = TMR_STATE_IDLE;
					break;
				}
			}
			_replyFail();
			m_tmrState = TMR_STATE_IDLE;
		}



		if (m_lastCmd == CMD__BRIG_DUTY)
		{
			CStringA params = m_szLastCmdParams;
			params.Replace(CStringA(s_SeparatorId), "");
			params.Replace(s_szRemCmds[CMD__BRIG_DUTY], "");
			if (params != "")
			{
				int index = atoi(params);
				if (_cmd_CMD__BRIG_DUTY(index))
				{
					_replyOk();
					m_tmrState = TMR_STATE_IDLE;
					break;
				}
			}
			_replyFail();
			m_tmrState = TMR_STATE_IDLE;
		}




		if (m_lastCmd == CMD__BRIG_CURRENT)
		{
			CStringA params = m_szLastCmdParams;
			params.Replace(CStringA(s_SeparatorId), "");
			params.Replace(s_szRemCmds[CMD__BRIG_CURRENT], "");
			if (params != "")
			{
				int index = atoi(params);
				if (_cmd_CMD__BRIG_CURRENT(index))
				{
					_replyOk();
					m_tmrState = TMR_STATE_IDLE;
					break;
				}
			}
			_replyFail();
			m_tmrState = TMR_STATE_IDLE;
		}


		if (m_lastCmd == CMD__BRIG_POTENTIOMETER)
		{
			CStringA params = m_szLastCmdParams;
			params.Replace(CStringA(s_SeparatorId), "");
			params.Replace(s_szRemCmds[CMD__BRIG_POTENTIOMETER], "");
			if (params != "")
			{
				int index = atoi(params);
				if (_cmd_CMD__BRIG_POTENTIOMETER(index))
				{
					_replyOk();
					m_tmrState = TMR_STATE_IDLE;
					break;
				}
			}
			_replyFail();
			m_tmrState = TMR_STATE_IDLE;
		}


		if (m_lastCmd == CMD__BRIG_DAY)
		{
			// M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("Dario: connect"));
			CStringA params = m_szLastCmdParams;
			params.Replace(CStringA(s_SeparatorId), "");
			params.Replace(s_szRemCmds[CMD__BRIG_DAY], "");
			if (params != "")
			{
				bool bOn = false;
				if (params == "On")
				{
					bOn = true;
				}

				if (_cmd_CMD__BRIG_DAY(bOn))
				{
					_replyOk();
					m_tmrState = TMR_STATE_IDLE;
					break;
				}
			}
			_replyFail();
			m_tmrState = TMR_STATE_IDLE;
		}


		if (m_lastCmd == CMD__LCD_PATTERN)
		{
			CStringA params = m_szLastCmdParams;
			params.Replace(CStringA(s_SeparatorId), "");
			params.Replace(s_szRemCmds[CMD__LCD_PATTERN], "");
			if (params != "")
			{
				m_LastUserMsg = _T("");


				if (_cmd_CMD__LCD_PATTERN(params))
				{

					// m_tmrState = TMR_STATE_WFOR_FINISH;
					// m_tmrState = TMR_STATE_IDLE;

					_replyOk();
					m_tmrState = TMR_STATE_IDLE;

					break;
				}
			}
			_replyFail();
			m_tmrState = TMR_STATE_IDLE;
		}


		if (m_lastCmd == CMD__LCD_PATTERN_COLOR_1)
		{
			CStringA params = m_szLastCmdParams;
			params.Replace(CStringA(s_SeparatorId), "");
			params.Replace(s_szRemCmds[CMD__LCD_PATTERN_COLOR_1], "");
			if (params != "")
			{
				m_LastUserMsg = _T("");


				if (_cmd_CMD__LCD_PATTERN_COLOR_1(params))
				{

					// m_tmrState = TMR_STATE_WFOR_FINISH;
					_replyOk();
					m_tmrState = TMR_STATE_IDLE;

					break;
				}
			}
			_replyFail();
			m_tmrState = TMR_STATE_IDLE;
		}



		if (m_lastCmd == CMD__LCD_PATTERN_COLOR_2)
		{
			CStringA params = m_szLastCmdParams;
			params.Replace(CStringA(s_SeparatorId), "");
			params.Replace(s_szRemCmds[CMD__LCD_PATTERN_COLOR_2], "");
			if (params != "")
			{
				m_LastUserMsg = _T("");


				if (_cmd_CMD__LCD_PATTERN_COLOR_2(params))
				{

					// m_tmrState = TMR_STATE_WFOR_FINISH;
					// m_tmrState = TMR_STATE_IDLE;

					_replyOk();
					m_tmrState = TMR_STATE_IDLE;

					break;
				}
			}
			_replyFail();
			m_tmrState = TMR_STATE_IDLE;
		}


		if (m_lastCmd == CMD__REBOOT)
		{
			CStringA params = m_szLastCmdParams;
			params.Replace(CStringA(s_SeparatorId), "");
			params.Replace(s_szRemCmds[CMD__REBOOT], "");
			// if (params != "")
			{
				m_LastUserMsg = _T("");


				if (_cmd_CMD__REBOOT())
				{

					// m_tmrState = TMR_STATE_WFOR_FINISH;
					// m_tmrState = TMR_STATE_IDLE;

					_replyOk();
					m_tmrState = TMR_STATE_IDLE;

					break;
				}
			}
			_replyFail();
			m_tmrState = TMR_STATE_IDLE;
		}






		/*
		if (m_lastCmd == CMD__prova_disconnect)
		{
			M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("Dario: disconnect"));
			CStringA params = m_szLastCmdParams;
			params.Replace(CStringA(s_SeparatorId), "");
			params.Replace(s_szRemCmds[CMD__prova_disconnect], "");
			//if(params != "")
			{
				m_LastUserMsg = _T("");
				if (_cmd_CMD__prova_disconnect())
				{
					m_tmrState = TMR_STATE_IDLE;
					break;
				}
			}
			_replyFail();
			m_tmrState = TMR_STATE_IDLE;
		}



		if (m_lastCmd == CMD__prova_connect_heater)
		{
			M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("Dario: connect heater"));
			CStringA params = m_szLastCmdParams;
			params.Replace(CStringA(s_SeparatorId), "");
			params.Replace(s_szRemCmds[CMD__prova_connect_heater], "");
			//if(params != "")
			{
				m_LastUserMsg = _T("");
				if (_cmd_CMD__prova_connect_heater())
				{
					m_tmrState = TMR_STATE_IDLE;
					break;
				}
			}
			_replyFail();
			m_tmrState = TMR_STATE_IDLE;
		}




		if (m_lastCmd == CMD__prova_destroy_win)
		{
			M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("Dario: destroy win"));
			CStringA params = m_szLastCmdParams;
			params.Replace(CStringA(s_SeparatorId), "");
			params.Replace(s_szRemCmds[CMD__prova_destroy_win], "");
			//if(params != "")
			{
				m_LastUserMsg = _T("");
				if (_cmd_CMD__prova_destroy_win())
				{
					m_tmrState = TMR_STATE_IDLE;
					break;
				}
			}
			_replyFail();
			m_tmrState = TMR_STATE_IDLE;
		}






		if (m_lastCmd == CMD__prova_free_resources)
		{
			M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("Dario: free resources"));
			CStringA params = m_szLastCmdParams;
			params.Replace(CStringA(s_SeparatorId), "");
			params.Replace(s_szRemCmds[CMD__prova_free_resources], "");
			//if(params != "")
			{
				m_LastUserMsg = _T("");
				if (_cmd_CMD__prova_free_resources())
				{
					m_tmrState = TMR_STATE_IDLE;
					break;
				}
			}
			_replyFail();
			m_tmrState = TMR_STATE_IDLE;
		}



		if (m_lastCmd == CMD__prova_disconnect_heater)
		{
			CStringA params = m_szLastCmdParams;
			params.Replace(CStringA(s_SeparatorId), "");
			params.Replace(s_szRemCmds[CMD__prova_disconnect_heater], "");
			//if(params != "")
			{
				m_LastUserMsg = _T("");
				if (_cmd_CMD__prova_disconnect_heater())
				{
					m_tmrState = TMR_STATE_IDLE;
					break;
				}
			}
			_replyFail();
			m_tmrState = TMR_STATE_IDLE;
		}
		*/

		if (m_lastCmd == CMD__LDR_READ)
		{
			CStringA params = m_szLastCmdParams;
			params.Replace(CStringA(s_SeparatorId), "");
			params.Replace(s_szRemCmds[CMD__LDR_READ], "");
			if(params != "")
			{
				m_LastUserMsg = _T("");

				
				if (_cmd_CMD__LDR_READ(params))
				{

					m_tmrState = TMR_STATE_WFOR_FINISH;
					// m_tmrState = TMR_STATE_IDLE;

					break;
				}
			}
			_replyFail();
			m_tmrState = TMR_STATE_IDLE;
		}


		
		if (m_lastCmd == CMD__LDR_WRITE)
		{
			M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("Dario: CMD__LDR_WRITE"));
			CStringA params = m_szLastCmdParams;
			params.Replace(CStringA(s_SeparatorId), "");
			params.Replace(s_szRemCmds[CMD__LDR_WRITE], "");
			if (params != "")
			{
				m_LastUserMsg = _T("");


				if (_cmd_CMD__LDR_WRITE(params))
				{

					m_tmrState = TMR_STATE_WFOR_FINISH;
					// m_tmrState = TMR_STATE_IDLE;

					break;
				}
			}
			_replyFail();
			m_tmrState = TMR_STATE_IDLE;
		}
		

		if (m_lastCmd == CMD__BUILDER_OPEN)
		{
			CStringA params = m_szLastCmdParams;
			params.Replace(CStringA(s_SeparatorId), "");
			params.Replace(s_szRemCmds[CMD__BUILDER_OPEN], "");
			if (params != "")
			{
				m_LastUserMsg = _T("");


				if (_cmd_CMD__BUILDER_OPEN(params))
				{

					m_tmrState = TMR_STATE_WFOR_FINISH;


					// _replyOk();
					// m_tmrState = TMR_STATE_IDLE;

					break;
				}
			}
			_replyFail();
			m_tmrState = TMR_STATE_IDLE;
		}


		if (m_lastCmd == CMD__BUILDER_SAVE)
		{
			CStringA params = m_szLastCmdParams;
			params.Replace(CStringA(s_SeparatorId), "");
			params.Replace(s_szRemCmds[CMD__BUILDER_SAVE], "");
			if (params != "")
			{
				m_LastUserMsg = _T("");


				if (_cmd_CMD__BUILDER_SAVE(params))
				{

					_replyOk();
					m_tmrState = TMR_STATE_IDLE;

					break;
				}
			}
			_replyFail();
			m_tmrState = TMR_STATE_IDLE;
		}



		if (m_lastCmd == CMD__BUILDER_GET_MIN_DUTY_NVG)
		{
			// M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("Dario: connect"));
			CStringA params = m_szLastCmdParams;
			params.Replace(CStringA(s_SeparatorId), "");
			params.Replace(s_szRemCmds[CMD__BUILDER_GET_MIN_DUTY_NVG], "");

			{


				int rtn;
				rtn = _cmd_CMD__BUILDER_GET_MIN_DUTY_NVG();

				if (true)
				{

					_replyString(rtn);
					m_tmrState = TMR_STATE_IDLE;
					break;
				}
			}

			_replyFail();
			m_tmrState = TMR_STATE_IDLE;
		}


		if (m_lastCmd == CMD__BUILDER_SET_MIN_DUTY_NVG)
		{
			// M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("Dario: CMD__LDR_WRITE"));
			CStringA params = m_szLastCmdParams;
			params.Replace(CStringA(s_SeparatorId), "");
			params.Replace(s_szRemCmds[CMD__BUILDER_SET_MIN_DUTY_NVG], "");
			if (params != "")
			{
				m_LastUserMsg = _T("");


				if (_cmd_CMD__BUILDER_SET_MIN_DUTY_NVG(params))
				{

					_replyOk();
					m_tmrState = TMR_STATE_IDLE;
					// m_tmrState = TMR_STATE_IDLE;

					break;
				}
			}
			_replyFail();
			m_tmrState = TMR_STATE_IDLE;
		}

		if (m_lastCmd == CMD__BUILDER_GET_MAX_DUTY_NVG)
		{
			// M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("Dario: connect"));
			CStringA params = m_szLastCmdParams;
			params.Replace(CStringA(s_SeparatorId), "");
			params.Replace(s_szRemCmds[CMD__BUILDER_GET_MAX_DUTY_NVG], "");

			{


				int rtn;
				rtn = _cmd_CMD__BUILDER_GET_MAX_DUTY_NVG();

				if (true)
				{

					_replyString(rtn);
					m_tmrState = TMR_STATE_IDLE;
					break;
				}
			}

			_replyFail();
			m_tmrState = TMR_STATE_IDLE;
		}

		if (m_lastCmd == CMD__BUILDER_SET_MAX_DUTY_NVG)
		{
			// M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("Dario: CMD__LDR_WRITE"));
			CStringA params = m_szLastCmdParams;
			params.Replace(CStringA(s_SeparatorId), "");
			params.Replace(s_szRemCmds[CMD__BUILDER_SET_MAX_DUTY_NVG], "");
			if (params != "")
			{
				m_LastUserMsg = _T("");


				if (_cmd_CMD__BUILDER_SET_MAX_DUTY_NVG(params))
				{

					_replyOk();
					m_tmrState = TMR_STATE_IDLE;

					break;
				}
			}
			_replyFail();
			m_tmrState = TMR_STATE_IDLE;
		}

		if (m_lastCmd == CMD__BUILDER_GET_MIN_DUTY_DAY)
		{
			// M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("Dario: connect"));
			CStringA params = m_szLastCmdParams;
			params.Replace(CStringA(s_SeparatorId), "");
			params.Replace(s_szRemCmds[CMD__BUILDER_GET_MIN_DUTY_DAY], "");

			{


				int rtn;
				rtn = _cmd_CMD__BUILDER_GET_MIN_DUTY_DAY();

				if (true)
				{

					_replyString(rtn);
					m_tmrState = TMR_STATE_IDLE;
					break;
				}
			}

			_replyFail();
			m_tmrState = TMR_STATE_IDLE;
		}

		if (m_lastCmd == CMD__BUILDER_SET_MIN_DUTY_DAY)
		{
			// M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("Dario: CMD__LDR_WRITE"));
			CStringA params = m_szLastCmdParams;
			params.Replace(CStringA(s_SeparatorId), "");
			params.Replace(s_szRemCmds[CMD__BUILDER_SET_MIN_DUTY_DAY], "");
			if (params != "")
			{
				m_LastUserMsg = _T("");


				if (_cmd_CMD__BUILDER_SET_MIN_DUTY_DAY(params))
				{

					_replyOk();
					m_tmrState = TMR_STATE_IDLE;

					break;
				}
			}
			_replyFail();
			m_tmrState = TMR_STATE_IDLE;
		}

		if (m_lastCmd == CMD__BUILDER_GET_MAX_DUTY_DAY)
		{
			// M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("Dario: connect"));
			CStringA params = m_szLastCmdParams;
			params.Replace(CStringA(s_SeparatorId), "");
			params.Replace(s_szRemCmds[CMD__BUILDER_GET_MAX_DUTY_DAY], "");

			{


				int rtn;
				rtn = _cmd_CMD__BUILDER_GET_MAX_DUTY_DAY();

				if (true)
				{

					_replyString(rtn);
					m_tmrState = TMR_STATE_IDLE;
					break;
				}
			}

			_replyFail();
			m_tmrState = TMR_STATE_IDLE;
		}

		if (m_lastCmd == CMD__BUILDER_SET_MAX_DUTY_DAY)
		{
			// M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("Dario: CMD__LDR_WRITE"));
			CStringA params = m_szLastCmdParams;
			params.Replace(CStringA(s_SeparatorId), "");
			params.Replace(s_szRemCmds[CMD__BUILDER_SET_MAX_DUTY_DAY], "");
			if (params != "")
			{
				m_LastUserMsg = _T("");


				if (_cmd_CMD__BUILDER_SET_MAX_DUTY_DAY(params))
				{

					_replyOk();
					m_tmrState = TMR_STATE_IDLE;

					break;
				}
			}
			_replyFail();
			m_tmrState = TMR_STATE_IDLE;
		}

		if (m_lastCmd == CMD__BUILDER_INFO_CODE)
		{
			// M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("Dario: CMD__LDR_WRITE"));
			CStringA params = m_szLastCmdParams;
			params.Replace(CStringA(s_SeparatorId), "");
			params.Replace(s_szRemCmds[CMD__BUILDER_INFO_CODE], "");
			if (params != "")
			{
				m_LastUserMsg = _T("");


				if (_cmd_CMD__BUILDER_INFO_CODE(params))
				{

					_replyOk();
					m_tmrState = TMR_STATE_IDLE;

					break;
				}
			}
			_replyFail();
			m_tmrState = TMR_STATE_IDLE;
		}

		if (m_lastCmd == CMD__BUILDER_INFO_DATE)
		{
			// M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("Dario: CMD__LDR_WRITE"));
			CStringA params = m_szLastCmdParams;
			params.Replace(CStringA(s_SeparatorId), "");
			params.Replace(s_szRemCmds[CMD__BUILDER_INFO_DATE], "");
			if (params != "")
			{
				m_LastUserMsg = _T("");


				if (_cmd_CMD__BUILDER_INFO_DATE(params))
				{

					_replyOk();
					m_tmrState = TMR_STATE_IDLE;

					break;
				}
			}
			_replyFail();
			m_tmrState = TMR_STATE_IDLE;
		}



		
		if (m_lastCmd == CMD__FREE_RSC)
		{
			CStringA params = m_szLastCmdParams;
			params.Replace(CStringA(s_SeparatorId), "");
			params.Replace(s_szRemCmds[CMD__FREE_RSC], "");
			// if (params != "")
			{
				m_LastUserMsg = _T("");


				if (_cmd_CMD__FREE_RSC())
				{

					_replyOk();
					m_tmrState = TMR_STATE_IDLE;

					break;
				}
			}
			_replyFail();
			m_tmrState = TMR_STATE_IDLE;
		}


		break;
	}

	case TMR_STATE_WFOR_FINISH:
	{
		
		_manageWFFState();

		break;
	}

	case TMR_STATE_IDLE:
	{
		int xxx = 0;
		xxx = 0;
		break;
	}

	//Auto Scroll 
	//RECT r;
	//M_GETLISTBOX(IDC_LIST_RMT_CMD)->GetItemRect(0, &r);
	//M_GETLISTBOX(IDC_LIST_RMT_CMD)->Scroll( CSize(0, (r.bottom - r.top) * (M_GETLISTBOX(IDC_LIST_RMT_CMD)->GetItemCount()) ));


	}
	CDialogEx::OnTimer(nIDEvent);
}

CRemotePanel::~CRemotePanel()
{
}

void CRemotePanel::OnClose()
{
	// TODO: aggiungere qui il codice del gestore di messaggi e/o chiamare il codice predefinito

	CDialogEx::OnClose();
}


void CRemotePanel::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: aggiungere qui il codice del gestore di messaggi
	KillTimer(0);
	m_remProcess.Deinit();
}


void CRemotePanel::SetParams(void* pMainDlg)
{
	m_pMainDlg = pMainDlg;
}



BEGIN_MESSAGE_MAP(CRemotePanel, CDialogEx)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_MESSAGE(WM_GRAPH_UPD_NEED, OnNeedUpdate)


	ON_BN_CLICKED(IDC_BUTTON_TEST, OnBtnTest)

END_MESSAGE_MAP()

int sw = 1;
CString TargetFile;
double minNvg;
double maxNvg;
double minDay;
double maxDay;

// Gestori di messaggi di CRemotePanel
void CRemotePanel::OnBtnTest()
{

	

	/*
		FUNZIONI CALIBRAZIONE FINESTRA LOADER + BUILDER
	*/
	// switch (sw)
	// {
	// case 1:
	// 
	// 	_cmd_CMD__SYS_CONNECT(true);
	// 	sw++;
	// 	break;
	// 
	// case 2:
	// 	_cmd_CMD__CONNECT_COM(TRUE);
	// 	sw++;
	// 	break;
	// 
	// case 3:
	// 	_cmd_CMD__CONNECT_COM(false);
	// 	sw++;
	// 	break;
	// 
	// 
	// case 4:
	// 	_cmd_CMD__LDR_READ("123456789BBB");
	// 	sw++;
	// 	break;
	// 
	// case 5:
	// 	_cmd_CMD__BUILDER_OPEN("123456789BBB");
	// 	sw++;
	// 	break;
	// 
	// case 6:
	// 	minNvg = _cmd_CMD__BUILDER_GET_MIN_DUTY_NVG();
	// 	sw++;
	// 	break;
	// 
	// case 7:
	// 	_cmd_CMD__BUILDER_SET_MIN_DUTY_NVG("69");
	// 	sw++;
	// 	break;
	// 
	// case 8:
	// 	_cmd_CMD__BUILDER_INFO_CODE("987654321");
	// 	sw++;
	// 	break;
	// 
	// case 9:
	// 	_cmd_CMD__BUILDER_SAVE("new\\123456789BBB");
	// 	sw++;
	// 	break;
	// 	
	// 
	// case 10:
	// 	_cmd_CMD__SYS_CONNECT(false);
	// 	sw++;
	// 	break;
	// 
	// case 11:
	// 	_cmd_CMD__FREE_RSC();
	// 	sw++;
	// 	break;
	// 
	// }

	/*
	FUNZIONI CALIBRAZIONE FINESTRA LOADER WRITE
	*/

	// switch (sw)
	// {
	// case 1:
	// 
	// 	_cmd_CMD__SYS_CONNECT(true);
	// 	sw++;
	// 	break;
	// 
	// case 2:
	// 	_cmd_CMD__CONNECT_COM(TRUE);
	// 	sw++;
	// 	break;
	// 
	// case 3:
	// 	_cmd_CMD__CONNECT_COM(false);
	// 	sw++;
	// 	break;
	// 
	// 
	// case 4:
	// 	TargetFile = _cmd_CMD__LDR_READ("123456789XXX");
	// 	sw++;
	// 	break;
	// 
	// case 5:
	// 	_cmd_CMD__LDR_WRITE("123456789XXX");
	// 	sw++;
	// 	break;
	// 
	// case 6:
	// 	_cmd_CMD__SYS_CONNECT(false);
	// 	sw++;
	// 	break;
	// 
	// case 7:
	// 	_cmd_CMD__FREE_RSC();
	// 	sw++;
	// 	break;
	// 
	// }


	// /*
	// 	FUNZIONI CALIBRAZIONE FINESTRA DI MAINTENANCE
	// */	
	switch (sw)
	{
	case 1:
	
		_cmd_CMD__SYS_CONNECT(true);
		sw++;
		break;
	
	case 2:
		_cmd_CMD__CONNECT_COM(TRUE);
		sw++;
		break;
	
	case 3:
		_cmd_CMD__IDC_OPER_BRT_MODE(true);
		sw++;
		break;
	
	case 4:
		_cmd_CMD__IDC_OPER_BRT_MODE(false);
		sw++;
		break;
	
	case 5:
		_cmd_CMD__OPR_CRV_BRIGHTNESS_SET(0);
		sw++;
		break;
	
	case 6:
		_cmd_CMD__OPR_CRV_BRIGHTNESS_SET(254);
		sw++;
		break;
	
	case 7:
		_cmd_CMD__OPR_CRV_BRIGHTNESS_GET();
		sw++;
		break;
	
	case 8:
	
		_cmd_CMD__BRIG_DAY(TRUE);
		sw++;
		break;

	case 9:

		_cmd_CMD__REBOOT();
		sw++;
		break;

	
	case 10:
		_cmd_CMD__CONNECT_COM(false);
		sw++;
		break;
	
	case 11:
		_cmd_CMD__SYS_CONNECT(false);
		sw++;
		break;
	
	case 12:
		_cmd_CMD__FREE_RSC();
		sw++;
		break;
	
	}

	/*
	FUNZIONI GENARALI
	*/
// #ifdef MY_DEBUG
	// switch(sw) {
	// 	case 1:
	// 
	// 		_cmd_CMD__SYS_CONNECT(true);
	// 		sw++;
	// 		break;
	// 
	// 	case 2:
	// 		_cmd_CMD__CONNECT_COM(TRUE);
	// 		sw++;
	// 		break;
	// 
	// 	case 3:
	// 
	// 		_cmd_CMD__BRIG_DUTY(5000);
	// 		sw++;
	// 		break;
	// 
	// 	case 4:
	// 		_cmd_CMD__BRIG_CURRENT(1000);
	// 		sw++;
	// 		break;
	// 
	// 	case 5:
	// 		_cmd_CMD__BRIG_POTENTIOMETER(1);
	// 		sw++;
	// 		break;
	// 
	// 	case 6:
	// 
	// 		_cmd_CMD__BRIG_DAY(TRUE);
	// 		sw++;
	// 		break;
	// 
	// 	case 7:
	// 		_cmd_CMD__LCD_PATTERN("Crosshair");
	// 		sw++;
	// 		break;
	// 
	// 	case 8:
	// 		_cmd_CMD__LCD_PATTERN_COLOR_1("W");
	// 		sw++;
	// 		break;
	// 
	// 	case 9:
	// 		_cmd_CMD__LCD_PATTERN_COLOR_2("B");
	// 		sw++;
	// 		break;
	// 
	// 	case 10:
	// 		_cmd_CMD__CONNECT_COM(false);
	// 		sw++;
	// 		break;
	// 
	// 	case 11:
	// 		_cmd_CMD__LDR_READ("123456789XXX");
	// 		sw++;
	// 		break;
	// 
	// 	case 12:
	// 		_cmd_CMD__BUILDER_OPEN("123456789XXX");
	// 		sw++;
	// 		break;
	// 
	// 	case 13:
	// 		_cmd_CMD__BUILDER_INFO( "727", "01-09-2025", "Dario", "Dario Esposito");
	// 		
	// 		sw++;
	// 		break;
	// 
	// 	case 14:
	// 		_cmd_CMD__BUILDER_SAVE("dario.bin");
	// 		sw++;
	// 		break;
	// 
	// 	case 15:
	// 		_cmd_CMD__BUILDER_INFO("727", "15 Aprile 25", "Dario Pio", "Dario Esposito");
	// 		sw++;
	// 		break;
	// 
	// 	case 16:
	// 		_cmd_CMD__BUILDER_SAVE("dario.bin");
	// 		sw++;
	// 		break;
	// 
	// 	case 17:
	// 		_cmd_CMD__SYS_CONNECT(false);
	// 		sw++;
	// 		break;
	// 
	// 	case 18:
	// 		// _cmd_CMD__prova_free_resources();
	// 		sw++;
	// 		break;
	// 
	// 
	// 
	// }

// #endif

}

BOOL CRemotePanel::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Aggiungere qui ulteriori informazioni per l'inizializzazione

	m_remProcess.Initialize(this);
	char path[2048] = { 0 };
	char* out = GetThisPath(path, 4096);
	if (!out)
	{
		return false;
	}
	CString szMyPath(path);
	CString szIniSWPath = szMyPath + _T("\\Config.ini");

	
	m_iniMng.LoadCfgFileINI(szIniSWPath);

	SetTimer(0, 100, NULL);

	m_bMaxIteration = false;

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ECCEZIONE: le pagine delle proprietà OCX devono restituire FALSE
}


bool CRemotePanel::_cmd_CMD__SYS_CONNECT(bool TargetConnect){

	M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("System connection"));
	M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("\n"));

	CButton* p = (CButton*)(DHA)->GetDlgItem(IDC_CHECK_STARTSTTE);

	if (TargetConnect) {

		p->SetCheck(1);
		// ((CDha5x5_STTEDlg*)m_pMainDlg)->OnCheckStartstte();

	}
	else {

		p->SetCheck(0);

	}

	


	(DHA)->OnCheckStartstte();

	if (p->GetCheck()) {
		M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("UUT is connected"));
		// return true;

	}
	else {
		M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("UUT is not connected"));
		return false;
	}
	return true;


}


int CRemotePanel::_cmd_CMD__BUILDER_GET_MIN_DUTY_NVG() {

	

	M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("Get min duty NVG mode"));

	_CreateBuilderDlg(TRUE, TRUE);

	MinDutyNvg = (int)m_pBuilder->m_CnfFile.m_pwLcdPwmMinDuty[0];

	
	
	return MinDutyNvg;

}


bool CRemotePanel::_cmd_CMD__BUILDER_SET_MIN_DUTY_NVG(CStringA TargetMinNvg) {

	M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("Set min duty NVG mode"));

	double Target = atof(TargetMinNvg);

	_CreateBuilderDlg(TRUE, TRUE);

	m_pBuilder->m_CnfFile.m_pwLcdPwmMinDuty[0] = Target;

	// if (_cmd_CMD__BUILDER_GET_MIN_DUTY_NVG() == Target) {
	// 
	// 	return true;
	// 
	// }

	return true;

}

int CRemotePanel::_cmd_CMD__BUILDER_GET_MAX_DUTY_NVG() {



	M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("Get max duty NVG mode"));


	_CreateBuilderDlg(TRUE, TRUE);

	MaxDutyNvg = (double)m_pBuilder->m_CnfFile.m_pwLcdPwmMaxDuty[0];

	return MaxDutyNvg;

}


bool CRemotePanel::_cmd_CMD__BUILDER_SET_MAX_DUTY_NVG(CStringA TargetMinNvg) {

	M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("Set max duty NVG mode"));

	double Target = atof(TargetMinNvg);

	_CreateBuilderDlg(TRUE, TRUE);

	m_pBuilder->m_CnfFile.m_pwLcdPwmMaxDuty[0] = Target;

	// if (_cmd_CMD__BUILDER_GET_MAX_DUTY_NVG() == TargetMinNvg) {
	// 
	// 	return true;
	// 
	// }

	return true;

}

int CRemotePanel::_cmd_CMD__BUILDER_GET_MIN_DUTY_DAY() {



	M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("Get min duty Day mode"));

	_CreateBuilderDlg(TRUE, TRUE);

	MinDutyDay = (int)m_pBuilder->m_CnfFile.m_pwLcdPwmMinDuty[1];

	return MinDutyDay;

}


bool CRemotePanel::_cmd_CMD__BUILDER_SET_MIN_DUTY_DAY(CStringA TargetMinNvg) {

	M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("Set min duty Day mode"));

	double Target = atof(TargetMinNvg);

	_CreateBuilderDlg(TRUE, TRUE);

	m_pBuilder->m_CnfFile.m_pwLcdPwmMinDuty[1] = Target;

	// if (_cmd_CMD__BUILDER_GET_MIN_DUTY_DAY() == TargetMinNvg) {
	// 
	// 	return true;
	// 
	// }

	return true;

}



int CRemotePanel::_cmd_CMD__BUILDER_GET_MAX_DUTY_DAY() {



	M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("Get max duty Day mode"));

	_CreateBuilderDlg(TRUE, TRUE);

	MaxDutyDay = (int)m_pBuilder->m_CnfFile.m_pwLcdPwmMaxDuty[1];

	return MaxDutyDay;

}

bool CRemotePanel::_cmd_CMD__BUILDER_SET_MAX_DUTY_DAY(CStringA TargetMinNvg) {

	M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("Set max duty Day mode"));

	double Target = atof(TargetMinNvg);

	_CreateBuilderDlg(TRUE, TRUE);

	m_pBuilder->m_CnfFile.m_pwLcdPwmMaxDuty[1] = Target;

	// if (_cmd_CMD__BUILDER_GET_MAX_DUTY_DAY() == TargetMinNvg) {
	// 
	// 	return true;
	// 
	// }

	return true;

}



bool CRemotePanel::_cmd_CMD__prova_disconnect() {

	CButton* p = (CButton*)(DHA)->GetDlgItem(IDC_CHECK_STARTSTTE);
	p->SetCheck(0);


	// (DHA)->OnCheckStartstte();

	if (p->GetCheck()) {
		M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("UUT Connect"));
		return false;

	}
	else {
		M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("Unable to connect"));
		return false;
	}
	return true;


}



bool CRemotePanel::_cmd_CMD__prova_connect_heater() {

	m_pMaint = new CEnhMaintDlg();

	m_pMaint->m_pDev = (DHA)->m_pDev;

	m_pMaint->Create(IDD_ENH_MAINT_DLG);

	m_pMaint->ShowWindow(TRUE);


	CButton* p = (CButton*)(m_pMaint)->GetDlgItem(IDC_CHECK_HEATER);
	p->SetCheck(1);

	m_pMaint->OnBnClickedCheckHeater();

	if (p->GetCheck()) {
		M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("Pulsante heater premuto"));
		// return false;
	
	}
	else {
		M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("Pulsante heater non premuto"));
		// return false;
	}

	// _cmd_CMD__prova_destroy_win();

	// m_pMaint->DestroyWindow();
	// delete m_pMaint;
	// m_pMaint = NULL;


	return true;


}


bool CRemotePanel::_cmd_CMD__prova_disconnect_heater() {

	// m_pMaint = new CEnhMaintDlg();
	// 
	// m_pMaint->m_pDev = (DHA)->m_pDev;
	// 
	// m_pMaint->Create(IDD_ENH_MAINT_DLG);
	// 
	// m_pMaint->ShowWindow(TRUE);


	CButton* p = (CButton*)(m_pMaint)->GetDlgItem(IDC_CHECK_HEATER);
	p->SetCheck(0);

	m_pMaint->OnBnClickedCheckHeater();

	if (p->GetCheck()) {
		M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("Pulsante heater premuto"));
		// return false;

	}
	else {
		M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("Pulsante heater non premuto"));
		// return false;
	}

	// _cmd_CMD__prova_destroy_win();

	// m_pMaint->DestroyWindow();
	// delete m_pMaint;
	// m_pMaint = NULL;


	return true;


}


bool CRemotePanel::_cmd_CMD__prova_destroy_win() {


	m_pMaint->DestroyWindow();
	delete m_pMaint;
	m_pMaint = NULL;

	M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("Destroy window"));

	_CreateEnhDlg(FALSE, FALSE);



	return true;


}

bool CRemotePanel::_cmd_CMD__FREE_RSC() {

	// DestroyWindow();
	// (DHA)->OnCancel();
	// (DHA)->DestroyWindow();
	(DHA)->m_pDev->Disconnect();
	return true;

}


bool CRemotePanel::_CreateEnhDlg(bool Open, bool ShowOption) {
	// Create Enhancement Maintenance Dialogue
	if (EnhMaintDlg_Open == FALSE && Open) {

		m_pMaint = new CEnhMaintDlg();
		m_pMaint->m_pDev = (DHA)->m_pDev;

		m_pMaint->Create(IDD_ENH_MAINT_DLG);
		
		EnhMaintDlg_Open = TRUE;

	}
	else if(EnhMaintDlg_Open == TRUE && !Open){

		EnhMaintDlg_Open = FALSE;
		m_pMaint->DestroyWindow();
		delete m_pMaint;
		m_pMaint = NULL;
		
		M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("Destroy maintenance window "));
		
		return false;

	}
	if (ShowOption)
		m_pMaint->ShowWindow(ShowOption);

	return true;

}

bool CRemotePanel::_CreateBuilderDlg(bool Open, bool ShowOption) {

	// Create Enhancement Maintenance Dialogue
	if (BrtBuilderDlg_Open == FALSE && Open) {

		m_pBuilder = new CBrtBuilderDlg();
		m_pBuilder->m_pDev = (DHA)->m_pDev;

		m_pBuilder->Create(IDD_BRT_BUILDER_DLG);
		

		BrtBuilderDlg_Open = TRUE;

		if (m_pBuilder == nullptr) {
			AfxMessageBox(_T("Errore: campo IDD_BRT_BUILDER_DLG non trovato."));
			return false;
		}


	}
	else if (BrtBuilderDlg_Open == TRUE && !Open) {

		BrtBuilderDlg_Open = FALSE;
		m_pBuilder->DestroyWindow();
		delete m_pBuilder;
		m_pBuilder = NULL;

		M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("Destroy builder window "));

		return false;
	}

	if (ShowOption) {
		m_pBuilder->ShowWindow(ShowOption);
	}

	return true;

}


bool CRemotePanel::_CreateLoaderDlg(bool Open, bool ShowOption) {

	// Create Enhancement Maintenance Dialogue
	if (BrtLoaderDlg_Open == FALSE && Open) {

		m_pLoader = new CLoaderDlg();
		m_pLoader->m_pDev = (DHA)->m_pDev;

		m_pLoader->Create(IDD_LOADER_DLG);


		BrtLoaderDlg_Open = TRUE;

	}
	else if (BrtLoaderDlg_Open == TRUE && !Open) {

		BrtLoaderDlg_Open = FALSE;
		// m_pLoader->DestroyWindow();
		// delete m_pLoader;
		// m_pLoader = NULL;


		m_pLoader->EnableControls(TRUE);
		m_pLoader->m_pDev->DisconnectMaintenance();
		m_pLoader->StopWaitCursor();

		m_pLoader->DestroyWindow();
		delete m_pLoader;
		m_pLoader = NULL;

		M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("Destroy loader window "));

		return false;


	}

	if (ShowOption) {
		m_pLoader->ShowWindow(ShowOption);


	}




	return 0;

}


bool CRemotePanel::_cmd_CMD__BRIG_DUTY(int TargetDuty) {

	M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("Brightness Duty"));

	CRemotePanel::_CreateEnhDlg(TRUE, TRUE);


	// Edit slider
	CSliderCtrl *p = (CSliderCtrl*)(m_pMaint)->GetDlgItem(IDC_SLIDER_DUTY);
	p->SetPos((int)TargetDuty);

	// Edit Windows
	WORD wTemp = p->GetPos();
	m_pMaint->m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Brt].SetField(0, 16, wTemp);
	
	CStringA s;
	s.Format("%d", wTemp);
	
	CEdit* e = (CEdit*)(m_pMaint)->GetDlgItem(IDC_EDIT_DUTY);
	e->SetWindowText(s);

	return true;

}


bool CRemotePanel::_cmd_CMD__BRIG_CURRENT(int TargetCurrent) {

	M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("Brightness Current"));

	CRemotePanel::_CreateEnhDlg(TRUE, TRUE);


	// Edit slider
	CSliderCtrl* p = (CSliderCtrl*)(m_pMaint)->GetDlgItem(IDC_SLIDER_CURRENT);
	p->SetPos((int)TargetCurrent);

	// Edit Windows
	WORD wTemp = p->GetPos();
	m_pMaint->m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Brt].SetField(0, 16, wTemp);

	CStringA s;
	s.Format("%d", wTemp);

	CEdit* e = (CEdit*)(m_pMaint)->GetDlgItem(IDC_EDIT_CURRENT);
	e->SetWindowText(s);

	return true;

}






bool CRemotePanel::_cmd_CMD__BRIG_POTENTIOMETER(int TargetPot){

	M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("Brightness Potentiometer"));

	CRemotePanel::_CreateEnhDlg(TRUE, TRUE);

	CComboBox* p = ((CComboBox*)(m_pMaint)->GetDlgItem(IDC_COMBO_POT));
	p->SetCurSel((int)TargetPot);

	m_pMaint->OnCbnSelendokComboPot();

	return true;

}

bool CRemotePanel::_cmd_CMD__REBOOT() {

	M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("Reboot"));

	CRemotePanel::_CreateEnhDlg(TRUE, TRUE);

	CButton* p = ((CButton*)(m_pMaint)->GetDlgItem(IDC_CHECK_CONNECT));
	
	m_pMaint->OnBnClickedCheckDay();

	m_pMaint->m_bReboot = FALSE;

	m_pMaint->EnableControls(FALSE);

	m_pMaint->KillTimer(STTE_MAINT_TIMER_ID);

	m_pMaint->m_pDev->DisconnectMaintenance();

	m_pMaint->m_pDev->m_btMaintLinkStatus = CDhaStteDevice::e_LinkStatus_Off;
	
	p->SetCheck(FALSE);
	

	return true;

}

bool CRemotePanel::_cmd_CMD__BRIG_DAY(bool TargetDay) {

	M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("Brightness Day"));

	CRemotePanel::_CreateEnhDlg(TRUE, TRUE);

	int Target = 0;
	if (TargetDay) {
		Target = 1;
	}

	CButton* p = ((CButton*)(m_pMaint)->GetDlgItem(IDC_CHECK_DAY));
	p->SetCheck(Target);

	m_pMaint->OnBnClickedCheckDay();

	return true;

}

bool CRemotePanel::_cmd_CMD__CONNECT_COM(bool TargetConnect) {

	CRemotePanel::_CreateEnhDlg(TRUE, TRUE);
	CButton* p = (CButton*)(m_pMaint)->GetDlgItem(IDC_CHECK_CONNECT);
	

	if (TargetConnect) {
		M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("Connection COM"));
		M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("\n"));

		CComDlg		d;

		d.m_sCOM = m_iniMng.m_arIniTbCfgSzData[INI_TB_MAINT_COM];
		d.m_pHdwManager = &(m_pMaint->m_pDev->m_HdwManager);


		m_pMaint->m_pDev->m_sMaintLinkComPort = d.m_sCOM;
		m_pMaint->m_pDev->SaveSettings();
		m_pMaint->RefreshPort();


		
		p->SetCheck(1);

		
	}
	else
	{
		M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("Disconnection COM"));
		M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("\n"));
		p->SetCheck(0);

	}

	m_pMaint->OnBnClickedCheckConnect();

	// CRemotePanel::_CreateEnhDlg(FALSE, FALSE);

	return TargetConnect;


}

int CRemotePanel::_cmd_CMD__OPR_CRV_BRIGHTNESS_GET() {

	M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("Get brightness operative curves"));
	M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("\n"));

	CComboBox* pComboBox = (CComboBox*)m_pMaint->GetDlgItem(IDC_COMBO_MNT_OPERBRT);

	int get_brg = pComboBox->GetCurSel();

	return get_brg;

}

bool CRemotePanel::_cmd_CMD__OPR_CRV_BRIGHTNESS_SET(int TargetBrightness) {

	M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("Set brightness operative curves"));
	M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("\n"));

	if (TargetBrightness >= 0 && TargetBrightness < 255) {

		CComboBox *pComboBox = (CComboBox*)m_pMaint->GetDlgItem(IDC_COMBO_MNT_OPERBRT);

		pComboBox->SetCurSel(TargetBrightness);

		return true;

	}
	

	M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("The target brightness is not beetwen 0 and 254"));
	M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("\n"));

	

	return false;

}

bool CRemotePanel::_cmd_CMD__LCD_PATTERN(CStringA TargetPattern) {

	M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("LCD pattern"));
	M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("\n"));

	CRemotePanel::_CreateEnhDlg(TRUE, TRUE);

	type_enumPattern myPattern = enumPattern_Border;

	for( int i = 0; i < enumPattern__NUMOF; i++) {

		if (TargetPattern == s_SelPattern[i]) {

			myPattern = (type_enumPattern)i;
		}
	}

	// Set defoult pattern
	if (myPattern == enumPattern__NUMOF) {

		CComboBox* p = (CComboBox*)m_pMaint->GetDlgItem(IDC_COMBO_VIDEO_PATTERN);
		p->SetCurSel(myPattern);
		// return false;
		
	}
	else {

		CComboBox* p = (CComboBox*)m_pMaint->GetDlgItem(IDC_COMBO_VIDEO_PATTERN);
		p->SetCurSel(myPattern);
	}
	return true;


}


bool CRemotePanel::_cmd_CMD__LCD_PATTERN_COLOR_1(CStringA TargetColor) {

	int R = 0;
	int G = 0;
	int B = 0;

	M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("LCD pattern color 1"));
	M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("\n"));

	if (TargetColor == "B") {
		R = 0;
		G = 0;
		B = 0;
	}
	else if (TargetColor == "W") {
		R = 255;
		G = 255;
		B = 255;

	}
	else if (TargetColor == "R") {
		R = 255;
		G = 0;
		B = 0;

	}
	else if (TargetColor == "G") {
		R = 0;
		G = 255;
		B = 0;

	}
	else if (TargetColor == "BL") {
		R = 0;
		G = 0;
		B = 255;

	}


	CRemotePanel::_CreateEnhDlg(TRUE, TRUE);

	// RGB_map color;


	// std::map<std::string, int> ola = color.type_myStruct.color[(std::string)TargetPattern];


	m_pMaint->m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Pat].SetField(8, 8, R);
	m_pMaint->m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Pat].SetField(16, 8, G);
	m_pMaint->m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Pat].SetField(24, 8, B);



	m_pMaint->RefreshPatColor(0);

	m_pMaint->OnCbnSelendokComboVideoPattern();


	return true;
}


/*
bool CRemotePanel::_cmd_CMD__LCD_PATTERN_COLOR_1(CStringA TargetPattern) {



	M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("LCD pattern color 1"));

	CRemotePanel::_CreateEnhDlg(TRUE, TRUE);

	RGB_map color;


	std::map<std::string, int> ola = color.type_myStruct.color[(std::string)TargetPattern];


	m_pMaint->m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Pat].SetField(8, 8, ola["R"]);
	m_pMaint->m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Pat].SetField(16, 8, ola["G"]);
	m_pMaint->m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Pat].SetField(24, 8, ola["B"]);

	m_pMaint->RefreshPatColor(0);


	return true;
}
*/


bool CRemotePanel::_cmd_CMD__LCD_PATTERN_COLOR_2(CStringA TargetColor) {

	int R = 0;
	int G = 0;
	int B = 0;


	if (TargetColor == "B") {
		R = 0;
		G = 0;
		B = 0;
	}
	else if (TargetColor == "W") {
		R = 255;
		G = 255;
		B = 255;

	}
	else if (TargetColor == "R") {
		R = 255;
		G = 0;
		B = 0;

	}
	else if (TargetColor == "G") {
		R = 0;
		G = 255;
		B = 0;

	}
	else if (TargetColor == "BL") {
		R = 0;
		G = 0;
		B = 255;

	}

	M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("LCD pattern color 2"));
	M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("\n"));

	CRemotePanel::_CreateEnhDlg(TRUE, TRUE);


	// std::map<std::string, int> t_color = color.type_myStruct.color[(std::string)TargetPattern];


	m_pMaint->m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Pat].SetField(32, 8, R);
	m_pMaint->m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Pat].SetField(40, 8, G);
	m_pMaint->m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Pat].SetField(48, 8, B);

	m_pMaint->RefreshPatColor(1);

	m_pMaint->OnCbnSelendokComboVideoPattern();

	return true;
}

/*
bool CRemotePanel::_cmd_CMD__LCD_PATTERN_COLOR_2(CStringA TargetPattern) {



	M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("LCD pattern color 2"));

	CRemotePanel::_CreateEnhDlg(TRUE, TRUE);

	RGB_map color;


	std::map<std::string, int> t_color = color.type_myStruct.color[(std::string)TargetPattern];


	m_pMaint->m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Pat].SetField(32, 8, t_color["R"]);
	m_pMaint->m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Pat].SetField(40, 8, t_color["G"]);
	m_pMaint->m_pDev->m_pMaintDataReg[CMaintMpp::e_MppReg_Pat].SetField(48, 8, t_color["B"]);

	m_pMaint->RefreshPatColor(1);


	return true;
}
*/

bool CRemotePanel::_cmd_CMD__IDC_OPER_BRT_MODE(bool TargetBrt) {

	M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("Load dimming curve from mem to FPGA"));
	M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("\n"));

	CRemotePanel::_CreateEnhDlg(TRUE, TRUE);

	CButton* pButton = (CButton*)(m_pMaint->GetDlgItem(IDC_OPER_BRT_MODE));

	pButton->SetCheck(TargetBrt ? 1 : 0);

	return TargetBrt;
}

std::string CRemotePanel::_touchFile() {

	std::time_t now = std::time(nullptr);               // Ottieni tempo attuale
	std::tm* tm_now = std::localtime(&now);             // Converte in ora locale

	std::ostringstream oss;
	oss << std::put_time(tm_now, "%d-%m-%Y");  // Formatta come stringa
	// oss << std::put_time(tm_now, "%Y-%m-%d %H:%M:%S");  // Formatta come stringa
	std::string dataStr = oss.str();

	// std::cout << "Data attuale: " << dataStr << std::endl;

	return dataStr;
}

bool CRemotePanel::_cmd_CMD__LDR_WRITE(CString TargetFileName) {

	M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("Loader write binary"));
	M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("\n"));

	CRemotePanel::_CreateEnhDlg(FALSE, FALSE);

	CRemotePanel::_CreateLoaderDlg(TRUE, TRUE);


	CFile			f;
	DWORD			dwRet;
	BYTE* pbtBuf;
	CString			s;
	DWORD			dwCrc;
	CString  FileName;


	m_pFile = new CFileDialog(TRUE, "bin", NULL, OFN_HIDEREADONLY, "Binary Files (*.bin) | *.bin|", this);


	//Leggo il path da file .ini 
	// FileName = TargetFileName + "_" + CString(CRemotePanel::_touchFile().c_str()) + ".bin"; // Converti da string a CString
	FileName = TargetFileName + ".bin"; // Converti da string a CString

	m_pLoader->m_sFilePath = m_iniMng.m_arIniTbCfgSzData[INI_TB_CFG__LOAD_DEF_FILE_PATH] + FileName;

	m_pLoader->m_sFileName = FileName;

	// Read the file ------------------------------------------

	if (!f.Open(m_pLoader->m_sFilePath, CFile::modeRead))
	{
		STTE_Message("Cannot read selected file", MB_ICONSTOP, this);
		return false;
	}

	if (!m_pLoader->CheckCfgFile(f))
	{
		STTE_Message("Invalid Configuration Factory Memory file", MB_ICONSTOP, this);
		f.Close();
		return false;
	}

	dwCrc = 0;

	pbtBuf = m_pLoader->m_pDev->m_MaintMpp.CreateTransferBuffer(CNF_TOT_MEMORY_BYTE_SIZE);

	try
	{
		f.Read(pbtBuf, CNF_TOT_MEMORY_BYTE_SIZE);
		memcpy(m_pLoader->m_pbtTempCfg, pbtBuf, CNF_TOT_MEMORY_BYTE_SIZE);

		dwCrc = ((DWORD)(*((WORD*)(pbtBuf + CNF_CRC_BO))));
	}
	catch (...)
	{
		STTE_Message("Cannot read selected file", MB_ICONSTOP, this);
		f.Close();
		return false;
	}

	f.Close();

	m_pLoader->RefreshCfgFileInfo(pbtBuf, dwCrc);

	// M_GETPROGRESS(IDC_PROG_LOADER)->SetRange(0, 10000);
	// M_GETPROGRESS(IDC_PROG_LOADER)->SetPos(0);
	((CProgressCtrl*)m_pLoader->GetDlgItem(IDC_PROG_LOADER))->SetRange(0, 10000);
	((CProgressCtrl*)m_pLoader->GetDlgItem(IDC_PROG_LOADER))->SetPos(0);

	m_pLoader->EnableControls(FALSE);

	if (!m_pLoader->m_pDev->ConnectMaintenance())
	{
		STTE_Message("Cannot open Loader Port.", MB_ICONSTOP, this);

		m_pLoader->EnableControls(TRUE);
		CRemotePanel::_CreateLoaderDlg(FALSE, FALSE);
		// m_pLoader->DestroyWindow();
		// delete m_pLoader;
		// m_pLoader = NULL;
		return false;
	}

	// Execute file transfer ----------------------------------

	m_pLoader->m_pDev->m_CfgBtp.m_bEraseAll = FALSE;
	m_pLoader->m_pDev->m_CfgBtp.m_bErasePage = FALSE;
	m_pLoader->m_pDev->m_CfgBtp.m_uiMaxNumItemPerTransfer = 6;
	m_pLoader->m_pDev->m_CfgBtp.m_uiPageSize = 0x100;
	m_pLoader->m_pDev->m_CfgBtp.m_uiEraseSize = 0x10000;
	m_pLoader->m_pDev->m_CfgBtp.m_uiRetries = 3;
	m_pLoader->m_pDev->m_CfgBtp.m_uiStartMemAddress = MEM_CNF_MPP_START_ADDRESS;
	m_pLoader->m_pDev->m_CfgBtp.m_uiTimeout = 3000;
	m_pLoader->m_pDev->m_CfgBtp.m_uiTransferSize = CNF_TOT_MEMORY_BYTE_SIZE;

	m_pLoader->StartWaitCursor();

	dwRet = m_pLoader->m_pDev->m_MaintMpp.EraseMemoryBuffer(&m_pLoader->m_pDev->m_CfgBtp);

	if (dwRet != e_Return_OK)
	{
		STTE_Message("Hardware communication error.", MB_ICONSTOP, this);
		m_pLoader->EnableControls(TRUE);
		m_pLoader->m_pDev->DisconnectMaintenance();
		m_pLoader->StopWaitCursor();
		CRemotePanel::_CreateLoaderDlg(FALSE, FALSE);
		// m_pLoader->DestroyWindow();
		// delete m_pLoader;
		// m_pLoader = NULL;
		return false;
	}

	s = "Erasing target Configuration Memory...";
	m_pLoader->m_ssTargetFile.SetWindowText(s);
	m_pLoader->m_ssTargetFile.SetBkColor(STTE_COLOR_YELLOW);

	m_pLoader->m_dwMode = CLoaderDlg::e_Mode_Program;
	m_pLoader->m_btPhase = 0;
	m_pLoader->SetTimer(STTE_CFGLOADER_TIMER_ID, STTE_CFGLOADER_TIMER_VAL, NULL);

	return true;


}


bool CRemotePanel::_cmd_CMD__LDR_READ(CString TargetFileName) {

	M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("Loader read binary"));
	M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("\n"));

	// CRemotePanel::_CreateEnhDlg(FALSE, FALSE);

	CRemotePanel::_CreateLoaderDlg(TRUE, TRUE);
	

	CFile			f;
	DWORD			dwRet;

	CString			s;

	CString  FileName;

	CFileDialog* pDlg = new CFileDialog(FALSE, "bin", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST,
		"Binary Files (*.bin) | *.bin|", this);

	

	
	// FileName = TargetFileName + "_" + CString(CRemotePanel::_touchFile().c_str()) + ".bin"; // Converti da string a CString
	FileName = TargetFileName + ".bin"; // Converti da string a CString

	// m_pLoader->m_sFilePath = m_iniMng.m_arIniTbCfgSzData[INI_TB_CFG__LOAD_DEF_FILE_PATH] + TargetFileName + "\\" + FileName;

	m_pLoader->m_sFilePath = m_iniMng.m_arIniTbCfgSzData[INI_TB_CFG__LOAD_DEF_FILE_PATH] + FileName;


	m_pLoader->m_sFileName = FileName;


	m_pLoader->EnableControls(FALSE);
	
	
	if (!m_pLoader->m_pDev->ConnectMaintenance())
	{
		STTE_Message("Cannot open Loader Port.", MB_ICONSTOP, this);
		// M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("Male male"));
		m_pLoader->EnableControls(TRUE);
		CRemotePanel::_CreateLoaderDlg(FALSE, FALSE);
		return false;
	}
	

	// Execute file transfer ----------------------------------
	m_pLoader->m_pDev->m_CfgBtp.m_bEraseAll = FALSE;
	m_pLoader->m_pDev->m_CfgBtp.m_bErasePage = FALSE;
	m_pLoader->m_pDev->m_CfgBtp.m_uiMaxNumItemPerTransfer = 1;
	m_pLoader->m_pDev->m_CfgBtp.m_uiPageSize = 0x100;
	m_pLoader->m_pDev->m_CfgBtp.m_uiEraseSize = 0x10000;
	m_pLoader->m_pDev->m_CfgBtp.m_uiRetries = 3;
	m_pLoader->m_pDev->m_CfgBtp.m_uiStartMemAddress = MEM_CNF_MPP_START_ADDRESS;
	m_pLoader->m_pDev->m_CfgBtp.m_uiTimeout = 500;
	m_pLoader->m_pDev->m_CfgBtp.m_uiTransferSize = CNF_TOT_MEMORY_BYTE_SIZE;

	m_pLoader->StartWaitCursor();

	dwRet = m_pLoader->m_pDev->m_MaintMpp.ReadMemoryBuffer(&m_pLoader->m_pDev->m_CfgBtp);

	if (dwRet != e_Return_OK)
	{
		STTE_Message("Hardware communication error.", MB_ICONSTOP, this);
		// M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("Male male 2"));
		m_pLoader->EnableControls(TRUE);
		m_pLoader->StopWaitCursor();
		CRemotePanel::_CreateLoaderDlg(FALSE, FALSE);
		return false;
	}

	s = "Reading target file as " + m_pLoader->m_sFileName + "...";
	m_pLoader->m_ssTargetFile.SetWindowText(s);
	m_pLoader->m_ssTargetFile.SetBkColor(STTE_COLOR_YELLOW);

	m_pLoader->m_dwMode = CLoaderDlg::e_Mode_Read;
	m_pLoader->m_btPhase = 0;
	m_pLoader->SetTimer(STTE_CFGLOADER_TIMER_ID, STTE_CFGLOADER_TIMER_VAL, NULL);
		
	// CRemotePanel::_CreateLoaderDlg(FALSE, FALSE);

	return true;

}


bool CRemotePanel::_cmd_CMD__BUILDER_INFO(std::string Code, std::string Date, std::string Name, std::string Author) {

	M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("Builder info"));
	M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("\n"));

	CRemotePanel::_CreateBuilderDlg(TRUE, TRUE);

	// Code
	CEdit* p = (CEdit*)m_pBuilder->GetDlgItem(IDC_EDIT_CODE);
	p->SetWindowText(Code.c_str());

	// Date
	p = (CEdit*)m_pBuilder->GetDlgItem(IDC_EDIT_DATE);
	p->SetWindowText(Date.c_str());

	// Name
	p = (CEdit*)m_pBuilder->GetDlgItem(IDC_EDIT_NAME);
	p->SetWindowText(Name.c_str());

	// Author
	p = (CEdit*)m_pBuilder->GetDlgItem(IDC_EDIT_AUTHOR);
	p->SetWindowText(Author.c_str());

	return true;

}

bool CRemotePanel::_cmd_CMD__BUILDER_INFO_CODE(CStringA Code) {

	M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("Builder info code"));
	M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("\n"));

	CRemotePanel::_CreateBuilderDlg(TRUE, TRUE);
	std::string SCode(Code.GetString());

	// Code
	CEdit* p = (CEdit*)m_pBuilder->GetDlgItem(IDC_EDIT_CODE);
	p->SetWindowText(SCode.c_str());

	return true;

}

bool CRemotePanel::_cmd_CMD__BUILDER_INFO_DATE(CStringA Date) {

	M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("Builder info"));
	M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("\n"));

	CRemotePanel::_CreateBuilderDlg(TRUE, TRUE);

	std::string SDate(Date.GetString());


	// Date
	CEdit* p = (CEdit*)m_pBuilder->GetDlgItem(IDC_EDIT_DATE);
	p->SetWindowText(SDate.c_str());


	return true;

}

bool CRemotePanel::_cmd_CMD__BUILDER_SAVE( CString TargetName) {

	M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("Builder save"));
	M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("\n"));

	CRemotePanel::_CreateBuilderDlg(TRUE, TRUE);

	CCnfFile CnfF;
	CStringA FileName = TargetName + ".bin";

	CnfF.m_sFilePath = m_iniMng.m_arIniTbCfgSzData[INI_TB_CFG__LOAD_DEF_FILE_PATH] + FileName;
	
	
	m_pBuilder->m_CnfFile.Save(CnfF.m_sFilePath);

	m_pBuilder->m_ssFilePath.SetWindowText(CnfF.m_sFilePath);
	
	return true;

}

// bool CRemotePanel::_cmd_CMD__BUILDER_OPEN(CString TargetName) {
// 
// 	M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("Builder open file"));
// 	M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("\n"));
// 
// 	CRemotePanel::_CreateBuilderDlg(TRUE, TRUE);
// 
// 	CCnfFile CnfF;
// 
// 	CStringA FileName = TargetName + ".bin";
// 	CnfF.m_sFilePath = m_iniMng.m_arIniTbCfgSzData[INI_TB_CFG__LOAD_DEF_FILE_PATH] + FileName;
// 
// 
// 	m_pBuilder->m_CnfFile.Load(CnfF.m_sFilePath);
// 
// 	m_pBuilder->m_ssFilePath.SetWindowText(CnfF.m_sFilePath);
// 
// 	return true;
// 
// }



bool CRemotePanel::_cmd_CMD__BUILDER_OPEN(CString TargetName) {

	M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("Builder open file"));
	M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("\n"));

	CRemotePanel::_CreateBuilderDlg(TRUE, TRUE);

	CCnfFile CnfF;

	CStringA FileName = TargetName + ".bin";
	CnfF.m_sFilePath = m_iniMng.m_arIniTbCfgSzData[INI_TB_CFG__LOAD_DEF_FILE_PATH] + FileName;



	if (m_pBuilder->m_CnfFile.Load(CnfF.m_sFilePath) != e_Return_OK)
	{
		STTE_Message("Cannot load Brightness File", MB_ICONSTOP, this);
		return false;
	}

	m_pBuilder->m_dwCurNode = 0;

	m_pBuilder->RefreshData();
	m_pBuilder->RefreshInfo();

	m_pBuilder->m_ssFilePath.SetWindowText(CnfF.m_sFilePath);

	STTE_Message("Brightness File correctly loaded", MB_ICONINFORMATION, this);


	return true;

}


void CRemotePanel::_replyFail()
{

	BYTE buf[MAX_BUF_SIZE] = { 0 };
	//Costruisco il messaggio da inviare
	CStringA msg = "";
	msg += CStringA(s_HeadId);
	msg += CStringA("0");
	msg += CStringA(s_CompleteId);

	memset(buf, 0, MAX_BUF_SIZE);
	if (msg.GetLength() > (MAX_BUF_SIZE - 1))
	{
		return;
	}

	memcpy(buf, msg, msg.GetLength());
	m_remProcess.TXToLib(buf, MAX_BUF_SIZE);
}

void CRemotePanel::_manageWFFState()
{
	CString sText = m_LastUserMsg;
	
	if (sText != _T(""))
	{
		m_LastUserMsg = _T("");
	}
	else
	{
		return;
	}



	if (m_tmrState == TMR_STATE_WFOR_FINISH)
	{
		

		if (m_lastCmd == CMD__LDR_READ)
		{
			

			if (sText == _T("File correctly saved."))
			{
				_replyOk();
				
				m_tmrState = TMR_STATE_IDLE;

				CRemotePanel::_CreateLoaderDlg(FALSE, FALSE);
				
				// m_pLoader->KillTimer(STTE_CFGLOADER_TIMER_ID);
				// m_pLoader->DestroyWindow();
				// delete m_pLoader;
				// m_pLoader = NULL;
				
	
			}
			else
			{
				_replyFail();
				m_tmrState = TMR_STATE_IDLE;
				
				CRemotePanel::_CreateLoaderDlg(FALSE, FALSE);

				// m_pLoader->KillTimer(STTE_CFGLOADER_TIMER_ID);
				// m_pLoader->DestroyWindow();
				// delete m_pLoader;
				// m_pLoader = NULL;
				
			}
		}

		if (m_lastCmd == CMD__BUILDER_OPEN)
		{


			if (sText == _T("Brightness File correctly loaded"))
			{
				_replyOk();

				m_tmrState = TMR_STATE_IDLE;

				// CRemotePanel::_CreateBuilderDlg(FALSE, FALSE);



			}
			else
			{
				_replyFail();
				m_tmrState = TMR_STATE_IDLE;

				CRemotePanel::_CreateBuilderDlg(FALSE, FALSE);

				// m_pLoader->KillTimer(STTE_CFGLOADER_TIMER_ID);
				// m_pLoader->DestroyWindow();
				// delete m_pLoader;
				// m_pLoader = NULL;

			}
		}
	}


	

	

	if (m_tmrState == TMR_STATE_WFOR_FINISH)
	{


		if (m_lastCmd == CMD__LDR_WRITE)
		{


			if (sText == _T("File correctly written."))
			{
				_replyOk();
				m_tmrState = TMR_STATE_IDLE;

				CRemotePanel::_CreateLoaderDlg(FALSE, FALSE);

				// m_pLoader->KillTimer(STTE_CFGLOADER_TIMER_ID);
				// m_pLoader->DestroyWindow();
				// delete m_pLoader;
				// m_pLoader = NULL;

				// STTE_Message("Hardware communication error.", MB_ICONSTOP, this);


			}
			else
			{
				_replyFail();
				m_tmrState = TMR_STATE_IDLE;

				CRemotePanel::_CreateLoaderDlg(FALSE, FALSE);

				// m_pLoader->KillTimer(STTE_CFGLOADER_TIMER_ID);
				// m_pLoader->DestroyWindow();
				// delete m_pLoader;
				// m_pLoader = NULL;
			}
		}
	}
	
	
	//////////////////////////////////////////
	//if (m_tmrState == TMR_STATE_WFOR_FINISH)
	//{
	//	if (m_lastCmd == CMD__CFG_ERASE_MEM)
	//	{
	//		if (sText == _T("Memory correcly erased."))
	//		{
	//			M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("OK"));
	//
	//
	//			_replyOk();
	//			m_tmrState = TMR_STATE_IDLE;
	//			m_pLoader->KillTimer(SMCTB_CFGLOADER_TIMER_ID);
	//			m_pLoader->DestroyWindow();
	//			delete m_pLoader;
	//			m_pLoader = NULL;
	//
	//		}
	//		else
	//		{
	//			M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(sText);
	//
	//			M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("FAIL!!!!!"));
	//			_replyFail();
	//			m_tmrState = TMR_STATE_IDLE;
	//			m_pLoader->KillTimer(SMCTB_CFGLOADER_TIMER_ID);
	//			m_pLoader->DestroyWindow();
	//			delete m_pLoader;
	//			m_pLoader = NULL;
	//		}
	//	}
	//}
	//
	//
	//////////////////////////////////////////
	//if (m_tmrState == TMR_STATE_WFOR_FINISH)
	//{
	//	if (m_lastCmd == CMD__CFG_VERIFY_MEM)
	//	{
	//		if (sText == _T("File correctly verified."))
	//		{
	//			_replyOk();
	//			m_tmrState = TMR_STATE_IDLE;
	//			m_pLoader->KillTimer(SMCTB_CFGLOADER_TIMER_ID);
	//			m_pLoader->DestroyWindow();
	//			delete m_pLoader;
	//			m_pLoader = NULL;
	//
	//		}
	//		else
	//		{
	//			_replyFail();
	//			m_tmrState = TMR_STATE_IDLE;
	//			m_pLoader->KillTimer(SMCTB_CFGLOADER_TIMER_ID);
	//			m_pLoader->DestroyWindow();
	//			delete m_pLoader;
	//			m_pLoader = NULL;
	//		}
	//	}
	//}
}


void CRemotePanel::ProcessUserMsg(CString& sText, int iParam)
{
	
	M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T(sText));
	m_LastUserMsg = sText;

}


RGB_map::RGB_map() {


	type_myStruct.color["RED"].insert(std::make_pair("R", 255));
	type_myStruct.color["RED"].insert(std::make_pair("G", 0));
	type_myStruct.color["RED"].insert(std::make_pair("B", 0));

	type_myStruct.color["WHITE"].insert(std::make_pair("R", 255));
	type_myStruct.color["WHITE"].insert(std::make_pair("G", 255));
	type_myStruct.color["WHITE"].insert(std::make_pair("B", 255));

	
}

RGB_map::~RGB_map()
{
}

void CRemotePanel::_replyOk()
{

	BYTE buf[MAX_BUF_SIZE] = { 0 };
	//Costruisco il messaggio da inviare
	CStringA msg = "";
	msg += CStringA(s_HeadId);
	msg += CStringA("1");
	msg += CStringA(s_CompleteId);

	memset(buf, 0, MAX_BUF_SIZE);
	if (msg.GetLength() > (MAX_BUF_SIZE - 1))
	{
		return;
	}

	memcpy(buf, msg, msg.GetLength());
	m_remProcess.TXToLib(buf, MAX_BUF_SIZE);
}


void CRemotePanel::_replyString(float TargetS)
{
	// CStringA TString;
	// TString.Format("%2f", TargetS);

	float str = TargetS;

	BYTE Tstring[256] = { 0 };

	std::memcpy(Tstring, &str, sizeof(float));

	BYTE buf[MAX_BUF_SIZE] = { 0 };
	//Costruisco il messaggio da inviare
	CStringA msg = "";

	for (int i = 0; i <= 9; i++) {

		if (i == 0) {
			msg += CStringA(s_HeadId);
			continue;
		}
		if (i == 9) {
			msg += CStringA(s_CompleteId);
			continue;
		}
		msg += Tstring[i];
		
	}

	// msg += CStringA(s_HeadId);
	// msg += CStringA("4");
	// msg += CStringA("6");
	// msg += CStringA("9");
	// msg += CStringA(s_CompleteId);

	memset(buf, 0, MAX_BUF_SIZE);
	if (msg.GetLength() > (MAX_BUF_SIZE - 1))
	{
		return;
	}

	memcpy(buf, msg, msg.GetLength());
	m_remProcess.TXToLib(buf, MAX_BUF_SIZE);
}


