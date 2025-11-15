#include <stdio.h>
#include <stdlib.h>
#include <__stddef_null.h>
#include <mach/processor_info.h>

//
// Created by 金卓远 on 24-11-4.
//
typedef struct {
    double coef; //x前的系数
    int degre; //指数
} Monome;

typedef struct cellule {
    Monome monome;
    struct cellule *suivant;
    struct cellule *precedent;
} *Polynome;

int degre(Monome monome) {
    return monome.degre;
}

double coef(Monome monome) {
    return monome.coef;
}

Polynome initP() {
    return NULL;
}

int estVide(Polynome polynome) {
    return polynome == NULL;
}

Monome mono(float coef, int degre) {
    Monome m;
    m.coef = coef;
    m.degre = degre;
    return m;
}

Polynome inserTete(Monome m, Polynome p) {
    Polynome cel = malloc(sizeof(struct cellule));
    if (cel == NULL) {
        printf("pb de memoire\n");
        exit(1);
    }
    cel->monome = m;
    cel->suivant = p; // 新节点的 suivant 指向当前链表头
    cel->precedent = NULL; // 新节点是头部，没有前驱

    if (p != NULL) {
        p->precedent = cel; // 原链表头的前驱指向新节点
    }
    return cel; // 返回新的链表头
}

