// TransmitFileDlg.h : ͷ�ļ�
//

#pragma once
#include <strstream>
#include <string>

// CTransmitFileDlg �Ի���
class CTransmitFileDlg : public CDialog
{
// ����
public:
	CTransmitFileDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TRANSMITFILE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnRecvFile();
public:
	afx_msg void OnBnClickedBtnSendFile();
public:
	afx_msg void OnBnClickedBtnClose();
public:
	afx_msg void OnBnClickedBtnFilePath();
public:
	CString m_strFilePath;
public:
	CString m_strBuddyIp;
public:
	short m_sBuddyPort;
public:
	CString m_strSelfInternetIp;
public:
	CString m_strSelfLocalIp;
public:
	short m_sSelfLocalPort;
public:
	short m_sSelfInternetPort;
public:
	CString m_strBuddyNatType;
public:
	CString m_strSelfNatType;
public:
	afx_msg void OnDevModeChange(LPTSTR lpDeviceName);
	afx_msg BOOL OnDeviceChange(UINT nEventType,DWORD_PTR dwData );
};
