#ifndef MpsKernel_h__
#define MpsKernel_h__

#include "InnerInterface.h"
#include "include/SdkKernelInterface.h"
#include "base/pack/mps_cl_strudef.h"

class CMpsKernel:public IMpsKernel
{
public:
	CMpsKernel();

	~CMpsKernel();

	void SetKernelService(IKernelService* pKernelService){m_pKernelService = pKernelService;}

	//����IProcess�ӿ�
	void SetProcess(ISdkProcess* pSdkProcess);

	//����ӿ�
	bool QueryInterface(uint32_t uID, void** ppVoid);

	//����ʧ��
	void OnConnectError();

	//���ӳɹ�
	void OnConnected();

	//��������
	void SolveMsg(char * apPackData, uint16_t awPackDataLen); 

	//�����
	void DealPack(char* pDate, uint16_t wDataLen);
public:
	virtual void ConnectMps(char* szAddr, uint16_t usPort);

	virtual void CloseMpsConnection();
    
    virtual void SetServerID ( uint16_t = DEF_PROPSMPS_SRVID );

private:
	void SendLoginRQ();

	void MakeMPSAttr(int32_t lRedTime, char *byPrivateAttr, uint32_t &uCommAttr);

	void DealLoginRS(STRU_CL_TCP_MPS_PKG_LOGIN_ACK* pStru);
private:
	IKernelService* m_pKernelService;
	IMpsProcess* m_pMpsProcess;
	string m_strAddr;
	uint16_t m_ui16Port;
    uint16_t m_ui16SvrID;
};
#endif // MpsKernel_h__