#include <stdio.h>
#include <stdlib.h>
#include "StructGraphe.h"

//Exe4.5 - 邻接表转后继表的实现
FileSucce createFileSucce(int nbsom, int nbarc) {
    FileSucce fs;
    fs.nbSom = nbsom;    // 设置顶点数
    fs.nbArcs = nbarc;   // 设置边数

    // 分配APS数组内存（大小为顶点数+1）
    fs.APS = (int*)malloc((nbsom + 1) * sizeof(int));
    if (fs.APS == NULL) {
        printf("Memory allocation failed for APS.\n");
        exit(1);
    }

    // 分配FS数组内存（大小为边数）
    fs.FS = (int*)malloc(nbarc * sizeof(int));
    if (fs.FS == NULL) {
        printf("Memory allocation failed for FS.\n");
        free(fs.APS);  // 释放之前分配的内存
        exit(1);
    }

    return fs;
}

// 将邻接表转换为后继表
FileSucce La2Fs(ListeAdj la){
    int n=la.nbsom;
    int p=0,s=0;
    Liste ll;
    
    // 计算总边数
    for(s=0;s<n;s++){
        ll=la.tab[s];
        while(ll!=NULL){
            p++;            // 统计所有后继节点数量
            ll=ll->suivant;
        }
    }
    
    // 创建后继表
    FileSucce fs=createFileSucce(n,p);
    int iAps=0;    // FS数组的当前位置
    
    // 构建后继表
    for(s=0;s<n;s++){
        fs.APS[s]=iAps;    // 记录当前顶点的后继起始位置
        ll=la.tab[s];
        while (ll!=NULL){
            fs.FS[iAps]=ll->SomSucce;    // 将后继顶点加入FS数组
            iAps++;
            ll=ll->suivant;
        }
    }
    fs.APS[n]=p;    // 最后一个位置存储总边数
    return fs;
}

// 在链表头部插入新节点
Liste inserTete(Liste l, int s) {
    Liste cel = (Liste)malloc(sizeof(struct cellul));
    cel->SomSucce = s;      // 设置后继顶点编号
    cel->suivant = l;       // 新节点指向原链表头
    l = cel;               // 更新链表头
    return l;
}

// 打印后继表结构
void printFileSucce(FileSucce fs) {
    printf("Number of nodes: %d\n", fs.nbSom);
    printf("Number of arcs: %d\n", fs.nbArcs);

    printf("APS: ");    // 打印顶点位置数组
    for (int i = 0; i <= fs.nbSom; i++) {
        printf("%d ", fs.APS[i]);
    }
    printf("\n");

    printf("FS: ");     // 打印后继数组
    for (int i = 0; i < fs.nbArcs; i++) {
        printf("%d ", fs.FS[i]);
    }
    printf("\n");
}

// 主函数：测试邻接表到后继表的转换
int main() {
    int n = 5;    // 假设图有5个顶点
    ListeAdj la;
    la.nbsom = n;

    // 创建邻接表并分配内存
    la.tab = (Liste*)malloc(n * sizeof(Liste));
    for (int i = 0; i < n; i++) {
        la.tab[i] = NULL;    // 初始化每个链表为空
    }

    // 构建邻接表（示例：环形有向图）
    // 添加测试边：0->1->2->3->4->0
    la.tab[0] = inserTete(la.tab[0], 1);    // 0 -> 1
    la.tab[1] = inserTete(la.tab[1], 2);    // 1 -> 2
    la.tab[2] = inserTete(la.tab[2], 3);    // 2 -> 3
    la.tab[3] = inserTete(la.tab[3], 4);    // 3 -> 4
    la.tab[4] = inserTete(la.tab[4], 0);    // 4 -> 0

    // 打印原始邻接表
    printf("Adjacency List (La):\n");
    for (int i = 0; i < n; i++) {
        printf("Node %d: ", i);
        Liste l = la.tab[i];
        while (l != NULL) {
            printf("%d -> ", l->SomSucce);
            l = l->suivant;
        }
        printf("NULL\n");
    }

    // 转换为后继表并打印结果
    FileSucce fs = La2Fs(la);
    printFileSucce(fs);

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
    free(fs.APS);
    free(fs.FS);

    return 0;
}