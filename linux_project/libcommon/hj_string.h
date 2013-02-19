/*! @hj_string.h
*******************************************************************************
</PRE>
ģ����       ���ַ��������������Լ�ת����ؿ⺯������
�ļ���       ��hj_string.h
����ļ�     ��hj_string.cpp
�ļ�ʵ�ֹ��� ���ַ��������������Լ�ת����ؿ⺯������
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

#ifndef __HJ_STRING_H__
#define __HJ_STRING_H__

#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <assert.h>

#ifndef __USE_XOPEN
#define __USE_XOPEN
#endif
#include <time.h>

#include "hj_macro.h"

/****************************************************************************
* ���ܣ���16�����ı�ת���ɶ�����,����Ϊԭ����1/2
* ���ߣ�huangjun
* ���ڣ�2008-07-31
* ע�⣺�ڸĽ����㷨ʱҪ���������㷨������
***************************************************************************/
int HJ_Hex_Str2Bin(BYTE *pszOut, int &nOutLen, const int &nMaxOutLen
    , const char *pszIn);

/****************************************************************************
* ���ܣ��Ѷ�����ֵת����16�����ַ�����ת������ַ�������Ϊ���볤�ȵ�����
* ���ߣ�huangjun
* ���ڣ�2008-07-31
* ע�⣺�ڸĽ����㷨ʱҪ���������㷨������
***************************************************************************/
int HJ_Hex_Bin2Str(char *pszOut, int &nOutLen, const int &nMaxOutLen
    , const char *pszIn, const int nInLen);

/****************************************************************************
* ���ܣ����ַ���ֵת����4���ֽڵ�Hashֵ
* ���ߣ�huangjun
* ���ڣ�2008-07-31
***************************************************************************/
unsigned long HJ_Str2Hash(const char *pszIn);

/****************************************************************************
* ���ܣ���ȡ��ǰ���ڵľ����ʽ�ַ���
* ���ߣ�huangjun
* ���ڣ�2008-07-31
* ��������磺20060325
* ��ע�������TLib���е��Ǹ�ͬ�Ⱥ����������������
***************************************************************************/
char* HJ_GetCurDateShortStr(char *pszDest, const int &nMaxOutSize);

/****************************************************************************
* ���ܣ���ȡ��ǰ����ʱ���ʽ�ַ���
* ���ߣ�huangjun
* ���ڣ�2008-07-31
* ��������磺2008-07-31 00:00:00
***************************************************************************/
char* HJ_GetCurDateTimeStr(char *pszDest, const int &nMaxOutSize);

/****************************************************************************
* ���ܣ���ʽ���ַ���������
* ���ߣ�huangjun
* ���ڣ�2006-12-08
***************************************************************************/
char* HJ_Format_StrCat(char *pszDest, size_t uDestMaxLen
    , const char *szFormat, ...);

#endif