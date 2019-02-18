#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//operations
double dotProd(int n, double* x, double* y);
void matrixVecProd(int m, int n, double* A, double* x, double* b);
void printA(int m, int n, double* A);
double norm(int n, double*x);
double* vecDiff(int n, double* a, double* b);

//tests
void testDotProd();
void testIdentity();
void testShortFat();
void testTallSkinny();
