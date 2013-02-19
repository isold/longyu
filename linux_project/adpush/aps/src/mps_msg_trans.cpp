/*! @file mps_msg_trans.cpp
 * *****************************************************************************
 * @n</PRE>
 * @nģ����       : mps_msg_trans���������ܹ�ʵ��
 * @n�ļ���       : mps_msg_trans.cpp
 * @n����ļ�     : mps_msg_trans.h
 * @n�ļ�ʵ�ֹ��� : ʵ����Ϣ�·���ת����
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
#include <arpa/inet.h>
#include <fcntl.h>
#include <fstream>
#include <errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>

#ifndef __STDC_FORMAT_MACROS
#define __STDC_FORMAT_MACROS
#endif
#include <inttypes.h>

#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <new>

#include "hj_log.h"
#include "hj_cfg.h"
#include "hj_misc.h"
#include "hj_net.h"
#include "hj_rpt_api.h"
#include "hj_hexshow.h"
#include "hj_mempool.h"
#include "hj_hash_map.h"

#undef DEBUG_LEVEL
#define DEBUG_LEVEL (LM_DEBUG|LM_INFO|LM_ERROR|LM_EXCEPT)
#include "hj_debug_print.h"

#include "mps_msg_trans.h"
#include "mps_pkg.h"
#include "mps_util.h"

// ȫ�ֱ�������
CHJ_Log              g_sh_log;
STRU_CONFIG          g_stConfig;

typedef struct
{
    // ��ǰ���̵Ĵ���ID
    size_t uProcessId;
    // ��ǰ���̼���������Ϣ��udp socket���
    int  nUdpSocket;

    // ��ǰÿ���������֧�ֵ��׽��־����С
    size_t uMaxSocketNum;

    // epoll���
    int nEpfd;
    struct epoll_event *pEvents;

    int nConn_Queue_Root;

    STRU_SOCKET_CONTEXT *pSocketContext;
    // ������Socket
    int  nListen_Socket;
    bool bListen_Epoll_Added;

    size_t uClientCnt;
    struct sockaddr_in stClientAddr[MAX_SRV_NUM];
} STRU_RUNTIME;

using namespace std;

STRU_RUNTIME g_stRuntime = {0, -1, 0, -1, NULL, -1, NULL, -1, false, 0};

/*!
 * ����: ��λָ��socket������״̬��Ϣ
 * @n����: huangjun
 * @n����: 2008-12-02
 */
int ResetSocketContext(STRU_SOCKET_CONTEXT &stSocketContext)
{
    stSocketContext.tm_LoginTime = stSocketContext.tm_LastActive = time(NULL);
    stSocketContext.lPkgLen = 0;
    stSocketContext.lRecvBytes = 0;
    stSocketContext.lToSendBytes = 0;

    return 0;
}

/*!
 * ����: �ر�ָ��socket������
 * @n����: huangjun
 * @n����: 2008-12-02
 */
int CloseSocket(int nSocket)
{
    assert((nSocket >= 0) && (nSocket < (int)g_stRuntime.uMaxSocketNum)
        && g_stRuntime.pSocketContext && (g_stRuntime.pSocketContext[nSocket].nSocketType == ACCEPTED));

    STRU_SOCKET_CONTEXT &stSocketContext = g_stRuntime.pSocketContext[nSocket];

#ifdef TRACE_IP
    if (stSocketContext.bTrace)
    {
        DEBUG_PRINT(LM_INFO, "nSocket: %d\n", nSocket);
    }
#endif

    // �����Ӷ�����ɾ����ǰ��Socket������
    conn_rmv_list(nSocket, g_stRuntime.pSocketContext, g_stRuntime.nConn_Queue_Root);

    // �Ƴ�epoll�¼�����
    if (HJ_unregister_epoll_event(g_stRuntime.nEpfd, nSocket) < 0)
    {
        DEBUG_PRINT(LM_ERROR, "Call HJ_unregister_epoll_event() failed\n");
    }

    close(nSocket);
    stSocketContext.nSocketType = NOT_USED;

    g_stConfig.uCurSocketNum--;

    if (!g_stRuntime.bListen_Epoll_Added)
    {
        if (HJ_register_epoll_event(g_stRuntime.nEpfd, g_stRuntime.nListen_Socket, EPOLLIN | EPOLLET) == 0)
        {
            g_stRuntime.bListen_Epoll_Added = true;
        }
    }

    return -1;
}

/*!
 * ����: �����ʱ����
 * @n����: huangjun
 * @n����: 2008-12-02
 */
#if defined(USE_CLR_TIMEOUT)
int ClearTimeoutConnections(time_t &tm_before)
{
    time_t tm_now = time(NULL);

    if (abs(tm_now - tm_before) < 5)
    {
        return 0;
    }
    else
    {
        tm_before = tm_now;
    }

    time_t tm_interval;
    int nNextIndex;
    for (int i = g_stRuntime.nConn_Queue_Root; i != -1; i = nNextIndex)
    {
        nNextIndex = g_stRuntime.pSocketContext[i].nNextIndex;

        tm_interval = abs(tm_now - g_stRuntime.pSocketContext[i].tm_LastActive);
        if (tm_interval > g_stConfig.lConnTimeout)
        {
            DEBUG_PRINT(LM_INFO, "ConnTimeout and CloseSocket iSocket:%d\n", i);
            CloseSocket(i);
        }
    }

    return 0;
}
#endif

