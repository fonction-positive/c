//
// Created by 金卓远 on 25-3-5.
//

#include "incidence.h"

#include <stdio.h>

#include "Ex4.h"
#include "../PrintFree.h"

void printIncLL(MatIncidLigLig incll) {
    printf("APS:\n");
    for (int i=0;i<incll.nbSom+1;i++) {
        printf("%d ",incll.APS[i]);
    }
    printf("\n");
    printf("FS:\n");
    for (int i=0;i<incll.nbArcs;i++) {
        printf("%d ",incll.FS[i]);
    }
    printf("\n");
    printf("AS:\n");
    for (int i=0;i<incll.nbArcs;i++) {
        printf("%d ",incll.AS[i]);
    }
    printf("\n");
}


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


    MatInc inc=Ajd_Inc(ma);

    printMatInc(inc);

    MatIncidLigLig incll=MatInc_MatIncidLigLig(inc);

    printIncLL(incll);

    printf("---------------");

    MatInc inc2=MatIncidLigLig_MatInc(incll);

    printMatInc(inc2);
}