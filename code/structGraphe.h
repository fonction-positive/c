//
// Created by 金卓远 on 25-2-23.
//

#ifndef STRUCTGRAPHE_H
#define STRUCTGRAPHE_H

#define TCout int

/// Matrices d'indidence 关联矩阵
typedef struct {
    int nbArc; // 图中边的数量
    int nbSom; // 图中顶点的数量
    int **mat; // 二维数组存储关联矩阵，mat[i][j]表示顶点i与边j的关系
} MatInc;

//ligne par ligne
typedef struct{
    int nbSom ;
    int nbArcs ;
    int *FS ;  //按顺序存所有边（弧）
    int *APS ;  //存每个顶点第一条边在FS中的索引
    int *AS ;  //存每条边（弧）的终点
    //TCout *Cout ;
} MatIncidLigLig ;

//colone par colone
typedef struct{
    int nbSom ;
    int nbArcs ;
    int *alpha ; //每条边的起点
    int *beta ; //每条边的终点
    //TCout *Cout ;
} MatIncidColCol ;


/// a)Matrices d’adjacence 数组
typedef struct {
    int nbSom; //顶点数量
    int **mat; //邻接矩阵
    int **cout; //边权矩阵
} MatAdj;

/// b) liste d'adjacence 邻接列表
//每个顶点的链表
typedef struct cellule {
    int somSucc;
    int cout;
    struct cellule *suiv;
    
} *Liste;

//邻接列表
typedef struct {
    int nbSom; //顶点数量
    Liste *tabAdj; //顶点数组
} ListeAdj;

/// c)file des successeurs 后继队列
typedef struct {
    int nbSom;
    int nbArcs;
    int *FS; //一维数组，存储所有非空的后继列表
    int *APS; //一维数组，长度为  n+1 （包括虚拟顶点  n+1 ），存储每个顶点后继在FS中的起始索引
    // TCout *cout; //权重
} FileSucc;


/// d) LASP 前驱后继链表
typedef struct {
    Liste lSucc; //Liste de successeurs
    Liste lPred; //Liste de Predecesseurs
} ListeSuccPred;

typedef struct {
    int nbSom; //图中顶点的数量
    ListeSuccPred *tabAdjSP; //存储每个顶点的后继和前驱列表
} ListeAdjSuccPred;


///LP ListePrincipal
typedef struct cellulelp *ListeSucc ;
typedef struct listPrincipale *ListePrincipale ;
struct listPrincipale {
    int numSom ;
    ListePrincipale suivLP ;
    ListeSucc lSucc ;
};
struct cellulelp{
    ListePrincipale succ ;
    // TCout cout ;
    ListeSucc suivLS ;
};

#endif //STRUCTGRAPHE_H
