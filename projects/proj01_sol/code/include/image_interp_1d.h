#ifndef __IMAGE_INTERP_1D_H__
#define __IMAGE_INTERP_1D_H__

int compute_1d_downsample_size(int N, int C, int K);

int interp1d_downsample(int C, int K, MImageF* in, MImageF* out);

int interp1d_nearest(MImageF* in, MImageF* out);

int interp1d_linear(MImageF* in, MImageF* out);

int interp1d_cubic(MImageF* in, MImageF* out);

#endif