/*!
 * ����: ������е�Socket�¼�
 * @n����: huangjun
 * @n����: 2008-12-02
 */
int CheckConnStatus(void)
{
    int iRet = epoll_wait(g_stRuntime.nEpfd, g_stRuntime.pEvents, (int)g_stRuntime.uMaxSocketNum, -1);
    if (iRet > 0)
    {
        return iRet;
    }
    else
    {
        return -1;
    }
}

/*!
* ����: ��鲢���ܿͻ��˵�Socket����
* @n����: huangjun
* @n����: 2008-12-02
*/
int CheckAndAcceptConns(int nListenSocket)
{
    // DEBUG_PRINT(LM_INFO, "Enter...\n");

    struct sockaddr_in stSockAddr;
    int nNewSocket = 0;
    socklen_t uSockAddrLen;
    // char *pClientIP = NULL;
    const size_t uMaxAcptSocketNum = g_stRuntime.uMaxSocketNum - RESERVE_OTHER_SOCKET_NUM;
    size_t &uCurSocketNum = g_stConfig.uCurSocketNum;

    while (true)
    {
        // ������������������Ѿ���������, �����ø���������ȥ��������
        if (uCurSocketNum >= uMaxAcptSocketNum)
        {
            // DEBUG_PRINT(LM_EXCEPT, "������uCurSocketNum(%u)>=uMaxAcptSocketNum(%u)\n"
            //     , uCurSocketNum, uMaxAcptSocketNum);
            if (HJ_unregister_epoll_event(g_stRuntime.nEpfd, nListenSocket) >= 0)
            {
                g_stRuntime.bListen_Epoll_Added = false;
            }
            return -1;
        }

        uSockAddrLen = sizeof(stSockAddr);
        nNewSocket = accept(nListenSocket, (struct sockaddr *)&stSockAddr
            , (socklen_t*)&uSockAddrLen);
        // DEBUG_PRINT(LM_DEBUG, "After accept, iNewSocket:%d\n", iNewSocket);
        if (nNewSocket < 0)
        {
            // if ((errno == EAGAIN) || (errno == EINTR))
            // {
            //     DEBUG_PRINT(LM_DEBUG, "In NOBLOCK mode, Command can't complete immediately\n");
            // }
            break;
        }

        if (nNewSocket >= (int)g_stRuntime.uMaxSocketNum)
        {
            DEBUG_PRINT(LM_EXCEPT, "������nNewSocket(%d)>=g_stRuntime.uMaxSocketNum(%Zu)\n"
                , nNewSocket, g_stRuntime.uMaxSocketNum);
            close(nNewSocket);
            break;
        }

        /*
        unsigned long ulClientIP = stSockAddr.sin_addr.s_addr;
        pClientIP = inet_ntoa(*(struct in_addr*)&stSockAddr.sin_addr);
        if (pClientIP == NULL)
        {
            DEBUG_PRINT(LM_ERROR, "Call inet_ntoa() failed\n");
            close(nNewSocket);
            continue;
        }
        */

        HJ_SetNoBlock(nNewSocket);
        HJ_SetTcpSockKeepAlive(nNewSocket, 1, 120, 20, 3);

        if (HJ_register_epoll_event(g_stRuntime.nEpfd, nNewSocket, EPOLLIN | EPOLLET) < 0)
        {
            DEBUG_PRINT(LM_ERROR, "Call HJ_register_epoll_event() for adding the new connect socket failed\n");
            close(nNewSocket);
            continue;
        }

#ifdef TRACE_IP
        if (true) // (strcmp(TRACE_IP, pClientIP) == 0)
        {
            g_stRuntime.pSocketContext[nNewSocket].bTrace = true;
            // DEBUG_PRINT(LM_INFO, "Accept a new connection!\n");
        }
        else
        {
            g_stRuntime.pSocketContext[nNewSocket].bTrace = false;
        }
#endif

        // ��ʼ���ͻ�������Ϣ
        g_stRuntime.pSocketContext[nNewSocket].nPrevIndex = g_stRuntime.pSocketContext[nNewSocket].nNextIndex = -1;
        g_stRuntime.pSocketContext[nNewSocket].nSocketType = ACCEPTED;
        g_stRuntime.pSocketContext[nNewSocket].lClientIP = stSockAddr.sin_addr.s_addr;
        g_stRuntime.pSocketContext[nNewSocket].usClientPort = ntohs(stSockAddr.sin_port);
        // snprintf(g_stRuntime.pSocketContext[nNewSocket].sClientAddr
        //     , sizeof(g_stRuntime.pSocketContext[nNewSocket].sClientAddr), "%s", pClientIP);

        ResetSocketContext(g_stRuntime.pSocketContext[nNewSocket]);

        // �������ӵ�Socket���뵽���Ӷ���
        conn_add_list(nNewSocket, g_stRuntime.pSocketContext, g_stRuntime.nConn_Queue_Root);

        uCurSocketNum++;
    } // end while (true)

    return 0;
}

