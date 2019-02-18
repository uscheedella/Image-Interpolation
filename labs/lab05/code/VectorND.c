#include <stdlib.h>
#include <time.h> // for clock
#include <string.h> // for memset
#include "VectorND.h"

int allocate_VectorND(VectorND *v, int dimension){
	v->dimension = dimension;
	v->data = malloc(sizeof(float)*dimension);

	// in case malloc failed
	if(v->data == NULL) return 1;

	// if malloc succeeded, set entries to 0
	memset(v->data, 0, sizeof(float)*dimension);

	return 0;
}

int deallocate_VectorND(VectorND *v){
	v-> dimension = 0;
	free(v->data);
	v->data = NULL;
	return 0;
}

int rand_fill_VectorND(VectorND *v){
	// seed with current time
	srand(time(NULL));
	// check that dimension of vector is reasonable
	int dim = v->dimension;
	if(dim < 1) return 1;
	// loop through and fill vector with random numbers 0 to 1
	for(int i=0; i<dim; ++i){
		v->data[i] = (float)rand() / (float)RAND_MAX;
	}
	return 0;
}

int zero_refill_VectorND(VectorND *v){
	// get dimension of vector and make sure it's reasonable
	int dim = v->dimension;
	if(dim < 1) return 1;
	// fill each entry of vector's data with a 0
	for(int i=0; i<dim; ++i) v->data[i] = 0.0;
	return 0;
}
