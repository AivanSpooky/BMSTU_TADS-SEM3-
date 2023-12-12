#include "graph_graphviz.h"

void printGraphAsDot(graph_t* g)
{
    FILE* file = fopen("graph.dot", "w");
    if (file == NULL)
    {
        printf("\nНевозможно создать DOT файл!\n");
        return;
    }
    fprintf(file, "graph G {\n");
    for (int i = 0; i < g->numVertices; i++) {
        int cnt = 0;
        for (int j = i + 1; j < g->numVertices; j++) {
            if (g->adjacencyMatrix[i][j] != 0) {
                fprintf(file, "%d -- %d [label=%d];\n", g->vertices[i], g->vertices[j], g->adjacencyMatrix[i][j]);
                cnt++;
            }
        }
        if (cnt == 0)
            fprintf(file, "%d;\n", g->vertices[i]);
    }
    fprintf(file, "}\n");

    fclose(file);
}
