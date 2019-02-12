#ifndef __IMAGE_CONVERT_H__
#define __IMAGE_CONVERT_H__

#include "image_types.h"

int convert_MImage8_to_IntensityImageFloat(MImage8* in, 
                                                   IntensityImageFloat* out);


int convert_IntensityImageFloat_to_MImage8(IntensityImageFloat* in, 
                                                   MImage8* out);

#endif
