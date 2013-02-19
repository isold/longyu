#ifndef __MPS_PKG_H__
#define __MPS_PKG_H__

#include <sys/types.h>

#define STX 0x03
#define ETX 0x07

typedef u_int8_t  UINT8;
typedef u_int16_t UINT16;
typedef u_int32_t UINT32;
typedef u_int64_t UINT64;

// �û�˽��������ռ�ֽڳ���
#define PRIVATE_ATTR_SIZE 16

// ��Ϣ���ݱ���
typedef enum
{
    CHARSET_UTF8    = 0,
    CHARSET_GB2312  = 1,
    CHARSET_GBK     = 2
} ENUM_ENCODING_TYPE;

// ��Ϣ����
typedef enum
{
    // �ͻ���¼��������������Ϣ
    LOGIN_REQ               =       0x0001,

    // �������·����ͻ��˵���Ϣ����
    PUSH_MSG_REQ            =       0x0002,

    // ��̨������Ϣ����
    DISPATCH_MSG_REQ        =       0x0003,

    // �ͻ���¼��������Ӧ����Ϣ
    LOGIN_ACK               =       0x8001,

    // �������·����ͻ��˵���ϢӦ��
    PUSH_MSG_ACK            =       0x8002,

    // ��̨������ϢӦ��
    DISPATCH_MSG_ACK        =       0x8003,

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

// ������ϢӦ���������
typedef enum
{
    // ���ͳɹ�
    PUSH_SUCCESS            =       0,
    // ���ݰ��Ƿ�
    PUSH_ILLEGAL            =       1,
    // ���Ͳ����Ƿ����߲�֧��
    PUSH_UNALLOW            =       2,
    // ��������
    PUSH_UNKNOWN            =       3
} PUSH_MSG_RET_VALUE;

#pragma pack(1)

// ����ϵͳ�����Ϣ����ͷ�ṹ
typedef struct
{
    // ���ݱ��ܳ��ȣ�������ʼ��־����ͷ�������ܳ���
    UINT16      u16PkgLen;
    // �汾�ţ��״�Ϊ0100
    UINT16      u16Verion;
    // ��Ϣ����
    UINT16      u16MsgType;
    // ��Ϣ��ˮ��
    UINT32      u32Seq;
    // ��Ϣ����ʱ���
    UINT32      u32Timestamp;
} STRU_MSGPUSH_PKG_HEAD;

// ����ϵͳ�����Ϣ���ṹ
typedef struct
{
    // ��ʼ��־
    UINT8       u8Stx;
    // ��ͷ
    STRU_MSGPUSH_PKG_HEAD stHead;
    // ���壬�䳤
    char        szBody[0];
    // ������־
    UINT8       u8Etx;
} STRU_MSGPUSH_PKG;

// �ͻ��˵�¼�������������������Ϣ�������������Ϣ��������
typedef struct
{
    // �û�Id
    UINT64      u64UsrId;
    // ҵ��Id
    UINT16      u16SvcId;
    // ͨ������
    UINT32      u32CommAttr;
    // ҵ��˽������
    char        chPrivateAttr[PRIVATE_ATTR_SIZE];
} STRU_REG_MSG;

// ����������ϱ��ͻ���Ϣ�ṹ�壬�����������Ϣ��������
typedef struct
{
    // �û�Id
    UINT64      u64UsrId;
    // ҵ��Id
    UINT16      u16SvcId;
    // �����룬Ŀǰ���λ����ɾ�û�֮�ã�0-ɾ����1-����
    UINT16      u16CtlMask;
} STRU_RPT_USRINFO;

// ������Ϣ����ṹ�������������Ϣ��������
typedef struct
{
    //////////////////////////////////////////////////////////////////////////
    // begin of ��̨���͹���ͷ��Ϣ�����·����ͻ���
    // �û�Id�������ָ�������û�����Ϊ0
    UINT64      u64UsrId;
    // ҵ��Id�����ȫԱ���ͣ���ָ��ҵ������Ϊ0
    UINT16      u16SvcId;
    // ͨ�����ԣ���������ӦλΪ1���й���
    UINT32      u32CommAttr;
    // ҵ��˽�����ԣ���������ӦλΪ1���й���
    char        chPrivateAttr[PRIVATE_ATTR_SIZE];
    // end of ��̨���͹���ͷ��Ϣ�����·����ͻ���
    //////////////////////////////////////////////////////////////////////////

    // ������Ϣ��������
    UINT8       u8MsgEncoding;
    // ������Ϣ����
    UINT16      u16MsgLen;
    // ������Ϣ����
    char        szMsg[0];
} STRU_PUSH_MSG;

// Ӧ����ṹ�������Ӧ�𱨱�����
typedef struct
{
    // ���ص����󳵴��������룬0-�ɹ���other-ʧ�ܴ���
    UINT16      u16RetCode;
    // ������Ϣ�����ݱ���
    UINT8       u8ErrMsgEncoding;
    // ������Ϣ���ݳ���
    UINT16      u16ErrMsgLen;
    // ������Ϣ����
    char        szErrMsg[0];
} STRU_ACK_MSG;

#pragma pack()

#endif
