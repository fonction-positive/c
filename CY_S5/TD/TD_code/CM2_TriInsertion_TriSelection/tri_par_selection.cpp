//
// Created by 金卓远 on 24-10-20.
//

#include <algorithm>
#include<stdio.h>

//找到最小数的索引
int indiceMin(int i, int n, int tab[]) {
    int iMin = i;
    for (int ind = i + 1; ind < n; ind++) {
        if (tab[ind] < tab[iMin]) {
            iMin = ind;
        }
    }
    return iMin;
}

//交换函数
void permutation(int i, int j, int tab[]) {
    int tmp = tab[i];
    tab[i] = tab[j];
    tab[j] = tmp;
}

//选择排序循环写法，每次找最小的放到最前面
void TriSelectionIterative(int n, int tab[]) {
    for (int i = 0; i < n - 1; i++) {
        int iMin = indiceMin(i, n, tab);
        if (i != iMin) {
            permutation(i, iMin, tab);
        }
    }
}

void afficherTab(int n, int tab[]) {
    for (int i = 0; i < n; i++)
        printf("%d", tab[i]);
    printf("\n");
}

int indiceMax(int i, int n, int tab[]) {
    int iMax = i;
    for (int ind = i + 1; ind < n; ind++) {
        if (tab[ind] > tab[iMax]) {
            iMax = ind;
        }
    }
    return iMax;
}

//选择排序递归写法（从右往左，找最大的）
void TriSelectionRecursive_DG(int n, int tab[]) {
    if (n>1) {
        int iMax=indiceMax(0,n,tab);
        if (n!=iMax) {
            permutation(iMax,n-1,tab);
        }
        TriSelectionRecursive_DG(n-1,tab);
    }
}

//选择排序递归写法，从左往右
void TriSelectionRecursive_GD(int i,int n,int tab[]) {
    if (i<n) {
        int iMin=indiceMin(i,n,tab);
        if (i!=iMin) {
            permutation(i,iMin,tab);
        }
        TriSelectionRecursive_GD(i+1,n,tab);
    }
}


int main(int argc, char *argv[]) {
    int tab[] = {8, 4, 2, 5, 2, 6, 7, 1};
    int n = sizeof(tab) / sizeof(tab[0]);
    // int res = indiceMin(0, n, tab);
    // int res = indiceMax(0, n, tab);
    // printf("%d", res);

    // afficherTab(n,tab);
    // TriSelectionIterative(n,tab);
    // afficherTab(n,tab);

    afficherTab(n,tab);
    // TriSelectionRecursive_DG(n,tab);
    TriSelectionRecursive_GD(0,n,tab);
    afficherTab(n,tab);
}
