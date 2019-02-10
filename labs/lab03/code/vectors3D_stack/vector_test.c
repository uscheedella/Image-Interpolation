#include <stdio.h>
#include <math.h>

#include "vector3d.h"


int test_Vector3D_equal(Vector3D* v1, Vector3D* v2){
    int pass = 1;
    for(int i=0; i < 3; i++){
        pass = pass && (v1->data[i] == v2->data[i]);
    }
    return pass;
}

int main()
{
    int all_tests = 1;
    int tests[8] = { 0 };

    Vector3D vx, vy, vz;
    Vector3D vx_unit;
    Vector3D vx0, vy0, vz0;
    Vector3D v0;
    Vector3D v_answer;

    float inv_sqrt3 = 1.0/sqrt(3.0); 

    // Test 0: norm does not change the vector
    vx = (Vector3D) {1.0, 1.0, 1.0};
    vx0 = vx;

    norm(&vx);
    tests[0] = test_Vector3D_equal(&vx, &vx0);

    // Test 1: normalize changes the results
    vx = (Vector3D) {1.0, 1.0, 1.0};
    vx_unit = (Vector3D) {inv_sqrt3, inv_sqrt3, inv_sqrt3};

    normalize(&vx);
    tests[1] = test_Vector3D_equal(&vx, &vx_unit);

    // Test 2-3: inner product produces correct results
    vx = (Vector3D) {1.0, 1.0, 1.0};
    vx_unit = (Vector3D) {inv_sqrt3, inv_sqrt3, inv_sqrt3};
    vy = (Vector3D) {1.0, 1.0, 1.0};
    
    tests[2] = inner_product(&vx_unit, &vy) == 3.0*inv_sqrt3;

    v0 = (Vector3D) {0.,0.,0.};
    tests[3] = inner_product(&vy, &v0) == 0.0;

    // Test 4-7: axpy does not change x or y and correctly changes z 
    vx = (Vector3D) {1.0, 1.0, 1.0};
    vx0 = vx;
    vy = (Vector3D) {2.0, 4.0, 6.0};
    vy0 = vy;
    vz = (Vector3D) {-1.0, -1.0, -1.0};
    vz0 = vz;

    axpy(0.25, &vy, &vx, &vz);

    v_answer = (Vector3D) {1.5, 2.0, 2.5};

    tests[4] = test_Vector3D_equal(&vx, &vx0);
    tests[5] = test_Vector3D_equal(&vy, &vy0);
    tests[6] = !test_Vector3D_equal(&vz, &vz0);
    tests[7] = test_Vector3D_equal(&vz, &v_answer);

    all_tests = 1;

    for(int i=0; i < 8; i++){
        all_tests = all_tests && tests[i];
        if (tests[i]){
            printf("Test %d: Pass\n", i);
        }
        else{
            printf("Test %d: Fail\n", i);
        }
    }
    if (all_tests){
        printf("All Tests: Pass\n");
    }
    else{
        printf("Some Tests: Fail\n");
    }
    return 0;
}
