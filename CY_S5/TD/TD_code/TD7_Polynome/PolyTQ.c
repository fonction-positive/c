//
// Created by 金卓远 on 24-12-15.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double coef; //x前的系数
    int degre; //指数
} Monome;

typedef struct cellule {
    Monome monome;
    struct cellule *suivant;
    struct cellule *precedent;
} *DListe;

typedef struct {
    DListe tete;
    DListe queue;
}Polynome;

int degre(Monome monome);
double coef(Monome monome);
Polynome initP();
int estVide(Polynome poly);
Monome mono(double coef, int degre);
Polynome inserTete(Monome m, Polynome p);
Polynome inserQueue(Monome m, Polynome p);
Polynome inserMonPoly(Monome m,Polynome p);
DListe rechMonPoly(Monome m,Polynome poly);
Polynome suppTete(Polynome p);
Polynome suppQueue(Polynome p);
Polynome suppMonPoly(Monome m,Polynome p);
void delPolynome(Polynome *poly);
void affichPoly(Polynome poly);
float maxCoef(Polynome p);
DListe maxCoefAdr(Polynome p);
float somCoef(Polynome p);
//通过数组创建多项式
Polynome generPoly(int n, float *tab);
//导数
Polynome derivPoly(Polynome p);
//合并两个多项式
Polynome somPoly(Polynome p1, Polynome p2);

int degre(Monome monome) {
    return monome.degre;
}

double coef(Monome monome) {
    return monome.coef;
}

// 初始化多项式（带头结点）
Polynome initP() {
    Polynome poly;
    poly.tete = NULL;
    poly.queue = NULL;
    return poly;
}

// 判断链表是否为空
int estVide(Polynome poly) {
    return poly.tete == NULL && poly.queue==NULL;
}

// 创建一个单项式
Monome mono(double coef, int degre) {
    Monome m;
    m.coef = coef;
    m.degre = degre;
    return m;
}

// 插入节点到链表头部
Polynome inserTete(Monome m, Polynome p) {
    DListe cel = malloc(sizeof(struct cellule));
    if (cel == NULL) {
        printf("pb de memoire\n");
        exit(1);
    }
    cel->monome = m;
    if (estVide(p)) {
        cel->suivant=NULL;
        cel->precedent=NULL;
        p.tete=cel;
        p.queue=cel;
    }else {
        cel->suivant = p.tete; // 新节点的 suivant 指向当前链表头
        cel->precedent = NULL; // 新节点是头部，没有前驱
        p.tete->precedent=cel;
        p.tete=cel;
    }
    return p;
}

// 插入节点到链表尾部
Polynome inserQueue(Monome m, Polynome p) {
    DListe cel = malloc(sizeof(struct cellule));
    if (cel == NULL) {
        printf("pb de memoire\n");
        exit(1);
    }
    cel->monome = m;
    if (estVide(p)) {
        cel->suivant=NULL;
        cel->precedent=NULL;
        p.tete=cel;
        p.queue=cel;
    }else {
        cel->suivant = NULL;
        cel->precedent = p.queue;
        p.queue->suivant=cel;
        p.queue=cel;
    }
    return p;
}

Polynome inserMonPoly(Monome m,Polynome p) {
    DListe cel = malloc(sizeof(struct cellule));
    if (cel == NULL) {
        printf("pb de memoire\n");
        exit(1);
    }
    cel->monome = m;
    cel->suivant = NULL;
    cel->precedent = NULL;

    // 如果链表为空，插头
    if (estVide(p)) {
        return inserTete(m,p);
    }

    int d = m.degre;
    int dmp=p.tete->monome.degre;

    if (d < dmp) {
        return inserTete(m,p);
    }

    DListe actuel = p.tete;
    DListe pre = p.tete->suivant;
    // 寻找插入位置，actuel 大于等于d的时候停止
    while (actuel != NULL && actuel->monome.degre < d) {
        pre = actuel;
        actuel = actuel->suivant;
    }

    // 如果找到了相同次数的单项式，合并系数
    if (actuel != NULL && actuel->monome.degre == d) {
        actuel->monome.coef += m.coef;
        // 如果系数为0，则删除该节点
        if (actuel->monome.coef == 0) {
            if (actuel->suivant == NULL) {
                pre->suivant=NULL;
                p.queue=pre;
            } else {
                pre->suivant=actuel->suivant;
                actuel->suivant->precedent=pre;
            }
            free(actuel);
        }
        return p;
    }

    // 插入新的节点
    if (actuel == NULL) {
        pre->suivant = cel;
        cel->precedent = pre;
        p.queue = cel;
    } else {
        pre->suivant = cel;
        cel->precedent = pre;
        cel->suivant = actuel;
        actuel->precedent = cel;
    }

    return p;
}


