// queue.h
#ifndef QUEUE_H
#define QUEUE_H

#define MAX_SIZE 100  // 队列的最大容量

typedef struct {
    int data[MAX_SIZE];
    int size; // 队列当前大小
} Queue;

// 初始化队列
Queue initf();
// 入队操作
void emfiler(Queue* q, int value);
// 出队操作
int defiler(Queue* q);
// 检查队列是否为空
int estVide(Queue* q);

#endif // QUEUE_H