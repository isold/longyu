
#ifndef WIN32
#include <pthread.h>
#include <sys/time.h>
#include <errno.h> 
#endif

#include "include.h"
#include "CriticalSection.h"

CCriticalSection::CCriticalSection()
{
#ifdef WIN32
	InitializeCriticalSection(&moSection);
#else
	pthread_mutexattr_t attr;
	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(&mMutex, &attr);
#endif
}

CCriticalSection::~CCriticalSection()
{
#ifdef WIN32
	DeleteCriticalSection(&moSection);
#else
	pthread_mutex_destroy(&mMutex);
#endif
}

CAutoLock::CAutoLock(CCriticalSection& aoSection):moSection(aoSection)
{
	moSection.Enter();
}
CAutoLock::~CAutoLock()
{
	moSection.Leave();
}

CEvent::CEvent()
{
#ifdef WIN32
	mhEventHandle = NULL;
#else

#endif
}

CEvent::~CEvent()
{
#ifdef WIN32
	ASSERT(mhEventHandle == NULL);
#else

#endif
}

//�����¼�
//Linux�²�֧���ֶ����÷�ʽ�ͳ�ʼ���¼�״̬��������������Ч
bool CEvent::Create(bool bManualReset /* = false */, bool bInitialState /* = false */)
{
#ifdef WIN32
	mhEventHandle = CreateEvent(NULL, abManualReset, abInitialState, NULL);
#else    
	mhMutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_init(&mhMutex, NULL);
	pthread_cond_init(&mhCond_t, NULL); 
#endif
	return true;
}

int CEvent::WaitForEvent(uint32 dwMilliseconds)
{
#ifdef WIN32
	uint32 ldwResult = WaitForSingleObject(mhEventHandle, dwMilliseconds);

	if (ldwResult == WAIT_OBJECT_0)
	{
		return 0;
	}
	else if (ldwResult == WAIT_TIMEOUT)
	{
		return -1;
	}

	return -2;

#else
	if (dwMilliseconds == (uint32)-1)
	{
		//ʹ�߳�������һ�����������Ļ������ϣ��������ȴ�
		pthread_mutex_lock(&mhMutex);
		pthread_cond_wait(&mhCond_t, &mhMutex);
		pthread_mutex_unlock(&mhMutex);
		return 0;
	}

	struct timeval now;      /*time when we started waiting*/ 
	struct timespec timeout; /*timeout value for the wait function */ 

	pthread_mutex_lock(&mhMutex);		//Lock
	//ȡ��ǰʱ��
	gettimeofday(&now, NULL); 
	//׼��ʱ����ֵ        
	timeout.tv_sec = now.tv_sec + dwMilliseconds / 1000; 
	timeout.tv_nsec = ((now.tv_usec + dwMilliseconds) % 1000) * 1000;        

	//ʹ�߳�������һ�����������Ļ������ϣ���ʱ�ȴ�
	int ldwResult = pthread_cond_timedwait(&mhCond_t, &mhMutex, &timeout);
	pthread_mutex_unlock(&mhMutex);		//UnLock
	if(ldwResult == ETIMEDOUT)
	{
		return -1;
	}
	return 0;
#endif    
}

//�����¼�Ϊ���ź�
void CEvent::SetEvent()
{
#ifdef WIN32
	if (mhEventHandle)
	{
		::SetEvent(mhEventHandle);
	}
#else
	//�������б���������������mhCond_t�ϵ��̡߳�
	pthread_cond_broadcast(&mhCond_t);
#endif
}

//���������¼�Ϊ���ź�
void CEvent::ResetEvent()
{
#ifdef WIN32
	if (mhEventHandle)
	{
		::ResetEvent(mhEventHandle);
	}
#endif
}

//�ر��¼�
void CEvent::Close()
{
#ifdef WIN32
	if (mhEventHandle != NULL)
	{
		CloseHandle(mhEventHandle);
		mhEventHandle = NULL;
	}
#else
	pthread_mutex_destroy(&mhMutex);
	pthread_cond_destroy(&mhCond_t);
#endif
}




