#ifndef Kernel_h__
#define Kernel_h__

#include "RoomKernel.h"
#include "MpsKernel.h"
#include "NetSocket.h"
#include "NetSelect.h"
#include "base/CriticalSection.h"
#include "base/ThreadGroup.h"
#include "base/task/task_queue.h"

class CKernel: public IKernelService, public ISdkKernel
{
public:
	CKernel();

	~CKernel();
public:
	//�������
	virtual void AddTask(Task* pTask);

	//����CRS����
	virtual void SendRoomData(char* data, uint16_t wLen);

	//���ӷ���
	virtual void ConnectRoom(const char* aspszServerAddr, uint16_t awServerPort);

	//�رշ���
	virtual void CloseRoom();

	//����MPS����
	virtual void SendMpsData(char* data, uint16_t wLen);

	//����MPS
	virtual void ConnectMps(const char* aspszServerAddr, uint16_t awServerPort);

	//�ر�MPS����
	virtual void CloseMpsConnection();
public:
	//��ȡ������
	virtual unsigned int GetLastError();

	//����ӿ�
	virtual bool QueryInterface(uint32_t uID, void** ppVoid);

	//����IProcess�ӿ�
	virtual void SetProcess(ISdkProcess* pSdkProcess);

	/*********************************************************
	* ͬ������ 
	* SDK���ڲ���������Ҫ֪ͨ�ϲ�ʱ��������лص������������� 
	* ͬʱ����NewTaskEvent֪ͨ�ϲ㣬ת�����̵߳��ô˷���
	*   �������̵߳��ô˷���ʱ��SDKһ����ִ�����л���Ķ���
	*   �ﵽ�����лص�ִ���ڵ����̵߳�Ŀ��
	**********************************************************/
	virtual void SolveTask();

	//�����û���Ϣ
	virtual void SetUserInfo(int64_t ai64UserID, const char* apszNick, const char* apszPsw, uint16_t usPhotoNm);

	//����������Ϣ
	virtual void SetNetInfo(int32_t netType,const char* proxyIP, int32_t proxyPort,const char* proxyUser,const char* proxyPwd);

public:
	void OnErrorNotify(uint32_t fd);

	void OnConnectNotify(uint32_t fd);

	void OnRecvDataNotify(uint32_t fd, char *buffer, uint32_t length);

	unsigned int NetWork(STRU_THREAD_CONTEXT *aoContext);
private:
	CRoomKernel m_RoomKernel;
	CMpsKernel  m_MpsKernel;


	ISdkProcess* m_pSdkProcess;

	CNetSocket m_mpsFd;
	CNetSocket mpTcpSession;
	CNetPackCRS m_objCrsNetPack;
	CNetPackMPS m_objMpssNetPack;

	CNetSelect mNetSelect;
	CEvent mNetThreadEvent;
	CEvent mNetThreadExitEvent;
	bool mbNetThreadExit;
	TaskQueue m_TaskQueue;

	CThreadGroup thread_group;
	bool m_bNetThreadWait;

	int64_t mi64LastKeepLiveTime;
};
#endif // Kernel_h__