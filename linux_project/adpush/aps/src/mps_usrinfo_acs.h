#ifndef __MPS_USRINFO_ACS_H__
#define __MPS_USRINFO_ACS_H__

#include <sys/types.h>

#include "mps_pkg.h"
#include "hj_rbtree.h"

// ����˴洢���û���Ϣ�ṹ��Ϣ
typedef struct _STRU_USERINFO_ACS
{
    // ����RB�������ӣ����ڰ��û�Id����
    struct HJ_RB_node rbNode;

    // �û�Id
    UINT64 u64UsrId;
    // ҵ��Id
    UINT16 u16SvcId;
    // ͨ������
    UINT32 u32CommAttr;
    // ҵ��˽������
    char chPrivateAttr[PRIVATE_ATTR_SIZE];
    // �û�����SocketId
    unsigned short usCommSocket;

    // ָ��ͬIdͬҵ��Id��ͬ����socket���û�������ظ��û���½���Σ�
    struct _STRU_USERINFO_ACS *pNext;
} STRU_USERINFO_ACS;

STRU_USERINFO_ACS* Search_Userinfo(struct HJ_RB_root *pRoot, UINT64 u64UsrId);
STRU_USERINFO_ACS* Search_Userinfo(struct HJ_RB_root *pRoot, UINT64 u64UsrId
    , unsigned short usSocket);
int Insert_Userinfo(struct HJ_RB_root *pRoot, STRU_USERINFO_ACS *pNewUserinfo
    , unsigned short usSocket);
STRU_USERINFO_ACS* Remove_Userinfo(struct HJ_RB_root *pRoot, UINT64 u64UsrId
    , unsigned short usSocket);

#endif
