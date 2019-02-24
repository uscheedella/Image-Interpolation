/*
* Authors:
*   Russell J. Hewett (rhewett@vt.edu)
*
* Not licensed for external distribution.
*/

#include "image_interp_2d.h"
#include <math.h>

int interp2d_downsample(int Cx, int Kx, int Cy, int Ky, MImageF* in, MImageF* out) {
    int Nx = in->width;
    int Ny = in->width;

    int Mx = ceil((Nx-Cx) / Kx);
    int My = ceil((Ny-Cy) / Ky);

    for (ihat = 0; ihat <= Mx-1; ihat++) {
        float i = Cx + ihat*Kx;
        for (int jhat = 0; jhat <= My-1; jhat++) {
            float j = Cy + jhat*Ky;
        }
        out->[ihat,jhat] = in->[i,j];
    }
    return 0;
}

int interp2d_nearest(MImageF* in, MImageF* out) {
   float a = 0.0;
   float b = 1.0;
   float c = 0.0;
   float d = 1.0;

   int Nx = in->width;
   int Ny = in->height;
   int Mx = out->width;
   int My = out->height;

   float h = (b-a) / (Nx-1);
   float hhat = (b-a) / (Ny-1);
   float j = (d-c) / (Mx-1);
   float jhat = (d-c) / (My-1);

   for(int ihat = 0; ihat <= Ny; ihat++) {
        float xihat = a + ihat*hhat;
        int i = floor((xihat-a) / h);
        for(int khat = 0; khat <= My; khat++) {
            float yihat = a + khat*jhat;
            int k = floor((yihat-a) / j);
        }
        out->[ihat,khat] = in->[i,k];
   }
    return 0;
}

int interp2d_linear(MImageF* in, MImageF* out) {
    float a = 0.0;
    float b = 1.0;
    float c = 0.0;
    float d = 1.0;

    int Nx = in->width;
    int Ny = in->height;
    int Mx = out->width;
    int My = out->height;

    float hx = (b-a) / (Nx - 1);
    float hxhat = (b-a) / (Mx - 1);
    float hy = (d-c) / (Ny - 1);
    float hyhat = (d-c) / (My-1);

    for (int jhat=0; jhat <= My-1; jhat++) {
        float yjhat = c + jhat*hyhat;
        int j = floor((yjhat-c)/hy);
        float yj = c + j*hy;
        float yjplusone = c + (j+1)*hy;
        float wy = (yjplusone-yj)/hy;
        for (int ihat = 0; ihat <= Mx-1; ihat++) {
            float xihat = a + ihat*hxhat;
            int i = floor((xihat-a)/hx);
            float xi = a+i*hx;
            float xiplusone = a+(i+1)*hx;
            float wx = (xiplusone-xihat) / hx;
            float ghatj = wx*in->data[i,j] + (1-wx)*in->data[i+1,j];
            float ghatjplusone = wx*in->data[i,j+1]+(1-wx)*in->data[i+1,j+1];
          out->data[ihat,jhat]=wy*ghatj+(1-wy)*ghatjplusone;  
        }  
    }
    return 0;
}

int interp2d_cubic(MImageF* in, MImageF* out) {
    

}

