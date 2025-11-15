//
// Created by 金卓远 on 24-12-3.
//

#include "Tas.h"
#include "ArbreParfait.h"


#include <stdio.h>
#include <math.h>
#include <string.h>


void printTree(int *tree, int n);
void printTab(int *tab,int n);


int main() {
    // Tas t=allocMemAP(20);
    // t=initAP(t);
    // t=inserTas(2,t);
    // t=inserTas(3,t);
    // t=reInserTas(t.taille,4,t);
    // t=reInserTas(t.taille,8,t);

    int tab[]={2,3,5,1,5,6,7};
    int n=sizeof(tab)/sizeof(tab[0]);

    Tas t=transTabTas(tab,n);
    //
    // printf("%d\n",estTasV1(t.taille,t.tab));
    // printf("%d\n",reEstTasV1(t.taille,t.tab));
    // printf("%d\n",estTasV2(t.taille,t.tab));
    // printf("%d\n",reEstTasV2(0,t.taille,t.tab));

    printTree(t.tab,t.taille);
    // ParcoursPrefixe(0,t);

    t=suppTas(t);
    printTree(t.tab,t.taille);

    t=reSuppTas(t);
    printTree(t.tab,t.taille);



    // printTab(tab,n);
    // TriParTas(tab,n);
    // printTab(tab,n);


}



void printTab(int *tab,int n) {
    for (int i=0;i<n;i++) {
        printf("%d ",tab[i]);
    }
    printf("\n");
}


// 打印以数组表示的二叉树
void printTree(int *tree, int n) {
    if (n == 0) {
        printf("树为空！\n");
        return;
    }

    int height = log2(n) + 1; // 计算树的高度

    for (int h = 0; h < height; h++) {
        int levelWidth = pow(2, h); // 当前层的节点数
        int startIdx = pow(2, h) - 1; // 当前层第一个节点的索引
        int endIdx = fmin(startIdx + levelWidth, n); // 当前层最后一个节点的索引（不超出数组范围）
        int spaceBetween = pow(2, height - h) - 1; // 节点间的空格数量
        int indent = spaceBetween / 2; // 前置缩进

        // 打印当前层的缩进
        for (int i = 0; i < indent; i++) printf("  ");

        // 打印当前层节点
        for (int i = startIdx; i < endIdx; i++) {
            printf("%2d", tree[i]);
            if (i < endIdx - 1) {
                for (int j = 0; j < spaceBetween; j++) printf("  ");
            }
        }
        printf("\n");

        // 打印斜杠（用于连接当前层和下一层）
        if (h < height - 1) {
            for (int i = 0; i < indent; i++) printf("  "); // 前置缩进
            for (int i = 0; i < levelWidth && (startIdx + i) < n; i++) {
                int leftIndex = 2 * (startIdx + i) + 1; // 左子节点索引
                int rightIndex = leftIndex + 1; // 右子节点索引
                if (leftIndex < n) printf(" /");
                else printf("  ");
                if (rightIndex < n) printf(" \\");
                else printf("  ");
                if (i < levelWidth - 1) {
                    for (int j = 0; j < spaceBetween - 1; j++) printf("  ");
                }
            }
            printf("\n");
        }
    }
}

