//
// Created by 金卓远 on 25-2-23.
//
#ifndef EX4_H
#define EX4_H

#include <stdio.h>
#include <stdlib.h>

#include "../structGraphe.h"

///Mat_Liste
///Mat_FS
///Mat_LASP
///FS_Liste
///Liste_FS
///Adj_Inc(oriente/NonOriente)
///Inc_Adj(oriente/Non）

/// 4.1 Mat_Liste
//创建ListeAdj
ListeAdj allocListeAdj(int n) {
    ListeAdj la;
    la.nbSom = n; //赋值顶点数量
    la.tabAdj = (Liste *) malloc(n * sizeof(Liste));
    //检查内存是否分配成功
    if (la.tabAdj == NULL) {
        printf("problem de memoire!");
        exit(1);
    }
    //初始化所有链表
    for (int i = 0; i < n; i++) {
        la.tabAdj[i] = NULL;
    }
    return la;
}

// 在链表头部插入新节点
Liste inserTete(Liste l, int s) {
    Liste cel = malloc(sizeof(struct cellule));
    cel->somSucc = s; // 设置后继顶点编号
    cel->suiv = l; // 新节点指向原链表头
    l = cel; // 更新链表头
    return l;
}

//转换函数
ListeAdj Mat_Liste(MatAdj ma) {
    int n = ma.nbSom;
    ListeAdj la = allocListeAdj(n);
    Liste l;

    for (int i = 0; i < n; i++) {
        l = NULL; //初始化后继链表
        for (int j = n - 1; j >= 0; j--) {
            //从右往左遍历矩阵，保证后继节点顺序
            if (ma.mat[i][j] == 1) {
                //如果有i->j的边则插入到链表中
                l = inserTete(l, j + 1);
                la.tabAdj[i] = l;
            }
        }
    }
    return la;
}


/// 4.2 Mat_FS
//创建FileSucc
FileSucc allocFS(int n, int p) {
    FileSucc fs;
    fs.nbSom = n;
    fs.nbArcs = p;

    //分配内存
    fs.APS = malloc((n + 1) * sizeof(int));
    if (fs.APS == NULL) {
        printf("Problem de memoire!");
        exit(1);
    }

    fs.FS = malloc(p * sizeof(int));
    if (fs.FS == NULL) {
        printf("Problem de memoire!");
        exit(1);
    }

    return fs;
}


/*
fct Mat_FS(ma) -> FileSucc
    P.F ma:Graphe=MatAdj(E)
Debut
    n <- nbSom(ma)
    p <- nbArcs(ma)
    fs <- allocFS(n,p)
    iaps <- 1
    pour s variant de 1 à n faire
        fs.APS[s] <- iaps
        pour t variant de 1 à n faire
            si ma.Mat[s][t] = 1 alors
                fs.FS[iaps] = t
                iaps <- iaps+1
            finsi
        finpour
    finpour
Fin
 */

FileSucc Mat_FS(MatAdj ma) {
    //计算n和p（顶点和弧的数量）
    int n = ma.nbSom; //顶点
    int p = 0; //弧
    //仅考虑有向图，计算弧的数量
    for (int s = 0; s < n; s++) {
        for (int t = 0; t < n; t++) {
            if (ma.mat[s][t] == 1) {
                p++;
            }
        }
    }

    FileSucc fs = allocFS(n, p);
    int iaps = 0;
    for (int s = 0; s < n; s++) {
        fs.APS[s] = iaps + 1;
        for (int t = 0; t < n; t++) {
            if (ma.mat[s][t] == 1) {
                fs.FS[iaps] = t + 1;
                iaps++;
            }
        }
    }
    fs.APS[n] = iaps + 1;
    return fs;
}


/// 4.3 Mat_LASP
ListeAdjSuccPred allocLASP(int n) {
    ListeAdjSuccPred lasp;
    lasp.nbSom = n;

    //分配内存
    lasp.tabAdjSP = malloc(n * sizeof(ListeSuccPred));
    if (lasp.tabAdjSP == NULL) {
        printf("Problem de memoire!");
        exit(1);
    }

    //初始化所有前驱和后继链表
    for (int i = 0; i < n; i++) {
        lasp.tabAdjSP[i].lPred = NULL;
        lasp.tabAdjSP[i].lSucc = NULL;
    }

    return lasp;
}

ListeAdjSuccPred Mat_LASP(MatAdj ma) {
    int n = ma.nbSom;
    ListeAdjSuccPred lasp = allocLASP(n);
    Liste lPred, lSucc;

    for (int s = 0; s < n; s++) {
        lPred = NULL;
        lSucc = NULL;
        for (int t = n - 1; t >= 0; t--) {
            if (ma.mat[s][t] == 1) {
                lSucc = inserTete(lSucc, t + 1);
            }
            if (ma.mat[t][s] == 1) {
                lPred = inserTete(lPred, t + 1);
            }
        }
        lasp.tabAdjSP[s].lPred = lPred;
        lasp.tabAdjSP[s].lSucc = lSucc;
    }
    return lasp;
}


/// 4.4 FS_Liste
ListeAdj FS_Liste(FileSucc fs) {
    int n = fs.nbSom;
    int p = fs.nbArcs;
    Liste l;
    ListeAdj la = allocListeAdj(n);
    for (int s = 0; s < n; s++) {
        l = NULL; //临时链表
        int nbSucc = fs.APS[s + 1] - fs.APS[s]; //后继数
        int daps = fs.APS[s + 1] - 1; //最后一个后继节点索引
        //从后向前读取当前顶点的所有后继
        for (int t = 0; t < nbSucc; t++) {
            int som = fs.FS[daps - 1]; //获取一个后继节点
            daps--; //移动到前一个位置
            l = inserTete(l, som); //将后继节点插入链表头
        }
        la.tabAdj[s] = l; //保存当前节点的后继链表
    }
    return la;
}

