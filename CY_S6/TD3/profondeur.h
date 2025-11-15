//
// Created by 金卓远 on 25-3-1.
//

#ifndef PROFONDEUR_H
#define PROFONDEUR_H

#include <stdio.h>
#include <stdlib.h>

#include "../structGraphe.h"

int somSuivant(int s, int n, int *visite) {
    for (int i = s + 1; i < n; i++) {
        // 从 s+1 开始找
        if (!visite[i]) {
            // 发现未访问的节点
            return i;
        }
    }
    // 如果没有找到，则从头开始找
    for (int i = 0; i < s; i++) {
        if (!visite[i]) {
            return i;
        }
    }
    return -1;
}

void reParcoursProfondeur_MA(int s, int *visite, MatAdj g, int n, int *nbSomVisite) {
    if (*nbSomVisite < n) {
        visite[s] = 1;
        printf("%d->", s + 1); //节点编号从1开始
        // printf("%d->", s);
        (*nbSomVisite)++;
        for (int t = 0; t < g.nbSom; t++) {
            if (g.mat[s][t] && !visite[t]) {
                //存在边且未访问
                reParcoursProfondeur_MA(t, visite, g, n, nbSomVisite);
            }
        }
    }
}

void itParcoursProfondeur_MA(int s, int *visite, MatAdj g, int n, int *nbSomVisite) {
    int *pile = (int *) malloc(n * sizeof(int)); // 栈
    int sommet = -1; // 栈顶索引
    int arret = 0; // 终止标志

    pile[++sommet] = s; // 入栈

    while (sommet >= 0 && !arret) {
        int u = pile[sommet--]; // 出栈

        if (!visite[u]) {
            printf("%d->", u + 1); // 输出节点编号（从 1 开始）
            visite[u] = 1;
            (*nbSomVisite)++;

            if (*nbSomVisite == n) {
                arret = 1; // 终止遍历
            } else {
                // 从最后一个邻接点到第一个邻接点遍历
                for (int t = g.nbSom - 1; t >= 0; t--) {
                    if (g.mat[u][t] && !visite[t]) {
                        pile[++sommet] = t; // 入栈
                    }
                }
            }
        }
    }
    free(pile);
}


void reParcoursProfondeur_LA(int s, int *visite, ListeAdj g, int n, int *nbSomVisite) {
    if (*nbSomVisite < n) {
        visite[s] = 1;
        printf("%d->", s + 1);  // 输出节点编号（从 1 开始）
        (*nbSomVisite)++;

        Liste courant = g.tabAdj[s];  // 获取顶点s的邻接链表
        while (courant != NULL) {
            if (!visite[courant->somSucc-1]) {  // 如果该节点没有被访问(存在g里的节点是从1开始编号的）
                reParcoursProfondeur_LA(courant->somSucc-1, visite, g, n, nbSomVisite);
            }
            courant = courant->suiv;  // 继续遍历下一个邻接点
        }
    }
}

void itParcoursProfondeur_LA(int s, int *visite, ListeAdj g, int n, int *nbSomVisite) {
    int *pile = (int *)malloc(n * sizeof(int)); // 栈
    int sommet = -1; // 栈顶索引
    int arret = 0; // 终止标志

    pile[++sommet] = s; // 入栈

    while (sommet >= 0 && !arret) {
        int u = pile[sommet--]; // 出栈

        if (!visite[u]) {
            printf("%d->", u + 1); // 输出节点编号（从 1 开始）
            visite[u] = 1;
            (*nbSomVisite)++;

            if (*nbSomVisite == n) {
                arret = 1; // 终止遍历
            } else {
                Liste courant = g.tabAdj[u]; // 获取顶点u的邻接链表
                while (courant != NULL) {
                    if (!visite[courant->somSucc-1]) {
                        pile[++sommet] = courant->somSucc-1; // 入栈
                    }
                    courant = courant->suiv;
                }
            }
        }
    }

    free(pile);
}



void reParcoursProfondeur_FS(int s, int *visite, FileSucc g, int n, int *nbSomVisite) {
    if (*nbSomVisite < n) {
        visite[s] = 1;
        printf("%d->", s+1); // 节点编号从1开始
        (*nbSomVisite)++;

        int start = g.APS[s]-1; // 当前顶点s在FS中的起始索引
        int end = g.APS[s+1]-1; // 当前顶点s在FS中的结束索引（不包括）

        for (int i = start; i < end; i++) {
            int succ = g.FS[i]-1;
            if (!visite[succ]) {
                reParcoursProfondeur_FS(succ, visite, g, n, nbSomVisite);
            }
        }
    }
}


void itParcoursProfondeur_FS(int s, int *visite, FileSucc g, int n, int *nbSomVisite) {
    int *pile = (int *)malloc(n * sizeof(int)); // 栈
    int sommet = -1; // 栈顶索引
    int arret = 0; // 终止标志

    pile[++sommet] = s; // 入栈

    while (sommet >= 0 && !arret) {
        int u = pile[sommet--]; // 出栈

        if (!visite[u]) {
            printf("%d->", u + 1); // 输出节点编号（从 1 开始）
            visite[u] = 1;
            (*nbSomVisite)++;

            if (*nbSomVisite == n) {
                arret = 1; // 终止遍历
            } else {
                int start = g.APS[u]-1; // 当前顶点u在FS中的起始索引
                int end = g.APS[u + 1]-1; // 当前顶点u在FS中的结束索引（不包括）

                for (int i = end - 1; i >= start; i--) {
                    int succ = g.FS[i]-1;
                    if (!visite[succ]) {
                        pile[++sommet] = succ; // 入栈
                    }
                }
            }
        }
    }

    free(pile);
}



//MatAdj,ListeAdj,FS
void parcoursProfondeur(int sd, FileSucc g) {

    //初始化
    int n = g.nbSom;
    int *visite = (int *) malloc(n * sizeof(int)); //访问数组，记录节点是否已经访问
    for (int s = 0; s < n; s++) {
        visite[s] = 0;
    }
    int s = sd-1; //临时节点，节点编号从1开始
    int nbSomVisite = 0; //计数已访问的节点数
    int finParcours = 0;

    while (!finParcours) {
        ///MatAdj
        // reParcoursProfondeur_MA(s, visite, g, n, &nbSomVisite);  //递归写法
        // itParcoursProfondeur_MA(s,visite,g,n,&nbSomVisite);  //迭代写法

        //ListeAdj
        // reParcoursProfondeur_LA(s, visite, g, n, &nbSomVisite);
        // itParcoursProfondeur_LA(s, visite, g, n, &nbSomVisite);

        //FS
        // reParcoursProfondeur_FS(s, visite, g, n, &nbSomVisite);
        itParcoursProfondeur_FS(s, visite, g, n, &nbSomVisite);

        if (nbSomVisite < n) {
            int suiv = somSuivant(s, n, visite);
            if (suiv == -1) {
                finParcours = 1;
            } else {
                s = suiv;
            }
        } else {
            finParcours = 1;
        }
    }
    free(visite);
}

#endif //PROFONDEUR_H
