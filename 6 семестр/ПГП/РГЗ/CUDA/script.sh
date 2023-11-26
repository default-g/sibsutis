nvcc -o cuda_main src/main.cu -ccbin g++-10 --expt-extended-lambda -lcublas -I src/lib/ -std=c++11
./cuda_main

rm *_main