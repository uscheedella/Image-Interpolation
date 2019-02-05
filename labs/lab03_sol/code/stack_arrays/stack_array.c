#include <stdio.h>

#include "array_utils.h"

int main(){

    int arr[128];

    randomize_array(arr, 128);

    int* print_ptr = &arr[9];

    print_array(print_ptr, 7);

    int sum = sum_array(arr, 128);
    float mean = mean_array(arr, 128);

    printf("Sum 0-127  = %d\n", sum);
    printf("Mean 0-127 = %f\n", mean);

    // First entry
    int* ptr0 = arr;
    // 33rd entry
    int* ptr32 = &arr[32];
    // 65th entry
    int* ptr64 = &arr[64];
    // 97th entry
    int* ptr96 = &arr[96];

    printf("Sum 0-31  = %d\n", sum_array(ptr0, 32));
    printf("Mean 0-31 = %f\n", mean_array(ptr0, 32));

    printf("Sum 32-63  = %d\n", sum_array(ptr32, 32));
    printf("Mean 32-63 = %f\n", mean_array(ptr32, 32));
    
    printf("Sum 64-95  = %d\n", sum_array(ptr64, 32));
    printf("Mean 64-95 = %f\n", mean_array(ptr64, 32));
    
    printf("Sum 96-127  = %d\n", sum_array(ptr96, 32));
    printf("Mean 96-127 = %f\n", mean_array(ptr96, 32));
    
    return 0;
}
