#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "consts.h"
#include "err_codes.h"

#include "not_sparce.h"
#include "sparce.h"


int main()
{
    printf("Программа выполняет умножение вектора-строки на матрицу и выводит изначальные данные и результат на экран\nВыберите, какие именно вектор и матрицу необходимо умножить друг на друга (1 – разреженное представление, 2 – обычное представление).\n");
    printf("Выберите способ умножения:\n");
    printf("1. Разряженным методом\n");
    printf("2. Обычным методом\n");
    int option;
    if (fscanf(stdin, "%d", &option) != ARG_READ)
    {
        printf("Неправильный ввод способа!\n");
        return ERR_IO;
    }
    if (option < 1 || option > 2)
    {
        printf("Неправильный ввод способа!\n");
        return ERR_RANGE;
    }

    SparseVector vector;
    SparseMatrix matrix;
    SparseVector result;
    Vector vector1;
    Matrix matrix1;
    Vector result1;

    int rc = OK;
    switch (option)
    {
    case 1:
        rc = inputSparseVector(&vector);
        if (rc != OK)
            break;
        
        rc = inputSparseMatrix(&matrix);
        if (rc != OK)
            break;
        
        printf("\nИзначальные данные:\n");
        printSparseVector(&vector);
        printSparseMatrix(&matrix);

        result = multiplySparseMatrixVector(&matrix, &vector);
        if (result.A != NULL)
        {
            printf("Результат умножения вектора-строки на матрицу:\n");
            printSparseVector(&result);
        }
        else
        {
            rc = ERR_DATA;
        }

        freeSparseMatrix(&matrix);
        freeSparseVector(&vector);
        freeSparseVector(&result);

        break;
    case 2:
        rc = inputVector(&vector1);
        if (rc != OK)
            return rc;
        
        rc = inputMatrix(&matrix1);
        if (rc != OK)
            return rc;
        
        printf("\nИзначальные данные:\n");
        printVector(&vector1);
        printMatrix(&matrix1);

        // matrix = m_to_sparce(&matrix1);
        // printSparseMatrix(&matrix);

        result1 = multiplyMatrixVector(&matrix1, &vector1);
        if (result1.vtr != NULL)
        {
            printf("Результат умножения вектора-строки на матрицу:\n");
            printVector(&result1);
        }
        else
        {
            rc = ERR_DATA;
        }

        free(matrix1.mtr);
        free(vector1.vtr);
        free(result1.vtr);
        break;
    default:
        printf("Invalid option selected!\n");
        return ERR_IO;
    }

    if (rc == OK)
    {
        // runExperiment(10);
        // runExperiment(50);
        
        // runExperiment(200);
    }

    return rc;
}