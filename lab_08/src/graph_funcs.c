#include "graph_funcs.h"
#include <limits.h>
#include <stdlib.h>

graph_t* initializeGraph(int size)
{
    graph_t* g = (graph_t*)malloc(sizeof(graph_t));
    g->numVertices = size;
    g->vertices = (int*)malloc(size * sizeof(int));
    g->adjacencyMatrix = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        g->adjacencyMatrix[i] = (int*)malloc(size * sizeof(int));
        g->vertices[i] = 0;
        for (int j = 0; j < size; j++) {
            g->adjacencyMatrix[i][j] = 0;
        }
    }
    return g;
}

int findIndex(graph_t* g, int v)
{
    int ind = -1;
    for (int i = 0; i < g->numVertices; i++)
        if (g->vertices[i] == v) return i;
    return ind;
}

void addEdge(graph_t* g, int v1, int v2, int weight, int* written)
{
    int ind1, ind2; 
    ind1 = findIndex(g, v1);
    ind2 = findIndex(g, v2);
    if (ind1 == -1)
    {
        g->vertices[*written] = v1;
        (*written)++;
    }
    if (ind2== -1)
    {
        g->vertices[*written] = v2;
        (*written)++;
    }
    g->adjacencyMatrix[findIndex(g, v1)][findIndex(g, v2)] = weight;
    g->adjacencyMatrix[findIndex(g, v2)][findIndex(g, v1)] = weight;
}

int countVerticesFromFile(const char* filename)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Ошибка открытия файла\n");
        return -1; // Возвращаем -1 в случае ошибки
    }

    int numVertices = 0;
    char line[256];
    graph_t* exp = initializeGraph(100);
    while (fgets(line, sizeof(line), file)) {
        if (line[0] >= '0' && line[0] <= '9') {
            int vertex1, vertex2, weight;
            if (sscanf(line, "%d %d %d", &vertex1, &vertex2, &weight) != 3)
            {
                printf("\nФайл имеет некорректные данные!\n");
                exit(0);
            }
            int ind1, ind2;
            ind1 = findIndex(exp, vertex1);
            ind2 = findIndex(exp, vertex2);
            if (ind1 == -1)
            {
                exp->vertices[numVertices] = vertex1;
                numVertices++;
            }
            if (ind2 == -1)
            {
                exp->vertices[numVertices] = vertex2;
                numVertices++;
            }
        }
    }

    fclose(file);
    //printf("vertices = %d\n", numVertices);
    return numVertices;
}


void readGraphFromFile(graph_t* g, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Unable to open file");
        return;
    }

    int v1, v2, weight;
    int written = 0;
    while (fscanf(file, "%d %d %d", &v1, &v2, &weight) == 3) {
        if (v1 == 0 || v2 == 0)
        {
            printf("\nГраф задан неправильно (номер вершины должен быть отличен от нуля)\n");
            exit(0);
        }
        if (weight < 0)
        {
            printf("\nГраф задан неправильно (расстояние должно быть положительным!)\n");
            exit(0);
        }
        if (findIndex(g, v1) != -1 && findIndex(g, v2) != -1 && g->adjacencyMatrix[findIndex(g, v1)][findIndex(g, v2)] != 0)
        {
            printf("\nВ графе не может быть 2 и более расстояний между одной парой вершин!\n");
            exit(0);
        }
        addEdge(g, v1, v2, weight, &written);
    }
    if (!feof(file))
    {
        printf("\nФайл имеет некорректные данные!\n");
        exit(0);
    }

    fclose(file);
    printf("\nГраф успешно прочитан из файла!\n");
}

void printGraph(graph_t* g)
{
    printf("\nGRAPH:\n");
    for (int i = 0; i < g->numVertices; i++) {
        for (int j = 0; j < g->numVertices; j++) {
            printf("%d ", g->adjacencyMatrix[i][j]);
        }
        printf("\n");
    }
}

void printDist(graph_t* g, int dist[MAX_VERTICES][MAX_VERTICES])
{
    printf("\n");
    printf("  |");
    for(int i = 0; i < g->numVertices; i++)
        printf("%d ", g->vertices[i]);
    printf("\n---------------------------------\n");
    for(int i = 0; i < g->numVertices; i++)
    {
        printf("%d |", g->vertices[i]);
        for(int j = 0; j < g->numVertices; j++)
            printf("%d ", dist[i][j]);
        printf("\n");
    }
}

