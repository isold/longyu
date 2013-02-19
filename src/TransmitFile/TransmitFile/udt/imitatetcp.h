#ifndef _IMITATE_TCP_H_
#define _IMITATE_TCP_H_

//    0                   1                   2                   3   
//    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 
//    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//  0 |                      Conversation Number                      |
//    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//  4 |                        Sequence Number                        |
//    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//  8 |                     Acknowledgment Number                     |
//    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//    |               |   |U|A|P|R|S|F|                               |
// 12 |    Control    |   |R|C|S|S|Y|I|            Window             |
//    |               |   |G|K|H|T|N|N|                               |
//    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// 16 |                       Timestamp sending                       |
//    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// 20 |                      Timestamp receiving                      |
//    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// 24 |                             data                              |
//    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

#include "..\..\..\..\include\defines.h"
#include "..\..\..\..\include\common\common.h"
#include "..\..\..\..\include\net\net.h"

namespace imitate_tcp
{
	//�������ֵ
	static const uint32 MAX_WIN_SIZE = 65535;
	//�������ݻ����С
	static const uint32 SEND_BUF_SIZE = 1024 * 60;
	//�������ݻ����С
	static const uint32 RECV_BUF_SIZE = 1024 * 90;
	//ACK�ظ�����������ֵ,���������ش�
	static const uint32 REXMTTHRESH = 3;
	//Ĭ��MSSֵ
	static const uint32 DEFAULT_MSS = 512;
	//windows max shift
	static const uint32 TCP_MAX_WINSHIFT = 14;

	/**********��ʱ�ش�ʱ����(RTO: retransmission timeout)**********/
	//��ʱ�ش��㷨��ѡ�� 
	//1.���� 2.RTOΪ�̶�ֵ 3. MIL-STD-1778(TCPIP���-24��) 4. Van Jacobson���㷨
	static const uint32 RTO_ALGORITHM = 4;
	//��С�ش���ʱʱ����(1S)
	static const uint32 MIN_RTO = 1; 
	//����ش���ʱʱ��(64S)
	static const uint32 MAX_RTO = 64;
	//Ĭ���ش���ʱʱ��(3S)
	static const uint32 DEF_ROT = 3;
	/**********��ʱ�ش�ʱ����(RTO: retransmission timeout)**********/


	/**********����ʱ����**********/
	//����̽��ʱ����(75S)
	static const uint32 KEEP_INIT = 75;
	//��һ��̽��ǰ�Ŀ���ʱ��(2Сʱ)
	static const uint32 KEEP_IDLE = 2 * 60 * 60;
	//Ĭ������̽��ʱ����(75S)
	static const uint32 KEEP_INTVL = 75;
	//̽��֮�󣬷���֮ǰ��ʱ��(10M)
	static const uint32 KEEP_PCNT = 10 * 60;
	/**********����ʱ����**********/

	/************************************************************************/
	//������ʱ����Сֵ(5S)
	static const uint32 PEERS_MIN = 5;
	//������ʱ�����ֵ(60S)
	static const uint32 PEERS_MAX = 60;
	//�ȴ�ĳ��ACK������ش�����
	static const uint32 MAX_RXTSHIFT = 12;
	//�Զ�����Ӧʱ,��󱣻���Դ���
	static const uint32 KEEP_COUNT = 8;
	//����SO_LINGER���ѡ������ʱ��(120S)
	static const uint32 LINGER_TIME = 120;
	/************************************************************************/

	//����״̬
	enum IT_STATE 
	{ 
		IT_CLOSE = 0, 
		IT_LISTEN = 1, 
		IT_SYN_SENT = 2, 
		IT_SYN_RECEIVED = 3, 
		IT_ESTABLISHED = 4, 
		IT_CLOSE_WAIT = 5, 
		IT_FIN_WAIT_1 = 6, 
		IT_CLOSING = 7, 
		IT_LAST_ACK = 8, 
		IT_FIN_WAIT_2 = 9, 
		IT_TIME_WAIT = 10
	};

	enum IT_TH_FLAGS 
	{ 
		TH_FIN = 0x01, //ȷ�������Ч 
		TH_SYN = 0x02, //���ͷ��ֽ�������
		TH_RST = 0x04, //���շ�Ӧ�������������ύ��Ӧ�ó���
		TH_PUSH = 0x08,//���Ӹ�λ
		TH_ACK = 0x10, //���ͬ��(��������)
		TH_URG = 0x20, //��������ƫ������Ч
	};

