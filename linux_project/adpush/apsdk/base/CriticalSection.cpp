#include "include.h"
#include "CriticalSection.h"

CCriticalSection::CCriticalSection()
{
#ifdef _WIN32
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
#ifdef _WIN32
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
:mbCreated(false)
{
	//TRACE(5,"CEvent::CEvent() construct:"<<apName);
#ifdef _WIN32
	mhEventHandle = NULL;
#else
	//mhCond_t = PTHREAD_COND_INITIALIZER;
#endif
}

CEvent::~CEvent()
{	
#ifdef _WIN32
	assert(mhEventHandle == NULL);
#else

#endif
}

//�����¼�
//Linux�²�֧���ֶ����÷�ʽ�ͳ�ʼ���¼�״̬��������������Ч
bool CEvent::Create(bool bManualReset /* = false */, bool bInitialState /* = false */)
{
#ifdef _WIN32
	mhEventHandle = CreateEvent(NULL, bManualReset, bInitialState, NULL);
#else    
	pthread_mutexattr_t attr;
	pthread_mutexattr_init(&attr);
	pthread_mutex_init(&mhMutex, &attr);
	pthread_mutexattr_destroy(&attr);
	pthread_cond_init(&mhCond_t, NULL); 
#endif
	mbCreated = true;
	return true;
}

int CEvent::WaitForEvent(unsigned int dwMilliseconds)
{
#ifdef _WIN32
	unsigned int ldwResult = WaitForSingleObject(mhEventHandle, dwMilliseconds);

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
	if (dwMilliseconds == (unsigned int)-1)
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
#ifdef _WIN32
	if (mhEventHandle)
	{
		::SetEvent(mhEventHandle);
	}
#else
	pthread_mutex_lock(&mhMutex);
	//�������б���������������mhCond_t�ϵ��̡߳�
	pthread_cond_broadcast(&mhCond_t);
	pthread_mutex_unlock(&mhMutex);
#endif
}

//���������¼�Ϊ���ź�
void CEvent::ResetEvent()
{
#ifdef _WIN32
	if (mhEventHandle)
	{
		::ResetEvent(mhEventHandle);
	}
#endif
}

//�ر��¼�
void CEvent::Close()
{
	if(mbCreated)
	{
#ifdef _WIN32
	if (mhEventHandle != NULL)
	{
		CloseHandle(mhEventHandle);
		mhEventHandle = NULL;
	}
#else
	pthread_cond_destroy(&mhCond_t);
	pthread_mutex_destroy(&mhMutex);
#endif
	mbCreated = false;
	}
}


#ifndef _WIN32
Conditional::Conditional(const char *id)
{
	pthread_mutexattr_t attr;
	pthread_mutexattr_init(&attr);
	pthread_mutex_init(&_mutex, &attr);
	pthread_mutexattr_destroy(&attr);
	pthread_cond_init(&_cond, NULL);
	miDataCount = 0;
}

Conditional::~Conditional()
{
	pthread_cond_destroy(&_cond);
	pthread_mutex_destroy(&_mutex);
	miDataCount = 0;
}

bool Conditional::tryEnterMutex(void)
{
	if(pthread_mutex_trylock(&_mutex) != 0)
		return false;
	return true;
}

void Conditional::enterMutex(void)
{
	pthread_mutex_lock(&_mutex);
}

void Conditional::leaveMutex(void)
{
	pthread_mutex_unlock(&_mutex);
}

void Conditional::signal(bool broadcast)
{
	enterMutex();
	miDataCount++;
	if(broadcast)
		pthread_cond_broadcast(&_cond);
	else
		pthread_cond_signal(&_cond);
	leaveMutex();
}

bool Conditional::wait(timeout_t timeout, bool locked)
{
	struct timespec ts;
	int rc;

	if(!locked)
		enterMutex();
	if(!timeout) 
	{
		if(miDataCount-- <= 0)
		{
			pthread_cond_wait(&_cond, &_mutex);
		}

		if(!locked)
			leaveMutex();
		return true;
	}
	getTimeoutEx(&ts, timeout);
	rc = pthread_cond_timedwait(&_cond, &_mutex, &ts);
	if(!locked)
		leaveMutex();
	if(rc == ETIMEDOUT)
		return false;
	return true;
}

#endif

