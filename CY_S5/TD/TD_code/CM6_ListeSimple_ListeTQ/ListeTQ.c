//
// Created by 金卓远 on 24-11-3.
//
#include "ListeTQ.h"

int main() {

    ListeTQ liste=initLTQ();

    inserTeteLTQ(3,&liste);
    inserTeteLTQ(2,&liste);
    inserTeteLTQ(1,&liste);

    inserQueue(4,&liste);
    inserQueue(5,&liste);

    suppTeteLTQ(&liste);

    // liste=inserTeteLTQ(3,liste);
    // liste=inserTeteLTQ(2,liste);
    // liste=inserTeteLTQ(1,liste);

    parcourLTQ(liste);
}