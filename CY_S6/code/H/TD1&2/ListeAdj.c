//Exe3.2 - 邻接表的实现
#include <stdio.h>
#include <stdlib.h>
#include "StructGraphe.h"

// 函数声明
ListeAdj createListeA(int n);     // 创建具有n个顶点的邻接表
Liste inserTete(Liste l,int s);    // 在链表头部插入新节点
Liste init();                      // 初始化空链表
int nbsom(ListeAdj la);           // 获取顶点数量
int estBoucle(ListeAdj la);       // 检查是否存在自环
void somSucce(int s,ListeAdj la); // 打印指定顶点的后继节点
int MaxSomSucce(ListeAdj la);     // 找出具有最多后继节点的顶点

// 创建具有n个顶点的邻接表
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

// 在链表头部插入值为s的新节点
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

// 返回图中顶点的数量
int nbsom(ListeAdj la){
    return la.nbsom;
}

// 检查图中是否存在自环（顶点到自身的边）
int estBoucle(ListeAdj la){
    int n=nbsom(la);
    int s=0;
    int estBoucle=0;
    Liste ll;
    while (s<n && estBoucle==0){
        ll=la.tab[s];    // 获取当前顶点的后继链表
        // 遍历链表查找是否存在指向自身的边
        while (ll!=NULL && estBoucle==0){
            if(ll->SomSucce==s){    // 如果找到指向自身的边
                estBoucle=1;
            }
            ll=ll->suivant;
        }
        s=s+1;
    }
    return estBoucle;
}

// 打印顶点s的所有后继节点
void somSucce(int s,ListeAdj la){
    Liste ll;
    ll=la.tab[s];    // 获取顶点s的后继链表
    printf("Les somme success de %d sont: \n",s);
    // 遍历并打印所有后继节点
    while (ll!=NULL){
        printf("%d ",ll->SomSucce);
        ll=ll->suivant;
    }
}

// 找出具有最多后继节点的顶点
int MaxSomSucce(ListeAdj la){
    int n=nbsom(la);
    int MaxSom=0;    // 存储最大后继数的顶点编号
    int Max=0;       // 最大后继节点数
    int i=0,lg=0;    // lg用于计数当前顶点的后继节点数
    Liste ll;
    
    // 遍历所有顶点
    for(i=0;i<n;i++){
        ll=la.tab[i];
        // 计算当前顶点的后继节点数
        while (ll!=NULL){
            lg++;
            ll=ll->suivant;
        }
        // 更新最大值
        if(lg>Max){
            Max=lg;
            MaxSom=i;
        }
        lg=0;    // 重置计数器
    }
    return MaxSom;
}

// 主函数：测试邻接表的各项功能
int main(void){
    ListeAdj la;
    int s=0;
    
    // 创建具有5个顶点的邻接表
    la=createListeA(5);
    
    // 添加测试边：1->2
    Liste l=init();
    l=inserTete(l,2);
    la.tab[1]=l;
    
    // 添加测试边：2->4和2->3
    l=init();
    l=inserTete(l,4);
    l=inserTete(l,3);
    la.tab[2]=l;
    
    // 测试各项功能
    printf("EstBoucle? %d\n",estBoucle(la));    // 检查是否有自环
    s=MaxSomSucce(la);                          // 获取最大后继节点的顶点
    somSucce(s,la);                             // 打印该顶点的后继节点
    
    return 0;
}