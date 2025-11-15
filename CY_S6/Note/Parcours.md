### ParcoursProfondeur

对三种数据结构（MatAdj,ListeAdj,FS）的图进行递归和迭代两种方法的深度优先遍历（DFS)。

```c
#include <stdio.h>
#include <stdlib.h>

#include "../structGraphe.h"

//根据visite数组，返回下一个sommet
int somSuivant(int s, int n, int *visite) {
    for (int i = s + 1; i < n; i++) {
        // 从 s+1 开始找
        if (!visite[i]) {
            // 发现未访问的节点
            return i;
        }
    }
    // 如果没有找到，则从头开始找
    for (int i = 0; i < s; i++) {
        if (!visite[i]) {
            return i;
        }
    }
    return -1;
}
```

#### MatAdj

```c
//MatAdj
void reParcoursProfondeur_MA(int s, int *visite, MatAdj g, int n, int *nbSomVisite) {
    if (*nbSomVisite < n) {
        visite[s] = 1;
        printf("%d->", s + 1); //节点编号从1开始
        // printf("%d->", s);
        (*nbSomVisite)++;
        for (int t = 0; t < g.nbSom; t++) {
            if (g.mat[s][t] && !visite[t]) {
                //存在边且未访问
                reParcoursProfondeur_MA(t, visite, g, n, nbSomVisite);
            }
        }
    }
}

void itParcoursProfondeur_MA(int s, int *visite, MatAdj g, int n, int *nbSomVisite) {
    int *pile = (int *) malloc(n * sizeof(int)); // 栈
    int sommet = -1; // 栈顶索引
    int arret = 0; // 终止标志

    pile[++sommet] = s; // 入栈

    while (sommet >= 0 && !arret) {
        int u = pile[sommet--]; // 出栈

        if (!visite[u]) {
            printf("%d->", u + 1); // 输出节点编号（从 1 开始）
            visite[u] = 1;
            (*nbSomVisite)++;

            if (*nbSomVisite == n) {
                arret = 1; // 终止遍历
            } else {
                // 从最后一个邻接点到第一个邻接点遍历
                for (int t = g.nbSom - 1; t >= 0; t--) {
                    if (g.mat[u][t] && !visite[t]) {
                        pile[++sommet] = t; // 入栈
                    }
                }
            }
        }
    }
    free(pile);
}
```



#### ListeAdj

```c
//LisiteAdj
void reParcoursProfondeur_LA(int s, int *visite, ListeAdj g, int n, int *nbSomVisite) {
    if (*nbSomVisite < n) {
        visite[s] = 1;
        printf("%d->", s + 1);  // 输出节点编号（从 1 开始）
        (*nbSomVisite)++;

        Liste courant = g.tabAdj[s];  // 获取顶点s的邻接链表
        while (courant != NULL) {
            if (!visite[courant->somSucc-1]) {  // 如果该节点没有被访问(存在g里的节点是从1开始编号的）
                reParcoursProfondeur_LA(courant->somSucc-1, visite, g, n, nbSomVisite);
            }
            courant = courant->suiv;  // 继续遍历下一个邻接点
        }
    }
}

void itParcoursProfondeur_LA(int s, int *visite, ListeAdj g, int n, int *nbSomVisite) {
    int *pile = (int *)malloc(n * sizeof(int)); // 栈
    int sommet = -1; // 栈顶索引
    int arret = 0; // 终止标志

    pile[++sommet] = s; // 入栈

    while (sommet >= 0 && !arret) {
        int u = pile[sommet--]; // 出栈

        if (!visite[u]) {
            printf("%d->", u + 1); // 输出节点编号（从 1 开始）
            visite[u] = 1;
            (*nbSomVisite)++;

            if (*nbSomVisite == n) {
                arret = 1; // 终止遍历
            } else {
                Liste courant = g.tabAdj[u]; // 获取顶点u的邻接链表
                while (courant != NULL) {
                    if (!visite[courant->somSucc-1]) {
                        pile[++sommet] = courant->somSucc-1; // 入栈
                    }
                    courant = courant->suiv;
                }
            }
        }
    }

    free(pile);
}

```



#### FileSucc

