/********************************************************************
	created:	2011/03/08
	created:	8:3:2011   10:12
	file base:	NetPack
	file ext:	cpp
	author:		������
	
	purpose:	TCPЭ��Ӧ�����ݰ��ṹ
*********************************************************************/
#include "NetPack.h"

#define TCP_PACK_VERSION		1		//TCP���汾

/*TCP���ṹ(������Ϊ����):
��ͷ(3)+������(2)+�汾(1)+ʱ���(2)+������(n)+��β(3)+������(2)
TCP���̶��ṹ����Ϊ13���ܳ�Ϊ13+n	*/
#define TCP_PACK_STRUCT_LEN		13		//TCP���̶��ṹ����

static char macPackHeader[] = "\01\02\03\0";
static char macPackTail[] = "\04\05\06\0";

static uint8_t STX = 0x03;
static uint8_t ETX = 0x07;

CNetPackCRS::CNetPackCRS(){
	_min_pack_size = TCP_PACK_STRUCT_LEN;
	_max_pack_size = DEF_MAX_BUFFER_LEN;
}

CNetPackCRS::~CNetPackCRS(){

}


int	CNetPackCRS::Pack(const char * in_buffer, const int in_length, char * out_buffer, int &out_length)
{
	if (in_length > out_length || in_length > DEF_MAX_BUFFER_LEN)  //���������ɰ�����
		return -1;

	uint16_t lwDecryptLen = in_length;

#ifdef LM_ENCRYPT	//����
	//�ı��8�ı���
	//lwDecryptLen = 8-(in_length+2)%8 + in_length + 2;
	char lpcEncrypt[DEF_MAX_BUFFER_LEN];
	if (moEnDecrypt.LmEncrypt((char*)in_buffer, in_length, lpcEncrypt, lwDecryptLen) == -1) //����ʧ��
	{
		return -3;
	}
	assert(lwDecryptLen <= DEF_MAX_BUFFER_LEN);
	//���ܹ���
	if (lwDecryptLen > out_length)
		return -2;
#endif

	uint8_t lbyVersion = TCP_PACK_VERSION;
	int liResult = 0;

	CStandardSerialize loStdSerialize(out_buffer,out_length, CStandardSerialize::STORE);

	loStdSerialize.Serialize(macPackHeader,3,out_length);	//��ͷ
	loStdSerialize.Serialize(lwDecryptLen);					//����
	loStdSerialize.Serialize(lbyVersion);					//�汾
	uint16_t lwPackSerial = GetPackSerial();
	loStdSerialize.Serialize(lwPackSerial);					//ʱ���

	//���л�����
#ifdef LM_ENCRYPT
	loStdSerialize.Serialize(lpcEncrypt,lwDecryptLen,DEF_MAX_BUFFER_LEN);
#else
	loStdSerialize.Serialize(in_buffer,in_length,in_length);
#endif
	loStdSerialize.Serialize(macPackTail,3,3);				//��β
	loStdSerialize.Serialize(lwDecryptLen);					//����

	liResult = loStdSerialize.getDataLen();					//�õ�������ܳ�

	out_length = liResult;
	return liResult;
}

