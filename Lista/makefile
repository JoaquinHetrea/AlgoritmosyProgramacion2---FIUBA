CC=gcc
CFLAGS=-g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0

build: lista.c lista.h 
	$(CC) $(CFLAGS) -c lista.c -o lista.o
	
compile: pruebas.c lista.o lista.h
	$(CC) $(CFLAGS) lista.o pruebas.c -o lista_se
	
run: compile
	./lista_se
    
valgrind: compile
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./lista_se
    
    
.PHONY : clean
