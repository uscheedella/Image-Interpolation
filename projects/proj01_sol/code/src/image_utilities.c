#include <math.h>

#include "image_utilities.h"

int compute_downsample_size(int N, int C, int K)
{
    return (int)ceil( (float)(N-C) / (float)K);
}