// 查找单项式在多项式中的地址
DListe rechMonPoly(Monome m,Polynome poly) {
    DListe actuel = poly.tete;
    while (actuel != NULL) {
        if (actuel->monome.coef == m.coef && actuel->monome.degre == m.degre) {
            return actuel;
        }
        actuel = actuel->suivant;
    }
    return NULL;
}

// 删除链表的头节点
Polynome suppTete(Polynome p) {
    if (estVide(p)){
        return p;
    }
    DListe supp=p.tete;
    if (p.tete==p.queue) {
        p.tete=NULL;
        p.queue=NULL;
        free(supp);
        return p;
    }
    p.tete=p.tete->suivant;
    p.tete->precedent=NULL;
    free(supp);
    return p;
}

// 删除链表的尾节点
Polynome suppQueue(Polynome p) {
    if (estVide(p)) {
        return p;
    }
    DListe supp=p.queue;
    if (p.tete==p.queue) {
        p.tete=NULL;
        p.queue=NULL;
        free(supp);
        return p;
    }
    p.queue=p.queue->precedent;
    p.queue->suivant=NULL;
    free(supp);
    return p;
}

// 删除指定单项式
Polynome suppMonPoly(Monome m,Polynome p) {
    DListe actuel=rechMonPoly(m,p);
    if (actuel==NULL) {
        return p;
    }
    if (actuel->precedent==NULL) {
        suppTete(p);
    }
    if (actuel->suivant==NULL) {
        suppQueue(p);
    }
    actuel->precedent->suivant=actuel->suivant;
    actuel->suivant->precedent=actuel->precedent;
    free(actuel);
    return p;
}

// 释放多项式链表的内存
void delPolynome(Polynome *poly) {
    DListe temp;
    while (poly->tete != NULL) {
        temp = poly->tete;
        poly->tete = poly->tete->suivant;
        free(temp);
    }
    poly->queue = NULL;
}

// 打印多项式
void affichPoly(Polynome poly) {
    DListe actuel = poly.tete;
    while (actuel != NULL) {
        printf("(%.2f, %d)", actuel->monome.coef, actuel->monome.degre);
        if (actuel->suivant != NULL) printf(" + ");
        actuel = actuel->suivant;
    }
    printf("\n");
}

float maxCoef(Polynome p) {
    DListe actuel = p.tete;
    float maxcoef = p.tete->monome.coef;
    while (actuel != NULL) {
        if (actuel->monome.coef > maxcoef) {
            maxcoef = actuel->monome.coef;
        }
        actuel = actuel->suivant;
    }
    return maxcoef;
}

DListe maxCoefAdr(Polynome p) {
    DListe actuel = p.tete;
    DListe maxadr=p.tete;
    float maxcoef = p.tete->monome.coef;
    while (actuel != NULL) {
        if (actuel->monome.coef > maxcoef) {
            maxcoef = actuel->monome.coef;
            maxadr=actuel;
        }
        actuel = actuel->suivant;
    }
    return maxadr;
}

float somCoef(Polynome p) {
    DListe actuel = p.tete;
    float maxcoef = 0;
    while (actuel != NULL) {
        maxcoef += actuel->monome.coef;
        actuel = actuel->suivant;
    }
    return maxcoef;
}

