//
// Created by 金卓远 on 25-4-2.
//
#include"plus_court_chemin.h"


// 分配布尔数组
int* allocTab(int n) {
    return (int*)malloc(n*sizeof(int));
}

// 释放布尔数组
void libTab(int* tab) {
    free(tab);
}

MatAdj allocMatAdj(int n) {
    MatAdj G;
    G.nbSom = n;

    // 分配邻接矩阵内存
    G.mat = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        G.mat[i] = (int *)malloc(n * sizeof(int));
    }

    // 分配边权矩阵内存
    G.cout = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        G.cout[i] = (int *)malloc(n * sizeof(int));
    }

    // 简单初始化邻接矩阵和边权矩阵（这里只是示例，实际需根据图结构设置）
    // 邻接矩阵：0 表示无边，1 表示有边
    // 边权矩阵：对应边的权重
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            G.mat[i][j] = 0;
            G.cout[i][j] = 0;
        }
    }
    return G;
}

void freeMatAdj(MatAdj G) {
    int n=G.nbSom;
    // 释放内存
    for (int i = 0; i < n; i++) {
        free(G.mat[i]);
        free(G.cout[i]);
    }
    free(G.mat);
    free(G.cout);
}

ListeAdj allocListeAdj(int n) {
    ListeAdj la;
    la.nbSom = n; //赋值顶点数量
    la.tabAdj = (Liste *) malloc(n * sizeof(Liste));
    //检查内存是否分配成功
    if (la.tabAdj == NULL) {
        printf("problem de memoire!");
        exit(1);
    }
    //初始化所有链表
    for (int i = 0; i < n; i++) {
        la.tabAdj[i] = NULL;
    }
    return la;
}

// 释放邻接列表
void freeListeAdj(ListeAdj l) {
    for (int i = 0; i < l.nbSom; i++) {
        Liste temp = l.tabAdj[i];
        while (temp) {
            Liste toDelete = temp;
            temp = temp->suiv;
            free(toDelete);
        }
    }
    free(l.tabAdj);
}

// 在链表头部插入新节点
Liste inserTete(Liste l, int s, int cout) {
    Liste cel = malloc(sizeof(struct cellule));
    cel->somSucc = s; // 设置后继顶点编号
    cel->cout=cout;
    cel->suiv = l; // 新节点指向原链表头
    l = cel; // 更新链表头
    return l;
}

//转换函数
ListeAdj Mat_Liste(MatAdj ma) {
    int n = ma.nbSom;
    ListeAdj la = allocListeAdj(n);
    Liste l;

    for (int i = 0; i < n; i++) {
        l = NULL; //初始化后继链表
        for (int j = n - 1; j >= 0; j--) {
            //从右往左遍历矩阵，保证后继节点顺序
            if (ma.mat[i][j] == 1) {
                //如果有i->j的边则插入到链表中
                l = inserTete(l, j,ma.cout[i][j]); //编号从0开始，从1开始为j+1
                la.tabAdj[i] = l;
            }
        }
    }
    return la;
}



// 打印邻接列表
void printListeAdj(ListeAdj l) {
    for (int i = 0; i < l.nbSom; i++) {
        printf("Sommet %d : ", i);
        Liste temp = l.tabAdj[i];
        while (temp!=NULL) {
            printf("(%d,%d)-> ", temp->somSucc,temp->cout);
            temp = temp->suiv;
        }
        printf("NULL\n");
    }
}


// 打印邻接矩阵
void printAdjacencyMatrix(MatAdj G) {
    printf("邻接矩阵:\n");
    for (int i = 0; i < G.nbSom; i++) {
        for (int j = 0; j < G.nbSom; j++) {
            printf("%4d", G.mat[i][j]); // 使用 %4d 控制输出宽度为 4 个字符，确保对齐
        }
        printf("\n");
    }
}

// 打印边权矩阵
void printWeightMatrix(MatAdj G) {
    printf("边权矩阵:\n");
    for (int i = 0; i < G.nbSom; i++) {
        for (int j = 0; j < G.nbSom; j++) {
            printf("%4d", G.cout[i][j]); // 使用 %4d 控制输出宽度为 4 个字符，确保对齐
        }
        printf("\n");
    }
}

void printDP(int *D, int *P, int n) {
    printf("S：");
    for (int i = 0; i < n; i++) {
        printf("%4d", i); // 使用 %4d 控制输出宽度为 4 个字符，确保对齐
    }
    printf("\n");

    printf("D：");
    for (int i = 0; i < n; i++) {
        printf("%4d", D[i]); // 使用 %4d 控制输出宽度为 4 个字符，确保对齐
    }
    printf("\n");

    printf("P：");
    for (int i = 0; i < n; i++) {
        printf("%4d", P[i]); // 使用 %4d 控制输出宽度为 4 个字符，确保对齐
    }
    printf("\n");
}

void printDPMat(int **D, int **P, int n) {

    // 打印 D 矩阵
    printf("D: \n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (D[i][j] == INT_MAX) {
                printf("%5s", "INF"); // 使用 %5s 确保宽度一致，字符串占 5 个字符宽度
            } else {
                printf("%5d", D[i][j]); // 使用 %5d 确保数字占 5 个字符宽度
            }
        }
        printf("\n");
    }

    // 打印 P 矩阵
    printf("P: \n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%4d", P[i][j]);
        }
        printf("\n");
    }
}

MICC allocMICC(int nbSom,int nbArete) {
    MICC T;
    T.nbSom = nbSom;
    T.nbArete = nbArete;
    // 分配边数组内存
    T.arete = (Arete*)malloc(nbArete * sizeof(Arete));
    if (T.arete == NULL) {
        exit(0);    // 内存分配失败
    }

    return T;
}

// 打印MICC结构体的函数
void printMICC(MICC t) {
    printf("最小生成树信息:\n");
    printf("顶点数: %d\n", t.nbSom);
    printf("边数: %d\n", t.nbArete);
    printf("边的信息:\n");
    for (int i = 0; i < t.nbArete; i++) {
        printf("边 %d:  %d ->  %d, 权重 %d\n", i + 1, t.arete[i].s,t.arete[i].t,t.arete[i].cout);
    }
}

// 动态分配并初始化 Ensemble 结构体
Ensemble allocEnsemble(int initialCapacity) {
    Ensemble ensemble;

    // 初始化默认值
    ensemble.taille = 0;
    ensemble.tailleMax = initialCapacity;

    // 分配边数组内存
    ensemble.arete = (Arete*)malloc(initialCapacity * sizeof(Arete));
    if (ensemble.arete == NULL) {
        exit(0);    // 内存分配失败
    }

    // 4. 返回初始化后的指针
    return ensemble;
}