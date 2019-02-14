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

typedef struct intensity_image_8_def {
	unsigned char* data;

	int width;
	int height;
} MImage8;


#endif