#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main (int argc, char *argv[]){

  FILE* f = fopen("scale.txt", "a");
  
  double tic = omp_get_wtime();
  
  long long int Ninside = 0; 
  long long int Ntests = 1000000000;
  long long n;
  double estpi = 0;

  struct drand48_data randBuffer;  
  srand48_r(omp_get_thread_num(),&randBuffer);

  //Tricky pragma statement
  #pragma omp parallel private(n,randBuffer) reduction(+:Ninside)
  for(n=0;n<Ntests;++n){
    double x;
    double y;
    drand48_r(&randBuffer, &x);
    drand48_r(&randBuffer, &y);
    
    //Same expression as serial here
    if(sqrt((x*x) + (y*y)) < 1){ //(check if radius is radius is less
        Ninside++;    
    }

  }

  //Same expression as serial code here
  estpi = (double)(4*Ninside) / (double)(Ntests * 8);

  double toc = omp_get_wtime();

  double elapsedTime = toc - tic;

  fprintf(f, "estPi = %lf\n", estpi);
  fprintf(f, "dt = %f\n", elapsedTime);
  fclose(f);
}
