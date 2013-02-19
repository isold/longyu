/***********************************************************
��Ȩ������  Copyright (C) 2002 - LongMaster Co.Ltd
�� �� ����  DebugTrace.cpp
�� �� �ˣ�  �ź���
�������ڣ�  2003-09-15
˵    ����  ������ӡ��������,��������ͨ����������
�� �� �ţ�  0.0001

����ΰ	2006-11-13 �޸�
Ŀ������Ӧ��ƽ̨Ӧ��
***********************************************************/
#include <stdio.h>
#include "include.h"
#include "debugtrace.h"
#include "FileStream.h"

char goLogMark[] = "SERVER_LOG_BEGIN";

int64		gi64TraceUserId;	//׷�ٵ��û�ID

//*****************************************************************************
//  ����ԭ�ͣ�  CDebugTrace(unsigned asTraceOptions)
//  ������      unsigned asTraceOptions (��־��ӡѡ��,Ĭ�ϴ�ӡʱ����д�뵽�ļ�)
//  ����ֵ��    
//  �÷���      ���캯��
//*****************************************************************************
// $_CODE_CHANGE 2005-09-09 fyf�޸ģ���ʼ������������
CDebugTrace::CDebugTrace(unsigned asTraceOptions)
{
	mlDataLen = 0;  
	mnLogLevel = 4;

	memset(mszLogFileName,0,512);
	memset(mszLogFileNamePre, 0, 450);

	//�����ʱ������
	memset(mszPrintBuff, 0, sizeof(mszPrintBuff));

    muTraceOptions = asTraceOptions;
	//Ĭ����־�ļ���СΪ1G
	muiLogFileSize = 1024*1024*1024;

#ifndef LOG_OUTPUT_TO_FILE_DIRECT
	//��֤�������ĳߴ�
	ASSERT(LOG_BUFFER_LEN > DEF_MAX_BUFF_LEN*5);

	//�ڻ�������ǰ��ӱ��
	strncpy(macMark, goLogMark, sizeof(macMark));

	//��ջ�����
	mlBufDataLen = 0 ;
#endif 
}

//*****************************************************************************
//  ����ԭ�ͣ�  ~CDebugTrace()
//  ������      
//  ����ֵ��    
//  �÷���      ��������
//*****************************************************************************
// $_CODE_CHANGE 2005-09-09 fyf�޸ģ���������ʱ��������еĻ�����
CDebugTrace::~CDebugTrace()
{
#ifndef LOG_OUTPUT_TO_FILE_DIRECT
	Flush();
#endif //LOG_OUTPUT_TO_FILE_DIRECT
}

//��ӡ�����ַ�
CDebugTrace& CDebugTrace::operator << (unsigned char acCharVal)
{
	if (mlDataLen < DEF_MAX_BUFF_LEN - 2)
	{
		char * lpWritePtr = mszPrintBuff + mlDataLen;		
		mlDataLen += sprintf(lpWritePtr,"%d",acCharVal);
	}
	return *this;
}

//��ӡboolֵ
CDebugTrace& CDebugTrace::operator << (bool abBoolVal)
{
	if (mlDataLen < DEF_MAX_BUFF_LEN - 6)
	{
		char * lpWritePtr = mszPrintBuff + mlDataLen;
		if (abBoolVal)
		{   
			mlDataLen += sprintf(lpWritePtr,"%s","true");
		}
		else
		{
			mlDataLen += sprintf(lpWritePtr,"%s","false");
		}
	}
	return *this;
}

#ifndef x86_64
//��ӡ64λ����(int64)
CDebugTrace& CDebugTrace::operator << (int64 aiint64Val)
{
	if (mlDataLen < DEF_MAX_BUFF_LEN - 20) //max:18446744073709551615
	{
		char *lpWritePtr = mszPrintBuff + mlDataLen;
#ifdef WIN32
		mlDataLen += sprintf(lpWritePtr,"%I64d",aiint64Val);
#else
		mlDataLen += sprintf(lpWritePtr,"%lld",aiint64Val);
#endif
	}
	return *this;
}
#endif

//��ӡ�ַ���ֵ
CDebugTrace& CDebugTrace::operator << (const char *apStrVal)
{	
	char * lpWritePtr = mszPrintBuff + mlDataLen;
	if (apStrVal == 0)
	{       
		if (mlDataLen < (int)(DEF_MAX_BUFF_LEN - strlen("NULL")))
			mlDataLen += sprintf(lpWritePtr,"%s","NULL");
	}
	else
	{
		if (mlDataLen < (int)(DEF_MAX_BUFF_LEN - strlen(apStrVal)))
			mlDataLen += sprintf(lpWritePtr,"%s",apStrVal);
	}   	
	return *this;
}

