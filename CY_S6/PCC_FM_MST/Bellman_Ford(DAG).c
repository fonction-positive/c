//
// Created by 金卓远 on 25-4-3.
//
#include"plus_court_chemin.h"


#include <stdlib.h>
#include <limits.h>


// 拓扑排序 Mat（返回数组长度固定为g.nbSom，存在环则返回NULL）
int* topologicalSortMat(MatAdj g) {
    int nbSom = g.nbSom;
    int *indegree = (int*)calloc(nbSom, sizeof(int));
    int *queue = (int*)malloc(nbSom * sizeof(int));
    int front = 0, rear = 0;
    int *topOrder = (int*)malloc(nbSom * sizeof(int));
    int count = 0;

    // 计算入度
    for (int j = 0; j < nbSom; j++) {
        for (int i = 0; i < nbSom; i++) {
            if (g.mat[i][j]) {
                indegree[j]++;
            }
        }
    }

    // 初始化队列（入度为0的顶点）
    for (int i = 0; i < nbSom; i++) {
        if (indegree[i] == 0) {
            queue[rear++] = i;
        }
    }

    // 生成拓扑序列
    while (front < rear) {
        int u = queue[front++];
        topOrder[count++] = u;

        for (int v = 0; v < nbSom; v++) {
            if (g.mat[u][v]) {
                indegree[v]--;
                if (indegree[v] == 0) {
                    queue[rear++] = v;
                }
            }
        }
    }

    free(indegree);
    free(queue);

    if (count != nbSom) { // 存在环（根据题意无需处理）
        free(topOrder);
        return NULL;
    }

    return topOrder;
}

// 改进的Bellman-Ford算法（按值传递MatAdj）
void bellman_improved_mat(MatAdj g, int s, int *D, int *P) {
    int *topOrder = topologicalSortMat(g);
    if (topOrder == NULL) {
        return; // 存在环，直接返回（根据题意无需处理）
    }

    // 初始化距离和前驱
    for (int i = 0; i < g.nbSom; i++) {
        D[i] = INT_MAX;
        P[i] = -1;
    }
    D[s] = 0;
    P[s] = s;

    // 按拓扑顺序松弛边
    for (int i = 0; i < g.nbSom; i++) {
        int u = topOrder[i];
        if (D[u] == INT_MAX) continue;

        for (int v = 0; v < g.nbSom; v++) {
            if (g.mat[u][v]) {
                int cost = g.cout[u][v];
                if (D[v] > D[u] + cost) {
                    D[v] = D[u] + cost;
                    P[v] = u;
                }
            }
        }
    }

    free(topOrder);
}




// 拓扑排序（Liste）
int* topologicalSortList(ListeAdj g) {
    int nbSom = g.nbSom;
    int *indegree = (int*)calloc(nbSom, sizeof(int));
    int *queue = (int*)malloc(nbSom * sizeof(int));
    int front = 0, rear = 0;
    int *topOrder = (int*)malloc(nbSom * sizeof(int));
    int count = 0;

    // 计算入度
    for (int u = 0; u < nbSom; u++) {
        Liste current = g.tabAdj[u];
        while (current != NULL) {
            indegree[current->somSucc]++;
            current = current->suiv;
        }
    }

    // 初始化队列
    for (int i = 0; i < nbSom; i++) {
        if (indegree[i] == 0) {
            queue[rear++] = i;
        }
    }

    // 生成拓扑序列
    while (front < rear) {
        int u = queue[front++];
        topOrder[count++] = u;

        Liste current = g.tabAdj[u];
        while (current != NULL) {
            int v = current->somSucc;
            indegree[v]--;
            if (indegree[v] == 0) {
                queue[rear++] = v;
            }
            current = current->suiv;
        }
    }

    free(indegree);
    free(queue);

    if (count != nbSom) { // 存在环
        free(topOrder);
        return NULL;
    }

    return topOrder;
}

// 改进的Bellman-Ford算法（按值传递ListeAdj）
void bellman_improved_list(ListeAdj g, int s, int *D, int *P) {
    int *topOrder = topologicalSortList(g);
    if (topOrder == NULL) {
        return; // 存在环，直接返回
    }

    // 初始化距离和前驱
    for (int i = 0; i < g.nbSom; i++) {
        D[i] = INT_MAX;
        P[i] = -1;
    }
    D[s] = 0;
    P[s] = s;

    // 按拓扑顺序松弛边
    for (int i = 0; i < g.nbSom; i++) {
        int u = topOrder[i];
        if (D[u] == INT_MAX) continue;

        Liste current = g.tabAdj[u];
        while (current != NULL) {
            int v = current->somSucc;
            int cost = current->cout;
            if (D[v] > D[u] + cost) {
                D[v] = D[u] + cost;
                P[v] = u;
            }
            current = current->suiv;
        }
    }

    free(topOrder);
}
void test_Bellman() {
    int n=6;

    MatAdj Mat=allocMatAdj(n);

    Mat.mat[0][1] = 1; Mat.cout[0][1] = 1;
    Mat.mat[0][2] = 1; Mat.cout[0][2] = -2;
    Mat.mat[1][3] = 1; Mat.cout[1][3] = -2;
    Mat.mat[1][5] = 1; Mat.cout[1][5] = 3;
    Mat.mat[2][1] = 1; Mat.cout[2][1] = 1;
    Mat.mat[2][3] = 1; Mat.cout[2][3] = 5;
    Mat.mat[2][4] = 1; Mat.cout[2][4] = 4;
    Mat.mat[4][5] = 1; Mat.cout[4][5] = -1;
    Mat.mat[5][3] = 1; Mat.cout[5][3] = -5;

    ListeAdj G=Mat_Liste(Mat);
    printListeAdj(G);

    int *D = (int *)malloc(n * sizeof(int));
    int *P = (int *)malloc(n * sizeof(int));

    // bellman_improved_mat(Mat,0,D,P);
    bellman_improved_list(G,0,D,P);

    printDP(D,P,n);

    freeMatAdj(Mat);
    free(D);
    free(P);
}

int main() {
    test_Bellman();
}