/*
 * Authors:
 *   Russell J. Hewett (rhewett@vt.edu)
 *
 * Not licensed for external distribution.
 */

#include "image_convert.h"
#include <math.h>
#include <stddef.h>

/**
 * Converts MImage8 to MImageF by traversing through each pixel and dividing
 * each pixel's data by 255 to convert it to float.
 *
 **/
int convert_MImage8_to_MImageF(MImage8* eight, MImageF* f) {
    if((eight->height == f->height) && (eight->width == f->width)) {

        if (eight->data == NULL) {
            return 1;
        }
        int totpixels = eight->width * eight->height;
        for (int x = 0; x <= totpixels - 1; x++) {
            *(f->data + x) = (float)floor(*(eight->data + x) / 255.0);
        }
    }
    return 0;
}

/**
 * Converts MImageF to MImage8 by traversing through each pixel and multiplying
 * each pixel's data by 255 to convert it to a value between 0.0 and 1.0.
 *
 **/

int convert_MImageF_to_MImage8(MImageF* f, MImage8* eight) {
    if((f->width == eight->width) && (f->height == eight->height)) {
        if (f->data == NULL) {
            return 1;
        }
        int totpixels = f->width * f->height;
        for (int x = 0; x <= totpixels - 1; x++) {
            *(eight->data + x) = (unsigned char)floor(*(f->data + x) * 255);
        }
    }
    return 0;
}
