#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include <math.h>

#include "image_types.h"
#include "image_memory.h"
#include "image_convert.h"
#include "image_utilities.h"
#include "image_interp_1d.h"

#include "pam_io.h"
#include "python_utilities.h"


int test_convert_F_to_M(){
    int nx = 256;
    int ny = 1;

    MImageF in;
    MImage8 out;

    nullify_MImageF(&in);
    allocate_MImageF(&in, nx, ny);
    initialize_MImageF(&in);
    
    float h = 1.0/(nx-1);

    for(int i=0; i < nx; i++) 
        for(int j=0; j < ny; j++) 
            in.data[j*nx + i] = 0 + i*h;

    nullify_MImage8(&out);
    allocate_MImage8(&out, nx, ny);
    initialize_MImage8(&out);

    convert_MImageF_to_MImage8(&in, &out);

    print_numpy_array_MImageF(stdout, "float_arr", &in);
    print_numpy_array_MImage8(stdout, "char_arr", &out);
    
    save_pgm_image_8("float_to_monochrome.pgm", &out);

    deallocate_MImageF(&in);
    deallocate_MImage8(&out);

    return 0;
}


int test_downsample(){
    int nx = 128;
    int ny = 1;

    int nx_down, C, K;

    MImageF in;
    MImageF down;
    MImage8 out;

    nullify_MImageF(&in);
    allocate_MImageF(&in, nx, ny);
    initialize_MImageF(&in);
    
    float h = 1.0/(nx-1);

    for(int i=0; i < nx; i++) 
        for(int j=0; j < ny; j++) 
            in.data[j*nx + i] = 0 + i*h;

    C = 1;
    K = 2;
    nx_down = compute_downsample_size(nx, C, K);

    nullify_MImageF(&down);
    allocate_MImageF(&down, nx_down, ny);
    initialize_MImageF(&down);

    interp1d_downsample(C, K, &in, &down);

    print_numpy_array_MImageF(stdout, "downsample_in", &in);
    print_numpy_array_MImageF(stdout, "downsample_out", &down);

    nullify_MImage8(&out);
    allocate_MImage8(&out, nx_down, ny);
    initialize_MImage8(&out);

    convert_MImageF_to_MImage8(&down, &out);
    
    save_pgm_image_8("1d_downsample.pgm", &out);

    deallocate_MImageF(&in);
    deallocate_MImageF(&down);
    deallocate_MImage8(&out);

    return 0;
}


int test_nearest(){
    int nx = 129;
    int ny = 1;

    int nx_nearest = 257;

    MImageF in;
    MImageF nearest;
    MImage8 out;

    nullify_MImageF(&in);
    allocate_MImageF(&in, nx, ny);
    initialize_MImageF(&in);
    
    float h = 1.0/(nx-1);

    for(int i=0; i < nx; i++) 
        for(int j=0; j < ny; j++) 
            in.data[j*nx + i] = 0 + i*h;

    nullify_MImageF(&nearest);
    allocate_MImageF(&nearest, nx_nearest, ny);
    initialize_MImageF(&nearest);

    interp1d_nearest(&in, &nearest);

    print_numpy_array_MImageF(stdout, "nearest_in", &in);
    print_numpy_array_MImageF(stdout, "nearest_out", &nearest);

    nullify_MImage8(&out);
    allocate_MImage8(&out, nx_nearest, ny);
    initialize_MImage8(&out);

    convert_MImageF_to_MImage8(&nearest, &out);
    
    save_pgm_image_8("1d_nearest.pgm", &out);

    deallocate_MImageF(&in);
    deallocate_MImageF(&nearest);
    deallocate_MImage8(&out);

    return 0;
}


int test_linear(){
    int nx = 129;
    int ny = 1;

    int nx_linear = 257;

    MImageF in;
    MImageF linear;
    MImage8 out;

    nullify_MImageF(&in);
    allocate_MImageF(&in, nx, ny);
    initialize_MImageF(&in);
    
    float h = 1.0/(nx-1);

    for(int i=0; i < nx; i++) 
        for(int j=0; j < ny; j++) 
            in.data[j*nx + i] = 0 + pow(i*h, 3.0);

    nullify_MImageF(&linear);
    allocate_MImageF(&linear, nx_linear, ny);
    initialize_MImageF(&linear);

    interp1d_linear(&in, &linear);

    print_numpy_array_MImageF(stdout, "linear_in", &in);
    print_numpy_array_MImageF(stdout, "linear_out", &linear);

    nullify_MImage8(&out);
    allocate_MImage8(&out, nx_linear, ny);
    initialize_MImage8(&out);

    convert_MImageF_to_MImage8(&linear, &out);
    
    save_pgm_image_8("1d_linear.pgm", &out);

    deallocate_MImageF(&in);
    deallocate_MImageF(&linear);
    deallocate_MImage8(&out);

    return 0;
}

int test_cubic(){
    int nx = 127;
    int ny = 1;

    int nx_cubic = 257;

    MImageF in;
    MImageF cubic;
    MImage8 out;

    nullify_MImageF(&in);
    allocate_MImageF(&in, nx, ny);
    initialize_MImageF(&in);
    
    float h = 1.0/(nx-1);

    for(int i=0; i < nx; i++) 
        for(int j=0; j < ny; j++) 
            in.data[j*nx + i] = 0 + pow(i*h, 3.0);

    nullify_MImageF(&cubic);
    allocate_MImageF(&cubic, nx_cubic, ny);
    initialize_MImageF(&cubic);

    interp1d_cubic(&in, &cubic);

    print_numpy_array_MImageF(stdout, "cubic_in", &in);
    print_numpy_array_MImageF(stdout, "cubic_out", &cubic);

    nullify_MImage8(&out);
    allocate_MImage8(&out, nx_cubic, ny);
    initialize_MImage8(&out);

    convert_MImageF_to_MImage8(&cubic, &out);
    
    save_pgm_image_8("1d_cubic.pgm", &out);

    deallocate_MImageF(&in);
    deallocate_MImageF(&cubic);
    deallocate_MImage8(&out);

    return 0;
}


int main(int argc, char **argv)
{
    print_numpy_header(stdout);

    test_convert_F_to_M();

    test_downsample();

    test_nearest();

    test_linear();

    test_cubic();

    return 0;
}