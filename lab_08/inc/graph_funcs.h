#ifndef GRAPH_FUNCS_H__

#define GRAPH_FUNCS_H__

#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include "graph_type.h"

graph_t* initializeGraph(int size);

void addEdge(graph_t* g, int v1, int v2, int weight, int* written);

int countVerticesFromFile(const char* filename);

void readGraphFromFile(graph_t* g, const char* filename);

void findMaxDistances(graph_t* g, bool info_output);

#endif