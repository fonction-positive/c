#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int nbSom;
    int** mat;
}MatriceAdj;

MatriceAdj creatMatriceAdj(int n);
int nbsom(MatriceAdj m);
int** initMat(int n,int** mat);
MatriceAdj carre(MatriceAdj m);

MatriceAdj creatMatriceAdj(int n){
    MatriceAdj m;
    m.nbSom=n;
    int i=0;
    m.mat=(int**)malloc(n*sizeof(int*));
    if(m.mat==NULL){
        printf("Memory allocation failed");
        exit(1);
    }
    for(i=0;i<n;i++){
        m.mat[i]=(int*)malloc(n*sizeof(int));
        if(m.mat[i]==NULL){
            printf("Memory allocation failed for ligne");
            exit(1);
        }
    }
    return m;
}

int nbsom(MatriceAdj m){
    return m.nbSom;
}

int** initMat(int n,int** mat){
    int s=0,t=0;
    for(s=0;s<n;s++){
        for(t=0;t<n;t++){
            mat[s][t]=0;
        }
    }
    return mat;
}

MatriceAdj carre(MatriceAdj g){
    int n=nbsom(g);
    MatriceAdj g2=creatMatriceAdj(n);
    g2.mat=initMat(n,g2.mat);
    int u,s,t;
    for(s=0;s<n;s++){
        for(t=0;t<n;t++){
            u=0;
            while(u<n && g.mat[s][u]*g.mat[u][t]==0){
                u++;
            }
            if(u<n){
                g2.mat[s][t]=1;
            }
        }
    }
    return g2;
}

void printMatrix(int n, int** mat) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int n = 3;
    MatriceAdj g = creatMatriceAdj(n);
    g.mat = initMat(n, g.mat);
    
    // 手动设置邻接矩阵
    g.mat[0][1] = 1;
    g.mat[1][2] = 1;
    g.mat[2][0] = 1;
    
    printf("Original Matrix:\n");
    printMatrix(n, g.mat);
    
    MatriceAdj g2 = carre(g);
    
    printf("Squared Matrix:\n");
    printMatrix(n, g2.mat);
    
    // 释放内存
    for (int i = 0; i < n; i++) {
        free(g.mat[i]);
        free(g2.mat[i]);
    }
    free(g.mat);
    free(g2.mat);
    
    return 0;
}
