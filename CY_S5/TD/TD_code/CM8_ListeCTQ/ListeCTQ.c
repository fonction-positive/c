//
// Created by 金卓远 on 24-11-4.
//
///有头结点的循环链表

#include <stdio.h>
#include <stdlib.h>
#include <sys/_types/_null.h>
typedef int TElement;
typedef struct cellule {
    TElement donnee;
    struct cellule* suivant;
}*Liste;

typedef struct {
    int taille;
    Liste tete;
    Liste queue;
}ListeCTQ;

//初始化链表
ListeCTQ initLCTQ() {
    ListeCTQ l;
    l.tete=NULL;
    l.queue=NULL;
    l.taille=0;
    return l;
}

int estVideLCTQ(ListeCTQ l) {
    return l.taille==0;
}

//新建节点并分配内存
Liste allocMemRempCel(TElement elt) {
    Liste cel=(Liste)malloc(sizeof(struct cellule));
    if (cel==NULL) {
        printf("erreur sur memoire!");
        exit(1);
    }
    cel->donnee=elt;
    cel->suivant=NULL;
    return cel;
}

//在空链表中插入元素
ListeCTQ inserListeVide(TElement elt,ListeCTQ l) {
    Liste cel=allocMemRempCel(elt);
    cel->suivant=cel;
    l.tete=cel;
    l.queue=cel;
    l.taille++;
    return l;
}

//插入尾
ListeCTQ inserQueueLCTQ(TElement elt,ListeCTQ l) {
    Liste cel=allocMemRempCel(elt);
    if (estVideLCTQ(l)) {
        inserListeVide(elt,l);
    }
    cel->suivant=l.tete;
    l.queue->suivant=cel;
    l.queue=cel;
    l.taille++;
    return l;
}

//插头
ListeCTQ inserTeteLCTQ(TElement elt,ListeCTQ l) {
    Liste cel=allocMemRempCel(elt);
    if (estVideLCTQ(l)) {
        inserListeVide(elt,l);
    }
    cel->suivant=l.tete;
    l.queue->suivant=cel;
    l.tete=cel;
    l.taille++;
    return l;
}


ListeCTQ suppTeteLCTQ(ListeCTQ l){
    Liste cel;
    cel = l.tete;
    l.tete = l.tete->suivant;
    l.queue->suivant = l.tete;
    free(cel);
    l.taille--;
    return l;
}

ListeCTQ suppEltUniqueListCirc(ListeCTQ l){
    Liste cel;
    cel = l.tete;
    l.tete = NULL;
    l.queue = NULL;
    free(cel);
    l.taille--; // l->taille = 0
    return l;
}

ListeCTQ suppListCTQ(ListeCTQ l){
    while ( l.taille > 1){
        l=suppTeteLCTQ(l);
    }
    l=suppEltUniqueListCirc(l) ;
    return l;
}

//遍历链表
void itParcour(ListeCTQ l) {
    Liste ll=l.tete;
    for (int i=0;i<l.taille;i++) {
        printf("%d->",ll->donnee);
        ll=ll->suivant;
    }
}