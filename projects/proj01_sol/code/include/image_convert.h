/*
* Authors:
*   Russell J. Hewett (rhewett@vt.edu)
*
* Not licensed for external distribution.
*/

#ifndef __IMAGE_CONVERT_H__
#define __IMAGE_CONVERT_H__

#include "image_types.h"

int convert_MImage8_to_MImageF(MImage8* in, MImageF* out);

int convert_MImageF_to_MImage8(MImageF* in, MImage8* out);

#endif
