//
// Created by 金卓远 on 25-4-3.
//
#include"plus_court_chemin.h"

// 找到集合M中D值最小的顶点索引
int recherche(int *M, int *D, int n) {
    int minIndex = -1;
    int minValue = INT_MAX;
    for (int i = 0; i < n; i++) {
        if (M[i] && D[i] < minValue) {
            minValue = D[i];
            minIndex = i;
        }
    }
    return minIndex;
}

// 判断集合M是否为空
int estVide(int *M, int n) {
    for (int i = 0; i < n; i++) {
        if (M[i]) {
            return 0;
        }
    }
    return 1;
}

// Dijkstra算法实现
void dijkstra_Mat(int s, MatAdj G, int *D, int *P) {
    int n = G.nbSom;
    int *M = (int *)malloc(n * sizeof(int));
    // 初始化
    for (int t = 0; t < n; t++) {
        if (G.mat[s][t] != 0) {
            D[t] = G.cout[s][t];
            P[t] = s;
        } else {
            D[t] = INT_MAX;
            P[t] = -1;
        }
        M[t] = 1;
    }
    D[s] = 0;
    P[s] = s;

    int estAccessible = 1;
    while (estAccessible &&!estVide(M, n)) {
        int m = recherche(M, D, n);
        if (D[m] == INT_MAX) {
            estAccessible = 0;
        } else {
            M[m] = 0;
            for (int t = 0; t < n; t++) {
                if (G.mat[m][t] != 0 && M[t]) {
                    int tmp = D[m] + G.cout[m][t];
                    if (tmp < D[t]) {
                        D[t] = tmp;
                        P[t] = m;
                    }
                }
            }
        }
    }
    free(M);
}

// Dijkstra算法实现
void dijkstra_Liste(int s, ListeAdj G, int *D, int *P) {
    int n = G.nbSom;
    int *M = (int *)malloc(n * sizeof(int));
    // 初始化
    for (int t = 0; t < n; t++) {
        D[t] = INT_MAX;
        P[t] = -1;
        M[t] = 1;
    }
    D[s] = 0;
    P[s] = s;

    // 处理源点的邻接顶点
    Liste current = G.tabAdj[s];
    while (current != NULL) {
        int t = current->somSucc;
        D[t] = current->cout;
        P[t] = s;
        current = current->suiv;
    }

    int estAccessible = 1;
    while (estAccessible &&!estVide(M, n)) {
        int m = recherche(M, D, n);
        if (D[m] == INT_MAX) {
            estAccessible = 0;
        } else {
            M[m] = 0;
            Liste neighbor = G.tabAdj[m];
            while (neighbor != NULL) {
                int t = neighbor->somSucc;
                if (M[t]) {
                    int tmp = D[m] + neighbor->cout;
                    if (tmp < D[t]) {
                        D[t] = tmp;
                        P[t] = m;
                    }
                }
                neighbor = neighbor->suiv;
            }
        }
    }
    free(M);
}

// Dijkstra算法实现，使用优先队列
void dijkstra_Liste_FileP(int s, ListeAdj G, int *D, int *P, File f) {
    int n = G.nbSom;
    int *M = (int *)malloc(n * sizeof(int));
    // 初始化
    for (int t = 0; t < n; t++) {
        D[t] = INT_MAX;
        P[t] = -1;
        M[t] = 1;
    }
    D[s] = 0;
    P[s] = s;

    initF(f); // 初始化优先队列
    f = enfiler(s,D[s],f); // 将源点入队

    while (!estVide(M, n)) {
        if (estVideF(f)) {
            break;
        }
        int m = sommetF(f);
        f = defiler(f);

        if (D[m] == INT_MAX) {
            break;
        }
        if (M[m]) {
            M[m] = 0;
            Liste neighbor = G.tabAdj[m];
            while (neighbor != NULL) {
                int t = neighbor->somSucc;
                if (M[t]) {
                    int tmp = D[m] + neighbor->cout;
                    if (tmp < D[t]) {
                        D[t] = tmp;
                        P[t] = m;
                        f = enfiler(t, D[t],f); // 将更新后的顶点入队
                    }
                }
                neighbor = neighbor->suiv;
            }
        }
    }
    free(M);
}

