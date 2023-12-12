#include "tree_file_funcs.h"
#include <assert.h>
#include <string.h>

bool find_duplicates(int *nums, size_t cnt)
{
    for (size_t i = 0; i < cnt - 1; i++)
    {
        for (size_t j = i + 1; j < cnt; j++)
        {
            if (nums[j] == nums[i])
                return true;
        }
    }
    return false;
}

bool file_exists(char *filename)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("\nТакого файла не существует!\n");
        return false;
    }
    else
        fclose(file);
    return true;
}

node_t* readTreeFromFile(char *filename)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL)
        assert(1 == 0);

    node_t* root = NULL;
    int num;
    size_t cnt = 0;
    while (fscanf(file, "%d", &num) == 1)
        cnt++;
    rewind(file);
    int nums[cnt];
    size_t i = 0;
    while (fscanf(file, "%d", &num) == 1 && i < cnt)
        nums[i++] = num;
    rewind(file);
    if (find_duplicates(nums, cnt))
    {
        printf("\nВ файле найдены дубликаты вершин!\n");
        strcpy(filename, "files/default.txt");
        fclose(file);
        return NULL;
    }
    while (fscanf(file, "%d", &num) == 1)
        root = insert(root, num);

    // fclose(file);

    return root;
}

// Добавление числа в дерево и запись его в файл
void addTreeNodeToFile(char *filename, node_t* root, int newNum)
{
    root = insert(root, newNum);
    FILE* file = fopen(filename, "a");
    if (file == NULL)
        assert(1 == 0);

    fprintf(file, " %d", newNum);
    printf("Число %d добавлено в дерево и записано в файл %s.\n", newNum, filename);
    fclose(file);
}

// Функция для вывода дерева на экран в виде дерева
void printTree(node_t* root, int space)
{
    if (root == NULL)
        return;

    space += 5;

    printTree(root->right, space);

    for (int i = 5; i < space; i++)
        printf(" ");

    printf("%d\n", root->data);

    printTree(root->left, space);
}
