#include "myBigChars.h"
#include <string.h> // Для strlen

#define MASK 0b00000000000000000000000000000001
/*
int bc_printA (char * str) - выводит строку символов с использованием допол-
нительной кодировочной таблицы;
*/
int bc_printA(char* str) {
	printf("\E(0%s\E(B", str);
	return 0;
}

/*
int bc_box(int x1, int y1, int x2, int y2) - выводит на экран псевдогра-
фическую рамку, в которой левый верхний угол располагается в строке x1 и столбце
y1, а еѐ ширина и высота равна y2 столбцов и x2 строк;
*/
int bc_box(int x1, int y1, int x2, int y2) {
    int i;
    if ((x1<0)||(x2<0)||(y1<0)||(y2<0)) {
        return 2;
    }
    for (i=x1; i < (x1+x2); i++) {
        mt_gotoXY(i, y1);
        bc_printA("│");
        mt_gotoXY(i, y1+y2);
        bc_printA("│");
    }
    for (i=y1; i < (y1+y2); i++) {
        mt_gotoXY(x1, i);
        bc_printA("─");
        mt_gotoXY(x1+x2, i);
        bc_printA("─");
    }
    mt_gotoXY(x1, y1);
    bc_printA("┌");
    mt_gotoXY(x1+x2, y1);
    bc_printA("└");
    mt_gotoXY(x1, y1+y2);
    bc_printA("┐");
    mt_gotoXY(x1+x2, y1+y2);
    bc_printA("┘");
    return 0;
}

/*
int bc_printbigchar (int [2], int x, int y, enum color, enum color) -
выводит на экран "большой символ" размером восемь строк на восемь столбцов, левый
верхний угол которого располагается в строке x и столбце y. Третий и четвѐртый па-
раметры определяют цвет и фон выводимых символов. "Символ" выводится исходя из
значений массива целых чисел следующим образом. В первой строке выводится 8
младших бит первого числа, во второй следующие 8, в третьей и 4 следующие. В 5
строке выводятся 8 младших бит второго числа и т.д. При этом если значение бита = 0,
то выводится символ "пробел", иначе - символ, закрашивающий знакоместо
(ACS_CKBOARD);
*/
int bc_printbigchar(char ch, int x, int y, enum colors fgcolor, enum colors bgcolor) {
	
	
	int table[16][2] = {{606348348, 1009001508},
			    {269752336, 1007685648},
			    {1008738364, 1006896132},
			    {1008738364, 1008738336},
			    {1009001508, 538976288},
			    {1006896188, 1008738336},
			    {1006896188, 1009001508},
			    {538976316, 538976288},
			    {1009001532, 1009001508},
			    {1009001532, 1008738336},
			    {1008738364, 1009001508},
			    {1006896132, 1009001508},
			    {67372092, 1006896132},
			    {1008738336, 1009001508},
			    {1006896188, 1006896132},
			    {1006896188, 67372036}};

	if (ch < '0' || (ch > '9' && ch < 'a') || ch > 'f') {
		printf("Character '%c' is not supported.\n", ch);
	       	return -1;
	}
	
	int* chnum = (int *)valloc(8);

	if (ch >= '0' && ch <= '9') chnum = table[ch - '0'];
	else if (ch >= 'a' && ch <= 'f') chnum = table[ch - 'a' + 10];

	int rows, cols;
	mt_getscreensize(&rows, &cols);
	
	if (x > rows) x = 0;
	if (y > cols) y = 0;
	
	mt_setfgcolor(fgcolor);
	mt_setbgcolor(bgcolor);

	for (int i = 0; i < x; i++) printf("\n");	
	for (int i = 0; i < y; i++) printf(" ");
	
	for (int i = 0; i < 4; i++) {
		for (int k = 0; k < y; k++) printf(" ");

		for (int j = 0; j < 8; j++) {
			
			if ((chnum[0] & MASK) != 0) bc_printA("a");
			else printf(" ");
			chnum[0] >>= 1;
		}
		printf("\n");
	}

	for (int i = 0; i < 4; i++) {
		for (int k = 0; k < y; k++) printf(" ");

		for (int j = 0; j < 8; j++) {
		
			if ((chnum[1] & MASK) != 0) bc_printA("a");
			else printf(" ");
			chnum[1] >>= 1;
		}
		printf("\n");
	}
	
//	printf("\n");
		
	return 0;
}

