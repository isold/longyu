#ifndef _HTTPDOWNLOAD_H_
#define _HTTPDOWNLOAD_H_
#pragma once

#include "http.h"
#include "tcp.h"
#include "file.h"
#include "thread.h"

#include <algorithm>
using namespace std;

#define HTTP_MAX_BUFFER 10 * 1024

///////////////////////////////////////////////////////////////////////////////////////////////
enum
{
	HTTP_SUCCESS = 0x00000000,			 // ���أ��ϴ��ɹ�
	HTTP_FAIL = 0xFFFFFFFF,			    // ���أ� �ϴ�ʧ��
	HTTP_CONNECT_ERROR = 0x00000001,    //���ӷ�����ʧ��
	HTTP_REQUEST_ERROR = 0x00000002,    //����ʧ��
	HTTP_SEND_REQUEST_ERROR = 0x00000003,//��������ʧ��
	
};

enum
{
	METHOD_DOWNLOAD = 0x00000000,
	METHOD_UPLOAD = 0x00000001,
};
///////////////////////////////////////////////////////////////////////////////////////////////
class CHttpDownload: public CHttp,
	 public CTcpSocket,
	public CThread
{
public:
	CHttpDownload(void);
	 ~CHttpDownload(void);

	bool DownloadFile(std::string strUrl, std::string strFilePath);
	bool UploadFile(std::string strUrl, std::string strFilePath);
private:
	DWORD WINAPI ThreadWorkItem(void* parameter);
	bool ReadInternetFile(void);
	bool ReadInternetFileFun(CHttpDownload *pHttpDownload);
	bool WriteInternetFile(void);
	bool WriteInternetFileFun(CHttpDownload *pHttpUpload);
	bool Connect();
	bool Close();

public:
	void *m_hHandle;

private:
	std::string m_strFilePath;
	HANDLE m_thread;
	int m_nHttpError;
	int m_nFlag;
};
///////////////////////////////////////////////////////////////////////////////////////////////


#endif //_HTTPDOWNLOAD_H_