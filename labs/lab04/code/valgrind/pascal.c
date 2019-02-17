#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc,char **argv) {
    //depth of triangle
    int depth = 17;
    int spacing = 5;
    int spacing_start = 3;
    int length = depth*depth;

    //initial setup
    int *nums = (int *) malloc(length*sizeof(int));

    //set first row and column equal to 1
    for (int i = 0; i < depth; i++) {
        nums[i] = 1;
        nums[i*depth] = 1;
    }

    //compute entries in the center
    for (int i = 1; i < depth-1; i++) {
        for (int j = 1; j < depth - i; j++) {
            nums[i*depth + j] = nums[(i-1)*depth + j] + nums[i*depth + j - 1];
        }
    }

    //print diagonals of matrix
    for (int i = 0; i < depth; i++) {
        //spacing at the start
        for (int j = 0; j < spacing_start*(depth-i-1); j++) {
            printf(" ");
        }
        for (int j = 0; j <= i; j++) {
            int num_to_print = nums[j*depth + (i - j)];
            printf("%d ",num_to_print);
            for (int k = 0; k < spacing-log10(abs(num_to_print))-1; k++) {
                printf(" ");
            }
        }
        printf("\n");
    }
    free(nums);
    return 0;
}
