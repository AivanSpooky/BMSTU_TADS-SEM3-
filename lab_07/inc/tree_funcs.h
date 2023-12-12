#ifndef TREE_FUNCS_H__

#define TREE_FUNCS_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tree_type.h"
#include "tree_graphviz.h"

node_t* createNode(int value);

void freeTree(node_t* root);

node_t* insert(node_t* root, int value);

void preOrder(node_t* root);

void inOrder(node_t* root);

void postOrder(node_t* root);

void countNodesAtEachLevel(node_t* root, int level, int* count);

size_t printNodesLevelsInfo(node_t* root, bool info);

node_t* search(node_t* root, int value, size_t* comparisons);

node_t* findMinNode(node_t* node);

node_t* deleteNode(node_t* root, int value);

#endif
