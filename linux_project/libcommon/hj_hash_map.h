/*! @file hj_hash_map.h
* *****************************************************************************
* @n</PRE>
* @nģ����       ��hash�������ؿ⺯������
* @n�ļ���       ��hj_hash_map.h
* @n����ļ�     ��hj_hash_map.cpp
* @n�ļ�ʵ�ֹ��� ��hash�������ؿ⺯������
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
#ifndef __HJ_HASH_MAP_H__
#define __HJ_HASH_MAP_H__

class CHJ_HashMap
{
public:
    CHJ_HashMap();
    virtual ~CHJ_HashMap() {Destroy();}
    int Init(size_t MaxKey);
    void Destroy(void);

    void* Insert(size_t Key, void *pItem);
    void* Replace(size_t Key, void *pItem);
    void* Remove(size_t Key, void *pItem);
    void* Search(size_t Key, void *pItem);

    void SetHashTable(int *pHashTable, const int &nMaxHashDepth);
    typedef int (*COMPARE)(void *, void *);
    void SetCompare(COMPARE compare);

private:
    int GetNeededDepth(size_t MaxKey);
    void UpdateRowLength();

    static int m_Hash_Default_Prime_Table[];
    static int m_Hash_Default_Prime_Table_Depth;
    static int m_DefaultCompare(void *pItemDest, void *pItemSrc);

    void **m_ppHashMap;
    int *m_pHashTable;       // prime table
    int  m_nMaxHashDepth;    // Hash��������Depth
    int  m_nHashDepth;       // ʵ������Hash���Depth
    int  m_nHashRowLength;
    int (*m_fCompare)(void *pItemDest, void *pItemSrc);
};

#endif
