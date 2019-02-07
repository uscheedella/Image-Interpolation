#include <math.h>

#include "vector3d.h"

float norm(Vector3D* v) {
	return sqrt(pow(v->x, 2.0) + pow(v->y, 2.0) + pow(v->z, 2.0));
}

void  normalize(Vector3D* vv) {
	Vector3D res;
	int n = norm(vv);
	int normie = 1/n;
	vv->x = normie * vv->x;
	vv->y = normie * vv->y;
	vv->z = normie * vv->z;

}

void axpy(float a, Vector3D* v, Vector3D* vv, Vector3D* z) {
        z->x = (a * v->x) + vv->x;
        z->y = (a * v->y) + vv->y;
        z->z = (a * v->z) + vv->z;
}

float inner_product(Vector3D* v, Vector3D* vv) {
        return (v->x * vv->x) + (v->y * vv->y) + (v->z * vv->z);
}

