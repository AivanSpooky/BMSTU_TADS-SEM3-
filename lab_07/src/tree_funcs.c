#include "tree_funcs.h"

// Функция для создания нового узла
node_t* createNode(int value)
{
    node_t* newNode = (node_t*)malloc(sizeof(node_t));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Функция для освобождения памяти из-под дерева
void freeTree(node_t* root)
{
    if (root == NULL)
        return;

    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

// Функция для включения узла в дерево
node_t* insert(node_t* root, int value)
{
    if (root == NULL)
        return createNode(value);
    if (value < root->data)
        root->left = insert(root->left, value);
    else if (value > root->data)
        root->right = insert(root->right, value);
    return root;
}

// Функции для обхода дерева
void preOrder(node_t* root)
{
    if (root != NULL) {
        printf("%d ", root->data);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void inOrder(node_t* root)
{
    if (root != NULL) {
        inOrder(root->left);
        printf("%d ", root->data);
        inOrder(root->right);
    }
}

void postOrder(node_t* root)
{
    if (root != NULL) {
        postOrder(root->left);
        postOrder(root->right);
        printf("%d ", root->data);
    }
}

// Функция для определения количества узлов дерева на каждом уровне
void countNodesAtEachLevel(node_t* root, int level, int* count)
{
    if (root == NULL)
        return;

    count[level]++;
    countNodesAtEachLevel(root->left, level + 1, count);
    countNodesAtEachLevel(root->right, level + 1, count);
}

// Вывод информации об уровнях и узлах
size_t printNodesLevelsInfo(node_t* root, bool info)
{
    int count[100] = {0};
    size_t sum = 0;
    countNodesAtEachLevel(root, 0, count);
    for (int i = 0; i < 100; i++)
    {
        if (count[i] > 0)
            if (info)
                printf("Уровень %d: %d узлов\n", i, count[i]);
        sum += count[i];
    }
    printf("Дерево занимает %zuБ\n", sum*sizeof(node_t));
    return sum;
}

// Функция для поиска узла в дереве
node_t* search(node_t* root, int value, size_t* comparisons)
{
    if (root == NULL || root->data == value) {
        (*comparisons)++;
        return root;
    }
    if (value < root->data) {
        (*comparisons)++;
        return search(root->left, value, comparisons);
    }
    (*comparisons)++;
    return search(root->right, value, comparisons);
}

node_t* findMinNode(node_t* node)
{
    node_t* current = node;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}

node_t* deleteNode(node_t* root, int value)
{
    if (root == NULL) {
        return root;
    }

    if (value < root->data) {
        root->left = deleteNode(root->left, value);
    } else if (value > root->data) {
        root->right = deleteNode(root->right, value);
    } else {
        if (root->left == NULL) {
            node_t* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            node_t* temp = root->left;
            free(root);
            return temp;
        }

        node_t* temp = findMinNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}
