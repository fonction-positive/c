//
// Created by 金卓远 on 25-4-2.
//

#ifndef PLUS_COURT_CHEMIN_H
#define PLUS_COURT_CHEMIN_H
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

/// a)Matrices d’adjacence 邻接矩阵
// 定义图的邻接矩阵和边权矩阵的结构体
typedef struct {
    int nbSom; // 顶点数量
    int **mat; // 邻接矩阵
    int **cout; // 边权矩阵
} MatAdj;

/// b) liste d'adjacence 邻接链表
//每个顶点的链表
typedef struct cellule {
    int somSucc;
    int cout;
    struct cellule *suiv;
} *Liste;

typedef struct {
    int nbSom; //顶点数量
    Liste *tabAdj; //顶点数组
} ListeAdj;

typedef struct {
    int taille;      // 当前堆大小
    int tailleMax;   // 最大容量
    int *tab;        // 存储堆中元素的数组（顶点索引）
    int *pos;        // 存储每个元素在堆中的位置
} TasMin;

typedef struct {
    int s;
    int t;
    int cout;
}Arete;

//MST
typedef struct {
    int nbSom; // 顶点数
    int nbArete; // 边数
    Arete *arete; //边集
} MICC;

//Ensemble(优先队列）


typedef struct {
    int taille;
    int tailleMax;
    Arete *arete;
}Ensemble;


int* allocTab(int n);
void libTab(int* tab);
void printAdjacencyMatrix(MatAdj G); // 打印邻接矩阵
void printWeightMatrix(MatAdj G); // 打印边权矩阵
void printDP(int *D, int *P, int n); //打印距离数组D和前驱数组 P
void printDPMat(int **D, int **P, int n);

MatAdj allocMatAdj(int n);
void freeMatAdj(MatAdj G);

ListeAdj allocListeAdj(int n);
void freeListeAdj(ListeAdj l);
Liste inserTete(Liste l, int s, int cout); // 在链表头部插入新节点
ListeAdj Mat_Liste(MatAdj ma); //Mat转Liste
ListeAdj matrixToAdjList(int **matrix, int nbSom);
void printListeAdj(ListeAdj l); // 打印邻接列表

//miniTas
TasMin allocMemTas(int nbSom);
TasMin libMemTas(TasMin M);
TasMin initTas(TasMin M);
int estVideTas(TasMin M);
int minTas(TasMin M) ;
TasMin inserTas(int t, int *D, TasMin M); // Priorité est fonction
TasMin suppMinTas(int *D, TasMin M); // des distances D[t]

MICC allocMICC(int nbSom,int nbArete);
void printMICC(MICC t);

Ensemble allocEnsemble(int initialCapacity);


// 定义优先队列（File）结构体
typedef struct {
    int *elements;  // 存储元素的数组
    int *priorities; // 存储元素优先级（距离）的数组
    int capacity;  // 队列容量
    int size;      // 当前队列元素数量
} File;


File initF();
int estVideF(File f);
// 获取队列头部元素（优先级最小的元素）
int sommetF(File f);
File enfiler(int elt, int priority, File f);
File defiler(File f);
void freeFile(File f);



#endif //PLUS_COURT_CHEMIN_H
