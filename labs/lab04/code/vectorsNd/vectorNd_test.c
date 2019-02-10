#include <stdio.h>
#include <stdint.h>
#include <math.h>

#include "vectorNd.h"


int test_VectorND_equal(VectorND* v1, VectorND* v2){
    int pass = 1;

    if (v1->dimension != v2->dimension){
        pass = 0;
        return pass;
    }

    for(int i=0; i < v1->dimension; i++){
        pass = pass && (fabs(v1->data[i] - v2->data[i]) < 1e-5);
    }
    return pass;
}

void setup_norm_test(VectorND* vx, float* ans){
    allocate_VectorND(vx, 100);
    for(int i=0;i < 100;i++) vx->data[i] = 2.1;
    *ans = 21.0;
}

void teardown_norm_test(VectorND* vx, float* ans){
    deallocate_VectorND(vx);
    *ans = 0.0;
}

void setup_normalize_test(VectorND* vx, VectorND* vy, 
                          VectorND* v_ans, VectorND* v_zero){
    allocate_VectorND(vx, 5);
    allocate_VectorND(v_ans, 5);

    vx->data[0] = 3.0;
    vx->data[1] = 3.0;
    vx->data[2] = 4.0;
    vx->data[3] = 4.0;
    vx->data[4] = 5.0;

    v_ans->data[0] = 0.34641016;
    v_ans->data[1] = 0.34641016;
    v_ans->data[2] = 0.46188022;
    v_ans->data[3] = 0.46188022;
    v_ans->data[4] = 0.57735027;

    allocate_VectorND(vy, 37);
    allocate_VectorND(v_zero, 37);
}

void teardown_normalize_test(VectorND* vx, VectorND* vy, 
                             VectorND* v_ans, VectorND* v_zero){
    deallocate_VectorND(vx);
    deallocate_VectorND(v_ans);
    deallocate_VectorND(vy);
    deallocate_VectorND(v_zero);
}

void setup_axpy_test(VectorND* vx, VectorND* vy, float* a, 
                     VectorND* vz, VectorND* v_ans) {

    int n = 555;

    allocate_VectorND(vx, n);
    allocate_VectorND(vy, n);
    allocate_VectorND(v_ans, n);
    allocate_VectorND(vz, n);
    
    *a = 0.137;

    for(int i=0; i<n; i++){
        vx->data[i] = 0.5*i;
        vy->data[i] = 0.11*i + 0.1123;
        v_ans->data[i] = 0.137*0.5*i + 0.11*i + 0.1123;
    }
}

void teardown_axpy_test(VectorND* vx, VectorND* vy, float* a, 
                        VectorND* vz, VectorND* v_ans) {
    deallocate_VectorND(vx);
    deallocate_VectorND(vy);
    deallocate_VectorND(v_ans);
    *a = 0.0;
    deallocate_VectorND(vz);
}

void setup_inner_product_test(VectorND* vx, VectorND* vy, float* s_ans){ 

    int n = 654;

    allocate_VectorND(vx, n);
    allocate_VectorND(vy, n);
    
    *s_ans = 0.0;

    for(int i=0; i<n; i++){
        vx->data[i] = 0.5*i;
        vy->data[i] = 0.11*i + 0.1123;
        *s_ans += (0.5*i)*(0.11*i + 0.1123);
    }
}

void teardown_inner_product_test(VectorND* vx, VectorND* vy, float* s_ans){
    deallocate_VectorND(vx);
    deallocate_VectorND(vy);
    *s_ans = 0.0;
}

int main()
{
    int all_tests = 1;
    int tests[100];
    int test_counter = 0;

    int err = 0;

    VectorND vx;
    VectorND vy;
    VectorND vz;
    float alpha;

    VectorND v_ans;
    VectorND v_zero;
    float s_ans;

    for(int i=0;i<100;i++) tests[i] = 1;

    // Test allocate for success
    err = allocate_VectorND(&vx, 13);
    
    tests[test_counter] = !err;
    test_counter++;

    tests[test_counter] = (vx.data != NULL);
    test_counter++;

    tests[test_counter] = (vx.dimension == 13);
    test_counter++;
    
    // Test allocate for 0
    for(int i=0; i<13;i++){ 
        tests[test_counter] = tests[test_counter] && (((int)vx.data[i]) == 0);
    }
    test_counter++;

    // Test allocate for failure on SIZE_MAX
    // We fake this by giving malloc a negative number
    err = allocate_VectorND(&vy, -1);

    tests[test_counter] = err;
    test_counter++;

    // Test deallocate for success
    err = deallocate_VectorND(&vx);
 
    tests[test_counter] = !err;
    test_counter++;

    // Test deallocate for NULL ptr return
    
    tests[test_counter] = (vx.data == NULL);
    test_counter++;

    err = deallocate_VectorND(&vx);
    
    // Test norm for return value
    setup_norm_test(&vx, &s_ans);

    tests[test_counter] = (fabs(s_ans - norm(&vx)) < 1e-5);
    test_counter++;           

    teardown_norm_test(&vx, &s_ans);

    // Test normalize for success
    // Test normalize for 0 vector
    setup_normalize_test(&vx, &vy, &v_ans, &v_zero);

    normalize(&vx);
    tests[test_counter] = test_VectorND_equal(&vx, &v_ans);
    test_counter++;           

    normalize(&vy);
    tests[test_counter] = test_VectorND_equal(&vy, &v_zero);
    test_counter++;           
    
    teardown_normalize_test(&vx, &vy, &v_ans, &v_zero);
    
    // Test axpy for success
    
    setup_axpy_test(&vx, &vy, &alpha, &vz, &v_ans); 
    
    tests[test_counter] = !axpy(alpha, &vx, &vy, &vz);
    test_counter++;

    tests[test_counter] = test_VectorND_equal(&vz, &v_ans);
    test_counter++;
    
    teardown_axpy_test(&vx, &vy, &alpha, &vz, &v_ans); 
        
    // Test axpy for wrong size x,y
    // Test axpy for wrong size x,z
    // Test axpy for wrong size y,z
    
    allocate_VectorND(&vx, 12);
    allocate_VectorND(&vy, 123);
    allocate_VectorND(&vz, 12);

    tests[test_counter] = axpy(1.0, &vx, &vy, &vz);
    test_counter++;

    deallocate_VectorND(&vy);
    deallocate_VectorND(&vz);

    allocate_VectorND(&vy, 12);
    allocate_VectorND(&vz, 123);

    tests[test_counter] = axpy(1.0, &vx, &vy, &vz);
    test_counter++;
    
    deallocate_VectorND(&vx);
    deallocate_VectorND(&vy);
    deallocate_VectorND(&vz);

    // Test inner_product for success
    setup_inner_product_test(&vx, &vy, &s_ans); 
    
    tests[test_counter] = !inner_product(&vx, &vy, &alpha);
    test_counter++;

    tests[test_counter] = (fabs(alpha - s_ans) < 1e-5);
    test_counter++;
    
    teardown_inner_product_test(&vx, &vy, &s_ans); 
        
    // Test inner_product for wrong size x, y

    allocate_VectorND(&vx, 12);
    allocate_VectorND(&vy, 123);

    tests[test_counter] = inner_product(&vx, &vy, &alpha);
    test_counter++;

    deallocate_VectorND(&vx);
    deallocate_VectorND(&vy);

    all_tests = 1;

    for(int i=0; i < test_counter; i++){
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
