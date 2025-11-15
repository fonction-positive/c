---
title: "Graphe_Matrices"
date: 2025-02-22 16:16:00
tags:
  - Algo
  - Graphe
  - CY
categories:
  - Algo
cover: /images/cover/CY.jpg
description: 记录一下CY课程之Graphe，内容仅代表老师教授内容
swiper_index: 5
---

# Matrices associées à un graph

## Matrice d‘incidence（关联矩阵）

### Matrice d’incidence sommets-Arcs（有向图）

#### 定义(顶点-弧的关联矩阵)

在图论中，关联矩阵（Matrice d’incidence） 是一种描述图中顶点与边（或弧）之间关系的矩阵。定义：

顶点-弧关联矩阵是一个矩阵，用于表示图中每个顶点与每个弧之间的关系。对于一个有向图或无向图的每个弧，矩阵中包含表示该弧和顶点之间的关联信息。

假设图有  n  个顶点和  m  条弧（边），则顶点-弧关联矩阵是一个  n \times m  的矩阵，其中：

- 每一行代表一个顶点（1,2,3,4）
- 每一列代表一个弧（或边）(a1,a2,a3...)

<img src="./img/matrice/截屏2025-02-22%2014.09.06.png" alt="截屏2025-02-22 14.09.06" style="zoom:50%;" />

#### 结构：

```c
typedef struct {
    int nbSom; //顶点数量（矩阵行数）
    int nbAcs; //弧数量（矩阵列数）
    int **mat; //二维数组用于存矩阵数据（-1，,0，1）
    //TCout **cout; //二维数组用于储存权重数据
}MatIncidente;
```



### Matrice d’incidence sommets-Arêtes（无向图）

无向图的顶点和边的关联矩阵

<img src="./img/matrice/截屏2025-02-22%2014.20.31.png" alt="截屏2025-02-22 14.20.31" style="zoom:50%;" />

```c
typedef struct {
    int nbSom; //顶点数量（矩阵行数）
    int nbAcs; //弧数量（矩阵列数）
    int **mat; //二维数组用于存矩阵数据（0，1）
    //TCout **cout; //二维数组用于储存权重数据
}MatIncidente;
```



### sous forme condensée de la matrice d’incidence（关联矩阵的子表示形式）

#### a) colonne par colonne

On utilise deux tableaux `α[]` et `β[]` de dimension `p=|A|` donnant pour chaque arc ou arête `a=1..p` les numéros `α[a]` et `β[a]` des extrémités.
si `G` est orienté alors
`α[a]` est l’origine de a （`α[a]`存弧`a`的起点）
`β[a]` est l’extrémité de a（`β[a]`存弧`a`的终点）

- 对于有向图

```c
//示例图
    1 → 2
    ↓   ↓
    3 → 4
    
//关联矩阵
    e1  e2  e3  e4
1    1   1   0   0
2    1   0   1   0
3    0   1   0   1
4    0   0   1   1

//储存
α = [1, 1, 2, 3]  // 每条边的起点
β = [2, 3, 4, 4]  // 每条边的终点
```

- 对于无向图

![截屏2025-02-22 20.48.46](img/matrice/%E6%88%AA%E5%B1%8F2025-02-22%2020.48.46.png)

```c
α = [1, 1, 2, 2, 3]  // 每条边的起点
β = [2, 3, 3, 4, 4]  // 每条边的终点
```



```c
typedef struct{
// TGraphe indicateur;
int nbSom ;
int nbArcs ; // int nbAretes
int *alpha ;
int *beta ;
//TCout *Cout ;
} MatIncidColCol ;
```



#### b) ligne par ligne

- 有向图（Graphe orienté）

  对于每个顶点 `s`：存储 `w⁺(s)`，即以 `s` 为起点的所有弧（即出边）。

  形式为：
  ```
  w⁺(s) = { a | a = (s, t) ∈ A(G) }
  ```

  例如，若 `s = 1` 有两条出边 `(1, 2)` 和 `(1, 3)`，那么：
  ```
  w⁺(1) = { a₁, a₂ }
  ```

- 无向图（Graphe non-orienté）

  对于每个顶点 `s`：存储 `w(s)`，即与 `s` 相关的所有边（即无向边）。

  形式为：
  ```
  w(s) = { a | a = {s, t} ∈ A(G) }
  ```

  例如，若 `s = 2` 有两条关联边 `{1,2}` 和 `{2,3}`，那么：
  ```
  w(2) = { a₁, a₃ }
  ```

为了存储图的邻接信息，我们使用以下 3 个数组：

1. APS（Adresse Premier Successeur）

   - 记录每个顶点的第一条边在 `FS` 数组中的索引。

   - 类似于邻接表的起始索引。

   - 需要引入**虚拟顶点** `n+1`，其索引指向 `FS` 的终点，便于计算索引范围。

2. FS（File des Successeurs）

   - 按顺序存储所有**边（或弧）**的索引。

   - 该数组实际上是一个**压缩后的邻接列表**，但存储的是**边的索引**，而不是顶点。

