#include <math.h>

#include "image_types.h"

#include "image_crop.h"



int crop_linear(float a_hat, float b_hat, float c_hat, float d_hat, MImageF* in, MImageF* out){

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


    // Clamp the ranges to 0-1
    a_hat = fmin(b_hat, fmax(a, a_hat));
    b_hat = fmin(b, fmax(a_hat, b_hat));
    c_hat = fmin(d_hat, fmax(c, c_hat));
    d_hat = fmin(d, fmax(c_hat, d_hat));

    hx = (b - a) / (in->width-1.0);
    hx_hat = (b_hat - a_hat) / (out->width-1.0);

    hy = (b - a) / (in->height-1.0);
    hy_hat = (d_hat - c_hat) / (out->height-1.0);

    // X is the fast direction for this problem.
    for(int j_hat=0; j_hat < out->height; j_hat++){
        
        y_hat = c_hat + j_hat*hy_hat;
        j = (int)floor((y_hat-c)/hy);
            
        yj = c + j*hy;
        yjp1 = c + (j+1)*hy;
        wy = (yjp1 - y_hat) / hy;

        for(int i_hat=0; i_hat < out->width; i_hat++){

            x_hat = a_hat + i_hat*hx_hat;
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

