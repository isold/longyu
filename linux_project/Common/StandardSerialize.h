/*********************************************************************************
�汾������	Copyright(C)2004-sina Co.Ltd
�ļ�����	StandardSerialize.h
�汾�ţ�	1.00.000
˵����		��׼���л�ʵ���࣬�������л�ͨ�õ���������

�޸ļ�¼��  2004-02-13 �ź��� �����˸��࣬��ֹ�ڴ�Խ��

����ΰ �޸�	2006-11-24 Ŀ�ģ���Ӧ��ƽ̨ʹ��
**********************************************************************************/

#ifndef DEF_SINA_STANDARD_SERIALIZE_H
#define DEF_SINA_STANDARD_SERIALIZE_H

#include "include.h"

//�������л�ͨѶ������
class CStandardSerialize
{
public:
	enum ENUM_TYPE{LOAD,STORE};	

public:
	//���������
	CStandardSerialize(char * apBuffer,int alBufLen, ENUM_TYPE abyType);
	~CStandardSerialize();

	template<class T>
	inline int Serialize(T& value)
	{
		if (mlBufLen < (mlDataLen+(int)sizeof(T)))
			throw(-1);
		if (mbyType == LOAD)//��ȡ
		{   
			memcpy(&value,mpBuffer + mlDataLen, sizeof(T));		        
		}
		else                //�洢
		{
			memcpy(mpBuffer + mlDataLen, &value, sizeof(T));
		}
		mlDataLen += sizeof(T);
		return 1;
	}

    /****************************************************************
	�� �� ����int	Serialize(unsigned int&	alValue);
	�������������л�int���͵�ֵ
	���������int alValue
	���������
	�� �� ֵ��int 1=�ɹ�����1��ʧ��(throw�����ⲿ����)
	�������ڣ�2002-5-27
	�� �� �ߣ�������
	****************************************************************/
#ifndef x86_64
	int	Serialize(int64& ai64Value);
#endif

	/****************************************************************
	�� �� ����int	Serialize(char * apValue);
	�������������л������͵�ֵ
	���������char * apValue :��ֵ(�ȿ�����Ϊ���������Ҳ������Ϊ�������)			  			  
	�� �� ֵ��int 1=�ɹ�����1��ʧ��(throw����Ҫ���ⲿ����)
	�������ڣ�2002-5-27
	�� �� �ߣ�������
	****************************************************************/
	int	Serialize(char * apValue,uint16_t awMaxLen);

	/****************************************************************
	�� �� ����int	Serialize(char * apValue, uint16_t& awLen);
	�������������л��ַ��������͵�ֵ
	���������char * apValue :��ֵ(�ȿ�����Ϊ���������Ҳ������Ϊ�������)			  
			  uint16_t & awLen : ������(�ȿ�����Ϊ���������Ҳ������Ϊ�������)			 			  
	�� �� ֵ��int 1=�ɹ�����1��ʧ��(throw����Ҫ���ⲿ����)
	�������ڣ�2002-5-27
	�� �� �ߣ�������
	****************************************************************/
	int	Serialize(char * apValue, uint16_t awLen,uint16_t aiBufferLen);


	//add by yanghannong 
	int	Serialize(uint8_t *apValue, uint16_t awLen);

	//ȡ������
	int	getDataLen();
	
	ENUM_TYPE	mbyType;		//���л�����
private:	
	int		mlDataLen;		//���ݳ���
	char *		mpBuffer;
    int        mlBufLen;       //buffer����
};

#endif //DEF_SINA_STANDARD_SERIALIZE_H
