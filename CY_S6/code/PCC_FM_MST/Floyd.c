//
// Created by 金卓远 on 25-4-3.
//

#include"plus_court_chemin.h"

// Floyd算法实现
void floyd_Mat(MatAdj G, int **D, int **P) {
    int n = G.nbSom;

    // 初始化距离矩阵 D 和前驱矩阵 P
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                D[i][j] = 0;
                P[i][j] = i;
            } else if (G.mat[i][j] != 0) {
                D[i][j] = G.cout[i][j];
                P[i][j] = i;
            } else {
                D[i][j] = INT_MAX;
                P[i][j] = -1;
            }
        }
    }

    // 进行 Floyd-Warshall 算法的核心迭代
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (D[i][k] != INT_MAX && D[k][j] != INT_MAX && D[i][k] + D[k][j] < D[i][j]) {
                    D[i][j] = D[i][k] + D[k][j];
                    P[i][j] = P[k][j];
                }
            }
        }
    }
}

void floyd_Liste(ListeAdj G, int **D, int **P) {
    int n = G.nbSom;

    // 初始化距离矩阵 D 和前驱矩阵 P
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                D[i][j] = 0;
                P[i][j] = i;
            } else {
                D[i][j] = INT_MAX;
                P[i][j] = -1;
            }
        }
    }

    // 根据邻接表更新初始距离矩阵和前驱矩阵
    for (int i = 0; i < n; i++) {
        Liste current = G.tabAdj[i];
        while (current != NULL) {
            int j = current->somSucc;
            D[i][j] = current->cout;
            P[i][j] = i;
            current = current->suiv;
        }
    }

    // 进行 Floyd-Warshall 算法的核心迭代
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (D[i][k] != INT_MAX && D[k][j] != INT_MAX && D[i][k] + D[k][j] < D[i][j]) {
                    D[i][j] = D[i][k] + D[k][j];
                    P[i][j] = P[k][j];
                }
            }
        }
    }
}

void test_floyd() {
    int n=5;

    MatAdj Mat=allocMatAdj(n);

    Mat.mat[0][1] = 1; Mat.cout[0][1] = 10;
    Mat.mat[0][3] = 1; Mat.cout[0][3] = 30;
    Mat.mat[0][4] = 1; Mat.cout[0][4] = 100;
    Mat.mat[1][2] = 1; Mat.cout[1][2] = 50;
    Mat.mat[2][4] = 1; Mat.cout[2][4] = 10;
    Mat.mat[3][2] = 1; Mat.cout[3][2] = 20;
    Mat.mat[3][4] = 1; Mat.cout[3][4] = 60;

    // printAdjacencyMatrix(Mat);
    // printWeightMatrix(Mat);

    ListeAdj G = Mat_Liste(Mat);
    printListeAdj(G);

    // 分配距离矩阵 D 和前驱矩阵 P 的内存
    int **D = (int **)malloc(n * sizeof(int *));
    int **P = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        D[i] = (int *)malloc(n * sizeof(int));
        P[i] = (int *)malloc(n * sizeof(int));
    }

    // floyd_Mat(Mat,D,P);
    floyd_Liste(G,D,P);

    printDPMat(D,P,n);

    freeMatAdj(Mat);
    freeListeAdj(G);
    free(D);
    free(P);

}

// int main() {
//     test_floyd();
// }

