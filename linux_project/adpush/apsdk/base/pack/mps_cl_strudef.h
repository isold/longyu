#ifndef mps_cl_strudef_h__
#define mps_cl_strudef_h__

#include "../include.h"
#define DEF_PROPSMPS_SRVID_DEFAULT  3
#define DEF_PROPSMPS_SRVID_ANDROID  25
#define DEF_PROPSMPS_SRVID_IOS      26

#define PRIVATE_ATTR_SIZE	16

#if defined (__linux__)
#if defined (__ANDROID__)
#define DEF_PROPSMPS_SRVID  DEF_PROPSMPS_SRVID_ANDROID
#else
#define DEF_PROPSMPS_SRVID  DEF_PROPSMPS_SRVID_DEFAULT
#endif
#elif defined (__APPLE__)
#ifdef __IPHONE_OS_VERSION_MIN_REQUIRED
#define DEF_PROPSMPS_SRVID  DEF_PROPSMPS_SRVID_IOS
#else
#define DEF_PROPSMPS_SRVID  DEF_PROPSMPS_SRVID_DEFAULT
#endif
#elif defined (_MSC_VER)
#define DEF_PROPSMPS_SRVID  DEF_PROPSMPS_SRVID_DEFAULT
#else
#define DEF_PROPSMPS_SRVID  DEF_PROPSMPS_SRVID_DEFAULT
#endif


// ��Ϣ����
typedef enum
{
	// �ͻ���¼��������������Ϣ
	LOGIN_REQ               =       0x0001,

	// �������·����ͻ��˵���Ϣ����
	PUSH_MSG_REQ            =       0x0002,
#if IS_SRV_MODE // �ͻ��˲���Ҫ
	// ��̨������Ϣ����
	DISPATCH_MSG_REQ        =       0x0003,
#endif

	// �ͻ���¼��������Ӧ����Ϣ
	LOGIN_ACK               =       0x8001,

	// �������·����ͻ��˵���ϢӦ��
	PUSH_MSG_ACK            =       0x8002,

#if IS_SRV_MODE // �ͻ��˲���Ҫ
	// ��̨������ϢӦ��
	DISPATCH_MSG_ACK        =       0x8003,
#endif

	// ����˵��û������ע��/ע���ͻ���Ϣ
	USER_CTL                =       0x5001
} MPS_MSG_TYPE;

// ��¼Ӧ���������
typedef enum
{
	// �����ɹ�
	LOGIN_SUCCESS           =       0,
	// ��¼ʱ����Ҫ�ض����µķ�����
	LOGIN_REDIRECT          =       1,
	// ��¼��������Ƿ����߲�֧��
	LOGIN_UNALLOW           =       2,
	// ϵͳ��æ����ϵͳ����
	LOGIN_SYSERROR          =       3,
	// ��������
	LOGIN_UNKNOWN           =       4
} LOGIN_RET_VALUE;


struct STRU_CL_TCP_MPS_PKG_BASE
{
	// ��Ϣ����
	uint16_t     u16MsgType;
	// ��Ϣ��ˮ��
	uint32_t     u32Seq;
	// ��Ϣ����ʱ���
	uint32_t       u32Timestamp;

	int Pack(char* apBuffer, int alLen);
	int UnPack(char* apBuffer, int alLen);
	STRU_CL_TCP_MPS_PKG_BASE();
	virtual int Serialize(CStandardSerialize& aoStandardSerialize);
};

struct STRU_CL_TCP_MPS_PKG_LOGIN_RQ:public STRU_CL_TCP_MPS_PKG_BASE
{
	// �û�Id
	uint64_t       u64UsrId;
	// ҵ��Id
	uint16_t       u16SvcId;
	// ͨ������
	uint32_t       u32CommAttr;
	// ҵ��˽������
	char         chPrivateAttr[PRIVATE_ATTR_SIZE];

	STRU_CL_TCP_MPS_PKG_LOGIN_RQ();
	virtual int Serialize(CStandardSerialize& aoStandardSerialize);
};

struct STRU_CL_TCP_MPS_PKG_LOGIN_ACK:public STRU_CL_TCP_MPS_PKG_BASE
{
	// ���ص������������룬0-�ɹ���other-ʧ�ܴ���
	uint16_t       u16RetCode;
	// ������Ϣ�����ݱ���
	uint8_t       u8ErrMsgEncoding;
	// ������Ϣ���ݳ���
	uint16_t       u16ErrMsgLen;
	// ������Ϣ����
	char*         szErrMsg;

	STRU_CL_TCP_MPS_PKG_LOGIN_ACK();
	~STRU_CL_TCP_MPS_PKG_LOGIN_ACK();
	virtual int Serialize(CStandardSerialize& aoStandardSerialize);
};

struct STRU_CL_TCP_MPS_PKG_PUSH_MSG:public STRU_CL_TCP_MPS_PKG_BASE
{
	// ������Ϣ��������
	uint8_t        u8MsgEncoding;
	// ������Ϣ����
	uint16_t       u16MsgLen;
	// ������Ϣ����
	char*         szMsg;

	STRU_CL_TCP_MPS_PKG_PUSH_MSG();
	~STRU_CL_TCP_MPS_PKG_PUSH_MSG();
	virtual int Serialize(CStandardSerialize& aoStandardSerialize);
};

#endif // mps_cl_strudef_h__