//
// Created by 金卓远 on 25-2-22.
//
/*
On considère un graphe orienté G=(S, A) qui peut être représenté selon l'une des structures
suivantes :
a) Une matrice d'adjacence.
b) Une liste d'adjacence
c) Une file des successeurs.
Pour chaque type de représentation, écrire les algorithmes suivants :
1. Détermination des successeurs : Écrire un algorithme qui identifie tous les successeurs
d’un sommet s donné dans un graphe G donné.
2. Détermination des prédécesseurs : Écrire un algorithme qui identifie tous les
prédécesseurs d’un sommet s donné dans un graphe G donné.
3. Détection de boucles : Écrire un algorithme qui vérifie si un graphe G donné contient une
boucle (un arc reliant un sommet à lui-même).
4. Sommet ayant le plus de successeurs : Écrire un algorithme qui détermine le sommet du
graphe G non vide, non vide, ayant le plus grand nombre de successeurs.
*/
#ifndef EX3_H
#define EX3_H
#include <stdbool.h>
#include <stdio.h>
#include"../structGraphe.h"

/// 1.找出给定顶点的所有后继顶点
// a)Mat
void somSucc1(int s, MatAdj m) {
    int n = m.nbSom; //顶点数量
    for (int i = 0; i < n; i++) {
        if (m.mat[s][i] == 1) {
            // 如果存在从s到i的边
            printf("%d ", i + 1);
        }
    }
}

// b)Liste
void somSucc2(int s, ListeAdj la) {
    Liste ll = la.tabAdj[s]; //获取s的后继链表
    //遍历并打印所有后继顶点
    while (ll != NULL) {
        printf("%d ", ll->somSucc);
        ll = ll->suiv;
    }
}

// c)FileSucc
/*
以索引从1开始为例：
FS[] = {2, 3, 1, 2, 3, 1, 2, 4, 3}
APS[] = {1, 3, 6, 9, 10}

fonction somSucc(s,fs) -> vide
    F.P s:Somment=int
        fs:Graphe=FileSucc
Debut
    nbSucc <- fs.APS[s+1]-fs.APS[s] //这个顶点的后继顶点数量
    pour i variant de fs.APS[s] à fs.APS[s]+nbSucc faire
        traiter(fs.FS[i])
    finpour
Fin
*/
void somSucc3(int s, FileSucc fs) {
    // APS[s-1] 给出的是第一个后继的索引位置，遍历该区间来获取后继节点
    for (int i = fs.APS[s - 1]; i < fs.APS[s]; i++) {
        printf("%d ", fs.FS[i - 1]);
    }
}

/// 2.输出给定顶点的所有前驱顶点
// a)Mat
void somPred1(int s, MatAdj m) {
    int n = m.nbSom;
    for (int i = 0; i < n; i++) {
        if (m.mat[i][s] == 1) {
            //如果存在从i到s的边
            printf("%d ", i + 1);
        }
    }
}

// b)Liste
void somPred2(int s, ListeAdj la) {
    //遍历每个顶点的邻接链表
    for (int i = 0; i < la.nbSom; i++) {
        Liste courant = la.tabAdj[i]; //获取第i个顶点的邻接链表
        while (courant != NULL) {
            if (courant->somSucc == s) {
                //如果顶点i的邻接链表中有s，则说明i是s的前驱节点
                printf("%d ", i + 1); //按照顶点从1开始编号
            }
            courant = courant->suiv;
        }
    }
}

// c)FileSucc
/*
fct somPred3(s,fs)->void
    F.S s:somment=int
        fs:graphe=FileSucc
Debut
    pour pred variant de 1 à nbSom faire
        pour i variant de fs.APS[pred] à fs.APS[pred+1] faire
            si fs.FS[i] = s
                traiter pred
            finsi
        finpour
    finpour
Fin
*/
void somPred3(int s, FileSucc fs) {
    //遍历所有顶点（可能的前驱）
    for (int pred = 1; pred <= fs.nbSom; pred++) {
        //遍历每个顶点的后继节点
        for (int i = fs.APS[pred - 1] - 1; i < fs.APS[pred] - 1; i++) {
            if (fs.FS[i] == s) {
                //如果后继节点中有s，则说明pred是s的前驱节点
                printf("%d ", pred);
                break; //继续判断下一个顶点
            }
        }
    }
}

