#include "lista.h"
#include <stdbool.h>
#include <stdio.h>

int main(){

	//EJEMPLO CREAR LISTA
	lista_t* lista = lista_crear();
	if(lista)
		printf("La Lista se creó correctamente");

	int numero_1 = 1;
	int numero_2 = 2;
	int numero_3 = 3;

	//EJEMPLO INSERCION
	lista_insertar(lista, &numero_1);
	lista_insertar(lista, &numero_3);

	//EJEMPLO PEDIR CANTIDAD DE ELEMENTOS
	if(lista_elementos(lista) == 2)
		printf("Insertó ambos elementos\n");

	//EJEMPLO PEDIR ULTIMO ELEMENTO
	if(*(int*)lista_ultimo(lista) == numero_3)
		printf("Los insertó en el orden correcto\n");

	//EJEMPLO INSERCION EN POSICION
	lista_insertar_en_posicion(lista, &numero_2, 1);

	//EJEMPLO BUSCAR ELEMENTO EN POSICION
	if(lista_elementos(lista) == 3 && *(int*)lista_elemento_en_posicion(lista, 1) == numero_2)
		printf("Insertó en posicion correctamente\n");

	//EJEMPLO BORRAR DE POSICION
	lista_borrar_de_posicion(lista, 0);

	if(lista_elementos(lista) == 2 && *(int*)lista_elemento_en_posicion(lista, 0) == numero_2)
		printf("Borró en posicion correctamente\n");

	//EJEMPLO PEDIR ULTIMO ELEMENTO
	if(*(int*)lista_ultimo(lista) == numero_3)
		printf("Devuelve correctamente el último elemento\n");

	//EJEMPLO DESTRUIR LISTA
	lista_destruir(lista);
}