/*!
 * ����: �������ݰ�
 * ����: nSocketΪҪ�������ݵ�socket, pPkgָ�����ݰ�, uPkgLenΪ���ݳ���(���ܳ���MAX_SEND_BUF_SIZE���ֽ�)
 * ����: 0 - �ɹ�; <0 - ʧ��
 */
int SendPkg(int nSocket, const char *pPkg, size_t uPkgLen)
{
    assert(g_stRuntime.pSocketContext && (nSocket >= 0) && ((size_t)nSocket < g_stRuntime.uMaxSocketNum) && pPkg);

    STRU_SOCKET_CONTEXT &stSocketContext = g_stRuntime.pSocketContext[nSocket];
    if ((uPkgLen <= 0) || (stSocketContext.nSocketType != ACCEPTED))
    {
        DEBUG_PRINT(LM_ERROR, "uPkgLen(%Zu) - nSocketType(%d)\n"
            , uPkgLen, stSocketContext.nSocketType);
        return -1;
    }

    if (stSocketContext.lToSendBytes > 0)
    {
        if ((stSocketContext.lToSendBytes + uPkgLen) > sizeof(stSocketContext.szSendBuffer))
        {
            DEBUG_PRINT(LM_ERROR, "���ͻ���������������ʧ�ܣ�\n");
            return -2;
        }
        // DEBUG_PRINT(LM_DEBUG, "�������ͻ�����!\n");
        memcpy(stSocketContext.szSendBuffer + stSocketContext.lToSendBytes, pPkg, uPkgLen);
        stSocketContext.lToSendBytes += uPkgLen;

        return 0;
    }

    int nBytesSent = send(nSocket, pPkg, uPkgLen, 0);
    // DEBUG_PRINT(LM_DEBUG, "Call send: %d\n", nBytesSent);
    stSocketContext.tm_LastActive = time(NULL);
    if (nBytesSent <= 0)
    {
        if ((nBytesSent < 0) && ((errno == EAGAIN) || (errno == EINTR)))
        {
            nBytesSent = 0; // ��һ��ѭ������������
        }
        else
        {
            return -3;
        }
    }

    if (nBytesSent >= (int)uPkgLen)
    {
        return 0;
    }

    if (HJ_modify_epoll_event(g_stRuntime.nEpfd, nSocket, EPOLLIN | EPOLLOUT | EPOLLET) != 0)
    {
        return -4;
    }

    stSocketContext.lToSendBytes = uPkgLen - nBytesSent;
    memcpy(stSocketContext.szSendBuffer, (char*)pPkg + nBytesSent, stSocketContext.lToSendBytes);

    return 0;
}

/*!
 * ����: ��������ͷ, ��ȡ���ܳ���
 * @n����: huangjun
 * @n����: 2008-12-02
 */
int HandlePkgHead(STRU_SOCKET_CONTEXT &stSocketContext, size_t &uPkgLen)
{
#ifdef TRACE_IP
    // const bool &bTrace = stSocketContext.bTrace;
#endif

    uPkgLen = 0;

    const long &lRecvBytes = stSocketContext.lRecvBytes;
    if (lRecvBytes < long(sizeof(UINT8) + sizeof(STRU_MSGPUSH_PKG_HEAD)))
    {
        return 1;
    }

    if (stSocketContext.szRecvBuffer[0] != STX)
    {
        return -1;
    }

    STRU_MSGPUSH_PKG_HEAD *pstMsgpushPkgHead
        = (STRU_MSGPUSH_PKG_HEAD*)(stSocketContext.szRecvBuffer + sizeof(UINT8));

    UINT16 u16MsgType = ntohs(pstMsgpushPkgHead->u16MsgType);
    if (u16MsgType != DISPATCH_MSG_REQ)
    {
        DEBUG_PRINT(LM_ERROR, "ҵ�����Ͳ���ȷ(%u)��\n", u16MsgType);
        return -2;
    }

    uPkgLen = ntohs(pstMsgpushPkgHead->u16PkgLen);
    if (uPkgLen < (2 * sizeof(UINT8) + sizeof(STRU_MSGPUSH_PKG_HEAD)
        + sizeof(STRU_PUSH_MSG)))
    {
        return -3;
    }

    return 0;
}

/*!
 * ����: ����ͻ��˵��ύ����
 * @n����: huangjun
 * @n����: 2008-12-02
 */
