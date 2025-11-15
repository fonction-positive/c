//
// Created by 金卓远 on 25-3-2.
//
#include"../PrintFree.h"
#include "Connexes.h"
// int main() {
//     int n = 5;
//     MatAdj ma;
//     ma.nbSom = n;
//     ma.mat = (int **)malloc(n * sizeof(int *));
//     for (int i = 0; i < n; i++) {
//         ma.mat[i] = (int *)malloc(n * sizeof(int));
//     }
//
//     // 初始化矩阵（无向图不带自环）
//     int adj[5][5] = {
//                 {0, 1, 0, 0, 0},
//                 {1, 0, 1, 0, 0},
//                 {0, 1, 0, 0, 0},
//                 {0, 0, 0, 0, 1},
//                 {0, 0, 0, 1, 0}
//     };
//
//     for (int i = 0; i < n; i++) {
//         for (int j = 0; j < n; j++) {
//             ma.mat[i][j] = adj[i][j];
//         }
//     }
//
//     printMatAdj(ma);
//     printf("Composant connexe:\n");
//     trouverComposantesConnexes(ma);
// }

// 输出结果的测试函数
void printResults(int *CFC, int nbSom, int nbCFC) {
    // 先输出CFC数组
    printf("CFC= [");
    for (int i = 0; i < nbSom; i++) {
        printf("%d", CFC[i]);
        if (i < nbSom - 1) {
            printf(", ");
        }
    }
    printf("]\n");

    // 按CFC编号分组输出每个强连通分量包含的顶点
    for (int i = 1; i <= nbCFC; i++) {
        printf("CFC%d = {", i);
        int first = 1;
        for (int j = 0; j < nbSom; j++) {
            if (CFC[j] == i) {
                if (!first) {
                    printf(", ");
                }
                printf("%d", j + 1);
                first = 0;
            }
        }
        printf("}\n");
    }

    // 输出强连通分量的数量
    printf("nbCFC = %d\n", nbCFC);
}

int main() {
    // 示例图的初始化
    int n = 8;
    MatAdj ma;
    ma.nbSom = n;
    ma.mat = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        ma.mat[i] = (int *)malloc(n * sizeof(int));
    }
    
    int adj[8][8] = {
        {0, 0, 0, 0, 0, 1, 1, 1},  // 顶点 1 的出边 (1 → 6, 1 → 7, 1 → 8)
        {1, 0, 0, 1, 0, 0, 0, 0},  // 顶点 2 的出边 (2 → 1, 2 → 4)
        {0, 1, 0, 0, 0, 0, 0, 0},  // 顶点 3 的出边 (3 → 2)
        {0, 0, 1, 0, 1, 0, 0, 0},  // 顶点 4 的出边 (4 → 3, 4 → 5)
        {1, 0, 0, 0, 0, 0, 0, 0},  // 顶点 5 的出边 (5->1)
        {0, 0, 0, 0, 1, 0, 1, 0},  // 顶点 6 的出边 (6 → 5, 6 → 7)
        {0, 0, 0, 0, 0, 0, 0, 0},  // 顶点 7 没有出边
        {0, 0, 0, 0, 0, 1, 1, 0}   // 顶点 8 的出边 (8 → 6, 8 → 7)
    };

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ma.mat[i][j] = adj[i][j];
        }
    }

    int *CFC = (int *)malloc(ma.nbSom * sizeof(int));
    int nbCFC;

    ComposanteFortementConnexe(ma, CFC, &nbCFC);

    // for (int i=0;i<8;i++) {
    //     printf("%d ",CFC[i]);
    // }
    printResults(CFC, ma.nbSom, nbCFC);


    // 释放内存
    for (int i = 0; i < ma.nbSom; i++) {
        free(ma.mat[i]);
    }
    free(ma.mat);
    free(CFC);

    return 0;
}