// Vector.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "Vector.h"
#include "VectorDlg.h" 

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
 

BEGIN_MESSAGE_MAP(CVectorApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CVectorApp ����

CVectorApp::CVectorApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CVectorApp ����

CVectorApp theApp;


// CVectorApp ��ʼ��

BOOL CVectorApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);
 
	AfxOleInit();

	CWinApp::InitInstance();
	AfxEnableControlContainer();

	SetRegistryKey(_T("Vector"));
	
	CVectorDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
 
	return FALSE;
}
