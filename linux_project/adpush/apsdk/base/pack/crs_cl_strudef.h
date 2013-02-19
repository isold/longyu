#ifndef _CRS_CL_STRUDEF_H_
#define _CRS_CL_STRUDEF_H_

#include "../include.h"
#include "../constdef.h"
#include "MediaInfo.h"

#define VERSION_LEN					10		//�汾��Ϣ		
#define MAX_USER_ID_NUM				20		///�û�������ϸ��Ϣ��ID �б�������
//*************************************************************************************************//
//***************************  ���¶������������GAS������������ʹ��  *****************************//
//*************************************************************************************************//
#define CRS_PACK_BASE						5300

#define UC_CL_CRS_DATA_HEAD							CRS_PACK_BASE+26	//���������ݰ�ͷ

#define UC_CL_CRS_UDPFIRSTLOGIN_RQ                  CRS_PACK_BASE+300		
#define UC_CL_CRS_UDPFIRSTLOGIN_RS                  CRS_PACK_BASE+301
#define UC_CL_CRS_LOGIN_INFO_RQ                     CRS_PACK_BASE+302
#define UC_CL_CRS_ALIVE_RQ                          CRS_PACK_BASE+303
#define UC_CL_CRS_ALIVE_RS                          CRS_PACK_BASE+304
#define UC_CL_CRS_LOGOUT                            CRS_PACK_BASE+305
#define UC_CL_CRS_LOGIN_INFO_RS                     CRS_PACK_BASE+306
#define UC_CL_CRS_LOGOUT_RS							CRS_PACK_BASE+307	//������Ҫ���˳�


/****************************  ��߰汾�����ͼ�����**************************
//��¼
#define UC_CL_CRS_LOGIN_HALL_RQ_2007					CRS_PACK_BASE+72    //��¼����� CL->CRS
#define UC_CL_CRS_LOGIN_HALL_RS_2007					CRS_PACK_BASE+126   //���˵�¼Ӧ��� CRS->CL

//�������� ��ͨ�û�
#define UC_CL_CRS_HOST_INFO_ID600						CRS_PACK_BASE+124 	//�����ַ֪ͨ�� CRS->CL
#define UC_CL_CRS_CHATROOM_TOPIC_ID						CRS_PACK_BASE+79	//���⻶ӭ��֪ͨ�� CRS->CL
#define UC_CL_CRS_CHATROOM_PROPERTY_ID					CRS_PACK_BASE+78   	//���Ըı�֪ͨ�� CRS->CL
//�������� ����Ա
#define UC_CL_CRS_HALL_STAT_CHG_ID						CRS_PACK_BASE+110	//��������������(�׻�������)���� CL<->CRS	
#define UC_CL_CRS_CHATROOM_PROPERTY_CHG_RQ				CRS_PACK_BASE+77	//�����������޸�(������)����� CL->CRS

//������Ƶ ��ͨ�û�
#define UC_CL_CRS_MIC_INFO_LIST_ID						CRS_PACK_BASE+113   //��״̬��Ϣ�б�֪ͨ CRS->CL
#define UC_CL_CRS_SPEAKER_INFO_LIST_ID					CRS_PACK_BASE+115   //������Ϣ�б� CRS<->CL
#define UC_CL_CRS_CHATROOM_MICROPHONE_ORDER_ID			CRS_PACK_BASE+48    //����֪ͨ�� CRS->CL
#define UC_CL_CRS_CHATROOM_MANAGER_TIMELIMIT_CHG_ID		CRS_PACK_BASE+54	//����ʱ������֪ͨ�� CRS->CL
#define UC_CL_CRS_CHATROOM_MANAGER_MICROPHONE_ID		CRS_PACK_BASE+52	//�������֪ͨ��CRS->CL
#define UC_CL_CRS_BEGIN_SPEAK_ID						CRS_PACK_BASE+114   //��ʼ����֪ͨ CRS->CL
#define UC_CL_CRS_CHATROOM_STOP_SPEAK_RQ				CRS_PACK_BASE+47    //�û�ֹͣ����֪ͨ�� CL->CRS
#define UC_CL_CRS_CHATROOM_MANAGER_PUT_MICROPHONE_ID	CRS_PACK_BASE+49	//����֪ͨ�� CRS->CL
#define UC_CL_CRS_MICROPHONE_MANAGER_RS					CRS_PACK_BASE+119	//����Ա�����������㲥 CRS->CL
#define UC_CL_CRS_USER_RECV_STATE_CHG_ID				CRS_PACK_BASE+121	//�û��򿪹رվ�����CL->CRS 
#define UC_CL_CRS_CHATROOM_APPLY_MICROPHONE_RQ			CRS_PACK_BASE+40	//��������� CL->CRS
#define UC_CL_CRS_CHATROOM_APPLY_MICROPHONE_RS			CRS_PACK_BASE+41	//����Ӧ��� CRS->CL
//������Ƶ ��ͨ�û� ��������
#define UC_CL_CRS_VOICE_CHAT_RQ							CRS_PACK_BASE+30	//������������� CL<->CRS
#define UC_CL_CRS_VOICE_CHAT_RS							CRS_PACK_BASE+31	//��������Ӧ��� CRS->CL
#define UC_CL_CRS_VOICE_CHAT_SERVER_RS					CRS_PACK_BASE+32	//��������������Ӧ��� ֪ͨAB��ʼ��������CRS->CL
#define UC_CL_CRS_VOICE_CHAT_STOP_ID					CRS_PACK_BASE+33	//��������ֹ֪ͣͨ CRS<->CL
//������Ƶ ����Ա
#define UC_CL_CRS_CHATROOM_MANAGER_GET_MICROPHONE_RQ	CRS_PACK_BASE+42	//��������� CL->CRS
#define UC_CL_CRS_CHATROOM_MANAGER_PUT_MICROPHONE_RQ	CRS_PACK_BASE+43	//��������� CL->CRS
#define UC_CL_CRS_CHATROOM_MANAGER_MICROPHONE_RQ		CRS_PACK_BASE+50	//�����ȡ����˷��������� CL->CRS
#define UC_CL_CRS_CHATROOM_MANAGER_MICROPHONE_RS		CRS_PACK_BASE+51	//�����ȡ����˷����Ӧ��� CRS->CL
#define UC_CL_CRS_CHATROOM_MANAGER_TIMELIMIT_CHG_RQ		CRS_PACK_BASE+53	//�޸������ҷ���ʱ����������� CL->CRS
#define UC_CL_CRS_CHATROOM_MANAGER_INSERTINTO_MICROPHONE_RQ		CRS_PACK_BASE+55	//��ָ��λ�ò����� CL->CRS
#define UC_CL_CRS_MICROPHONE_MANAGER_RQ					CRS_PACK_BASE+118			//����Ա��������� CL->CRS
//������Ƶ ����Ա���ͣ������˽���
#define UC_CL_CRS_MIC_STATE_CONTROL_ID					CRS_PACK_BASE+120			//����\�رշ�����Ƶ\������\����Ÿ�CL<->CRS

//�û����� ��ͨ�û�
#define UC_CL_CRS_USER_BE_OPERATED_ID					CRS_PACK_BASE+70   	//�û�������֪ͨ�� CRS->CL
#define UC_CL_CRS_USER_POWER_CHG_ID						CRS_PACK_BASE+71	//�û�����仯֪ͨ�� CRS->CL
#define UC_CL_CRS_VOICE_STATE_CHG_ID					CRS_PACK_BASE+74	//�û���״̬�仯֪ͨ(����\���ĵ�) CRS->CL
#define UC_CL_CRS_USER_INFO_ID_2007						CRS_PACK_BASE+128	//�û��б�֪ͨ��   CRS->CL
#define UC_CL_CRS_ENTRY_OTHERUSER_ID_400				CRS_PACK_BASE+81	//�û�����֪ͨ  CRS->CL
#define UC_CL_CRS_LEAVE_OTHERUSER_ID_350				CRS_PACK_BASE+82	//�û��뿪֪ͨ CRS->CL
#define UC_CL_CRS_DATA_ID_350							CRS_PACK_BASE+83	//������Ϣ�� CRS<->CL
#define UC_CL_CRS_GENERAL_PACK_350						CRS_PACK_BASE+84	//�����ҿ�����Ϣ����͸��ת���� CRS<->CL
#define UC_CL_CRS_FLOWERS_ID							CRS_PACK_BASE+108   //�û��׻���CRS<->CL
//�û����� �û�״̬����� �û�״̬Ӧ���һ���������������û��Ƿ�����¼��¼���
#define UC_CL_CRS_USER_STATE_RQ							CRS_PACK_BASE+111	//�û�״̬�����	CL->CRS
#define UC_CL_CRS_USER_STATE_RS							RS_PACK_BASE+112	//�û�״̬Ӧ���	CRS->CL
//�û����� ���� ��Ƶ���ƣ����Ƿ������ʻ����Ƿ�����¼��
#define UC_CL_CRS_USER_STATE_CHG_ID_390					CRS_PACK_BASE+103	//�û�״̬�ı�֪ͨ CL<->CRS
//�û����� ��Ŀ��
#define UC_CL_CRS_PLAYBILL_RQ							CRS_PACK_BASE+90	//��Ŀ�������		CL->CRS
#define UC_CL_CRS_PLAYBILL_ID							CRS_PACK_BASE+91	//��Ŀ��֪ͨ��		CRS->CL
#define UC_CL_CRS_PLAYBILL_CHANGED_ID					CRS_PACK_BASE+92	//��Ŀ���仯֪ͨ�� CRS->CL 
//�û����� ����Ա
#define UC_CL_CRS_CHATROOM_BROADCAST_RQ     			CRS_PACK_BASE+60	//����Ա����ϵͳ�㲥 CRS<->CL
#define UC_CL_CRS_MANAGER_OPERATION_ON_USER_RQ			CRS_PACK_BASE+61	//����Ա���û����в�������� CL->CRS
#define UC_CL_CRS_MANAGER_OPERATION_ON_USER_RS			CRS_PACK_BASE+62	//����Ա���û����в���Ӧ��� CRS->CL
#define UC_CL_CRS_CHATROOM_USER_STATE_CHG_ID			CRS_PACK_BASE+63	//����Ա״̬�ı�֪ͨ����������CRS<->CL
#define UC_CL_CRS_BLACK_QUERY_RQ						CRS_PACK_BASE+85	//��ʱ����������� CL->CRS
#define UC_CL_CRS_TIME_BLACK_LIST						CRS_PACK_BASE+86	//��ʱ�������б�� CRS->CL
#define UC_CL_CRS_BLACKIP_LIST_RQ  						CRS_PACK_BASE+87	//IP����������� CL->CRS
#define UC_CL_CRS_BLACKIP_LIST_RS  						CRS_PACK_BASE+88	//IP�������б�� CRS->CL

******************************************************************************/
//************************************************//
//*****  ����������ͨѶ�� ****************************//
//************************************************//
//ChatRoom Server = CRS

#define UC_CL_CRS_LOGIN_RQ					CRS_PACK_BASE+1		//(ͣ��)�����ҵ�¼�����
#define UC_CL_CRS_LOGIN_RS					CRS_PACK_BASE+2		//(ͣ��)�����ҵ�¼Ӧ���

#define UC_CL_CRS_USER_INFO_ID				CRS_PACK_BASE+3		//(ͣ��)�������û���Ϣ

#define UC_CL_CRS_ENTRY_OTHERUSER_ID		CRS_PACK_BASE+5		//(ͣ��)�����������û�����֪ͨ
#define UC_CL_CRS_LEAVE_OTHERUSER_ID		CRS_PACK_BASE+6		//(ͣ��)�����������û��뿪֪ͨ

#define UC_CL_CRS_MANAGER_OPERATION_RQ      CRS_PACK_BASE+20	//��������Ȩ������������
#define UC_CL_CRS_MANAGER_OPERATION_RS      CRS_PACK_BASE+21    //����Ա����Ӧ���

#define UC_CL_CRS_DATA_ID					CRS_PACK_BASE+23	//(ͣ��)���������ݰ�
#define UC_CL_CRS_SYS_INFO_ID		        CRS_PACK_BASE+24	//������ϵͳ��Ϣ��
#define UC_CL_CRS_GENERAL_PACK		        CRS_PACK_BASE+25	//(ͣ��)������һ����Ϣ��

#define UC_CL_CRS_DATA_HEAD					CRS_PACK_BASE+26	//���������ݰ�ͷ

#define UC_COM_GAS_VISITOR_INFO_RQ			CRS_PACK_BASE+35	//�ο���Ϣ�����
#define UC_COM_GAS_VISITOR_INFO_RS			CRS_PACK_BASE+36	//�ο���ϢӦ���

#define UC_COM_GAS_APPLY_WEBKEY_RQ			CRS_PACK_BASE+37	//��Կ�����
#define UC_COM_GAS_APPLY_WEBKEY_RS			CRS_PACK_BASE+38	//��ԿӦ���
//�������İ�(��ʼ����Ӧ���ֹͣ)
//***********************************************************//
//*****  �������İ�(��ʼ����Ӧ���ֹͣ)********************//
//***********************************************************//
#define UC_CL_CRS_VOICE_CHAT_RQ								CRS_PACK_BASE+30	//�������������
#define UC_CL_CRS_VOICE_CHAT_RS								CRS_PACK_BASE+31	//��������Ӧ���
#define UC_CL_CRS_VOICE_CHAT_SERVER_RS						CRS_PACK_BASE+32	//��������������Ӧ���
#define UC_CL_CRS_VOICE_CHAT_STOP_ID						CRS_PACK_BASE+33	//��������ֹ֪ͣͨ

//���������Ҷ���˷�����(Ҫ�󡢸�ʱ�������󡢸�����Ӻ�ֹ֪ͣͨ)
#define UC_CL_CRS_CHATROOM_APPLY_MICROPHONE_RQ				CRS_PACK_BASE+40	//Ҫ�������
#define UC_CL_CRS_CHATROOM_APPLY_MICROPHONE_RS				CRS_PACK_BASE+41	//Ҫ��Ӧ���
#define UC_CL_CRS_CHATROOM_MANAGER_GET_MICROPHONE_RQ		CRS_PACK_BASE+42	//���������
#define UC_CL_CRS_CHATROOM_MANAGER_PUT_MICROPHONE_RQ		CRS_PACK_BASE+43	//���������
#define UC_CL_CRS_CHATROOM_MANAGER_INSERT_MICROPHONE_RQ		CRS_PACK_BASE+44	//��ӵ����Զ��������
#define UC_CL_CRS_CHATROOM_MICROPHONE_TIMELIMIT_CNG_RQ		CRS_PACK_BASE+45	//�ı䷢��ʱ�������
#define UC_CL_CRS_CHATROOM_MICROPHONE_TIMELIMIT_CNG_ID		CRS_PACK_BASE+46	//�ı䷢��ʱ��֪ͨ��
#define UC_CL_CRS_CHATROOM_STOP_SPEAK_RQ					CRS_PACK_BASE+47	//�û�ֹͣ����֪ͨ��
#define UC_CL_CRS_CHATROOM_MICROPHONE_ORDER_ID				CRS_PACK_BASE+48	//GAS���͵�������
#define UC_SINASHOW_MICROPHONE_ORDER_ID						CRS_PACK_BASE+135	//SinaShow��������������֪ͨ��
#define UC_CL_CRS_CHATROOM_MANAGER_PUT_MICROPHONE_ID		CRS_PACK_BASE+49	//����֪ͨ��

//����Ա����˷�����(��������Ӧ��֪ͨ��������֪ͨ��Ҫ��֪ͨ)
#define UC_CL_CRS_CHATROOM_MANAGER_MICROPHONE_RQ			CRS_PACK_BASE+50	//�����ȡ����˷���������
#define UC_CL_CRS_CHATROOM_MANAGER_MICROPHONE_RS			CRS_PACK_BASE+51	//�����ȡ����˷����Ӧ���
#define UC_CL_CRS_CHATROOM_MANAGER_MICROPHONE_ID			CRS_PACK_BASE+52	//�����ȡ����˷����֪ͨ��
#define UC_CL_CRS_CHATROOM_MANAGER_TIMELIMIT_CHG_RQ			CRS_PACK_BASE+53	//�޸������ҷ���ʱ�����������
#define UC_CL_CRS_CHATROOM_MANAGER_TIMELIMIT_CHG_ID			CRS_PACK_BASE+54	//�޸������ҷ���ʱ������֪ͨ��

//����Ա���й����(�㲥�������û�����Ӧ��״̬�ı�֪ͨ)
#define UC_CL_CRS_CHATROOM_BROADCAST_RQ     				CRS_PACK_BASE+60	//����Ա����ϵͳ�㲥
//#define UC_CL_CRS_MANAGER_OPERATION_ON_USER_RQ				CRS_PACK_BASE+61	//�����û�����
#define UC_CL_CRS_MANAGER_OPERATION_ON_USER_RS				CRS_PACK_BASE+62	//�����û�Ӧ��
#define UC_CL_CRS_CHATROOM_USER_STATE_CHG_ID				CRS_PACK_BASE+63	//����Ա״̬�ı�֪ͨ��

//���������û�ͨѶ��(������֪ͨ������仯֪ͨ����¼���󡢵�¼Ӧ��״̬�仯֪ͨ)
#define UC_CL_CRS_USER_BE_OPERATED_ID						CRS_PACK_BASE+70	//�û�������֪ͨ
#define UC_CL_CRS_USER_POWER_CHG_ID							CRS_PACK_BASE+71	//����仯֪ͨ
#define UC_CL_CRS_LOGIN_HALL_RQ_2007						CRS_PACK_BASE+72	//2007������¼����
#define UC_CL_CRS_LOGIN_HALL_RS_350							CRS_PACK_BASE+73	//(ͣ��)������¼Ӧ��
#define UC_CL_CRS_VOICE_STATE_CHG_ID						CRS_PACK_BASE+74	//״̬�仯֪ͨ
#define UC_CL_CRS_LOGIN_HALL_RQ_380							CRS_PACK_BASE+75	//(ͣ��)������¼����(380)

//����������֪ͨ��(�����޸������������֪ͨ��������֪ͨ��)
#define UC_CL_CRS_CHATROOM_PROPERTY_CHG_RQ					CRS_PACK_BASE+77	//�����޸������
#define UC_CL_CRS_CHATROOM_PROPERTY_ID						CRS_PACK_BASE+78	//����֪ͨ��
#define UC_CL_CRS_CHATROOM_TOPIC_ID							CRS_PACK_BASE+79	//����֪ͨ��

