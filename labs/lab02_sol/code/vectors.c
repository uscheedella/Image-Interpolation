#include <stdio.h>

#include <math.h>

typedef struct Vector3D_tag {
    float x;
    float y;
    float z;
} Vector3D;

float norm(Vector3D v) {

    float length;

    length = sqrt(pow(v.x, 2.0) + pow(v.y, 2.0) + pow(v.z, 2.0));

    return length;
}

Vector3D axpy(float alpha, Vector3D vx, Vector3D vy)
{
    Vector3D vz;

    vz.x = alpha*vx.x + vy.x;
    vz.y = alpha*vx.y + vy.y;
    vz.z = alpha*vx.z + vy.z;

    return vz;
}

int main()
{

    float alpha = 0.25;
    float beta = 0.56;

    Vector3D vec_x;
    Vector3D vec_y;

    vec_x.x = 1.0;
    vec_x.y = 1.5;
    vec_x.z = 2.3;

    vec_y.x = 0.01;
    vec_y.y = 5.0;
    vec_y.z = 17.1717;

    
    float m;
    m = norm(vec_x);

    printf("2a) norm(vec_x) = %f\n", m);
   
    Vector3D vec_z1;
    Vector3D vec_z2;

    vec_z1 = axpy(alpha, vec_x, vec_y);
    printf("2b) axpy(alpha, vec_x, vec_y) = [%f, %f, %f]^T\n", vec_z1.x, vec_z1.y, vec_z1.z);

    vec_z2 = axpy(alpha, vec_y, vec_y);
    printf("2c) axpy(beta, vec_y, vec_y) = [%f, %f, %f]^T\n", vec_z2.x, vec_z2.y, vec_z2.z);
    
    return 0;
}
