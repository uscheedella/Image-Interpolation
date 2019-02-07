#include <math.h>

#include "vector3d.h"

float norm(Vector3D* v) {
	return sqrt(pow(v->x, 2.0) + pow(v->y, 2.0) + pow(v->z, 2.0));
}

Vector3D axpy(Vector3D v, Vector3D vv, float a) {
        Vector3D z;
        z.x = (a * v.x) + vv.x;
        z.y = (a * v.y) + vv.y;
        z.z = (a * v.z) + vv.z;
        return z;
}

float inner_product(Vector3D v, Vector3D vv) {
        return (v.x * vv.x) + (v.y * vv.y) + (v.z * vv.z);
}

