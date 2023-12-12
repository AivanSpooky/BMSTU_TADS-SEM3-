#include "tree_graphviz.h"

// Функция для создания DOT-кода из дерева
void printTreeAsDot(node_t* root, FILE* file)
{
    if (root == NULL) {
        return;
    }

    if (root->left != NULL) {
        fprintf(file, "%d -> %d;\n", root->data, root->left->data);
        printTreeAsDot(root->left, file);
    }

    if (root->right != NULL) {
        fprintf(file, "%d -> %d;\n", root->data, root->right->data);
        printTreeAsDot(root->right, file);
    }
}

// Функция для создания DOT-файла
void convertTreeToDot(node_t* root)
{
    FILE* file = fopen("tree.dot", "w");
    if (file == NULL) {
        perror("Unable to create file");
        return;
    }

    fprintf(file, "digraph G {\n");
    if (root->left == NULL && root->right == NULL)
        fprintf(file, "%d;\n", root->data);
    else
        printTreeAsDot(root, file);
    fprintf(file, "}\n");

    fclose(file);
}
