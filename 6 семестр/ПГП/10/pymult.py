import numpy as np
import sys
import time

start_time_total = time.time_ns()
if len(sys.argv) < 2:
    print("Please specify the size of the matrix as a command-line argument.")
    sys.exit()

N = int(sys.argv[1])

A = np.full((N, N), 0)
B = np.full((N, N), 0)

for i in range(N*N):
    A.fill(i)
    B.fill(i)

start_time = time.time_ns()
C = np.matmul(A, B)
end_time = time.time_ns()

elapsed_time = (end_time - start_time) / 1000000

print("numpy: {}^2 / {:.6f} ms".format(N, elapsed_time))

# save the results to a CSV file
with open('numpy_res.csv', 'a+') as f:
    f.write("{};{:.6f}\n".format(N*N, elapsed_time))

end_time_total = time.time_ns()
print("numpy: Total time {:.6f} ms".format((end_time_total - start_time_total) / 1000000))
