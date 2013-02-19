// Sms.cpp : implementation file
//

#include "stdafx.h"
#include "Sms.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSms

CSms::CSms()
{
}

CSms::~CSms()
{
}


BEGIN_MESSAGE_MAP(CSms, CWnd)
	//{{AFX_MSG_MAP(CSms)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSms message handlers
//����ֵ ��1���ɹ���0��ʧ�ܣ�
//�򿪴���
int CSms::Open_Com(int port, int baud_rate){

	if(com.Open(port,baud_rate)==true){


		return 1;
	}
	else
		return 0;
}

void CSms::Set_Wnd(HWND hWnd){
	com.SetWnd(hWnd);
}

//�رմ���
void CSms::Close_Com(){
	com.Close();
}

LRESULT CSms::On_Receive(WPARAM wp, LPARAM lp)
{
	int len;
	char str[100];
	len = com.Read(str, 100);
	
	AfxMessageBox(" com Read!in dll");
	if(len > 0)
	{
		char com_str[10];
		strcpy(com_str, "COM");
		ltoa((long)wp, com_str + 3, 10); //	WPARAM ����˿ں�
		strResult+=str;
		AfxMessageBox(" com Read!in dll");


	}
	
	return 0;
}

//����ATָ��
int CSms::Send_ATCmd(char* ATCmd,char* result){
	int i,len=0;
	char str[300];
	CString beginstring;
	char beginstr[2];
	char endokstr[4]={' ',' ',' ',' '};
	char enderrorstr[7]={' ',' ',' ',' ',' ',' ',' '};
	int count=0;

	if(!com.IsOpen()) return 0;

	beginstring=ATCmd;

	strcpy(beginstr,beginstring.Left(2));

	if((strncmp(beginstr,"at", 2) == 0) || (strncmp(beginstr,"AT", 2) == 0)) {
	
		strResult="";

		i=com.Write(ATCmd);

		while(true){

			len = com.Read(str, 300);

			strResult+=str;

			if(strncmp(strResult.Right(4),"OK\r\n", 4) == 0) break;
			if(strncmp(strResult.Right(7),"ERROR\r\n", 7) == 0) break;

		}

		strcpy(result,strResult);

		return 1;
	}else{
		return 0;
	}

}

//��ȡSIM����������
int CSms::Get_SmCapacity(char* smCapacity){
	int i,len=0;
	char str[300];
	
	if(!com.IsOpen()) return 0;
	
	i=com.Write("AT+CPMS?\r");
	
	strResult="";
	
	while(true){
		len = com.Read(str, 300);
		
		strResult+=str;
		
		if(strncmp(strResult.Right(4),"OK\r\n", 4) == 0) break;
		if(strncmp(strResult.Right(7),"ERROR\r\n", 7) == 0) break;
	}
	
	strcpy(smCapacity,(strResult.Right(24)).Mid(0,11));
	
	return 1;
}

//��ȡ�������ĺ���
int CSms::Get_Smsc(char* smsc){
	int i,len=0;
	char str[300];

	if(!com.IsOpen()) return 0;

	i=com.Write("AT+CSCA?\r");

	strResult="";

	while(true){
		len = com.Read(str, 300);

		strResult+=str;

		if(strncmp(strResult.Right(4),"OK\r\n", 4) == 0) break;
		if(strncmp(strResult.Right(7),"ERROR\r\n", 7) == 0) break;
	}

	strcpy(smsc,(strResult.Right(24)).Mid(0,11));

	return 1;
}

//���ö������ĺ���
int CSms::Set_Smsc(char* smsc){
	int i,len=0;
	char str[300];
	char cmd[20];

	strcpy(cmd,"AT+CSCA=");
	strcat(cmd,smsc);
	strcat(cmd,"\r");

	if(!com.IsOpen()) return 0;

	i=com.Write(cmd);

	strResult="";

	while(true){
		len = com.Read(str, 300);

		strResult+=str;

		if(strncmp(strResult.Right(4),"OK\r\n", 4) == 0) return 1;
		if(strncmp(strResult.Right(7),"ERROR\r\n", 7) == 0) return 0;
	}

}

