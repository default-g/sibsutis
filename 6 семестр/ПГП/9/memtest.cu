#include <math.h>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cuda_runtime.h>

using namespace std;

#define EPS 6

int main(int argc, char **argv)
{
    int size = atoi(argv[1]);
    float *h_data, *d_data;
    float *h_data_pinned;
    FILE *csv_file = fopen("results_9/1.csv", "a+");
    if (fgetc(csv_file) == EOF)
    {
        fprintf(csv_file, "Size; S: D → H; P: D → H; S: H → D; P: H → D;\n");
    }

    // Allocate memory on the host
    h_data = (float *)malloc(size * sizeof(float));
    cudaMallocHost((void **)&h_data_pinned, size * sizeof(float));

    // Allocate memory on the device
    cudaMalloc((void **)&d_data, size * sizeof(float));

    // Initialize data on the device
    cudaMemset(d_data, 0, size * sizeof(float));
    cudaMemcpy(d_data, h_data, size * sizeof(float), cudaMemcpyHostToDevice);

    cout << "Testing memory copying (S - standart, P - pinned)" << endl;
    cout << "Size = " << size << endl;
    fprintf(csv_file, "%d; ", size);

    // Standard memory copy from device to host
    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);
    cudaEventRecord(start, 0);

    cudaMemcpy(h_data, d_data, size * sizeof(float), cudaMemcpyDeviceToHost);

    cudaEventRecord(stop, 0);
    cudaEventSynchronize(stop);

    float elapsedTime;
    cudaEventElapsedTime(&elapsedTime, start, stop);
    cout << "S: D → H = " << setprecision(EPS + 1) << elapsedTime << " ms" << endl;
    fprintf(csv_file, "%f; ", elapsedTime);

    // Pinned memory copy from device to host
    cudaStream_t stream;
    cudaStreamCreate(&stream);
    cudaEventRecord(start, 0);

    cudaMemcpyAsync(h_data_pinned, d_data, size * sizeof(float), cudaMemcpyDeviceToHost, stream);
    cudaStreamSynchronize(stream);

    cudaEventRecord(stop, 0);
    cudaEventSynchronize(stop);

    cudaEventElapsedTime(&elapsedTime, start, stop);
    cout << "P: D → H = " << setprecision(EPS) << elapsedTime << " ms" << endl;
    fprintf(csv_file, "%f; ", elapsedTime);

    // Standard memory copy from host to device
    cudaEventRecord(start, 0);

    cudaMemcpy(d_data, h_data, size * sizeof(float), cudaMemcpyHostToDevice);

    cudaEventRecord(stop, 0);
    cudaEventSynchronize(stop);

    cudaEventElapsedTime(&elapsedTime, start, stop);
    cout << "S: H → D = " << setprecision(EPS) << elapsedTime << " ms" << endl;
    fprintf(csv_file, "%f; ", elapsedTime);

    // Pinned memory copy from host to device
    cudaEventRecord(start, 0);

    cudaMemcpyAsync(d_data, h_data_pinned, size * sizeof(float), cudaMemcpyHostToDevice, stream);
    cudaStreamSynchronize(stream);

    cudaEventRecord(stop, 0);
    cudaEventSynchronize(stop);

    cudaEventElapsedTime(&elapsedTime, start, stop);
    cout << "P: H → D = " << setprecision(EPS) << elapsedTime << " ms" << endl
         << endl;
    fprintf(csv_file, "%f\n", elapsedTime);

    // Free memory
    cudaFree(d_data);
    free(h_data);
    cudaFreeHost(h_data_pinned);
    return 0;
}