#ifndef CUDA_HANDLER
#define CUDA_HANDLER
#include <thrust/device_vector.h>
#include <thrust/iterator/zip_iterator.h>
#include <thrust/tuple.h>
#include <thrust/functional.h>
#include <thrust/transform.h>
#include <thrust/execution_policy.h>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <cuda_runtime.h>
#include <cublas_v2.h>
#include "utility.h"
#include "matrix_handler.h"

using namespace std;

// TRANSPOSING PART

void transpose_check(float *input_matrix, float *transposed_matrix)
{
    bool is_equal = true;
    float *expected_matrix = (float *)malloc(NUM_ELEMENTS * sizeof(float));
    for (int i = 0; i < MATRIX_SIZE; i++)
        for (int j = 0; j < MATRIX_SIZE; j++)
            expected_matrix[j * MATRIX_SIZE + i] = input_matrix[i * MATRIX_SIZE + j];

    if (PRINT_MODE)
    {
        cout << "INPUT MATRIX:" << endl;
        print_matrix(input_matrix);
        cout << "EXPECTED MATRIX:" << endl;
        print_matrix(expected_matrix);
        cout << "ACTUAL MATRIX:" << endl;
        print_matrix(transposed_matrix);
    }

    bool found_mismatch = false;
    for (int i = 0; i < MATRIX_SIZE; i++)
    {
        for (int j = 0; j < MATRIX_SIZE; j++)
            if (transposed_matrix[i * MATRIX_SIZE + j] != expected_matrix[i * MATRIX_SIZE + j])
            {
                is_equal = false;
                found_mismatch = true;
                cout << "Mismatch found at index (" << i << ", " << j << ")" << endl;
                cout << "Expected: " << expected_matrix[i * MATRIX_SIZE + j] << endl;
                cout << "Actual: " << transposed_matrix[i * MATRIX_SIZE + j] << endl;
                break;
            }
        if (found_mismatch)
            break;
    }

    if (is_equal)
        cout << GREEN << "SUCCESS: Transposed matrix equal to expected" << STANDART_COLOR << endl;
    else
        cout << RED << "FAILURE: Transposed matrix doesn't equal to expected" << STANDART_COLOR << endl;
}

__global__ void transpose_kernel(float *input_matrix, float *output_matrix)
{
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;

    if (x < MATRIX_SIZE && y < MATRIX_SIZE)
    {
        int index_in = y * MATRIX_SIZE + x;
        int index_out = x * MATRIX_SIZE + y;
        output_matrix[index_out] = input_matrix[index_in];
    }
}

float kernel_transpose(float *input_matrix, float *output_matrix)
{
    float elapsed_time = 0.0f;
    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    cudaEventRecord(start);

    dim3 dimGrid((MATRIX_SIZE - 1) / BLOCK_SIZE + 1, (MATRIX_SIZE - 1) / BLOCK_SIZE + 1);
    dim3 dimBlock(TILE_DIM, BLOCK_SIZE, 1);

    transpose_kernel<<<dimGrid, dimBlock>>>(input_matrix, output_matrix);

    cudaEventRecord(stop);
    cudaEventSynchronize(stop);
    cudaEventElapsedTime(&elapsed_time, start, stop);

    return elapsed_time;
}

float thrust_transpose(float *input_matrix, float *output_matrix)
{
    float elapsed_time = 0.0f;
    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    cudaEventRecord(start);

    thrust::device_vector<float> input(NUM_ELEMENTS);
    thrust::device_vector<float> output(NUM_ELEMENTS);

    // Copy input data to input vector
    thrust::copy(input_matrix, input_matrix + NUM_ELEMENTS, input.begin());

    thrust::counting_iterator<int> first(0);
    thrust::counting_iterator<int> last(NUM_ELEMENTS);

    auto input_iter = thrust::make_permutation_iterator(input.begin(),
                                                        thrust::make_transform_iterator(first,
                                                                                        [=] __device__(int i) mutable
                                                                                        {
                                                                                            int r = i / MATRIX_SIZE;
                                                                                            int c = i % MATRIX_SIZE;
                                                                                            return c * MATRIX_SIZE + r;
                                                                                        }));

    thrust::copy(input_iter, input_iter + NUM_ELEMENTS, output.begin());

    // Copy output data back to output_matrix
    thrust::copy(output.begin(), output.end(), output_matrix);

    cudaEventRecord(stop);
    cudaEventSynchronize(stop);
    cudaEventElapsedTime(&elapsed_time, start, stop);

    return elapsed_time;
}