	enum IT_TF_FLAGS
	{
		TF_ACKNOW = 0x0001,//��������ACK
		TF_DELACK = 0x0002,//�ӳٷ���ACK
		TF_NODELAY = 0x0004,//���������û�����,���ȴ��γ�����Ķ�(��ֹNagle�㷨)
		TF_NOOPT = 0x0008,//��ʹ��TCPѡ��
		TF_SENTFIN = 0x0010,//FIN�ѷ���
		TF_REQ_SCALE = 0x0020, //�Ѿ�/��Ҫ��SYN���������󴰿ڱ仯ѡ��
		TF_RCVD_SCALE = 0x0040,//�Զ���SYN�����з��ʹ��ڱ仯ʱ��λ
		TF_REQ_TSTMP = 0x0080,//�Ѿ�/��Ҫ��SYN����������ʱ���ѡ��
		TF_RCVD_TSTMP = 0x0100,//�Զ���SYN�����з���ʱ���ѡ��ʱ��λ
		TF_SACK_PERMIT = 0x0200, //other side said I could SACK
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma pack(1)
	typedef struct
	{
		uint32 m_nConNum;
		uint32 m_nSeqNum;
		uint32 m_nAckNum;
		uint8  m_nControl;
		uint8  m_nFlag;  
		uint16 m_nWinSize;
		uint32 m_nTimeSend;
		uint32 m_nTimeRecv;
	}IT_HEADER,*PIT_HEADER;
#pragma pack()

	static const uint32 HEADER_SIZE = sizeof(IT_HEADER);
/////////////////////////////////////////////////////////////////////////////////////////////////////////
	class CImitateTcp
	{
	public:
		CImitateTcp(void);
		virtual ~CImitateTcp(void);

		const uint32 Now(void) const { return wlw::CTimeBase::GetTime(); }
		const uint32 GetError(void) const { return m_Error; }

		void TimerRangSet(uint32 tv, uint32 value, uint32 min, uint32 max);
		/**�ر����ж�ʱ��*/
		void CancelTimer();
		/**ÿ��200MS����һ��, ���ڲ����ӳ�ACK��ʱ��*/
		void FastTimer();
		/**ÿ��500MS����һ��, ���ڲ�������6����ʱ��: 
		* 1. ���ӽ�����ʱ��--
		* 2. �ش���ʱ��      --  ��TCPʵ������������һ����־ KEEP
		* 3. ������ʱ��      --  ��TCPʵ������������һ����־ KEEP
		* 4. ���ʱ��------
		* 5. FIN_WAIT_2��ʱ��--��TCPʵ������������һ����־
		* 6. 2MSL��ʱ��--------��TCPʵ������������һ����־
		*/
		void SlowTimer();
		/************************************************************************/
		/**
		*  ����������Ϊ0ʱ����
		*/
		/************************************************************************/
		void Timer(int timer);
		/************************************************************************/
		/** ������ʱ������
		*   �ڳ�����ʱ����ʱ�󽫵����������.��������õ���TCP���ش���ʱ�㷨.
		*/
		/************************************************************************/
		void SetPersist(void);
		/************************************************************************/
		/** �ڵõ�һ��RTT����ֵ,������ƽ��������(srtt)��ƽ��ƫ��(rttvar)ʱ���� 
		*/
		/************************************************************************/
		void XmitTimer();
	private:
		void Init(void);
	private:
		IT_HEADER m_itHeader;
		//����״̬
		IT_STATE m_itState;
		//������Ϣ
		uint32 m_Error;
		int8 m_SendBuf[SEND_BUF_SIZE];
		int8 m_RecvBuf[RECV_BUF_SIZE];
		//�������
		uint32 m_nSeq;
		//��ǰʱ��
		uint32 m_nNow;
		//���ݷ��Ͷ˵�ַ
		wlw::CSocketAddr m_AddrFrom;
		//���ݽ��ն˵�ַ
		wlw::CSocketAddr m_AddrTo;
		//�������ݰ�����
		uint32 m_nSendTotal;
		//�������ݰ�����
		uint32 m_nRecvTotal;
		//�ش����ݰ�����
		uint32 m_nRetransmitTotal;
		/*****************************�������***8**************************/
		//���ʹ��ڴ�С
		uint32 m_nSendWnd;
		//�����δȷ�ϵ����
		uint32 m_nSendUna;
		//��һ���������
		uint32 m_nSendNxt;
		//��������
		uint32 m_nSendMax;
		/*****************************�������*****************************/
		/*****************************�������****5*************************/
		//���մ��ڴ�С
		uint32 m_nRecvWnd;
		//��һ���������
		uint32 m_nRecvNxt;
		//ͨ��������ֵ��1
		uint32 m_nRecvAdv;
		/*****************************�������*****************************/
		/*****************************ʱ��****7*************************/
		//����SYN���ĺ�,���ӽ���ʱ��������
		//���û����75S���յ��ظ�,���ӽ���ֹ
		uint32 m_nTimerCon;
#define TIMER_CON 0
		//�ش���ʱ��,��̬����
		uint32 m_nTimerRetransmission;
#define TIMER_RETRANS 1
		//�յ�����ȷ�ϵ���������ȷ�ϵ����ݰ���,�ȴ�200MS����ȷ��,
		//�������200MS��������һ�����Ϸ��͵�����,ȷ�Ͼ͸�������
		//���һ����("�Ӵ�ȷ��")
		uint32 m_nTimerDelayAck;
#define TIMER_DELAYACK 2
		//������ʱ��(����δ����)
		uint32 m_nTimerPersist;
#define TIMER_PERSIST 3
		//���ʱ��,��������������г���2��Сʱ�ͷ���̽�����ݰ�,
		//ǿ�ƶԶ���Ӧ.����յ���Ӧ,��������.���δ�յ���Ӧ�ͳ���
		//���ɴ�(����δ��),һֱû����Ӧ����Ϊ�Զ˱���.
		uint32 m_nTimerKeepLive;
#define TIMER_KEEP 4
		//�����Ӵ�FIN_WAIT_1״̬��Ǩ��FIN_WAIT_2״̬���Ҳ����ٽ����κ�����
		//ʱ(��ζ��Ӧ�ý��̵�����close,����shutdown,û������TCP�İ�رչ���),
		//FIN_WAIT_2��ʱ������,��Ϊ10����.��ʱ����ʱ��,������Ϊ75S,�ڶ��γ�ʱ��
		//���ӱ��ر�.���������ʱ����ԭ���Ǳ���Զ�һֱ����FIN,ĳ�����ӻ���Զ
		//������FIN_WAIT_2״̬
		uint32 m_nTimerFinWait2;
#define TIMER_FIN_WAIT2 5
		//TIMN_WAIT��ʱ��,һ��Ҳ��Ϊ2MSL��ʱ��.2MSLָ������MSL.������ת�Ƶ�
		//TIME_WAIT״̬,�����������ر�ʱ,��ʱ������.���ӽ���TIME_WAIT״̬ʱ,
		//��ʱ���趨Ϊ1����,��ʱ��,TCP���ƿ��Internet PCB��ɾ��,�˿ڿ�����ʹ��.
		uint32 m_nTimerWait;
#define TIMER_WAIT 6
		/*****************************ʱ��*****************************/

#define TIMER_COUNT 7
		short m_nTimersp[TIMER_COUNT];