3. AS（Adresses des Sommets）

   - 存储 `FS` 数组中**每条边的终点**（即目标顶点）。

   - **对于有向图**，`AS[i]` 存储弧的终点 `t`。
   - **对于无向图**，`AS[i]` 存储边的**另一个端点**。

<img src="img/matrice/%E6%88%AA%E5%B1%8F2025-02-22%2021.14.45.png" alt="截屏2025-02-22 21.14.45" style="zoom:50%;" />

<img src="img/matrice/%E6%88%AA%E5%B1%8F2025-02-22%2021.15.05.png" alt="截屏2025-02-22 21.15.05" style="zoom:50%;" />



```c
typedef struct{
int nbSom ;
int nbArcs ;
int *FS ;  //按顺序存所有边（弧）
int *APS ;  //存每个顶点第一条边在FS中的索引
int *AS ;  //存每条边（弧）的终点
//TCout *Cout ;
} MatIncidLigLig ;
```



#### c) Listes d’incidences

- 有向图

<img src="img/matrice/%E6%88%AA%E5%B1%8F2025-02-22%2021.20.12.png" alt="截屏2025-02-22 21.20.12" style="zoom:50%;" />

- 无向图

<img src="img/matrice/%E6%88%AA%E5%B1%8F2025-02-22%2013.01.44.png" alt="截屏2025-02-22 21.20.40" style="zoom:50%;" />

## Matrices d’adjacence A（邻接矩阵）

### 1. 邻接矩阵的定义

假设图中有  n  个顶点  `S = {v1, v2, …, vn}` ，则邻接矩阵是一个  `n * n`  的矩阵，矩阵中的元素  `A[i][j]`  表示顶点  `vi`  和顶点  `vj`  之间是否有边连接。

- 对于无向图，如果有边  `(vi, vj)` ，则 ` A[i][j] = 1` ，否则 `A[i][j] = 0`。
- 对于有向图，如果有弧从  `vi`  指向  `vj` ，则  `A[i][j] = 1` ，否则  `A[i][j] = 0 `。
- 如果图包含自环（即一个顶点与自己相连），则在矩阵的对角线上  `A[i][i] = 1` 。
- 有向图

<img src="./img/matrice/截屏2025-02-22%2014.27.38.png" alt="截屏2025-02-22 14.27.38" style="zoom:50%;" />

- 无向图

<img src="./img/matrice/截屏2025-02-22%2014.28.23.png" alt="截屏2025-02-22 14.28.23" style="zoom:50%;" />

```c
///Matrices d’adjacence A (邻接矩阵，表述顶点和顶点之间关系）
typedef struct {
    int nbSom;  //顶点数量
    int **mat;  //二维数组用于储存矩阵数据
    //TCout **cout;
}MatAdjacence;
```



### 2. Représentations des graphes（关联矩阵 VS 邻接矩阵）

图的表示方法：

- 邻接矩阵（Matrice d’adjacence）或其派生形式：
  这种表示方法侧重于图是由一组顶点组成的。它适用于顶点集合固定不变的图（即图中的顶点不发生变化）。这种方法通过矩阵的形式表示顶点之间的连接关系，通常用于存储和处理稠密图（即边多的图）。
- 关联矩阵（Matrice d’incidence）或其派生形式：
  这种表示方法侧重于图是由一组边（或弧）组成的。与邻接矩阵不同，关联矩阵通过矩阵表示图中的边及其与顶点的关联。它更适用于边集合固定不变的图，并且通常用于存储和处理稀疏图（即边少的图）。

总结：

- 邻接矩阵强调图的顶点，适合顶点数量固定的图。
- 关联矩阵强调图的边（或弧），适合边数量固定的图。

### 3. sous forme condensée de la matrice d’adjacence（邻接矩阵的子表示形式）

#### a) 后继列（File des successeurs）

<img src="img/matrice/截屏2025-02-22%2014.57.23.png" alt="截屏2025-02-22 14.57.23" style="zoom:50%;" />

`FS = File des successeurs`
	est un tableau linéaire contenant successivement les listes non
`APS = Adresse (=indice) du premier successeur`
	Tableau linéaire indicé par les numéros des sommets

FS：后继队列，存放所有非空的后继列表`T(1), T(2), T(3)...`(就是按顺序存每个顶点的后继节点列表)

APS：后继地址表，`APS[s]`表示顶点`s`第一个后继在FS中的位置

虚拟顶点：为了简化计算和管理，引入一个虚拟顶点`s = p + 1`,在后续操作时`APS[n+1]`会被设定为一个特定值`p + 1`来帮助简化计算（处理边界问题等）

```c
///后继队列
typedef struct {
    int nbSom;
    int nbArcs;
    int *FS; //一维数组，存储所有非空的后继列表
    int *APS; //一维数组，长度为  n+1 （包括虚拟顶点  n+1 ），存储每个顶点后继在FS中的起始索引
    // TCout *cout; //权重
}FileSucc;
```



#### b) 邻接列表（Listes d’adjacence）

在邻接列表中，每个顶点都有一个对应的列表，列表中包含该顶点所有相邻的顶点（即与该顶点有边相连的顶点）。