// ����Ҫ���Ϸ�����ֹһ�������������ӱ��Ͽ�
int HandlePkg(int nSocket, STRU_SOCKET_CONTEXT &stSocketContext)
{
    // DEBUG_PRINT(LM_INFO, "Enter...\n");
#ifdef TRACE_IP
    // const bool &bTrace = stSocketContext.bTrace;
#endif

    // HJ_hex_show(stSocketContext.szRecvBuffer, stSocketContext.lPkgLen);

    if (stSocketContext.szRecvBuffer[stSocketContext.lPkgLen - 1] != ETX)
    {
        DEBUG_PRINT(LM_ERROR, "���ݽ�β��ʶ�Ƿ���\n");
        return -1;
    }

    STRU_MSGPUSH_PKG *pstMsgpush_Pkg = (STRU_MSGPUSH_PKG*)stSocketContext.szRecvBuffer;
    STRU_PUSH_MSG *pPushMsg = (STRU_PUSH_MSG*)pstMsgpush_Pkg->szBody;
    UINT16 u16MsgLen = htons(pPushMsg->u16MsgLen);
    if (u16MsgLen != (stSocketContext.lPkgLen - (2 * sizeof(UINT8)
        + sizeof(STRU_MSGPUSH_PKG_HEAD) + sizeof(STRU_PUSH_MSG))))
    {
        DEBUG_PRINT(LM_ERROR, "wMsgLen: %u is illegal!\n", u16MsgLen);
        return -2;
    }

    stSocketContext.szRecvBuffer[stSocketContext.lPkgLen - 1] = '\0';
    g_sh_log.Log("%s", pPushMsg->szMsg);
    stSocketContext.szRecvBuffer[stSocketContext.lPkgLen - 1] = ETX;

    // DEBUG_PRINT(LM_DEBUG, "srvId: %u, userId: %" PRIu64 ", commAttr: %u\n"
    //    , ntohs(pPushMsg->u16SvcId), ntohq(pPushMsg->u64UsrId), ntohl(pPushMsg->u32CommAttr));

    for (size_t i = 0; i < g_stRuntime.uClientCnt; i++)
    {
        sendto(g_stRuntime.nUdpSocket, stSocketContext.szRecvBuffer, stSocketContext.lPkgLen, 0
            , (const struct sockaddr*)&g_stRuntime.stClientAddr[i], sizeof(struct sockaddr_in));
    }

    SendPkg(nSocket, "OK", 2);

    return 0;
}

/*!
 * ����: �������ݵ����ӵĿͻ���
 * @n����: huangjun
 * @n����: 2008-12-02
 */
int HandleSend(int nSocket)
{
    assert(g_stRuntime.pSocketContext && (nSocket >= 0) && ((size_t)nSocket < g_stRuntime.uMaxSocketNum));

    STRU_SOCKET_CONTEXT &stSocketContext = g_stRuntime.pSocketContext[nSocket];
    if (stSocketContext.nSocketType != ACCEPTED)
    {
        return -1;
    }

    // ��Ҫ���͵�ʣ���ֽ���
    if (stSocketContext.lToSendBytes < 0)
    {
        return -1;
    }
    else if (stSocketContext.lToSendBytes == 0)
    {
        return 1;
    }

    int nBytesSent = send(nSocket, stSocketContext.szRecvBuffer, stSocketContext.lToSendBytes, 0);
    if (nBytesSent <= 0)
    {
        if ((nBytesSent < 0) && ((errno == EAGAIN) || (errno == EINTR)))
        {
            // nBytesSent = 0; // ��һ��ѭ������������
            return 0;
        }
        else
        {
            return -1;
        }
    }

    stSocketContext.tm_LastActive = time(NULL);
    if (nBytesSent >= stSocketContext.lToSendBytes)
    {
        stSocketContext.lToSendBytes = 0;

        // �������ö��¼�����
        if (HJ_modify_epoll_event(g_stRuntime.nEpfd, nSocket, EPOLLIN | EPOLLET) < 0)
        {
            DEBUG_PRINT(LM_ERROR, "Call HJ_modify_epoll_event() for read failed:(nSocket is:%d)!\n"
                , nSocket);
            return -1;
        }
    }
    else
    {
        stSocketContext.lToSendBytes -= nBytesSent;
        memmove(stSocketContext.szSendBuffer, stSocketContext.szSendBuffer + nBytesSent
            , stSocketContext.lToSendBytes);
    }

    return 0;
}

/*!
 * ����: ��ָ��Socket��������
 * @n����: huangjun
 * @n����: 2008-12-02
 */
