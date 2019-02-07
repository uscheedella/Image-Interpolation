#ifndef __VECTOR3D_H__
#define __VECTOR3D_H__

typedef struct vector3D_tag {
	float x;
	float y;
	float z;
} Vector3D;

float norm(Vector3D*);

Vector3D axpy(Vector3D, Vector3D, float);

float inner_product(Vector3D, Vector3D);

#endif
