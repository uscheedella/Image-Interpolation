/*
Copyright (c) 1992-2013 The University of Tennessee and The University
                        of Tennessee Research Foundation.  All rights
                        reserved.
Copyright (c) 2000-2013 The University of California Berkeley. All
                        rights reserved.
Copyright (c) 2006-2013 The University of Colorado Denver.  All rights
                        reserved.

$COPYRIGHT$

Additional copyrights may follow

$HEADER$

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:

- Redistributions of source code must retain the above copyright
  notice, this list of conditions and the following disclaimer.

- Redistributions in binary form must reproduce the above copyright
  notice, this list of conditions and the following disclaimer listed
  in this license in the documentation and/or other materials
  provided with the distribution.

- Neither the name of the copyright holders nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

The copyright holders provide no reassurances that the source code
provided does not infringe any patent, copyright, or any other
intellectual property rights of third parties.  The copyright holders
disclaim any liability to any recipient for claims brought against
recipient by any third party for infringement of that parties
intellectual property rights.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/*
    LAPACKE Example : Calling DGELS using row-major layout
    =====================================================
 
    The program computes the solution to the system of linear
    equations with a square matrix A and multiple
    right-hand sides B, where A is the coefficient matrix
    and b is the right-hand side matrix:
 
    Description
    ===========
 
    In this example, we wish solve the least squares problem min_x || B - Ax ||
    for two right-hand sides using the LAPACK routine DGELS. For input we will
    use the 5-by-3 matrix
 
          ( 1  1  1 )
          ( 2  3  4 )
      A = ( 3  5  2 )
          ( 4  2  5 )
          ( 5  4  3 )
     and the 5-by-2 matrix
 
          ( -10 -3 )
          (  12 14 )
      B = (  14 12 )
          (  16 16 )
          (  18 16 )
     We will first store the input matrix as a static C two-dimensional array,
     which is stored in row-major layout, and let LAPACKE handle the work space
     array allocation. The LAPACK base name for this function is gels, and we
     will use double precision (d), so the LAPACKE function name is LAPACKE_dgels.
 
     thus lda=3 and ldb=2. The output for each right hand side is stored in b as
     consecutive vectors of length 3. The correct answer for this problem is
     the 3-by-2 matrix
 
          ( 2 1 )
          ( 1 1 )
          ( 1 2 )
 
     A complete C program for this example is given below. Note that when the arrays
      are passed to the LAPACK routine, they must be dereferenced, since LAPACK is
       expecting arrays of type double *, not double **.
 
 
    LAPACKE Interface
    =================
 
    LAPACKE_dgels (row-major, high-level) Example Program Results
 
   -- LAPACKE Example routine (version 3.7.0) --
   -- LAPACK is a software package provided by Univ. of Tennessee,    --
   -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..--
      December 2016
 
 */
 /* Calling DGELS using row-major layout */
 
 /* Includes */
 #include <stdio.h>
 #include <lapacke.h>
 #include "lapacke_example_aux.h"
 
 /* Main program */
 int main (int argc, const char * argv[])
 {
    /* Locals */
    double A[5][3] = {1,1,1,2,3,4,3,5,2,4,2,5,5,4,3};
    double b[5][2] = {-10,-3,12,14,14,12,16,16,18,16};
    lapack_int info,m,n,lda,ldb,nrhs;
 
    /* Initialization */
    m = 5;
    n = 3;
    nrhs = 2;
    lda = 3;
    ldb = 2;
 
    /* Print Entry Matrix */
    print_matrix_rowmajor( "Entry Matrix A", m, n, *A, lda );
    /* Print Right Rand Side */
    print_matrix_rowmajor( "Right Hand Side b", n, nrhs, *b, ldb );
    printf( "\n" );
 
    /* Executable statements */
    printf( "LAPACKE_dgels (row-major, high-level) Example Program Results\n" );
    /* Solve least squares problem*/
    info = LAPACKE_dgels(LAPACK_ROW_MAJOR,'N',m,n,nrhs,*A,lda,*b,ldb);
 
    /* Print Solution */
    print_matrix_rowmajor( "Solution", n, nrhs, *b, ldb );
    printf( "\n" );
    exit( 0 );
 } /* End of LAPACKE_dgels Example */