Polynome inserQueue(Monome m, Polynome p) {
    Polynome cel = malloc(sizeof(struct cellule));
    if (cel == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    cel->monome = m;
    cel->suivant = NULL;
    cel->precedent = NULL;

    // 如果链表为空，新节点成为唯一节点
    if (estVide(p)) {
        return cel;
    }

    // 找到链表的尾部
    Polynome actuel = p;
    while (actuel->suivant != NULL) {
        actuel = actuel->suivant;
    }

    // 插入到尾部
    actuel->suivant = cel;
    cel->precedent = actuel;

    return p;
}

Polynome inserMonPoly(Monome m, Polynome p) {
    Polynome cel = malloc(sizeof(struct cellule));
    cel->monome = m;
    cel->suivant = NULL;
    cel->precedent = NULL;
    //如果链表是空的
    if (estVide(p)) {
        return cel;
    }
    int d = m.degre;
    int dmp = p->monome.degre;
    //如果插入元素次方小于多项式第一项次方，则插入头
    if (d < dmp) {
        cel->suivant = p;
        p->precedent = cel;
        return cel;
    }

    Polynome actuel = p->suivant;
    Polynome pre = p;
    //找到合适位置，actuel 大于等于d的时候停止
    while (actuel != NULL && actuel->monome.degre < d) {
        pre = actuel; //存actuel前一个节点
        actuel = actuel->suivant;
    }
    //如果actuel等于d
    if (actuel != NULL && actuel->monome.degre == d) {
        actuel->monome.coef += m.coef; //合并系数
        //判断系数是否为0,删除actuel
        if (actuel->monome.coef == 0) {
            if (actuel->suivant == NULL) {
                //如果是最后一个节点
                pre->suivant = NULL;
            } else {
                pre->suivant = actuel->suivant;
                actuel->suivant->precedent = pre;
            }
            free(actuel);
        }
        return p;
    }

    //actuel 不等于 d
    if (actuel == NULL) {
        pre->suivant = cel;
        cel->precedent = pre;
        return p;
    }

    pre->suivant = cel;
    cel->precedent = pre;
    cel->suivant = actuel;
    actuel->precedent = cel;
    return p;
}

//查找单项式是否属于多项式,返回地址或NULL
Polynome rechMonPoly(Monome m, Polynome p) {
    Polynome actuel = p;
    while (actuel != NULL) {
        if (actuel->monome.coef == m.coef && actuel->monome.degre == m.degre) {
            return actuel;
        }
        actuel = actuel->suivant;
    }
    return NULL;
}


Polynome suppTete(Polynome p) {
    // 如果链表为空，直接返回
    if (estVide(p)) {
        return NULL;
    }

    Polynome temp = p;        // 保存当前头节点
    p = p->suivant;           // 更新头指针到下一个节点

    if (p != NULL) {
        p->precedent = NULL;  // 如果新头节点存在，前驱设为 NULL
    }

    free(temp);               // 释放原头节点的内存
    return p;                 // 返回新的头指针
}

Polynome suppQueue(Polynome p) {
    // 如果链表为空，直接返回
    if (estVide(p)) {
        return NULL;
    }

    // 如果链表只有一个节点，删除该节点并返回 NULL
    if (p->suivant == NULL) {
        free(p);
        return NULL;
    }

    Polynome actuel = p;

    // 找到尾节点
    while (actuel->suivant != NULL) {
        actuel = actuel->suivant;
    }

    // 更新尾节点的前一个节点的指针
    actuel->precedent->suivant = NULL;

    free(actuel); // 释放尾节点内存
    return p;     // 返回链表头
}

Polynome suppMonPoly(Monome m, Polynome p) {
    //如果不存在这个单项式直接返回p
    if (rechMonPoly(m, p) == NULL) {
        return p;
    }

    Polynome actuel = rechMonPoly(m, p);
    //如果是头
    if (actuel->precedent == NULL) {
        // suppTete(p);
        actuel->suivant->precedent = NULL;
        p = actuel->suivant;
        free(actuel);
        return p;
    }
    //如果是尾
    if (actuel->suivant == NULL) {
        // suppQueue(p);
        actuel->precedent->suivant = NULL;
        free(actuel);
        return p;
    }

    //不是头也不是尾
    actuel->precedent->suivant = actuel->suivant;
    actuel->suivant->precedent = actuel->precedent;
    free(actuel);
    return p;
}

//释放内存
void delPolynome(Polynome p) {
    Polynome temp;
    while (p != NULL) {
        temp = p;
        p = p->suivant; // 移动到下一个节点
        free(temp); // 释放当前节点
    }
}

#include <stdio.h>

void affichPoly(Polynome p) {
    if (estVide(p)) {
        printf("Poly is empty.\n");
        return;
    }

    Polynome actuel = p;
    while (actuel != NULL) {
        // 打印每个节点的系数和指数
        printf("(%.2f, %d)", actuel->monome.coef, actuel->monome.degre);

        // 如果当前节点不是链表的最后一个节点，打印箭头
        if (actuel->suivant != NULL) {
            printf(" + ");
        }

        actuel = actuel->suivant; // 移动到下一个节点
    }
    printf("\n");
}

float maxCoef(Polynome p) {
    Polynome actuel = p;
    float maxcoef = p->monome.coef;
    while (actuel != NULL) {
        if (actuel->monome.coef > maxcoef) {
            maxcoef = actuel->monome.coef;
        }
        actuel = actuel->suivant;
    }
    return maxcoef;
}

float somCoef(Polynome p) {
    Polynome actuel = p;
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
    Polynome actuel = p;
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
    Polynome index1 = p1, index2 = p2;
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
    Polynome p = initP();
    // p = inserMonPoly(mono(2, 1), p);
    // affichPoly(p);
    // p = inserMonPoly(mono(1, 0), p);
    // affichPoly(p);
    // p = inserMonPoly(mono(2, 3), p);
    // affichPoly(p);
    // p = inserMonPoly(mono(3, 1), p);
    // affichPoly(p);
    // p = inserMonPoly(mono(2, 2), p);
    // affichPoly(p);
    // p = inserMonPoly(mono(3, 3), p);
    // affichPoly(p);
    // p = inserMonPoly(mono(2, 0), p);
    // affichPoly(p);
    // (3.00, 0) -> (5.00, 1) -> (2.00, 2) -> (5.00, 3)

    float tab[] = {3, 5, 2, 3};
    int n = sizeof(tab) / sizeof(tab[0]);
    p = generPoly(n, tab);
    affichPoly(p);

    p = derivPoly(p);
    affichPoly(p);

    printf("maxcoef : %.2f\n", maxCoef(p));
    printf("somcoef : %.2f\n", somCoef(p));


    Polynome res = rechMonPoly(mono(5, 8), p);
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


    // 释放多项式链表的内存
    delPolynome(p);
    return 0;
}
