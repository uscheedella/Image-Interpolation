#ifndef __VECTOR3D_H__
#define __VECTOR3D_H__

typedef struct vector3D_tag {
	float x;
	float y;
	float z;
} Vector3D;


float norm(Vector3D* one);


void normalize(Vector3D* one);


void axpy(float f, Vector3D * one, Vector3D * two , Vector3D * three);


float inner_product(Vector3D* one, Vector3D* two);

#endif
