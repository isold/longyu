/*! @hj_ini.h
*******************************************************************************
</PRE>
ģ����       ����ȡini�ļ���ع�������
�ļ���       ��hj_ini.h
����ļ�     ��hj_ini.cpp
�ļ�ʵ�ֹ��� ����ȡini�ļ���ع�������
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

#ifndef __HJ_INI_H__
#define __HJ_INI_H__

#define HJ_INI_MAX_OPENED_NUM               255

#define HJ_INI_OPEN_NORMAL                  0
#define HJ_INI_OPEN_FAIL_IGNORE             1

#define HJ_INI_ERROR_FAIL_TO_ALLOC_MEM    (HJ_INI_ERROR_BASE-1)
#define HJ_INI_ERROR_NO_FREE_HANDLE       (HJ_INI_ERROR_BASE-2)
#define HJ_INI_ERROR_FAIL_TO_OPEN_FILE    (HJ_INI_ERROR_BASE-3)
#define HJ_INI_ERROR_INVALID_HANDLE       (HJ_INI_ERROR_BASE-4)
#define HJ_INI_ERROR_FAIL_TO_READ_FILE    (HJ_INI_ERROR_BASE-5)
#define HJ_INI_ERROR_FAIL_TO_WRITE        (HJ_INI_ERROR_BASE-6)
#define HJ_INI_ERROR_FAIL_TO_SEEK         (HJ_INI_ERROR_BASE-7)

int HJ_Ini_Load(char *sIniFileName, int iMode);
void HJ_Ini_Free(int iIniHandle);
int HJ_Ini_Dump(int iIniHandle);

int HJ_Ini_ReadString(int iIniHandle, char *sSection, char *sIdent
    , char *sDefault, char *sValue, int iSize);

int HJ_Ini_WriteString(int iIniHandle, char *sSection, char *sIdent, char *sValue);
int HJ_Ini_RemoveSection(int iIniHandle, char *sSection);
int HJ_Ini_RemoveKey(int iIniHandle, char *sSection, char *sIdent);

int HJ_Ini_Save(int iIniHandle, char *sIniFileName);
void HJ_Ini_FreeAll(void);

int HJ_Ini_ShmLoad(char *sShm, int iMode);

#endif
