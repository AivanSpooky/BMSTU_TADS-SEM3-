#include "sparce.h"
#include <time.h>

#define EPS 1e-6

int inputSparseVector(SparseVector *vector)
{
    int nums = 0;
    printf("Введите размерность вектора:\n");
    if (fscanf(stdin, "%d", &nums) != ARG_READ || nums <= 0)
    {
        printf("Число введено неверно!\n");
        return ERR_IO;
    }

    vector->csize = (size_t)nums;
    printf("Введите кол-во ненулевых элементов вектора-строки: ");

    if (fscanf(stdin, "%zu", &vector->size) != ARG_READ)
    {
        printf("Число введено неверно!\n");
        return ERR_IO;
    }
    if (vector->size == 0)
    {
        // vector->A = NULL;
        // vector->IA = NULL;
        return OK;
    }

    vector->A = (int *)calloc(vector->size, sizeof(int));
    vector->IA = (int *)calloc(vector->size, sizeof(int));

    printf("Введите через пробел:\n1-значение ненулевого элемента\n2-его столбец\n(только первые %zu элементов учтутся):\n", vector->size);
    for (size_t i = 0; i < vector->size; i++)
    {
        int num = 0;
        int col = 0;
        if (fscanf(stdin, "%d %d", &num, &col) != 2 * ARG_READ)
        {
            printf("Элементы введены неверно! (неправильный формат или значения)!\n");
            return ERR_IO;
        }
        if (col < 0 || col >= nums)
        {
            printf("Столбец введен неправильно!\n");
            return ERR_RANGE;
        }
        else if (num == 0)
        {
            printf("Нельзя вводить нулевой элемент!\n");
            return ERR_RANGE;
        }
        vector->A[i] = num;
        vector->IA[i] = col;
    }

    // Проверкана неповторяющиеся элементы в одном столбце
    size_t elem = -1;
    for (size_t i = 0; i < vector->size; i++)
    {
        if ((size_t)vector->IA[i] == elem)
        {
            printf("Несколько элементов в одном!\n");
            return ERR_DATA;
        }
        else
        {
            elem = vector->IA[i];
        }
    }

    // Сортировка элементов по номеру столбца
    size_t ind = 99999;
    for (size_t i = 0; i < vector->size - 1; i++)
    {
        ind = i;
        for (size_t j = i + 1; j < vector->size; j++)
        {
            if (vector->IA[j] < vector->IA[ind])
            {
                ind = j;
            }
        }
        int atmp = vector->A[i];
        vector->A[i] = vector->A[ind];
        vector->A[ind] = atmp;

        atmp = vector->IA[i];
        vector->IA[i] = vector->IA[ind];
        vector->IA[ind] = atmp;
    }

    return OK;
}

void find_vals(Matrix *matrix, size_t *cnt, size_t *col_cnt)
{
    for (size_t j = 0; j < matrix->csize; j++)
    {
        int flag = 0;
        for (size_t i = 0; i < matrix->rsize; i++)
        {
            if (matrix->mtr[matrix->rsize * i + j] != 0)
            {
                if (flag == 0)
                {
                    (*col_cnt)++;
                    flag = 1;
                }
                flag = 1;
                (*cnt)++;
            }
        }
        if (flag == 0)
        {
            (*col_cnt)++;
        }
    }
    (void) *cnt;
    (void) *col_cnt;
}

// Vector v_to_not_sparce(SparseVector *vector, size_t msize)
// {
//     Vector res;
//     res.size = msize;
//     size_t cur_i = 0;
//     res.vtr = (int *)calloc(vector->IA[vector->size - 1], sizeof(int));
//     for (size_t i = 0; i < (size_t)vector->IA[vector->size - 1]; i++)
//     {
//         //printf("i - %zu cur_i - %zu\n", i, cur_i);
//         if (vector->IA[cur_i] == (int)i)
//         {
//             res.vtr[i] = vector->A[cur_i];
//             cur_i++;
//         }
//     }
//     return res;
// }
// Matrix m_to_not_sparce(SparseMatrix *matrix)
// {
//     Matrix res;
//     res.csize = matrix->csize;
//     res.rsize = matrix->rsize;
//     size_t cnt = 0;
//     for (size_t i = 0; i < matrix->csize; i++)
//     {
//         int zero_fill = 0;
//         if (matrix->JA[i] == -1)
//             zero_fill = 1;
//         if (i + 1 != matrix->csize)
//         {
//             for (size_t j = 0; j < matrix->rsize; j++)
//             {
//                 if (matrix->IA[cnt] == j)
//                 {
//                     if (cnt < matrix->JA[i + 1])
//                 }
//             }
//         }
        
