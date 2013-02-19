/*! @hj_shm.cpp
*******************************************************************************
</PRE>
ģ����       �������ڴ������ؿ⺯������
�ļ���       ��hj_shm.cpp
����ļ�     ��hj_shm.h
�ļ�ʵ�ֹ��� �������ڴ������ؿ⺯������
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
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

#include "hj_shm.h"

/****************************************************************************
* ���ܣ���ʼ�������ڴ�
* ���ߣ�Huangjun
* ���ڣ�2008-09-22
***************************************************************************/
char* HJ_GetShm(int iKey, int iSize, int iFlag)
{
    int iShmID = shmget(iKey, iSize, iFlag);
    if (iShmID < 0)
    {
        char szErrMsg[64];
        snprintf(szErrMsg, sizeof(szErrMsg), "shmget key(%d) size(%d)"
            , iKey, iSize);
        perror(szErrMsg);
        return NULL;
    }

    char *pShm = (char*)shmat(iShmID, NULL, 0);
    if (pShm == (char*)-1)
    {
        perror("shmat");
        return NULL;
    }

    return pShm;
}

/****************************************************************************
* ���ܣ���ʼ�������ڴ棬����ǵ�һ�δ������������ʼ��
* ����ֵ��-1-����ʧ�ܣ�0-�����ɹ�
* ���ߣ�Huangjun
* ���ڣ�2008-09-22
***************************************************************************/
int HJ_GetShm_Zero(char **ppShm, int iShmID, int iSize, int iFlag)
{
    assert(ppShm);

    *ppShm = NULL;
    char *pShm = HJ_GetShm(iShmID, iSize, iFlag & (~IPC_CREAT));
    if (!pShm)
    {
        if (!(iFlag & IPC_CREAT))
        {
            return -1;
        }

        pShm = HJ_GetShm(iShmID, iSize, iFlag);
        if (!pShm)
        {
            return -1;
        }

        bzero(pShm, iSize);
    }

    *ppShm = pShm;
    return 0;
}

/****************************************************************************
* ���ܣ���ʼ�������ڴ棬�������״δ���ʱ��ʼ������
* ����ֵ��-1-����ʧ�ܣ�0-�����ɹ���1-�״δ���
* ���ߣ�Huangjun
* ���ڣ�2008-09-22
***************************************************************************/
int HJ_GetShm_NZero(char **ppShm, int iShmID, int iSize, int iFlag)
{
    assert(ppShm);

    *ppShm = NULL;
    char *pShm = HJ_GetShm(iShmID, iSize, iFlag & (~IPC_CREAT));
    if (!pShm)
    {
        if (!(iFlag & IPC_CREAT))
        {
            return -1;
        }

        pShm = HJ_GetShm(iShmID, iSize, iFlag);
        if (!pShm)
        {
            return -1;
        }

        *ppShm =pShm;
        return 1;
    }

    *ppShm = pShm;
    return 0;
}
