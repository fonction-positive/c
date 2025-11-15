//
// Created by 金卓远 on 25-3-2.
//
#include<stdlib.h>
#include<stdio.h>
#include "FermetureTransitive.h"

#include "../PrintFree.h"
#include "../TD1&2/Ex4.h"

int **allocM(MatAdj g) {
    // 为传递闭包矩阵分配内存

    int **M = (int **) malloc(g.nbSom * sizeof(int *));
    for (int i = 0; i < g.nbSom; i++) {
        M[i] = (int *) malloc(g.nbSom * sizeof(int));
    }

    return M;
}

void printFermeture(int n, int **M) {
    // 输出传递闭包矩阵
    printf("传递闭包矩阵:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", M[i][j]);
        }
        printf("\n");
    }
}


int main() {
    int n = 3;
    MatAdj ma;
    ma.nbSom = n;
    ma.mat = (int **) malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        ma.mat[i] = (int *) malloc(n * sizeof(int));
    }

    // 初始化矩阵（有向图不带自环）
    int adj[3][3] = {
        {0, 1, 0},
        {0, 0, 0},
        {0, 0, 0}
    };

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ma.mat[i][j] = adj[i][j];
        }
    }

    printMatAdj(ma);
    int **M = allocM(ma);

    // 调用计算传递闭包的函数 MA
    // FermetureTransitive_MA(ma, M);
    // printFermeture(n,M);

    //LA
    ListeAdj la=Mat_Liste(ma);
    FermetureTransitive_LA(la,M);
    printFermeture(n,M);

    // 释放邻接矩阵和传递闭包矩阵的内存
    for (int i = 0; i < ma.nbSom; i++) {
        free(ma.mat[i]);
        free(M[i]);
    }
    free(ma.mat);
    free(M);
}
