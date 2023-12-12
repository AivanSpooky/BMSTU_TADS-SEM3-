#ifndef NOT_SPARCE_H__

#define NOT_SPARCE_H__

#include <stdio.h>
#include <stdlib.h>
#include "sparce.h"
#include "mtr_types.h"

#include "consts.h"
#include "err_codes.h"



int inputVector(Vector *vector);

int inputMatrix(Matrix *matrix);

Vector multiplyMatrixVector(const Matrix *matrix, const Vector *vector);

void printMatrix(const Matrix *matrix);

void printVector(const Vector *vector);

#endif
