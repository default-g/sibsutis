
# - inc/
#     - *.h
# - src/
#     - *.c
#     - *.cpp
# - obj/
#     - *.o
# - main

TARGET := main
SOURCES := $(wildcard src/*.c src/*.cpp)
OBJECTS := $(patsubst src%,obj%, $(patsubst %.c,%.o, $(patsubst %.cpp,%.o,$(SOURCES))))

INCLUDE := -I.
LIBPATH :=
LIBS :=

FLAGS := -Wall -lm -L
CCFLAGS := $(FLAGS) -std=c99
CXXFLAGS := $(FLAGS)

CC := gcc
Cxx := g++

all:
	g++ src/main.cpp -o main

.PHONY: clean

clean:
	rm -rf obj/*
	rm -f $(TARGET)
	rm -f *.csv

run:
	./$(TARGET)