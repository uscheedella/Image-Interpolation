#ifndef __VECTORND_H__
#define __VECTORND_H__

typedef struct VectorND_tag {
    int dimension;
    float* data;

} VectorND;

float norm(VectorND* v);

float normalize(VectorND* v);

float axpy(float alpha, VectorND* vx, VectorND* vy, VectorND* vz);

float inner_product(VectorND* vx, VectorND* vy, float* l);

float allocate_VectorND(VectorND*, int dim);

float deallocate_VectorND(VectorND*);

#endif

