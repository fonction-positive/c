//
// Created by 金卓远 on 25-3-1.
//

#include "ListePrincipale.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct cellulelp *ListeSucc;
typedef struct listPrincipale *ListePrincipale;

struct cellulelp {
    ListePrincipale succ;  // 邻接点
    ListeSucc suivLS;      // 下一个邻接点
};

struct listPrincipale {
    int numSom;            // 当前节点编号
    ListePrincipale suivLP; // 下一个主节点（链表）
    ListeSucc lSucc;       // 当前节点的邻接链表
};

// 将邻接矩阵转换为邻接链表
void MAtoLP(int **MA, ListePrincipale *LP, int n) {
    for (int i = 0; i < n; i++) {
        LP[i] = (ListePrincipale)malloc(sizeof(struct listPrincipale));
        LP[i]->numSom = i;
        LP[i]->suivLP = NULL;
        LP[i]->lSucc = NULL;

        ListeSucc lastSucc = NULL;

        for (int j = 0; j < n; j++) {
            if (MA[i][j] != 0) {  // 如果有边（非零值）
                ListeSucc newSucc = (ListeSucc)malloc(sizeof(struct cellulelp));
                newSucc->succ = LP[j];  // 将邻接点设置为对应的节点
                newSucc->suivLS = NULL;

                // 连接链表
                if (lastSucc == NULL) {
                    LP[i]->lSucc = newSucc;  // 如果链表为空，将其作为头节点
                } else {
                    lastSucc->suivLS = newSucc;  // 否则将新节点连接到链表的尾部
                }
                lastSucc = newSucc;  // 更新尾指针
            }
        }
    }
}

// 打印邻接链表
void printLP(ListePrincipale *LP, int n) {
    for (int i = 0; i < n; i++) {
        printf("Node %d: ", i + 1); // 打印当前节点编号
        ListeSucc current = LP[i]->lSucc;
        if (current == NULL) {
            printf("No adjacent nodes.\n");  // 如果没有邻接节点，输出提示
        } else {
            while (current != NULL) {
                printf("%d -> ", current->succ->numSom + 1);  // 输出邻接节点编号
                current = current->suivLS;
            }
            printf("NULL\n");
        }
    }
}

// 测试代码
int main() {
    int n = 4;  // 节点数

    // 初始化邻接矩阵
    int **MA = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        MA[i] = (int *)malloc(n * sizeof(int));
    }

    // 填充邻接矩阵
    int mat[4][4] = {
        {0, 1, 1, 0},
        {1, 0, 1, 0},
        {1, 1, 0, 1},
        {0, 0, 1, 0}
    };

    // 将邻接矩阵赋值给MA
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            MA[i][j] = mat[i][j];
        }
    }

    // 创建邻接链表
    ListePrincipale LP[n];
    MAtoLP(MA, LP, n);

    // 打印邻接链表
    printf("Adjacency List (LP):\n");
    printLP(LP, n);

    // 释放内存
    for (int i = 0; i < n; i++) {
        free(LP[i]);
    }

    for (int i = 0; i < n; i++) {
        free(MA[i]);
    }
    free(MA);

    return 0;
}