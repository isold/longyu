

#ifndef DEF_SINA_TIME_STAMP_H
#define DEF_SINA_TIME_STAMP_H

#include "include.h"
#include "Pool.h"

#define RECORD_MAX_COUNT		65536
#define TIME_STAMP_SECOND		7	//7���ӳ�ʱ

//ʱ�����Ϣ�ṹ
class CRecordItem
{
public:
	unsigned int	mulIpAddr;	//IP��ַ
	unsigned short			mwPort;		//�˿�
	int			mlTime;		//ʱ��
	CRecordItem * mpNext;
	CRecordItem * mpPre;
};

//ʱ�����
class CTimeStamp
{
private:
	CRecordItem			*mpList[RECORD_MAX_COUNT];	//ʱ�����������
	CCriticalSection	mCriSection;				//����������ٽ���

	CPool<CRecordItem>	moRecordPool;				//ʱ��������

	unsigned int				mdwRepeatCount;				//ʱ������δ���ڵĴ���

public:
  	 CTimeStamp();
	~CTimeStamp();

	//���ʱ����Ƿ����
	bool CheckTimeStamp(unsigned short awPackSerial, unsigned int aulIpAddr, unsigned short awPort);

	//�����������
	void Dump();
};

#endif /*DEF_SINA_TIME_STAMP_H*/
