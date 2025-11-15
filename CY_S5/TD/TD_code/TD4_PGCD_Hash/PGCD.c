//
// Created by 金卓远 on 24-11-3.
//


// TabListe 表示一个包含多个整数及其质因数分解的表。
// tab 是一个数组，存储多个 TElement。
// 每个 TElement 包含一个链表长度，以及一个链表 ldfp，链表中的每个节点存储该整数的一个质因数及其出现次数。


#include <stdio.h>
#include <stdlib.h>



//一个donnee
typedef struct {
    int fact; // 质因数
    int nbOcc; // 质因数的个数
} FactPremier;

//一个节点
typedef struct cellule {
    FactPremier donnee;
    struct cellule *suivant;
} *Liste;


//ex1
typedef struct {
    int valeur;
    Liste ldfp; //liste de fact premier
} TElement;

typedef struct {
    int nbEltMax;
    int nbElt;
    TElement *tab;
} TabListe;

int nbOcc(int n, int facteur) {
    int occ = 0; //计数器
    while (n % facteur == 0) {
        occ++;
        n = n / facteur;
    }
    return occ;
}

Liste init() {
    return NULL;
};
int estVide(Liste l) {
    return l==NULL;
}
Liste dernier(Liste l) {
    Liste der=l;
    while (!estVide(der->suivant)) {
        der=der->suivant;
    }
    return der;
}
Liste inserTete(FactPremier elt, Liste *l) {
    Liste cel=(Liste)malloc(sizeof(struct cellule));
    cel->donnee=elt;
    cel->suivant=*l;
    *l=cel;
    // return l;
}
Liste inserQueue(FactPremier elt, Liste ldfp) {
    if (estVide(ldfp)) {
        return inserTete(elt, &ldfp); // 空链表时，直接调用 inserTete 并返回新头指针
    }

    Liste der = dernier(ldfp); // 找到最后一个节点
    Liste cel = (Liste)malloc(sizeof(struct cellule));
    cel->donnee = elt;
    cel->suivant = NULL;
    der->suivant = cel;
    return ldfp;
};

void parcours(Liste l) {
    if (!estVide(l)) {
        printf("(%d,%d)->",l->donnee.fact,l->donnee.nbOcc);
        parcours(l->suivant);
    }
}

//ex2将数组分解为链表ldfp
//分解
Liste diviser(int n, Liste ldfp) {
    int facteur = 2;
    while (n > 1) {
        int occ = 0; //计数器
        while (n % facteur == 0) {
            occ++;
            n = n / facteur;
        }
        if (occ > 0) {
            FactPremier elt;
            elt.fact = facteur;
            elt.nbOcc = occ;
            ldfp = inserQueue(elt, ldfp);
        }
        facteur++;
    }
    return ldfp;
}

//ex3
//Tab={40,15,13,210} 把他转化为TabListe

TabListe constructionTL(int n,int tab[]) {
    TabListe tl;
    tl.nbEltMax=1000;
    tl.nbElt=n;
    tl.tab=malloc(n*sizeof(TElement));

    for (int i=0;i<n;i++) {
        Liste ldfp=init();
        tl.tab[i].valeur=tab[i];
        tl.tab[i].ldfp=diviser(tab[i],ldfp);
    }
    return tl;
}



//求交集 交集代表两个数的公因数
Liste intersection(Liste l1,Liste l2) {
    Liste l=init();
    while (!estVide(l1) && !estVide(l2)) {
        int f1=l1->donnee.fact;
        int f2=l2->donnee.fact;
        int o1=l1->donnee.nbOcc;
        int o2=l2->donnee.nbOcc;
        if (f1==f2) {
            FactPremier elt;
            elt.fact=f1;
            elt.nbOcc=(o1<o2)?o1:o2;
            l=inserQueue(elt,l);
            l1=l1->suivant;
            l2=l2->suivant;
        }else {
            if (f1<f2) {
                l1=l1->suivant;
            }else {
                l2=l2->suivant;
            }
        }
    }
    if (l==NULL) {
        printf("il n'y a pas intersection entre les listes.\n");
    }
    return l;
}


//求PGCD
int PGCD(TabListe tl) {
    Liste inter=tl.tab[0].ldfp; //先假设交集为第一个链表，然后和第二个第三个...做交集
    int pgcd=1;
    for (int i=1;i<tl.nbElt;i++) {
        inter=intersection(inter,tl.tab[i].ldfp);
        if (estVide(inter)) {//如果没有交集，那就说明没有公因数，则最大公因数为1
            free(inter);
            return pgcd;
        }
    }
    //计算PGCD，把质因数乘起来

    while (!estVide(inter)) {
        pgcd*=inter->donnee.fact;
        inter=inter->suivant;
    }
    free(inter);
    return pgcd;

}


int main() {
    int tab[] = {40,15,13,210};
    int sizeTab=sizeof(tab)/sizeof(tab[0]);
    TabListe tl=constructionTL(sizeTab,tab);

     for(int i=0;i<sizeTab;i++) {
         printf("%d : ",tl.tab[i].valeur);
         parcours(tl.tab[i].ldfp);
         printf("\n");
     }

    // 查看两个链表之间的公因数
    printf("两个链表之间的公因数:\n");
    Liste l=intersection(tl.tab[0].ldfp,tl.tab[1].ldfp);
    parcours(l);
    printf("\n");

    //求n个数之间的最大公因数
    int pgcd=PGCD(tl);
    printf("PGCD = %d",pgcd);

    // 释放内存
    for (int i = 0; i < 4; i++) {
        Liste ldfp = tl.tab[i].ldfp;
        while (ldfp != NULL) {
            Liste temp = ldfp;
            ldfp = ldfp->suivant;
            free(temp);
        }
    }
    free(tl.tab);

    return 0;
}

