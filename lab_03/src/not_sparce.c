#include "not_sparce.h"

int inputVector(Vector *vector)
{
    printf("Введите размер вектора-строки: ");
    if (scanf("%zu", &vector->size) != 1)
    {
        printf("Число введено неверно!\n");
        return ERR_IO;
    }
    if (vector->size == 0)
    {
        printf("Число введено неверно!\n");
        return ERR_RANGE;
    }

    vector->vtr = (int *)calloc(vector->size, sizeof(int));

    printf("Ввести координатным методом или обычным?\n1 - Координатным\n2 - Обычным\n");
    int opt = 0;
    if (scanf("%d", &opt) != ARG_READ || opt <= 0 || opt > 2)
    {
        printf("Ошибка ввода пункта!");
        return ERR_DATA;
    }
    if (opt == 2)
    {
        vector->cnt = vector->size;
        printf("Введите %zu элеменов (через пробел):\n", vector->size);
        for (size_t i = 0; i < vector->size; i++)
        {
            int value;
            if (scanf("%d", &value) != ARG_READ)
            {
                printf("Invalid elements entered!\n");
                return ERR_IO;
            }
            vector->vtr[i] = value;
        }
    }
    else if (opt == 1)
    {
        int cnt = 0;
        printf("Введите кол-во ненулевых элементов матрицы: ");

        if (fscanf(stdin, "%d", &cnt) != ARG_READ)
        {
            printf("Число введено неверно!\n");
            return ERR_IO;
        }
        if (cnt < 0)
        {
            // matrix->A = NULL;
            // matrix->IA = NULL;
            // matrix->JA = NULL;
            return OK;
        }
        vector->cnt = (size_t)cnt;

        printf("Введите через пробел для каждого элемента:\n1-номер столбца\n2-значение ненулевого элемента\n(только первые %d элементов учтутся):\n", cnt);
        //Matrix res1;
        int cols[cnt];
        for (size_t i = 0; i < (size_t)cnt; i++)
        {
            int num = 0;
            int col = 0;
            if (fscanf(stdin, "%d %d", &col, &num) != 2 * ARG_READ || col < 0)
            {
                printf("Элементы введены неверно! (неправильный формат или значения)!\n");
                return ERR_IO;
            }
            else if (num == 0)
            {
                printf("Нельзя вводить нулевой элемент!\n");
                return ERR_RANGE;
            }

            cols[i] = col;
            vector->vtr[col] = num;
            //matrix->mtr[matrix->rsize * row + col] = num;
        }

        // Проверкана неповторяющиеся элементы в одном столбце
        size_t elem = -1;
        for (size_t i = 0; i < (size_t)cnt; i++)
        {
            if ((size_t)cols[i] == elem)
            {
                printf("Несколько элементов в одном!\n");
                return ERR_DATA;
            }
            else
            {
                elem = (size_t)cols[i];
            }
        }

        // // Сортировка элементов по номеру столбца
        // size_t ind = 99999;
        // for (size_t i = 0; i < cnt - 1; i++)
        // {
        //     ind = i;
        //     for (size_t j = i + 1; j < cnt; j++)
        //     {
        //         if (cols[j] < cols[ind])
        //         {
        //             ind = j;
        //         }
        //     }
        //     int atmp = vector->vtr[cols[i]];
        //     vector->vtr[cols[i]] = vector->vtr[ind];
        //     vector->vtr[ind] = atmp;

        //     atmp = cols[i];
        //     cols[i] = cols[ind];
        //     cols[ind] = atmp;
        // }
    }

    return OK;
}

