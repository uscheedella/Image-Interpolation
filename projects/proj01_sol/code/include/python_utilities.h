/*
* Authors:
*   Russell J. Hewett (rhewett@vt.edu)
*
* Not licensed for external distribution.
*/

#ifndef __PYTHON_UTILITIES_H__
#define __PYTHON_UTILITIES_H__

void print_numpy_header(FILE* outfile);

void print_numpy_array_MImageF(FILE* outfile, char* name, MImageF* im);

void print_numpy_array_MImage8(FILE* outfile, char* name, MImage8* im);


#endif