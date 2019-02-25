/*
 * Authors:
 *   Russell J. Hewett (rhewett@vt.edu)
 *
 * Not licensed for external distribution.
 */

#include "image_interp_1d.h"
#include <math.h>
#include <stddef.h>
#include "image_utilities.h"
#include <stdlib.h>
#include "math_utilities.h"
#include "linalg.h"
#include <stdio.h>


/**
 * Downsamples in 1d and outputs as an image in a monochrome image format which stores data as a float type
 * which stores the subsampled result.
 *
 **/
int interp1d_downsample(int C, int K, MImageF* in, MImageF* out) {
    if (in->width == 0 || in->data == NULL) {
        return 1;
    }
    int N = in -> width;
    int M = (int)(ceil((N-C)/K));

    for (int x = 0; x <= M-1; x++) {
        int i = (int)(floor(C + x*K));
        out->data[x] = in->data[i];
    }
    return 0;
}

/**
 * Implements the nearest left-neighbor
 * algorithm for a monochrome image format which stores data as a float type
 *
 **/

int interp1d_nearest(MImageF* in, MImageF* out) {
    if (in -> data == NULL) {
        return 1;
    } 

    float a = 0.0;
    float b = 1.0;

    int N = in -> width;
    int M = out -> width;

    float h = (b-a) / (N-1);
    float i = (b-a) / (M-1);

    for(int x = 0; x <= M-1; x++) {
        float j = a + x*i;
        int k = floor((j-a)/h);
        out->data[x] = in->data[k];
    }
    return 0;

}

/**
 * Implements the piecewise linear
 * algorithm for a monochrome image format which stores data as a float type
 *
 **/

int interp1d_linear(MImageF* in, MImageF* out) {
    float a = 0.0;
    float b = 1.0;

    int Nx = in -> width;
    int Mx = out -> width;

    float hx = (float)((b-a) / (Nx-1));
    float jx = (float)((b-a) / (Mx-1));

    for(int y=0; y<= Mx-1; y++) {
        float xihat = a + y*jx;
        int i = (int)(floor((xihat - a)/hx));
        float xi = a + i*hx;
        float xione = a + (i+1)*hx;
        float wx = (xione - xihat) / hx;
        out->data[y] = wx*in->data[i] + (1-wx)*in->data[i+1];
    }
    return 0;
}

/**
 * Implements the piecewise cubic
 * algorithm for a monochrome image format which stores data as a float type
 *
 **/

int interp1d_cubic(MImageF* in, MImageF* out) {
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
        float xihat = a + (float)ihat * hxhat;
        int i = (int)floor((xihat-a)/hx);
        i = max(1,i);
        i = min(i, Nx-3);
        //float xi = a + (i*hx);

        float ximinone = a + (i-1.0)*hx;
        float xipluszero = a + (i+0.0)*hx;
        float xiplusone = a + (i+1.0)*hx;
        float xiplustwo = a + (i+2.0)*hx;

        *(AArr+0) = powf(ximinone, 3.0);
        *(AArr+1) = powf(ximinone, 2.0);
        *(AArr+2) = ximinone;
        *(AArr+3) = 1.0;

        *(AArr+4) = powf(xipluszero, 3.0);
        *(AArr+5) = powf(xipluszero, 2.0);
        *(AArr+6) = xipluszero;
        *(AArr+7) = 1.0;

        *(AArr+8) = powf(xiplusone, 3.0);
        *(AArr+9) = powf(xiplusone, 2.0);
        *(AArr+10) = xiplusone;
        *(AArr+11) = 1.0;

        *(AArr+12) = powf(xiplustwo, 3.0);
        *(AArr+13) = powf(xiplustwo, 2.0);
        *(AArr+14) = xiplustwo;
        *(AArr+15) = 1.0;

        *(bArr+0) = *(in->data + (i-1));
        *(bArr+1) = *(in->data + i);
        *(bArr+2) = *(in->data + (i+1));
        *(bArr+3) = *(in->data + (i+2));

        linear_solve(4, AArr, bArr, xArr);

        out->data[ihat] = ((*(xArr+0))*powf(xihat, 3.0)) + ((*(xArr+1))*powf(xihat, 2.0)) + ((*(xArr+2))*xihat) + (*(xArr+3));

    }

    free(AArr);
    //AArr = NULL;
    free(xArr);
    //xArr = NULL;
    free(bArr);
    //bArr = NULL;

    return 0;
}
