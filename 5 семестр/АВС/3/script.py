import matplotlib.pyplot as mp
import csv

data = []

with open('file.csv') as csv_file:
    csv_reader = csv.reader(csv_file, delimiter=';')
    for row in csv_reader:
        data.append(row)

x_axis = set()

first_graphs_data = data[1:81]


for row in first_graphs_data:
    x_axis.add(float(row[1]))

dict_y = {}

for row in first_graphs_data:
    if not row[0] in dict_y.keys():
         dict_y[row[0]] = []
    dict_y[row[0]].append(float(row[8]))


fix, ax = mp.subplots(3, 2)

for key in dict_y.keys():
    ax[0, 0].plot(sorted(list(x_axis)), dict_y[key], label = str(key))
    
ax[0, 0].set_title('WriteBandWidth')
ax[0, 0].legend()

dict_y = {}

for row in first_graphs_data:
    if not row[0] in dict_y.keys():
        dict_y[row[0]] = []
    dict_y[row[0]].append(float(row[13]))    

print(dict_y) 


for key in dict_y.keys():
    ax[0, 1].plot(sorted(list(x_axis)), dict_y[key], label = str(key))

ax[0, 1].set_title('ReadBandWidth')
ax[0, 1].legend()


dict_y = {}

for row in first_graphs_data:
    if not row[0] in dict_y.keys():
        dict_y[row[0]] = []
    dict_y[row[0]].append(float(row[10])) 
     
for key in dict_y.keys():
    ax[1, 0].plot(sorted(list(x_axis)), dict_y[key], label = str(key))

ax[1, 0].set_title('RelErrorWrite')
ax[1, 0].legend()     
dict_y = {}

for row in first_graphs_data:
    if not row[0] in dict_y.keys():
        dict_y[row[0]] = []
    dict_y[row[0]].append(float(row[15])) 
     
for key in dict_y.keys():
    ax[1, 1].plot(sorted(list(x_axis)), dict_y[key], label = str(key))

ax[1, 1].set_title('RelErrorRead')
ax[1, 1].legend()     

y_axis = []
x_axis = []
second_graphs_data = data[82:]

for row in second_graphs_data:
    x_axis.append(int(row[4]))
    y_axis.append(float(row[10]))

ax[2, 0].plot(x_axis, y_axis)
ax[2, 0].set_title('RelErrorWrite - Launch Count')

y_axis = []
x_axis = []

for row in second_graphs_data:
    x_axis.append(int(row[4]))
    y_axis.append(float(row[15]))
    
ax[2, 1].plot(x_axis, y_axis)
ax[2, 1].set_title('RelErrorRead - Launch Count')



mp.show()    
    