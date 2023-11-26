#include <stdio.h>
#include <stdio.h>
#include <sys/ioctl.h>

#define SC_F_OM 1 // ошибка выхода за границы памяти
#define SC_F_IG 2 // игнорирование тактовых импульсов
#define SC_F_DZ 4 // ошибка деления на 0
#define SC_F_OV 8 // переполнение при выполнение операции
#define SC_F_UN 16 // указана неверная команда


enum colors {
        MT_BLACK,
        MT_RED,
        MT_GREEN,
        MT_YELLOW,
        MT_BLUE,
        MT_VIOLET,
        MT_BIRUZ,
        MT_WHITE
};

int mt_clrscr (void);
int mt_setbgcolor (enum colors color);
int mt_setfgcolor (enum colors color);
int mt_getscreensize(int *rows, int *cols);
int mt_gotoXY (int x, int y);



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