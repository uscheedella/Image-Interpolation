#ifndef __PYTHON_UTILITIES_H__
#define __PYTHON_UTILITIES_H__

void print_numpy_header(FILE* outfile);

void print_numpy_float_array(FILE* outfile, char* name, int N, float* arr);

void print_numpy_char_array(FILE* outfile, char* name, int N, unsigned char* arr);


#endif