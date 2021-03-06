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

#include "pam_io.h"

int main(int argc, char **argv)
{
    MImage8 im1;
    MImage8 im2;

    nullify_MImage8(&im1);
    nullify_MImage8(&im2);

    allocate_MImage8(&im1, 255, 255);
    initialize_MImage8(&im1);


    for(int i=0; i <255; i++) 
        for(int j=0; j <255; j++) 
            im1.data[j*255 + i] = i;

    save_pgm_MImage8("test.pgm", &im1);

    load_pgm_MImage8("test.pgm", &im2);

    save_pgm_MImage8("test2.pgm", &im2);

    deallocate_MImage8(&im1);
    deallocate_MImage8(&im1);

    return 0;
}