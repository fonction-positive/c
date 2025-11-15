//
// Created by 金卓远 on 24-12-15.
//

#include "Arbre234.h"
#include <stdio.h>
#include <stdlib.h>

#define NBMAXDONNEES 3
#define NBMAXFILS 4

typedef int TElement;

typedef struct noeud {
    int nbFils;                     // 当前节点的子节点数
    TElement donnee[NBMAXDONNEES];  // 存储最多3个数据
    struct noeud* fils[NBMAXFILS];       // 存储最多4个子树
    int estFeuille;
}*Arbre234;


// 创建一个新节点
Arbre234 creerNoeud();
// 查找插入位置的辅助函数
void insererDansNoeud(Arbre234 arbre, TElement element, int position);
// 节点分裂函数
void splitter(Arbre234 arbre, int i, Arbre234 parent);
// 向2-3-4树插入一个元素
void inserer(Arbre234 *racine, TElement element);
// 中序遍历输出树的元素
void afficherArbre(Arbre234 arbre);
// 构建2-3-4树并插入元素
void construireArbre(Arbre234 *racine, TElement elements[], int taille);
//找最小值
TElement trouverMin(Arbre234 arbre);
TElement trouverMax(Arbre234 arbre);
//返回给定elt的地址
Arbre234 rechercherElement(Arbre234 arbre, TElement element);
// 统计节点类型的递归函数
void compterTypesDeNoeuds(Arbre234 arbre, int *compteur2, int *compteur3, int *compteur4);
// 计算节点类型数量的函数(打印）
void calculerTypesDeNoeuds(Arbre234 arbre);
// 前序遍历
void parcoursPreOrdre(Arbre234 arbre);
void parcoursInOrdre(Arbre234 arbre);
void parcoursPostOrdre(Arbre234 arbre);



// 创建一个新节点
Arbre234 creerNoeud() {
    Arbre234 nouveau = (Arbre234)malloc(sizeof(struct noeud));
    if (nouveau) {
        nouveau->nbFils = 0;
        for (int i = 0; i < NBMAXFILS; i++) {
            nouveau->fils[i] = NULL;
        }
    }
    return nouveau;
}

// 查找插入位置的辅助函数
void insererDansNoeud(Arbre234 arbre, TElement element, int position) {
    for (int i = arbre->nbFils; i > position; i--) {
        arbre->donnee[i] = arbre->donnee[i - 1];
        arbre->fils[i + 1] = arbre->fils[i];
    }
    arbre->donnee[position] = element;
    arbre->fils[position + 1] = NULL;
    arbre->nbFils++;
}

// 节点分裂函数
void splitter(Arbre234 arbre, int i, Arbre234 parent) {
    // 分裂一个节点，并将中间元素提升到父节点
    Arbre234 nouveau = creerNoeud();
    nouveau->nbFils = 1;
    nouveau->donnee[0] = arbre->donnee[2];
    nouveau->fils[0] = arbre->fils[2];
    nouveau->fils[1] = arbre->fils[3];

    // 更新当前节点
    arbre->nbFils = 1;
    arbre->fils[2] = NULL;
    arbre->fils[3] = NULL;

    // 将中间元素移到父节点
    insererDansNoeud(parent, arbre->donnee[1], i);
    parent->fils[i + 1] = nouveau;
}

// 向2-3-4树插入一个元素
void inserer(Arbre234 *racine, TElement element) {
    if (*racine == NULL) {
        *racine = creerNoeud();
    }

    Arbre234 arbre = *racine;
    while (arbre->nbFils > 0) {
        int i = 0;
        while (i < arbre->nbFils && element > arbre->donnee[i]) {
            i++;
        }

        if (i < arbre->nbFils && element == arbre->donnee[i]) {
            return;  // 元素已经存在，跳过
        }

        if (arbre->fils[i] == NULL) {
            insererDansNoeud(arbre, element, i);
            return;
        } else {
            arbre = arbre->fils[i];
        }
    }

    // 插入到叶子节点
    int i = 0;
    while (i < arbre->nbFils && element > arbre->donnee[i]) {
        i++;
    }
    insererDansNoeud(arbre, element, i);

    // 如果节点超过了最大数据数，则进行分裂
    if (arbre->nbFils > 3) {
        if (*racine == arbre) {
            Arbre234 new_root = creerNoeud();
            new_root->nbFils = 1;
            new_root->donnee[0] = arbre->donnee[1];
            new_root->fils[0] = arbre;
            *racine = new_root;
            splitter(arbre, 0, new_root);
        } else {
            Arbre234 parent = arbre->fils[arbre->nbFils - 1];
            splitter(arbre, 0, parent);
        }
    }
}

// 中序遍历输出树的元素
void afficherArbre(Arbre234 arbre) {
    if (arbre != NULL) {
        for (int i = 0; i < arbre->nbFils; i++) {
            afficherArbre(arbre->fils[i]);
            printf("%d ", arbre->donnee[i]);
        }
    }
}

