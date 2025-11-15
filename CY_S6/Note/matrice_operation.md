## Opération de Matrice

On considère un graphe orienté G=(S, A) qui peut être représenté selon l'une des structures suivantes :

- Une matrice d'adjacence.
- Une liste d'adjacence.
- Une file des successeurs.

Pour chaque type de représentation, écrire les algorithmes suivants :

### Détermination des successeurs

找出给定顶点的所有后继顶点

#### MatAdj

```c
void somSucc1(int s, MatAdj m) {
    int n = m.nbSom; //顶点数量
    for (int i = 0; i < n; i++) {
        if (m.mat[s][i] == 1) {
            // 如果存在从s到i的边
            printf("%d ", i + 1);
        }
    }
}
```

#### ListeAdj

```c
void somSucc2(int s, ListeAdj la) {
    Liste ll = la.tabAdj[s]; //获取s的后继链表
    //遍历并打印所有后继顶点
    while (ll != NULL) {
        printf("%d ", ll->somSucc);
        ll = ll->suiv;
    }
}
```

#### FileSucc

```
伪代码，以索引从1开始为例：
FS[] = {2, 3, 1, 2, 3, 1, 2, 4, 3}
APS[] = {1, 3, 6, 9, 10}

fonction somSucc(s,fs) -> vide
    F.P s:Somment=int
        fs:Graphe=FileSucc
Debut
    nbSucc <- fs.APS[s+1]-fs.APS[s] //这个顶点的后继顶点数量
    pour i variant de fs.APS[s] à fs.APS[s]+nbSucc faire
        traiter(fs.FS[i])
    finpour
Fin
```

```c
void somSucc3(int s, FileSucc fs) {
    // APS[s-1] 给出的是第一个后继的索引位置，遍历该区间来获取后继节点
    for (int i = fs.APS[s - 1]; i < fs.APS[s]; i++) {
        printf("%d ", fs.FS[i - 1]);
    }
}
```

### Détermination des prédécesseurs

输出给定顶点的所有前驱顶点

#### MatAdj

```c
void somPred1(int s, MatAdj m) {
    int n = m.nbSom;
    for (int i = 0; i < n; i++) {
        if (m.mat[i][s] == 1) {
            //如果存在从i到s的边
            printf("%d ", i + 1);
        }
    }
}
```

#### ListeAdj

```c
void somPred2(int s, ListeAdj la) {
    //遍历每个顶点的邻接链表
    for (int i = 0; i < la.nbSom; i++) {
        Liste courant = la.tabAdj[i]; //获取第i个顶点的邻接链表
        while (courant != NULL) {
            if (courant->somSucc == s) {
                //如果顶点i的邻接链表中有s，则说明i是s的前驱节点
                printf("%d ", i + 1); //按照顶点从1开始编号
            }
            courant = courant->suiv;
        }
    }
}
```

#### FileSucc

```
伪代码：
fct somPred3(s,fs)->void
    F.S s:somment=int
        fs:graphe=FileSucc
Debut
    pour pred variant de 1 à nbSom faire
        pour i variant de fs.APS[pred] à fs.APS[pred+1] faire
            si fs.FS[i] = s
                traiter pred
            finsi
        finpour
    finpour
Fin
```

```c
void somPred3(int s, FileSucc fs) {
    //遍历所有顶点（可能的前驱）
    for (int pred = 1; pred <= fs.nbSom; pred++) {
        //遍历每个顶点的后继节点
        for (int i = fs.APS[pred - 1] - 1; i < fs.APS[pred] - 1; i++) {
            if (fs.FS[i] == s) {
                //如果后继节点中有s，则说明pred是s的前驱节点
                printf("%d ", pred);
                break; //继续判断下一个顶点
            }
        }
    }
}
```

### Détection de boucles

判断是否有自环

#### MatAdj

```c
int estBoucle1(MatAdj m) {
    int n = m.nbSom;
    int s = 0;
    int flag = 0;
    while (s < n && flag == 0) {
        //如果mat[s][s]=1说明有自己到自己的弧（边）
        if (m.mat[s][s] == 1) {
            flag = 1;
        }
        s++;
    }
    return flag;
}
```

#### ListeAdj

