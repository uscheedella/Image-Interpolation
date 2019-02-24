/*
* Authors:
*   Russell J. Hewett (rhewett@vt.edu)
*
* Not licensed for external distribution.
*/

#include "image_utilities.h"
#include <math.h>

//NOT SURE ABOUT THIS
int compute_downsample_size(int N, int C, int K) {
    return ceil((N-C)/K);
}


