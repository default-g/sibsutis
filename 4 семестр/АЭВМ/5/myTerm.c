#include "myTerm.h"

int mt_clrscr() {
	int chk;

	chk = write(1, "\E[H\E[J", 6);
	if (chk == 6)
		return 0;
	else
		return -1;
}

int mt_gotoXY(int x, int y) {
	char buf[100];
	int chk;
	
	sprintf(buf, "%s%d%c%d%c", "\E[", x, ';', y, 'H');
	chk = write(1, buf, strlen(buf));
	
	if (chk == strlen(buf))
		return 0;
	else
		return -1;
}

int mt_getscreensize (unsigned int *rows, unsigned int *cols) {
	struct winsize ws;
	
	if (!ioctl(1, TIOCGWINSZ, &ws)) {
		*rows = ws.ws_row;
		*cols = ws.ws_col;
		return 0;
	} else
		return -1;
}
int mt_setfgcolor(enum colors x) {
	char buf[100];
	int chk;
	
	sprintf(buf, "%s%d%c", "\E[3", x, 'm');
	chk = write(1, buf, strlen(buf));
	
	if (chk == strlen(buf))
		return 0;
	else
		return -1;
}

int mt_setgbcolor(enum colors x) {
	char buf[100];
	int chk;
	
	sprintf(buf, "%s%d%c", "\E[4", x, 'm');
	chk = write(1, buf, strlen(buf));
	
	if (chk == strlen(buf))
		return 0;
	else
		return -1;
}
