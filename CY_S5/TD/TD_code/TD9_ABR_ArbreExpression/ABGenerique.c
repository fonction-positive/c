#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// 定义树节点结构体
typedef struct Node {
    char op;
    double value;
    struct Node *left;
    struct Node *right;
} *ArbreE;  // 使用指针类型

// 创建节点：如果是操作数，op为'\0'
ArbreE createNode(char op, double value) {
    ArbreE node = (ArbreE)malloc(sizeof(struct Node));  // 使用ArbreE指针类型
    node->op = op;
    node->value = value;
    node->left = node->right = NULL;
    return node;
}

// 将完全括号化表达式转换为二叉树
ArbreE parseExpression(const char **exp) {
    if (**exp == '(') {
        (*exp)++;  // 跳过 '('
        ArbreE left = parseExpression(exp);  // 左子树
        char op = **exp;                    // 操作符
        (*exp)++;
        ArbreE right = parseExpression(exp); // 右子树
        (*exp)++;  // 跳过 ')'
        ArbreE node = createNode(op, 0);
        node->left = left;
        node->right = right;
        return node;
    } else {  // 操作数
        double value = strtod(*exp, (char**)exp);
        return createNode('\0', value);
    }
}

// 后序遍历计算表达式值
double evaluate(ArbreE root) {
    if (root->op == '\0')  // 如果是操作数节点
        return root->value;

    double left = evaluate(root->left);
    double right = evaluate(root->right);

    switch (root->op) {
        case '+': return left + right;
        case '-': return left - right;
        case '*': return left * right;
        case '/': return left / right;
        default:
            printf("Erreur de symbole dans l’expression！");
            exit(1);

    }
}

// 计算运算符出现的次数
void countOperators(ArbreE root, int *opCount) {
    if (root == NULL) return;
    if (root->op != '\0') {  // 如果是运算符节点
        // 使用运算符映射到索引
        switch (root->op) {
            case '+': opCount[0]++; break;
            case '-': opCount[1]++; break;
            case '*': opCount[2]++; break;
            case '/': opCount[3]++; break;
            default: break;
        }
    }
    countOperators(root->left, opCount);   // 左子树
    countOperators(root->right, opCount);  // 右子树
}

// 释放树内存
void freeTree(ArbreE root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    const char *exp = "((3.3+(16*2.22))-(4.06*(9.9-3.5)))";
    ArbreE root = parseExpression(&exp);
    double result = evaluate(root);
    printf("结果: %lf\n", result);


    // 计算运算符的出现次数
    int opCount[4] = {0};  // 对应 '+', '-', '*', '/'
    countOperators(root, opCount);
    printf("运算符出现次数：\n");
    printf("+ : %d\n", opCount[0]);
    printf("- : %d\n", opCount[1]);
    printf("* : %d\n", opCount[2]);
    printf("/ : %d\n", opCount[3]);

    freeTree(root);
    return 0;
}