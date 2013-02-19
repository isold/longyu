// TransmitFileDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TransmitFile.h"
#include "TransmitFileDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
wlw::CWinInit wininit;

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CTransmitFileDlg �Ի���




CTransmitFileDlg::CTransmitFileDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTransmitFileDlg::IDD, pParent)
	, m_strFilePath(_T(""))
	, m_strBuddyIp(_T(""))
	, m_sBuddyPort(0)
	, m_strSelfInternetIp(_T(""))
	, m_strSelfLocalIp(_T(""))
	, m_sSelfLocalPort(0)
	, m_sSelfInternetPort(0)
	, m_strBuddyNatType(_T(""))
	, m_strSelfNatType(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTransmitFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strFilePath);
	DDX_Text(pDX, IDC_EDIT2, m_strBuddyIp);
	DDX_Text(pDX, IDC_EDIT3, m_sBuddyPort);
	DDX_Text(pDX, IDC_EDIT6, m_strSelfInternetIp);
	DDX_Text(pDX, IDC_EDIT8, m_strSelfLocalIp);
	DDX_Text(pDX, IDC_EDIT9, m_sSelfLocalPort);
	DDX_Text(pDX, IDC_EDIT7, m_sSelfInternetPort);
	DDX_Text(pDX, IDC_EDIT4, m_strBuddyNatType);
	DDX_Text(pDX, IDC_EDIT5, m_strSelfNatType);
}

BEGIN_MESSAGE_MAP(CTransmitFileDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(ID_BTN_RECV_FILE, &CTransmitFileDlg::OnBnClickedBtnRecvFile)
	ON_BN_CLICKED(IDC_BTN_SEND_FILE, &CTransmitFileDlg::OnBnClickedBtnSendFile)
	ON_BN_CLICKED(IDC_BTN_CLOSE, &CTransmitFileDlg::OnBnClickedBtnClose)
	ON_BN_CLICKED(IDC_BTN_FILE_PATH, &CTransmitFileDlg::OnBnClickedBtnFilePath)
	ON_WM_DEVMODECHANGE()
	ON_WM_DEVICECHANGE()
END_MESSAGE_MAP()


// CTransmitFileDlg ��Ϣ�������

BOOL CTransmitFileDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CTransmitFileDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTransmitFileDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CTransmitFileDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CTransmitFileDlg::OnBnClickedBtnRecvFile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CTransmitFileDlg::OnBnClickedBtnSendFile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
/************************************************************************/
/** 
  *��ȡ��������״̬
*/
/************************************************************************/
	HANDLE hand = WSACreateEvent();
	OVERLAPPED overlap;
	overlap.hEvent = WSACreateEvent();  
	DWORD dwRet = ::NotifyAddrChange(&hand, &overlap);  

	if (WaitForSingleObject(overlap.hEvent, INFINITE) == WAIT_OBJECT_0)
	{
		PrintLog(_LOG_LEVEL_DEBUG, "ip change");
	}
/************************************************************************/
/** 
* PING ����
*/
/************************************************************************/
	//code_net::CSocketAddr addr("20.108.22.43", 80);
	//code_net::CIcmp icmp(addr);
	//bool bReturn = icmp.ping();
	//if (bReturn)
	//{
	//	PrintLog(_LOG_LEVEL_DEBUG, "success");
	//}
	//else
	//{
	//	PrintLog(_LOG_LEVEL_DEBUG, "failed");
	//}
}

void CTransmitFileDlg::OnBnClickedBtnClose()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnCancel();
}

void CTransmitFileDlg::OnBnClickedBtnFilePath()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	char szFilters[] = "All Files (*.*)|*.*||";

	CFileDialog OpenFileDlg (TRUE, "", "",
		OFN_FILEMUSTEXIST| OFN_HIDEREADONLY, szFilters, this);
	if (OpenFileDlg.DoModal() == IDOK)
	{
		m_strFilePath = OpenFileDlg.GetPathName();
	}
	UpdateData(FALSE);

}

BOOL CTransmitFileDlg::OnDeviceChange(UINT nEventType, DWORD_PTR dwData)
{
	CDialog::OnDeviceChange(nEventType, dwData);
	return TRUE;
}

void CTransmitFileDlg::OnDevModeChange(LPTSTR lpDeviceName)
{
	CDialog::OnDevModeChange(lpDeviceName);

	// TODO: �ڴ˴������Ϣ����������
}
