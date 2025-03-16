#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 2000 // Tamanho da matriz

// Função para realizar a eliminação de Gauss
void GaussianElimination(float matrix[N][N + 1]) {
  for (int i = 0; i < N; i++) {
    int maxRow = i;
    for (int k = i + 1; k < N; k++) {
      if (fabs(matrix[k][i]) > fabs(matrix[maxRow][i])) {
        maxRow = k;
      }
    }

    for (int k = i; k < N + 1; k++) {
      float temp = matrix[maxRow][k];
      matrix[maxRow][k] = matrix[i][k];
      matrix[i][k] = temp;
    }

    for (int k = i + 1; k < N; k++) {
      float factor = matrix[k][i] / matrix[i][i];
      for (int j = i; j < N + 1; j++) {
        matrix[k][j] -= matrix[i][j] * factor;
      }
    }
  }

  float solution[N];
  for (int i = N - 1; i >= 0; i--) {
    solution[i] = matrix[i][N];
    for (int j = i + 1; j < N; j++) {
      solution[i] -= matrix[i][j] * solution[j];
    }
    solution[i] /= matrix[i][i];
  }

  if (N <= 10) {
    printf("Resultados: \n");
    for (int i = 0; i < N; i++) {
      printf("x%d = %.6f\n", i + 1, solution[i]);
    }
  }
}

// Função para gerar uma matriz de elementos aleatórios
void GenerateRandomMatrix(float matrix[N][N + 1]) {
  srand(time(0));
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      matrix[i][j] = rand() % 10 + 1;
    }
    matrix[i][N] = rand() % 10 + 1;
  }
}

// Função para imprimir a matriz criada
void PrintMatrix(float matrix[N][N + 1]) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N + 1; j++) {
      printf("%.6f ", matrix[i][j]);
    }
    printf("\n");
  }
}

int main() {
  // Gera uma matriz
  float matrix[N][N + 1];
  GenerateRandomMatrix(matrix);

  // Imprime a matriz gerada
  if (N <= 10) {
    printf("Matriz aleatória:\n");
    PrintMatrix(matrix);
  }

  // Executa o algoritmo de eliminação de Gauss
  clock_t start = clock();
  GaussianElimination(matrix);
  clock_t end = clock();

  double timeSpent = (double)(end - start) / CLOCKS_PER_SEC;

  // Imprime o tempo que a função demorou para executar
  printf("Tempo gasto: %.6f segundos\n", timeSpent);

  return 0;
}
