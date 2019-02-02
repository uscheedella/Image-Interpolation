#ifndef __VECTOR3D_H__
#define __VECTOR3D_H__

typedef struct Vector3D_tag {
    float x;
    float y;
    float z;
} Vector3D;

float norm(Vector3D* v);

void normalize(Vector3D* v);

void axpy(float alpha, Vector3D* vx, Vector3D* vy, Vector3D* vz);

float inner_product(Vector3D* vx, Vector3D* vy);

#endif

