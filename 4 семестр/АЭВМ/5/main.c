#include "MSC.h"
#include "myTerm.h"
#include "myBigChars.h"
#include "myReadKey.h"
#include <stdio.h>
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>

struct itimerval nval, oval;

void RefreshWindow();

void my_handler()
{
	int value;
	sc_regGet(IGNR_CLOCK, &value);
	if(value == 0 && Pointer + 1 < 100)
	{
		Pointer++;
		RefreshWindow();
	}
	else
	{
		signal(SIGALRM, my_handler);
		nval.it_interval.tv_sec = 0;
		nval.it_interval.tv_usec = 0;
		nval.it_value.tv_sec = 0;
		nval.it_value.tv_usec = 0;
	 	setitimer (ITIMER_REAL, &nval, &oval);
		sc_regSet(IGNR_CLOCK, 1);
		RefreshWindow();
	}
}

void my_handler2()
{
	int value;
	sc_regGet(IGNR_CLOCK, &value);
	if(value == 0 && Pointer + 1 < 100)
	{
		Pointer++;
		RefreshWindow();
	}
	
	signal(SIGALRM, my_handler);
	nval.it_interval.tv_sec = 0;
	nval.it_interval.tv_usec = 0;
	nval.it_value.tv_sec = 0;
	nval.it_value.tv_usec = 0;
	setitimer (ITIMER_REAL, &nval, &oval);
	sc_regSet(IGNR_CLOCK, 1);
	RefreshWindow();
       
}
void oneTimer()
{
	int value;
	signal(SIGALRM, my_handler2);
	nval.it_interval.tv_sec = 0;
	nval.it_interval.tv_usec = 0;
	nval.it_value.tv_sec = 1;
	nval.it_value.tv_usec = 0;/* ������������ */
	/* ��������� ������ */
  	setitimer (ITIMER_REAL, &nval, &oval);
}

void endlessTimer()
{
	int value;
	signal(SIGALRM, my_handler);
	nval.it_interval.tv_sec = 0;
	nval.it_interval.tv_usec = 500;
	nval.it_value.tv_sec = 1;
	nval.it_value.tv_usec = 0;
  	setitimer (ITIMER_REAL, &nval, &oval);
}


void printHotkeys()
{
	mt_gotoXY(15, 50);
	bc_printA("L \u2014 LOAD");
	mt_gotoXY(16, 50);
	bc_printA("S \u2014 SAVE");
	mt_gotoXY(17, 50);
	bc_printA("R \u2014 RUN");
	mt_gotoXY(18, 50);
	bc_printA("T \u2014 STEP");
	mt_gotoXY(19, 50);
	bc_printA("I \u2014 INPUT");
	mt_gotoXY(20, 50);

}

void printFlags()
{
	int value;
	mt_gotoXY(12, 64);
	sc_regGet(OVERFLOW, &value);
	if(value) bc_printA(" OV ");
	sc_regGet(ZERO_ERR, &value);
	if(value) bc_printA(" ZE ");
	sc_regGet(OUT_OF_MEM, &value);
	if(value) bc_printA(" OU ");
	sc_regGet(IGNR_CLOCK, &value);
	if(value) printf(" IC ");
	sc_regGet(COMMAND_ERROR, &value);
	if(value) bc_printA(" CO ");
}

void printBigCharWindow(int Pointer)
{	
	int xx;
	int container[4];
	int B[2]={1579134,2115508224};
	int First[2]={0,0};
	int Second[2]={0,0};
	int Third[2]={0,0};
	int Fourth[2]={0,0};

	bc_printbigchar(B, 15, 3, 5, 10);
	int temp = ram[Pointer];
	bc_bigcharLayout(First, (temp << 12) >> 12);
	bc_printbigchar(First, 15, 39, 5, 10);

	bc_bigcharLayout(Second, (temp << 8) >> 12);
	bc_printbigchar(Second, 15, 30, 5, 10);

	bc_bigcharLayout(Third, (temp << 4) >> 12);
	bc_printbigchar(Third, 15, 21, 5, 10);

	bc_bigcharLayout(Fourth, temp >> 12);
	bc_printbigchar(Fourth, 15, 12, 5, 10);
	mt_gotoXY(50,1);
}

void printAcc()
{
	mt_gotoXY(3,65);
	printf("+%04x ", ram[Pointer]);
	mt_gotoXY(50,1);
}

