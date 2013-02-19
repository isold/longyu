/*
FlyNet
Copyright (C) 2005  author:lu_zi

��һ���������������壬�������������������������� GNU GENERAL PUBLIC LICENSE
�������޸ĺ����·�����һ��ʽ�����������֤�ĵڶ��棬���� (��������ѡ��)
���κθ��µİ汾��

������һ�������Ŀ����ϣ�������ã���û���κε���������û���ʺ��ض�Ŀ�Ķ�������
����������ϸ���������� GNU General Public License��

���κ������뷢�ʼ���:lu_zi@msn.com
*/
#ifndef __BIG_MEMORY__
#define __BIG_MEMORY__

#include <list>

using namespace std;

//#include <boost/thread.hpp>

//using namespace boost;

template<int size>
class CBigMemoryAllocator
{
public:
	CBigMemoryAllocator(){}
  ~CBigMemoryAllocator()
    {
      for(list<unsigned char*>::iterator iter=m_buffer.begin();iter!=m_buffer.end();iter++)
	{
	  if(*iter)
            {
	      delete (*iter);
            }
        }
    }
 protected:
  list<unsigned char*> m_buffer;
  //mutex m_mutex;
 public:
  unsigned char* GetBuffer()
    {
     // mutex::scoped_lock lock(m_mutex);
      if(m_buffer.size())
        {
	  unsigned char* p=*m_buffer.begin();
	  m_buffer.pop_front();
	  return p;
        }
      return new unsigned char[size];
    }
  void ReturnBuffer(unsigned char* p)
  {
    m_buffer.push_back(p);
  }
};
 
#endif//__BIG_MEMORY__
