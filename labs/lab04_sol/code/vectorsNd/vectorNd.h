#ifndef __VECTORND_H__
#define __VECTORND_H__

typedef struct VectorND_tag {
    float* data;
    int dimension;
} VectorND;

int allocate_VectorND(VectorND* v, int dimension);

int deallocate_VectorND(VectorND* v);

float norm(VectorND* v);

int normalize(VectorND* v);

int axpy(float alpha, VectorND* vx, VectorND* vy, VectorND* vz);

int inner_product(VectorND* vx, VectorND* vy, float* ip);

#endif

