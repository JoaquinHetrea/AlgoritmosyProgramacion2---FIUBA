CC=gcc
CFLAGS=-g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0

build: abb.c abb.h 
	$(CC) $(CFLAGS) -c abb.c -o abb.o
	
compile: pruebas.c abb.o abb.h
	$(CC) $(CFLAGS) abb.o pruebas.c -o abb
	
run: compile
	./abb
    
valgrind: compile
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./abb
    
    
.PHONY : clean
