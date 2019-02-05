#include <stdio.h>

#include "array_utils.h"

int main(){

    int arr[128];

    randomize_array(arr, 128);

    int* print_ptr = &arr[9];

    print_array(print_ptr, 7);

    return 0;
}