// 构建2-3-4树并插入元素
void construireArbre(Arbre234 *racine, TElement elements[], int taille) {
    for (int i = 0; i < taille; i++) {
        inserer(racine, elements[i]);
    }
}

//找最小值
TElement trouverMin(Arbre234 arbre) {
    // 如果树为空，返回一个无效的值
    if (arbre == NULL) {
        return -1;  // 这里假设-1为无效的值
    }

    // 遍历最左边的子树
    while (arbre->nbFils > 0) {
        arbre = arbre->fils[0];  // 递归进入最左子树
    }

    return arbre->donnee[0];  // 返回最左叶子节点的第一个数据
}

TElement trouverMax(Arbre234 arbre) {
    // 如果树为空，返回一个无效的值
    if (arbre == NULL) {
        return -1;  // 这里假设-1为无效的值
    }

    // 遍历最右边的子树
    while (arbre->nbFils > 0) {
        arbre = arbre->fils[arbre->nbFils - 1];  // 递归进入最右子树
    }

    return arbre->donnee[arbre->nbFils - 1];  // 返回最右叶子节点的最后一个数据
}


//返回给定elt的地址
Arbre234 rechercherElement(Arbre234 arbre, TElement element) {
    if (arbre == NULL) {
        return NULL;  // 如果树为空，返回NULL
    }

    // 查找当前节点中的元素位置
    for (int i = 0; i < arbre->nbFils; i++) {
        if (element == arbre->donnee[i]) {
            return arbre;  // 找到元素，返回当前节点的地址
        } else if (element < arbre->donnee[i]) {
            // 如果当前元素小于节点的值，进入左侧子树
            return rechercherElement(arbre->fils[i], element);
        }
    }

    // 如果元素大于节点中的所有元素，进入右侧子树
    return rechercherElement(arbre->fils[arbre->nbFils], element);
}


// 统计节点类型的递归函数
void compterTypesDeNoeuds(Arbre234 arbre, int *compteur2, int *compteur3, int *compteur4) {
    if (arbre == NULL) {
        return;
    }

    // 根据当前节点的元素个数更新计数器
    int nbElements = arbre->nbFils; // 当前节点的元素个数
    if (nbElements == 1) {
        (*compteur2)++;
    } else if (nbElements == 2) {
        (*compteur3)++;
    } else if (nbElements == 3) {
        (*compteur4)++;
    }

    // 遍历子节点
    for (int i = 0; i <= arbre->nbFils; i++) {
        compterTypesDeNoeuds(arbre->fils[i], compteur2, compteur3, compteur4);
    }
}

// 计算节点类型数量的函数
void calculerTypesDeNoeuds(Arbre234 arbre) {
    int compteur2 = 0, compteur3 = 0, compteur4 = 0;

    compterTypesDeNoeuds(arbre, &compteur2, &compteur3, &compteur4);

    printf("Nombre de 2-nœuds : %d\n", compteur2);
    printf("Nombre de 3-nœuds : %d\n", compteur3);
    printf("Nombre de 4-nœuds : %d\n", compteur4);
}


// 前序遍历
void parcoursPreOrdre(Arbre234 arbre) {
    if (arbre == NULL) return;

    // 打印当前节点数据
    for (int i = 0; i < arbre->nbFils; i++) {
        printf("%d ", arbre->donnee[i]);
    }

    // 遍历子树
    for (int i = 0; i <= arbre->nbFils; i++) {
        parcoursPreOrdre(arbre->fils[i]);
    }
}

// 中序遍历
void parcoursInOrdre(Arbre234 arbre) {
    if (arbre == NULL) return;

    // 遍历子树和打印数据
    for (int i = 0; i < arbre->nbFils; i++) {
        parcoursInOrdre(arbre->fils[i]);
        printf("%d ", arbre->donnee[i]);
    }
    // 遍历最后一个子树
    parcoursInOrdre(arbre->fils[arbre->nbFils]);
}

// 后序遍历
void parcoursPostOrdre(Arbre234 arbre) {
    if (arbre == NULL) return;

    // 遍历所有子树
    for (int i = 0; i <= arbre->nbFils; i++) {
        parcoursPostOrdre(arbre->fils[i]);
    }

    // 打印当前节点数据
    for (int i = 0; i < arbre->nbFils; i++) {
        printf("%d ", arbre->donnee[i]);
    }
}
int main() {
    Arbre234 a = NULL;
    TElement elements[] = {8, 15, 35, 2, 4, 12, 19, 22, 39, 1, 3, 6, 7, 10, 18, 20, 21};
    int taille = sizeof(elements) / sizeof(elements[0]);

    inserer(&a,2);
    inserer(&a,3);
    inserer(&a,1);
    inserer(&a,6);
    inserer(&a,5);


    // construireArbre(&racine, elements, taille);

    // printf("Elements de l'arbre 2-3-4 en ordre : ");
    afficherArbre(a);
    printf("\n");

    return 0;
}