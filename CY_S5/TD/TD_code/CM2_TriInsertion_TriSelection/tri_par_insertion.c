//
// Created by 金卓远 on 24-10-20.
//
#include <stdio.h>

void afficherTab(int n, int tab[]) {
    for (int i = 0; i < n; i++)
        printf("%d", tab[i]);
    printf("\n");
}


//一个数组左边为有序数列，将右边的元素一个个插入到左边有序数列中
void triInsertion(int n,int tab[]) {
    for(int j=1;j<n;j++) {
        int carte=tab[j];
        int i=j-1;
        //i为左边有序数列最后一个元素，carte从右往左比较，知道找到比carte小的元素，然后把carte插入到其右边
        while(i>=0 && carte<tab[i]) {
            //如果不是，就把左边的数列元素往后移，腾出位子
            tab[i+1]=tab[i];
            i--;
        }
        //找到第一个比carte小的元素，然后把carte插到i+1的位置上
        tab[i+1]=carte;
    }
}

int main(int argc, char *argv[]) {
    int tab[] = {8, 4, 2, 5, 2, 6, 7, 1};
    int n = sizeof(tab) / sizeof(tab[0]);

    afficherTab(n,tab);
    triInsertion(n,tab);
    afficherTab(n,tab);
}