#define UC_CL_CRS_USER_INFO_ID_350							CRS_PACK_BASE+80	//(ͣ��)�������û���Ϣ
#define UC_CL_CRS_ENTRY_OTHERUSER_ID_400					CRS_PACK_BASE+81	//�û�����֪ͨ
#define UC_CL_CRS_LEAVE_OTHERUSER_ID_350					CRS_PACK_BASE+82	//�û��뿪֪ͨ
#define UC_CL_CRS_DATA_ID_350								CRS_PACK_BASE+83	//������Ϣ��
#define UC_CL_CRS_GENERAL_PACK_350							CRS_PACK_BASE+84	//�����ҿ�����Ϣ��
#define UC_CL_CRS_BLACK_QUERY_RQ							CRS_PACK_BASE+85	//��ѯ��ʱ�����������
#define UC_CL_CRS_TIME_BLACK_LIST							CRS_PACK_BASE+86	//��ʱ�������б��

#define UC_CL_CRS_BLACKIP_LIST_RQ  							CRS_PACK_BASE+87	//��ѯIP�����������
#define UC_CL_CRS_BLACKIP_LIST_RS  							CRS_PACK_BASE+88	//IP�������б��

#define UC_CL_CRS_PLAYBILL_RQ								CRS_PACK_BASE+90	//��ѯ��Ŀ�������
#define UC_CL_CRS_PLAYBILL_ID								CRS_PACK_BASE+91	//��Ŀ��֪ͨ��
#define UC_CL_CRS_PLAYBILL_CHANGED_ID					    CRS_PACK_BASE+92	//��Ŀ���仯֪ͨ��
#define UC_CL_CRS_VISITOR_INFO_ID							CRS_PACK_BASE+93	//�ο�ID�Ŷ�֪ͨ��

#define UC_CL_CRS_LOGIN_HALL_RQ_390							CRS_PACK_BASE+100	//(ͣ��)��¼���󣨰汾390��
#define UC_CL_CRS_LOGIN_HALL_RS_390							CRS_PACK_BASE+101	//(ͣ��)��¼Ӧ�𣨰汾390��
#define UC_CL_CRS_HOST_INFO_ID							    CRS_PACK_BASE+102	//��ҳ��ַ֪ͨ��
#define UC_CL_CRS_USER_STATE_CHG_ID_390						CRS_PACK_BASE+103	//�û�״̬�ı�֪ͨ��390��
#define UC_CL_CRS_USER_INFO_ID_390							CRS_PACK_BASE+104	//(ͣ��)�������û���Ϣ��390��
#define UC_CL_CRS_LOGIN_HALL_RQ_391							CRS_PACK_BASE+105	//(ͣ��)��¼���󣨰汾391��

//400�����ӵİ�����
#define UC_CL_CRS_USER_INFO_ID_400							CRS_PACK_BASE+106	//�������û���Ϣ(400)
#define UC_CL_CRS_LOGIN_HALL_RQ_400							CRS_PACK_BASE+107	//(ͣ��)��¼���󣨰汾400��
#define UC_CL_CRS_FLOWERS_ID								CRS_PACK_BASE+108	//Flowers
#define UC_CL_CRS_LOGIN_HALL_RS_400							CRS_PACK_BASE+109	//(ͣ��)��¼Ӧ�𣨰汾400��
#define UC_CL_CRS_HALL_STAT_CHG_ID							CRS_PACK_BASE+110	//����������״̬

#define UC_CL_CRS_USER_STATE_RQ							CRS_PACK_BASE+111	//��¼Ӧ�𣨰汾400��
#define UC_CL_CRS_USER_STATE_RS							CRS_PACK_BASE+112	//����������״̬

//500�¶�������ݰ� **********************
#define UC_CL_CRS_MIC_INFO_LIST_ID							CRS_PACK_BASE+113	//��״̬��Ϣ�б�
#define UC_CL_CRS_BEGIN_SPEAK_ID							CRS_PACK_BASE+114	//��ʼ����֪ͨ
#define UC_CL_CRS_SPEAKER_INFO_LIST_ID						CRS_PACK_BASE+115	//������Ϣ�б�
#define UC_CL_CRS_LOGIN_HALL_RQ_500							CRS_PACK_BASE+116	//�µĵ�¼��
#define UC_CL_CRS_LOGIN_HALL_RS_500							CRS_PACK_BASE+117	//
#define UC_CL_CRS_MICROPHONE_MANAGER_RQ						CRS_PACK_BASE+118	//����Ա���������
#define UC_CL_CRS_MICROPHONE_MANAGER_RS						CRS_PACK_BASE+119	//����Ӧ���
#define UC_CL_CRS_MIC_STATE_CONTROL_ID						CRS_PACK_BASE+120	//��״̬��Ϣ�б�
#define UC_CL_CRS_USER_RECV_STATE_CHG_ID					CRS_PACK_BASE+121	//�û��ı����״̬

//510�¶�������ݰ�
#define UC_CL_CRS_CHATROOM_MANAGER_INSERTINTO_MICROPHONE_RQ		CRS_PACK_BASE+55	//��ָ��λ�ò�����

//600�¶�������ݰ�
#define UC_CL_CRS_LOGIN_HALL_RQ_600						    CRS_PACK_BASE+122	//600�ĵ�¼�����
#define UC_CL_CRS_LOGIN_HALL_RS_600						    CRS_PACK_BASE+123	//600�ĵ�¼Ӧ���
#define UC_CL_CRS_HOST_INFO_ID600							CRS_PACK_BASE+124	//��ҳ��ַ֪ͨ��(�汾600)

//700�¶�������ݰ�
#define UC_CL_CRS_LOGIN_HALL_RQ_700						    CRS_PACK_BASE+125	//700�ĵ�¼�����
#define UC_CL_CRS_LOGIN_HALL_RS_2007						CRS_PACK_BASE+126	//700�ĵ�¼Ӧ���

#define UC_CL_CRS_USER_INFO_ID_2007							CRS_PACK_BASE+128	//�������û���Ϣ(2007)

//add by qufeng 2008-06-12
#define UC_CL_CRS_NEW_OFFER_BROW_ID                         CRS_PACK_BASE + 129 //����������  
#define UC_CL_CRS_USER_INFO_RS								CRS_PACK_BASE+130   //�û������Լ���ϸ��Ϣ
#define UC_CL_CRS_USER_INFO_RQ                              CRS_PACK_BASE+131   //�û���������û���ϸ��Ϣ

//Show�¼�			
#define UC_CL_CRS_USER_INFO_ID_SINASHOW_2008				CRS_PACK_BASE+137	//�û��б�
#define UC_CL_CRS_ENTRY_OTHERUSER_ID_SINASHOW_2008			CRS_PACK_BASE+136	//�û�����֪ͨ
//////////////////////////////////////////////////////////////////////////


#define UC_CL_CRS_USE_PROP_RQ								CRS_PACK_BASE+200	//ʹ�õ�������
#define UC_CL_CRS_USE_PROP_RS								CRS_PACK_BASE+201	//ʹ�õ���Ӧ��
#define UC_CL_CRS_USE_PROP_ID								CRS_PACK_BASE+202	//ʹ�õ���֪ͨ
#define UC_CL_CRS_USE_PROP_FAILED_ID						CRS_PACK_BASE+203	//ʹ�õ���ʧ��֪ͨ
#define UC_CRS_CL_PROP_CHECK_RQ								CRS_PACK_BASE+205	//����ʹ����֤����
#define UC_CRS_CL_PROP_CHECK_RS								CRS_PACK_BASE+206	//����ʹ����֤Ӧ��
//////////////////////////////////////////////////////////////////////////
#define UC_COM_RAS_APPLY_KEY_RQ								CRS_PACK_BASE+207	//��Կ�����
#define UC_COM_RAS_APPLY_KEY_RS								CRS_PACK_BASE+208	//��ԿӦ���

#define UC_ENDECRYPT_FUN									CRS_PACK_BASE+209	//���ܰ�

#define UC_CRS_CL_GET_MIC_PROP_CHECK_RQ						CRS_PACK_BASE+210	//����ͬʱ�ύ��ǰװ���б�
#define UC_CRS_CL_GET_MIC_PROP_CHECK_RS						CRS_PACK_BASE+211	//����ʱ�ύװ���б�Ľ��

#define UC_CL_CRS_INSERT_MIC_ID								CRS_PACK_BASE+212	//����֪ͨ

#define UC_CL_CRS_PROP_QUICK_BUY_RQ							CRS_PACK_BASE+213	//���ٹ����������
#define UC_CL_CRS_PROP_QUICK_BUY_RS							CRS_PACK_BASE+214	//���ٹ������Ӧ��
#define UC_CL_CRS_DO_USE_PROP_ID							CRS_PACK_BASE+215	//��Ⱦ�����
#define UC_CL_CRS_LOGIN_HALL_RS_2009						CRS_PACK_BASE+216	//2009�ĵ�¼Ӧ���

#define UC_CL_CRS_TD_CALL_RQ_2009							CRS_PACK_BASE+217	//���������
#define UC_CL_CRS_TD_CALL_RS_2009							CRS_PACK_BASE+218	//����Ӧ���


#define UC_CL_CRS_ENTRY_OTHERUSER_ID_2009 					CRS_PACK_BASE+219	//���뷿��֪ͨ**1.3����
#define UC_CL_CRS_USER_INFO_ID_2009							CRS_PACK_BASE+220	//�������û���Ϣ(2009)**1.3����

//#define UC_CL_CRS_ENTRY_OTHERUSER_ID_2009_2					CRS_PACK_BASE+221	//���뷿��֪ͨ**1.3�������ѷϳ�
//#define UC_CL_CRS_USER_INFO_ID_2009_2						CRS_PACK_BASE+222	//�������û���Ϣ(2009)**1.3�������ѷϳ�

#define UC_CL_CRS_ACTION_ID                                 CRS_PACK_BASE + 221  //���Ϣ֪ͨ�� cl<->crs
#define UC_CL_CRS_USER_ATTR_EX						        CRS_PACK_BASE+222	 //��չ���԰�(2009)**1.3����

#define UC_CL_CRS_GIFT_PROP_USE_RQ						    CRS_PACK_BASE+223	 //������������
#define UC_CL_CRS_GIFT_PROP_USE_RS						    CRS_PACK_BASE+224	 //�������Ӧ���
#define UC_CL_CRS_GIFT_PROP_USE_NOTIFY                      CRS_PACK_BASE+225	 //������߹㲥��
#define UC_CL_CRS_BIG_GIFT_PROP_USE_NOTIFY         			CRS_PACK_BASE+228  //ʹ�ô�����㲥
#define UC_CRS_CL_BALANCE_NOTIFY                            CRS_PACK_BASE+229  //U�����֪ͨ

#define UC_CRS_CL_LOUDSPEAKER_NOTIFY						CRS_PACK_BASE + 230    //���ȵ�ʹ��֪ͨ   20100423(zdm)
#define UC_CRS_CL_LOUDSPEAKER_NOTIFY_RS						CRS_PACK_BASE + 231		//��С���ȹ㲥Ӧ�� 20100423(zdm)
#define UC_CRS_CL_LOUDSPEAKER_NOTIFY_RS_EX					CRS_PACK_BASE + 234  //��С���ȹ㲥Ӧ����չ 20100818(xq)

#define UC_CL_CRS_AWARD_USE_NOTIFY         			        CRS_PACK_BASE + 235  //��������㲥  2010-11-24  fangkm
#define UC_CL_CRS_FIREWORKS_USE_NOTIFY         		    	CRS_PACK_BASE + 236  //�̻����߹㲥  2010-11-24  fangkm
#define UC_CL_CRS_LUCK_PROP_USE_INFO                        CRS_PACK_BASE + 237  //���˵��ߴ���(�ɰ治�ô˰�) 2011-03-10

#define UC_CRS_CL_USER_LOSTRATE_RQ							CRS_PACK_BASE + 232    //����������
#define UC_CRS_CL_USER_LOSTRATE_RS							CRS_PACK_BASE + 233    //������Ӧ��
#define UC_CL_VIP_ENTER_NOTIFY_EX							CRS_PACK_BASE + 240		//VIP�û���Ϣ֪ͨ��
#define UC_CRS_CL_USER_AVS_INFO_ID							CRS_PACK_BASE + 241		//AVS��Ϣ֪ͨ��
#define UC_CL_CRS_USER_AVS_CHANGE_ID						CRS_PACK_BASE + 242     //�û�AVS��Ϣ�仯֪ͨ��

#define UC_CL_CRS_FLOWERS_ID_NO_LIMIT   					CRS_PACK_BASE+250	 //�û��׻���  ��ʱ������
#define UC_CL_CRS_MANAGER_OPERATION_ON_USER_RQ				CRS_PACK_BASE+251	//�����û����� ����
#define UC_CL_CRS_DATA_ID_HERMIT							CRS_PACK_BASE+252	 //������Ϣ�� ����
#define UC_CL_CRS_DATA_ID_LONG								CRS_PACK_BASE+253	 //������Ϣ��
#define UC_CL_CRS_CHG_USER_INFO_ID							CRS_PACK_BASE+254	 //�޸��û���Ϣ֪ͨ

//*************************************************************************************************//
//***********************  ���¶�����ö����������GAS������������ʹ��  ***************************//
//*************************************************************************************************//
//����������Ӧ����
#define UC_VOICE_CHAT_RESULE_AGREE				0					//������Ӧ��ͬ����������
#define UC_VOICE_CHAT_RESULE_DISAGREE			1					//������Ӧ��ͬ����������

//����Ա����˷����Ҫ���еĲ���
#define UC_MANAGER_MICROPHONE_APPLY				0					//������˷����
#define UC_MANAGER_MICROPHONE_CANCEL			1					//ȡ����˷����

//����������˷���������Ӧ��
#define UC_MANAGER_MICROPHONE_RESULT_SUCCESS	0					//������˷����ɹ�
#define UC_MANAGER_MICROPHONE_RESULT_NO_SUCCESS	1					//������˷�����ɹ�

#define UC_MANAGER_USER_DESCRIBE_LEN			256					//����Ա��ǰ����������
#define UC_MANAGER_BROADCAST_LEN				512 				//����Ա���͹㲥�ĳ���
#define UC_CRS_NOTIFY_MSG_LEN					1024 				//����Ա���͹㲥�ĳ���

#define	ERROR_BUFFER_LENGTH						256					//���������߳����󳤶�

//����Ա����˷����Ҫ���еĲ���
//#define UC_MANAGER_RECORD_ACTION_APPLY			0					//��ʼ¼��
//#define UC_MANAGER_RECORD_ACTION_CANCEL			1					//����¼��
//#define UC_CHATROOM_RECORD_DATA_LEN				512					//¼�������ݵĳ���

//�û���¼����Ӧ����
#define UC_LOGIN_HALL_RESULT_AGREE				0					//ͬ���¼
#define UC_LOGIN_HALL_RESULT_PASSWORD_ERROR		1					//�������

//�����Ҹ������Եĳ���
#define UC_CHATROOM_TOPIC_LEN					512					//����ĳ���
#define UC_CHATROOM_SALUTATORY_LEN				512					//��ӭ�ʵĳ���
#define UC_HALL_PWD_LEN			128					//���볤��

#define UC_LOGIN_HALL_USER_VIDEO_STATE          0x01				//�û�����Ƶ�豸

#define UC_NEW_OFFER_BROW_NAME_LEN              50                  //������������������ֳ���

#define DEF_CONTENT_NAME_LEN					255					//�������Ƴ���
#define UC_RSA_KEY_LEN							1024 				//RSA���ͳ���

#define USER_INTRO_LEN							200

#define UC_HALL_AVS_NAME_LEN					50
//add by Fanyunfeng
//STRU_UC_CL_CRS_FLOWERS_ID.mbyIsPrivate
//STRU_UC_CL_CRS_DATA_ID_350.mi64IsPrivate
//��Ϣ����
#define DEF_MESSAGE_PUBLIC		0
#define DEF_MESSAGE_PRIVATE		~NULL

//������״̬ STRU_UC_CL_CRS_HALL_STAT_CHG_ID.mwProperty �е�����
#define DEF_HALL_STATE_ALLOW_PRESENT_FLOWERS 		0
#define DEF_HALL_STATE_ALLOW_PUBLIC_MESSAGE			1
#define DEF_HALL_STATE_TRANS_VIDEO					2

//����������
#define DEF_MIC_MANAGE_SEIZE	1//		ռ��
#define DEF_MIC_MANAGE_GET		2//		����
#define DEF_MIC_MANAGE_PUT		3//		����
#define DEF_MIC_MANAGE_PREP		4//		׼������

//��˹����������
#define DEF_CHG_MIC_STAT		1//		��/�ر���
#define DEF_CHG_VIDEO_STAT		2//		���ϵ���Ƶת��
#define DEF_CHG_MANAGE_STAT		3//		��ʼ/��������Ա����
#define DEF_CHG_SWITCH_STAT		4//		����ʹ�ã��Զ���������
#define DEF_CHG_PLAY_STAT		5//		����ʹ�ã��Զ���������
/*********************************************************************************************/
//****************************�������İ�(��ʼ����Ӧ���ֹͣ)*******************************//
/*********************************************************************************************/
/*********************************************************************************************/
//������������� 
//��;:�û������������û���������˽�ġ�
/*********************************************************************************************/

//STRU_MIC_OPERATE
struct STRU_CL_CRS_VOICE_CHAT_RQ
{
	int Pack(char * apBuffer ,int alLen);
	int UnPack(char *apBuffer,int alLen);
	STRU_CL_CRS_VOICE_CHAT_RQ()
	{
		memset(this, 0, sizeof(STRU_CL_CRS_VOICE_CHAT_RQ));
	}
	int Serialize(CStandardSerialize & aoStandardSerialize);

	int64_t		mi64SelfUserId;			//�Լ��û�ID	STRU_MIC_OPERATE::mi64SourceUserId
	int64_t		mi64DestUserId;			//Ŀ���û�ID	STRU_MIC_OPERATE::mi64DestUserId
};
typedef struct STRU_CL_CRS_VOICE_CHAT_RQ * PSTRU_CL_CRS_VOICE_CHAT_RQ;

/*********************************************************************************************/
//��������Ӧ��
//��;:������ͬ���뷢����˽�ġ�
/*********************************************************************************************/
//STRU_MIC_OPERATE
struct STRU_CL_CRS_VOICE_CHAT_RS
{
	int Pack(char * apBuffer ,int alLen);
	int UnPack(char *apBuffer,int alLen);
	STRU_CL_CRS_VOICE_CHAT_RS()
	{
		memset(this, 0, sizeof(STRU_CL_CRS_VOICE_CHAT_RS));
	}
	int Serialize(CStandardSerialize & aoStandardSerialize);

