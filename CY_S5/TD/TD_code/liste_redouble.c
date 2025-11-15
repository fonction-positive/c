//
// Created by 金卓远 on 24-10-16.
//
# define  TypeElement int
#include <sys/_types/_null.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct cellule {
    TypeElement donnee;
    struct cellule* suivant;
    struct cellule* precedent;
}*ListeDC;

ListeDC initLDC() {
    return NULL;
}

bool estVideDC(ListeDC L) {
    return (L==NULL);
}

bool estPleinLDC(ListeDC L) {
    return false; //链表不会满，直接返回faux
}

//创建一个节点
ListeDC allocRemCel(TypeElement elt) {
    ListeDC cel=(ListeDC)malloc(sizeof(struct cellule));
    if (!estVideDC(cel)) {
        cel->donnee=elt;
        return cel;
    }
    printf('problem alloc memoire');
    exit(1);
}

void inserTeteLDC(TypeElement elt, ListeDC l) {
    //分配内存和填充值
    ListeDC cel=allocRemCel(elt);
    //没有头结点，cel前指向NULL
    cel->precedent=initLDC();
    //如果链表为空
    if (estVideDC(l)) {
        //cel是第一个节点也是最后一个节点，让cel后指针指向NULL
        cel->precedent=initLDC();
        l=cel;
    }
    //如果链表不空
    else {
        //将cel插入链表最前面，cel后指针指向原链表的头
        cel->suivant=l;
        //原链表头的前指针指向cel
        l->precedent=cel;
        //跟新链表，让头变成cel
        l=cel;
    }
}

void inserQueueLDC(TypeElement elt,ListeDC l) {
    //给新节点分配内存并填入值
    ListeDC cel=allocRemCel(elt);
    //cel的后节点指向NULL
    cel->suivant=initLDC();
    //如果链表为空
    if (estVideDC(l)) {
        cel->precedent=initLDC();
        l=cel;
    }
    //如果不为空
    else {
        
    }

}


void main() {


}





