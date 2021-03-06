/*
* Authors:
*   Russell J. Hewett (rhewett@vt.edu)
*
* Not licensed for external distribution.
*/

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "linalg.h"

#include "math_utilities.h"
#include "image_types.h"

#include "image_utilities.h"
#include "image_interp_1d.h"


/*
* Interpolate a 1D "image" via downsampling.
*
* Assumes the output image has been pre-allocated.
*
* Arguments:
*   C: Offset of the starting pixel for downsampling
*   K: Downsampling factor
*   in: input image pointer
*   out: output image pointer
*
* Returns:
*   error code: 0 on success, 1 on failure
*/

int interp1d_downsample(int C, int K, MImageF* in, MImageF* out){

    int i, i_hat;

    if(in->data == NULL){
        fprintf(stderr, "Input image null.\n");
        return 1;
    }

    if(out->data == NULL){
        fprintf(stderr, "Output image null.\n");
        return 1;
    }

    if(compute_downsample_size(in->width, C, K) != out->width){
        fprintf(stderr, "Width mismatch.\n");
        return 1;
    }

    for(int i_hat=0; i_hat < out->width; i_hat++){
        i = C + i_hat*K;
        out->data[i_hat] = in->data[i];
    }

    return 0;
}


/*
* Interpolate a 1D "image" via left-nearest neighbor interpolation.
*
* Assumes the output image has been pre-allocated.
*
* Arguments:
*   in: input image pointer
*   out: output image pointer
*
* Returns:
*   error code: 0 on success, 1 on failure
*/

int interp1d_nearest(MImageF* in, MImageF* out){

    int i, i_hat;
    float h, h_hat;
    float x_hat;

    const float a = 0.0;
    const float b = 1.0;

    if(in->data == NULL){
        fprintf(stderr, "Input image null.\n");
        return 1;
    }

    if(out->data == NULL){
        fprintf(stderr, "Output image null.\n");
        return 1;
    }

    h = (b - a) / (in->width-1.0);
    h_hat = (b - a) / (out->width-1.0);

    for(int i_hat=0; i_hat < out->width; i_hat++){
        x_hat = a + i_hat*h_hat;
        i = (int)floor((x_hat-a)/h);
        i = max(0, i);

        out->data[i_hat] = in->data[i];
    }

    return 0;
}


/*
* Interpolate a 1D "image" via piecewise linear interpolation.
*
* Assumes the output image has been pre-allocated.
*
* Arguments:
*   in: input image pointer
*   out: output image pointer
*
* Returns:
*   error code: 0 on success, 1 on failure
*/

int interp1d_linear(MImageF* in, MImageF* out){

    int i, i_hat;
    float h, h_hat;
    float x_hat;
    float xi, xip1;
    float w;

    const float a = 0.0;
    const float b = 1.0;

    if(in->data == NULL){
        fprintf(stderr, "Input image null.\n");
        return 1;
    }

    if(out->data == NULL){
        fprintf(stderr, "Output image null.\n");
        return 1;
    }

    h = (b - a) / (float)(in->width-1);
    h_hat = (b - a) / (out->width-1.0);

    for(int i_hat=0; i_hat < out->width; i_hat++){
        x_hat = a + i_hat*h_hat;
        i = (int)floor((x_hat-a)/h);
        i = max(0, i);
        i = min(i, in->width-2);


        xi = a + i*h;
        xip1 = a + (i+1)*h;

        w = (xip1 - x_hat) / h;

        out->data[i_hat] = w*in->data[i] + (1-w)*in->data[i+1];
    }

    return 0;
}


/*
* Interpolate a 1D "image" via piecewise cubic interpolation.
*
* Assumes the output image has been pre-allocated.
*
* Arguments:
*   in: input image pointer
*   out: output image pointer
*
* Returns:
*   error code: 0 on success, 1 on failure
*/

int interp1d_cubic(MImageF* in, MImageF* out){

    int i, i_hat;
    float h, h_hat;
    float x_hat;
    float xk;
    float i_temp;

    float A[16];
    float rhs[4];
    float coeffs[4];

    const float a = 0.0;
    const float b = 1.0;

    if(in->data == NULL){
        fprintf(stderr, "Input image null.\n");
        return 1;
    }

    if(out->data == NULL){
        fprintf(stderr, "Output image null.\n");
        return 1;
    }

    h = (b - a) / ((float)in->width-1.0);
    h_hat = (b - a) / ((float)out->width-1.0);

    for(int i_hat=0; i_hat < out->width; i_hat++){
        x_hat = a + i_hat*h_hat;

        i = (int)floor((x_hat-a)/h);
        i = max(i, 1);
        i = min(i, in->width-3);

        // create system
        for (int k=0; k<4; k++){
            xk = a + (i+k-1)*h;
            A[k*4 + 0] = pow(xk, 3.0);
            A[k*4 + 1] = pow(xk, 2.0);
            A[k*4 + 2] = xk; //pow(xk, 1.0);
            A[k*4 + 3] = 1.0; //pow(xk, 0.0);
            rhs[k] = in->data[i+k-1];
            coeffs[k] = 0.0;
        }

        linear_solve(4, A, rhs, coeffs);

        out->data[i_hat] = 0.0;
        for(int k=0; k<4; k++){
            out->data[i_hat] += coeffs[k]*pow(x_hat, (float)(3-k));
        }
    }

    return 0;
}