```c
//FileSucc
void reParcoursProfondeur_FS(int s, int *visite, FileSucc g, int n, int *nbSomVisite) {
    if (*nbSomVisite < n) {
        visite[s] = 1;
        printf("%d->", s+1); // 节点编号从1开始
        (*nbSomVisite)++;

        int start = g.APS[s]-1; // 当前顶点s在FS中的起始索引
        int end = g.APS[s+1]-1; // 当前顶点s在FS中的结束索引（不包括）

        for (int i = start; i < end; i++) {
            int succ = g.FS[i]-1;
            if (!visite[succ]) {
                reParcoursProfondeur_FS(succ, visite, g, n, nbSomVisite);
            }
        }
    }
}


void itParcoursProfondeur_FS(int s, int *visite, FileSucc g, int n, int *nbSomVisite) {
    int *pile = (int *)malloc(n * sizeof(int)); // 栈
    int sommet = -1; // 栈顶索引
    int arret = 0; // 终止标志

    pile[++sommet] = s; // 入栈

    while (sommet >= 0 && !arret) {
        int u = pile[sommet--]; // 出栈

        if (!visite[u]) {
            printf("%d->", u + 1); // 输出节点编号（从 1 开始）
            visite[u] = 1;
            (*nbSomVisite)++;

            if (*nbSomVisite == n) {
                arret = 1; // 终止遍历
            } else {
                int start = g.APS[u]-1; // 当前顶点u在FS中的起始索引
                int end = g.APS[u + 1]-1; // 当前顶点u在FS中的结束索引（不包括）

                for (int i = end - 1; i >= start; i--) {
                    int succ = g.FS[i]-1;
                    if (!visite[succ]) {
                        pile[++sommet] = succ; // 入栈
                    }
                }
            }
        }
    }

    free(pile);
}
```



#### 主函数

```c
//深度遍历的主函数
//MatAdj,ListeAdj,FS
void parcoursProfondeur(int sd, FileSucc g) {

    //初始化
    int n = g.nbSom;
    int *visite = (int *) malloc(n * sizeof(int)); //访问数组，记录节点是否已经访问
    for (int s = 0; s < n; s++) {
        visite[s] = 0;
    }
    int s = sd-1; //临时节点，节点编号从1开始
    int nbSomVisite = 0; //计数已访问的节点数
    int finParcours = 0;

    while (!finParcours) {
        ///MatAdj
        // reParcoursProfondeur_MA(s, visite, g, n, &nbSomVisite);  //递归写法
        // itParcoursProfondeur_MA(s,visite,g,n,&nbSomVisite);  //迭代写法

        //ListeAdj
        // reParcoursProfondeur_LA(s, visite, g, n, &nbSomVisite);
        // itParcoursProfondeur_LA(s, visite, g, n, &nbSomVisite);

        //FS
        // reParcoursProfondeur_FS(s, visite, g, n, &nbSomVisite);
        itParcoursProfondeur_FS(s, visite, g, n, &nbSomVisite);

        if (nbSomVisite < n) {
            int suiv = somSuivant(s, n, visite);
            if (suiv == -1) {
                finParcours = 1;
            } else {
                s = suiv;
            }
        } else {
            finParcours = 1;
        }
    }
    free(visite);
}
```

#### 测试函数

```c
#include "profondeur.h"
#include "../PrintFree.h"
#include"../structGraphe.h"
#include"../TD1&2/Ex4.h"

int main() {

    int n = 3;
    MatAdj ma;
    ma.nbSom = n;
    ma.mat = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        ma.mat[i] = (int *)malloc(n * sizeof(int));
    }

    // 初始化矩阵（有向图不带自环）
    int adj[3][3] = {
        {0, 0, 1},
        {1, 0, 1},
        {1, 1, 0}
    };

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ma.mat[i][j] = adj[i][j];
        }
    }

    printMatAdj(ma);
    printf("DFS:\n");

    //测试MA
    // parcoursProfondeur(1,ma);

    //测试LA
    // ListeAdj la=Mat_Liste(ma);
    // printListeAdj(la);
    // parcoursProfondeur(1,la);

    //测试FS
    FileSucc fs=Mat_FS(ma);
    printFileSucce(fs);
    parcoursProfondeur(1,fs);


    freeMatAdj(ma);
}
```



### ParcoursLargeur

广度优先遍历只写了迭代版本

#### MatAdj

```c
// MA
void itParcoursLargeur_MA(int s, int *visite, MatAdj g, int n, int *nbSomVisite) {
    File *F = initFile(n);  // 初始化队列，大小为n
    enfiler(s, F);  // 将起始节点加入队列
    int arret = 0;  // 终止条件
    while (!estVideFile(F) && !arret) {
        int u = sommetFile(F);  // 获取队列头部元素
        defiler(F);  // 从队列中移除头部元素

        if (!visite[u]) {  // 如果当前节点未被访问
            visite[u] = 1;  // 标记为已访问
            printf("%d->",u+1);  //打印
            (*nbSomVisite)++;  // 已访问的节点数量加1

            if (n == *nbSomVisite) {  // 如果已访问节点数等于n，则终止
                arret = 1;
            } else {
                // 遍历当前节点u的邻接节点
                for (int t = 0; t < n; t++) {
                    if (g.mat[u][t] == 1 && !visite[t]) {  // 如果存在边u->t且t未访问
                        enfiler(t, F);  // 将t加入队列
                    }
                }
            }
        }
    }

    // 释放队列内存
    free(F->elements);
    free(F);
}
```

