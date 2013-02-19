/*! @hj_net.cpp
*******************************************************************************
</PRE>
ģ����       ��������ؿ⺯������
�ļ���       ��hj_net.cpp
����ļ�     ��hj_net.h
�ļ�ʵ�ֹ��� ��������ؿ⺯������
����         ��huangjun - �����ǹ���(http://www.shenzhoustar.com)
�汾         ��1.0.1
-------------------------------------------------------------------------------
��ע��
-------------------------------------------------------------------------------
�޸ļ�¼��
����        �汾        �޸���      �޸�����
20080731    1.0.1       Huangjun    Created
</PRE>
******************************************************************************/
#include <assert.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include "hj_net.h"

/****************************************************************************
* ���ܣ���������Socket
* ���ߣ�Huangjun
* ���ڣ�2008-07-14
***************************************************************************/
int HJ_CreateListenSock(int iSocketType, const char *pszHost
    , const u_short usPort, int *pListener)
{
    int iListenSocket = socket(AF_INET, iSocketType, 0);
    if (iListenSocket < 0)
    {
        perror("socket");
        return -1;
    }

    if (pListener != NULL)
    {
        *pListener = iListenSocket;
    }

    int iReuseAddr = 1;
    setsockopt(iListenSocket, SOL_SOCKET, SO_REUSEADDR, (void*)(&(iReuseAddr))
        , sizeof(iReuseAddr));

    struct sockaddr_in stAddr;

    bzero((char*)&stAddr, sizeof(stAddr));
    stAddr.sin_family = AF_INET;
    if (pszHost)
    {
        stAddr.sin_addr.s_addr = inet_addr(pszHost);
    }
    else
    {
        stAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    }
    stAddr.sin_port = htons(usPort);

    if (bind(iListenSocket, (struct sockaddr *)&stAddr, sizeof(stAddr)) < 0)
    {
        perror("bind");
        close(iListenSocket);
        return -1;
    }

    if (iSocketType == SOCK_STREAM)
    {
        // Queue up to 1024 connections before having them automatically rejected.
        listen(iListenSocket, 1024);
    }
    return iListenSocket;
}

/****************************************************************************
* ���ܣ�����Udp����Socket
* ���ߣ�Huangjun
* ���ڣ�2008-07-14
***************************************************************************/
int HJ_UDP_Server(const char *pszHost, u_int16_t nPort)
{
    int iUdpSock = socket(AF_INET, SOCK_DGRAM, 0);
    if (iUdpSock < 0)
    {
        perror("socket");
        return -1;
    }

    struct sockaddr_in stAddr;

    bzero(&stAddr, sizeof(stAddr));
    stAddr.sin_family = AF_INET;
    if (pszHost)
    {
        stAddr.sin_addr.s_addr = inet_addr(pszHost);
    }
    else
    {
        stAddr.sin_addr.s_addr = INADDR_ANY;
    }
    stAddr.sin_port = htons(nPort);

    if ((bind(iUdpSock, (struct sockaddr *)&stAddr, sizeof(stAddr))) == -1)
    {
        close(iUdpSock);
        perror("bind");
        return -1;
    }

    return iUdpSock;
}

/****************************************************************************
* ���ܣ���ָ��Socket���÷�����ģʽ
* ���ߣ�huangjun
* ���ڣ�2006-12-08
***************************************************************************/
int HJ_SetNoBlock(int iSocket)
{
    int iFlags = 1; // nonblock reusaddr

    ioctl(iSocket, FIONBIO, &iFlags);

    iFlags = fcntl(iSocket, F_GETFL, 0);
    fcntl(iSocket, F_SETFL, iFlags | O_NONBLOCK | O_NDELAY);

#if 1
    int iBufLen = 30 * 1024;
    //����TCP�Ľ��ջ���
    if(setsockopt(iSocket, SOL_SOCKET, SO_RCVBUF, (char*)&iBufLen, sizeof(iBufLen)) == -1)
    {
        perror("setsockopt and set SO_RCVBUF");
    }

    //����TCP�ķ��ͻ���
    if(setsockopt(iSocket, SOL_SOCKET, SO_SNDBUF, (char*)&iBufLen, sizeof(iBufLen)) == -1)
    {
        perror("setsockopt and set SO_SNDBUF");
    }
#endif
    return 0;
}

