//
// Created by 金卓远 on 24-11-5.
//

#include <stdio.h>
#include <stdlib.h>


typedef int TElement;
typedef struct cellule {
    TElement donnee;
    struct cellule* suivant;
}*ListeCS;

ListeCS initLCS() {
    ListeCS sentinelle=malloc(sizeof(ListeCS));
    sentinelle->suivant=sentinelle;
    return sentinelle;
}


//插入元素到有序的哨兵循环链表中
ListeCS insererTri(TElement elt,ListeCS sentinelle) {
    ListeCS cel=malloc(sizeof(ListeCS));
    cel->donnee=elt;
    //找到插入位置
    ListeCS courante=sentinelle;
    while (courante->suivant!=sentinelle && courante->suivant->donnee<elt) {
        courante=courante->suivant;
    }
    //插入新节点
    cel->suivant=courante->suivant;
    courante->suivant=cel;
}


//用哨兵的循环链表对数组排序
void triTabAvecListeCS(TElement tab[],int taille) {
    ListeCS sentinelle=initLCS();
    //将数组中的元素插入链表中
    for (int i=0;i<taille;i++) {
        sentinelle=insererTri(tab[i],sentinelle);
    }
    //将链表写会数组
    ListeCS courante=sentinelle->suivant;
    for (int i=0;i<taille;i++) {
        tab[i]=courante->donnee;
        courante=courante->suivant;
    }
}



int main() {
    int tableau[] = {42, 15, 73, 8, 23};
    int taille = sizeof(tableau) / sizeof(tableau[0]);

    printf("未排序数组：");
    for (int i = 0; i < taille; i++) {
        printf("%d ", tableau[i]);
    }
    printf("\n");

    // 使用循环链表排序
    triTabAvecListeCS(tableau, taille);

    printf("排序后的数组：");
    for (int i = 0; i < taille; i++) {
        printf("%d ", tableau[i]);
    }
    printf("\n");

    return 0;
}