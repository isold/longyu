// downloadfileDlg.h : ͷ�ļ�
//

#pragma once
#include "download/HttpDownload.h"

// CdownloadfileDlg �Ի���
class CdownloadfileDlg : public CDialog
{
// ����
public:
	CdownloadfileDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DOWNLOADFILE_DIALOG };

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
	afx_msg void OnBnClickedBtnDownload();
public:
	CString m_strUrl;
public:
	CString m_strLocal;
public:
	afx_msg void OnBnClickedButton2();
public:
	CString m_strProxyIp;
public:
	CString m_strProxyPort;
public:
	CString m_strProxyPassword;
public:
	CString m_strProxyUserName;
public:
	afx_msg void OnBnClickedButton1();
public:
	CString m_strUploadFileName;
public:
	afx_msg void OnBnClickedBtnUpload();
};
