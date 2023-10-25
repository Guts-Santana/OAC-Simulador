CC = gcc
CFLAGS = -std=c11 -Wall

all: Simulador
	./Simulador

Simulador: memoria.o codigo.o Simulador.o
	$(CC) $(CFLAGS) memoria.o codigo.o Simulador.o -o Simulador

Simulador.o: Simulador.c memoria.h codigo.h 
	$(CC) $(CFLAGS) -c Simulador.c

memoria.o: memoria.c memoria.h
	$(CC) $(CFLAGS) -c memoria.c

codigo.o: codigo.c codigo.h
	$(CC) $(CFLAGS) -c codigo.c

clean:
	rm -rf *.o main
