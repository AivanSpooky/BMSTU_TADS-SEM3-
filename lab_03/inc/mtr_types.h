#ifndef MTR_TYPES_H__

#define MTR_TYPES_H__

#include <stdio.h>

typedef struct
{
    size_t rsize;
    size_t csize;
    int *mtr;
} Matrix;

typedef struct
{
    size_t size;
    size_t cnt;
    int *vtr;
} Vector;

typedef struct
{
    size_t cnt;
    int *A;
    int *IA;
    int *JA;
    size_t rsize;
    size_t csize;
} SparseMatrix;

typedef struct
{
    int *A;
    int *IA;
    size_t size;
    size_t csize;
} SparseVector;

#endif