		IT_TF_FLAGS m_nTFlag;
		//Round-Trip Time: ����ʱ��
		uint32 m_nRTT;
		//�ط�ʱ��
		uint32 m_nRTO;

		/**��ʱ�ش��õ��ı���****************************************************/
		//��ƽ����RTT������ : m_nSrtt * 8
		uint32 m_nSrtt;
		//��ƽ����RTTƽ��ƫ�������: m_nRttvar * 4
		uint32 m_nRttvar;
		//��ǰ�ش�ʱ��:RTO
		uint32 m_nRxtcur;
		//�ش�ʱ����Сֵ
		uint32 m_nRttmin;
		//tcp_backoff[��������(ָ���˱�)]
		uint32 m_nRxtshift;
		//���: *8
#define RTT_SCALE 8
		//��λ: <<3
#define RTT_SHIFT 3
		//���: *4
#define RTTVAR_SCALE 4
		//��λ: <<2
#define RTTVAR_SHIFT 2
		/************************************************************************/
	};
	inline void CImitateTcp::Init(void)
	{
		memset(&m_itHeader, 0, sizeof(IT_HEADER));
		m_Error = 0;
		memset(m_SendBuf, 0, SEND_BUF_SIZE);
		memset(m_RecvBuf, 0, RECV_BUF_SIZE);
		m_nSeq = 0;
		m_itState = IT_LISTEN;
		m_nNow = Now();

		m_nSendWnd = MAX_WIN_SIZE << TCP_MAX_WINSHIFT;
	}

	inline void CImitateTcp::TimerRangSet(uint32 tv, uint32 value, uint32 min, uint32 max)
	{
		tv = value;
		if (tv < min) tv = min;
		else if(tv > max) tv = max;
	}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
}//end of namespace imitate_tcp
#endif //_IMITATE_TCP_H_
