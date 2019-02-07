#include <stdio.h>

#include "vector3d.h"

int main(int argc, char** argv)
{
	printf("1\n");

        Vector3D xvec;

        Vector3D yvec;
	
	printf("2\n");

        xvec.x = 1.0;
        xvec.y = 1.5;
        xvec.z = 2.3;

	printf("3\n");

        yvec.x = 0.01;
        yvec.y = 5;
        yvec.z = 17.1717;

	printf("4\n");

        Vector3D newvec;
	Vector3D newvec2;

	printf("5\n");

	axpy(0.25, &xvec, &yvec, &newvec);
        axpy(0.56, &xvec, &yvec, &newvec2);

	printf("6\n");

	printf("2a. = %f\n", norm(&xvec));

        printf("2b. = %f\n", newvec.x);
        printf("2b. = %f\n", newvec.y);
        printf("2b. = %f\n", newvec.z);

        printf("2c. = %f\n", newvec2.x);
        printf("2c. = %f\n", newvec2.y);
        printf("2c. = %f\n", newvec2.z);

        printf("2d. = %f\n", inner_product(&xvec, &yvec));

        /**printf("v.x = %f\n", myvec.x);
        printf("v.y = %f\n", myvec.y);
        printf("v.z = %f\n", myvec.z); **/

        return 0;


}

