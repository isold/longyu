#pragma once


// CMultiConfirmDlg �Ի���

class CMultiConfirmDlg : public CDialog
{
	DECLARE_DYNAMIC(CMultiConfirmDlg)

public:
	CMultiConfirmDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMultiConfirmDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
