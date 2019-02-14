/*
* Authors:
*   Russell J. Hewett (rhewett@vt.edu)
*
* Not licensed for external distribution.
*/

#ifndef __IMAGE_MEMORY_H__
#define __IMAGE_MEMORY_H__

#include "image_types.h"

int nullify_MImage8(MImage8* image);
int allocate_MImage8(MImage8* image, int width, int height);
int initialize_MImage8(MImage8* image);
int deallocate_MImage8(MImage8* image);

int nullify_MImageF(MImageF* image);
int allocate_MImageF(MImageF* image, int width, int height);
int initialize_MImageF(MImageF* image);
int deallocate_MImageF(MImageF* image);

#endif