//通过数组生成多项式
Polynome generPoly(int n, float *tab) {
    Polynome p = initP();
    Monome m;
    for (int i = 0; i < n; i++) {
        m.degre = i;
        m.coef = tab[i];
        p = inserMonPoly(m, p);
    }
    return p;
}

//计算多项式的导数
Polynome derivPoly(Polynome p) {
    DListe actuel = p.tete;
    while (actuel != NULL) {
        if (actuel->monome.degre == 0) {
            actuel->monome.coef = actuel->monome.coef * actuel->monome.degre;
        } else {
            actuel->monome.coef = actuel->monome.coef * actuel->monome.degre;
            actuel->monome.degre--;
        }

        actuel = actuel->suivant;
    }
    return p;
}

//计算两个给定多项式的和（不修改原多项式）
Polynome somPoly(Polynome p1, Polynome p2) {
    Polynome p = initP();
    DListe index1 = p1.tete, index2 = p2.tete;
    Monome m;

    while (index1 != NULL && index2 != NULL) {
        if (index1->monome.degre == index2->monome.degre) {
            m.degre = index1->monome.degre;
            m.coef = index1->monome.coef + index2->monome.coef;
            p = inserMonPoly(m, p);
            index1 = index1->suivant;
            index2 = index2->suivant;
        } else if (index1->monome.degre < index2->monome.degre) {
            m.degre = index1->monome.degre;
            m.coef = index1->monome.coef;
            p = inserMonPoly(m, p);
            index1 = index1->suivant;
        } else {
            m.degre = index2->monome.degre;
            m.coef = index2->monome.coef;
            p = inserMonPoly(m, p);
            index2 = index2->suivant;
        }
    }
    while (index1 !=NULL) {
        m.degre = index1->monome.degre;
        m.coef = index1->monome.coef;
        p = inserMonPoly(m, p);
        index1 = index1->suivant;
    }
    while (index2 != NULL) {
        m.degre = index2->monome.degre;
        m.coef = index2->monome.coef;
        p = inserMonPoly(m, p);
        index2 = index2->suivant;
    }

    return p;
}

int main() {
    // Polynome p = initP();
    // p=inserTete(mono(3, 2),p);
    // p=inserTete(mono(2, 1),p);
    // // p=inserTete(mono(4, 0),p);
    // p=inserMonPoly(mono(2,0),p);
    // p=inserMonPoly(mono(2,3),p);
    // affichPoly(p);

    // suppMonPoly(&p, mono(3, 2));
    // affichPoly(p);

    Polynome p = initP();
    float tab[] = {3, 5, 2, 3};
    int n = sizeof(tab) / sizeof(tab[0]);
    p = generPoly(n, tab);
    affichPoly(p);

    p = derivPoly(p);
    affichPoly(p);

    printf("maxcoef : %.2f\n", maxCoef(p));
    printf("somcoef : %.2f\n", somCoef(p));


    DListe res = rechMonPoly(mono(5, 8), p);
    if (res == NULL) {
        printf("NULL\n");
    } else {
        printf("%p", res);
    }

    p = suppMonPoly(mono(5, 3), p);
    affichPoly(p);


    Polynome p1, p2;
    float tab1[] = {1, 3, 2, 3, 5, 2, 3};
    int n1 = sizeof(tab1) / sizeof(tab1[0]);
    p1 = generPoly(n1, tab1);
    p1=suppMonPoly(mono(3,1),p1);
    printf("p1 : "); affichPoly(p1);

    float tab2[] = {3, 5, 2, 3, 4};
    int n2 = sizeof(tab2) / sizeof(tab2[0]);
    p2 = generPoly(n2, tab2);
    printf("p2 : "); affichPoly(p2);


    Polynome somP=initP();
    somP=somPoly(p1,p2);
    printf("somP : "); affichPoly(somP);

    delPolynome(&p);
    return 0;
}