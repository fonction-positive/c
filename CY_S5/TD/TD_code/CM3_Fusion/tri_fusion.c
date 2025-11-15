//
// Created by 金卓远 on 24-10-20.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void afficherTab(int n, int tab[]) {
    for (int i = 0; i < n; i++)
        printf("%d ", tab[i]);
    printf("\n");
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

//Version2 将最后一个元素设为无穷大
void fusionner_v2(int indinf,int indmil,int indsup,int tab[]) {
    int VMAX=100000;

    //数组长度增加1，用来放VMAX
    int n1=indmil-indinf+2;
    int n2=indsup-indmil+1;
    int tab1[n1];
    int tab2[n2];
    //复制数组
    for (int i=0;i<n1-1;i++) {
        tab1[i]=tab[indinf+i];
    }
    for (int i=0;i<n2-1;i++) {
        tab2[i]=tab[indmil+1+i];
    }
    tab1[n1-1]=VMAX;
    tab2[n2-1]=VMAX;

    int i=0,j=0;
    for (int k=indinf;k<=indsup;k++) {
        if (tab1[i]<tab2[j]) {
            tab[k]=tab1[i];
            i++;
        }else {
            tab[k]=tab2[j];
            j++;
        }
    }
}


void tri_fusion(int indinf,int indsup,int tab[]) {
    if (indinf<indsup) {
        int indmil=(indinf+indsup)/2;
        tri_fusion(indinf,indmil,tab);
        tri_fusion(indmil+1,indsup,tab);
        fusionner_v2(indinf,indmil,indsup,tab);
    }
}



int main(int argc, char *argv[]) {
    int n=10000;
    int tab[n];
    // int n = sizeof(tab) / sizeof(tab[0]);

    for (int i=0;i<n;i++) {
        tab[i]=rand()%101;
    }

    afficherTab(n,tab);

    clock_t start=clock();
    tri_fusion(0,n,tab);
    clock_t end=clock();

    afficherTab(n,tab);

    float time=end-start;
    printf("%.6f",time);
}