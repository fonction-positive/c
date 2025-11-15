//
// Created by 金卓远 on 25-3-2.
//

#ifndef CONNEXES_H
#define CONNEXES_H
#include"../TD3/profondeur.h"
#include"../TD3/largeur.h"

//找连通分量（无向图）
///trouverComposantesConnexes
//找强连通分量（有向图）
///somSuivant_PPG、somSuivant_PPTG
///parcoursProfondeurSuffixe 第一遍深度遍历
///parcoursProfondeurTransposeG 对转置图深度遍历
///ComposanteFortementConnexe 主函数
///伪代码在最后
//Effectuer un premier parcours DFS sur le graphe  G  et enregistrer l’ordre de sortie de chaque sommet au cours du parcours.
//Ensuite,transposer le graphe et effectuer un deuxième parcours DFS sur le graphe transposé en suivant l’ordre inverse de sortie
//afin d’obtenir les composantes fortement connexes(CFC)


// 分配布尔数组
int* allocTab(int n) {
    return (int*)malloc(n*sizeof(int));
}

// 释放布尔数组
void libTab(int* tab) {
    free(tab);
}

//Composantes connexes
//寻找连通分量（对于无向图）
void trouverComposantesConnexes(MatAdj g) {
    int n = g.nbSom;
    int* visite = allocTab(n);
    int nbSomVisite = 0;
    int s = 0;
    int finParcours = 0;

    while (!finParcours) {
        // 选择 DFS 或 BFS
        reParcoursProfondeur_MA(s, visite, g, n , &nbSomVisite);
        // itParcoursProfondeur_MA(s, visite, g, n, &nbSomVisite);
        // itParcoursLargeur_MA(s, visite, g, n, &nbSomVisite);

        if (nbSomVisite < n) {
            printf("\n");
            s = somSuivant(s, n, visite);
        } else {
            finParcours = 1;
        }
    }

    libTab(visite);
}


// 寻找下一个未访问的顶点，用于构建后缀序遍历（第一遍深度优先搜索）
int somSuivant_PPG(int s, int n, int *visite) {
    for (int i = s + 1; i < n; i++) {
        if (!visite[i]) {
            return i;
        }
    }
    return s; // 如果没有找到未访问的顶点，返回当前顶点（理论上不应出现这种情况，除非逻辑错误）
}

// 寻找下一个用于转置图深度优先搜索的顶点，基于后缀序列表L
int somSuivant_PPTG(int s, int n, int *visite, int *L) {
    for (int i = s - 1; i >= 0; i--) {
        if (!visite[L[i]]) {
            return i;
        }
    }
    return s; // 如果没有找到合适的顶点，返回当前顶点（理论上不应出现这种情况，除非逻辑错误）
}


//Parcours en Profondeur en ordre Suffixe
//后序遍历（对图G进行DFS遍历，并在遍历过程中，记录每一个点的退出顺序）
// 深度优先搜索后缀序遍历
void parcoursProfondeurSuffixe(int s, int *visite, MatAdj G, int *L, int *nbSomVisite) {
    visite[s] = 1;
    for (int t = 0; t < G.nbSom; t++) {
        if (G.mat[s][t]==1 && !visite[t]) {
            parcoursProfondeurSuffixe(t, visite, G, L, nbSomVisite);
        }
    }
    L[(*nbSomVisite)++] = s;
}

//对图 G 的转置图进行深度优先遍历
void parcoursProfondeurTransposeG(int s, int *visite, MatAdj G, int *CFC, int NumCFC, int *nbSomVisite) {
    visite[s] = 1;
    CFC[s] = NumCFC;  // 记录强连通分量编号
    (*nbSomVisite)++;
    for (int t = 0; t < G.nbSom; t++) {
        if (G.mat[t][s]==1 && !visite[t]) {
            parcoursProfondeurTransposeG(t, visite, G, CFC, NumCFC, nbSomVisite);
        }
    }
}

void ComposanteFortementConnexe(MatAdj G, int *CFC, int *nbCFC) {
    int n = G.nbSom;
    int *visite = (int *)malloc(n * sizeof(int));
    int *L = (int *)malloc(n * sizeof(int));  // 用于记录后序遍历的顶点顺序
    int nbSomVisite = 0;
    int finParcours = 0;
    int s = 0;

    // 初始化访问数组
    for (int i = 0; i < n; i++) {
        visite[i] = 0;
    }

    // 构建后缀序顶点列表
    while (!finParcours) {
        parcoursProfondeurSuffixe(s, visite, G, L, &nbSomVisite);
        if (nbSomVisite<n) {
           s=somSuivant_PPG(s,n,visite);
        }else{
            finParcours = 1;
        }
    }

    // 重置访问数组
    for (int i = 0; i < n; i++) {
        visite[i] = 0;
    }

    *nbCFC = 0;
    nbSomVisite = 0;
    finParcours = 0;
    s = n-1;

    // 对转置图进行深度优先搜索
    while (!finParcours) {
        (*nbCFC)++;
        parcoursProfondeurTransposeG(L[s], visite, G, CFC, *nbCFC, &nbSomVisite);
        if (nbSomVisite<n) {
            s=somSuivant_PPTG(s,n,visite,L);
        }else{
            finParcours = 1;
        }
    }

    free(visite);
    free(L);
}

