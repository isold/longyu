/*! @hj_string.cpp
*******************************************************************************
</PRE>
ģ����       ���ַ������������Լ�ת����ؿ⺯������
�ļ���       ��hj_string.cpp
����ļ�     ��hj_string.h
�ļ�ʵ�ֹ��� ���ַ������������Լ�ת����ؿ⺯������
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

#include "hj_string.h"

/****************************************************************************
* ���ܣ���16�����ı�ת���ɶ�����,����Ϊԭ����1/2
* ���ߣ�huangjun
* ���ڣ�2008-07-31
* ע�⣺�ڸĽ����㷨ʱҪ���������㷨������
***************************************************************************/
int HJ_Hex_Str2Bin(BYTE *pszOut, int &nOutLen, const int &nMaxOutLen
    , const char *pszIn)
{
    assert(pszOut && pszIn);

    nOutLen = 0;

    int  nInLen = strlen(pszIn);
    if ((nInLen & 0X01 != 0)
        || (nInLen > (nMaxOutLen << 1)))
    {
        // DEBUG_PRINT(LM_ERROR, "�����ָ�����Ϊ�ջ����볤�Ȳ��Ϸ��򻺳�����С��\n");
        return -1;
    }

    char szChar[5];
    bzero(pszOut, nMaxOutLen);

    nOutLen = nInLen >> 1;
    for (register int i = 0; i < nOutLen; i++)
    {
        szChar[0] = '\0';
        strncat(szChar, (pszIn + int(i << 1)), 2);
        sscanf(szChar, "%x", (unsigned int*)(pszOut + i));
    }

    return 0;
}

/****************************************************************************
* ���ܣ��Ѷ�����ֵת����16�����ַ�����ת������ַ�������Ϊ���볤�ȵ�����
* ���ߣ�huangjun
* ���ڣ�2008-07-31
* ע�⣺�ڸĽ����㷨ʱҪ���������㷨������
***************************************************************************/
int HJ_Hex_Bin2Str(char *pszOut, int &nOutLen, const int &nMaxOutLen
    , const char *pszIn, const int nInLen)
{
    assert(pszOut && pszIn);

    nOutLen = 0;

    bzero(pszOut, nMaxOutLen);

    if ((nInLen << 1) > (nMaxOutLen - 1))
    {
        // DEBUG_PRINT(LM_ERROR, "���ת����Ļ�����̫С��\n");
        return -1;
    }

    for (register int i = 0; i < nInLen; i++)
    {
        sprintf((pszOut + int(i << 1)), "%02x", *((unsigned char *)(pszIn + i)));
    }
    nOutLen = nInLen << 1;

    return 0;
}

/****************************************************************************
* ���ܣ����ַ���ֵת����4���ֽڵ�Hashֵ
* ���ߣ�huangjun
* ���ڣ�2008-07-31
***************************************************************************/
unsigned long HJ_Str2Hash(const char *pszIn)
{
    assert(pszIn);

    unsigned long ulHashValue = 0, ulTemp;
    int nLen = strlen(pszIn);
    char *pszPos = const_cast<char*>(pszIn);
    const char *pszEnd = pszIn + nLen;

    while (pszPos < pszEnd)
    {
        ulHashValue = (ulHashValue << 4) + tolower(*pszPos++);
        if ((ulTemp = (ulHashValue & 0xF0000000)) != 0)
        {
            ulHashValue ^= (ulTemp >> 24);
            ulHashValue ^= ulTemp;
        }
    }
    return ulHashValue;
}

/****************************************************************************
* ���ܣ���ȡ��ǰ���ڵľ����ʽ�ַ���
* ���ߣ�huangjun
* ���ڣ�2008-07-31
* ��������磺20060325
* ��ע�������TLib���е��Ǹ�ͬ�Ⱥ����������������
***************************************************************************/
char* HJ_GetCurDateShortStr(char *pszDest, const int &nMaxOutSize)
{
    assert(pszDest);

    time_t tm_now = time(NULL);
    struct tm strc_now = *localtime(&tm_now);

    if (strc_now.tm_year > 50)
    {
        snprintf(pszDest, nMaxOutSize, "%04d%02d%02d"
            , strc_now.tm_year + 1900, strc_now.tm_mon + 1, strc_now.tm_mday);
    }
    else
    {
        snprintf(pszDest, nMaxOutSize, "%04d%02d%02d"
            , strc_now.tm_year + 2000, strc_now.tm_mon + 1, strc_now.tm_mday);
    }

    return pszDest;
}

/****************************************************************************
* ���ܣ���ȡ��ǰ����ʱ���ʽ�ַ���
* ���ߣ�huangjun
* ���ڣ�2008-07-31
* ��������磺2008-07-31 00:00:00
***************************************************************************/
char* HJ_GetCurDateTimeStr(char *pszDest, const int &nMaxOutSize)
{
    assert(pszDest);

    time_t tm_now = time(NULL);
    struct tm strc_now = *localtime(&tm_now);

    if (strc_now.tm_year > 50)
    {
        snprintf(pszDest, nMaxOutSize, "%04d-%02d-%02d %02d:%02d:%02d"
            , strc_now.tm_year + 1900, strc_now.tm_mon + 1, strc_now.tm_mday
            , strc_now.tm_hour, strc_now.tm_min, strc_now.tm_sec);
    }
    else
    {
        snprintf(pszDest, nMaxOutSize, "%04d-%02d-%02d %02d:%02d:%02d"
            , strc_now.tm_year + 2000, strc_now.tm_mon + 1, strc_now.tm_mday
            , strc_now.tm_hour, strc_now.tm_min, strc_now.tm_sec);
    }

    return pszDest;
}

/****************************************************************************
* ���ܣ���ʽ���ַ���������
* ���ߣ�huangjun
* ���ڣ�2006-12-08
***************************************************************************/
char* HJ_Format_StrCat(char *pszDest, size_t uDestMaxLen
    , const char *szFormat, ...)
{
    assert(pszDest && szFormat);

    va_list ap;

    va_start(ap, szFormat);
    size_t uDestLen = strlen(pszDest);
    assert(uDestLen <= uDestMaxLen);
    (void)vsnprintf(pszDest + uDestLen, (uDestMaxLen - uDestLen), szFormat, ap);
    va_end(ap);

    return pszDest;
}
