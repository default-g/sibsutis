#pragma once
all:
	gcc -c main.c -o main.o
	gcc -c myTerm.c -o myTerm.o
	gcc -c MSC.c -o MSC.o
	gcc -c myBigChars.c -o myBigChars.o
	gcc -c myReadKey.c -o myReadKey.o
	gcc main.o myTerm.o MSC.o myBigChars.o myReadKey.o -o output
	./output
clean:
	find . -name "*.o" -exec rm -rf {} \;
