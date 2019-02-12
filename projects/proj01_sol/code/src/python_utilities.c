#include <stdio.h>

#include "python_utilities.h"

void print_numpy_header(FILE* outfile){
    fprintf(outfile, "import numpy as np\n\n");
}

void print_numpy_float_array(FILE* outfile, char* name, int N, float* arr){
    fprintf(outfile, "%s = np.array([ ", name);
    for(int i = 0; i < N-1; i++)
        fprintf(outfile, "%f, ", arr[i]);
    fprintf(outfile, "%f ])\n\n", arr[N-1]);
}

void print_numpy_char_array(FILE* outfile, char* name, int N, unsigned char* arr){
    fprintf(outfile, "%s = np.array([ ", name);
    for(int i = 0; i < N-1; i++)
        fprintf(outfile, "%hhu, ", arr[i]);
    fprintf(outfile, "%hhu ])\n\n", arr[N-1]);
}