//inline _CRTIMP ostream& __cdecl endl(ostream& _outs) { return _outs << '\n' << flush; }
CDebugTrace& CDebugTrace::endl(CDebugTrace &aoDebugTrace)
{
#ifdef WIN32
	//��������Դ�����
	OutputDebugString(aoDebugTrace.mszPrintBuff); 
#endif

	//��Ҫ�����������̨,�����־��Ϣ�ڿ���̨Ҳ��ӡһ��
	if (aoDebugTrace.muTraceOptions & CDebugTrace::PrintToConsole) {
		printf("%s",aoDebugTrace.mszPrintBuff);
	}

	//��Ҫ��д�ļ�����������־�ļ���,�����־��Ϣд���ļ���
	if ((aoDebugTrace.muTraceOptions & CDebugTrace::AppendToFile) && (strlen(aoDebugTrace.mszLogFileName) > 1))
	{
		FILE * lfpTraceFile = NULL;
		lfpTraceFile = fopen(aoDebugTrace.mszLogFileName,"a");  
		if (lfpTraceFile != NULL)
		{
			fprintf(lfpTraceFile,"%s",aoDebugTrace.mszPrintBuff);
			fclose(lfpTraceFile);
		}
	}
	aoDebugTrace.mlDataLen = 0;
	moCriticalSection.Leave(); //�˳��ٽ���
	return aoDebugTrace;	
}
//*****************************************************************************
//  ����ԭ�ͣ�  TraceFormat(const char * pFmt,...)
//  ����˵��:   ����printf�����ĸ�ʽ��ӡһ����־
//  ������      const char * pFmt,...(�ɱ䳤�Ȳ���,��:"����:%s,����:%d","zht",26)
//  ����ֵ��    
//  �÷���      TraceFormat("����:%s,����:%d","zht",26)
//*****************************************************************************
void CDebugTrace::TraceFormat(const char * pFmt,...)
{
	va_list argptr;
	va_start(argptr, pFmt);

#ifdef WIN32
	mlDataLen += _vsnprintf(mszPrintBuff + mlDataLen, 
		DEF_MAX_BUFF_LEN - mlDataLen,
		pFmt , argptr);
#else
	mlDataLen += vsnprintf(mszPrintBuff + mlDataLen, 
		DEF_MAX_BUFF_LEN - mlDataLen,
		pFmt , argptr);
#endif

	va_end(argptr);

	//����EndTrace������ӡ
	EndTrace();
}

////////////////////////////////////////////////
//�����Ǿ�̬����

//����TRACE�ȼ�(0�����,1���,��������,С�ڸõȼ�����־����ӡ)
void CDebugTrace::SetTraceLevel(int aiTraceLevel)
{
	mnLogLevel = aiTraceLevel;
}

void CDebugTrace::SetLogFileSize(unsigned int aiSize)
{
	muiLogFileSize = aiSize;
}


//���������־�ļ���
// $_CODE_CHANGE 2005-09-09 fyf�޸ģ������û����ļ�����ʱ�������һ��
void CDebugTrace::SetLogFileName(char *aszLogFile)
{
#ifndef LOG_OUTPUT_TO_FILE_DIRECT
	Flush();
#endif //LOG_OUTPUT_TO_FILE_DIRECT
	if (aszLogFile != NULL)
	{
		ASSERT(strlen(aszLogFile) <= 512);
		strcpy(mszLogFileNamePre,aszLogFile);
	}
	else
	{
		strcpy(mszLogFileNamePre,"");
	}

	char lszFileDate[50];
	memset(lszFileDate, 0, 50);
	time_t loSystemTime;
	time(&loSystemTime);
	struct tm* lptm = localtime(&loSystemTime);
	sprintf(lszFileDate, "-%4d%02d%02d%02d%02d.log", 
		1900+lptm->tm_year,1+lptm->tm_mon,lptm->tm_mday, 
		lptm->tm_hour, lptm->tm_min);

	memcpy(mszLogFileName, mszLogFileNamePre, strlen(mszLogFileNamePre));
	memcpy(mszLogFileName+strlen(mszLogFileNamePre), lszFileDate, strlen(lszFileDate));
}


// ����TRACEѡ�� .����������� OR ��ѡ��
void CDebugTrace::SetTraceOptions(unsigned options /** New level for trace */ )
{
	muTraceOptions = options;
}

