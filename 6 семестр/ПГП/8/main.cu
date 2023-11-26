#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>
#include <thrust/device_vector.h>
#include <thrust/inner_product.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <thrust/gather.h>
#include <cublas_v2.h>

#define THREADS_PER_BLOCK 64

template <typename T>
void write_to_file(std::vector<std::vector<T>> data, std::string filename)
{
    std::ofstream out(filename);
    for (auto row : data)
    {
        std::string row_out = "";
        for (auto item : row)
        {
            row_out += std::to_string(item) + ";";
        }
        row_out.pop_back();
        out << row_out << std::endl;
    }
}

__global__ void simpleMatMulKernell(float *d_M, float *d_N, float *d_P, int N)
{
    int row = blockIdx.y * N + threadIdx.y;
    int col = blockIdx.x * N + threadIdx.x;
    if (row < N && col < N)
    {
        float product_val = 0;
        for (int k = 0; k < N; k++)
        {
            product_val += d_M[row * N + k] * d_N[k * N + col];
        }
        d_P[row * N + col] = product_val;
    }
}

__host__ std::vector<float> matrix_multiplication_compare(int N)
{
    float *h_A, *h_B, *h_C;
    float *d_A, *d_B, *d_C;
    int matrix_size = N * N * sizeof(float);
    h_A = (float *)malloc(matrix_size);
    h_B = (float *)malloc(matrix_size);
    h_C = (float *)malloc(matrix_size);

    std::vector<float> stats{(float)N};

    cudaMalloc(&d_A, matrix_size);
    cudaMalloc(&d_B, matrix_size);
    cudaMalloc(&d_C, matrix_size);

    for (int i = 0; i < N * N; i++)
    {
        h_A[i] = rand() % 10;
        h_B[i] = rand() % 10;
    }

    cudaMemcpy(d_A, h_A, matrix_size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, matrix_size, cudaMemcpyHostToDevice);

    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    cudaEventRecord(start);

    simpleMatMulKernell<<< (N / THREADS_PER_BLOCK - 1) + THREADS_PER_BLOCK, THREADS_PER_BLOCK>>> (d_A, d_B, d_C, N);
    cudaMemcpy(h_C, d_C, matrix_size, cudaMemcpyDeviceToHost);
    cudaEventRecord(stop);
    cudaEventSynchronize(stop);
    float milliseconds = 0;

    cudaEventElapsedTime(&milliseconds, start, stop);

    stats.push_back(milliseconds);


    cublasHandle_t handle;
    cublasCreate(&handle);
    int lda = N, ldb = N, ldc = N;
    const float alf = 1;
    const float bet = 0;
    const float *alpha = &alf;
    const float *beta = &bet;

    cudaEventRecord(start);
    cublasSgemm(handle, CUBLAS_OP_N, CUBLAS_OP_N, N, N, N, alpha, d_A, lda, d_B, ldb, beta, d_C, ldc);
    cudaMemcpy(h_C, d_C, matrix_size, cudaMemcpyDeviceToHost);
    cudaEventRecord(stop);
    cudaEventSynchronize(stop);

    cudaEventElapsedTime(&milliseconds, start, stop);

    stats.push_back(milliseconds);

    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

    free(h_A);
    free(h_B);
    free(h_C);

    return stats;
}

int main()
{
    std::vector<std::vector<float>> statistics;
    for (int i = 2; i <= 1 << 13; i *= 2 ) {
        statistics.push_back(matrix_multiplication_compare(i));
    }

    write_to_file(statistics, "multiplication.csv");
        
}