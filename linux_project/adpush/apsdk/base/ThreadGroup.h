#ifndef _THREAD_GROUP_H_
#define _THREAD_GROUP_H_

#include <list>
#include "include.h"
#include "CriticalSection.h"

using std::list;

//�̹߳�������
struct STRU_THREAD_CONTEXT;

//����ʹ�õ��̺߳���ԭ�ͺ������߳���Ҫ�ĺ���ԭ��
#ifdef _WIN32
#include <process.h>
typedef unsigned int ( __stdcall ThreadFunc) (STRU_THREAD_CONTEXT&);
typedef unsigned int ( __stdcall StdThreadFunc) (void * );
#else
typedef unsigned int (ThreadFunc) (STRU_THREAD_CONTEXT&);
typedef void* (StdThreadFunc) (void * );
#endif

//�ṩ�̵߳ļ��ӹ���
class CThreadStat
{
public:
	CThreadStat()
		: miStep( 0 )
	{
		memset(this, 0, sizeof(CThreadStat));
		Alive();
		threadIndex = 0;
	}

	//�㱨���
	void Alive()
	{ 
	/*	ftime( &mtLastAliveTime );
		mui64AliveTimestamp = mtLastAliveTime.time * 1000 + mtLastAliveTime.millitm;
		++muiAliveCounter;
		*/
	}

	//ȡ������
	int GetAliveCounter()
	{
		int liRet = muiAliveCounter;
		muiAliveCounter = 0;
		return liRet;
	}

	int GetAliveCounter( int )
	{
		return muiAliveCounter;
	}

	struct timeb GetLastAliveTime() const
	{
		return mtLastAliveTime;
	}

	int64_t GetAliveTimestamp() const
	{
		return mui64AliveTimestamp;
	}

	//�������ƺͱ��
	void SetThreadName(char* apThreadName, int aiNum = 0)
	{
		threadIndex = aiNum;
		if (apThreadName)
		{
			sprintf((char*)macThreadName, "%d��%s", aiNum, apThreadName);
		}
	}

	//ȡ�߳�����
	char* GetThreadName(){return macThreadName;}

	//ȡ���ܲ���
	int GetPerformance()
	{
		int llTemp = mlPerformance;
		mlPerformance = 0;
		return llTemp;
	}

	//�����̵߳����ܲ���������ͳ�ƺ�ʱ����ִ�е�ʱ��
	void SetPerformance(int alPerformance)
	{
		if(mlPerformance<alPerformance)
		{
			mlPerformance = alPerformance;
		}
	}

	void SetStep( int n )
	{
		miStep = n;
	}

	int GetStep() const
	{
		return miStep;
	}
	int GetThreadIndex()
	{
		return threadIndex;
	}
private:
	unsigned int	muiAliveCounter;		// �̴߳�����
	int64_t           mui64AliveTimestamp;    // ���ʱ���
	struct timeb    mtLastAliveTime;        // ���һ�δ��ʱ��
	int			mlPerformance;			// �߳�����
	char			macThreadName[64+1];	// �߳�����
	int             miStep;
	int threadIndex;
};
class CThreadGroup;
struct STRU_THREAD_CONTEXT
{
public:
	void*			mpWorkContext;		//�����Ļ���
	CThreadGroup*	mpGroupManager;		//������
	CThreadStat		moThreadStat;		//ͳ��
	int				miPriority;			//�̵߳����ȼ�

#ifdef _WIN32
	HANDLE			mhHandle;			//�߳̾��
	unsigned int	muiThreadID;		//�߳�ID
#else
	timeb			moStartTime;		//����ʱ��
	pthread_t		muiThreadID;		//�߳�ID
#endif
};

//�߳���������
class CThreadGroup
{
public:
	//���졢����
	CThreadGroup(void);
	~CThreadGroup(void);

public:
	//��ʼ�̵߳�����
	unsigned int Start(ThreadFunc* apThreadFucn, void* apWorkContext, 
		unsigned int auiThreadNum, char* apThreadName = NULL, int aiPriority = 0);

	//�Ƿ�ֹͣ
	bool IsStop(){return mbStop;};
	//ֹͣ���߳�
	bool StopAll();

	//�͹����߷���
	bool Detach(STRU_THREAD_CONTEXT& apThread);
	//���������Ϣ
	void Dump();

	//���жϵĵȴ�
	bool Sleep(unsigned int ldwWaitTime);

	//���������߳�
	void WakeAll();

private:
	//�����߳�
	bool StartThread(STRU_THREAD_CONTEXT* apContext, ThreadFunc* apThreadFunc);
	//ֹͣ�߳�
	bool EndThread(STRU_THREAD_CONTEXT* apContext);
		
	//��ӡ�̵߳���Ϣ
	void PrintThreadInfo(STRU_THREAD_CONTEXT& aThreadContext);

#ifdef _WIN32 
	//������������߳�ʱ��
	void PrintThreadTime(char* apTime, FILETIME& aoFileTime);
#endif

private:
	//ֹͣ���
	bool						mbStop;
	//�߳���Ϣ�б�
	list<STRU_THREAD_CONTEXT*>	moThreadList;

	//�ȴ�ʹ�õľ��
	//���߳�Sleepʱ����Ҫ�˳�ʱ��ʹ�������Խ���Sleep״̬
	CEvent						moStopEvent;

	//�߳���Ϣ�ı���
	CCriticalSection			moAccessCS;
};
#endif //_THREAD_GROUP_H_
