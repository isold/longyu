#include "stdafx.h"
#include "Excel.h" 


/******************************************************************************
*
* ��������VBAReportDemo�Ķ�Ӧ����
* ��ʾʹ��VC����Excel 2003
* ���ܣ����õ�Ԫ�񣬷�񣬶��ᴰ���Լ���ν���Ӧ��VB���뷭���VC
*
* ʱ�䣺2007-04-16 09:31
* ���ߣ��ߺ�ΰ(DukeJoe)
* QQ��21807822
* Blog��http://dukejoe.yeah.net
* ע�ͣ�������ɵ����о�������ú������VBAReportDemo��Ӧ���ȽϺ�
*
* ����������Visual Studio.NET 2003
* ����ϵͳ��Windows XP Home Edition Service Pack 2
*
*
*****************************************************************************/
/*
#include <iostream>

using namespace std ;

#import "C:\Program Files\Common Files\Microsoft Shared\OFFICE11\mso.dll" rename("RGB", "MSRGB")

#import "C:\Program Files\Common Files\Microsoft Shared\VBA\VBA6\VBE6EXT.OLB" raw_interfaces_only, \
	rename("Reference", "ignorethis"), rename("VBE", "JOEVBE")

#import "C:\Program Files\Microsoft Office\OFFICE11\excel.exe" exclude("IFont", "IPicture") \
	rename("RGB", "ignorethis"), rename("DialogBox", "ignorethis"), rename("VBE", "JOEVBE"), \
	rename("ReplaceText", "JOEReplaceText"), rename("CopyFile","JOECopyFile"), \
	rename("FindText", "JOEFindText"), rename("NoPrompt", "JOENoPrompt")

using namespace Office;
using namespace VBIDE;
using namespace Excel ;

int ExportExcelFile() ;

int main(int argc, char* argv[])
{
	if(FAILED(::CoInitialize(NULL)))
		return 1 ;

	ExportExcelFile() ;

	::CoUninitialize();

	return 0;
}

int ExportExcelFile()
{
	_ApplicationPtr pApplication = NULL ;
	_WorkbookPtr pThisWorkbook = NULL ;
	_WorksheetPtr pThisWorksheet = NULL ;
	SheetsPtr pThisSheets = NULL ;
	RangePtr pThisRange = NULL ;
	_variant_t vt ;
	Excel::XlFileFormat vFileFormat ;
	Excel::XlSaveAsAccessMode vSaveAsAccessMode ;
	Excel::XlSaveConflictResolution vSaveConflictResolution ;

	pApplication.CreateInstance("Excel.Application");
	pApplication->PutVisible (0,VARIANT_TRUE);
	pThisWorkbook = pApplication->GetWorkbooks()->Add() ;
	pThisSheets = pThisWorkbook->GetWorksheets() ;
	pThisWorksheet = pThisSheets->GetItem((short)1);
	// ��������sheet�����ɫΪ��ɫ
	pThisWorksheet->GetCells()->GetInterior()->PutColor(RGB(255, 255, 255));
	pThisWorksheet->GetCells()->ClearContents() ;
	pThisRange = pThisWorksheet->GetRange("A1:C5") ;
	pThisRange->ClearFormats() ;
	// ����в���ģ�������debug�ļ��е�excel.tlh������
	//pThisRange->GetItem(1,1) ;
	pThisRange->PutItem(1, 1, _variant_t("��������ƽ����")) ;
	pThisRange->PutItem(1, 2, _variant_t("�ߺ�ΰ")) ;
	pThisRange->PutItem(1, 3, _variant_t("QQ:21807822")) ;
	pThisRange->PutItem(2, 1, _variant_t("1")) ;
	pThisRange->PutItem(3, 1, _variant_t("2")) ;
	pThisRange->PutItem(4, 1, _variant_t("3")) ;
	pThisRange->PutItem(5, 1, _variant_t("4")) ;
	// ΪRange�����ܺ��ڲ����ϱ߿�
	pThisRange->GetBorders()->GetItem(xlEdgeLeft)->PutLineStyle(xlContinuous) ;
	pThisRange->GetBorders()->GetItem(xlEdgeTop)->PutLineStyle(xlContinuous) ;
	pThisRange->GetBorders()->GetItem(xlEdgeRight)->PutLineStyle(xlContinuous) ;
	pThisRange->GetBorders()->GetItem(xlEdgeBottom)->PutLineStyle(xlContinuous) ;
	pThisRange->GetBorders()->GetItem(xlInsideHorizontal)->PutLineStyle(xlContinuous) ;
	pThisRange->GetBorders()->GetItem(xlInsideVertical)->PutLineStyle(xlContinuous) ;
	// ���õ�һ�еĸ�ʽ������ɫ�����塢��ɫ���п�
	pThisRange->GetRange("A1:C1")->GetInterior()->ColorIndex = 47 ;
	pThisRange->GetRange("A1:C1")->GetInterior()->Pattern = xlPatternSolid ;
	pThisRange->GetRange("A1:C1")->GetFont()->ColorIndex = 6 ;
	pThisRange->GetRange("A1:C1")->GetFont()->Bold = TRUE ;
	pThisRange->GetEntireColumn()->ColumnWidth = 18.63 ;
	pThisRange->GetRange("A2:C5")->GetInterior()->ColorIndex = 16 ;
	pThisRange->GetRange("A2:C5")->GetInterior()->Pattern = xlPatternSolid ;
	pThisRange->GetRange("A2:C5")->GetFont()->ColorIndex = 2 ;
	// ���ᴰ��
	pApplication->ActiveWindow->FreezePanes = FALSE ;
	pApplication->Range["A2"]->Select() ;
	pApplication->ActiveWindow->FreezePanes = TRUE ;

	// �����˳�
	vSaveAsAccessMode = xlNoChange ;
	vFileFormat = xlWorkbookNormal ;
	vSaveConflictResolution = xlLocalSessionChanges ;
	pThisWorkbook->SaveAs(_variant_t("D:\\Visual Studio Projects\\VCReportDemo\\joe.xls"), vFileFormat,_variant_t(""),_variant_t(""), _variant_t(false),
		_variant_t(false), vSaveAsAccessMode, vSaveConflictResolution, _variant_t(false)) ;
	pThisWorkbook->Close();
	pApplication->Quit();

	return 0 ;
}
*/