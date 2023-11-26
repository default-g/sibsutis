#include <stdio.h>

#define WIDTH 3
#define HEIGHT 4

__global__ void transpose1(int *in, int *out) {
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;

    if (x < WIDTH && y < HEIGHT) {
        out[x * HEIGHT + y] = in[y * WIDTH + x];
    }
}


__global__ void transpose2(int *in, int *out) {
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;

    if (x < WIDTH && y < HEIGHT) {
        out[x + y * WIDTH] = in[y + x * HEIGHT];
    }
}


int main() {
    int in[WIDTH * HEIGHT];
	for (int i = 0; i < WIDTH * HEIGHT; i++) {
		in[i] = i;
	}
    int out[HEIGHT * WIDTH];

    int *d_in, *d_out, *d2_out;

    cudaMalloc((void **)&d_in, sizeof(int) * WIDTH * HEIGHT);
    cudaMalloc((void **)&d_out, sizeof(int) * HEIGHT * WIDTH);
    cudaMalloc((void **)&d2_out, sizeof(int) * HEIGHT * WIDTH);


    cudaMemcpy(d_in, in, sizeof(int) * WIDTH * HEIGHT, cudaMemcpyHostToDevice);

    dim3 grid((WIDTH + 15) / 16, (HEIGHT + 15) / 16);
    dim3 block(16, 16);

    transpose1<<<grid, block>>>(d_in, d_out);
    cudaDeviceSynchronize();
    transpose2<<<grid, block>>>(d_in, d2_out);
    cudaMemcpy(out, d_out, sizeof(int) * HEIGHT * WIDTH, cudaMemcpyDeviceToHost);



    cudaFree(d_in);
    cudaFree(d_out);
    cudaFree(d2_out);

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