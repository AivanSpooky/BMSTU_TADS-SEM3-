#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "err_codes.h"

#include "tree_type.h"
#include "tree_graphviz.h"
#include "tree_funcs.h"
#include "tree_file_funcs.h"
#include "tree_comparison.h"

#include "tree_balance.h"
#include "external_ht.h"
#include "internal_ht.h"
#include <math.h>

int main()
{
    node_t* root = NULL;
    hashtable_t* ht_ex = NULL;
    ClosedAddressingHashTable* ht_in = NULL;

    int choice, value;
    size_t tests = 100;
    double t1_arr[tests];
    double t2_arr[tests];
    (void) t2_arr;
    double t1, t2;
    (void) t1;
    (void) t2;
    double t1_avg, t2_avg;
    (void) t1_avg;
    (void) t2_avg;
    char tmp_buf[MAX_FILE_LEN];
    char filename[MAX_FILE_LEN] = "files/default.txt";
    size_t len = strlen(filename);
    clock_t start, end;
    printf("Данная программа работает с типами <Бинарное дерево>, <Сбалансированное бинарное дерево>, <Хеш-таблица с внешним хешированием>, <Хеш-таблица с внутренним хешированием>. В выпадающем меню необходимо выбрать номер команды для её выполнения. В программе реализованы следующие функции:\n");
    do
    {
        printf("\nМеню:\n\
        ---\n\
        1. Вывести дерево и хеш-таблицы(graphviz)\n\
        2. Сбалансировать дерево\n\
        ---\n\
        3. Считать дерево (из файла)\n\
        4. Считать хеш-таблицу с закрытой адресацией (из файла)\n\
        5. Считать хеш-таблицу с открытой адресацией (из файла)\n\
        ---\n\
        6. Поиск значения (в хеш-таблице с закрытой адресацией)\n\
        7. Поиск значения (в хеш-таблице с открытой адресацией)\n\
        8. Поиск узла (в дереве)\n\
        ---\n\
        9. Обход дерева (pre-order)\n\
        10. Обход дерева (in-order)\n\
        11. Обход дерева (post-order)\n\
        ---\n\
        0. Выход\n");
        printf("Введите ваш выбор: ");
        if (scanf("%d", &choice) != ARG_READ)
        {
            printf("\nПожалуйста, введите целое число!\n");
            fgets(tmp_buf, MAX_FILE_LEN, stdin);
            continue;
        }
        switch (choice)
        {
            case 1:
                if (root == NULL)
                    printf("\nДерево пусто!\n");
                // else if (root->left == NULL && root->right == NULL)
                //     printf("\ngraphviz не сможет нарисовать дерево, состоящее из одной вершины!\n");
                else
                {
                    convertTreeToDot(root);
                    // Запуск Graphviz для визуализации
                    system("dot -Tpng tree.dot -o tree.png");
                    system("xdg-open tree.png");
                }
                if (ht_ex != NULL)
                    printHashtable(ht_ex);
                if (ht_in != NULL)
                    printClosedAddressingHashTable(ht_in);
                break;
            case 2:
                if (root == NULL)
                    printf("\nДерево пусто!\n");
                else
                {
                    root = balanceBST(root);
                    printf("\nДерево успешно сбалансировано!\n");
                }
                break;
            case 3:
                printf("Введите название файла:\n");
                scanf("%s", filename);
                len = strlen(filename);
                if (filename[len - 1] == '\n')
                    filename[--len] = '\0';
                if (file_exists(filename))
                {
                    printf("\nСтарое дерево уничтожено\n");
                    freeTree(root);
                    root = readTreeFromFile(filename);
                    // Вывод дерева на экран в виде дерева
                    printf("Считанное дерево:\n");
                    printTree(root, 0);
                    if (root != NULL)
                    {
                        clock_t start, end;
                        for (size_t i = 0; i < tests; i++)
                        {
                            freeTree(root);
                            start = clock();
                            root = readTreeFromFile(filename);
                            end = clock();
                            t1 = ((double)(end - start));
                            t1_arr[i] = t1;
                        }
                        t1_avg = avg(t1_arr, tests);
                        printf("\nДерево создалось из данных из файла <%s> за: %.6lfмкс.\n", filename, t1_avg);
                    }
                }
                break;
            case 4:
                printf("Введите название файла:\n");
                scanf("%s", filename);
                len = strlen(filename);
                if (filename[len - 1] == '\n')
                    filename[--len] = '\0';
                if (file_exists(filename))
                {
                    printf("\nСтарая хеш-таблица уничтожена\n");
                    //freeExternalCacheHashTable(ht_ex);
                    ht_ex = createExternalCacheHashTable(filename);
                }
                break;
            case 5:
                printf("Введите название файла:\n");
                scanf("%s", filename);
                len = strlen(filename);
                if (filename[len - 1] == '\n')
                    filename[--len] = '\0';
                if (file_exists(filename))
                {
                    printf("\nСтарая хеш-таблица уничтожена\n");
                    //freeInternalCacheHashTable(ht_in);
                    ht_in = createClosedAddressingHashTable(filename);
                }
                break;
            case 6:
                printf("Введите значение для поиска (оно должно быть в хеш-таблице): ");
                if (scanf("%d", &value) != ARG_READ)
                {
                    printf("\nПожалуйста, введите целое число!\n");
                    fgets(tmp_buf, MAX_FILE_LEN, stdin);
                    break;
                }
                findNumberInExternalCacheHashTable(ht_ex, value, true);
                break;
            case 7:
                printf("Введите значение для поиска (оно должно быть в хеш-таблице): ");
                if (scanf("%d", &value) != ARG_READ)
                {
                    printf("\nПожалуйста, введите целое число!\n");
                    fgets(tmp_buf, MAX_FILE_LEN, stdin);
                    break;
                }
                searchClosedAddressingHashTable(ht_in, value);
                break;
            case 8:
                printf("Введите значение для поиска (оно должно быть в дереве): ");
                if (scanf("%d", &value) != ARG_READ)
                {
                    printf("\nПожалуйста, введите целое число!\n");
                    fgets(tmp_buf, MAX_FILE_LEN, stdin);
                    break;
                }
                size_t comparisons = 0;
                if (search(root, value, &comparisons) == NULL)
                {
                    printf("\nУзел не найден!\n");
                }
                else
                {
                    printf("\nУзел присутсвует в дереве!\n");
                }
                for (size_t i = 0; i < tests; i++)
                {
                    //printf("%zu\n", i);
                    comparisons = 0;
                    start = clock();
                    search(root, value, &comparisons);
                    end = clock();

                    t1 = ((double)(end - start));
                    t1_arr[i] = t1;
                }
                t1_avg = avg(t1_arr, tests);
                size_t sum = printNodesLevelsInfo(root, false);
                printf("Поиск элемента <%d> в дереве: %.6lfмкс.\n", value, t1_avg);
                printf("Теоретическое количество сравниваний в сбалансированном дереве: (%d - %d)\n", 1, (int)log2(sum)+1);
                printf("Количество сравниваний: %zu\n", comparisons);
                break;
            case 9:
                printf("\nPre-order обход: ");
                preOrder(root);
                break;
            case 10:
                printf("\nIn-order обход: ");
                inOrder(root);
                break;
            case 11:
                printf("\nPost-order обход: ");
                postOrder(root);
                break;
            case 0:
                printf("\nПрограмма завершена.\n");
                break;
            default:
                printf("\nНеверный выбор.\n");
                break;
        }
    } while (choice != 0);
    
    return OK;
}  
