FLAGS += -Wall -Werror -g
USER_DIR_S = build
EXECUTABLE = bin/program
DISK = bin/disk

.PHONY: all clean hard start

all: $(EXECUTABLE) $(DISK)

$(EXECUTABLE): $(USER_DIR_S)/main.o $(USER_DIR_S)/libmySimpleComputer.a $(USER_DIR_S)/libmyTerm.a  $(USER_DIR_S)/libbasic.a $(USER_DIR_S)/libasm.a $(USER_DIR_S)/libmyBigChars.a $(USER_DIR_S)/libcu.a $(USER_DIR_S)/libprintConsole.a $(USER_DIR_S)/libmyReadkey.a $(USER_DIR_S)/libmySignal.a
	gcc $(FLAGS) -o $@ $^ -Lbuild -lmySimpleComputer -Lbuild -lmyTerm -Lbuild -lmyBigChars -Lbuild -lbasic -Lbuild -lasm -Lbuild -lprintConsole -Lbuild -lmyReadkey -Lbuild -lmySignal -Lbuild -lcu

$(USER_DIR_S)/main.o: src/main.c
	gcc $(FLAGS) -c $^ -o $@

$(USER_DIR_S)/mySimpleComputer.o: src/mySimpleComputer.c
	gcc $(FLAGS) -c $^ -o $@

$(USER_DIR_S)/libmySimpleComputer.a: $(USER_DIR_S)/mySimpleComputer.o
	ar rc $(USER_DIR_S)/libmySimpleComputer.a $(USER_DIR_S)/mySimpleComputer.o

$(USER_DIR_S)/myTerm.o: src/myTerm.c
	gcc $(FLAGS) -c $^ -o $@

$(USER_DIR_S)/myBigChars.o: src/myBigChars.c
	gcc $(FLAGS) -c $^ -o $@

$(USER_DIR_S)/printConsole.o: src/printConsole.c
	gcc $(FLAGS) -c $^ -o $@

$(USER_DIR_S)/myReadkey.o: src/myReadkey.c
	gcc $(FLAGS) -c $^ -o $@

$(USER_DIR_S)/mySignal.o: src/mySignal.c
	gcc $(FLAGS) -c $^ -o $@

$(USER_DIR_S)/basic.o: src/basic.c
	gcc $(FLAGS) -c $^ -o $@

$(USER_DIR_S)/cu.o: src/cu.c
	gcc $(FLAGS) -c $^ -o $@

$(USER_DIR_S)/asm.o: src/asm.c
	gcc $(FLAGS) -c $^ -o $@

$(USER_DIR_S)/libmyTerm.a: $(USER_DIR_S)/myTerm.o
	ar rc $(USER_DIR_S)/libmyTerm.a $(USER_DIR_S)/myTerm.o

$(USER_DIR_S)/libcu.a: $(USER_DIR_S)/cu.o
	ar rc $(USER_DIR_S)/libcu.a $(USER_DIR_S)/cu.o

$(USER_DIR_S)/libbasic.a: $(USER_DIR_S)/basic.o
	ar rc $(USER_DIR_S)/libbasic.a $(USER_DIR_S)/basic.o

$(USER_DIR_S)/libasm.a: $(USER_DIR_S)/asm.o
	ar rc $(USER_DIR_S)/libasm.a $(USER_DIR_S)/asm.o

$(USER_DIR_S)/libmyBigChars.a: $(USER_DIR_S)/myBigChars.o
	ar rc $(USER_DIR_S)/libmyBigChars.a $(USER_DIR_S)/myBigChars.o

$(USER_DIR_S)/libmyReadkey.a: $(USER_DIR_S)/myReadkey.o
	ar rc $(USER_DIR_S)/libmyReadkey.a $(USER_DIR_S)/myReadkey.o

$(USER_DIR_S)/libprintConsole.a: $(USER_DIR_S)/printConsole.o
	ar rc $(USER_DIR_S)/libprintConsole.a $(USER_DIR_S)/printConsole.o

$(USER_DIR_S)/libmySignal.a: $(USER_DIR_S)/mySignal.o
	ar rc $(USER_DIR_S)/libmySignal.a $(USER_DIR_S)/mySignal.o

$(DISK): $(USER_DIR_S)/main_7.o $(USER_DIR_S)/libdisk.a 
	gcc $(FLAGS) -o $@ $^ -Lbuild -ldisk

$(USER_DIR_S)/main_7.o: src/main_7.c
	gcc $(FLAGS) -c $^ -o $@

$(USER_DIR_S)/disk.o: src/disk.c
	gcc $(FLAGS) -c $^ -o $@

$(USER_DIR_S)/libdisk.a: $(USER_DIR_S)/disk.o
	ar rc $(USER_DIR_S)/libdisk.a $(USER_DIR_S)/disk.o

hard:
	./bin/disk

start:
	./bin/program

clean:
	rm -rf $(USER_DIR_S)/*.o
	rm -rf $(USER_DIR_S)/*.a
	rm -rf bin/program