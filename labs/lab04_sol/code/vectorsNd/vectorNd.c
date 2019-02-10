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

/*
float norm(Vector3D* v) {

    float length;

    length = sqrt(pow(v->x, 2.0) + pow(v->y, 2.0) + pow(v->z, 2.0));

    return length;
}

void normalize(Vector3D* v) {
    float length = norm(v);

    v->x = v->x/length;
    v->y = v->y/length;
    v->z = v->z/length;
}

void axpy(float alpha, Vector3D* vx, Vector3D* vy, Vector3D* vz) {

    vz->x = alpha*vx->x + vy->x;
    vz->y = alpha*vx->y + vy->y;
    vz->z = alpha*vx->z + vy->z;

}

float inner_product(Vector3D* vx, Vector3D* vy) {
    return vx->x*vy->x + vx->y*vy->y + vx->z*vy->z;
}
*/
