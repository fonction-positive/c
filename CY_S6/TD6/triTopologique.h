//
// Created by 金卓远 on 25-3-3.
//

#ifndef TRITOPOLOGIQUE_H
#define TRITOPOLOGIQUE_H

#include"../TD3/file.h"
#include "../structGraphe.h"
#define Max 100




#include <stdio.h>
#include <stdlib.h>


// 初始化空集合，这里简单返回NULL，因为主要用于逻辑判断
void* InitEnsVide() {
    return NULL;
}

// 初始化队列，这里用简单数组模拟队列，返回队列指针
int* initFile() {
    return (int*)malloc(sizeof(int) * 100); // 假设最大队列长度100，可调整
}

// 获取图中顶点数量
int nbSom(MatAdj G) {
    return G.nbSom;
}

// 计算顶点的入度
int degreEntrant(int s, MatAdj G) {
    int i, count = 0;
    for (i = 0; i < G.nbSom; i++) {
        if (G.mat[i][s] != 0) {
            count++;
        }
    }
    return count;
}

// 向集合中插入元素，这里简单处理
void inser(int s, void* M) {
    // 这里可以根据集合的具体实现进行操作，目前只是简单处理
}

// 从集合中选择一个顶点，这里简单返回0
int choisirUnSommet(void* M) {
    return 0;
}

// 从集合中删除一个顶点，这里简单处理
void supprimer(int t, void* M) {
    // 这里可以根据集合的具体实现进行操作，目前只是简单处理
}

// 入队操作
void enfiler(int t, int* f) {
    // 简单数组模拟队列的入队操作，假设队列有足够空间
    static int rear = 0;
    f[rear++] = t;
}

// 判断集合是否为空，这里简单返回1表示空
int estVideEns(void* M) {
    return 1;
}

// 拓扑排序函数
int* triTopologique(MatAdj G) {
    // 获取图G中的顶点数量
    int n = nbSom(G);
    // 初始化一个空集合M，用于存储没有前驱节点的顶点，这里返回的是一个空指针，后续的集合操作需基于实际的数据结构来完善
    void* M = InitEnsVide();
    // 初始化一个队列F，这里用动态数组模拟队列，用于存储拓扑排序的结果
    int* F = initFile();
    // 动态分配一个长度为n的数组d，用于记录每个顶点的入度
    int *d = (int*)malloc(sizeof(int) * n);

    // 初始化阶段
    for (int s = 0; s < n; s++) {
        // 计算顶点s的入度 degré entrant（degré sortant出度）
        int de = degreEntrant(s, G);
        // 如果顶点s的入度为0，说明它没有前驱节点，将其插入到集合M中
        if (de == 0) {
            inser(s, M);
        }
        // 将顶点s的入度记录到数组d中
        d[s] = de;
    }

    // 处理阶段，构建队列F（即生成拓扑排序的结果）
    while (!estVideEns(M)) {
        // 从集合M中选择一个没有前驱节点的顶点t
        int t = choisirUnSommet(M);
        // 将顶点t从集合M中删除
        supprimer(t, M);
        // 将顶点t的入度标记为-1，表示该顶点已处理
        d[t] = -1;
        // 将顶点t入队到队列F中，F最终将存储拓扑排序的结果
        enfiler(t, F);

        // 更新数组d和集合M
        for (int u = 0; u < G.nbSom; u++) {
            // 如果存在从顶点t到顶点u的边
            if (G.mat[t][u] != 0) {
                // 顶点u的入度减1
                d[u]--;
                // 如果顶点u的入度变为0，说明它现在没有前驱节点了，将其插入到集合M中
                if (d[u] == 0) {
                    inser(u, M);
                }
            }
        }
    }

    // 返回存储拓扑排序结果的队列F
    return F;
}


/*
Fonction triTopologique(G) → Liste ordonnée de sommets de G
    G(S, A) : Graphe Acyclique
Début
    // Phase initialisation
    n ← nbSom(G)
    M← InitEnsVide() // Contient les sommets sans prédécesseurs
    F← initFile()
    Pour s variant de 1 à n faire
        de ← degreEntrant(s, G)
        si de=0 alors
            M ← inser(s, M)
        Fsi
        d[s] ← de
    fpour
    // Traitement = Construction de la File F
    Tant que non estVideEns(M) faire
        t ← choisirUnSommet(M)
        M ← supprimer(t, M)
        d[t]←-1
        f ← enfiler(t, f) //insert t ds une File (F) ou un tableau (F)
        // Mise à jour du tableau d et de l’Ens M
        Pour u ∈ Γ(t) faire
            d[u] ← d[u] – 1
            si d[u]=0 alors
                M ← inser(u, M)
            Fsi
        FinPour
    FinTq
    Renvoyer f
FIN
*/



#endif //TRITOPOLOGIQUE_H
