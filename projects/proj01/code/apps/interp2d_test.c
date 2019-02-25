/*
* Authors:
*   Russell J. Hewett (rhewett@vt.edu)
*
* Not licensed for external distribution.
*/

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
#include "image_interp_2d.h"

#include "pam_io.h"
#include "python_utilities.h"


int test_convert_F_to_M(){
    int nx = 16;
    int ny = 16;

    MImageF in;
    MImage8 out;

    float max_value;

    nullify_MImageF(&in);
    allocate_MImageF(&in, nx, ny);
    initialize_MImageF(&in);
    
    float hx = 1.0/(nx-1);
    float hy = 1.0/(ny-1);

    max_value = -1.0;
    for(int i=0; i < nx; i++){
        for(int j=0; j < ny; j++){
            in.data[j*nx + i] = 0 + i*hx + j*hy;
            max_value = fmax(max_value, in.data[j*nx + i]);
        }
    }

    for(int i=0; i < nx; i++) 
        for(int j=0; j < ny; j++) 
            in.data[j*nx + i] /= max_value;

    nullify_MImage8(&out);
    allocate_MImage8(&out, nx, ny);
    initialize_MImage8(&out);

    convert_MImageF_to_MImage8(&in, &out);

    print_numpy_array_MImageF(stdout, "float_arr", &in);
    print_numpy_array_MImage8(stdout, "char_arr", &out);
    
    save_pgm_MImage8("float_to_monochrome_2d.pgm", &out);

    deallocate_MImageF(&in);
    deallocate_MImage8(&out);

    return 0;
}


int test_downsample(){
    int nx = 33;
    int ny = 33;

    int nx_down, Cx, Kx;
    int ny_down, Cy, Ky;

    MImageF in;
    MImageF down;
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
            in.data[j*nx + i] = 0 + i*hx + j*hy;
            max_value = fmax(max_value, in.data[j*nx + i]);
        }
    }

    for(int j=0; j < ny; j++)
        for(int i=0; i < nx; i++)
            in.data[j*nx + i] /= max_value;

    Cx = 1;
    Kx = 3;
    Cy = 0;
    Ky = 2;

    nx_down = compute_downsample_size(nx, Cx, Kx);
    ny_down = compute_downsample_size(ny, Cy, Ky);

    nullify_MImageF(&down);
    allocate_MImageF(&down, nx_down, ny_down);
    initialize_MImageF(&down);

    interp2d_downsample(Cx, Kx, Cy, Ky, &in, &down);

    print_numpy_array_MImageF(stdout, "downsample_in", &in);
    print_numpy_array_MImageF(stdout, "downsample_out", &down);

    nullify_MImage8(&out);
    allocate_MImage8(&out, nx_down, ny_down);
    initialize_MImage8(&out);

    convert_MImageF_to_MImage8(&down, &out);
    
    save_pgm_MImage8("2d_downsample.pgm", &out);

    deallocate_MImageF(&in);
    deallocate_MImageF(&down);
    deallocate_MImage8(&out);

    return 0;
}


int test_nearest(){
    int nx = 5;
    int ny = 5;

    int nx_nearest = 13;
    int ny_nearest = 21;

    MImageF in;
    MImageF nearest;
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
            in.data[j*nx + i] = 0 + i*hx + j*hy;
            max_value = fmax(max_value, in.data[j*nx + i]);
        }
    }

    for(int j=0; j < ny; j++)
        for(int i=0; i < nx; i++)
            in.data[j*nx + i] /= max_value;

    nullify_MImageF(&nearest);
    allocate_MImageF(&nearest, nx_nearest, ny_nearest);
    initialize_MImageF(&nearest);

    interp2d_nearest(&in, &nearest);

    print_numpy_array_MImageF(stdout, "nearest_in", &in);
    print_numpy_array_MImageF(stdout, "nearest_out", &nearest);

    nullify_MImage8(&out);
    allocate_MImage8(&out, nx_nearest, ny_nearest);
    initialize_MImage8(&out);

    convert_MImageF_to_MImage8(&nearest, &out);
    
    save_pgm_MImage8("2d_nearest.pgm", &out);

    deallocate_MImageF(&in);
    deallocate_MImageF(&nearest);
    deallocate_MImage8(&out);

    return 0;
}


int test_linear(){
    int nx = 5;
    int ny = 5;

    int nx_linear = 16;
    int ny_linear = 24;

    MImageF in;
    MImageF linear;
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

     nullify_MImageF(&linear);
     allocate_MImageF(&linear, nx_linear, ny_linear);
     initialize_MImageF(&linear);

     interp2d_linear(&in, &linear);

     print_numpy_array_MImageF(stdout, "linear_in", &in);
     print_numpy_array_MImageF(stdout, "linear_out", &linear);

     nullify_MImage8(&out);
     allocate_MImage8(&out, nx_linear, ny_linear);
     initialize_MImage8(&out);

     convert_MImageF_to_MImage8(&linear, &out);
    
     save_pgm_MImage8("2d_linear.pgm", &out);

     deallocate_MImageF(&in);
     deallocate_MImageF(&linear);
     deallocate_MImage8(&out);

    return 0;
}


int test_cubic(){
    int nx = 5;
    int ny = 5;

    int nx_cubic = 16;
    int ny_cubic = 24;

    MImageF in;
    MImageF cubic;
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

     nullify_MImageF(&cubic);
     allocate_MImageF(&cubic, nx_cubic, ny_cubic);
     initialize_MImageF(&cubic);

     interp2d_cubic(&in, &cubic);

     print_numpy_array_MImageF(stdout, "cubic_in", &in);
     print_numpy_array_MImageF(stdout, "cubic_out", &cubic);

     nullify_MImage8(&out);
     allocate_MImage8(&out, nx_cubic, ny_cubic);
     initialize_MImage8(&out);

     convert_MImageF_to_MImage8(&cubic, &out);
    
     save_pgm_MImage8("2d_cubic.pgm", &out);

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
