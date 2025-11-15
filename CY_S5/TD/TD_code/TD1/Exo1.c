//
// Created by 金卓远 on 24-9-9.
//
#include<stdio.h>
#include <stdlib.h>
#include <time.h>

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

//Version1
void fusionner_v1(int indinf,int indmil,int indsup,int tab[]) {
    int n1=indmil-indinf+1; //左边数组长度（mid在左边数组中）
    int n2=indsup-indmil; //右边数组长度
    int tab1[n1],tab2[n2];
    //复制左边部分到tab1，右边部分到tab2
    for (int i=0;i<n1;i++) {
        tab1[i]=tab[indinf+i];
    }
    for (int i=0;i<n2;i++) {
        tab2[i]=tab[indmil+1+i];
    }

    int i=0,j=0,k=indinf;
    while (i < n1 && j< n2) {
        if (tab1[i]<=tab2[j]) {
            tab[k]=tab1[i];
            i++;
        }else {
            tab[k]=tab2[j];
            j++;
        }
        k++;
    }

    while (i<n1) {
        tab[k]=tab1[i];
        i++;
        k++;
    }
    while (j<n2) {
        tab[k]=tab2[j];
        j++;
        k++;
    }

}
void tri_fusion(int indinf,int indsup,int tab[]) {
    if (indinf<indsup) {
        int indmil=(indinf+indsup)/2;
        tri_fusion(indinf,indmil,tab);
        tri_fusion(indmil+1,indsup,tab);
        fusionner_v1(indinf,indmil,indsup,tab);
    }
}

//中国人的思路 Hoare法（选取最左边为pivot）
int partition(int left,int rigth,int tab[]) {
    //把最左边的元素作为pivot
    int indpivot=left;
    int pivot=tab[indpivot];
    //如果left<right则继续循环，说明还没相遇
    while (left<rigth) {
        //如果把最左边的元素作为pivot，得先从right往左移开始，确保left=right的时候那个元素是小于pivot的
        //移动right，找小于pivot的元素
        while (left<rigth && tab[rigth]>=pivot)
            rigth--;
        //移动left，找大于pivot的元素
        while (left<rigth && tab[left]<=pivot)
            left++;
        //交换left和right
        permutation(left,rigth,tab);
    }
    //交换pivot和相遇位置，并返回相遇位置的坐标
    permutation(left,indpivot,tab);
    return left;
}

void triRapid(int indinf,int indsup,int tab[]) {
    if (indinf<indsup) {
        int indpivot=partition(indinf,indsup,tab);
        triRapid(indinf,indpivot-1,tab);
        triRapid(indpivot+1,indsup,tab);
    }
}



void afficher(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int tab[] = {1, 4, 5, 6, 3, 2, 7};
    int n = sizeof(tab) / sizeof(tab[0]);

    // int n=100;
    // int tab[n];
    // for (int i=0;i<n;i++) {
    //     srand(0);
    //     tab[i]=rand()%101;
    // }

    // afficher(tab, n);
    clock_t start1=clock();
    TriSelectionIterative(n,tab);
    clock_t end1=clock();
    double time1=end1-start1;
    printf("selection : %f\n",time1);

    clock_t start_inser=clock();
    triInsertion(n,tab);
    clock_t end_inser=clock();
    printf("selection : %lu\n",end_inser-start_inser);



    // afficher(tab, n);
}
