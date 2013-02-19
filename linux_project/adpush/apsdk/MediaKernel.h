#ifndef MediaKernel_h__
#define MediaKernel_h__

#include "InnerInterface.h"
#include "include/SdkKernelInterface.h"
#include "base/pack/crs_cl_strudef.h"

class CMediaKernel: public IRoomKernel, public IMediaKernel
{
private:
	//����
	virtual void  ApplyMic();	

	//���������
	/*
	#define DEF_MIC_MGR_TYPE_LOOT		1//����
	#define DEF_MIC_MGR_TYPE_GET		2//����
	#define DEF_MIC_MGR_TYPE_SET		3//����
	#define DEF_MIC_MGR_TYPE_PREPARE	4//׼������
	*/
	virtual void  ManageMic(int64_t ai64UserID, uint8_t byType, uint8_t byIndex);

	//��ĳ�˲嵽ָ������λ��
	virtual void  InsertMic(int64_t ai64UserID, uint8_t byIndex);

	//ֹͣ����
	virtual void  StopSpeak();

	//�޸���ʱ��
	virtual void  ChangeMicTime(uint8_t byIndex, uint8_t byTime);

	//����Ա����������
	/*
	#define DEF_ADMINCTRL_MIC_SWITCH		1//�󿪹��л�
	#define DEF_ADMINCTRL_VIDEO_SWITCH		2//��Ƶ���л�
	#define DEF_ADMINCTRL_MGR_SWITCH		3//�������л�
	*/
	virtual void  ManageMicState(uint8_t byType, uint8_t byIndex, bool abValue);

	//�û������������
	/*
	#define DEF_AUDIO_OPERATOR				0		//��Ƶ����
	#define DEF_VIDEO_OPERATOR				1		//��Ƶ����
	*/
	virtual void  ChangeRecvState(uint8_t byType, uint8_t byIndex, bool abState);	

	//�û�״̬���� ��¼����¼��ǰ���ò鿴Ŀ���û��Ƿ�����ò���
	virtual void  UserStateRQ(int64_t ai64Dest);

	//�û�״̬�������
	/*
	#define DEF_SEND_AUDIO					1//��������
	#define DEF_RECV_AUDIO					2//��������
	#define DEF_SEND_VIDEO					3//������Ƶ
	#define DEF_ALLOW_RECORD_AUDIO			5//����¼��
	#define DEF_ALLOW_RECORD_VIDEO			6//����¼��
	*/
	virtual void  UserChangeState(uint16_t wType, uint8_t byValue);	

	//��������Ϣ  ������ʱ���ͱ���������Ƶ������Ϣ
	virtual void  SendSpeakerInfo(PRKN_STRU_SPEAKER_INFO apSpeakerInfo); 

	//��������
	virtual void  VoiceChatRQ(int64_t ai64UserID);	

	//ͬ�����Ӧ��  ��ͬ��ʱ���÷���
	virtual void  VoiceChatRS(int64_t ai64UserID);	

	//ֹͣ����
	virtual void  StopVoiceChat(int64_t ai64UserID);

	//���AVS֪ͨ
	virtual void  ChangeAvsNodify(uint32_t aulAvsIP, uint16_t awAvsPort);
};
#endif // MediaKernel_h__