#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv){

    long long int Ntests = atoll(argv[1]);
    
    clock_t tic = clock();

    long long int Ninside = 0; //Number of points landing inside quarder of unit circle in the first quadrant
    long long n;
  
    double estpi = 0;

    srand48(12345);
  
    for(n=0;n<Ntests;++n){
        double x = drand48();
        double y = drand48();
     
        if(sqrt(pow(x,2) + pow(y,2)) < 1){
             Ninside++;
        }
    }

    estpi = 4*(double)Ninside / (double)Ntests;

    clock_t toc = clock();
    double elapsed = (double)(toc-tic)/CLOCKS_PER_SEC;

    printf("estPi = %lf\n", estpi);
    printf("dt = %f\n", elapsed);

  
    return 0;
}
