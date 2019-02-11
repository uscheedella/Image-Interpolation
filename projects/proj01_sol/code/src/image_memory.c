#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#include "image_types.h"
#include "image_memory.h"

int nullify_IntensityImage8(IntensityImage8* image)
{
    image->width = 0;
    image->height = 0;
    image->data = NULL;

    return 0;   
}

int allocate_IntensityImage8(IntensityImage8* image, int width, int height)
{
    int n_pixels;

    image->width = width;
    image->height = height;

    n_pixels = width*height;

    image->data = malloc(n_pixels*sizeof(unsigned char));

    if(image->data == NULL){
        fprintf(stderr, "Error allocating image data.\n");
        return 1;
    }

    return 0;
}


int deallocate_IntensityImage8(IntensityImage8* image)
{
    image->width = 0;
    image->height = 0;

    free(image->data);

    image->data = NULL;

    return 0;
}


