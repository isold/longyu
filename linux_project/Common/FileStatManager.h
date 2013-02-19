#ifndef _FILEMANAGER_H_
#define _FILEMANAGER_H_


#include <sys/stat.h>
#include "include.h"
#include "define.h"

#define stat_fn stat
#define lstat_fn lstat
#define fstat_fn fstat
#define chmod_fn chmod
#define fchmod_fn fchmod
#define lchmod_fn lchmod
#define fchmodat_fn fchmodat
#define chown_fn chown

class CFileStatManager{
public:

	CFileStatManager (){
		Reset();
	}

	~CFileStatManager (){
		Reset();
	}

	void		Reset (){
		mbooChecked					=		FAILED;
		memset( &moStatus, 0, sizeof( stat_t ) );
		memset( mszFileName, 0, FILE_NAME_LEN );
	}

	// ��	�ܣ���ȡָ���ļ�Name��status��Ϣ��
	// ��	����pFileName ָ�����ļ�����
	// ��	�أ��ɹ� SUCCEEDED��ʧ�� FAILED��
	uint8		Check ( const char* pFileName = NULL );

	// ��	�ܣ���ȡָ���ļ������͡�
	// ��	������
	// ��	�أ��ļ�����
	uint32		GetFileType ();

	// ��	�ܣ���ȡ����Ȩ�ޡ�
	// ��	������
	// ��	�أ�����Ȩ��
	uint16		GetFileAccessPermission ();

	// ��	�ܣ����÷���Ȩ�ޡ�
	// ��	��������Ȩ��
	// ��	�أ��ɹ� SUCCEEDED��ʧ�� FAILED��
	uint8		SetFileAccessPermission ( uint16 );

	// ��	�ܣ��޸��ļ���ӵ�����˻�
	// ��	����uid �µ��˻�ID
	// ��	�أ��ɹ� SUCCEEDED��ʧ�� FAILED��
	uint8		ChangeFileOwner ( uid_t uid );

private:
	// ��	�ܣ�ָ���ļ��Ƿ��ȡ�ɹ�
	// ��	������
	// ��	�أ��ɹ� SUCCEEDED��ʧ�� FAILED��
	uint8		BeChecked (){
		return mbooChecked;
	}
	
private:
	typedef struct stat		stat_t;
	static const int		FILE_NAME_LEN = 255;
	char					mszFileName[ FILE_NAME_LEN ];
	stat_t					moStatus;
	uint8					mbooChecked;
};

#endif // _FILEMANAGER_H_

