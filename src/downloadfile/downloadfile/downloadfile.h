// downloadfile.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CdownloadfileApp:
// �йش����ʵ�֣������ downloadfile.cpp
//

class CdownloadfileApp : public CWinApp
{
public:
	CdownloadfileApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CdownloadfileApp theApp;