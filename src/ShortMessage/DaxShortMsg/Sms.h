#if !defined(AFX_SMS_H__B34AC0BB_9C66_46F4_A48E_8C09CF93ADD6__INCLUDED_)
#define AFX_SMS_H__B34AC0BB_9C66_46F4_A48E_8C09CF93ADD6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Sms.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSms window
#include "cnComm.h"

class CSms : public CWnd
{
// Construction
public:
	LRESULT On_Receive(WPARAM wp, LPARAM lp);
	CSms();
	int Open_Com(int port, int baud_rate);
	void Close_Com();
	void Set_Wnd(HWND hWnd);
	int Send_ATCmd(char* ATCmd,char* result);
	int Send_Msg(char* PhoneID,char* SmsContent);
	int Delete_Msg(int index);
	int Read_Msg(int index,char* PhoneID,char* SmsContent,char* Date);
	int Get_Smsc(char* smsc);
	int Set_Smsc(char* smsc);
	int Read_AllMsg(int type,char* PhoneID,char* SmsContent,char* Date,char* Index);
	int SMS_Init();
	int Set_SendModle(int modle);
	int Get_SmCapacity(char* smCapacity);
// Attributes
public:
	CString strResult;


// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSms)
	//}}AFX_VIRTUAL

// Implementation
public:
	cnComm com;//����
	virtual ~CSms();

	// Generated message map functions
protected:
	
	//_thread_com com;
	//_sync_com com;
	//_asyn_com com;
	//{{AFX_MSG(CSms)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	// ����Ϣ�����ṹ������/���빲��
// ���У��ַ�����'\0'��β
typedef struct {
	char SCA[16];			// ����Ϣ�������ĺ���(SMSC��ַ)
	char TPA[16];			// Ŀ������ظ�����(TP-DA��TP-RA)
	char TP_PID;			// �û���ϢЭ���ʶ(TP-PID)
	char TP_DCS;			// �û���Ϣ���뷽ʽ(TP-DCS)
	char TP_SCTS[16];		// ����ʱ����ַ���(TP_SCTS), ����ʱ�õ�
	char TP_UD[160];		// ԭʼ�û���Ϣ(����ǰ�������TP-UD)
	short index;			// ����Ϣ��ţ��ڶ�ȡʱ�õ�
} SM_PARAM;
// �û���Ϣ���뷽ʽ
#define GSM_7BIT		0
#define GSM_8BIT		4
#define GSM_UCS2		8

// Ӧ��״̬
#define GSM_WAIT		0		// �ȴ�����ȷ��
#define GSM_OK			1		// OK
#define GSM_ERR			-1		// ERROR

// ��ȡӦ��Ļ�����
typedef struct {
	int len;
	char data[16384];
} SM_BUFF;

int gsmBytes2String(const unsigned char* pSrc, char* pDst, int nSrcLength);
int gsmString2Bytes(const char* pSrc, unsigned char* pDst, int nSrcLength);
int gsmEncode7bit(const char* pSrc, unsigned char* pDst, int nSrcLength);
int gsmDecode7bit(const unsigned char* pSrc, char* pDst, int nSrcLength);
int gsmEncode8bit(const char* pSrc, unsigned char* pDst, int nSrcLength);
int gsmDecode8bit(const unsigned char* pSrc, char* pDst, int nSrcLength);
int gsmEncodeUcs2(const char* pSrc, unsigned char* pDst, int nSrcLength);
int gsmDecodeUcs2(const unsigned char* pSrc, char* pDst, int nSrcLength);
int gsmInvertNumbers(const char* pSrc, char* pDst, int nSrcLength);
int gsmSerializeNumbers(const char* pSrc, char* pDst, int nSrcLength);
int gsmEncodePdu(const SM_PARAM* pSrc, char* pDst);
int gsmDecodePdu(const char* pSrc, SM_PARAM* pDst);

int gsmSendMessage(SM_PARAM* pSrc);
int gsmReadMessageList();
int gsmDeleteMessage(int index);

int gsmGetResponse(SM_BUFF* pBuff);

int gsmParseMessageList(SM_PARAM* pMsg, SM_BUFF* pBuff);

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SMS_H__B34AC0BB_9C66_46F4_A48E_8C09CF93ADD6__INCLUDED_)
