#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#include <iostream>
#include <windows.h>
#include <stdio.h>

using namespace std;

bool isEscPressed(){
	return GetAsyncKeyState(VK_ESCAPE) & 0x8000;
}

void drawPlane(int x, int y, int color)	{
	setcolor(color);
	moveto(x, y);
	lineto(x+20, y);
	lineto(x+50, y-15);
	lineto(x+60, y);
	lineto(x+75, y);
	arc(x+75, y+13, 270, 90, 13);
	moveto(x+75, y+25);
	lineto(x-15, y+25);
	lineto(x-30, y-15);
	lineto(x-7, y-15);
	lineto(x, y);
	moveto(x+5, y+13);
	lineto(x-17, y+50);
	lineto(x-5, y+ 50);
	lineto(x+50, y+13);
}


int moveWithKeyBoard() {
	int x=200; int y=200; int code;
	while(1) {
		code = getch();
		drawPlane(x, y, 0);
		if(isEscPressed()) { return 0;};
		switch(code){
			case 75:  x-=5; if ( x <= 30 ) x = 30; break; 
    		case 77:  x+=5; if ( x >= 405 ) x = 405; break;
    		case 72:  y-=5; if ( y <= 25 ) y = 25; break;
    		case 80:  y+=5; if ( y >= 430 ) y = 430; break;
		}	
		drawPlane(x, y, 15);	
	}
}


int iWantToBeFree() {
	int x = 200; int y = 200;
	while(1) {
		while(x != 400 && y != 25) {
			drawPlane(x, y, 0);
			if( isEscPressed() ){ return 0; };
			drawPlane(++x, --y, 15);
			delay(20);
		
		}
		
			while(y != 432) {
			drawPlane(x, y, 0);
			if( isEscPressed()){ return 0; };
			drawPlane(x, ++y, 15);
			delay(20);
			
		}
			while(x != 27 ) {
			drawPlane(x, y, 0);
			if( isEscPressed()){ return 0; };
			drawPlane(--x, --y, 15);
			delay(20);
			
		}
			while(y != 426) {
			drawPlane(x, y, 0);
			if(isEscPressed() ){ return 0; };
			drawPlane(x, ++y, 15);
			delay(20);
			
		}
	}
}


int main() {
	setlocale(LC_ALL, "Russian");
	initwindow(500, 500);
while(1) {
	drawPlane(200, 200, 12);
	printf("1. Свободное движение объекта\n2. Движение с помощью клавиатуры\n3. Выход из программы\n>>> ");
	int choice = 0;
	cin >> choice;
	if(choice == 1) iWantToBeFree();
	else if(choice == 2) moveWithKeyBoard();
	else if(choice == 3) return 0;
	else {
	cout << "ОШИБКА" << endl;
	return 1;
	};
	};
	return 0;
}


