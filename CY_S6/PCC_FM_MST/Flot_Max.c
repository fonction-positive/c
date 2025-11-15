//
// Created by 金卓远 on 25-4-3.
//
#include"plus_court_chemin.h"

// 寻找增广路径，这里使用深度优先搜索（DFS）
int dfs(int s, int t, int** residualGraph, int* parent, int n) {
    int visited[n];
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
    }

    int stack[n];
    int top = -1;
    stack[++top] = s;
    visited[s] = 1;
    parent[s] = -1;

    while (top != -1) {
        int u = stack[top--];
        for (int v = 0; v < n; v++) {
            if (!visited[v] && residualGraph[u][v] > 0) {
                stack[++top] = v;
                visited[v] = 1;
                parent[v] = u;
                if (v == t) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

// Ford - Fulkerson DFS版本 Mat
int fordFulkerson(MatAdj G, int source, int sink) {
    int n = G.nbSom;

    //初始化残余图
    int** residualGraph = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        residualGraph[i] = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            residualGraph[i][j] = G.cout[i][j];
        }
    }

    int parent[n];
    int maxFlow = 0;

    //寻找增广路径并更新残余图（dfs为0时结束）
    while (dfs(source, sink, residualGraph, parent, n)) {
        int pathFlow = INT_MAX;
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            pathFlow = (pathFlow < residualGraph[u][v])? pathFlow : residualGraph[u][v];
        }

        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            residualGraph[u][v] -= pathFlow;
            residualGraph[v][u] += pathFlow;
        }

        maxFlow += pathFlow;
    }

    // 释放内存
    for (int i = 0; i < n; i++) {
        free(residualGraph[i]);
    }
    free(residualGraph);

    return maxFlow;
}

// 寻找增广路径，这里使用深度优先搜索（DFS）
int dfs_l(int s, int t, ListeAdj G, int* parent, int n) {
    int visited[n];
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
    }

    int stack[n];
    int top = -1;
    stack[++top] = s;
    visited[s] = 1;
    parent[s] = -1;

    while (top != -1) {
        int u = stack[top--];
        Liste current = G.tabAdj[u];
        while (current != NULL) {
            int v = current->somSucc;
            if (!visited[v] && current->cout > 0) {
                stack[++top] = v;
                visited[v] = 1;
                parent[v] = u;
                if (v == t) {
                    return 1;
                }
            }
            current = current->suiv;
        }
    }
    return 0;
}

// Ford - Fulkerson DFS Liste
int fordFulkerson_l(ListeAdj G, int source, int sink) {
    int n = G.nbSom;
    int maxFlow = 0;
    int parent[n];

    while (dfs_l(source, sink, G, parent, n)) {
        int pathFlow = INT_MAX;
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            Liste current = G.tabAdj[u];
            while (current != NULL) {
                if (current->somSucc == v) {
                    pathFlow = (pathFlow < current->cout)? pathFlow : current->cout;
                    break;
                }
                current = current->suiv;
            }
        }

        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            Liste current = G.tabAdj[u];
            while (current != NULL) {
                if (current->somSucc == v) {
                    current->cout -= pathFlow;
                    break;
                }
                current = current->suiv;
            }

            Liste reverseCurrent = G.tabAdj[v];
            int found = 0;
            while (reverseCurrent != NULL) {
                if (reverseCurrent->somSucc == u) {
                    reverseCurrent->cout += pathFlow;
                    found = 1;
                    break;
                }
                reverseCurrent = reverseCurrent->suiv;
            }
            if (!found) {
                Liste newNode = (Liste)malloc(sizeof(struct cellule));
                newNode->somSucc = u;
                newNode->cout = pathFlow;
                newNode->suiv = G.tabAdj[v];
                G.tabAdj[v] = newNode;
            }
        }

        maxFlow += pathFlow;
    }

    return maxFlow;
}


///分步实现,BFS实现
ListeAdj creatGrapheEcart(ListeAdj g) {
    ListeAdj ge;
    ge.nbSom = g.nbSom;
    ge.tabAdj = (Liste*)malloc(ge.nbSom * sizeof(Liste));
    
    for (int u = 0; u < ge.nbSom; u++) {
        ge.tabAdj[u] = NULL;
        Liste current = g.tabAdj[u];
        while (current != NULL) {
            // Ajouter l'arête u->v avec capacité originale
            Liste newCell = (Liste)malloc(sizeof(struct cellule));
            newCell->somSucc = current->somSucc;
            newCell->cout = current->cout;
            newCell->suiv = ge.tabAdj[u];
            ge.tabAdj[u] = newCell;

            // Ajouter l'arête inverse v->u avec capacité 0
            int v = current->somSucc;
            Liste reverseCell = (Liste)malloc(sizeof(struct cellule));
            reverseCell->somSucc = u;
            reverseCell->cout = 0;
            reverseCell->suiv = ge.tabAdj[v];
            ge.tabAdj[v] = reverseCell;
            
            current = current->suiv;
        }
    }
    return ge;
}