int HandleRecv(int nSocket)
{
    // DEBUG_PRINT(LM_TRACE, "iSocket is: %d\n", iSocket);
    assert(g_stRuntime.pSocketContext
        && (nSocket >= 0) && (nSocket < (int)g_stRuntime.uMaxSocketNum));

    STRU_SOCKET_CONTEXT &stSocketContext = g_stRuntime.pSocketContext[nSocket];

#ifdef TRACE_IP
    // const bool &bTrace = stSocketContext.bTrace;
#endif

    bool bRecvFull, bFirstProcess;

    int nBytesReceived, nRetCode;
    size_t uPkgLen;

    for (;;)
    {
        // ��ǰ���ջ��������д�С
        nBytesReceived = recv(nSocket, stSocketContext.szRecvBuffer + stSocketContext.lRecvBytes
            , sizeof(stSocketContext.szRecvBuffer) - stSocketContext.lRecvBytes - 1, 0);
        stSocketContext.tm_LastActive = time(NULL);
        if (nBytesReceived <= 0)
        {
            if ((nBytesReceived < 0)
                && ((errno == EAGAIN) || (errno == EINTR))) // ��Socket�������жϻ��߷�����û����, ��Ҫ������
            {
                // �´μ�����
                return 1;
            }
            else // ��ʧ��, Socket�ѶϿ�
            {
                return -1;
            }
        }
        stSocketContext.lRecvBytes += nBytesReceived;
        stSocketContext.szRecvBuffer[stSocketContext.lRecvBytes] = '\0';

        // ��ǰ���ջ������Ƿ�����
        bRecvFull = ((sizeof(stSocketContext.szRecvBuffer) - stSocketContext.lRecvBytes - 1) == 0);

        // ��һ�ν�����ѭ������
        bFirstProcess = true;
        for (;;)
        {
            // �����δ������ǰ��ͷ, �����Ƚ��н���
            if (stSocketContext.lPkgLen == 0)
            {
                nRetCode = HandlePkgHead(stSocketContext, uPkgLen);
                // DEBUG_PRINT(LM_DEBUG, "Call HandlePkgHead: %d, lRecvBytes: %ld, uPkgLen: %Zu, bFirstProcess: %s\n"
                //    , nRetCode, stSocketContext.lRecvBytes, uPkgLen, bFirstProcess? "first" : "nofirst");
                if (nRetCode > 0)          // ��δ��������
                {
                    if (bRecvFull)
                    {
                        // ����ϴν��ղ����ѽ�����, ˵��ϵͳ���������ܻ�������
                        // �ڷ��״���ѭ��������Ϣ����ʱ���������ϲ�ѭ����������ϵͳ��������Ϣ
                        if (!bFirstProcess)
                        {
                            break;
                        }
                        else // ����״ν���ʱ���ֲ�����, ���ǽ��ջ���������, ��˵����������С, ������Ϣ�Ƿ�, ��ֱ�ӶϿ�����
                        {
                            nRetCode = -1;
                        }
                    }
                    else
                    {
                        return 1;           // �´μ�������
                    }
                }
                else if (nRetCode == 0)      // �����ɹ�
                {
                    // �����ͷָʾ�İ������ڻ�������ֱ�ӶϿ�����
                    if (uPkgLen >= sizeof(stSocketContext.szRecvBuffer))
                    {
                        nRetCode = -2;
                    }
                    else
                    {
                        stSocketContext.lPkgLen = uPkgLen;
                    }
                }

                if (nRetCode < 0)           // ����������
                {
                    DEBUG_PRINT(LM_ERROR, "���ܵ�������ͷ��ʽ����\n");
                    return -1;
                }
            }

            // ����δ��������
            if (stSocketContext.lRecvBytes < stSocketContext.lPkgLen)
            {
                // �������ϵͳ������������Ϣ���ҵ�ǰΪ���״���ѭ�����������ϲ�ѭ����������
                if (bRecvFull && (!bFirstProcess))
                {
                    break;
                }
                return 1; // ����δ��������
            }

            // �����Ѿ���������
            if (HandlePkg(nSocket, stSocketContext) < 0)
            {
                return -1;
            }

            // ��ǰ�����Ѿ�������, ��ʼ����һ������λ��
            stSocketContext.lRecvBytes -= stSocketContext.lPkgLen;
            if (stSocketContext.lRecvBytes < 0)
            {
                return -1;
            }
            // ������ջ���������δ��������Ϣ
            if (stSocketContext.lRecvBytes > 0)
            {
                memmove(stSocketContext.szRecvBuffer, (stSocketContext.szRecvBuffer + stSocketContext.lPkgLen)
                    , stSocketContext.lRecvBytes);
                stSocketContext.szRecvBuffer[stSocketContext.lRecvBytes] = '\0';
            }
            stSocketContext.lPkgLen = 0;

            bFirstProcess = false;

            if (stSocketContext.lRecvBytes == 0)
            {
                if (bRecvFull)
                {
                    break;
                }
                else
                {
                    return 0;
                }
            }
        }
    }

    return 0;
}

/*!
 * ����: ����Socket��״̬�������ʼ�������Socket���ݷ��ͺͽ���
 * @n����: huangjun
 * @n����: 2008-12-02
 */
