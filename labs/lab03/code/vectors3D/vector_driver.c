#include <stdio.h>

#include "vector3d.h"

int main()
{
        Vector3D xvec;
        Vector3D yvec;

        xvec.x = 1.0;
        xvec.y = 1.5;
        xvec.z = 2.3;

        yvec.x = 0.01;
        yvec.y = 5;
        yvec.z = 17.1717;

        Vector3D twob  = axpy(xvec, yvec, 0.25);
        Vector3D twoc = axpy(xvec, yvec, 0.56);

	printf("2a. = %f\n", norm(&xvec));

        printf("2b. = %f\n", twob.x);
        printf("2b. = %f\n", twob.y);
        printf("2b. = %f\n", twob.z);

        printf("2c. = %f\n", twoc.x);
        printf("2c. = %f\n", twoc.y);
        printf("2c. = %f\n", twoc.z);

        printf("2d. = %f\n", inner_product(xvec, yvec));

        /**printf("v.x = %f\n", myvec.x);
        printf("v.y = %f\n", myvec.y);
        printf("v.z = %f\n", myvec.z);

        return 0; **/


}