- 对于无向图，每条边会在两个顶点的列表中都出现
- 对于有向图，边只会出现在起点的列表中

<img src="./img/matrice/截屏2025-02-22%2015.11.37.png" alt="截屏2025-02-22 15.11.37" style="zoom:50%;" />

<img src="./img/matrice/截屏2025-02-22%2015.15.21.png" alt="截屏2025-02-22 15.15.21" style="zoom:50%;" />

```c
///邻接列表
//每个顶点的链表
typedef struct cellule{
    int somSucc ;   
    //TCout cout ;
    struct cellule *suiv ;  
} *Liste ;

//邻接列表
typedef struct{
    int nbSom ;  //顶点数量
    Liste *tabAdj ;  //顶点数组
} ListAdjacence ;
```



#### c) 后继和前驱的列表数组（Tableau de listes successeurs et prédécesseurs）

<img src="./img/matrice/截屏2025-02-22%2015.23.08.png" alt="截屏2025-02-22 15.23.08" style="zoom:50%;" />

```c 
//后继和前驱的列表
typedef struct celluleAdj {
    int somAdj;  //存储当前节点（即某个顶点）的一个相邻顶点的编号
    struct celluleAdj *suivAdj;  //指向下一个相邻顶点
}*Liste;

typedef struct {
    Liste lSucc;  //Liste de successeurs
    Liste lPred;  //Liste de Predecesseurs
}ListeSuccPred;

typedef struct {
    int nbSom;  //图中顶点的数量
    ListeSuccPred *tabAdjSP;  //存储每个顶点的后继和前驱列表
}ListeAdjSuccPred;
```



#### d) 主列表（Liste principale）

Les sommets du graphe sont associés en une liste linéaire appelée **liste**

**principale**.

Chaque sommet du graphe étant représenté dans cette liste par une

structure comportant 3 membres :

<img src="./img/matrice/%E6%88%AA%E5%B1%8F2025-02-22%2020.14.33.png" alt="截屏2025-02-22 20.14.33" style="zoom:50%;" />

- Nom du sommet（顶点名称）
- Un pointeur sur le sommet suivant（下一个顶点）
- Un pointeur sur la liste des successeurs de ce sommet.（顶点的后继列表）

Chaque successeur t de s est représenté par une structure comportant 3 membres :

- Un pointeur vers la structure `t` dans la liste principale
- La valeur de l’arc `(s, t)` dans le cas d’un graphe valué
- Pointeur vers le sommet suivant de cette liste de successeurs

<img src="./img/matrice/%E6%88%AA%E5%B1%8F2025-02-22%2020.17.39.png" alt="截屏2025-02-22 20.17.39" style="zoom:50%;" />

<img src="./img/matrice/%E6%88%AA%E5%B1%8F2025-02-22%2020.18.12.png" alt="截屏2025-02-22 20.18.12" style="zoom:50%;" />

#### e) 稀疏矩阵（Matrice creuse）

稀疏矩阵（Matrice creuse） 是指一个矩阵中大部分元素为零，或者非零元素所占的比例较低。通常，稀疏矩阵中的零元素非常多，因此我们不再存储这些零元素，而只存储非零元素。这样可以大大节省存储空间，并且提高计算效率。

稀疏矩阵的定义：

- 一个矩阵被称为稀疏矩阵，当矩阵中大部分元素为零，或者非零元素的比例较低。
- 在数学上，稀疏矩阵常见于大型数据结构中，例如图的邻接矩阵、有限元法的系数矩阵等。

稀疏矩阵的存储方式：

由于稀疏矩阵大多数元素为零，直接存储所有元素会浪费大量内存。因此，稀疏矩阵通常采用 指针表示法（Représentation dynamique par pointeur） 来存储，只保存非零元素及其位置。

1. 方法一（矩阵的数学表示）

   ```c
   typedef struct cellule {
       int numlig;        // 行号
       int numcol;       // 列号
       TCout cout;       // 存储矩阵元素的值
       struct cellule *ligSuiv;   // 指向同一行下一个元素的指针
       struct cellule *colSuiv;   // 指向同一列下一个元素的指针
   }* Liste;
   
   typedef struct matrice {
       int nblig;    // 行数
       int nbcol;    // 列数
       Liste *ligne;  // 每行的链表头指针
       Liste *colonne;  // 每列的链表头指针
   } MatriceCreuse;
   ```

   

2. 方法二（图的表示）

   ```c
   typedef struct cellule {
       int somSucc;       // 成功者（后继节点）
       int somPred;       // 前驱节点
       TCout cout;        // 存储边的权重或值
       struct cellule *succSuiv;  // 指向下一个成功者的指针
       struct cellule *predSuiv;  // 指向下一个前驱的指针
   }* Liste;
   
   typedef struct matrice {
       int nbSom;    // 顶点数（即图中的节点数）
       Liste *tabSucc;  // 每个节点的后继节点链表头指针
       Liste *tabPred;  // 每个节点的前驱节点链表头指针
   } MatriceCreuse;
   ```

   