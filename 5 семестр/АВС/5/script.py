import matplotlib.pyplot as mp
import csv

data = []

with open('file.csv') as csv_file:
    csv_reader = csv.reader(csv_file, delimiter=';')
    for row in csv_reader:
        data.append(row)


posix_graph_data = data[:5]
omp_graph_data = data[5:]
print(posix_graph_data)
print(omp_graph_data)

x_axis = []
y_axis = []
for item in posix_graph_data:
    x_axis.append(int(item[1]))
    y_axis.append(float(  float(posix_graph_data[0][2]) / float(item[2])))
    
mp.plot(x_axis, y_axis, label="POSIX")

x_axis = []
y_axis = []
for item in omp_graph_data:
    x_axis.append(int(item[1]))
    y_axis.append(float(  float(omp_graph_data[0][2]) / float(item[2])))
    
mp.plot(x_axis, y_axis, label="OPENMP")

mp.legend()
mp.show()
    