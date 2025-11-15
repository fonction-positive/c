//
// Created by 金卓远 on 24-12-13.
//

#ifndef HOFFMAN_H
#define HOFFMAN_H
#include <stdio.h>
#include<string.h>
#include "TasMin.h"

int calculFreq(int nbCarAlph, const char *msg, int *freq);
void creatArbreHuffman(int nbCarAlph, int nbCarAlphFreq, int *freq, int *pere, int *filsG, int *filsD, int racine);
//获取某个节点的编码
char *codage(int nd, int *pere);
//生成编码表
void CreatTableCodage(int nbCarAlph, int *freq, int *pere, char **tabCod);
void CodageTexte(const char *MsgSrc, char **tabCode, char *MsgCode);


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


void creatArbreHuffman(int nbCarAlph, int nbCarAlphFreq, int *freq, int *pere, int *filsG, int *filsD, int racine) {
    Tas tas = allocMemAP(nbCarAlph);
    tas = initAP(tas);

    for (int c = 0; c < nbCarAlph; c++) {
        if (freq[c] > 0) {
            //如果这个字母出现的次数不为0
            inserTasMin(c, tas, freq); //则把他插到tas里
        }
        filsG[c] = -1; //-1表示没有值
        filsD[c] = -1;
    }
    for (int c = nbCarAlph; c < nbCarAlph + nbCarAlphFreq - 1; c++) {
        //取出出现次数最少得两个
        int c1 = minTas(tas);
        tas = suppTasMin(tas, freq);
        int c2 = minTas(tas);
        tas = suppTasMin(tas, freq);

        //创建一个新节点，插入到tasMin中
        freq[c] = freq[c1] + freq[c2];
        pere[c1] = -c; //负的说明是左分支，正的是右分支
        pere[c2] = c;
        filsG[c] = c1;
        filsD[c] = c2;
        tas = inserTasMin(c, tas, freq);
    }
    racine = minTas(tas);
    tas = suppTasMin(tas, freq);
    pere[racine] = -1;

    free(tas.tab);
}

//获取某个节点的编码
char *codage(int nd, int *pere) {
    if (pere[nd] == -1) {
        //返回空字符串
        char *chinevide = (char *) malloc(1);
        chinevide[0] = '\0';
        return chinevide;
    }

    //递归调用获取父亲的编码
    char *codeParent = codage(abs(pere[nd]), pere);
    //为新字符串分配空间，并把父亲编码和当前编码拼接
    int lg = strlen(codeParent);
    char *res = malloc(lg + 2); //+2:一个新字符和‘\0’
    strcpy(res, codeParent);
    //根据pere[nd]正负决定0，1
    res[lg] = pere[nd] < 0 ? '0' : '1';
    res[lg + 1] = '\0';

    free(codeParent);
    return res;
}

//生成编码表
void CreatTableCodage(int nbCarAlph, int *freq, int *pere, char **tabCod) {
    for (int c = 0; c < nbCarAlph; c++) {
        if (freq[c] > 0) {
            tabCod[c] = codage(c, pere);
        }
    }
}

//遍历texte把每个字符替换成编码
void CodageTexte(const char *MsgSrc, char **tabCode, char *MsgCode) {
    MsgCode[0] = '\0';
    int lenMsg = strlen(MsgSrc); //获取输入字符串的长度
    for (int i = 0; i < lenMsg; i++) {
        char c = MsgSrc[i];
        strcat(MsgCode, tabCode[c]);
    }
}

void decodage_it(char *MsgCode, int Racine, int FG[], int FD[], char *MsgSrc, char Alphabet[]) {
    int lgMsgCode = strlen(MsgCode); // 计算消息代码的长度
    int ind = 0;                    // 初始化索引为0
    bool Erreur = false;            // 错误标志初始化为false
    MsgSrc[0] = '\0';               // 初始化目标消息字符串为空

    // 当索引小于消息代码长度 且 没有错误时，继续循环
    while (ind < lgMsgCode && !Erreur) {
        // 调用已知的decodage函数
        decodage(ind, lgMsgCode, MsgCode, MsgSrc, Racine, FG, FD, Alphabet);
    }

    // 结束函数
    return;
}



// 判断是否为叶子节点
bool estFeuille(int racine, int FG[], int FD[]) {
    return (FG[racine] == -1 && FD[racine] == -1);
}

// Decodage函数的实现
void Decodage(int *ind, int lgMsgCode, char MsgCode[], char MsgSrc[], int *racine, int FG[], int FD[], char Alphabet[]) {
    if (*ind < lgMsgCode) {
        // 判断当前节点是否为叶子节点
        if (estFeuille(*racine, FG, FD)) {
            // 将当前叶子节点的字符加入解码字符串
            int len = strlen(MsgSrc);
            MsgSrc[len] = Alphabet[*racine];
            MsgSrc[len + 1] = '\0'; // 添加结束符
        } else {
            // 根据当前消息编码判断下一步方向
            if (MsgCode[*ind] == '0') {
                *racine = FG[*racine]; // 走向左子树
            } else {
                *racine = FD[*racine]; // 走向右子树
            }
            (*ind)++; // 更新索引位置

            // 递归调用 Decodage 函数
            Decodage(ind, lgMsgCode, MsgCode, MsgSrc, racine, FG, FD, Alphabet);
        }
    }
}

// 函数：计算树的高度
int hauteurArbre(int* Pere, int n) {
    int hauteur = 0;

    // 用一个数组来存储每个节点的深度
    int profondeur[n];
    for (int i = 0; i < n; i++) {
        profondeur[i] = -1; // 初始化为-1，表示尚未计算
    }

    // 计算每个节点的深度
    for (int i = 0; i < n; i++) {
        int profondeurCourante = 0;
        int courant = i;
        
        while (courant != -1) { // 遍历到根节点
            if (profondeur[courant] != -1) {
                profondeurCourante += profondeur[courant];
                break;
            }
            profondeurCourante++;
            courant = Pere[courant];
        }
        
        profondeur[i] = profondeurCourante; // 存储深度
        if (profondeurCourante > hauteur) {
            hauteur = profondeurCourante; // 更新最大高度
        }
    }

    return hauteur;
}

#endif //HOFFMAN_H
