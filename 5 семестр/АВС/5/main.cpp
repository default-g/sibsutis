#include <chrono>
#include <fstream>
#include <iostream>
#include <math.h>
#include <omp.h>
#include <pthread.h>
#include <vector>

typedef std::vector<std::vector<double>> matrix;

int NUMBER_OF_THREADS = 1;
int N = 1;
int THREAD_MODE = 0;

static matrix A;
static matrix B;
static matrix C;

void fill_matrix(matrix &a) {
  for (auto &row : a) {
    for (auto &item : row) {
      item = rand() % 10;
    }
  }
}

void init_matrix(matrix &a, int n) {
  a.clear();
  for (int i = 0; i < n; i++) {
    a.push_back(std::vector<double>(n, 0));
  }
}

void print_matrix(matrix a) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      std::cout << a[i][j] << " ";
    }
    std::cout << "\n";
  }
}

typedef struct arguments {
  int start_row;
  int end_row;
} arguments;

void *compute_row(void *args) {
  arguments *argument = (arguments *)args;
  int start_row = argument->start_row;
  int end_row = argument->end_row;
  for (int i = start_row; i < end_row; i++) {
    for (int j = 0; j < N; j++) {
      unsigned long sum = 0;
      for (int k = 0; k < N; k++) {
        sum += A[i][k] * B[j][k];
      }
      C[i][j] = sum;
    }
  }
  pthread_exit(NULL);
}

long double multiply_posix() {

  pthread_t thread_pool[NUMBER_OF_THREADS];
  arguments args_pool[NUMBER_OF_THREADS];

  matrix BT;

  init_matrix(BT, N);

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      BT[j][i] = B[i][j];
    }
  }

  B = BT;

  int n_split = N < NUMBER_OF_THREADS ? N : NUMBER_OF_THREADS;
  int n_work = N < NUMBER_OF_THREADS ? 1 : N / NUMBER_OF_THREADS;

  for (int i = 0; i < n_split; i++) {
    arguments args;
    args.start_row = i * n_work;
    args.end_row = args.start_row + n_work;
    if (i == n_split - 1 && args.end_row < N) {
      args.end_row = N;
    }
    args_pool[i] = args;
    pthread_create(&thread_pool[i], NULL, compute_row, (void *)&args_pool[i]);
  }

  auto start = std::chrono::system_clock::now();
  for (int i = 0; i < n_split; i++) {
    pthread_join(thread_pool[i], NULL);
  }
  auto end = std::chrono::system_clock::now();
  std::chrono::duration<long double> difference = end - start;
  return difference.count();
}

long double multiply_omp() {
  matrix BT;

  init_matrix(BT, N);

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      BT[j][i] = B[i][j];
    }
  }

  B = BT;

  int n_split = N < NUMBER_OF_THREADS ? N : NUMBER_OF_THREADS;
  int n_work = N < NUMBER_OF_THREADS ? 1 : N / NUMBER_OF_THREADS;
  omp_set_num_threads(NUMBER_OF_THREADS);
  auto start = std::chrono::system_clock::now();

#pragma omp parallel
  {
    int i, j, k;
#pragma omp for
    for (i = 0; i < N; i++) {
      for (j = 0; j < N; j++) {
        double dot = 0;
        for (k = 0; k < N; k++) {
          dot += A[i][k] * B[j][k];
        }
        C[i][j] = dot;
      }
    }
  }

  auto end = std::chrono::system_clock::now();
  std::chrono::duration<long double> difference = end - start;

  return difference.count();
}

int main(int argc, char *argv[]) {
  N = std::stol(std::string(argv[1]));
  NUMBER_OF_THREADS = std::stol(std::string(argv[2]));
  THREAD_MODE = std::stol(std::string(argv[3]));
  init_matrix(A, N);
  fill_matrix(A);
  init_matrix(B, N);
  fill_matrix(B);
  init_matrix(C, N);
  long double time = 0;

  if (THREAD_MODE == 0) {
    time = multiply_posix();
  } else {
    time = multiply_omp();
  }

  print_matrix(A);
  std::cout << std::endl;
  print_matrix(B);
  std::cout << std::endl;
  print_matrix(C);

  std::ofstream out("file.csv", std::ios_base::app);
  if (out.is_open()) {
    out << N << ";" << NUMBER_OF_THREADS << ";" << time << std::endl;
  }
}