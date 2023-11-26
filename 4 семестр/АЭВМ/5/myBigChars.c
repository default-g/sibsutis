#include "myBigChars.h"

int bc_printA (char * str)
{
	printf("\E(0%s", str);
	printf("\E(B");
}

void bc_bigcharLayout(int *A, int number)
{
  number = number % 16;
  switch(number)
  {
    case 0:
      A[0] = 1010975298;
      A[1] = 1111638588;
      break;
    case 1:
      A[0] = 808464432;
      A[1] = 808467512;
      break;
    case 2:
      A[0] = 1006897168;
      A[1] = 539239484;
      break;
    case 3:
      A[0] = 1009000496;
      A[1] = 539239484;
      break;
    case 4:
      A[0] = 538976288;
      A[1] = 1009001508;
      break;
    case 5:
      A[0] = 1008738336;
      A[1] = 1006896188;
      break;
    case 6:
      A[0] = 1009001532;
      A[1] = 67372092;
      break;
    case 7:
      A[0] = 538976368;
      A[1] = 538976316;
      break;
    case 8:
      A[0] = 405021732;
      A[1] = 405021720;
      break;
    case 9:
      A[0] = 1009000480;
      A[1] = 1009001532;
      break;
    case 10: //a
      A[0] = 405021752;
      A[1] = 538977340;
      break;
    case 11: //b
      A[0] = 405021724;
      A[1] = 67372036;
      break;
    case 12: //c
      A[0] = 405013508;
      A[1] = 67380248;
      break;
    case 13: //d
      A[0] = 405021752;
      A[1] = 538976288;
      break;
    case 14: //e
      A[0] = 405013508;
      A[1] = 1009001496;
      break;
    case 15: //f
      A[0] = 67372046;
      A[1] = 67380248;
      break;
    default:
      return;
    }
}

int bc_printbigchar(int *A, int x, int y, enum colors clr1, enum colors clr2)
{
  mt_gotoXY(x, y);
  mt_setgbcolor(clr1);
  mt_setfgcolor(clr2);
  int k = 1;
  for(int i = 0; i < 8; i++)
  {
    for(int j = 0; j < 8; j++)
    { 
      if(i==4) k = 0;
      if(A[k] % 2)
	bc_printA("\u2588");
      else
        bc_printA(" ");
      A[k] = A[k] >> 1;
      mt_gotoXY(x, y+j+1);
    }
    x++;
    mt_gotoXY(x, y);
  }
  mt_setgbcolor(9);
  mt_setfgcolor(9);
}

int bc_box(int x1, int y1, int x2, int y2)
{
  mt_gotoXY(y1, x1); //upper
  printf("\u250C");
  for(int i = 0; i < x2-x1; i++)
  {
   bc_printA("\u2500");
  }
  bc_printA("\u2510");

  for(int i = 0; i < y2-y1; i++) //leftright
  {
    mt_gotoXY(y1+i+1, x1);
    bc_printA("\u2502");
    mt_gotoXY(y1+i+1, x2+1);
    bc_printA("\u2502");
  }

  mt_gotoXY(y2+1, x1); //lower
  bc_printA("\u2514");
  for(int i = 0; i < x2-x1; i++)
  {
    bc_printA("\u2500");
  }
  bc_printA("\u2518");
}

int bc_setbigcharpos(int * big, int x, int y, int value)
{
    if((value != 0 && value != 1) || x < 1 || x > 8 || y < 1 || y > 8)
        return -1;
    if(value == 1)
    {
        big[y/5] |= 1 << ((y - 1) * 8 + x -1);
        return 0;
    }
    if(value == 0)
    {
        big[y/5] &= ~(1 << ((y - 1) * 8 + x - 1));
        return 0;
    }
    return -1;
}

int bc_getbigcharpos(int * big, int x, int y, int *value)
{
    if(x < 1 || x > 8 || y < 1 || y > 8)
        return -1;
    *value = (big[y/5] >> ((y - 1) * 8 + x - 1)) & 0x1;
    return 0;
}

int bc_bigcharwrite(int fd, int * big, int count)
{
    write(fd, big, sizeof(count) * 2 * count);
    close(fd);
    return 0;
}

int bc_bigcharread(int fd, int * big, int need_count, int * count)
{
    *count = read(fd, big, sizeof(need_count) * 2 * need_count) / 8;
    if(*count == 0)
        return -1;
    close(fd);
    return 0;
}

