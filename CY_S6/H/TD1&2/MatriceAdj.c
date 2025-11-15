//Exe3.1 - 邻接矩阵的实现
#include <stdio.h>
#include <stdlib.h>
#include "StructGraphe.h"

// 函数声明
MatriceAdj creatMatriceAdj(int n);    // 创建邻接矩阵
int nbsom(MatriceAdj m);              // 获取顶点数量
int estBoucle(MatriceAdj m);          // 检查是否存在自环
void somSucce(int s,MatriceAdj m);    // 打印指定顶点的后继节点
void somPredce(int s,MatriceAdj m);   // 打印指定顶点的前驱节点
int MaxSomSucce(MatriceAdj m);        // 找出具有最多后继节点的顶点

// 创建n×n的邻接矩阵
MatriceAdj creatMatriceAdj(int n){
    MatriceAdj m;
    m.nbsom=n;    // 设置顶点数量
    int i=0;
    // 为矩阵分配行内存
    m.mat=(int**)malloc(n*sizeof(int*));
    if(m.mat==NULL){
        printf("Memory allocation failed");
        exit(1);
    }
    // 为每一行分配列内存
    for(i=0;i<n;i++){
        m.mat[i]=(int*)malloc(n*sizeof(int));
        if(m.mat[i]==NULL){
            printf("Memory allocation failed for ligne");
            exit(1);
        }
    }
    return m;
}

// 返回图中顶点的数量
int nbsom(MatriceAdj m){
    return m.nbsom;
}

// 检查图中是否存在自环（顶点到自身的边）
int estBoucle(MatriceAdj m){
    int s=0;
    int n=nbsom(m);
    int flag=0;    // 标记是否找到自环
    while(s<n && flag==0){
        if(m.mat[s][s]==1){    // 检查对角线元素
            flag=1;
        }
        s++;
    }
    return flag;
}

// 打印顶点s的所有后继节点
void somSucce(int s,MatriceAdj m){
    int i=0;
    int n=nbsom(m);
    printf("Les somme success de %d sont: \n",s);
    for(i=0;i<n;i++){
        if(m.mat[s][i]==1){    // 如果存在从s到i的边
            printf("%d ",i);
        }
    }
    printf("\n");
}

// 打印顶点s的所有前驱节点
void somPredce(int s,MatriceAdj m){
     int i=0;
    int n=nbsom(m);
    printf("Les somme predecesseurs de %d sont: \n",s);
    for(i=0;i<n;i++){
        if(m.mat[i][s]==1){    // 如果存在从i到s的边
            printf("%d ",i);
        }
    }
    printf("\n");
}

// 找出具有最多后继节点的顶点
int MaxSomSucce(MatriceAdj m){
    int MaxS=0;        // 存储最大后继节点数的顶点
    int MaxSucce=0;    // 最大后继节点数
    int SomSucce=0;    // 当前顶点的后继节点数
    int i=0,j=0;
    int n=nbsom(m);
    for(i=0;i<n;i++){
        SomSucce = 0;  // 重置计数器
        for(j=0;j<n;j++){
            if(m.mat[i][j]==1){
                SomSucce++;
            }
        }
        if(SomSucce>MaxSucce){
            MaxSucce=SomSucce;
            MaxS=i;
        }
    }
    return MaxS;
}

// 主函数：测试邻接矩阵的各项功能
int main(void){
    MatriceAdj m;
    int i=0,j=0,s=0;
    
    // 创建5×5的邻接矩阵
    m=creatMatriceAdj(5);
    
    // 初始化矩阵，所有元素置0
    for(i=0;i<5;i++){
        for(j=0;j<5;j++){
            m.mat[i][j]=0;
        }
    }
    
    // 添加测试边
    m.mat[2][3]=1;    // 添加边 2->3
    m.mat[1][2]=1;    // 添加边 1->2
    m.mat[2][4]=1;    // 添加边 2->4
    
    // 测试各项功能
    printf("EstBoucle? %d\n",estBoucle(m));    // 检查是否有自环
    s=MaxSomSucce(m);                          // 获取最大后继节点的顶点
    somSucce(s,m);                             // 打印该顶点的后继节点
    somPredce(s,m);                            // 打印该顶点的前驱节点
    
    return 0;
}