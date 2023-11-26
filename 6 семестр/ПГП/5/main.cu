#include <stdio.h>

#define WIDTH 4
#define HEIGHT 4
#define BLOCK_SIZE 32


__global__ void transposeNaive(int *in, int *out) {
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;

    if (x < HEIGHT && y < WIDTH) {
        out[x + y * HEIGHT] = in[y + x * WIDTH];
    }
}


__global__ void transposeNaiveWithSharedMemory(int *in, int *out) {
    __shared__ int cache[BLOCK_SIZE][BLOCK_SIZE];
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;

    if (x < WIDTH && y < HEIGHT) {
        cache[threadIdx.y][threadIdx.x] = in[y * WIDTH + x];
    }
    __syncthreads();
    
    x = blockIdx.x * blockDim.x + threadIdx.x;
    y = blockIdx.y * blockDim.y + threadIdx.y;

     if (x < HEIGHT && y < WIDTH) {
        out[y * HEIGHT + x] = cache[threadIdx.x][threadIdx.y];
    }
}


__global__ void transposeWithUsingOfSharedMemoryAndBankConflictResolution(int *in, int *out) {
    __shared__ int tile[BLOCK_SIZE][BLOCK_SIZE + 1];
    int x = blockIdx.x * BLOCK_SIZE + threadIdx.x;
    int y = blockIdx.y * BLOCK_SIZE + threadIdx.y;

    for (int j = 0; j < BLOCK_SIZE; j += blockDim.y)
    {
        if (x < WIDTH && y + j < HEIGHT)
        {
            int index_in = (y + j) * WIDTH + x;
            tile[threadIdx.y + j][threadIdx.x] = in[index_in];
        }
    }

    __syncthreads();

    x = blockIdx.y * BLOCK_SIZE + threadIdx.x;
    y = blockIdx.x * BLOCK_SIZE + threadIdx.y;
    for (int j = 0; j < BLOCK_SIZE; j += blockDim.y)
    {
        if (x < HEIGHT && y + j < WIDTH)
        {
            int index_out = (y + j) * HEIGHT + x;
            out[index_out] = tile[threadIdx.x][threadIdx.y + j];
        }
    }
     
}




int main() {
    int in[WIDTH * HEIGHT];
	for (int i = 0; i < WIDTH * HEIGHT; i++) {
		in[i] = i;
	}
    int out[HEIGHT * WIDTH];

    int *d_in, *d_out, *d2_out, *d3_out;

    cudaMalloc((void **)&d_in, sizeof(int) * WIDTH * HEIGHT);
    cudaMalloc((void **)&d_out, sizeof(int) * HEIGHT * WIDTH);
    cudaMalloc((void **)&d2_out, sizeof(int) * HEIGHT * WIDTH);
    cudaMalloc((void **)&d3_out, sizeof(int) * HEIGHT * WIDTH);

    cudaMemcpy(d_in, in, sizeof(int) * WIDTH * HEIGHT, cudaMemcpyHostToDevice);

    dim3 grid((WIDTH + 31) / 32, (HEIGHT + 31) / 32);
    dim3 block(BLOCK_SIZE, BLOCK_SIZE);

    cudaDeviceSynchronize();
    transposeNaive<<<grid, block>>>(d_in, d_out);
    cudaDeviceSynchronize();
    transposeNaiveWithSharedMemory<<<grid, block>>>(d_in, d2_out);
    cudaDeviceSynchronize();
    transposeWithUsingOfSharedMemoryAndBankConflictResolution<<<grid, block>>>(d_in, d3_out);


    cudaMemcpy(out, d3_out, sizeof(int) * HEIGHT * WIDTH, cudaMemcpyDeviceToHost);

    cudaFree(d_in);
    cudaFree(d_out);
    cudaFree(d2_out);
    cudaFree(d3_out);

    printf("Input matrix:\n");
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("%d ", in[i * WIDTH + j]);
        }
        printf("\n");
    }

    printf("Output matrix:\n");
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            printf("%d ", out[i * HEIGHT + j]);
        }
        printf("\n");
    }

    return 0;
}