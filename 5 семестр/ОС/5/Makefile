all:
	gcc -c -fPIC -Wall lib/list_functions.c -o lib/list_functions.o
	gcc -shared lib/*.o -o liblist_functions.so
	gcc -c main.c
	gcc main.o -L. -llist_functions -o main
	rm main.o
	rm lib/list_functions.o
