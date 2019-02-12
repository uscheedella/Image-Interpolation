#ifndef __IMAGE_CONVERT_H__
#define __IMAGE_CONVERT_H__

#include "image_types.h"

int convert_IntensityImage8_to_IntensityImageFloat(IntensityImage8* in, 
                                                   IntensityImageFloat* out);


int convert_IntensityImageFloat_to_IntensityImage8(IntensityImageFloat* in, 
                                                   IntensityImage8* out);

#endif
