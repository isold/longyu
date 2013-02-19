/***********************************************************
��Ȩ������	Copyright (C) 2003 - LongMaster Co.Ltd
�� �� ����	DebugTrace.h
�� �� �ˣ�	�ź���
�������ڣ�	2003-09-15
˵    ����	���ڳ�����Ե���־���
�� �� �ţ�	0.0003

����ΰ	2006-11-13 �޸�
Ŀ������Ӧ��ƽ̨Ӧ��
***********************************************************/

#ifndef DEF_SINA_DEBUGTRACE_HEAD_
#define DEF_SINA_DEBUGTRACE_HEAD_

#define SINA_UC_INFORMATION_OUTPUT		//���������־�ı��
#define DEF_MAX_BUFF_LEN 2048			//����ÿ����־��󻺳峤��

//zyw 2007-4-19	����������Ҫʱʱ�����־
#ifdef _DEBUG
#define LOG_OUTPUT_TO_FILE_DIRECT 		//�ڵ���״ֱ̬��������ļ�
#endif //_DEBUG

#ifdef WIN32
#include <windows.h>
#else
#include <stdarg.h>
#endif

#include <sstream>
#include <string>
using namespace std;

#include "CriticalSection.h"
#include "sigslot.h"
class CDebugTrace;
extern CDebugTrace	*goDebugTrace;       //��ӡ��־��DebugTrace����
//////////////////////////////////////////////////////////////////////
//�й�ASSERT�Ķ���

#undef ASSERT		//ȡ��ASSERT��

//  ���¶���ASSERT��  
#ifdef _DEBUG		//���԰汾ʹ�ô˺�
#define ASSERT(f)               \
	if(f)							\
	;							\
	else                            \
	goDebugTrace->AssertFail(#f,__FILE__, __LINE__)
#else			
#define ASSERT(f)
#endif//_DEBUG


//////////////////////////////////////////////////////////////////////
//�й�TRACE�Ķ���
#define SET_TRACE_LEVEL		goDebugTrace->SetTraceLevel
#define SET_LOG_FILENAME	goDebugTrace->SetLogFileName
 #define SET_TRACE_OPTIONS	goDebugTrace->SetTraceOptions
#define GET_TRACE_OPTIONS	goDebugTrace->GetTraceOptions

//ȡ��TRACE����
#undef TRACE

//���¶���TRACE���
//��¼��־:��������㹻�߲Ŵ�ӡ��־,���򲻴�
#ifdef SINA_UC_INFORMATION_OUTPUT			
#define TRACE(level, args) \
	if (!goDebugTrace->CanTrace(level)) 	;  else\
	{\
		goDebugTrace->Lock();\
		try\
		{\
			(goDebugTrace->BeginTrace(level,__FILE__,__LINE__) << args << '\n').EndTrace();\
		}\
		catch (...)\
		{\
		}\
		goDebugTrace->UnLock();\
	}


		

#else					//���а�
#define TRACE ;
#endif //SINA_UC_INFORMATION_OUTPUT

//////////////////////////////////////////////////////////////////////
//���ָ�����û�����׷��
extern int64	gi64TraceUserId;	//׷�ٵ��û�ID

#define SET_TRACE_USER_ID(userid)  (gi64TraceUserId=(userid));\
{\
	goDebugTrace->Lock();\
	try\
	{\
		(goDebugTrace->BeginTrace(0,__FILE__,__LINE__) << "����׷�ٵ��û�ID:" << userid << '\n').EndTrace();\
	}\
	catch (...)\
	{\
	}\
	goDebugTrace->UnLock();\
}

#define TraceUserEvent(userid, args) \
{\
	goDebugTrace->Lock();\
	try\
	{\
		if ((userid) == gi64TraceUserId)\
		(goDebugTrace->BeginTrace(0,__FILE__,__LINE__) << args << '\n').EndTrace();\
	}\
	catch (...)\
	{\
	}\
	goDebugTrace->UnLock();\
}



//////////////////////////////////////////////////////////////////////
//��־ʵ��������
typedef CDebugTrace& (* DebugTraceFunc)(CDebugTrace &aoDebugTrace);

class CDebugTrace
{
public:
	char		mszPrintBuff[DEF_MAX_BUFF_LEN+1];	 //��ӡ���ݻ���
	int		mlDataLen;			 //���ݳ���
	int			mnLogLevel;			 //��־�ȼ�
	char		mszLogFileName[512]; //��־�ļ�����
	//��־�ļ�ǰ׺
	char mszLogFileNamePre[450];
	unsigned    muTraceOptions;		 //��ӡ��־ѡ��	

	CCriticalSection moCriticalSection;     //��ӡ��־ͬ���ٽ���
	struct timeb moSystemTime;				//ĳ�λỰ��ʱ��
	int	 miLogLevel;						//ĳ�λỰ����־�ȼ�
	//��־�ļ�����ֽ�
	unsigned int muiLogFileSize;

public:
	//��ӡѡ��
	enum Options 
	{
		/// ��ӡʱ��
		Timestamp = 1,
		/// ��ӡ��־����
		LogLevel = 2,
		/// ��ӡԴ�ļ������к�
		FileAndLine = 4,
		/// ����־׷�ӵ��ļ���
		AppendToFile = 8,
		///�����־������̨
		PrintToConsole = 16
	};    	

public:
	//���캯��	
	CDebugTrace(unsigned asTraceOptions = Timestamp | AppendToFile);
	//��������
	~CDebugTrace();
public:
	//������־����(0�����,1���,��������,С�ڸõȼ�����־����ӡ)
	void SetTraceLevel(int aiTraceLevel);

	//������־�ļ�����ֽ���
	void SetLogFileSize(unsigned int aiSize);

	//������־�ļ���
	void SetLogFileName(char *aszLogFile);

	// ����TRACEѡ�� .ע�⺯������ OR ��ѡ��
	void SetTraceOptions(unsigned options /** New level for trace */ );

	//ȡ��TRACEѡ��
	unsigned GetTraceOptions(void);

	//�жϸ��������Ƿ���Դ�ӡ
	bool CanTrace(int aiLogLevel);					

	//��ʼ��ӡ
	CDebugTrace& BeginTrace(int aiLogLevel,char *apSrcFile,int aiSrcLine);	

	//������ӡ
	void EndTrace();

	//����ʧ�ܴ�����
	void AssertFail(char * strCond,char *strFile, unsigned uLine);

	//���պ���printf�����Ƹ�ʽ��ӡ��־
	void TraceFormat(const char * pFmt,...);	

	//��ӡ��ǰ��ջ
	void TraceStack(void);

	//�������
	CDebugTrace& endl(CDebugTrace& _outs);

	template <class T>
	inline CDebugTrace& operator<<(T value)
	{
		stringstream str;
		str<<value;
		string ss = "";
		ss = str.str();
		if (mlDataLen < DEF_MAX_BUFF_LEN - (int)ss.length())
		{
			memcpy((void*)(mszPrintBuff + mlDataLen), ss.c_str(), ss.length());
			mlDataLen += ss.length();
		}
		return *this;
	}

	//���·ֱ����������������
	CDebugTrace& operator << (unsigned char acCharVal);
	CDebugTrace& operator << (bool abBoolVal);

#ifndef x86_64
	CDebugTrace& operator << (int64 aiInt64Val);
#endif
	CDebugTrace& operator << (const char *apStrVal);	
	CDebugTrace& operator << (DebugTraceFunc _f) { (*_f)(*this); return *this; }	

	//����������ʱ������
	int Flush();
	void Lock()
	{
		 moCriticalSection.Enter();
	}
	void UnLock()
	{
		moCriticalSection.Leave();
	}

private:
	unsigned int GetFileSize( FILE *fp )
	{
		unsigned int cur_pos = 0;
		unsigned int len = 0;
		cur_pos = ftell( fp );
		//���ļ����Ķ�ȡλ����Ϊ�ļ�ĩβ
		fseek( fp, 0, SEEK_END );
		//��ȡ�ļ�ĩβ�Ķ�ȡλ��,���ļ���С
		len = ftell( fp );
		//���ļ����Ķ�ȡλ�û�ԭΪԭ�ȵ�ֵ
		fseek( fp, cur_pos, SEEK_SET );
		return len;
	}


#ifndef LOG_OUTPUT_TO_FILE_DIRECT
	enum{ LOG_BUFFER_LEN = 1024 * 512 };

private:
	char	macMark[20];
	//�Ѿ�ʹ�õĻ���������
	int    mlBufDataLen;
	//������
	char    mszLogBuffer[ LOG_BUFFER_LEN + 1 ];
private:
	//��������ӵ���ʱ������
	bool    AddToLogBuffer();
#endif
};


#endif	//DEF_SINA_DEBUGTRACE_HEAD_