//     }
// }

SparseMatrix m_to_sparce(Matrix *matrix)
{
    SparseMatrix res;
    res.rsize = matrix->rsize;
    res.csize = matrix->csize;
    res.cnt = 0;
    size_t col_cnt = 0;

    find_vals(matrix, &res.cnt, &col_cnt);
    //printf("%zu - %zu\n", res.cnt, col_cnt);
    res.A = (int *)calloc(res.cnt, sizeof(int));
    res.IA = (int *)calloc(res.cnt, sizeof(int));
    res.JA = (int *)calloc(col_cnt, sizeof(int));

    res.cnt = 0;
    col_cnt = 0;
    for (size_t j = 0; j < matrix->csize; j++)
    {
        int flag = 0;
        for (size_t i = 0; i < matrix->rsize; i++)
        {
            if (matrix->mtr[matrix->rsize * i + j] != 0)
            {
                if (flag == 0)
                {
                    res.JA[col_cnt] = col_cnt;
                    col_cnt++;
                    flag = 1;
                }
                flag = 1;
                //printf("%zu %zu el - %d\n", i, j, matrix->mtr[matrix->rsize * i + j]);
                res.A[res.cnt] = matrix->mtr[matrix->rsize * i + j];
                res.IA[res.cnt] = i;
                res.cnt++;
            }
        }
        if (flag == 0)
        {
            res.JA[col_cnt] = -1;
            col_cnt++;
        }
    }
    return res;
}

size_t findVectorSize(Vector *vector)
{
    size_t cur_col = 0;
    for (size_t i = 0; i < vector->size; i++)
    {
        if (vector->vtr[i] != 0)
        {
            cur_col++;
        }
    }
    return cur_col;
}

SparseVector v_to_sparce(Vector *vector)
{
    SparseVector res;
    res.size = findVectorSize(vector);

    res.csize = vector->size;

    res.A = (int *)calloc(res.size, sizeof(int));
    res.IA = (int *)calloc(res.size, sizeof(int));
    size_t cur_col = 0;
    for (size_t i = 0; i < vector->size; i++)
    {
        if (vector->vtr[i] != 0)
        {
            res.A[cur_col] = vector->vtr[i];
            res.IA[cur_col] = i;
            cur_col++;
        }
    }
    return res;
}

int maximum(int *arr, size_t size)
{
    int max = 0;
    for (size_t i = 0; i < size; i++)
    {
        max = arr[i] > max ? arr[i] : max;
    }
    return max;
}

void sortByC(size_t cnt, size_t *columns, int *A, int *IA)
{
    size_t min_c = 9999999, min_r = 9999999999;
    //printf("\n");
    for (size_t i = 0; i < cnt - 1; i++)
    {
        min_c = i;
        min_r = i;
        for (size_t j = i + 1; j < cnt; j++)
        {
            //printf("%zu - %zu\n", columns[j], columns[min_c]);
            if (columns[j] <= columns[min_c])
            {
                if (columns[j] == columns[min_c])
                {
                    if (IA[j] < IA[min_r])
                    {
                        min_c = j;
                        min_r = j;
                    }
                }
                else
                {
                    min_c = j;
                    min_r = j;
                }
            }
        }
        // printf("%zu %zu\n", min_c, min_r);
        int ctmp = columns[min_r];
        columns[min_r] = columns[i];
        columns[i] = ctmp;

        ctmp = A[min_r];
        A[min_r] = A[i];
        A[i] = ctmp;

        ctmp = IA[min_r];
        IA[min_r] = IA[i];
        IA[i] = ctmp;
        // for (size_t t = 0; t < cnt; t++)
        //     printf("%zu ", columns[t]);
        // printf("\n");
    }
}

