#ifndef GRAPH_TYPE_H__

#define GRAPH_TYPE_H__

#define MAX_VERTICES 100

typedef struct {
    int* vertices;
    int numVertices;
    int** adjacencyMatrix;
} graph_t;

#endif