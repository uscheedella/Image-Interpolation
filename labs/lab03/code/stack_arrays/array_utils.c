#include <stdlib.h>

#include "array_utils.h"

/* Places (pseudo) random numbers from 0-99 in arr */
void randomize_array(int* arr, int N){
    for(int i=0; i < N; i++) arr[i] = rand() % 100;
}