size_t findCCount(size_t *columns, size_t cnt)
{
    size_t res = 0;
    size_t cur_i = 0;
    int ind = -100;
    for (size_t i = 0; i <= columns[cnt - 1]; i++)
    {
        //printf("\n%zu, %zu", i, columns[cnt - 1]);
        if (columns[cur_i] == i && (int)columns[cur_i] != ind)
        {
            ind = (int)columns[cur_i];
            res++;
            cur_i++;
        }
        else if ((int)columns[cur_i] == ind)
        {
            i--;
            cur_i++;
        }
        else
        {
            res++;
        }
    }
    return res;

}

void formJA(int *JA, size_t csize, size_t *columns, size_t cnt)
{
    (void) cnt;
    size_t j = 0;
    size_t res = 0;
    int ind = -100;
    for (size_t i = 0; i <= columns[cnt - 1]; i++)
    {
        //printf("%zu %zu - %zu - %d\n", i, res, columns[res], ind);
        if (columns[res] == i && (int)columns[res] != ind)
        {
            ind = (int)columns[res];
            JA[i] = (int)res;
            res++;
            j++;
        }
        else if ((int)columns[res] == ind)
        {
            i--;
            res++;
        }
        else
        {
            JA[i] = -1;
        }
    }
    for (size_t i = columns[cnt - 1] + 1; i < csize; i++)
        JA[i] = -1;
    (void) csize;
}

int inputSparseMatrix(SparseMatrix *matrix)
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

    printf("Введите кол-во ненулевых элементов матрицы: ");

    if (fscanf(stdin, "%zu", &matrix->cnt) != ARG_READ)
    {
        printf("Число введено неверно!\n");
        return ERR_IO;
    }
    if (matrix->cnt == 0)
    {
        // matrix->A = NULL;
        // matrix->IA = NULL;
        // matrix->JA = NULL;
        return OK;
    }

    matrix->A = (int *)calloc(matrix->cnt, sizeof(int));
    matrix->IA = (int *)calloc(matrix->cnt, sizeof(int));
    // matrix->JA = (int *)calloc(matrix->cnt, sizeof(int));
    size_t *columns = calloc(matrix->cnt, sizeof(size_t));

    printf("Введите через пробел для каждого элемента:\n1-номер строки\n2-номер столбца\n3-значение ненулевого элемента\n(только первые %zu элементов учтутся):\n", matrix->cnt);
    int cols[matrix->cnt], rows[matrix->cnt];
    //Matrix res1;
    for (size_t i = 0; i < matrix->cnt; i++)
    {
        int num = 0;
        int row = 0;
        int col = 0;
        if (fscanf(stdin, "%d %d %d", &row, &col, &num) != 3 * ARG_READ || row < 0 || col < 0 || (size_t)col >= matrix->csize || (size_t)row >= matrix->rsize)
        {
            printf("Элементы введены неверно! (неправильный формат или значения)!\n");
            return ERR_IO;
        }
        else if (num == 0)
        {
            printf("Нельзя вводить нулевой элемент!\n");
            return ERR_RANGE;
        }
        matrix->A[i] = num;
        matrix->IA[i] = row;

        cols[i] = col;
        rows[i] = row;

        columns[i] = (size_t)col;
    }

    for (size_t i = 0; i < matrix->cnt - 1; i++)
    {
        for (size_t j = i + 1; j < matrix->cnt; j++)
        {
            if (cols[i] == cols[j] && rows[i] == rows[j])
            {
                printf("Ошибка! Несколько элементов в одном!\n");
                return ERR_DATA;
            }
        }
    }

    sortByC(matrix->cnt, columns, matrix->A, matrix->IA);
    // size_t csize = findCCount(columns, matrix->cnt);
    // matrix->csize = csize;
    matrix->JA = calloc(matrix->csize, sizeof(int));
    formJA(matrix->JA, matrix->csize, columns, matrix->cnt);

    // for (size_t i = 0; i < matrix->csize; i++)
    //     printf("%d\n", matrix->JA[i]);

    // matrix->rsize = maximum(matrix->IA, matrix->cnt) + 1;

    // for (size_t i = 0; i < matrix->rsize; i++)
    // {
    //     for (size_t j = 0; j < matrix->csize; j++)
    //     {
    //         res1.mtr[matrix->rsize * i + j] = 0;
    //     }
    // }
    // for (size_t i = 0; i < matrix->cnt; i++)
    // {
    //     res1.mtr[matrix->rsize * rows[i] + cols[i]] = nums[i];
    // }
    // *matrix = m_to_sparce(&res1);

    free(columns);
    return OK;
}

