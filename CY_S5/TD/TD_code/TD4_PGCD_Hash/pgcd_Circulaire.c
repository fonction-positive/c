#include <stdio.h>
#include <stdlib.h>
#include <__stddef_null.h>

//
// Created by 金卓远 on 24-11-6.
//

typedef struct entier{
    int donnee;
    struct entier* suivant ;
}*ListeEntier; //lpre

typedef struct{
    int fact ; // indique le facteur premier
    int nbOcc ; // nombre d’occurrences du facteur premier
}FactPremier;

typedef struct cellule {
    FactPremier donnee;
    struct cellule* suivant;
}*ListeDFP;

typedef struct {
    ListeDFP tete;
    ListeDFP queue;
}ListeTQ_DFP;

ListeTQ_DFP initLTQ_DFP() {
    ListeTQ_DFP liste_tq_dfp;
    liste_tq_dfp.tete=NULL;
    liste_tq_dfp.queue=NULL;
    return liste_tq_dfp;
}

int estVideLDFP_TQ(ListeTQ_DFP ldfp) {
    return ldfp.tete==NULL && ldfp.queue==NULL;
}

ListeDFP allocMemRemp(FactPremier elt) {
    ListeDFP liste_dfp=malloc(sizeof(ListeDFP));
    liste_dfp->donnee=elt;
    liste_dfp->suivant=NULL;
    return liste_dfp;
}

ListeTQ_DFP inserQueue(FactPremier elt,ListeTQ_DFP ldfp) {
    ListeDFP cel=allocMemRemp(elt);
    // cel->suivant=NULL;
    ldfp.queue->suivant=cel;
    ldfp.queue=cel;
    return ldfp;
}

//将entier分解为链表
ListeTQ_DFP diviser(int n,ListeEntier lPre) {
    ListeTQ_DFP ldfp=initLTQ_DFP();
    // int facteur = 2;
    ListeEntier facteur=lPre;

    while (n > 1) {
        int fact=facteur->donnee;
        int occ = 0; //计数器
        while (n % fact == 0) {
            occ++;
            n = n / fact;
        }
        if (occ > 0) {
            FactPremier elt;
            elt.fact = fact;
            elt.nbOcc = occ;
            ldfp = inserQueue(elt, ldfp);
        }
        facteur++;
    }
    return ldfp;
}

//返回occ最大的premier
int recherchePlusOcc(ListeTQ_DFP ldfp) {
    int pre=ldfp.tete->donnee.fact;
    int max_pre=ldfp.tete->donnee.nbOcc; //假设第一个因数次数最多

    ListeDFP courante=ldfp.tete->suivant; //从第二个开始比较
    while (courante!=NULL) {
        if (courante->donnee.nbOcc > max_pre) {
            pre=courante->donnee.fact;
            max_pre=courante->donnee.nbOcc;
        }
        courante=courante->suivant;
    }
    return pre;
}

//求交集
//求交集 交集代表两个数的公因数
ListeTQ_DFP intersection(ListeTQ_DFP l1,ListeTQ_DFP l2) {
    ListeTQ_DFP l=initLTQ_DFP();
    while (!estVideLDFP_TQ(l1) && !estVideLDFP_TQ(l2)) {
        int f1=l1.tete->donnee.fact;
        int f2=l2.tete->donnee.fact;
        int o1=l1.tete->donnee.nbOcc;
        int o2=l2.tete->donnee.nbOcc;

        if (f1==f2) {
            FactPremier elt;
            elt.fact=f1;
            elt.nbOcc=(o1<o2)?o1:o2;
            l=inserQueue(elt,l);
            l1.tete=l1.tete->suivant;
            l2.tete=l2.tete->suivant;
        }else {
            if (f1<f2) {
                l1.tete=l1.tete->suivant;
            }else {
                l2.tete=l2.tete->suivant;
            }
        }
    }
    if (estVideLDFP_TQ(l)) {
        printf("il n'y a pas intersection entre les listes.\n");
    }
    return l;
}

ListeTQ_DFP intersectionRec(ListeTQ_DFP l1, ListeTQ_DFP l2) {
    // 如果其中一个列表为空，返回空的交集
    if (estVideLDFP_TQ(l1) || estVideLDFP_TQ(l2)) {
        ListeTQ_DFP l = initLTQ_DFP();
        printf("il n'y a pas intersection entre les listes.\n");
        return l;
    }

    int f1 = l1.tete->donnee.fact;
    int f2 = l2.tete->donnee.fact;
    int o1 = l1.tete->donnee.nbOcc;
    int o2 = l2.tete->donnee.nbOcc;

    if (f1 == f2) {
        // 创建交集节点
        FactPremier elt;
        elt.fact = f1;
        elt.nbOcc = (o1 < o2) ? o1 : o2;

        // 递归获取剩余部分的交集
        l1.tete=l1.tete->suivant;
        l2.tete=l2.tete->suivant;
        ListeTQ_DFP resteIntersection = intersectionRec(l1, l2);

        // 将当前节点插入交集列表的头部
        return inserQueue(elt, resteIntersection);

    } else if (f1 < f2) {
        // 递归在 l1 的下一节点与 l2 的当前节点之间继续寻找交集
        l1.tete=l1.tete->suivant;
        return intersectionRec(l1, l2);

    } else {
        // 递归在 l1 的当前节点与 l2 的下一节点之间继续寻找交集
        l2.tete=l2.tete->suivant;
        return intersectionRec(l1, l2);
    }
}

//构建ll，竖着的链表
typedef struct ll {
    int entier;
    ListeTQ_DFP ldfp;
    struct ll* suivant;
}*LL;

//构建竖着的链表
LL initLL() {
    return NULL;
}

//插入ll
LL inserLL(int entier,LL ll,ListeEntier lPre) {
    LL cel=malloc(sizeof(LL));
    cel->entier=entier;
    cel->ldfp=diviser(entier,lPre);
    cel->suivant=NULL;

    if(ll==NULL || entier < ll->entier) {
        cel->suivant=ll;
        ll=cel;
        return ll;
    }

    LL courante=ll;
    while (courante->suivant!=NULL && courante->suivant->entier < entier) {
        courante=courante->suivant;
    }
    cel->suivant=courante->suivant;
    courante->suivant=cel;
    return ll;
}

//构建ll
LL constructionLL(ListeEntier lNbre,ListeEntier lPre) {
    LL ll=initLL();
    ListeEntier courante=lNbre;
    //使用do while遍历lNbre
    do {
        ll=inserLL(courante->donnee,ll,lPre);
        courante=courante->suivant;
    }while (courante!=lNbre);
    return ll;
}

//求PGCD
int PGCD(LL ll) {
    ListeTQ_DFP inter = ll->ldfp; // 假设交集为第一个链表，然后依次与其他链表求交集
    int pgcd = 1;

    while (ll != NULL) {
        inter = intersection(inter, ll->ldfp);
        if (estVideLDFP_TQ(inter)) { // 如果没有交集，则最大公因数为1
            // 释放 inter 的内存
            ListeDFP temp = inter.tete;
            free(temp);
            return pgcd;
        }
        ll = ll->suivant;
    }

    // 计算 PGCD，把交集中的质因数乘起来
    ListeDFP courant = inter.tete;
    while (courant != NULL) {
        pgcd *= courant->donnee.fact;
        courant = courant->suivant;
    }

    // 释放 inter 的内存
    courant = inter.tete;
    while (courant != NULL) {
        ListeDFP temp = courant;
        courant = courant->suivant;
        free(temp);
    }

    return pgcd;
}