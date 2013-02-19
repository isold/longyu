#ifndef _DCS_DEAL_DATA_H_
#define _DCS_DEAL_DATA_H_

#include "sigslot.h"
#include "BasePack.h"
#include "include.h"

class CDCSDealData
{
public:
	CDCSDealData();
	~CDCSDealData();
	/************************************************************************/
	/*
	����ֵ�� ���ݷ���ֵ��ͬ�����ݽ��в�ͬ����
			 0 �����κδ���
		     1 �ظ����ݸ�������
			 2 ���ݹ㲥
	*/
	/************************************************************************/
	 uint32 DCSDealData(const char *apIn, 
		const uint32 aiIn, char *apOut, uint32 &aiOut);

public:
	sigslot::signal3<int, int, CBasePack*> DealDataComplete;

};
#endif //_DCS_DEAL_DATA_H_







