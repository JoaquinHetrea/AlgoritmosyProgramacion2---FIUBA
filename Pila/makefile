CC=gcc
CFLAGS=-g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0

build: pila.c pila.h
	$(CC) $(CFLAGS) -c pila.c -o pila.o

compile: pruebas.c pila.o pila.h
	$(CC) $(CFLAGS) pila.o pruebas.c -o pila_vd 
    
run: compile
	./pila_vd
    
valgrind: compile
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./pila_vd
    
    
.PHONY : clean
