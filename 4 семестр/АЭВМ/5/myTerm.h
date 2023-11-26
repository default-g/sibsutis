#pragma once

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>

enum colors 
{ 
	black, red, green, yellow, blue, lilac, tarquoise,  gray, nope, white
};
			
int mt_clrscr();
int mt_gotoXY(int x, int y);
int mt_getscreensize(unsigned int *rows, unsigned int *cols);
int mt_setfgcolor(enum colors x);
int mt_setgbcolor(enum colors x);

