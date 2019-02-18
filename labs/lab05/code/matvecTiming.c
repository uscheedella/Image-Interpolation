#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "VectorND.h"
#include "Matrix.h"

int nRuns = 50;

int main(int argc, char *argv[]){
	if(argc < 3){
		printf("WARNING: Missing input argument specifying matrix dimensions. \n");
		printf("Run code as > executable_name nRows nColumns \n");
		return 1;
	}

	// read input arguments to get number of rows and columns
	int nRows = atoi(argv[1]);
	int nCols = atoi(argv[2]);

	printf("matvec timing, %4d, %4d, %4d", nRows, nCols, nRuns);

	// create A matrix thats nRows x nCols with random entries
	Matrix A;
	allocate_Matrix(&A, nRows, nCols);
	rand_fill_Matrix(&A);
	// create x vector that has nCols random entries
	VectorND x;
	allocate_VectorND(&x, nCols);
	rand_fill_VectorND(&x);
	// create b vector that has nRows, initialized as zeros
	VectorND b;
	allocate_VectorND(&b, nRows);


	// set up number of repeat runs, and declare timers
	clock_t beginning, ending;

	// timing of A*x = b with outer loop over rows of A
	beginning = clock();
	for(int i=0; i<nRuns; ++i) matvec_row_oriented(&A, &x, &b);
	ending = clock();
	double secondsToRun = (double)(ending-beginning)/(double)CLOCKS_PER_SEC;
	double avgSecPerRunRows = secondsToRun/(double)nRuns;
	
	printf(", %lf, %lf", secondsToRun, avgSecPerRunRows);

	// timing of A*x = b with outer loop over columns of A
	beginning = clock();
	for(int i=0; i<nRuns; ++i) matvec_col_oriented(&A, &x, &b);
	ending = clock();
	secondsToRun = (double)(ending-beginning)/(double)CLOCKS_PER_SEC;
	double avgSecPerRunCols = secondsToRun/(double)nRuns;

	printf(", %lf, %lf", secondsToRun, avgSecPerRunCols);

	printf("\n");

	// cleanup
	deallocate_Matrix(&A);
	deallocate_VectorND(&x);
	deallocate_VectorND(&b);

	return 0;
}
