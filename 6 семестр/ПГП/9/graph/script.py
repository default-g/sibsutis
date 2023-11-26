import matplotlib.pyplot as plt
import csv

import numpy as np

# Initialize data lists
size = []
elapsed_time_standard_dev_host = []
elapsed_time_pinned_dev_host = []
elapsed_time_standard_host_dev = []
elapsed_time_pinned_host_dev = []
chunk_size_sum = []
elapsed_time_sum = []
acceleration_sum = []
chunk_size_mul = []
elapsed_time_mul = []
acceleration_mul = []

# Read data from CSV file
with open('1.csv', 'r') as file:
    reader = csv.reader(file)
    next(reader) # Skip header row
    for row in reader:
        row_data = row[0].split(';')
        size.append(int(row_data[0]))
        elapsed_time_standard_dev_host.append(float(row_data[1]))
        elapsed_time_pinned_dev_host.append(float(row_data[2]))
        elapsed_time_standard_host_dev.append(float(row_data[3]))
        elapsed_time_pinned_host_dev.append(float(row_data[4]))

# Read data from CSV file
with open('2.csv', 'r') as file:
    reader = csv.reader(file)
    next(reader) # Skip header row
    for row in reader:
        row_data = row[0].split(';')
        chunk_size_sum.append(int(row_data[0]))
        elapsed_time_sum.append(float(row_data[1]))
        acceleration_sum.append(float(row_data[2]))

# Read data from CSV file
with open('3.csv', 'r') as file:
    reader = csv.reader(file)
    next(reader) # Skip header row
    for row in reader:
        row_data = row[0].split(';')
        chunk_size_mul.append(int(row_data[0]))
        elapsed_time_mul.append(float(row_data[1]))
        acceleration_mul.append(float(row_data[2]))

# Plot all four lines on one graph
plt.subplot(3, 1, 1)
plt.plot(size, elapsed_time_standard_dev_host, label='Standard Dev->Host')
plt.plot(size, elapsed_time_pinned_dev_host, label='Pinned Dev->Host')
plt.plot(size, elapsed_time_standard_host_dev, label='Standard Host->Dev')
plt.plot(size, elapsed_time_pinned_host_dev, label='Pinned Host->Dev')
plt.title('Comparison of Data Transfer Time Using Different Memory Types')
plt.xlabel('Data Size')
plt.ylabel('Transfer Time (ms)')
plt.xscale('log')
plt.yscale('log')
plt.xticks([10**i for i in range(10)], [f'$10^{i}$' for i in range(10)])
plt.legend()

plt.subplot(3, 2, 3)
plt.plot(chunk_size_sum, elapsed_time_sum, label='Elapsed time')
plt.title('Vector addition using CUDA Streams and memory chunks')
plt.xlabel('Chunk Size')
plt.ylabel('Transfer Time (ms)')
plt.xscale('log')
#plt.yscale('log')
plt.xticks(chunk_size_sum, [f'2^{i}' for i in range(1, 15)])
plt.legend()

plt.subplot(3, 2, 4)
plt.plot(chunk_size_sum, acceleration_sum, label='Acceleration')
plt.title('Acceleration of vector addition')
plt.xlabel('Chunk Size')
plt.xscale('log')
#plt.yscale('log')
plt.xticks(chunk_size_sum, [f'2^{i}' for i in range(1, 15)])
plt.axhline(y=0.0, linestyle='--', color='black')
plt.legend()

plt.subplot(3, 2, 5)
plt.plot(chunk_size_mul, elapsed_time_mul, label='Elapsed time')
plt.title('Scalar vector multiplication using CUDA Streams and memory chunks')
plt.xlabel('Chunk Size')
plt.ylabel('Transfer Time (ms)')
plt.xscale('log')
#plt.yscale('log')
plt.xticks(chunk_size_mul, [f'2^{i}' for i in range(1, 15)])
plt.legend()

plt.subplot(3, 2, 6)
plt.plot(chunk_size_mul, acceleration_mul, label='Acceleration')
plt.title('Acceleration of scalar vector multiplication')
plt.xlabel('Chunk Size')
plt.xscale('log')
#plt.yscale('log')
plt.xticks(chunk_size_mul, [f'2^{i}' for i in range(1, 15)])
plt.axhline(y=0.0, linestyle='--', color='black')
plt.legend()

plt.show()
