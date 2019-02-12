#include <stdio.h>

#include <math.h>

#include "image_types.h"
#include "image_convert.h"


/*
* Converts a single channel image from 8-bit int to float.
*
* Arguments:
*   in: input image pointer
*   out: output image pointer
*
* Returns:
*   error code: 0 on success, 1 on failure
*/

int convert_MImage8_to_MImageF(MImage8* in, MImageF* out){

    int n_pixels;

    if(in->data == NULL){
        fprintf(stderr, "Input image null.\n");
        return 1;
    }

    if(out->data == NULL){
        fprintf(stderr, "Output image null.\n");
        return 1;
    }

    if(in->width != out->width){
        fprintf(stderr, "Width mismatch.\n");
        return 1;
    }

    if(in->width != out->width){
        fprintf(stderr, "Height mismatch.\n");
        return 1;
    }

    n_pixels = (in->width)*(in->height);

    for(int i=0; i< n_pixels; i++){
        out->data[i] = (float)in->data[i]/255.0;
    }

    return 0;
}


/*
* Converts a single channel image from float to 8-bit int.
*
* Arguments:
*   in: input image pointer
*   out: output image pointer
*
* Returns:
*   error code: 0 on success, 1 on failure
*/

int convert_MImageF_to_MImage8(MImageF* in, MImage8* out){

    int n_pixels;
    float temp;

    if(in->data == NULL){
        fprintf(stderr, "Input image null.\n");
        return 1;
    }

    if(out->data == NULL){
        fprintf(stderr, "Output image null.\n");
        return 1;
    }

    if(in->width != out->width){
        fprintf(stderr, "Width mismatch.\n");
        return 1;
    }

    if(in->width != out->width){
        fprintf(stderr, "Height mismatch.\n");
        return 1;
    }

    n_pixels = (in->width)*(in->height);

    for(int i=0; i< n_pixels; i++){
        temp = (float)in->data[i];
        temp = fmax(temp, 0.0);
        temp = fmin(temp, 1.0);
        out->data[i] = (int)floor(255.0*temp);
    }

    return 0;
}