/// Ex4.5 Liste_FS
FileSucc Liste_FS(ListeAdj la) {
    int n = la.nbSom;
    int p = 0;
    Liste l;

    //计算总弧数
    for (int s = 0; s < n; s++) {
        l = la.tabAdj[s];
        while (l != NULL) {
            p++;
            l = l->suiv;
        }
    }

    FileSucc fs = allocFS(n, p);
    int iaps = 0;

    for (int s = 0; s < n; s++) {
        fs.APS[s] = iaps;
        l = la.tabAdj[s];
        while (l != NULL) {
            fs.FS[iaps - 1] = l->somSucc;
            iaps++;
            l = l->suiv;
        }
    }
    fs.APS[n] = p + 1;
    return fs;
}


/// Ex4.6 Adj_Inc(oriente)
/// 邻接矩阵转关联矩阵（无自环）
//创建关联矩阵
MatInc allocMatInc(int n, int p) {
    MatInc mi;
    mi.nbSom = n;
    mi.nbArc = p;
    //为矩阵分配内存
    mi.mat = malloc(n * sizeof(int *));
    if (mi.mat == NULL) {
        printf("Problem de memoire!");
        exit(1);
    }
    //为每行分配内存
    for (int i = 0; i < n; i++) {
        mi.mat[i] = malloc(p * sizeof(int));
        if (mi.mat[i] == NULL) {
            printf("Problem de memoire!");
            exit(1);
        }
    }
    //初始化矩阵为0
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p; j++) {
            mi.mat[i][j] = 0;
        }
    }

    return mi;
}

//对于有向图
MatInc Ajd_Inc(MatAdj ma) {
    int n = ma.nbSom;
    int p = 0;
    //计算边的数量
    for (int s = 0; s < n; s++) {
        for (int t = 0; t < n; t++) {
            if (ma.mat[s][t] == 1) {
                p++;
            }
        }
    }

    MatInc mi = allocMatInc(n, p);
    int a = 0; //边的计数器(a1,a2,a3...)
    for (int s = 0; s < n; s++) {
        for (int t = 0; t < n; t++) {
            if (ma.mat[s][t] == 1) {
                mi.mat[s][a] = 1; //边的起点标记为1
                mi.mat[t][a] = -1; //边的终点标记为-1
                a++;
            }
        }
    }
    return mi;
}

//对于无向图
MatInc Ajd_Inc_NonOriente(MatAdj ma) {
    int n = ma.nbSom;
    int p = 0;

    // 计算无向图的边的数量（避免重复计算）
    for (int s = 0; s < n; s++) {
        for (int t = s + 1; t < n; t++) { // 只考虑上三角部分
            if (ma.mat[s][t] == 1) {
                p++;
            }
        }
    }

    // 分配关联矩阵
    MatInc mi = allocMatInc(n, p);

    int a = 0; // 关联矩阵列索引（表示边）
    for (int s = 0; s < n; s++) {
        for (int t = s + 1; t < n; t++) { // 只处理 (s, t)，避免重复
            if (ma.mat[s][t] == 1) {
                mi.mat[s][a] = 1; // 端点1
                mi.mat[t][a] = 1; // 端点2
                a++;
            }
        }
    }

    return mi;
}

/// 4.7 Inc_Adj（oriente）
/// 关联矩阵转邻接矩阵（有向图，无自环）
//创建邻接矩阵
MatAdj allocMatAdj(int n) {
    MatAdj ma;
    ma.nbSom = n;

    //为矩阵分配内存
    ma.mat = malloc(n * sizeof(int *));
    if (ma.mat == NULL) {
        printf("Problem de memoire!");
        exit(1);
    }

    //给每行分配内存
    for (int i = 0; i < n; i++) {
        ma.mat[i] = malloc(n * sizeof(int));
        if (ma.mat[i] == NULL) {
            printf("Problem de memoire!");
            exit(1);
        }
    }

    //初始化矩阵为0
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ma.mat[i][j] = 0;
        }
    }

    return ma;
}

//转换函数
MatAdj Inc_Adj(MatInc mi) {
    int n = mi.nbSom;
    int p = mi.nbArc;

    MatAdj ma = allocMatAdj(n);

    for (int a = 0; a < p; a++) {
        int s = -1, t = -1, u = 0; //s起点，t终点，u临时顶点
        //还没找到起点或终点时继续
        while (s == -1 || t == -1) {
            if (mi.mat[u][a] == 1) {
                //如果有u到a的边（1）
                s = u; //则是起点
            }
            if (mi.mat[u][a] == -1) {
                //如果有a到u的边（-1）
                t = u; //则是终点
            }
            u++;
        }
        ma.mat[s][t] = 1; //在邻接矩阵中记录这条边
    }
    return ma;
}


/// 4.8 Inc_Adj（non oriente）
// 无向图，关联转邻接（无自环）
MatAdj Inc_Adj_NonOriente(MatInc mi) {
    int n = mi.nbSom;
    int p = mi.nbArc;

    MatAdj ma = allocMatAdj(n);

    for (int a = 0; a < p; a++) {
        int s = -1, t = -1, u = 0;
        while (s == -1 || t == -1) {
            if (mi.mat[u][a] == 1) {
                if (s == -1) {
                    s = u; // 记录第一个顶点
                } else {
                    t = u; // 记录第二个顶点
                }
            }
            u++;
        }
        ma.mat[s][t] = 1;
        ma.mat[t][s] = 1; // 无向图需要对称存储
    }
    return ma;
}


#endif //EX4_H
