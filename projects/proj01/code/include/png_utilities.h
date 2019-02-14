/*
 * Portions of this file are copyright Guillaume Cottenceau
 * and redistributed freely under the X11 license.  
 * 
 * Modifications by Russell J. Hewett are also licensed under the X11 license.
 *
 * http://zarb.org/~gc/html/libpng.html
 */

#ifndef __PNG_UTILITIES_H__
#define __PNG_UTILITIES_H__

typedef struct png_image_def {

    // Image height and width
    int width;
    int height;
    
    // Image color type (RGB, RGBA)
    png_byte color_type;

    // ???
    png_byte bit_depth;

    int number_of_passes;

    png_bytep* row_ptrs;

} PNGImage;

void abort_(const char * s, ...);

void allocate_png_image(PNGImage* image, int width, int height);

void deallocate_png_image(PNGImage* image);

void read_png_file(PNGImage* image, char* file_name);

void write_png_file(PNGImage* image, char* file_name);

#endif