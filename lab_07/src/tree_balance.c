#include "tree_balance.h"

#include <stdlib.h>
// Функция для подсчета узлов в дереве
int countNodes(node_t* root)
{
    if (root == NULL)
        return 0;

    return 1 + countNodes(root->left) + countNodes(root->right);
}

// Функция для копирования значений узлов в массив
void storeInorder(node_t* root, int* arr, int* index)
{
    if (root == NULL) {
        return;
    }
    storeInorder(root->left, arr, index);
    arr[(*index)++] = root->data;
    storeInorder(root->right, arr, index);
}

// Вспомогательная функция для создания сбалансированного дерева из отсортированного массива
node_t* sortedArrayToBST(int* arr, int start, int end)
{
    if (start > end) {
        return NULL;
    }
    int mid = (start + end) / 2;
    node_t* newNode = (node_t*)malloc(sizeof(node_t));
    newNode->data = arr[mid];
    newNode->left = sortedArrayToBST(arr, start, mid - 1);
    newNode->right = sortedArrayToBST(arr, mid + 1, end);
    return newNode;
}

// Функция для балансировки дерева
node_t* balanceBST(node_t* root)
{
    int n = countNodes(root);
    int* arr = (int*)malloc(n * sizeof(int));
    int index = 0;
    storeInorder(root, arr, &index);
    return sortedArrayToBST(arr, 0, n - 1);
}