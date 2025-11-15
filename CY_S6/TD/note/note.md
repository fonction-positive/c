



#### TD4

##### Ex1. 求G²
(1)matAdj
```
Algorithme CalculerG2
    Entrée : Une matrice d'adjacence A représentant un graphe G
    Sortie : Une matrice d'adjacence A^2 représentant le graphe G^2

    // 初始化 A^2 矩阵，所有元素设为 0
    Pour chaque paire de sommets (i, j) dans G
        A^2[i][j] ← 0 
    Fin Pour

    // 遍历所有顶点，检查是否存在通过一个中间顶点的路径
    Pour chaque sommet i variant de 1 à n
        Pour chaque sommet j de 1 à n
            Pour chaque sommet k de 1 à n
                // 如果从 i 到 k 和从 k 到 j 都有边，则 i 到 j 在 G^2 中有边
                Si A[i][k] == 1 et A[k][j] == 1
                    A^2[i][j] ← 1
                Fin Si
            Fin Pour
        Fin Pour
    Fin Pour

    // 返回计算得到的 A^2 矩阵
    Retourner la matrice A^2
Fin Algorithme

```
、、、
debut
    n<--nbSom(g)
    g2<--allocSMA
    Pour i variant de 1 a n faire
        pour variant de 1 a n faire
            u<--1
            tq u <= n et g.mat[s][u]*g.mat[u]
、、、

(2)ListeAdj
、、、
Algorithme CalculerG2_AdjList
    Entrée : Une liste d'adjacence adj représentant un graphe G
    Sortie : Une liste d'adjacence adj^2 représentant le graphe G^2

    // 初始化 adj^2 为一个空的邻接表
    Pour chaque sommet i dans G
        adj^2[i] ← Liste vide
    Fin Pour

    // 遍历每一对顶点 (i, j)，检查是否存在一个中间顶点 k
    Pour chaque sommet i dans G
        Pour chaque sommet j dans G
            Pour chaque sommet k dans G
                Si k est un voisin de i (dans adj[i]) et k est un voisin de j (dans adj[j])
                    Ajouter j à adj^2[i]
                Fin Si
            Fin Pour
        Fin Pour
    Fin Pour

    // 返回 adj^2（表示 G^2 的邻接表）
    Retourner adj^2
Fin Algorithme
、、、

、、、
Pour i variant de 1 a n faire
    le=initL()
    ls = iEmeElt(s,g) //g.tav[s]
    tq nm estvide(ls) faire
        u = somAdj(ls)
        ls = suivant(ls)
        lu = iEmeElt(u,g) //g.tab[u]
        tq nm estvide(lu) faire
            t = SumAdj(lu)
            lu = suivant(lu)
        ftq
    ftq
finpour
Retourner g 

、、、


##### TD1-Ex5
1) 每个sommet的degre总和是边或弧数量的两倍
2) 由此推导出一个图（无向或有向）有一个偶数个度数为奇数的顶点。
在无向图或有向图中，所有顶点的度数之和是偶数（如上所述，等于 2m，是偶数）。而所有度数为奇数的顶点的度数之和是奇数，因为奇数个奇数之和是奇数。
然而，图中所有度数之和是偶数，所以度数为奇数的顶点的个数必须是偶数。因此，图中必定有一个偶数个度数为奇数的顶点。
3) 对于有向图，情况与无向图类似，但需要分别考虑出度和入度。
有向图的顶点的出度和入度的总和是偶数。就像无向图一样，度数为奇数的顶点的个数必须是偶数。然而，在有向图中，出度和入度是分开的，因此度数为奇数的顶点可以是出度为奇数或入度为奇数。
在有向图中，每个顶点的出度和入度的总和必须是偶数，因此度数为奇数的顶点的个数依然是偶数。

##### Ex2
Soit G=(S, A) un graphe simple non orienté fini ayant n sommets (n>1).
1) Montrer que le degré d’un sommet est toujours strictement inférieur à n.
2) Montrer qu’il ne peut pas y avoir simultanément un sommet de degré 0 et un sommet de degré n-1.
3) En déduire qu’il y a au moins deux sommets de même degré.


设 \( G = (S, A) \) 是一个简单无向有限图，包含 \(n\) 个顶点（\(n > 1\)）。我们需要证明以下三点：

1) 证明一个顶点的度数总是严格小于 \(n\)。
2) 证明不可能同时存在一个度数为 0 的顶点和一个度数为 \(n - 1\) 的顶点。
3) 根据（a）和（b）的结果，推导出图中至少有两个顶点的度数相同。

###### 解释

1) 证明一个顶点的度数总是严格小于 \(n\)：
- **度数**是指一个顶点连接的边的数量。对于一个简单图（没有自环或多重边），每个顶点的度数是与它相连的其他顶点的数量。
- 在一个有 \(n\) 个顶点的图中，顶点的度数最大只能是 \(n - 1\)，因为它最多可以与除自己以外的 \(n - 1\) 个顶点相连。
- 但是，题目要求证明度数是严格小于 \(n\)，也就是说，顶点的度数不能等于 \(n\)。这是因为在简单无向图中，不可能存在一个顶点与所有其他顶点相连且没有自环的情况。
- 因此，一个顶点的度数总是小于 \(n\)。

2) 证明不可能同时存在一个度数为 0 的顶点和一个度数为 \(n - 1\) 的顶点：
- 假设存在一个度数为 0 的顶点 \(v_0\) 和一个度数为 \(n - 1\) 的顶点 \(v_1\)。
- 顶点 \(v_0\) 的度数为 0，意味着 \(v_0\) 没有任何边与其他顶点相连。
- 顶点 \(v_1\) 的度数为 \(n - 1\)，意味着 \(v_1\) 与图中所有其他顶点相连。
- 由于 \(v_1\) 与所有其他顶点相连，特别是与 \(v_0\) 相连，意味着 \(v_0\) 的度数应该至少为 1，矛盾于假设 \(v_0\) 的度数为 0。
- 因此，不可能同时存在度数为 0 的顶点和度数为 \(n - 1\) 的顶点。

3) 根据（a）和（b）的结果，推导出图中至少有两个顶点的度数相同：
- 根据（a），图中每个顶点的度数都小于 \(n\)，因此顶点的度数只能是 \(0\) 到 \(n - 1\) 之间的整数。
- 根据（b），我们知道不可能同时存在度数为 0 的顶点和度数为 \(n - 1\) 的顶点。
- 因此，度数的可能值被限制在 \(0, 1, 2, \dots, n - 2\) 之间，也就是说，图中有 \(n\) 个顶点，但只有 \(n - 1\) 种可能的度数值（从 0 到 \(n - 2\)）。
- 由于每个顶点的度数都是 \(0\) 到 \(n - 2\) 之间的一个整数，而有 \(n\) 个顶点，**根据鸽巢原理**（Pigeonhole Principle），至少有两个顶点的度数相同。

###### 答案总结

1) 图中每个顶点的度数总是严格小于 \(n\)，因为它最多只能与 \(n - 1\) 个其他顶点相连。
2) 不可能同时存在一个度数为 0 的顶点和一个度数为 \(n - 1\) 的顶点，因为它们之间会存在矛盾。
3) 由于图中有 \(n\) 个顶点，但度数只能取 \(0\) 到 \(n - 2\) 之间的值，所以根据鸽巢原理，至少有两个顶点的度数相同。


##### Ex3 
求最大度数plusguer


