
/****************************************************************************************************************************
�汾������	����������Ϣ�����������ι�˾
�ļ�����	DynamicLib.h
�����ˣ�	����ΰ
�������ڣ�	2006-12-07
˵����		��װ��ƽ̨��̬�����ʹ�õĺ������������ö�̬��ʹ��
�汾�ţ�	1.00.000
*****************************************************************************************************************************/

#ifndef DEF_SINA_DYNAMIC_LINK_LIBRARY_H
#define DEF_SINA_DYNAMIC_LINK_LIBRARY_H

#ifdef WIN32
#include <Windows.h>
#else
#include <dlfcn.h> 
#endif 

#include "include.h"

class CDynamicLib{
public:
	//���캯��
	CDynamicLib(void);

	//��������
	~CDynamicLib(void);

public:
	//�����ļ����ƣ�װ���ƶ���̬�⣬ע�⴫���ļ���ʱ��������չ��
	bool LoadDynamicLib(const char* apFileName);

	//ȡ���ƶ������ĵ�ַ
	void* GetDynamicLibFun(const char* apFunName); 

	//�رմ򿪵Ķ�̬���ӿ�
	void CloseDynamicLib();

private:

#ifdef WIN32
	HMODULE mhDynamic;	//��̬���ӿ�򿪺�ľ��
#else
	void* mhDynamic;	//��̬���ӿ�򿪺�ľ��
#endif
};

#endif /*DEF_SINA_DYNAMIC_LINK_LIBRARY_H*/


