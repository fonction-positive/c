//Exe4.4 - 后继表转邻接表的实现
#include <stdio.h>
#include <stdlib.h>
#include "StructGraphe.h"

// 创建具有n个顶点的邻接表
ListeAdj createListeA(int n){
    ListeAdj la;
    int i=0;
    la.nbsom=n;    // 设置顶点数
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

// 将后继表转换为邻接表
ListeAdj Fs2La(FileSucce fs){
    int n=fs.nbSom;    // 获取顶点数
    ListeAdj la=createListeA(n);    // 创建空邻接表
    int s,j,t;
    Liste l;
    int nbSucc,daps;
    
    // 遍历每个顶点
    for(s=0;s<n;s++){
        l=init();    // 初始化当前顶点的链表
        nbSucc=fs.APS[s+1]-fs.APS[s];    // 计算当前顶点的后继数量
        daps=fs.APS[s+1]-1;              // 获取当前顶点后继在FS中的末位置
        
        // 从后向前读取当前顶点的所有后继
        for(j=0;j<nbSucc;j++){
            t=fs.FS[daps];          // 获取一个后继顶点
            daps--;                 // 移动到前一个位置
            l=inserTete(l,t);       // 将后继顶点加入链表
        }
        la.tab[s]=l;    // 保存当前顶点的后继链表
    }
    return la;
}

// 打印邻接表
void printListeAdj(ListeAdj la) {
    for (int i = 0; i < la.nbsom; i++) {
        printf("Node %d: ", i);
        Liste l = la.tab[i];
        while (l != NULL) {
            printf("%d -> ", l->SomSucce);
            l = l->suivant;
        }
        printf("NULL\n");
    }
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

// 主函数：测试后继表到邻接表的转换
int main() {
    // 创建测试用的后继表
    FileSucce fs;
    fs.nbSom = 5;    // 5个顶点
    fs.nbArcs = 5;   // 5条边

    // 分配内存
    fs.APS = (int*)malloc((fs.nbSom + 1) * sizeof(int));
    fs.FS = (int*)malloc(fs.nbArcs * sizeof(int));

    // 初始化后继表（示例：环形有向图）
    // 边：0->1, 1->2, 2->3, 3->4, 4->0
    fs.APS[0] = 0;   // 顶点0的后继开始位置
    fs.APS[1] = 1;   // 顶点1的后继开始位置
    fs.APS[2] = 2;   // 顶点2的后继开始位置
    fs.APS[3] = 3;   // 顶点3的后继开始位置
    fs.APS[4] = 4;   // 顶点4的后继开始位置
    fs.APS[5] = 5;   // 结束位置

    fs.FS[0] = 1;    // 顶点0的后继是1
    fs.FS[1] = 2;    // 顶点1的后继是2
    fs.FS[2] = 3;    // 顶点2的后继是3
    fs.FS[3] = 4;    // 顶点3的后继是4
    fs.FS[4] = 0;    // 顶点4的后继是0

    // 打印原始后继表
    printf("FileSucce format:\n");
    printFileSucce(fs);

    // 转换为邻接表并打印结果
    ListeAdj la = Fs2La(fs);
    printf("\nConverted Adjacency List (ListeAdj):\n");
    printListeAdj(la);

    // 释放内存
    free(fs.APS);
    free(fs.FS);
    for (int i = 0; i < la.nbsom; i++) {
        Liste current = la.tab[i];
        while (current != NULL) {
            Liste temp = current;
            current = current->suivant;
            free(temp);
        }
    }
    free(la.tab);

    return 0;
}