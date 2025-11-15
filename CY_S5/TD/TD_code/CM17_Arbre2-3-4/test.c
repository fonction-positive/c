#include <stdio.h>
#include <stdlib.h>

#define NBMAXDONNEES 3
#define NBMAXFILS 4

typedef int TElement;

typedef struct noeud {
    int nbElements;                  // 当前节点的元素数
    int nbFils;                      // 当前节点的子节点数
    TElement donnee[NBMAXDONNEES];   // 存储最多3个数据
    struct noeud* fils[NBMAXFILS];   // 存储最多4个子树
    int estFeuille;                  // 是否是叶子节点
}*Arbre234;

// 广度优先遍历
void breadthFirstTraversal(Arbre234 root) {
    if (root == NULL) {
        return;
    }

    // 使用队列进行广度优先遍历
    Arbre234 queue[100];
    int front = 0, rear = 0;

    queue[rear++] = root;

    while (front < rear) {
        Arbre234 node = queue[front++];

        // 打印当前节点的数据
        for (int i = 0; i < node->nbElements; i++) {
            printf("%d ", node->donnee[i]);
        }
        printf("| ");

        // 将孩子节点加入队列
        for (int i = 0; i < node->nbFils; i++) {
            if (node->fils[i] != NULL) {
                queue[rear++] = node->fils[i];
            }
        }
    }
    printf("\n");
}

// 搜索指定元素的节点地址
Arbre234 search(Arbre234 root, TElement key) {
    if (root == NULL) {
        return NULL;
    }

    // 遍历当前节点的所有数据
    for (int i = 0; i < root->nbElements; i++) {
        if (root->donnee[i] == key) {
            return root; // 找到关键字，返回当前节点
        }
    }

    // 如果不是叶子节点，递归查找子节点
    if (!root->estFeuille) {
        for (int i = 0; i < root->nbFils; i++) {
            Arbre234 result = search(root->fils[i], key);
            if (result != NULL) {
                return result;
            }
        }
    }

    return NULL; // 未找到
}

int main() {
    // 手动构建一颗简单的 2-3-4 树
    Arbre234 root = (Arbre234)malloc(sizeof(struct noeud));
    root->nbElements = 2;
    root->donnee[0] = 10;
    root->donnee[1] = 20;
    root->nbFils = 3;
    root->estFeuille = 0;

    // 创建子节点
    Arbre234 child1 = (Arbre234)malloc(sizeof(struct noeud));
    child1->nbElements = 1;
    child1->donnee[0] = 5;
    child1->nbFils = 0;
    child1->estFeuille = 1;

    Arbre234 child2 = (Arbre234)malloc(sizeof(struct noeud));
    child2->nbElements = 1;
    child2->donnee[0] = 15;
    child2->nbFils = 0;
    child2->estFeuille = 1;

    Arbre234 child3 = (Arbre234)malloc(sizeof(struct noeud));
    child3->nbElements = 1;
    child3->donnee[0] = 25;
    child3->nbFils = 0;
    child3->estFeuille = 1;

    // 将子节点连接到根节点
    root->fils[0] = child1;
    root->fils[1] = child2;
    root->fils[2] = child3;

    // 测试广度优先遍历
    printf("Breadth First Traversal:\n");
    breadthFirstTraversal(root);

    // 测试搜索操作
    TElement searchKey = 15;
    Arbre234 result = search(root, searchKey);
    if (result != NULL) {
        printf("Key %d found at node address: %p\n", searchKey, result);
        printf("Node elements: ");
        for (int i = 0; i < result->nbElements; i++) {
            printf("%d ", result->donnee[i]);
        }
        printf("\n");
    } else {
        printf("Key %d not found in the tree.\n", searchKey);
    }

    // 释放内存
    free(child1);
    free(child2);
    free(child3);
    free(root);

    return 0;
}