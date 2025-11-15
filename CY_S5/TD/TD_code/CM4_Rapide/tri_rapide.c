//
// Created by 金卓远 on 24-10-20.
//
//分而治之
//version2：
//选择数组第一个元素作为pivot，i和j分别从第二个元素和最后一个元素开始移动
//i先往右移，找到第一个大于pivot的停止（等于pivot的元素放在左边）
//然后j往左移，找到第一个小于等于pivot的元素停止
//交换tab[i]和tab[j]
//直到i=j停止循环
//如果pivot不等于k则交换pivot和k

#include <stdio.h>

void permutation(int i, int j, int tab[]) {
    int tmp = tab[i];
    tab[i] = tab[j];
    tab[j] = tmp;
}

//奇怪的思路不太看得懂
int partitionner(int indinf,int indsup,int tab[]) {
    int indpivot=indinf;
    int pivot=tab[indpivot];
    int i=indinf+1;
    int k=indsup;

    //如果i<k说明还没有相遇，继续交换数组内元素
    while (i<=k) {
        //如果i<k且元素i小于
        while (i<=k && tab[i]<=pivot)
            i++;
        while (i<=k && tab[k]>pivot)
            k--;
        if (i<k) {
            permutation(i,k,tab);
            i++;
            k--;
        }
    }
    if (indpivot!=k)
        permutation(indpivot,k,tab);
    return k;
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



void afficherTab(int n, int tab[]) {
    for (int i = 0; i < n; i++)
        printf("%d ", tab[i]);
    printf("\n");
}

int main(int argc, char *argv[]) {
    int tab[] = {8,15,4,9,16,12,5,0};
    int n = sizeof(tab) / sizeof(tab[0]);

    afficherTab(n,tab);
    triRapid(0,n-1,tab);
    afficherTab(n,tab);
}