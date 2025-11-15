//
// Created by 金卓远 on 25-3-6.
//

#include "Circuit.h"
#include "../TD1&2/Ex4.h"
#include <stdio.h>

int main() {
    int n = 3;
    MatAdj ma;
    ma.nbSom = n;
    ma.mat = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        ma.mat[i] = (int *)malloc(n * sizeof(int));
    }

    //a cycle
    // int adj[3][3] = {
    //     {0, 0, 1},
    //     {1, 0, 1},
    //     {1, 1, 0}
    // };

    //sans cycle
    int adj[3][3] = {
        {0, 0, 1},
        {1, 0, 1},
        {0, 0, 0}
    };

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ma.mat[i][j] = adj[i][j];
        }
    }

    if (hasCycle_MatAdj(ma)) {
        printf("il y a cycle!\n");
    }else {
        printf("Sans cycle!\n");
    }

    ListeAdj la=Mat_Liste(ma);

    printf("%d \n",hasCycle_ListeAdj(la));

    FileSucc fs=Mat_FS(ma);

    printf("%d \n",hasCycle_FileSucc(fs));
}
