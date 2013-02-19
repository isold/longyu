#ifndef _HTTP_BASE_H_
#define _HTTP_BASE_H_

#include <WinSock2.h>
#pragma comment(lib, "Ws2_32")

#include <string>
#include <vector>
#include <strstream>
#include <WinInet.h>
#pragma comment(lib, "WININET.lib")
#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

#import "pstorec.dll" no_namespace
#pragma comment(lib, "COMCTL32.lib")

#include "common.h"
using namespace code_common;

/************************************************************************/
/** lock 
*/
/************************************************************************/
class CLock
{
public:
	CLock()
	{
		InitializeCriticalSection(&m_critsec);
	}

	CLock(const CLock&)
	{
		InitializeCriticalSection(&m_critsec);
	}

	virtual ~CLock()
	{
		DeleteCriticalSection(&m_critsec);
	}

	virtual void lock()
	{
		EnterCriticalSection(&m_critsec);
	}

	virtual void unlock()
	{
		LeaveCriticalSection(&m_critsec);
	}

private:
	CRITICAL_SECTION m_critsec;
};
/************************************************************************/
/** 
* ������Ϣ
*/
/************************************************************************/
class CProxyInfo
{
public:
	CProxyInfo();
	~CProxyInfo();

	void GetIEProxyInfo();
	bool IsValidProxy() const;

private:
	void GetIEProxyPassword();
public:
	std::string m_ip;
	unsigned short m_port;
	std::string m_user;
	std::string m_password;
	std::string m_domain;
};

/************************************************************************/
/** 
* ʹ��winnet �첽����
* Ŀ�꣺ HTTP���أ��ϴ��ļ���
* �÷��� һ��ʵ����Ӧһ̨�����������ӣ�����Ӳ�ͬ���������أ������µ�ʵ��
*/
/************************************************************************/
typedef enum
{
	HTTP_GET = 0,
	HTTP_POST = 1,
}HTTP_METHOD;


//����״̬�ص�����
typedef void (WINAPI *WINNET_STATE_FUN)(void* lpParameter);

class CHttpBase
{
public:
	CHttpBase(WINNET_STATE_FUN fun, HTTP_METHOD method = HTTP_GET);
	~CHttpBase(void);

	struct FileInfo
	{
		std::string url;
		std::string path;
	};

	typedef std::vector<FileInfo> FILE_LIST;
	typedef std::vector<FileInfo>::iterator FILE_ITER;

#define WM_THREAD_RTN WM_USER + 1000;
#define MAX_PACK_SIZE 1024 * 10

	void SetReferer(std::string &referer);
	bool Add(const char* pcszUrl, const char* pcszFilePath);

	static DWORD WINAPI ExecuteFun(void *p);

	static void CALLBACK InternetCallback(HINTERNET hInternet,
		DWORD_PTR dwContext, DWORD dwInternetStatus, LPVOID lpvStatusInformation,
		DWORD dwStatusInformationLength);

private:
	bool ConnectServer(void);
	bool Execute(void);
	bool Close(void);
	int WaitForEnd(HANDLE &handle, DWORD timeout = 30*1000);
	void HttpGetName(string strURL, string &strHostName, string &strFileName) const;
	BOOL HttpGetFileInfo(int &nFileSize);

private:
	FILE_LIST m_FileList;
	//list lock
	CLock m_FileListLock;
	CProxyInfo m_ProxyInfo;
	std::string m_strHost;
	std::string m_strMethod;
	std::string m_strReferer;

	//HTTP Internet application handle
	HINTERNET m_hSession; 
	//HTTP connection handle
	HINTERNET m_hConnect;
	//HTTP request handle 
	HINTERNET m_hRequest;

	HANDLE m_hDownThread;
	HANDLE m_hUpThread;
	unsigned int m_nDownId;
	unsigned int m_nUpId;
	//�̳߳�ʱʱ��
	unsigned int m_nTimeout;
	//�̵߳ȴ���ʱʱ��
	unsigned int m_nWaitTimeout;
	//֪ͨ�¼�
	HANDLE m_hEvent;
	HANDLE m_hEventRead;
	HANDLE m_hThread;
	DWORD m_dwThreadId;
	WINNET_STATE_FUN m_pStateFun;

};
#endif //_HTTP_BASE_H_