int CheckAndProcessOnSockets(int nSocketNum)
{
    // DEBUG_PRINT(LM_TRACE, "iSocketNum is:%d\n", iSocketNum);

    int nRetCode, nSocket;
    for (int i = 0; i < nSocketNum; i++)
    {
        nSocket = g_stRuntime.pEvents[i].data.fd;
        if ((nSocket < 0) || (nSocket >= (int)g_stRuntime.uMaxSocketNum)
            || (g_stRuntime.pSocketContext[nSocket].nSocketType == NOT_USED))
        {
            continue;
        }

        if (g_stRuntime.pSocketContext[nSocket].nSocketType == LISTENER)
        {
            if (g_stRuntime.pEvents[i].events & (EPOLLERR | EPOLLHUP))
            {
                DEBUG_PRINT(LM_ERROR, "Listen socket meet error\n");
                continue;
            }

            if (g_stRuntime.pEvents[i].events & EPOLLIN)
            {
                CheckAndAcceptConns(nSocket);
            }
        }
        else
        {
            if (g_stRuntime.pEvents[i].events & (EPOLLERR | EPOLLHUP))
            {
                DEBUG_PRINT(LM_ERROR, "Socket error and CloseSocket!\n");
                CloseSocket(nSocket);
                continue;
            }

            if (g_stRuntime.pEvents[i].events & EPOLLIN)
            {
                nRetCode = HandleRecv(nSocket);
                if (nRetCode < 0)
                {
                    CloseSocket(nSocket);
                    continue;
                }
            }

            if (g_stRuntime.pEvents[i].events & EPOLLOUT)
            {
                nRetCode = HandleSend(nSocket);
                if (nRetCode < 0)
                {
                    CloseSocket(nSocket);
                    continue;
                }
            }
        }
    }

    return 0;
}

/*!
 * ����: ��ʼ���ӽ���
 * @n����: huangjun
 * @n����: 2008-12-02
 */
int InitializeChildProcess(void)
{
    bool bInitFailed = true;

    do
    {
        g_stRuntime.nUdpSocket = HJ_UDP_Server(g_stConfig.szLocalIp, 0);
        if (g_stRuntime.nUdpSocket < 0)
        {
            printf("Call HJ_UDP_Server(%s-%u) failed!\n"
                , g_stConfig.szLocalIp, 0);
            break;
        }

        // ��ʼ����������Socket״̬����
        g_stRuntime.pSocketContext = new(nothrow) STRU_SOCKET_CONTEXT[g_stRuntime.uMaxSocketNum];
        if (!g_stRuntime.pSocketContext)
        {
            printf("new pSocketContext[%Zu] failed!\n", g_stRuntime.uMaxSocketNum);
            break;
        }
        bzero(g_stRuntime.pSocketContext, (g_stRuntime.uMaxSocketNum * sizeof(STRU_SOCKET_CONTEXT)));

        // ��ʼ��������׽�����ص�״̬
        g_stRuntime.pSocketContext[g_stRuntime.nListen_Socket].nSocketType = LISTENER;

        // ��ʼ������epoll�����¼�����
        g_stRuntime.pEvents = new(nothrow) struct epoll_event[g_stRuntime.uMaxSocketNum];
        if (!g_stRuntime.pEvents)
        {
            printf("new g_pEvent[%Zu] failed!\n", g_stRuntime.uMaxSocketNum);
            break;
        }
        bzero(g_stRuntime.pEvents, (g_stRuntime.uMaxSocketNum * sizeof(struct epoll_event)));

        g_stRuntime.nEpfd = epoll_create(g_stRuntime.uMaxSocketNum);
        if (g_stRuntime.nEpfd < 0)
        {
            printf("Call epoll_create(%Zu) failed!\n", g_stRuntime.uMaxSocketNum);
            break;
        }

        if (HJ_register_epoll_event(g_stRuntime.nEpfd, g_stRuntime.nListen_Socket, EPOLLIN | EPOLLET) < 0)
        {
            printf("Call HJ_register_epoll_event() for adding listen socket failed!\n");
            break;
        }
        g_stRuntime.bListen_Epoll_Added = true;

        bInitFailed = false;
    } while (false);

    if (bInitFailed)
    {
        if (g_stRuntime.nEpfd >= 0)
        {
            if (HJ_unregister_epoll_event(g_stRuntime.nEpfd, g_stRuntime.nListen_Socket) >= 0)
            {
                g_stRuntime.bListen_Epoll_Added = false;
            }
            close(g_stRuntime.nEpfd);
            g_stRuntime.nEpfd = -1;
        }

        if (g_stRuntime.pEvents)
        {
            delete []g_stRuntime.pEvents;
            g_stRuntime.pEvents = NULL;
        }

        if (g_stRuntime.pSocketContext)
        {
            delete []g_stRuntime.pSocketContext;
            g_stRuntime.pSocketContext = NULL;
        }

        if (g_stRuntime.nUdpSocket >= 0)
        {
            close(g_stRuntime.nUdpSocket);
            g_stRuntime.nUdpSocket = -1;
        }

        return -1;
    }

    char szLogFilePath[MAXNAMLEN];
    snprintf(szLogFilePath, sizeof(szLogFilePath), "%s_%03Zu"
        , g_stConfig.szLogFilePath, g_stRuntime.uProcessId);
    g_sh_log.InitLogFile(szLogFilePath, g_stConfig.nMaxLogNum, g_stConfig.lMaxLogSize);

    printf("End initialize Child Process %Zu\n", g_stRuntime.uProcessId);

    return 0;
}

