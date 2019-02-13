#include <stdio.h>

#include "image_types.h"

#include "python_utilities.h"


/*
* Write the numpy import statement to a file.
*/

void print_numpy_header(FILE* outfile){
    fprintf(outfile, "import numpy as np\n\n");
}


/*
* Write a float image to a numpy array named "name".
*/

void print_numpy_array_MImageF(FILE* outfile, char* name, MImageF* im){

    int i, j;
    int nx = im->width;
    int ny = im->height;

    fprintf(outfile, "%s = np.array([", name);

    for(j=0; j < ny-1; j++){
        fprintf(outfile, "[ ");

        for(i=0; i < nx-1; i++){
            fprintf(outfile, "%f, ", im->data[j*nx + i]);
        }
        fprintf(outfile, "%f ", im->data[j*nx + i]);
        fprintf(outfile, "],  ");
    }
    fprintf(outfile, " [ ");

    for(i=0; i < nx-1; i++){
        fprintf(outfile, "%f, ", im->data[j*nx + i]);
    }
    fprintf(outfile, "%f ", im->data[j*nx + i]);
    fprintf(outfile, "] ");

    fprintf(outfile, "] )\n\n");
}


/*
* Write a unsigned char image to a numpy array named "name".
*/

void print_numpy_array_MImage8(FILE* outfile, char* name, MImage8* im){

    int i, j;
    int nx = im->width;
    int ny = im->height;

    fprintf(outfile, "%s = np.array([", name);

    for(j=0; j < ny-1; j++){
        fprintf(outfile, "[ ");

        for(i=0; i < nx-1; i++){
            fprintf(outfile, "%hhu, ", im->data[j*nx + i]);
        }
        fprintf(outfile, "%hhu ", im->data[j*nx + i]);
        fprintf(outfile, "],  ");
    }
    fprintf(outfile, " [ ");

    for(i=0; i < nx-1; i++){
        fprintf(outfile, "%hhu, ", im->data[j*nx + i]);
    }
    fprintf(outfile, "%hhu ", im->data[j*nx + i]);
    fprintf(outfile, "] ");

    fprintf(outfile, "] )\n\n");
}
