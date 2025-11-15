//
// Created by 金卓远 on 25-3-1.
//

#include "largeur.h"
#include "file.h"
#include "../PrintFree.h"
#include "../TD1&2/Ex4.h"

int main() {
    int n = 3;
    MatAdj ma;
    ma.nbSom = n;
    ma.mat = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        ma.mat[i] = (int *)malloc(n * sizeof(int));
    }

    // 初始化矩阵（有向图不带自环）
    int adj[3][3] = {
        {0, 0, 1},
        {1, 0, 1},
        {1, 1, 0}
    };

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ma.mat[i][j] = adj[i][j];
        }
    }

    printMatAdj(ma);
    //MA
    // parcoursLargeur(1,ma);
    //LA
    // ListeAdj la=Mat_Liste(ma);
    // parcoursLargeur(1,la);
    //FS
    FileSucc fs=Mat_FS(ma);
    parcoursLargeur(1,fs);

    // 释放la内存
    // freeListeAdj(la);

    //释放fs内存
    free(fs.APS);
    free(fs.FS);

    //释放Mat内存
    freeMatAdj(ma);
    return 0;
}