void printCounter()
{
	mt_gotoXY(6,65);
	printf("+%04x ", Pointer);
	mt_gotoXY(50,1);
}

void printMem(int x, int y, int Pointer)
{
	mt_gotoXY(x, y);
	for(int i = 0; i < 100; i++)
	{
		if(i == Pointer)
			mt_setgbcolor(5);
		else
			mt_setgbcolor(9);
		if(i%10 == 0)
		{
			if(i!=0)
			{
				bc_printA("\n"); printf("\033[%dC", y);
				
			}
			else if(i == 0)
			{
				printf("\033[%dC", y-1);
			}
			printf("+%04x ", ram[i]);
		}
		else if(i%10 == 9)
			printf("+%04x", ram[i]);
		else
			printf("+%04x ", ram[i]);
	}
	mt_gotoXY(50,1);
}

void printGraphics()
{
	mt_clrscr();
	bc_box(2, 2, 61, 12); // memory
	mt_gotoXY(2,29);
	printf("Memory:");

	bc_box(2,14,46,22); // bigchar

	bc_box(48,14,83,22); // keys
	mt_gotoXY(14,64);
	printf("Keys:");
	printHotkeys();

	bc_box(63,2,83,3); // accum
	mt_gotoXY(2,64);
	printf("Accumulator:");

	bc_box(63,5,83,6); //intruction
	mt_gotoXY(5,64);
	printf("InstructionCounter:");

	bc_box(63,8,83,9); //operation
	mt_gotoXY(8,64);
	printf("Operation:");

	bc_box(63,11,83,12); //flags
	mt_gotoXY(11,64);
	printf("Flags:");
	printFlags();
}


void RefreshWindow()
{
	mt_clrscr();
	printGraphics();
	printAcc();
	printCounter();
	printMem(3,2,Pointer);
	printBigCharWindow(Pointer);
}

void KbrdCommands()
{
	int value = 0;
	int temp;
	char *fileSave = "memSave";
	char *fileLoad = fileSave;
	enum keys key = incorrectkey;
	while(key != Quit)
	{
		rk_readkey(&key);
		switch(key)
		{
			case IgnrCancel: // c
				sc_regSet(IGNR_CLOCK, 1);
				//signal(SIGUSR1, userHandler);
				//raise(SIGUSR1);
				RefreshWindow();
				break;

			case Reset: // p
				sc_regInit();
				sc_regSet(IGNR_CLOCK, 1);
				sc_memoryInit();
				RefreshWindow();
				break;

			case Run: // r
				sc_regSet(IGNR_CLOCK, 0);
				endlessTimer();
				break;

			case sTep: // t
				sc_regSet(IGNR_CLOCK, 0);
				oneTimer();
				break;

			case Load: // l
				if(sc_regGet(IGNR_CLOCK, &value) == 0)
					break;
				sc_regInit();
				sc_regSet(IGNR_CLOCK, 1);
				sc_memoryLoad(fileLoad);
				RefreshWindow();
				break;

			case Save:
				if(sc_regGet(IGNR_CLOCK, &value) == 0)
					break;
				sc_memorySave(fileSave);
				break;

			case Input: // i
				if(sc_regGet(IGNR_CLOCK, &value) == 0)
					break;
				scanf("%d", &temp);
				sc_memorySet(Pointer, temp);
				RefreshWindow();
				break;

			case up:
				if(sc_regGet(IGNR_CLOCK, &value) == 0)
					break;
				if(!(Pointer - 10 < 0))
				{
					Pointer -= 10;
					RefreshWindow();
				}
				break;

			case down:
				if(sc_regGet(IGNR_CLOCK, &value) == 0)
					break;
				if(!(Pointer + 10 > 99))
				{
					Pointer += 10;
					RefreshWindow();
				}
				break;

			case left:
				if(sc_regGet(IGNR_CLOCK, &value) == 0)
					break;
				if(!(Pointer - 1 < 0))
				{
					Pointer -= 1;
					RefreshWindow();
				}
				break;

			case right:
				if(sc_regGet(IGNR_CLOCK, &value) == 0)
					break;
				if(!(Pointer + 1 > 99))
				{
					Pointer += 1;
					RefreshWindow();
				}
				break;
		}
	}
}
int main() {
	setbuf(stdout, NULL);
	sc_regInit();
	sc_memoryInit();
	sc_regSet(IGNR_CLOCK, 1);
	RefreshWindow();
	KbrdCommands();
	mt_gotoXY(50,1);
	return 0;
}
