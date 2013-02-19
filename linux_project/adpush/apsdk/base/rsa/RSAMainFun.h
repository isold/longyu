#ifndef RSAMainFun_h__
#define RSAMainFun_h__

#include "MyCryptLib.h"
#include "Rijndael.h"


class CRSAMainFun
{
public:
	CRSAMainFun(void);
	~CRSAMainFun(void);

public:
	// $_FUNCTION_BEGIN ******************************
	// �������ƣ� fnRSAGetPublicKey
	// ���������� 
	// �� �� ֵ�� 
	// ����˵���� ��ó�ʼ��Կ
	// $_FUNCTION_END ********************************
	int fnRSAGetPublicKey(/*OUT*/uint32_t ** pPublicKey,/*OUT*/uint32_t & nKeySize);
	// $_FUNCTION_BEGIN ******************************
	// �������ƣ� fnRSAClientMakePassWord
	// ����������
	// �� �� ֵ�� 
	// ����˵���� �趨�ͻ�����Կ, ͬʱ����һ���µ���Կ��������
	// $_FUNCTION_END ********************************
	int fnRSAClientMakePassWord(/*IN*/const uint32_t *pKey,/*OUT*/uint8_t** pOutKey, /*OUT*/uint32_t &nKeySize);
	// $_FUNCTION_BEGIN ******************************
	// �������ƣ� fnRSAServerMakePassWord
	// ����������
	// �� �� ֵ�� 
	// ����˵���� �趨����������Կ, ͬʱ��������ǩ�����ͻ����Ա���֤�ɿ���
	// $_FUNCTION_END ********************************
	int fnRSAServerMakePassWord(/*IN*/const uint32_t *pKey,/*OUT*/uint8_t** pOutKey, /*OUT*/uint32_t &nKeySize);
	// $_FUNCTION_BEGIN ******************************
	// �������ƣ� fnRSAVerifyKey
	// ����������
	// �� �� ֵ�� 
	// ����˵���� ����ǩ����֤, ͬʱ���ظ�������
	// $_FUNCTION_END ********************************
	int fnRSAVerifyKey(/*IN*/const uint32_t *pKey,/*OUT*/uint8_t** pOutKey, /*OUT*/uint32_t &nKeySize);
	// $_FUNCTION_BEGIN ******************************
	// �������ƣ� fnRSAStartHash
	// ����������
	// �� �� ֵ�� 
	// ����˵���� ��ʼHASH����
	// $_FUNCTION_END ********************************
	void fnRSAStartHash(void);
	// $_FUNCTION_BEGIN ******************************
	// �������ƣ� fnRSAFinishHash
	// ����������
	// �� �� ֵ�� 
	// ����˵���� HASH���
	// $_FUNCTION_END ********************************
	bool fnRSAFinishHash(const uint32_t *pKey,uint32_t nKeySize);
	// $_FUNCTION_BEGIN ******************************
	// �������ƣ� fnDeCryptBuffer
	// ����������
	// �� �� ֵ�� 
	// ����˵���� ����
	// $_FUNCTION_END ********************************
	char* fnEnCryptBuffer(const char *pBuff, int & nBufSize);
	// $_FUNCTION_BEGIN ******************************
	// �������ƣ� fnDeCryptBuffer
	// ����������
	// �� �� ֵ�� 
	// ����˵���� ����
	// $_FUNCTION_END ********************************
	char* fnDeCryptBuffer(const char *pBuff,int & nBufSize);
	// $_FUNCTION_BEGIN ******************************
	// �������ƣ� fnReleaseKey
	// ����������
	// �� �� ֵ�� 
	// ����˵���� ����key�Ŀռ�
	// $_FUNCTION_END ********************************
	void fnReleaseKey(uint32_t *pKey);
	// $_FUNCTION_BEGIN ******************************
	// �������ƣ� fnGetKeyLength
	// ����������
	// �� �� ֵ�� ��Կ����
	// ����˵���� 
	// $_FUNCTION_END ********************************
	int fnGetKeyLength();
private:
	//Function to convert unsigned char to string of length 2
	void Char2Hex(unsigned char ch, char* szHex);
	//Function to convert string of length 2 to unsigned char
	void Hex2Char(char const* szHex, unsigned char& rch);
	//Function to convert string of unsigned chars to string of chars
	void  CharStr2HexStr(unsigned char const* pucCharStr, char* pszHexStr, int iSize);
	//Function to convert string of chars to string of unsigned chars
	void HexStr2CharStr(char const* pszHexStr, unsigned char* pucCharStr, int iSize);
	// $_FUNCTION_BEGIN ******************************
	// �������ƣ� ComputeAndSendPublicKey
	// ����������
	// �� �� ֵ�� 
	// ����˵���� ���㲢���ɹ�Կ
	// $_FUNCTION_END ********************************
	int ComputeAndSendPublicKey(/*OUT*/uint8_t** pPublicKey, /*OUT*/uint32_t &nKeySize);
	// $_FUNCTION_BEGIN ******************************
	// �������ƣ� ComputeAndSetSessionKey
	// ����������
	// �� �� ֵ�� 
	// ����˵���� ���㲢������һ����̬��key, �趨���ӽ���ģ��
	// $_FUNCTION_END ********************************
	bool ComputeAndSetSessionKey(const uint32_t *pKey,uint32_t nSize);
	// $_FUNCTION_BEGIN ******************************
	// �������ƣ� ComputeAndSendSignature
	// ����������
	// �� �� ֵ�� 
	// ����˵���� ���㲢�ҷ�������ǩ��
	// $_FUNCTION_END ********************************
	int ComputeAndSendSignature(/*IN*/uint8_t** pSignature, /*OUT*/uint32_t & nSizeKey);

private:
	MyCryptLib m_cCryptLib;
	CRijndael m_cCryptor;
	SHA1_STATETYPE m_csha1Hash;
	uint32_t* m_pPublicKey;
	uint32_t m_Privatekey[_PRIVATEKEYSIZE_];
};
#endif // RSAMainFun_h__