/****************************************************************************
* ���ܣ�����ģʽ�·�������
* ����ֵ��<0 - ����ʧ�ܻ��������=0 - ��ʱ�����ѹرգ�>0 - ���͵��ֽ���
* ���ߣ�Huangjun
* ���ڣ�2008-07-14
***************************************************************************/
int HJ_SingleSend(int iEpfd, int iSocket, struct msghdr &stMsg)
{
    if ((iEpfd < 0) || (iSocket < 0))
    {
        printf("�����iEpfd����Socket����Ƿ�(iEpfd:%d,iSocket:%d)��\n"
            , iEpfd, iSocket);
        return -1;
    }

    struct epoll_event stEv, stEvents[2];

    bzero(&stEv, sizeof(stEv));
    stEv.data.fd = iSocket;
    stEv.events = EPOLLOUT | EPOLLERR | EPOLLHUP;
    if (epoll_ctl(iEpfd, EPOLL_CTL_ADD, stEv.data.fd, &stEv) < 0)
    {
        perror("epoll_ctl");
        return -1;
    }

    int iRet = epoll_wait(iEpfd, stEvents, 1, 0);
    epoll_ctl(iEpfd, EPOLL_CTL_DEL, stEv.data.fd, &stEv);

    if (iRet > 0)
    {
        if (stEvents[0].events & (EPOLLERR | EPOLLHUP))
        {
            return -1;
        }
        return sendmsg(iSocket, &stMsg, 0);
    }
    else
    {
        return iRet;
    }

    return 0;
}

/****************************************************************************
* ���ܣ�UDP���ݱ��ķ���
* ����ֵ��<0 - ����ʧ�ܻ��������=0 - ��ʱ�����ѹرգ�>0 - ���͵��ֽ���
* ���ߣ�Huangjun
* ���ڣ�2008-07-14
***************************************************************************/
int HJ_SendData(int iSocket, char *szToIp, short iToPort, char *pDataBuf, int iSendLen)
{
    assert(szToIp && pDataBuf);

    struct sockaddr_in stToAddr;

    bzero(&stToAddr, sizeof(stToAddr));
    stToAddr.sin_family = AF_INET;
    stToAddr.sin_addr.s_addr = inet_addr(szToIp);
    stToAddr.sin_port   = htons((unsigned short)iToPort);
    int iSendbytes = sendto(iSocket, pDataBuf, iSendLen, 0
        , (struct sockaddr *)&stToAddr, sizeof(struct sockaddr_in));

    return iSendbytes;
}

/*!
 * ����: ����TcpSocket��keepalive���ʱ����ֵ
 * ����: nSocket-Ҫ���õ�Socket id, nKeepAlive-���û������keepalive����
 * @n    nKeepIdle-�೤ʱ���������շ�, ��̽��, nKeepInterval-̽�ⷢ��ʱ����
 * @n    nKeepCnt-̽�Ⳣ�Դ���
 * @n����: huangjun
 * @n����: 2009-01-06
 */
int HJ_SetTcpSockKeepAlive(int nSocket, int nKeepAlive, int nKeepIdle, int nKeepInterval, int nKeepCnt)
{
    if (setsockopt(nSocket, SOL_SOCKET, SO_KEEPALIVE, (void*)&nKeepAlive, sizeof(nKeepAlive)))
    {
        return -1;
    }

    if (nKeepAlive)
    {
        if (nKeepIdle > 0)
        {
            if (setsockopt(nSocket, SOL_TCP, TCP_KEEPIDLE, (void*)&nKeepIdle, sizeof(nKeepIdle)))
            {
                return -2;
            }
        }

        if (nKeepInterval > 0)
        {
            if (setsockopt(nSocket, SOL_TCP, TCP_KEEPINTVL, (void*)&nKeepInterval, sizeof(nKeepInterval)))
            {
                return -3;
            }
        }

        if (nKeepCnt > 0)
        {
            if (setsockopt(nSocket, SOL_TCP, TCP_KEEPCNT, (void*)&nKeepCnt, sizeof(nKeepCnt)))
            {
                return -4;
            }
        }
    }

    return 0;
}
