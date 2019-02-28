#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]){

  FILE* f = fopen("scale.txt", "a");
  
  double tic = omp_get_wtime();
  
  long long int Ninside = 0; 
  long long int Ntests = 1000000000;
  long long n;
  double estpi = 0;

  struct drand48_data randBuffer;  
  srand48_r(12345,&randBuffer);

  //Tricky pragma statement
  for(n=0;n<Ntests;++n){
    double x;
    double y;
    drand48_r(&randBuffer, &x);
    drand48_r(&randBuffer, &y);
    
    //Same expression as serial here
  }

  //Same expression as serial code here
  
  double toc = omp_get_wtime();

  double elapsedTime = toc - tic;

  fprintf(f, "estPi = %lf\n", estpi);
  fprintf(f, "dt = %f\n", elapsedTime);
  fclose(f);
}
