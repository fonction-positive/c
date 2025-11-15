//
// Created by 金卓远 on 24-12-15.
//

#ifndef BTREE_H
#define BTREE_H

// 定义m序(阶)B树的最小度数 BTree_D = ceil(m)
#define BTree_D        2
#define ORDER          (BTree_D * 2)  // 定义为4阶B-tree, 2-3-4树。最简单为3阶B-tree, 2-3树
#include <stdbool.h>

typedef int KeyType;  // 定义关键字类型

// BTree节点结构体
typedef struct BTNode {
    int keynum;                        // 结点中关键字的个数，keynum <= BTree_N
    KeyType key[ORDER - 1];             // 关键字向量 key[0..keynum - 1]
    struct BTNode* child[ORDER];       // 孩子指针向量 child[0..keynum]
    bool isLeaf;                       // 是否是叶子节点的标志
} BTNode;

typedef BTNode* BTree;  // 定义BTree类型

// 创建BTree
void BTree_create(BTree* tree, const KeyType* data, int length);

// 销毁BTree，释放内存空间
void BTree_destroy(BTree* tree);

// 在BTree中插入关键字key
void BTree_insert(BTree* tree, KeyType key);

// 在BTree中移除关键字key
void BTree_remove(BTree* tree, KeyType key);

// 深度遍历BTree并打印各层节点信息
void BTree_print(const BTree tree, int layer = 1);

// 在BTree中查找关键字 key
// 成功时返回找到的节点的地址及 key 在其中的位置 *pos
// 失败时返回 NULL 及查找失败时扫描到的节点位置 *pos
BTNode* BTree_search(const BTree tree, int key, int* pos);

#endif //BTREE_H
