//
// Created by 金卓远 on 24-11-1.
//

#ifndef OPERATION_LISTE_CHAINEE_H
#define OPERATION_LISTE_CHAINEE_H
#include <stdio.h>
#include <stdlib.h>
#include <sys/_types/_null.h>



#include<stdbool.h>
#include <malloc/malloc.h>
#define TElement int

typedef struct cellule {
    TElement donnee;
    struct cellule* suivant;
}*Liste;

TElement donnee(Liste l) {
    return l->donnee;
}

Liste suivant(Liste l) {
    return l->suivant;
}

Liste init() {
    return NULL;
}

int estVide(Liste l) {
    return l==NULL;
}

int estPlein(Liste l) {
    return 0; //因为链表永远不会满，所以永远返回false
}

//返回节点地址
Liste accessPosition(int pos,Liste l) {
    if (estVide(l) || pos==1) {
        return l;
    }
    return accessPosition(pos-1,suivant(l));
}

//parcour
void parcours(Liste l) {
    if (!estVide(l)) {
        printf("%d->",donnee(l));
        parcours(suivant(l));
    }
}

//计算链表长度
int longListe(Liste l) {
    int lg=0;
    while (!estVide(l)) {
        lg++;
        l=suivant(l);
    }
    return lg;
}

//查找元素是否在链表中
int rechercheElement(int elt,Liste l) {
    while (!estVide(l) && donnee(l)!=elt) {
        l=suivant(l);
    }
    return !estVide(l);
}

//插头
Liste inserTete(TElement elt, Liste l) {
    Liste cel=(Liste)malloc(sizeof(struct cellule));
    cel->donnee=elt;
    cel->suivant=l;
    l=cel;
    return l;
}

//返回最后一个节点
Liste dernier(Liste l) {
    Liste der=l;
    while (!estVide(suivant(der))) {
        der=suivant(der);
    }
    return der;
}
// Liste dernier(Liste l) {
//     Liste celCourant=l;
//     Liste celPrecedente=NULL; //因为最后一个节点的suivante是NULL，最后一个节点是NULL的前一个
//     while (!estVide(celCourant)) {
//         celPrecedente=celCourant;
//         celCourant=suivant(celCourant);
//     }
//     return celPrecedente;
// }

//插尾
Liste inserQueue(TElement elt, Liste l) {
    if (estVide(l)) {
        return inserTete(elt, l); // 空链表时，直接调用 inserTete 并返回新头指针
    }

    Liste der = dernier(l); // 找到最后一个节点
    Liste cel = (Liste)malloc(sizeof(struct cellule));
    cel->donnee = elt;
    cel->suivant = NULL;
    der->suivant = cel;
    return l;
}

//insertion dans une liste triee
Liste inserElementListeTriee(TElement elt,Liste l) {
    //如果是空链表或者elt小于第一个元素，则插入在头
    if (estVide(l) || elt<=donnee(l)) {
        return inserTete(elt,l);
    }

    //如果不是，则一直递归，知道找到大于elt的节点,然后插在前面
    return inserElementListeTriee(elt,suivant(l));
}

//删头
Liste suppTete(Liste l) {
    Liste adressel=l; //保留头结点的地址，为了过会释放内存
    l=suivant(l); //把头结点指向第二个节点
    free(adressel); //释放内存
    return l;
}


//删除链表
Liste suppListe(Liste l) {
    while (!estVide(l)) {
        suppTete(l);
    }
}


//删除指定元素 递归
Liste suppElementListe(TElement elt,Liste l) {
    if (estVide(l))
        return l;
    if (donnee(l)==elt) {
        return suppTete(l);
    }
    //suppElementListe 返回的是子链表中删除了值为 elt 节点后的结果链表的头节点。
    //通过 l->suivant = suppElementListe(elt, l->suivant); 将删除后的子链表的头节点重新链接回 l->suivant
    l->suivant=suppElementListe(elt,suivant(l));
    return l;
}



//删除指定位置的节点
Liste suppPosListe(int pos,Liste l) {
    if (estVide(l)) {
        return l;
    }
    if (pos==1) {
        return suppTete(l);
    }
    l->suivant=suppPosListe(pos-1,l->suivant);
    return l;
}







#endif //OPERATION_LISTE_CHAINEE_H