```c
int estBoucle2(ListeAdj la) {
    int n = la.nbSom;
    int s = 0;
    int flag = 0;
    Liste l;
    //遍历每个顶点
    while (s < n && flag == 0) {
        l = la.tabAdj[s]; //获取s的后继节点链表
        //遍历当前顶点的后继链表
        while (l != NULL && flag == 0) {
            //如果s的后继节点中有自己，说明有自环
            if (l->somSucc == s) {
                flag = 1;
            }
            l = l->suiv;
        }
        s++;
    }
    return flag;
}
```

#### FileSucc

```
伪代码：
fct estBoucle3(fs) -> bool
    F.S fs:Graphe = FileSucc
Debut
    n <- nbsom(fs)
    s <- 0
    nbSucc <- 0
    iAps <- 0
    flag <- faux

    tq s<n et flag=faux
        nbSucc <- fs.APS[s+1]-fs.APS[s]
        iAps <- fs.APS[s]

        pour j variant de 0 à nbSucc faire
            si fs.FS[iAps+j] = s
                flag <- vrai
            finsi
        finpour
        s <- s+1
    fintq

    renvoyer flag
Fin
```

```c
int estBoucle3(FileSucc fs) {
    int n = fs.nbSom;
    int s = 0;
    int nbSucc = 0;
    int iAps = 0;
    int flag = 0;

    while (s < n && flag == 0) {
        nbSucc = fs.APS[s + 1] - fs.APS[s]; //当前节点的后继数量
        iAps = fs.APS[s]; //当前节点后继节点在FS中的起始位置
        for (int j = 0; j < nbSucc && flag == 0; j++) {
            if (fs.FS[iAps - 1 + j] == s) {
                flag = 1;
            }
        }
        s++;
    }
    return flag;
}
```

```c
//受不了摩洛哥了，自己写吧
int estBoucle3_jin(FileSucc fs) {
    int n = fs.nbSom;
    int flag = 0;
    int s = 0;
    //遍历所有顶点
    while (s < n && flag == 0) {
        //遍历当前顶点的后继节点
        for (int i = fs.APS[s] - 1; i < fs.APS[s + 1] - 1; i++) {
            //如果后继节点中有s，则说明当前节点是s的前序节点
            if (fs.FS[i] == s) {
                flag = 1;
                break;
            }
        }
        s++;
    }
    return flag;
}
```

### Sommet ayant le plus de successeurs

找出后继节点最多的顶点

#### MatAdj

```c
int somPlusSucc1(MatAdj m) {
    int n = m.nbSom; //图中顶点数
    int nsMax = 0; //记录最大后继数
    int sMax = 1; //记录后继数最多的顶点
    int ns = 0; //计数器
    //遍历所有顶点（每一行）
    for (int i = 0; i < n; i++) {
        //遍历每一列
        for (int j = 0; j < n; j++) {
            if (m.mat[i][j] == 1) {
                ns++;
            }
        }
        if (ns > nsMax) {
            nsMax = ns;
            sMax = i + 1; //顶点从1开始编号
        }
        ns = 0; //重置计数器
    }
    return sMax;
}
```

#### ListeAdj

```c
int somPlusSucc2(ListeAdj la) {
    int n = la.nbSom;
    int nsMax = 0;
    int sMax = 1;
    int ns = 0;
    Liste l;
    for (int i = 0; i < n; i++) {
        l = la.tabAdj[i];
        while (l != NULL) {
            ns++;
            l = l->suiv;
        }
        if (ns > nsMax) {
            nsMax = ns;
            sMax = i + 1; //顶点从1开始编号
        }
        ns = 0; //重置计数器
    }
    return sMax;
}
```

#### FileSucc

```c
int somPlusSucc3(FileSucc fs) {
    int n=fs.nbSom;
    int nsMax=0;
    int sMax=1;
    for (int i=0;i<n;i++) {
        int ns=fs.APS[i+1]-fs.APS[i]; //计算当前顶点的后继数
        if (ns>nsMax) {
            nsMax=ns;
            sMax=i+1; //顶点编号从1开始
        }
    }
    return sMax;
}
```

### 测试函数

