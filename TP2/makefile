CC=gcc
CFLAGS=-g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0

build_abb: abb.c abb.h 
	$(CC) $(CFLAGS) -c abb.c -o abb.o
	
build_cola: cola.c cola.h 
	$(CC) $(CFLAGS) -c cola.c -o cola.o
	
build_lista: lista.c lista.h
	$(CC) $(CFLAGS) -c lista.c -o lista.o
	
build: game_of_thrones.h game_of_thrones.c 
	$(CC) $(CFLAGS) -c game_of_thrones.c -o game_of_thrones.o
	
compile: juego_de_tronos.c game_of_thrones.o cola.o abb.o lista.o 
	$(CC) $(CFLAGS) game_of_thrones.o cola.o abb.o lista.o juego_de_tronos.c -o game_of_thrones
	
run: compile
	./game_of_thrones
	
valgrind: compile
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./game_of_thrones
       
.PHONY : clean
