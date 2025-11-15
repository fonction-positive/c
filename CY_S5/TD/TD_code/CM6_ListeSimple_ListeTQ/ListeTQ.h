//
// Created by 金卓远 on 24-11-3.
//

#ifndef LISTETQ_H
#define LISTETQ_H
#include <stdio.h>
#include <stdlib.h>
#include <sys/_types/_null.h>

typedef int TElement;

typedef struct cellule {
    TElement donnee;
    struct cellule* suivant;
}*Cellule;

//头结点
typedef struct ListeTQ {
    int taille;
    Cellule tete;
    Cellule queue;
}ListeTQ;

ListeTQ initLTQ() {
    ListeTQ l;
    l.taille=0;
    l.tete=NULL;
    l.queue=NULL;
    return l;
}

int estVideLTQ(ListeTQ l) {
    return l.taille==0;
}

ListeTQ inserTeteLTQ(TElement elt,ListeTQ *l) {
    Cellule cel=(Cellule)malloc(sizeof(struct cellule));
    cel->donnee=elt;
    if (estVideLTQ(*l)) {
        cel->suivant=NULL;
        l->tete=cel;
        l->queue=cel;
    }else {
        cel->suivant=l->tete;
        l->tete=cel;
    }
    l->taille++;
}

// ListeTQ inserTeteLTQ(TElement elt,ListeTQ l) {
//     Cellule cel=(Cellule)malloc(sizeof(struct cellule));
//     cel->donnee=elt;
//     if (estVideLTQ(l)) {
//         cel->suivant=NULL;
//         l.tete=cel;
//         l.queue=cel;
//     }else {
//         cel->suivant=l.tete;
//         l.tete=cel;
//     }
//     l.taille++;
//     return l;
// }

ListeTQ inserQueue(TElement elt,ListeTQ* l) {
    Cellule cel=(Cellule)malloc(sizeof(struct cellule));
    cel->donnee=elt;
    cel->suivant=NULL;
    if (estVideLTQ(*l)) {
        l->tete=cel;
        l->queue=cel;
    }else {
        l->queue->suivant=cel;
        l->queue=cel;
    }
    l->taille++;
}

ListeTQ suppTeteLTQ(ListeTQ *l) {
    Cellule adresseTete=l->tete;
    l->tete=l->tete->suivant;
    free(adresseTete);
    l->taille--;
    if (estVideLTQ(*l)) {
        l->tete=NULL;
        l->queue=NULL;
    }
}



//parcour
void parcourLTQ(ListeTQ l) {
    Cellule courant = l.tete; // 从头结点开始

    for (int i=0;i<l.taille;i++) { // 遍历链表
        printf("%d->", courant->donnee); // 打印当前节点的数据
        courant = courant->suivant; // 移动到下一个节点
    }

    printf("\n");
}


#endif //LISTETQ_H
