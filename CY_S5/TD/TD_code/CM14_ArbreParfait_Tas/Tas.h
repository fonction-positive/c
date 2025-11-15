//
// Created by 金卓远 on 24-12-3.
//

#ifndef TAS_H
#define TAS_H
#include <stdbool.h>
#include "ArbreParfait.h"

typedef int TElement;
typedef ArbreParfait Tas;
// typedef struct tas {
//     int tailleMax;
//     int taille;
//     TElement *tab;
// }Tas;


TElment maxTas(Tas t);
Tas inserTas(TElement elt, Tas t);
Tas reInserTas(int n, TElement elt, Tas t);
Tas heapifierBas(int r, Tas t);
Tas reSuppTas(Tas t);
Tas transTabTas(int *arr, int n);
void TriParTas(int *tab, int n);
int estTasV1(int n, int *tab);
int reEstTasV1(int n, int *tab);
int estTasV2(int n, int *tab);
int reEstTasV2(int i, int n, int *tab);



//返回堆顶元素（对于tas max）
TElment maxTas(Tas t) {
    return t.tab[0];
}


Tas inserTas(TElement elt, Tas t) {
    int n = taille(t);
    if (n == 0) {
        //如果tas是空
        t.tab[0] = elt;
        t.taille = 1;
    } else {
        int p = pereAP(n); //找到插入元素父节点的位置
        int dp = donneAP(p, t); //获取父亲节点donnee，用于比较
        while (n > 0 && elt > dp) {
            //如果比父节点大就交换，一直比较直到racine
            t.tab[n] = dp; //让子节点的值等于父节点
            n = p; //子节点变成父节点
            p = pereAP(n);
            dp = donneAP(p, t);
        }
        //直到n=0（n到了racine的位置）或者 elt<dp (小于父节点）退出循环
        t.tab[n] = elt;
        t.taille++;
    }
    return t;
}

Tas reInserTas(int n, TElement elt, Tas t) {
    if (n == 0) {
        t.tab[0] = elt;
        t.taille++;
        return t;
    }
    int p = pereAP(n);
    int dp = donneAP(p, t);
    if (elt > dp) {
        t.tab[n] = dp;
        n = p;
        return reInserTas(n, elt, t);
    }
    t.tab[n] = elt;
    t.taille++;
    return t;
}

// Tas Max 删除节点，就是删除racine，将最后一个换到racine，然后比较左右子节点，哪个小就和拿个换
Tas suppTas(Tas t) {
    int r = 0; // nœud racine
    int dn = taille(t) - 1; // dernier nœud
    t.tab[r] = donneAP(dn, t); // Placer le dernier nœud à la racine
    t.taille--; // Décrémenter la taille du tas

    int e = donneAP(r, t);
    bool verif = false;
    int fg = filsGaucheAP(r);

    while (!verif && estExistNoeud(fg,t)) {
        int fd = filsDroitAP(r);
        int fmax = fg;

        // Vérification de l’existence du fils droit et recherche du maximum
        if (estExistNoeud(fd, t) && donneAP(fd, t) > donneAP(fg, t)) {
            fmax = fd;
        }

        if (e >= donneAP(fmax, t)) {
            verif = true;
        } else {
            t.tab[r] = donneAP(fmax, t);
            r = fmax;
            fg = filsGaucheAP(r);
        }
    }

    // Placer la donnée de la feuille à la bonne place
    t.tab[r] = e;
    return t;
}

// 递归调整堆的辅助函数
Tas ajusterTas(int r, int e, Tas t) {
    int fg = filsGaucheAP(r);
    if (!estExistNoeud(fg,t)) {
        t.tab[r] = e; // 如果没有左子节点，将当前值放入
        return t;
    }

    int fd = filsDroitAP(r);
    int fmax = fg;

    // 判断右子节点是否存在，且是否大于左子节点
    if (estExistNoeud(fd, t) && donneAP(fd, t) > donneAP(fg, t)) {
        fmax = fd;
    }

    // 如果当前值大于等于最大的子节点，停止调整
    if (e >= donneAP(fmax, t)) {
        t.tab[r] = e;
        return t;
    }

    // 否则，将最大子节点的值上移，并递归调整子树
    t.tab[r] = donneAP(fmax, t);
    ajusterTas(fmax, e, t);
}

// SuppMax 使用递归实现
Tas reSuppTas(Tas t) {
    int r = 0; // nœud racine
    int dn = taille(t) - 1; // dernier nœud
    int dernierValeur = donneAP(dn, t);

    // 将最后一个节点值移动到根节点并减少堆大小
    t.taille--;
    ajusterTas(r, dernierValeur, t); // 递归调整堆

    return t;
}



//将一个数组转化为Tas
Tas transTabTas(int *arr, int n) {
    Tas t = allocMemAP(n);
    for (int i = 0; i < n; i++) {
        t=inserTas(arr[i],t);
    }
    return t;
}


void TriParTas(int *tab, int n) {
    // Tas t = transTabTas(tab, n);
    Tas t=allocMemAP(n);
    t=initAP(t);
    for (int i=0;i<n;i++) {
        t=inserTas(tab[i],t);
    }
    for (int i = n - 1; i >= 0; i--) {
        tab[i] = t.tab[0];
        t = suppTas(t);
    }
    //free
    free(t.tab);
}

//从右往左比较验证
int estTasV1(int n, int *tab) {
    if (n <= 1) {
        return 1;
    }
    int r = 0;
    int nd = n - 1;
    int p = pereAP(nd);
    while (nd > r && tab[nd] <= tab[p]) {
        nd = nd - 1;
        p = pereAP(nd);
    }
    return nd == r; //如果比较到最后nd=0（nd=racine)就说明他是tasMax
}

int reEstTasV1(int n, int *tab) {
    if (n <= 1) {
        return 1;
    }
    int nd = n - 1;
    int p = pereAP(nd);
    if (tab[nd] > tab[p]) {
        return 0;
    }
    return reEstTasV1(nd, tab);
}

// 从左往右
int estTasV2(int n, int *tab) {
    for (int i = 0; i < n; i++) {
        int fg = filsGaucheAP(i);
        int fd = filsDroitAP(i);

        // 检查左子节点是否存在且满足堆性质
        if (fg < n && tab[i] < tab[fg]) {
            return 0;
        }

        // 检查右子节点是否存在且满足堆性质
        if (fd < n && tab[i] < tab[fd]) {
            return 0;
        }
    }
    return 1; // 如果全部检查通过，则是 Tas Max
}

int reEstTasV2(int i, int n, int *tab) {
    // 如果当前节点索引超出范围，返回 1 (空堆视为有效堆)
    if (i >= n) {
        return 1;
    }

    int fg = filsGaucheAP(i);
    int fd = filsDroitAP(i);

    // 检查左子节点是否满足堆性质
    if (fg < n && tab[i] < tab[fg]) {
        return 0;
    }

    // 检查右子节点是否满足堆性质
    if (fd < n && tab[i] < tab[fd]) {
        return 0;
    }

    // 递归检查左子树和右子树是否满足堆性质
    return reEstTasV2(fg, n, tab) && reEstTasV2(fd, n, tab);
}



#endif //TAS_H
