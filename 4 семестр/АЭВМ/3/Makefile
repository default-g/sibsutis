all:clean main

main:main.o lib.a
	g++ -o main main.o -L. lib.a
lib.a: lib.o myTerm.o myBigChars.o
	ar rc lib.a lib.o myTerm.o myBigChars.o
	ranlib lib.a
lib.o: lib.c
	g++ -c lib.c
myTerm.o: myTerm.c
	g++ -c myTerm.c
myBigChars.o: myBigChars.c
	g++ -c myBigChars.c
main.o: main.c
	g++  -c main.c
clean:
	rm -f *.o *.a
	rm -f main