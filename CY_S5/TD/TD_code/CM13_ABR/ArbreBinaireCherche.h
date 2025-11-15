//
// Created by 金卓远 on 24-12-14.
//

#ifndef ARBREBINAIRECHERCHE_H
#define ARBREBINAIRECHERCHE_H
#include <stdbool.h>
#include <sys/_types/_null.h>
#include<stdio.h>
#include <stdlib.h>

typedef int TElement;

typedef struct noeud {
    TElement donnee;
    struct noeud *filsG;
    struct noeud *filsD;
} *Arbre;

Arbre filsGauche(Arbre racine);
Arbre filsDroit(Arbre racine);
TElement donnee(Arbre racine);
Arbre initA();
int estVide(Arbre racine);
Arbre CreatFeuille(TElement elt);
Arbre CreatNoeud(TElement elt, Arbre fg, Arbre fd);
void LibMemoire(Arbre racine);
int estFeuille(Arbre racine);
int hauteurArbre(Arbre racine);
void parcoursPrefixe(Arbre a);
void parcoursInfixe(Arbre a);
void parcoursPostfixe(Arbre a);
int tailleArbre(Arbre a);
int nbFeuilles(Arbre a);

//---------------------------

//是否存在elt(re)
int rechEltABR(TElement elt, Arbre a);
int inrechEltABR(TElement elt, Arbre a);
//返回需要插入的父节点位置
Arbre adrInserABR(TElement elt, Arbre a);
//插入节点到给定父节点下
void insert(TElement elt, Arbre adrPere);
//插入节点到ABR
Arbre inserABR(TElement elt, Arbre a); //(re)
Arbre it_inserABR(TElement elt, Arbre a);
Arbre creatABRParTab(int *tab, int taille);
//中序遍历ABR输出到数组
void parcoursInfixeABRTab(int *n, Arbre racine, int *tab);
void triParABR(int n, int *tab);
//返回最小值
TElement minABR(Arbre racine);
TElement it_minABR(Arbre racine);
//返回最小节点
Arbre minABR_a(Arbre racine);
Arbre it_minABR_a(Arbre racine);
//删除racine，把左子树接到右边最小的节点下面
Arbre suppRacineABR(Arbre racine);
Arbre suppEltABR(TElement elt, Arbre racine);
TElement suppMaxABR(Arbre *a);
void afficherTableau(int *tab, int n);



Arbre filsGauche(Arbre racine) {
    return racine->filsG;
}

Arbre filsDroit(Arbre racine) {
    return racine->filsD;
}

TElement donnee(Arbre racine) {
    return racine->donnee;
}

Arbre initA() {
    return NULL;
}

int estVide(Arbre racine) {
    return racine == NULL;
}

Arbre CreatFeuille(TElement elt) {
    Arbre f = malloc(sizeof(struct noeud));
    f->donnee = elt;
    f->filsG = initA();
    f->filsD = initA();
    return f;
}

Arbre CreatNoeud(TElement elt, Arbre fg, Arbre fd) {
    Arbre a = malloc(sizeof(struct noeud));
    a->donnee = elt;
    a->filsG = fg;
    a->filsD = fd;
    return a;
}

void LibMemoire(Arbre racine) {
    if (!estVide(racine)) {
        LibMemoire(filsGauche(racine));
        LibMemoire(filsDroit(racine));
        free(racine);
    }
}

int estFeuille(Arbre racine) {
    return estVide(filsGauche(racine)) && estVide(filsDroit(racine));
}

int hauteurArbre(Arbre racine) {
    if (estVide(racine)) {
        return -1;
    } else {
        if (estFeuille(racine)) {
            return 0;
        } else {
            int hg = hauteurArbre(filsGauche(racine));
            int hd = hauteurArbre(filsDroit(racine));
            return 1 + (hg >= hd ? hg : hd);
        }
    }
}

void parcoursPrefixe(Arbre a) {
    if (!estVide(a)) {
        printf("%d ", donnee(a));
        parcoursPrefixe(filsGauche(a));
        parcoursPrefixe(filsDroit(a));
    }
}

void parcoursInfixe(Arbre a) {
    if (!estVide(a)) {
        parcoursInfixe(filsGauche(a));
        printf("%d ", donnee(a));
        parcoursInfixe(filsDroit(a));
    }
}

void parcoursPostfixe(Arbre a) {
    if (!estVide(a)) {
        parcoursPostfixe(filsGauche(a));
        parcoursPostfixe(filsDroit(a));
        printf("%d ", donnee(a));
    }
}

int tailleArbre(Arbre a) {
    if (estVide(a)) {
        return 0;
    }
    return 1 + tailleArbre(filsGauche(a)) +tailleArbre(filsDroit(a));
}

int nbFeuilles(Arbre a) {
    if (estVide(a)) {
        return 0;
    }
    if (estFeuille(a)) {
        return 1;
    }
    return nbFeuilles(filsGauche(a)) + nbFeuilles(filsDroit(a));
}

//---------------------------------------------

int rechEltABR(TElement elt, Arbre a) {
    if (estVide(a)) {
        return 0;
    }
    if (donnee(a) == elt) {
        return 1;
    }
    if (elt < donnee(a)) {
        return rechEltABR(elt, filsGauche(a));
    } else {
        return rechEltABR(elt, filsDroit(a));
    }
}

