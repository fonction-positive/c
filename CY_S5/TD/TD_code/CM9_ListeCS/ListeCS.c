//
// Created by 金卓远 on 24-11-4.
//
///带有哨兵（sentinelle）的循环链表
///将链表第一个节点作为哨兵，不储存重要数据
///这样可以确保链表的地址不变(只在初始化的时候设定)，而且不存在NULL的链表，避免了错误
///方便插入和删除头节点，避免每次跟新头节点的地址
///方便循环，遍历链表

#include <stdlib.h>

typedef int TElment;
typedef struct cellule {
    TElment donnee;;
    struct cellule* suivant;
}*ListeCS;

//初始化链表
ListeCS initLCS() {
    ListeCS sentinelle=malloc(sizeof(ListeCS));
    sentinelle->donnee=-1;
    sentinelle->suivant=sentinelle;
    return sentinelle;
}

int estVideCS(ListeCS lcs) {
    return lcs->suivant==lcs;
}

ListeCS teteLCS(ListeCS lcs) {
    return lcs->suivant;
}

ListeCS queueLCS(ListeCS lcs) {
    ListeCS ll=lcs;
    while (ll->suivant!=lcs) {
        ll=ll->suivant;
    }
    return ll;
}




