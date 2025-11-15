#include <stdio.h>
#include <stdlib.h>
#include "StructGraphe.h"

//Exe4.1 - 邻接矩阵转邻接表的实现
ListeAdj createListeA(int n){
    ListeAdj la;
    int i=0;
    la.nbsom=n;    // 设置顶点数量
    // 为邻接表分配内存
    la.tab=(Liste*)malloc(n*sizeof(Liste));
    if(la.tab==NULL){
        printf("Memory allocation faild");
        exit(1);
    }
    // 初始化所有链表为空
    for(i=0;i<n;i++){
        la.tab[i]=NULL;
    }
    return la;
}

// 在链表头部插入新节点
Liste inserTete(Liste l,int s){
    Liste cel=(Liste)malloc(sizeof(Liste));
    cel->SomSucce=s;      // 设置后继顶点编号
    cel->suivant=l;       // 新节点指向原链表头
    l=cel;               // 更新链表头
    return l;
}

// 初始化空链表
Liste init(){
    return NULL;
}

// 将邻接矩阵转换为邻接表
ListeAdj Ma2La(MatriceAdj ma){
    int n=ma.nbsom;
    ListeAdj la=createListeA(n);    // 创建空邻接表
    int s=0,t=0;
    Liste l;
    
    // 遍历邻接矩阵的每一行
    for(s=0;s<n;s++){
        l=init();    // 初始化当前顶点的链表
        // 从后向前遍历，确保插入顺序
        for(t=n-1;t>=0;t--){
            if(ma.mat[s][t]==1){    // 如果存在边
                l=inserTete(l,t);    // 将目标顶点加入链表
            }
        }
        la.tab[s]=l;    // 保存当前顶点的后继链表
    }
    return la;
}

// 打印链表内容
void printListe(Liste l) {
    while (l != NULL) {
        printf("%d -> ", l->SomSucce);
        l = l->suivant;
    }
    printf("NULL\n");
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
    
    // 初始化邻接矩阵 (图的结构)
    // 假设一个简单的有向图
    // 0 -> 1, 1 -> 2, 2 -> 3, 3 -> 4, 4 -> 0
    ma.mat[0][1] = 1;
    ma.mat[1][2] = 1;
    ma.mat[2][3] = 1;
    ma.mat[3][4] = 1;
    ma.mat[4][0] = 1;
    
    // 转换为邻接链表
    ListeAdj la = Ma2La(ma);
    
    // 打印邻接链表
    printf("Adjacency List:\n");
    for (int i = 0; i < n; i++) {
        printf("Node %d: ", i);
        printListe(la.tab[i]);
    }

    // 释放内存
    for (int i = 0; i < n; i++) {
        Liste current = la.tab[i];
        while (current != NULL) {
            Liste temp = current;
            current = current->suivant;
            free(temp);
        }
    }
    free(la.tab);
    
    for (int i = 0; i < n; i++) {
        free(ma.mat[i]);
    }
    free(ma.mat);

    return 0;
}