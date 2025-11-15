#include <stdio.h>
#include <stdlib.h>
#include "../TD4/queue.h"

typedef struct{
    int nbSom;
    int nbArcs;
    int *FS;
    int *APS;
}FileSucce;

// 创建 FileSucce 结构体并分配内存
FileSucce createFileSucce(int nbsom, int nbarc) {
    FileSucce fs;
    fs.nbSom = nbsom;
    fs.nbArcs = nbarc;

    // 分配内存
    fs.APS = (int*)malloc((nbsom + 1) * sizeof(int));
    if (fs.APS == NULL) {
        printf("Memory allocation failed for APS.\n");
        exit(1);  // 内存分配失败，退出程序
    }

    fs.FS = (int*)malloc(nbarc * sizeof(int));
    if (fs.FS == NULL) {
        printf("Memory allocation failed for FS.\n");
        free(fs.APS);  // 释放之前分配的内存
        exit(1);
    }

    return fs;
}

Queue TriTog(FileSucce fs,int * ciruct){
    int n=fs.nbSom;
    int* D=(int*)malloc(n*sizeof(int));
    Queue f,M;
    f=initf();
    M=initf();
    int s,nbsucc,j,iAps,t;
    for(s=0;s<n;s++){
        nbsucc=fs.APS[s+1]-fs.APS[s];
        iAps=fs.APS[s];
        for(j=0;j<nbsucc;j++){
            t=fs.FS[j+iAps];
            D[t]++;
        }
    }
    for(s=0;s<n;s++){
        if(D[s]==0){
            emfiler(&M,s);
        }
    }
    int cnt=0,u;
    while (!estVide(&M)){
        t=defiler(&M);
        emfiler(&f,t);
        nbsucc=fs.APS[t+1]-fs.APS[t];
        iAps=fs.APS[t];
        for(j=0;j<nbsucc;j++){
            u=fs.FS[j+iAps];
            D[u]--;
            if(D[u]==0){
                emfiler(&M,u);
            }
            
        }
        cnt++;
    }
    if(cnt<n){
        (*ciruct)=1;
    }
    return f;
}
void testTriTog_FileSucce()
{
    int n = 4;
    int circuit = 0;
    FileSucce fs = createFileSucce(n, 4);

    // 设置 FS 和 APS
    fs.APS[0] = 0;
    fs.APS[1] = 1;
    fs.APS[2] = 2;
    fs.APS[3] = 3;
    fs.APS[4] = 4;

    fs.FS[0] = 1;
    fs.FS[1] = 2;
    fs.FS[2] = 3;
    fs.FS[3] = 0;
    

    Queue result = TriTog(fs, &circuit);

    if (circuit)
    {
        printf("The FileSucce graph has a cycle.\n");
    }
    else
    {
        printf("FileSucce Topological Order: ");
        while (!estVide(&result))
        {
            printf("%d ", defiler(&result));
        }
        printf("\n");
    }

    free(fs.FS);
    free(fs.APS);
}

int main()
{
    testTriTog_FileSucce();
    return 0;
}
