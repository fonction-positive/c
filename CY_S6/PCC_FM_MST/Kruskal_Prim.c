//
// Created by 金卓远 on 25-4-3.
//
#include"plus_court_chemin.h"

// Prim 算法实现
MICC prim_Mat(MatAdj g, int s) {
    int n = g.nbSom;
    int *Dist = (int *)malloc(n * sizeof(int));
    int *PlusProche = (int *)malloc(n * sizeof(int));
    int *CC = (int *)malloc(n * sizeof(int)); // 标记是否已加入生成树
    TasMin M = allocMemTas(n);
    M = initTas(M);

    // 初始化
    for (int i = 0; i < n; i++) {
        Dist[i] = INT_MAX;
        PlusProche[i] = -1;
        CC[i] = 0;
    }
    Dist[s] = 0;
    PlusProche[s] = s;

    // 初始插入起始节点
    M = inserTas(s, Dist, M);

    MICC T = allocMICC(n, n - 1);

    while (!estVideTas(M)) {
        // 取出当前距离最小节点
        int m = minTas(M);
        M = suppMinTas(Dist, M);

        // 关键修正：检查是否为有效节点（可能取出过时值）
        if (!CC[m]) {
            // 如果节点不在 MST 中
            CC[m] = 1;

            // 添加边到生成树（排除起始节点）
            if (m != s) {
                T.arete[T.nbArete].s = PlusProche[m];
                T.arete[T.nbArete].t = m;
                T.arete[T.nbArete].cout = Dist[m];
                T.nbArete++;
            }

            // 处理邻接节点
            for (int t = 0; t < n; t++) {
                if (g.mat[m][t] && !CC[t] && g.cout[m][t] < Dist[t]) {
                    Dist[t] = g.cout[m][t];
                    PlusProche[t] = m;

                    // 插入新实例（旧实例会通过 CC 过滤）
                    M = inserTas(t, Dist, M);
                }
            }
        }
    }

    // 释放资源
    free(Dist);
    free(PlusProche);
    free(CC);
    M = libMemTas(M);
    return T;
}

//Prim(minTas实现）
MICC prim_Liste(ListeAdj g, int s) {
    int n = g.nbSom;
    int *Dist = allocTab(n);
    int *PlusProche = allocTab(n);
    int *CC = allocTab(n); // 标记是否已加入生成树
    TasMin M = allocMemTas(n);
    M = initTas(M);

    // 初始化
    for (int i = 0; i < n; i++) {
        Dist[i] = INT_MAX;
        PlusProche[i] = -1;
        CC[i] = 0;
    }
    Dist[s] = 0;
    PlusProche[s] = s;

    // 初始插入起始节点
    M = inserTas(s, Dist, M);

    MICC T = allocMICC(n, 0);

    while (!estVideTas(M)) {
        // 取出当前距离最小节点
        int m = minTas(M);
        M = suppMinTas(Dist, M);

        // 关键修正：检查是否为有效节点（可能取出过时值）
        if (!CC[m]) {
            //如果节点不在MST中
            CC[m] = 1;

            // 添加边到生成树（排除起始节点）
            if (m != s) {
                T.arete[T.nbArete].s = PlusProche[m];
                T.arete[T.nbArete].t = m;
                T.arete[T.nbArete].cout = Dist[m];
                T.nbArete++;
            }

            // 处理邻接节点
            Liste current = g.tabAdj[m];
            while (current != NULL) {
                int t = current->somSucc;
                int cout = current->cout;

                if (!CC[t] && cout < Dist[t]) {
                    Dist[t] = cout;
                    PlusProche[t] = m;

                    // 插入新实例（旧实例会通过CC过滤）
                    M = inserTas(t, Dist, M);
                }
                current = current->suiv;
            }
        }
    }

    // 释放资源
    free(Dist);
    free(PlusProche);
    free(CC);
    M = libMemTas(M);
    return T;
}


//kurskal

bool isConnected(int u, int v, MICC T, bool *visited) {
    if (u == v) return true;
    visited[u] = true;

    // 遍历当前生成树的所有边
    for (int i = 0; i < T.nbArete; i++) {
        int a = T.arete[i].s, b = T.arete[i].t;
        if (a == u && !visited[b] && isConnected(b, v, T, visited)) return true;
        if (b == u && !visited[a] && isConnected(a, v, T, visited)) return true;
    }
    return false;
}
// 判断边 (s, t) 是否在 T 中形成环路
bool formsCycle(MICC T, Arete edge) {
    bool *visited = (bool*)calloc(T.nbSom, sizeof(bool));
    bool cycle = isConnected(edge.s, edge.t, T, visited);
    free(visited);
    return cycle;
}

