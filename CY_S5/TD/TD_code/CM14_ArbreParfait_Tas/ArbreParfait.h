//
// Created by 金卓远 on 24-12-3.
//

#ifndef ARBREPARFAIT_H
#define ARBREPARFAIT_H

#include <stdio.h>
#include <stdlib.h>

typedef int TElment;
typedef struct arbre_parfait {
    int taille;
    int tailleMax;
    TElment *tab;
}ArbreParfait;

int taille(ArbreParfait a);
int tailleMax(ArbreParfait a);
TElment iEmeElts(int i,ArbreParfait a);
TElment donneAP(int nd,ArbreParfait a);
int filsGaucheAP(int nd);
int filsDroitAP(int nd);
int pereAP(int nd);
ArbreParfait allocMemAP(int tailleMax);
void libMemAP(ArbreParfait a);
ArbreParfait initAP(ArbreParfait a);
int estVideAP(ArbreParfait a);
int estPleinAP(ArbreParfait a);
//test le noeud n'est pas existe
int estVideNoeud(int nd,ArbreParfait a);
int estExistNoeud(int nd,ArbreParfait a);
void ParcoursPrefixe(int racine,ArbreParfait a);
void ParcoursInfixe(int racine,ArbreParfait a);
void ParcoursPostfixe(int racine,ArbreParfait a);
void ParcoursLargeur(ArbreParfait a);


int taille(ArbreParfait a) {
    return a.taille;
}

int tailleMax(ArbreParfait a) {
    return a.tailleMax;
}

// Retourne la donnée associée au iéme nœud de l’arbre parfait
// Précondition : si le Iémé nœud existe (càd 0<=i < taille(a) )
TElment iEmeElts(int i,ArbreParfait a) {
    return a.tab[i];
}

// Accès à la donnée d’un nœud donné « nd »
// Précondition : si le nœud « nd » existe (càd nd < taille(a)
TElment donneAP(int nd,ArbreParfait a) {
    return iEmeElts(nd,a);
}

// Retourne le fils gauche d’un nœud « nd » donné s’il existe
int filsGaucheAP(int nd) {
    return 2*nd+1;
}

//return droit
int filsDroitAP(int nd) {
    return 2*nd+2;
}

// Retourne le père d’un nœud « nd » donné s’il existe
// Sauf pour le premier nœud (=racine) de l’arbre
int pereAP(int nd) {
    return (nd-1)/2;
}

ArbreParfait allocMemAP(int tailleMax) {
    ArbreParfait a;
    a.tailleMax=tailleMax;
    a.tab=malloc(tailleMax*sizeof(struct arbre_parfait));
    return a;
}

void libMemAP(ArbreParfait a) {
    free(a.tab);
}

//initiation de arbre parfait
ArbreParfait initAP(ArbreParfait a) {
    a.taille=0;
    return a;
}

int estVideAP(ArbreParfait a) {
    return a.taille==0;
}

int estPleinAP(ArbreParfait a) {
    return a.taille>=a.tailleMax;
}

//test le noeud n'est pas existe
int estVideNoeud(int nd,ArbreParfait a) {
    return nd >= a.taille;
}

//test le noeud est existe
int estExistNoeud(int nd,ArbreParfait a) {
    return nd < a.taille;
}

//parcours prefixe(racine,gauche,droit) 前序遍历（根左右）
void ParcoursPrefixe(int racine,ArbreParfait a) {
    if (estExistNoeud(racine,a)) {
        printf("%d ",donneAP(racine,a));
        ParcoursPrefixe(filsGaucheAP(racine),a);
        ParcoursPrefixe(filsDroitAP(racine),a);
    }
}

//infixe(gauche,racine,droit)
void ParcoursInfixe(int racine,ArbreParfait a) {
    if (estExistNoeud(racine,a)) {
        ParcoursInfixe(filsGaucheAP(racine),a);
        printf("%d ",donneAP(racine,a));
        ParcoursInfixe(filsDroitAP(racine),a);
    }
}

//postfixe(gauche,droit,racine)
void ParcoursPostfixe(int racine,ArbreParfait a) {
    if (estExistNoeud(racine,a)) {
        ParcoursPostfixe(filsGaucheAP(racine),a);
        ParcoursPostfixe(filsDroitAP(racine),a);
        printf("%d ",donneAP(racine,a));
    }
}

//largeur(一行一行遍历）
void ParcoursLargeur(ArbreParfait a) {
    for (int i=0;i<a.taille;i++) {
        printf("%d ",a.tab[i]);
    }
}

#endif //ARBREPARFAIT_H
