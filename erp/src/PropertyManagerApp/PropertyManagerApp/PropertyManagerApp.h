
// PropertyManagerApp.h : PropertyManagerApp Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       

class CPropertyManagerAppApp : public CWinApp
{
	DECLARE_MESSAGE_MAP()
public:
	CPropertyManagerAppApp(void);


public:
	virtual BOOL InitInstance(void);

	afx_msg void OnAppAbout();
};

extern CPropertyManagerAppApp theApp;
