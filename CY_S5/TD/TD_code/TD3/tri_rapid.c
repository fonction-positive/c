//
// Created by 金卓远 on 24-9-24.
//

#include <stdio.h>
void swap(int *a,int *b) {
    int temp=*a;
    *a=*b;
    *b=temp;
}

int partition(int tab[],int left,int right) {
    int pivot=tab[left]; //选择第一个元素为基准
    int i=left+1;
    int j=right;

    while (i<=j) {
        while (i<=right && tab[i]<=pivot) {
            i++;
        }
        while (j>=left && tab[j]>pivot) {
            j--;
        }
        if (i<j) {
            swap(&tab[i],&tab[j]);
        }
    }
    //让pivot到准确位置
    swap(&tab[left],&tab[j]); //left是最初pivot位置，j是最终pivot的位置
    return j;
}

void tri_rapid(int tab[],int left,int right) {
    if (left<right) {
        int pivotindex=partition(tab,left,right);
        tri_rapid(tab,left,pivotindex-1);
        tri_rapid(tab,pivotindex+1,right);
    }
}

void afficher(int tab[],int n) {
    for (int i=0;i<n;i++) {
        printf("%d",tab[i]);
    }
    printf("\n");
}

int main() {
    int tab[]={6,8,9,4,5,4,3,2};
    int n=sizeof(tab)/sizeof(tab[0]);

    afficher(tab,n);

    tri_rapid(tab,0,n-1);

    afficher(tab,n);
}

