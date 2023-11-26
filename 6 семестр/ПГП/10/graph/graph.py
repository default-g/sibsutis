import matplotlib.pyplot as plt
import csv
import numpy as np

# Initialize data lists
size = []
elapsed_time_cublas = []
elapsed_time_numpy = []
delta = []

# Read data from CSV file
with open('cublas_res.csv', 'r') as file:
    reader = csv.reader(file)
    for row in reader:
        row_data = row[0].split(';')
        size.append(int(row_data[0]))
        elapsed_time_cublas.append(float(row_data[1]))

# Read data from CSV file
with open('numpy_res.csv', 'r') as file:
    reader = csv.reader(file)
    for row in reader:
        row_data = row[0].split(';')
        elapsed_time_numpy.append(float(row_data[1]))


plt.plot(size, elapsed_time_cublas, label='cuBLAS')
plt.plot(size, elapsed_time_numpy, label='numpy.matmul')
plt.title('Comparison of matrix multiplication: cuBLAS vs numpy.matmul')
plt.xlabel('Matrix size')
plt.ylabel('Time (ms)')
# plt.gca().set_xscale('log', basex=2) # set base 2 for x-axis
plt.legend()


plt.show()