/*!
 * ����: �ӽ��̴���
 * @n����: huangjun
 * @n����: 2008-12-02
 */
int ChildProcess(void)
{
    int iRetCode = InitializeChildProcess();
    if (iRetCode < 0)
    {
        return iRetCode;
    }

#if defined(USE_CLR_TIMEOUT)
    time_t tm_before = time(NULL);
#endif

    while (true)
    {
#if defined(USE_CLR_TIMEOUT)
        ClearTimeoutConnections(tm_before);
#endif

        iRetCode = CheckConnStatus();
        if (iRetCode < 0)
        {
            continue;
        }

        CheckAndProcessOnSockets(iRetCode);
    }

    return 0;
}

/*!
 * ����: ��ʼ�������˿�
 * @n����: huangjun
 * @n����: 2008-12-02
 */
int InitListenPort(void)
{
    //////////////////////////////////////////////////////////////////////////
    putchar('\n');
    //////////////////////////////////////////////////////////////////////////

    int iSocket = HJ_CreateListenSock(SOCK_STREAM, g_stConfig.szLocalIp
        , g_stConfig.usServerPort, NULL);
    if (iSocket < 0)
    {
        printf("Initiate Listening Socket Failed: (%s:%u)\n"
            , g_stConfig.szLocalIp, g_stConfig.usServerPort);
        return -1;
    }
    else
    {
        HJ_SetNoBlock(iSocket); // ����SocketΪ������ģʽ

        // ��¼�����׽���ID��ע��: ���ܼ������Ӷ���, ����һ��ȫ�ֱ��������棩
        g_stRuntime.nListen_Socket = iSocket;

        printf("Initiate Listening  Port OK: (IP:Port=%s:%u) and (Socket=%d)\n"
            , g_stConfig.szLocalIp, g_stConfig.usServerPort, iSocket);
    }

    return 0;
}

/*!
 * ����: �������еĳ�ʼ����Ӧ����ʱ����
 * @n����: huangjun
 * @n����: 2008-12-02
 */
