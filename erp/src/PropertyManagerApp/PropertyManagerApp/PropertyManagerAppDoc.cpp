
// PropertyManagerAppDoc.cpp : CPropertyManagerAppDoc ���ʵ��
//

#include "stdafx.h"
#include "PropertyManagerApp.h"

#include "PropertyManagerAppDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPropertyManagerAppDoc

IMPLEMENT_DYNCREATE(CPropertyManagerAppDoc, CDocument)

BEGIN_MESSAGE_MAP(CPropertyManagerAppDoc, CDocument)
END_MESSAGE_MAP()


// CPropertyManagerAppDoc ����/����

CPropertyManagerAppDoc::CPropertyManagerAppDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CPropertyManagerAppDoc::~CPropertyManagerAppDoc()
{
}

BOOL CPropertyManagerAppDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CPropertyManagerAppDoc ���л�

void CPropertyManagerAppDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// CPropertyManagerAppDoc ���

#ifdef _DEBUG
void CPropertyManagerAppDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPropertyManagerAppDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CPropertyManagerAppDoc ����
