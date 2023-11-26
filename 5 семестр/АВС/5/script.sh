#!/bin/bash

g++ *.cpp -o main -pthread -fopenmp



./main 5000 1 0
./main 5000 2 0
./main 5000 4 0
./main 5000 6 0
./main 5000 8 0


./main 5000 1 1
./main 5000 2 1
./main 5000 4 1
./main 5000 6 1
./main 5000 8 1


