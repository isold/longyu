/*! @hj_misc.h
*******************************************************************************
</PRE>
ģ����       ������̴�����ؿ⺯������
�ļ���       ��hj_misc.h
����ļ�     ��hj_misc.cpp
�ļ�ʵ�ֹ��� ������̴�����ؿ⺯������
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

#ifndef __HJ_MISC_H__
#define __HJ_MISC_H__

/* This ignores the SIGPIPE signal.  This is usually a good idea, since
   the default behaviour is to terminate the application.  SIGPIPE is
   sent when you try to write to an unconnected socket.  You should
   check your return codes to make sure you catch this error! */
void HJ_ignore_pipe(void);

/****************************************************************************
* ���ܣ��ѵ�ǰ���̼����̨����
* ���ߣ�huangjun
* ���ڣ�2006-12-08
***************************************************************************/
void HJ_InitDaemon(void);

/****************************************************************************
* ���ܣ��ѵ�ǰ���̵�pidд�뵽ָ���ļ�
* ���ߣ�huangjun
* ���ڣ�2006-12-08
***************************************************************************/
void HJ_CreatePIDFile(char *sPIDFile);

/****************************************************************************
* ���ܣ���չϵͳ��һЩ���Ʋ���
* ���ߣ�huangjun
* ���ڣ�2006-12-08
***************************************************************************/
int HJ_SetRLimit(void);

#define HJ_xchg(ptr,v) ((__typeof__(*(ptr)))HJ___xchg((unsigned long)(v),(ptr),sizeof(*(ptr))))
struct HJ___xchg_dummy { unsigned long a[100]; };
#define HJ___xg(x) ((struct HJ___xchg_dummy *)(x))

static inline unsigned long HJ___xchg(unsigned long x, volatile void *ptr, int size)
{
    switch (size)
    {
    case 1:
        __asm__ __volatile__("xchgb %b0,%1"
            :"=q" (x)
            :"m" (*HJ___xg(ptr)), "0" (x)
            :"memory");
        break;
    case 2:
        __asm__ __volatile__("xchgw %w0,%1"
            :"=r" (x)
            :"m" (*HJ___xg(ptr)), "0" (x)
            :"memory");
        break;
    case 4:
        __asm__ __volatile__("xchgl %0,%1"
            :"=r" (x)
            :"m" (*HJ___xg(ptr)), "0" (x)
            :"memory");
        break;
    case 8:
        __asm__ __volatile__("xchgq %0,%1"
            :"=r" (x)
            :"m" (*HJ___xg(ptr)), "0" (x)
            :"memory");
        break;
    }
    return x;
}

#endif
