/*
* Authors:
*   Russell J. Hewett (rhewett@vt.edu)
*
* Not licensed for external distribution.
*/

#include <stdio.h>
#include <lapacke.h>

#include "linalg.h"


/*
* Solves an NxN linear system using LAPACKE Row Major order
*
* Arguments:
*   N: size of matrix
*   A: pointer to matrix, NxN in row major order
*   b: pointer to RHS
*   x: pointer to solution vector to output
*
* Returns:
*   error code: 0 for success, LAPACKE error code on failure
*/

int linear_solve(int N, float* A, float* b, float* x){

    int info;
    int ipiv[N];

    // Copy RHS into solution vector because LAPACKE solves in place
    // This makes this call safe for the RHS if needed.
    for(int i=0; i<N;i++)
        x[i] = b[i];

    info = LAPACKE_sgesv(LAPACK_ROW_MAJOR, N, 1, A, N, ipiv, x, 1);
    
    if (info){
        fprintf(stderr, "Error in LAPACKE sgesv.");
        return info;
    }
}