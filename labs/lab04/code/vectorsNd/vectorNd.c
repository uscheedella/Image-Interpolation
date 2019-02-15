#include <math.h>
#include <stddef.h>
#include "vectorNd.h"
#include <string.h>
#include <stdlib.h>

float norm(VectorND* v) {

    float length = 0;

    for(int x = 0; x < v->dimension; x++) {

    length = length + sqrt(pow(v->data[x], 2.0));
    
    }

    return length;
}

float normalize(VectorND* v) {
    float length = norm(v);
    if (length < pow(10, -5)) {
	return 1;
    }
    else {
    	for (int x = 0; v->dimension;x++) {
    		v->data[x] = v->data[x]/length;
    	}
    }
    return 0;
}

float axpy(float alpha, VectorND* vx, VectorND* vy, VectorND* vz) {
    float vxlength = norm(vx);
    float vylength = norm(vy);
    if (vxlength != vylength) {
        return 1;
    }
    else {
        for (int x = 0; vx->dimension;x++) {
                vz->data[x] = alpha*vx->data[x] + vy->data[x];
        }
    return 0;
    }
}

float inner_product(VectorND* vx, VectorND* vy, float* length) {
    if (vx->data == NULL || vy->data == NULL) {
	return 1;
    } 
    if (vx->dimension != vy->dimension) {
        return 1;
    }
    else {
	float sum = 0.0;
        for (int x = 0; x< vx->dimension;x++) {
                sum += vx->data[x]*vy->data[x];
        }
	length = &sum;
    
    return 0;
    }
}

float allocate_VectorND(VectorND* v, int dim) {
	v->data = malloc(dim*sizeof(float));
	v->data = memset(v->data, 0, dim);
	v->dimension = dim;

}

float deallocate_VectorND(VectorND* v) {
	free(v);
	v->dimension = 0;
	
}