// Dijkstra算法实现，使用最小堆
void dijkstra_Liste_minTas(int s, ListeAdj G, int *D, int *P) {
    int n = G.nbSom;
    int *M = (int *)malloc(n * sizeof(int));
    // 初始化距离数组和前驱数组
    for (int t = 0; t < n; t++) {
        D[t] = INT_MAX;
        P[t] = -1;
        M[t] = 1;
    }
    D[s] = 0;
    P[s] = s;

    // 初始化最小堆
    TasMin minHeap = allocMemTas(n);
    minHeap = initTas(minHeap);
    // 将源点插入最小堆
    minHeap = inserTas(s, D, minHeap);

    while (!estVideTas(minHeap)) {
        // 取出最小距离的顶点
        int m = minTas(minHeap);
        minHeap = suppMinTas(D, minHeap);

        if (D[m] == INT_MAX) {
            break;
        }
        if (M[m]) {
            M[m] = 0;
            Liste neighbor = G.tabAdj[m];
            while (neighbor != NULL) {
                int t = neighbor->somSucc;
                if (M[t]) {
                    int tmp = D[m] + neighbor->cout;
                    if (tmp < D[t]) {
                        D[t] = tmp;
                        P[t] = m;
                        // 如果顶点 t 已经在堆中，堆会自动调整
                        // 如果不在堆中，插入堆
                        minHeap = inserTas(t, D, minHeap);
                    }
                }
                neighbor = neighbor->suiv;
            }
        }
    }

    // 释放最小堆的内存
    minHeap = libMemTas(minHeap);
    free(M);
}


void test_dijkstra_Mat() {
    int n=5;

    MatAdj Mat=allocMatAdj(n);

    Mat.mat[0][1] = 1; Mat.cout[0][1] = 10;
    Mat.mat[0][3] = 1; Mat.cout[0][3] = 30;
    Mat.mat[0][4] = 1; Mat.cout[0][4] = 100;
    Mat.mat[1][2] = 1; Mat.cout[1][2] = 50;
    Mat.mat[2][4] = 1; Mat.cout[2][4] = 10;
    Mat.mat[3][2] = 1; Mat.cout[3][2] = 20;
    Mat.mat[3][4] = 1; Mat.cout[3][4] = 60;

    printAdjacencyMatrix(Mat);
    printWeightMatrix(Mat);

    int *D = (int *)malloc(n * sizeof(int));
    int *P = (int *)malloc(n * sizeof(int));

    dijkstra_Mat(0,Mat,D,P);

    printDP(D,P,n);

    freeMatAdj(Mat);
    free(D);
    free(P);
}



void test_dijkstra_Liste() {
    int n=5;

    MatAdj Mat=allocMatAdj(n);

    Mat.mat[0][1] = 1; Mat.cout[0][1] = 10;
    Mat.mat[0][3] = 1; Mat.cout[0][3] = 30;
    Mat.mat[0][4] = 1; Mat.cout[0][4] = 100;
    Mat.mat[1][2] = 1; Mat.cout[1][2] = 50;
    Mat.mat[2][4] = 1; Mat.cout[2][4] = 10;
    Mat.mat[3][2] = 1; Mat.cout[3][2] = 20;
    Mat.mat[3][4] = 1; Mat.cout[3][4] = 60;

    ListeAdj G=Mat_Liste(Mat);
    printListeAdj(G);

    int *D = (int *)malloc(n * sizeof(int));
    int *P = (int *)malloc(n * sizeof(int));

    dijkstra_Liste(0,G,D,P);

    printDP(D,P,n);

    freeMatAdj(Mat);
    free(D);
    free(P);
}


// int main() {
//     test_dijkstra_Mat();
//     test_dijkstra_Liste();
//
//     return 0;
// }


/*
Procédure Dijkstra(s, G, D, P)
G = (S, A, V) graphe sans circuit valué par des coûts quelconques.
s = sommet de départ
Retourne (D et P) un plus court chemin de s à chacun des autres sommets de G.
Début
    //Initialisation
    M ← S \ {s}
    Pour tout sommet t ∈ M faire
        Si (s,t) ∈ A alors
            D[t] ← Coût(s, t)
            P[t] ← s
        Sinon
            D[t] ← ∞
            P[t] ← -1
        Finsi
    Finpour
    D[s] ← 0
    P[s] ← s
    //Itérations
    estAccessible ← vrai
    Tantque estAccessible et non estVide(M) faire
        // Recherche un sommet m ∈ M tel que D[m] est minimal
        m ← recherche(M, D)
            si D[m] = ∞ alors
            // les sommets de M sont inaccessibles depuis s
            estAccessible ← faux
        sinon
            M ← M \ {m}
            Pour tout t ∈ Γ(m) tel que t ∈ M faire
                tmp ← D[m] + coût(m, t)
                Si tmp < D[t] alors
                    D[t] ← tmp
                    P[t] ← m
                Finsi
            Finpour
        Finsi
    Fintq
Fin

*/