//
// Created by 金卓远 on 25-3-6.
//

#ifndef CIRCUIT_H
#define CIRCUIT_H

///判断Circuit（MatAdj、ListeAdj、FS)

#include <stdbool.h>
#include <stdlib.h>
#include "../structGraphe.h"

//检查图是否有循环（对于简单有向图)(判断图中是否存在入度为0的节点）
//MatAdj
bool hasCycle_MatAdj(MatAdj g) {
    int *inDegree = (int *)malloc(g.nbSom * sizeof(int)); // 存储每个节点的入度
    for (int i = 0; i < g.nbSom; i++) {
        inDegree[i] = 0; // 初始化入度为0
    }

    // 计算每个节点的入度
    for (int i = 0; i < g.nbSom; i++) {
        for (int j = 0; j < g.nbSom; j++) {
            if (g.mat[i][j] == 1) {
                inDegree[j]++; // 如果存在边 i -> j，增加节点 j 的入度
            }
        }
    }

    // 检查是否所有节点都有前驱（即入度都大于0）
    for (int i = 0; i < g.nbSom; i++) {
        if (inDegree[i] == 0) {
            free(inDegree);
            return false; // 如果存在入度为0的节点，说明没有环
        }
    }

    // 如果所有节点的入度都大于0，说明存在环
    free(inDegree);
    return true;
}


// ListeAdj
bool hasCycle_ListeAdj(ListeAdj g) {
    int *inDegree = (int *)malloc(g.nbSom * sizeof(int)); // 存储每个节点的入度
    for (int i = 0; i < g.nbSom; i++) {
        inDegree[i] = 0; // 初始化入度为0
    }

    // 计算每个节点的入度
    for (int i = 0; i < g.nbSom; i++) {
        Liste temp = g.tabAdj[i];
        while (temp != NULL) {
            inDegree[temp->somSucc-1]++; // 如果存在边 i -> temp->somSucc，增加节点 somSucc 的入度
            temp = temp->suiv;
        }
    }

    // 检查是否所有节点都有前驱（即入度都大于0）
    for (int i = 0; i < g.nbSom; i++) {
        if (inDegree[i] == 0) {
            free(inDegree);
            return false; // 如果存在入度为0的节点，说明没有环
        }
    }

    // 如果所有节点的入度都大于0，说明存在环
    free(inDegree);
    return true;
}



// FileSucc
bool hasCycle_FileSucc(FileSucc g) {
    int *inDegree = (int *)malloc(g.nbSom * sizeof(int)); // 存储每个节点的入度
    for (int i = 0; i < g.nbSom; i++) {
        inDegree[i] = 0; // 初始化入度为0
    }

    // 计算每个节点的入度
    for (int i = 0; i < g.nbSom; i++) {
        // 遍历当前节点的后继
        for (int j = g.APS[i]-1; j < g.APS[i + 1]-1; j++) {
            inDegree[g.FS[j]-1]++; // 如果存在边 i -> g.FS[j]，增加节点 g.FS[j] 的入度
        }
    }

    // 检查是否所有节点都有前驱（即入度都大于0）
    for (int i = 0; i < g.nbSom; i++) {
        if (inDegree[i] == 0) {
            free(inDegree);
            return false; // 如果存在入度为0的节点，说明没有环
        }
    }

    // 如果所有节点的入度都大于0，说明存在环
    free(inDegree);
    return true;
}
#endif //CIRCUIT_H
