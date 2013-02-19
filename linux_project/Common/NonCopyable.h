#ifndef NONCOPYABLE_H
#define NONCOPYABLE_H	(1)
/*
  *file NonCopyable.h
  *brief ����Ǵ�boost��copy���Ĵ���,����ʵ�ַ�ֹ���������
  *      ԭ��ܼ򵥾���˽�л��˹��캯���Ϳ������캯��,������
  *      �޷�����������
  *author peiwenhao
  *version 0.1
  *date 2010.11.26
  */
/*******************************************************************************
 * include
 *******************************************************************************/
/*******************************************************************************
 * class/struct
 *******************************************************************************/
class CNonCopyable
{
protected:
	CNonCopyable() {}
	~CNonCopyable() {}
private:  
	CNonCopyable(const CNonCopyable&);
	const CNonCopyable& operator=(const CNonCopyable&);
};

#endif