

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <assert.h>

#include <math.h>

#include "mkl_blas.h"

#include "mkl_service.h"

#include "mkl_lapack.h"

 

#define N 3

static double A[9] = {2, -1, 0, -1, 2, -1, 0, -1, 2};

 

int main (int argc, char **argv)

{

int n = N;

char jobz = 'V', range = 'A', uplo = 'U';

int i, lda, il, iu, m, ldz, *isuppz;

double *a, *w, *z, *work, vl, vu, abstol, dtemp;

int lwork, liwork, *iwork, info, itemp;

 

lda = n;

abstol = dlamch_("S");

ldz = n;

lwork = -1;

liwork = -1;

 

a = (double*) malloc(sizeof(double)*n*n);

memcpy(a, A, sizeof(double)*n*n);

 

w = (double*) malloc(sizeof(double)*n);

z = (double*) malloc(sizeof(double)*ldz*n);

isuppz = (int*) malloc(sizeof(int)*2*n);

 

dsyevr(&jobz, &range, &uplo, &n, a, &lda, &vl, &vu, &il, &iu, &abstol, &m, w, z,

&ldz, isuppz, &dtemp, &lwork, &itemp, &liwork, &info);

assert (info == 0);

lwork = (int)dtemp;

liwork = itemp;

work = (double*) malloc(sizeof(double)*lwork);

iwork = (int*) malloc(sizeof(int)*liwork);

 

dsyevr(&jobz, &range, &uplo, &n, a, &lda, &vl, &vu, &il, &iu, &abstol, &m, w, z,

&ldz, isuppz, work, &lwork, iwork, &liwork, &info);

printf("info = %d\n", info);

printf("# eig found = %d\n\n", m);

for (i = 0; i < m; i++) printf("eigen value [%d] = %f\n", i, w[i]);

free (a);

free (w);

free (z);

free (isuppz);

free (work);

free (iwork);

 

 

{

double x = 1.0, y = 2.0, r;

printf("\n");

r = fmod(x, y);

printf("fmod(%f, %f) = %f\n\n", x, y, r); //

}

return 0;

}
