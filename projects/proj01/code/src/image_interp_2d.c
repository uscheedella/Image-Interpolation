/*
 * Authors:
 *   Russell J. Hewett (rhewett@vt.edu)
 *
 * Not licensed for external distribution.
 */

#include "image_interp_2d.h"
#include <math.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "math_utilities.h"
#include "linalg.h"

int interp2d_downsample(int Cx, int Kx, int Cy, int Ky, MImageF* in, MImageF* out) {
    if(in->width == 0 || in->data == NULL) {
        return 1;
    }

    int Nx = in->width;
    int Ny = in->height;

    int Mx = (int)ceil((Nx-Cx) / Kx);
    int My = (int)ceil((Ny-Cy) / Ky);

    int jhat;
    int j;

    for (int ihat = 0; ihat <= Mx-1; ihat++) {
        int i = (int)(floor(Cx + ihat*Kx));
        for (jhat = 0; jhat <= My-1; jhat++) {
            j = (int)(floor(Cy + jhat*Ky));
            out->data[jhat*out->width+ihat] = in->data[j*in->width+i];
        }
        //out->data[jhat*out->width+ihat] = in->data[j*in->width+i];
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
    float hhat = (b-a) / (Mx-1);
    float j = (d-c) / (Ny-1);
    float jhat = (d-c) / (My-1);

    int khat;
    int k; 

    for(int ihat = 0; ihat <= Mx-1; ihat++) {
        float xihat = a + ihat*hhat;
        int i = (int)floor((xihat-a) / h);
        for(khat = 0; khat <= My-1; khat++) {
            float yihat = c + khat*jhat;
            k = (int)floor((yihat-c) / j);
            out->data[khat*Mx+ihat] = in->data[k*Nx+i];
        }
        //out->data[ihat,khat] = in->data[i,k];
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

    float hx = (float)(b-a) / (Nx - 1);
    float hxhat = (float)(b-a) / (Mx - 1);
    float hy = (float)(d-c) / (Ny - 1);
    float hyhat = (float)(d-c) / (My-1);

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
            float ghatj = wx*in->data[j*Nx+i] + (1-wx)*in->data[j*Nx+(i+1)];
            float ghatjplusone = wx*in->data[(j+1)*Nx+i]+(1-wx)*in->data[(j+1)*Nx+(i+1)];
            out->data[jhat*Mx+ihat]=wy*ghatj+(1-wy)*ghatjplusone; 
            //out->data[ihat*Mx+khat] = in->data[i*Nx+k];
        }  
    }
    return 0;
}

int interp2d_cubic(MImageF* in, MImageF* out) {
    float a = 0.0;
    float b = 1.0;
    float c = 0.0;
    float d = 1.0;

    int Nx = in->width;
    int Ny = in->height;
    int Mx = out->width;
    int My = out->height;

    float hx = (b-a)/(Nx-1);
    float hxhat = (b-a)/(Mx-1);
    float hy = (d-c)/(Ny-1);
    float hyhat = (d-c)/(My-1);

    float *AArrx = malloc(16 * sizeof(float));
    float *bArrx = malloc(4 * sizeof(float));
    float *xArrx = malloc(4 * sizeof(float));

    float *AArry = malloc(16 * sizeof(float));
    float *bArry = malloc(4 * sizeof(float));
    float *xArry = malloc(4 * sizeof(float));

    for(int jhat=0; jhat <= My-1; jhat++) {
        float yjhat = c + jhat * hyhat;
        int j = floor((yjhat-c)/hy);
        j = max(1,j);
        j = min(j, Ny-3);
        float yjminone = c + (j-1)*hy;
        float yjpluszero = c + (j+0)*hy;
        float yjplusone = c + (j+1)*hy;
        float yjplustwo = c + (j+2)*hy;

        for(int ihat=0; ihat <= Mx-1; ihat++) {
            float xihat = a + ihat * hxhat;
            int i = floor((xihat-a)/hx);
            i = max(1,i);
            i = min(i, Nx-3);
            float xi = a + i*hx;
            float ximinone = a + (i-1)*hx;
            float xipluszero = a + (i+0)*hx;
            float xiplusone = a + (i+1)*hx;
            float xiplustwo = a + (i+2)*hx;

            *(AArrx+0) = powf(ximinone, 3.0);
            *(AArrx+1) = powf(ximinone, 2.0);
            *(AArrx+2) = ximinone;
            *(AArrx+3) = 1.0;

            *(AArrx+4) = powf(xipluszero, 3.0);
            *(AArrx+5) = powf(xipluszero, 2.0);
            *(AArrx+6) = xipluszero;
            *(AArrx+7) = 1.0;

            *(AArrx+8) = powf(xiplusone, 3.0);
            *(AArrx+9) = powf(xiplusone, 2.0);
            *(AArrx+10) = xiplusone;
            *(AArrx+11) = 1.0;

            *(AArrx+12) = powf(xiplustwo, 3.0);
            *(AArrx+13) = powf(xiplustwo, 2.0);
            *(AArrx+14) = xiplustwo;
            *(AArrx+15) = 1.0;

            *(bArrx+0) = *(in->data + (i-1));
            *(bArrx+1) = *(in->data + i);
            *(bArrx+2) = *(in->data + (i+1));
            *(bArrx+3) = *(in->data + (i+2));
            
            linear_solve(4, AArrx, bArrx, xArrx);

            //out->data[ihat] = ((*(xArrx+0))*powf(xihat, 3.0)) + ((*(xArrx+1))*powf(xihat, 2.0)) + ((*(xArrx+2))*xihat) + (*(xArrx+3));

        }

            *(AArry+0) = powf(yjminone, 3.0);
            *(AArry+1) = powf(yjminone, 2.0);
            *(AArry+2) = yjminone;
            *(AArry+3) = 1.0;

            *(AArry+4) = powf(yjpluszero, 3.0);
            *(AArry+5) = powf(yjpluszero, 2.0);
            *(AArry+6) = yjpluszero;
            *(AArry+7) = 1.0;

            *(AArry+8) = powf(yjplusone, 3.0);
            *(AArry+9) = powf(yjplusone, 2.0);
            *(AArry+10) = yjplusone;
            *(AArry+11) = 1.0;

            *(AArry+12) = powf(yjplustwo, 3.0);
            *(AArry+13) = powf(yjplustwo, 2.0);
            *(AArry+14) = yjplustwo;
            *(AArry+15) = 1.0;

            *(bArry+0) = *(in->data + (j-1));
            *(bArry+1) = *(in->data + j);
            *(bArry+2) = *(in->data + (j+1));
            *(bArry+3) = *(in->data + (j+2));

            linear_solve(4, AArry, bArry, xArry);
    }




return 0;
}

