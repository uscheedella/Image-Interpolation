/*
* Authors:
*   Russell J. Hewett (rhewett@vt.edu)
*
* Not licensed for external distribution.
*/

#include "image_interp_1d.h"
#include <math.h>

int interp1d_downsample(int C, int K, MImageF* in, MImageF* out) {
    if (in->width == NULL || in->data == NULL) {
        return 1;
    }
    int N -> in -> width;
    int M -> compute_downsample_size(N, C, K);

    for (int x = 0; x <= M-1; x++) {
        int i = C + x*K;
        out->data[i] = in->data[i];
    }
    return 0;
}

int interp1D_nearest(MImageF* in, MImageF* out) {
    if (in -> data == NULL) {
        return 1;
    } 

    float a = 0.0;
    float b = 1.0;
    
    float h = (b-a) / (N-1);
    float i = (b-a) / (M-1);

   for(int x = 0; x <= M-1; x++) {
        float j = a + x*i;
        int k = floor((j-a)/h);
        out->data[x] = in->data[k];
   }
    return 0;

}

int interp1d_linear(MImageF* in, MImageF* out) {
    float a = 0.0;
    float b = 1.0;
    
    int Nx = in <- width;
    int Ny = in <- height;

    int hx = (b-a) / (Nx-1);
    int jx = (b-a) / (Mx-1);

    for(int y=0; y<= Mx-1; y++) {
        float xihat = a + y*jx;
        int i = floor((xihat - a)/jx);
        float xi = a + i*hx;
        float xione = a + (i+1)*hx;
        float wx = (xione - xihat) / hx;
        out->data[y] = wx*in->data[y] + (1-wx)*in->data[i+1];
    }
    return 0;
}
int interp1d_cubic(MImageF* in, MImage F* out) {
    float a = 0.0;
    float b = 1.0;

    int Nx = in->width;
    int Mx = out->width;

    float hx = (b-a) / (Nx-1);
    float hxhat = (b-a) / (Mx-1);

    float *AArr = malloc(16 * sizeof(float));
    float *bArr = malloc(4 * sizeof(float));
    float *xArr = malloc(4 * sizeof(float));
    
    for (int ihat = 0; ihat <= Mx-1; ihat++) {
        float xihat = a + (ihat * hxhat);
        float i = floor((xihat-a)/hx);
        float i = max(1,i);
        float i = min(i, Nx-3);
        float xi = a + (i*hx);
        float ximinone = a + (i-1)*hx;
        float xipluszero = a + (i+0)*hx;
        float xiplusone = a + (i+1)*hx;
        float xiplustwo = a + (i+2)*hx;

        *(AArr) = powf(xminone, 3);
        *(AArr+1) = powf(xminone, 2);
        *(AArr+2) = xminone;
        *(AArr+3) = 1;

        *(AArr+4) = powf(xipluszero, 3);
        *(AArr+5) = powf(xipluszero, 2);
        *(AArr+6) = xipluszero;
        *(AArr+7) = 1;

        *(AArr+8) = powf(xiplusone, 3);
        *(AArr+9) = powf(xiplusone, 2);
        *(AArr+10) = xiplusone;
        *(AArr+11) = 1;
        
        *(AArr+12) = powf(xiplustwo, 3);
        *(AArr+13) = powf(xiplustwo, 2);
        *(AArr+14) = xiplustwo;
        *(AArr+15) = 1;
    }

    linear_solve(4, AArr, bArr, xArr);
    out->data = xArr[0]*powf(xi, 3) + xArr[1]*powf(xi, 2) + xArr[2]*xi + xArr[3];

    free(AArr);
    free(xArr);
    free(bArr);

    return 0;
}
