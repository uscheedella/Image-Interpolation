// http://zarb.org/~gc/html/libpng.html

/*
 * Copyright 2002-2010 Guillaume Cottenceau.
 *
 * This software may be freely redistributed under the terms
 * of the X11 license.
 *
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
        IntensityImage8 im1;
        IntensityImage8 im2;

        nullify_IntensityImage8(&im1);
        nullify_IntensityImage8(&im2);

        allocate_IntensityImage8(&im1, 255, 255);
        initialize_IntensityImage8(&im1);


        for(int i=0; i <255; i++) 
            for(int j=0; j <255; j++) 
                im1.data[j*255 + i] = i;

        save_pgm_image_8("test.pgm", &im1);

        load_pgm_image_8("test.pgm", &im2);

        save_pgm_image_8("test2.pgm", &im2);

        deallocate_IntensityImage8(&im1);
        deallocate_IntensityImage8(&im1);

        return 0;
}