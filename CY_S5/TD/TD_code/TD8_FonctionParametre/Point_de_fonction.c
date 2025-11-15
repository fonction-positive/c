#include <stdio.h>
//
// Created by 金卓远 on 24-12-8.
//
int somme(int a, int b) {
    return (a + b);
}

int diff(int a, int b) {
    return (a - b);
}

int produit(int a, int b) {
    return (a * b);
}

// b !=0
int division(int a, int b) {
    return (a / b);
}

int modulo(int a, int b) {
    return (a % b);
}

// fct en Parametre
//这个函数有三个变量，int x,int y 和一个指向函数的指针
int OperatBinaire(int x, int y, int (*f)(int, int)) {
    //appel de f sur les arguments x et y
    //调用函数指针指向的那个函数
    return ((*f)(x, y));
}


//Renommage fct en parametre = Def Type Fct
//给函数指针取一个别名
typedef int (*Fptr)(int, int);

// Passage d une fct en parametre a une fct
int OperatBinaire2(int x, int y, Fptr f ) {
    //appel de f sur les arguments x et y
    return ((*f)(x,y) ) ;
}

void main(void) {
    printf("\n Operations Passage par nom fcts");
    printf("\n %d ", OperatBinaire(3, 4, somme));
    printf("\n %d ", OperatBinaire(3, 4, diff));
    printf("\n %d ", OperatBinaire(3, 4, produit));
    printf("\n %d ", OperatBinaire(3, 4, division));
    printf("\n %d ", OperatBinaire(3, 4, modulo));
    printf("\n Operations Passage par adresse des fcts");
    printf("\n %d ", OperatBinaire(3, 4, &somme));
    printf("\n %d ", OperatBinaire(3, 4, &diff));
    printf("\n %d ", OperatBinaire(3, 4, &produit));
    printf("\n %d ", OperatBinaire(3, 4, &division));
    printf("\n %d ", OperatBinaire(3, 4, &modulo));
    printf("\n");
}


