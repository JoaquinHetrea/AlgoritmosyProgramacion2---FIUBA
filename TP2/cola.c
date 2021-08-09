#include <stdlib.h>
#include <stdio.h>
#include "cola.h"
#define ERROR -1
#define EXITO 0

/* 
 * Crea una cola reservando la memoria necesaria
 * para almacenar la estructura.
 * Devuelve un puntero a la estructura cola_t creada.
 */
cola_t* cola_crear(){
	cola_t* cola = malloc(sizeof(cola_t));
	if(cola == NULL) return NULL;
	
	cola->nodo_inicio = NULL;
	cola->nodo_fin = NULL;
	cola->cantidad = 0;
	return cola;
}

/* 
 * Encola un elemento.
 * Devuelve 0 si pudo encolar o -1 si no pudo.
 */
int cola_encolar(cola_t* cola, void* elemento){
	if(!cola) return ERROR;

	nodo_t* nodo = malloc(sizeof(nodo_t));
	if(nodo == NULL) return ERROR;
	

	if(cola->cantidad == 0){
		cola->nodo_inicio = nodo;
		cola->nodo_fin = nodo;
	} else {
		(cola->nodo_fin)->siguiente = nodo;
		cola->nodo_fin = nodo;

	}
	nodo->siguiente = NULL;
	nodo->elemento = elemento;
	cola->cantidad++;
	return EXITO;
}

/* 
 * Desencola un elemento.
 * Devuelve 0 si pudo desencolar o -1 si no pudo.
 */
int cola_desencolar(cola_t* cola){
	if(!cola) return ERROR;
	if(cola_vacia(cola)) return ERROR;
	
	nodo_t* nodo_aux = cola->nodo_inicio;
	cola->nodo_inicio = nodo_aux->siguiente;
	free(nodo_aux);
	cola->cantidad--;
	return EXITO;
}

/* 
 * Determina si la cola está vacia.
 * Devuelve true si está vacía y false si no.
 * Si la cola no existe devolverá true.
 */
bool cola_vacia(cola_t* cola){
	if(!cola) return true;

	return cola->cantidad == 0;
}

/* 
 * Devuelve la cantidad de elementos almacenados en la cola.
 * Si la cola no existe devolverá 0.
 */
int cola_cantidad(cola_t* cola){
	if(!cola) return 0;
	
	return cola->cantidad;
}

/*
 * Devuelve el primer elemento de la cola o NULL en caso de estar
 * vacía.
 * Si la cola no existe devolverá NULL.
 */
void* cola_primero(cola_t* cola){
	if(!cola) return NULL;
	if(cola_vacia(cola)) return NULL;

	return cola->nodo_inicio->elemento;
}

/*
 * Destruye los nodos liberando toda la memoria reservada
*/
void cola_destruir_nodos(cola_t* cola){
	if(cola_vacia(cola)) return;
	cola_desencolar(cola);
	cola_destruir_nodos(cola);
}

/* 
 * Destruye la cola liberando toda la memoria reservada
 * por la cola.
 */
void cola_destruir(cola_t* cola){
	if(!cola) return;
	
	cola_destruir_nodos(cola);
	free(cola);
}
