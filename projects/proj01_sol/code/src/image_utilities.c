#include <math.h>

#include "image_utilities.h"

/*
* Computes the length of a downsampled image, given offset and skip.
*
* Arguments:
*   N: length in pixels of the starting image
*   C: starting offset of the downsample
*   K: skip length
*
* Returns:
*   downsampled length
*/

int compute_downsample_size(int N, int C, int K)
{
    return (int)ceil( (float)(N-C) / (float)K);
}