//
// Created by 金卓远 on 25-3-1.
//

#include "profondeur.h"
#include "../PrintFree.h"
#include"../structGraphe.h"
#include"../TD1&2/Ex4.h"

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
    printf("DFS:\n");

    //测试MA
    // parcoursProfondeur(1,ma);

    //测试LA
    // ListeAdj la=Mat_Liste(ma);
    // printListeAdj(la);
    // parcoursProfondeur(1,la);

    //测试FS
    FileSucc fs=Mat_FS(ma);
    printFileSucce(fs);
    parcoursProfondeur(1,fs);


    freeMatAdj(ma);
}