//���Ͷ���
int CSms::Send_Msg(char* PhoneID,char* SmsContent){
	SM_PARAM SmParam;
	int len,i;
	char str[300];
	char smsc[11];
	CString strSmsc;
	CString strNumber;
	CString strContent;
	int nPduLength;		// PDU������
	unsigned char nSmscLength;	// SMSC������
//	int nLength;		// �����յ������ݳ���
	char cmd[16];		// ���
	char pdu[512];		// PDU��
//	char ans[128];		// Ӧ��

	if(!com.IsOpen()) return 0;

	com.Write("AT+CMGF=0\r");
	while(true){
		len = com.Read(str, 300);

		strResult+=str;

		if(strncmp(strResult.Right(4),"OK\r\n", 4) == 0) break;
		if(strncmp(strResult.Right(7),"ERROR\r\n", 7) == 0) return 0;
	}


	i=Get_Smsc(smsc);

	if(i==0) return 0;

	strSmsc=smsc;

	strNumber=PhoneID;
	strContent=SmsContent;

		// ȥ������ǰ��"+"
		if(strSmsc[0] == '+')  strSmsc = strSmsc.Mid(1);
		if(strNumber[0] == '+')  strNumber = strNumber.Mid(1);

		// �ں���ǰ��"86"
		if(strSmsc.Left(2) != "86")  strSmsc = "86" + strSmsc;
		if(strNumber.Left(2) != "86")  strNumber = "86" + strNumber;

		// ������Ϣ�ṹ
		strcpy(SmParam.SCA, strSmsc);
		strcpy(SmParam.TPA, strNumber);
		strcpy(SmParam.TP_UD, strContent);
		SmParam.TP_PID = 0;
		SmParam.TP_DCS = GSM_UCS2;

	nPduLength = gsmEncodePdu(&SmParam, pdu);	// ����PDU����������PDU��
	strcat(pdu, "\x01a");		// ��Ctrl-Z����

	//AfxMessageBox(pdu);

	gsmString2Bytes(pdu, &nSmscLength, 2);	// ȡPDU���е�SMSC��Ϣ����
	nSmscLength++;		// ���ϳ����ֽڱ���

	// �����еĳ��ȣ�������SMSC��Ϣ���ȣ��������ֽڼ�
	sprintf(cmd, "AT+CMGS=%d\r", nPduLength / 2 - nSmscLength);	// ��������

	//AfxMessageBox(cmd);

	i=com.Write(cmd);

	strResult="";

	while(true){
		len = com.Read(str, 300);

			strResult+=str;

		if(strncmp(strResult.Right(2),"> ", 2) == 0) {

			com.Write(pdu);
			break;
		}

		if(strncmp(strResult.Right(7),"ERROR\r\n", 7) == 0) {
			return 0;
		}
	}

	while(true){
		len = com.Read(str, 300);

			strResult+=str;

		if(strncmp(strResult.Right(4),"OK\r\n", 4) == 0) {
			return 1;
		}

		if(strncmp(strResult.Right(7),"ERROR\r\n", 7) == 0) {
			return 0;
		}
	} 

}

//ɾ������
int CSms::Delete_Msg(int index){

	int len;
	char str[300];
	char cmd[16];		// ���

	if(!com.IsOpen()) return 0;

	sprintf(cmd, "AT+CMGD=%d\r", index);	// ��������

	// ������
	com.Write(cmd);

	strResult="";

	while(true){
		len = com.Read(str, 300);

		strResult+=str;

		if(strncmp(strResult.Right(4),"OK\r\n", 4) == 0) {
			return 1;
		}

		if(strncmp(strResult.Right(7),"ERROR\r\n", 7) == 0) {
			return 0;
		}
	}
}

//����Ŷ�����
int CSms::Read_Msg(int index,char* PhoneID,char* SmsContent,char* Date){
	int len;
	char str[300];
	char cmd[16];		// ���
	char sptr[512];
	char* ptr;
	SM_PARAM pMsg;

	if(!com.IsOpen()) return 0;

	strResult="";

	sprintf(cmd, "AT+CMGR=%d\r", index);	// ��������

	// ������
	com.Write(cmd);

	while(true){
		len = com.Read(str, 300);

		strResult+=str;

		if(strncmp(strResult.Right(4),"OK\r\n", 4) == 0) {

			strcpy(sptr,strResult);

			ptr=sptr;


			// ��ȡһ������Ϣ, ��"+CMGR:"��ͷ
			if((ptr = strstr(ptr, "+CMGR:")) != NULL){

				ptr = strstr(ptr, "\r\n");	// ����һ��
				if (ptr != NULL){
					ptr += 2;		// ����"\r\n", ��λ��PDU
			
					gsmDecodePdu(ptr, &pMsg);	// PDU������
				}
				strcpy(PhoneID,pMsg.TPA);
				strcpy(SmsContent,pMsg.TP_UD);
				strcpy(Date,pMsg.TP_SCTS);
			}

			return 1;
		}

		if(strncmp(strResult.Right(7),"ERROR\r\n", 7) == 0) {
			return 0;
		}
	}

}

