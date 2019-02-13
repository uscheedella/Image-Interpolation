#include "matrixProd.h"

/*
  Returns the dot product of n vectors x and y
*/
double dotProd(int n, double* x, double* y){

  double dotProd = 0;

  for(int i=0; i<=n; i++){
    dotProd += x[i]*y[i];
  }

  return dotProd;
}

/*
  Computes matrix vector product Ax where A is an m x n matrix x is an n vector

  Outputs b, an m vector
*/
void matrixVecProd(int m, int n, double* A, double* x, double* b){

  for(int i=0; i<m; i++){
    b[i] = dotProd(n, A+i*m, x);
  }
}

//Prints m x n matrix A
void printA(int m, int n, double* A){
  printf("A = \n");
  
  for(int i=0; i<m; i++){
    for(int j=0; j<n; j++){
      printf("%f ", A[j+n*i]);
    }
    printf("\n");
  }
}

//Returns the L2 norm of an n vector
double norm(int n, double* x){

  double dot = dotProd(n, x, x);

  return sqrt(dot);
}

/*
  Computes the difference of n vectors: a-b and returns the result in a new vector
 */
double* vecDiff(int n, double* a, double* b){

  double* c = (double*)calloc(n, sizeof(double));
  
  for(int i=0; i<n; i++){
    c[i] = a[i] - b[i];
  }

  return c;
}


