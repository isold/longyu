#pragma once
#include "../UI/UIControl.h"

// CUserList �Ի���

class CUserList : public CDialog
{
	DECLARE_DYNAMIC(CUserList)

public:
	CUserList(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUserList();

// �Ի�������
	enum { IDD = IDD_DIALOG_LIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	CBaseTree* mpTreeCtrl;
public:
	void Initialize();
	void AddUser(void* pDate);
	void DelUser(__int64 ai64UserID);
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
private:
	bool mbTrackLeaveMsg;
public:
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
};
