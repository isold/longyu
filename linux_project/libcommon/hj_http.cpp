/*! @hj_http.cpp
* *****************************************************************************
* @n</PRE>
* @nģ����       ��Http������ؿ⺯���ӿڶ���
* @n�ļ���       ��hj_http.cpp
* @n����ļ�     ��hj_http.h
* @n�ļ�ʵ�ֹ��� ��Http������ؿ⺯���ӿڶ���
* @n����         ��huangjun - ���˼���(�й�)
* @n�汾         ��1.0.1
* @n-----------------------------------------------------------------------------
* @n��ע��
* @n-----------------------------------------------------------------------------
* @n�޸ļ�¼��
* @n����        �汾        �޸���      �޸�����
* @n20080731    1.0.0       Huangjun    Created
* @n</PRE>
* @n****************************************************************************/
#include <assert.h>
#include <string.h>
#include <netinet/in.h>
//
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
//

#include "hj_macro.h"
#include "hj_http.h"

/*!
* ���ܣ��滻�ַ���pSrcMsg�е�����strOrgMsgΪstrReplaceMsg
* @n���ߣ�huangjun
* @n���ڣ�2008-07-31
*/
int HJ_ReplaceInfo(char *pSrcMsg, const string &strOrgMsg, const string &strReplaceMsg)
{
    assert(pSrcMsg);

    string strSrcMsg = pSrcMsg;
    int nOrgLen = strOrgMsg.length();
    int nReplaceLen = strReplaceMsg.length();
    int findarea = 0;
    while ((findarea = strSrcMsg.find(strOrgMsg, findarea)) != -1)
    {
        strSrcMsg.replace(findarea, nOrgLen, strReplaceMsg.c_str());
        findarea += nReplaceLen;
    }

    memcpy(pSrcMsg, strSrcMsg.c_str(), strSrcMsg.length());
    pSrcMsg[strSrcMsg.length()] = 0;

    return 0;
}

int HJ_ReplaceInfo(string &strSrcMsg, const string &strOrgMsg, const string &strReplaceMsg)
{
    int nOrgLen = strOrgMsg.length();
    int nReplaceLen = strReplaceMsg.length();
    int findarea = 0;
    while ((findarea = strSrcMsg.find(strOrgMsg, findarea)) != -1)
    {
        strSrcMsg.replace(findarea, nOrgLen, strReplaceMsg.c_str());
        findarea += nReplaceLen;
    }

    return 0;
}

/*!
* ���ܣ�ת��what��ͷ�������ֽڱ��봮Ϊһ���ֽڶ�����
* @n���ߣ�huangjun
* @n���ڣ�2008-07-31
*/
char x2c(char *what)
{
    assert(what);

    unsigned char digit;

    digit = ((what[0] >= 'A')? ((what[0] & 0xdf) - 'A') + 10 : (what[0] - '0'));
    // digit *= 16;
    digit <<= 4;
    digit += ((what[1] >= 'A')? ((what[1] & 0xdf) - 'A') + 10 : (what[1] - '0'));
    return (digit);
}

/*!
* ���ܣ�ת��������ı����ַ���Ϊ����������
* @n���ߣ�huangjun
* @n���ڣ�2008-07-31
*/
void HJ_unescape_url(char *url)
{
    assert(url);

    register int x, y;

    for (x=0, y=0; url[y]; ++x, ++y)
    {
        if ((url[x] = url[y]) == '%')
        {
            url[x] = x2c(&url[y + 1]);
            y += 2;
        }
        else if (url[x] == '+')
        {
            url[x] = ' ';
        }
    }
    url[x] = '\0';
}

/*!
* ���ܣ���HTTP������ȡ�������в���
* @n���ߣ�huangjun
* @n���ڣ�2008-07-31
*/
int HJ_GetRequestLine(string &strRequestLine, const char *sPkg)
{
    assert(sPkg);

    strRequestLine = "";

    char *pLinePos = NULL;
    if ((pLinePos = strchr(sPkg, '\r')) || (pLinePos = strchr(sPkg, '\n')))
    {
        strRequestLine = string(sPkg, (pLinePos - sPkg));
        return 0;
    }
    else
    {
        return -1;
    }
}

