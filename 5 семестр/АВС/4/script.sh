#!/bin/bash

g++ main.cpp -o main

for ((idx=1000;idx<=6000;idx += 1000 ))do
    ./main ${idx} 0
done

for ((idx=1000;idx<=6000;idx += 1000 ))do
    ./main ${idx} 1
done