	int64_t		mi64SelfUserId;			//�Լ��û�ID	STRU_MIC_OPERATE::mi64SourceUserId
	int64_t		mi64DestUserId;			//Ŀ���û�ID	STRU_MIC_OPERATE::mi64DestUserId
};
typedef struct STRU_CL_CRS_VOICE_CHAT_RS * PSTRU_CL_CRS_VOICE_CHAT_RS;

/*********************************************************************************************/
//��������������Ӧ���
//��;:����������˽�Ĺ�ϵ�ɹ���֪ͨ˽�ĵ����뷽�ͷ���˽�Ľ����ɹ���
/*********************************************************************************************/
//STRU_MIC_OPERATE
struct STRU_CL_CRS_VOICE_CHAT_SERVER_RS
{
	int Pack(char * apBuffer ,int alLen);
	int UnPack(char *apBuffer,int alLen);
	STRU_CL_CRS_VOICE_CHAT_SERVER_RS()
	{
		memset(this, 0, sizeof(STRU_CL_CRS_VOICE_CHAT_SERVER_RS));
	}
	int Serialize(CStandardSerialize & aoStandardSerialize);

	uint8_t		mbyResult;				//Ӧ����	STRU_MIC_OPERATE::mbyResult
	int64_t		mi64RQUserId;			//��������û�ID	STRU_MIC_OPERATE::mi64SourceUserId
	int64_t		mi64RSUserId;			//Ӧ���û��û�ID	STRU_MIC_OPERATE::mi64DestUserId
};
typedef struct STRU_CL_CRS_VOICE_CHAT_SERVER_RS * PSTRU_CL_CRS_VOICE_CHAT_SERVER_RS;

/*********************************************************************************************/
//��������ֹ֪ͣͨ
//��;:˽�ĵ�˫�������˳�ʱ��֪ͨ����������˽�Ĺ�ϵ��������֪ͨ��һ��������˽�Ĺ�ϵ��
/*********************************************************************************************/
//STRU_MIC_OPERATE
struct STRU_CL_CRS_VOICE_CHAT_STOP_ID
{
	int Pack(char *apBuffer ,int alLen);
	int UnPack(char *apBuffer,int alLen);
	STRU_CL_CRS_VOICE_CHAT_STOP_ID()
	{
		memset(this, 0, sizeof(STRU_CL_CRS_VOICE_CHAT_STOP_ID));
	}
	int Serialize(CStandardSerialize & aoStandardSerialize);

	int64_t		mi64SelfUserId;			//�Լ��û�ID	STRU_MIC_OPERATE::mi64SourceUserId
	int64_t		mi64DestUserId;			//Ŀ���û�ID	STRU_MIC_OPERATE::mi64DestUserId
};
typedef struct STRU_CL_CRS_VOICE_CHAT_STOP_ID * PSTRU_CL_CRS_VOICE_CHAT_STOP_ID;

/*********************************************************************************************/
//***** ���������Ҷ���˷�����(Ҫ�󡢸�ʱ�������󡢸�����ӡ�ֹ֪ͣͨ������֪ͨ)  *******//
/*********************************************************************************************/
/*********************************************************************************************/
//�û�����Ҫ��������
//��;:�û����뷢��ʱ���ʹ����ݰ���
/*********************************************************************************************/
//STRU_MIC_OPERATE
struct STRU_CL_CRS_CHATROOM_APPLY_MICROPHONE_RQ
{
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	STRU_CL_CRS_CHATROOM_APPLY_MICROPHONE_RQ()
	{
		memset(this, 0, sizeof(STRU_CL_CRS_CHATROOM_APPLY_MICROPHONE_RQ));
	}
	int Serialize(CStandardSerialize & aoStandardSerialize);

	int64_t		mi64UserId;		//���뷢�Ե��û�ID STRU_MIC_OPERATE::mi64SourceUserId
};
typedef struct STRU_CL_CRS_CHATROOM_APPLY_MICROPHONE_RQ * PSTRU_CL_CRS_CHATROOM_APPLY_MICROPHONE_RQ;

/*********************************************************************************************/
//�û�����Ҫ���Ӧ���
//��;:֪ͨ�û�������
/*********************************************************************************************/
//STRU_MIC_OPERATE
struct STRU_CL_CRS_CHATROOM_APPLY_MICROPHONE_RS
{
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	STRU_CL_CRS_CHATROOM_APPLY_MICROPHONE_RS()
	{
		memset(this, 0, sizeof(STRU_CL_CRS_CHATROOM_APPLY_MICROPHONE_RS));
	}
	int Serialize(CStandardSerialize & aoStandardSerialize);

	int64_t		mi64UserId;		//���뷢�Ե��û�ID	STRU_MIC_OPERATE::mi64SourceUserId
	//�û����뵽����˷�˳��(��1��ʼ)�������벻�ɹ�����0
	uint16_t		mwSpeakOrder;	//STRU_MIC_OPERATE::mbyIndex	
};
typedef struct STRU_CL_CRS_CHATROOM_APPLY_MICROPHONE_RS* PSTRU_CL_CRS_CHATROOM_APPLY_MICROPHONE_RS;

//����Աǿ���������������
struct STRU_CL_CRS_CHATROOM_MANAGER_GET_MICROFPHONE_RQ
{
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	STRU_CL_CRS_CHATROOM_MANAGER_GET_MICROFPHONE_RQ();
	int Serialize(CStandardSerialize & aoStandardSerialize);

	int64_t		mi64ManagerId;
	int64_t		mi64UserId;		//��������û�ID
};
typedef struct STRU_CL_CRS_CHATROOM_MANAGER_GET_MICROFPHONE_RQ * PSTRU_CL_CRS_CHATROOM_MANAGER_GET_MICROFPHONE_RQ;

//����Ա�����ĳ���û������
struct STRU_CL_CRS_CHATROOM_MANAGER_PUT_MICROFPHONE_RQ
{
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	STRU_CL_CRS_CHATROOM_MANAGER_PUT_MICROFPHONE_RQ();
	int Serialize(CStandardSerialize & aoStandardSerialize);

	int64_t		mi64ManagerId;
	int64_t		mi64UserId;		//��������û�ID
};
typedef struct STRU_CL_CRS_CHATROOM_MANAGER_PUT_MICROFPHONE_RQ * PSTRU_CL_CRS_CHATROOM_MANAGER_PUT_MICROFPHONE_RQ;

//����Ա�����ĳ���û�֪ͨ��
//STRU_MIC_OPERATE
struct STRU_CL_CRS_CHATROOM_MANAGER_PUT_MICROFPHONE_ID
{
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	STRU_CL_CRS_CHATROOM_MANAGER_PUT_MICROFPHONE_ID()
	{
		memset(this, 0, sizeof(STRU_CL_CRS_CHATROOM_MANAGER_PUT_MICROFPHONE_ID));
	}
	int Serialize(CStandardSerialize & aoStandardSerialize);

	int64_t		mi64ManagerId;		//STRU_MIC_OPERATE::mi64SourceUserId
	int64_t		mi64UserId;		//��������û�ID	STRU_MIC_OPERATE::mi64DestUserId
};
typedef struct STRU_CL_CRS_CHATROOM_MANAGER_PUT_MICROFPHONE_ID * PSTRU_CL_CRS_CHATROOM_MANAGER_PUT_MICROFPHONE_ID;

//����Ա��ĳ���û����뵽���Զ��������
struct STRU_CL_CRS_CHATROOM_MANAGER_INSERT_MICROFPHONE_RQ
{
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	STRU_CL_CRS_CHATROOM_MANAGER_INSERT_MICROFPHONE_RQ();
	int Serialize(CStandardSerialize & aoStandardSerialize);

	int64_t		mi64ManagerId;
	int64_t		mi64UserId;		//����ӵ����Զ��е��û�ID
};
typedef struct STRU_CL_CRS_CHATROOM_MANAGER_INSERT_MICROFPHONE_RQ * PSTRU_CL_CRS_CHATROOM_MANAGER_INSERT_MICROFPHONE_RQ;

//���ӣ��ν��� 2006-11-21 below
//����Ա��ĳ���û����뵽���Զ���ָ��λ�������
//STRU_MIC_OPERATE
struct STRU_CL_CRS_CHATROOM_MANAGER_INSERTINTO_MICROFPHONE_RQ
{
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	STRU_CL_CRS_CHATROOM_MANAGER_INSERTINTO_MICROFPHONE_RQ()
	{
		memset(this, 0, sizeof(STRU_CL_CRS_CHATROOM_MANAGER_INSERTINTO_MICROFPHONE_RQ));
	}
	int Serialize(CStandardSerialize & aoStandardSerialize);

	int64_t		mi64ManagerId;		//STRU_MIC_OPERATE::mi64SourceUserId
	int64_t		mi64UserId;		//����ӵ����Զ��е��û�ID	STRU_MIC_OPERATE::mi64DestUserId
	uint8_t		miInsertIndex;  //�����λ��	STRU_MIC_OPERATE::mbyIndex
};
typedef struct STRU_CL_CRS_CHATROOM_MANAGER_INSERTINTO_MICROFPHONE_RQ * PSTRU_CL_CRS_CHATROOM_MANAGER_INSERTINTO_MICROFPHONE_RQ;
//���ӣ��ν��� 2006-11-21 above
/*********************************************************************************************/
//�ı䵱ǰ�û��ķ���ʱ�������
//��;:�ɹ���Ա������
/*********************************************************************************************/
struct STRU_CL_CRS_CHATROOM_MICROPHONE_TIMELIMIT_CHG_RQ
{
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	STRU_CL_CRS_CHATROOM_MICROPHONE_TIMELIMIT_CHG_RQ();
	int Serialize(CStandardSerialize & aoStandardSerialize);

	int64_t		mi64ManagerId;
	int64_t		mi64UserId;		//�ı���û�ID
	uint8_t		mbyMinute;		//�����Է�����
	uint8_t		mbyMicIndex;	//�������
};
typedef struct STRU_CL_CRS_CHATROOM_MICROPHONE_TIMELIMIT_CHG_RQ* PSTRU_CL_CRS_CHATROOM_MICROPHONE_TIMELIMIT_CHG_RQ;

/*********************************************************************************************/
//�ı䵱ǰ�û��ķ���ʱ�������
//��;:�ı䵱ǰ�û��ķ���ʱ���ɹ���֪ͨ�����������û���
/*********************************************************************************************/
struct STRU_CL_CRS_CHATROOM_MICROPHONE_TIMELIMIT_CHG_ID
{
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	STRU_CL_CRS_CHATROOM_MICROPHONE_TIMELIMIT_CHG_ID();
	int Serialize(CStandardSerialize & aoStandardSerialize);

	int64_t		mi64UserId;		//�ı���û�ID
	uint8_t		mbyMinute;		//�����Է�����	
	int64_t		mi64ManagerId;	//
	uint8_t		mbyMicIndex;	//�������
};
typedef struct STRU_CL_CRS_CHATROOM_MICROPHONE_TIMELIMIT_CHG_ID* PSTRU_CL_CRS_CHATROOM_MICROPHONE_TIMELIMIT_CHG_ID;

/*********************************************************************************************/
//�û�����ֹ֪ͣͨ��
//��;:�û���ǰֹͣ����,����ֹͣ������֪ͨ��������
/*********************************************************************************************/
//STRU_MIC_OPERATE
struct STRU_CL_CRS_CHATROOM_STOP_SPEAK_ID
{
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	STRU_CL_CRS_CHATROOM_STOP_SPEAK_ID()
	{
		memset(this, 0, sizeof(STRU_CL_CRS_CHATROOM_STOP_SPEAK_ID));
	}
	int Serialize(CStandardSerialize & aoStandardSerialize);

	int64_t		mi64UserId;		//ֹͣ���Ե��û�ID		STRU_MIC_OPERATE::mi64SourceUserId
};
typedef struct STRU_CL_CRS_CHATROOM_STOP_SPEAK_ID * PSTRU_CL_CRS_CHATROOM_STOP_SPEAK_ID;

/*********************************************************************************************/
//��ǰ��˷緢��˳���
//��;:������ǰ�������ǰN���û���
/*********************************************************************************************/
//��������˷緢��˳���
struct STRU_CL_CRS_CHATROOM_MICROPHONE_ORDER_ID
{
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	STRU_CL_CRS_CHATROOM_MICROPHONE_ORDER_ID()
	{
		memset(this, 0, sizeof(STRU_CL_CRS_CHATROOM_MICROPHONE_ORDER_ID));
	}
	int Serialize(CStandardSerialize & aoStandardSerialize);
	~STRU_CL_CRS_CHATROOM_MICROPHONE_ORDER_ID();

	uint8_t		mbyCount;			//list�ĸ���
	int64_t *	mpUserIdList;		//�û�ID��ָ���б�
} ;
typedef struct STRU_CL_CRS_MICROPHONE_ORDER_ID * PSTRU_CL_CRS_MICROPHONE_ORDER_ID;
//SinaShow��˷緢��˳���
struct STRU_WAITING_USER_INFO
{
	int64_t	 	mi64UserID;
	char		macNickName[NICK_NAME_LEN+1];
	int		mlHallID;
	int		mlPicIndex;
	uint16_t		mwVersion;
	uint8_t		mbyGrade;	//�û�����   
	int		mlUserState; //�û�״̬ 
	int Serialize(CStandardSerialize & aoStandardSerialize);
};

struct STRU_SINASHOW_MICROPHONE_ORDER_ID
{
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	STRU_SINASHOW_MICROPHONE_ORDER_ID();
	int Serialize(CStandardSerialize & aoStandardSerialize);

	uint8_t						mbyCount;			//list�ĸ���
	STRU_WAITING_USER_INFO*		mpUserIdList;		//�û�ID��ָ���б�
} ;
//**********************************************************************************//
//*******  ����Ա����˷�����(��������Ӧ��֪ͨ��������֪ͨ��Ҫ��֪ͨ)	 *******//
//**********************************************************************************//
/*********************************************************************************************/
//����Ա�����ȡ����˷���������
//��;:
/*********************************************************************************************/
struct STRU_CL_CRS_CHATROOM_MANAGER_MICROPHONE_RQ
{
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	STRU_CL_CRS_CHATROOM_MANAGER_MICROPHONE_RQ();
	int Serialize(CStandardSerialize & aoStandardSerialize);

	int64_t		mi64ManagerId;	
	uint8_t		mbyType;		// 0=������Ĺ���1��ȡ����Ĺ���
};
typedef struct STRU_CL_CRS_CHATROOM_MANAGER_MICROPHONE_RQ * PSTRU_CL_CRS_CHATROOM_MANAGER_MICROPHONE_RQ;

/*********************************************************************************************/
//����Ա�����ȡ����˷����Ӧ���
//��;:
/*********************************************************************************************/
struct STRU_CL_CRS_CHATROOM_MANAGER_MICROPHONE_RS
{
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	STRU_CL_CRS_CHATROOM_MANAGER_MICROPHONE_RS();
	int Serialize(CStandardSerialize & aoStandardSerialize);

	int64_t		mi64ManagerId;	
	uint8_t		mbyType;		// 0=������Ĺ���1��ȡ����Ĺ���
	//����� ��������������ڹ�����󣬷������������ڹ������
	uint8_t		mbyResult;
};
typedef struct STRU_CL_CRS_CHATROOM_MANAGER_MICROPHONE_RS * PSTRU_CL_CRS_CHATROOM_MANAGER_MICROPHONE_RS;

/*********************************************************************************************/
//����Ա�����ȡ����˷����֪ͨ��
//��;:
/*********************************************************************************************/
struct STRU_CL_CRS_CHATROOM_MANAGER_MICROPHONE_ID
{
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	int Serialize(CStandardSerialize & aoStandardSerialize);
	STRU_CL_CRS_CHATROOM_MANAGER_MICROPHONE_ID();

	int64_t		mi64ManagerId;	
	uint8_t		mbyType;		// 0=��ʼ��Ĺ���1=ֹͣ��Ĺ���
};
typedef struct STRU_CL_CRS_CHATROOM_MANAGER_MICROPHONE_ID * PSTRU_CL_CRS_CHATROOM_MANAGER_MICROPHONE_ID;

/*********************************************************************************************/
//����Ա�޸������ҷ���ʱ�����������
//��;:
/*********************************************************************************************/
//STRU_MIC_OPERATE
struct STRU_CL_CRS_CHATROOM_MANAGER_TIMELIMIT_CHG_RQ
{
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	int Serialize(CStandardSerialize & aoStandardSerialize);
	STRU_CL_CRS_CHATROOM_MANAGER_TIMELIMIT_CHG_RQ()
	{
		memset(this, 0, sizeof(STRU_CL_CRS_CHATROOM_MANAGER_TIMELIMIT_CHG_RQ));
	}

	int64_t		mi64ManagerId;		//STRU_MIC_OPERATE::mi64SourceUserId
	uint8_t		mbyMinute;		//�����Է�����	STRU_MIC_OPERATE::mlTime
	uint8_t		mbyMicIndex;	//STRU_MIC_OPERATE::mbyIndex
};
typedef struct STRU_CL_CRS_CHATROOM_MANAGER_TIMELIMIT_CHG_RQ * PSTRU_CL_CRS_CHATROOM_MANAGER_TIMELIMIT_CHG_RQ;

/*********************************************************************************************/
//����Ա�޸������ҷ���ʱ������֪ͨ��
//��;:
/*********************************************************************************************/
//STRU_MIC_OPERATE
struct STRU_CL_CRS_CHATROOM_MANAGER_TIMELIMIT_CHG_ID
{
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	int Serialize(CStandardSerialize & aoStandardSerialize);
	STRU_CL_CRS_CHATROOM_MANAGER_TIMELIMIT_CHG_ID()
	{
		memset(this, 0,sizeof(STRU_CL_CRS_CHATROOM_MANAGER_TIMELIMIT_CHG_ID));
	}

	int64_t		mi64ManagerId;	//STRU_MIC_OPERATE::mi64SourceUserId
	uint8_t		mbyMinute;		//�����Է�����	STRU_MIC_OPERATE::mlTime
	uint8_t		mbyMicIndex;	//STRU_MIC_OPERATE::mbyIndex
};
typedef struct STRU_CL_CRS_CHATROOM_MANAGER_TIMELIMIT_CHG_ID * PSTRU_CL_CRS_CHATROOM_MANAGER_TIMELIMIT_CHG_ID;

