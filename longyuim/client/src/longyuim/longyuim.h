
// longyuim.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "TcpTransfer.h"


// ClongyuimApp:
// �йش����ʵ�֣������ longyuim.cpp
//

class ClongyuimApp : public CWinApp
{
public:
	ClongyuimApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
public:
	CTcpTransfer mTcpTransfer;
};

extern ClongyuimApp theApp;