/*! @hj_macro.h
*******************************************************************************
</PRE>
ģ����       �������ͨ�ú궨��
�ļ���       ��hj_macro.h
����ļ�     ��hj_macro.cpp
�ļ�ʵ�ֹ��� �������ͨ�ú궨��
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

#ifndef __HJ_MACRO_H__
#define __HJ_MACRO_H__

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;

#define MIN(a,b) ((a>b)?b:a)
#define MAX(a,b) ((a>b)?a:b)

// Uncomment this line under unix/linux
#define HJ_UNIX

#ifdef HJ_UNIX

#define O_BINARY    0
#define O_DENYNONE  0

#else

#include <io.h>

#endif

#define HJ_STR_ERROR_BASE    -1000
#define HJ_INI_ERROR_BASE    -2000

#endif
