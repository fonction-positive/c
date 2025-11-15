#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

typedef struct{
    int nbSom;
    int** mat;
}MatriceAdj;

MatriceAdj creatMatriceAdj(int n);
int nbsom(MatriceAdj m);
int * initTab(int n,int *tab);

MatriceAdj creatMatriceAdj(int n){
    MatriceAdj m;
    m.nbSom=n;
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

int * initTab(int n,int *tab){
    int i=0;
    for(i=0;i<n;i++){
        tab[i]=0;
    }
    return tab;
}

int nbsom(MatriceAdj m){
    return m.nbSom;
}

//Etap 1
// 广度优先遍历，记录每个节点的层级
int * parcourLargeur(MatriceAdj m) {
    int n = nbsom(m);
    int *viste = (int *)malloc(n * sizeof(int));  // 用于标记访问过的节点
    int *mangage = (int *)malloc(n * sizeof(int)); // 用于记录每个节点的层级（niveau）
    
    // 初始化访问标志数组和层级数组
    viste = initTab(n, viste);
    mangage = initTab(n, mangage);

    int nbSvisite = 0;  // 记录已访问节点的数量
    int s = 0;          // 起始节点
    Queue f = initf();  // 创建队列
    emfiler(&f, s);     // 将起始节点加入队列
    mangage[s] = 0;     // 起始节点的层级为0

    while (!estVide(&f) && nbSvisite < n) {
        s = defiler(&f);  // 从队列中取出一个节点
        if (viste[s] == 0) {  // 如果该节点未被访问
            viste[s] = 1;     // 标记该节点为已访问
            nbSvisite++;      // 已访问节点数量加1
            for (int t = 0; t < n; t++) {  // 遍历该节点的所有后继节点
                if (m.mat[s][t] == 1 && viste[t] == 0) {  // 如果 t 是 s 的后继且未访问
                    mangage[t] = mangage[s] + 1;  // 更新 t 的层级
                    emfiler(&f, t);  // 将 t 加入队列
                }
            }
        }
    }

    return mangage;  // 返回每个节点的层级
}

//Etap 2
void Separer(int *s1,int *s2,int * mangage,int n){
    int i=0,t=0,u=0;
    for(i=0;i<n;i++){
        if(mangage[i]%2==0){
            s1[t]=i;
            t++;
        }else{
            s2[u]=i;
            u++;
        }
    }
}

//Etap 3
int estLinaire(int *Sn, MatriceAdj g) {
    int flag = 0;
    int s = 0, t, j;

    // 遍历 Sn 数组，直到遇到结束标志 -1
    while (flag == 0 && Sn[s] != -1) {
        t = 0;

        // 遍历所有节点，寻找 Sn[s] 和 t 是否有边连接
        while (t < nbsom(g) && flag == 0) {
            if (g.mat[Sn[s]][t] == 1) {  // 如果 Sn[s] 和 t 有边连接
                // 检查 t 是否在 Sn 数组的后续部分
                for (j = s + 1; Sn[j] != -1; j++) {
                    if (Sn[j] == t) {
                        flag = 1;  // 如果找到了，标记为非线性
                        break;
                    }
                }
            }
            t++;
        }
        s++;
    }

    return flag;  // 0 表示线性，1 表示非线性
}


// 主函数
int main() {
    // 创建一个简单的图（邻接矩阵）
    int n = 4;  // 图中有6个节点
    MatriceAdj m = creatMatriceAdj(n);

    // 手动设置邻接矩阵（图）
    m.mat[0][1] = 1;
    m.mat[0][2] = 1;
    m.mat[1][3] = 1;
    m.mat[3][2] = 1;

    // 执行广度优先遍历
    int *mangage = parcourLargeur(m);
    printf("Nodes' levels (mangage):\n");
    for (int i = 0; i < n; i++) {
        printf("Node %d: Level %d\n", i, mangage[i]);
    }

    // 执行分离节点到两个集合
    int *s1 = (int *)malloc(n * sizeof(int));
    int *s2 = (int *)malloc(n * sizeof(int));
    Separer(s1, s2, mangage, n);
    printf("\nNodes in set 1 (even levels):\n");
    for (int i = 0; i < n; i++) {
        if (s1[i] != -1) {
            printf("%d ", s1[i]);
        }
    }
    printf("\nNodes in set 2 (odd levels):\n");
    for (int i = 0; i < n; i++) {
        if (s2[i] != -1) {
            printf("%d ", s2[i]);
        }
    }

    // 检查图是否是线性的
    int result1 = estLinaire(s1, m);
    printf("\nResult for even level set (S1): %d\n", result1);

    // 检查奇数层级部分是否线性
    int result2 = estLinaire(s2, m);
    printf("Result for odd level set (S2): %d\n", result2);

    // 最终结果：两个部分的检查结果做与运算
    if (result1 == 1 && result2 == 1) {
        printf("\nThe graph is linear.\n");
    } else {
        printf("\nThe graph is not linear.\n");
    }

    // 释放内存
    free(mangage);
    free(s1);
    free(s2);
    for (int i = 0; i < n; i++) {
        free(m.mat[i]);
    }
    free(m.mat);

    return 0;
}