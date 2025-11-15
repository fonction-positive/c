//
// Created by 金卓远 on 25-4-3.
//

#include <stdio.h>
#include"plus_court_chemin.h"



// 分配堆内存
TasMin allocMemTas(int nbSom) {
    TasMin M;
    M.tailleMax = nbSom;
    M.taille = 0;
    M.tab = (int *)malloc(nbSom * sizeof(int));
    M.pos = (int *)malloc(nbSom * sizeof(int));
    for (int i = 0; i < nbSom; i++) {
        M.pos[i] = -1; // 初始时所有顶点不在堆中
    }
    return M;
}

// 释放堆内存
TasMin libMemTas(TasMin M) {
    free(M.tab);
    free(M.pos);
    M.tab = NULL;
    M.pos = NULL;
    M.taille = 0;
    M.tailleMax = 0;
    return M;
}

// 初始化堆
TasMin initTas(TasMin M) {
    M.taille = 0;
    for (int i = 0; i < M.tailleMax; i++) {
        M.pos[i] = -1;
    }
    return M;
}

// 判断堆是否为空
int estVideTas(TasMin M) {
    return M.taille == 0;
}

// 获取堆顶元素（最小值）
int minTas(TasMin M) {
    return (M.taille > 0) ? M.tab[0] : -1;
}

// 交换堆中的两个元素
void echanger(TasMin *M, int i, int j) {
    int temp = M->tab[i];
    M->tab[i] = M->tab[j];
    M->tab[j] = temp;

    // 更新位置数组
    M->pos[M->tab[i]] = i;
    M->pos[M->tab[j]] = j;
}

// 向上调整堆
void monterTas(TasMin *M, int i, int *D) {
    while (i > 0 && D[M->tab[i]] < D[M->tab[(i - 1) / 2]]) {
        echanger(M, i, (i - 1) / 2);
        i = (i - 1) / 2;
    }
}

// 插入元素 t 到最小堆
TasMin inserTas(int t, int *D, TasMin M) {
    if (M.taille >= M.tailleMax) return M; // 堆已满

    int i = M.taille++;
    M.tab[i] = t;
    M.pos[t] = i;

    monterTas(&M, i, D);
    return M;
}

// 向下调整堆
void descendreTas(TasMin *M, int i, int *D) {
    int minIndex = i;
    int gauche = 2 * i + 1;
    int droite = 2 * i + 2;

    if (gauche < M->taille && D[M->tab[gauche]] < D[M->tab[minIndex]]) {
        minIndex = gauche;
    }
    if (droite < M->taille && D[M->tab[droite]] < D[M->tab[minIndex]]) {
        minIndex = droite;
    }

    if (minIndex != i) {
        echanger(M, i, minIndex);
        descendreTas(M, minIndex, D);
    }
}

// 删除堆顶元素（最小值）
TasMin suppMinTas(int *D, TasMin M) {
    if (M.taille == 0) return M;

    int minElem = M.tab[0];
    M.tab[0] = M.tab[--M.taille];
    M.pos[M.tab[0]] = 0;
    M.pos[minElem] = -1; // minElem 已经被移除

    descendreTas(&M, 0, D);
    return M;
}

// 测试代码
// int main() {
//     int D[] = {10, 20, 5, 30, 15}; // 假设的距离数组
//
//     // 初始化最小堆
//     TasMin M = allocMemTas(5);
//     M = initTas(M);
//
//     // 插入元素
//     M = inserTas(0, D, M);
//     M = inserTas(1, D, M);
//     M = inserTas(2, D, M);
//     M = inserTas(3, D, M);
//     M = inserTas(4, D, M);
//
//     // 打印堆顶元素
//     printf("Min: %d\n", minTas(M));
//
//     // 删除最小元素
//     M = suppMinTas(D, M);
//     printf("Après suppression, Min: %d\n", minTas(M));
//
//     // 释放内存
//     M = libMemTas(M);
//     return 0;
// }