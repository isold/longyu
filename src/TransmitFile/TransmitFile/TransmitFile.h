// TransmitFile.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CTransmitFileApp:
// �йش����ʵ�֣������ TransmitFile.cpp
//

class CTransmitFileApp : public CWinApp
{
public:
	CTransmitFileApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTransmitFileApp theApp;