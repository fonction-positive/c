//
// Created by 金卓远 on 25-3-1.
//

#ifndef TD4_H
#define TD4_H

#include"../structGraphe.h"
#include "../TD1&2/Ex4.h"

MatAdj carre_MA(MatAdj g) {
    int n = g.nbSom;
    MatAdj g2 = allocMatAdj(n);
    for (int s = 0; s < n; s++) {
        for (int t = 0; t < n; t++) {
            int u = 0;
            while (u < n && g.mat[s][u] * g.mat[u][t] == 0) {
                u++;
            }
            if (u < n) {
                g2.mat[s][t] = 1;
            } else {
                g2.mat[s][t] = 0;
            }
        }
    }
    return g2;
}


// 检查链表中是否存在某个元素t
int existeDansListe(Liste l, int t) {
    while (l != NULL) {
        if (l->somSucc == t) {
            return 1;  // 存在
        }
        l = l->suiv;
    }
    return 0;  // 不存在
}

ListeAdj carre_LA(ListeAdj g) {
    int n = g.nbSom;
    int u, t;
    ListeAdj g2 = allocListeAdj(n);

    // 遍历每个顶点s
    for (int s = 0; s < n; s++) {
        Liste ls = g.tabAdj[s];  // 顶点s的邻接链表

        // 遍历s的邻接链表
        while (ls != NULL) {
            u = ls->somSucc;  // 邻接的顶点u
            ls = ls->suiv;  // 移动到u的下一个邻接顶点

            // 遍历u的邻接链表
            Liste lu = g.tabAdj[u-1];
            while (lu != NULL) {
                t = lu->somSucc;  // 邻接的顶点t
                if (!existeDansListe(g2.tabAdj[s],t)) {
                    g2.tabAdj[s] = inserTete(g2.tabAdj[s], t);  // 将t加入i的邻接链表
                }
                lu = lu->suiv;  // 移动到t的下一个邻接顶点
            }
        }
    }
    return g2;
}


// 计算图的平方
FileSucc carre_FS(FileSucc g) {
    int n = g.nbSom;
    int p=g.nbArcs;
    FileSucc g2 = allocFS(n,p);

    // 为每个顶点对 (s, t) 检查是否存在中间顶点 u
    for (int s = 0; s < n; s++) {
        for (int t = 0; t < n; t++) {
            int found = 0;
            // 遍历顶点 s 的所有后继 u
            for (int i = g.APS[s-1]; i < g.APS[s]; i++) {
                int u = g.FS[i-1];
                // 遍历顶点 u 的所有后继，如果找到 t 则存在路径
                for (int j = g.APS[u-1]; j < g.APS[u]; j++) {
                    if (g.FS[j-1] == t) {
                        found = 1;
                        break;
                    }
                }
                if (found) break;
            }
            if (found) {
                // 如果存在路径，更新 g2 的后继列表
                g2.nbArcs++;
                g2.FS = (int*)realloc(g2.FS, g2.nbArcs * sizeof(int));
                g2.FS[g2.nbArcs - 1] = t;
            }
            g2.APS[s] = g2.nbArcs;
        }
    }
    return g2;
}






#endif //TD4_H
