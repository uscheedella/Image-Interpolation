#include <stdio.h>
#include <stdlib.h>

#include "linalg.h"



int main()
{
    float* A;
    float* b;
    float* x;

    int N = 3;

    A = malloc(N*N*sizeof(float));
    b = malloc(N*sizeof(float));
    x = malloc(N*sizeof(float));

    for(int i=0; i<N*N; i++) A[i] = 0.0;
    for(int i=0; i<N; i++) b[i] = 0.0;
    for(int i=0; i<N; i++) x[i] = 0.0;

    b[0] = 3.0;
    b[1] = 1.0;
    b[2] = 2.0;

    A[0] = 1.0; A[1] = 1.0; A[2] = 1.0; 
    A[3] = 0.0; A[4] = 0.0; A[5] = 1.0; 
    A[6] = 0.0; A[7] = 1.0; A[8] = 1.0; 

    printf("A\n");
    for(int i=0; i< N; i++)
    {
        for(int j=0; j< N; j++)
            printf("%f ", A[i*N + j]);
        printf("\n");
    }

    printf("b\n");
    for(int i=0; i< N; i++)
    {
        printf("%f\n", b[i]);
    }

    printf("x\n");
    for(int i=0; i< N; i++)
    {
        printf("%f\n", x[i]);
    }

    linear_solve(N, A, b, x);

    printf("A\n");
    for(int i=0; i< N; i++)
    {
        for(int j=0; j< N; j++)
            printf("%f ", A[i*N + j]);
        printf("\n");
    }

    printf("b\n");
    for(int i=0; i< N; i++)
    {
        printf("%f\n", b[i]);
    }

    printf("x\n");
    for(int i=0; i< N; i++)
    {
        printf("%f\n", x[i]);
    }




    free(A);
    free(b);
    free(x);

}