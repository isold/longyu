// WatchColorDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CWatchColorDlg �Ի���
class CWatchColorDlg : public CDialog
{
// ����
public:
	CWatchColorDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_WATCHCOLOR_DIALOG };

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
	CStatic m_StaticColorView;
public:
	CStatic m_StaticAd;
public:
	CEdit m_EditRGB;
public:
	CString m_StrCopyRight;
public:
	CStatic m_StaticCopyRight;
};
