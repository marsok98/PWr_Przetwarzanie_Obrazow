CC = gcc -Wall -pedantic

all: przetwarzanie_obrazow.o pgm.o
	$(CC) przetwarzanie_obrazow.o pgm.o -o a.out

pgm.o: pgm.c pgm.h
	$(CC) pgm.c -c -o pgm.o
	

przetwarzanie_obrazow.o: przetwarzanie_obrazow.c 
	$(CC) przetwarzanie_obrazow.c -c -o przetwarzanie_obrazow.o

a.out: przetwarzanie_obrazow.o pgm.o 
	$(CC) przetwarzanie_obrazow.o pgm.o -o a.out