int inrechEltABR(TElement elt, Arbre a) {
    while (!estVide(a) && donnee(a) != elt) {
        if (elt < donnee(a)) {
            a = filsGauche(a);
        } else {
            a = filsDroit(a);
        }
    }
    return 0;
}

Arbre adrInserABR(TElement elt, Arbre a) {
    Arbre fg = filsGauche(a);
    Arbre fd = filsDroit(a);
    if (elt <= donnee(a)) {
        if (estVide(fg)) {
            return a;
        } else {
            return adrInserABR(elt, fg);
        }
    } else {
        if (estVide(fd)) {
            return a;
        } else {
            return adrInserABR(elt, fd);
        }
    }
}

void insert(TElement elt, Arbre adrPere) {
    Arbre f = CreatFeuille(elt);
    if (elt <= donnee(adrPere)) {
        adrPere->filsG = f;
    } else {
        adrPere->filsD = f;
    }
}

Arbre inserABR(TElement elt, Arbre a) {
    if (estVide(a)) {
        a = CreatFeuille(elt);
        return a;
    } else {
        if (elt <= donnee(a)) {
            a->filsG = inserABR(elt, filsGauche(a));
        } else {
            a->filsD = inserABR(elt, filsDroit(a));
        }
        return a;
    }
}

Arbre it_inserABR(TElement elt, Arbre a) {
    if (estVide(a)) {
        a = CreatFeuille(elt);
        return a;
    } else {
        Arbre adrePere = adrInserABR(elt, a);
        insert(elt, adrePere);
        return a;
    }
}

Arbre creatABRParTab(int *tab, int taille) {
    if (taille <= 0) return initA(); // 空数组返回空树

    Arbre racine = CreatFeuille(tab[0]); // 用第一个元素初始化根节点
    for (int i = 1; i < taille; i++) {
        inserABR(tab[i], racine); // 依次插入其他元素
    }

    return racine; // 返回创建好的树
}

void parcoursInfixeABRTab(int *n, Arbre racine, int *tab) {
    if (!estVide(racine)) {
        parcoursInfixeABRTab(n, filsGauche(racine), tab);
        tab[*n] = donnee(racine);
        (*n)++;
        parcoursInfixeABRTab(n, filsDroit(racine), tab);
    }
}

void triParABR(int n, int *tab) {
    Arbre racine = CreatFeuille(tab[0]);
    for (int i = 1; i < n; i++) {
        inserABR(tab[i], racine);
    }
    int index = 0;
    parcoursInfixeABRTab(&index, racine, tab);
    LibMemoire(racine);
}

TElement minABR(Arbre racine) {
    Arbre fg = filsGauche(racine);
    if (estVide(fg)) {
        return donnee(racine);
    } else {
        return minABR(fg);
    }
}

TElement it_minABR(Arbre racine) {
    Arbre fg = filsGauche(racine);
    while (!estVide(racine)) {
        racine = fg;
        fg = filsGauche(racine);
    }
    return donnee(racine);
}

Arbre minABR_a(Arbre racine) {
    Arbre fg = filsGauche(racine);
    if (estVide(fg)) {
        return racine;
    } else {
        return minABR_a(filsGauche(racine));
    }
}

Arbre it_minABR_a(Arbre racine) {
    Arbre fg = filsGauche(racine);
    while (!estVide(racine)) {
        racine = fg;
        fg = filsGauche(racine);
    }
    return racine;
}

Arbre suppRacineABR(Arbre racine) {
    Arbre rr = racine; //记录下要删的节点地址
    if (estFeuille(racine)) {
        racine = NULL;
    } else {
        Arbre fg = filsGauche(racine);
        Arbre fd = filsDroit(racine);
        if (!estVide(fd)) {
            //找右边最小的节点替换
            Arbre PlusPetitFD = minABR_a(fd);
            PlusPetitFD->filsG = fg;
            racine = fd;
        } else {
            racine = fg;
        }
    }
    free(rr);
    return racine;
}

Arbre suppEltABR(TElement elt, Arbre racine) {
    if (estVide(racine)) {
        return racine; // 树为空时直接返回
    }

    if (donnee(racine) == elt) {
        // 删除当前节点
        return suppRacineABR(racine);
    } else if (elt < donnee(racine)) {
        // 递归处理左子树，并更新左子树指针
        racine->filsG = suppEltABR(elt, filsGauche(racine));
    } else {
        // 递归处理右子树，并更新右子树指针
        racine->filsD = suppEltABR(elt, filsDroit(racine));
    }

    return racine; // 返回更新后的树
}

TElement suppMaxABR(Arbre *a) {
    // 如果右子树为空，当前节点即为最大节点
    if (estVide(filsDroit(*a))) {
        TElement eMax = donnee(*a); // 获取当前节点的值（最大值）
        Arbre tmp = *a; // 保存当前节点
        *a = filsGauche(*a); // 用当前节点的左子树替代当前节点
        free(tmp); // 释放当前节点的内存
        return eMax; // 返回最大值
    } else {
        // 否则递归查找右子树的最大值
        return suppMaxABR(&(*a)->filsD);
    }
}


void afficherTableau(int *tab, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", tab[i]);
    }
    printf("\n");
}

#endif //ARBREBINAIRECHERCHE_H
