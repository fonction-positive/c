//
// Created by 金卓远 on 24-10-15.
//

#include <stdio.h>
#include <stdlib.h>

// 定义链表节点结构
struct Noeud {
    int donnees;           // 存储数据
    struct Noeud* suivant; // 指向下一个节点
};

// 定义循环链表栈结构
struct Pile {
    struct Noeud* tete; // 指向栈顶节点
};

// 初始化栈
struct Pile* initPile() {
    struct Pile* p = (struct Pile*)malloc(sizeof(struct Pile));
    p->tete = NULL; // 初始化栈顶节点为空
    return p;
}

// 判断栈是否为空
int estVideP(struct Pile* p) {
    return p->tete == NULL; // 如果栈顶节点为空，栈为空
}

// 判断栈是否满（假设永远不满）
int estPleinP(struct Pile* p) {
    return 0; // 返回假，因为假设栈永远不会满
}

// 返回栈顶元素
int sommetPile(struct Pile* p) {
    if (estVideP(p)) {
        printf("La pile est vide.\n");
        return -1; // 返回-1表示栈为空
    }
    return p->tete->donnees; // 返回栈顶节点的元素
}

// 入栈操作
void empiler(int elt, struct Pile* p) {
    struct Noeud* nouveauNoeud = (struct Noeud*)malloc(sizeof(struct Noeud));
    nouveauNoeud->donnees = elt; // 设置新节点的数据
    if (estVideP(p)) {
        p->tete = nouveauNoeud; // 如果栈为空，设置新节点为栈顶
        nouveauNoeud->suivant = nouveauNoeud; // 哨兵指向自身
    } else {
        nouveauNoeud->suivant = p->tete; // 新节点的下一个指向当前栈顶
        struct Noeud* dernier = p->tete;
        while (dernier->suivant != p->tete) {
            dernier = dernier->suivant; // 找到当前栈的最后一个节点
        }
        dernier->suivant = nouveauNoeud; // 更新最后一个节点的下一个指向新节点
        p->tete = nouveauNoeud; // 更新栈顶为新节点
    }
}

// 出栈操作
int depiler(struct Pile* p) {
    if (estVideP(p)) {
        printf("La pile est vide.\n");
        return -1; // 返回-1表示栈为空
    }
    struct Noeud* sommet = p->tete; // 获取栈顶节点
    int valeur = sommet->donnees;    // 保存栈顶节点的值
    if (sommet->suivant == sommet) {  // 如果只有一个元素
        p->tete = NULL; // 栈为空
    } else {
        struct Noeud* courant = p->tete;
        while (courant->suivant != sommet) {
            courant = courant->suivant; // 找到栈顶节点的前一个节点
        }
        courant->suivant = sommet->suivant; // 更新前一个节点的下一个指向栈顶节点的下一个
        p->tete = sommet->suivant; // 更新栈顶为下一个节点
    }
    free(sommet); // 释放原栈顶节点的内存
    return valeur; // 返回出栈的元素
}

// 打印栈内容
void afficherPile(struct Pile* p) {
    if (estVideP(p)) {
        printf("La pile est vide.\n");
        return;
    }
    struct Noeud* courant = p->tete;
    printf("Contenu de la pile : ");
    do {
        printf("%d ", courant->donnees); // 打印当前节点的值
        courant = courant->suivant;       // 移动到下一个节点
    } while (courant != p->tete);
    printf("\n");
}

// 主程序
int main() {
    struct Pile* p = initPile(); // 初始化栈

    empiler(5, p);
    empiler(10, p);
    empiler(15, p);
    afficherPile(p); // 打印当前栈内容

    printf("Sommet de la pile : %d\n", sommetPile(p)); // 打印栈顶元素

    printf("Dépile : %d\n", depiler(p)); // 出栈
    afficherPile(p); // 打印当前栈内容

    // 释放内存
    while (!estVideP(p)) {
        depiler(p); // 逐个出栈以释放内存
    }
    free(p); // 释放栈的结构
    return 0;
}