//**********************************************************************************//
//*******  ����Ա���й����(�㲥�������û�����Ӧ��¼�������¼������)	********//
//**********************************************************************************//
/*********************************************************************************************/
//����㲥��
//��;:
/*********************************************************************************************/
//STRU_USER_OPERATE
struct STRU_CL_CRS_CHATROOM_BROADCAST_RQ
{
	STRU_CL_CRS_CHATROOM_BROADCAST_RQ()
	{
		memset(this, 0, sizeof(STRU_CL_CRS_CHATROOM_BROADCAST_RQ));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	int Serialize(CStandardSerialize & aoStandardSerialize);

	int64_t		mi64ManagerId;	//STRU_USER_OPERATE::mi64SourceUserId
	uint16_t        mwDataLen;		//STRU_USER_OPERATE::mlValue
	char		macBroadcaseMsg[UC_MANAGER_BROADCAST_LEN + 1];//�㲥������	//STRU_USER_OPERATE::mpContent
};
typedef struct STRU_CL_CRS_CHATROOM_BROADCAST_RQ* PSTRU_CL_CRS_CHATROOM_BROADCAST_RQ;

/*********************************************************************************************/
//����Ա�����û��Ĵ��������
//��;:
/*********************************************************************************************/
//STRU_MIC_OPERATE
struct STRU_CL_CRS_OPERATION_ON_USER_RQ
{
	STRU_CL_CRS_OPERATION_ON_USER_RQ()
	{
		memset(this, 0, sizeof(STRU_CL_CRS_OPERATION_ON_USER_RQ));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	int Serialize(CStandardSerialize & aoStandardSerialize);

	int64_t		mi64ManagerId;		//����ԱID	STRU_MIC_OPERATE::mi64SourceUserId
	//STRU_MIC_OPERATE::mbyType
	//�������ͣ�����(���)��ʱ����Ա:10(11);��ֹ(���)�û�����:12(13);��ʱ(��ʱ)(����)�߳��û�14(15)(16);
	//�ָ���ʱ�߳��û�:17;  ��ʱ(����)��ֹIP:29(30);�ָ���ʱ��ֹIP�û�:31;
	//#define DEF_MANAGER_OPERATION_ADD_SHOWBAR     32//������ɳ�Ա;
	//#define DEF_MANAGER_OPERATION_DELETE_SHOWBAR  33//ɾ����ɳ�Ա
	uint8_t		mbyType;			
	int64_t		mi64UserId;			//�������û�ID	STRU_MIC_OPERATE::mi64DestUserId
	int     	mlOtherParam;		//����ʱ�߳��û�ʱ������ʱ��	STRU_MIC_OPERATE::mlTime
	//��ǰ����������(���˵Ļ�����������ԭ��)	STRU_MIC_OPERATE::mpContent
	char		mstrDescribe[UC_MANAGER_USER_DESCRIBE_LEN + 1];		
};
typedef struct STRU_CL_CRS_OPERATION_ON_USER_RQ * PSTRU_CL_CRS_OPERATION_ON_USER_RQ ;

/*********************************************************************************************/
//����Ա�����û��Ĵ���Ӧ���
//��;:
/*********************************************************************************************/
//STRU_MIC_OPERATE
struct STRU_CL_CRS_MANAGER_OPERATION_ON_USER_RS
{
	STRU_CL_CRS_MANAGER_OPERATION_ON_USER_RS()
	{
		memset(this, 0, sizeof(STRU_CL_CRS_MANAGER_OPERATION_ON_USER_RS));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	int Serialize(CStandardSerialize & aoStandardSerialize);

	uint8_t		mbyResult;			//������� ���ʾ�ɹ� �����ʾʧ��	STRU_MIC_OPERATE::mbyResult
	int64_t		mi64ManagerId;		//����ԱID		STRU_MIC_OPERATE::mi64SourceUserId
	//STRU_MIC_OPERATE::mbyType
	uint8_t		mbyType;			//�������ͣ�������ʱ����Ա�������ʱ����Ա����ֹ�û����ԣ���ʱ�߳��û�����ʱ�߳��û���
	int64_t		mi64UserId;			//�������û�ID	STRU_MIC_OPERATE::mi64DestUserId
	//��ǰ����������(���˵Ļ�����������ԭ��)
	char		mstrDescribe[UC_MANAGER_USER_DESCRIBE_LEN + 1];	//STRU_MIC_OPERATE::mpContent	
} ;
typedef struct STRU_CL_CRS_MANAGER_OPERATION_ON_USER_RS * PSTRU_CL_CRS_MANAGER_OPERATION_ON_USER_RS ;

/*********************************************************************************************/
//�û�״̬�ı�֪ͨ��
//��;:
/*********************************************************************************************/
//STRU_USER_OPERATE
struct STRU_CL_CRS_CHATROOM_USER_STATE_CHG_ID
{
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	int Serialize(CStandardSerialize & aoStandardSerialize);
	STRU_CL_CRS_CHATROOM_USER_STATE_CHG_ID()
	{
		memset(this, 0, sizeof(STRU_CL_CRS_CHATROOM_USER_STATE_CHG_ID));
	}

	int64_t mi64UserId; //�û�ID		STRU_USER_OPERATE::mi64SourceUserId
	uint8_t mbyState;      //Ҫ�޸ĵ�״̬��		STRU_USER_OPERATE::mbyType
	bool mbNewVal;      //�µ�״ֵ̬			STRU_USER_OPERATE::mbyValue
};
typedef struct STRU_CL_CRS_CHATROOM_USER_STATE_CHG_ID * PSTRU_CL_CRS_CHATROOM_USER_STATE_CHG_ID;

//*************************************************************************************************//
//******  ���������û�ͨѶ��(������֪ͨ������仯֪ͨ����¼���󡢵�¼Ӧ��״̬�仯֪ͨ) **********//
//*************************************************************************************************//
/*********************************************************************************************/
//�û�������֪ͨ��
//����Ա�޸������ҷ���ʱ������֪ͨ��
/*********************************************************************************************/
//STRU_USER_OPERATE
struct STRU_CL_CRS_USER_BE_OPERATED_ID
{
	STRU_CL_CRS_USER_BE_OPERATED_ID()
	{
		memset(this, 0, sizeof(STRU_CL_CRS_USER_BE_OPERATED_ID));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	int Serialize(CStandardSerialize & aoStandardSerialize);

	int64_t		mi64ManagerId;		//����ԱID	STRU_USER_OPERATE::mi64SourceUserId
	int64_t		mi64UserId;			//�������û�ID	STRU_USER_OPERATE::mi64DestUserId
	//������������ͣ�����(���)��ʱ����Ա:10(11);��ֹ(���)�û�����:12(13);��ʱ(��ʱ)(����)�߳��û�14(15)(16);
	//�ָ���ʱ�߳��û�:17;  ��ʱ(����)��ֹIP:29(30); �ָ���ʱ��ֹIP�û�:31; ����:40; 100:���к��н��뱻�߳�
	uint8_t		mbyType;			//	STRU_USER_OPERATE::mbyType
	char		mstrDescribe[UC_MANAGER_USER_DESCRIBE_LEN + 1];		//������Ϣ������	STRU_USER_OPERATE::mpContent
} ;
typedef struct STRU_CL_CRS_USER_BE_OPERATED_ID * PSTRU_CL_CRS_USER_BE_OPERATED_ID;

/*********************************************************************************************/
//�û�����仯֪ͨ��
//��;:
/*********************************************************************************************/
//STRU_USER_OPERATE
struct STRU_CL_CRS_USER_POWER_CHG_ID
{
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	STRU_CL_CRS_USER_POWER_CHG_ID();
	int Serialize(CStandardSerialize & aoStandardSerialize);

	int64_t		mi64UserId;			//�û�ID	STRU_USER_OPERATE::mi64SourceUserId
	uint8_t		mbyPower;			//�任��ļ���	STRU_USER_OPERATE::mbyValue
};
typedef struct STRU_CL_CRS_USER_POWER_CHG_ID * PSTRU_CL_CRS_USER_POWER_CHG_ID ;

/*********************************************************************************************/
//�û�����״̬�仯֪ͨ��
//��;:
/*********************************************************************************************/
//STRU_USER_OPERATE
struct STRU_CL_CRS_VOICE_STATE_CHG_ID
{
	STRU_CL_CRS_VOICE_STATE_CHG_ID()
	{
		memset(this, 0, sizeof(STRU_CL_CRS_VOICE_STATE_CHG_ID));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	int Serialize(CStandardSerialize & aoStandardSerialize);

	int64_t		mi64UserId;			//�û�ID	STRU_USER_OPERATE::mi64SourceUserId
	uint8_t		mbyState;			//�仯���״̬	STRU_USER_OPERATE::mbyValue
};
typedef struct STRU_CL_CRS_USER_STATE_CHG_ID * PSTRU_CL_CRS_USER_STATE_CHG_ID;

//**********************************************************************************//
//**********  ����������֪ͨ��(�����޸������������֪ͨ��������֪ͨ��)	************//
//**********************************************************************************//
/*********************************************************************************************/
//�����������޸������
//��;:
/*********************************************************************************************/
struct STRU_CL_CRS_CHATROOM_PROPERTY_CHG_RQ
{
	STRU_CL_CRS_CHATROOM_PROPERTY_CHG_RQ()
	{
		memset(this, 0, sizeof(STRU_CL_CRS_CHATROOM_PROPERTY_CHG_RQ));
	}

	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	int	   Serialize(CStandardSerialize & aoStandardSerialize);

	int64_t		mi64ManagerId;
	char		macTopic[UC_CHATROOM_TOPIC_LEN + 1];				//�����ҵ�����
	char		macSalutatory[UC_CHATROOM_SALUTATORY_LEN + 1];		//�����ҵĻ�ӭ��
	char		macPassword[UC_HALL_PWD_LEN + 1];		//�����ҵ�����
	bool		mbIsLockHall;										//���������Ƿ����
} ;
typedef struct STRU_CL_CRS_CHATROOM_PROPERTY_CHG_RQ * PSTRU_CL_CRS_CHATROOM_PROPERTY_CHG_RQ;

/*********************************************************************************************/
//�����ҵ�����֪ͨ��(����֪ͨ���й���Ա)
//��;:
/*********************************************************************************************/
struct STRU_CL_CRS_CHATROOM_PROPERTY_ID
{
	STRU_CL_CRS_CHATROOM_PROPERTY_ID()
	{
		memset(this, 0, sizeof(STRU_CL_CRS_CHATROOM_PROPERTY_ID));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	int Serialize(CStandardSerialize & aoStandardSerialize);

	int64_t		mi64ManagerId;										//�޸���ID
	char		macTopic[UC_CHATROOM_TOPIC_LEN + 1];				//�����ҵ�����
	char		macSalutatory[UC_CHATROOM_SALUTATORY_LEN + 1];		//�����ҵĻ�ӭ��
	char		macPassword[UC_HALL_PWD_LEN + 1];		//�����ҵ�����
	bool		mbIsLocked;											//�Ƿ����
};
typedef struct STRU_CL_CRS_CHATROOM_PROPERTY_ID * PSTRU_CL_CRS_CHATROOM_PROPERTY_ID;

/*********************************************************************************************/
//����������֪ͨ
//��;:
/*********************************************************************************************/
struct STRU_CL_CRS_CHATROOM_TOPIC_ID
{
	STRU_CL_CRS_CHATROOM_TOPIC_ID()
	{
		memset(this, 0, sizeof(STRU_CL_CRS_CHATROOM_TOPIC_ID));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	int Serialize(CStandardSerialize & aoStandardSerialize);

	int64_t		mi64ManagerId;										//�޸���ID
	char		macTopic[UC_CHATROOM_TOPIC_LEN + 1];	        	//�����ҵ�����
	char        macWelcome[UC_CHATROOM_SALUTATORY_LEN+1];           //�����ҵĻ�ӭ��    
} ;
typedef struct STRU_CL_CRS_CHATROOM_TOPIC_ID * PSTRU_CL_CRS_CHATROOM_TOPIC_ID;

/*********************************************************************************************/
//�����������û�����֪ͨ
//�޸��ˣ�	Fanyunfeng
//ʱ�䣺	2004��12��28
//���ݣ�	RA:�������û���Ϣ(�汾400) ��390��Ϊ400 ͬʱ�����û���������
/*********************************************************************************************/
struct	STRU_UC_CL_CRS_ENTRY_OTHERUSER_ID_400
{
	int mlChatroomID;					//����id
	int64_t	mi64UserID;					//�û�ID
	char macNickName[NICK_NAME_LEN + 1];	//�û��ǳ�
	uint16_t mwPhotoNum;					//�û�ͷ��
	uint8_t mbyPower;						//�û�Ȩ��
	int mlUserState;					//�û�״̬

	uint8_t mbyUserLanguage; 			//�û���������
	int	 miRedMemTime;					//�����ʸ�

	STRU_UC_CL_CRS_ENTRY_OTHERUSER_ID_400();
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	int Serialize(CStandardSerialize & aoStandardSerialize);
};
typedef STRU_UC_CL_CRS_ENTRY_OTHERUSER_ID_400* PSTRU_UC_CL_CRS_ENTRY_OTHERUSER_ID_400; 

/*********************************************************************************************/
//�����������û��뿪֪ͨ
//��;:
/*********************************************************************************************/
//STRU_USER_OPERATE
struct	STRU_UC_CL_CRS_LEAVE_OTHERUSER_ID_350
{
	int mlChatroomID;//����id	
	int64_t	mi64UserID; //�û�ID	//STRU_USER_OPERATE::mi64SourceUserId
	uint8_t mbyCancelType;//0 ��ͨ�˳� 1����Ҫ��ʾԭ��		//STRU_USER_OPERATE::mbyType
	char	macReason[REASON_LEN + 1];//�˳�ԭ��	//STRU_USER_OPERATE::mpContent
	STRU_UC_CL_CRS_LEAVE_OTHERUSER_ID_350()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_LEAVE_OTHERUSER_ID_350));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	int Serialize(CStandardSerialize & aoStandardSerialize);
};
typedef STRU_UC_CL_CRS_LEAVE_OTHERUSER_ID_350 * PSTRU_UC_CL_CRS_LEAVE_OTHERUSER_ID_350;

/*********************************************************************************************/
//��������Ϣ֪ͨ��
//��;:
/*********************************************************************************************/
struct STRU_UC_CL_CRS_CHAT_INFO
{
	int64_t mi64FromId;
	int64_t mi64ToId;
	uint8_t	mbyChatType;
	uint16_t	mwMoodLen;
	uint16_t	mwControlLen;
	uint16_t	mwContentLen;//ͨѶ�������ֶ�
	char	mstrMood[CRS_DATA_LEN+1];
	char	mstrControl[CRS_DATA_LEN+1];
	char	mstrContent[CRS_DATA_LEN+1];
	uint16_t    mwLen;		//�ܳ������ڽ��ʱͨ������mwContentLen
	STRU_UC_CL_CRS_CHAT_INFO()
	{
		mwLen = 0;
		mi64FromId = 0;
		mi64ToId= 0;
		mbyChatType= 0;
		mwMoodLen  = 0;
		mwControlLen = 0;
		mwContentLen = 0;
		memset(mstrMood, 0, CRS_DATA_LEN+1);
		memset(mstrControl, 0,CRS_DATA_LEN+1);
		memset(mstrContent, 0,CRS_DATA_LEN+1);

	}
	int GetSubLen()
	{
		return sizeof(mi64FromId) * 2 +sizeof(uint8_t) + sizeof(uint16_t)*2 +mwMoodLen + mwControlLen;//mi64FromId+mi64ToId+mbyChatType+mwMoodLen+mwControlLen
	}
	int Serialize(CStandardSerialize & aoStandardSerialize);

};
//STRU_USER_OPERATE
struct	STRU_UC_CL_CRS_DATA_ID_350
{
	int	mlChatroomID;			//����id
	int64_t	mi64DstUserID;			//������Ϣ��ʶ	STRU_USER_OPERATE::mi64DestUserId
	uint16_t	mwDataLen;				//��Ϣ��С		STRU_USER_OPERATE::mlValue
	//char	mData[CRS_DATA_LEN+1];	//��Ϣ			STRU_USER_OPERATE::mpContent
	STRU_UC_CL_CRS_CHAT_INFO mChatInfo;
	int64_t	mi64SrcUserID;			//��Դ�û�ID	STRU_USER_OPERATE::mi64SourceUserId


	///int64_t mi64DstUserID;			//Ŀ���û�ID 2005II ��ʼ����

	STRU_UC_CL_CRS_DATA_ID_350()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_DATA_ID_350));
	}

	int Pack(char* apBuffer , int alLen);
	int UnPack(char* apBuffer, int alLen);
	int Serialize(CStandardSerialize& aoStandardSerialize);
};
typedef STRU_UC_CL_CRS_DATA_ID_350 * PSTRU_UC_CL_CRS_DATA_ID_350;

struct	STRU_UC_CL_CRS_DATA_ID_LONG
{
	long	mlChatroomID;			//����id
	int64_t	mi64DstUserID;			//������Ϣ��ʶ	STRU_USER_OPERATE::mi64DestUserId
	uint16_t	mwDataLen;				//��Ϣ��С		STRU_USER_OPERATE::mlValue
	//char	mData[CRS_DATA_LEN+1];	//��Ϣ			STRU_USER_OPERATE::mpContent
	STRU_UC_CL_CRS_CHAT_INFO mChatInfo;
	int64_t	mi64SrcUserID;			//��Դ�û�ID	STRU_USER_OPERATE::mi64SourceUserId


	///INT64 mi64DstUserID;			//Ŀ���û�ID 2005II ��ʼ����

	STRU_UC_CL_CRS_DATA_ID_LONG()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_DATA_ID_LONG));
	}

	int Pack(char* apBuffer, int alLen);
	int UnPack(char* apBuffer, int alLen);
	int Serialize(CStandardSerialize& aoStandardSerialize);
};
typedef STRU_UC_CL_CRS_DATA_ID_LONG * PSTRU_UC_CL_CRS_DATA_ID_LONG;


//�����ҿ�����Ϣ
struct STRU_UC_CL_CRS_GENERAL_INFO
{
	int64_t mi64FromId;
	int64_t mi64ToId;
	uint16_t	mwType;
	uint16_t	mwContentLen;
	char	mstrContent[CRS_DATA_LEN+1];
	int GetSubLen()
	{
		return sizeof(mi64FromId) * 2 +sizeof(uint16_t);//mi64FromId+mi64ToId+mbyChatType+mwMoodLen+mwControlLen
	}
	int Serialize(CStandardSerialize & aoStandardSerialize);
};

