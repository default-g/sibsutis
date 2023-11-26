#ifndef MY_BIG_CHARS_H_   /* Include guard */
#define MY_BIG_CHARS_H_

#include <stdio.h>
#include <unistd.h>
#include "myTerm.h"

int bc_printA (char * str);
int bc_box(int x1, int y1, int x2, int y2);
int bc_printbigchar(char ch, int x, int y, enum colors fgcolor, enum colors bgcolor);
int bc_bigcharread (int fd, int * big, int need_count, int *count);
int bc_setbigcharpos (int * big, int x, int y, int value);
int bc_getbigcharpos (int * big, int x, int y, int *value);
int bc_bigcharwrite (int fd, int * big, int count);
void bc_printStr(char* str, int x, int y, enum colors fgcolor, enum colors bgcolor);


#endif