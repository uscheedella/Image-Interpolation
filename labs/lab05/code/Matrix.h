#include "VectorND.h"

#ifndef __MATRIX_H__
#define __MATRIX_H__

typedef struct Matrix_tag {
    // This defines a matrix stored in row major order so
    // the (row i, column j) entry
    float *data;
    int nRows;
    int nCols;
} Matrix;

int allocate_Matrix(Matrix *mat, int nRows, int nCols);

int deallocate_Matrix(Matrix *mat);

int rand_fill_Matrix(Matrix *mat);

int matvec_row_oriented(Matrix *mat, VectorND *inVec, VectorND *outVec);

int matvec_col_oriented(Matrix *mat, VectorND *inVec, VectorND *outVec);

int matvec_row_oriented_omp(Matrix *mat, VectorND *inVec, VectorND *outVec);

#endif
