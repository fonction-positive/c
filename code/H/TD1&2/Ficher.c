#include <stdio.h>
#include <stdlib.h>
#include "StructGraphe.h"

MatriceAdj creatMatriceAdj(int n){
    MatriceAdj m;
    m.nbsom=n;
    int i=0;
    m.mat=(int**)malloc(n*sizeof(int*));
    if(m.mat==NULL){
        printf("Memory allocation failed");
        exit(1);
    }
    for(i=0;i<n;i++){
        m.mat[i]=(int*)malloc(n*sizeof(int));
        if(m.mat[i]==NULL){
            printf("Memory allocation failed for ligne");
            exit(1);
        }
    }
    return m;
}

MatriceAdj chargeurMA(char *nomG) {
    FILE *fo;
    int type, nbSom, nbArc, nbSucc, i, src, dest;
    MatriceAdj m;
    
    // 打开文件并检查
    fo = fopen(nomG, "r");
    if (fo == NULL) {
        printf("文件打开失败。\n");
        exit(1);
    }

    // 读取文件头部分
    fscanf(fo, "\n #Chageur MatAdj");
    fscanf(fo, "\n #oriende=1 , non oriende=2");
    fscanf(fo, "\n typeGraphe=%d", &type);
    fscanf(fo, "\n nbSome=%d", &nbSom);
    fscanf(fo, "\n nbArc=%d", &nbArc);
    
    // 初始化邻接矩阵
    m = creatMatriceAdj(nbSom);
    for (i = 0; i < nbSom; i++) {
        for (int j = 0; j < nbSom; j++) {
            m.mat[i][j] = 0;
        }
    }

    // 读取每个节点的后继节点
    for (i = 0; i < nbSom; i++) {
        fscanf(fo, "\n Sommet=%d nbSucc=%d Succ=", &src, &nbSucc);
        printf("Read Sommet=%d, nbSucc=%d\n", src, nbSucc);

        if (nbSucc > 0) {
            while (fscanf(fo, "%d", &dest) == 1) {
                printf("Read edge: %d -> %d\n", src, dest);
                if (type == 1) { // 有向图
                    m.mat[src - 1][dest - 1] = 1;
                } else { // 无向图
                    m.mat[src - 1][dest - 1] = 1;
                    m.mat[dest - 1][src - 1] = 1;
                }
                // 检查下一个字符是不是空格
                if (fgetc(fo) != ' ') {
                    break;
                }
            }
        }
    }
    
    fclose(fo);  // 确保文件关闭
    return m;
}


// 输出邻接矩阵
void afficherMatrice(MatriceAdj m) {
    printf("邻接矩阵：\n");
    for (int i = 0; i < m.nbsom; i++) {
        for (int j = 0; j < m.nbsom; j++) {
            printf("%d ", m.mat[i][j]);
        }
        printf("\n");
    }
}

int main(void){

    // 加载邻接矩阵
    MatriceAdj m = chargeurMA("Graphe.txt");

    // 输出邻接矩阵
    afficherMatrice(m);
    
    // 释放内存
    for (int i = 0; i < m.nbsom; i++) {
        free(m.mat[i]);
    }
    free(m.mat);
    return 0;
}