```c
#include "Ex3.h"

int main() {

    FileSucc fs;
    fs.nbSom = 3; // 顶点数
    fs.nbArcs = 6; // 边数

    // FS：存储所有后继
    //
    // int FS[] = {2, 3, 1, 2, 3, 1, 2, 4, 3};
    int FS[] = {1, 3, 1, 3, 1, 2};
    fs.FS = FS;

    // APS：存储每个顶点的后继在 FS 中的起始位置
    // int APS[] = {1, 3, 6, 9, 10};
    int APS[] = {1, 3, 5, 7};
    fs.APS = APS;

    // 测试打印每个顶点的后继节点
    // for (int i = 1; i <= fs.nbSom; i++) {
    //     printf("Les successeurs du sommet %d sont: ", i);
    //     somSucc3(i, fs);
    // }
    // somSucc3(1, fs);
    // printf("\n");
    somPred3(1, fs);


    return 0;
}
```

## Changement de Matrice

### Mat_Liste

Ecrire un algorithme qui construit la liste d’adjacence d’un graphe donné à partir de sa matrice d’adjacence.

```c
/// 4.1 Mat_Liste
//创建ListeAdj
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

// 在链表头部插入新节点
Liste inserTete(Liste l, int s) {
    Liste cel = malloc(sizeof(struct cellule));
    cel->somSucc = s; // 设置后继顶点编号
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
                l = inserTete(l, j + 1);
                la.tabAdj[i] = l;
            }
        }
    }
    return la;
}
```

### Mat_FS

Ecrire un algorithme qui construit la file des successeurs d’un graphe donné à partir de sa matrice d’adjacence.

```c
/// 4.2 Mat_FS
//创建FileSucc
FileSucc allocSFS(int n, int p) {
    FileSucc fs;
    fs.nbSom = n;
    fs.nbArcs = p;

    //分配内存
    fs.APS = malloc((n + 1) * sizeof(int));
    if (fs.APS == NULL) {
        printf("Problem de memoire!");
        exit(1);
    }

    fs.FS = malloc(p * sizeof(int));
    if (fs.FS == NULL) {
        printf("Problem de memoire!");
        exit(1);
    }

    return fs;
}


/*
fct Mat_FS(ma) -> FileSucc
    P.F ma:Graphe=MatAdj(E)
Debut
    n <- nbSom(ma)
    p <- nbArcs(ma)
    fs <- allocSFS(n,p)
    iaps <- 1
    pour s variant de 1 à n faire
        fs.APS[s] <- iaps
        pour t variant de 1 à n faire
            si ma.Mat[s][t] = 1 alors
                fs.FS[iaps] = t
                iaps <- iaps+1
            finsi
        finpour
    finpour
Fin
 */

FileSucc Mat_FS(MatAdj ma) {
    //计算n和p（顶点和弧的数量）
    int n = ma.nbSom; //顶点
    int p = 0; //弧
    //仅考虑有向图，计算弧的数量
    for (int s = 0; s < n; s++) {
        for (int t = 0; t < n; t++) {
            if (ma.mat[s][t] == 1) {
                p++;
            }
        }
    }

    FileSucc fs = allocSFS(n, p);
    int iaps = 0;
    for (int s = 0; s < n; s++) {
        fs.APS[s] = iaps + 1;
        for (int t = 0; t < n; t++) {
            if (ma.mat[s][t] == 1) {
                fs.FS[iaps] = t + 1;
                iaps++;
            }
        }
    }
    fs.APS[n] = iaps + 1;
    return fs;
}
```

### Mat_LASP

Ecrire un algorithme qui construit le tableau de listes des successeurs et prédécesseurs d’un graphe donné à partir de sa matrice d’adjacence.

