#ifndef ____BIG_ROOM__
#define ____BIG_ROOM__
#include "Dp.h"

struct _d_struct stLoginAppearance
{
	_d_serializable_impl(stLoginAppearance)

	_d_id(-) uint64_t	userId;
	_d_id(-) Dp::String<NICK_NAME_LEN> nick;
	_d_id(-) uint16_t	photoIndex;
	_d_id(-) uint8_t	grade;										//�û�����   
	_d_id(-) uint32_t	redTime;								//�����ʸ�
	_d_id(-) Dp::String<DEF_USER_MOOD_LEN> mood;				//�û�����
	_d_id(-) Dp::String<URL_LINK_LEN> headUrl;	
	_d_id(-) uint8_t	sex; 									//�û��Ա�
	_d_id(-) uint32_t 	charm;									//�û�����ֵ
	_d_id(-) uint32_t	wealth;									//�û��Ƹ�ֵ
	_d_id(-) uint32_t	activity;								//�û���Ծ��
	_d_id(-) uint32_t	vipRoomId;									//�û��Ƿ���VIP��
	_d_id(-) uint32_t	tycoon;										//���
	_d_id(-) uint32_t	seller;										//�ٷ�����
	_d_id(-) uint8_t	weekStar;									//�Ƿ�����
};

void copy(const STRU_HALL_USER_INFO &hallUser,stLoginAppearance &userInfo)
{
	userInfo.userId = hallUser.mi64UserId;
	userInfo.nick.assign(hallUser.macNickName);
	userInfo.photoIndex = hallUser.mwPhotoIndex;
	userInfo.grade = hallUser.mbyGrade;
	userInfo.redTime = hallUser.miRedMemTime;
	userInfo.mood.assign(hallUser.mstrUserMood);
	userInfo.headUrl.assign(hallUser.mstrUserImageURL);
	userInfo.sex = hallUser.mbyUserSex;
	userInfo.charm = hallUser.miUserCharm;
	userInfo.wealth = hallUser.miUserWealth;
	userInfo.activity = hallUser.miUserActivity;
	userInfo.vipRoomId = hallUser.mlVipRooomID;
	userInfo.tycoon = hallUser.miTycoon;
	userInfo.seller = hallUser.miSeller;
	userInfo.weekStar = hallUser.mbyWeekStar;
}


//struct _f_struct stOverRoomAppearance
//{
//	_d_serializable_impl(stOverRoomAppearance)
//
//	_f_f uint32_t	hallId;
//	_f_d stLoginAppearance userInfo;;
//};

// �Թۿͻ��˵�¼����
#define UC_CL_CRS_WATCH_LOGIN_HALL_RQ 
struct stCrsWatchLoginReq : public STRU_UC_CL_CRS_LOGIN_HALL_RQ_2007
{
	int Pack(char *buf,int len);
	int UnPack(char *buf,int len);
}
 				//�û���������

// �Թ۵�¼�ظ�
#define UC_CL_CRS_WATCH_LOGIN_HALL_RS
struct stCrsWatchLoginRet : public STRU_UC_CL_CRS_LOGIN_HALL_RS_2009
{
	int Pack(char *buf,int len);
	int UnPack(char *buf,int len);
};


// �Թ۵�¼�����û��б�
#define UC_CL_CRS_WATCH_USERLIST_RQ
struct _f_struct tagCrsWatchUserListReq
{
	_d_serializable_impl(tagCrsWatchUserListReq)
	
	_f_f uint16_t cmd _def(UC_CL_CRS_WATCH_USERLIST_RQ);
	_f_f uint64_t userId;
};



// �����б�
#define	UC_CL_CRS_WATCH_USERLIST_RS
struct tagCrsWatchUserListRet
{
	_d_serializable_impl(tagCrsWatchUserListRet)
	
	_f_f uint16_t cmd _def(UC_CL_CRS_WATCH_USERLIST_RS);
	_f_f uint32_t hallId;
	_f_a Dp::Array<stLoginAppearance> users;
};

// ���û�����
#define UC_CL_CRS_WATCH_USER_ENTER_NOTIFY
struct _f_struct tagCrsWatchUserEnterNotify
{
	_f_f uint16_t cmd _def(UC_CL_CRS_WATCH_USER_ENTER_NOTIFY);
	_f_f uint32_t hallId;
	_f_d stLoginAppearance userInfo;
};

// �û��˳�
#define UC_CL_CRS_WATCH_USER_LEFT_NOTIFY
struct tagCrsWatchUserLeftNotify
{ 
	_f_f uint16_t cmd _def(UC_CL_CRS_WATCH_USER_LEFT_NOTIFY);
	_f_f uint32_t hallId;
	_f_f uint64_t userId;
};

// �Թ�˽�ķ���
typedef STRU_UC_CL_CRS_DATA_ID_350 tagWatchPrivateChatReq;

// ������֪ͨ�Թ�˽����֤��
// �ð���ʽ����ͨ��֤��֪ͨ��ʽ��ͬ

// �Թ�˽�Ľ��շ�
// �Թ�˽��ʱĿ���û��յ��İ���ʽ����
#define UC_CL_CRS_WATCH_USER_PRIVATE_CHAT
struct tagCrsWatchPrivateChatDest
{
	_f_f uint16_t cmd _def(UC_CL_CRS_WATCH_USER_PRIVATE_CHAT);	
	_f_f Dp::String<1024> message;
};

// ��������������
// �Թ۷����������������ʽ����ͨ�����������ʽ��ͬ
typedef STRU_UC_CL_CRS_USE_PROPS_RQ tagCrsWatchUserPropsReq;

// �����ﴦ���Ӧ

#include "BigRoom.inl";
#endif

