#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include <math.h>

#include "image_types.h"
#include "image_memory.h"
#include "image_convert.h"
#include "image_crop.h"

#include "pam_io.h"
#include "python_utilities.h"


int test_crop_linear(){
    int nx = 5;
    int ny = 5;

    int nx_crop = 16;
    int ny_crop = 24;

    MImageF in;
    MImageF crop;
    MImage8 out;

    float max_value;

    nullify_MImageF(&in);
    allocate_MImageF(&in, nx, ny);
    initialize_MImageF(&in);
    
    float hx = 1.0/(nx-1);
    float hy = 1.0/(ny-1);

    max_value = -1.0;
    for(int j=0; j < ny; j++){
        for(int i=0; i < nx; i++){
            in.data[j*nx + i] = 0 + pow(i*hx,2.0) + pow(j*hy,2.0);
            max_value = fmax(max_value, in.data[j*nx + i]);
        }
    }

    for(int j=0; j < ny; j++)
        for(int i=0; i < nx; i++)
            in.data[j*nx + i] /= max_value;

    nullify_MImageF(&crop);
    allocate_MImageF(&crop, nx_crop, ny_crop);
    initialize_MImageF(&crop);

    crop_linear(0.0, 0.7, 0.7, 0.9, &in, &crop);

    print_numpy_array_MImageF(stdout, "crop_in", &in);
    print_numpy_array_MImageF(stdout, "crop_out", &crop);

    nullify_MImage8(&out);
    allocate_MImage8(&out, nx_crop, ny_crop);
    initialize_MImage8(&out);

    convert_MImageF_to_MImage8(&crop, &out);
    
    save_pgm_MImage8("2d_crop.pgm", &out);

    deallocate_MImageF(&in);
    deallocate_MImageF(&crop);
    deallocate_MImage8(&out);

    return 0;
}

int main(int argc, char **argv)
{
    print_numpy_header(stdout);

    test_crop_linear();

    return 0;
}