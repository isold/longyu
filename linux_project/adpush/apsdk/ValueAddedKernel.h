#ifndef _VALUE_ADDED_KERNEL_H_
#define _VALUE_ADDED_KERNEL_H_

#include "InnerInterface.h"
#include "include/SdkKernelInterface.h"

class CValueAddedKernel :public IRoomKernel, public IValueAddedKernel
{
private:
	//���������ĳ��
	virtual void  SendGift(int64_t ai64UserID, int32_t aiGiftID, char* apszGiftName, int32_t aiUseCount);

	//��������
	virtual void  SendLoudSpeaker(uint8_t abyType, char* apszContent, char* apszControl);
};
#endif //_VALUE_ADDED_KERNEL_H_
