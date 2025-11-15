//
// Created by 金卓远 on 24-10-15.
//

#include <stdio.h>
#include <stdlib.h>

//circulaire
struct Noeud {
    int element;
    struct Noeud* suivant;
};

struct Noeud* ajouter(struct Noeud* dernier,int element) {
    struct Noeud* nouveau=(struct Noeud*)malloc(sizeof(struct Noeud));
    nouveau->element=element;
    if (dernier==NULL) {
        nouveau->suivant=nouveau;
        return nouveau;
    }
    nouveau->suivant=dernier->suivant;
    dernier->suivant=nouveau;
    return nouveau;
}

int compterOccurrences(struct Noeud* tete, int valeur) {
    if(tete==NULL) return 0;
    struct Noeud* courant =tete;
    int compteur=0;
    do {
        if(courant->element==valeur) {
            compteur++;
        }
        courant=courant->suivant;
    }while (courant!=tete);

    return compteur;
}

int main() {
    struct Noeud* liste=NULL;

    liste=ajouter(liste,10);
    liste=ajouter(liste,20);
    liste=ajouter(liste,10);

    int valeur=10;
    int resultat=compterOccurrences(liste->suivant,valeur);
    printf("l'element %d apparaite %d fois",valeur,resultat);

}