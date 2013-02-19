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

#include "include.h"
#include "CriticalSection.h"
#include "NetPack.h"
#include "list.h"

#define DEF_LOCAL_ADDR "127.0.0.1"
#define DEF_SOCKET_CATCH_LEN (10*1024)
#define RECV_CATCH_LEN (DEF_SOCKET_CATCH_LEN+DEF_BUFFER_LEN+1)
#define SEND_CATCH_LEN (DEF_SOCKET_CATCH_LEN+1)

class STRU_NET_DATA_INFO{
public:
	STRU_NET_DATA_INFO(){
		buffer = NULL;
		length = 0;
	}	

	~STRU_NET_DATA_INFO(){}

	STRU_NET_DATA_INFO(const STRU_NET_DATA_INFO &info){
		if(this != &info){
			buffer = info.buffer;
			length = info.length;
		}
	}
	STRU_NET_DATA_INFO& operator = (const STRU_NET_DATA_INFO &info){
		if(this != &info){
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
enum NET_STAT{
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

class CNetSocket
{
public:
	CNetSocket();
	CNetSocket(CNetPack *pack){
		ASSERT(pack != NULL);
		m_pNetPack = pack;
	}
	~CNetSocket();

	inline void SetNetPack(CNetPack *pack){
		ASSERT(pack != NULL);
		m_pNetPack = pack;
		
		//������ǿͻ�������socket������Ϊ��accept������socket��ʹ��epollĬ�ϵ�Э��
		if (miSocket>0 && !mbClientSocket && !mbListenSocket)
		{
			mp_net_io = m_pNetPack->create_svr_io(miSocket);
			mp_net_io->open();			
		}		
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
	//��������
	bool Listen();
	//�����ֽ���
	bool ConnectServer(const char* ip, const short port);
	//ACCEPT ip �� port��Ϊ�����ֽ���
	int Accept(unsigned int &ip, unsigned short &port);
	bool SetNoBlock();
	int SendData(const char* buffer, const int length);
	int SendData();
	bool RecvData(char* buffer, int &length);
	bool RecvData();
	const int GetSocket(){ return miSocket; }

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
	int miSocket;
	bool mbListenSocket;
	bool mbClientSocket;
	bool mbCanSend;
	CNetPack *m_pNetPack;	
	//io�ӿ�
	i_net_io *mp_net_io;

private:
	char mszResendBuffer[SEND_CATCH_LEN];
	CCriticalSection moSendSection;
	CCriticalSection moRecvSection;
	int miResendLength;
	_List<STRU_NET_DATA_INFO> moSendList;
	_List<STRU_NET_DATA_INFO> moRecvList;
	char mszRecvCache[RECV_CATCH_LEN];
	int miRecvCacheLength;
};
#endif //_NET_SOCKET_H_

















