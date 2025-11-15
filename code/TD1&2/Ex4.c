//
// Created by 金卓远 on 25-2-23.
//

#include "Ex4.h"
#include "../PrintFree.h"

// **测试代码**
int main() {

    // int n = 3;
    int n = 4;
    MatAdj ma;
    ma.nbSom = n;
    ma.mat = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        ma.mat[i] = (int *)malloc(n * sizeof(int));
    }

    // 初始化矩阵（有向图带自环）
    // int adj[3][3] = {
    //     {1, 0, 1},
    //     {1, 0, 1},
    //     {1, 1, 0}
    // };


    // 初始化矩阵（有向图不带自环）
    // int adj[3][3] = {
    //     {0, 0, 1},
    //     {1, 0, 1},
    //     {1, 1, 0}
    // };


    // 初始化矩阵（有向图不带自环）
    int adj[4][4] = {
        {0, 1, 1, 0},
        {1, 0, 1, 1},
        {1, 1, 0, 1},
        {0, 1, 1, 0}
    };

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ma.mat[i][j] = adj[i][j];
        }
    }


    /// Ex4.1 Mat_ListeAdj 转换为邻接列表
    ListeAdj la = Mat_Liste(ma);
    printListeAdj(la);

    printf("-----------------------------------------------\n");

    ///Ex4.2 Mat_FS 转换为FileSucc
    FileSucc fs=Mat_FS(ma);
    printFileSucce(fs);

    printf("-----------------------------------------------\n");

    //Ex4.3 Mat_LASP 转换为前序后继链表
    ListeAdjSuccPred lasp=Mat_LASP(ma);
    printLASP(lasp);

    printf("-----------------------------------------------\n");

    //Ex4.4 FS_Liste 后继队列转链表
    ListeAdj la2=FS_Liste(fs);
    printListeAdj(la2);

    printf("-----------------------------------------------\n");

    //Ex4.5 链表转队列
    FileSucc fs2=Liste_FS(la);
    printFileSucce(fs2);

    printf("-----------------------------------------------\n");

    //Ex4.6 邻接矩阵转关联矩阵（有向图）
    printMatAdj(ma);
    MatInc inc=Ajd_Inc(ma);
    printMatInc(inc);

    printf("-----------------------------------------------\n");

    //Ex4.7 关联矩阵转邻接矩阵（有向图）
    printMatInc(inc);
    MatAdj ma2=Inc_Adj(inc);
    printMatAdj(ma2);

    printf("-----------------------------------------------\n");

    //Ex4.8 测试Inc转Adj（无向图）
    printMatInc(inc);
    MatAdj ma3=Inc_Adj_NonOriente(inc);
    printMatAdj(ma3);


    // 释放la内存
    freeListeAdj(la);

    //释放fs内存
    free(fs.APS);
    free(fs.FS);

    //释放Mat内存
    freeMatAdj(ma);
    return 0;
}