#endif //CONNEXES_H

/*
//找连通分量
procédure ComposantesConnexes(Graphe g)
Début
    //Initialisation
    n ← nbSom(g)
    visite ← allocTab(n)
    pour chaque sommet s variant de 1 à n faire
        visite[s] ← faux
    finPour
    s ← 1
    nbSomVisite ← 0
    finParcours ← faux
    //Traitement
    Tantque non finParcours faire
        reParcoursProfondeur(s, visite, g, nbSomVisite, ....) //A modifier
        // itParcoursProfondeur(s, visite, g, nbSomVisite, ....) //A modifier
        // parcoursLargeur((s, visite, g, nbSomVisite, ....)) //A modifier

        Si nbsomVisite < n
            traiter("\n")
            s ← somSuivant(s, n, visite)
        Sinon
            finParcours ← Vrai
        FSi
    FinTq
    Visite ← libTab (tab)
Fin
*/
//-------------------------------------------------------------------
/*
// 寻找下一个未访问的顶点，用于构建后缀序遍历（第一遍深度优先搜索）
fct somSuivant_PPG (s, n, visite)
Début
    Pour i variant de s + 1 à n - 1 faire
        Si non visite[i] alors
            Retourner i
        Finsi
    Ffinpour
    Retourner s
Fin

// 寻找下一个用于转置图深度优先搜索的顶点，基于后缀序列表L
fct somSuivant_PPTG (s, n, visite, L)
Début
    Pour i variant de s - 1 à 0 faire
        Si non visite[L[i]] alors
            Retourner i
        Finsi
    Ffinpour
    Retourner s
Fin

// 深度优先搜索后缀序遍历
procédure parcoursProfondeurSuffixe(s, visite, G, L, nbSomVisite)
Début
    Visite[s] ← vrai
    Pour chaque t ∈ Γ(s) dans G faire
        Si non visite[t] alors
            parcoursProfondeurSuffixe(t, visite, G, L, nbSomVisite)
        Finsi
    Finpour
    nbSomVisite ← nbSomVisite + 1
    L[nbSomVisite] ← s
Fin

//对图 G 的转置图进行深度优先遍历
procédure parcoursProfondeurTransposeG (s, visite, G, CFC, NumCFC, nbSomVisite)
Début
    Visite[s] ← vrai
    CFC[s] ← NumCFC
    nbSomVisite ← nbSomVisite + 1
    Pour chaque t prédécesseur de s dans G faire
        Si non visite[t] alors
            parcoursProfondeurTransposeG (t, visite, G, CFC, NumCFC, nbSomVisite)
        Finsi
    Finpour
FIN

procédure ComposanteFortementConnexe(G, CFC, nbCFC)
Début
    //initialisation
    n ← nbSom (G)
    visite ← allocTab (n)
    Pour s variant de 1 à n faire
        visite[s] ← faux
    Fpour
    nbSomVisite← 0
    finParcours ← faux
    s ← 1
    //Construction de la liste L des sommets en ordre suffixe de G
    Tantque (non finParcours) faire
        parcoursProfondeurSuffixe(s, visite, G, L, nbSomVisite)
        Si nbsomVisite < n alors
            s ←somSuivant_PPG(s, n, visite)
        Sinon
            finParcours ← Vrai
        FSi
    Fintq
    //Parcours en profondeur de tG
    // initialisation
    pour s variant de 1 à n faire
        visite[s] ← faux
    fpour
    nbCFC ← 0
    nbSomVisite← 0
    finParcours ← faux
    s ← n
    Tantque (non finParcours) faire
        nbCFC ← nbCFC + 1
        ParcoursProfondeurTransposeG(L[s], visite, G, CFC, nbCFC, nbSomVisite)
        Si nbsomVisite < n alors
            s ←somSuivant_PPTG(s, n, visite, L)
        Sinon
            finParcours ← Vrai
        FSi
    FinTq
    Visite ← libTab(n)
Fin
*/