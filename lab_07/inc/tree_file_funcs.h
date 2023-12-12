#ifndef TREE_FILE_FUNCS_H__

#define TREE_FILE_FUNCS_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "tree_type.h"
#include "tree_funcs.h"

#define MAX_FILE_LEN 1000

bool file_exists(char *filename);

node_t* readTreeFromFile(char *filename);

void addTreeNodeToFile(char *filename, node_t* root, int newNum);

void printTree(node_t* root, int space);

#endif
