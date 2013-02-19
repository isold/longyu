#ifndef BaseKernel_h__
#define BaseKernel_h__

#include "InnerInterface.h"
#include "include/SdkKernelInterface.h"
#include "base/pack/crs_cl_strudef.h"

class CBaseKernel: public IRoomKernel, public IBaseKernel
{
public:
	CBaseKernel(){
		m_bHaveVideo = false;
	}
private:
	//��ʼ��                   �ͻ��˰汾��      �Ƿ�������ͷ       ��¼��Դ�ͻ��˱�ʶ
	virtual void  Initialize(char* apszVersion, bool abHaveVideo, uint8_t abyLoginSource);

	//��¼����
	virtual void  LoginRoom(int32_t alRoomId, const char* aspszServerAddr, uint16_t awServerPort, const char* pszRoomPsw, const char* pszMachineCode );

	//�˳�����
	virtual void  LogOut(int32_t alRoomId);	

	//�׻�
	virtual void  SendFlower(int64_t ai64SendTo, uint8_t abyFlowerIndex); 

	//����������Ϣ
	virtual void  SendChat(uint8_t byChatType, int64_t ai64SendTo, char* apszMood, char* apszContrl, char* apszContent);
	
	//����
	virtual void  ChangeHermitState(bool bHermit);  

	//�����û�
	virtual void  ManageUser(int64_t ai64UserID, uint8_t byType, int32_t otherParam, char* strText);

	//�����û������� �޹���Ա
	virtual void  GetBlackList();	

	//����IP������  �޹���Ա
	virtual void  GetBlackIPList();	

	//���ķ���״̬����
	/*
	#define DEF_ALLOW_FLOWER				0//�����׻�
	#define DEF_ALLOW_PUBCHAT				1//������
	*/
	virtual void  ModifyRoomStateRQ(uint16_t wProperty, bool abValue);

	//����㲥 �޹���Ա
	virtual void  SendBroadCast(char* astrText);

	//�޸ķ������� ���������롢���⡢��ӭ��
	virtual void  ModifyRoomProperty(bool bLocked, char* strPSW, char* strTopic, char* strSalutatory);	

	//�û�һ����Ϣ ������͸��ת��
	/*
	const uint16_t REFUSE_PRIVATE 		= 0x1006;		//�ܾ�����˽����Ϣ
	const uint16_t REFUSE_CHAT			= 0x1007;		//�ܾ��κ�������Ϣ
	const uint16_t REFUSE_PUBLIC		= 0x100D;		//���ι�����ʾ�Է�
	const uint16_t REFUSE_PRICHAT		= 0x1010;		//�ܾ�����
	*/
	virtual void  SendGeneralInfo(int64_t ai64UserID, uint16_t wType);

	//�����û���Ϣ
	virtual void  ModifyUserInfo(PRKN_STRU_MD_USER_INFO_ITEM apItemList, uint8_t abyItemCount);
public:
	void LoginRoom();

private:
	string m_strPsw;

	string m_strVersion;

	bool m_bHaveVideo;

	uint8_t m_byLoginSource;
    
    string m_strMachineCode;
};
#endif // BaseKernel_h__