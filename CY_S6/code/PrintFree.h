//
// Created by 金卓远 on 25-3-1.
//

#ifndef PRINTFREE_H
#define PRINTFREE_H
#include "stdio.h"
#include "structGraphe.h"
#include "stdlib.h"

// 打印邻接列表
void printListeAdj(ListeAdj l) {
    for (int i = 0; i < l.nbSom; i++) {
        printf("Sommet %d : ", i+1);
        Liste temp = l.tabAdj[i];
        while (temp!=NULL) {
            printf("%d -> ", temp->somSucc);
            temp = temp->suiv;
        }
        printf("NULL\n");
    }
}

// 释放邻接列表
void freeListeAdj(ListeAdj l) {
    for (int i = 0; i < l.nbSom; i++) {
        Liste temp = l.tabAdj[i];
        while (temp) {
            Liste toDelete = temp;
            temp = temp->suiv;
            free(toDelete);
        }
    }
    free(l.tabAdj);
}

// 释放邻接矩阵
void freeMatAdj(MatAdj m) {
    for (int i = 0; i < m.nbSom; i++) {
        free(m.mat[i]);
    }
    free(m.mat);
}


// 打印 FileSucce
void printFileSucce(FileSucc fs) {
    printf("nbSom: %d\n", fs.nbSom);
    printf("nbArcs: %d\n", fs.nbArcs);
    printf("APS: ");
    for (int i = 0; i <= fs.nbSom; i++) {
        printf("%d ", fs.APS[i]);
    }
    printf("\nFS: ");
    for (int i = 0; i < fs.nbArcs; i++) {
        printf("%d ", fs.FS[i]);
    }
    printf("\n");
}

//打印LASP
void printLASP(ListeAdjSuccPred lasp) {
    printf("Nombre de sommets: %d\n", lasp.nbSom);

    for (int i = 0; i < lasp.nbSom; i++) {
        printf("Sommet %d:\n", i + 1);

        // 打印后继（Succ）
        printf("  Successeurs: ");
        Liste temp = lasp.tabAdjSP[i].lSucc;
        while (temp != NULL) {
            printf("%d ", temp->somSucc);
            temp = temp->suiv;
        }
        printf("\n");

        // 打印前驱（Pred）
        printf("  Predecesseurs: ");
        temp = lasp.tabAdjSP[i].lPred;
        while (temp != NULL) {
            printf("%d ", temp->somSucc);
            temp = temp->suiv;
        }
        printf("\n");
    }
}

//打印关联矩阵
void printMatInc(MatInc inc) {
    printf("Matrice d'incidence :\n");
    for (int i = 0; i < inc.nbSom; i++) {  // 遍历顶点
        for (int j = 0; j < inc.nbArc; j++) {  // 遍历边
            printf("%d ", inc.mat[i][j]);
        }
        printf("\n");
    }
}

//打印邻接矩阵
void printMatAdj(MatAdj adj) {
    printf("Matrice d'adjacence :\n");
    for (int i = 0; i < adj.nbSom; i++) {  // 遍历所有顶点
        for (int j = 0; j < adj.nbSom; j++) {  // 遍历所有顶点的连接
            printf("%d ", adj.mat[i][j]);
        }
        printf("\n"); // 换行，打印下一行
    }
}
#endif //PRINTFREE_H
