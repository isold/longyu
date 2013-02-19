#ifndef _CONST_DEF_H_
#define _CONST_DEF_H_

#include <stdint.h>

//=======================================��������=========================================================

//1.0Beta:							2.01.000
//1.0Release:						2.01.190
//1.1:								2.05.190
//1.1.1:							2.06.190
//1.2:								2.08.190
//1.2.1								2.09.190
//1.3:                              2.12.190
//1.3��ʽ��:                        2.13.190
//������                            2.15.190
//1.3SP1��                          2.16.190
//������1.2.1��                     2.17.190
const char SINA_SHOW_VERSION[]	 = "2.27.190";		//�汾��
const uint8_t SINA_SHOW_MPS_VERSION = 1;   //Show��ӦMPS�İ汾�ţ��ͻ��˰汾��ÿ��һ�Σ�
										   //��ӦMPS�汾��ֵӦ��1����ͬ������ӦMPS�İ汾�ļ��С�
										   //ȡֵ��Χ��SINA_SHOW_MPS_VERSION = (0~254),��֧��255�����ϰ汾��
#define WHOLE_PACK_DATA_LEN   1024*6
#define ROOM_PACK_DATA_LEN	  10240	

const uint8_t LOGIN_RESULT_OK              = 0;
const uint8_t LOGIN_RESULT_ERROR           = 1;
const uint8_t LOGIN_RESULT_FORBID          = 2;
const uint8_t LOGIN_RESULT_MEMBERROOMFULL  = 3;
const uint8_t LOGIN_RESULT_MEMBERFULL      = 4;
const uint8_t LOGIN_CHG_ROOM				= 5;//�л�����

#define DEF_MAX_ACTION_DESCRIPTION_LEN	 	512     //�������󳤶�


//�û���Ϣ״̬���
const uint8_t	CONST_USER_STATUS_HIDDE			=	0;//����
const uint8_t	CONST_USER_STATUS_REFUSECHAT	=	1;//�ܾ�������Ϣ
const uint8_t	CONST_USER_STATUS_ATTENTION		=	2;//��ע���û�
const uint8_t	CONST_USER_STATUS_FORBIDTALK	=	3;//��ֹ����
const uint8_t	CONST_USER_STATUS_HAVEVIDEO		=	4;//�Ƿ�����Ƶ
const uint8_t	CONST_USER_STATUS_SENDVOICE		=	5;//�Ƿ�������
const uint8_t	CONST_USER_STATUS_RECVVOICE		=	6;//�Ƿ��������
const uint8_t	CONST_USER_STATUS_SENDVIDEO		=	7;//�Ƿ�����Ƶ
const uint8_t	CONST_USER_STATUS_RECVVIDEO		=	8;//�Ƿ������Ƶ
const uint8_t	CONST_USER_STATUS_RECORD		=	9;//�Ƿ�����¼��
const uint8_t	CONST_USER_STATUS_KINESCOPE		=	10;//�Ƿ�����¼��
const uint8_t	CONST_USER_STATUS_PUBCHAT		=	11;//�Ƿ�������
const uint8_t	CONST_USER_STATUS_PRIVATECHAT	=	12;//�Ƿ�����˽��
const uint8_t	CONST_USER_STATUS_FLOWER		=	13;//�Ƿ������ʻ�

const uint16_t DEF_USE_IE_PROXY_SET		= 0;	//ʹ��IE��������
const uint16_t DEF_CONNECTION_DIRECT	= 1;	//�κŻ�ֱ��
const uint16_t DEF_CONNECTION_NAT		= 2;	//�������޴���
const uint16_t DEF_USE_SOCKS_PROXY		= 3;	//ʹ��SOCKS����
const uint16_t DEF_USE_HTTP_PROXY		= 4;	//ʹ��HTTP����

const uint16_t IP_ADDR_STR_LEN			= 15;	//IP����
const uint16_t PROXY_NAME_LEN			= 15;	//�����û�������
const uint16_t PROXY_PASSWORD_LEN		= 15;	//�������볤��

//�û���Ϣ
const uint16_t NICK_NAME_LEN			= 20;	//�û����Ƴ���
const uint16_t USER_CUSTOMEMOTION_LEN	= 400; //���100��������
const uint16_t USER_NAME_LEN			= 30;	//�����û����Ƴ���
const uint16_t USER_ID_LEN				= 20;	//�û�ID����
const uint16_t USER_PWD_LEN				= 16;	//�û����볤��

const uint16_t GROUP_NAME_LEN			= 40;
const uint16_t USER_EMOTION_LEN			= 20;  //�û����鳤��
const uint16_t COMMUNITY_NAME_LEN		= 200;

const uint16_t HALL_NAME_LEN			= 30;	//�������Ƴ���
const uint16_t CHATROOM_TYPE_NAME_LEN	= 30;	//�������Ƴ���
const uint16_t ACT_NAME_LEN				= 30;	//��Ŀ���Ƴ���
const uint16_t	DATA_LEN				= 2048;
const uint16_t	FILE_NAME_LEN			= 256;	//�ļ�������
const uint16_t	SYNOPSIS_LEN			= 256;	//��鳤��

const uint16_t FIND_NAME_LEN			= 14;	//���������ҹؼ��ֳ���


const uint16_t NODE_TYPE_CRTYPE_ID_ROOT				= 0;		//����

const uint16_t NODE_TYPE_CRTYPE_TYPE_OFFICIAL		= 1;		//�ٷ�
const uint16_t NODE_TYPE_CRTYPE_TYPE_COOPERATE		= 2;		//����

const uint16_t NODE_TYPE_CRTYPE_CHILD_TYPE_ROOM		= 0;		//�ӽڵ�Ϊ������
const uint16_t NODE_TYPE_CRTYPE_CHILD_TYPE_AREA	    = 1;		//��


const uint16_t MD5_LEN						= 32;		// MD5���ĳ���

#define CHATROOM_BMP_NAME_LEN		50
//----------------------------------------------------------------------
#define	CHG_TYPE_DELETE				2		//��������Ϣ���л�

//MsgModule
#define UC_CHATROOM_TOPIC_LEN					512					//����ĳ���
#define UC_CHATROOM_SALUTATORY_LEN				512					//��ӭ�ʵĳ���
#define UC_HALL_PWD_LEN			128					//���������볤��
#define REASON_LEN					500		// ����ԭ�򳤶�
#define CHATROOM_IMV_NAME_LEN		20		//�����ҳ������Ƴ���
#define DEF_TC_CONTENT_LEN_380      1024	//�ı��������ݰ����ݳ���
#define CRS_DATA_LEN				1024	//���������ݳ���
#define INFO_LEN					512		//һ����Ϣ����
#define SONG_NAME_LEN				40		//�����������ֳ���
#define	ERR_BUF_LEN					256		//��¼����
#define HOMEPAGE_DISPLAY_LEN		40		//��ַ���ӳ���
#define URL_LINK_LEN				100		//��ַ���ӳ���
#define DEF_USER_MOOD_LENGTH	    40		//�û����鳤��
#define DEF_USER_UNINAME_LEN		60		//ͳһ��Ա���Ƴ���
#define DEF_USER_BIRTHDAY_LEN   15  //�û����� 
#endif //_CONST_DEF_H_



