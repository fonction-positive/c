//
// Created by 金卓远 on 24-11-3.
//
#include"operation_simple2.h"


int main() {

    Liste liste=init();
    inserTete(3,&liste);
    inserTete(2,&liste);
    inserTete(1,&liste);
    inserQueue(4,&liste);

    parcours(liste);
    printf("\n");
    // suppTete(&liste);
    suppElementListe(2,&liste);
    parcours(liste);
}