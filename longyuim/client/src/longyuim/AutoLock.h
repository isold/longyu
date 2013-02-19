#pragma once

namespace _LONGYU_COMMON
{
	class CCriticalSection
	{
	public:
		//���캯��
		CCriticalSection();
		//��������
		~CCriticalSection();

		//�����ٽ���
		void Enter();
		//�뿪�ٽ���
		void Leave();
	private:
		CRITICAL_SECTION moSection;
	};

	class CAutoLock
	{
	public:
		//���캯��
		CAutoLock(CCriticalSection& aoSection);
		//��������
		~CAutoLock();
	private:
		CCriticalSection& moSection;
	};

}; //end _LONGYU_COMMON