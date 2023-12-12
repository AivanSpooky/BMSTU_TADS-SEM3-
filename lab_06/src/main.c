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

int main()
{
    node_t* root = NULL;
    int choice, value;
    size_t tests = 100;
    double t1_arr[tests];
    double t2_arr[tests];
    double t1, t2;
    (void) t1;
    (void) t2;
    double t1_avg, t2_avg;
    char tmp_buf[MAX_FILE_LEN];
    char filename[MAX_FILE_LEN] = "files/default.txt";
    printf("Данная программа работает с типом <Бинарное дерево>. В выпадающем меню необходимо выбрать номер команды для её выполнения. В программе реализованы следующие функции:\n");
    do
    {
        printf("\nМеню:\n\
        ---\n\
        1. Вывести дерево (graphviz)\n\
        2. Вывести дерево (терминал)\n\
        ---\n\
        3. Считать дерево (из файла)\n\
        4. Включить узел (в дерево и файл)(сравнить время добавления)\n\
        5. Вывести количество узлов на всех уровнях дерева\n\
        ---\n\
        6. Включить узел (в дерево)\n\
        7. Исключить узел (из дерева)\n\
        8. Поиск узла\n\
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
                break;
            case 2:
                if (root == NULL)
                    printf("\nДерево пусто!\n");
                printTree(root, 0);
                break;
            case 3:
                printf("Введите название файла:\n");
                scanf("%s", filename);
                size_t len = strlen(filename);
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
                if (filename == NULL)
                {
                    printf("\nФайл не найден! (скорее всего вы не считали дерево из файла, воспользуйтесь пунктом №3)\n");
                    break;
                }
                printf("Введите значение для включения: ");
                if (scanf("%d", &value) != ARG_READ)
                {
                    printf("\nПожалуйста, введите целое число!\n");
                    fgets(tmp_buf, MAX_FILE_LEN, stdin);
                    break;
                }
                if (strcmp(filename, "default.txt") == 0)
                    printf("\nЗапись произойдет в файл <default.txt>\n");
                else
                    printf("\nЗапись произойдет в файл <%s>\n", filename);
                if (search(root, value) != NULL)
                {
                    printf("\nЭлемент нельзя добавить, так как он уже существует!\n");
                    break;
                }
                addTreeNodeToFile(filename, root, value);
                if (root == NULL)
                    root = readTreeFromFile(filename);

                char tmp_filename[MAX_FILE_LEN] = "tmp.txt";
                char ch;
                clock_t start, end;
                for (size_t i = 0; i < tests; i++)
                {
                    //printf("%zu\n", i);
                    root = deleteNode(root, value);
                    
                    start = clock();
                    root = insert(root, value);
                    end = clock();

                    t1 = ((double)(end - start));
                    t1_arr[i] = t1;

                    // Открытие оригинального файла для чтения
                    FILE* originalFile = fopen(filename, "r");
                    if (originalFile == NULL)
                        assert(1 == 0);

                    // Создание копии файла
                    FILE* copyFile = fopen("tmp.txt", "w");
                    if (copyFile == NULL)
                        assert(1 == 0);
                        
                    // Копирование содержимого из оригинального файла в копию
                    while ((ch = fgetc(originalFile)) != EOF)
                        fputc(ch, copyFile);

                    // Закрытие файлов
                    fclose(originalFile);

                    start = clock();
                    fprintf(copyFile, " %d", value);
                    end = clock();

                    t2 = ((double)(end - start));
                    t2_arr[i] = t2;
                    fclose(copyFile);
                    remove(tmp_filename);
                }
                t1_avg = avg(t1_arr, tests);
                t2_avg = avg(t2_arr, tests);
                double eff_ = eff(t2_avg, t1_avg);
                printf("Добавление элемента <%d> в дерево: %.6lfмкс.\nДобавление элемента <%d> в файл: %.6lfмкс.\nЭффективность добавления в дерево относительно добавления в файл: %.6lf%%\n", value, t1_avg, value, t2_avg, eff_);
                break;
            case 5:
                printNodesLevelsInfo(root);
                break;
            case 6:
                printf("Введите значение для включения: ");
                if (scanf("%d", &value) != ARG_READ)
                {
                    printf("\nПожалуйста, введите целое число!\n");
                    fgets(tmp_buf, MAX_FILE_LEN, stdin);
                    break;
                }
                if (search(root, value) != NULL)
                {
                    printf("Элемент нельзя добавить, так как он уже существует!\n");
                    break;
                }
                root = insert(root, value);
                break;
            case 7:
                printf("Введите значение для исключения (оно должно быть в дереве): ");
                if (scanf("%d", &value) != ARG_READ)
                {
                    printf("\nПожалуйста, введите целое число!\n");
                    fgets(tmp_buf, MAX_FILE_LEN, stdin);
                    break;
                }
                if (search(root, value) == NULL)
                {
                    printf("\nУзел не найден!\n");
                }
                else
                {
                    root = deleteNode(root, value);
                }
                break;
            case 8:
                printf("Введите значение для поиска (оно должно быть в дереве): ");
                if (scanf("%d", &value) != ARG_READ)
                {
                    printf("\nПожалуйста, введите целое число!\n");
                    fgets(tmp_buf, MAX_FILE_LEN, stdin);
                    break;
                }
                if (search(root, value) == NULL)
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
                    start = clock();
                    search(root, value);
                    end = clock();

                    t1 = ((double)(end - start));
                    t1_arr[i] = t1;
                }
                t1_avg = avg(t1_arr, tests);
                printf("Поиск элемента <%d> в дереве: %.6lfмкс.\n", value, t1_avg);
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
