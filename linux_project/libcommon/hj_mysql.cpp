/*! @file hj_mysql.cpp
* *****************************************************************************
* @n</PRE>
* @nģ����       ��mysql���ݿ������ؿ⺯������
* @n�ļ���       ��hj_mysql.cpp
* @n����ļ�     ��hj_mysql.h
* @n�ļ�ʵ�ֹ��� ��mysql���ݿ������ؿ⺯������
* @n����         ��huangjun - �����ǹ���(http://www.shenzhoustar.com)
* @n�汾         ��1.0.1
* @n-----------------------------------------------------------------------------
* @n��ע��
* @n-----------------------------------------------------------------------------
* @n�޸ļ�¼��
* @n����        �汾        �޸���      �޸�����
* @n20080731    1.0.1       Huangjun    Created
* @n</PRE>
* @n****************************************************************************/
#include <assert.h>
#include <stdio.h>
#include <strings.h>

#include "hj_mysql.h"

/*!
* ���ܣ���ʼ��Mysql����
* @n���ߣ�huangjun
* @n���ڣ�2008-07-31
*/
void HJ_Init_Mysql(HJ_MYSQL_LINK *pstMysqlLink)
{
    assert(pstMysqlLink);

    bzero(pstMysqlLink, sizeof(HJ_MYSQL_LINK));

    // ��ʼ��Mysql����
    mysql_init(&(pstMysqlLink->stMysql));
}

/*!
* ���ܣ�����Mysql
* @n���ߣ�huangjun
* @n���ڣ�2008-07-31
*/
int HJ_Mysql_ConnectDB(HJ_MYSQL_LINK *pstMysqlLink, const char *pEncode)
{
    assert(pstMysqlLink);

    if (pstMysqlLink->iConnected)
    {
        HJ_Mysql_CloseDB(pstMysqlLink);
        pstMysqlLink->iConnected = 0;
    }

    if (!mysql_real_connect(&(pstMysqlLink->stMysql)
        , pstMysqlLink->stMysqlConn.sHost
        , pstMysqlLink->stMysqlConn.sUser
        , pstMysqlLink->stMysqlConn.sPasswd
        , pstMysqlLink->stMysqlConn.sDB
        , pstMysqlLink->stMysqlConn.uPort
        , NULL, 0))
    {
        return -1;
    }

    if (pEncode)
    {
        char szSetEncode[32];
        snprintf(szSetEncode, sizeof(szSetEncode), "SET NAMES %s"
            , pEncode);
        if (mysql_query(&(pstMysqlLink->stMysql), szSetEncode))
        {
            mysql_close(&(pstMysqlLink->stMysql));
            return -3;
        }
    }

    pstMysqlLink->iConnected = 1;

    return 0;
}

/*!
* ���ܣ��ر�Mysql����
* @n���ߣ�huangjun
* @n���ڣ�2008-07-31
*/
int HJ_Mysql_CloseDB(HJ_MYSQL_LINK *pstMysqlLink)
{
    assert(pstMysqlLink);

    if (pstMysqlLink->iConnected)
    {
        HJ_Mysql_FreeResult(pstMysqlLink);
        mysql_close(&(pstMysqlLink->stMysql));
        pstMysqlLink->iConnected = 0;
    }

    return 0;
}

/*!
* ���ܣ�ִ��Mysql�������
* @n���ߣ�huangjun
* @n���ڣ�2008-07-31
*/
int HJ_Mysql_ExecSQL(HJ_MYSQL_LINK *pstMysqlLink)
{
    assert(pstMysqlLink);

    if (!pstMysqlLink->iConnected)
    {
        return -1;
    }

    if (pstMysqlLink->iQueryType == 1)
    {
        if (strncasecmp("select", pstMysqlLink->szQuery, 6))
        {
            return -2;
        }

        HJ_Mysql_FreeResult(pstMysqlLink);
    }

    if (mysql_query(&(pstMysqlLink->stMysql), pstMysqlLink->szQuery))
    {
        if (mysql_errno(&(pstMysqlLink->stMysql)) == CR_SERVER_GONE_ERROR)
        {
            HJ_Mysql_CloseDB(pstMysqlLink);
            return -3;
        }

        return -4;
    }

    if (pstMysqlLink->iQueryType == 1)
    {
        pstMysqlLink->pstRes = mysql_store_result(&(pstMysqlLink->stMysql));
        if (!pstMysqlLink->pstRes)
        {
            pstMysqlLink->nResNum = 0;
            return -5;
        }
        else
        {
            pstMysqlLink->nResNum = mysql_num_rows(pstMysqlLink->pstRes);
        }
    }

    return 0;
}

/*!
* ���ܣ���Mysql���ؼ���ȡ��һ��
* @n���ߣ�huangjun
* @n���ڣ�2008-07-31
*/
int HJ_Mysql_FetchRow(HJ_MYSQL_LINK* pstMysqlLink)
{
    assert(pstMysqlLink);

    if (!pstMysqlLink->pstRes || (pstMysqlLink->nResNum == 0))
    {
        return -1;
    }

    pstMysqlLink->ppRow = mysql_fetch_row(pstMysqlLink->pstRes);

    return pstMysqlLink->ppRow? 0 : -2;
}

/*!
* ���ܣ��鿴���һ�ε�Mysql����Ӱ������
* @n���ߣ�huangjun
* @n���ڣ�2008-07-31
*/
int HJ_Mysql_AffectedRow(HJ_MYSQL_LINK *pstMysqlLink)
{
    assert(pstMysqlLink);

    if (pstMysqlLink->iConnected == 0)
    {
        return -1;
    }

    return mysql_affected_rows(&pstMysqlLink->stMysql);
}

/*!
* ���ܣ��ͷ����һ��Mysql�������ؼ�
* @n���ߣ�huangjun
* @n���ڣ�2008-07-31
*/
int HJ_Mysql_FreeResult(HJ_MYSQL_LINK *pstMysqlLink)
{
    assert(pstMysqlLink);

    if (pstMysqlLink->pstRes)
    {
        mysql_free_result(pstMysqlLink->pstRes);
        pstMysqlLink->pstRes = NULL;
    }

    return 0;
}

/*!
* ���ܣ��鿴���һ��Mysql�������ؼ����ֶ���
* @n���ߣ�huangjun
* @n���ڣ�2008-07-31
*/
int HJ_Mysql_NumFields(HJ_MYSQL_LINK *pstMysqlLink)
{
    assert(pstMysqlLink);

    if (!pstMysqlLink->pstRes)
    {
        return -1;
    }

    return mysql_num_fields(pstMysqlLink->pstRes);
}

/*!
* ���ܣ��鿴���һ��Mysql�������ؼ�������
* @n���ߣ�huangjun
* @n���ڣ�2008-07-31
*/
int HJ_Mysql_NumRows(HJ_MYSQL_LINK *pstMysqlLink)
{
    assert(pstMysqlLink);

    if (!pstMysqlLink->pstRes)
    {
        return -1;
    }

    return mysql_num_rows(pstMysqlLink->pstRes);
}
