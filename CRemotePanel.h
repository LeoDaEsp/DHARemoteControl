#pragma once

#include <iostream>
#include <string>
#include <map>
#include "string"

#include <afxdialogex.h>
#include <utility> 

#include "resource.h"
#include "IniFileMng.h"
#include "LibGlobals.h"
#include "CRemoteProcess.h"
#include "BrtBuilderDlg.h"
#include "CnfFile.h"
#include "LoaderDlg.h"
#include "DhaStteDevice.h"




// Finestra di dialogo CRemotePanel
class CEnhMaintDlg;
// class CConfBuilderDlg;

class RGB_map {

public:
	struct myStruct {


		std::map<std::string, std::map<std::string, int>> color;


	}type_myStruct;

	RGB_map();
	virtual ~RGB_map();




};



class CRemotePanel : public CDialogEx
{
	DECLARE_DYNAMIC(CRemotePanel)

public:

	CRemotePanel(CWnd* pParent = nullptr);   // costruttore standard
	virtual ~CRemotePanel();

	// Dati della finestra di dialogo
	//#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CRemotePanel };
	//#endif

protected:
	// virtual void DoDataExchange(CDataExchange* pDX);    // supporto DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	

	void SetParams(void* pMainDlg);
	void CRemotePanel::OnClose();
	afx_msg void OnBtnTest();
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();

	typedef enum enmRemCmds
	{
		CMD__SYS_CONNECT = 0,
		CMD__CONNECT_COM,

		//Finestra MAINTENANCE
		CMD__IDC_OPER_BRT_MODE,
		CMD__OPR_CRV_BRIGHTNESS_SET,
		CMD__BRIG_DUTY,
		CMD__BRIG_CURRENT,
		CMD__BRIG_POTENTIOMETER,
		CMD__BRIG_DAY,
		CMD__LCD_PATTERN,
		CMD__LCD_PATTERN_COLOR_1,
		CMD__LCD_PATTERN_COLOR_2,


		/*
		CMD__prova_disconnect,
		CMD__prova_connect_heater,
		CMD__prova_destroy_win,

		CMD__prova_free_resources,
		CMD__prova_disconnect_heater,
		*/
		CMD__LDR_READ,
		CMD__LDR_WRITE,
		CMD__BUILDER_OPEN,
		CMD__BUILDER_SAVE,
		CMD__BUILDER_GET_MIN_DUTY_NVG,
		CMD__BUILDER_SET_MIN_DUTY_NVG,
		CMD__BUILDER_GET_MAX_DUTY_NVG,
		CMD__BUILDER_SET_MAX_DUTY_NVG,
		CMD__BUILDER_GET_MIN_DUTY_DAY,
		CMD__BUILDER_SET_MIN_DUTY_DAY,
		CMD__BUILDER_GET_MAX_DUTY_DAY,
		CMD__BUILDER_SET_MAX_DUTY_DAY,
		CMD__BUILDER_INFO_CODE,
		CMD__BUILDER_INFO_DATE,
		CMD__FREE_RSC,
		NUM_OF__CMD

	} enmRemCmds_t;


	void* m_pMainDlg;
	// CDhaStteDevice* m_pDev;

	
	CStringA m_szLastCmdParams;

	// CConfLoaderDlg* m_pLoader;
	// CConfBuilderDlg* m_pBuilder;
	typedef enum enumPattern {

		enumPattern_Solid,
		enumPattern_Border,
		enumPattern_Crosshair,
		enumPattern_Flicker,
		enumPattern_Horizontal_Color_Bar,
		enumPattern_Vertical_Color_Bar,
		enumPattern_Horizontal_White_Greyscale,
		enumPattern_Horizontal_Red_Greyscale,
		enumPattern_Horizontal_Green_Greyscale,
		enumPattern_Horizontal_Blu_Greyscale,
		enumPattern_Top_Left_Rect,
		enumPattern_Center_Rect,
		enumPattern__NUMOF

	}type_enumPattern;

	CStringA s_SelPattern[enumPattern::enumPattern__NUMOF]{

		"Solid",
		"Border",
		"Crosshair",
		"Flicker",
		"Horizontal Color Bar",
		"Vertical Color Bar",
		"Horizontal White Greyscale",
		"Horizontal Red Greyscale",
		"Horizontal Green Greyscale",
		"Horizontal Blu Greyscale",
		"Top-Left Rect",
		"Center Rect"

	};


