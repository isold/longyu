
#include "stdafx.h"
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

#ifndef x86_64
int CStandardSerialize::Serialize(int64& aiValue)
{	
    if (mlBufLen < (mlDataLen+sizeof(int64)))
        throw(-1);

    if (mbyType == LOAD)//��ȡ
    {   
        memcpy(&aiValue,mpBuffer + mlDataLen, sizeof(int64));		        
    }
    else                //�洢
    {
        memcpy(mpBuffer + mlDataLen, &aiValue, sizeof(int64));
    }
    mlDataLen += sizeof(int64);

    return 1;
}
#endif

//*****************************************************************************
//  ������  ���л���0��β���ַ�������
//  ������  char * apValue		�ַ�������
//			uint16 awBufferLen	���ɴ��ַ������ݵĻ�������С
//  ����ֵ��int  1= �ɹ��� -1 = ʧ��
//  �÷���	
//*****************************************************************************
int CStandardSerialize::Serialize(char * apValue,uint16 awMaxLen)
{
    if (mlBufLen < (mlDataLen+2))
        throw(-1);

    uint16	lwLen = 0;
    if (mbyType == LOAD)    //��ȡ
    {
        //���ȶ�ȡ����
        memcpy(&lwLen,mpBuffer + mlDataLen, 2);
        mlDataLen += 2;

        //��ȡ���ݱ���
        if ((lwLen >= awMaxLen) || ((mlDataLen+lwLen) > mlBufLen))
        {
            throw(-1);
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
            throw(-1);

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
//			uint16& awLen			�����ݵ���������
//			uint16 awBufferLen	���ɴ����ݵĻ�������С
//  ����ֵ��int  1= �ɹ��� -1 = ʧ��
//  �÷���	
//*****************************************************************************
int CStandardSerialize::Serialize(char * apValue, uint16 awLen,uint16 aiBufferLen)
{
    if ((awLen > aiBufferLen) || (mlBufLen < (mlDataLen+awLen)))
	{
//		TRACE(1, "CStandardSerialize::Serialize  <awLen>��"<<awLen<<" <aiBufferLen>��"<<aiBufferLen<<"<mlBufLen>��"<<mlBufLen<<"<mlDataLen>��"<<mlDataLen);
        throw (-1);
	}

    if (mbyType == LOAD)    //��ȡ
    {			
        //��Ϊ�ⲿ�ƶ��˶�ȡ���ȣ����Բ���Ҫ�����ݳ��Ƚ������л�
        memcpy(apValue, mpBuffer + mlDataLen, awLen);
		//TRACE(1,"CStandardSerialize::Serialize LOAD��  apValue��"<<apValue<<" mpBuffer��"<<mpBuffer<<" mlDataLen��"<<mlDataLen<<" awLen��"<<awLen);//add by tanwei 20081216
    }
    else    //�洢���ݱ���
    {            
        memcpy(mpBuffer+mlDataLen, apValue, awLen);
		//TRACE(1,"CStandardSerialize::Serialize ��  mpBuffer��"<<mpBuffer<<" mlDataLen��"<<mlDataLen<<" apValue��"<<apValue<<" awLen��"<<awLen);//add by tanwei 20081216
    }	
    mlDataLen += awLen;
    return 1;	
}
//add by yanghannong 090508
//RSA �ӽ�����Ҫ
int	CStandardSerialize::Serialize(uint8 *apValue, uint16 awLen)
{
	if (mlBufLen < (mlDataLen+awLen))
		throw (-1);

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


