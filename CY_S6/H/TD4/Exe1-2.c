#include <stdio.h>
#include <stdlib.h>

typedef struct cellule{
    int SomSucce;
    struct cellule* suivant;
}*Liste;

typedef struct {
    int nbSom;
    Liste* tab;
}ListeAdj;

ListeAdj createListeA(int n);
Liste inserTete(Liste l,int s);
Liste init();
int nbsom(ListeAdj la);
ListeAdj carre(ListeAdj g);

ListeAdj createListeA(int n){
    ListeAdj la;
    int i=0;
    la.nbSom=n;
    la.tab=(Liste*)malloc(n*sizeof(Liste));
    if(la.tab==NULL){
        printf("Memory allocation faild");
        exit(1);
    }
    for(i=0;i<n;i++){
        la.tab[i]= NULL;
    }
    return la;
}

Liste inserTete(Liste l,int s){
    Liste cel=(Liste)malloc(sizeof(Liste));
    cel->SomSucce=s;
    cel->suivant=l;
    l=cel;
    return l;
}

Liste init(){
    return NULL;
}

int nbsom(ListeAdj la){
    return la.nbSom;
}

ListeAdj carre(ListeAdj g){
    int n=nbsom(g);
    ListeAdj g2=createListeA(n);
    int s,u;
    Liste ll,l;
    for(s=0;s<n;s++){
        ll=g.tab[s];
        l=NULL;
        while (ll!=NULL){
            u=ll->SomSucce;
            if(g.tab[u]!=NULL){
                Liste lu=g.tab[u];
                while (lu!=NULL){
                    l=inserTete(l,lu->SomSucce);
                    lu=lu->suivant;
                }
                
            }
            ll=ll->suivant;
        }
        g2.tab[s]=l;
    }
    return g2;
}

void printListeAdj(ListeAdj la) {
    for (int i = 0; i < la.nbSom; i++) {
        printf("%d: ", i);
        Liste temp = la.tab[i];
        while (temp != NULL) {
            printf("%d -> ", temp->SomSucce);
            temp = temp->suivant;
        }
        printf("NULL\n");
    }
}

int main() {
    int n = 3;
    ListeAdj g = createListeA(n);
    
    // 手动设置邻接表
    g.tab[0] = inserTete(g.tab[0], 1);
    g.tab[1] = inserTete(g.tab[1], 2);
    g.tab[2] = inserTete(g.tab[2], 0);
    
    printf("Original Adjacency List:\n");
    printListeAdj(g);
    
    ListeAdj g2 = carre(g);
    
    printf("Squared Adjacency List:\n");
    printListeAdj(g2);
    
    // 释放内存
    for (int i = 0; i < n; i++) {
        Liste temp;
        while (g.tab[i] != NULL) {
            temp = g.tab[i];
            g.tab[i] = g.tab[i]->suivant;
            free(temp);
        }
        while (g2.tab[i] != NULL) {
            temp = g2.tab[i];
            g2.tab[i] = g2.tab[i]->suivant;
            free(temp);
        }
    }
    free(g.tab);
    free(g2.tab);
    
    return 0;
}
