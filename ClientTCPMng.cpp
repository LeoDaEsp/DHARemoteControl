#include "StdAfx.h"
#include "ClientTCPMng.h"


ClientTCPMng::ClientTCPMng(void)
{
	m_bIsConnected = FALSE;
	m_ConnectSocket = INVALID_SOCKET;
	m_rxBuffer.reserve(RX_BUFFER_SIZ * 2); // per evitare reallocazione
}

ClientTCPMng::~ClientTCPMng(void)
{

}

BOOL ClientTCPMng::Connect(CClientParam param)
{
	if (m_bIsConnected)
		return FALSE;

	m_param = param;
	m_bIsConnected = FALSE;

	TRACE(_T("Connecting on addr: %s port %d ..\n"), param.szIP, (int)param.port);
	WSADATA wsaData;
	struct addrinfo* result = NULL,
		* ptr = NULL,
		hints;

	int iResult;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
	{
		TRACE(_T("WSAStartup failed with error: %d\n"), iResult);
		return FALSE;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port
	CString szPort;
	szPort.Format(_T("%d"), param.port);
	CStringA szPortA(szPort);
	CStringA szIPA(param.szIP);
	iResult = getaddrinfo(szIPA, szPortA, &hints, &result);
	if (iResult != 0)
	{
		TRACE(_T("getaddrinfo failed with error: %d\n"), iResult);
		WSACleanup();
		return FALSE;
	}

	// Attempt to connect to an address until one succeeds
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next)
	{
		// Create a SOCKET for connecting to server
		m_ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
		if (m_ConnectSocket == INVALID_SOCKET)
		{
			TRACE(_T("socket failed with error: %ld\n"), WSAGetLastError());
			WSACleanup();
			return FALSE;
		}

		if (param.bSetWindow)
		{
			int nSize = 800;
			int nSizeLen = sizeof(int);
			int iResult = setsockopt(m_ConnectSocket, SOL_SOCKET, SO_RCVBUF, (char*)&nSize, nSizeLen);
			if (iResult == SOCKET_ERROR)
			{
				WSACleanup();
				return FALSE;
			}
			nSize = 800;
			iResult = setsockopt(m_ConnectSocket, SOL_SOCKET, SO_SNDBUF, (char*)&nSize, nSizeLen);
			if (iResult == SOCKET_ERROR)
			{
				WSACleanup();
				return FALSE;
			}
		}
		if (param.bDisableNagle)
		{
			int iOptVal = 0;
			int iOptLen = sizeof(int);

			BOOL bOptVal = FALSE;
			int bOptLen = sizeof(BOOL);

			/* keep-alive off */
			int iResult = setsockopt(m_ConnectSocket, SOL_SOCKET, SO_KEEPALIVE, (char*)&bOptVal, bOptLen);

			/* Nagle's algorithm off */
			bOptVal = TRUE;
			iResult |= setsockopt(m_ConnectSocket, SOL_SOCKET, TCP_NODELAY, (char*)&bOptVal, bOptLen);
			//iResult |= setsockopt(m_ConnectSocket, SOL_SOCKET, SO_SNDBUF, (char*)& iOptVal, iOptLen);

			//iOptVal = 10; /* 10 msec timeout */
			//iResult |= setsockopt(m_ConnectSocket, SOL_SOCKET, SO_RCVTIMEO, (char*)& iOptVal, iOptLen);
			//iResult |= setsockopt(m_ConnectSocket, SOL_SOCKET, SO_SNDBUF, (char*)& iOptVal, iOptLen);

			if (iResult == SOCKET_ERROR)
			{
				WSACleanup();
				return FALSE;
			}
		}

		// Connect to server.
		iResult = connect(m_ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR)
		{
			closesocket(m_ConnectSocket);
			m_ConnectSocket = INVALID_SOCKET;
			continue;
		}
		break;
	}
	freeaddrinfo(result);

	if (m_ConnectSocket == INVALID_SOCKET)
	{
		//TRACE(_T("Unable to connect to server!\n"));
		WSACleanup();
		return FALSE;
	}

	//u_long iMode=1;
	//ioctlsocket(m_ConnectSocket,FIONBIO,&iMode); 

	m_bIsConnected = TRUE;
	TRACE(_T("Connection OK\n"));

	CString szId;
	szId.Format(_T("CLIENT %d"), param.id);

	_startThread(szId);
	return TRUE;
}

