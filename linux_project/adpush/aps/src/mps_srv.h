/*! @file mps_srv.h
 * *****************************************************************************
 * @n</PRE>
 * @nģ����       : mps_srv��غ��Լ��ṹ������
 * @n�ļ���       : mps_srv.h
 * @n����ļ�     : mps_srv.cpp
 * @n�ļ�ʵ�ֹ��� : ����һЩ��غ��Լ��ṹ��
 * @n����         : huangjun - ���˼���(�й�)
 * @n�汾         : 1.0.1
 * @n---------------------------------------------------------------------------
 * @n��ע:
 * @n---------------------------------------------------------------------------
 * @n�޸ļ�¼:
 * @n����        �汾        �޸���      �޸�����
 * @n20081202    1.0.0       huangjun    Created
 * @n</PRE>
 ******************************************************************************/
#ifndef __MPS_SRV_H__
#define __MPS_SRV_H__

#include <dirent.h>

#include "mps_usrinfo_acs.h"

// ����״̬
typedef enum
{
    NOT_USED        =   0,
    LISTENER        =   1,
    ACCEPTED        =   2,
    CONNECTING      =   3,
    CONNECTED       =   4,
    RECONNECTIONG   =   5
} SOCK_STATUS;

// �Ƿ���ø��ؾ�����
#define USE_LOAD_BALANCE       0

// �Ƿ���������Լ���¼�û���
// #define TRACE_USER

// ����ض�IP�������, �����ڴ������û����ʵ���Ӫ��������/debug
#define TRACE_IP               "127.0.0.1"

// Ĭ�ϱ�������IP
#define DEFAULT_LOCAL_IP       "127.0.0.1"

// ÿ���������֧�ֵ��׽��־����С
#define DEFAULT_MAX_SOCKET_NUM 5000

// ������Ϣ���ݱ�����С
#define MAX_PUSH_PKG_LEN       8192

// ���ջ���������С
#define MAX_RECV_BUF_SIZE      1024
// ���ͻ���������С
#define MAX_SEND_BUF_SIZE      MAX_PUSH_PKG_LEN

// Ĭ�ϵķ������Tcp�˿�
#define DEFAULT_SERVER_PORT    80
// Ĭ�ϵķ������������Ϣ��Udp�˿�
#define DEFAULT_UDP_PORT       18000

// Ĭ�ϵ�pid�ļ����Ŀ¼
#define DEFAULT_PID_FILE       "/home/mps_srv/var/mps_srv.pid"

// Ĭ�ϵ���־�ļ����·����
#define DEFAULT_LOG_FILE       "/home/mps_srv/logs/mps_srv"
// Ĭ����־�����ļ�����С
#define MAX_LOG_SIZE           10000000
// Ĭ����־�ļ�����������
#define MAX_LOG_NUM            10

// Ĭ��tcp���ӳ�ʱֵ, ����Ϊ��λ
#define DEFAULT_CONN_TIMEOUT   90

// Ĭ�Ϸ�������ʱfork�Ľ�����
#define DEFAULT_PROCESS_NUM    10

#define RESERVE_OTHER_SOCKET_NUM 20     // Ϊ���̴򿪵������ļ���������ĸ���

// Ĭ�����֧��ҵ����
#define DEFAULT_MAX_SERVICE_NUM  1024

typedef struct
{
    size_t uServerId;                   // �����ڶ�̨ͬ������ͬServer������ʶ�Լ�

    char   szLocalIp[16];               // ��������IP��ַ
    unsigned short usServerPort;        // ���������������Tcp�˿�
    unsigned short usUdpPort;           // ���̼���������Ϣ��Udp�˿�

    size_t uProcessNum;                 // ��������ʱfork�Ľ�����
    char   szPidFilePath[MAXNAMLEN];    // PID�ļ����·��

    size_t uMaxSocketNum;               // ÿ�����̿��Դ��������׽��־��ֵ
    size_t uCurSocketNum;               // �����̵�ǰ�Ѿ����ܵľ����

    long   lConnTimeout;                // ÿ������������ĳ�ʱʱ��, ��ʱֱ�ӶϿ�

    size_t uMaxServiceNum;              // ÿ�����̿���֧�ֵ����ҵ����

    char szLogFilePath[MAXNAMLEN - 32]; // ��־�ļ���·����
    long lMaxLogSize;                   // ������־�ļ�������С
    int  nMaxLogNum;                    // ��־�ļ�������������
} STRU_CONFIG;

typedef struct
{
#ifdef TRACE_IP
    bool bTrace;                        // ��ʶ�Ƿ�Ե�ǰ���ӽ��и���
#endif

    int nPrevIndex;                     // ���Ӷ��е�ǰ������
    int nNextIndex;                     // ���Ӷ��еĺ�������

    volatile long lSendLock;            // ִ�з��Ͳ�����lock

    int  nSocketType;                   // Socket����״̬
    time_t tm_LoginTime;                // �����ӵ�¼��ʱ��
    time_t tm_LastActive;               // ����������ʱ��

    unsigned long lClientIP;            // �ͻ���IP
    unsigned short usClientPort;        // �ͻ������ӵĶ˿ں�
    // char sClientAddr[16];               // �����ϵ��ַ�����ʽ�Ŀͻ��˵�ַ

    bool bCloseOnSendAll;               // �������������ݰ�֮��ر�����

    long lPkgLen;                       // �û����������

    STRU_USERINFO_ACS *pUserinfo;       // ��ǰ���ӵ��û���Ϣ

    long lRecvBytes;                    // ��ǰ�Ѿ����յ����ֽ���
    char szRecvBuffer[MAX_RECV_BUF_SIZE]; // ���ܻ�����

    long lToSendBytes;                  // ���ͻ�������Ҫ���͵����ֽ���
    char szSendBuffer[MAX_SEND_BUF_SIZE]; // �������ݻ�����
} STRU_SOCKET_CONTEXT;

#endif
