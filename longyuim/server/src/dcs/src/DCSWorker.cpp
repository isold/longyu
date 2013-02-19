

#include "DCSWorker.h"

CDCSWorker::CDCSWorker()
{
	m_pDcsConfig = NULL;
	uint64 time_now = CTimeBase::get_current_time();
	m_i64LastDumpTime = time_now;
	m_i64LastLogTime = time_now;
}

CDCSWorker::~CDCSWorker()
{
	m_ThreadManager.StopAll();
	m_DcsServer.RecvFrom.disconnect(this);
	m_DcsServer.OnErrorNotice.disconnect(this);
}

void CDCSWorker::SetConfig(CDCSConfig *apDcsConfig)
{
	ASSERT(apDcsConfig != NULL);
	m_pDcsConfig = apDcsConfig;
}

bool CDCSWorker::Init()
{
	m_DCSDealData.DealDataComplete.connect(this, &CDCSWorker::DealDataComplete);
	bool lbBind = false;
	unsigned short lusBindPort = m_pDcsConfig->server_port;
	struct sockaddr_in addr;
	addr.sin_addr.s_addr = htonl(m_pDcsConfig->server_ip);
	for(int i = 0; i < m_pDcsConfig->max_bind_time;++i)
	{
		bool bRet = m_DcsListenFd.CreateSocket(inet_ntoa(addr.sin_addr), 
			lusBindPort);
		if(bRet)
		{
			lbBind = true;
			break;
		}
	}

	if(!lbBind)
	{
		TRACE(1, "CDCSWorker::Run �󶨶˿�ʧ�ܡ�");
		return false;
	}

	bool bRet = m_DcsListenFd.SetNoBlock();
	if(!bRet)
	{
		m_DcsListenFd.Close();
		TRACE(1, "CDCSWorker::Run ���÷���������ʧ�ܡ�");
		return false;
	}
	bRet = m_DcsListenFd.Listen();
	if(!bRet)
	{
		m_DcsListenFd.Close();
		TRACE(1, "CDCSWorker::Run �����˿�ʧ�ܡ�");
		return false;
	}
	m_DcsListenFd.moNetStat = TCP_LISTEN;
	m_DcsListenFd.mbListenSocket = true;

	bRet = m_DcsServer.Init();
	if(!bRet)
	{
		TRACE(1, "CDCSWorker::Run EPOLL��ʼ��ʧ�ܡ�");
		return false;
	}
	bRet = m_DcsServer.Addfd(&m_DcsListenFd);
	if(!bRet)
	{
		TRACE(1, "CDCSWorker::Run ��Ӽ����˿ڵ�EPOLL��ʧ�ܡ�");
		m_DcsServer.Destroy();
		return false;
	}

	m_DcsServer.RecvFrom.connect(this, &CDCSWorker::DealDnsData);
	m_DcsServer.OnErrorNotice.connect(this, &CDCSWorker::OnDealErrorFd);

	return true;
}

unsigned int CDCSWorker::DealSendEvent(STRU_THREAD_CONTEXT& apContext)
{
	try
	{
		CDCSWorker* p = reinterpret_cast<CDCSWorker*>(apContext.mpWorkContext);
		ASSERT(p != NULL);
		for(;;)
		{
			bool bSendEmpty = true;
			bSendEmpty = p->m_DcsServer.SendData();
			if(bSendEmpty)
			{
				p->m_DcsServer.WaitSendEvent();
			}
		}
	}
	catch (...)
	{
		TRACE(1, "CDCSWorker::DealSendEvent �����쳣��");
	}
	return 0;
}

unsigned int CDCSWorker::DealRecvEvent(STRU_THREAD_CONTEXT& apContext)
{
	try
	{
		CDCSWorker* p = reinterpret_cast<CDCSWorker*>(apContext.mpWorkContext);
		ASSERT(p != NULL);
		for(;;)
		{
			bool bRecvEmpty = true;
			bRecvEmpty = p->m_DcsServer.RecvData();
			if( bRecvEmpty)
			{
				p->m_DcsServer.WaitRecvEvent();
			}
		}
	}
	catch (...)
	{
		TRACE(1, "CDCSWorker::DealRecvEvent �����쳣��");
	}
	return 0;
}

unsigned int CDCSWorker::CheckNetEvent(STRU_THREAD_CONTEXT& apContext)
{
	try
	{
		CDCSWorker* p = reinterpret_cast<CDCSWorker*>(apContext.mpWorkContext);
		ASSERT(p != NULL);
		for(;;)
		{
			int nRet = p->m_DcsServer.CheckEpollEvent(-1);
			p->m_DcsServer.ProcessEpollEvent(nRet);
		}
	}
	catch (...)
	{
		TRACE(1, "CDCSWorker::CheckNetEvent �����쳣��");
	}
	return 0;
}

