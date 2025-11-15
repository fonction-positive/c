//
// Created by 金卓远 on 25-3-1.
//

#ifndef EX4_H
#define EX4_H

///Marquage
///partition（S1，S2）
///estLiaison 是否连通
///estBiparti


#include"../structGraphe.h"
#include <stdlib.h>
#include "../TD3/file.h"
#include "../TD3/largeur.h"
#define MAX_SOM 100

typedef struct cel {
    int elt;
    struct cel *suiv;
} *Ensemble;


Ensemble initE() {
    Ensemble e;
    e = NULL;   // 初始化为空链表
    return e;
}

// 在链表头部插入新节点
Ensemble inserTeteE(int s, Ensemble e) {
    Ensemble newCell = malloc(sizeof(struct cel));
    if (!newCell) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    newCell->elt = s;
    newCell->suiv = e;  // 让新节点指向原来的头节点
    e=newCell;      // 返回新的头节点
    return e;
}

int *initTab(int n, int *tab) {
    int i = 0;
    for (i = 0; i < n; i++) {
        tab[i] = 0;
    }
    return tab;
}



//etape1
//广度优先遍历，记录每个点的层级
int *Marquage(MatAdj g) {
    int n = g.nbSom;
    int *visite = malloc(n * sizeof(int));
    int *marquage = malloc(n * sizeof(int));
    visite = initTab(n, visite);
    marquage = initTab(n, marquage);

    int s = 0;
    int nbSV = 0;
    File *f = initFile(MAX_SOM);
    enfiler(s, f);
    marquage[s] = 0;

    while (!estVideFile(f) && nbSV < n) {
        s = sommetFile(f);
        defiler(f);
        if (visite[s] == 0) {
            visite[s] = 1;
            nbSV++;
            for (int t = 0; t < n; t++) {
                if (g.mat[s][t] == 1 && visite[t] == 0) {
                    enfiler(t, f);
                    marquage[t] = marquage[s] + 1;
                }
            }
        }
    }
    free(visite);
    return marquage;
}

//etape2 将图分为S1,S2两个集合
void partition(int n, int *marquage,Ensemble *s1,Ensemble *s2) {
    // s1=initE();
    // s2=initE();
    for (int s=n-1;s>=0;s--) {
        if (marquage[s]%2==0) {
            *s1=inserTeteE(s,*s1);
        }else {
            *s2=inserTeteE(s,*s2);
        }
    }
}

//etape3 判断S1和S2是否是连通的
int estLiaison(Ensemble S, MatAdj g) {
    int flag = 0;  // 初始化 flag，表示是否找到连接的边
    Ensemble temp1 = S;

    // 遍历集合 S 中的每一对节点
    while (temp1 != NULL && flag == 0) {  // 如果 flag 为 1，则不再继续检查
        int s = temp1->elt;
        Ensemble temp2 = temp1->suiv;

        while (temp2 != NULL) {
            int t = temp2->elt;
            // 检查节点 s 和 t 是否有边连接
            if (g.mat[s][t] == 1 || g.mat[t][s] == 1) {
                flag = 1;  // 如果有连接边，将 flag 设置为 1
                break;  // 立即退出内层循环
            }
            temp2 = temp2->suiv;
        }
        temp1 = temp1->suiv;
    }

    return flag;  // 返回 flag，1 表示有连接边，0 表示没有
}

//主函数
int estBiparti(MatAdj g) {
    int n=g.nbSom;
    int *marquage=Marquage(g);
    Ensemble s1,s2;
    s1=initE();
    s2=initE();
    partition(n,marquage,&s1,&s2);

    int biparti=!estLiaison(s1,g) && !estLiaison(s2,g);

    free(s1);
    free(s2);
    free(marquage);

    return biparti;
}

#endif //EX4_H
