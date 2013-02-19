/*! @sfl_http.h
* *****************************************************************************
* @n</PRE>
* @nģ����       ��Http������ؿ⺯���ӿ�����
* @n�ļ���       ��sfl_http.h
* @n����ļ�     ��sfl_http.cpp
* @n�ļ�ʵ�ֹ��� ��Http������ؿ⺯���ӿ�����
* @n����         ��huangjun - ���˼���(�й�)
* @n�汾         ��1.0.1
* @n-----------------------------------------------------------------------------
* @n��ע��
* @n-----------------------------------------------------------------------------
* @n�޸ļ�¼��
* @n����        �汾        �޸���      �޸�����
* @n20080713    1.0.0       huangjun    Created
* @n</PRE>
* @n****************************************************************************/
#ifndef __HJ_HTTP_H__
#define __HJ_HTTP_H__

#include <string>

using namespace std;

/*!
* ���ܣ��滻�ַ���pSrcMsg�е�����strOrgMsgΪstrReplaceMsg
* @n���ߣ�huangjun
* @n���ڣ�2008-07-31
*/
int HJ_ReplaceInfo(char *pSrcMsg, const string &strOrgMsg, const string &strReplaceMsg);
int HJ_ReplaceInfo(string &strSrcMsg, const string &strOrgMsg, const string &strReplaceMsg);

/*!
* ���ܣ�ת��������ı����ַ���Ϊ����������
* @n���ߣ�huangjun
* @n���ڣ�2008-07-31
*/
void HJ_unescape_url(char *url);

/*!
* ���ܣ���HTTP�����ж�λ��ͷ����λ��
* @n���ߣ�huangjun
* @n���ڣ�2008-07-31
*/
char* HJ_GetPkgHeadPos(const char *sPkg);

/*!
* ���ܣ���HTTP������ȡ����ͷ����
* @n���ߣ�huangjun
* @n���ڣ�2008-07-31
*/
int HJ_GetPkgHead(string &strHead, const char *sPkg);

/*!
* ���ܣ���HTTP������ȡ�������в���
* @n���ߣ�huangjun
* @n���ڣ�2008-07-31
*/
int HJ_GetRequestLine(string &strRequestLine, const char *sPkg);

/*!
* ���ܣ���HTTP�����ж�λ���岿��λ��
* @n���ߣ�huangjun
* @n���ڣ�2008-07-31
*/
char* HJ_GetPkgBodyPos(const char *sPkg);

/*!
* ���ܣ���HTTP������ȡ�����岿��
* @n���ߣ�huangjun
* @n���ڣ�2008-07-31
*/
int HJ_GetPkgBody(string &strBody, const char *sPkg);

/*!
* ���ܣ���HTTP��ͷ�в�������Ϊsymbol�ֶε���Ӧֵ
* @n���ߣ�huangjun
* @n���ڣ�2008-07-31
*/
int HJ_FindHeadItem(string &strValue, const char *sHttpHead, const char *symbol);

/*!
* ���ܣ���ĳ���ַ������������Ϊsymbol�ֶε�ֵ
* @n���ߣ�huangjun
* @n���ڣ�2008-07-31
*/
int HJ_FindItemValue(string &strValue, const char *sLineBuffer, const char *symbol);

/*!
* ���ܣ���Դ�ַ���msg�в�������Ϊsymbol�ֶε���Ӧֵ
* @n���ߣ�huangjun
* @n���ڣ�2008-07-31
*/
string HJ_FindSymbol(const string &msg, const char *symbol);

/*!
* ���ܣ���html��Ϣ�������л�ȡContent-Length�ֶε�ֵ
* @n���ߣ�huangjun
* @n���ڣ�2008-07-31
*/
int HJ_GetPageLength(const char *caTempBuffer);

#endif
