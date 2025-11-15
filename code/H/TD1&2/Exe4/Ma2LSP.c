#include <stdio.h>
#include <stdlib.h>
#include "StructGraphe.h"

//Exe4.3 - 邻接矩阵转前驱后继表的实现
Liste inserTete(Liste l,int s){
    Liste cel=(Liste)malloc(sizeof(Liste));
    cel->SomSucce=s;      // 设置顶点编号
    cel->suivant=l;       // 新节点指向原链表头
    l=cel;               // 更新链表头
    return l;
}

Liste init(){
    return NULL;
}

ListeSP createListeSP(int n){
    ListeSP LSP;
    int i;
    LSP.nbSom=n;    // 设置顶点数
    
    // 分配内存
    LSP.tab=(SP*)malloc(n*sizeof(SP));
    if(LSP.tab==NULL){
        printf("eurro!");
        exit(1);
    }
    
    // 初始化所有前驱和后继链表为空
    for(i=0;i<n;i++){
        LSP.tab[i].ListePrece=NULL;
        LSP.tab[i].ListeSucce=NULL;
    }
    return LSP;
}

ListeSP Ma2LSP(MatriceAdj ma){
    int n=ma.nbsom;
    ListeSP LSP=createListeSP(n);
    int s,t;
    Liste ls,lp;
    
    // 遍历邻接矩阵的每个顶点
    for(s=0;s<n;s++){
        ls=init();    // 初始化后继链表
        lp=init();    // 初始化前驱链表
        
        // 从后向前遍历，确保插入顺序
        for(t=n-1;t>=0;t--){
            if(ma.mat[s][t]==1){         // 如果存在边s->t
                ls=inserTete(ls,t);       // 将t加入s的后继表
            }
            if(ma.mat[t][s]==1){         // 如果存在边t->s
                lp=inserTete(lp,t);       // 将t加入s的前驱表
            }
        }
        LSP.tab[s].ListePrece=lp;    // 保存前驱链表
        LSP.tab[s].ListeSucce=ls;    // 保存后继链表
    }
    return LSP;
}

// 打印链表
void printListe(Liste l) {
    while (l != NULL) {
        printf("%d -> ", l->SomSucce);
        l = l->suivant;
    }
    printf("NULL\n");
}

// 打印 ListeSP
void printListeSP(ListeSP LSP) {
    printf("ListeSP (Adjacency List with Predecessors and Successors):\n");
    for (int i = 0; i < LSP.nbSom; i++) {
        printf("Node %d:\n", i);
        printf("  Predecessors: ");
        printListe(LSP.tab[i].ListePrece);
        printf("  Successors: ");
        printListe(LSP.tab[i].ListeSucce);
    }
}

int main() {
    // 创建邻接矩阵
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

    // 转换为 ListeSP
    ListeSP LSP = Ma2LSP(ma);

    // 打印 ListeSP 内容
    printListeSP(LSP);

    // 释放内存
    for (int i = 0; i < n; i++) {
        free(ma.mat[i]);
    }
    free(ma.mat);

    // 释放 ListeSP 中的内存
    for (int i = 0; i < LSP.nbSom; i++) {
        Liste current;
        // 释放 ListePrece 链表
        current = LSP.tab[i].ListePrece;
        while (current != NULL) {
            Liste temp = current;
            current = current->suivant;
            free(temp);
        }
        // 释放 ListeSucce 链表
        current = LSP.tab[i].ListeSucce;
        while (current != NULL) {
            Liste temp = current;
            current = current->suivant;
            free(temp);
        }
    }
    free(LSP.tab);

    return 0;
}