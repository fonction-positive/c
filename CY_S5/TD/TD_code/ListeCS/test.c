#include <stdio.h>
#include <stdlib.h>

typedef struct cellule {
    int donnee;
    struct cellule *suivant;
} Cellule;

typedef Cellule *Liste;

void trier_liste_iterative(Liste lst) {
    if (lst == NULL || lst->suivant == lst) return; // 空列表或只有哨兵节点时返回

    Liste i, j;
    int temp;

    for (i = lst->suivant; i != lst; i = i->suivant) {
        for (j = i->suivant; j != lst; j = j->suivant) {
            if (i->donnee > j->donnee) {
                // 交换数据而不是节点
                temp = i->donnee;
                i->donnee = j->donnee;
                j->donnee = temp;
            }
        }
    }
}

void trier_liste_recursive(Liste lst) {
    if (lst == NULL || lst->suivant == lst) return; // 空列表或只有哨兵节点时返回

    static int sorted = 0;
    sorted = 1;
    Liste i = lst->suivant;
    while (i->suivant != lst) {
        if (i->donnee > i->suivant->donnee) {
            int temp = i->donnee;
            i->donnee = i->suivant->donnee;
            i->suivant->donnee = temp;
            sorted = 0;
        }
        i = i->suivant;
    }

    if (!sorted) {
        trier_liste_recursive(lst); // 递归调用直到完全排序
    }
}

// 创建哨兵节点
Liste creer_liste() {
    Liste lst = (Liste)malloc(sizeof(Cellule));
    if (lst) {
        lst->suivant = lst;
    }
    return lst;
}

// 向链表中添加元素（在哨兵节点之后）
void ajouter_element(Liste lst, int valeur) {
    Cellule *nouveau = (Cellule *)malloc(sizeof(Cellule));
    if (nouveau) {
        nouveau->donnee = valeur;
        nouveau->suivant = lst->suivant;
        lst->suivant = nouveau;
    }
}

// 打印链表中的元素
void afficher_liste(Liste lst) {
    Cellule *p = lst->suivant;
    while (p != lst) {
        printf("%d ", p->donnee);
        p = p->suivant;
    }
    printf("\n");
}

// 释放链表内存
void liberer_liste(Liste lst) {
    Cellule *p = lst->suivant;
    while (p != lst) {
        Cellule *temp = p;
        p = p->suivant;
        free(temp);
    }
    free(lst); // 释放哨兵节点
}



// 主函数
int main() {
    Liste lst = creer_liste();  // 创建循环链表（带哨兵）

    // 添加一些元素
    ajouter_element(lst, 5);
    ajouter_element(lst, 3);
    ajouter_element(lst, 8);
    ajouter_element(lst, 1);
    ajouter_element(lst, 7);

    printf("排序前的链表: ");
    afficher_liste(lst);

    // 调用排序函数（可以选择迭代或递归版本）
    trier_liste_recursive(lst);

    printf("排序后的链表: ");
    afficher_liste(lst);

    // 释放内存
    liberer_liste(lst);

    return 0;
}