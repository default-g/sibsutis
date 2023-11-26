import matplotlib.pyplot as mp




data = []
file = open('data_cuda.txt', 'r')

for line in file.readlines():
    line = line.split()
    time = float(line[0])
    size = float(line[1])
    data.append([time, size])

print(data)

x_axis = [item[0] for item in data]
y_axis = [item[1] for item in data]
# mp.subplot(2, 1, 1)
mp.plot(y_axis, x_axis)
mp.title('posix')
mp.legend()

    
mp.show()