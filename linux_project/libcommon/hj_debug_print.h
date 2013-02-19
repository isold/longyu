#ifndef __HJ_DEBUG_PRINT_H__
#define __HJ_DEBUG_PRINT_H__

#include <stdio.h>

#define LM_DEBUG    0x01    // ���������
#define LM_TRACE    0x02    // �������ټ�
#define LM_INFO     0x04    // ��Ϣ�����
#define LM_ERROR    0x08    // ���������
#define LM_EXCEPT   0x10    // �����쳣��

/*!
* DEBUG_LEVEL : ��־�������λ����
* @n�ӵ�λ����λÿλ����Ϊ
* @n0x00-����ʾ�κ���Ϣ��0x01-��ʾ�쳣�����0x02-��ʾ���������0x04-����������Ϣ
* @n0x08-��ʾ���������Ϣ
*/
// #ifndef DEBUG_LEVEL
// #define DEBUG_LEVEL (LM_DEBUG|LM_INFO|LM_ERROR|LM_EXCEPT)
// #endif

#if DEBUG_LEVEL
#define DEBUG_PRINT(level, fmt, args...) \
do{ \
    if (DEBUG_LEVEL & level) \
    { \
        printf("%s-%s-[%d:%d]-%s: " fmt, #level, __FILE__, getpid(), __LINE__, __FUNCTION__ , ##args); \
    } \
}while(false)
#else
#define DEBUG_PRINT(level, fmt, args...)
#endif

#endif
