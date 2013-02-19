#ifndef __HJ_RPT_API_H__
#define __HJ_RPT_API_H__

// �ϱ�������������Ĺ����ڴ�Key
#define RPT_SHM_KEY 51234
// ��ǰ�ϱ��������֧�ֵ�����ϱ�������
#define MAX_ATTR_ITEM_CNT 1000
// ��ǰ�ϱ�����汾��
#define RPT_API_VERSION 0x0101

#pragma pack(1)

typedef struct
{
    unsigned char byIsUse;
    unsigned long ulRptId;
    unsigned long ulCurValue;
} STRU_RPT_NODE;

typedef struct
{
    STRU_RPT_NODE stRptNodeArr[MAX_ATTR_ITEM_CNT];
} STRU_RPT_LIST;

#pragma pack()

/****************************************************************************
* ���ܣ���ȡ�ϱ�����API�İ汾��
* ���ߣ�Huangjun
* ���ڣ�2008-09-22
***************************************************************************/
unsigned short HJ_Rpt_GetVer();

/****************************************************************************
* ���ܣ��ۼ��ϱ���ӦID�ļ������ϱ��ļ��������ۼ�
* ���ߣ�Huangjun
* ���ڣ�2008-09-22
***************************************************************************/
int HJ_Rpt_API(unsigned long ulRptId, unsigned long ulValue);

/****************************************************************************
* ���ܣ�ȫ���ϱ���ӦID�ļ������ϱ��ļ����������Ϊ����ֵ
* ���ߣ�Huangjun
* ���ڣ�2008-09-22
***************************************************************************/
int HJ_Rpt_API_Set(unsigned long ulRptId, unsigned long ulValue);

/****************************************************************************
* ���ܣ���ȡĳ�ϱ�ID�����¼���
* ���ߣ�Huangjun
* ���ڣ�2008-09-22
***************************************************************************/
int HJ_Get_Rpt_Value(unsigned long ulRptId, unsigned long &ulValue);

#endif
