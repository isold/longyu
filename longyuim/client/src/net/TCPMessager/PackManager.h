#pragma once
#include "Interface.h"
#include "AutoBuffer.h"
#include "AutoLock.h"

#define TCPPACK_LEN   64*1024 - 1        //tcp����󳤶�
#define MAXBUFFSIZE 65536

#define WM_SOCKET_CLOSE WM_USER + 1000
#define WM_SOCKET_ERROR WM_USER + 1001
#define WM_RECV_PACK	WM_USER + 1002
#define WM_SOCKET_OPEN_RESULT	WM_USER + 1003

typedef struct STRU_PACK_INFO
{
	char* mpBuffer;
	WORD mwBuffLen;
	STRU_PACK_INFO()
	{
		mpBuffer = new char[MAXBUFFSIZE];
		memset(mpBuffer, 0, MAXBUFFSIZE);
		mwBuffLen = MAXBUFFSIZE;
	}
	~STRU_PACK_INFO()
	{
		delete [] mpBuffer;
	}
}*PSTRU_PACK_INFO;

template<class T>
class CPackManager:public IPackManager
{
public:
	CPackManager(int aiBufferMaxLen);
	virtual ~CPackManager();

	virtual void SocketClose();
	virtual void SocketError(int ErrorCode);
	virtual void AddRecvData(const char* apszBuffer, WORD awDataLen);
	virtual int GetSendData(const char* apszBuffer, WORD& awMaxDataLen);

	//----------------------------------------------------
	//����������ݴ����TCPͨѶ��
	//������	apInData: ���������
	//		awInDataLen ��������ݵĳ���
	//		char * apTcpPack ����õ�TCP����
	//		WORD& awTcpPackLen ����õ�tcp���ݳ���
	//����ֵ��	int  1= �ɹ���-1=ʧ��
	//���ͣ�				
	//----------------------------------------------------
	//virtual int	Pack(char* apInData, WORD awInDataLen, char* apTcpPack, WORD& awTcpPackLen) = 0;

	///----------------------------------------------------
	//��TCPͨѶ�����
	//������
	//		char * apTcpBuffer  TCP����
	//		WORD& awTcpBuffLen TCP���泤��
	//		apOutData: ����������
	//		WORD& awOutDataLen ���������ݵĳ���
	//      WORD&  awtimestamp ʱ���λ����ֵ
	//����ֵ��	 1= �ɹ���-1=ʧ��

	//----------------------------------------------------
	//virtual int UnPack(char* apTcpBuffer, WORD& awTcpBuffLen, char* apOutData, WORD& awOutDataLen, WORD& awtimestamp) = 0;

	bool AddSendData(const char* apszBuffer, WORD awDataLen);

	void Init(HWND ahMsgHandle, void* apUserParam){mhMsgHandle = ahMsgHandle; mpUserParam = apUserParam;}

	void* GetUserParam(){return mpUserParam;}
private:
	char* mpRecvBuffer;
	int   miRecvBuffMaxlen;
	int   miRecvBuffLen;
	CAutoBuffer m_SendBuffer;
	CCriticalSection m_SendCS;
	CCriticalSection m_RecvCS;

	void* mpUserParam;
	HWND mhMsgHandle;
};