int cheminSimple(int S, int P, ListeAdj ge, int *visite, int *parent) {
    for (int i = 0; i < ge.nbSom; i++) {
        visite[i] = 0;
        parent[i] = -1;
    }
    
    int *queue = (int*)malloc(ge.nbSom * sizeof(int));
    int front = 0, rear = 0;
    queue[rear++] = S;
    visite[S] = 1;
    
    while (front < rear) {
        int u = queue[front++];
        Liste current = ge.tabAdj[u];
        while (current != NULL) {
            int v = current->somSucc;
            if (!visite[v] && current->cout > 0) {
                parent[v] = u;
                visite[v] = 1;
                queue[rear++] = v;
                if (v == P) {
                    free(queue);
                    return 1;
                }
            }
            current = current->suiv;
        }
    }
    free(queue);
    return 0;
}

int capaciteResiduel(int S, int P, int *parent, ListeAdj ge) {
    int min_cap = INT_MAX;
    int v = P;
    
    while (v != S) {
        int u = parent[v];
        Liste current = ge.tabAdj[u];
        while (current != NULL) {
            if (current->somSucc == v) {
                if (current->cout < min_cap) {
                    min_cap = current->cout;
                }
                break;
            }
            current = current->suiv;
        }
        v = u;
    }
    return min_cap;
}

void libererGraphe(ListeAdj ge) {
    for (int i = 0; i < ge.nbSom; i++) {
        Liste current = ge.tabAdj[i];
        while (current != NULL) {
            Liste temp = current;
            current = current->suiv;
            free(temp);
        }
    }
    free(ge.tabAdj);
}

int fordFulkerson_BFS(int S, int P, ListeAdj g) {
    ListeAdj ge = creatGrapheEcart(g);
    int *visite = (int*)malloc(ge.nbSom * sizeof(int));
    int *parent = (int*)malloc(ge.nbSom * sizeof(int));
    int max_flow = 0;
    
    while (cheminSimple(S, P, ge, visite, parent)) {
        int path_flow = capaciteResiduel(S, P, parent, ge);
        max_flow += path_flow;
        
        int v = P;
        while (v != S) {
            int u = parent[v];
            
            // Mettre à jour l'arête u->v
            Liste current = ge.tabAdj[u];
            while (current != NULL) {
                if (current->somSucc == v) {
                    current->cout -= path_flow;
                    break;
                }
                current = current->suiv;
            }
            
            // Mettre à jour l'arête v->u
            current = ge.tabAdj[v];
            while (current != NULL) {
                if (current->somSucc == u) {
                    current->cout += path_flow;
                    break;
                }
                current = current->suiv;
            }
            
            v = u;
        }
    }
    
    free(visite);
    free(parent);
    libererGraphe(ge);
    return max_flow;
}

void test_Flot_Max() {
    int n=6;
    MatAdj Mat=allocMatAdj(n);

    Mat.mat[0][1] = 1; Mat.cout[0][1] = 4;
    Mat.mat[0][2] = 1; Mat.cout[0][2] = 2;
    Mat.mat[1][2] = 1; Mat.cout[1][2] = 1;
    Mat.mat[1][3] = 1; Mat.cout[1][3] = 2;
    Mat.mat[1][4] = 1; Mat.cout[1][4] = 4;
    Mat.mat[2][4] = 1; Mat.cout[2][4] = 2;
    Mat.mat[3][5] = 1; Mat.cout[3][5] = 3;
    Mat.mat[4][5] = 1; Mat.cout[4][5] = 3;

    ListeAdj G =Mat_Liste(Mat);
    // printListeAdj(G);

    // int Flot_Max=fordFulkerson(Mat,0,5);
    // int Flot_Max = fordFulkerson_l(G,0,5);

    int Flot_Max = fordFulkerson_BFS(0,5,G);
    printf("flot maximale = %d \n",Flot_Max);

}

// int main() {
//     test_Flot_Max();
// }