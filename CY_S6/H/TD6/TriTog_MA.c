#include <stdio.h>
#include <stdlib.h>
#include "../TD4/queue.h"

typedef struct {
    int nbSom;
    int **mat;
} MatriceAdj;

MatriceAdj creatMatriceAdj(int n);
int nbsom(MatriceAdj m);

MatriceAdj creatMatriceAdj(int n) {
    MatriceAdj m;
    m.nbSom = n;
    m.mat = (int**)malloc(n * sizeof(int*));
    if (m.mat == NULL) {
        printf("Memory allocation failed");
        exit(1);
    }
    for (int i = 0; i < n; i++) {
        m.mat[i] = (int*)malloc(n * sizeof(int));
        if (m.mat[i] == NULL) {
            printf("Memory allocation failed for row");
            exit(1);
        }
        for (int j = 0; j < n; j++) {
            m.mat[i][j] = 0; // 初始化为 0
        }
    }
    return m;
}

int nbsom(MatriceAdj m) {
    return m.nbSom;
}

Queue TriTog(MatriceAdj m,int * ciruct){
    int n=nbsom(m);
    int* D=(int*)malloc(n*sizeof(int));
    Queue f,M;
    f=initf();
    M=initf();
    int t,s,de;
    for(s=0;s<n;s++){
        de=0;
        for(t=0;t<n;t++){
            if(m.mat[t][s]){
                de++;
            }
        }
        D[s]=de;
        if(de==0){
            emfiler(&M,s);
        }
    }
    int cnt=0,u;
    while (!estVide(&M)){
        t=defiler(&M);
        emfiler(&f,t);
        for(u=0;u<n;u++){
            if(m.mat[t][u]){
                D[u]--;
                if(D[u]==0){
                    emfiler(&M,u);
                }
            }
        }
        cnt++;
    }
    if(cnt<n){
        (*ciruct)=1;
    }
    return f;
}

void testTriTog()
{
    int n = 4;
    int circuit = 0;
    MatriceAdj G = creatMatriceAdj(n);

    // 创建一个无环图
    G.mat[0][1] = 1;
    G.mat[1][2] = 1;
    G.mat[2][3] = 1;
    G.mat[3][0] = 1;

    Queue result = TriTog(G, &circuit);

    if (circuit)
    {
        printf("The graph has a cycle.\n");
    }
    else
    {
        printf("Topological Order: ");
        while (!estVide(&result))
        {
            printf("%d ", defiler(&result));
        }
        printf("\n");
    }
}

int main()
{
    testTriTog();
    return 0;
}
