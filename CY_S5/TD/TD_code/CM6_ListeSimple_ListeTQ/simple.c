//
// Created by 金卓远 on 24-11-1.
//
#include "operation_simple.h"

int main() {

    Liste liste=init();
    liste=inserTete(3,liste);
    liste=inserTete(2,liste);
    liste=inserTete(1,liste);
    liste=inserQueue(4,liste);

    parcours(liste);
    printf("\n");
    // liste=suppTete(liste);
    // suppElementListe(2,liste);
    suppPosListe(2,liste);
    parcours(liste);
}