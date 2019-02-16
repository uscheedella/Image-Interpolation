#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int sum_length = 5;
    int arr_length = 5*5;

    float *sum = (float *) malloc(sum_length*sizeof(float));
    float *arr = (float *) malloc(sum_length*sizeof(float));

    //seed array with random numbers
    srand48(0);
    
    for (int i = 0; i < arr_length; i++) {
	arr[i] = drand48();
    }

    //compute sum of each column and store to sum
    for (int i = 0; i < sum_length; i++) {
	sum[i] = 0;
	for (int j = 0; j < sum_length; j++) {
	    sum[i] += arr[j*sum_length+i];
	}
	printf("%f\n",sum[i]);
    }

    free(sum);
    free(arr);
    return 0;
}
 
