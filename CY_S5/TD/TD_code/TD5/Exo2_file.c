//
// Created by 金卓远 on 24-10-15.
//
#include <stdio.h>
#include <stdlib.h>

// 定义链表节点结构
struct Noeud {
    int donnees;          // 存储队列元素
    struct Noeud* suivant; // 指向下一个节点
};

// 定义队列结构
struct File {
    struct Noeud* tete;   // 指向队列的头节点
    struct Noeud* queue;  // 指向队列的尾节点
};

// 初始化队列
struct File* initFile() {
    struct File* f = (struct File*)malloc(sizeof(struct File));
    f->tete = NULL;      // 初始化头节点为空
    f->queue = NULL;     // 初始化尾节点为空
    return f;
}

// 判断队列是否为空
int estVideF(struct File* f) {
    return f->tete == NULL; // 如果头节点为空，队列为空
}

// 判断队列是否满（假设永远不满）
int estPleinF(struct File* f) {
    return 0; // 返回假，因为假设队列永远不会满
}

// 返回队列顶部元素
int sommetFile(struct File* f) {
    if (estVideF(f)) {
        printf("La file est vide.\n");
        return -1; // 返回-1表示队列为空
    }
    return f->tete->donnees; // 返回头节点的元素
}

// 入队操作
void emfiler(int elt, struct File* f) {
    struct Noeud* nouveauNoeud = (struct Noeud*)malloc(sizeof(struct Noeud));
    nouveauNoeud->donnees = elt;
    nouveauNoeud->suivant = NULL; // 新节点的下一个指针初始化为空

    if (estVideF(f)) {
        f->tete = nouveauNoeud;  // 如果队列为空，头节点指向新节点
        f->queue = nouveauNoeud; // 队列尾节点也指向新节点
    } else {
        f->queue->suivant = nouveauNoeud; // 将当前尾节点的下一个指向新节点
        f->queue = nouveauNoeud; // 更新队列尾节点
    }
}

// 出队操作
int defiler(struct File* f) {
    if (estVideF(f)) {
        printf("La file est vide.\n");
        return -1; // 返回-1表示队列为空
    }
    struct Noeud* premier = f->tete; // 获取头节点
    int valeur = premier->donnees;    // 保存头节点的值

    f->tete = f->tete->suivant; // 将头节点指向下一个节点
    free(premier); // 释放原头节点的内存

    if (f->tete == NULL) { // 如果队列为空，尾节点也要设置为NULL
        f->queue = NULL;
    }

    return valeur; // 返回出队的元素
}

// 打印队列内容
void afficherFile(struct File* f) {
    if (estVideF(f)) {
        printf("La file est vide.\n");
        return;
    }

    struct Noeud* courant = f->tete; // 从头节点开始遍历
    printf("Contenu de la file : ");
    do {
        printf("%d ", courant->donnees); // 打印当前节点的值
        courant = courant->suivant;       // 移动到下一个节点
    } while (courant != f->tete); // 直到回到头节点
    printf("\n");
}

// 测试程序
int main() {
    struct File* maFile = initFile();

    emfiler(10, maFile);
    emfiler(20, maFile);
    emfiler(30, maFile);

    afficherFile(maFile);

    printf("Sommet de la file : %d\n", sommetFile(maFile)); // 输出 10

    printf("Défilement : %d\n", defiler(maFile)); // 输出 10
    printf("Défilement : %d\n", defiler(maFile)); // 输出 20

    printf("Sommet de la file : %d\n", sommetFile(maFile)); // 输出 30

    // 清理队列
    while (!estVideF(maFile)) {
        defiler(maFile);
    }
    free(maFile); // 释放队列的内存

    return 0;
}