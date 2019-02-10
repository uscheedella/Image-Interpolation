#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include <math.h>

#include "vectorNd.h"

int allocate_VectorND(VectorND* v, int dimension) {

    v->dimension = dimension;
    v->data = malloc(sizeof(float)*dimension);

    // malloc failed
    if (v->data == NULL) return 1;

    memset(v->data, 0, sizeof(float)*dimension);

    return 0;
}

int deallocate_VectorND(VectorND* v) {

    v->dimension = 0;

    free(v->data);
    v->data = NULL;

    return 0;
}

float norm(VectorND* v) {

    float length = 0.0;

    for(int i=0; i < v->dimension; i++){
        length += pow(v->data[i], 2.0);
    }
    length = sqrt(length);

    return length;
}

int normalize(VectorND* v) {
    float length = norm(v);

    // Zero vector, nothing to do.
    if( abs(length) < 1e-5 ) return 0;

    for(int i=0; i < v->dimension; i++){
        v->data[i] /= length;
    }
    
    return 0;
}

int axpy(float alpha, VectorND* vx, VectorND* vy, VectorND* vz) {

    // Sanity check on array dimensions
    if ((vx->dimension != vy->dimension) ||
        (vx->dimension != vz->dimension)){
        return 1;
    }

    for(int i=0; i < vx->dimension; i++){
        vz->data[i] = alpha*vx->data[i] + vy->data[i];
    }

    return 0;
}

int inner_product(VectorND* vx, VectorND* vy, float* ip) {

    *ip = 0.0;

    // Sanity check on array dimensions
    if (vx->dimension != vy->dimension) return 1;



    for(int i=0; i < vx->dimension; i++){
        *ip += vx->data[i]*vy->data[i];
    }
    
    return 0;
}
