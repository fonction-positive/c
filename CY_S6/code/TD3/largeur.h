//
// Created by 金卓远 on 25-3-1.
//

#ifndef LARGEUR_H
#define LARGEUR_H

#include "file.h"
#include "../structGraphe.h"
#include"profondeur.h"

// MA
void itParcoursLargeur_MA(int s, int *visite, MatAdj g, int n, int *nbSomVisite) {
    File *F = initFile(n);  // 初始化队列，大小为n
    enfiler(s, F);  // 将起始节点加入队列
    int arret = 0;  // 终止条件
    while (!estVideFile(F) && !arret) {
        int u = sommetFile(F);  // 获取队列头部元素
        defiler(F);  // 从队列中移除头部元素

        if (!visite[u]) {  // 如果当前节点未被访问
            visite[u] = 1;  // 标记为已访问
            printf("%d->",u+1);  //打印
            (*nbSomVisite)++;  // 已访问的节点数量加1

            if (n == *nbSomVisite) {  // 如果已访问节点数等于n，则终止
                arret = 1;
            } else {
                // 遍历当前节点u的邻接节点
                for (int t = 0; t < n; t++) {
                    if (g.mat[u][t] == 1 && !visite[t]) {  // 如果存在边u->t且t未访问
                        enfiler(t, F);  // 将t加入队列
                    }
                }
            }
        }
    }

    // 释放队列内存
    free(F->elements);
    free(F);
}


//LA
// 迭代广度优先遍历 (邻接表)
void itParcoursLargeur_LA(int s, int *visite, ListeAdj g, int n, int *nbSomVisite) {
    File *F = initFile(n);  // 初始化队列
    enfiler(s, F);  // 将起始节点加入队列
    int arret = 0;  // 终止条件

    while (!estVideFile(F) && !arret) {
        int u = sommetFile(F);  // 获取队列头部元素
        defiler(F);  // 出队

        if (!visite[u]) {  // 如果当前节点未被访问
            visite[u] = 1;  // 标记为已访问
            printf("%d->", u + 1);  // 输出当前访问的节点
            (*nbSomVisite)++;  // 访问计数增加

            if (n == *nbSomVisite) {  // 如果已访问节点数等于n，则终止
                arret = 1;
            } else {
                // 遍历当前顶点的邻接链表
                Liste voisin = g.tabAdj[u];
                while (voisin) {
                    if (!visite[voisin->somSucc-1]) {  // 如果邻接点未访问
                        enfiler(voisin->somSucc-1, F);  // 入队
                    }
                    voisin = voisin->suiv;
                }
            }
        }
    }

    // 释放队列内存
    free(F->elements);
    free(F);
}



//FS
void itParcoursLargeur_FS(int s, int *visite, FileSucc g, int n, int *nbSomVisite) {
    File *F = initFile(n);  // 初始化队列
    enfiler(s, F);  // 将起始节点加入队列
    int arret = 0;  // 终止条件

    while (!estVideFile(F) && !arret) {
        int u = sommetFile(F);  // 获取队列头部元素
        defiler(F);  // 出队

        if (!visite[u]) {  // 如果当前节点未被访问
            visite[u] = 1;  // 标记为已访问
            printf("%d->", u + 1);  // 输出当前访问的节点
            (*nbSomVisite)++;  // 访问计数增加

            if (n == *nbSomVisite) {  // 如果已访问节点数等于n，则终止
                arret = 1;
            } else {
                // 遍历当前顶点 u 的后继
                int debut = g.APS[u] - 1;
                int fin = g.APS[u + 1] - 1;
                for (int i = debut; i < fin; i++) {
                    int succ = g.FS[i];
                    if (!visite[succ-1]) {  // 如果后继未访问
                        enfiler(succ-1, F);  // 入队
                    }
                }
            }
        }
    }

    // 释放队列内存
    free(F->elements);
    free(F);
}


//主函数
void parcoursLargeur(int sd,FileSucc g) {
    //Initialisation
    int n=g.nbSom;
    int *visite = (int *) malloc(n * sizeof(int)); //访问数组，记录节点是否已经访问
    for (int s = 0; s < n; s++) {
        visite[s] = 0;
    }
    int s = sd-1; //临时节点，节点编号从1开始
    int nbSomVisite = 0; //计数已访问的节点数
    int finParcours = 0;

    //traitement
    while (!finParcours) {
        //MA
        // itParcoursLargeur_MA(s,visite,g,n,&nbSomVisite);
        //LA
        // itParcoursLargeur_LA(s,visite,g,n,&nbSomVisite);
        //FS
        itParcoursLargeur_FS(s,visite,g,n,&nbSomVisite);


        if (nbSomVisite<n) {
            s=somSuivant(s,n,visite);
        }else {
            finParcours=1;
        }
    }
    free(visite);
}


#endif //LARGEUR_H
