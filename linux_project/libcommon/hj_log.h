/*! @hj_log.h
*******************************************************************************
</PRE>
ģ����       ��д��־��ؿ⺯������
�ļ���       ��hj_log.h
����ļ�     ��hj_log.cpp
�ļ�ʵ�ֹ��� ��д��־��ؿ⺯������
����         ��huangjun - �����ǹ���
�汾         ��1.0.1
-------------------------------------------------------------------------------
��ע��
-------------------------------------------------------------------------------
�޸ļ�¼��
����        �汾        �޸���      �޸�����
20080731    1.0.1       Huangjun    Created
</PRE>
******************************************************************************/

#ifndef __HJ_LOG_H__
#define __HJ_LOG_H__

#include <stdio.h>
#include <assert.h>

#ifndef __USE_XOPEN
#define __USE_XOPEN
#endif
#include <time.h>

typedef struct
{
    FILE    *pLogFile;
    char    sBaseFileName[80];
    char    sLogFileName[80];

    int     iMaxLogNum;
    long    lMaxSize;
    // long    lMaxCount;
    long    lLogCount;
    time_t  lCurTimeBase;
    time_t  lLastFlush;
} stLogFile;

class CHJ_Log
{
public:
    CHJ_Log();
    virtual ~CHJ_Log();
    long InitLogFile(char *sLogBaseName, long iMaxLogNum, long iMAX);
    int Log(char *sFormat, ...);
private:
    int ShiftFiles();
    time_t GetCurTimeBase();
    stLogFile m_Logfile;
};

#endif
