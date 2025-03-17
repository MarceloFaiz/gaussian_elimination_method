package main

import (
	"fmt"
	"math"
	"math/rand"
	"time"
)

const N = 5 // Tamanho da matriz

// Função para realizar a eliminação de Gauss
func GaussianElimination(matrix [N][N + 1]float64) {
	for i := range N {
		maxRow := i
		for k := i + 1; k < N; k++ {
			if math.Abs(matrix[k][i]) > math.Abs(matrix[maxRow][i]) {
				maxRow = k
			}
		}

		for k := i; k < N+1; k++ {
			matrix[i][k], matrix[maxRow][k] = matrix[maxRow][k], matrix[i][k]
		}

		for k := i + 1; k < N; k++ {
			factor := matrix[k][i] / matrix[i][i]
			for j := i; j < N+1; j++ {
				matrix[k][j] -= matrix[i][j] * factor
			}
		}
	}

	var solution [N]float64
	for i := N - 1; i >= 0; i-- {
		solution[i] = matrix[i][N]
		for j := i + 1; j < N; j++ {
			solution[i] -= matrix[i][j] * solution[j]
		}
		solution[i] /= matrix[i][i]
	}

	if N <= 10 {
		fmt.Println("Resultados:")
		for i := range N {
			fmt.Printf("x%d = %.6f\n", i+1, solution[i])
		}
	}
}

// Função para gerar uma matriz de elementos aleatórios
func GenerateRandomMatrix() [N][N + 1]float64 {
	var matrix [N][N + 1]float64
	rand.NewSource(time.Now().UnixNano())
	for i := range N {
		for j := range N {
			matrix[i][j] = float64(rand.Intn(10) + 1)
		}
		matrix[i][N] = float64(rand.Intn(10) + 1)
	}
	return matrix
}

// Função para imprimir a matriz criada
func PrintMatrix(matrix [N][N + 1]float64) {
	for i := range N {
		for j := range N + 1 {
			fmt.Printf("%f ", matrix[i][j])
		}
		fmt.Println()
	}
}

func main() {
	// Gera uma matriz
	matrix := GenerateRandomMatrix()

	// Imprime a matriz gerada
	if N <= 10 {
		fmt.Println("Matriz aleatória:")
		PrintMatrix(matrix)
	}

	// Executa o algoritmo de eliminação de Gauss
	start := time.Now()
	GaussianElimination(matrix)
	timeSpent := time.Since(start)

	// Imprime o tempo que a função demorou para executar
	fmt.Printf("Tempo gasto: %.6f segundos\n", timeSpent.Seconds())
}
