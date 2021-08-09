#include "lista.h"
#include <stdbool.h>
#include <stdio.h>

int main(){

	//EJEMPLO CREAR UNA LISTA
	lista_t* lista = lista_crear();
	if(lista)
		printf("La lista se creó correctamente\n");

	//EJEMPLO INSERTAR UN ELEMENTO EN LA LISTA
	int numero = 1;
	lista_insertar(lista, &numero);

	//EJEMPLO VER CANTIDAD DE ELEMENTOS
	if(lista_elementos(lista) == 1)
		printf("Insertó corretamente\n");

	//EJEMPLO DE BORRADO
	lista_borrar(lista);

	//EJEMPLO VERIFICAR SI ESTÁ VACÍA
	if(lista_vacia(lista))
		printf("Borró correctamente\n");

	//EJEMPLO DESTRUIR LISTA
	lista_destruir(lista);
}