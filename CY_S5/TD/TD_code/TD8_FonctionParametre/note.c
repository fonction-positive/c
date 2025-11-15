//
// Created by 金卓远 on 24-12-8.
//

#include <stdio.h>
#include <stdlib.h>
#include <malloc/malloc.h>
///指针函数（返回值是指针的函数）
//这是一个普通的函数,返回一个整数
int func() {
    int a = 10;
    return a;
}

//这是一个返回值为指针的函数，返回一个地址（指针函数）
int *func2() {
    int *a = malloc(sizeof(int));
    *a = 10;
    return a;
}


//*悬挂指针
//因为在函数运行结束后，函数中定义的所有栈区变量都会被自动释放
//所以如果不是malloc申请的堆区变量，肯能会造成悬挂指针
int *fa() {
    int a = 10;
    int *pa = &a;
    return pa;
}

int *fb() {
    int b = 20;
    int *pb = &b;
    return pb;
}

int main() {
    int *pa = NULL;
    int *pb = NULL;
    *pa = fa();
    printf("pa : %p", pa); //地址
    printf("*pa %d: ", *pa); //10

    *pb = fb();
    printf("pb : %p", pb); //地址
    printf("*pb %d: ", *pb); //20

    *pa = fa();
    printf("pa : %p", pa); //地址
    printf("*pa %d: ", *pa); // 10 ? 20 ?
}

//以上函数pa和pb的地址是相同的，而且第二次打印的pa的值会变成20
//这是一个悬挂指针的例子


///函数指针(指向一个函数的指针）
//和数组同理，数组名可以表示数组的地址（tab和&tab都表示数组的地址）
//函数也是这样，函数名可以表示函数的地址（func=&func）
int (*f)(int);

//这是一个指向函数的指针，函数的参数在后面括号里，函数的返回值在前面


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
int OperatBinaire(int x, int y, int (*f)(int, int)) {
    //appel de f sur les arguments x et y
    return ((*f)(x, y));
}
