CC = gcc
CFLAGS = -std=c11 -Wall

all: Simulador
	./Simulador

compile: Memory.o Instructions.o Simulador.o

Simulador: Memory.o Instructions.o Simulador.o
	$(CC) $(CFLAGS) Memory.o Instructions.o Simulador.o -o Simulador

Simulador.o: Simulador.c Memory.h Instructions.h 
	$(CC) $(CFLAGS) -c Simulador.c

Memory.o: Memory.c Memory.h
	$(CC) $(CFLAGS) -c Memory.c

Instructions.o: Instructions.c Instructions.h
	$(CC) $(CFLAGS) -c Instructions.c

clean:
	rm -rf *.o Simulador
