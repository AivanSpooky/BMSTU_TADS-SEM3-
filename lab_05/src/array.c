#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "rc.h"
#include "array.h"

/*
Create array.

Input data:
* const int capacity - array capacity.

Output data:
* arr - pointer to created array.
*/
arr_t *create_array(const int capacity)
{
    arr_t *arr = (arr_t *)malloc(sizeof(arr_t));
    if (!arr)
    {
        return NULL;
    }

    arr->capacity = capacity;
    arr->ind = -1;
    arr->arr = (size_t *)calloc(arr->capacity, sizeof(size_t));
    if (!arr->arr)
    {
        free_array(arr);
        arr = NULL;
        return NULL;
    }

    return arr;
}

/*
Output filled array to ind element.
*/
void output_array(arr_t* arr)
{
    if (arr->ind == -1)
    {
        printf("%s", "Массив пуст");
    }
    else
    {
        for (int i = 0; i < arr->ind + 1; ++i)
        {
            printf("%zx ", arr->arr[i]);
        }
    }

    printf("\n");
}

/*
Free memory allocated for array.

Input data:
* arr_t *arr - array to be freed.

*/
void free_array(arr_t *arr)
{
    if (arr)
    {
        if (arr->arr)
        {
            free(arr->arr);
            arr->arr = NULL;
            free(arr);
            arr = NULL;
            errno = EOK;

            return;
        }

        free(arr);
        arr = NULL;
        errno = EOK;

        return;
    }

    errno = EARRAYMEMORY;
}