/*********************************************************************************************/
//�ͻ���ͨѶ�õ����ݰ�
//��;:
/*********************************************************************************************/
//STRU_USER_OPERATE
struct STRU_UC_CL_CRS_GENERAL_PACK_350
{
	int mlChatRoomID;		
	int64_t mi64DstUserID;	//STRU_USER_OPERATE::mi64DestUserId
	uint16_t mwDataLen;			//STRU_USER_OPERATE::���治��ֵ
	STRU_UC_CL_CRS_GENERAL_INFO	mGENERALInfo;	//
	//char	macGeneralMsg[INFO_LEN + 1];	//STRU_USER_OPERATE::���洫��mbyType �������⴦��
	int64_t	mi64SrcUserID; //��Դ�û�ID		//STRU_USER_OPERATE::mi64SourceUserId

	STRU_UC_CL_CRS_GENERAL_PACK_350()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_GENERAL_PACK_350));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	int Serialize(CStandardSerialize & aoStandardSerialize);
};
typedef STRU_UC_CL_CRS_GENERAL_PACK_350 *PSTRU_UC_CL_CRS_GENERAL_PACK_350;


/*********************************************************************************************/
//��ѯ��ʱ�߳��������б������
//��;:
/*********************************************************************************************/
//STRU_USER_OPERATE
struct STRU_UC_CL_CRS_BLACK_QUERY_RQ
{
	int64_t		mi64ManagerId;		//������ID  STRU_USER_OPERATE::mi64SourceUserId

	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	int Serialize(CStandardSerialize & aoStandardSerialize);
	STRU_UC_CL_CRS_BLACK_QUERY_RQ()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_BLACK_QUERY_RQ));
	}
};

/*********************************************************************************************/
//��ʱ�߳��������б�
//��;:
/*********************************************************************************************/
struct STRU_UC_CL_CRS_TIME_BLACK_LIST
{
	struct STRU_TIME_KICKOUT_USER
	{
		int64_t mi64UserID;			//�û�ID
		int   mlNoComeInTime;		//����ʱ��
		int   mlResidualTime;		//ʣ��ʱ��
		int Serialize(CStandardSerialize & aoStandardSerialize);
	};

	int64_t		mi64ManagerId;								//������ID
	short		msUserCount;								//����������
	struct STRU_TIME_KICKOUT_USER * mpBlackList;			//�������б�

	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	STRU_UC_CL_CRS_TIME_BLACK_LIST()
	{
		memset(this, 0,sizeof(STRU_UC_CL_CRS_TIME_BLACK_LIST));
	}
	int Serialize(CStandardSerialize & aoStandardSerialize);
};

/*********************************************************************************************/
//�û�����仯֪ͨ��
//��;:
/*********************************************************************************************/
struct STRU_UC_CL_CRS_POWER_CHANGED_ID
{
	STRU_UC_CL_CRS_POWER_CHANGED_ID();
	int Pack(char * apBuffer ,int alLen);
	int UnPack(char * apBuffer,int alLen);
	int Serialize(CStandardSerialize & aoStandardSerialize);

	int64_t mi64ManagerId; //����ԱID
	int64_t mi64UserId; //�������û�ID
	uint8_t mbyNewPower; //�µļ���
	char mstrDescribe[UC_MANAGER_USER_DESCRIBE_LEN + 1]; //������Ϣ������
} ;
typedef struct STRU_UC_CL_CRS_POWER_CHANGED_ID * PSTRU_UC_CL_CRS_POWER_CHANGED_ID;

/*********************************************************************************************/
//��¼Ӧ�𣨰汾390��
//��;:
/*********************************************************************************************/
struct	STRU_UC_CL_CRS_LOGIN_HALL_RS_390         
{
	STRU_UC_CL_CRS_LOGIN_HALL_RS_390();
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	int Serialize(CStandardSerialize & aoStandardSerialize);

	uint8_t				mbyResult;											//0��ͬ��,�����Ǿܾ���
	int				mlHallID;							//����id
	int				mlRoomMaxPlayer;					//�����������	
	char				macErrInfo[ERR_BUF_LEN + 1];			//������Ϣ
	char				mszVoiceIp[64];						//������ת��IP
	unsigned short		musVoicePort;							//������ת�Ķ˿�
	char				macTopic[ UC_CHATROOM_TOPIC_LEN + 1 ] ;//�����ҵ�����
	char				macSalutatory[ UC_CHATROOM_SALUTATORY_LEN + 1 ] ;		//�����ҵĻ�ӭ��	
	char				macPwd[UC_HALL_PWD_LEN + 1];			//��������(ֻ���߹���Ա)
	int64_t				mi64CurManageMic;			//��ǰ��˭�ڹ�������
	unsigned int		mulUserSpeakTime;				//��ǰ����ʱ��	
	char				macImvName[CHATROOM_IMV_NAME_LEN+1]; //�����ҳ���
	int				mlHallProperty;             //��������                               
};

/*********************************************************************************************/
//�޸��ˣ�	Fanyunfeng
//ʱ�䣺	2005��01��10
//���ݣ�	C:��¼Ӧ�𣨰汾401�� ���Ӵ���״̬
/*********************************************************************************************/
struct	STRU_UC_CL_CRS_LOGIN_HALL_RS_400         
{
	uint8_t				mbyResult;						//0��ͬ��,�����Ǿܾ���
	int				mlHallID;						//����id
	int				mlRoomMaxPlayer;				//�����������	
	char				macErrInfo[ERR_BUF_LEN + 1];	//������Ϣ
	char				mszVoiceIp[64];					//������ת��IP
	unsigned short		musVoicePort;					//������ת�Ķ˿�
	char				macTopic[ UC_CHATROOM_TOPIC_LEN + 1 ] ;
	//�����ҵ�����
	char				macSalutatory[ UC_CHATROOM_SALUTATORY_LEN + 1 ] ;		
	//�����ҵĻ�ӭ��	
	char				macPwd[UC_HALL_PWD_LEN + 1];	//��������(ֻ���߹���Ա)
	int64_t				mi64CurManageMic;				//��ǰ��˭�ڹ�������
	unsigned int		mulUserSpeakTime;				//��ǰ����ʱ��	
	char				macImvName[CHATROOM_IMV_NAME_LEN+1]; //�����ҳ���
	int				mlHallProperty;					//��������
	int				mlHallState;					//����״̬

	STRU_UC_CL_CRS_LOGIN_HALL_RS_400()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_LOGIN_HALL_RS_400));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	int Serialize(CStandardSerialize & aoStandardSerialize);
};

/*********************************************************************************************/
//��ҳ��ַ��Ϣ
//��;:
/*********************************************************************************************/
struct STRU_UC_CL_CRS_HOST_INFO
{
	STRU_UC_CL_CRS_HOST_INFO();
	char mszhostName[HOMEPAGE_DISPLAY_LEN+1];
	char mszhostAddr[URL_LINK_LEN+1];
	int Serialize(CStandardSerialize & aoStandardSerialize);
};

/*********************************************************************************************/
//��ҳ��ַ֪ͨ��
//��;:
/*********************************************************************************************/
struct  STRU_UC_CL_CRS_HOST_INFO_ID
{
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	STRU_UC_CL_CRS_HOST_INFO_ID();
	int Serialize(CStandardSerialize & aoStandardSerialize);

	char macBgBmpName[CHATROOM_BMP_NAME_LEN+1];		//����ͼƬ����
	uint16_t mwListCount;
	STRU_UC_CL_CRS_HOST_INFO *mpHostInfoList;
};

/*********************************************************************************************/
//��ҳ��ַ֪ͨ��600
//��;:
/*********************************************************************************************/
struct  STRU_UC_CL_CRS_HOST_INFO_ID600
{
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	STRU_UC_CL_CRS_HOST_INFO_ID600()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_HOST_INFO_ID600));
	}
	~STRU_UC_CL_CRS_HOST_INFO_ID600();
	int Serialize(CStandardSerialize & aoStandardSerialize);

	char macBgBmpName[CHATROOM_BMP_NAME_LEN+1];		//����ͼƬ����
	uint16_t mwListCount;
	uint16_t mwInnerPageListCount;
	STRU_UC_CL_CRS_HOST_INFO *mpHostInfoList;
	STRU_UC_CL_CRS_HOST_INFO *mpInnerPageList;		//��Ƕ��ҳ��Ϣ�б��ṹ����ҳ�б�һ��
};

/*********************************************************************************************/
//�û�״̬�ı�֪ͨ��390��
//��;:
/*********************************************************************************************/
//STRU_USER_OPERATE
struct	STRU_UC_CL_CRS_USER_STATE_CHG_ID_390         
{
	STRU_UC_CL_CRS_USER_STATE_CHG_ID_390()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_USER_STATE_CHG_ID_390));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	int Serialize(CStandardSerialize & aoStandardSerialize);

	int64_t		mi64UserId;			//�û�ID    STRU_USER_OPERATE::mi64SourceUserId
	uint16_t        mwChgType;			//���Ƶ�����	STRU_USER_OPERATE::mbyType
	uint8_t		mbyChgVal;          //���Ƶ�״̬ 0��ʾ��1��ʾ��		STRU_USER_OPERATE::mbyValue
};
//��ӣ� ����ΰ 2004��06��30 above

/*********************************************************************************************/
//�������û���Ϣ�ṹ
//�޸��ˣ�	HJH
//ʱ�䣺	2007��12��17
//���ݣ�	C:�������û���Ϣ�ṹ���汾2007�� ������������
/*********************************************************************************************/
struct	STRU_CHATROOM_USER_INFO_2007
{
	int64_t	mi64UserId;
	char	macNickName[NICK_NAME_LEN + 1];
	uint16_t	mwPhotoNum;
	uint8_t    mbyPower;					//�û�Ȩ��
	int    mlUserState;				//�û�״̬
	uint8_t	mbyVoiceState ;				//����ӣ���������״̬
	uint8_t	mbyUserLanguage;            //�û���������
	int		miRedMemTime;				//�����ʸ�
	int Serialize(CStandardSerialize & aoStandardSerialize);
	STRU_CHATROOM_USER_INFO_2007()
	{
		memset(this, 0, sizeof(STRU_CHATROOM_USER_INFO_2007));
	}
};
typedef	STRU_CHATROOM_USER_INFO_2007* PSTRU_CHATROOM_USER_INFO_2007 ;

/*********************************************************************************************/
//�������û���Ϣ
//�޸��ˣ�	HJH
//ʱ�䣺	2007��12��17
//���ݣ�	C:�������û���Ϣ���汾2007�� ʹ��2007���û���Ϣ
/*********************************************************************************************/
struct	STRU_UC_CL_CRS_USER_INFO_ID_2007
{
	int mlChatroomID;      //����id
	uint16_t mwUserCount;       //�û���
	PSTRU_CHATROOM_USER_INFO_2007 mpUserIDList;//�û���Ϣ�б�
	//STRU_UC_CL_CRS_USER_INFO_ID_2007();
	//int    Pack(char *   apBuffer ,int    alLen);
	//int    UnPack(char * apBuffer,int    alLen);
	int    Serialize(CStandardSerialize & aoStandardSerialize);

	STRU_UC_CL_CRS_USER_INFO_ID_2007()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_USER_INFO_ID_2007));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	~STRU_UC_CL_CRS_USER_INFO_ID_2007();
};
typedef	STRU_UC_CL_CRS_USER_INFO_ID_2007* PSTRU_UC_CL_CRS_USER_INFO_ID_2007;

/*********************************************************************************************/
//�������û���Ϣ�ṹ
//�޸��ˣ�	Fanyunfeng
//ʱ�䣺	2004��12��28
//���ݣ�	C:�������û���Ϣ�ṹ���汾400�� ������������
/*********************************************************************************************/
struct	STRU_CHATROOM_USER_INFO_400
{
	int64_t	mi64UserId;
	char	macNickName[NICK_NAME_LEN + 1];
	uint16_t	mwPhotoNum;
	uint8_t    mbyPower;					//�û�Ȩ��
	int    mlUserState;				//�û�״̬
	uint8_t	mbyVoiceState ;				//����ӣ���������״̬
	uint8_t	mbyUserLanguage;            //�û���������
	int Serialize(CStandardSerialize & aoStandardSerialize);

	STRU_CHATROOM_USER_INFO_400()
	{
		memset(this, 0, sizeof(STRU_CHATROOM_USER_INFO_400));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
};
typedef	STRU_CHATROOM_USER_INFO_400* PSTRU_CHATROOM_USER_INFO_400 ;

/*********************************************************************************************/
//�������û���Ϣ
//�޸��ˣ�	Fanyunfeng
//ʱ�䣺	2004��12��28
//���ݣ�	C:�������û���Ϣ���汾400�� ʹ��400���û���Ϣ
/*********************************************************************************************/
struct	STRU_UC_CL_CRS_USER_INFO_ID_400
{
	int mlChatroomID;      //����id
	uint16_t mwUserCount;       //�û���
	PSTRU_CHATROOM_USER_INFO_400 mpUserIDList;//�û���Ϣ�б�
	//STRU_UC_CL_CRS_USER_INFO_ID_400();
	//int    Pack(char *   apBuffer ,int    alLen);
	//int    UnPack(char * apBuffer,int    alLen);
	int    Serialize(CStandardSerialize & aoStandardSerialize);


	STRU_UC_CL_CRS_USER_INFO_ID_400()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_USER_INFO_ID_400));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
};
typedef	STRU_UC_CL_CRS_USER_INFO_ID_400* PSTRU_UC_CL_CRS_USER_INFO_ID_400;

/*********************************************************************************************/
//�������׻����ݰ�
//�޸��ˣ�	Fanyunfeng
//ʱ�䣺	2005��01��10
//���ݣ�	A:�׻�ʱʹ�õ����ݰ�
/*********************************************************************************************/
// $_CODE_CHANGE 2005-03-23 fyf �޸ģ����ṹ����
//STRU_USER_OPERATE
struct STRU_UC_CL_CRS_FLOWERS_ID
{
	int		mlChatroomID;		//����ID	
	int64_t		mi64DstUserID; 		//Ŀ���û�ID	STRU_USER_OPERATE::mi64DestUserId
	int64_t		mi64SrcUserID; 		//��Դ�û�ID	STRU_USER_OPERATE::mi64SourceUserId
	uint8_t		mbyIsPrivate;		//STRU_USER_OPERATE::mbyType
	int		mlFlowerType;		//STRU_USER_OPERATE::mlValue

	int    Serialize(CStandardSerialize & aoStandardSerialize);

	STRU_UC_CL_CRS_FLOWERS_ID()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_FLOWERS_ID));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
};

//*******************************************************************************************
//�������ұ������ݰ��������������
//����ˣ�����
//ʱ�䣺2008-06-12
//*******************************************************************************************
//STRU_USER_OPERATE
struct STRU_CL_CRS_OFFER_BROW_ID
{
	int64_t		mi64DstUserID; 		//Ŀ���û�ID	STRU_USER_OPERATE::mi64DestUserId
	int64_t		mi64SrcUserID; 		//��Դ�û�ID	STRU_USER_OPERATE::mi64SourceUserId
	uint8_t        mbyBrowType;        //0:������ 1:����	STRU_USER_OPERATE::mbyType
	uint8_t		mbyIsPrivate;		//���ġ�˽��״̬	STRU_USER_OPERATE::mbyValue
	uint16_t		mwOfferBrowLen;		//���鳤��
	char		macOfferBrowName[UC_NEW_OFFER_BROW_NAME_LEN + 1];//��������//STRU_USER_OPERATE::mpContent

	int    Serialize(CStandardSerialize & aoStandardSerialize);
	STRU_CL_CRS_OFFER_BROW_ID()
	{
		memset(this, 0, sizeof(STRU_CL_CRS_OFFER_BROW_ID));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
};

/*********************************************************************************************/
//�����ҹ���Ա���Ĵ���״̬���ݰ�
//�޸��ˣ�	Fanyunfeng
//ʱ�䣺	2005��01��10
//���ݣ�	A:����������״̬
/*********************************************************************************************/
//STRU_USER_OPERATE
struct STRU_UC_CL_CRS_HALL_STAT_CHG_ID
{
	int64_t 	mi64ManagerID;		//����ԱID		STRU_USER_OPERATE::mi64SourceUserId
	int		mlChatHallID;		//����ID
	//STRU_USER_OPERATE::mbyType
	uint16_t		mwProperty;			//0�׻�		
	//1����
	//2ֹͣ��Ƶת��  �Ѿ���ʹ��
	//STRU_USER_OPERATE::mbyValue
	int		mlNewValue;			//1	TRUE;	
	//0	FALSE;
	uint16_t   	mwOtherDataLen;		//STRU_USER_OPERATE::mlValue
	char   	mpzOthreData[256];	//STRU_USER_OPERATE::mpContent

	int    Serialize(CStandardSerialize & aoStandardSerialize);
	STRU_UC_CL_CRS_HALL_STAT_CHG_ID()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_HALL_STAT_CHG_ID));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
};

/*********************************************************************************************/
//����Աȡ��IP�б�����
//�޸��ˣ�	Fanyunfeng
//ʱ�䣺	2005��03��10
//���ݣ�	A:����������״̬
/*********************************************************************************************/
//STRU_USER_OPERATE
struct STRU_UC_CL_CRS_BLACKIP_LIST_RQ
{
	int64_t		mi64ManagerId;		//������ID		STRU_USER_OPERATE::mi64SourceUserId

	int Pack(char *   apBuffer ,int    alLen);
	int UnPack(char * apBuffer,int    alLen);
	int Serialize(CStandardSerialize & aoStandardSerialize);
	STRU_UC_CL_CRS_BLACKIP_LIST_RQ()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_BLACKIP_LIST_RQ));
	}
};

/*********************************************************************************************/
//��IP�б� Ӧ�����Ա���͵�STRU_UC_CL_CRS_BLACKIP_QUERY_RQ 
//�޸��ˣ�	Fanyunfeng
//ʱ�䣺	2005��03��10
//���ݣ�	A:����������״̬
/*********************************************************************************************/
struct STRU_UC_CL_CRS_BLACKIP_LIST_RS
{
	struct STRU_BLACK_IP_INFO
	{
		int64_t					mi64UserID;			//�û�ID
		unsigned int			mulIP;				//IP
		int   					mlNoComeInTime;		//����ʱ��
		int   					mlResidualTime;		//ʣ��ʱ��
		int Serialize(CStandardSerialize& aoStandardSerialize);
		STRU_BLACK_IP_INFO()
		{
			memset(this, 0, sizeof(STRU_BLACK_IP_INFO));
		}
	};
	typedef STRU_BLACK_IP_INFO* PSTRU_BLACK_IP_INFO ;