```c
/// 4.3 Mat_LASP
ListeAdjSuccPred allocLASP(int n) {
    ListeAdjSuccPred lasp;
    lasp.nbSom = n;

    //分配内存
    lasp.tabAdjSP = malloc(n * sizeof(ListeSuccPred));
    if (lasp.tabAdjSP == NULL) {
        printf("Problem de memoire!");
        exit(1);
    }

    //初始化所有前驱和后继链表
    for (int i = 0; i < n; i++) {
        lasp.tabAdjSP[i].lPred = NULL;
        lasp.tabAdjSP[i].lSucc = NULL;
    }

    return lasp;
}

ListeAdjSuccPred Mat_LASP(MatAdj ma) {
    int n = ma.nbSom;
    ListeAdjSuccPred lasp = allocLASP(n);
    Liste lPred, lSucc;

    for (int s = 0; s < n; s++) {
        lPred = NULL;
        lSucc = NULL;
        for (int t = n - 1; t >= 0; t--) {
            if (ma.mat[s][t] == 1) {
                lSucc = inserTete(lSucc, t + 1);
            }
            if (ma.mat[t][s] == 1) {
                lPred = inserTete(lPred, t + 1);
            }
        }
        lasp.tabAdjSP[s].lPred = lPred;
        lasp.tabAdjSP[s].lSucc = lSucc;
    }
    return lasp;
}
```

### FS_Liste

Ecrire un algorithme qui construit la liste d’adjacence d’un graphe donné à partir de sa file des successeurs.

```c
/// 4.4 FS_Liste
ListeAdj FS_Liste(FileSucc fs) {
    int n = fs.nbSom;
    int p = fs.nbArcs;
    Liste l;
    ListeAdj la = allocListeAdj(n);
    for (int s = 0; s < n; s++) {
        l = NULL; //临时链表
        int nbSucc = fs.APS[s + 1] - fs.APS[s]; //后继数
        int daps = fs.APS[s + 1] - 1; //最后一个后继节点索引
        //从后向前读取当前顶点的所有后继
        for (int t = 0; t < nbSucc; t++) {
            int som = fs.FS[daps - 1]; //获取一个后继节点
            daps--; //移动到前一个位置
            l = inserTete(l, som); //将后继节点插入链表头
        }
        la.tabAdj[s] = l; //保存当前节点的后继链表
    }
    return la;
}
```

### Liste_FS

Ecrire un algorithme qui construit la file des successeurs d’un graphe donné à partir de la liste d’adjacence.

```c
/// Ex4.5 Liste_FS
FileSucc Liste_FS(ListeAdj la) {
    int n = la.nbSom;
    int p = 0;
    Liste l;

    //计算总弧数
    for (int s = 0; s < n; s++) {
        l = la.tabAdj[s];
        while (l != NULL) {
            p++;
            l = l->suiv;
        }
    }

    FileSucc fs = allocSFS(n, p);
    int iaps = 0;

    for (int s = 0; s < n; s++) {
        fs.APS[s] = iaps;
        l = la.tabAdj[s];
        while (l != NULL) {
            fs.FS[iaps - 1] = l->somSucc;
            iaps++;
            l = l->suiv;
        }
    }
    fs.APS[n] = p + 1;
    return fs;
}
```

### Adj_Inc (oriente)

Ecrire en langage algorithmique (ou en langage C), le passage d’un graphe orienté `G=(S,A)` représenté par sa une matrice d’adjacence à une autre représentation par une matrice d’incidence.

```c
/// Ex4.6 Adj_Inc(oriente)
/// 邻接矩阵转关联矩阵（无自环）
//创建关联矩阵
MatInc allocMatInc(int n, int p) {
    MatInc mi;
    mi.nbSom = n;
    mi.nbArc = p;
    //为矩阵分配内存
    mi.mat = malloc(n * sizeof(int *));
    if (mi.mat == NULL) {
        printf("Problem de memoire!");
        exit(1);
    }
    //为每行分配内存
    for (int i = 0; i < n; i++) {
        mi.mat[i] = malloc(p * sizeof(int));
        if (mi.mat[i] == NULL) {
            printf("Problem de memoire!");
            exit(1);
        }
    }
    //初始化矩阵为0
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p; j++) {
            mi.mat[i][j] = 0;
        }
    }

    return mi;
}


MatInc Ajd_Inc(MatAdj ma) {
    int n = ma.nbSom;
    int p = 0;
    //计算边的数量
    for (int s = 0; s < n; s++) {
        for (int t = 0; t < n; t++) {
            if (ma.mat[s][t] == 1) {
                p++;
            }
        }
    }

    MatInc mi = allocMatInc(n, p);
    int a = 0; //边的计数器(a1,a2,a3...)
    for (int s = 0; s < n; s++) {
        for (int t = 0; t < n; t++) {
            if (ma.mat[s][t] == 1) {
                mi.mat[s][a] = 1; //边的起点标记为1
                mi.mat[t][a] = -1; //边的终点标记为-1
                a++;
            }
        }
    }
    return mi;
}
```

