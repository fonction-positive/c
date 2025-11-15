//
// Created by 金卓远 on 25-3-1.
//

#include "Carre.h"
#include "../PrintFree.h"

int main() {
    int n = 4;
    MatAdj ma;
    ma.nbSom = n;
    ma.mat = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        ma.mat[i] = (int *)malloc(n * sizeof(int));
    }

    // 初始化矩阵（有向图不带自环）
    int adj[4][4] = {
        {0, 1, 1, 0},
        {0, 0, 0, 1},
        {0, 0, 0, 1},
        {1, 0, 0, 0}
    };

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ma.mat[i][j] = adj[i][j];
        }
    }

    printMatAdj(ma);
    MatAdj g2=carre_MA(ma);
    printMatAdj(g2);

    ListeAdj la=Mat_Liste(ma);
    printListeAdj(la);
    ListeAdj g3=carre_LA(la);
    printListeAdj(g3);

    FileSucc fs=Mat_FS(ma);
    printFileSucce(fs);
    FileSucc fs2=carre_FS(fs);
    printFileSucce(fs2);

}