	int64_t						mi64ManagerId;		//������ID
	short						msCount;			//����������
	struct STRU_BLACK_IP_INFO *  mpBlackList;		//�������б�

	int Pack(char*   apBuffer,int    alLen);
	int UnPack(char* apBuffer,int    alLen);
	int Serialize(CStandardSerialize& aoStandardSerialize);
	STRU_UC_CL_CRS_BLACKIP_LIST_RS()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_BLACKIP_LIST_RS));
	}
	~STRU_UC_CL_CRS_BLACKIP_LIST_RS();
};

/*********************************************************************************************/
//�û�״̬����
//�޸��ˣ�	Fanyunfeng
//ʱ�䣺	2005��03��16
//���ݣ�	A
/*********************************************************************************************/
//STRU_USER_OPERATE
struct STRU_UC_CL_CRS_USER_STATE_RQ
{
	int64_t	mi64UserId;		//ָ�����û�ID		STRU_USER_OPERATE::mi64DestUserId

	int Pack(char*   apBuffer,int    alLen);
	int UnPack(char* apBuffer,int    alLen);
	int Serialize(CStandardSerialize& aoStandardSerialize);
	STRU_UC_CL_CRS_USER_STATE_RQ()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_USER_STATE_RQ));
	}
};

/*********************************************************************************************/
//�û�״̬Ӧ��
//�޸��ˣ�	Fanyunfeng
//ʱ�䣺	2005��03��16
//���ݣ�	A
/*********************************************************************************************/
//STRU_USER_OPERATE
struct STRU_UC_CL_CRS_USER_STATE_RS
{
	int64_t	mi64UserId;	//ָ�����û�ID		STRU_USER_OPERATE::mi64DestUserId
	int	mlState;	//�û�״̬			STRU_USER_OPERATE::mlValue

	int Pack(char*   apBuffer,int    alLen);
	int UnPack(char* apBuffer,int    alLen);
	int Serialize(CStandardSerialize& aoStandardSerialize);
	STRU_UC_CL_CRS_USER_STATE_RS()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_USER_STATE_RS));
	}
};
//********************************************** 500 *****************************************

/*********************************************************************************************/
//��״̬��Ϣ�б�
//��;����¼ʱ֪ͨ�ͻ���
/*********************************************************************************************/
struct STRU_UC_CL_CRS_MIC_INFO_LIST_ID
{
	//��״̬��Ϣ
	struct STRU_UC_CL_CRS_MIC_INFO
	{
		uint8_t	mbyOperateType;					//0		ADD
		//1		DELETE
		//2		UPDATE

		uint8_t	mbyMicIndex;

		bool				mbSupportVideo;		//֧����Ƶ
		STRU_AUDIO_CONFIG	mstruAudioConfig;	//��Ƶ������Ϣ
		STRU_VIDEO_CONFIG	mstruVideoConfig;	//��Ƶ������Ϣ

		uint16_t	mwMicStatue;    				//���״̬
		//��2λ:���Ƿ�� ��3λ:�Ƿ�ر���Ƶ ��4λ:�Ƿ񱻹��� ��6λ:�Ƿ�����Ÿ�
		//(����/ֹͣ �Ƿ�֧����Ƶ �Ƿ��ڹ���״̬) 
		uint16_t	mwMicTimeLen;  					//����ʱ��
		int64_t mi64ManagerID;  				//����ԱID
		int	mlDeltaSpeakTime;				//����ʱ�Ĳ�ֵ

		STRU_UC_CL_CRS_MIC_INFO()
		{
			memset(this, 0, sizeof(STRU_UC_CL_CRS_MIC_INFO));
		}
		int Serialize(CStandardSerialize& aoStandardSerialize);
	};

	uint16_t					mwMicCount;			//Mic����
	STRU_UC_CL_CRS_MIC_INFO *mpMicInfoList;		//�б�

	STRU_UC_CL_CRS_MIC_INFO_LIST_ID()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_MIC_INFO_LIST_ID));
	}
	~STRU_UC_CL_CRS_MIC_INFO_LIST_ID();
	int Pack(char*   apBuffer,int    alLen);
	int UnPack(char* apBuffer,int    alLen);
	int Serialize(CStandardSerialize& aoStandardSerialize);
};

/*********************************************************************************************/
//��ʼ����֪ͨ
//��;��������֪ͨ�û���ʼ����
/*********************************************************************************************/
//STRU_MIC_OPERATE
struct STRU_UC_CL_CRS_BEGIN_SPEAK_ID
{
	uint8_t	mbyMicIndex;	//Mic����	STRU_MIC_OPERATE::mbyIndex
	int64_t 	mi64UserID;		//�û�ID    STRU_MIC_OPERATE::mi64SourceUserId


	STRU_UC_CL_CRS_BEGIN_SPEAK_ID()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_BEGIN_SPEAK_ID));
	}
	int Pack(char* apBuffer,int alLen);
	int UnPack(char* apBuffer,int alLen);
	int Serialize(CStandardSerialize& aoStandardSerialize);
};

/*********************************************************************************************/
//�µĵ�¼��
//��;������ǰ�İ������û��İ汾
/*********************************************************************************************/
struct	STRU_UC_CL_CRS_LOGIN_HALL_RQ_500
{
	char	macVersion[VERSION_LEN + 1];		//
	int	mlHallID;							//����id
	int64_t	mi64UserId;							//�û�ID
	char	macNickName[NICK_NAME_LEN + 1];  	//�û��ǳ�
	uint16_t	mwPhotoNum;							//�û�ͷ��
	char	macPassword[UC_HALL_PWD_LEN + 1];	//����������
	uint8_t	mbySource;           				//��Դ
	int    mlUserState;						//�û�״̬ 0λ��ʾ��Ƶ״̬
	char	macUserPwd[MD5_LEN + 1];			//�û�����
	uint8_t	mbyUserLanguage; 					//�û���������
	//	0���������ģ�
	//	1���������ģ� 
	//	2��Ӣ��
	STRU_UC_CL_CRS_LOGIN_HALL_RQ_500()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_LOGIN_HALL_RQ_500));
	}
	int Pack(char* apBuffer,int alLen);
	int UnPack(char* apBuffer,int alLen);
	int Serialize(CStandardSerialize& aoStandardSerialize);
};

/*********************************************************************************************/
//��¼Ӧ���
//��;���µ�Ӧ���,�����������
/*********************************************************************************************/
struct STRU_UC_CL_CRS_LOGIN_HALL_RS_500
{
	uint8_t			mbyResult;							//0��ͬ��,�����Ǿܾ���
	int			mlHallID;							//����id
	int			mlRoomMaxPlayer;					//�����������	
	char			macErrInfo[ERR_BUF_LEN + 1];		//������Ϣ
	char			mszVoiceIp[64];						//������ת��IP
	unsigned short	musVoicePort;						//������ת�Ķ˿�
	char			macTopic[ UC_CHATROOM_TOPIC_LEN + 1 ] ;
	//�����ҵ�����
	char			macSalutatory[ UC_CHATROOM_SALUTATORY_LEN + 1 ] ;		
	//�����ҵĻ�ӭ��	
	char			macPwd[UC_HALL_PWD_LEN + 1];		//��������(ֻ���߹���Ա)
	char			macImvName[CHATROOM_IMV_NAME_LEN+1]; //�����ҳ���
	int			mlHallProperty;						//�������� From DataBase
	int			mlHallState;						//����״̬ Dynamic Data

	uint8_t			mbyMicNum;							//�������������

	STRU_UC_CL_CRS_LOGIN_HALL_RS_500()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_LOGIN_HALL_RS_500));
	}

	int Pack(char* apBuffer,int alLen);
	int UnPack(char* apBuffer,int alLen);
	int Serialize(CStandardSerialize& aoStandardSerialize);
};

struct STRU_UC_CL_CRS_LOGIN_HALL_RS_600
{
	unsigned int	mulToken;							//�û�Tokenֵ
	uint8_t			mbyResult;							//0��ͬ��,�����Ǿܾ���
	int			mlHallID;							//����id
	int			mlRoomMaxPlayer;					//�����������	
	char			macErrInfo[ERR_BUF_LEN + 1];		//������Ϣ
	char			mszVoiceIp[64];						//������ת��IP
	unsigned short	musVoicePort;						//������ת�Ķ˿�
	char			macTopic[ UC_CHATROOM_TOPIC_LEN + 1 ] ;
	//�����ҵ�����
	char			macSalutatory[ UC_CHATROOM_SALUTATORY_LEN + 1 ] ;		
	//�����ҵĻ�ӭ��	
	char			macPwd[UC_HALL_PWD_LEN + 1];		//��������(ֻ���߹���Ա)
	char			macImvName[CHATROOM_IMV_NAME_LEN+1]; //�����ҳ���
	int			mlHallProperty;						//�������� From DataBase
	int			mlHallState;						//����״̬ Dynamic Data

	uint8_t			mbyMicNum;							//�������������


	STRU_UC_CL_CRS_LOGIN_HALL_RS_600()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_LOGIN_HALL_RS_600));
	}
	int Pack(char* apBuffer,int alLen);
	int UnPack(char* apBuffer,int alLen);
	int Serialize(CStandardSerialize& aoStandardSerialize);
};

struct STRU_UC_CL_CRS_LOGIN_HALL_RS_2007
{
	unsigned int	mulToken;							//�û�Tokenֵ
	uint8_t			mbyResult;							//0��ͬ��,�����Ǿܾ���
	int			mlHallID;							//����id
	int			mlRoomMaxPlayer;					//�����������	
	char			macErrInfo[ERR_BUF_LEN + 1];		//������Ϣ
	char			mszVoiceIp[64];						//������ת��IP
	unsigned short	musVoicePort;						//������ת�Ķ˿�
	char			macTopic[ UC_CHATROOM_TOPIC_LEN + 1 ] ;
	//�����ҵ�����
	char			macSalutatory[ UC_CHATROOM_SALUTATORY_LEN + 1 ] ;		
	//�����ҵĻ�ӭ��	
	char			macPwd[UC_HALL_PWD_LEN + 1];		//��������(ֻ���߹���Ա)
	char			macImvName[CHATROOM_IMV_NAME_LEN+1]; //�����ҳ���
	int			mlHallProperty;						//�������� From DataBase
	int			mlHallState;						//����״̬ Dynamic Data

	uint8_t			mbyMicNum;							//�������������
	char			macWUserURL[ERR_BUF_LEN + 1];		//������Ϣ


	STRU_UC_CL_CRS_LOGIN_HALL_RS_2007()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_LOGIN_HALL_RS_2007));
	}

	int Pack(char* apBuffer,int alLen);
	int UnPack(char* apBuffer,int alLen);
	int Serialize(CStandardSerialize& aoStandardSerialize);
};

struct STRU_UC_CL_CRS_LOGIN_HALL_RS_2009
{
	unsigned int	mulToken;							//�û�Tokenֵ
	uint8_t			mbyResult;							//0��ͬ��,�����Ǿܾ���
	int			mlHallID;							//����id
	int			mlRoomMaxPlayer;					//�����������	
	char			macErrInfo[ERR_BUF_LEN + 1];		//������Ϣ
	char			mszVoiceIp[64];						//������ת��IP
	unsigned short	musVoicePort;						//������ת�Ķ˿�
	char			macTopic[ UC_CHATROOM_TOPIC_LEN + 1 ] ;
	//�����ҵ�����
	char			macSalutatory[ UC_CHATROOM_SALUTATORY_LEN + 1 ] ;		
	//�����ҵĻ�ӭ��	
	char			macPwd[UC_HALL_PWD_LEN + 1];		//��������(ֻ���߹���Ա)
	char			macImvName[CHATROOM_IMV_NAME_LEN+1]; //�����ҳ���
	int			mlHallState;						//����״̬ Dynamic Data

	uint8_t			mbyMicNum;							//�������������
	char			macWUserURL[ERR_BUF_LEN + 1];		//������Ϣ

	uint64_t           mi64HallProperty;					//�������� From DataBase

	STRU_UC_CL_CRS_LOGIN_HALL_RS_2009()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_LOGIN_HALL_RS_2009));
	}
	int Pack(char* apBuffer,int alLen);
	int UnPack(char* apBuffer,int alLen);
	int Serialize(CStandardSerialize& aoStandardSerialize);
};
/*********************************************************************************************/
//����Ա���������
//��;������Ա�����������
/*********************************************************************************************/
//STRU_MIC_OPERATE
struct STRU_UC_CL_CRS_MICROPHONE_MANAGER_RQ
{
	int64_t		mi64ManagerID;			//����ԱID	STRU_MIC_OPERATE::mi64SourceUserId
	//�������Ͷ���:1 ������:2������:3��׼������:4	STRU_MIC_OPERATE::mbyType
	uint16_t		mwType;					
	int64_t		mi64DesUserID;			//�������û�	STRU_MIC_OPERATE::mi64DestUserId
	uint8_t		mbyMicIndex;			//MicIndex		STRU_MIC_OPERATE::mbyIndex

	STRU_UC_CL_CRS_MICROPHONE_MANAGER_RQ()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_MICROPHONE_MANAGER_RQ));
	}
	int Pack(char* apBuffer,int alLen);
	int UnPack(char* apBuffer,int alLen);
	int Serialize(CStandardSerialize& aoStandardSerialize);
};

/*********************************************************************************************/
//����Ա����Ӧ���
//��;������Ա����Ĳ������
/*********************************************************************************************/
//STRU_MIC_OPERATE
struct STRU_UC_CL_CRS_MICROPHONE_MANAGER_RS
{
	int64_t		mi64ManagerID;			//����ԱID	STRU_MIC_OPERATE::mi64SourceUserId
	uint16_t		mwType;					//��������	STRU_MIC_OPERATE::mbyType
	uint8_t		mbyResult;				//1	TRUE	STRU_MIC_OPERATE::mbyResult
	int64_t		mi64DesUserID;			//�������û�	STRU_MIC_OPERATE::mi64DestUserId

	STRU_UC_CL_CRS_MICROPHONE_MANAGER_RS()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_MICROPHONE_MANAGER_RS));
	}
	int Pack(char* apBuffer,int alLen);
	int UnPack(char* apBuffer,int alLen);
	int Serialize(CStandardSerialize& aoStandardSerialize);
};

/*********************************************************************************************/
//����Ա����MIC
//��;���ı����״̬
/*********************************************************************************************/
//STRU_MIC_OPERATE
struct STRU_UC_CL_CRS_MIC_STATE_CONTROL_ID
{
	int64_t		mi64ManagerID;		//����ԱID	STRU_MIC_OPERATE::mi64SourceUserId
	uint8_t		mbyMicIndex;		//Mic������		STRU_MIC_OPERATE::mbyIndex
	//STRU_MIC_OPERATE::mbyType
	uint16_t		mbOperateType;		//1	��/�ر���	
	//2	�ر���Ƶ
	//3	��ʼ/��������Ա����
	//5 �Ƿ�������
	//STRU_MIC_OPERATE::mbState
	uint16_t		mwValue;			//0	FALSE
	//1	TRUE

	STRU_UC_CL_CRS_MIC_STATE_CONTROL_ID()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_MIC_STATE_CONTROL_ID));
	}
	int Pack(char* apBuffer,int alLen);
	int UnPack(char* apBuffer,int alLen);
	int Serialize(CStandardSerialize& aoStandardSerialize);
};

/*********************************************************************************************/
//�û��ı����״̬
//��;���û��ı����״̬
/*********************************************************************************************/
//STRU_MIC_OPERATE
struct STRU_UC_CL_CRS_USER_RECV_STATE_CHG_ID
{
	int64_t	mi64UserID;		//STRU_MIC_OPERATE::mi64SourceUserId
	uint8_t	mbyMicIndex;	//STRU_MIC_OPERATE::mbyIndex
	uint8_t	mbyMediaType;	//STRU_MIC_OPERATE::mbyType
	bool	mbyState;		//STRU_MIC_OPERATE::mbState

	STRU_UC_CL_CRS_USER_RECV_STATE_CHG_ID()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_USER_RECV_STATE_CHG_ID));
	}
	int Pack(char* apBuffer,int alLen);
	int UnPack(char* apBuffer,int alLen);
	int Serialize(CStandardSerialize& aoStandardSerialize);
};

/*********************************************************************************************/
//GGS���͵�Mic�������
//��;���ڴ�������ʱ֪ͨCRS
//**����GGSû��ʹ��������ݰ������Ϊ�ڲ��Ľṹ�� GGSFunc��CChatHall֮��ת����Ϣ
/*********************************************************************************************/
struct STRU_UC_GGS_CRS_MIC_PROPERTY_LIST_ID
{
	//Mic����
	struct STRU_UC_GGS_CRS_MIC_PROPERTY
	{
		uint8_t	mbyType;						//0		ADD
		//1		DELETE
		//2		UPDATE
		uint8_t mbyMicIndex;

		bool				mbSupportVideo;		//֧����Ƶ
		STRU_AUDIO_CONFIG	mstruAudioConfig;	//��Ƶ������Ϣ
		STRU_VIDEO_CONFIG	mstruVideoConfig;	//��Ƶ������Ϣ

		STRU_UC_GGS_CRS_MIC_PROPERTY()
		{
			memset(this,0, sizeof(STRU_UC_GGS_CRS_MIC_PROPERTY));
		}
		int	Serialize(CStandardSerialize& aoStandardSerialize);
	};

	int	mlHallId;							//����ID
	uint16_t	mwMicCount;
	STRU_UC_GGS_CRS_MIC_PROPERTY * mpMicProportyList;

	STRU_UC_GGS_CRS_MIC_PROPERTY_LIST_ID()
	{
		memset(this,0, sizeof(STRU_UC_GGS_CRS_MIC_PROPERTY_LIST_ID));
	}
	int Pack(char* apBuffer,int alLen);
	int UnPack(char* apBuffer,int alLen);
	int Serialize(CStandardSerialize& aoStandardSerialize);
};

/*********************************************************************************************/
//��¼��2007
//���ñ仯��¼�����
/*********************************************************************************************/


