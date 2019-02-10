#ifndef __VECTORND_H__
#define __VECTORND_H__

typedef struct VectorND_tag {
    float* data;
    int dimension;
} VectorND;

int allocate_VectorND(VectorND* v, int dimension);

int deallocate_VectorND(VectorND* v);

//float norm(Vector3D* v);

//void normalize(Vector3D* v);

//void axpy(float alpha, Vector3D* vx, Vector3D* vy, Vector3D* vz);

//float inner_product(Vector3D* vx, Vector3D* vy);

#endif