	void ProcessUserMsg(CString& sText, int iParam);

	double MinDutyNvg;
	int MaxDutyNvg;

	double MinDutyDay;
	double MaxDutyDay;







	

	
private:
	CRemoteProcess m_remProcess;
	CIniFileMng m_iniMng;
	bool m_bMaxIteration;


	afx_msg LRESULT OnNeedUpdate(WPARAM a, LPARAM b);

	bool _cmd_CMD__SYS_CONNECT(bool TargetConnect);
	bool _cmd_CMD__prova_disconnect();
	bool _cmd_CMD__prova_disconnect_heater();
	bool _cmd_CMD__prova_connect_heater();
	bool _cmd_CMD__prova_destroy_win();
	bool _cmd_CMD__FREE_RSC();

	bool _cmd_CMD__BRIG_DUTY(int TargetDuty);
	bool _cmd_CMD__BRIG_CURRENT(int TargetCurrent);
	bool _cmd_CMD__BRIG_POTENTIOMETER(int TargetPot);
	bool _cmd_CMD__BRIG_DAY(bool TargetDay);

	bool _cmd_CMD__CONNECT_COM(bool TargetConnect);
	bool _cmd_CMD__LCD_PATTERN(CStringA TargetPattern);
	bool _cmd_CMD__LCD_PATTERN_COLOR_1(CStringA TargetColor);
	bool _cmd_CMD__LCD_PATTERN_COLOR_2(CStringA TargetColor);
	// bool _cmd_CMD__BUILDER_INFO_CLASS(std::string Code, std::string Date, std::string Name, std::string Author);
	bool _cmd_CMD__BUILDER_INFO(std::string Code, std::string Date, std::string Name, std::string Author);
	bool _cmd_CMD__BUILDER_INFO_CODE(CStringA Code);
	bool _cmd_CMD__BUILDER_INFO_DATE(CStringA Date);
	bool _cmd_CMD__BUILDER_SAVE(CString TargetName);
	bool _cmd_CMD__BUILDER_OPEN(CString TargetName);

	int _cmd_CMD__BUILDER_GET_MIN_DUTY_NVG();
	bool _cmd_CMD__BUILDER_SET_MIN_DUTY_NVG(CStringA TargetMinNvg);

	int _cmd_CMD__BUILDER_GET_MAX_DUTY_NVG();
	bool _cmd_CMD__BUILDER_SET_MAX_DUTY_NVG(CStringA TargetMinNvg);

	int _cmd_CMD__BUILDER_GET_MIN_DUTY_DAY();
	bool _cmd_CMD__BUILDER_SET_MIN_DUTY_DAY(CStringA TargetMinNvg);

	int _cmd_CMD__BUILDER_GET_MAX_DUTY_DAY();
	bool _cmd_CMD__BUILDER_SET_MAX_DUTY_DAY(CStringA TargetMinNvg);

	bool _cmd_CMD__IDC_OPER_BRT_MODE(bool TargetBrt);
	bool _cmd_CMD__OPR_CRV_BRIGHTNESS_SET(int TargetBrightness);
	int _cmd_CMD__OPR_CRV_BRIGHTNESS_GET();

	bool _cmd_CMD__LDR_READ(CString TargetFileName);
	bool _cmd_CMD__LDR_WRITE(CString TargetFileName);
	

	std::string _touchFile();
	void _replyOk();
	void _replyString(float TargetS);




	CEnhMaintDlg* m_pMaint;
	CBrtBuilderDlg* m_pBuilder;
	CLoaderDlg* m_pLoader;
	CFileDialog* m_pFile;

	CDhaStteDevice* m_pDha;

	typedef enum tmrState
	{
		TMR_STATE_IDLE = 0,
		TMR_STATE_PROCESSING_CMD,
		TMR_STATE_WFOR_FINISH,
	} tmrState_t;

	tmrState_t m_tmrState;
	void OnTimer(UINT_PTR nIDEvent);
	enmRemCmds_t m_lastCmd;

	CString m_LastUserMsg;
	void _replyFail();

	void _manageWFFState();

	bool _CreateEnhDlg(bool Open, bool ShowOption);
	bool EnhMaintDlg_Open = FALSE;

	bool _CreateBuilderDlg(bool Open, bool ShowOption);
	bool BrtBuilderDlg_Open = FALSE;

	bool _CreateLoaderDlg(bool Open, bool ShowOption);
	bool BrtLoaderDlg_Open = FALSE;





	

	

};


