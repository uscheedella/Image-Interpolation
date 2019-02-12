#include <math.h>
#include <stdlib.h>

#include "linalg.h"

#include "math_utilities.h"
#include "image_types.h"

#include "image_interp_1d.h"


int compute_1d_downsample_size(int N, int C, int K){

    return (int)ceil( (float)(N-C) / (float)K);
}


int interp1d_downsample(int C, int K, MImageF* in, MImageF* out){

    int i, ihat;

    for(int ihat=0; ihat < out->width; ihat++){
        i = C + ihat*K;
        out->data[ihat] = in->data[i];
    }

    return 0;
}


int interp1d_nearest(MImageF* in, MImageF* out){

    int i, ihat;
    float h, hhat;
    float xhat;

    const float a = 0.0;
    const float b = 1.0;

    h = (b - a) / (in->width-1.0);
    hhat = (b - a) / (out->width-1.0);

    for(int ihat=0; ihat < out->width; ihat++){
        xhat = a + ihat*hhat;
        i = (int)floor((xhat-a)/h);

        out->data[ihat] = in->data[i];
    }
}



int interp1d_linear(MImageF* in, MImageF* out){

    int i, ihat;
    float h, hhat;
    float xhat;
    float xi, xip1;
    float w;

    const float a = 0.0;
    const float b = 1.0;

    h = (b - a) / (float)(in->width-1);
    hhat = (b - a) / (out->width-1.0);

    for(int ihat=0; ihat < out->width; ihat++){
        xhat = a + ihat*hhat;
        i = (int)floor((xhat-a)/h);
        xi = a + i*h;
        xip1 = a + (i+1)*h;

        w = (xip1 - xhat) / h;

        out->data[ihat] = w*in->data[i] + (1-w)*in->data[i+1];
    }
}

int interp1d_cubic(MImageF* in, MImageF* out){

    int i, ihat;
    float h, hhat;
    float xhat;
    float xk;
    float i_temp;

    float A[16];
    float rhs[4];
    float coeffs[4];

    const float a = 0.0;
    const float b = 1.0;

    h = (b - a) / ((float)in->width-1.0);
    hhat = (b - a) / ((float)out->width-1.0);

    for(int ihat=0; ihat < out->width; ihat++){
        xhat = a + ihat*hhat;

        i = (int)floor((xhat-a)/h);
        i = max(i, 1);
        i = min(i, in->width);

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

        out->data[ihat] = 0.0;
        for(int k=0; k<4; k++){
            out->data[ihat] += coeffs[k]*pow(xhat, (float)(3-k));
        }
    }
}

