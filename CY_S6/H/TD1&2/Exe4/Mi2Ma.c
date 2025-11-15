//Exe4.7 - 关联矩阵转邻接矩阵的实现
#include <stdio.h>
#include <stdlib.h>
#include "StructGraphe.h"

// 创建n×n的邻接矩阵
MatriceAdj createMatriceAdj(int n){
    MatriceAdj ma;
    ma.nbsom=n;    // 设置顶点数
    int i,j;
    
    // 为矩阵分配行内存
    ma.mat=(int**)malloc(n*sizeof(int*));
    if(ma.mat==NULL){
        printf("eurro1!");
        exit(1);
    }
    
    // 为每行分配列内存
    for(i=0;i<n;i++){
        ma.mat[i]=(int*)malloc(n*sizeof(int));
        if(ma.mat[i]==NULL){
            printf("eurro2!");
            exit(1);
        }
    }
    
    // 初始化矩阵为0
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            ma.mat[i][j]=0;
        }
    }
    return ma;
}

// 将关联矩阵转换为邻接矩阵
MatriceAdj Mi2Ma(MatriceIncid mi){
    int n=mi.nbSom;    // 顶点数
    int p=mi.nbArc;    // 边数
    MatriceAdj ma=createMatriceAdj(n);
    int a=0,s=0,t=0,u=0;
    
    // 遍历每条边
    for(a=0;a<p;a++){
        s=0;
        t=0;
        u=0;
        // 寻找边的起点和终点
        while (s*t==0){    // 当还未找到起点或终点时继续
            if(mi.mat[u][a]==1){     // 找到起点
                s=u;
            }
            if(mi.mat[u][a]==-1){    // 找到终点
                t=u;
            }
            u++;
        }
        ma.mat[s][t]=1;    // 在邻接矩阵中标记这条边
    }
    return ma;
}

// 主函数：测试关联矩阵到邻接矩阵的转换
int main() {
    // 创建测试用的关联矩阵
    MatriceIncid mi;
    mi.nbSom = 4;  // 4个顶点
    mi.nbArc = 4;  // 4条边
    
    // 分配内存
    mi.mat = (int**)malloc(4 * sizeof(int*));
    for (int i = 0; i < 4; i++) {
        mi.mat[i] = (int*)malloc(4 * sizeof(int));
    }

    // 初始化关联矩阵（示例：表示一个环形有向图）
    // 边1：0->1, 边2：1->2, 边3：2->3, 边4：3->0
    mi.mat[0][0] = 1;  mi.mat[0][1] = -1; mi.mat[0][2] = 0;  mi.mat[0][3] = 0;
    mi.mat[1][0] = -1; mi.mat[1][1] = 0;  mi.mat[1][2] = 1;  mi.mat[1][3] = 0;
    mi.mat[2][0] = 0;  mi.mat[2][1] = 1;  mi.mat[2][2] = 0;  mi.mat[2][3] = 0;
    mi.mat[3][0] = 0;  mi.mat[3][1] = 0;  mi.mat[3][2] = 0;  mi.mat[3][3] = 1;

    // 转换为邻接矩阵
    MatriceAdj ma = Mi2Ma(mi);

    // 打印结果
    printf("Adjacency Matrix:\n");
    for (int i = 0; i < ma.nbsom; i++) {
        for (int j = 0; j < ma.nbsom; j++) {
            printf("%d ", ma.mat[i][j]);
        }
        printf("\n");
    }

    // 释放内存
    for (int i = 0; i < mi.nbArc; i++) {
        free(mi.mat[i]);
    }
    free(mi.mat);

    for (int i = 0; i < ma.nbsom; i++) {
        free(ma.mat[i]);
    }
    free(ma.mat);

    return 0;
}