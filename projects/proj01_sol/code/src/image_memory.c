/*
* Authors:
*   Russell J. Hewett (rhewett@vt.edu)
*
* Not licensed for external distribution.
*/

#include <stddef.h>
#include <stdlib.h>
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

    for(int i=0;i<n_pixels;i++)
        image->data[i] = 0;

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




/*
* Nullifies a single channel (intensity), float image struct.
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

int nullify_MImageF(MImageF* image)
{
    image->width = 0;
    image->height = 0;
    image->data = NULL;

    return 0;   
}


/*
* Allocates a single channel (intensity), float image struct.
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

int allocate_MImageF(MImageF* image, int width, int height)
{
    int n_pixels;

    image->width = width;
    image->height = height;

    n_pixels = width*height;

    image->data = malloc(n_pixels*sizeof(float));

    if(image->data == NULL){
        fprintf(stderr, "Error allocating image data.\n");
        return 1;
    }

    return 0;
}


/*
* Initlaizes a single channel (intensity), float image to 0.
*
* Arguments:
*   image: pointer to the image to be initialized
*
* Returns:
*   error code: 0 on success
*/

int initialize_MImageF(MImageF* image)
{
    int n_pixels = (image->width)*(image->height);

    for(int i=0;i<n_pixels;i++)
        image->data[i] = 0.0;

    return 0;
}


/*
* Deallocates a single channel (intensity), float image.
*
* Arguments:
*   image: pointer to the image to be deallocated
*
* Returns:
*   error code: 0 on success
*/

int deallocate_MImageF(MImageF* image)
{
    image->width = 0;
    image->height = 0;

    free(image->data);

    image->data = NULL;

    return 0;
}
