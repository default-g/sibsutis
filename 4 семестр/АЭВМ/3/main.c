#include <stdio.h>
#include "myTerm.h"
#include "myBigChars.h"
#include "lib.h"

int main() {
	mt_clrscr();

	enum colors blue = blue;
	enum colors red = red;
	
	char  str[]  = "";
	sc_memoryInit();
  sc_regInit();
  sc_memorySet(0, 10);
  int tmp = 7;

  sc_memoryGet(0, &tmp);

//	for (int i=0; i<16; i++) {
//		bc_printbigchar(str[i], 0, 0, blue, red);
//		printf("\n");
//	}
  sprintf(str, "%x", tmp);
  char newchars[4];
  //printf("%s", str);
  //bc_printStr(str, 0, 0, MT_RED, MT_BLACK);
  for(int i = 0; i < 4; i++) {
      if(str[i] == NULL) {
        newchars[3 - i] = '0';
      } else {
        newchars[3 - i] = str[i];
      }
  }
  bc_printStr(newchars, 0, 0, MT_WHITE, MT_BLACK);

  
	//bc_printbigchar( , 1, 30, MT_WHITE, MT_BLACK);
 // bc_printbigchar( str[0], 10,10, MT_RED, MT_BLACK);
  
}