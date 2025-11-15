#include <stdio.h>
#include <stdlib.h>

//
// Created by 金卓远 on 24-12-15.
//
typedef int TElement;

typedef struct cellule {
    TElement donnee;
    struct cellule *suivant;
    struct cellule *precedent;
} *ListeDC;

typedef struct {
    int taille;
    ListeDC tete;
    ListeDC queue;
} ListeDCTQ;

ListeDCTQ initLDCTQ();
int estVideLDCTQ(ListeDCTQ l);
ListeDC allocMemCelDC(TElement elt);
ListeDCTQ inserLVideDCTQ(TElement elt);
ListeDCTQ inserTeteLDCTQ(TElement elt, ListeDCTQ l);
ListeDCTQ inserQueue(TElement elt, ListeDCTQ l);
ListeDC adrInertElt(TElement elt, ListeDCTQ l);
ListeDCTQ inserAvant(TElement elt, TElement eltAv, ListeDCTQ l);
ListeDCTQ inserApres(TElement elt,TElement eltAp,ListeDCTQ l);
ListeDCTQ suppTeteLDCTQ(ListeDCTQ l);
ListeDCTQ suppQueueLDCTQ(ListeDCTQ l);
ListeDCTQ suppAutreLDCTQ(ListeDCTQ l,ListeDC adSupp);


ListeDCTQ initLDCTQ() {
    ListeDCTQ l;
    l.tete = NULL;
    l.queue = NULL;
    l.taille = 0;
    return l;
}

int estVideLDCTQ(ListeDCTQ l) {
    return l.taille == 0;
}

//创建一个节点cel
ListeDC allocMemCelDC(TElement elt) {
    ListeDC cel = malloc(sizeof(struct cellule));
    if (cel == NULL) {
        printf("pb de memoire");
        exit(1);
    }
    cel->donnee = elt;
    return cel;
}

//在空链表中创建节点
ListeDCTQ inserLVideDCTQ(TElement elt) {
    ListeDC cel = allocMemCelDC(elt);
    cel->suivant = NULL;
    cel->precedent = NULL;
    ListeDCTQ l;
    l.tete = cel;
    l.queue = cel;
    l.taille = 1;
    return l;
}

//插入头
ListeDCTQ inserTeteLDCTQ(TElement elt, ListeDCTQ l) {
    if (l.taille == 0) {
        return inserLVideDCTQ(elt);
    }
    ListeDC cel = allocMemCelDC(elt);
    cel->suivant = l.tete;
    cel->precedent = NULL;
    l.tete->precedent = cel;
    l.tete = cel;
    l.taille++;
    return l;
}

//插尾
ListeDCTQ inserQueue(TElement elt, ListeDCTQ l) {
    if (l.taille == 0) {
        return inserLVideDCTQ(elt);
    }
    ListeDC cel = allocMemCelDC(elt);
    cel->suivant = NULL;
    cel->precedent = l.queue;
    l.queue->suivant = cel;
    l.queue = cel;
    l.taille++;
    return l;
}

//返回eltAv的地址
ListeDC adrInertElt(TElement elt, ListeDCTQ l) {
    ListeDC adr = l.tete;
    while ( adr!= NULL) {
        if (adr->donnee == elt) {
            return adr;
        }
        adr = adr->suivant;
    }
    return NULL;
}


//在eltAv这个元素前面插入
ListeDCTQ inserAvant(TElement elt, TElement eltAv, ListeDCTQ l) {
    ListeDC adrInser=adrInertElt(eltAv,l);
    if(!estVideLDCTQ(l)) {
        ListeDC cel=allocMemCelDC(elt);
        cel->suivant=adrInser;
        cel->precedent=adrInser->precedent;
        if (adrInser!=l.tete) {
            adrInser->precedent->suivant=cel;
        }else {
            l.tete=cel;
        }
        adrInser->precedent=cel;
        l.taille++;
    }
    return l;
}

//在指定元素后插入
ListeDCTQ inserApres(TElement elt,TElement eltAp,ListeDCTQ l) {
    ListeDC adr=adrInertElt(eltAp,l);
    if (!estVideLDCTQ(l)) {
        ListeDC cel=allocMemCelDC(elt);
        cel->precedent=adr;
        cel->suivant=adr->suivant;
        if (adr->suivant!=NULL) {
            adr->suivant->precedent=cel;
        }else {
            l.queue=cel;
        }
        adr->suivant=cel;
        l.taille++;
    }
    return l;
}

ListeDCTQ suppTeteLDCTQ(ListeDCTQ l) {
    if (l.taille==0) {
        return l;
    }
    ListeDC adSupp=l.tete;
    l.tete=l.tete->suivant;
    l.tete->precedent=NULL;
    if (estVideLDCTQ(l)) {
        l.queue=NULL;
    }
    free(adSupp);
    l.taille--;
    return l;
}

ListeDCTQ suppQueueLDCTQ(ListeDCTQ l) {
    if (l.taille==0) {
        return l;
    }
    ListeDC adSupp=l.queue;
    l.queue=l.queue->precedent;
    l.queue->suivant=NULL;
    free(adSupp);
    l.taille--;
    return l;
}

//指定位置删除
ListeDCTQ suppAutreLDCTQ(ListeDCTQ l,ListeDC adSupp) {
    if (l.taille==0) {
        return l;
    }
    if (adSupp->precedent==NULL) {
        return suppTeteLDCTQ(l);
    }
    if (adSupp->suivant==NULL) {
        return suppQueueLDCTQ(l);
    }
    adSupp->precedent->suivant=adSupp->suivant;
    adSupp->suivant->precedent=adSupp->precedent;
    free(adSupp);
    l.taille--;
    return l;
}

