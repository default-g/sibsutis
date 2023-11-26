#!/usr/bin/env bash

nm  -g -C  --defined-only liblist_functions.so
g++ main.cpp -o main
./main liblist_functions.so