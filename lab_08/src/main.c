#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "graph_comparison.h"
#include "graph_type.h"
#include "graph_graphviz.h"
#include "graph_funcs.h"
#define MAX_FILE_LEN 100

int main()
{
    char tmp_buf[MAX_FILE_LEN];
    graph_t* g = NULL;
    FILE *f = fopen("input.txt", "r");
    if (f == NULL)
    {
        printf("Файла input.txt не существует!");
        goto end_p;
    }
    g = initializeGraph(countVerticesFromFile("input.txt"));
    
    printf("Программа работает с типом данных <граф>. \
    Программа умеет считывать граф из файла <input.txt> \
    Программа выводит полученный из файла граф с помощью утилиты graphviz \
    Программа находит в графе максимальное ррасстояние между всеми парами вершин с помощью алгоритма Флойда-Уоршалла\
    Номера вершин и расстояния между ними - целые числа\
    Выберите один из следующих пунтов меню:\n\n");
    int choice;
    do {
        printf("\nМеню:\n\t1 - считать граф из файла\n");
        printf("\t2 - вывести граф в graphviz\n");
        printf("\t3 - найти максимальное расстояние между всеми парами вершин\n");
        printf("\t0 - выход\nВведите ваш выбор: ");
        if (scanf("%d", &choice) != 1)
        {
            printf("\nПожалуйста, введите целое число!\n");
            fgets(tmp_buf, MAX_FILE_LEN, stdin);
            continue;
        }

        switch (choice)
        {
            case 1:
                g = NULL;
                g = initializeGraph(countVerticesFromFile("input.txt"));
                readGraphFromFile(g, "input.txt");
                if (g == NULL)
                    goto end_p;
                break;
            case 2:
                if (g->vertices[0] != 0)
                {
                    printGraphAsDot(g);
                    system("dot -Tpng graph.dot -o graph.png");
                    system("xdg-open graph.png");
                }
                else
                    printf("\nГраф пуст!\n");
                break;
            case 3:
                if (g->vertices[0] != 0)
                {
                    size_t tests = 100;
                    clock_t start, end;
                    double times[tests];
                    for (size_t i = 0; i < tests; i++)
                    {
                        bool info_output = (i + 1 == tests) ? true : false;
                        start = clock();
                        findMaxDistances(g, info_output);
                        end = clock();
                        times[i] = ((double)(end - start));
                    }
                    double t_avg = avg(times, tests);
                    printf("Поиск пути занял: %.6lfмкс.\n", t_avg);
                    printf("Граф занимает: %zuБ\n", sizeof(graph_t *) + sizeof(int) * g->numVertices + sizeof(int) * sizeof(int) * g->numVertices);
                }
                else
                {
                    printf("\nГраф пуст!\n");
                }
                break;
            case 0:
                printf("Выход из программы\n");
                break;
            default:
                printf("Некорректный выбор!\n");
        }
    } while (choice != 0);

    end_p:
    //free(g);
    return 0;
}