//�����Ͷ����ж���
//type 0 �� ����δ������
//     1 �� �����Ѷ�����
//     2 �� ����δ���Ͷ���
//     3 �� �����ѷ��Ͷ���
//     4 �� ���ж���
int CSms::Read_AllMsg(int type,char* PhoneID,char* SmsContent,char* Date,char* Index){
	int len;
	char str[300];
	char cmd[16];		// ���
	char sptr[8192];
	char* ptr;
	SM_PARAM pMsg;
	int nMsg=0;

	if(!com.IsOpen()) return 0;

	strResult="";

	sprintf(cmd, "AT+CMGL=%d\r", type);	// ��������

	// ������
	com.Write(cmd);

	while(true){
		len = com.Read(str, 300);

		strResult+=str;

		//AfxMessageBox(strResult);

		if(strncmp(strResult.Right(4),"OK\r\n", 4) == 0) {

			strcpy(sptr,strResult);

			ptr=sptr;


			// ѭ����ȡÿһ������Ϣ, ��"+CMGL:"��ͷ
			while((ptr = strstr(ptr, "+CMGL:")) != NULL)
			{
	
				ptr += 7;		// ����"+CMGL:", ��λ�����

				//ȡ���		
				CString strindex=ptr;
				char cindex[2];
				int j=0;

				//AfxMessageBox(strindex);

				while(strindex.Mid(j,1)!=","){
					j++;
				}
				strcpy(cindex,strindex.Mid(0,j));

		
				ptr = strstr(ptr, "\r\n");	// ����һ��
				if (ptr != NULL)
				{
					ptr += 2;		// ����"\r\n", ��λ��PDU
				
					gsmDecodePdu(ptr, &pMsg);	// PDU������

					strcpy(PhoneID+nMsg*20,pMsg.TPA);
					strcpy(SmsContent+nMsg*512,pMsg.TP_UD);
					strcpy(Date+nMsg*20,pMsg.TP_SCTS);
					strcpy(Index+nMsg*3,cindex);

					nMsg++;		// ����Ϣ������1
				}		

			}

			return nMsg;
		}

		if(strncmp(strResult.Right(7),"ERROR\r\n", 7) == 0) {
			return 0;
		}
	}
}

//��ʼ��
int CSms::SMS_Init(){
	int i,len=0;
	char str[100];

	if(!com.IsOpen()) return 0;

	i=com.Write("AT\r");

	strResult="";

	while(true){
		len = com.Read(str, 300);

		strResult+=str;

		if(strncmp(strResult.Right(4),"OK\r\n", 4) == 0) break;
		if(strncmp(strResult.Right(7),"ERROR\r\n", 7) == 0) return 0;
	}

	i=com.Write("AT+CMEE=0\r");

	strResult="";

	while(true){
		len = com.Read(str, 300);

		strResult+=str;

		if(strncmp(strResult.Right(4),"OK\r\n", 4) == 0) break;
		if(strncmp(strResult.Right(7),"ERROR\r\n", 7) == 0) return 0;
	}

	i=com.Write("AT+CMGF=0\r");

	strResult="";

	while(true){
		len = com.Read(str, 300);

		strResult+=str;

		if(strncmp(strResult.Right(4),"OK\r\n", 4) == 0) break;
		if(strncmp(strResult.Right(7),"ERROR\r\n", 7) == 0) return 0;
	}

	return 1;

}

