#include "lista.h"
#include <stdbool.h>
#include <stdio.h>

int main(){

	//EJEMPLO CREAR LISTA
	lista_t* lista = lista_crear();
	if(lista)
		printf("La Lista se creó correctamente\n");

	//EJEMPLO INSERTAR 
	char letra_a = 'A';
	char letra_b = 'B';
	char letra_c = 'C';
	lista_insertar(lista, &letra_a);
	lista_insertar(lista, &letra_b);
	lista_insertar(lista, &letra_c);

	//EJEMPLO PEDIR CANTIDAD DE ELEMENTOS
	if(lista_elementos(lista) == 3)
		printf("Insertó correctamente\n");

	//EJEMPLO CREAR ITERADOR
	lista_iterador_t* iterador = lista_iterador_crear(lista);
	if(iterador)
		printf("El iterador se creó correctamente\n");

	//EJEMPLO VERIFICAR SI EL ITERADOR TIENE SIGUIENTE
	if(lista_iterador_tiene_siguiente(iterador))
		printf("Iterador verificó correctamente que tiene siguiente\n");

	//EJEMPLO AVANZAR ITERADOR
	if(*(char*)lista_iterador_siguiente(iterador) == letra_a){
		printf("Iterador devolvió el elemento correcto\n");
	}

	//EJEMPLO DESTRUIR ITERADOR
	lista_iterador_destruir(iterador);

	//EJEMPLO DESTRUIR LISTA
	lista_destruir(lista);

	return 0;
}