// int findMaxPath(graph_t* g, int start, int end, int dist[MAX_VERTICES][MAX_VERTICES], int visited[MAX_VERTICES], bool info, bool first_v) {
//     if (start == end) {
//         return 0;
//     }
//     visited[start] = 1;
//     int cnt = 0;
//     int prev = 0;
//     for (int i = 0; i < g->numVertices; i++)
//     {
//         if (dist[end][i] != 0)
//         {
//             prev = i;
//             cnt++;
//         }
//     }
//     if (cnt == 1 && visited[prev] == 1)
//     {
//         if (info) printf("%d %dBACK\n", g->vertices[start], g->vertices[end]);
//         return (first_v) ? dist[start][end] : -10;
//     }
//     int first_ver = false;
//     int maxPath = -1; // Изменяем начальное значение на -1
//     visited[start] = 1;
//     for (int i = 0; i < g->numVertices; i++) {
//         if (start != i && dist[start][i] != 0 && !visited[i]) {
//             if (info) printf("%d %d\n", g->vertices[start], g->vertices[end]);
//             if (info) printf("path = %d\n", dist[start][i]);
//             int adder = findMaxPath(g, i, end, dist, visited, info, first_ver);
//             int path = dist[start][i];
//             if (adder == -10)
//             {
//                 path += dist[i][end];
//             }
//             else
//                 path += adder;
//             if (path > maxPath) {
//                 maxPath = path;
//             }
//         }
//     }
//     visited[start] = 0;
//     return maxPath;
// }

int findMaxPath(graph_t* g, int start, int end, int dist[MAX_VERTICES][MAX_VERTICES], int visited[MAX_VERTICES], bool info, bool first_v) {
    if (start == end) {
        return 0;
    }
    (void) first_v;
    visited[start] = 1;
    int maxPath = -1;
    for (int i = 0; i < g->numVertices; i++) {
        if (dist[start][i] != 0 && !visited[i]) {
            if (info) printf("%d %d\n", g->vertices[start], g->vertices[i]);
            if (info) printf("path = %d\n", dist[start][i]);
            int adder = findMaxPath(g, i, end, dist, visited, info, false);
            if (adder != -1) {
                int path = dist[start][i] + adder;
                if (path > maxPath) {
                    maxPath = path;
                }
            }
        }
    }
    visited[start] = 0;
    return (maxPath == -1) ? -1 : maxPath;
}
void findMaxDistances(graph_t* g, bool info_output) {
    int dist[MAX_VERTICES][MAX_VERTICES];
    int finaldist[MAX_VERTICES][MAX_VERTICES];
    int i, j;

    // Инициализируем матрицу расстояний
    for (i = 0; i < g->numVertices; i++) {
        for (j = 0; j < g->numVertices; j++) {
            dist[i][j] = g->adjacencyMatrix[i][j];
            finaldist[i][j] = g->adjacencyMatrix[i][j];
        }
    }

    // Проверка на наличие пути между вершинами
    //printDist(g, finaldist);
    bool info = false;
    for (i = 0; i < g->numVertices; i++) {
        for (j = i + 1; j < g->numVertices; j++) {
            if (i != j) {
                int visited[MAX_VERTICES];
                for (int k = 0; k < MAX_VERTICES; k++)
                    visited[k] = 0;
                int maxPath = findMaxPath(g, i, j, dist, visited, info, true);
                if (maxPath == -1) {
                    finaldist[i][j] = 0;
                    finaldist[j][i] = 0;
                } else {
                    finaldist[i][j] = maxPath;
                    finaldist[j][i] = maxPath;
                }
            }
        }
    }
    printDist(g, finaldist);

    for (i = 0; i < g->numVertices; i++) {
        for (j = i; j < g->numVertices; j++)
        {
            if (i != j && info_output)
                printf("Максимальное расстояние между вершинами %d и %d: %d\n", g->vertices[i], g->vertices[j], finaldist[i][j]);
        }
    }
}
