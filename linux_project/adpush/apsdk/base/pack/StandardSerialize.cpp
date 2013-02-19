
/*********************************************************************************
�汾������	Copyright(C)2004-sina Co.Ltd
�ļ�����	StandardSerialize.cpp
�汾�ţ�	1.00.000
�� �� �ˣ�	������
˵����		��׼���л�ʵ���࣬�������л�ͨ�õ���������

�޸ļ�¼��  2004-02-13 �ź��� �����˸��࣬��ֹ�ڴ�Խ��

����ΰ �޸�	2006-11-24
Ŀ�ģ���Ӧ��ƽ̨ʹ��
***********************************************************************************/

#include "StandardSerialize.h"

CStandardSerialize::CStandardSerialize(char * apBuffer,int alBufLen, ENUM_TYPE abyType)
{
    mpBuffer = apBuffer;
    mbyType  = abyType;
    mlBufLen = alBufLen;
    mlDataLen = 0;
}

CStandardSerialize::~CStandardSerialize()
{
}

int CStandardSerialize::getDataLen()
{
    return mlDataLen;
}

//*****************************************************************************
//  ������  ���л���0��β���ַ�������
//  ������  char * apValue		�ַ�������
//			uint16_t awBufferLen	���ɴ��ַ������ݵĻ�������С
//  ����ֵ��int  1= �ɹ��� -1 = ʧ��
//  �÷���	
//*****************************************************************************
int CStandardSerialize::Serialize(char * apValue,uint16_t awMaxLen)
{
    if (mlBufLen < (mlDataLen+2))
		return -1;

    uint16_t	lwLen = 0;
    if (mbyType == LOAD)    //��ȡ
    {
        //���ȶ�ȡ����
        memcpy(&lwLen,mpBuffer + mlDataLen, 2);
        mlDataLen += 2;

        //��ȡ���ݱ���
        if ((lwLen >= awMaxLen) || ((mlDataLen+lwLen) > mlBufLen))
        {
			return -1;
        }
        memcpy(apValue, mpBuffer + mlDataLen, lwLen);
        apValue[lwLen] = '\0';
        mlDataLen += lwLen;                
    }
    else    //�洢
    {        
        //���ȴ洢����
        lwLen = strlen(apValue);
        if ((lwLen >= awMaxLen) || (lwLen+mlDataLen+2 > mlBufLen))
            return -1;

        memcpy(mpBuffer+mlDataLen, &lwLen, 2);
        mlDataLen += 2;

        //�洢���ݱ���
        memcpy(mpBuffer+mlDataLen, apValue, lwLen);
        mlDataLen += lwLen;            
    }		
    return 1;	
}

//*****************************************************************************
//  ������  ���л�����
//  ������  char * apValue		����
//			uint16_t& awLen			�����ݵ���������
//			uint16_t awBufferLen	���ɴ����ݵĻ�������С
//  ����ֵ��int  1= �ɹ��� -1 = ʧ��
//  �÷���	
//*****************************************************************************
int CStandardSerialize::Serialize(char * apValue, uint16_t awLen,uint16_t aiBufferLen)
{
    if ((awLen > aiBufferLen) || (mlBufLen < (mlDataLen+awLen)))
	{
		//TRACE(1, "CStandardSerialize::Serialize  <awLen>��"<<awLen<<" <aiBufferLen>��"<<aiBufferLen<<"<mlBufLen>��"<<mlBufLen<<"<mlDataLen>��"<<mlDataLen);
        return -1;
	}

    if (mbyType == LOAD)    //��ȡ
    {			
        //��Ϊ�ⲿ�ƶ��˶�ȡ���ȣ����Բ���Ҫ�����ݳ��Ƚ������л�
        memcpy(apValue, mpBuffer + mlDataLen, awLen);
    }
    else    //�洢���ݱ���
    {            
        memcpy(mpBuffer+mlDataLen, apValue, awLen);
    }	
    mlDataLen += awLen;
    return 1;	
}

//RSA �ӽ�����Ҫ
int	CStandardSerialize::Serialize(unsigned char *apValue, uint16_t awLen)
{
	if (mlBufLen < (mlDataLen+awLen))
		return -1;

	if (mbyType == LOAD)    //��ȡ
	{			
		//��Ϊ�ⲿ�ƶ��˶�ȡ���ȣ����Բ���Ҫ�����ݳ��Ƚ������л�
		memcpy(apValue, mpBuffer + mlDataLen, awLen);            
	}
	else    //�洢���ݱ���
	{            
		memcpy(mpBuffer+mlDataLen, apValue, awLen);                        
	}	

	mlDataLen += awLen;
	return 1;
}