struct STRU_UC_CL_CRS_LOGIN_HALL_RQ_2007_INFO
{
	enum LoginAttributeType
	{
		AT_BYTE_REDMEMBER,      //���˱�ʶ
		AT_PCHAR_USERUNINAME,   //�û��ǳ�
		AT_PCHAR_USERMOOD,      //�û�����
		AT_PCHAR_USERIMAGEURL,  //�û�ͷ��URL
		AT_BYTE_USERSEX,        //�û��Ա�
		AT_INT_USER_ONLINETIME, //�û�����ʱ��
		AT_INT_USER_CHARM,      //�û�����ֵ
		AT_INT_USER_WEALTH,     //�û��Ƹ�ֵ
		AT_INT_USER_ACTIVITY,   //�û���Ծ��
		AT_INT_VIP_ROOMID,      //�û�VIP��������ID
		AT_BYTE_SHOW_BAR,       //�û�����û���ʶ
		AT_PCHAR_BIRTHDAY,      //�û�����
		AT_BYTE_SHOP_USER,      //�û���ͨ�̳��û���ʶ
		AT_PCHAR_MAC,			//MAC��ַ
		AT_INT_USER_PEER_LEVEL, //���弶��
		AT_INT_USER_SELLER,     //�ٷ�����
        AT_PCHAR_MACHINE_CODE,
		ATTRIBUTETYPE_MAX       //�û����Խ�����
	};

	int					 menumAttributeType;	//��������
	int					 mnDateLen;
	char*				 mPbVal;

	int		Serialize(CStandardSerialize & aoStandardSerialize);
	STRU_UC_CL_CRS_LOGIN_HALL_RQ_2007_INFO();
};

struct	STRU_UC_CL_CRS_LOGIN_HALL_RQ_2007
{
	char	macVersion[VERSION_LEN + 1];		//
	int	mlHallID;							//����id
	int64_t	mi64UserId;							//�û�ID
	char	macNickName[NICK_NAME_LEN + 1];  	//�û��ǳ�
	uint16_t	mwPhotoNum;							//�û�ͷ��
	char	macPassword[UC_HALL_PWD_LEN + 1];	//����������
	uint8_t	mbySource;           				//��Դ
	int    mlUserState;						//�û�״̬ 0λ��ʾ��Ƶ״̬
	char	macUserPwd[MD5_LEN + 1];			//�û�����
	uint8_t	mbyUserLanguage; 					//�û���������
	//	0���������ģ�
	//	1���������ģ� 
	//	2��Ӣ��

	uint8_t    mbyAttributeCount;					//�������Ը���
	STRU_UC_CL_CRS_LOGIN_HALL_RQ_2007_INFO *mpAttributeInfo;

	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	int    Serialize(CStandardSerialize & aoStandardSerialize);
	STRU_UC_CL_CRS_LOGIN_HALL_RQ_2007 ()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_LOGIN_HALL_RQ_2007));
	}
	~STRU_UC_CL_CRS_LOGIN_HALL_RQ_2007();
};
//---------------------------UDP---------------------------
struct STRU_UC_CL_CRS_UDPFIRSTLOGIN_RQ
{
	int64_t 	mi64UserID;		//�û�ID
	STRU_UC_CL_CRS_UDPFIRSTLOGIN_RQ();
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	int    Serialize(CStandardSerialize & aoStandardSerialize);
};

//�ͻ��˵�¼�����з��������ظ��ͻ��˵ĵ�һ�����ݰ��ṹ
struct STRU_UC_CL_CRS_UDPFIRSTLOGIN_RS
{
	int64_t 	mi64UserID;		//�û�ID
	int	mlHallID;       //����ID
	unsigned int mulToken; //�û�����
	STRU_UC_CL_CRS_UDPFIRSTLOGIN_RS();
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	int    Serialize(CStandardSerialize & aoStandardSerialize);
};

//�ͻ��˵�¼�����з��ĵ�һ�����ݰ��ṹ
struct STRU_UC_CL_CRS_LOGIN_INFO_RQ
{
	int64_t	mi64UserId;	     //�û�ID
	int		muLoginPhase;	//��¼�׶�
	STRU_UC_CL_CRS_LOGIN_INFO_RQ();
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	int    Serialize(CStandardSerialize & aoStandardSerialize);
};
struct STRU_UC_CL_CRS_LOGIN_INFO_RS
{
	int64_t	mi64UserId;	     //�û�ID
	int		muLoginPhase;	//��¼�׶�
	STRU_UC_CL_CRS_LOGIN_INFO_RS();
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	int    Serialize(CStandardSerialize & aoStandardSerialize);
};
//keep live  �ͻ��˷��������������ݰ��ṹ
struct STRU_UC_CL_CRS_ALIVE_RQ 
{
	int64_t mi64UserID;					//�û���UC��
	int  mlHallID;						//����ID
	STRU_UC_CL_CRS_ALIVE_RQ()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_ALIVE_RQ));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	int    Serialize(CStandardSerialize & aoStandardSerialize);
};

//keep live ���������ظ��ͻ��˵����ݰ��ṹ
struct STRU_UC_CL_CRS_ALIVE_RS
{
	int64_t 	mi64UserID;					//�û���UC��
	int	mlHallID;						//����ID
	int64_t	mi64LastTime;					//������ʱ��
	STRU_UC_CL_CRS_ALIVE_RS();
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	int    Serialize(CStandardSerialize & aoStandardSerialize);
};
//�Ƴ�����
struct STRU_UC_CL_CRS_LOGOUT
{
	int64_t mi64UserID;					//�û���UC��
	int  mlHallID;						//����ID
	STRU_UC_CL_CRS_LOGOUT();
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	int    Serialize(CStandardSerialize & aoStandardSerialize);
};

struct STRU_UC_CL_CRS_LOGOUT_RS 
{
	int64_t mi64UserID;					//�û���UC��
	int  mlHallID;						//����ID
	int   miErrorCode;                  //������
	char  mszErrorInfo[ERROR_BUFFER_LENGTH + 1];//������Ϣ
	STRU_UC_CL_CRS_LOGOUT_RS();
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	int Serialize(CStandardSerialize & aoStandardSerialize);
};
//---------------------------------------UDP----------------------------------------------

struct STRU_UC_CL_CRS_SPEAKER_INFO_LIST_ID
{
	//��������Ϣ
	struct STRU_UC_CL_CRS_SPEAKER_INFO
	{
		int64_t			mi64DstUserID;				//0		�����û�
		//		˽�ĵ��û�ID
		uint8_t 			mbyMicIndex;				//ʹ�õ�MicIncex
		int64_t			mi64SpeakerUserID;			//�����û�ID

		bool			mbContainAudioInfo;			//������Ƶ��ʽ
		STRU_AUDIO_INFO	mstrAudioInfo;				//����ı�ʶΪ����������Ƶ��ʽ

		bool			mbContainVideoInfo;			//������Ƶ��Ϣ
		STRU_VIDEO_INFO	mstrVideoInfo;				//����ı�ʶΪ����������Ƶ��ʽ��Ϣ

		STRU_UC_CL_CRS_SPEAKER_INFO()
		{
			memset(this, 0, sizeof(STRU_UC_CL_CRS_SPEAKER_INFO));
		}
		int Serialize(CStandardSerialize& aoStandardSerialize);
	};

	uint8_t							mbySpeakerNum;
	STRU_UC_CL_CRS_SPEAKER_INFO* 	mpSpeakerUserInfo;

	STRU_UC_CL_CRS_SPEAKER_INFO_LIST_ID()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_SPEAKER_INFO_LIST_ID));
	}
	~STRU_UC_CL_CRS_SPEAKER_INFO_LIST_ID();
	int Pack(char* apBuffer,int alLen);
	int UnPack(char* apBuffer,int alLen);
	int Serialize(CStandardSerialize& aoStandardSerialize);
};
//
struct	STRU_CHATROOM_USER_INFO_2008
{
	int64_t	mi64UserId;
	char	macNickName[NICK_NAME_LEN + 1];
	uint16_t	mwPhotoNum;
	uint8_t    mbyPower;					//�û�Ȩ��
	int    mlUserState;				//�û�״̬
	uint8_t	mbyVoiceState ;				//����ӣ���������״̬
	uint8_t	mbyUserLanguage;            //�û���������
	int		miRedMemTime;				//�����ʸ�
	int Serialize(CStandardSerialize & aoStandardSerialize);

	STRU_CHATROOM_USER_INFO_2008()
	{
		memset(this, 0, sizeof(STRU_CHATROOM_USER_INFO_2008));
	}

};
typedef	STRU_CHATROOM_USER_INFO_2008* PSTRU_CHATROOM_USER_INFO_2008 ;

struct	STRU_UC_CL_CRS_USER_INFO_ID_2008
{
	int mlChatroomID;      //����id
	uint16_t mwUserCount;       //�û���
	PSTRU_CHATROOM_USER_INFO_2008 mpUserIDList;//�û���Ϣ�б�
	//STRU_UC_CL_CRS_USER_INFO_ID_2007();
	//int    Pack(char *   apBuffer ,int    alLen);
	//int    UnPack(char * apBuffer,int    alLen);
	int    Serialize(CStandardSerialize & aoStandardSerialize);
	STRU_UC_CL_CRS_USER_INFO_ID_2008()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_USER_INFO_ID_2008));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
};
typedef	STRU_UC_CL_CRS_USER_INFO_ID_2008* PSTRU_UC_CL_CRS_USER_INFO_ID_2008;

//�û����������Ϣ
struct	STRU_USER_ID_LIST_RQ_2008
{
	int miUserCount;  //�û�����
	int64_t mvUserIdList[MAX_USER_ID_NUM];//�û�ID �б� 

	int    Serialize(CStandardSerialize & aoStandardSerialize);
	STRU_USER_ID_LIST_RQ_2008()
	{
		memset(this, 0, sizeof(STRU_USER_ID_LIST_RQ_2008));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
};

//�û��������ʱ�������˵�֪ͨ��
//mwVersion !=0ʱ����ʾ��
struct	STRU_UC_CL_CRS_ENTRY_OTHERUSER_ID_SINASHOW2008
{
	int	mlChatroomID;				//����id
	int64_t	mi64UserID;					//�û�ID
	char macNickName[NICK_NAME_LEN + 1];//�û��ǳ�
	uint16_t mwPhotoNum;					//�û�ͷ��
	uint8_t mbyPower;						//�û�Ȩ��
	int mlUserState;					//�û�״̬

	uint8_t mbyUserLanguage; 				//�û���������
	int	 miRedMemTime;					//�����ʸ�
	uint16_t mwVersion;						//�û����� 

	STRU_UC_CL_CRS_ENTRY_OTHERUSER_ID_SINASHOW2008();
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	int Serialize(CStandardSerialize & aoStandardSerialize);
};

//////////////////////////////////////////////
//�û���¼ʱ�յ��Ĵ����û��б��
typedef struct	STRU_CHATROOM_USER_INFO_SINASHOW_2008
{
	int64_t	mi64UserId;
	char	macNickName[NICK_NAME_LEN + 1];
	uint16_t	mwPhotoNum;
	uint8_t    mbyPower;					//�û�Ȩ��
	int    mlUserState;				//�û�״̬
	uint8_t	mbyVoiceState ;				//����ӣ���������״̬
	uint8_t	mbyUserLanguage;            //�û���������
	int		miRedMemTime;				//�����ʸ�
	int		mwVersion;					//�û�����
	int	mlUserHallID; 
	int Serialize(CStandardSerialize & aoStandardSerialize);
	STRU_CHATROOM_USER_INFO_SINASHOW_2008()
	{
		memset(this, 0, sizeof(STRU_CHATROOM_USER_INFO_SINASHOW_2008));
	}

}*PSTRU_CHATROOM_USER_INFO_SINASHOW_2008;

//////////////////////////////////////////////////////////////////////////
typedef struct	STRU_CHATROOM_USER_INFO_SINASHOW_2009
{
	int64_t	mi64UserId;
	char	macNickName[NICK_NAME_LEN + 1];
	uint16_t	mwPhotoNum;
	uint8_t  	mbyPower;					//�û�Ȩ��
	int  	mlUserState;				//�û�״̬
	uint8_t	mbyVoiceState ;				//����ӣ���������״̬
	uint8_t	mbyUserLanguage;			//�û���������
	uint16_t	mwTypeLen;					//���͸���
	uint8_t*	pmByteUserLevel;				//�û�����#
	int*	pmlUserTime;					//����ʱ��#
	int		mwVersion;					//�û�����
	int	mlUserHallID;				//�û����ڵĴ���ID
	int Serialize(CStandardSerialize & aoStandardSerialize);
	STRU_CHATROOM_USER_INFO_SINASHOW_2009()
	{
		memset(this, 0, sizeof(STRU_CHATROOM_USER_INFO_SINASHOW_2009));
	}
}* PSTRU_CHATROOM_USER_INFO_SINASHOW_2009;

//RSA����
struct STRU_RSA_INFO_RQ
{
	int		nLen;							//��Կ����
	uint8_t*	mszPublicKey;					//��Կ
	int		nType;							//���ܲ���
	int64_t 	mi64UserID;						//�û�ID
	int		nSize;							//ԭʼ��Կ����
	int Serialize(CStandardSerialize & aoStandardSerialize);
	STRU_RSA_INFO_RQ()
	{
		memset(this, 0, sizeof(STRU_RSA_INFO_RQ));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
};

//RSAӦ��
struct STRU_RSA_INFO_RS
{
	int		nLen;							//��Կ����
	uint8_t*	mszPublicKey;					//��Կ
	int		nType;							//���ܲ���
	int64_t 	mi64UserID;						//�û�ID
	int		nSize;							//ԭʼ��Կ����
	uint8_t	byRet;							//���
	int Serialize(CStandardSerialize & aoStandardSerialize);
	STRU_RSA_INFO_RS()
	{
		memset(this, 0, sizeof(STRU_RSA_INFO_RS));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
};

//�ӽ���
struct STRU_ENDECRYPT_FUN
{
	int		nLen;							//���ĳ���
	char *	mszEncrypt;						//����

	int Serialize(CStandardSerialize & aoStandardSerialize);
	STRU_ENDECRYPT_FUN()
	{
		memset(this, 0, sizeof(STRU_ENDECRYPT_FUN));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
};

//////////////////////////////////////////////////////////////////////////

//����֪ͨ�� 
typedef struct STRU_UC_CL_CRS_INSERT_MIC_ID	
{
	int64_t mi64ManagerID;	//����ԱID
	int64_t mi64UserId;		//�������ID
	uint8_t mbyIndex;			//�����λ��
	int Serialize(CStandardSerialize & aoStandardSerialize);
	STRU_UC_CL_CRS_INSERT_MIC_ID()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_INSERT_MIC_ID));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
}*PSTRU_UC_CL_CRS_INSERT_MIC_ID;


//SinaShow1.3���¼ӵ�
struct STRU_UC_CL_CRS_ENTRY_OTHERUSER_ID_2009
{
	int 	mlChatroomID;						//����id
	int64_t	mi64UserID; 						//�û�ID
	char 	macNickName[NICK_NAME_LEN + 1];		//�û��ǳ�
	uint16_t 	mwPhotoNum;							//�û�ͷ��
	uint8_t 	mbyPower;							//�û�Ȩ��
	int 	mlUserState;						//�û�״̬

	uint8_t 	mbyUserLanguage;					//�û���������
	int  	miRedMemTime;						//�����ʸ�

	char 	mstrUniName[DEF_USER_UNINAME_LEN+1];//�û�ͳһ��Ա��
	char 	mstrUserMood[DEF_USER_MOOD_LENGTH+1];  //�û�����
	char 	mstrUserImageURL[URL_LINK_LEN+1];  	//�û�ͷ��汾��
	uint8_t    mbyUserSex;           				//�û��Ա�0-δ֪��1-�У�2-Ů
	int 	miUserOnLineTime;					//�û��ȼ�������ʱ������λΪ�룬
	int 	miUserCharm;       				    //�û�����ֵ
	int 	miUserWealth;       				//�û��Ƹ�ֵ
	int 	miUserActivity;    				    //�û���Ծ��
	int    mlVipRooomID;      					//�û��Ƿ���VIP������0-����VIP������ ����ֵ��VIP������������ֵΪ����VIP����ID��
	uint8_t    mbyShowBar;          				//�û��Ƿ�������û���0-���ǣ�������
	char  mstrUserBirthDay[DEF_USER_BIRTHDAY_LEN+1]; //�û����� 
	//uint8_t    mbyShopUser;          				//�û��Ƿ����̳��û���0-���ǣ�������

	int	Serialize(CStandardSerialize & aoStandardSerialize);	
	STRU_UC_CL_CRS_ENTRY_OTHERUSER_ID_2009()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_ENTRY_OTHERUSER_ID_2009));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
};

//�ͻ��������û���ϢӦ���(SinaShow1.3)
typedef struct	STRU_CHATROOM_USER_INFO_2009
{
	int64_t	mi64UserId;
	char	macNickName[NICK_NAME_LEN + 1];
	uint16_t	mwPhotoNum;
	uint8_t    mbyPower;							//�û�Ȩ��
	int    	mlUserState;						//�û�״̬
	uint8_t	mbyVoiceState ;						//����ӣ���������״̬
	uint8_t	mbyUserLanguage;           			//�û���������
	int		miRedMemTime;						//�����ʸ�
	//char	macVersion[VERSION_LEN + 1];		//�ͻ�����ʵ�汾
	char 	mstrUniName[DEF_USER_UNINAME_LEN+1];//�û�ͳһ��Ա��
	char 	mstrUserMood[DEF_USER_MOOD_LENGTH+1];  //�û�����
	char 	mstrUserImageURL[URL_LINK_LEN+1];  	//�û�ͷ��汾��
	uint8_t    mbyUserSex;           				//�û��Ա�0-δ֪��1-�У�2-Ů
	int 	miUserOnLineTime;					//�û��ȼ�������ʱ������λΪ�룬
	int 	miUserCharm;       				//�û�����ֵ
	int 	miUserWealth;       				//�û��Ƹ�ֵ
	int		miUserActivity;    				//�û���Ծ��
	int    mlVipRooomID;      					//�û��Ƿ���VIP������0-����VIP������ ����ֵ��VIP������������ֵΪ����VIP����ID��
	uint8_t   	mbyShowBar;          				//�û��Ƿ�������û���0-���ǣ�������
	char    mstrUserBirthDay[DEF_USER_BIRTHDAY_LEN+1]; //�û�����      //�û������ַ�����2009-07-01��
	//uint8_t   	mbyShopUser;          				//�û��Ƿ����̳��û���0-���ǣ�������

	int 	Serialize(CStandardSerialize & aoStandardSerialize);
	STRU_CHATROOM_USER_INFO_2009()
	{
		memset(this, 0, sizeof(STRU_CHATROOM_USER_INFO_2009));
	}
}*PSTRU_CHATROOM_USER_INFO_2009;

