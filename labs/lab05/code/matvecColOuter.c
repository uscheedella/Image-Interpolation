#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "VectorND.h"
#include "Matrix.h"

int main(int argc, char *argv[]){
	if(argc < 3){
		printf("WARNING: Missing input argument specifying matrix dimensions. \n");
		printf("Run code as > executable_name nRows nColumns \n");
		return 1;
	}

	// read input arguments to get number of rows and columns
	int nRows = atoi(argv[1]);
	int nCols = atoi(argv[2]);
	printf("----------- Testing %d x %d matrix multiplied by %d dimensional vector ------- \n", nRows, nCols, nCols);

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
	int nRuns = 50;
	printf("Starting timing tests with %d repeat runs \n", nRuns);


	// timing of A*x = b with outer loop over columns of A
	beginning = clock();
	for(int i=0; i<nRuns; ++i) matvec_outer_cols(&A, &x, &b);
	ending = clock();
	double secondsToRun = (double)(ending-beginning)/(double)CLOCKS_PER_SEC;
	double avgSecPerRunCols = secondsToRun/(double)nRuns;
	printf("Matvec with columns as outer loop took %e seconds per run \n", avgSecPerRunCols);

	// cleanup
	deallocate_Matrix(&A);
	deallocate_VectorND(&x);
	deallocate_VectorND(&b);

	return 0;
}
