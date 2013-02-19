/********************************************************************
	created:	2011/03/08
	created:	8:3:2011   10:39
	file base:	Common
	file ext:	cpp
	author:		������
	
	purpose:	��������
*********************************************************************/
#include "Common.h"

//�õ���ǰӦ�ó����·��
void CCommon::GetAppPath(char* apPath, int aiLen)
{
	memset(apPath, 0, aiLen);
#ifdef _WIN32
	GetModuleFileNameA(NULL, (LPSTR)apPath, aiLen);
#else	
	char lcAppPath[256+1] = ""; 
	sprintf(lcAppPath, "/proc/self/exe");
	readlink(lcAppPath, apPath, aiLen-1);
#endif
}

//����·��
void CCommon::CreatePath(char* apPath)
{
#ifdef _WIN32
	CreateDirectoryA(apPath, NULL);
#else	
	//mkdir�����ĵڶ��������������ô����ļ��е�Ȩ�ޣ�
	//Ȩ�޲���8���ƣ�����Ϊ777��ʾ�����û������Բ鿴
	mkdir(apPath, 511);
#endif
}


uint64_t CCommon::get_current_time()
{
#if defined(__linux__) || defined(__APPLE__)
        struct timeb loTimeb;
        memset(&loTimeb, 0 , sizeof(timeb));
        ftime(&loTimeb); 
        return ((uint64_t)loTimeb.time * 1000) + loTimeb.millitm;
#endif

#ifdef _WIN32
	    struct _timeb loTimeb;
        memset(&loTimeb, 0 , sizeof(timeb));
        _ftime(&loTimeb); 
        return ((uint64_t)loTimeb.time * 1000) + loTimeb.millitm;
#endif
}

string CCommon::get_now()
{
	string strCurrentTime = "";

	/*struct timeb loSystemTime;
	ftime(&loSystemTime);
	struct tm* lptm = localtime(&loSystemTime.time);

	stringstream lstrTimeNow;
	lstrTimeNow.fill('0');
	lstrTimeNow<<setw(4)<<1900+lptm->tm_year<<"-"<<
		setw(2)<<1+lptm->tm_mon<<"-"<<
		setw(2)<<lptm->tm_mday<<" "<<
		setw(2)<<lptm->tm_hour<<":"<<
		setw(2)<<lptm->tm_min<<":"<<
		setw(2)<<lptm->tm_sec<<":"<<
		setw(3)<<loSystemTime.millitm<<ends;

	strCurrentTime = lstrTimeNow.str();
	*/
	return strCurrentTime;
}

//����Ƿ�ʱ
bool CCommon::CheckTimeOut(const int64_t &ai64LastTime, const int64_t &ai64TimeInterval)
{
	int64_t now = CCommon::get_current_time();
	if(now > ai64LastTime + ai64TimeInterval)
	{
		return true;
	}
	return false;
}

//����IP��ַ�Ͱ���ż�������
int64_t CCommon::MakeIpPortKey(const sockaddr_in& addr, const uint16_t awPackSerial)
{
#ifdef _WIN32
	return (int64_t)addr.sin_addr.S_un.S_addr * 0x100000000 + \
		(int64_t)addr.sin_port * 0x10000 + awPackSerial;
#else
	return (int64_t)addr.sin_addr.s_addr * 0x100000000LL + \
		(int64_t)addr.sin_port * 0x10000 + awPackSerial;
#endif
}

//ͨ��sockaddr_in�õ�int�͵�IP��ַ
unsigned int CCommon::GetSocketAddr(const sockaddr_in& addr)
{
#ifdef _WIN32
	return addr.sin_addr.S_un.S_addr;
#else
	return addr.sin_addr.s_addr;
#endif
}

void CCommon::GetSocketAddr(const sockaddr_in &addr, unsigned int &ip, uint16_t &port)
{
	ip = ntohl(addr.sin_addr.s_addr);
	port = ntohs(addr.sin_port);
}

