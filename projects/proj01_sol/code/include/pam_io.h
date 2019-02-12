#ifndef __PAM_IO_H__
#define __PAM_IO_H__

#include "image_types.h"

int load_pgm_image_8(char* filename, MImage8* image);

int save_pgm_image_8(char* filename, MImage8* image);

int load_ppm_image_8(char* filename, RGBImage8* image);

int save_ppm_image_8(char* filename, RGBImage8* image);


#endif