BOOL ClientTCPMng::Disconnect()
{
	// shutdown the connection since no more data will be sent
	int iResult = shutdown(m_ConnectSocket, SD_SEND);
	if (iResult == SOCKET_ERROR)
	{
		TRACE(_T("shutdown failed with error: %d\n"), WSAGetLastError());
	}

	closesocket(m_ConnectSocket);
	WSACleanup();

	m_cs.Lock();
	m_bIsConnected = FALSE;
	m_cs.Unlock();

	_stopThread();
	return FALSE;
}

BOOL ClientTCPMng::IsConnected()
{
	m_cs.Lock();
	BOOL res = m_bIsConnected;
	m_cs.Unlock();
	return res;
}

BOOL ClientTCPMng::Send(unsigned char* pData, int nSize)
{
	m_cs.Lock();
	BOOL bConn = m_bIsConnected;
	m_cs.Unlock();

	if (!bConn)
		return FALSE;

	int iSendResult = send(m_ConnectSocket, (char*)pData, nSize, 0);
	if (iSendResult == SOCKET_ERROR)
	{
		TRACE(_T("send failed with error: %d\n"), WSAGetLastError());
		m_cs.Lock();
		m_bIsConnected = FALSE;
		m_cs.Unlock();

		return FALSE;
	}
	TRACE(_T("Bytes sent: %d\n"), iSendResult);

	return TRUE;
}

BOOL ClientTCPMng::_Recv(unsigned char* pData, int& nSize, int nMaxAvlSize)
{
	m_cs.Lock();
	BOOL bConn = m_bIsConnected;
	m_cs.Unlock();

	if (!bConn)
		return FALSE;

	nSize = recv(m_ConnectSocket, (char*)m_rxTmpBuf, TMP_RX_BUF_SIZ, 0);
	if (nSize > 0)
	{
		TRACE(_T("Bytes received: %d\n"), nSize);
		m_cs.Lock();
		for (int i = 0; i < nSize; i++)
		{
			m_rxBuffer.push_back(m_rxTmpBuf[i]);
		}
		m_cs.Unlock();
	}
	else if (nSize == 0)
	{
		m_cs.Lock();
		m_bIsConnected = FALSE;
		m_cs.Unlock();
		return FALSE;
	}
	else
	{
		m_cs.Lock();
		m_bIsConnected = FALSE;
		m_cs.Unlock();
		return FALSE;
	}
	return TRUE;
}

void ClientTCPMng::_loop()
{
	int nSize = 0;

	BOOL bRes = _Recv(m_rxTmpBuf, nSize, PKT_BUF_SIZE);
	if (bRes && (nSize > 0))
	{
		m_cs.Lock();
		for (int i = 0; i < nSize; i++)
		{
			m_rxBuffer.push_back(m_rxTmpBuf[i]);
		}
		m_cs.Unlock();
	}
}

void ClientTCPMng::_finished()
{
}

void ClientTCPMng::_begin()
{
}

int ClientTCPMng::CIRCBUFF_GetBytesAvailForRead()
{
	m_cs.Lock();
	auto siz = m_rxBuffer.size();
	m_cs.Unlock();
	return (int)siz;
}

void ClientTCPMng::CIRCBUFF_GetData(std::vector<unsigned char>& v)
{
	v.clear();
	m_cs.Lock();
	v = m_rxBuffer;
	m_rxBuffer.clear();
	m_cs.Unlock();
}