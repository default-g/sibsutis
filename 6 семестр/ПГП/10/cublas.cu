#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <cuda_runtime.h>
#include <cublas_v2.h>

void init_matrix(float *mat, int size)
{
    for (int i = 0; i < size * size; i++)
    {
        mat[i] = i;
    }
}

int main(int argc, char **argv)
{
    int N;
    N = atoi(argv[1]);
    if (argc < 2)
    {
        printf("INVALID INPUT!\n");
        exit(EXIT_FAILURE);
    }

    FILE *csv_file = fopen("cublas_res.csv", "a+");

    float *A, *B, *C;
    float alpha = 1.0, beta = 0.0;
    int size = N * N;

    A = (float *)malloc(size * sizeof(float));
    B = (float *)malloc(size * sizeof(float));
    C = (float *)malloc(size * sizeof(float));

    init_matrix(A, N);
    init_matrix(B, N);

    float *d_A, *d_B, *d_C;
    cudaMalloc(&d_A, size * sizeof(float));
    cudaMalloc(&d_B, size * sizeof(float));
    cudaMalloc(&d_C, size * sizeof(float));

    cudaMemcpy(d_A, A, size * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, B, size * sizeof(float), cudaMemcpyHostToDevice);

    cublasHandle_t handle;
    cublasCreate(&handle);

    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    cudaEventRecord(start);
    cublasSgemm(handle, CUBLAS_OP_N, CUBLAS_OP_N, N, N, N, &alpha, d_B, N, d_A, N, &beta, d_C, N);
    cudaEventRecord(stop);

    cudaEventSynchronize(stop);
    float elapsed_time = 0;
    cudaEventElapsedTime(&elapsed_time, start, stop);
    printf("cuBLAS: %d^2 / %f ms\n", N, elapsed_time);
    fprintf(csv_file, "%d; %f;\n", size, elapsed_time);

    cudaMemcpy(C, d_C, size * sizeof(float), cudaMemcpyDeviceToHost);

    free(A);
    free(B);
    free(C);
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

    cublasDestroy(handle);

    return 0;
}
