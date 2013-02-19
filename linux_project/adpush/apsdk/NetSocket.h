/********************************************************************
	created:	2011/03/08
	created:	8:3:2011   10:01
	file base:	NetSocket
	file ext:	h
	author:		������
	
	purpose:	TCPЭ��SOCKET�ӿ���
*********************************************************************/
#ifndef _NET_SOCKET_H_
#define _NET_SOCKET_H_

#include "base/include.h"
#include "base/pack/NetPack.h"
#include "base/list.h"

#define DEF_LOCAL_ADDR "127.0.0.1"
#define DEF_SOCKET_CATCH_LEN (10*1024)
#define RECV_CATCH_LEN (DEF_SOCKET_CATCH_LEN+DEF_BUFFER_LEN+1)
#define SEND_CATCH_LEN (DEF_SOCKET_CATCH_LEN+1)

#if defined(__linux__) || defined(__APPLE__)

#define SOCKET int

#endif

#ifdef _WIN32

typedef int socklen_t;

class CWinNet
{
public:
	CWinNet()
	{
		WSADATA wsd;
		WSAStartup(MAKEWORD(2,2),&wsd);
	}
	~CWinNet()
	{
		WSACleanup();
	}
	static CWinNet* Instance()
	{
		if( PWinNetInstance == 0 )
		{
			PWinNetInstance = new (CWinNet);
		}
		return PWinNetInstance; 
	}

	static CWinNet* PWinNetInstance;

};

#endif

class STRU_NET_DATA_INFO
{
public:
	STRU_NET_DATA_INFO()
	{
		buffer = NULL;
		length = 0;
	}	

	~STRU_NET_DATA_INFO(){}

	STRU_NET_DATA_INFO(const STRU_NET_DATA_INFO &info)
	{
		if(this != &info)
		{
			buffer = info.buffer;
			length = info.length;
		}
	}
	STRU_NET_DATA_INFO& operator = (const STRU_NET_DATA_INFO &info)
	{
		if(this != &info)
		{
			buffer = info.buffer;
			length = info.length;
		}
		return *this;
	}
public:
	char* buffer;
	int length;
};

//����״̬
enum NET_STAT
{
	//����
	TCP_ERROR = ERROR,
	//����
	COMMON_TCP_LISTEN, 
	COMMON_TCP_SYN_SENT,
	COMMON_TCP_SYN_RECEIVED, 
	COMMON_TCP_ESTABLISHED, 
	COMMON_TCP_CONNECTING,
	COMMON_TCP_CONNECTED,
	COMMON_TCP_CLOSED
};

enum SEND_STAT
{
	SEND_NULL = ERROR,
	SENDINT,
	SENDED
};

class CNetSocket
{
public:
	CNetSocket();
	CNetSocket(CNetPack *pack)
	{
		assert(pack != NULL);
		m_pNetPack = pack;
	}
	~CNetSocket();

	inline void SetNetPack(CNetPack *pack)
	{
		assert(pack != NULL);
		m_pNetPack = pack;
	}

	//����socket�����󶨵�ָ���˿�
	//��������Ϊ�����ֽ���
	bool CreateSocket(const char* ip, const short port);
	//����socket������Ҫ��
	bool CreateSocket(void);

	//�ر��׽��֣�����������Դ
	bool Close(int flag = 2);
	//ֻ�ǹر��׽��ֲ��������Դ
	void CloseWR(int flag = 2);

	void CloseSocket(SOCKET socket)
	{
#if defined(__linux__) || defined(__APPLE__)
		close(socket);
#endif

#ifdef _WIN32
		closesocket(socket);
#endif
	}

	//��������
	bool Listen();
	//�����ֽ���
	bool ConnectServer(const char* ip, const short port);

	//ACCEPT ip �� port��Ϊ�����ֽ���
	int Accept(unsigned int &ip, uint16_t &port);

	bool SetNoBlock();

	int SendData(const char* buffer, const int length);

	int SendData();

	bool RecvData(char* buffer, int &length);

	bool RecvData();

	const SOCKET GetSocket(){ return miSocket; }

private:
	int _SendData(const char* buffer, const int length);
	int SendCacheData(void);
	//nKeepAlive-�Ƿ������
	//nKeepIdle-�೤ʱ���������շ�, ��̽��
	//nKeepInterval-̽�ⷢ��ʱ����
	//nKeepCnt-̽�Ⳣ�Դ���
	int SetTcpSockKeepAlive(int nKeepAlive,int nKeepIdle,
		int nKeepInterval, int nKeepCnt);

public:
	NET_STAT moNetStat;
	SOCKET miSocket;
	bool mbListenSocket;
	bool mbClientSocket;
	bool mbCanSend;
	SEND_STAT moSendStat;
	char mszResendBuffer[SEND_CATCH_LEN];
	CCriticalSection moSendSection;
	CCriticalSection moRecvSection;
	int miResendLength;
	_List<STRU_NET_DATA_INFO> moSendList;
	_List<STRU_NET_DATA_INFO> moRecvList;
	char mszRecvCache[RECV_CATCH_LEN];
	int miRecvCacheLength;
	CNetPack*  m_pNetPack;
};
#endif //_NET_SOCKET_H_

















