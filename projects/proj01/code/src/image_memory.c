/*
* Authors:
*   Russell J. Hewett (rhewett@vt.edu)
*
* Not licensed for external distribution.
*/

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "image_types.h"
#include "image_memory.h"


/*
* Nullifies a single channel (intensity), 8-bit image struct.
*
* This should always be called after an instance is created.
* There is no mechanism to know if it points to anything, so
* care should be taken.
*
* Arguments:
*   image: pointer to the image to be nullified
*
* Returns:
*   error code: 0 on success
*/

int nullify_MImage8(MImage8* image)
{
    image->width = 0;
    image->height = 0;
    image->data = NULL;

    return 0;   
}


/*
* Allocates a single channel (intensity), 8-bit image struct.
*
* The allocated array is sized width*height.
*
* Arguments:
*   image: pointer to the image to be allocated
*   width: image width
*   height: image height
*
* Returns:
*   error code: 0 on success, 1 on failure
*/

int allocate_MImage8(MImage8* image, int width, int height)
{
    int n_pixels;

    image->width = width;
    image->height = height;

    n_pixels = width*height;

    image->data = malloc(n_pixels*sizeof(unsigned char));

    if(image->data == NULL){
        fprintf(stderr, "Error allocating image data.\n");
        return 1;
    }

    return 0;
}


/*
* Initlaizes a single channel (intensity), 8-bit image to 0.
*
* Arguments:
*   image: pointer to the image to be initialized
*
* Returns:
*   error code: 0 on success
*/

int initialize_MImage8(MImage8* image)
{
    int n_pixels = (image->width)*(image->height);

    memset(image->data, 0, n_pixels*sizeof(unsigned char));

    return 0;
}


/*
* Deallocates a single channel (intensity), 8-bit image.
*
* Arguments:
*   image: pointer to the image to be deallocated
*
* Returns:
*   error code: 0 on success
*/

int deallocate_MImage8(MImage8* image)
{
    image->width = 0;
    image->height = 0;

    free(image->data);

    image->data = NULL;

    return 0;
}
