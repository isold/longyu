#ifndef _DNS_DEAL_DATA_H_
#define _DNS_DEAL_DATA_H_

#include "sigslot.h"
#include "BasePack.h"
#include "include.h"

class CDNSDealData
{
public:
	CDNSDealData();
	~CDNSDealData();
	/************************************************************************/
	/*
	����ֵ�� ���ݷ���ֵ��ͬ�����ݽ��в�ͬ����
	0 �����κδ���
	1 �ظ����ݸ�������
	2 ���ݹ㲥
	*/
	/************************************************************************/
	uint32 DNSDealDcsData(const char *apIn, 
		const uint32 aiIn, char *apOut, uint32 &aiOut);

	uint32 DNSDealCrsData(const char *apIn, 
		const uint32 aiIn, char *apOut, uint32 &aiOut);

public:
	sigslot::signal3<int, int, CBasePack*> DealDcsDataComplete;
	sigslot::signal3<int, int, CBasePack*> DealCrsDataComplete;
};
#endif //_DNS_DEAL_DATA_H_