//ȡ��TRACEѡ��
unsigned CDebugTrace::GetTraceOptions(void)
{
	return muTraceOptions;
}

//�жϸ��������Ƿ���Դ�ӡ
bool CDebugTrace::CanTrace(int aiLogLevel)
{
	return (aiLogLevel <= mnLogLevel) && (aiLogLevel);
}

//*****************************************************************************
//  ����ԭ�ͣ�  BeginTrace(int aiLogLevel,char *apSrcFile,int aiSrcLine)
//  ����˵��:   ��ʼ��ӡһ����־
//  ������      int aiLogLevel(��־�ļ���),char *apSrcFile(Դ�ļ���),
//              int aiSrcLine(Դ����)
//  ����ֵ��    �������������
//  �÷���      BeginTrace(3,__FILE__,__LINE__)
//*****************************************************************************
CDebugTrace& CDebugTrace::BeginTrace(int aiLogLevel,char *apSrcFile,int aiSrcLine)
{      
	mlDataLen = 0;  //�Ѵ�ӡ�����ݳ�����0
	memset(mszPrintBuff, 0, (DEF_MAX_BUFF_LEN+1));
	miLogLevel = aiLogLevel;
		
	ftime(&moSystemTime);

	struct tm* lptm = localtime(&moSystemTime.time);

	//���Ҫ�����ʱ��,������־�������־������ʱ��(��:��:����)
	if (muTraceOptions & Timestamp) 
	{
		char lszTraceDataBuff[20];
		sprintf(lszTraceDataBuff,"%02d:%02d:%02d:%03d",\
			lptm->tm_hour, lptm->tm_min, lptm->tm_sec, moSystemTime.millitm);

		*this << lszTraceDataBuff<<' ';
	}
	//���Ҫ�������־����,������־�������־����
	if (muTraceOptions & LogLevel)
	{
		*this << aiLogLevel << ' ';
	}
	//���Ҫ�����Դ�ļ������к�,������־�����Դ�ļ������к�
	if ( muTraceOptions & FileAndLine ) 
	{
		*this << apSrcFile << "(" << aiSrcLine << ") ";
	}
	//���ض���
	return *this;
}


//*****************************************************************************
//  ����ԭ�ͣ�  EndTrace(CDebugTrace &aoDebugTrace)
//  ����˵��:   ������ӡһ����־
//  ������      CDebugTrace &aoDebugTrace(CDebugTrace ��������)
//  ����ֵ��    
//  �÷���      
//*****************************************************************************
// $_CODE_CHANGE 2005-09-09 fyf�޸ģ��������������
void CDebugTrace::EndTrace()       //������ӡ
{
	try
	{
#ifdef WIN32
		//��������Դ�����
		OutputDebugString( mszPrintBuff ); 
#endif

		//��Ҫ�����������̨,�����־��Ϣ�ڿ���̨Ҳ��ӡһ��
		if (muTraceOptions & PrintToConsole) 
		{
			printf( "%s" , mszPrintBuff );
		}

		//��Ҫ��д�ļ�����������־�ļ���,�����־��Ϣд���ļ���
		if ((muTraceOptions & AppendToFile) \
			&& (strlen(mszLogFileName) > 1))
		{
			//fanyunfeng ֱ��������ļ������������ʱ������
#ifdef LOG_OUTPUT_TO_FILE_DIRECT
			FILE* lfpTraceFile = NULL;
			lfpTraceFile = fopen(mszLogFileName,"a");  
			if(GetFileSize(lfpTraceFile) > muiLogFileSize)
			{
				SetLogFileName(mszLogFileNamePre);
				fclose(lfpTraceFile);
				lfpTraceFile = NULL;
				lfpTraceFile = fopen(mszLogFileName,"a");  
			}
			
			if (lfpTraceFile != NULL)
			{
				fprintf(lfpTraceFile,"%s",mszPrintBuff);
				fclose(lfpTraceFile);
			}
#else  //LOG_OUTPUT_TO_FILE_DIRECT
			AddToLogBuffer();
#endif //LOG_OUTPUT_TO_FILE_DIRECT
		}
	}
	catch( ... )
	{
	}
}

