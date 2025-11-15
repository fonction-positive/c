//
// Created by 金卓远 on 24-12-14.
//

#ifndef AVL_H
#define AVL_H
#include <stdio.h>
#include <stdlib.h>
typedef int TElement;

typedef struct noeud {
    int hauteur;
    TElement donne;
    struct noeud *filsG;
    struct noeud *filsD;
} *AVL;

TElement donnee(AVL a);
AVL filsGauche(AVL a);
AVL filsDroit(AVL a);
int hauteur(AVL a);
AVL initAVL();
int estVideAVL(AVL a);
int estFeuilleAVL(AVL a);
AVL creatFeuille(TElement elt);
AVL creatNoeud(TElement elt, AVL fg, AVL fd);
int haut(AVL a);
int max(int a, int b);
void parcoursPre(AVL a);
void parcoursIn(AVL a);
void parcoursPost(AVL a);
int factEquilibre(AVL a);
AVL rotationG(AVL a);
AVL rotationD(AVL a);
AVL rotationGD(AVL a);
AVL rotationDG(AVL a);
AVL inserAVL(TElement elt, AVL a);
AVL equilibrage(AVL a);
AVL suppEltAVL(TElement elt, AVL a);
AVL suppRacineAVL(AVL a);
TElement suppMaxAVL(AVL *a);
int estAVL(AVL a);
// 中序遍历并填充数组
void remplirTableau(AVL a, TElement *arr, int *index);



TElement donnee(AVL a) {
    return a->donne;
}

AVL filsGauche(AVL a) {
    return a->filsG;
}

AVL filsDroit(AVL a) {
    return a->filsD;
}

int hauteur(AVL a) {
    return a->hauteur;
}

AVL initAVL() {
    return NULL;
}

int estVideAVL(AVL a) {
    return a == NULL;
}

int estFeuilleAVL(AVL a) {
    return estVideAVL(a->filsG) && estVideAVL(a->filsD);
}

AVL creatFeuille(TElement elt) {
    AVL f = (AVL) malloc(sizeof(struct noeud));
    if (estVideAVL(f)) {
        printf("pb de memoire");
        exit(1);
    }
    f->donne = elt;
    f->filsD = NULL;
    f->filsG = NULL;
    f->hauteur = 0;
    return f;
}

AVL creatNoeud(TElement elt, AVL fg, AVL fd) {
    AVL nd = (AVL) malloc(sizeof(struct noeud));
    if (estVideAVL(nd)) {
        printf("pb de memoire");
        exit(1);
    }
    nd->donne = elt;
    nd->filsD = fd;
    nd->filsG = fg;
    nd->hauteur = 1 + max(haut(fg), haut(fd));
    return nd;
}

int haut(AVL a) {
    return (a == NULL) ? -1 : hauteur(a);
}

int max(int a, int b) {
    return a > b ? a : b;
}

void parcoursPre(AVL a) {
    if (!estVideAVL(a)) {
        printf("%d ", donnee(a));
        parcoursPre(filsDroit(a));
        parcoursPre(filsGauche(a));
    }
}

void parcoursIn(AVL a) {
    if (!estVideAVL(a)) {
        parcoursIn(a->filsG);
        printf("%d ", a->donne);
        parcoursIn(a->filsD);
    }
}

void parcoursPost(AVL a) {
    if (!estVideAVL(a)) {
        parcoursPost(a->filsG);
        parcoursPost(a->filsD);
        printf("%d ", a->donne);
    }
}

int factEquilibre(AVL a) {
    int hd = haut(a->filsD);
    int hg = haut(a->filsG);
    return hd - hg;
}

AVL rotationG(AVL a) {
    AVL p = a;
    AVL q = filsDroit(a);
    AVL u = filsGauche(a);
    AVL v = filsGauche(q);
    AVL w = filsDroit(q);
    q->filsG = p;
    p->filsD = v;
    p->hauteur = 1 + max(haut(u), haut(v));
    q->hauteur = 1 + max(haut(p), haut(w));
    return q;
}

AVL rotationD(AVL a) {
    AVL q = a;
    AVL p = filsGauche(a);
    AVL w = filsDroit(a);
    AVL u = filsGauche(p);
    AVL v = filsDroit(p);
    p->filsD = q;
    q->filsG = v;
    q->hauteur = 1 + max(haut(v), haut(w));
    p->hauteur = 1 + max(haut(u), haut(q));
    return p;
}

