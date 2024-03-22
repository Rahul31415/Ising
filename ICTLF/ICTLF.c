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
int VectorToNumber(int *A, int m);
int *NumberToVector(int n);
int *Cycle(int *B);
complex (*MS) (complex *M, complex s, int m) = ms;



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
	complex Z2[2] = SPIN_DOWN;

	for (i = 0; i < N + 1; i++){
		if (i % 2 == 0){
			Z2 = kronecker(Z2, SPIN_DOWN);
		}
		else{
			Z2 = kronecker(Z2, SPIN_UP);
		}
	}

	// 构造对应函数
	int corresponding[M] = {0};

	for (i = 0; i < M; i++){
		corresponding[i] = i;
	}

	for (i = 0; i < M; i++){
		int *vector = NumberToVector(i);
		int n = sizeof(vector)/sizeof(vector[0]);
		int *vectori = calloc(n, sizeof(int));
		memcpy(vetori[0], vector[0], sizeof(int) * n);
		vector = Cycle(vectori);
		corresponding[i] = VectorToNumber(vector);
	}


	// 寻找代表态
	struct node{
		int state;
		struct node *next;
	} //用链表来存储类
	
	struct node representative[M]; //使用结构体数组来存储所有链表的头部
	for (i = 0; i < M; i++){
		representative[i].next = NULL;
		representative[i].state = 0;
	} //初始化
	
	int summary = 0; 初始化计数器，用来计算类的数目

	struct node all_basis = {0, NULL};

	struct node *current = all_basis;
	for (i = 0; i < M; i++){
		current = add(current -> next, i);
	} //构造一个链表用来存储所有的张量基
	
	for (i = 0; i < M; i++){
		if (all_basis -> next != NULL){
			int numInitial = 0;
			int num = 0;
			struct node *bro = NULL;
		        struct node *current = NULL;	
			summary = i;
			num = all_basis.next -> state;
			numInitial = num;
			del(all_basis.next, num);
			bro = representative[i].next;
			for (current = bro; current -> next != NULL; current = bro){
				bro = current -> next;
			} // 找到当前链表的末尾节点，在这后面添加新的节点
			add(current, num);

			while(numInitial != corresponding[num]){
				int nextNum = 0;
				nextNum = corresponding[num];
				del(all_basis.next, nextNum);
				bro = representative[i].next;
				for (current = bro; current -> next != NULL; current = bro){
					bro = current -> next;
				}
				add(current, nextNum);
				num = nextNum;
			}
		}
	}

	
	// 寻找不变子空间，按照动量分类
	complex P[M][M] = {0};
	int index[N] = {0};
	int length[summary + 1] = {0};
	for (i = 0; i < summary + 1; i++){
		length[i] = len(representative[i].next);
	}

	for (i = 0; i < N; i++){
		for (j = 0; j < summary + 1; j++){
			if (0 == i % int(N/length[j])){
				int value[length[j]] = {0};
				value




	

	

	




	


	

	



	clock_t end = clock();
	time_comsume = (double)(end - start) / CLOCK_PER_SECOND;
	printf("time comsuming: %.2f \n", time_comsume);

	return 0;
}



complex *ms(complex *M, complex s, int m, int n){
	int i;
	int j;
	static complex **OUT = calloc(m, sizeof(complex *));
	for (i = 0; i < m; i++){
		OUT[i] = calloc(n, sizeof(complex));
	}
	for (i = 0; i < m; i++){
		for (j = 0; j < n; j++){
			OUT[i][j] = M[i][j] * s;
		}
	}

	return OUT;
}



complex *kronecker(complex *LM, complex *RM, int lr, int lc, int rr, int rc){
	int i; 
	int j;
	int jj;
	complex *LIJ;
	static complex **PM = calloc(lr * rr, sizeof(complex *));
	for (i = 0; i < lr * rr; i++){
		PM[i] = calloc(lc * rc, sizeof(complex));
	}
	for (i = 0; i < lr; i++){
		for (j = 0; j < lc; j++){
			LIJ = MS(RM, LM[i][j], rr, rc);
			for (jj = 0; jj < rr; jj++){
				memcpy(*(PM + (i * lr + jj)) + (j * rc), LIJ[jj], sizeof(complex) * rc);
			}
		}
	}

	return PM;
}



// 定义链表操作

struct node *add(struct node *head, int state){ //添加节点
	struct node *p1;
	if (head == NULL){
		p1 = (struct node*)malloc(sizeof(struct node));
		if (NULL == p1){ // 判空
			printf("malloc失败");
		}
		else{
		p1 -> state = state;
		head = p1;
		p1 -> next = NULL;
		}
	} //尾部添加节点
	else{
		p1 = (struct node*)malloc(sizef(struct node));
		if (NULL == p1){
			printf("malloc失败");
		}
		else{
			p1 -> next = head;
			p1 -> state = state;
			head = p1;
		}
	}
	return p1;
}




void del(struct node *head, int state){ //删除指定state节点
	struct node *current = NULL;
	struct node *mom = NULL;
	struct node *bro = NULL;
	mom = head;
	current = head;
	bro = head;
	while (current -> next == NULL){ //判断是否到链表结尾
		for (current = bro; current -> state != state; current = bro){
			mom = current;
			bro = current -> next;
		} // 遍历链表直到找到第一个state

		mom -> next = current -> next;
		free(current);
		bro = mom;
	}
} // 删除了所有值为指定state的节点


	

int len(steuct node *head){ //计算链表长度
	int sum = 0;
	struct node *bro = NULL;
	struct node *current = NULL;
	bro = head;
	for (current = bro; current -> next != NULL; current = bro){
		bro = current -> next;
		sum += 1;
	}

	return sum + 1;
}


















