#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "image_types.h"
#include "image_memory.h"
#include "image_convert.h"

#include "pam_io.h"

int main(int argc, char **argv)
{
    int nx = 255;
    int ny = 1;
    float h = 1.0/(nx-1);

    MImage8 im1;
    MImageF im2;

    nullify_MImage8(&im1);
    allocate_MImage8(&im1, nx, ny);
    initialize_MImage8(&im1);

    nullify_MImageF(&im2);
    allocate_MImageF(&im2, nx, ny);
    initialize_MImageF(&im2);

    for(int i=0; i < nx; i++) 
        for(int j=0; j < ny; j++) 
            im2.data[j*nx + i] = 0 + i*h;

    convert_MImageF_to_MImage8(&im2, &im1);

    save_pgm_image_8("test.pgm", &im1);

    deallocate_MImage8(&im1);
    deallocate_MImage8(&im1);

    return 0;
}