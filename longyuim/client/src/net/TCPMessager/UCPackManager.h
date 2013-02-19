#pragma once

#include "PackManager.h"

class CUCPackManager: public CPackManager<CUCPackManager>
{
public:
	CUCPackManager(int aiBufferMaxLen = TCPPACK_LEN);

	virtual ~CUCPackManager(){}

	//----------------------------------------------------
	//����������ݴ����TCPͨѶ��
	//������	apInData: ���������
	//		awInDataLen ��������ݵĳ���
	//		char * apTcpPack ����õ�TCP����
	//		WORD& awTcpPackLen ����õ�tcp���ݳ���
	//����ֵ��	int  1= �ɹ���-1=ʧ��
	//���ͣ�				
	//----------------------------------------------------
	virtual int	Pack(char* apInData, WORD awInDataLen, char* apTcpPack, WORD& awTcpPackLen);

	//----------------------------------------------------
	//��TCPͨѶ�����
	//������
	//		char * apTcpBuffer  TCP����
	//		WORD& awTcpBuffLen TCP���泤��
	//		apOutData: ����������
	//		WORD& awOutDataLen ���������ݵĳ���
	//      WORD&  awtimestamp ʱ���λ����ֵ
	//����ֵ��	 1= �ɹ���-1=ʧ��

	//----------------------------------------------------
	virtual int UnPack(char* apTcpBuffer, WORD& awTcpBuffLen, char* apOutData, WORD& awOutDataLen, WORD& awtimestamp);
private:

	//----------------------------------------------------
	// ��TCP�����зֽ��TCP��(������tcp����
	//      ��Ҫ���������İ��ӻ��������Ƴ�������Ӧ�޸Ļ��������ݵĳ���)
	//������
	//		char * apTcpBuffer  TCP����
	//		WORD& awTcpBuffLen TCP���泤��
	//		char * apTcpPack  ��������tcp���ݰ�
	//		WORD& awTcpPackLen ��������tcp���ݰ��ĳ���
	//����ֵ��	int  1= ��������tcp���ݰ���
	//		    	-1=û�з�����tcp���ݰ�
	//----------------------------------------------------
	int	AnalyseTcpStoreBuffer(char* apTcpBuffer, WORD& awTcpBuffLen, char* apTcpPack, WORD& awTcpPackLen);
private:
	WORD mwTimestamp;
};