int CNetPackCRS::Unpack(const char *in_buffer, const int in_length, 
	char * out_buffer, int &out_length, int &out_data_length){
		if (in_length ==0)
			return 0;

		uint16_t lwTcpPackLen = DEF_MAX_BUFFER_LEN;

		//TCPͨѶ��������Ȳ���
		if(in_length < TCP_PACK_STRUCT_LEN)
			return 0;


		CStandardSerialize loStdSerialize((char*)in_buffer,in_length, CStandardSerialize::LOAD);

		//�жϰ�ͷ
		char lacPackTag[4];
		loStdSerialize.Serialize(lacPackTag,3,4);	//��ͷ
		if(memcmp(lacPackTag,macPackHeader,3)!=0)
		{
			return -3;  //ͷ����
		}

		//�ж��Ƿ�������ɰ�����
		uint16_t lwPacklenHeader=0;
		loStdSerialize.Serialize(lwPacklenHeader);	//����
		if(lwPacklenHeader > (in_length - TCP_PACK_STRUCT_LEN)){
			return 0;
		}
		assert(lwPacklenHeader <= out_length);
		//�õ��汾
		uint8_t lbyVersion = 0;
		loStdSerialize.Serialize(lbyVersion);		//�汾
		uint16_t awtimestamp = 0;
		loStdSerialize.Serialize(awtimestamp);		//ʱ���

		//��������
#ifdef LM_ENCRYPT
		char lpRawData[DEF_MAX_BUFFER_LEN];
		loStdSerialize.Serialize(lpRawData,lwPacklenHeader,DEF_MAX_BUFFER_LEN);
		uint16_t  inlen = lwPacklenHeader;
		uint16_t outlen = 0;
		if (moEnDecrypt.LmDecrypt(lpRawData, inlen, out_buffer, outlen) == -1) //����ʧ��
		{
			return -7;	//���ܴ���
		}
		out_length = outlen;
#else
		loStdSerialize.Serialize(out_buffer,lwPacklenHeader,out_length);
#endif
		//�жϰ�β
		loStdSerialize.Serialize(lacPackTag,3,4);   //��β
		if (memcmp(lacPackTag,macPackTail,3) != 0)
		{
			return -5;
		}

		//�жϰ�ǰ�󳤶�
		uint16_t lwPacklenTail  =0;
		loStdSerialize.Serialize(lwPacklenTail);	//����
		if (lwPacklenTail != lwPacklenHeader)
		{
			return -6; //ǰ�󳤶Ȳ�һ��
		}
		out_data_length = lwPacklenHeader + 13;
		return 1;
}


uint16_t CNetPackCRS::GetPackSerial()
{
	CAutoLock loLock(mCriSection);
	return mwSendTimestamp++;
}

CNetPackMPS::CNetPackMPS(){
	_min_pack_size = TCP_PACK_STRUCT_LEN;
	_max_pack_size = DEF_MAX_BUFFER_LEN;
}

int CNetPackMPS::Pack(const char* in_buffer, const int in_length, char* out_buffer, int &out_length)
{
	if (in_length > out_length || in_length > DEF_MAX_BUFFER_LEN)  //���������ɰ�����
		return -1;

	CStandardSerialize loStdSerialize(out_buffer,out_length, CStandardSerialize::STORE);

	loStdSerialize.Serialize(STX);							//��ͷ
	uint16_t u16PackLen = in_length + 2*sizeof(uint8_t) + 2*sizeof(uint16_t);
	u16PackLen = htons(u16PackLen);
	loStdSerialize.Serialize(u16PackLen);				//����
	uint16_t  u16Verion = 0;
	loStdSerialize.Serialize(u16Verion);					//�汾��
	loStdSerialize.Serialize((char*)in_buffer,in_length, in_length);
	loStdSerialize.Serialize(ETX);							//��β

	int liResult = loStdSerialize.getDataLen();			 //�õ�������ܳ�
	out_length = liResult;
	return liResult;
}

int CNetPackMPS::Unpack(const char* in_buffer, const int in_length, char* out_buffer, int &out_buffer_length, int &out_data_length)
{
	if (in_length ==0)
		return 0;

	uint16_t lwTcpPackLen = DEF_MAX_BUFFER_LEN;

	CStandardSerialize loStdSerialize((char*)in_buffer, in_length, CStandardSerialize::LOAD);

	//�жϰ�ͷ
	uint8_t u8PackTag;
	loStdSerialize.Serialize(u8PackTag);	//��ͷ
	if(u8PackTag != STX)
	{
		return -3;  //ͷ����
	}
	uint16_t u16PackLen;
	loStdSerialize.Serialize(u16PackLen);	//����
	u16PackLen = ntohs(u16PackLen);

	if(u16PackLen > in_length)
		return 0;

	uint16_t  u16Verion = 0;
	loStdSerialize.Serialize(u16Verion);	//�汾��
	
	out_buffer_length = u16PackLen - 2*sizeof(uint8_t) - 2*sizeof(uint16_t);
	loStdSerialize.Serialize(out_buffer, out_buffer_length, out_buffer_length);

	//�жϰ�β
	loStdSerialize.Serialize(u8PackTag);   //��β
	if (u8PackTag != ETX)
	{
		return -5;
	}
	
	out_data_length = u16PackLen;
	return 1;
}