#ifndef SPARCE_H__

#define SPARCE_H__

#include <stdio.h>
#include <stdlib.h>

#include "consts.h"
#include "err_codes.h"

#include "not_sparce.h"
#include "mtr_types.h"


SparseMatrix m_to_sparce(Matrix *matrix);

int inputSparseVector(SparseVector *vector);

int inputSparseMatrix(SparseMatrix *matrix);

SparseVector createSparseVector(int *values, int *indices, int size);

SparseVector multiplySparseMatrixVector(const SparseMatrix *matrix, const SparseVector *vector);

void printSparseVector(const SparseVector *sparseVector);

void printSparseMatrix(const SparseMatrix *matrix);

void freeSparseMatrix(SparseMatrix *matrix);

void freeSparseVector(SparseVector *sparseVector);

void runExperiment(size_t msize);

#endif
