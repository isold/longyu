/********************************************************************
created:	2011/03/08
created:	8:3:2011   10:11
file base:	NetPack
file ext:	h
author:		������

purpose:	TCPЭ��Ӧ�����ݰ��ṹ
*********************************************************************/
#ifndef _NET_PACK_H_
#define _NET_PACK_H_

#include "include.h"
#include "StandardSerialize.h"

#define DEF_NET_PACK_HEAD_PREFIX 0x99
#define DEF_BUFFER_LEN (5*1024)


/*
  ����IO�����ӿ�
*/
class i_net_io
{
public:	
	virtual bool open() =0;		
	virtual void close()=0;
	virtual int  read(int ai_sock, void *ap_buf, int ai_num)=0;	
	virtual int  write(int ai_sock, const void *ap_buf, int ai_num)=0;
		
	virtual void release() =0;
};

class CNetPack{
public:
	CNetPack(){}
	virtual ~CNetPack(){}
	virtual bool CheckPack() = 0;
	virtual int Pack(const char* in_buffer, const int in_length, char* out_buffer, int &out_length) = 0;
	//0 �����Ȳ��� 1 ���һ���� -1 ���ʧ��
	virtual int Unpack(const char* in_buffer, const int in_length, char* out_buffer, int &out_buffer_length, int &out_data_length) = 0;
	
public:
	//�����IO����
	virtual i_net_io* create_svr_io(int ai_sock);
	//�ͻ���IO����
	virtual i_net_io* create_clt_io(int ai_sock);

public:
	int _min_pack_size;
	int _max_pack_size;
};

class CNetPackVersion1 : public CNetPack{
public:
	CNetPackVersion1();
	virtual ~CNetPackVersion1();

	int Pack(const char* in_buffer, const int in_length, char* out_buffer, int &out_length);
	int Unpack(const char* in_buffer, const int in_length, char* out_buffer, int &out_buffer_length, int &out_data_length);

	bool CheckPack(){
		if((recv_flag == send_flag) && 
			(recv_length <= (_max_pack_size-_min_pack_size)) && 
			(recv_length >= 2)){
			return true;
		}
		else{
			TRACE(1, "CNetPackHead::CheckHead Э����ʧ�ܡ�FLAG = "<<
				recv_flag<<" Length = "<<recv_length);
			return false;
		}
	}
private:
	int Serialize(CStandardSerialize & aoStandardSerialize);

public:
	//��������ͷ
	int send_flag;
	int send_version;
	int send_id;
	int send_time;
	int send_encry;
	int send_compress;
	int send_error_code;
	int send_length;

	//��������ͷ
	int recv_flag;
	int recv_version;
	int recv_id;
	int recv_time;
	int recv_encry;
	int recv_compress;
	int recv_error_code;
	int recv_length;
};

class CNetPackVersion2 : public CNetPack{
public:
	CNetPackVersion2();
	virtual ~CNetPackVersion2();

	int Pack(const char* in_buffer, const int in_length, char* out_buffer, int &out_length);
	int Unpack(const char* in_buffer, const int in_length, char* out_buffer, int &out_buffer_length, int &out_data_length);

	bool CheckPack(){
		if((recv_flag == send_flag) && 
			(recv_length <= (_max_pack_size-_min_pack_size)) && 
			(recv_length >= 2)){
				return true;
		}
		else{
			TRACE(1, "CNetPackHead::CheckHead Э����ʧ�ܡ�FLAG = "<<
				recv_flag<<" Length = "<<recv_length);
			return false;
		}
	}

private:
	int Serialize(CStandardSerialize &aoStandardSerialize);
	string GetEncryKey(uint64_t user_id, uint32_t encry_type){
		stringstream  strStream;
		strStream<<user_id;
		string strUserId = "";
		strStream>>strUserId;
		char strMd5[33];
		memset(strMd5, 0, 33);
		CCommon::MakeMD5WithBuffer32((uint8_t*)strUserId.c_str(), strUserId.length(), (uint8_t*)strMd5);
		char strEncryKey[17];
		memset(strEncryKey, 0, 17);
		memcpy(strEncryKey, strMd5+7, 16);
		return strEncryKey;
	}

public:
	//��������ͷ
	int32 send_flag;
	int16 send_version;
	int16 send_length;
	int8 send_encry;
	int8 send_extend1;
	int16 send_extend2;
	int32 send_check_key;
	int64 send_id;

	//��������ͷ
	int32 recv_flag;
	int16 recv_version;
	int16 recv_length;
	int8 recv_encry;
	int8 recv_extend1;
	int16 recv_extend2;
	int32 recv_check_key;
	int64 recv_id;
};

#endif //_NET_PACK_H_











