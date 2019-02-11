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

#include "pam_io.h"

int main(int argc, char **argv)
{
        // if (argc != 3)
        //         abort_("Usage: program_name <file_in> <file_out>");

        // PNGImage image;

        // // read acts as an allocator
        // read_png_file(&image, argv[1]);

        // // Do the above transformations
        // process_file(&image);

        // // write the output and cleanup
        // write_png_file(&image, argv[2]);
        // deallocate_png_image(&image);

        // allocate_png_image(&image, 100, 200);

        // gradient(&image);

        // write_png_file(&image, argv[3]);
        // deallocate_png_image(&image);

        IntensityImage8 im1;
        IntensityImage8 im2;

        im1.data = malloc(255*255*sizeof(unsigned short int));

        im1.width = 255;
        im1.height = 255;

        for(int i=0; i <255; i++) 
            for(int j=0; j <255; j++) 
                im1.data[j*255 + i] = i;

        save_pgm_image_8("test.pgm", &im1);

        load_pgm_image_8("test.pgm", &im2);

        save_pgm_image_8("test2.pgm", &im2);


        free(im1.data);
        // free(im2.data);

        return 0;
}