AVL rotationGD(AVL a) {
    a->filsG = rotationG(filsGauche(a));
    return rotationD(a);
}

AVL rotationDG(AVL a) {
    a->filsD = rotationD(filsDroit(a));
    return rotationG(a);
}

AVL inserAVL(TElement elt, AVL a) {
    if (estVideAVL(a)) {
        return creatFeuille(elt);
    }
    if (donnee(a) == elt) {
        return a;
    }
    if (elt < donnee(a)) {
        a->filsG = inserAVL(elt, filsGauche(a));
    } else {
        a->filsD = inserAVL(elt, filsDroit(a));
    }
    return equilibrage(a);
}

AVL equilibrage(AVL a) {
    if (estVideAVL(a)) {
        return a;
    }
    int fact = factEquilibre(a);
    if (fact == -2) {
        if (factEquilibre(filsGauche(a)) <= 0) {
            a = rotationD(a);
        } else {
            a = rotationGD(a);
        }
    }
    if (fact == 2) {
        if (factEquilibre(filsDroit(a)) >= 0) {
            a = rotationG(a);
        } else {
            a = rotationDG(a);
        }
    }

    a->hauteur = 1 + max(haut(filsGauche(a)), haut(filsDroit(a)));
    return a;
}

AVL suppEltAVL(TElement elt, AVL a) {
    if (estVideAVL(a)) {
        return a;
    }
    TElement da = donnee(a);
    if (da == elt) {
        return suppRacineAVL(a);
    }
    if (da > elt) {
        a->filsG = suppEltAVL(elt, filsGauche(a));
    } else {
        a->filsD = suppEltAVL(elt, filsDroit(a));
    }
    return equilibrage(a);
}

// 从右子树中删除最小节点
TElement suppMinAVL(AVL *a) {
    if (estVideAVL(filsGauche(*a))) {
        // 如果左子树为空，当前节点就是最小节点
        TElement minValue = donnee(*a);
        AVL tmp = *a;
        *a = filsDroit(*a);  // 用右子树替代当前节点
        free(tmp);
        return minValue;
    }
    return suppMinAVL(&(*a)->filsG);  // 递归查找右子树中的最小节点
}


AVL suppRacineAVL(AVL a) {
    AVL r = a;
    AVL fg = filsGauche(a);
    AVL fd = filsDroit(a);
    if (estFeuilleAVL(a)) {
        a = NULL;
        free(r);
        return a;
    }
    if (estVideAVL(fg)) {
        a = fd;
        free(r);
        return equilibrage(a);
    }
    if (estVideAVL(fd)) {
        a = fg;
        free(r);
        return equilibrage(a);
    }
    a->donne = suppMaxAVL(&a->filsG);
    return equilibrage(a);
}

TElement suppMaxAVL(AVL *a) {
    if (estVideAVL((*a)->filsD)) {
        // 当前节点是最大节点
        TElement eMax = (*a)->donne;
        AVL temp = *a;
        *a = (*a)->filsG;  // 用左子树代替当前节点
        free(temp);        // 释放当前节点的内存
        return eMax;
    } else {
        // 递归找到右子树的最大节点
        TElement eMax = suppMaxAVL(&((*a)->filsD));
        (*a)->hauteur = 1 + max(haut((*a)->filsG), haut((*a)->filsD));  // 更新高度
        *a = equilibrage(*a);  // 平衡树
        return eMax;
    }
}

int estAVL(AVL a) {
    if (estVideAVL(a) || estFeuilleAVL(a)) {
        return 1;
    }
    if (factEquilibre(a) > 1 || factEquilibre(a) < -1) {
        return 0;
    }
    return estAVL(filsGauche(a)) && estAVL(filsDroit(a));
}

// 中序遍历并填充数组
void remplirTableau(AVL a, TElement *arr, int *index) {
    if (a != NULL) {
        remplirTableau(a->filsG, arr, index);
        arr[(*index)++] = a->donne;
        remplirTableau(a->filsD, arr, index);
    }
}



#endif //AVL_H
