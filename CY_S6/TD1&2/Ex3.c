//
// Created by 金卓远 on 25-2-22.
//

#include "Ex3.h"

int main() {

    FileSucc fs;
    fs.nbSom = 3; // 顶点数
    fs.nbArcs = 6; // 边数

    // FS：存储所有后继
    //
    // int FS[] = {2, 3, 1, 2, 3, 1, 2, 4, 3};
    int FS[] = {1, 3, 1, 3, 1, 2};
    fs.FS = FS;

    // APS：存储每个顶点的后继在 FS 中的起始位置
    // int APS[] = {1, 3, 6, 9, 10};
    int APS[] = {1, 3, 5, 7};
    fs.APS = APS;

    // 测试打印每个顶点的后继节点
    // for (int i = 1; i <= fs.nbSom; i++) {
    //     printf("Les successeurs du sommet %d sont: ", i);
    //     somSucc3(i, fs);
    // }
    // somSucc3(1, fs);
    // printf("\n");
    somPred3(1, fs);


    return 0;
}
