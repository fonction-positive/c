//
// Created by 金卓远 on 24-12-14.
//

#include "ArbreBinaireCherche.h"



int main() {
    int tableau[] = {5, 2, 8, 3, 1, 7, 4, 6};
    int taille = sizeof(tableau) / sizeof(tableau[0]);

    Arbre a=creatABRParTab(tableau,taille);
    int h=hauteurArbre(a);
    // afficherArbre(a,h);

    parcoursInfixe(a);
    printf("\n");
    suppMaxABR(&a);
    parcoursInfixe(a);


    printf("Tableau avant tri :\n");
    afficherTableau(tableau, taille);

    triParABR(taille, tableau);

    printf("Tableau après tri :\n");
    afficherTableau(tableau, taille);

    printf("最小值：%d \n",minABR(a));

    return 0;
}