int inputMatrix(Matrix *matrix)
{
    printf("Введите кол-во строк матрицы: ");
    if (scanf("%zu", &matrix->rsize) != 1)
    {
        printf("Количество строк введено неправильно!\n");
        return ERR_IO;
    }

    printf("Введите кол-во столбцов матрицы: ");
    if (scanf("%zu", &matrix->csize) != 1)
    {
        printf("Количество столбцов введено неправильно!\n");
        return ERR_IO;
    }

    printf("Вводите строки матрицы:\n");
    matrix->mtr = (int *)calloc(matrix->csize * matrix->rsize, sizeof(int));
    printf("Ввести координатным методом или обычным?\n1 - Координатным\n2 - Обычным\n");
    int opt = 0;
    if (scanf("%d", &opt) != ARG_READ || opt <= 0 || opt > 2)
    {
        printf("Ошибка ввода пункта!");
        return ERR_DATA;
    }
    if (opt == 2)
    {
        for (size_t i = 0; i < matrix->rsize; i++)
        {
            printf("Строка %zu: ", i);
            for (size_t j = 0; j < matrix->csize; j++)
            {
                int value = 0;
                if (scanf("%d", &value) != ARG_READ)
                {
                    printf("Элементы введены неправильно!\n");
                    return ERR_IO;
                }

                matrix->mtr[matrix->csize * i + j] = value;
            }
        }
    }
    else if (opt == 1)
    {
        int cnt = 0;
        printf("Введите кол-во ненулевых элементов матрицы: ");

        if (fscanf(stdin, "%d", &cnt) != ARG_READ)
        {
            printf("Число введено неверно!\n");
            return ERR_IO;
        }
        if (cnt < 0)
        {
            // matrix->A = NULL;
            // matrix->IA = NULL;
            // matrix->JA = NULL;
            return OK;
        }

        printf("Введите через пробел для каждого элемента:\n1-номер строки\n2-номер столбца\n3-значение ненулевого элемента\n(только первые %d элементов учтутся):\n", cnt);
        //Matrix res1;
        int cols[cnt], rows[cnt];
        for (size_t i = 0; i < (size_t)cnt; i++)
        {
            int num = 0;
            int row = 0;
            int col = 0;
            if (fscanf(stdin, "%d %d %d", &row, &col, &num) != 3 * ARG_READ || row < 0 || col < 0)
            {
                printf("Элементы введены неверно! (неправильный формат или значения)!\n");
                return ERR_IO;
            }
            else if (num == 0)
            {
                printf("Нельзя вводить нулевой элемент!\n");
                return ERR_RANGE;
            }
            cols[i] = col;
            rows[i] = row;
            //printf("HAHHA\n");
            matrix->mtr[matrix->csize * row + col] = num;
        }

        // Проверкана неповторяющиеся элементы в одном столбце
        for (size_t i = 0; i < (size_t)cnt - 1; i++)
        {
            for (size_t j = i + 1; j < (size_t)cnt; j++)
            {
                if (cols[i] == cols[j] && rows[i] == rows[j])
                {
                    printf("Ошибка! Несколько элементов в одном!\n");
                    return ERR_DATA;
                }
            }
        }

    }

    return OK;
}

Vector multiplyMatrixVector(const Matrix *matrix, const Vector *vector)
{
    Vector result;
    if (vector->size == 0 || matrix->rsize * matrix->csize == 0)
    {
        result.size = 0;
        return result;
    }
    if (vector->size != matrix->rsize)
    {
        printf("Такое умножение невозможно! (кол-во столбцов вектора-строки не совпадает с кол-вом строк матрицы)\n");
        result.vtr = NULL;
        return result;
    }

    result.size = matrix->csize;
    result.cnt = matrix->csize;
    result.vtr = (int *)calloc(matrix->csize, sizeof(int));

    for (size_t i = 0; i < matrix->csize; i++)
    {
        for (size_t j = 0; j < matrix->rsize; j++)
        {
            //printf("(%zu %zu) %d %d\n", j, i, matrix->mtr[matrix->rsize * i + j], vector->vtr[j]);
            result.vtr[i] += matrix->mtr[matrix->csize * j + i] * vector->vtr[j];
        }
    }

    return result;
}


void printMatrix(const Matrix *matrix)
{
    printf("Matrix (%zux%zu):\n", matrix->rsize, matrix->csize);
    if (matrix->rsize * matrix->csize == 0)
    {
        printf("Пусто!\n\n");
        return;
    }
    else if (matrix->mtr == NULL)
    {
        return;
    }
    for (size_t i = 0; i < matrix->rsize; i++)
    {
        for (size_t j = 0; j < matrix->csize; j++)
        {
            printf("%d ", matrix->mtr[matrix->csize * i + j]);
        }
        printf("\n");
    }
}

void printVector(const Vector *vector)
{
    printf("Vector:\n");
    if (vector->size == 0)
    {
        printf("Пусто!\n\n");
        return;
    }
    else if (vector->vtr == NULL)
    {
        return;
    }
    for (size_t i = 0; i < vector->size; i++)
    {
        printf("%d ", vector->vtr[i]);
    }
    printf("\n");
}