//
// Created by 金卓远 on 25-3-2.
//

#ifndef FERMETURETRANSITIVE_H
#define FERMETURETRANSITIVE_H

#include"../structGraphe.h"

///Fermeture MA、LA
///伪代码

void FermetureTransitive_MA(MatAdj g,int **M) {
    for (int s = 0; s < g.nbSom; s++) {
        for (int t = 0; t < g.nbSom; t++) {
            if (g.mat[s][t] == 1) {
                M[s][t] = 1;
            } else {
                M[s][t] = 0;
            }
        }
        M[s][s] = 1;
    }

    for (int k = 0; k < g.nbSom; k++) {
        for (int s = 0; s < g.nbSom; s++) {
            for (int t = 0; t < g.nbSom; t++) {
                M[s][t] = M[s][t] || (M[s][k] && M[k][t]);
            }
        }
    }
}

// 计算图的传递闭包的函数
// 参数：g 是一个表示图的邻接矩阵的结构体，M 是用于存储计算得到的传递闭包矩阵的二维数组
void FermetureTransitive_commentaire(MatAdj g, int **M) {
    // 初始化传递闭包矩阵 M，根据图 g 的邻接矩阵来设置初始值
    for (int s = 0; s < g.nbSom; s++) {
        for (int t = 0; t < g.nbSom; t++) {
            // 如果图 g 的邻接矩阵中 s 到 t 有边（值为 1）
            if (g.mat[s][t] == 1) {
                // 则在传递闭包矩阵 M 中设置 s 到 t 可达（值为 1）
                M[s][t] = 1;
            } else {
                // 否则在传递闭包矩阵 M 中设置 s 到 t 不可达（值为 0）
                M[s][t] = 0;
            }
        }
        // 每个顶点自身到自身是可达的，所以将 M[s][s] 设置为 1
        M[s][s] = 1;
    }

    // 利用 Floyd-Warshall 算法的思想来计算传递闭包
    // 这里通过中间顶点 k 来判断是否存在从 s 到 t 的路径
    for (int k = 0; k < g.nbSom; k++) {
        for (int s = 0; s < g.nbSom; s++) {
            for (int t = 0; t < g.nbSom; t++) {
                // 如果当前 M[s][t] 为 1（即已经知道 s 到 t 可达），或者存在从 s 到 k 且从 k 到 t 的路径
                M[s][t] = M[s][t] || (M[s][k] && M[k][t]);
                // 则更新 M[s][t] 为 1，表示 s 到 t 可达
            }
        }
    }
}


void FermetureTransitive_LA(ListeAdj g,int **M) {
    for (int s = 0; s < g.nbSom; s++) {
        for (int t = 0; t < g.nbSom; t++) {
            M[s][t] = 0;
        }
        M[s][s] = 1;
    }

    for (int s = 0; s < g.nbSom; s++) {
        Liste current = g.tabAdj[s];
        while (current != NULL) {
            int t = current->somSucc-1;
            M[s][t] = 1;
            current = current->suiv;
        }
    }

    // 使用 Floyd-Warshall 算法更新传递闭包矩阵
    for (int k = 0; k < g.nbSom; k++) {
        for (int s = 0; s < g.nbSom; s++) {
            for (int t = 0; t < g.nbSom; t++) {
                M[s][t] = M[s][t] || (M[s][k] && M[k][t]);
            }
        }
    }
}


#endif //FERMETURETRANSITIVE_H

/*
Procédure FermetureTransitive(G, M*)
Début
    //Initialisation M⁰ = MAdj + Identité
    Pour s variant de 1 à n faire
        Pour t variant de 1 à n faire
            Si (s, t) appartient à A alors
                M⁽⁰⁾[s][t] ← 1
            Sinon
                M⁽⁰⁾[s][t] ← 1
            Finsi
        FfinPour
        M⁽⁰⁾[s][s] ← 1
    FfinPour
    //Itérations : mₛₜ⁽ᵏ⁾ = mₛₜ⁽ᵏ⁻¹⁾ ∪ (mₛₖ⁽ᵏ⁻¹⁾ ∩ mₖₜ⁽ᵏ⁻¹⁾)
    Pour k variant de 1 à n faire
        Pour s variant de 1 à n faire
            Pour t variant de 1 à n faire
                M⁽ᵏ⁾[s][t] ← M⁽ᵏ⁻¹⁾[s][t] ∪ (M⁽ᵏ⁻¹⁾[s][k] ∩ M⁽ᵏ⁻¹⁾[k][t])
            FfinPour
        FfinPour
    FfinPour
Fin
*/