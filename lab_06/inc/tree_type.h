#ifndef TREE_TYPES_H__

#define TREE_TYPES_H__

#include <stdio.h>

#include "err_codes.h"

// Структура для узла дерева
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} node_t;

#endif
