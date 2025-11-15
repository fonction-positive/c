#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

// 初始化队列
Queue initf() {
    Queue q;
    q.size = 0;
    return q;
}

// 入队操作
void emfiler(Queue* q, int value) {
    if (q->size >= MAX_SIZE) {
        printf("Queue is full!\n");
        return;
    }
    q->data[q->size] = value;
    q->size++;
}

// 出队操作
int defiler(Queue* q) {
    if (q->size == 0) {
        printf("Queue is empty!\n");
        return -1;
    }
    int value = q->data[0];
    for (int i = 1; i < q->size; i++) {
        q->data[i - 1] = q->data[i];
    }
    q->size--;
    return value;
}

// 检查队列是否为空
int estVide(Queue* q) {
    return q->size == 0;
}
