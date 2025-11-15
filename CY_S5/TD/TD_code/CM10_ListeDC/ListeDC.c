#include <stdio.h>
#include <stdlib.h>
#include <mach/processor_info.h>
#include <sys/_types/_null.h>
//
// Created by 金卓远 on 24-12-8.
//
typedef int TElement;

typedef struct cellule {
    TElement donnee;
    struct cellule *suivant;
    struct cellule *precedent;
} *ListeDC;

ListeDC initLDC() {
    return NULL;
}

int estVideDC(ListeDC l) {
    return l == NULL;
}


//给节点分配内存并赋值
ListeDC allocRempCel(TElement elt) {
    ListeDC cel = malloc(sizeof(struct cellule));
    if (!estVideDC(cel)) {
        cel->donnee = elt;
        return cel;
    }
    printf("erreur de alloc memoire!\n");
    exit(1);
}

ListeDC inserTeteLCD(TElement elt, ListeDC l) {
    ListeDC cel = allocRempCel(elt);
    if (estVideDC(l)) {
        cel->precedent = NULL;
        cel->suivant = NULL;
        return cel;
    }
    cel->precedent = NULL;
    cel->suivant = l;
    l->precedent = cel;
    l = cel;
    return l;
}


ListeDC inserQueueLDC(TElement elt, ListeDC l) {
    ListeDC cel = allocRempCel(elt);
    if (estVideDC(l)) {
        cel->precedent = NULL;
        cel->suivant = NULL;
        return cel;
    }

    //找到最后一个节点
    ListeDC der = l;
    while (der->suivant != NULL) {
        der = der->suivant;
    }
    cel->precedent = der;
    cel->suivant = NULL;
    der->suivant = cel;
    return l;
}

ListeDC inserAvantLDC(TElement elt,ListeDC l) {

}