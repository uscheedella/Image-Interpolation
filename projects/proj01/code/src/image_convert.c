/*
* Authors:
*   Russell J. Hewett (rhewett@vt.edu)
*
* Not licensed for external distribution.
*/

#include "image_convert.h"
#include <math.h>

int convert_MImage8_to_MImageF(MImage8* eight, MImageF* f) {
    if (eight->data == NULL) {
        return 1;
    }
    float f->data = eight->data/255;
    f->width = eight->width;
    f->height = eight->height;
    return 0;
}

int convert_MImageF_to_MImage8(MImageF* f, MImage8* eight) {
    if (f->data == NULL) {
        return 1;
    }
    unsigned char eight-> = floor(f->data*255);
    eight->width = f->width;
    eight->height = f->height;
    return 0;
}
