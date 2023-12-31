#include <stdio.h>

#define SC_F_OM 1 // ошибка выхода за границы памяти
#define SC_F_IG 2 // игнорирование тактовых импульсов
#define SC_F_DZ 4 // ошибка деления на 0
#define SC_F_OV 8 // переполнение при выполнение операции
#define SC_F_UN 16 // указана неверная команда

int sc_memoryInit();
int sc_memorySet(int address, int value);
int sc_memoryGet(int address, int * value);
int sc_memorySave (char * filename);
int sc_memoryLoad (char * filename);
int sc_regInit (void);
int sc_regSet (int reg, int value);
int sc_regGet (int reg, int * value);
int sc_commandEncode (int command, int operand, int * value);
int sc_commandDecode (int value, int * command, int * operand);