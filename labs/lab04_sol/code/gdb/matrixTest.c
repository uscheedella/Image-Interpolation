#include "matrixProd.h"

//Define global tolerance
double tol = 1e-6;

//Simple function to test dot product
void testDotProd(){

  printf("Testing dotProd\n");

  int n = 3;
  double* vecA = (double*)calloc(n, sizeof(double));
  double* vecB = (double*)calloc(n, sizeof(double));

  for(int i=0; i<n; i++){
    vecA[i] = i+1;
    vecB[i] = i+1+n;
  }

  printf("vecA = {%f, %f, %f}\n", vecA[0], vecA[1], vecA[2]);
  printf("vecB = {%f, %f, %f}\n", vecB[0], vecB[1], vecB[2]);

  double dot = dotProd(n, vecA, vecB);
  
  printf("vecA*vecB = %f\n", dot);

  if(fabs(dot-32)<tol){
    printf("Test Passed!\n");
  }
  else{
    printf("Test Failed!\n");
  }

  printf("\n");
  printf("\n");

  free(vecA);
  free(vecB);

}

/*
  
  Tests matrix prod agains the identity matrix.

*/

void testIdentity(){

  int n = 3;
  
  double* A = (double*)calloc(n*n, sizeof(double));
  double* x = (double*)calloc(n, sizeof(double));
  double* b = (double*)calloc(n, sizeof(double)); 
  
  for(int i=0; i<n; i++){
    A[i+n*i] = 1;
    x[i] = i+1;
  }

  printf("Testing matrixVecProd with identity matrix\n");

  printA(n, n, A);

  printf("x = {%f, %f, %f}\n", x[0], x[1], x[2]);

  matrixVecProd(n, n, A, x, b);

  printf("b = {%f, %f, %f}\n", b[0], b[1], b[2]);

  //Since A = I we know that b should be x
  double* c = vecDiff(n, b, x);
  
  if(norm(n, c)<tol){
    printf("Test passed!\n");
  }
  else{
    printf("Test failed!\n");
  }

  printf("\n");
  printf("\n");
  
  free(A);
  free(x);
  free(b);
  free(c);
}

void testShortFat(){

  int m = 2;
  int n = 3;
  
  double* A = (double*)calloc(m*n, sizeof(double));
  double* x = (double*)calloc(n, sizeof(double));
  double* b = (double*)calloc(m, sizeof(double)); 
  
  for(int i=0; i<m; i++){
    for(int j=0; j<n; j++){
      A[j+n*i] = j+n*i+1;
      if(!i){
        x[j] = j+1;
      }
    }
  }

  printf("Testing matrixVecProd a short and fat matrix\n");

  printA(m, n, A);

  printf("x = {%f, %f, %f}\n", x[0], x[1], x[2]);

  matrixVecProd(m, n, A, x, b);

  printf("b = {%f, %f}\n", b[0], b[1]);

  double ans[2] = {14, 32};

  
  double* c = vecDiff(n, b, ans);
  
  if(norm(m, c)<tol){ 
    printf("Test passed!\n");
  }
  else{
    printf("Test failed!\n");
  }

  printf("\n");
  printf("\n");
  
  free(A);
  free(x);
  free(b);
  free(c);
}


void testTallSkinny(){

  int m = 3;
  int n = 2;
  
  double* A = (double*)calloc(m*n, sizeof(double));
  double* x = (double*)calloc(n, sizeof(double));
  double* b = (double*)calloc(m, sizeof(double)); 
  
  for(int i=0; i<m; i++){
    for(int j=0; j<n; j++){
      A[j+n*i] = j+n*i+1;
      if(!i){
        x[j] = j+1;
      }
    }
  }

  printf("Testing matrixVecProd a short and fat matrix\n");

  printA(m, n, A);

  printf("x = {%f, %f}\n", x[0], x[1]);

  matrixVecProd(m, n, A, x, b);

  printf("b = {%f, %f, %f}\n", b[0], b[1], b[2]);

  double ans[3] = {5, 11, 17};

  
  double* c = vecDiff(m, b, ans);
  
  if(norm(m, b)<tol){
    printf("Test passed!\n");
  }
  else{
    printf("Test failed!\n");
  }

  printf("\n");
  printf("\n");
  
  free(A);
  free(x);
  free(b);
  free(c);
}
