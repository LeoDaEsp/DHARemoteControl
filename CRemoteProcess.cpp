#include "stdafx.h"
#include "CRemoteProcess.h"
#include "CRemotePanel.h"

CRemoteProcess::CRemoteProcess(void)
{
	m_bInitialized = FALSE;
	m_pRemPnl = NULL;

	m_rxBuffer.reserve(RX_BUFFER_SIZ * 2); // per evitare reallocazione
}

CRemoteProcess::~CRemoteProcess(void)
{
}


BOOL CRemoteProcess::Initialize(CRemotePanel* pGraph)
{
	m_pRemPnl = pGraph;
	m_machState = ENM_WAIT_HEAD;
	m_msgSize = 0;

	ClientTCPMng::CClientParam par;
	par.port = TCP_PORT;
	par.id = 0;
	par.szIP = _T("127.0.0.1");
	BOOL bOK = m_TCPClient.Connect(par);
	if (!bOK)
	{
		return FALSE;
	}
	__super::m_IdleTime = 300;
	_startThread(_T("CRemoteProcess -> THRD"));
	m_bInitialized = TRUE;

	m_szParams = "";
	return 0;
}

void CRemoteProcess::Deinit()
{
	if (m_bInitialized)
	{
		_stopThread();
		m_TCPClient.Disconnect();
		m_bInitialized = FALSE;
	}
}

void CRemoteProcess::_finished()
{

}


void CRemoteProcess::_begin()
{

}


void CRemoteProcess::_loop()
{
	m_TCPClient.CIRCBUFF_GetData(m_rxBuffer);

	for (int i = 0; i < m_rxBuffer.size(); i++)
	{
		switch (m_machState)
		{
		case ENM_WAIT_HEAD:
			if (m_rxBuffer[i] == s_HeadId)
			{
				m_machState = ENM_WAIT_COMPLETE;
				memset(m_msgbuf, 0, MAX_BUF_SIZE);
				m_msgSize = 0;
			}
			break;

		case ENM_WAIT_COMPLETE:
			if (m_msgSize >= MAX_BUF_SIZE - 10)
			{
				m_machState = ENM_WAIT_HEAD;
				//msg sbagliato..
			}
			else if (m_rxBuffer[i] == s_CompleteId)
			{
				m_machState = ENM_WAIT_HEAD;
				//Msg completato..lo notifico..
				_mngMsg();
			}
			else
			{
				m_msgbuf[m_msgSize] = m_rxBuffer[i];
				m_msgSize++;
			}
			break;
		}
	}
}



void CRemoteProcess::_mngMsg()
{
	//Gestire con una FIFO da scaricare nell'OnTimer del Main SW
	m_cs.Lock();
	m_msgbuf[m_msgSize] = 0;
	m_msgbuf[MAX_BUF_SIZE - 1] = 0;
	m_szParams = CStringA(&m_msgbuf[0]);
	m_cs.Unlock();

	WPARAM wParam = 0;
	LPARAM lParam = 0;
	m_pRemPnl->PostMessage(WM_GRAPH_UPD_NEED, 0, 0);
}


void CRemoteProcess::TXToLib(unsigned char* pBuf, int nSize)
{
	if (m_TCPClient.IsConnected())
	{
		m_TCPClient.Send(pBuf, MAX_BUF_SIZE);

	}
}

void CRemoteProcess::GetCmdParam_str(CStringA& param)
{
	m_cs.Lock();
	param = m_szParams;
	m_szParams = "";
	m_cs.Unlock();
}

LRESULT CRemotePanel::OnNeedUpdate(WPARAM a, LPARAM b)
{
	if (m_tmrState == TMR_STATE_IDLE)
	{
		m_tmrState = TMR_STATE_PROCESSING_CMD;
		m_remProcess.GetCmdParam_str(m_szLastCmdParams);

		M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("#New CMD Rx:\n"));
		M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(m_szLastCmdParams);
		// M_GETLISTBOX(IDC_LIST_RMT_CMD)->AddString(_T("\n"));
		M_GETLISTBOX(IDC_LIST_RMT_CMD)->SetCurSel(M_GETLISTBOX(IDC_LIST_RMT_CMD)->GetCount() - 1);
	}
	return 0;
}