#ifndef InnerInterface_h__
#define InnerInterface_h__

#include "base/include.h"
#include "base/constdef.h"

struct STRU_USER_INFO
{
	int64_t m_i64UserID;
	uint16_t m_wPhotoNm;
	string m_strUserNick;
	string m_strUserPsw;
	string m_strPswMd5;
};

class Task;

class IKernelService
{
public:
	//���ô�����
	virtual void SetLastError(uint32_t iError){
		m_uiErrorCode = iError;}

	//��ȡ�û���Ϣ
	virtual STRU_USER_INFO& GetUserInfo(){return m_struUserInfo;}

	//�������
	virtual void AddTask(Task* pTask) = 0;

	//����CRS����
	virtual void SendRoomData(char* data, uint16_t wLen) = 0;

	//���ӷ���
	virtual void ConnectRoom(const char* aspszServerAddr, uint16_t awServerPort) = 0;

	//�رշ���
	virtual void CloseRoom() = 0;

	//����MPS����
	virtual void SendMpsData(char* data, uint16_t wLen) = 0;

	//����MPS
	virtual void ConnectMps(const char* aspszServerAddr, uint16_t awServerPort) = 0;

	//�ر�MPS����
	virtual void CloseMpsConnection() = 0;
protected:
	STRU_USER_INFO m_struUserInfo; 

	//������
	uint32_t m_uiErrorCode;
};

struct ISdkProcess;

class IRoomKernelService
{
public:
	IRoomKernelService(){
		m_pKernelService = 0;
	}

	void SetKernelService(IKernelService* pKernelService){m_pKernelService = pKernelService;}

	//���ô�����
	virtual void SetLastError(uint32_t iError){
		m_pKernelService->SetLastError(iError);
	}

	//��ȡ�û���Ϣ
	virtual const STRU_USER_INFO& GetUserInfo(){
			return m_pKernelService->GetUserInfo();
	}

	//��������
	virtual void SendData(char* data, uint16_t wLen){
			m_pKernelService->SendRoomData(data, wLen);
	}

	//���ӷ���
	virtual void ConnectRoom(int32_t alRoomId, const char* aspszServerAddr, uint16_t awServerPort) = 0;

	//�رշ���
	virtual void CloseRoom(int32_t alRoomId) = 0;

	//��ȡ��ǰ����ID
	virtual int GetCurrRoomID(){return m_lCurrRoomID;}

	//RSA����
	virtual void RSAEncrypt(char* inData, uint16_t inLen, char* outData/*allocate inner free outer*/, int32_t& outLen) = 0;

	//RSA����
	virtual void RSADecrypt(char* inData, uint16_t inLen, char* outData/*allocate inner free outer*/, int32_t& outLen) = 0;
protected:
	//��ǰ����ID
	int32_t m_lCurrRoomID;

	IKernelService* m_pKernelService;
};

class IRoomKernel
{
public:
	IRoomKernel(){m_pRoomKernelService = NULL;}

	void SetRoomKernelService(IRoomKernelService* pRoomKernelService){m_pRoomKernelService = pRoomKernelService;}

	template <class T>
	void AutoSendPack(T& t)
	{
		char lszPack[WHOLE_PACK_DATA_LEN];
		uint16_t lwDataLen = t.Pack(lszPack, WHOLE_PACK_DATA_LEN);
		if(lwDataLen > 0 && m_pRoomKernelService)
		{
			m_pRoomKernelService->SendData(lszPack, lwDataLen);
		}
	}

	template <class T>
	void AutoSendRSAEncryptPack(T& t)
	{
		char lszPack[WHOLE_PACK_DATA_LEN];
		uint16_t lwDataLen = t.Pack(lszPack, WHOLE_PACK_DATA_LEN);
		if(lwDataLen > 0 && m_pRoomKernelService)
		{
			char* outData = NULL;
			int32_t outLen;
			m_pRoomKernelService->RSAEncrypt(lszPack, lwDataLen, outData, outLen);
			if(outLen > 0)
				m_pRoomKernelService->SendData(outData, outLen);

			delete [] outData;
		}
	}
protected:
	IRoomKernelService* m_pRoomKernelService;
};

#endif // InnerInterface_h__