typedef struct	STRU_UC_CL_CRS_USER_INFO_ID_2009
{
	int		mlChatroomID;      					//����id

	uint16_t 	mwUserCount;       					//�û���
	PSTRU_CHATROOM_USER_INFO_2009 mpUserIDList;	//�û���Ϣ�б�

	int    Serialize(CStandardSerialize & aoStandardSerialize);
	~STRU_UC_CL_CRS_USER_INFO_ID_2009();
	STRU_UC_CL_CRS_USER_INFO_ID_2009()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_USER_INFO_ID_2009));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
}PSTRU_UC_CL_CRS_USER_INFO_ID_2009;

//����Ƶ���������
typedef struct STRU_UC_CL_CRS_GIFT_PROP_USE_RQ
{
	int64_t mi64UserID; //�û�ID
	int64_t mi64DestID; //ʹ��Ŀ���û�ID
	int     miContentID;//����ID
	char    mszContentName[DEF_CONTENT_NAME_LEN+1];//��������
	int     miUseCount;//ʹ������

	int    Serialize(CStandardSerialize & aoStandardSerialize);
	STRU_UC_CL_CRS_GIFT_PROP_USE_RQ()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_GIFT_PROP_USE_RQ));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
}STRU_UC_CL_CRS_GIFT_PROP_USE_RQ,*PSTRU_UC_CL_CRS_GIFT_PROP_USE_RQ;

//����Ƶ����Ӧ���
typedef struct STRU_UC_CL_CRS_GIFT_PROP_USE_RS
{
	uint8_t mbyResult; //�ɹ���ʧ��
	int64_t mi64UserID; //�û�ID
	int64_t mi64DestID; //ʹ��Ŀ���û�ID
	int     miContentID;//����ID
	char    mszContentName[DEF_CONTENT_NAME_LEN+1];//��������
	int     miUseCount;//ʹ������
	int     miResidualValue;//ʣ������ 

	int    Serialize(CStandardSerialize & aoStandardSerialize);
	STRU_UC_CL_CRS_GIFT_PROP_USE_RS()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_GIFT_PROP_USE_RS));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
}STRU_UC_CL_CRS_GIFT_PROP_USE_RS,*PSTRU_UC_CL_CRS_GIFT_PROP_USE_RS;

//����Ƶ���߹㲥��
typedef struct STRU_UC_CL_CRS_GIFT_PROP_USE_NOTIFY
{
	int64_t mi64UserID; //�û�ID
	int64_t mi64DestID; //ʹ��Ŀ���û�ID
	int     miContentID;//����ID
	char    mszContentName[DEF_CONTENT_NAME_LEN+1];//��������
	int     miUseCount;//ʹ������

	int     miRecvCount; //Ŀ���û��յ��˵��ߵ�����
	int     miPackMark;  //����ʶ���漴����
	int     miPackBeginNum;  //����ʼ��
	int     miPackUseNum;  //��ʹ����

	char    mszUserName[NICK_NAME_LEN+1]; //�û�����
	char    mszDestName[NICK_NAME_LEN+1]; //Ŀ���û�����

	int    Serialize(CStandardSerialize & aoStandardSerialize);
	STRU_UC_CL_CRS_GIFT_PROP_USE_NOTIFY()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_GIFT_PROP_USE_NOTIFY));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
}STRU_UC_CL_CRS_GIFT_PROP_USE_NOTIFY,*PSTRU_UC_CL_CRS_GIFT_PROP_USE_NOTIFY;

//������㲥��
typedef struct STRU_UC_CL_CRS_BIG_GIFT_PROP_USE_NOTIFY
{
	int64_t 		mi64UserID; //�û�ID
	char    	    mszUserName[NICK_NAME_LEN+1];//�û�����
	int64_t 		mi64DestID; //ʹ��Ŀ���û�ID
	char    	    mszDestName[NICK_NAME_LEN+1];//Ŀ���û�����
	int        	    miContentID;//����ID
	char    	    mszContentName[DEF_CONTENT_NAME_LEN+1];//��������
	int       	    miUseCount;	//����ʹ������	
	int 		    mlChatroomID;		//����id
	char		    mstruRoomName[HALL_NAME_LEN+1];  //��������		
	int			    mstruTimeStamp; //00:00:00 UTC, January 1, 1970

	int             miHallIP;      //����IP
	short           miHallPort;      //����PORT
	int             miHallProperty;     //��������
	int             miHallPropertyEx;    //������չ����

	uint8_t     mbyShowStar;     //���Ǽ���1~6����0Ϊ������
	uint8_t     mbyNobleman;     //���弶��1~3����0Ϊ�ǹ���
	uint8_t     mbyManager;      //����Ա����
	uint8_t     mbyWeekStar;     //���ǣ� 0Ϊ������
	uint8_t     mbySell;      //�ٷ����ۣ�0�������ۣ�1������
	uint8_t     mbyDstShowStar;     //Ŀ���û����Ǽ���1~6����0Ϊ������
	uint8_t     mbyDstNobleman;     //Ŀ���û����弶��1~3����0Ϊ�ǹ���
	uint8_t     mbyDstManager;     //Ŀ���û�����Ա����
	uint8_t     mbyDstWeekStar;     //Ŀ���û����ǣ� 0Ϊ������
	uint8_t     mbyDstSell;      //Ŀ���û��ٷ����ۣ�0�������ۣ�1������

	int             miReserved1;     //Ԥ��1
	int             miReserved2;     //Ԥ��2

	int Serialize(CStandardSerialize & aoStandardSerialize);
	STRU_UC_CL_CRS_BIG_GIFT_PROP_USE_NOTIFY()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_BIG_GIFT_PROP_USE_NOTIFY));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
}STRU_UC_CL_CRS_BIG_GIFT_PROP_USE_NOTIFY,*PSTRU_UC_CL_CRS_BIG_GIFT_PROP_USE_NOTIFY;

//U�����֪ͨ
typedef struct STRU_UC_CRS_CL_BALANCE_NOTIFY
{
	int64_t 		mi64UserID;        //�û�ID
	int         miResidualValue;   //���ڵ�U����
	uint8_t        mbyUseType;        // 0��ʹ�õ���  1���յ����� 
	int         miSecond;          // ʱ�� ����

	int Serialize(CStandardSerialize & aoStandardSerialize);
	STRU_UC_CRS_CL_BALANCE_NOTIFY()
	{
		memset(this, 0, sizeof(STRU_UC_CRS_CL_BALANCE_NOTIFY));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
}STRU_UC_CRS_CL_BALANCE_NOTIFY,*PSTRU_UC_CRS_CL_BALANCE_NOTIFY;

//��С���ȹ㲥����֪ͨ��
typedef struct STRU_UC_CRS_CL_LOUDSPEAKER_NOTIFY
{
	int64_t		mi64FromUserID;					//�û�ID
	char		mszUserName[NICK_NAME_LEN + 1]; //�û�����
	int64_t		mi64ToUserID;					//Ŀ���û�ID
	char		mszDestName[NICK_NAME_LEN + 1]; //Ŀ���û�����
	uint8_t		mbyType;						//�������� 4:С���� 5:�����ȣ�1~3δʹ��

	uint8_t		mbyShowStar;					//���Ǽ���1~6����0Ϊ������
	uint8_t		mbyNobleman;					//���弶��1~3����0Ϊ�ǹ���
	uint8_t		mbyManager;						//����Ա����
	uint8_t		mbyWeekStar;					//���ǣ�1~3����
	uint8_t		mbySell;						//�ٷ����ۣ�0�������ۣ�1������

	uint16_t	    mwMessageLen;					//��Ϣ����	


	STRU_UC_CL_CRS_CHAT_INFO mChatInfo;

	int Serialize(CStandardSerialize & aoStandardSerialize);
	STRU_UC_CRS_CL_LOUDSPEAKER_NOTIFY()
	{
		memset(this, 0, sizeof(STRU_UC_CRS_CL_LOUDSPEAKER_NOTIFY));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
}STRU_UC_CRS_CL_LOUDSPEAKER_NOTIFY,*PSTRU_UC_CRS_CL_LOUDSPEAKER_NOTIFY;

//��С����Ӧ���
typedef struct STRU_UC_CRS_CL_LOUDSPEAKER_NOTIFY_RS
{
	uint8_t 	mbyResult; 	//�ɹ���ʧ��

	int Serialize(CStandardSerialize & aoStandardSerialize);

	STRU_UC_CRS_CL_LOUDSPEAKER_NOTIFY_RS()
	{
		memset(this, 0, sizeof(STRU_UC_CRS_CL_LOUDSPEAKER_NOTIFY_RS));
	}
	int  Pack(char *   apBuffer ,int    alLen);
	int  UnPack(char * apBuffer,int    alLen);
}STRU_UC_CRS_CL_LOUDSPEAKER_NOTIFY_RS,*PSTRU_UC_CRS_CL_LOUDSPEAKER_NOTIFY_RS;


//��С����Ӧ����չ��
typedef struct STRU_UC_CRS_CL_LOUDSPEAKER_NOTIFY_RS_EX
{
	uint8_t	m_nResult; 			//1:�ɹ�,����:ʧ��
	char	m_szReason[100];	//ʧ�ܵ�ԭ��
	int Serialize(CStandardSerialize & aoStandardSerialize);
	STRU_UC_CRS_CL_LOUDSPEAKER_NOTIFY_RS_EX()
	{
		memset(this, 0, sizeof(STRU_UC_CRS_CL_LOUDSPEAKER_NOTIFY_RS_EX));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
}STRU_UC_CRS_CL_LOUDSPEAKER_NOTIFY_RS_EX,*PSTRU_UC_CRS_CL_LOUDSPEAKER_NOTIFY_RS_EX;

// ���˵��߹㲥��
typedef struct _STRU_UC_CL_CRS_AWARD_NOTIFY 
{
	int32_t        m_nPackMark;       // ����־
	int64_t    m_i64UserID;       // ���û���ID
	char       m_szUserName[NICK_NAME_LEN + 1];//�û�����
	int32_t        m_nContentID;   // ����ID
	int32_t        m_nMaxTimes;       // �����

	int32_t        m_nExtraDataCount;     // m_pExtraData����ĳ���

	struct STRU_EXTRA_DATA
	{
		int32_t        m_nIndex;          // �н���������������
		int32_t        m_nTimes;          // ��ǰ�н�����
		int64_t    m_i64GainPoint;    // ������U��ֵ
	}*m_pExtraData;

	int Serialize(CStandardSerialize & StandardSerialize);
	_STRU_UC_CL_CRS_AWARD_NOTIFY()
	{
		memset(this, 0, sizeof(_STRU_UC_CL_CRS_AWARD_NOTIFY));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);

}STRU_UC_CL_CRS_AWARD_NOTIFY, *PSTRU_UC_CL_CRS_AWARD_NOTIFY;

// ���˵���ͳ����Ϣ��  2011-03-10 ���
typedef struct STRU_UC_CL_CRS_AWARD_INFO 
{
	int32_t        miPackMark; //����ʶ
	int64_t      mi64UserID;       // ���û���ID
	char       mszUserName[NICK_NAME_LEN + 1];//�û�����
	int32_t        miContentID;   // ����ID
	int32_t        miMaxTimes;       // �����
	int32_t        miExtraDataCount;

	struct STRU_EXTRA_DATA
	{
		int32_t        miMultiple;          //����
		int32_t        miTimes;             //����
	}*m_pExtraData;
	int Serialize(CStandardSerialize & aoStandardSerialize);
	STRU_UC_CL_CRS_AWARD_INFO()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_AWARD_INFO));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
}STRU_UC_CL_CRS_AWARD_INFO,*PSTRU_UC_CL_CRS_AWARD_INFO;

// �̻����߹㲥��
typedef struct _STRU_UC_CL_CRS_FIREWORKS_NOTIFY 
{
	int64_t     m_i64UserID;       // �����û���ID
	char        m_szUserName[NICK_NAME_LEN + 1];//�û�����
	int32_t         m_nContentID;   // ����ID
	int32_t         m_nUseCount;      // ʹ������
	int64_t     m_i64GainPoint;    // ������U��ֵ

	int Serialize(CStandardSerialize & StandardSerialize);
	_STRU_UC_CL_CRS_FIREWORKS_NOTIFY()
	{
		memset(this, 0, sizeof(_STRU_UC_CL_CRS_FIREWORKS_NOTIFY));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);

}STRU_UC_CL_CRS_FIREWORKS_NOTIFY, *PSTRU_UC_CL_CRS_FIREWORKS_NOTIFY;

//VIP�û���Ϣ֪ͨ��
typedef struct STRU_UC_CL_VIP_ENTER_NOTIFY_EX
{
	unsigned char mui8VIPType;             //�ݶ���0Ϊ���壬1Ϊ���� 2Ϊ�ٷ�����
	unsigned char mui8NotifyType;          //0Ϊ�½����û���1Ϊ��������û�
	int64_t       mi64UserID;                //�û�ID��
	unsigned int mui32Reserve;             //�����ֶ�1����mui8VIPTypeΪ1ʱ�����ﱣ�����ID��
	//��mui8VIPTypeΪ0ʱ�����ﱣ�����ȼ�
	unsigned int mui32Reserve2;            //�����ֶ�2,
	unsigned int mui32Reserve3;            //�����ֶ�2��Ϊ0
	int    Serialize(CStandardSerialize & aoStandardSerialize);
	STRU_UC_CL_VIP_ENTER_NOTIFY_EX()
	{
		memset(this, 0, sizeof(STRU_UC_CL_VIP_ENTER_NOTIFY_EX));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
}*PSTRU_UC_CL_VIP_ENTER_NOTIFY_EX;

struct STRU_UC_CL_CRS_USER_AVSINFO_ID
{
	char mszAvsName[UC_HALL_AVS_NAME_LEN+1];
	unsigned int	miAvsIp;
	unsigned short	miVoicePort;
	STRU_UC_CL_CRS_USER_AVSINFO_ID();
	~STRU_UC_CL_CRS_USER_AVSINFO_ID();
	int Serialize(CStandardSerialize & aoStandardSerialize);
};

//AVS�仯֪ͨ��
struct STRU_UC_CRS_CL_USER_AVS_INFO_ID
{
	int	miAvsId;					//��ʼ�û���¼�·�ʱΪ��������Ϊ�û�ѡ��� avsid 1����2����avs�仯�·�ʱ avsid=0
	unsigned short miAvsCount;
	STRU_UC_CL_CRS_USER_AVSINFO_ID *miAvsInfoList;					

	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	int Serialize(CStandardSerialize & aoStandardSerialize);
	STRU_UC_CRS_CL_USER_AVS_INFO_ID();
	~STRU_UC_CRS_CL_USER_AVS_INFO_ID();
};

//�û�avs��Ϣ�仯֪ͨ��
struct STRU_UC_CL_CRS_USER_AVS_CHANGE_ID
{
	int64_t   mi64UserID;                //�û�id                    
	unsigned int  muAvsIp;              //�û��Լ���avsip
	unsigned short muVoicePort;          //�û��Լ���avsport

	STRU_UC_CL_CRS_USER_AVS_CHANGE_ID()
	{
		memset(this, 0, sizeof(STRU_UC_CL_CRS_USER_AVS_CHANGE_ID));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	int Serialize(CStandardSerialize & aoStandardSerialize);
};


//����������
struct STRU_USER_LOSTRATE_RQ
{
	int64_t mi64UserID;
	int    Serialize(CStandardSerialize & aoStandardSerialize);
	STRU_USER_LOSTRATE_RQ()
	{
		memset(this, 0, sizeof(STRU_USER_LOSTRATE_RQ));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
};

//������Ӧ��
struct STRU_USER_LOSTRATE_RS
{
	int64_t mi64UserID;
	int miLostRate;
	int    Serialize(CStandardSerialize & aoStandardSerialize);
	STRU_USER_LOSTRATE_RS()
	{
		memset(this, 0, sizeof(STRU_USER_LOSTRATE_RS));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
};

enum emModifyType
{
	EM_FIELD_PHOTO,
	EM_FIELD_NICKNAME,
	EM_FIELD_MAX
};

struct STRU_MODIFIED_USER_INFO_FIELD
{
	uint8_t mbyFieldName; //�޸��ֶ�����
	char macValue[USER_INTRO_LEN + 1]; //�޸�ֵ
	int Serialize(CStandardSerialize & aoStandardSerialize);
	STRU_MODIFIED_USER_INFO_FIELD();
};
typedef struct STRU_MODIFIED_USER_INFO_FIELD * PSTRU_MODIFIED_USER_INFO_FIELD;

struct STRU_UC_CL_CRS_CHG_USER_INFO_ID
{
	int64_t mi64UserId;
	uint8_t    mbyCount; //�޸ĵ�ֵ���������
	PSTRU_MODIFIED_USER_INFO_FIELD mpModifyList; //�޸ĵ�ֵ����
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	int Serialize(CStandardSerialize & aoStandardSerialize);
	STRU_UC_CL_CRS_CHG_USER_INFO_ID();
	~STRU_UC_CL_CRS_CHG_USER_INFO_ID();
};


//�����ο�ID����� --�˰������������ҷ���������һ���ο͵�ID��
struct	STRU_UC_COM_GAS_APPLY_VISITOR_ID_RQ
{
	char macVersion[VERSION_LEN + 1]; //�汾


	int Serialize(CStandardSerialize &aoStandardSerialize);

	STRU_UC_COM_GAS_APPLY_VISITOR_ID_RQ()
	{
		memset(this, 0, sizeof(STRU_UC_COM_GAS_APPLY_VISITOR_ID_RQ));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
};

//�����ο�IDӦ���--�����ҷ��������ο�
struct	STRU_UC_COM_GAS_APPLY_VISITOR_ID_RS
{
	int64_t 	mi64VisitorID;
	char		 macVisitorName[NICK_NAME_LEN+1];
	uint16_t	mwPhotoNum;

	int Serialize(CStandardSerialize &aoStandardSerialize);


	STRU_UC_COM_GAS_APPLY_VISITOR_ID_RS()
	{
		memset(this, 0, sizeof(STRU_UC_COM_GAS_APPLY_VISITOR_ID_RS));
	}
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
};

//TCP���䱨ͷ
struct	STRU_UC_CL_TCP_CRS_DATA_HEAD
{
	int	mlChatroomID;//����id	
	uint16_t	mwDataLen;//��Ϣ��С
	char	mpData[ROOM_PACK_DATA_LEN];//��Ϣ

	STRU_UC_CL_TCP_CRS_DATA_HEAD();
	int    Pack(char *   apBuffer ,int    alLen);
	int    UnPack(char * apBuffer,int    alLen);
	int Serialize(CStandardSerialize & aoStandardSerialize);
};
typedef STRU_UC_CL_TCP_CRS_DATA_HEAD * PSTRU_UC_CL_TCP_CRS_DATA_HEAD;


#endif //_CRS_CL_STRUDEF_H_