float cublas_transpose(float *input_matrix, float *output_matrix)
{
    float alpha = 1.0f;
    float beta = 0.0f;
    float elapsed_time = 0.0f;
    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    cublasHandle_t handle;
    cublasCreate(&handle);

    cudaEventRecord(start);
    cublasSgeam(handle, CUBLAS_OP_T, CUBLAS_OP_N, MATRIX_SIZE, MATRIX_SIZE, &alpha, input_matrix, MATRIX_SIZE, &beta, input_matrix, MATRIX_SIZE, output_matrix, MATRIX_SIZE);
    cudaEventRecord(stop);

    cudaEventSynchronize(stop);
    cudaEventElapsedTime(&elapsed_time, start, stop);

    cublasDestroy(handle);

    return elapsed_time;
}

// MULTIPLYING PART

void multiply_check(float *input_matrix_1, float *input_matrix_2, float *result_matrix)
{
    bool is_equal = true;
    float *expected_matrix = (float *)malloc(NUM_ELEMENTS * sizeof(float));
    for (int i = 0; i < MATRIX_SIZE; i++)
        for (int j = 0; j < MATRIX_SIZE; j++)
        {
            float sum = 0.0f;
            for (int k = 0; k < MATRIX_SIZE; k++)
                sum += input_matrix_1[i * MATRIX_SIZE + k] * input_matrix_2[k * MATRIX_SIZE + j];
            expected_matrix[i * MATRIX_SIZE + j] = sum;
        }

    if (PRINT_MODE)
    {
        cout << "INPUT MATRIX 1:" << endl;
        print_matrix(input_matrix_1);
        cout << "INPUT MATRIX 2:" << endl;
        print_matrix(input_matrix_2);
        cout << "EXPECTED MATRIX:" << endl;
        print_matrix(expected_matrix);
        cout << "ACTUAL MATRIX:" << endl;
        print_matrix(result_matrix);
    }

    bool found_mismatch = false;
    for (int i = 0; i < MATRIX_SIZE; i++)
    {
        for (int j = 0; j < MATRIX_SIZE; j++)
            if (fabs(result_matrix[i * MATRIX_SIZE + j] - expected_matrix[i * MATRIX_SIZE + j]) > 1e-6f)
            {
                is_equal = false;
                found_mismatch = true;
                cout << "Mismatch found at index (" << i << ", " << j << ")" << endl;
                cout << "Expected: " << expected_matrix[i * MATRIX_SIZE + j] << endl;
                cout << "Actual: " << result_matrix[i * MATRIX_SIZE + j] << endl;
                break;
            }
        if (found_mismatch)
            break;
    }

    if (is_equal)
        cout << GREEN << "SUCCESS: Result matrix equal to expected" << STANDART_COLOR << endl;
    else
        cout << RED << "FAILURE: Result matrix doesn't equal to expected" << STANDART_COLOR << endl;
}

__global__ void matrix_multiply_kernel(float *input_matrix_1, float *input_matrix_2, float *output_matrix)
{
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if (row < MATRIX_SIZE && col < MATRIX_SIZE)
    {
        float sum = 0.0f;
        for (int i = 0; i < MATRIX_SIZE; i++)
        {
            sum += input_matrix_1[row * MATRIX_SIZE + i] * input_matrix_2[i * MATRIX_SIZE + col];
        }
        output_matrix[row * MATRIX_SIZE + col] = sum;
    }
}

float kernel_matrix_multiply(float *input_matrix_1, float *input_matrix_2, float *output_matrix)
{
    float elapsed_time = 0.0f;
    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    cudaEventRecord(start);

    dim3 dimGrid((MATRIX_SIZE - 1) / BLOCK_SIZE + 1, (MATRIX_SIZE - 1) / BLOCK_SIZE + 1);
    dim3 dimBlock(TILE_DIM, BLOCK_SIZE, 1);

    matrix_multiply_kernel<<<dimGrid, dimBlock>>>(input_matrix_1, input_matrix_2, output_matrix);

    cudaEventRecord(stop);
    cudaEventSynchronize(stop);
    cudaEventElapsedTime(&elapsed_time, start, stop);

    return elapsed_time;
}

float thrust_matrix_multiply(float *input_matrix_1, float *input_matrix_2, float *output_matrix)
{
    float elapsed_time = 0.0f;
    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    cudaEventRecord(start);

    thrust::device_ptr<float> d_input_matrix_1(input_matrix_1);
    thrust::device_ptr<float> d_input_matrix_2(input_matrix_2);
    thrust::device_ptr<float> d_output_matrix(output_matrix);

    thrust::counting_iterator<int> idx_first(0);
    thrust::counting_iterator<int> idx_last = idx_first + MATRIX_SIZE * MATRIX_SIZE;

    thrust::transform(
        idx_first, idx_last,
        d_output_matrix,
        [d_input_matrix_1, d_input_matrix_2] __device__(int idx) -> float
        {
            int row = idx / MATRIX_SIZE;
            int col = idx % MATRIX_SIZE;
            float sum = 0.0f;
            for (int i = 0; i < MATRIX_SIZE; i++)
            {
                sum += d_input_matrix_1[row * MATRIX_SIZE + i] * d_input_matrix_2[i * MATRIX_SIZE + col];
            }
            return sum;
        });

    cudaEventRecord(stop);
    cudaEventSynchronize(stop);
    cudaEventElapsedTime(&elapsed_time, start, stop);

    return elapsed_time;
}

float cublas_matrix_multiply(float *input_matrix_1, float *input_matrix_2, float *output_matrix)
{
    float alpha = 1.0f;
    float beta = 0.0f;

    cublasHandle_t handle;
    cublasCreate(&handle);

    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    cudaEventRecord(start);

    cublasSgemm(handle, CUBLAS_OP_N, CUBLAS_OP_N, MATRIX_SIZE, MATRIX_SIZE, MATRIX_SIZE, &alpha, input_matrix_2, MATRIX_SIZE, input_matrix_1, MATRIX_SIZE, &beta, output_matrix, MATRIX_SIZE);

    cudaEventRecord(stop);
    cudaEventSynchronize(stop);
    float elapsed_time;
    cudaEventElapsedTime(&elapsed_time, start, stop);

    cublasDestroy(handle);

    return elapsed_time;
}

/*Scalar multiplication of matrices is the operation of multiplying each element of a matrix by a scalar value (a single number).
In other words, given a matrix A and a scalar k, the scalar multiplication of A and k is a new matrix C
where each element of A is multiplied by k to get the corresponding element of C. For example, if A = [1 2; 3 4] and k = 2,
then the scalar multiplication of A and k is C = [2 4; 6 8].
A scalar is a unit matrix with a necessary number on the main diagonal.
For example, if scalar k = 2 and width of matrix A is 2, then k => k * E_2 => [2 0; 0 2]*/

