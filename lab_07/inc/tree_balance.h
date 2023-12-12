#ifndef TREE_BALANCE_H__

#define TREE_BALANCE_H__

#include "tree_type.h"

// Функция для подсчета узлов в дереве
int countNodes(node_t* root);
// Функция для копирования значений узлов в массив
void storeInorder(node_t* root, int* arr, int* index);

// Вспомогательная функция для создания сбалансированного дерева из отсортированного массива
node_t* sortedArrayToBST(int* arr, int start, int end);

// Функция для балансировки дерева
node_t* balanceBST(node_t* root);

#endif