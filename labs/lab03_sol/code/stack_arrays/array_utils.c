#include <stdlib.h>
#include <stdio.h>


#include "array_utils.h"

/* Places (pseudo) random numbers from 0-99 in arr */
void randomize_array(int* arr, int N){
    for(int i=0; i < N; i++) arr[i] = rand() % 100;
}


void print_array(int* arr, int N){
    for(int i=0; i < (N-1); i++)
        printf("%2d, ", arr[i]);
    printf("%2d\n", arr[N-1]);
}


int sum_array(int* arr, int N){
    int partial_sum = 0;

    for(int i=0; i < N; i++){
        partial_sum += arr[i];
    }
    
    return partial_sum;
}


float mean_array(int* arr, int N){
    return (float)sum_array(arr, N) / (float)N;
}