SparseVector createSparseVector(int *values, int *indices, int size)
{
    SparseVector sparseVector;
    sparseVector.A = values;
    sparseVector.IA = indices;
    sparseVector.size = size;
    return sparseVector;
}

size_t findNextInd(int *inds, size_t size, size_t cur)
{
    size_t ind = -1;
    size_t i = cur + 1;

    while (i < size)
    {
        if (inds[i] != -1)
        {
            ind = inds[i]/* - inds[cur]*/;
            break;
        }
        i++;
    }
    return ind;
}

size_t findResSize(int *inds, size_t cols)
{
    size_t res = 0;
    for (size_t i = 0; i < cols; i++)
    {
        if (inds[i] != ONLYZEROS)
        {
            res++;
        }
    }
    return res;
}

SparseVector multiplySparseMatrixVector(const SparseMatrix *matrix, const SparseVector *vector)
{
    SparseVector result;
    if (vector->size == 0 || matrix->cnt == 0)
    {
        result.size = 0;
        return result;
    }
    if (vector->csize != matrix->rsize)
    {
        // printf("%d, %d\n", vector->IA[vector->size - 1] + 1, (int)matrix->rsize);
        printf("Такое умножение невозможно! (кол-во столбцов вектора-строки не совпадает с кол-вом строк матрицы)\n");
        result.A = NULL;
        return result;
    }

    result.size = findResSize(matrix->JA, matrix->csize);
    result.csize = matrix->rsize;

    result.A = (int *)calloc(result.size, sizeof(int));
    result.IA = (int *)calloc(result.size, sizeof(int));
    
    size_t cur_i = 0;
    for (size_t i = 0; i < matrix->csize; i++)
    {
        if (matrix->JA[i] != ONLYZEROS)
        {
            int end = (matrix->JA[i + 1] != ONLYZEROS) ? (size_t)matrix->JA[i + 1] : findNextInd(matrix->JA, matrix->csize, i);
            end = (i + 1 < matrix->csize) ? end : (int)matrix->cnt;
            end = (end == ONLYZEROS) ? (int)matrix->cnt : end;
            for (size_t j = matrix->JA[i]; j < (size_t)end; j++)
            {
                int row = matrix->IA[j];
                for (size_t k = 0; k < vector->size; k++)
                {
                    if (vector->IA[k] > row)
                        break;
                    if (vector->IA[k] == row)
                    {
                        //printf("%zu (%d, %zu): %d %d\n", cur_i, row, i, matrix->A[j], vector->A[k]);
                        result.A[cur_i] += matrix->A[j] * vector->A[k];
                        result.IA[cur_i] = i;
                        break;
                    }
                }
            }
            if (result.A[cur_i] == 0)
            {
                cur_i--;
                result.size--;
            }
            cur_i++;
        }
    }
    return result;
}

SparseVector multiplySparseMatrixVectorEx(const SparseMatrix *matrix, const Vector *vector)
{
    SparseVector result;
    if (vector->size == 0 || matrix->cnt == 0)
    {
        result.size = 0;
        return result;
    }
    if (vector->size != matrix->rsize)
    {
        printf("Такое умножение невозможно! (кол-во столбцов вектора-строки не совпадает с кол-вом строк матрицы)");
        result.A = NULL;
        return result;
    }

    result.size = findResSize(matrix->JA, matrix->csize);

    result.A = (int *)calloc(result.size, sizeof(int));
    result.IA = (int *)calloc(result.size, sizeof(int));
    
    size_t cur_i = 0;
    for (size_t i = 0; i < matrix->csize; i++)
    {
        if (matrix->JA[i] != ONLYZEROS)
        {
            size_t end = matrix->JA[i + 1] != ONLYZEROS ? (size_t)matrix->JA[i + 1] : findNextInd(matrix->JA, matrix->csize, i);
            end = (i + 1 < matrix->csize) ? end : matrix->cnt;
            for (size_t j = matrix->JA[i]; j < end; j++)
            {
                int row = matrix->IA[j];
                result.A[cur_i] += matrix->A[j] * vector->vtr[row];
                result.IA[cur_i] = i;
            }
            cur_i++;
        }
    }
    return result;
}

