/********************************************************************
	created:	2011/03/08
	created:	8:3:2011   10:39
	file base:	Common
	file ext:	h
	author:		������
	
	purpose:	��������
*********************************************************************/
#ifndef _COMMON_H_
#define _COMMON_H_

#include <grp.h>
#include <sys/types.h>
#include <pwd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <sys/timeb.h>
#include <execinfo.h>
#include <sys/stat.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

using namespace std;

#include "define.h"
#include "debugtrace.h"
#include "md5.h"

struct Passwd{
	static const uint8	BUFF_LEN	=	200;
	typedef struct passwd passwd_t;
	passwd_t	moPd;
	passwd_t*	motmpPwd;
	char		mcbuffer[ BUFF_LEN ];
	Passwd (){
		memset( this, 0, sizeof( Passwd ) );
	}
	~Passwd (){
		memset( this, 0, sizeof( Passwd ) );
	}
};

/************************************************************************/
/*
	int��ֵ���ͻ�
*/
/************************************************************************/
template <int v>
struct Int2Type{
	enum { value = v };
};

/************************************************************************/
/*
	Short��ֵ���ͻ�
*/
/************************************************************************/
template <short v>
struct Short2Type{
	enum { value = v };
};

class CCommon{
public:
	static uint32 GetProcessId();
	static uint32 GetProcessParentId();
	static void SetOpenFiles(uint32 max_file_opens_number);
	static void GetAppPath(char* apPath, int aiLen);
	static void CreatePath(char* apPath);
	static uint64 get_current_time(void);
	static uint64 escape_time(uint64 last_time);

	//��ȡ��ǰʱ�� 2009-12-02 12:02:30:234
	static string get_now(void);
	//����Ƿ�ʱ
	static bool CheckTimeOut(const INT64 &ai64LastTime,const INT64 &ai64TimeInterval);
	
	//����IP��ַ�Ͱ���ż�������
	static INT64 MakeIpPortKey(const sockaddr_in& addr, const uint16_t awPackSerial);
	static unsigned int GetSocketAddr(const sockaddr_in& addr);
	static unsigned int GetSocketAddr(const char* addr);
	static void SetSocketAddr(sockaddr_in& addr, unsigned int alAddr);
	static void SetSocketAddr(sockaddr_in& addr, unsigned int alAddr, unsigned short alPort);
	static char* GetIPAddr(unsigned int alAddr);
	static char* Getctime(time_t *apTime);

	//��ȡ�����ֽ����ַ
	static void GetSocketAddr(const sockaddr_in &addr, uint32 &ip, uint16 &port);
	//��װ������ö�ջ�Ĺ���
	static void DumpStack();

	template <class T>
	static void PeriodicTask(uint32 time_gap, uint64 &last_time, T* ptr, void(T::*fun)()){
		uint64 time_now = CCommon::get_current_time();
		if(time_now > last_time + time_gap){
			(ptr->*fun)();  
		}
		last_time = time_now;
	}
	//ȡ��һ���������,ȡֵ��Χ�� 1 -- rand_max,rand_max�������1
	static unsigned int GetRandInt(unsigned int rand_max);
	
	//���ַ�������������仯˳��,aiChgTimesָ���任����
	static string ChgStrInRandomSeq(const string& astrData,int aiChgTimes = 3);

	// ��	�ܣ������û��˻�Name����û���Ϣ��
	// ��	����lszUserName �û��˻�����struct Passwd* һ��Ԥ��ʵ������ͬ���Ͷ���
	// ��	�أ��ɹ� SUCCEEDED�� ʧ�� FAILED��
	static uint8 GetPasswd ( const char* lszUserName, struct Passwd* opPasswd );

	// ��	�ܣ������û��˻�Name�����ӽ�������ʱ���û����û���Ȩ�ޡ�
	// ��	����lszUserName ��Ҫָ�����û��˻�Name��
	// ��	�أ���
	static void	SetUA2SomeBody ( const char* lszUserName );

	// ��	�ܣ���õ�ǰ�Ĺ���·����
	// ��	����oszcPath Ԥ�ȷ�������ڴ洢·�����ڴ�ռ䣬 ilen �ڴ�ռ�Ĵ�С��
	// ��	�أ��ɹ� SUCCEEDED�� ʧ�� FAILED��
	static uint8 GetCurWorkingPath ( char* oszcPath, int ilen );

	//��ȡmd5ֵ 16�ֽ�
	static int MakeMD5WithBuffer16(uint8_t *Input, unsigned int InputLen, uint8_t *Output)
	{
		MD5_CTX md5;
		md5.MD5Update (Input, InputLen);
		md5.MD5Final (Output);
		return 0;
	}

	//��ֵת���ַ���
	static void ConvertString(char *apIn,char* alpOut)
	{
		uint8_t lcTemp=0;
		for(int i=0;i<16;i++)
		{
			lcTemp=apIn[i];
			lcTemp=lcTemp&0xF0;
			lcTemp=lcTemp>>4;
			if (lcTemp<10)
				alpOut[2*i]=lcTemp+'0';
			else
				alpOut[2*i]=lcTemp+87;
			lcTemp=apIn[i];
			lcTemp=lcTemp&0x0F;
			if (lcTemp<10)
				alpOut[2*i+1]=lcTemp+'0';
			else
				alpOut[2*i+1]=lcTemp+87;
		}
		alpOut[32]=0;
	}

	//��ȡmd5ֵ 32λ
	static int MakeMD5WithBuffer32(uint8_t *Input, unsigned int InputLen, uint8_t *Output)
	{
		uint8_t lpMD5[16];
		MD5_CTX md5;
		md5.MD5Update (Input, InputLen);
		md5.MD5Final (lpMD5);
		CCommon::ConvertString((char*)lpMD5, (char*)Output);
		return 0;
	}
};

template <class State, class T>
class AbstractFSM{
public:
	AbstractFSM(){}
	~AbstractFSM(){}

	void SetState(State st){
		_st = st;
	}

	State GetState(void){
		return _st;
	}

	bool IsState(State st){
		return (_st == st) ? true : false;
	}

	bool IsNotState(State st){
		return (_st != st) ? true : false;
	}
	void ChangeState(State end_state, T* ptr, bool(T::*fun)()){
		bool lbRet = (ptr->*fun)();
		if(lbRet){
			_st = end_state;
		}
	}

private:
	State _st;
};


#endif //_COMMON_H_



