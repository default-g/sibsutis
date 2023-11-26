#include <stdio.h>
#include "myTerm.h"

int main() {
		
	unsigned int x = 0, y = 0, d, R = 2, C = 1;
	
	unsigned int *row = &x, *col = &y;
	
	mt_clrscr();
	mt_clrscr();
	d = mt_getscreensize(row, col);
	
	d = mt_gotoXY(*row/(*row), *col/4);
	write(1, "Memory", 6);
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			d = mt_gotoXY(R, C);
			write(1, "+0000", 5);
			C = C + 6;	
		}
		C = 1;
		R = R + 1;
	}
	
	d = mt_gotoXY(1, *col-18);
	write(1, "Flags", 5);

	d = mt_gotoXY(2, *col-19);
	write(1, "O", 1);
	d = mt_gotoXY(2, *col-17);
	write(1, "E", 1);
	d = mt_gotoXY(2, *col-15);
	write(1, "V", 1);
	d = mt_gotoXY(2, *col-13);
	write(1, "M", 1);

	d = mt_gotoXY(4, *col-18);
	write(1, "Keys:", 5);
	d = mt_gotoXY(5, *col-19);
	write(1, "l  -  load", 10);
	d = mt_gotoXY(6, *col-19);
	write(1, "s  -  save", 10);
	d = mt_gotoXY(7, *col-19);
	write(1, "r  -  run", 9);
	d = mt_gotoXY(8, *col-19);
	write(1, "t  -  step", 10);
	d = mt_gotoXY(9, *col-19);
	write(1, "i  -  reset", 11);
	d = mt_gotoXY(10, *col-19);
	write(1, "F5 -  accumulator", 17);
	d = mt_gotoXY(11, *col-19);
	write(1, "F6 -  instrCounter", 18);

	d = mt_gotoXY(12, 1);

	


	
	

/*
	d = mt_gotoXY(*row/2, *col/2);
	d = mt_setfgcolor(red);
	d = mt_setgbcolor(blue);
	write(1, "tet", 3);
	d = mt_setfgcolor(yellow);
	d = mt_setgbcolor(red);
	write(1, "ris\n", 4);
	
	y = mt_setfgcolor(9);
	y = mt_setgbcolor(9);*/
	return 0;
}
