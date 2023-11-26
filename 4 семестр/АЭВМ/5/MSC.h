#ifndef simplcomp_h
#define simplcomp_h

#include <stdint.h>
#include <stdio.h>
#include <memory.h>
#include <math.h>
#include <stdlib.h>

#define SIZE 100
#define OVERFLOW 1
#define ZERO_ERR 2
#define OUT_OF_MEM 3
#define IGNR_CLOCK 4
#define COMMAND_ERROR 5

int ram[SIZE];
int flags;
int Pointer;

void errorHandler(int);
int sc_memoryInit();
int sc_memorySet(int, int);
int sc_memoryGet(int, int*);
int sc_memorySave(char*);
int sc_memoryLoad(char*);
int sc_regInit();
int sc_regSet(int, int);
int sc_regGet(int, int*);
int sc_commandEncode(int, int, int*);
int sc_commandDecode(int, int*, int*);

#endif
