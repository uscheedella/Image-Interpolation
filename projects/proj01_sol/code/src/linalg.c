#include <stdio.h>
#include <lapacke.h>

#include "linalg.h"


int linear_solve(int N, float* A, float* b, float* x){

    int info;
    int ipiv[N];

    /* Swap through the partial pivot matrix. */
    for(int i=0; i<N;i++)
        x[i] = b[i];

    info = LAPACKE_sgesv(LAPACK_ROW_MAJOR, N, 1, A, N, ipiv, x, 1);
    
    if (info){
        fprintf(stderr, "Error in LAPACKE sgesv.");
        return 1;
    }


}