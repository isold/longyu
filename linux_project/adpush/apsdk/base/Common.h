/********************************************************************
created:	2011/03/08
created:	8:3:2011   10:39
file base:	Common
file ext:	h
author:		王立卫

purpose:	公共方法
*********************************************************************/
#ifndef _COMMON_H_
#define _COMMON_H_
#include "include.h"

#if defined(__linux__) || defined(__APPLE__)

#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/timeb.h>
#include <sys/stat.h>

#include <arpa/inet.h>
#include <grp.h>
#include <pwd.h>
#include <errno.h>
#include <unistd.h>

#endif

#ifdef _WIN32

#include <Windows.h>
#include <sys/timeb.h>
#include <time.h>

#endif

#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
using namespace std;

#include "define.h"
#include "md5.h"

class CCommon
{
public:
	static void GetAppPath(char* apPath, int aiLen);
	static void CreatePath(char* apPath);
	static uint64_t get_current_time(void);

	//获取当前时间 
	static string get_now(void);

	//检测是否超时
	static bool CheckTimeOut(const int64_t &ai64LastTime,const int64_t &ai64TimeInterval);

	//根据IP地址和包序号计算主键
	static int64_t MakeIpPortKey(const sockaddr_in& addr, const uint16_t awPackSerial);
	static unsigned int GetSocketAddr(const sockaddr_in& addr);
	static unsigned int GetSocketAddr(const char* addr);
	static void SetSocketAddr(sockaddr_in& addr, unsigned int alAddr);
	static void SetSocketAddr(sockaddr_in& addr, unsigned int alAddr, uint16_t alPort);
	static char* GetIPAddr(unsigned int alAddr);
	static char* Getctime(time_t *apTime);
	static int GetLastErrorCode()
	{
#if defined(__linux__) || defined(__APPLE__)
		return errno;
#endif

#ifdef _WIN32
		return GetLastError();
#endif
	}

	//time 单位豪秒
	static void thread_sleep(uint32_t time)
	{
#if defined(__linux__) || defined(__APPLE__)
		usleep(1000*time);
#endif

#ifdef _WIN32
		Sleep(time);
#endif
	}

	//获取本地字节序地址
	static void GetSocketAddr(const sockaddr_in &addr, unsigned int &ip, uint16_t &port);
	//封装输出调用堆栈的功能
	static void DumpStack();

	template <class T>
	static void PeriodicTask(unsigned int time_gap, uint64_t &last_time, T* ptr, void(T::*fun)())
	{
		uint64_t time_now = CCommon::get_current_time();
		if(time_now > last_time + time_gap)
		{
			(ptr->*fun)();  
		}
		last_time = time_now;
	}
	//取得一个随机整数,取值范围在 1 -- rand_max,rand_max必须大于1
	static unsigned int GetRandInt(unsigned int rand_max);

	//将字符串的内容随机变化顺序,aiChgTimes指定变换次数
	static string ChgStrInRandomSeq(const string& astrData,int aiChgTimes = 3);
	//获取md5值 16字节
	static int MakeMD5WithBuffer16(uint8_t *Input, unsigned int InputLen, uint8_t *Output)
	{
		MD5_CTX md5;
		md5.MD5Update (Input, InputLen);
		md5.MD5Final (Output);
		return 0;
	}

	//数值转成字符串
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

	//获取md5值 32位
	static int MakeMD5WithBuffer32(uint8_t *Input, unsigned int InputLen, uint8_t *Output)
	{
		uint8_t lpMD5[16];
		MD5_CTX md5;
		md5.MD5Update (Input, InputLen);
		md5.MD5Final (lpMD5);
		CCommon::ConvertString((char*)lpMD5, (char*)Output);
		return 0;
	}
	static void LOGTRACE(const char* szFmt, ...)
	{
#ifdef OUTPUT_LOG
		char strPrintBuff[1024] = {0};
		va_list argptr;
		va_start(argptr, szFmt);
		vsprintf(strPrintBuff, szFmt, argptr);
		va_end(argptr);
#ifdef OS_ANDROID

#else
		cout<<strPrintBuff<<endl;
#endif
#endif //OUTPUT_LOG
	}

	// 64位主机字节序转网络字节序
	static uint64_t _htonq(uint64_t u64HostValue);

	// 64位网络字节序转主机字节序
	static uint64_t _ntohq(uint64_t u64NetValue);
};

template <class State, class T>
class AbstractFSM
{
public:
	AbstractFSM(){}
	~AbstractFSM(){}

	void SetState(State st)
	{
		_st = st;
	}

	State GetState(void)
	{
		return _st;
	}

	bool IsState(State st)
	{
		return (_st == st) ? true : false;
	}

	bool IsNotState(State st)
	{
		return (_st != st) ? true : false;
	}
	void ChangeState(State end_state, T* ptr, bool(T::*fun)())
	{
		bool lbRet = (ptr->*fun)();
		if(lbRet)
		{
			_st = end_state;
		}
	}

private:
	State _st;
};


#endif //_COMMON_H_

