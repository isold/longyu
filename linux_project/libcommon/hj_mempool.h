/*! @file hj_mempool.h
* *****************************************************************************
* @n</PRE>
* @nģ����       ���ڴ�ز�����ؿ⺯������
* @n�ļ���       ��hj_mempool.h
* @n����ļ�     ��hj_mempool.cpp
* @n�ļ�ʵ�ֹ��� ���ڴ�ز�����ؿ⺯������
* @n����         ��huangjun - ���˼������й���
* @n�汾         ��1.0.1
* @n-----------------------------------------------------------------------------
* @n��ע��
* @n-----------------------------------------------------------------------------
* @n�޸ļ�¼��
* @n����        �汾        �޸���      �޸�����
* @n20080731    1.0.1       Huangjun    Created
* @n</PRE>
* @n****************************************************************************/
#ifndef __HJ_MEMPOOL_H__
#define __HJ_MEMPOOL_H__

class CHJMemPool
{
public:
    explicit CHJMemPool(void);
    virtual ~CHJMemPool() {Destroy();}

    int Init(size_t BlockSize, size_t BlockCount);
    void Destroy(void);

    void* Alloc(void);
    void Free(void *pItem);

    size_t GetBlockSize(void) const;

private:
    typedef unsigned char byte;
    typedef struct block
    {
        struct block *pNext;
    } block;

    byte  *m_pBaseAddr;
    size_t m_BlockSize;
    size_t m_BlockCount;

    block *m_pFreeBlockList;
};

#endif