unsigned int CCommon::GetSocketAddr(const char* addr)
{
	return ntohl(inet_addr(addr));
}

//��int�͵�IP��ַ���õ�sockaddr_in�ṹ����
void CCommon::SetSocketAddr(sockaddr_in& addr,unsigned int alAddr)
{
#ifdef _WIN32
	addr.sin_addr.S_un.S_addr = alAddr;
#else
	addr.sin_addr.s_addr = alAddr;
#endif
}

void CCommon::SetSocketAddr(sockaddr_in& addr,unsigned int alAddr, uint16_t alPort)
{
	addr.sin_family = AF_INET;
	addr.sin_port = alPort;
#ifdef _WIN32
	addr.sin_addr.S_un.S_addr = alAddr;
#else
	addr.sin_addr.s_addr = alAddr;
#endif
}

//��int�͵�IP��ַ�õ��ַ������͵�IP��ַ
char* CCommon::GetIPAddr(unsigned int alAddr)
{
	sockaddr_in addr;

#ifdef _WIN32
	addr.sin_addr.S_un.S_addr = alAddr;
#else
	addr.sin_addr.s_addr = alAddr;
#endif	

	return inet_ntoa(addr.sin_addr);
}

//��time_t����ȡ�����ں�ʱ����ַ�����ʽ
char* CCommon::Getctime(time_t *apTime)
{
	static char lszTime[20];
	strftime(lszTime, 20, "%Y-%m-%d %H:%M:%S", localtime(apTime));
	return lszTime;
}

//��װ������ö�ջ�Ĺ���
void CCommon::DumpStack()
{
	/*void * larray[25];
	int liSize = backtrace(larray, 25);
	char ** lszSymbols = backtrace_symbols(larray, liSize);

	for (int i = 0; i < liSize; i++)
	{
		//TRACE(1, "CUCTools::DumpStack " << lszSymbols[i]);
	}
	if(lszSymbols)
		free(lszSymbols);
		*/
}

unsigned int CCommon::GetRandInt(unsigned int rand_max)
{
	assert(rand_max > 1);
	return 1 + (int) ((float)rand_max * (rand() /(RAND_MAX + 1.0)));
}

string CCommon::ChgStrInRandomSeq(const string& astrData,int aiChgTimes)
{
	assert(aiChgTimes > 0 && astrData.size() > 1);
	string lstrNewData = astrData;
	for(int i = 0; i < aiChgTimes; ++i)
	{
		string lstr1 = lstrNewData.substr(0,lstrNewData.size()/2);
		lstrNewData = lstrNewData.substr(lstrNewData.size()/2);
		unsigned int liInsertPos = 0;
		for(string::size_type i = 0; i < lstr1.size(); ++i)
		{
			liInsertPos = GetRandInt(lstrNewData.size()+1) - 1;
			if(liInsertPos < lstrNewData.size())
			{
				lstrNewData.insert(liInsertPos,1,lstr1.at(i));
			}
			else
			{
				lstrNewData += lstr1.at(i);
			}
		}
	}

	return lstrNewData;
}

// 64λ�����ֽ���ת�����ֽ���
uint64_t  CCommon::_htonq(uint64_t u64HostValue)
{
	uint16_t u16Value = 1;
	if (!(*((char*)&u16Value)))
	{
		return u64HostValue;
	}
	else
	{
		uint32_t u32High = (uint32_t)(u64HostValue & 0xFFFFFFFF);
		u32High = htonl(u32High);
		uint32_t u32Low  = (uint32_t)(u64HostValue >> 32);
		u32Low = htonl(u32Low);

		uint64_t u64NetValue = u32High;
		u64NetValue <<= 32;
		u64NetValue |= u32Low;
		return u64NetValue;
	}
}

// 64λ�����ֽ���ת�����ֽ���
uint64_t CCommon::_ntohq(uint64_t u64NetValue)
{
	return _htonq(u64NetValue);
}