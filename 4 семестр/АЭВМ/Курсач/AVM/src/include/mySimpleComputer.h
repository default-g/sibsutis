#ifndef MYSIMPLECOMPUTER
#define MYSIMPLECOMPUTER
#define SIZE 100
#pragma once


#define P 0b00000001	// переполнение при выполнение операции
#define O 0b00000010	// ошибка деления на 0
#define M 0b00000100	// ошибка выхода за границы массива
#define T 0b00001000	// игнорирование тактовых импульсов
#define E 0b00010000    // указана неверная команда

#include <stdio.h>

extern int RAM[100];

extern int flag;

int sc_memoryInit();

int sc_memorySet(int address, int value);

int sc_memoryGet(int address, int *value);

int sc_memorySave(const char *filename);

int sc_memoryLoad(const char *filename);

int sc_regInit();

int sc_regSet(int reg, int value);

int sc_regGet(int reg, int *value);

int sc_commandEncode(int command, int operand, int *value);

int sc_commandDecode(int value, int *command, int *operand);

#endif