/*!
* ���ܣ���HTTP�����ж�λ��ͷ����λ��
* @n���ߣ�huangjun
* @n���ڣ�2008-07-31
*/
char* HJ_GetPkgHeadPos(const char *sPkg)
{
    assert(sPkg);

    char *pFindPos = NULL;
    // ����������
    if ((NULL != (pFindPos = strchr(sPkg, '\r'))) && (pFindPos[1] == '\n'))
    {
        pFindPos += 2;
    }
    else if (NULL != (pFindPos = strchr(sPkg, '\n')))
    {
        pFindPos += 1;
    }

    return pFindPos;
}

/*!
* ���ܣ���HTTP������ȡ����ͷ����
* @n���ߣ�huangjun
* @n���ڣ�2008-07-31
*/
int HJ_GetPkgHead(string &strHead, const char *sPkg)
{
    assert(sPkg);

    strHead = "";

    char *pBeginPos = HJ_GetPkgHeadPos(sPkg);
    if (!pBeginPos)
    {
        return -1;
    }

    char *pDblLinePos = NULL;
    if ((pDblLinePos = strstr(pBeginPos, "\r\n\r\n")) || (pDblLinePos = strstr(pBeginPos, "\n\n")))
    {
        strHead = string(pBeginPos, (pDblLinePos - pBeginPos));
        return 0;
    }
    else
    {
        return -1;
    }
}

/*!
* ���ܣ���HTTP�����ж�λ���岿��λ��
* @n���ߣ�huangjun
* @n���ڣ�2008-07-31
*/
char* HJ_GetPkgBodyPos(const char *sPkg)
{
    assert(sPkg);

    char *pDblLinePos = NULL;
    if (NULL != (pDblLinePos = strstr(sPkg, "\r\n\r\n")))
    {
        pDblLinePos += 4;
    }
    else if (NULL != (pDblLinePos = strstr(sPkg, "\n\n")))
    {
        pDblLinePos += 2;
    }

    return pDblLinePos;
}

/*!
* ���ܣ���HTTP������ȡ�����岿��
* @n���ߣ�huangjun
* @n���ڣ�2008-07-31
*/
int HJ_GetPkgBody(string &strBody, const char *sPkg)
{
    assert(sPkg);

    strBody = "";

    char *pDblLinePos = HJ_GetPkgBodyPos(sPkg);
    if (!pDblLinePos)
    {
        return -1;
    }

    strBody = string(pDblLinePos);
    return 0;
}

/*!
* ���ܣ���HTTP��ͷ�в�������Ϊsymbol�ֶε���Ӧֵ
* @n���ߣ�huangjun
* @n���ڣ�2008-07-31
*/
int HJ_FindHeadItem(string &strValue, const char *sHttpHead, const char *symbol)
{
    assert(sHttpHead && symbol);

    strValue = "";
    string strSymbol = string(symbol) + ":";

    char *pBeginPos = strstr(sHttpHead, strSymbol.c_str());
    if (!pBeginPos)
    {
        return -1;
    }
    pBeginPos += strSymbol.length();

    char *pEndPos = NULL;
    if ((pEndPos = strchr(pBeginPos, '\r')) || (pEndPos = strchr(pBeginPos, '\n')))
    {
        strValue = string(pBeginPos, (pEndPos - pBeginPos));
    }
    else
    {
        strValue = string(pBeginPos);
    }

    return 0;
}

