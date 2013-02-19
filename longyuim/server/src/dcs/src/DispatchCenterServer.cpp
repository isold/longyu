
/********************************************************************
	created:	2010/04/12
	created:	12:4:2010   13:57
	filename: 	DispatchCenterServer.cpp
	file path:	crs_servers\dcs\src
	file base:	DispatchCenterServer
	file ext:	cpp
	author:		sina
	
	purpose:	
*********************************************************************/

#include "DCSInclude.h"
#include "DCSWorker.h"

CDebugTrace *goDebugTrace = NULL;

void help_info()
{
	cout<<"SinaShow Dispatch Center Server Help Infomation:"<<endl;
	cout<<"./dcs -f config_file_name(���г���)"<<endl;
	cout<<"./dcs -v(�鿴����汾)"<<endl;
	cout<<"./dcs -h(�鿴������Ϣ)"<<endl;
	cout<<"Copyright (C) Beijing Sina Information Technology Co.,Ltd 2009-2010"<<endl;
};

int main(int argc, char* argv[])
{
	if(argc > 1 && strcmp(argv[1], "-v") == 0)
	{
		cout<<"SinaShow DCS Version Infomation:"<<endl;
		cout<<"CrsTrans Version: "<<gstrDCSWorkerVersion.c_str()<<endl;
		cout<<"Copyright (C) Beijing Sina Information Technology Co.,Ltd 2003-2009"<<endl;
		return 0;
	}

	if(argc > 1 && strcmp(argv[1], "-h") == 0)
	{
		help_info();
		return 0;
	}

	if(argc > 1 && strcmp(argv[1], "-f") != 0)
	{
		help_info();
		return 0;
	}

	string lstrConfigName = "";
	if(argc > 1 && strcmp(argv[1], "-f") == 0)
	{
		lstrConfigName = argv[2];
		if(lstrConfigName.empty())
		{
			help_info();
			return 0;
		}
	}

	char lszLogFileName[255];
	memset(lszLogFileName, 0, 255);
	CFileStream::GetAppPath(lszLogFileName,255);

	string lstrAppPath = lszLogFileName;
	string lstrApp = lstrAppPath.substr(0, lstrAppPath.find_last_of('/'));
	if (chdir(lstrApp.c_str()))
	{
		cout<<"crs_trans error: chdir error."<<lszLogFileName<<endl;
		return 0;
	}

	goDebugTrace = new CDebugTrace;

	unsigned int process_id = CCommon::GetProcessId();

	//������־�ļ���Ϣ
	SET_TRACE_LEVEL(5);
	unsigned liOptions = (CDebugTrace::Timestamp | CDebugTrace::LogLevel
		& ~CDebugTrace::FileAndLine | CDebugTrace::AppendToFile);
	SET_TRACE_OPTIONS(GET_TRACE_OPTIONS() | liOptions);

	strcpy(strrchr(lszLogFileName,'/'),"//DCS_log");
	CFileStream::CreatePath(lszLogFileName);
	char lszFileDate[50];
	memset(lszFileDate, 0, 50);
	sprintf(lszFileDate, "//DCS-%u", process_id);
	strcat(lszLogFileName,lszFileDate);
	SET_LOG_FILENAME(lszLogFileName);
	TRACE(1,"\n\n*******************DCS������־VERSION:" <<
		gstrDCSWorkerVersion.c_str() << "*******************");

	TRACE(1, "�����ļ���Ϣ: "<<lstrConfigName.c_str());

	//���������ļ�
	CDCSConfig loDCSConfig;
	loDCSConfig.set_conf_file_name(lstrConfigName.c_str());
	bool bRet = loDCSConfig.load();
	if(!bRet)
	{
		TRACE(1, "ERROR: ���������ļ�ʧ�ܡ�");
		return 0;
	}

	CDCSWorker worker;
	worker.SetConfig(&loDCSConfig);
	worker.Run();

	return 0;
}












