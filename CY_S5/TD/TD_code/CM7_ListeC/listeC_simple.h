//
// Created by 金卓远 on 24-11-3.
//

#ifndef LISTEC_SIMPLE_H
#define LISTEC_SIMPLE_H
#include <stdio.h>
#include <stdlib.h>
#include <sys/_types/_null.h>




typedef int TElement;

typedef struct cellule {
    TElement donnee;
    struct cellule* suivant;
}*ListeC;


ListeC initLC() {
    return NULL;
}

int estVideLC(ListeC l) {
    return l==NULL;
}

void parcourLC(ListeC l) {
    ListeC courant=l;
    do {
        printf("%d",courant->donnee);
        courant=courant->suivant;
    }while (courant!=l);
}


// 分配内存并初始化节点
ListeC allocMemRempCel(TElement elt) {
    ListeC cel = (ListeC)malloc(sizeof(struct cellule)); // 分配内存
    // 检查内存分配是否成功
    if (estVideLC(cel)) {
        printf("Erreur d'allocation de mémoire."); // 调用错误处理
    }

    cel->donnee = elt; // 设置节点的数据
    cel->suivant = NULL; // 初始化指针为 NULL

    return cel; // 返回新节点
}

//在空链表中插入节点
ListeC inserListeCVide(TElement elt,ListeC l) {
    ListeC cel=allocMemRempCel(elt);
    cel->suivant=cel; //只有一个节点，所以下一个还是指向自己
    return cel;
}

//在l前插入节点
//1.找到需要插入的位置，前一个节点（也就是最后一个节点）
ListeC adrInsertion(ListeC l) {
    ListeC ai=l;
    while (ai->suivant!=l) {
        ai=ai->suivant;
    }
    return ai; //返回需要插入的位置
}

//2.插入
ListeC inserAvantLC(TElement elt,ListeC l) {
    ListeC cel=allocMemRempCel(elt); //新建一个节点并赋值
    ListeC ai=adrInsertion(l); //找到需要插入的位置
    cel->suivant=l; //新节点的suivant指向l
    ai->suivant=cel; //最后一个节点指向cel
    return l;
}

//在l之后插入
ListeC inserApresLC(TElement elt,ListeC l) {
    ListeC cel=allocMemRempCel(elt);
    cel->suivant=l->suivant; //新节点的suivant指向l的下一个节点
    l->suivant=cel; //l的suivant指向cel
}

///我们将链表的最后一个节点der作为链表的地址，是为了方便实现队列file，这样可以快速的插入头和尾

//插入头结点
ListeC inserTeteLC(TElement elt,ListeC der) {
    if (estVideLC(der)) {
        der=inserListeCVide(elt,der);
        return der;
    }
    ListeC cel=allocMemRempCel(elt);
    cel->suivant=der->suivant;
    der->suivant=cel;
    return der;
}

//插入尾节点
ListeC inserQueueLC(TElement elt,ListeC der) {
    if (estVideLC(der)) {
        der=inserListeCVide(elt,der);
        return der;
    }
    ListeC cel=allocMemRempCel(elt);
    cel->suivant=der->suivant;
    der->suivant=cel;
    der=cel; //别忘了跟新der，指向最后一个节点
    return der;
}

//删除下一个节点
ListeC suppSuivant(ListeC l) {
    ListeC adresseS=l->suivant;
    if (l==adresseS) { //如果链表只有一个节点，那l->suivant就指向他自己
        l=NULL;
    }else {
        l->suivant=adresseS->suivant;
    }
    free(adresseS);
    return l;
}

//删除整个链表
ListeC itsuppLC(ListeC l) {
    ListeC cel; //用于临时保存地址
    ListeC ll=l->suivant; //从第二个开始删，一圈回来后再删除第一个
    while (ll!=l) {
        cel=ll; //保存ll的地址，以防丢失
        ll=ll->suivant; //循环到下一个节点
        free(cel); //释放节点
    }
    free(l); //别忘记释放第一个节点
    return NULL; //返回NULL
}

ListeC resuppLC(ListeC ll,ListeC l) { //l是不会变的，ll用来遍历每个节点
    if (ll!=l) {
        ListeC cel=ll;
        ll=ll->suivant;
        free(cel);
        return resuppLC(ll,l);
    }
}


#endif //LISTEC_SIMPLE_H
