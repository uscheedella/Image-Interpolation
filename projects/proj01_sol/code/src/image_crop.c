/*
* Authors:
*   Russell J. Hewett (rhewett@vt.edu)
*
* Not licensed for external distribution.
*/

#include <math.h>
#include <stdio.h>

#include "image_types.h"
#include "math_utilities.h"

#include "image_crop.h"


/*
* Crops an image using linear interpolation.
*
* The coordinates (a_hat,c_hat) and (b_hat,d_hat) are the top left and bottom
* right coordinates, in real image coordinates, of the desired window of the
* input image.  The input image is assumed to be defined by the box (0,0),
* (1,1).
*
* Arguments:
*   a_hat: left x coordinate of the crop window
*   b_hat: right x coordinate of the crop window
*   c_hat: left y coordinate of the crop window
*   d_hat: right y coordinate of the crop window
*   in: input image pointer
*   out: output image pointer
*
* Returns:
*   error code: 0 on success, 1 on failure
*/

int crop_linear(float a_hat, float b_hat, float c_hat, float d_hat,
                MImageF* in, MImageF* out)
{

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

    if(in->data == NULL){
        fprintf(stderr, "Input image null.\n");
        return 1;
    }

    if(out->data == NULL){
        fprintf(stderr, "Output image null.\n");
        return 1;
    }


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
        j = min(j, in->height-2);

        yj = c + j*hy;
        yjp1 = c + (j+1)*hy;
        wy = (yjp1 - y_hat) / hy;

        for(int i_hat=0; i_hat < out->width; i_hat++){

            x_hat = a_hat + i_hat*hx_hat;
            i = (int)floor((x_hat-a)/hx);
            i = min(i, in->height-2);

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

