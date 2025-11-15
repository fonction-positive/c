//
// Created by 金卓远 on 24-11-3.
//

#include "listeC_simple.h"

#include <stdio.h>


int main() {
    ListeC liste_c=initLC();
    int res=estVideLC(liste_c);
    printf("%d",res);
}
