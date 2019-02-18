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

int matvec_outer_rows(Matrix *mat, VectorND *inVec, VectorND *outVec);

int matvec_outer_cols(Matrix *mat, VectorND *inVec, VectorND *outVec);

int matvec_OMP_outer(Matrix *mat, VectorND *inVec, VectorND *outVec);

#endif
