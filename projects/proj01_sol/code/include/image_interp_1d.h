/*
* Authors:
*   Russell J. Hewett (rhewett@vt.edu)
*
* Not licensed for external distribution.
*/

#ifndef __IMAGE_INTERP_1D_H__
#define __IMAGE_INTERP_1D_H__

int interp1d_downsample(int C, int K, MImageF* in, MImageF* out);

int interp1d_nearest(MImageF* in, MImageF* out);

int interp1d_linear(MImageF* in, MImageF* out);

int interp1d_cubic(MImageF* in, MImageF* out);

#endif