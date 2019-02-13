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

#include "image_types.h"
#include "image_memory.h"
#include "image_convert.h"

#include "pam_io.h"

int main(int argc, char **argv)
{
    int vert_width = 30;
    int vert_height = 120;
    int n_verts = 24;
    int stripe_width = 960;
    int stripe_height = 40;
    int n_stripes = 4;

    int nx = vert_width*n_verts;
    int ny = 2*vert_height + stripe_height*n_stripes;

    MImage8 im1;

    unsigned char Kv = 256/n_verts;
    unsigned char Ks = 256/n_stripes;

    nullify_MImage8(&im1);
    allocate_MImage8(&im1, nx, ny);
    initialize_MImage8(&im1);

    int idx;
    int base_row, end_row;

    base_row = 0;
    end_row = base_row + vert_height;
    for(int c=0; c<n_verts; c++){
        for(int j=base_row; j<end_row; j++){
            for(int i=c*vert_width; i<(c+1)*vert_width; i++){
                idx = j*nx + i;
                im1.data[idx] = c*Kv;
            }
        }
    }

    for(int c=0; c<n_stripes; c++){
        base_row = vert_height + c*(stripe_height);
        end_row = base_row + (c+1)*stripe_height;
        for(int j=base_row; j<(end_row); j++){
            for(int i=0; i<nx; i++){
                idx = j*nx + i;
                im1.data[idx] = c*Ks;
            }
        }
    }

    base_row = vert_height + n_stripes*stripe_height;
    end_row = base_row + vert_height;
    for(int c=0; c<n_verts; c++){
        for(int j=base_row; j<end_row; j++){
            for(int i=c*vert_width; i<(c+1)*vert_width; i++){
                idx = j*nx + i;
                im1.data[idx] = (n_verts-c-1)*Kv;
            }
        }
    }

    save_pgm_MImage8("graytable.pgm", &im1);

    deallocate_MImage8(&im1);

    return 0;
}