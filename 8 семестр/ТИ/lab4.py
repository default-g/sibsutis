import numpy as np
from typing import Tuple

def generate_generator_matrix(filename: str, n: int, m: int) -> None:
    generator_matrix = np.random.randint(0, 2, size=(n, m))
    with open(filename, 'w') as file:
        file.write(f"{n} {m}\n")
        for row in generator_matrix:
            file.write(' '.join(map(str, row)) + '\n')

def read_generator_matrix(filename: str) -> Tuple[np.ndarray, int, int]:
    with open(filename, 'r') as file:
        lines = file.readlines()
        n, m = map(int, lines[0].split())
        generator_matrix = np.array([list(map(int, line.split())) for line in lines[1:]])
    return generator_matrix, n, m

def linear_code_characteristics(matrix: np.ndarray) -> Tuple[int, int, int]:
    n, m = matrix.shape
    code_dimension = n
    code_words = 2 ** m
    min_distance = float("inf")
    for code in range(n):
        for i in range(code + 1, n):
            distance = np.sum(matrix[code] != matrix[i])
            min_distance = min(min_distance, distance)
    return code_dimension, code_words, min_distance

def main() -> None:
    num_of_matrices = 5
    for i in range(1, num_of_matrices + 1):
        filename = f"output/matrix{i}.txt"
        n = np.random.randint(2, 5)  # ROWS
        m = np.random.randint(2, 10)  # COLS
        generate_generator_matrix(filename, n, m)

    for i in range(1, num_of_matrices + 1):
        filename = f"output/matrix{i}.txt"
        generator_matrix, n, m = read_generator_matrix(filename)
        print(f"Filename: {filename}")
        print(f"Matrix Size: {n} x {m}")
        print("Generator Matrix:")
        print(generator_matrix)
        code_dimension, code_words, min_distance = linear_code_characteristics(generator_matrix)
        print(f"Code Dimension: {code_dimension}")
        print(f"Number of Code Words: {code_words}")
        print(f"Minimum Code Distance: {min_distance}")
        print()

if __name__ == "__main__":
    main()
