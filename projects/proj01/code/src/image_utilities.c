/*
* Authors:
*   Russell J. Hewett (rhewett@vt.edu)
*
* Not licensed for external distribution.
*/

#include "image_utilities.h"
#include <math.h>

int compute_downsample_size(int N, int C, int K) {
    if (N==0 || K==0) {
        return 1;
    }
    
    int res = (int)ceil((N-C)/K);

    return res;
}


