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

    return 0;
}
