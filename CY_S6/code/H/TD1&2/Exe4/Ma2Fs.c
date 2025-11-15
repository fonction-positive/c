#include <stdio.h>
#include <stdlib.h>
#include "StructGraphe.h"

//Exe4.2
FileSucce createFileSucce(int nbsom, int nbarc) {
    FileSucce fs;
    fs.nbSom = nbsom;
    fs.nbArcs = nbarc;

    // 分配内存
    fs.APS = (int*)malloc((nbsom + 1) * sizeof(int));
    if (fs.APS == NULL) {
        printf("Memory allocation failed for APS.\n");
        exit(1);  // 内存分配失败，退出程序
    }

    fs.FS = (int*)malloc(nbarc * sizeof(int));
    if (fs.FS == NULL) {
        printf("Memory allocation failed for FS.\n");
        free(fs.APS);  // 释放之前分配的内存
        exit(1);
    }

    return fs;
}

FileSucce Ma2Fs(MatriceAdj ma){
    int n=ma.nbsom;
    int p=0,s,t;
    for(s=0;s<n;s++){
        for(t=0;t<n;t++){
            if(ma.mat[s][t]==1){
                p++;
            }
        }
    }
    FileSucce fs=createFileSucce(n,p);
    int iAps=0;
    for(s=0;s<n;s++){
        fs.APS[s]=iAps;
        for(t=0;t<n;t++){
            if(ma.mat[s][t]==1){
                fs.FS[iAps]=t;
                iAps++;
            }
        }
    }
    fs.APS[n]=p;
    return fs;
}

// 打印 FileSucce
void printFileSucce(FileSucce fs) {
    printf("FileSucce (Adjacency List as File):\n");
    printf("Number of nodes: %d\n", fs.nbSom);
    printf("Number of arcs: %d\n", fs.nbArcs);
    printf("APS: ");
    for (int i = 0; i <= fs.nbSom; i++) {
        printf("%d ", fs.APS[i]);
    }
    printf("\nFS: ");
    for (int i = 0; i < fs.nbArcs; i++) {
        printf("%d ", fs.FS[i]);
    }
    printf("\n");
}

int main() {
    // 创建一个邻接矩阵
    int n = 5;  // 假设图有 5 个节点
    MatriceAdj ma;
    ma.nbsom = n;

    // 分配内存并初始化邻接矩阵
    ma.mat = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        ma.mat[i] = (int*)malloc(n * sizeof(int));
    }

    // 初始化邻接矩阵（有向图示例）
    // 0 -> 1, 1 -> 2, 2 -> 3, 3 -> 4, 4 -> 0
    ma.mat[0][1] = 1;
    ma.mat[1][2] = 1;
    ma.mat[2][3] = 1;
    ma.mat[3][4] = 1;
    ma.mat[4][0] = 1;

    // 转换为 FileSucce
    FileSucce fs = Ma2Fs(ma);

    // 打印 FileSucce 内容
    printFileSucce(fs);

    // 释放内存
    for (int i = 0; i < n; i++) {
        free(ma.mat[i]);
    }
    free(ma.mat);

    free(fs.APS);
    free(fs.FS);

    return 0;
}