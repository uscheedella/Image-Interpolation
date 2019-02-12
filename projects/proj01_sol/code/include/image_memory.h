#ifndef __IMAGE_MEMORY_H__
#define __IMAGE_MEMORY_H__

#include "image_types.h"

int nullify_MImage8(MImage8* image);
int allocate_MImage8(MImage8* image, int width, int height);
int initialize_MImage8(MImage8* image);
int deallocate_MImage8(MImage8* image);

// int nullify_RGBImage8(RGBImage8* image);
// int allocate_RGBImage8(RGBImage8* image, int width, int height);
// int deallocate_RGBImage8(RGBImage8* image);

// int nullify_IntensityImage16(IntensityImage16* image);
// int allocate_IntensityImage16(IntensityImage16* image, int width, int height);
// int deallocate_IntensityImage16(IntensityImage16* image);

// int nullify_RGBImage16(RGBImage16* image);
// int allocate_RGBImage16(RGBImage16* image, int width, int height);
// int deallocate_RGBImage16(RGBImage16* image);

int nullify_IntensityImageFloat(IntensityImageFloat* image);
int allocate_IntensityImageFloat(IntensityImageFloat* image, int width, int height);
int initialize_IntensityImageFloat(IntensityImageFloat* image);
int deallocate_IntensityImageFloat(IntensityImageFloat* image);

// int nullify_RGBImageFloat(RGBImageFloat* image);
// int allocate_RGBImageFloat(RGBImageFloat* image, int width, int height);
// int deallocate_RGBImageFloat(RGBImageFloat* image);

#endif
