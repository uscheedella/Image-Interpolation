#ifndef __IMAGE_INTERP_2D_H__
#define __IMAGE_INTERP_2D_H__

int interp2d_downsample(int Cx, int Kx, int Cy, int Ky, MImageF* in, MImageF* out);

int interp2d_nearest(MImageF* in, MImageF* out);

int interp2d_linear(MImageF* in, MImageF* out);

int interp2d_cubic(MImageF* in, MImageF* out);

#endif