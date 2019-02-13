#include <math.h>
#include <stdlib.h>

#include "linalg.h"

#include "math_utilities.h"
#include "image_types.h"

#include "image_interp_1d.h"


int interp1d_downsample(int C, int K, MImageF* in, MImageF* out){

    int i, i_hat;

    for(int i_hat=0; i_hat < out->width; i_hat++){
        i = C + i_hat*K;
        out->data[i_hat] = in->data[i];
    }

    return 0;
}


int interp1d_nearest(MImageF* in, MImageF* out){

    int i, i_hat;
    float h, h_hat;
    float x_hat;

    const float a = 0.0;
    const float b = 1.0;

    h = (b - a) / (in->width-1.0);
    h_hat = (b - a) / (out->width-1.0);

    for(int i_hat=0; i_hat < out->width; i_hat++){
        x_hat = a + i_hat*h_hat;
        i = (int)floor((x_hat-a)/h);

        out->data[i_hat] = in->data[i];
    }

    return 0;
}



int interp1d_linear(MImageF* in, MImageF* out){

    int i, i_hat;
    float h, h_hat;
    float x_hat;
    float xi, xip1;
    float w;

    const float a = 0.0;
    const float b = 1.0;

    h = (b - a) / (float)(in->width-1);
    h_hat = (b - a) / (out->width-1.0);

    for(int i_hat=0; i_hat < out->width; i_hat++){
        x_hat = a + i_hat*h_hat;
        i = (int)floor((x_hat-a)/h);
        xi = a + i*h;
        xip1 = a + (i+1)*h;

        w = (xip1 - x_hat) / h;

        out->data[i_hat] = w*in->data[i] + (1-w)*in->data[i+1];
    }

    return 0;
}

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

    h = (b - a) / ((float)in->width-1.0);
    h_hat = (b - a) / ((float)out->width-1.0);

    for(int i_hat=0; i_hat < out->width; i_hat++){
        x_hat = a + i_hat*h_hat;

        i = (int)floor((x_hat-a)/h);
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

        out->data[i_hat] = 0.0;
        for(int k=0; k<4; k++){
            out->data[i_hat] += coeffs[k]*pow(x_hat, (float)(3-k));
        }
    }

    return 0;
}