#### ListeAdj

```c
//LA
// 迭代广度优先遍历 (邻接表)
void itParcoursLargeur_LA(int s, int *visite, ListeAdj g, int n, int *nbSomVisite) {
    File *F = initFile(n);  // 初始化队列
    enfiler(s, F);  // 将起始节点加入队列
    int arret = 0;  // 终止条件

    while (!estVideFile(F) && !arret) {
        int u = sommetFile(F);  // 获取队列头部元素
        defiler(F);  // 出队

        if (!visite[u]) {  // 如果当前节点未被访问
            visite[u] = 1;  // 标记为已访问
            printf("%d->", u + 1);  // 输出当前访问的节点
            (*nbSomVisite)++;  // 访问计数增加

            if (n == *nbSomVisite) {  // 如果已访问节点数等于n，则终止
                arret = 1;
            } else {
                // 遍历当前顶点的邻接链表
                Liste voisin = g.tabAdj[u];
                while (voisin) {
                    if (!visite[voisin->somSucc-1]) {  // 如果邻接点未访问
                        enfiler(voisin->somSucc-1, F);  // 入队
                    }
                    voisin = voisin->suiv;
                }
            }
        }
    }

    // 释放队列内存
    free(F->elements);
    free(F);
}
```

#### FileSucc

```c
//FS
void itParcoursLargeur_FS(int s, int *visite, FileSucc g, int n, int *nbSomVisite) {
    File *F = initFile(n);  // 初始化队列
    enfiler(s, F);  // 将起始节点加入队列
    int arret = 0;  // 终止条件

    while (!estVideFile(F) && !arret) {
        int u = sommetFile(F);  // 获取队列头部元素
        defiler(F);  // 出队

        if (!visite[u]) {  // 如果当前节点未被访问
            visite[u] = 1;  // 标记为已访问
            printf("%d->", u + 1);  // 输出当前访问的节点
            (*nbSomVisite)++;  // 访问计数增加

            if (n == *nbSomVisite) {  // 如果已访问节点数等于n，则终止
                arret = 1;
            } else {
                // 遍历当前顶点 u 的后继
                int debut = g.APS[u] - 1;
                int fin = g.APS[u + 1] - 1;
                for (int i = debut; i < fin; i++) {
                    int succ = g.FS[i];
                    if (!visite[succ-1]) {  // 如果后继未访问
                        enfiler(succ-1, F);  // 入队
                    }
                }
            }
        }
    }

    // 释放队列内存
    free(F->elements);
    free(F);
}
```

#### 主函数

```c
//主函数
void parcoursLargeur(int sd,FileSucc g) {
    //Initialisation
    int n=g.nbSom;
    int *visite = (int *) malloc(n * sizeof(int)); //访问数组，记录节点是否已经访问
    for (int s = 0; s < n; s++) {
        visite[s] = 0;
    }
    int s = sd-1; //临时节点，节点编号从1开始
    int nbSomVisite = 0; //计数已访问的节点数
    int finParcours = 0;

    //traitement
    while (!finParcours) {
        //MA
        // itParcoursLargeur_MA(s,visite,g,n,&nbSomVisite);
        //LA
        // itParcoursLargeur_LA(s,visite,g,n,&nbSomVisite);
        //FS
        itParcoursLargeur_FS(s,visite,g,n,&nbSomVisite);


        if (nbSomVisite<n) {
            s=somSuivant(s,n,visite);
        }else {
            finParcours=1;
        }
    }
    free(visite);
}
```

#### 测试函数

```c
#include "largeur.h"
#include "file.h"
#include "../PrintFree.h"
#include "../TD1&2/Ex4.h"

int main() {
    int n = 3;
    MatAdj ma;
    ma.nbSom = n;
    ma.mat = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        ma.mat[i] = (int *)malloc(n * sizeof(int));
    }

    // 初始化矩阵（有向图不带自环）
    int adj[3][3] = {
        {0, 0, 1},
        {1, 0, 1},
        {1, 1, 0}
    };

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ma.mat[i][j] = adj[i][j];
        }
    }

    printMatAdj(ma);
    //MA
    // parcoursLargeur(1,ma);
    //LA
    // ListeAdj la=Mat_Liste(ma);
    // parcoursLargeur(1,la);
    //FS
    FileSucc fs=Mat_FS(ma);
    parcoursLargeur(1,fs);

    // 释放la内存
    // freeListeAdj(la);

    //释放fs内存
    free(fs.APS);
    free(fs.FS);

    //释放Mat内存
    freeMatAdj(ma);
    return 0;
}
```