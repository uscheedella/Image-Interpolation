#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int vector_size = 7;
    float *vector = (float *) malloc(vector_size*sizeof(float));
    float *rotations = (float *) malloc(vector_size*vector_size*sizeof(float));

    //seed vector with random data
    srand48(0);
    for (int i = 0; i < vector_size; i++) {
	vector[i] = drand48();
    }

    //fill rows of array with vector rotations
    for (int i = 0; i < vector_size; i++) {
	for (int j = 0; j < vector_size; i++) {
	    int index = (j+i)%vector_size;
	    rotations[i*vector_size + index] = vector[j];
	}
    }

    //print matrix entries
    for (int i = 0; i < vector_size; i++) {
	for (int j = 0; j < vector_size; j++) {
	    printf("%f ",rotations[i*vector_size+j]);
	}
	printf("\n");
	}
    free(vector);
    free(rotations);
    return 0;
}
