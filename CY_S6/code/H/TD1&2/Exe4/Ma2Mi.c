//Exe4.6 - 邻接矩阵转关联矩阵的实现
#include <stdio.h>
#include <stdlib.h>
#include "StructGraphe.h"

// 创建n×p的关联矩阵（n个顶点，p条边）
MatriceIncid createMatriceIncid(int n,int p){
    MatriceIncid mi;
    int i,j;
    mi.nbArc=p;    // 设置边数
    mi.nbSom=n;    // 设置顶点数
    
    // 为矩阵分配行内存
    mi.mat=(int**)malloc(n*sizeof(int*));
    if(mi.mat==NULL){
        printf("eurro1!");
        exit(1);
    }
    
    // 为每行分配列内存
    for(i=0;i<n;i++){
        mi.mat[i]=(int*)malloc(p*sizeof(int));
        if(mi.mat[i]==NULL){
            printf("eurro2!");
            exit(1);
        }
    }
    
    // 初始化矩阵为0
    for(i=0;i<n;i++){
        for(j=0;j<p;j++){
            mi.mat[i][j]=0;
        }
    }
    return mi;
}

// 将邻接矩阵转换为关联矩阵
MatriceIncid Ma2Mi(MatriceAdj ma){
    int n=ma.nbsom;
    int s,t;
    int p=0;
    
    // 计算图中边的数量
    for(s=0;s<n;s++){
        for(t=0;t<n;t++){
            if(ma.mat[s][t]==1){
                p++;
            }
        }
    }
    
    // 创建关联矩阵
    MatriceIncid mi=createMatriceIncid(n,p);
    int a=0;    // 边的计数器
    
    // 遍历邻接矩阵，构建关联矩阵
    for(s=0;s<n;s++){
        for(t=0;t<n;t++){
            if(ma.mat[s][t]==1){
                mi.mat[s][a]=1;     // 边的起点标记为1
                mi.mat[t][a]=-1;    // 边的终点标记为-1
                a++;
            }
        }
    }
    return mi;
}

// 打印邻接矩阵
void printMatriceAdj(MatriceAdj ma) {
    for (int i = 0; i < ma.nbsom; i++) {
        for (int j = 0; j < ma.nbsom; j++) {
            printf("%d ", ma.mat[i][j]);
        }
        printf("\n");
    }
}

// 打印关联矩阵
void printMatriceIncid(MatriceIncid mi) {
    printf("Matrix Incidence:\n");
    for (int i = 0; i < mi.nbArc; i++) {
        for (int j = 0; j < mi.nbSom; j++) {
            printf("%d ", mi.mat[j][i]);
        }
        printf("\n");
    }
}

// 主函数：测试邻接矩阵到关联矩阵的转换
int main() {
    // 创建邻接矩阵（一个简单的有向图）
    MatriceAdj ma;
    ma.nbsom = 4;  // 图有4个节点
    
    // 分配内存并初始化邻接矩阵
    ma.mat = (int**)malloc(ma.nbsom * sizeof(int*));
    for (int i = 0; i < ma.nbsom; i++) {
        ma.mat[i] = (int*)malloc(ma.nbsom * sizeof(int));
    }

    // 初始化邻接矩阵：添加测试边
    // 图的边：0 -> 1, 1 -> 2, 2 -> 3
    ma.mat[0][1] = 1;  // 0 -> 1
    ma.mat[1][2] = 1;  // 1 -> 2
    ma.mat[2][3] = 1;  // 2 -> 3

    // 打印原始邻接矩阵
    printf("Adjacency Matrix (MatriceAdj):\n");
    printMatriceAdj(ma);

    // 转换为关联矩阵并打印结果
    MatriceIncid mi = Ma2Mi(ma);
    printf("\nConverted Incidence Matrix (MatriceIncid):\n");
    printMatriceIncid(mi);

    // 释放内存
    for (int i = 0; i < ma.nbsom; i++) {
        free(ma.mat[i]);
    }
    free(ma.mat);

    for (int i = 0; i < mi.nbSom; i++) {
        free(mi.mat[i]);
    }
    free(mi.mat);

    return 0;
}