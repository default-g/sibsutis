#ifndef myBigChars_h
#define myBigChars_h

#include <sys/ioctl.h>
#include <stdio.h>
#include "myTerm.h"
#include <inttypes.h>
#include <fcntl.h>

void bc_bigcharLayout(int*, int);
int bc_printA (char* str);
int bc_box(int, int, int, int);
int bc_printbigchar(int*, int, int, enum colors, enum colors);
int bc_setbigcharpos(int *big, int x, int y, int value);
int bc_getbigcharpos(int *big, int x, int y, int *value);
int bc_bigcharwrite(int fd, int * big, int count);
int bc_bigcharread(int fd, int * big, int need_count, int *count);

#endif
