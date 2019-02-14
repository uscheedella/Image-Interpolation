#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv) {
    //initialize variables
    int array_size = 30;
    int *nums = (int *) malloc(array_size);
    
    //seed with first two values
    nums[0] = 1;
    nums[1] = 1;

    //calculate and print remaining values
    for (int i = 2; i<array_size; i++) {
	nums[i] = nums[i-2] + nums[i-1];
    }

    /*printf("the first %d fibonacci numbers are:\n",array_size);
    for (int i = 0; i < array_size; i++) {
	printf("%d: %d\n",i,nums[i]);
	}*/

    //free memory and exit
    free(nums);
    return 0;
}
