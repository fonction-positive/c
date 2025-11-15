#ifndef S_G_H    // 防止头文件重复包含
#define S_G_H

// FileSucce：使用数组实现的后继表示法
// MatriceAdj：使用二维数组实现的邻接矩阵表示法
// ListeAdj：使用链表实现的邻接表表示法
// ListeSP：同时存储前驱和后继信息的表示法

// 文件后继表示法结构体
typedef struct{
    int nbSom;     // 图中顶点的数量
    int nbArcs;    // 图中边的数量
    int *FS;       // 后继表数组(Forward Star)，存储所有顶点的后继节点
    int *APS;      // 顶点位置数组(Access Position)，存储每个顶点在FS中的起始位置
}FileSucce;

// 邻接矩阵表示法结构体
typedef struct{
    int nbsom;     // 图中顶点的数量
    int ** mat;    // 二维数组存储邻接矩阵，mat[i][j]=1表示存在从i到j的边
}MatriceAdj;

// 链表节点结构体
typedef struct  cellul{
    int SomSucce;              // 后继顶点的编号
    struct cellul * suivant;   // 指向下一个节点的指针
}* Liste;

// 邻接表表示法结构体
typedef struct{
    int nbsom;    // 图中顶点的数量
    Liste* tab;   // 指针数组，每个元素指向一个顶点的后继链表
}ListeAdj;

// 前驱后继表节点结构体
typedef struct {
    Liste ListeSucce;    // 后继顶点链表
    Liste ListePrece;    // 前驱顶点链表
}SP;

// 前驱后继表表示法结构体
typedef struct{
    int nbSom;    // 图中顶点的数量
    SP* tab;      // 存储每个顶点的前驱和后继链表的数组
}ListeSP;




#endif
