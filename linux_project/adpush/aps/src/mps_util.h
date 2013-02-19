#ifndef __MPS_UTIL_H__
#define __MPS_UTIL_H__

#include <assert.h>
#include <sys/types.h>
#include <stdio.h>

#include "hj_misc.h"

class CAutoLock
{
public:
    CAutoLock(volatile long *plLock)
        : m_plLock(plLock)
    {
        while (HJ_xchg(plLock, 1))
        {
        }
    }
    virtual ~CAutoLock()
    {
        HJ_xchg(m_plLock, 0);
    }

private:
    volatile long *m_plLock;
};

/*!
 * ����: �ѵ�ǰҪ���ӵ�Socket�����ļ��뵽������
 * @n����: huangjun
 * @n����: 2008-12-02
 */
template<class STRU_SOCKET_CONTEXT>
int conn_add_list(int nSockFd, STRU_SOCKET_CONTEXT *pSocketContent, int &queue_root)
{
    assert((nSockFd >= 0) && pSocketContent);

    pSocketContent[nSockFd].nPrevIndex = -1;
    pSocketContent[nSockFd].nNextIndex = queue_root;

    if (queue_root != -1)
    {
        pSocketContent[queue_root].nPrevIndex = nSockFd;
    }

    queue_root = nSockFd;

    return 0;
}

/*!
 * ����: �ѵ�ǰҪ�رյ�Socket�����ĴӶ�����ɾ��
 * @n����: huangjun
 * @n����: 2008-12-02
 */
template<class STRU_SOCKET_CONTEXT>
int conn_rmv_list(int nSockFd, STRU_SOCKET_CONTEXT *pSocketContent, int &queue_root)
{
    assert((nSockFd >= 0) && pSocketContent);

    int &nPrev = pSocketContent[nSockFd].nPrevIndex;
    int &nNext = pSocketContent[nSockFd].nNextIndex;
    if (nNext != -1)
    {
        pSocketContent[nNext].nPrevIndex = nPrev;
    }
    if (nPrev != -1)
    {
        pSocketContent[nPrev].nNextIndex = nNext;
    }

    if (nSockFd == queue_root)
    {
        queue_root = nNext;
    }
    nPrev = nNext = -1;

    return 0;
}

/*!
 * ����: �ѵ�ǰ�û���Ϣ���뵽˫������ͷ
 * @n����: huangjun
 * @n����: 2008-12-02
 */
template<class STRU_ELEMENT>
int user_add_list(STRU_ELEMENT *pEle, STRU_ELEMENT* &pEle_Root)
{
    assert(pEle);

    pEle->pRight = pEle_Root;
    pEle->pLeft = NULL;

    if (pEle_Root)
    {
        pEle_Root->pLeft = pEle;
    }

    pEle_Root = pEle;

    return 0;
}

/*!
 * ����: ��ָ���û���Ϣ��˫��������ɾ��
 * @n����: huangjun
 * @n����: 2008-12-02
 */
template<class STRU_ELEMENT>
int user_rmv_list(STRU_ELEMENT *pEle, STRU_ELEMENT* &pEle_Root)
{
    assert(pEle && pEle_Root);

    STRU_ELEMENT* &pLeft = pEle->pLeft;
    STRU_ELEMENT* &pRight = pEle->pRight;

    if (pRight)
    {
        pRight->pLeft = pLeft;
    }

    if (pLeft)
    {
        pLeft->pRight = pRight;
    }

    if (pEle == pEle_Root)
    {
        pEle_Root = pRight;
    }

    pLeft = pRight = NULL;

    return 0;
}

#endif
