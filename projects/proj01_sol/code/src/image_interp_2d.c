#include <math.h>
#include <stdlib.h>

#include "linalg.h"

#include "math_utilities.h"
#include "image_types.h"

#include "image_interp_2d.h"


int interp2d_downsample(int Cx, int Kx, int Cy, int Ky, MImageF* in, MImageF* out){

    int i, i_hat;
    int j, j_hat;
    int idx, idx_hat;

    // X is the fast direction for this problem.
    for(int j_hat=0; j_hat < out->height; j_hat++){
        j = Cy + j_hat*Ky;

        for(int i_hat=0; i_hat < out->width; i_hat++){
            i = Cx + i_hat*Kx;

            idx_hat = j_hat*(out->width) + i_hat;
            idx = j*(in->width) + i;

            out->data[idx_hat] = in->data[idx];
        }
    }

    return 0;
}


int interp2d_nearest(MImageF* in, MImageF* out){


    int i, i_hat;
    int j, j_hat;
    int idx, idx_hat;
    float hx, hx_hat;
    float hy, hy_hat;
    float x_hat, y_hat;

    const float a = 0.0;
    const float b = 1.0;
    const float c = 0.0;
    const float d = 1.0;

    hx = (b - a) / (in->width-1.0);
    hx_hat = (b - a) / (out->width-1.0);

    hy = (d - c) / (in->height-1.0);
    hy_hat = (d - c) / (out->height-1.0);

    // X is the fast direction for this problem.
    for(int j_hat=0; j_hat < out->height; j_hat++){
        
        y_hat = c + j_hat*hy_hat;
        j = (int)floor((y_hat-c)/hy);

        for(int i_hat=0; i_hat < out->width; i_hat++){

            x_hat = a + i_hat*hx_hat;
            i = (int)floor((x_hat-a)/hx);
 
            idx_hat = j_hat*(out->width) + i_hat;
            idx = j*(in->width) + i;

            out->data[idx_hat] = in->data[idx];
        }
    }

    return 0;
}



int interp2d_linear(MImageF* in, MImageF* out){

    int i, i_hat;
    int j, j_hat;
    int idx, idx_hat;
    float hx, hx_hat;
    float hy, hy_hat;
    float x_hat, y_hat;
    float xi, xip1;
    float yj, yjp1;
    float wx, wy;
    float gj_hat, gjp1_hat;

    const float a = 0.0;
    const float b = 1.0;
    const float c = 0.0;
    const float d = 1.0;

    hx = (b - a) / (in->width-1.0);
    hx_hat = (b - a) / (out->width-1.0);

    hy = (d - c) / (in->height-1.0);
    hy_hat = (d - c) / (out->height-1.0);

    // X is the fast direction for this problem.
    for(int j_hat=0; j_hat < out->height; j_hat++){
        
        y_hat = c + j_hat*hy_hat;
        j = (int)floor((y_hat-c)/hy);
            
        yj = c + j*hy;
        yjp1 = c + (j+1)*hy;
        wy = (yjp1 - y_hat) / hy;

        for(int i_hat=0; i_hat < out->width; i_hat++){

            x_hat = a + i_hat*hx_hat;
            i = (int)floor((x_hat-a)/hx);
            
            xi = a + i*hx;
            xip1 = a + (i+1)*hx;
            wx = (xip1 - x_hat) / hx;

            // Do x direction on first row
            idx = j*(in->width) + i;
            gj_hat = wx*in->data[idx] + (1.0-wx)*in->data[idx+1];

            // Do x direction on second row
            idx = (j+1)*(in->width) + i;
            gjp1_hat = wx*in->data[idx] + (1.0-wx)*in->data[idx+1];

            // Do y direction
            idx_hat = j_hat*(out->width) + i_hat;
            out->data[idx_hat] = wy*gj_hat + (1.0-wy)*gjp1_hat;
        }
    }
    
    return 0;
}


void build_cubic_system(float a, int i, float h, float* data, float* A, float* b, float* coeffs){
    
    float x;

    for (int k=0; k<4; k++){
        x = a + (i+k)*h;
        A[k*4 + 0] = pow(x, 3.0);
        A[k*4 + 1] = pow(x, 2.0);
        A[k*4 + 2] = x; //pow(xk, 1.0);
        A[k*4 + 3] = 1.0; //pow(xk, 0.0);
        b[k] = data[k];
        coeffs[k] = 0.0;
    }
}

float evaluate_cubic_polynomial(float* coeffs, float x){
    return coeffs[0]*pow(x, 3.0) + coeffs[1]*pow(x, 2.0) + coeffs[2]*x + coeffs[3]*1;
}

int interp2d_cubic(MImageF* in, MImageF* out){

    int i, i_hat;
    int j, j_hat;
    int idx, idx_hat;
    float hx, hx_hat;
    float hy, hy_hat;
    float x_hat, y_hat;

    float A[16];
    float rhs[4];
    float coeffs[4];
    float g_hat[4];

    const float a = 0.0;
    const float b = 1.0;
    const float c = 0.0;
    const float d = 1.0;

    hx = (b - a) / (in->width-1.0);
    hx_hat = (b - a) / (out->width-1.0);

    hy = (d - c) / (in->height-1.0);
    hy_hat = (d - c) / (out->height-1.0);

    // X is the fast direction for this problem.
    for(int j_hat=0; j_hat < out->height; j_hat++){
        
        y_hat = c + j_hat*hy_hat;
        j = (int)floor((y_hat-c)/hy);
        j = max(j, 1);
        j = min(j, in->height-3);
            
        for(int i_hat=0; i_hat < out->width; i_hat++){

            x_hat = a + i_hat*hx_hat;
            i = (int)floor((x_hat-a)/hx);
            i = max(i, 1);
            i = min(i, in->width-3);
            
            // Do x direction on each of 4 rows
            for (int k=0; k<4; k++){
                idx = (j+k-1)*(in->width) + i;
                build_cubic_system(a, i-1, hx, in->data+(idx-1), A, rhs, coeffs);
                linear_solve(4, A, rhs, coeffs);
                g_hat[k] = evaluate_cubic_polynomial(coeffs, x_hat);
            }

            // Do y direction across results from x
            build_cubic_system(c, j-1, hy, g_hat, A, rhs, coeffs);
            linear_solve(4, A, rhs, coeffs);

            idx_hat = j_hat*(out->width) + i_hat;
            out->data[idx_hat] = evaluate_cubic_polynomial(coeffs, y_hat);
        }
    }
    
    return 0;
}

