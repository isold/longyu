/*! @file hj_mysql.h
* *****************************************************************************
* @n</PRE>
* @nģ����       ��mysql���ݿ������ؿ⺯������
* @n�ļ���       ��hj_mysql.h
* @n����ļ�     ��hj_mysql.cpp
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
#ifndef __HJ_MYSQL_H__
#define __HJ_MYSQL_H__

#include <mysql/mysql.h>
#include <mysql/errmsg.h>

typedef struct
{
    // ���ݿ�������
    char sHost[64];
    // ���ݿ�����Ķ˿ں�
    unsigned int uPort;
    // ���ݿ������û���
    char sUser[64];
    // ���ݿ���������
    char sPasswd[64];
    // ���ݿ���
    char sDB[64];
} HJ_MYSQL_CONN;

typedef struct
{
    HJ_MYSQL_CONN stMysqlConn; // ���ݿ�������Ϣ

    MYSQL stMysql;              // Mysql����
    int  iConnected;            // ��ǰ���ݿ��Ƿ��Ѿ����ӣ�0-û�У�1-������

    char szQuery[10240];        // ��ǰ������SQL���
    int  iQueryType;            // ��ǰ����SQL����Ƿ���Ҫ����ֵ��0-��Ҫ��1-��Ҫ��Ҳ����select��ѯ

    MYSQL_RES *pstRes;          // ��ǰ����SQL��ķ��ؼ�
    MYSQL_ROW ppRow;            // ��ǰ����SQL��ͨ��ȡһ�к�ķ�����

    // int nResNotNull;         // ��ǰ����SQL���RecordSet�Ƿ�Ϊ�գ�0-Ϊ�գ�1-�ǿ�
    int nResNum;                // ��ǰ����SQL���RecordSet�ļ�¼��Ŀ
} HJ_MYSQL_LINK;

/*!
* ���ܣ���ʼ��Mysql����
* @n���ߣ�huangjun
* @n���ڣ�2008-07-31
*/
void HJ_Init_Mysql(HJ_MYSQL_LINK *pstMysqlLink);

/*!
* ���ܣ�����Mysql
* @n���ߣ�huangjun
* @n���ڣ�2008-07-31
*/
int HJ_Mysql_ConnectDB(HJ_MYSQL_LINK *pstMysqlLink, const char *pEncode);

/*!
* ���ܣ��ر�Mysql����
* @n���ߣ�huangjun
* @n���ڣ�2008-07-31
*/
int HJ_Mysql_CloseDB(HJ_MYSQL_LINK *pstMysqlLink);

/*!
* ���ܣ�ִ��Mysql�������
* @n���ߣ�huangjun
* @n���ڣ�2008-07-31
*/
int HJ_Mysql_ExecSQL(HJ_MYSQL_LINK *pstMysqlLink);

/*!
* ���ܣ���Mysql���ؼ���ȡ��һ��
* @n���ߣ�huangjun
* @n���ڣ�2008-07-31
*/
int HJ_Mysql_FetchRow(HJ_MYSQL_LINK* pstMysqlLink);

/*!
* ���ܣ��鿴���һ�ε�Mysql����Ӱ������
* @n���ߣ�huangjun
* @n���ڣ�2008-07-31
*/
int HJ_Mysql_AffectedRow(HJ_MYSQL_LINK *pstMysqlLink);

/*!
* ���ܣ��ͷ����һ��Mysql�������ؼ�
* @n���ߣ�huangjun
* @n���ڣ�2008-07-31
*/
int HJ_Mysql_FreeResult(HJ_MYSQL_LINK *pstMysqlLink);

/*!
* ���ܣ��鿴���һ��Mysql�������ؼ����ֶ���
* @n���ߣ�huangjun
* @n���ڣ�2008-07-31
*/
int HJ_Mysql_NumFields(HJ_MYSQL_LINK *pstMysqlLink);

/*!
* ���ܣ��鿴���һ��Mysql�������ؼ�������
* @n���ߣ�huangjun
* @n���ڣ�2008-07-31
*/
int HJ_Mysql_NumRows(HJ_MYSQL_LINK *pstMysqlLink);

#endif
