//
// Created by 金卓远 on 24-12-13.
//

#ifndef TASMIN_H
#define TASMIN_H
#include <stdlib.h>

#include"../CM14_ArbreParfait_Tas/Tas.h"

int *freq;

TElement minTas(Tas tm) {
    return tm.tab[0];
}

Tas inserTasMin(int e,Tas t,int *freq) {
    int n=t.taille;
    if (n==0) {
        t.tab[n]=e;
        t.taille++;
    }else {
        int p=(n-1)/2;
        int dp=t.tab[p];
        while (n>0 && freq[dp] > freq[e]) { //插入最小堆
            t.tab[n]=dp;
            n=p;
            p=(n-1)/2;
            dp=t.tab[p];
        }
        t.tab[n]=e;
        t.taille++;
    }
    return t;
}

Tas suppTasMin(Tas tas, int *freq) {
    int r = 0; // 根节点
    int dn = tas.taille - 1; // 最后一个节点
    int e; // 临时存储节点

    // 将最后一个节点移动到根节点
    tas.tab[r] = tas.tab[dn];
    tas.taille--; // 减少堆大小

    // 如果堆不为空，重新调整堆
    if (tas.taille > 0) {
        e = tas.tab[r]; // 当前根节点值
        bool verif = false; // 是否需要进一步调整
        int fg = filsGaucheAP(r); // 左子节点索引
        int fmin;

        // 下沉操作，确保最小堆性质
        while (!verif && estExistNoeud(fg,tas)) {
            fmin = fg; // 假设左子节点是更小的子节点
            int fd = filsDroitAP(r); // 右子节点索引

            // 如果右子节点存在且小于左子节点，更新 fmin
            if (estExistNoeud(fd, tas) && freq[tas.tab[fd]] < freq[tas.tab[fg]]) {
                fmin = fd;
            }

            // 如果当前节点小于等于 fmin 子节点，停止调整
            if (freq[e] <= freq[tas.tab[fmin]]) {
                verif = true;
            } else {
                // 否则，将 fmin 子节点的值上移，继续下沉
                tas.tab[r] = tas.tab[fmin];
                r = fmin;
                fg = filsGaucheAP(r);
            }
        }

        // 将初始的根节点值放在正确位置
        tas.tab[r] = e;
    }

    return tas;
}






#endif //TASMIN_H
