//
// Created by 金卓远 on 24-12-13.
//
#include <string.h>

#include"TasMin.h"
//频率函数 nbCarAlph=26(a~z)
int calculFreq(int nbCarAlph, const char *msg, int *freq) {
    //初始化频率数组
    for (int i = 0; i < nbCarAlph; i++) {
        freq[i] = 0;
    }
    //获取adeASCII值
    int codeA = 'a';

    //计算字符串长度
    int lgMsg = strlen(msg);

    //计算频率
    for (int i = 0; i < lgMsg; i++) {
        int numCar = msg[i] - codeA; //当前字母在freq中的索引
        if (numCar >= 0 && numCar < nbCarAlph) {
            freq[numCar]++;
        }
    }

    //统计出现次数非零的字母
    int nb = 0;
    for (int i = 0; i < nbCarAlph; i++) {
        if (freq[i] > 0) {
            nb++;
        }
    }
    return nb;
}


int main() {
    const char *msg = "abcac";  // 测试消息
    int nbCarAlph = 26;  // 字母表大小
    int freq[26];  // 存储每个字母的频率

    // 计算频率
    calculFreq(nbCarAlph, msg, freq);

    printf("Fréquences des lettres :\n");
    for (int i = 0; i < nbCarAlph; i++) {
        if (freq[i] > 0) {
            printf("%c: %d\n", 'a' + i, freq[i]);
        }
    }

    // 创建最小堆
    Tas tas = allocMemAP(nbCarAlph);
    tas = initAP(tas);

    // 插入最小堆的节点
    for (int c = 0; c < nbCarAlph; c++) {
        if (freq[c] > 0) {
            tas = inserTasMin(c, tas, freq);  // 插入频率最小的节点
        }
    }

    // 打印最小堆的内容
    printf("\nÉtat du tas (après insertion) :\n");
    for (int i = 0; i < tas.taille; i++) {
        printf("%c: %d\n", 'a' + tas.tab[i], freq[tas.tab[i]]);
    }

    // 删除最小堆的最小元素
    tas = suppTasMin(tas, freq);

    // 打印堆删除后的状态
    printf("\nÉtat du tas (après suppression) :\n");
    for (int i = 0; i < tas.taille; i++) {
        printf("%c: %d\n", 'a' + tas.tab[i], freq[tas.tab[i]]);
    }
}
