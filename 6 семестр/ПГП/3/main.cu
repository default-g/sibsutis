#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <chrono>
#include <cuda.h>
#include <math.h>
#include <stdio.h>

__global__ void sumOfVec(float *a, float *b, float *c) {
  c[threadIdx.x + blockDim.x * blockIdx.x] =
      a[threadIdx.x + blockDim.x * blockIdx.x] +
      b[threadIdx.x + blockDim.x * blockIdx.x];
}

int main() {
  float *ca, *a, *cb, *b, *cc, *c;
  FILE *fp = fopen("data_cuda.txt", "w");
  unsigned int N = 1 << 20;
   for(unsigned int threads = 1; threads <= 1024; threads = (threads == 1) ? 16 : threads * 2) {
    unsigned int amount_of_blocks = N / threads;
    a = (float *)calloc(N, sizeof(float));
    b = (float *)calloc(N, sizeof(float));
    c = (float *)calloc(N, sizeof(float));
    for (int j = 0; j < N; j++) {
      a[j] = 1;
      b[j] = 1;
      c[j] = 0;
    }
    cudaMalloc((void **)&ca, N * sizeof(float));
    cudaMalloc((void **)&cb, N * sizeof(float));
    cudaMalloc((void **)&cc, N * sizeof(float));
    auto start = std::chrono::high_resolution_clock::now();
    sumOfVec<<<dim3(amount_of_blocks), dim3(threads)>>>(ca, cb, cc);
    cudaMemcpy(a, ca, N * sizeof(float), cudaMemcpyDeviceToHost);
    cudaMemcpy(b, cb, N * sizeof(float), cudaMemcpyDeviceToHost);
    cudaMemcpy(c, cc, N * sizeof(float), cudaMemcpyDeviceToHost);
    cudaDeviceSynchronize();
    auto end = std::chrono::high_resolution_clock::now();
    free(a);
    free(b);
    free(c);
    cudaFree(ca);
    cudaFree(cb);
    cudaFree(cc);
    std::chrono::duration<long double> difference = end - start;
    printf("Size of vector: %d, time: %Lf\n", threads, difference.count());
    fprintf(fp, "%Lf %d\n", difference.count(), threads);
  }

  return 0;
}