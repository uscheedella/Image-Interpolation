#include <stdlib.h>
#include <stdio.h>
#include <array_utils.h>

/* Places (pseudo) random numbers from 0-99 in arr */
void randomize_array(int* arr, int N){
    for(int i=0; i < N; i++) arr[i] = rand() % 100;
}

void print_array(int* arr, int N) {
	for (int x=0; x < N; x++) {
		printf("%d, ", arr[x]);
	}
}

int sum_array(int* arr, int N) {
	float sum = 0;
	for (int x=0; x<N; x++) {
		sum  = sum + *(arr+x);
		
	}
	return sum;
}

float mean_array(int* arr, int N) {
	float sum = sum_array(arr, N);
	float mean = sum/N;
	return mean;
}
	









