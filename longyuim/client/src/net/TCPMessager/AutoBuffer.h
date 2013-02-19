/*
FlyNet
Copyright (C) 2005  author:lu_zi

��һ���������������壬�������������������������� GNU GENERAL PUBLIC LICENSE
�������޸ĺ����·�����һ��ʽ�����������֤�ĵڶ��棬���� (��������ѡ��)
���κθ��µİ汾��

������һ�������Ŀ����ϣ�������ã���û���κε���������û���ʺ��ض�Ŀ�Ķ�������
����������ϸ���������� GNU Lesser General Public License��

���κ������뷢�ʼ���:lu_zi@msn.com
*/
/**
 * @file AutoBuffer.h
 * @brief �Զ����������
 * @author lu_zi
 * @versino 1.0
 * @date 2004.11.26
 */
#ifndef __AUTO_BUFFER__
#define __AUTO_BUFFER__

//#include "FlyNetPublic.h"

#include <list>
#include <cassert>
using namespace std;

//#include <boost/thread.hpp>
//
//using namespace boost;

#include "BigMemoryAllocator.h"

/**
* @brief �Զ�����������ڶԿ����ӵĻ�������Զ����������ȻᰴҪ���Զ����䶨��
  ��С�Ļ��������ڸ������ݣ����������ݸ�����ɺ��ٽ���һ������copy�������ݷŵ�
  һ����С����Ч����һ�µĻ������У������ַ�ʽ�����ٻ�����copy�Ĵ���
* @author lu_zi
* @versino 1.0
* @date 2004.11.26
* @version 1.1
* @date 2004.12.10
* ���ӿ����ļ�ͷ������Ĳ���������ӦһЩ��������Ӧ�ã�ʹ�Զ��������һ�����������
* @version 1.2
* @data 2004.12.20
* ���ӶԶ��̵߳�֧��
* @version 1.3
* @data 2005.4.20
* ���ڴ���й���
*/
class CAutoBuffer
{
 public:
  /**@���С*/
  static const int s_blockSize=2048;
  /**@�ڴ������*/
  static CBigMemoryAllocator<CAutoBuffer::s_blockSize> s_allocator;
 protected:
  unsigned int m_length;
  list<unsigned char*> m_buffer;
 public:
  CAutoBuffer():m_length(0),m_pTop(NULL),m_beginPos(0){}
  ~CAutoBuffer(){Clear();}
 public:
  /**@brief ��������*/
  void Append(const unsigned char* pBuffer,int length);
  /**@brief �õ���������������*/
  unsigned char* AllocateFullBuffer(int& length);
  /**@brief �õ�����������*/
  unsigned int GetLength()const {return m_length;}
  /**@�ر�*/
  void Clear();
 public:
  /**@brief ���ڶ�ֱ��д�뻺������Ч�ʿ��ǣ��û����Եõ���ǰ����Ƭ�Ŀ�д��λ�ü���д��
     ���ݵĳ�������ֱ��д�룬д���ͨ��UnlockCurrentPiece���趨��ز���*/
  unsigned char* LockCurrentPieceForWrite(int& length);
  /**@brief ���ڽ�����ǰд�뻺���Ƭ*/
  void UnlockCurrentPieceForWrite(int writedLength);
  /**@brief ���ڶ�ֱ�Ӷ�ȡ��������Ч�ʿ��ǣ��û����Եõ���ǰ����Ƭ�Ķ�ȡλ�ü��ɶ�ȡ
     ���ݵĳ�������ֱ�Ӷ�ȡ����ȡ��ͨ��UnlockCurrentPiece���趨��ز���*/
  const unsigned char* LockCurrentPieceForRead(int& length);
  /**@brief ���ڽ�����ǰ��ȡ�����Ƭ*/
  void UnlockCurrentPieceForRead(int readedLength);
 protected:
  struct Top
  {
    /**@brief ��ǰ�Ļ���ƫ��*/
    unsigned int m_pieceOffset;
    /**@brief ��һ�εĻ���ƫ��*/
    unsigned int m_pieceOffsetOld;
    /**@brief ��ǰ���λ��*/
    list<unsigned char*>::iterator m_beginPiece;
    /**@brief ������ܳ���*/
    int m_length;
  };
  Top* m_pTop;
  /**@brief �������ڵ�һ��Ƭ�ڵ���ʼλ�ã�Ҳ�ǻ���������ʼλ��*/
  int m_beginPos;
  /**@brief �߳�ģʽ*/
  //boost::mutex m_mutex;
  //mutex::scoped_lock m_lock;
 public:
  /**@brief ��ʼ��ͷ��ȡ����*/
  bool BeginTop();
  /**@brief �õ�ͷ������*/
  unsigned int GetTop(unsigned char* p,int length);
  /**@brief ����ȡ���ݣ���������ˢ��*/
  void EndTop();
  /**@brief ����ȡ���ݣ����������ع�*/
  void RestoreTop();
 protected:
  /**
   * @brief ���ƴ�ͷ����ʼ��ָ�����ȵĻ���
   * @param pBuffer ������
   * @param length ����������
   * @param beginPos ��ʼλ��
   * @param iterBegin ��ʼ��Ƭλ��
   * @param endPos ���ƺ������λ��
   * @param iterEnd ���ƺ������Ƭλ��
   * @return ʵ�ʸ��Ƶĳ���
   */
  int GetTopBuffer(unsigned char* pBuffer,unsigned int length,unsigned int beginPos,list<unsigned char*>::iterator iterBegin,unsigned int* endPos=NULL,list<unsigned char*>::iterator* iterEnd=NULL);
  void ClearBuffer();
  
};



#endif//__AUTO_BUFFER__
