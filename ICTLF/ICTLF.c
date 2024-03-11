#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <clock.h>
#include <complex.h>
#include "mkl.h"
#include "mkl_blas.h"
#include "mkl_service.h"
#include "mkl_lapack.h"



#define N 14
#define M pow(2, N)
#define J 0.3
#define h 0.6

complex E[2][2] = {{1+I*0, 0}, {0, 1+I*0}};
complex SIGMA_1[2][2] = {{0, 1}, {1, 0}};
complex SIGMA_2[2][2] = {{0, -I*1}, {I*1, 0}};
complex SIGMA_3[2][2] = {{1, 0}, {0, -1}};
complex SPIN_UP[2] = {1, 0};
complex SPIN_DOWN[2] = {0, 1};
const K_INITIAL = M_PI;
const E_INITIAL = 0;




int main()
{
	clock_t start = clock();



































	clock_t end = clock();
	time_comsume = (double)(end - start) / CLOCK_PER_SECOND;
	printf("time comsuming: %.2f \n", time_comsume);

	return 0;
}
