#include <stdio.h>
#include <stdlib.h>

//
// Created by 金卓远 on 24-11-3.
//

typedef int TElement;

//链表的一个节点
typedef struct cellule {
    TElement donnee;
    struct cellule* suivant;
}*Liste;

//TabListe
typedef struct {
    int taille;
    Liste *tab;
}Table;

//在有序链表中找值
int rechercherElement(TElement elt,Liste l) {
    Liste courante=l;
    while (courante!=NULL) {
        if (courante->donnee==elt) {
            return 1;
        }
        courante=courante->suivant;
    }
    return 0;
}
//在有序链表中插入
Liste insererElement(TElement elt,Liste l) {
    Liste cel=malloc(sizeof(struct cellule));
    cel->donnee=elt;
    cel->suivant=NULL;

    if(l==NULL || elt < l->donnee) {
        cel->suivant=l;
        l=cel;
        return l;
    }

    Liste courante=l;
    while (courante->suivant!=NULL && courante->suivant->donnee<elt) {
        courante=courante->suivant;
    }
    cel->suivant=courante->suivant;
    courante->suivant=cel;
    return l;
}

//在有序链表中删除给定元素
Liste suppElement(TElement elt,Liste l) {
    if (l==NULL) {
        return l;
    }
    if (l->donnee==elt) {
        Liste addresse=l;
        l=l->suivant;
        free(addresse);
        return l;
    }
    Liste courante=l;
    while (courante!=NULL) {
        if (courante->suivant->donnee==elt) {
            Liste addresse=courante->suivant;
            courante->suivant=courante->suivant->suivant;
            free(addresse);
        }
        courante=courante->suivant;
    }
    return l;
}

void parcour(Liste l) {
    Liste courante=l;
    while (courante!=NULL) {
        printf("%d->",courante->donnee);
        courante=courante->suivant;
    }
}
//给table分配内存
Table allocMemTable(int taille) {
    Table table;
    table.tab=malloc(taille*sizeof(Liste));
    if (table.tab==NULL) {
        printf("error memorie");
        exit(1);
    }
    return table;
}
//释放内存
void libererTable(Table * table) {
    for (int i=0;i<table->taille;i++) {//便利每个链表
        Liste courante=table->tab[i];
        while (courante!=NULL) {
            Liste f=courante; //f来保存节点的地址，防止丢失
            courante=courante->suivant; //便利每个节点，把所有节点释放
            free(f);
        }
    }
    free(table->tab); //把竖着的tab也释放掉
}
//初始化
Table initialiserTable(int taille) {
    Table table=allocMemTable(taille);
    table.taille=taille;
    //给tab全部赋初值NULL
    for (int i=0;i<table.taille;i++) {
        table.tab[i]=NULL;
    }
    return table;
};

//把给定数组中的数填充到tableliste中
Table remplirTableIteratif(Table table, TElement arr[], int n) {
    for (int i=0;i<n;i++) {
        int pos=arr[i] % table.taille;
        if (!rechercherElement(arr[i],table.tab[pos])) {
            table.tab[pos]=insererElement(arr[i],table.tab[pos]);
        }
    }
    return table;
};

Table remplirTableRecursif(Table table,TElement arr[],int n,int index) {
    if(index>=n) {
        return table;
    }

    int pos=arr[index] % table.taille;
    if (!rechercherElement(arr[index],table.tab[pos])) {
        table.tab[pos]=insererElement(arr[index],table.tab[pos]);
    }
    return remplirTableRecursif(table,arr,n,index+1);
}
//打印table
void afficherTable(Table table) {
    for (int i=0;i<table.taille;i++) {
        printf("%d : ",i);
        Liste courante=table.tab[i];
        while (courante!=NULL) {
            printf("%d->",courante->donnee);
            courante=courante->suivant;
        }
        printf("\n");
    }
};
//统计链表里节点个数
int compterElements(Liste l) {
    Liste courante=l;
    int compter=0;
    while (courante!=NULL) {
        compter++;
        courante=courante->suivant;
    }
    return compter;
};
//找出第几个桶节点最多（迭代）
int plusElementIteratif(Table table) {
    int plus=0; //假设第0个桶最多
    int max_compter=compterElements(table.tab[0]);
    for (int i=0;i<table.taille;i++) {
        if (compterElements(table.tab[i])>max_compter) {
            plus=i;
            max_compter=compterElements(table.tab[i]);
        }
    }
    return plus;
}
//递归
int plusElementRecursif(Table table,int index,int plus,int max_compter) {
    if (index>=table.taille) {
        return plus;
    }
    int current_compter=compterElements(table.tab[index]);
    if (current_compter>max_compter) {
        plus=index;
        max_compter=current_compter;
    }
    return plusElementRecursif(table,index+1,plus,max_compter);
}
//在table中删除指定元素
Table supprimerElementTable(TElement elt,Table table) {
    // 计算元素在哈希表中的位置
    int pos = elt % table.taille;

    if (rechercherElement(elt,table.tab[pos])) {
        table.tab[pos]=suppElement(elt,table.tab[pos]);
    }else {
        printf("n'existe pas!");
    }
    return table;
}


int main(void) {
    // TElement tab[] = {14, 72, 99, 7, 103, 14, 56, 9, 5, 13, 6, 2, 12, 15, 19, 33, 47, 13, 0};
    // int n = 17;
    // Table t;

    TElement tab[] = {72, 14, 100, 13, 14, 56, 9 , 5, 13, 20};
    int n = 10;
    Table t;
    //
    //
    // Liste l=NULL;
    // l=insererElement(1,l);
    // l=insererElement(2,l);
    // l=insererElement(5,l);
    // l=insererElement(3,l);
    // l=insererElement(4,l);
    //
    // parcour(l);
    // printf("\n");
    // printf("%d",rechercherElement(1,l));
    // printf("\n");
    //
    // parcour(l);
    // printf("\n");
    //
    // l=suppElement(1,l);
    // parcour(l);

    //测试搜索函数
    // printf("%d",rechercherElement(8,l));



    //
    // 初始化表
    t=initialiserTable(7);

    // 填充表（使用迭代或递归）
    t=remplirTableIteratif(t, tab, n);

    // 显示表内容
    afficherTable(t);


    // 统计元素数量
    // printf("Nombre d'elements: %d\n", compterElements(t.tab[2]));
    // printf("possède le plus d’éléments : %d \n",plusElementIteratif(t));
    printf("possède le plus d’éléments : %d \n",plusElementRecursif(t,0,0,compterElements(t.tab[0])));


    // 删除元素示例
    t=supprimerElementTable(13,t);
    afficherTable(t);


    // 释放表内存
    libererTable(&t);

    return 0;
}
