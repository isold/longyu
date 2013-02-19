

#ifndef _CRITICAL_SECTION_H_
#define _CRITICAL_SECTION_H_

#ifdef WIN32

#else
#include <pthread.h>
#include <sys/time.h>
#include <errno.h> 
#endif
#include "define.h"

class CCriticalSection
{
public:
	CCriticalSection();
	~CCriticalSection();

	//�����ٽ���
	inline void Enter()
	{
#ifdef WIN32
		EnterCriticalSection(&moSection);
#else
		pthread_mutex_lock(&mMutex);
#endif
	}
	//�뿪�ٽ���
	inline void Leave()
	{
#ifdef WIN32
		LeaveCriticalSection(&moSection);
#else
		pthread_mutex_unlock(&mMutex);
#endif
	}

private:
#ifdef WIN32
	//Windowsƽ̨�ٽ�������
	CRITICAL_SECTION moSection;
#else
	//Linuxƽ̨����ṹ�����
	pthread_mutex_t mMutex;
#endif
};

//�Զ��ٽ�����ʵ����
class CAutoLock
{
public:
	//���캯��
	CAutoLock(CCriticalSection& aoSection);
	//��������
	~CAutoLock();
private:
	CCriticalSection& moSection;
};

class CEvent
{
public:
	CEvent();
	~CEvent();

public:
	//�����¼�
	bool Create(bool bManualReset = false, bool bInitialState = false);
	//�ȴ��¼�
	int WaitForEvent(uint32 dwMilliseconds);
	//�����¼�Ϊ���ź�
	void SetEvent();
	//���������¼�Ϊ���ź�
	void ResetEvent();
	//�ر��¼�
	void Close();

private:
#ifdef WIN32
	//�¼����
	void*				mhEventHandle;
#else
	//Ϊ�˷�ֹ����������������ʹ�����Ǻ�һ�������������һ��
	//Linuxƽ̨����ṹ�����
	pthread_mutex_t		mhMutex;
	//Linux���������ṹ�����
	pthread_cond_t		mhCond_t;
#endif
};
#endif //_CRITICAL_SECTION_H_