void CDCSWorker::Run()
{
	ASSERT(m_pDcsConfig != NULL);
	try
	{
		bool bInitRet = Init();
		if(!bInitRet)
		{
			TRACE(1, "CDCSWorker::Run �����ʼ��ʧ�ܡ�");
			return;
		}

		if (0 == m_ThreadManager.Start(CheckNetEvent, this, 1, "dcs_check_net_event")) 
		{
			TRACE(1,"CDCSWorker::Run: �����¼��߳�����ʧ�ܣ������˳���");
			return;
		}

		if (0 == m_ThreadManager.Start(DealSendEvent, this, 1, "dcs_send_data")) 
		{
			TRACE(1,"CDCSWorker::Run: ���ݷ����߳�����ʧ�ܣ������˳���");
			return;
		}

		if (0 == m_ThreadManager.Start(DealRecvEvent, this, 1, "dcs_recv_data")) 
		{
			TRACE(1,"CDCSWorker::Run: ���ݽ����߳�����ʧ�ܣ������˳���");
			return;
		}

		for(;;)
		{
			TimeOutWork();
			usleep(1000*1000);
		}

		m_DcsServer.Delfd(m_DcsListenFd.miSocket);
		m_DcsListenFd.Close();
		m_DcsServer.Destroy();
	}
	catch (...)
	{
		TRACE(1, "CDCSWorker::Run �����쳣��");
	}
}

void CDCSWorker::Dump()
{

}

void CDCSWorker::TimeOutWork()
{
	uint64 time_now = CTimeBase::get_current_time();
	if(time_now > m_i64LastDumpTime + m_pDcsConfig->dump_info_time * 1000)
	{
		Dump();
		m_i64LastDumpTime = time_now;
	}

	if(time_now > m_i64LastLogTime + m_pDcsConfig->log_file_update_time * 1000)
	{
		unsigned int process_id = CCommon::GetProcessId();

		char lszLogFileName[255];
		memset(lszLogFileName, 0, 255);
		CFileStream::GetAppPath(lszLogFileName,255);

		//������־�ļ���Ϣ
		SET_TRACE_LEVEL(5);
		unsigned liOptions = (CDebugTrace::Timestamp | CDebugTrace::LogLevel
			& ~CDebugTrace::FileAndLine | CDebugTrace::AppendToFile);
		SET_TRACE_OPTIONS(GET_TRACE_OPTIONS() | liOptions);

		strcpy(strrchr(lszLogFileName,'/'),"//DCS_log");
		CFileStream::CreatePath(lszLogFileName);
		char lszFileDate[50];
		memset(lszFileDate, 0, 50);
		time_t loSystemTime;
		time(&loSystemTime);
		struct tm* lptm = localtime(&loSystemTime);
		sprintf(lszFileDate, "//DCS-%u-%4d%02d%02d%02d%02d.log", process_id,
			1900+lptm->tm_year,1+lptm->tm_mon,lptm->tm_mday, lptm->tm_hour, lptm->tm_min);
		strcat(lszLogFileName,lszFileDate);
		SET_LOG_FILENAME(lszLogFileName);
		m_i64LastLogTime = time_now;
	}
}

void CDCSWorker::OnDealErrorFd(int fd)
{
	TRACE(1, "CDCSWorker::OnDealErrorFd fd = "<<fd);
}

void CDCSWorker::DealDnsData(int fd, char *buffer, int length)
{
	char rtn[DEF_BUFFER_LEN];
	memset(rtn, 0, DEF_BUFFER_LEN);
	uint32 rtn_len = 0;
	uint32 rtn_del = m_DCSDealData.DCSDealData(buffer, length, rtn, rtn_len);
	switch(rtn_del)
	{
	case 0:
		{
			break;
		}
	case 1:
		{
			m_DcsServer.SendData(fd, rtn, rtn_len);
			break;
		}
	case 2:
		{
			m_DcsServer.SendAllData(rtn, rtn_len);
			break;
		}
	default:
		{
			TRACE(1, "CDCSWorker::DealRecvData δ֪�������͡����ͣ�"<<rtn_del);
			break;
		}
	}
}

void CDCSWorker::DealDataComplete(int rtn_op, int fd, CBasePack *pack)
{
	char rtn[DEF_BUFFER_LEN];
	memset(rtn, 0, DEF_BUFFER_LEN);
	uint32 rtn_len = 0;

	if(pack != NULL)
	{
		if(pack->Pack(rtn, rtn_len) == -1)
		{
			TRACE(1, "CDCSWorker::DealDataComplete ������ִ���");
			return;
		}
	}

	switch(rtn_op)
	{
	case 0:
		{
			break;
		}
	case 1:
		{
			m_DcsServer.SendData(fd, rtn, rtn_len);
			break;
		}
	case 2:
		{
			m_DcsServer.SendAllData(rtn, rtn_len);
			break;
		}
	default:
		{
			TRACE(1, "CDCSWorker::DealRecvData δ֪�������͡����ͣ�"<<rtn_op);
			break;
		}
	}
	return;
}