#ifndef myReadKey_h
#define myReadKey_h

#include <stdio.h>
#include "myTerm.h"
#include <inttypes.h>
#include <fcntl.h>

#include <termios.h>
#include <sys/ioctl.h>


#include <unistd.h>
#include <time.h>
#include <sys/time.h>

struct termios termState; // dlya izm
struct termios termStateDefault; // ne izm
struct termios termStateSave; // vrmemenn

enum keys
{
  up, down, left, right, Save, Load, Run, sTep, Input, f5, f6, incorrectkey, Quit, Reset, IgnrCancel
};

int rk_mytermregime(int, int, int, int, int);
void rk_mytermsave();
void rk_mytermrestore();
int rk_readkey(enum keys*);

#endif
