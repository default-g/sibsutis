import matplotlib.pyplot as plt
import csv


sizes = []
time_cuda_api = []
time_thrust = []

with open('multiplication.csv', newline='') as csvfile:
    reader = csv.reader(csvfile, delimiter=';')
    for row in reader:
        sizes.append(int(float(row[0])))
        time_cuda_api.append(float(row[1]))
        time_thrust.append(float(row[2]))

plt.plot(sizes, time_cuda_api, label="CUDA API")
plt.plot(sizes, time_thrust, label="CUBLAS")
plt.suptitle('Matrix multiplication')
plt.legend()


plt.show()