#ifndef DEF_SINA_STANDARD_SERIALIZE_H
#define DEF_SINA_STANDARD_SERIALIZE_H

#include "define.h"

class CStandardSerialize
{
public:
	enum ENUM_TYPE{LOAD,STORE};	

public:
	CStandardSerialize(char * apBuffer,int alBufLen, ENUM_TYPE abyType);
	~CStandardSerialize();

	int	Serialize(bool&	abValue);
	int	Serialize(int&	abValue);
	int	Serialize(uint8&	abyValue);
	int	Serialize(short& asValue);
	int	Serialize(uint16&	awValue);
	long Serialize(long&	alValue);
	int	Serialize(unsigned int&	aulValue);
	int	Serialize(int64& ai64Value);
	int	Serialize(char * apValue,uint16 awMaxLen);
	int	Serialize(char * apValue, uint16 awLen,uint16 aiBufferLen);
	int	Serialize(uint8 *apValue, uint16 awLen);

	//ȡ������
	int	getDataLen();

private:
	//���л�����
	ENUM_TYPE	mbyType;		
	//���ݳ���
	int		mlDataLen;	
	char *		mpBuffer;
	//buffer����
	int        mlBufLen;       
};

#endif //DEF_SINA_STANDARD_SERIALIZE_H
