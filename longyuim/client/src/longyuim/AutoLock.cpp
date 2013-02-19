#include "stdafx.h"
#include "AutoLock.h"

namespace _LONGYU_COMMON
{
	CCriticalSection::CCriticalSection()
	{
		InitializeCriticalSection(&moSection);
	}
	//��������
	CCriticalSection::~CCriticalSection()
	{
		DeleteCriticalSection(&moSection);
	}
	//�����ٽ���
	void CCriticalSection::Enter()
	{
		EnterCriticalSection(&moSection);
	}
	//�뿪�ٽ���
	void CCriticalSection::Leave()
	{
		LeaveCriticalSection(&moSection);
	}

	//���캯��
	CAutoLock::CAutoLock(CCriticalSection& aoSection):moSection(aoSection)
	{
		moSection.Enter();
	}

	//��������
	CAutoLock::~CAutoLock()
	{
		moSection.Leave();
	}

};//end _LONGYU_COMMON