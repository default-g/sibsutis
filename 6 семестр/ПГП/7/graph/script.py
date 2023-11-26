import matplotlib.pyplot as plt
import csv


sizes = []
time_cuda_api = []
time_thrust = []

with open('dot_product.csv', newline='') as csvfile:
    reader = csv.reader(csvfile, delimiter=';')
    for row in reader:
        sizes.append(int(float(row[0])))
        time_cuda_api.append(float(row[1]))
        time_thrust.append(float(row[2]))

figure, axis = plt.subplots(2, 1)

axis[0].plot(sizes, time_cuda_api, label="CUDA API")
axis[0].plot(sizes, time_thrust, label="THRUST")
axis[0].set_title('Dot production')
axis[0].legend()

sizes = []
time_cuda_api = []
time_thrust = []

with open('transpose.csv', newline='') as csvfile:
    reader = csv.reader(csvfile, delimiter=';')
    for row in reader:
        sizes.append(int(float(row[0])))
        time_cuda_api.append(float(row[1]))
        time_thrust.append(float(row[2]))


axis[1].plot(sizes, time_cuda_api, label="CUDA API")
axis[1].plot(sizes, time_thrust, label="THRUST")
axis[1].set_title('Transposition')
axis[1].legend()


plt.show()