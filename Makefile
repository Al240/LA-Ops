# Makefile: Linear Algebra Operations
# Written by: Al240 // 2/15/2025

CC = gcc
CFLAGS = -Wall -std=c17 -c
LFLAGS = -Wall -std=c17 $(DEBUG)
DEBUG = -O2 -DNODEBUG
#DEBUG = -g -DDEBUG

all: LA-Ops_v1.1.exe

clean:
	rm -f *.o
	rm -f LA-Ops_v1.1.exe

vectors.o: vectors.h vectors.c
	$(CC) $(CFLAGS) vectors.c -o vectors.o

matrix.o: matrix.h matrix.c
	$(CC) $(CFLAGS) matrix.c -o matrix.o

LA-Ops_v1.1.exe: vectors.o matrix.o main.c
	$(CC) $(LFLAGS) vectors.o matrix.o main.c -o ./version/LA-Ops_v1.1.exe