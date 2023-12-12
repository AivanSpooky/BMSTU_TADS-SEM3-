#ifndef TREE_GRAPHVIZ_H__

#define TREE_GRAPHVIZ_H__

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "tree_type.h"

void printTreeAsDot(node_t* root, FILE* file);

void convertTreeToDot(node_t* root);

#endif
