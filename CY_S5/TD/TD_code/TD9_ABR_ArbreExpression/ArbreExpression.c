#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef union {
    char operateur;
    double operande;
} DNeoud;

typedef enum { OPERATEUR, OPERANDE } NNeoud;

typedef struct {
    NNeoud nneoud;
    DNeoud dneoud;
} TElement;

typedef struct neoud {
    TElement donnee;
    struct neoud *filsG;
    struct neoud *filsD;
} ArbreExp;


// 创建一个操作符节点
ArbreExp *creerNoeudOperateur(char operateur);
// 创建一个操作数节点
ArbreExp *creerNoeudOperande(double operande);
ArbreExp *construireArbre(const char **exp);
// 打印表达树（中序遍历）
void afficherArbre(ArbreExp *racine);
// 计算表达树的结果
double calculerExpression(ArbreExp *racine);
void libererArbre(ArbreExp *racine);
// 统计操作符的出现次数
void compterSymbole(ArbreExp *racine, int *compteurs);



// 创建一个操作符节点
ArbreExp *creerNoeudOperateur(char operateur) {
    ArbreExp *noeud = (ArbreExp *) malloc(sizeof(ArbreExp));
    noeud->donnee.nneoud = OPERATEUR;
    noeud->donnee.dneoud.operateur = operateur;
    noeud->filsG = noeud->filsD = NULL;
    return noeud;
}

// 创建一个操作数节点
ArbreExp *creerNoeudOperande(double operande) {
    ArbreExp *noeud = (ArbreExp *) malloc(sizeof(ArbreExp));
    noeud->donnee.nneoud = OPERANDE;
    noeud->donnee.dneoud.operande = operande;
    noeud->filsG = noeud->filsD = NULL;
    return noeud;
}

// 根据完全括号化表达式递归构建表达树
ArbreExp *construireArbre(const char **exp) {
    if (**exp == '(') {
        // 左括号，表示一个操作符节点
        (*exp)++; // 跳过 '('
        ArbreExp *filsG = construireArbre(exp); // 构建左子树
        char operateur = **exp; // 获取操作符
        (*exp)++; // 跳过操作符
        ArbreExp *filsD = construireArbre(exp); // 构建右子树
        (*exp)++; // 跳过 ')'

        ArbreExp *noeud = creerNoeudOperateur(operateur);
        noeud->filsG = filsG;
        noeud->filsD = filsD;
        return noeud;
    } else {
        // 操作数
        char *fin;
        //(strtod)Extraire le nombre flottant au début d’une chaîne de caractères
        double operande = strtod(*exp, &fin); // 转换为双精度浮点数
        *exp = fin; // 更新指针
        return creerNoeudOperande(operande);
    }
}

// 打印表达树（中序遍历）
void afficherArbre(ArbreExp *racine) {
    if (racine == NULL) return;

    if (racine->donnee.nneoud == OPERATEUR) {
        printf("(");
        afficherArbre(racine->filsG);
        printf(" %c ", racine->donnee.dneoud.operateur);
        afficherArbre(racine->filsD);
        printf(")");
    } else if (racine->donnee.nneoud == OPERANDE) {
        printf("%.2f", racine->donnee.dneoud.operande);
    }
}

// 计算表达树的结果
double calculerExpression(ArbreExp *racine) {
    if (racine == NULL) {
        printf("Erreur : l'arbre est vide !\n");
        exit(EXIT_FAILURE);
    }

    if (racine->donnee.nneoud == OPERANDE) {
        // 如果是操作数节点，直接返回其值
        return racine->donnee.dneoud.operande;
    }

    // 递归计算左右子树的值
    double gauche = calculerExpression(racine->filsG);
    double droite = calculerExpression(racine->filsD);

    // 根据操作符计算当前节点的值
    switch (racine->donnee.dneoud.operateur) {
        case '+':
            return gauche + droite;
        case '-':
            return gauche - droite;
        case '*':
            return gauche * droite;
        case '/':
            if (droite == 0) {
                printf("Erreur : division par zéro !\n");
                exit(1);
            }
            return gauche / droite;
        default:
            printf("Erreur : opérateur inconnu '%c' !\n", racine->donnee.dneoud.operateur);
            exit(1);
    }
}

// 统计操作符的出现次数
void compterSymbole(ArbreExp *racine, int *compteurs) {
    if (racine == NULL) return;

    if (racine->donnee.nneoud == OPERATEUR) {
        switch (racine->donnee.dneoud.operateur) {
            case '+':
                compteurs[0]++;
                break;
            case '-':
                compteurs[1]++;
                break;
            case '*':
                compteurs[2]++;
                break;
            case '/':
                compteurs[3]++;
                break;
            default:
                printf("Erreur : opérateur inconnu '%c' !\n", racine->donnee.dneoud.operateur);
                exit(1);
        }
    }

    // 递归统计左右子树的操作符
    compterSymbole(racine->filsG, compteurs);
    compterSymbole(racine->filsD, compteurs);
}


// 释放表达树的内存
void libererArbre(ArbreExp *racine) {
    if (racine == NULL) return;
    libererArbre(racine->filsG);
    libererArbre(racine->filsD);
    free(racine);
}



int main() {
    const char *exp = "((3.3+(16*2.22))-(4.06*(9.9-3.5)))";
    ArbreExp *racine = construireArbre(&exp);

    printf("表达式树（中序表示）：\n");
    afficherArbre(racine);
    printf("\n");

    double res = calculerExpression(racine);
    printf("res = %.2f\n", res);

    // 统计操作符的出现次数
    int compteurs[4] = {0};  // 0: '+', 1: '-', 2: '*', 3: '/'
    compterSymbole(racine, compteurs);

    printf("操作符出现的次数：\n");
    printf("+: %d\n", compteurs[0]);
    printf("-: %d\n", compteurs[1]);
    printf("*: %d\n", compteurs[2]);
    printf("/: %d\n", compteurs[3]);

    libererArbre(racine);
    return 0;
}