void scalar_check(float *input_matrix, float *result_matrix)
{
    bool is_equal = true;
    float *expected_matrix = (float *)malloc(NUM_ELEMENTS * sizeof(float));
    for (int i = 0; i < NUM_ELEMENTS; i++)
        expected_matrix[i] = SCALAR * input_matrix[i];

    if (PRINT_MODE)
    {
        cout << "INPUT MATRIX:" << endl;
        print_matrix(input_matrix);
        cout << "SCALAR = " << SCALAR << endl;
        cout << "EXPECTED MATRIX:" << endl;
        print_matrix(expected_matrix);
        cout << "ACTUAL MATRIX:" << endl;
        print_matrix(result_matrix);
    }

    bool found_mismatch = false;
    for (int i = 0; i < MATRIX_SIZE; i++)
    {
        for (int j = 0; j < MATRIX_SIZE; j++)
            if (result_matrix[i * MATRIX_SIZE + j] != expected_matrix[i * MATRIX_SIZE + j])
            {
                is_equal = false;
                found_mismatch = true;
                cout << "Mismatch found at index (" << i << ", " << j << ")" << endl;
                cout << "Expected: " << expected_matrix[i * MATRIX_SIZE + j] << endl;
                cout << "Actual: " << result_matrix[i * MATRIX_SIZE + j] << endl;
                break;
            }
        if (found_mismatch)
            break;
    }

    if (is_equal)
        cout << GREEN << "SUCCESS: Result matrix equal to expected" << STANDART_COLOR << endl;
    else
        cout << RED << "FAILURE: Result matrix doesn't equal to expected" << STANDART_COLOR << endl;
}

__global__ void scalar_multiply_kernel(float *input_matrix, float *output_matrix)
{
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;

    if (x < MATRIX_SIZE && y < MATRIX_SIZE)
        output_matrix[y * MATRIX_SIZE + x] = input_matrix[y * MATRIX_SIZE + x] * SCALAR;
}

float kernel_scalar_multiply(float *input_matrix, float *output_matrix)
{
    float elapsed_time = 0.0f;
    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    cudaEventRecord(start);

    dim3 dimGrid((MATRIX_SIZE - 1) / BLOCK_SIZE + 1, (MATRIX_SIZE - 1) / BLOCK_SIZE + 1);
    dim3 dimBlock(TILE_DIM, BLOCK_SIZE, 1);

    scalar_multiply_kernel<<<dimGrid, dimBlock>>>(input_matrix, output_matrix);

    cudaEventRecord(stop);
    cudaEventSynchronize(stop);
    cudaEventElapsedTime(&elapsed_time, start, stop);

    return elapsed_time;
}

float thrust_scalar_multiply(float *input_matrix, float *output_matrix)
{
    float elapsed_time = 0.0f;
    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    cudaEventRecord(start);

    thrust::device_ptr<float> d_input_matrix(input_matrix);
    thrust::device_ptr<float> d_output_matrix(output_matrix);

    thrust::counting_iterator<int> idx_first(0);
    thrust::counting_iterator<int> idx_last = idx_first + MATRIX_SIZE * MATRIX_SIZE;

    thrust::transform(
        idx_first, idx_last,
        d_output_matrix,
        [d_input_matrix] __device__(int idx) -> float
        {
            return d_input_matrix[idx] * SCALAR;
        });

    cudaEventRecord(stop);
    cudaEventSynchronize(stop);
    cudaEventElapsedTime(&elapsed_time, start, stop);

    return elapsed_time;
}

float cublas_scalar_multiply(float *input_matrix, float *output_matrix)
{
    cublasHandle_t handle;
    cublasCreate(&handle);

    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    cudaEventRecord(start);

    float scalar = static_cast<float>(SCALAR);
    cublasSscal(handle, MATRIX_SIZE * MATRIX_SIZE, &scalar, input_matrix, 1);

    cudaMemcpy(output_matrix, input_matrix, MATRIX_SIZE * MATRIX_SIZE * sizeof(float), cudaMemcpyDeviceToDevice);

    cudaEventRecord(stop);
    cudaEventSynchronize(stop);
    float elapsed_time;
    cudaEventElapsedTime(&elapsed_time, start, stop);

    cublasDestroy(handle);

    return elapsed_time;
}

#endif