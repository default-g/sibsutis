#include <cuda_runtime.h>
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <fstream>
#include "utility.h"
#include "cuda_handler.h"
#include "matrix_handler.h"

using namespace std;

int main()
{
    float *input_matrix_1, *input_matrix_2, *output_matrix;
    input_matrix_1 = (float *)malloc(NUM_ELEMENTS * sizeof(float));
    input_matrix_2 = (float *)malloc(NUM_ELEMENTS * sizeof(float));
    output_matrix = (float *)malloc(NUM_ELEMENTS * sizeof(float));

    init_matrix(input_matrix_1);
    this_thread::sleep_for(chrono::seconds(1));
    init_matrix(input_matrix_2);
    init_zero_matrix(output_matrix);

    if (PRINT_MODE)
    {
        cout << "BASE MATRICES:" << endl;
        cout << "input_matrix_1:" << endl;
        print_matrix(input_matrix_1);
        cout << "input_matrix_2:" << endl;
        print_matrix(input_matrix_2);
        cout << "output_matrix:" << endl;
        print_matrix(output_matrix);
    }

    float *device_input_matrix_1, *device_input_matrix_2, *device_output_matrix;
    cudaMalloc(&device_input_matrix_1, NUM_ELEMENTS * sizeof(float));
    cudaMalloc(&device_input_matrix_2, NUM_ELEMENTS * sizeof(float));
    cudaMalloc(&device_output_matrix, NUM_ELEMENTS * sizeof(float));
    cudaMemcpy(device_input_matrix_1, input_matrix_1, NUM_ELEMENTS * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(device_input_matrix_2, input_matrix_2, NUM_ELEMENTS * sizeof(float), cudaMemcpyHostToDevice);

    cout << "KERNEL TRANSPOSING:" << endl;
    init_zero_matrix(output_matrix);
    float elapsed_time_kernel_transpose = 0.0f;
    elapsed_time_kernel_transpose = kernel_transpose(device_input_matrix_1, device_output_matrix);
    cudaMemcpy(output_matrix, device_output_matrix, NUM_ELEMENTS * sizeof(float), cudaMemcpyDeviceToHost);
    transpose_check(input_matrix_1, output_matrix);
    cout << "Time: " << elapsed_time_kernel_transpose << " ms" << endl;
    cout << endl;

    cout << "THRUST TRANSPOSING:" << endl;
    init_zero_matrix(output_matrix);
    float elapsed_time_thrust_transpose = 0.0f;
    elapsed_time_thrust_transpose = thrust_transpose(device_input_matrix_1, device_output_matrix);
    cudaMemcpy(output_matrix, device_output_matrix, NUM_ELEMENTS * sizeof(float), cudaMemcpyDeviceToHost);
    transpose_check(input_matrix_1, output_matrix);
    cout << "Time: " << elapsed_time_thrust_transpose << " ms" << endl;
    cout << endl;

    cout << "CUBLAS TRANSPOSING:" << endl;
    init_zero_matrix(output_matrix);
    float elapsed_time_cublas_transpose = 0.0f;
    elapsed_time_cublas_transpose = cublas_transpose(device_input_matrix_1, device_output_matrix);
    cudaMemcpy(output_matrix, device_output_matrix, NUM_ELEMENTS * sizeof(float), cudaMemcpyDeviceToHost);
    transpose_check(input_matrix_1, output_matrix);
    cout << "Time: " << elapsed_time_cublas_transpose << " ms" << endl;
    cout << endl;

    cout << "KERNEL MATRIX MULTIPLICATION:" << endl;
    init_zero_matrix(output_matrix);
    float elapsed_time_kernel_matrix_multiplication = 0.0f;
    elapsed_time_kernel_matrix_multiplication = kernel_matrix_multiply(device_input_matrix_1, device_input_matrix_2, device_output_matrix);
    cudaMemcpy(output_matrix, device_output_matrix, NUM_ELEMENTS * sizeof(float), cudaMemcpyDeviceToHost);
    multiply_check(input_matrix_1, input_matrix_2, output_matrix);
    cout << "Time: " << elapsed_time_kernel_matrix_multiplication << " ms" << endl;
    cout << endl;

    cout << "THRUST MATRIX MULTIPLICATION:" << endl;
    init_zero_matrix(output_matrix);
    float elapsed_time_thrust_matrix_multiplication = 0.0f;
    elapsed_time_thrust_matrix_multiplication = thrust_matrix_multiply(device_input_matrix_1, device_input_matrix_2, device_output_matrix);
    cudaMemcpy(output_matrix, device_output_matrix, NUM_ELEMENTS * sizeof(float), cudaMemcpyDeviceToHost);
    multiply_check(input_matrix_1, input_matrix_2, output_matrix);
    cout << "Time: " << elapsed_time_thrust_matrix_multiplication << " ms" << endl;
    cout << endl;

    cout << "CUBLAS MATRIX MULTIPLICATION:" << endl;
    init_zero_matrix(output_matrix);
    float elapsed_time_cublas_matrix_multiplication = 0.0f;
    elapsed_time_cublas_matrix_multiplication = cublas_matrix_multiply(device_input_matrix_1, device_input_matrix_2, device_output_matrix);
    cudaMemcpy(output_matrix, device_output_matrix, NUM_ELEMENTS * sizeof(float), cudaMemcpyDeviceToHost);
    multiply_check(input_matrix_1, input_matrix_2, output_matrix);
    cout << "Time: " << elapsed_time_cublas_matrix_multiplication << " ms" << endl;
    cout << endl;

    cout << "KERNEL SCALAR MULTIPLICATION:" << endl;
    init_zero_matrix(output_matrix);
    float elapsed_time_kernel_scalar_multiplication = 0.0f;
    elapsed_time_kernel_scalar_multiplication = kernel_scalar_multiply(device_input_matrix_1, device_output_matrix);
    cudaMemcpy(output_matrix, device_output_matrix, NUM_ELEMENTS * sizeof(float), cudaMemcpyDeviceToHost);
    scalar_check(input_matrix_1, output_matrix);
    cout << "Time: " << elapsed_time_kernel_scalar_multiplication << " ms" << endl;
    cout << endl;

    cout << "THRUST SCALAR MULTIPLICATION:" << endl;
    init_zero_matrix(output_matrix);
    float elapsed_time_thrust_scalar_multiplication = 0.0f;
    elapsed_time_thrust_scalar_multiplication = thrust_scalar_multiply(device_input_matrix_1, device_output_matrix);
    cudaMemcpy(output_matrix, device_output_matrix, NUM_ELEMENTS * sizeof(float), cudaMemcpyDeviceToHost);
    scalar_check(input_matrix_1, output_matrix);
    cout << "Time: " << elapsed_time_thrust_scalar_multiplication << " ms" << endl;
    cout << endl;

    cout << "CUBLAS SCALAR MULTIPLICATION:" << endl;
    init_zero_matrix(output_matrix);
    float elapsed_time_cublas_scalar_multiplication = 0.0f;
    elapsed_time_cublas_scalar_multiplication = cublas_scalar_multiply(device_input_matrix_1, device_output_matrix);
    cudaMemcpy(output_matrix, device_output_matrix, NUM_ELEMENTS * sizeof(float), cudaMemcpyDeviceToHost);
    scalar_check(input_matrix_1, output_matrix);
    cout << "Time: " << elapsed_time_cublas_scalar_multiplication << " ms" << endl;
    cout << endl;

    cout << "TOTAL RESULTS:" << endl;
    cout << "MATRIX SIZE = " << MATRIX_SIZE << " x " << MATRIX_SIZE << " (" << NUM_ELEMENTS << " elements)" << endl;
    cout << setw(40) << "raw CUDA, ms" << setw(15) << "Thrust, ms"
         << setw(15) << "cuBLSAS, ms" << endl;
    cout << fixed;
    cout << setw(25) << "Matrix transposing" << setw(15) << elapsed_time_kernel_transpose << setw(15) << elapsed_time_thrust_transpose << setw(15) << elapsed_time_cublas_transpose << endl;
    cout << setw(25) << "Matrix multiplication" << setw(15) << elapsed_time_kernel_matrix_multiplication << setw(15) << elapsed_time_thrust_matrix_multiplication << setw(15) << elapsed_time_cublas_matrix_multiplication << endl;
    cout << setw(25) << "Scalar multiplication" << setw(15) << elapsed_time_kernel_scalar_multiplication << setw(15) << elapsed_time_thrust_scalar_multiplication << setw(15) << elapsed_time_cublas_scalar_multiplication << endl;

    if (FILE_OUTPUT)
    {
        ofstream file;
        file.open("results.csv", ios::app);

        if (file.tellp() == streampos(0))
        {
            file << "Matrix size (n^2); MT (CUDA); MT (Thrust); MT (cuBLAS); MM (CUDA); MM (Thrust); MM (cuBLAS); SM (CUDA); SM (Thrust); SM (cuBLAS);" << endl;
        }

        file << MATRIX_SIZE << ";"
             << elapsed_time_kernel_transpose << ";" << elapsed_time_thrust_transpose << ";" << elapsed_time_cublas_transpose << ";"
             << elapsed_time_kernel_matrix_multiplication << ";" << elapsed_time_thrust_matrix_multiplication << ";" << elapsed_time_cublas_matrix_multiplication << ";"
             << elapsed_time_kernel_scalar_multiplication << ";" << elapsed_time_thrust_scalar_multiplication << ";" << elapsed_time_cublas_scalar_multiplication << ";"
             << endl;

        file.close();
    }

    return EXIT_SUCCESS;
}