#include <stdio.h>
#include <mkl.h>

// 定义矩阵大小
#define N 2

// 定义矩阵
float A[N][N] = {{1.0, 2.0}, {3.0, 4.0}};
float B[N][N] = {{5.0, 6.0}, {7.0, 8.0}};
float C[N][N];

int main() {
  // 使用 MKL 函数计算矩阵乘法
  cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
              N, N, N, 1.0, A, N, B, N, 0.0, C, N);

  // 打印结果矩阵
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      printf("%f ", C[i][j]);
    }
    printf("\n");
  }

  return 0;
}


