CC=gcc
CFLAGS=-g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0

build: cola.c cola.h 
	$(CC) $(CFLAGS) -c cola.c -o cola.o
	
compile: pruebas.c cola.o cola.h
	$(CC) $(CFLAGS) cola.o pruebas.c -o cola_ne
	
run: compile
	./cola_ne
    
valgrind: compile
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./cola_ne
    
    
.PHONY : clean
