use rand::Rng;
use std::time::Instant;

const N: usize = 2000; // Tamanho da matriz

// Função para realizar a eliminação de Gauss
fn gaussian_elimination(mut matrix: [[f32; N + 1]; N]) {
    for i in 0..N {
        let mut max_row = i;
        for k in i + 1..N {
            if matrix[k][i].abs() > matrix[max_row][i].abs() {
                max_row = k;
            }
        }

        matrix.swap(i, max_row);

        for k in i + 1..N {
            let factor = matrix[k][i] / matrix[i][i];
            for j in i..=N {
                matrix[k][j] -= matrix[i][j] * factor;
            }
        }
    }

    let mut solution: [f32; N] = [0.0; N];
    for i in (0..N).rev() {
        solution[i] = matrix[i][N];
        for j in i + 1..N {
            solution[i] -= matrix[i][j] * solution[j];
        }
        solution[i] /= matrix[i][i];
    }

    if N <= 10 {
        println!("Resultados:");
        for (i, &x) in solution.iter().enumerate() {
            println!("x{} = {:.6}", i + 1, x);
        }
    }
}

// Função para imprimir a matriz criada
fn generate_random_matrix() -> [[f32; N + 1]; N] {
    let mut rng = rand::rng();
    let mut matrix = [[0.0; N + 1]; N];
    for i in 0..N {
        for j in 0..N {
            matrix[i][j] = rng.random_range(1..10) as f32;
        }
        matrix[i][N] = rng.random_range(1..10) as f32;
    }
    matrix
}

fn main() {
    // Gera uma matriz
    let matrix = generate_random_matrix();

    // Imprime a matriz gerada
    if N <= 10 {
        println!("Matriz aleatória:");
        for row in &matrix {
            for &value in row.iter() {
                print!("{:.6} ", value);
            }
            println!();
        }
    }

    // Executa o algoritmo de eliminação de Gauss
    let start = Instant::now();
    gaussian_elimination(matrix);
    let duration = start.elapsed();

    // Imprime o tempo que a função demorou para executar
    println!("Tempo gasto: {:.6} segundos", duration.as_secs_f64());
}
