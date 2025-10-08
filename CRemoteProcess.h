#pragma once
#include "Thrd.h"
#include "ClientTCPMng.h"
#include "LibGlobals.h"

#include <vector>
#include <Shlwapi.h>
#include <tchar.h>
#include <string>
#include <sstream>
#include <vector>


static void SplitString(const std::string& s, char delim, std::vector<std::string>& elems)
{
	std::stringstream ss;
	ss.str(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
}

static void MySplitString(const CString& s, char delim, std::vector<CString>& elems)
{
	CStringA A(s);
	std::string myStd = A.GetBuffer();
	A.ReleaseBuffer();

	std::stringstream ss;
	ss.str(myStd);
	std::string item;
	//	CString tmp = _T("");
	while (std::getline(ss, item, delim))
	{
		CString tmp(item.c_str());
		//tmp.Format(_T("%s"), (char*)item.c_str());
		elems.push_back(tmp);
	}
}



class CRemotePanel;

class CRemoteProcess : public Thrd
{
public:
	CRemoteProcess(void);
	virtual ~CRemoteProcess(void);
	BOOL Initialize(CRemotePanel* pGraph);
	void Deinit();
	void TXToLib(unsigned char* pBuf, int nSize);
	void GetCmdParam_str(CStringA& param);
private:

	void _finished() override;
	void _begin() override;
	void _loop() override;
	void _mngMsg();

	BOOL m_bInitialized;
	ClientTCPMng m_TCPClient;
	//BYTE m_buf[MAX_BUF_SIZE];

	///Protocol
	typedef enum enmMachState
	{
		ENM_WAIT_HEAD = 0,
		ENM_WAIT_COMPLETE
	} enmMachState_t;

	enmMachState_t m_machState;
	BYTE m_msgbuf[MAX_BUF_SIZE];
	BYTE m_msgSize;
	CRemotePanel* m_pRemPnl;

	CCriticalSection m_cs;
	CStringA m_szParams;

	std::vector<unsigned char> m_rxBuffer;
};