/// 判断是否有自环
// a)Mat
int estBoucle1(MatAdj m) {
    int n = m.nbSom;
    int s = 0;
    int flag = 0;
    while (s < n && flag == 0) {
        //如果mat[s][s]=1说明有自己到自己的弧（边）
        if (m.mat[s][s] == 1) {
            flag = 1;
        }
        s++;
    }
    return flag;
}

// b)Liste
int estBoucle2(ListeAdj la) {
    int n = la.nbSom;
    int s = 0;
    int flag = 0;
    Liste l;
    //遍历每个顶点
    while (s < n && flag == 0) {
        l = la.tabAdj[s]; //获取s的后继节点链表
        //遍历当前顶点的后继链表
        while (l != NULL && flag == 0) {
            //如果s的后继节点中有自己，说明有自环
            if (l->somSucc == s) {
                flag = 1;
            }
            l = l->suiv;
        }
        s++;
    }
    return flag;
}

// c)FileSucc
/*
fct estBoucle3(fs) -> bool
    F.S fs:Graphe = FileSucc
Debut
    n <- nbsom(fs)
    s <- 0
    nbSucc <- 0
    iAps <- 0
    flag <- faux

    tq s<n et flag=faux
        nbSucc <- fs.APS[s+1]-fs.APS[s]
        iAps <- fs.APS[s]

        pour j variant de 0 à nbSucc faire
            si fs.FS[iAps+j] = s
                flag <- vrai
            finsi
        finpour
        s <- s+1
    fintq

    renvoyer flag
Fin
 */
int estBoucle3(FileSucc fs) {
    int n = fs.nbSom;
    int s = 0;
    int nbSucc = 0;
    int iAps = 0;
    int flag = 0;

    while (s < n && flag == 0) {
        nbSucc = fs.APS[s + 1] - fs.APS[s]; //当前节点的后继数量
        iAps = fs.APS[s]; //当前节点后继节点在FS中的起始位置
        for (int j = 0; j < nbSucc && flag == 0; j++) {
            if (fs.FS[iAps - 1 + j] == s) {
                flag = 1;
            }
        }
        s++;
    }
    return flag;
}

//受不了摩洛哥了，自己写吧
int estBoucle3_jin(FileSucc fs) {
    int n = fs.nbSom;
    int flag = 0;
    int s = 0;
    //遍历所有顶点
    while (s < n && flag == 0) {
        //遍历当前顶点的后继节点
        for (int i = fs.APS[s] - 1; i < fs.APS[s + 1] - 1; i++) {
            //如果后继节点中有s，则说明当前节点是s的前序节点
            if (fs.FS[i] == s) {
                flag = 1;
                break;
            }
        }
        s++;
    }
    return flag;
}


/// 找出后继节点最多的顶点
// a)Mat
int somPlusSucc1(MatAdj m) {
    int n = m.nbSom; //图中顶点数
    int nsMax = 0; //记录最大后继数
    int sMax = 1; //记录后继数最多的顶点
    int ns = 0; //计数器
    //遍历所有顶点（每一行）
    for (int i = 0; i < n; i++) {
        //遍历每一列
        for (int j = 0; j < n; j++) {
            if (m.mat[i][j] == 1) {
                ns++;
            }
        }
        if (ns > nsMax) {
            nsMax = ns;
            sMax = i + 1; //顶点从1开始编号
        }
        ns = 0; //重置计数器
    }
    return sMax;
}

// b)Liste
int somPlusSucc2(ListeAdj la) {
    int n = la.nbSom;
    int nsMax = 0;
    int sMax = 1;
    int ns = 0;
    Liste l;
    for (int i = 0; i < n; i++) {
        l = la.tabAdj[i];
        while (l != NULL) {
            ns++;
            l = l->suiv;
        }
        if (ns > nsMax) {
            nsMax = ns;
            sMax = i + 1; //顶点从1开始编号
        }
        ns = 0; //重置计数器
    }
    return sMax;
}

// c)FileSucc
int somPlusSucc3(FileSucc fs) {
    int n=fs.nbSom;
    int nsMax=0;
    int sMax=1;
    for (int i=0;i<n;i++) {
        int ns=fs.APS[i+1]-fs.APS[i]; //计算当前顶点的后继数
        if (ns>nsMax) {
            nsMax=ns;
            sMax=i+1; //顶点编号从1开始
        }
    }
    return sMax;
}

#endif //EX3_H
