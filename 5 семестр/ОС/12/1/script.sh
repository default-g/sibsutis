#!/usr/bin/env bash
gcc -c lab12d3.c -o lab12d3
gcc -c lab12d1.c -o lab12d1
gcc -c lab12d2.c -o lab12d2
gcc lab12d3 lab12d1 -o 1program
gcc lab12d3 lab12d2 -o 2program