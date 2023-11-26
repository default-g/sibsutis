#ifndef MY_TERM_H_   /* Include guard */
#define MY_TERM_H_

#include <stdio.h>
#include <stdio.h>
#include <sys/ioctl.h>

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

#endif