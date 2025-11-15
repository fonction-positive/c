//
// Created by 金卓远 on 25-4-6.
//
#include"plus_court_chemin.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


// 初始化优先队列
File initF() {
    File f;
    f.capacity = 100; // 初始容量，可以根据需要调整
    f.size = 0;
    f.elements = (int *)malloc(f.capacity * sizeof(int));
    f.priorities = (int *)malloc(f.capacity * sizeof(int));
    if (f.elements == NULL || f.priorities == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    return f;
}

// 判断优先队列是否为空
int estVideF(File f) {
    return f.size == 0;
}

// 获取队列头部元素（优先级最小的元素）
int sommetF(File f) {
    if (f.size == 0) {
        fprintf(stderr, "Queue is empty\n");
        exit(EXIT_FAILURE);
    }
    return f.elements[0];
}

// 交换两个元素及其优先级
void swap(int *a, int *b, int *pri_a, int *pri_b) {
    int temp = *a;
    *a = *b;
    *b = temp;
    temp = *pri_a;
    *pri_a = *pri_b;
    *pri_b = temp;
}

// 上浮操作，维护最小堆性质
void heapifyUp(File *f, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (f->priorities[index] >= f->priorities[parent]) {
            break;
        }
        swap(&f->elements[index], &f->elements[parent], &f->priorities[index], &f->priorities[parent]);
        index = parent;
    }
}

// 入队操作
File enfiler(int elt, int priority, File f) {
    if (f.size == f.capacity) {
        // 扩容
        f.capacity *= 2;
        f.elements = (int *)realloc(f.elements, f.capacity * sizeof(int));
        f.priorities = (int *)realloc(f.priorities, f.capacity * sizeof(int));
        if (f.elements == NULL || f.priorities == NULL) {
            fprintf(stderr, "Memory reallocation failed\n");
            exit(EXIT_FAILURE);
        }
    }
    f.elements[f.size] = elt;
    f.priorities[f.size] = priority;
    heapifyUp(&f, f.size);
    f.size++;
    return f;
}

// 下沉操作，维护最小堆性质
void heapifyDown(File *f, int index) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int smallest = index;

    if (left < f->size && f->priorities[left] < f->priorities[smallest]) {
        smallest = left;
    }
    if (right < f->size && f->priorities[right] < f->priorities[smallest]) {
        smallest = right;
    }
    if (smallest != index) {
        swap(&f->elements[index], &f->elements[smallest], &f->priorities[index], &f->priorities[smallest]);
        heapifyDown(f, smallest);
    }
}

// 出队操作
File defiler(File f) {
    if (f.size == 0) {
        fprintf(stderr, "Queue is empty\n");
        exit(EXIT_FAILURE);
    }
    f.elements[0] = f.elements[f.size - 1];
    f.priorities[0] = f.priorities[f.size - 1];
    f.size--;
    heapifyDown(&f, 0);
    return f;
}

// 释放优先队列的内存
void freeFile(File f) {
    free(f.elements);
    free(f.priorities);
}

// 示例使用
int main() {
    File f = initF();
    f = enfiler(1, 3, f);
    f = enfiler(2, 1, f);
    f = enfiler(3, 2, f);

    while (f.size > 0) {
        int top = sommetF(f);
        printf("Top element: %d\n", top);
        f = defiler(f);
    }

    freeFile(f);
    return 0;
}