void printSparseVector(const SparseVector *sparseVector)
{
    printf("SparseVector (size=%zu):\n", sparseVector->csize);
    if (sparseVector->size == 0)
    {
        printf("Пусто!\n\n");
        return;
    }
    else if (sparseVector->A == NULL)
    {
        return;
    }
    for (size_t i = 0; i < sparseVector->size; i++)
    {
        printf("(%d, %d): %d\n", 0, sparseVector->IA[i], sparseVector->A[i]);
    }
    printf("\n");
}

void printSparseMatrix(const SparseMatrix *matrix)
{
    printf("SparceMatrix:\n");
    if (matrix->cnt == 0)
    {
        printf("Пусто!\n\n");
        return;
    }
    else if (matrix->A == NULL)
    {
        return;
    }
    printf("%zu - %zu - %zu\n", matrix->rsize, matrix->csize, matrix->cnt);
    for (size_t i = 0; i < matrix->csize; i++)
    {
        if (matrix->JA[i] != -1)
        {
            int end = matrix->JA[i + 1] != ONLYZEROS ? (size_t)matrix->JA[i + 1] : findNextInd(matrix->JA, matrix->csize, i);
            end = (i + 1 < matrix->csize) ? end : (int)matrix->cnt;
            end = (end == ONLYZEROS) ? (int)matrix->cnt : end;
            //printf("End: %d\n", end);
            for (size_t j = matrix->JA[i]; j < (size_t)end; j++)
            {
                printf("(%d, %zu): %d\n", matrix->IA[j], i, matrix->A[j]);
            }
        }
    }
    printf("\n");
}

void freeSparseMatrix(SparseMatrix *matrix)
{
    matrix->A = NULL;
    matrix->IA = NULL;
    matrix->JA = NULL;
    free(matrix->A);
    free(matrix->IA);
    free(matrix->JA);
}

void freeSparseVector(SparseVector *sparseVector)
{
    sparseVector->A = NULL;
    sparseVector->IA = NULL;
    free(sparseVector->A);
    free(sparseVector->IA);
}

// void initSparceVector(size_t *size, int *vectorValues, int *vectorIndices)
// {
//     size_t d = *size - 1;
//     size_t cur_size = *size;
//     for (size_t i = 0; i < *size; i++)
//     {
//         if (i % d == 0)
//         {
//             vectorValues[i] = 1;
//             vectorIndices[i] = i;
//         }
//         else
//             (cur_size)--;
//     }
//     (*size) = cur_size;
// }

// void initSparceVector(size_t *size, int *vectorValues, int *vectorIndices)
// {
//     size_t d = *size - 1;
//     size_t cur_size = *size;
//     for (size_t i = 0; i < *size; i++)
//     {
//         if (i % d == 0)
//         {
//             vectorValues[i] = 1;
//             vectorIndices[i] = i;
//         }
//         else
//             (cur_size)--;
//     }
//     (*size) = cur_size;
// }
void fillVector(Vector *vector)
{
    size_t d = 3;
    for (size_t i = 0; i < vector->size; i++)
    {
        vector->vtr[i] = ((i + 1) % d) != 0 ? (i + 1) % d : d;
    }
    vector->cnt = vector->size;
}

void fillMatrix(Matrix *matrix)
{
    size_t d = 10;
    for (size_t i = 0; i < matrix->rsize; i++)
    {
        for (size_t j = 0; j < matrix->csize; j++)
        {
            matrix->mtr[matrix->rsize * i + j] = ((i + 1) % d) != 0 ? (i + 1) % d : d;
        }
    }
}

double avg(double *nums, size_t cnt)
{
    double sum = 0;
    for (size_t i = 0; i < cnt; i++)
    {
        sum += nums[i];
    }
    return sum / cnt;
}

void addSparce(int sparsity, Matrix *matrix1)
{
    size_t cnt = (matrix1->csize * matrix1->rsize * sparsity) / 100;
    size_t zeros = 0;
    for (size_t j = 0; j < matrix1->csize; j++)
    {
        for (size_t i = 0; i < matrix1->rsize; i++)
        {
            matrix1->mtr[matrix1->rsize * i + j] = 0;
            zeros++;
        }
        if (zeros >= cnt)
        {
            break;
        }
    }
}

void addVectorSparce(int sparsity, Vector *vector1)
{
    size_t cnt = (vector1->size * sparsity) / 100;
    size_t zeros = 0;
    for (size_t i = 0; i < vector1->size; i++)
    {
        vector1->vtr[i] = 0;
        zeros++;
        if (zeros >= cnt)
        {
            break;
        }
    }

}

