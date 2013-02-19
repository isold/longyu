#include <assert.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include "hj_rpt_api.h"
#include "hj_shm.h"

static STRU_RPT_LIST *gs_pRptList = NULL;
/****************************************************************************
* ���ܣ���ȡ�ϱ�����API�İ汾��
* ���ߣ�Huangjun
* ���ڣ�2008-09-22
***************************************************************************/
unsigned short HJ_Rpt_GetVer()
{
    return RPT_API_VERSION;
}

/****************************************************************************
* ���ܣ�������Ӧ�ϱ�Id���ڹ����ڴ��е�����λ������
* ���ߣ�Huangjun
* ���ڣ�2008-09-22
***************************************************************************/
static int HJ_Rpt_SearchRptId(STRU_RPT_LIST *pstRptLst, unsigned long ulRptId
    , int &nPosIndex)
{
    nPosIndex = 0;

    int index;
    for (index = 0; pstRptLst->stRptNodeArr[index].byIsUse; index++)
    {
        if (pstRptLst->stRptNodeArr[index].ulRptId == ulRptId)
        {
            nPosIndex = index;
            return 1;
        }
    }

    if (index >= MAX_ATTR_ITEM_CNT)
    {
        return -1;
    }
    else
    {
        nPosIndex = index;
        return 0;
    }
}

/****************************************************************************
* ���ܣ��ۼ��ϱ���ӦID�ļ������ϱ��ļ��������ۼ�
* ���ߣ�Huangjun
* ���ڣ�2008-09-22
***************************************************************************/
int HJ_Rpt_API(unsigned long ulRptId, unsigned long ulValue)
{
    if (!gs_pRptList
        && (HJ_GetShm_Zero((char**)&gs_pRptList, RPT_SHM_KEY
        , sizeof(STRU_RPT_LIST), (0666 | IPC_CREAT)) < 0))
    {
        return -1;
    }

    int nRptPosIndex;
    int nRet = HJ_Rpt_SearchRptId(gs_pRptList, ulRptId, nRptPosIndex);
    if (!nRet)
    {
        gs_pRptList->stRptNodeArr[nRptPosIndex].byIsUse = 1;
        gs_pRptList->stRptNodeArr[nRptPosIndex].ulRptId = ulRptId;
        gs_pRptList->stRptNodeArr[nRptPosIndex].ulCurValue = ulValue;
    }
    else if (nRet == -1)
    {
        return -2;
    }
    else
    {
        gs_pRptList->stRptNodeArr[nRptPosIndex].ulCurValue += ulValue;
    }

    return 0;
}

/****************************************************************************
* ���ܣ�ȫ���ϱ���ӦID�ļ������ϱ��ļ����������Ϊ����ֵ
* ���ߣ�Huangjun
* ���ڣ�2008-09-22
***************************************************************************/
int HJ_Rpt_API_Set(unsigned long ulRptId, unsigned long ulValue)
{
    if (!gs_pRptList
        && (HJ_GetShm_Zero((char**)&gs_pRptList, RPT_SHM_KEY
        , sizeof(STRU_RPT_LIST), (0666 | IPC_CREAT)) < 0))
    {
        return -1;
    }

    int nRptPosIndex;
    int nRet = HJ_Rpt_SearchRptId(gs_pRptList, ulRptId, nRptPosIndex);
    if (!nRet)
    {
        gs_pRptList->stRptNodeArr[nRptPosIndex].byIsUse = 1;
        gs_pRptList->stRptNodeArr[nRptPosIndex].ulRptId = ulRptId;
        gs_pRptList->stRptNodeArr[nRptPosIndex].ulCurValue = ulValue;
    }
    else if (nRet == -1)
    {
        return -2;
    }
    else
    {
        gs_pRptList->stRptNodeArr[nRptPosIndex].ulCurValue = ulValue;
    }

    return 0;
}

/****************************************************************************
* ���ܣ���ȡĳ�ϱ�ID�����¼���
* ���ߣ�Huangjun
* ���ڣ�2008-09-22
***************************************************************************/
int HJ_Get_Rpt_Value(unsigned long ulRptId, unsigned long &ulValue)
{
    ulValue = 0;

    if (!gs_pRptList
        && (HJ_GetShm_Zero((char**)&gs_pRptList, RPT_SHM_KEY
        , sizeof(STRU_RPT_LIST), (0666 | IPC_CREAT)) < 0))
    {
        return -1;
    }

    int nRptPosIndex;
    int nRet = HJ_Rpt_SearchRptId(gs_pRptList, ulRptId, nRptPosIndex);
    if (nRet > 0)
    {
        ulValue = gs_pRptList->stRptNodeArr[nRptPosIndex].ulCurValue;
        return 0;
    }
    else
    {
        return -2;
    }
}
