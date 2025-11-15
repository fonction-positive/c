//
// Created by 金卓远 on 25-4-2.
//

#include "plus_court_chemin.h"


/// Bellman-Ford
void ford_mat(int s, MatAdj G, int *D, int *P) {
    int n = G.nbSom;
    // 初始化部分
    D[s] = 0;
    P[s] = s;
    for (int t = 0; t < n; t++) {
        if (t != s) {
            D[t] = INT_MAX;  // 这里用 INT_MAX 近似表示无穷大
            P[t] = -1;
        }
    }

    // 处理部分
    int Modif;
    do {
        Modif = 0;
        for (int u = 0; u < n; u++) {
            for (int v = 0; v < n; v++) {
                if (G.mat[u][v] != 0) {  // 存在边 (u, v)
                    int tmp = D[u] + G.cout[u][v];
                    if (tmp < D[v]) {
                        D[v] = tmp;
                        P[v] = u;
                        Modif = 1;
                    }
                }
            }
        }
    } while (Modif);
}

void testFord_Mat() {
    int n=5;
    MatAdj G=allocMatAdj(n);

    G.mat[0][1] = 1; G.cout[0][1] = 90;
    G.mat[0][3] = 1; G.cout[0][3] = 80;
    G.mat[0][4] = 1; G.cout[0][4] = 75;
    G.mat[1][2] = 1; G.cout[1][2] = -30;
    G.mat[2][4] = 1; G.cout[2][4] = 10;
    G.mat[3][2] = 1; G.cout[3][2] = -30;
    G.mat[3][4] = 1; G.cout[3][4] = 10;

    int *D = (int *)malloc(n * sizeof(int));
    int *P = (int *)malloc(n * sizeof(int));

    printAdjacencyMatrix(G);
    printWeightMatrix(G);

    ford_mat(0, G, D, P);

    printDP(D,P,n);

    freeMatAdj(G);
    free(D);
    free(P);
}

void ford_liste(int s,ListeAdj graph, int *D, int *P) {
    int n = graph.nbSom;
    // 初始化
    for (int t = 0; t < n; t++) {
        if (t == s) {
            D[t] = 0;
            P[t] = s;
        } else {
            D[t] = INT_MAX;
            P[t] = -1;
        }
    }

    int Modif;
    do {
        Modif = 0;
        for (int u = 0; u < n; u++) {
            Liste pCrawl = graph.tabAdj[u];
            while (pCrawl != NULL) {
                int v = pCrawl->somSucc;
                int weight = pCrawl->cout;
                int tmp = D[u] + weight;
                if (D[u] != INT_MAX && tmp < D[v]) {
                    D[v] = tmp;
                    P[v] = u;
                    Modif = 1;
                }
                pCrawl = pCrawl->suiv;
            }
        }
    } while (Modif);
}

void testFord_Liste() {
    int n=5;

    MatAdj Mat=allocMatAdj(n);

    Mat.mat[0][1] = 1; Mat.cout[0][1] = 90;
    Mat.mat[0][3] = 1; Mat.cout[0][3] = 80;
    Mat.mat[0][4] = 1; Mat.cout[0][4] = 75;
    Mat.mat[1][2] = 1; Mat.cout[1][2] = -30;
    Mat.mat[2][4] = 1; Mat.cout[2][4] = 10;
    Mat.mat[3][2] = 1; Mat.cout[3][2] = -30;
    Mat.mat[3][4] = 1; Mat.cout[3][4] = 10;

    ListeAdj G = Mat_Liste(Mat);

    printListeAdj(G);

    int *D = (int *)malloc(n * sizeof(int));
    int *P = (int *)malloc(n * sizeof(int));

    ford_liste(0,G,D,P);

    printDP(D,P,n);

    freeMatAdj(Mat);
    freeListeAdj(G);
    free(D);
    free(P);
    
}

/*
procedure ford(s, G, D, P)
Début
    // Initialisation
    D[s] ← 0
    P[s] ← s
    Pour t ∈ S(G)-{s} faire
        D[t] ← ∞
        P[t] ← -1
    Finpour
    // Traitement
    Répéter
        Modif ← faux
        Pour s ∈ S(G) faire
            Pour t ∈ Γ(s) faire
                tmp ← d[s] + coût(s, t)
                Si tmp < D[t] alors
                    D[t] ← tmp
                    P[t] ← s
                    Modif ← vrai
                Finsi
            FinPour
        Finpour
    Jusqu'à Modif = faux
Fin

procedure ford(s, G, D, P)
Début
    // Initialisation：初始化部分
    D[s] ← 0 // 将源顶点s在距离数组D中的距离值初始化为0，表示从源点到自身距离为0
    P[s] ← s // 将源顶点s在前驱数组P中的前驱设为自身
    Pour t ∈ S(G)-{s} faire // 对于图G中除源顶点s之外的每个顶点t
        D[t] ← ∞ // 将顶点t在距离数组D中的距离值初始化为无穷大，表示初始时认为不可达
        P[t] ← -1 // 将顶点t在前驱数组P中的前驱设为 -1，表示初始时无前驱顶点
    Finpour
    // Traitement：处理部分
    Répéter // 重复以下操作
        Modif ← faux // 初始化修改标志为假，表示本次迭代尚未发生距离更新
        Pour s ∈ S(G) faire // 对于图G中的每个顶点s
            Pour t ∈ Γ(s) faire // 对于顶点s的每个邻接顶点t（Γ(s)表示s的邻接顶点集合 ）
                tmp ← d[s] + coût(s, t) // 计算从源点经s到t的临时距离，d[s]是s到源点距离，coût(s, t)是s到t的边权
                Si tmp < D[t] alors // 如果临时距离小于当前记录的t到源点的距离
                    D[t] ← tmp // 更新顶点t在距离数组D中的距离值为临时距离
                    P[t] ← s // 更新顶点t在前驱数组P中的前驱为s
                    Modif ← vrai // 将修改标志设为真，表示本次迭代发生了距离更新
                Finsi
            FinPour
        Finpour
    Jusqu'à Modif = faux // 直到修改标志为假，即所有顶点距离不再更新
Fin
*/
