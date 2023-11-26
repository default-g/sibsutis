import csv
import matplotlib.pyplot as plt

# создаем списки для каждого параметра CUDA
with open('results.csv', 'r') as file:
    matrix_sizes = []
    cuda_mt = []
    thrust_mt = []
    cublas_mt = []
    cuda_mm = []
    thrust_mm = []
    cublas_mm = []
    cuda_sm = []
    thrust_sm = []
    cublas_sm = []
    
    lines = file.readlines()
    for line in lines[1:]:
        values = line.split(';')
        matrix_sizes.append(int(values[0]))
        cuda_mt.append(float(values[1]))
        thrust_mt.append(float(values[2]))
        cublas_mt.append(float(values[3]))
        cuda_mm.append(float(values[4]))
        thrust_mm.append(float(values[5]))
        cublas_mm.append(float(values[6]))
        cuda_sm.append(float(values[7]))
        thrust_sm.append(float(values[8]))
        cublas_sm.append(float(values[9]))

# создаем списки для каждого параметра OpenGL
with open('results_opengl.csv', 'r') as file:
    opengl_mt = []
    opengl_mm = []
    opengl_sm = []
    
    lines = file.readlines()
    for line in lines[1:]:
        values = line.split(';')
        opengl_mt.append(float(values[1]))
        opengl_mm.append(float(values[2]))
        opengl_sm.append(float(values[3]))

        
    
# создаем графики для каждого параметра
fig, axs = plt.subplots(3, 1)



# First subplot
axs[0].plot(matrix_sizes, cuda_mt, label='Matrix Transposing (CUDA)')
axs[0].plot(matrix_sizes, thrust_mt, label='Matrix Transposing (Thrust)')
axs[0].plot(matrix_sizes, cublas_mt, label='Matrix Transposing (cuBLAS)')
axs[0].plot(matrix_sizes, opengl_mt, label='Matrix Transposing (OpenGL)')
axs[0].set_title('Matrix Transposing')
axs[0].set_xlabel('Matrix size (n^2)')
axs[0].set_ylabel('Time (ms)')
axs[0].legend()

# Second subplot
axs[1].plot(matrix_sizes, cuda_mm, label='Matrix Multiplication (CUDA)')
axs[1].plot(matrix_sizes, thrust_mm, label='Matrix Multiplication (Thrust)')
axs[1].plot(matrix_sizes, cublas_mm, label='Matrix Multiplication (cuBLAS)')
axs[1].plot(matrix_sizes, opengl_mm, label='Matrix Multiplication (OpenGL)')
axs[1].set_title('Matrix Multiplication')
axs[1].set_xlabel('Matrix size (n^2)')
axs[1].set_ylabel('Time (ms)')
axs[1].legend()

# Third subplot
axs[2].plot(matrix_sizes, cuda_sm, label='Scalar Multiplication (CUDA)')
axs[2].plot(matrix_sizes, thrust_sm, label='Scalar Multiplication (Thrust)')
axs[2].plot(matrix_sizes, cublas_sm, label='Scalar Multiplication (cuBLAS)')
axs[2].plot(matrix_sizes, opengl_sm, label='Scalar Multiplication (OpenGL))')
axs[2].set_title('Scalar Multiplication')
axs[2].set_xlabel('Matrix size (n^2)')
axs[2].set_ylabel('Time (ms)')
axs[2].legend()

plt.show()
