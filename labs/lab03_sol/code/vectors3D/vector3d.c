#include <math.h>

#include "vector3d.h"

float norm(Vector3D v) {

    float length;

    length = sqrt(pow(v.x, 2.0) + pow(v.y, 2.0) + pow(v.z, 2.0));

    return length;
}

Vector3D axpy(float alpha, Vector3D vx, Vector3D vy) {
    Vector3D vz;

    vz.x = alpha*vx.x + vy.x;
    vz.y = alpha*vx.y + vy.y;
    vz.z = alpha*vx.z + vy.z;

    return vz;
}

float inner_product(Vector3D vx, Vector3D vy) {
    return vx.x*vy.x + vx.y*vy.y + vx.z*vy.z;
}

