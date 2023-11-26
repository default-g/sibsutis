all:clean main

main:main.o lib.a
	g++ -o main main.o -L. lib.a
lib.a: lib.o
	ar rc lib.a lib.o
	ranlib lib.a
lib.o:lib.c
	g++ -c lib.c
main.o:main.c
	g++  -c main.c
clean:
	rm -f *.o *.a
	rm -f main