### Inc_Adj（oriente）

Ecrire en langage algorithmique (ou en langage C), le passage d’un graphe orienté `G=(S,A)` représenté par sa une matrice d’incidence à une autre représentation par une matrice d’adjacente.

```c
/// 4.7 Inc_Adj（oriente）
/// 关联矩阵转邻接矩阵（有向图，无自环）
//创建邻接矩阵
MatAdj allocMatAdj(int n) {
    MatAdj ma;
    ma.nbSom = n;

    //为矩阵分配内存
    ma.mat = malloc(n * sizeof(int *));
    if (ma.mat == NULL) {
        printf("Problem de memoire!");
        exit(1);
    }

    //给每行分配内存
    for (int i = 0; i < n; i++) {
        ma.mat[i] = malloc(n * sizeof(int));
        if (ma.mat[i] == NULL) {
            printf("Problem de memoire!");
            exit(1);
        }
    }

    //初始化矩阵为0
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ma.mat[i][j] = 0;
        }
    }

    return ma;
}

//转换函数
MatAdj Inc_Adj(MatInc mi) {
    int n = mi.nbSom;
    int p = mi.nbArc;

    MatAdj ma = allocMatAdj(n);

    for (int a = 0; a < p; a++) {
        int s = -1, t = -1, u = 0; //s起点，t终点，u临时顶点
        //还没找到起点或终点时继续
        while (s == -1 || t == -1) {
            if (mi.mat[u][a] == 1) {
                //如果有u到a的边（1）
                s = u; //则是起点
            }
            if (mi.mat[u][a] == -1) {
                //如果有a到u的边（-1）
                t = u; //则是终点
            }
            u++;
        }
        ma.mat[s][t] = 1; //在邻接矩阵中记录这条边
    }
    return ma;
}
```

### Inc_Adj（non oriente）

Ecrire en langage algorithmique (ou en langage C), le passage d’un graphe non orienté `G=(S, A)` représenté par sa une matrice d’incidence à une autre représentation par une matrice d’adjacente.

```c
/// 4.8 Inc_Adj（non oriente）
// 无向图，关联转邻接（无自环）
MatAdj Inc_Adj_NonOriente(MatInc mi) {
    int n = mi.nbSom;
    int p = mi.nbArc;

    MatAdj ma = allocMatAdj(n);

    for (int a = 0; a < p; a++) {
        int s = -1, t = -1, u = 0;
        while (s == -1 || t == -1) {
            if (mi.mat[u][a] == 1) {
                if (s == -1) {
                    s = u; // 记录第一个顶点
                } else {
                    t = u; // 记录第二个顶点
                }
            }
            u++;
        }
        ma.mat[s][t] = 1;
        ma.mat[t][s] = 1; // 无向图需要对称存储
    }
    return ma;
}
```

### 测试函数

