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

complex E[2][2] = {{1, 0}, {0, 1}};
complex SIGMA_1[2][2] = {{0, 1}, {1, 0}};
complex SIGMA_2[2][2] = {{0, -1.0i}, {1.0i, 0}};
complex SIGMA_3[2][2] = {{1, 0}, {0, -1}};
complex SPIN_UP[2] = {1, 0};
complex SPIN_DOWN[2] = {0, 1};
const K_INITIAL = M_PI;
const E_INITIAL = 0;



complex *ms(complex *M, complex s, int m); // 数组与标量乘法
complex *kronecker(complex *LM, complex *RM, int l, int r); // 两个数组作张量积



int main()
{
	clock_t start = clock();
	// 构造局域化算符
	complex *L_OPERATOR; 
	complex *L_ANXULIARY;
	complex *HAMILTONIAN = NULL;
	complex *HAMILTONIAN_TRANS = NULL;
	complex *HAMILTONIAN_LONGI = NULL;
	int i;
	int j;
	for (i = 0; i < N + 1; i++){
		*L_OPERATOR = *L_OPERATOR + *L_ANXULIARY;
		*L_ANXULIARY = 1;
		for (j = 0; j < N; j++){
			if (j == i || j == (i + 1) % N){
				L_ANXULIARY = kronecker(L_ANXULIARY, SIGMA_3);
			}
			else{
				L_ANXULIARY = kronecker(L_ANXULIARY, E);
			}
		}
		
	L_OPERATOR = L_OPERATOR / N;


	//构造哈密顿量
	for (i = 0; i < N + 1; i++){
		*HAMILTONIAN = *HAMILTONIAN + *HAMILTONIAN_TRANS;
		*HAMILTONIAN = *HAMILTONIAN + *HAMILTONIAN_LONGI;
		*HAMILTONIAN_TRANS = 1;
		*HAMILTONIAN_LONGI = h;
		for (j = 0; j < N; j++){
			if (j == i){
				HAMILTONIAN_TRANS = kronecker(HAMILTONIAN_TRANS, SIGMA_1);
				HAMILTONIAN_LONGI = kronecker(HAMILTONIAN_LONGI, SIGMA_3);
			}
			else {
				HAMILTONIAN_TRANS = kronecker(HAMILTONIAN_TRANS, E);
				HAMILTONIAN_LONGI = kronecker(HAMILTONIAN_LONGI, E);
			}
		}
	}
	*HAMILTONIAN += J * N * L_OPERATOR;

	// 构造反铁磁态
	

	



	clock_t end = clock();
	time_comsume = (double)(end - start) / CLOCK_PER_SECOND;
	printf("time comsuming: %.2f \n", time_comsume);

	return 0;
}



complex *ms(complex *M, complex s, int m){
	int i;
	int j;
	complex **OUT = calloc(m, sizeof(complex *));
	for (i = 0; i < m; i++){
		OUT[i] = calloc(m, sizeof(complex));
	}
	for (i = 0; i < m; i++){
		for (j = 0; j < m; j++){
			OUT[i][j] = M[i][j] * s;
		}
	}
	return OUT;
}



complex *kronecker(complex *LM, complex *RM, int l, int r){
	int i; 
	int j;
	int jj;
	complex **PM = calloc(l * r, sizeof(complex *));
	for (i = 0; i < l * r; i++){
		PM[i] = calloc(l * r, sizeof(complex));
	}
	for (i = 0; i < l; i++){
		for (j = 0; j < l; j++){
			complex *LIJ = ms(RM, LM[i][j], r);
			for (jj = 0; jj < r; jj++){
				memcpy(*(PM + (i * r + jj)) + (j * r), LIJ[jj], sizeof(complex) * r);
			}
		}
	}
}















