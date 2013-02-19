/************************************************************************************
*
*��    ˾�� Beijing DaxStudio dagital Corp,
*�ļ������� Dax ShortMsg Foundation Libiary
*ʱ    �䣺 2005/11/22
*
**************************************************************************************/

#if !defined (AFX_ENCRYPT_H_INCLUDE_)
#define AFX_ENCRYPT_H_INCLUDE_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define DLL_EXPORT extern "C"
/*
function:
�˺������ڼ���MD5ɢ��ֵ��

  Parameters:
  
	lpInBuffer
	ָ�������ַ����Ļ�����ָ�롣
	
	  lpOutBuffer
	  ָ�����MD5ɢ��ֵ��������ָ�롣
	  (��������Ϊ16)
	  
		Return values:
		�˺����̶����32λ���ȡ�
		����������óɹ����򷵻�ֵΪTRUE�������������ʧ�ܣ�����ֵΪFALSE��
*/
DLL_EXPORT int WINAPI OpenCom(int port, int baud_rate);

DLL_EXPORT void WINAPI CloseCom();

DLL_EXPORT int WINAPI ATCommand(char* ATCmd,char* result);

DLL_EXPORT int WINAPI GetSmCapacity(char* smCapacity);

DLL_EXPORT int WINAPI GetSmsc(char* smsc);

DLL_EXPORT int WINAPI SetSmsc(char* smsc);

DLL_EXPORT int WINAPI SendMsg(char* PhoneID,char* SmsContent);

DLL_EXPORT int WINAPI DeleteMsg(int index);

DLL_EXPORT int WINAPI ReadMsg(int index,char* PhoneID,char* SmsContent,char* Date);

DLL_EXPORT int WINAPI ReadAllMsg(int type,char* PhoneID,char* SmsContent,char* Date,char* Index);

DLL_EXPORT int WINAPI SMSInit();

DLL_EXPORT int WINAPI SetSendModle(int modle);

#endif AFX_ENCRYPT_H_INCLUDE_