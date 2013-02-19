/*! @hj_net.h
*******************************************************************************
</PRE>
ģ����       ��������ؿ⺯������
�ļ���       ��hj_net.h
����ļ�     ��hj_net.cpp
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

#ifndef __HJ_NET_H__
#define __HJ_NET_H__

#include <errno.h>
#include <sys/types.h>
#include <sys/epoll.h>

#include <endian.h>
#include <byteswap.h>

#if __BYTE_ORDER == __BIG_ENDIAN
/* The host byte order is the same as network byte order,
so these functions are all just identity.  */
// 64λ�����ֽ���ת�����ֽ���
#define ntohq(neti64)   (neti64)
// 64λ�����ֽ���ת�����ֽ���
#define htonq(hosti64)  (hosti64)
#else
#if __BYTE_ORDER == __LITTLE_ENDIAN
// 64λ�����ֽ���ת�����ֽ���
#define ntohq(neti64)  __bswap_64(neti64)
// 64λ�����ֽ���ת�����ֽ���
#define htonq(hosti64) __bswap_64(hosti64)
#endif
#endif

/****************************************************************************
* ���ܣ���������Socket
* ���ߣ�Huangjun
* ���ڣ�2008-07-14
***************************************************************************/
int HJ_CreateListenSock(int iSocketType, const char *pszHost
    , const u_short usPort, int *iListener);

/****************************************************************************
* ���ܣ�����Udp����Socket
* ���ߣ�Huangjun
* ���ڣ�2008-07-14
***************************************************************************/
int HJ_UDP_Server(const char *pszHost, u_int16_t nPort);

/****************************************************************************
* ���ܣ���ָ��Socket���÷�����ģʽ
* ���ߣ�huangjun
* ���ڣ�2006-12-08
***************************************************************************/
int HJ_SetNoBlock(int iSocket);

/****************************************************************************
* ���ܣ�����ģʽ�·�������
* ����ֵ��<0 - ����ʧ�ܻ��������=0 - ��ʱ�����ѹرգ�>0 - ���͵��ֽ���
* ���ߣ�Huangjun
* ���ڣ�2008-07-14
***************************************************************************/
int HJ_SingleSend(int iEpfd, int iSocket, struct msghdr &stMsg);

/****************************************************************************
* ���ܣ�UDP���ݱ��ķ���
* ����ֵ��<0 - ����ʧ�ܻ��������=0 - ��ʱ�����ѹرգ�>0 - ���͵��ֽ���
* ���ߣ�Huangjun
* ���ڣ�2008-07-14
***************************************************************************/
int HJ_SendData(int iSocket, char *szToIp, short iToPort, char *pDataBuf
    , int iSendLen);

// ���epoll�¼�����
inline int HJ_register_epoll_event(int epfd, int iSocket, unsigned long ulEvent)
{
    struct epoll_event ev;
    ev.data.fd = iSocket;
    ev.events = ulEvent;

    return epoll_ctl(epfd, EPOLL_CTL_ADD, iSocket, &ev);
}

// �Ƴ�epoll�¼�����
inline int HJ_unregister_epoll_event(int epfd, int iSocket)
{
    struct epoll_event ev;
    ev.data.fd = iSocket;
    ev.events = 0;
    // ev.events = EPOLLIN | EPOLLOUT | EPOLLET;

    return epoll_ctl(epfd, EPOLL_CTL_DEL, iSocket, &ev);
}

// �޸�epoll�¼�����
inline int HJ_modify_epoll_event(int epfd, int iSocket, unsigned long ulEvent)
{
    struct epoll_event ev;
    ev.data.fd = iSocket;
    ev.events = ulEvent;

    if (epoll_ctl(epfd, EPOLL_CTL_MOD, iSocket, &ev) < 0)
    {
        if (errno != ENOENT)
        {
            return epoll_ctl(epfd, EPOLL_CTL_ADD, iSocket, &ev);
        }
        else
        {
            return -1;
        }
    }

    return 0;
}

/*!
 * ����: ����TcpSocket��keepalive���ʱ����ֵ
 * ����: nSocket-Ҫ���õ�Socket id, nKeepAlive-���û������keepalive����
 * @n    nKeepIdle-�೤ʱ���������շ�, ��̽��, nKeepInterval-̽�ⷢ��ʱ����
 * @n    nKeepCnt-̽�Ⳣ�Դ���
 * @n����: huangjun
 * @n����: 2009-01-06
 */
int HJ_SetTcpSockKeepAlive(int nSocket, int nKeepAlive, int nKeepIdle, int nKeepInterval, int nKeepCnt);

#endif
