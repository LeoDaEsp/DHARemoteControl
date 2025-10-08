
#pragma once
#include "EthernetGlobals.h"
#include "Thrd.h"
#include <vector>

class ClientTCPMng : public Thrd
{
public:
	ClientTCPMng(void);
	virtual ~ClientTCPMng(void);

	class CClientParam;
	BOOL Connect(CClientParam param);
	BOOL Disconnect();
	BOOL IsConnected();
	BOOL Send(unsigned char* pData, int size);

	class CClientParam
	{
	public:
		CClientParam()
		{
			szIP = _T("");
			port = 55555;
			bDisableNagle = TRUE;
			bSetWindow = FALSE; //meglio non usare!!
			bNoBlock = FALSE; //meglio non usare!!
			id = 0;
		}

		CString szIP;
		WORD port;
		BOOL bDisableNagle;
		BOOL bSetWindow;
		BOOL bNoBlock;
		int id;
	};

	int CIRCBUFF_GetBytesAvailForRead();
	void CIRCBUFF_GetData(std::vector<unsigned char>& v);

private:
	BOOL _Recv(unsigned char* pData, int& nSize, int nMaxAvlSize);
	CClientParam m_param;
	BOOL m_bIsConnected;
	CCriticalSection m_cs;
	SOCKET m_ConnectSocket;

#define TMP_RX_BUF_SIZ (1024)
	unsigned char m_rxTmpBuf[TMP_RX_BUF_SIZ];

#define RX_BUFFER_SIZ (1024*1024)
	std::vector<unsigned char> m_rxBuffer;

	//////////////////////////////////////////////////////////////////////////////////////////////
protected:
	void _loop() override;
	void _finished() override;
	void _begin() override;
};

