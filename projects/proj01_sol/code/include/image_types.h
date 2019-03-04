/*
* Authors:
*   Russell J. Hewett (rhewett@vt.edu)
*
* Not licensed for external distribution.
*/

#ifndef __IMAGE_TYPES_H__
#define __IMAGE_TYPES_H__

typedef struct intensity_image_float_def {
    float* data;

    int width;
    int height;
} MImageF;

typedef struct rgb_image_float_def {
    float* data;

    int width;
    int height;

    float* r_ptr;
    float* g_ptr;
    float* b_ptr;
} RGBImageFloat;


typedef struct intensity_image_8_def {
    unsigned char* data;

    int width;
    int height;
} MImage8;

typedef struct rgb_image_8_def {
    unsigned char* data;

    int width;
    int height;

    unsigned char* r_ptr;
    unsigned char* g_ptr;
    unsigned char* b_ptr;
} RGBImage8;


typedef struct intensity_image_16_def {
    unsigned short int* data;

    int width;
    int height;
} IntensityImage16;

typedef struct rgb_image_16_def {
    unsigned short int* data;

    int width;
    int height;

    unsigned short int* r_ptr;
    unsigned short int* g_ptr;
    unsigned short int* b_ptr;
} RGBImage16;




#endif