double eff(double t1, double t2)
{
    return ((t1 - t2) / t1 * 100);
}

void runExperiment(size_t msize)
{
    printf("\nЗамерный эксперимент для матрицы %zux%zu:\n\n", msize, msize);
    // size_t size = msize;
    // int *vectorValues = (int *)calloc(size, sizeof(int));
    // int *vectorIndices = (int *)calloc(size, sizeof(int));
    Vector vector1;
    vector1.size = msize;
    vector1.vtr = (int *)calloc(vector1.size, sizeof(int));
    fillVector(&vector1);
    //printf("A\n");
    SparseVector vector = v_to_sparce(&vector1);
    //printSparseVector(&vector);
    //printf("A\n");
    //printVector(&vector1);
    Matrix matrix1;
    matrix1.rsize = msize;
    matrix1.csize = msize;
    matrix1.mtr = (int *)calloc(matrix1.rsize * matrix1.csize, sizeof(int));
    fillMatrix(&matrix1);
    //printf("A\n");
    SparseMatrix matrix = m_to_sparce(&matrix1);

    //printf("A\n");
    size_t tests = 100;
    double t_1[tests];
    double t_2[tests];
    int sizes = 0;
    // Varying the sparsity percentage from 0% to 99%
    for (int sparsity = 0; sparsity <= 99; sparsity += 1)
    {
        addVectorSparce(sparsity, &vector1);
        freeSparseVector(&vector);
        vector = v_to_sparce(&vector1);

        addSparce(sparsity, &matrix1);
        freeSparseMatrix(&matrix);
        matrix = m_to_sparce(&matrix1);

        size_t size_1 = 3 * sizeof(size_t) + msize * msize * sizeof(size_t) + msize * sizeof(int);
        size_t size_2 = 4 * sizeof(size_t) + 2 * vector.size * sizeof(int) + 2 * matrix.cnt * sizeof(int) + matrix.csize * sizeof(int);
        Vector res1;
        SparseVector res;
        for (size_t i = 0; i < tests; i++)
        {
            // Вычисление времен
            clock_t start, end;
            start = clock();
            res1 = multiplyMatrixVector(&matrix1, &vector1);
            end = clock();
            double t1 = ((double)(end - start));
            t_1[i] = t1;
            // Замер начался
            start = clock();
            res = multiplySparseMatrixVector(&matrix, &vector);
            end = clock();
            double t2 = ((double)(end - start));
            t_2[i] = t2;
            // Замер закончился
        }

        double t1_avg = avg(t_1, tests);
        double t2_avg = avg(t_2, tests);
        if (size_2 - size_1 > EPS && sizes == 0)
        {
            printf("\nSparsity: %d%%\n", sparsity);
            printf("Всего замеров: %zu\n", tests);
            printf("Время выполнения:\n1. Обычный алгоритм - %.6lfмкс.\n2. Разреженный алгоритм - %.6lfмкс.\n", t1_avg, t2_avg);
            printf("Затраты по памяти:\n1. Обычный алгоритм - %zuБ\n2. Разреженный алгоритм - %zuБ\nЭффективность по памяти обычного представления: %.8lf\n", size_1, size_2, -eff(size_2, size_1));
            freeSparseVector(&res);
            free(res1.vtr);
            sizes = 1;
            continue;
        }
        if (t2_avg - t1_avg < EPS)
        {
            printf("\nSparsity: %d%%\n", sparsity);
            printf("Всего замеров: %zu\n", tests);
            printf("Время выполнения:\n1. Обычный алгоритм - %.6lfмкс.\n2. Разреженный алгоритм - %.6lfмкс.\n", t1_avg, t2_avg);
            printf("Затраты по памяти:\n1. Обычный алгоритм - %zuБ\n2. Разреженный алгоритм - %zuБ\nЭффективность по памяти обычного представления: %.8lf\n", size_1, size_2, -eff(size_2, size_1));
            freeSparseVector(&res);
            free(res1.vtr);
            break;
        }
        freeSparseVector(&res);
        free(res1.vtr);
    }

    freeSparseMatrix(&matrix);
    freeSparseVector(&vector);
    free(matrix1.mtr);
    free(vector1.vtr);
}
