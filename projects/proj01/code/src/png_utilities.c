/*
 * Portions of this file are copyright Guillaume Cottenceau
 * and redistributed freely under the X11 license.
 * 
 * Modifications by Russell J. Hewett are also licensed under the X11 license.
 *
 * http://zarb.org/~gc/html/libpng.html
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


void abort_(const char * s, ...)
{
        va_list args;
        va_start(args, s);
        vfprintf(stderr, s, args);
        fprintf(stderr, "\n");
        va_end(args);
        abort();
}

void allocate_png_image(PNGImage* image, int width, int height)
{

    int y;

    image->width = width;
    image->height = height;

    image->color_type = PNG_COLOR_TYPE_RGBA;
    image->bit_depth = 8;

    image->row_ptrs = (png_bytep*) malloc(sizeof(png_bytep) * image->height);

    for (y=0; y<image->height; y++)
            image->row_ptrs[y] = (png_byte*) malloc(sizeof(png_byte)*4*width);

}

void deallocate_png_image(PNGImage* image)
{
    int y;

    for (y=0; y<image->height; y++)
        free(image->row_ptrs[y]);
    free(image->row_ptrs);

    image->width = -1;
    image->height = -1;

    image->row_ptrs = NULL;

}


void read_png_file(PNGImage* image, char* file_name)
{
        int x;
        int y;
        char header[8];    // 8 is the maximum size that can be checked

        png_structp png_ptr;
        png_infop info_ptr;

        /* open file and test for it being a png */
        FILE *fp = fopen(file_name, "rb");
        if (!fp)
                abort_("[read_png_file] File %s could not be opened for reading", file_name);
        x = fread(header, 1, 8, fp);
        if (png_sig_cmp(header, 0, 8))
                abort_("[read_png_file] File %s is not recognized as a PNG file", file_name);


        /* initialize stuff */
        png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

        if (!(png_ptr))
                abort_("[read_png_file] png_create_read_struct failed");

        info_ptr = png_create_info_struct(png_ptr);
        if (!(info_ptr))
                abort_("[read_png_file] png_create_info_struct failed");

        if (setjmp(png_jmpbuf(png_ptr)))
                abort_("[read_png_file] Error during init_io");

        png_init_io(png_ptr, fp);
        png_set_sig_bytes(png_ptr, 8);

        png_read_info(png_ptr, info_ptr);

        image->width = png_get_image_width(png_ptr, info_ptr);
        image->height = png_get_image_height(png_ptr, info_ptr);
        image->color_type = png_get_color_type(png_ptr, info_ptr);
        image->bit_depth = png_get_bit_depth(png_ptr, info_ptr);

        if (png_get_color_type(png_ptr, info_ptr) == PNG_COLOR_TYPE_RGB)
                abort_("[process_file] input file is PNG_COLOR_TYPE_RGB but must be PNG_COLOR_TYPE_RGBA "
                       "(lacks the alpha channel)");

        if (png_get_color_type(png_ptr, info_ptr) != PNG_COLOR_TYPE_RGBA)
                abort_("[process_file] color_type of input file must be PNG_COLOR_TYPE_RGBA (%d) (is %d)",
                       PNG_COLOR_TYPE_RGBA, png_get_color_type(png_ptr, info_ptr));

        image->number_of_passes = png_set_interlace_handling(png_ptr);
        png_read_update_info(png_ptr, info_ptr);


        /* read file */
        if (setjmp(png_jmpbuf(png_ptr)))
                abort_("[read_png_file] Error during read_image");

        image->row_ptrs = (png_bytep*) malloc(sizeof(png_bytep) * image->height);
        for (y=0; y<image->height; y++)
                image->row_ptrs[y] = (png_byte*) malloc(png_get_rowbytes(png_ptr, info_ptr));

        png_read_image(png_ptr, image->row_ptrs);

        fclose(fp);
}


void write_png_file(PNGImage* image, char* file_name)
{
        int y;

        png_structp png_ptr;
        png_infop info_ptr;
        /* create file */
        FILE *fp = fopen(file_name, "wb");
        if (!fp)
                abort_("[write_png_file] File %s could not be opened for writing", file_name);


        /* initialize stuff */
        png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

        if (!png_ptr)
                abort_("[write_png_file] png_create_write_struct failed");

        info_ptr = png_create_info_struct(png_ptr);
        if (!info_ptr)
                abort_("[write_png_file] png_create_info_struct failed");

        if (setjmp(png_jmpbuf(png_ptr)))
                abort_("[write_png_file] Error during init_io");

        png_init_io(png_ptr, fp);


        /* write header */
        if (setjmp(png_jmpbuf(png_ptr)))
                abort_("[write_png_file] Error during writing header");

        png_set_IHDR(png_ptr, info_ptr, 
                     image->width, image->height,
                     image->bit_depth, 
                     image->color_type, 
                     PNG_INTERLACE_NONE,
                     PNG_COMPRESSION_TYPE_BASE, 
                     PNG_FILTER_TYPE_BASE);

        png_write_info(png_ptr, info_ptr);


        /* write bytes */
        if (setjmp(png_jmpbuf(png_ptr)))
                abort_("[write_png_file] Error during writing bytes");

        png_write_image(png_ptr, image->row_ptrs);


        /* end write */
        if (setjmp(png_jmpbuf(png_ptr)))
                abort_("[write_png_file] Error during end of write");

        png_write_end(png_ptr, NULL);

        /* cleanup heap allocation */
        // for (y=0; y<image->height; y++)
        //         free(image->row_ptrs[y]);
        // free(image->row_ptrs);

        fclose(fp);
}