/*!
* ���ܣ���ĳ���ַ������������Ϊsymbol�ֶε�ֵ
* @n���ߣ�huangjun
* @n���ڣ�2008-07-31
*/
int HJ_FindItemValue(string &strValue, const char *sLineBuffer, const char *symbol)
{
    assert(sLineBuffer && symbol);

    strValue = "";
    string strSymbol = string(" ") + symbol + "=";

    char *pBeginPos = strstr(sLineBuffer, strSymbol.c_str());
    if (!pBeginPos)
    {
        return -1;
    }
    pBeginPos += strSymbol.length();

    char *pEndPos = NULL;
    if ((pEndPos = strchr(pBeginPos, ';')) || (pEndPos = strchr(pBeginPos, '\r'))
        || (pEndPos = strchr(pBeginPos, '\n')))
    {
        strValue = string(pBeginPos, (pEndPos - pBeginPos));
    }
    else
    {
        strValue = string(pBeginPos);
    }

    return 0;
}

/*!
* ���ܣ���Դ�ַ���msg�в�������Ϊsymbol�ֶε���Ӧֵ
* @n���ߣ�huangjun
* @n���ڣ�2008-07-31
*/
string HJ_FindSymbol(const string &msg, const char *symbol)
{
    assert(symbol);

    int loc;

    int ibegin = 0;
    char c;
    while (true)
    {
        ibegin =  msg.find(symbol, ibegin);
        if (ibegin == -1)
        {
            return "";
        }

        if (ibegin != 0)
        {
            c = msg[ibegin-1];
            if (((c >= '0') && (c <= '9')) || ((c >= 'a') && (c <= 'z'))
                || ((c >= 'A') && (c <= 'Z')))
            {
                ibegin++;
                continue;
            }
            else
            {
                break;
            }
        }
        else
        {
            break;
        }
    }

    loc = ibegin;
    if (loc == -1)
    {
        return "";
    }
    int head = msg.find("=", loc);
    if (head == -1)
    {
        return "";
    }

    int tail = msg.find_first_of("&", head);
    if (tail == -1)
    {
        tail = msg.find_first_of(" ", head);
    }

    string strTmp;
    if (tail != -1)
    {
        strTmp = string(msg.begin() + head + 1, msg.begin() + tail);
    }
    else
    {
        strTmp = string(msg.begin() + head + 1, msg.end());
    }

    if (!strTmp.empty())
    {
        char szTemp[8192];
        snprintf(szTemp, sizeof(szTemp), "%s", strTmp.c_str());
        HJ_unescape_url(szTemp);
        return string(szTemp);
    }

    return "";
}

/*!
* ���ܣ���html��Ϣ�������л�ȡContent-Length�ֶε�ֵ
* @n���ߣ�huangjun
* @n���ڣ�2008-07-31
*/
int HJ_GetPageLength(const char *caTempBuffer)
{
    static const char szContentLength[] = "Content-Length: ";

    assert(caTempBuffer);

    // �ƶ���ʼָ�뵽��ͷ���֣�������������
    char *pBeginPos = HJ_GetPkgHeadPos(caTempBuffer);
    if (!pBeginPos)
    {
        return -1;
    }

    if (((pBeginPos = strstr(pBeginPos, szContentLength)) == NULL))
    {
        // DEBUG_PRINT(LM_DEBUG, "NOT FOUND %s\n", szContentLength);
        return -1;
    }
    pBeginPos += (sizeof(szContentLength) - 1);

    char *pEndPos = NULL;
    if (((pEndPos = strchr(pBeginPos, '\n')) == NULL) 
        && ((pEndPos = strchr(pBeginPos, '\r')) == NULL))
    {
        // DEBUG_PRINT(LM_DEBUG, "NOT FOUND ENTER\n");
        return -1;
    }

    int iLength = pEndPos - pBeginPos;
    if ((iLength > 5) || (iLength < 1))
    {
        // DEBUG_PRINT(LM_DEBUG, "string length is illegal!\n");
        return -1;
    }

    char szBuffer[16];
    strncpy(szBuffer, pBeginPos, iLength);
    szBuffer[iLength] = '\0';

    // DEBUG_PRINT(LM_DEBUG, "length string is: %s\n", szBuffer);
    return atoi(szBuffer);
}
