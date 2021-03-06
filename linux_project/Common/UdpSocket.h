/********************************************************************
	created:	2011/03/03
	created:	3:3:2011   10:49
	file base:	UdpSocket
	file ext:	h
	author:		王立卫
	
	purpose:	UDP协议简单封装类
*********************************************************************/
#ifndef _UDP_SOCKET_H_
#define _UDP_SOCKET_H_

#include "include.h"
#include "NetPack.h"

#define DEF_UDP_PACK_BUF_LEN 1500

class CUdpSocket
{
public:
	CUdpSocket();
	~CUdpSocket();

	//本地字节序
	bool CreateSocket(const char* ip, const short port);
	bool CreateSocket(void);
	bool Close(int flag = 2);
	//设置socket属性
	bool SetNoBlock(void);
	//发送数据加载默认协议头
	bool SendData(const char* buffer, const unsigned int length,
		const uint32 dst_ip, const unsigned short dst_port);
	//接收数据包解析默认协议头
	bool RecvData(char* buffer, unsigned int &length, 
		uint32 &src_ip, unsigned short &src_port);

	//发送数据未加载默认协议头
	bool SendDataWithoutHeader(const char* buffer, const unsigned int length,
		const uint32 dst_ip, const unsigned short dst_port);
	//接收数据包未解析默认协议头
	bool RecvDataWithoutHeader(char* buffer, unsigned int &length, 
		uint32 &src_ip, unsigned short &src_port);

	//Dump日志
	void Dump(void);
	void TimeWorkFunction(void);

private:
	int miSocket;
};


#endif //_UDP_SOCKET_H