//���ö��ŷ���ģʽ
int CSms::Set_SendModle(int modle)
{
	int len;
	char str[300];
	char cmd[16];		// ���

	if(!com.IsOpen()) return 0;

	sprintf(cmd, "AT+CMGF=%d\r", modle);	// ��������

	AfxMessageBox(cmd);

	com.Write(cmd);

	strResult="";

	while(true){
		len = com.Read(str, 300);

		strResult+=str;

		AfxMessageBox(strResult);

		if(strncmp(strResult.Right(4),"OK\r\n", 4) == 0) {
			return 1;
		}

		if(strncmp(strResult.Right(7),"ERROR\r\n", 7) == 0) {
			return 0;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////
//private method
// �ɴ�ӡ�ַ���ת��Ϊ�ֽ�����
// �磺"C8329BFD0E01" --> {0xC8, 0x32, 0x9B, 0xFD, 0x0E, 0x01}
// ����: pSrc - Դ�ַ���ָ��
//       nSrcLength - Դ�ַ�������
// ���: pDst - Ŀ������ָ��
// ����: Ŀ�����ݳ���
int CSms::gsmString2Bytes(const char* pSrc, unsigned char* pDst, int nSrcLength)
{
	for (int i = 0; i < nSrcLength; i += 2)
	{
		// �����4λ
		if ((*pSrc >= '0') && (*pSrc <= '9'))
		{
			*pDst = (*pSrc - '0') << 4;
		}
		else
		{
			*pDst = (*pSrc - 'A' + 10) << 4;
		}

		pSrc++;

		// �����4λ
		if ((*pSrc>='0') && (*pSrc<='9'))
		{
			*pDst |= *pSrc - '0';
		}
		else
		{
			*pDst |= *pSrc - 'A' + 10;
		}

		pSrc++;
		pDst++;
	}

	// ����Ŀ�����ݳ���
	return (nSrcLength / 2);
}

// �ֽ�����ת��Ϊ�ɴ�ӡ�ַ���
// �磺{0xC8, 0x32, 0x9B, 0xFD, 0x0E, 0x01} --> "C8329BFD0E01" 
// ����: pSrc - Դ����ָ��
//       nSrcLength - Դ���ݳ���
// ���: pDst - Ŀ���ַ���ָ��
// ����: Ŀ���ַ�������
int CSms::gsmBytes2String(const unsigned char* pSrc, char* pDst, int nSrcLength)
{
	const char tab[]="0123456789ABCDEF";	// 0x0-0xf���ַ����ұ�

	for (int i = 0; i < nSrcLength; i++)
	{
		*pDst++ = tab[*pSrc >> 4];		// �����4λ
		*pDst++ = tab[*pSrc & 0x0f];	// �����4λ
		pSrc++;
	}

	// ����ַ����Ӹ�������
	*pDst = '\0';

	// ����Ŀ���ַ�������
	return (nSrcLength * 2);
}

// 7bit����
// ����: pSrc - Դ�ַ���ָ��
//       nSrcLength - Դ�ַ�������
// ���: pDst - Ŀ����봮ָ��
// ����: Ŀ����봮����
int CSms::gsmEncode7bit(const char* pSrc, unsigned char* pDst, int nSrcLength)
{
	int nSrc;		// Դ�ַ����ļ���ֵ
	int nDst;		// Ŀ����봮�ļ���ֵ
	int nChar;		// ��ǰ���ڴ���������ַ��ֽڵ���ţ���Χ��0-7
	unsigned char nLeft;	// ��һ�ֽڲ��������

	// ����ֵ��ʼ��
	nSrc = 0;
	nDst = 0;

	// ��Դ��ÿ8���ֽڷ�Ϊһ�飬ѹ����7���ֽ�
	// ѭ���ô�����̣�ֱ��Դ����������
	// ������鲻��8�ֽڣ�Ҳ����ȷ����
	while (nSrc < nSrcLength)
	{
		// ȡԴ�ַ����ļ���ֵ�����3λ
		nChar = nSrc & 7;

		// ����Դ����ÿ���ֽ�
		if(nChar == 0)
		{
			// ���ڵ�һ���ֽڣ�ֻ�Ǳ�����������������һ���ֽ�ʱʹ��
			nLeft = *pSrc;
		}
		else
		{
			// ���������ֽڣ������ұ߲��������������ӣ��õ�һ��Ŀ������ֽ�
			*pDst = (*pSrc << (8-nChar)) | nLeft;

			// �����ֽ�ʣ�µ���߲��֣���Ϊ�������ݱ�������
			nLeft = *pSrc >> nChar;

			// �޸�Ŀ�괮��ָ��ͼ���ֵ
			pDst++;
			nDst++;
		}

		// �޸�Դ����ָ��ͼ���ֵ
		pSrc++;
		nSrc++;
	}

	// ����Ŀ�괮����
	return nDst;
}

// 7bit����
// ����: pSrc - Դ���봮ָ��
//       nSrcLength - Դ���봮����
// ���: pDst - Ŀ���ַ���ָ��
// ����: Ŀ���ַ�������
int CSms::gsmDecode7bit(const unsigned char* pSrc, char* pDst, int nSrcLength)
{
	int nSrc;		// Դ�ַ����ļ���ֵ
	int nDst;		// Ŀ����봮�ļ���ֵ
	int nByte;		// ��ǰ���ڴ���������ֽڵ���ţ���Χ��0-6
	unsigned char nLeft;	// ��һ�ֽڲ��������

	// ����ֵ��ʼ��
	nSrc = 0;
	nDst = 0;
	
	// �����ֽ���źͲ������ݳ�ʼ��
	nByte = 0;
	nLeft = 0;

	// ��Դ����ÿ7���ֽڷ�Ϊһ�飬��ѹ����8���ֽ�
	// ѭ���ô�����̣�ֱ��Դ���ݱ�������
	// ������鲻��7�ֽڣ�Ҳ����ȷ����
	while(nSrc<nSrcLength)
	{
		// ��Դ�ֽ��ұ߲��������������ӣ�ȥ�����λ���õ�һ��Ŀ������ֽ�
		*pDst = ((*pSrc << nByte) | nLeft) & 0x7f;

		// �����ֽ�ʣ�µ���߲��֣���Ϊ�������ݱ�������
		nLeft = *pSrc >> (7-nByte);

		// �޸�Ŀ�괮��ָ��ͼ���ֵ
		pDst++;
		nDst++;

		// �޸��ֽڼ���ֵ
		nByte++;

		// ����һ������һ���ֽ�
		if(nByte == 7)
		{
			// ����õ�һ��Ŀ������ֽ�
			*pDst = nLeft;

			// �޸�Ŀ�괮��ָ��ͼ���ֵ
			pDst++;
			nDst++;

			// �����ֽ���źͲ������ݳ�ʼ��
			nByte = 0;
			nLeft = 0;
		}

		// �޸�Դ����ָ��ͼ���ֵ
		pSrc++;
		nSrc++;
	}

	// ����ַ����Ӹ�������
	*pDst = '\0';

	// ����Ŀ�괮����
	return nDst;
}

// 8bit����
// ����: pSrc - Դ�ַ���ָ��
//       nSrcLength - Դ�ַ�������
// ���: pDst - Ŀ����봮ָ��
// ����: Ŀ����봮����
int CSms::gsmEncode8bit(const char* pSrc, unsigned char* pDst, int nSrcLength)
{
	// �򵥸���
	memcpy(pDst, pSrc, nSrcLength);

	return nSrcLength;
}

// 8bit����
// ����: pSrc - Դ���봮ָ��
//       nSrcLength -  Դ���봮����
// ���: pDst -  Ŀ���ַ���ָ��
// ����: Ŀ���ַ�������
int CSms::gsmDecode8bit(const unsigned char* pSrc, char* pDst, int nSrcLength)
{
	// �򵥸���
	memcpy(pDst, pSrc, nSrcLength);

	// ����ַ����Ӹ�������
	*pDst = '\0';

	return nSrcLength;
}

// UCS2����
// ����: pSrc - Դ�ַ���ָ��
//       nSrcLength - Դ�ַ�������
// ���: pDst - Ŀ����봮ָ��
// ����: Ŀ����봮����
int CSms::gsmEncodeUcs2(const char* pSrc, unsigned char* pDst, int nSrcLength)
{
	int nDstLength;		// UNICODE���ַ���Ŀ
	WCHAR wchar[128];	// UNICODE��������

	// �ַ���-->UNICODE��
	nDstLength = MultiByteToWideChar(CP_ACP, 0, pSrc, nSrcLength, wchar, 128);

	// �ߵ��ֽڶԵ������
	for(int i=0; i<nDstLength; i++)
	{
		*pDst++ = wchar[i] >> 8;		// �������λ�ֽ�
		*pDst++ = wchar[i] & 0xff;		// �������λ�ֽ�
	}

	// ����Ŀ����봮����
	return nDstLength * 2;
}

// UCS2����
// ����: pSrc - Դ���봮ָ��
//       nSrcLength -  Դ���봮����
// ���: pDst -  Ŀ���ַ���ָ��
// ����: Ŀ���ַ�������
int CSms::gsmDecodeUcs2(const unsigned char* pSrc, char* pDst, int nSrcLength)
{
	int nDstLength;		// UNICODE���ַ���Ŀ
	WCHAR wchar[128];	// UNICODE��������

	// �ߵ��ֽڶԵ���ƴ��UNICODE
	for(int i=0; i<nSrcLength/2; i++)
	{
		wchar[i] = *pSrc++ << 8;	// �ȸ�λ�ֽ�
		wchar[i] |= *pSrc++;		// ���λ�ֽ�
	}

	// UNICODE��-->�ַ���
	nDstLength = WideCharToMultiByte(CP_ACP, 0, wchar, nSrcLength/2, pDst, 160, NULL, NULL);

	// ����ַ����Ӹ�������
	pDst[nDstLength] = '\0';

	// ����Ŀ���ַ�������
	return nDstLength;
}

// ����˳����ַ���ת��Ϊ�����ߵ����ַ�����������Ϊ��������'F'�ճ�ż��
// �磺"8613851872468" --> "683158812764F8"
// ����: pSrc - Դ�ַ���ָ��
//       nSrcLength - Դ�ַ�������
// ���: pDst - Ŀ���ַ���ָ��
// ����: Ŀ���ַ�������
int CSms::gsmInvertNumbers(const char* pSrc, char* pDst, int nSrcLength)
{
	int nDstLength;		// Ŀ���ַ�������
	char ch;			// ���ڱ���һ���ַ�

	// ���ƴ�����
	nDstLength = nSrcLength;

	// �����ߵ�
	for(int i=0; i<nSrcLength;i+=2)
	{
		ch = *pSrc++;		// �����ȳ��ֵ��ַ�
		*pDst++ = *pSrc++;	// ���ƺ���ֵ��ַ�
		*pDst++ = ch;		// �����ȳ��ֵ��ַ�
	}

	// Դ��������������
	if(nSrcLength & 1)
	{
		*(pDst-2) = 'F';	// ��'F'
		nDstLength++;		// Ŀ�괮���ȼ�1
	}

	// ����ַ����Ӹ�������
	*pDst = '\0';

	// ����Ŀ���ַ�������
	return nDstLength;
}

// �����ߵ����ַ���ת��Ϊ����˳����ַ���
// �磺"683158812764F8" --> "8613851872468"
// ����: pSrc - Դ�ַ���ָ��
//       nSrcLength - Դ�ַ�������
// ���: pDst - Ŀ���ַ���ָ��
// ����: Ŀ���ַ�������
int CSms::gsmSerializeNumbers(const char* pSrc, char* pDst, int nSrcLength)
{
	int nDstLength;		// Ŀ���ַ�������
	char ch;			// ���ڱ���һ���ַ�

	// ���ƴ�����
	nDstLength = nSrcLength;

	// �����ߵ�
	for(int i=0; i<nSrcLength;i+=2)
	{
		ch = *pSrc++;		// �����ȳ��ֵ��ַ�
		*pDst++ = *pSrc++;	// ���ƺ���ֵ��ַ�
		*pDst++ = ch;		// �����ȳ��ֵ��ַ�
	}

	// �����ַ���'F'��
	if(*(pDst-1) == 'F')
	{
		pDst--;
		nDstLength--;		// Ŀ���ַ������ȼ�1
	}

	// ����ַ����Ӹ�������
	*pDst = '\0';

	// ����Ŀ���ַ�������
	return nDstLength;
}

// PDU���룬���ڱ��ơ����Ͷ���Ϣ
// ����: pSrc - ԴPDU����ָ��
// ���: pDst - Ŀ��PDU��ָ��
// ����: Ŀ��PDU������
int CSms::gsmEncodePdu(const CSms::SM_PARAM* pSrc, char* pDst)
{
	int nLength;			// �ڲ��õĴ�����
	int nDstLength;			// Ŀ��PDU������
	unsigned char buf[256];	// �ڲ��õĻ�����

	// SMSC��ַ��Ϣ��
	nLength = strlen(pSrc->SCA);	// SMSC��ַ�ַ����ĳ���	
	buf[0] = (char)((nLength & 1) == 0 ? nLength : nLength + 1) / 2 + 1;	// SMSC��ַ��Ϣ����
	buf[1] = 0x91;		// �̶�: �ù��ʸ�ʽ����
	nDstLength = gsmBytes2String(buf, pDst, 2);		// ת��2���ֽڵ�Ŀ��PDU��
	nDstLength += gsmInvertNumbers(pSrc->SCA, &pDst[nDstLength], nLength);	// ת��SMSC���뵽Ŀ��PDU��

	// TPDU�λ���������Ŀ���ַ��
	nLength = strlen(pSrc->TPA);	// TP-DA��ַ�ַ����ĳ���
	buf[0] = 0x11;					// �Ƿ��Ͷ���(TP-MTI=01)��TP-VP����Ը�ʽ(TP-VPF=10)
	buf[1] = 0;						// TP-MR=0
	buf[2] = (char)nLength;			// Ŀ���ַ���ָ���(TP-DA��ַ�ַ�����ʵ����)
	buf[3] = 0x91;					// �̶�: �ù��ʸ�ʽ����
	nDstLength += gsmBytes2String(buf, &pDst[nDstLength], 4);		// ת��4���ֽڵ�Ŀ��PDU��
	nDstLength += gsmInvertNumbers(pSrc->TPA, &pDst[nDstLength], nLength);	// ת��TP-DA��Ŀ��PDU��

	// TPDU��Э���ʶ�����뷽ʽ���û���Ϣ��
	nLength = strlen(pSrc->TP_UD);	// �û���Ϣ�ַ����ĳ���
	buf[0] = pSrc->TP_PID;			// Э���ʶ(TP-PID)
	buf[1] = pSrc->TP_DCS;			// �û���Ϣ���뷽ʽ(TP-DCS)
	buf[2] = 0;						// ��Ч��(TP-VP)Ϊ5����
	if(pSrc->TP_DCS == GSM_7BIT)	
	{
		// 7-bit���뷽ʽ
		buf[3] = nLength;			// ����ǰ����
		nLength = gsmEncode7bit(pSrc->TP_UD, &buf[4], nLength+1) + 4;	// ת��TP-DA��Ŀ��PDU��
	}
	else if(pSrc->TP_DCS == GSM_UCS2)
	{
		// UCS2���뷽ʽ
		buf[3] = gsmEncodeUcs2(pSrc->TP_UD, &buf[4], nLength);	// ת��TP-DA��Ŀ��PDU��
		nLength = buf[3] + 4;		// nLength���ڸö����ݳ���
	}
	else
	{
		// 8-bit���뷽ʽ
		buf[3] = gsmEncode8bit(pSrc->TP_UD, &buf[4], nLength);	// ת��TP-DA��Ŀ��PDU��
		nLength = buf[3] + 4;		// nLength���ڸö����ݳ���
	}
	nDstLength += gsmBytes2String(buf, &pDst[nDstLength], nLength);		// ת���ö����ݵ�Ŀ��PDU��

	// ����Ŀ���ַ�������
	return nDstLength;
}

// PDU���룬���ڽ��ա��Ķ�����Ϣ
// ����: pSrc - ԴPDU��ָ��
// ���: pDst - Ŀ��PDU����ָ��
// ����: �û���Ϣ������
int CSms::gsmDecodePdu(const char* pSrc, CSms::SM_PARAM* pDst)
{
	int nDstLength;			// Ŀ��PDU������
	unsigned char tmp;		// �ڲ��õ���ʱ�ֽڱ���
	unsigned char buf[256];	// �ڲ��õĻ�����

	// SMSC��ַ��Ϣ��
	gsmString2Bytes(pSrc, &tmp, 2);	// ȡ����
	tmp = (tmp - 1) * 2;	// SMSC���봮����
	pSrc += 4;			// ָ����ƣ�������SMSC��ַ��ʽ
	gsmSerializeNumbers(pSrc, pDst->SCA, tmp);	// ת��SMSC���뵽Ŀ��PDU��
	pSrc += tmp;		// ָ�����

	// TPDU�λ�������
	gsmString2Bytes(pSrc, &tmp, 2);	// ȡ��������
	pSrc += 2;		// ָ�����

	// ȡ�ظ�����
	gsmString2Bytes(pSrc, &tmp, 2);	// ȡ����
	if(tmp & 1) tmp += 1;	// ������ż��
	pSrc += 4;			// ָ����ƣ������˻ظ���ַ(TP-RA)��ʽ
	gsmSerializeNumbers(pSrc, pDst->TPA, tmp);	// ȡTP-RA����
	pSrc += tmp;		// ָ�����

	// TPDU��Э���ʶ�����뷽ʽ���û���Ϣ��
	gsmString2Bytes(pSrc, (unsigned char*)&pDst->TP_PID, 2);	// ȡЭ���ʶ(TP-PID)
	pSrc += 2;		// ָ�����
	gsmString2Bytes(pSrc, (unsigned char*)&pDst->TP_DCS, 2);	// ȡ���뷽ʽ(TP-DCS)
	pSrc += 2;		// ָ�����
	gsmSerializeNumbers(pSrc, pDst->TP_SCTS, 14);		// ����ʱ����ַ���(TP_SCTS) 
	pSrc += 14;		// ָ�����
	gsmString2Bytes(pSrc, &tmp, 2);	// �û���Ϣ����(TP-UDL)
	pSrc += 2;		// ָ�����
	if(pDst->TP_DCS == GSM_7BIT)	
	{
		// 7-bit����
		nDstLength = gsmString2Bytes(pSrc, buf, tmp & 7 ? (int)tmp * 7 / 4 + 2 : (int)tmp * 7 / 4);	// ��ʽת��
		gsmDecode7bit(buf, pDst->TP_UD, nDstLength);	// ת����TP-DU
		nDstLength = tmp;
	}
	else if(pDst->TP_DCS == GSM_UCS2)
	{
		// UCS2����
		nDstLength = gsmString2Bytes(pSrc, buf, tmp * 2);			// ��ʽת��
		nDstLength = gsmDecodeUcs2(buf, pDst->TP_UD, nDstLength);	// ת����TP-DU
	}
	else
	{
		// 8-bit����
		nDstLength = gsmString2Bytes(pSrc, buf, tmp * 2);			// ��ʽת��
		nDstLength = gsmDecode8bit(buf, pDst->TP_UD, nDstLength);	// ת����TP-DU
	}

	// ����Ŀ���ַ�������
	return nDstLength;
}


// ���Ͷ���Ϣ���������������ȡӦ��
// ����: pSrc - ԴPDU����ָ��
int CSms::gsmSendMessage(CSms::SM_PARAM* pSrc)
{
	int nPduLength;		// PDU������
	unsigned char nSmscLength;	// SMSC������
	int nLength;		// �����յ������ݳ���
	char cmd[16];		// ���
	char pdu[512];		// PDU��
	char ans[128];		// Ӧ��

	nPduLength = gsmEncodePdu(pSrc, pdu);	// ����PDU����������PDU��
	strcat(pdu, "\x01a");		// ��Ctrl-Z����

	AfxMessageBox(pdu);

	gsmString2Bytes(pdu, &nSmscLength, 2);	// ȡPDU���е�SMSC��Ϣ����
	nSmscLength++;		// ���ϳ����ֽڱ���

	// �����еĳ��ȣ�������SMSC��Ϣ���ȣ��������ֽڼ�
	sprintf(cmd, "AT+CMGS=%d\r", nPduLength / 2 - nSmscLength);	// ��������

	AfxMessageBox(cmd);



	com.Write(cmd, strlen(cmd));	// ��������

	nLength = com.Read(ans, 128);	// ��Ӧ������

	// �����ܷ��ҵ�"\r\n> "�����ɹ����
	if(nLength == 4 && strncmp(ans, "\r\n> ", 4) == 0)
	{
//		return com.Write(pdu, strlen(pdu));		// �õ��϶��ش𣬼������PDU��
	}

	return 0;
}

// ��ȡ����Ϣ���������������ȡӦ��
// ��+CMGL����+CMGR����һ���Զ���ȫ������Ϣ
int CSms::gsmReadMessageList()
{
	return com.Write("AT+CMGL\r", 8);
}

// ɾ������Ϣ���������������ȡӦ��
// ����: index - ����Ϣ��ţ�1-255
int CSms::gsmDeleteMessage(int index)
{
	char cmd[16];		// ���

	sprintf(cmd, "AT+CMGD=%d\r", index);	// ��������

	// ������
	return com.Write(cmd, strlen(cmd));
}

// ��ȡGSM MODEM��Ӧ�𣬿�����һ����
// ���: pBuff - ����Ӧ�𻺳���
// ����: GSM MODEM��Ӧ��״̬, GSM_WAIT/GSM_OK/GSM_ERR
// ��ע: ������Ҫ��ε��ò�����ɶ�ȡһ��Ӧ���״ε���ʱӦ��pBuff��ʼ��
int CSms::gsmGetResponse(CSms::SM_BUFF* pBuff)
{
	int nLength;		// �����յ������ݳ���
	int nState;

	// �Ӵ��ڶ����ݣ�׷�ӵ�������β��
	nLength = com.Read(&pBuff->data[pBuff->len], 128);	
	pBuff->len += nLength;

	// ȷ��GSM MODEM��Ӧ��״̬
	nState = GSM_WAIT;
	if ((nLength > 0) && (pBuff->len >= 4))
	{
		if (strncmp(&pBuff->data[pBuff->len - 4], "OK\r\n", 4) == 0)  nState = GSM_OK;
		else if (strstr(pBuff->data, "+CMS ERROR") != NULL) nState = GSM_ERR;
	}

	return nState;
}

// ���б��н�����ȫ������Ϣ
// ����: pBuff - ����Ϣ�б�����
// ���: pMsg - ����Ϣ������
// ����: ����Ϣ����
int CSms::gsmParseMessageList(CSms::SM_PARAM* pMsg, CSms::SM_BUFF* pBuff)
{
	int nMsg;			// ����Ϣ����ֵ
	char* ptr;			// �ڲ��õ�����ָ��

	nMsg = 0;
	ptr = pBuff->data;

	// ѭ����ȡÿһ������Ϣ, ��"+CMGL:"��ͷ
	while((ptr = strstr(ptr, "+CMGL:")) != NULL)
	{
		ptr += 6;		// ����"+CMGL:", ��λ�����
		sscanf(ptr, "%d", &pMsg->index);	// ��ȡ���
//		TRACE("  index=%d\n",pMsg->index);

		ptr = strstr(ptr, "\r\n");	// ����һ��
		if (ptr != NULL)
		{
			ptr += 2;		// ����"\r\n", ��λ��PDU
			
			gsmDecodePdu(ptr, pMsg);	// PDU������

			pMsg++;		// ׼������һ������Ϣ
			nMsg++;		// ����Ϣ������1
		}
	}

	return nMsg;
}
