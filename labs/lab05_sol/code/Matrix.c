#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include "VectorND.h"
#include "Matrix.h"


int allocate_Matrix(Matrix* mat, int nRows, int nCols){
    mat->nRows = nRows;
    mat->nCols = nCols;
    mat->data = malloc(sizeof(float)*nRows*nCols);

    // if malloc failed
    if(mat->data == NULL) return 1;

    // if malloc succeeded, initialize entries to 0
    memset(mat->data, 0, sizeof(float)*nRows*nCols);

    return 0;
}

int deallocate_Matrix(Matrix* mat){
    mat->nRows = 0;
    mat->nCols = 0;
    free(mat->data);
    mat->data = NULL;
    return 0;
}

int rand_fill_Matrix(Matrix *mat){
    srand(time(NULL));
    int nRows = mat->nRows;
    int nCols = mat->nCols;
    for(int i=0; i<nRows; ++i){
        for(int j=0; j<nCols; ++j){
            mat->data[i*nCols + j] = (float)rand() / (float)RAND_MAX;
        }
    }
    return 0;
}

int matvec_row_oriented(Matrix *mat, VectorND *inVec, VectorND *outVec){
    // check dimensions
    int nRows = mat->nRows;
    int nCols = mat->nCols;
    int lenIn = inVec->dimension;
    if(lenIn != nCols) return 1;
    int lenOut = outVec->dimension;
    if(lenOut != nRows) return 1;

    // start out each entry of outVec as a 0
    int errFlag = zero_refill_VectorND(outVec);
    if(errFlag != 0) return errFlag;

    // actually loop through all rows and columns to do the matrix vector multiplication
    for(int i=0; i<nRows; ++i){
        for(int j=0; j<nCols; ++j){
            outVec->data[i] = outVec->data[i] + ( mat->data[i*nCols + j] * inVec->data[j]);
        }
    }
    return 0;
}

int matvec_col_oriented(Matrix *mat, VectorND *inVec, VectorND *outVec){
    // check dimensions
    int nRows = mat->nRows;
    int nCols = mat->nCols;
    int lenIn = inVec->dimension;
    if(lenIn != nCols) return 1;
    int lenOut = outVec->dimension;
    if(lenOut != nRows) return 1;

    // start out each entry of outVec as a 0
    int errFlag = zero_refill_VectorND(outVec);
    if(errFlag != 0) return errFlag;

    // actually loop through all columns and rows to do the matrix vector multiplication
    for(int j=0; j<nCols; ++j){
        for(int i=0; i<nRows; ++i){
            outVec->data[i] = outVec->data[i] + (mat->data[i*nCols + j] * inVec->data[j]);
        }
    }
    return 0;
}


int matvec_row_oriented_omp(Matrix *mat, VectorND *inVec, VectorND *outVec){
    // THIS IS THE FUNCTION YOULL MODIFY FOR OMP PART
    //
    // check dimensions
        int nRows = mat->nRows;
        int nCols = mat->nCols;
    int lenIn = inVec->dimension;
    if(lenIn != nCols) return 1;
    int lenOut = outVec->dimension;
    if(lenOut != nRows) return 1;

        // start out each entry of outVec as a 0
        int errFlag = zero_refill_VectorND(outVec);
        if(errFlag != 0) return errFlag;

        // actually loop through all rows and columns to do the matrix vector multiplication, but break up the work into chunks:
    int i;
    #pragma omp parallel for
    for(i=0; i<nRows; ++i){
        for(int j=0; j<nCols; ++j){
                        outVec->data[i] = outVec->data[i] + ( mat->data[i*nCols + j] * inVec->data[j]);
                }
        }
        return 0;
}