```c
#include "Ex4.h"
#include "../PrintFree.h"

// **测试代码**
int main() {

    // int n = 3;
    int n = 4;
    MatAdj ma;
    ma.nbSom = n;
    ma.mat = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        ma.mat[i] = (int *)malloc(n * sizeof(int));
    }

    // 初始化矩阵（有向图带自环）
    // int adj[3][3] = {
    //     {1, 0, 1},
    //     {1, 0, 1},
    //     {1, 1, 0}
    // };


    // 初始化矩阵（有向图不带自环）
    // int adj[3][3] = {
    //     {0, 0, 1},
    //     {1, 0, 1},
    //     {1, 1, 0}
    // };


    // 初始化矩阵（有向图不带自环）
    int adj[4][4] = {
        {0, 1, 1, 0},
        {1, 0, 1, 1},
        {1, 1, 0, 1},
        {0, 1, 1, 0}
    };

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ma.mat[i][j] = adj[i][j];
        }
    }


    /// Ex4.1 Mat_ListeAdj 转换为邻接列表
    ListeAdj la = Mat_Liste(ma);
    printListeAdj(la);

    printf("-----------------------------------------------\n");

    ///Ex4.2 Mat_FS 转换为FileSucc
    FileSucc fs=Mat_FS(ma);
    printFileSucce(fs);

    printf("-----------------------------------------------\n");

    //Ex4.3 Mat_LASP 转换为前序后继链表
    ListeAdjSuccPred lasp=Mat_LASP(ma);
    printLASP(lasp);

    printf("-----------------------------------------------\n");

    //Ex4.4 FS_Liste 后继队列转链表
    ListeAdj la2=FS_Liste(fs);
    printListeAdj(la2);

    printf("-----------------------------------------------\n");

    //Ex4.5 链表转队列
    FileSucc fs2=Liste_FS(la);
    printFileSucce(fs2);

    printf("-----------------------------------------------\n");

    //Ex4.6 邻接矩阵转关联矩阵（有向图）
    printMatAdj(ma);
    MatInc inc=Ajd_Inc(ma);
    printMatInc(inc);

    printf("-----------------------------------------------\n");

    //Ex4.7 关联矩阵转邻接矩阵（有向图）
    printMatInc(inc);
    MatAdj ma2=Inc_Adj(inc);
    printMatAdj(ma2);

    printf("-----------------------------------------------\n");

    //Ex4.8 测试Inc转Adj（无向图）
    printMatInc(inc);
    MatAdj ma3=Inc_Adj_NonOriente(inc);
    printMatAdj(ma3);


    // 释放la内存
    freeListeAdj(la);

    //释放fs内存
    free(fs.APS);
    free(fs.FS);

    //释放Mat内存
    freeMatAdj(ma);
    return 0;
}
```

```
//resultats
Sommet 1 : 2 -> 3 -> NULL
Sommet 2 : 1 -> 3 -> 4 -> NULL
Sommet 3 : 1 -> 2 -> 4 -> NULL

Sommet 4 : 2 -> 3 -> NULL
-----------------------------------------------

nbSom: 4
nbArcs: 10
APS: 1 3 6 9 11 

FS: 2 3 1 3 4 1 2 4 2 3 
-----------------------------------------------

Nombre de sommets: 4
Sommet 1:
  Successeurs: 2 3 
  Predecesseurs: 2 3 
Sommet 2:
  Successeurs: 1 3 4 
  Predecesseurs: 1 3 4 
Sommet 3:
  Successeurs: 1 2 4 
  Predecesseurs: 1 2 4 
Sommet 4:
  Successeurs: 2 3 

  Predecesseurs: 2 3 
-----------------------------------------------

Sommet 1 : 2 -> 3 -> NULL
Sommet 2 : 1 -> 3 -> 4 -> NULL
Sommet 3 : 1 -> 2 -> 4 -> NULL

Sommet 4 : 2 -> 3 -> NULL
-----------------------------------------------

nbSom: 4
nbArcs: 10
APS: 0 2 5 8 11 

FS: 3 1 3 4 1 2 4 2 3 0 
-----------------------------------------------

Matrice d'adjacence :
0 1 1 0 
1 0 1 1 
1 1 0 1 
0 1 1 0 
Matrice d'incidence :
1 1 -1 0 0 -1 0 0 0 0 
-1 0 1 1 1 0 -1 0 -1 0 
0 -1 0 -1 0 1 1 1 0 -1 

0 0 0 0 -1 0 0 -1 1 1 
-----------------------------------------------

Matrice d'incidence :
1 1 -1 0 0 -1 0 0 0 0 
-1 0 1 1 1 0 -1 0 -1 0 
0 -1 0 -1 0 1 1 1 0 -1 
0 0 0 0 -1 0 0 -1 1 1 
Matrice d'adjacence :
0 1 1 0 
1 0 1 1 
1 1 0 1 

0 1 1 0 
-----------------------------------------------

Matrice d'incidence :
1 1 -1 0 0 -1 0 0 0 0 
-1 0 1 1 1 0 -1 0 -1 0 
0 -1 0 -1 0 1 1 1 0 -1 
0 0 0 0 -1 0 0 -1 1 1 
```

