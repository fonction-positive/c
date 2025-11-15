//
// Created by 金卓远 on 24-12-2.
//
#include "ArbreParfait.h"


int main() {

    // int racine=8;
    // int res=filsDroitAP(racine);
    // printf("%d",res);


        ArbreParfait a=allocMemAP(20);
        a=initAP(a);
        int i=0;
        int b[10]={23,15,7,12,5,6,1,4,8,2};
        for(i=0;i<10;i++){
            a.tab[i]=b[i];
            a.taille++;
        }


        ParcoursInfixe(0,a);
        printf("\n");

        ParcoursPostfixe(0,a);
        printf("\n");

        ParcoursPrefixe(0,a);
        printf("\n");

        ParcoursLargeur(a);
        printf("\n");
    }




