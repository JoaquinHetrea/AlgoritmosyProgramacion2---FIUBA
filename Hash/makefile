CC=gcc
CFLAGS=-g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0

build_lista: lista.c lista.h 
	$(CC) $(CFLAGS) -c lista.c -o lista.o

build: hash.h hash_iterador.h hash.c 
	$(CC) $(CFLAGS) -c hash.c -o hash.o
	
compile: pruebas.c hash.o hash.h hash_iterador.h lista.o
	$(CC) $(CFLAGS) lista.o hash.o pruebas.c -o hash
	
run: compile
	./hash_abierto
    
valgrind: compile
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./hash
	
compile_minipruebas: minipruebas_hash.c hash.o hash.h hash_iterador.h lista.o
	$(CC) $(CFLAGS) lista.o hash.o minipruebas_hash.c -o hash_abierto

valgrind_minipruebas: compile_minipruebas
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./hash_abierto
	
    
.PHONY : clean