// 插入边到集合（避免重复）
Ensemble insertEnsemble(Ensemble U, int s, int t, int cout) {
    // 确保 s <= t 避免重复存储无向边
    if (s > t) {
        int temp = s;
        s = t;
        t = temp;
    }
    // 检查是否已存在
    for (int i = 0; i < U.taille; i++) {
        if (U.arete[i].s == s && U.arete[i].t == t) {
            return U;
        }
    }
    // 插入新边
    if (U.taille < U.tailleMax) {
        U.arete[U.taille++] = (Arete){s, t, cout};
    }
    return U;
}

Arete Minimun(Ensemble U) {
    if (U.taille == 0) {
        // 处理空集合情况
        return (Arete){-1, -1, INT_MAX}; // 返回无效边
    }

    Arete minArete = U.arete[0];
    for (int i = 1; i < U.taille; i++) {
        if (U.arete[i].cout < minArete.cout) {
            minArete = U.arete[i];
        }
    }
    return minArete;
}

Ensemble supArete(Ensemble U, Arete arete) {
    if (U.taille == 0) {
        return U;
    }

    for (int i = 0; i < U.taille; i++) {
        Arete current = U.arete[i];
        if (current.s == arete.s && current.t == arete.t && current.cout == arete.cout) {
            //移动后续元素覆盖当前元素
            for (int j = i; j < U.taille; j++) {
                U.arete[j] = U.arete[j + 1];
            }
            U.taille--;
            break;
        }
    }
    return U;
}

MICC kurskal(MICC g) {
    int n = g.nbSom;
    int na = g.nbArete;
    Ensemble U = allocEnsemble(na);
    MICC T = allocMICC(n, n - 1);
    for (int s = 0; s < n; s++) {
        for (int i = 0; i < g.nbArete; i++) {
            if (g.arete[i].s == s || g.arete[i].t == s) {
                int t = (g.arete[i].s == s) ? g.arete[i].t : g.arete[i].s;
                U = insertEnsemble(U, s, t, g.arete[i].cout);
            }
        }
    }

    int cpt = 0;
    while (cpt < n - 1) {
        Arete arete = Minimun(U);
        U = supArete(U, arete);

        if (!formsCycle(T, arete)) {
            T.arete[cpt]=arete;
            cpt++;
        }
    }
    T.nbArete = cpt;
    return T;
}

void test_prim() {
    int nbSom = 6;
    MatAdj Mat = allocMatAdj(nbSom);


    Mat.mat[0][1] = 1;
    Mat.cout[0][1] = 7;
    Mat.mat[1][0] = 1;
    Mat.cout[1][0] = 7;

    Mat.mat[0][4] = 1;
    Mat.cout[0][4] = 7;
    Mat.mat[4][0] = 1;
    Mat.cout[4][0] = 7;

    Mat.mat[0][5] = 1;
    Mat.cout[0][5] = 2;
    Mat.mat[5][0] = 1;
    Mat.cout[5][0] = 2;

    Mat.mat[1][2] = 1;
    Mat.cout[1][2] = 4;
    Mat.mat[2][1] = 1;
    Mat.cout[2][1] = 4;

    Mat.mat[1][4] = 1;
    Mat.cout[1][4] = 5;
    Mat.mat[4][1] = 1;
    Mat.cout[4][1] = 5;

    Mat.mat[2][3] = 1;
    Mat.cout[2][3] = 1;
    Mat.mat[3][2] = 1;
    Mat.cout[3][2] = 1;

    Mat.mat[2][4] = 1;
    Mat.cout[2][4] = 2;
    Mat.mat[4][2] = 1;
    Mat.cout[4][2] = 2;

    Mat.mat[3][4] = 1;
    Mat.cout[3][4] = 3;
    Mat.mat[4][3] = 1;
    Mat.cout[4][3] = 3;

    Mat.mat[4][5] = 1;
    Mat.cout[4][5] = 1;
    Mat.mat[5][4] = 1;
    Mat.cout[5][4] = 1;

    ListeAdj adjList = Mat_Liste(Mat);

    printListeAdj(adjList);

    MICC T = prim(adjList, 0);
    printMICC(T);

    // 释放矩阵内存
    freeMatAdj(Mat);
    // 释放邻接链表内存
    freeListeAdj(adjList);
}

void test_kurskal() {
    MICC g = allocMICC(6, 9);

    Arete a[] = {
        {0, 1, 7}, // 原 {1,2,7}
        {0, 4, 7}, // 原 {1,5,7}
        {0, 5, 2}, // 原 {1,6,2}
        {1, 2, 4}, // 原 {2,3,4}
        {1, 4, 5}, // 原 {2,5,5}
        {2, 3, 1}, // 原 {3,4,1}
        {2, 4, 2}, // 原 {3,5,2}
        {3, 4, 3}, // 原 {4,5,3}
        {4, 5, 1} // 原 {5,6,1}
    };

    // 填充数据
    for (int i = 0; i < 9; i++) {
        g.arete[i]=a[i];
    }


    printf("G:\n");
    printMICC(g);

    MICC T = kurskal(g);

    printf("MST:\n");
    printMICC(T);
}

// int main() {
//     test_prim();
//     // test_kurskal();
// }