void CDebugTrace::AssertFail(char * strCond,char *strFile, unsigned uLine)
{
	char szMessage[512];    
	char strExePath[256];
	CCommon::GetAppPath(strExePath, 200);

#ifdef WIN32
	sprintf(szMessage, " Debug Assertion Failed!\n Program: %s   \n File: %s  \n Condition: ASSERT(%s);    \n Line:%d \n\n Continue?",
		strExePath,strFile,strCond,uLine);      

	int nResult = MessageBox(NULL,szMessage,"Assert failure",MB_OKCANCEL+MB_ICONERROR);

	sprintf(szMessage, " Debug Assertion Failed!\n File: %s Line:%d Condition: ASSERT(%s); \n",strFile,uLine,strCond);

	OutputDebugString(szMessage);

	if (nResult == IDCANCEL)
	{   
		FatalExit(-1);
	}
	DebugBreak();

#else
	sprintf(szMessage, " Debug Assertion Failed!\n Program: %s   \n File: %s  \n Condition: ASSERT(%s);    \n Line:%d \n\n",
		strExePath,strFile,strCond,uLine);      
	TRACE(1,szMessage);
	exit(0);
#endif
}

int CDebugTrace::Flush()
{
	int liRet = 0;

#ifndef  LOG_OUTPUT_TO_FILE_DIRECT
	CAutoLock loLock(moCriticalSection);
    try
    {
        if (mlBufDataLen > 0)
        {
            FILE* lfpTraceFile = NULL;
            lfpTraceFile = fopen(mszLogFileName,"a");  
			if(GetFileSize(lfpTraceFile) > muiLogFileSize)
			{
				SetLogFileName(mszLogFileNamePre);
				fclose(lfpTraceFile);
				lfpTraceFile = NULL;
				lfpTraceFile = fopen(mszLogFileName,"a");  
			}
            if (lfpTraceFile != NULL)
            {
                if(1 != fwrite(mszLogBuffer, mlBufDataLen, 1, lfpTraceFile))
				{
					liRet = errno;
				}
				fclose(lfpTraceFile);

				//���������
				mlBufDataLen = 0;
				memset(mszLogBuffer, 0, (LOG_BUFFER_LEN + 1));
			}
			else
			{
				liRet = errno;
			}
		}
	}
	catch(...)
	{
		liRet = errno;
	}
#endif // LOG_OUTPUT_TO_FILE_DIRECT
	return liRet;
}

#ifndef  LOG_OUTPUT_TO_FILE_DIRECT
bool CDebugTrace::AddToLogBuffer()
{
	int liFlushRet = 0;

	if ( mlDataLen > LOG_BUFFER_LEN - mlBufDataLen )
	{
		if (NULL != (liFlushRet = Flush()))
		{
			//������еĻ�����
			mlBufDataLen = 0;

			//����һ��������Ϣ
			struct timeb loSystemTime;
			ftime(&loSystemTime);
			struct tm* lptm = localtime(&loSystemTime.time);

			mlBufDataLen = sprintf(mszLogBuffer,"%02d:%02d:%02d:%03d ***CDebugTrace::AddToLogBuffer ���������ʱʧ�� ��־����ѭ������(ENO:%d)\n",
				lptm->tm_hour, lptm->tm_min, lptm->tm_sec, loSystemTime.millitm, liFlushRet);

		}
	}

	//ǰ���Ѿ�ȷ�Ϲ��������ĳ���
	//�������㹻��
	memcpy(mszLogBuffer + mlBufDataLen, mszPrintBuff, mlDataLen);
	mlBufDataLen += mlDataLen;
	return true;
}
#endif // LOG_OUTPUT_TO_FILE_DIRECT

//��ӡ��ǰ��ջ
void CDebugTrace::TraceStack(void)
{
	/*
	bool bResult = false;
	HANDLE         hProcess = GetCurrentProcess();
	HANDLE         hThread = GetCurrentThread();

	for( uint32_t index = 0; ; index++ ) 
	{
	bResult = StackWalk(
	IMAGE_FILE_MACHINE_I386,
	hProcess,
	hThread,
	&callStack,
	NULL, 
	NULL,
	SymFunctionTableAccess,
	SymGetModuleBase,
	NULL);

	if ( index == 0 )
	continue;

	if( !bResult || callStack.AddrFrame.Offset == 0 ) 
	break;

	GetFunctionInfoFromAddresses( callStack.AddrPC.Offset, callStack.AddrFrame.Offset, symInfo );
	GetSourceInfoFromAddress( callStack.AddrPC.Offset, srcInfo );

	fputs("    ", lfpTraceFile);
	fputs(srcInfo, lfpTraceFile);
	fputs("\n      ", lfpTraceFile);
	fputs(symInfo, lfpTraceFile);       
	fputs("\n", lfpTraceFile);
	}
	*/
}
