/*
* Authors:
*   Russell J. Hewett (rhewett@vt.edu)
*
* Not licensed for external distribution.
*/

#ifndef __IMAGE_CROP_H__
#define __IMAGE_CROP_H__

#include "image_types.h"

int crop_linear(float a_hat, float b_hat, float c_hat, float d_hat, 
	            MImageF* in, MImageF* out);

#endif