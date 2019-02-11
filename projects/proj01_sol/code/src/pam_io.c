#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "image_types.h"
#include "pam_io.h"


// Based on https://stackoverflow.com/questions/2693631/read-ppm-file-and-store-it-in-an-array-coded-with-c
// This is very fragile!
int load_pgm_image_8(char* filename, IntensityImage8* image) {

    FILE* f;
    char format[2];
    int color_depth;
    int n_pixels;

    // Open the file
    f = fopen(filename, "rb");
    if (f == NULL) {
        fprintf(stderr, "Error opening file %s for read.\n", filename);
        return 1;
    }

    // // Read format, width, height, color depth
    if(fscanf(f, "%c%c %d %d %d\n", &format[0], &format[1], &image->width, &image->height, &color_depth) != 5){
        fprintf(stderr, "Error opening file %s: malformed pgm file.\n", filename);
        return 1;
    }

    // Fail if wrong format
    if(format[0] != 'P' || format[1] != '5') {
        fprintf(stderr, "Error opening file %s: Incorrect file format %c%c, must be P5.\n", 
                filename, format[0], format[1]);
        return 1;
    }

    n_pixels = image->width*image->height;

    image->data = malloc(n_pixels*sizeof(unsigned char));

    if(fread(image->data, sizeof(unsigned char), n_pixels, f) != n_pixels){
        fprintf(stderr, "Error opening file %s: malformed pgm file.\n", filename);
        return 1;
    }

    fclose(f);

    return 0;
}

int save_pgm_image_8(char* filename, IntensityImage8* image) {

    FILE* f;
    int n_pixels;

    // Open the file
    f = fopen(filename, "wb");
    if (f == NULL) {
        fprintf(stderr, "Error opening file %s for write.\n", filename);
        return 1;
    }

    // Write the ppm header, max color depth = 255
    fprintf(f, "P5 %d %d %d\n", image->width, image->height, 255);

    n_pixels = image->width*image->height;

    // Write entire image at once, as it is planar format
    fwrite(image->data, sizeof(unsigned char), n_pixels, f);

    fclose(f);

    return 0;
}

// int load_ppm_image_8(char* filename, RGBImage8* image) {

//     return 0;

// }

int save_ppm_image_8(char* filename, RGBImage8* image) {

    FILE* f;
    int n_pixels;

    // Open the file
    f = fopen(filename, "wb");
    if (f == NULL) {
        fprintf(stderr, "Error opening file %s for write.\n", filename);
        return 1;
    }

    // Write the ppm header
    fprintf(f, "P6 %d %d %hu\n", image->width, image->height, 255);

    n_pixels = (image->width)*(image->height);

    // Write planar data in interleaved format
    for(int i=0; i < n_pixels; i++) {

        // Write pixel i: r, then g, then b, 1 record at a time
        fwrite(&image->data[0*n_pixels + i], sizeof(unsigned char), 1, f);
        fwrite(&image->data[1*n_pixels + i], sizeof(unsigned char), 1, f);
        fwrite(&image->data[2*n_pixels + i], sizeof(unsigned char), 1, f);
    }


    fclose(f);

    return 0;
}