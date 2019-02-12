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



#define PNG_DEBUG 3
#include <png.h>

#include "png_utilities.h"


void process_file(PNGImage* image)
{
    png_byte tmp;

    for (int y=0; y<image->height; y++) {
            png_byte* row = image->row_ptrs[y];
            for (int x=0; x<image->width; x++) {
                    png_byte* ptr = &(row[x*4]);
                    // printf("Pixel at position [ %d - %d ] has RGBA values: %d - %d - %d - %d\n",
                           // x, y, ptr[0], ptr[1], ptr[2], ptr[3]);

                    /* set red value to 0 and green value to the blue one */
                    ptr[0] = 0;
                    tmp = ptr[2];
                    ptr[2] = ptr[1];
                    ptr[1] = tmp;
            }
    }
}

void gradient(PNGImage* image)
{
    for (int y=0; y<image->height; y++) {
            png_byte* row = image->row_ptrs[y];
            for (int x=0; x<image->width; x++) {
                    png_byte* ptr = &(row[x*4]);
                    // Set red
                    ptr[0] = (255*y)/(image->height-1);
                    // Set green
                    ptr[1] = (255*x)/(image->width-1);
                    // Set blue
                    ptr[2] = 255 - (255*y)/(image->height-1);
                    // Set alpha
                    ptr[3] = 255;
                    // printf("Pixel at position [ %d - %d ] has RGBA values: %d - %d - %d - %d\n",
                           // x, y, ptr[0], ptr[1], ptr[2], ptr[3]);
            }
    }
}

int main(int argc, char **argv)
{
        if (argc != 4)
                abort_("Usage: program_name <file_in> <file_out>");

        PNGImage image;

        // read acts as an allocator
        read_png_file(&image, argv[1]);

        // Do the above transformations
        process_file(&image);

        // write the output and cleanup
        write_png_file(&image, argv[2]);
        deallocate_png_image(&image);

        allocate_png_image(&image, 100, 200);

        gradient(&image);

        write_png_file(&image, argv[3]);
        deallocate_png_image(&image);

        return 0;
}