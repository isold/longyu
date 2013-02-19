
/****************************************************************************************************************************
�汾������	����������Ϣ�����������ι�˾
�ļ�����	DynamicLib.h
�����ˣ�	����ΰ
�������ڣ�	2006-12-07
˵����		��װ��ƽ̨��̬�����ʹ�õĺ������������ö�̬��ʹ��
�汾�ţ�	1.00.000
*****************************************************************************************************************************/

#include "DynamicLib.h"

//���캯��
CDynamicLib::CDynamicLib(void){
	mhDynamic = NULL;
}

//��������
CDynamicLib::~CDynamicLib(void){
	CloseDynamicLib();
}

//�����ļ����ƣ�װ���ƶ���̬��
bool CDynamicLib::LoadDynamicLib(const char* apFileName){
	char lszName[512];
	memset(lszName, 0, 512);

#ifdef WIN32
	sprintf(lszName, "%s%s", apFileName, ".dll");
	mhDynamic = LoadLibrary(lszName);
#else
	sprintf(lszName, "%s%s", apFileName, ".so");
	mhDynamic = dlopen(lszName, RTLD_NOW);

	if (NULL == mhDynamic){
		printf("CDynamicLib::LoadDynamicLib error:%s!", dlerror());
	}
#endif

	return (NULL != mhDynamic);
}

//ȡ���ƶ������ĵ�ַ
void* CDynamicLib::GetDynamicLibFun(const char* apFunName){
	if (NULL == mhDynamic){
		return NULL;
	}

#ifdef WIN32
	return GetProcAddress(mhDynamic, apFunName);
#else
	return dlsym(mhDynamic, apFunName);
#endif
}

//�رմ򿪵Ķ�̬���ӿ�
void CDynamicLib::CloseDynamicLib(){
	if (NULL == mhDynamic){
		return;
	}

#ifdef WIN32
	FreeLibrary(mhDynamic);
#else
	dlclose(mhDynamic);
#endif
	mhDynamic = NULL;
}


