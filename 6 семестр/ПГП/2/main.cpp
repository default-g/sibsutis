#include <chrono>
#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Indexes {
  unsigned int start_index;
  unsigned int end_index;
} Indexes;

float *A;
float *B;
float *C;

void *sum(void *arg) {
  Indexes indexes = *(Indexes *)arg;
  unsigned int start_index = indexes.start_index;
  unsigned int end_index = indexes.end_index;
  for (unsigned int i = start_index; i < end_index; i++) {
    C[i] = A[i] + B[i];
  }
  return 0;
}

int main() {
  unsigned long long int N = pow(2, 28);
  FILE *fp = fopen("data_posix.txt", "w");
  for (int threads = 2; threads <= 1024; threads *= 2) {
    A = (float *)calloc(N, sizeof(float));
    B = (float *)calloc(N, sizeof(float));
    C = (float *)calloc(N, sizeof(float));
    for (int i = 0; i < N; i++) {
      A[i] = 1;
      B[i] = 1;
      C[i] = 0;
    }
    unsigned long long int items_per_threads = N / threads;
    Indexes indexes[threads];

    for (int i = 0; i < threads; i++) {
      Indexes index;
      index.start_index = i * items_per_threads;
      index.end_index = index.start_index + items_per_threads;
      indexes[i] = index;
    }

    auto start = std::chrono::high_resolution_clock::now();
    pthread_t threads_array[threads];
    for (int i = 0; i < threads; i++) {
      pthread_create(&threads_array[i], NULL, sum, &indexes[i]);
    }
    for (int i = 0; i < threads; i++) {
      pthread_join(threads_array[i], NULL);
    }
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<long double> difference = end - start;
    printf("Size of vector: 2^15, threads=%d time: %Lf\n", threads, difference.count());
    fprintf(fp, "%Lf %d\n", difference.count(), threads);
    free(A);
    free(B);
    free(C);
  }
}