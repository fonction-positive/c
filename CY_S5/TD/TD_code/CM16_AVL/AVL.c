#include <stdlib.h>
#include <__stddef_null.h>
//
// Created by 金卓远 on 24-12-3.
//

#include "AVL.h"
int main() {
    AVL arbre = initAVL();

    // 插入节点测试
    arbre = inserAVL(20, arbre);
    arbre = inserAVL(10, arbre);
    arbre = inserAVL(30, arbre);
    arbre = inserAVL(5, arbre);
    arbre = inserAVL(15, arbre);
    arbre = inserAVL(25, arbre);
    arbre = inserAVL(35, arbre);

    // printf("\nAVL Tree after insertions:\n");
    // printAVL(arbre, 0);

    // 遍历测试
    // printf("\nPreorder Traversal: ");
    // parcoursPre(arbre);
    // printf("\nInorder Traversal: ");
    // parcoursIn(arbre);
    // printf("\nPostorder Traversal: ");
    // parcoursPost(arbre);
    // printf("\n");

    // 删除节点测试
    // printf("\nDeleting element 10\n");
    parcoursIn(arbre);
    printf("\n");
    arbre=suppEltAVL(10,arbre);
    parcoursIn(arbre);
    // printf("\nAVL Tree after deletion:\n");
    // printAVL(arbre, 0);

    // printf("\nDeleting element 30\n");
    // arbre = suppEltAVL(30, arbre);
    // printf("\nAVL Tree after deletion:\n");
    // printAVL(arbre, 0);


    // suppMaxAVL(&arbre);
    // printAVL(arbre,0);

    // 检查是否仍为 AVL
    if (estAVL(arbre)) {
        printf("\nThe tree is a valid AVL tree.\n");
    } else {
        printf("\nThe tree is not a valid AVL tree.\n");
    }

    return 0;
}