/*
int bc_setbigcharpos (int * big, int x, int y, int value) - устанавли-
вает значение знакоместа "большого символа" в строке x и столбце y в значение value;
*/
int bc_setbigcharpos (int * big, int x, int y, int value) {
    big[y/4] |= (!!value << (31 - ( (y%4) * 8 + x)));
}

/*
int bc_getbigcharpos(int * big, int x, int y, int *value) - возвращает
значение позиции в "большом символе" в строке x и столбце y;
*/
int bc_getbigcharpos (int * big, int x, int y, int *value) {
     *value = (big[y/4] >> (31 - ((y%4) * 8 + x))) & 1;
}

/*
int bc_bigcharwrite (int fd, int * big, int count) - записывает заданное
число "больших символов" в файл. Формат записи определяется пользователем;
*/
int bc_bigcharwrite (int fd, int * big, int count){
	int i, j;
	for(j=0; j < count; j++) {
	    for(i=0; i < 2; i++) {
    		write(fd, &big[i], sizeof(int));
        }
    }
	return 0;
}

/*
int bc_bigcharread (int fd, int * big, int need_count, int * count)
считывает из файла заданное количество "больших символов". Третий параметр ука-
зывает адрес переменной, в которую помещается количество считанных символов или
0, в случае ошибки.
*/
int bc_bigcharread (int fd, int * big, int need_count, int *count) {
    int i, j;
    *count = 0;
    for(i = 0; i < 2; i++) {
        read(fd, &big[i], sizeof(int));
    }
    *count++;
    return 0;
}

void bc_printStr(char* str, int x, int y, enum colors fgcolor, enum colors bgcolor) {
	
		
	int table[17][2] = {{606348348, 1009001508},
			    {269752336, 1007685648},
			    {1008738364, 1006896132},
			    {1008738364, 1008738336},
			    {1009001508, 538976288},
			    {1006896188, 1008738336},
			    {1006896188, 1009001508},
			    {538976316, 538976288},
			    {1009001532, 1009001508},
			    {1009001532, 1008738336},
			    {1008738364, 1009001508},
			    {1006896132, 1009001508},
			    {67372092, 1006896132},
			    {1008738336, 1009001508},
			    {1006896188, 1006896132},
			    {1006896188, 67372036},
			    {2115508224, 1579134}};

	int len = (int)strlen(str);
	int** chnum = (int **)valloc(len * 8);
	
	for (int i = 0; i < len; i++) {

//		if (str[i] < '0' || (str[i] > '9' && str[i] < 'a') || str[i] > 'f' || str[i] != '+') {
//			printf("Character '%c' is not supported.\n", str[i]);
//		       	return;
//		}
	
		if (str[i] >= '0' && str[i] <= '9') chnum[i] = table[str[i] - '0'];
		else if (str[i] >= 'a' && str[i] <= 'f') chnum[i] = table[str[i] - 'a' + 10];
		else chnum[i] = table[16];
	}

	int rows, cols;
	mt_getscreensize(&rows, &cols);
	
	if (x > rows) x = 0;
	if (y > cols) y = 0;
	
	mt_setfgcolor(fgcolor);
	mt_setbgcolor(bgcolor);

	for (int i = 0; i < x; i++) printf("\n");	
	for (int i = 0; i < y; i++) printf(" ");
	
	int ch = 0;
	for (int i = 0; i < 4; i++) {
		
		for (int j = 0; j < len; j++) {
			ch = chnum[j][0] >> i * 8;
			for (int k = 0; k < y; k++) printf(" ");

			for (int l = 0; l < 8; l++) {
				if ((ch & MASK) != 0) bc_printA("a");
				else printf(" ");
				ch >>= 1;
			}
		}
		printf("\n");
	}

	
	for (int i = 0; i < 4; i++) {
		
		for (int j = 0; j < len; j++) {
			ch = chnum[j][1] >> i * 8;
			for (int k = 0; k < y; k++) printf(" ");

			for (int l = 0; l < 8; l++) {
				if ((ch & MASK) != 0) bc_printA("a");
				else printf(" ");
				ch >>= 1;
			}
		}
		printf("\n");
	}

	printf("\n");
	

}