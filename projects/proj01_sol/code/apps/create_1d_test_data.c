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

        IntensityImage8 im1;
        IntensityImageFloat im2;

        nullify_IntensityImage8(&im1);
        allocate_IntensityImage8(&im1, nx, ny);
        initialize_IntensityImage8(&im1);

        nullify_IntensityImageFloat(&im2);
        allocate_IntensityImageFloat(&im2, nx, ny);
        initialize_IntensityImageFloat(&im2);

        for(int i=0; i < nx; i++) 
            for(int j=0; j < ny; j++) 
                im2.data[j*nx + i] = 0 + i*h;

        convert_IntensityImageFloat_to_IntensityImage8(&im2, &im1);

        save_pgm_image_8("test.pgm", &im1);

        deallocate_IntensityImage8(&im1);
        deallocate_IntensityImage8(&im1);

        return 0;
}