//
// Created by 金卓远 on 25-3-5.
//

#ifndef INCIDENCE_H
#define INCIDENCE_H
#include"../structGraphe.h"
#include<stdlib.h>

// 从 MatInc 转换为 MatIncidLigLig(对于有向图）
MatIncidLigLig MatInc_MatIncidLigLig(MatInc matInc) {
    int nbSom = matInc.nbSom;
    int nbArc = matInc.nbArc;

    MatIncidLigLig result;
    result.nbSom = nbSom;
    result.nbArcs = nbArc;
    result.FS = (int *) malloc((nbArc) * sizeof(int)); // FS 的大小为 nbArc
    result.APS = (int *) malloc((nbSom + 1) * sizeof(int)); // APS 大小为 nbSom + 1
    result.AS = (int *) malloc(nbArc * sizeof(int)); // AS 大小为 nbArc

    int fsIndex = 0; // FS 索引

    for (int i = 0; i < nbSom; i++) {
        result.APS[i] = fsIndex + 1; // 记录当前顶点的 FS 开始索引

        for (int j = 0; j < nbArc; j++) {
            if (matInc.mat[i][j] == -1) {
                // 顶点 i 是起点
                for (int k = 0; k < nbSom; k++) {
                    if (matInc.mat[k][j] == 1) {
                        // k 是终点
                        result.FS[fsIndex] = j + 1; // 存储边的编号（从 1 开始）
                        result.AS[fsIndex] = k + 1; // 存终点（从 1 开始）
                        fsIndex++;
                        break;
                    }
                }
            }
        }
    }
    result.APS[nbSom] = nbArc + 1;

    return result;
}


// 从 MatIncidLigLig 转换为 MatInc(对于有向图）
MatInc MatIncidLigLig_MatInc(MatIncidLigLig matLig) {
    int nbSom = matLig.nbSom;
    int nbArc = matLig.nbArcs;

    // 分配 MatInc 结构
    MatInc matInc;
    matInc.nbSom = nbSom;
    matInc.nbArc = nbArc;

    // 分配关联矩阵
    matInc.mat = (int **)malloc(nbSom * sizeof(int *));
    for (int i = 0; i < nbSom; i++) {
        matInc.mat[i] = (int *)calloc(nbArc, sizeof(int)); // 初始化为 0
    }

    // 遍历 APS 和 FS 填充 mat
    for (int i = 0; i < nbSom; i++) {
        int startIdx = matLig.APS[i] - 1;    // 该顶点的起始索引（APS 是 1-based）
        int endIdx = matLig.APS[i + 1] - 1;  // 下一个顶点的起始索引

        for (int j = startIdx; j < endIdx; j++) {
            int edgeIdx = matLig.FS[j] - 1;  // 边编号（1-based 转换为 0-based）
            int endVertex = matLig.AS[j] - 1; // 终点编号（1-based 转换为 0-based）

            matInc.mat[i][edgeIdx] = -1;  // 起点标记 -1
            matInc.mat[endVertex][edgeIdx] = 1; // 终点标记 1
        }
    }

    return matInc;
}


//对于无向图的转换
MatIncidLigLig MatInc_MatIncidLigLig_Undirected(MatInc matInc) {
    int nbSom = matInc.nbSom;
    int nbArc = matInc.nbArc;

    MatIncidLigLig result;
    result.nbSom = nbSom;
    result.nbArcs = nbArc;
    result.FS = (int *)malloc(nbArc * 2 * sizeof(int)); // 无向图，每条边存两次
    result.APS = (int *)malloc((nbSom + 1) * sizeof(int));
    result.AS = (int *)malloc(nbArc * 2 * sizeof(int));

    int fsIndex = 0;

    for (int i = 0; i < nbSom; i++) {
        result.APS[i] = fsIndex + 1;

        for (int j = 0; j < nbArc; j++) {
            if (matInc.mat[i][j] == 1) {
                // 找到另一端的顶点
                for (int k = i + 1; k < nbSom; k++) { // 只向前搜索，避免重复
                    if (matInc.mat[k][j] == 1) {
                        // 添加两次 (因为无向边)
                        result.FS[fsIndex] = j + 1;
                        result.AS[fsIndex] = k + 1;
                        fsIndex++;

                        result.FS[fsIndex] = j + 1;
                        result.AS[fsIndex] = i + 1;
                        fsIndex++;
                        break;
                    }
                }
            }
        }
    }
    result.APS[nbSom] = fsIndex + 1;

    return result;
}


MatInc MatIncidLigLig_MatInc_NonOriente(MatIncidLigLig matLig) {
    int nbSom = matLig.nbSom;
    int nbArc = matLig.nbArcs;

    MatInc matInc;
    matInc.nbSom = nbSom;
    matInc.nbArc = nbArc;
    matInc.mat = (int **)malloc(nbSom * sizeof(int *));
    for (int i = 0; i < nbSom; i++) {
        matInc.mat[i] = (int *)calloc(nbArc, sizeof(int));
    }

    for (int i = 0; i < nbSom; i++) {
        int startIdx = matLig.APS[i] - 1;
        int endIdx = matLig.APS[i + 1] - 1;

        for (int j = startIdx; j < endIdx; j++) {
            int edgeIdx = matLig.FS[j] - 1;
            int endVertex = matLig.AS[j] - 1;

            matInc.mat[i][edgeIdx] = 1;
            matInc.mat[endVertex][edgeIdx] = 1; // 由于是无向图，反向也标记
        }
    }

    return matInc;
}
#endif //INCIDENCE_H
