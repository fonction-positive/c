//
// Created by 金卓远 on 25-3-1.
//

#ifndef FILE_H
#define FILE_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 定义队列结构
typedef struct {
    int *elements;
    int front, rear, size, capacity;
} File;

// 初始化队列
File* initFile(int capacity) {
    File* queue = (File*)malloc(sizeof(File));
    queue->capacity = capacity;
    queue->front = 0;
    queue->rear = -1;
    queue->size = 0;
    queue->elements = (int*)malloc(capacity * sizeof(int));
    return queue;
}

// 判断队列是否为空
bool estVideFile(File *queue) {
    return queue->size == 0;
}

// 向队列中插入元素
void enfiler(int element, File *queue) {
    if (queue->size == queue->capacity) {
        printf("Queue is full\n");
        return;
    }
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->elements[queue->rear] = element;
    queue->size++;
}

// 从队列中取出元素
int sommetFile(File *queue) {
    return queue->elements[queue->front];
}

// 从队列中移除元素
void defiler(File *queue) {
    if (estVideFile(queue)) {
        printf("Queue is empty\n");
        return;
    }
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
}


#include <stdio.h>
#include <stdlib.h>

// // 定义链表节点结构
// struct Noeud {
//     int donnees;          // 存储队列元素
//     struct Noeud* suivant; // 指向下一个节点
// };
//
// // 定义队列结构
// typedef struct file {
//     struct Noeud* tete;   // 指向队列的头节点
//     struct Noeud* queue;  // 指向队列的尾节点
// }File;
//
// // 初始化队列
// struct File* initFile() {
//     struct File* f = (struct File*)malloc(sizeof(struct File));
//     f->tete = NULL;      // 初始化头节点为空
//     f->queue = NULL;     // 初始化尾节点为空
//     return f;
// }
//
// // 判断队列是否为空
// int estVideF(struct File* f) {
//     return f->tete == NULL; // 如果头节点为空，队列为空
// }
//
// // 判断队列是否满（假设永远不满）
// int estPleinF(struct File* f) {
//     return 0; // 返回假，因为假设队列永远不会满
// }
//
// // 返回队列顶部元素
// int sommetFile(struct File* f) {
//     if (estVideF(f)) {
//         printf("La file est vide.\n");
//         return -1; // 返回-1表示队列为空
//     }
//     return f->tete->donnees; // 返回头节点的元素
// }
//
// // 入队操作
// void emfiler(int elt, struct File* f) {
//     struct Noeud* nouveauNoeud = (struct Noeud*)malloc(sizeof(struct Noeud));
//     nouveauNoeud->donnees = elt;
//     nouveauNoeud->suivant = NULL; // 新节点的下一个指针初始化为空
//
//     if (estVideF(f)) {
//         f->tete = nouveauNoeud;  // 如果队列为空，头节点指向新节点
//         f->queue = nouveauNoeud; // 队列尾节点也指向新节点
//     } else {
//         f->queue->suivant = nouveauNoeud; // 将当前尾节点的下一个指向新节点
//         f->queue = nouveauNoeud; // 更新队列尾节点
//     }
// }
//
// // 出队操作
// int defiler(struct File* f) {
//     if (estVideF(f)) {
//         printf("La file est vide.\n");
//         return -1; // 返回-1表示队列为空
//     }
//     struct Noeud* premier = f->tete; // 获取头节点
//     int valeur = premier->donnees;    // 保存头节点的值
//
//     f->tete = f->tete->suivant; // 将头节点指向下一个节点
//     free(premier); // 释放原头节点的内存
//
//     if (f->tete == NULL) { // 如果队列为空，尾节点也要设置为NULL
//         f->queue = NULL;
//     }
//
//     return valeur; // 返回出队的元素
// }


#endif //FILE_H