int InitializeMainProcess(char *pConfigFile)
{
    assert(pConfigFile);

    bzero(&g_stConfig, sizeof(g_stConfig));

    struct stat stFileStat;
    if (stat(pConfigFile, &stFileStat) < 0)
    {
        printf("�����ļ�:  %s �����ڣ�\n", pConfigFile);
        return -1;
    }

    int nServerId, nServerPort, nProcessNum, nMaxSocketNum, nMaxServiceNum;

    char szClientAddr[1024];

    printf("Initializing...\nUse config file: %s\n", pConfigFile);

    HJ_Cfg_GetConfig(pConfigFile
        , "LocalIp", CFG_STRING, g_stConfig.szLocalIp, DEFAULT_LOCAL_IP
            , sizeof(g_stConfig.szLocalIp)
        , "ServerId", CFG_INT, &nServerId, (int)0

        , "ServerPort", CFG_INT, &nServerPort, (int)DEFAULT_SERVER_PORT
        , "ProcessNum", CFG_INT, &nProcessNum, (int)DEFAULT_PROCESS_NUM
        , "PidFilePath", CFG_STRING, g_stConfig.szPidFilePath, DEFAULT_PID_FILE
            , sizeof(g_stConfig.szPidFilePath)

        , "MaxSocketNum", CFG_INT, &nMaxSocketNum, (int)DEFAULT_MAX_SOCKET_NUM

        , "ConnTimeout", CFG_LONG, &(g_stConfig.lConnTimeout), (long)DEFAULT_CONN_TIMEOUT

        , "MaxServiceNum", CFG_INT, &nMaxServiceNum, (int)DEFAULT_MAX_SERVICE_NUM

        , "ClientAddr", CFG_STRING, szClientAddr, "", sizeof(szClientAddr)

        , "LogFilePath", CFG_STRING, g_stConfig.szLogFilePath, DEFAULT_LOG_FILE
            , sizeof(g_stConfig.szLogFilePath)
        , "MaxLogSize", CFG_LONG, &(g_stConfig.lMaxLogSize), (long)MAX_LOG_SIZE
        , "MaxLogNum", CFG_INT, &(g_stConfig.nMaxLogNum), (int)MAX_LOG_NUM

        , NULL
        );
    g_stConfig.uServerId = (size_t)nServerId;
    g_stConfig.usServerPort = (unsigned short)nServerPort;
    g_stConfig.uProcessNum = (size_t)nProcessNum;
    g_stConfig.uMaxSocketNum = (size_t)nMaxSocketNum;
    g_stConfig.uMaxServiceNum = (size_t)nMaxServiceNum;

    if (g_stConfig.uMaxSocketNum < RESERVE_OTHER_SOCKET_NUM)
    {
        printf("MaxSocketNum: %Zu is illegal!\n", g_stConfig.uMaxSocketNum);
        return -2;
    }

    //////////////////////////////////////////////////////////////////////////
    // ����������IP��ַ
    char szSep[] = " ,\t\n\r";
    char *pStr1 = NULL, *pTmp = NULL, *pToken = NULL;
    bool bInitNone = true;
    for (pStr1 = szClientAddr; ; pStr1 = NULL)
    {
        pToken = strtok_r(pStr1, szSep, &pTmp);
        if (!pToken)
        {
            break;
        }

        g_stRuntime.stClientAddr[g_stRuntime.uClientCnt].sin_addr.s_addr = inet_addr(pToken);
        if (g_stRuntime.stClientAddr[g_stRuntime.uClientCnt].sin_addr.s_addr == INADDR_NONE)
        {
            continue;
        }
        g_stRuntime.stClientAddr[g_stRuntime.uClientCnt].sin_family = AF_INET;
        g_stRuntime.stClientAddr[g_stRuntime.uClientCnt].sin_port = htons(18000);
        bInitNone = false;

        g_stRuntime.uClientCnt++;
    }

    if (bInitNone)
    {
        printf("ClientAddr: %s is error format!\n", szClientAddr);
        return -3;
    }
    //////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////
    printf("*************************************************************\n");
    printf("Startup paremeters is as following:\n\n");
    printf("LocalIp: %s\n\n", g_stConfig.szLocalIp);
    printf("ServerId: %Zu\n",g_stConfig.uServerId);
    printf("ServerPort: %u\n", g_stConfig.usServerPort);
    printf("ProcessNum: %Zu\n", g_stConfig.uProcessNum);
    printf("PidFilePath: %s\n\n", g_stConfig.szPidFilePath);
    printf("MaxSocketNum: %Zu\n\n", g_stConfig.uMaxSocketNum);
    printf("ConnTimeout: %ld\n", g_stConfig.lConnTimeout);
    printf("MaxServiceNum: %Zu\n", g_stConfig.uMaxServiceNum);
    printf("ClientCnt: %Zu\n", g_stRuntime.uClientCnt);
    printf("ClientAddr: %s\n\n", szClientAddr);
    printf("LogFilePath: %s\n", g_stConfig.szLogFilePath);
    printf("MaxLogSize: %ld\n", g_stConfig.lMaxLogSize);
    printf("MaxLogNum: %d\n\n", g_stConfig.nMaxLogNum);
    printf("*************************************************************\n");
    //////////////////////////////////////////////////////////////////////////

    // g_sh_log.InitLogFile(g_stConfig.szLogFilePath, g_stConfig.nMaxLogNum, g_stConfig.lMaxLogSize);

    // ��չϵͳ��һЩ���Ʋ���
    // HJ_SetRLimit();

    rlimit rlim;
    getrlimit(RLIMIT_NOFILE, &rlim);
    rlim.rlim_max = rlim.rlim_cur = g_stConfig.uMaxSocketNum;

    if (setrlimit(RLIMIT_NOFILE, &rlim))
    {
        DEBUG_PRINT(LM_ERROR, "Call setrlimit for RLIMIT_NOFILE failed!\n");
        return -4;
    }
    getrlimit(RLIMIT_NOFILE, &rlim);
    g_stRuntime.uMaxSocketNum = rlim.rlim_max;

    HJ_CreatePIDFile(g_stConfig.szPidFilePath);

    printf("Initializing as a daemon...\n");
    HJ_InitDaemon();

    return 0;
}

/*!
 * ����: �����ӽ���
 * @n����ֵ: 0 - ������,  > 0 - �ӽ���
 * @n����: huangjun
 * @n����: 2008-12-02
 */
int ForkChildProcesses(size_t &uProcessId, size_t uProcessNum)
{
    pid_t iPid;

    uProcessId = 0;
    for (size_t i = 1; i <= uProcessNum; i++)
    {
        if ((iPid = fork()) < 0)
        {
            DEBUG_PRINT(LM_ERROR, "Fork the %Zust child process failed!\n", i);
            kill(0, SIGKILL);
            return -1;
        }
        else if (iPid == 0)
        {
            uProcessId = i;
            return uProcessId;
        }
    }

    return uProcessId;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s ConfigFile\n", argv[0]);
        return -1;
    }

    int nRet = InitializeMainProcess(argv[1]);
    if (nRet < 0)
    {
        printf("Call InitializeMainProcess() failed!\n");
        return -1;
    }

    nRet = InitListenPort();
    if (nRet < 0)
    {
        printf("Call InitListenPort() failed!\n");
        return -1;
    }

    if (ForkChildProcesses(g_stRuntime.uProcessId, g_stConfig.uProcessNum) < 0)
    {
        printf("Call ForkChildProcesses() failed!\n");
        return -1;
    }

    ChildProcess();
    printf("������Exception: Call ChildProcess() failed!\n");

    return 0;
}
