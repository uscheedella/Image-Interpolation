/*
* Authors:
*   Russell J. Hewett (rhewett@vt.edu)
*
* Not licensed for external distribution.
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "image_types.h"
#include "image_memory.h"
#include "image_interp_2d.h"
#include "image_convert.h"

#include "pam_io.h"

int main(int argc, char **argv)
{
    MImage8 input8;
    MImageF input;

    MImageF output;
    MImage8 output8;

    nullify_MImage8(&input8);
    nullify_MImageF(&input);

    nullify_MImageF(&output);
    nullify_MImage8(&output8);

    //int error = load_pgm_MImage8("graytable.pgm");
    int error = load_pgm_MImage8("../../../test_data/cameraman.pgm", &input8);
    if(error != 0) {
        return error;
    }

    allocate_MImageF(&input, input8.width, input8.height);
    initialize_MImageF(&input);
    convert_MImage8_to_MImageF(&input8, &input);

    allocate_MImage8(&output8, input.width*3, input.height*3);
    allocate_MImageF(&output, input.width*3, input.height*3);

    // Nearest-neighbor
    initialize_MImageF(&output);
    initialize_MImage8(&output8);

    interp2d_nearest(&input, &output);

    convert_MImageF_to_MImage8(&output, &output8);
    save_pgm_MImage8("cameraman_nearest_3x.pgm", &output8);

    // Linear
    initialize_MImageF(&output);
    initialize_MImage8(&output8);

    interp2d_linear(&input, &output);

    convert_MImageF_to_MImage8(&output, &output8);
    save_pgm_MImage8("cameraman_linear_3x.pgm", &output8);

    // Cubic
    initialize_MImageF(&output);
    initialize_MImage8(&output8);

    interp2d_cubic(&input, &output);

    convert_MImageF_to_MImage8(&output, &output8);
    save_pgm_MImage8("cameraman_cubic_3x.pgm", &output8);

    deallocate_MImage8(&input8);
    deallocate_MImageF(&input);
    deallocate_MImageF(&output);
    deallocate_MImage8(&output8);

    return 0;
}
