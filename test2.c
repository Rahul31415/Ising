#include <stdio.h>
#include <mkl.h>

// 定义矩阵大小
#define N 3

// 定义矩阵
float A[N][N] = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}};
float w[N];
float V[N][N];

int main() {
  // 使用 MKL 函数计算矩阵 A 的特征值和特征向量
  dsyevr(CblasRowMajor, 'V', 'U', N, A, N, w, V);

  // 打印特征值
  for (int i = 0; i < N; i++) {
    printf("特征值 %d: %f\n", i, w[i]);
  }

  // 打印特征向量
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      printf("%f ", V[i][j]);
    }
    printf("\n");
  }

  return 0;
}
