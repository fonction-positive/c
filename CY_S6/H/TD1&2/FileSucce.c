#include <stdio.h>
#include <stdlib.h>
#include "StructGraphe.h"

// 创建 FileSucce 结构体并分配内存
FileSucce createFileSucce(int nbsom, int nbarc) {
    FileSucce fs;
    fs.nbSom = nbsom;
    fs.nbArcs = nbarc;

    // 分配内存
    fs.APS = (int*)malloc((nbsom + 1) * sizeof(int));
    if (fs.APS == NULL) {
        printf("Memory allocation failed for APS.\n");
        exit(1);  // 内存分配失败，退出程序
    }

    fs.FS = (int*)malloc(nbarc * sizeof(int));
    if (fs.FS == NULL) {
        printf("Memory allocation failed for FS.\n");
        free(fs.APS);  // 释放之前分配的内存
        exit(1);
    }

    return fs;
}

// 检查是否存在循环
int estBoucle(FileSucce fs) {
    int n = fs.nbSom;
    int s = 0;
    int nbSucc = 0;
    int j = 0;
    int iAps = 0;
    int flag = 0;
    
    while (s < n && flag == 0) {
        nbSucc = fs.APS[s + 1] - fs.APS[s]; // 当前节点的后继数量
        iAps = fs.APS[s];  // 从当前节点的起始位置开始
        
        for (j = 0; j < nbSucc && flag == 0; j++) {
            if (fs.FS[iAps + j] == s) {
                flag = 1; // 找到一个指向自己，即存在循环
            }
        }
        s++;  // 遍历下一个节点
    }
    return flag;
}

// 打印节点 s 的后继节点
void sommSucce(int s, FileSucce fs) {
    int nbSucc = fs.APS[s + 1] - fs.APS[s];  // 计算后继节点的数量
    printf("Les somme success de %d sont: \n", s+1);
    for (int i = fs.APS[s]; i < fs.APS[s] + nbSucc; i++) {
        printf("%d ", fs.FS[i]+1);
    }
    printf("\n");
}

// 返回后继最多的节点
int MaxSomSucce(FileSucce fs) {
    int MaxS = 0;    // 用于存储最大后继节点的索引
    int MaxSu = 0;   // 用于存储最多的后继数
    for (int i = 0; i < fs.nbSom; i++) {
        int nbSucc = fs.APS[i + 1] - fs.APS[i];  // 当前节点的后继数量
        if (nbSucc > MaxSu) {
            MaxSu = nbSucc;
            MaxS = i;  // 更新最大后继节点
        }
    }
    return MaxS;
}

int main(void){
    FileSucce fs;
    int n,s;
    fs=createFileSucce(7,5);
    int i;
    // 输入 APS 数组的值
    printf("Pour APS:\n");
    for (int i = 0; i < 8; i++) {
        printf("Entrez APS[%d]: ", i);
        scanf("%d", &n);
        fs.APS[i] = n;
    }
    // 输入 FS 数组的值
    printf("Pour FS:\n");
    for (int i = 0; i < 5; i++) {
        printf("Entrez FS[%d]: ", i);
        scanf("%d", &n);
        fs.FS[i] = n;
    }
    printf("EstBoucle? %d\n",estBoucle(fs));
    s=MaxSomSucce(fs);
    sommSucce(s,fs);
}