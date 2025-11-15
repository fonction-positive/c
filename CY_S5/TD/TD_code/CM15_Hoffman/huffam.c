//
// Created by 金卓远 on 24-11-26.
//

#include "Hoffman.h"
#include"TasMin.h"

void printTab(int *tab, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", tab[i]);
    }
    printf("\n");
}

int main() {
    const char *testMsg = "abcba";
    int nbCarAlph = 6; // 字母表的大小 (a-z)
    int freq[]={450,130,120,160,90,50,0,0,0,0,0}; // 包括叶子和内部节点
    int pere[2 * nbCarAlph - 1];
    int filsG[2 * nbCarAlph - 1];
    int filsD[2 * nbCarAlph - 1];
    int racine = -1;

    // 初始化扩展频率部分
    for (int i = nbCarAlph; i < 2 * nbCarAlph - 1; i++) {
        freq[i] = 0;
    }

    int nbCarAlphFreq = calculFreq(nbCarAlph, testMsg, freq);
    printf("%d\n", nbCarAlphFreq);
    printTab(freq, nbCarAlph);


    creatArbreHuffman(6, 6, freq, pere, filsG, filsD, racine);

    printTab(pere,2 * nbCarAlph - 1);
}
