//
// Created by 金卓远 on 25-3-1.
//

#include "bipartition.h"

int main() {

    int n = 10;
    MatAdj ma;
    ma.nbSom = n;
    ma.mat = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        ma.mat[i] = (int *)malloc(n * sizeof(int));
    }

    int adj[10][10] = {
        {0, 1, 1, 0, 0, 0, 0, 0, 0, 0},  // 1 -> 2, 1 -> 3
        {0, 0, 0, 1, 1, 0, 0, 0, 0, 0},  // 2 -> 4, 2 -> 5
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 1},  // 3 -> 10
        {0, 0, 0, 0, 0, 1, 0, 0, 0, 0},  // 4 -> 6
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  // 5 (无出边)
        {0, 0, 0, 0, 0, 0, 1, 0, 0, 0},  // 6 -> 7
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  // 7 (无出边)
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 0},  // 8 -> 9
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  // 9 (无出边)
        {0, 0, 0, 0, 0, 0, 0, 1, 0, 0}   // 10 -> 8
    };

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ma.mat[i][j] = adj[i][j];
        }
    }

    int *marquage=Marquage(ma);

    for (int i=0;i<10;i++) {
        printf("%d ",marquage[i]);
    }
    printf("\n");

    Ensemble s1,s2;
    s1=initE();
    s2=initE();
    partition(n,marquage,&s1,&s2);

    while (s1!=NULL){
        printf("%d ",s1->elt+1);
        s1=s1->suiv;
    }
    printf("\n");
    while (s2!=NULL){
        printf("%d ",s2->elt+1);
        s2=s2->suiv;
    }
    printf("\n");

    if (estBiparti(ma)) {
        printf("le graphe est biparti\n");
    }else {
        printf("le graphe n'est pas biparti\n");
    }
}

