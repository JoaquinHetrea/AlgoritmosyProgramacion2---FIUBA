#include "pila.h"
#include <stdlib.h>
#include <stdio.h>
#define PILA_TAMANIO_INICIAL 10
#define ERROR -1
#define EXITO 0

/* 
 * Crea una pila, reservando la memoria necesearia para almacenar la
 * estructura.
 * Devuelve un puntero a la estructura pila_t creada o NULL si no pudo
 * crearla.
 */
pila_t* pila_crear(){
	pila_t* pila;
	pila = malloc(sizeof(pila_t));
	if(pila == NULL) {
		return NULL;
	} else {
		pila->tope = 0;
		pila->tamanio = PILA_TAMANIO_INICIAL;
		pila->elementos = malloc((size_t)(pila->tamanio)*sizeof(void*));
		if(pila->elementos == NULL){
			return NULL;
		}
	}
	return pila;
}

/*
 * Cambia el tamaño del vector de elementos
 * Devuelve 0 si puso o -1 en caso contrario
 */
int redimensionar_pila(pila_t* pila, int tamanio){
	if(!pila) return ERROR;

	void* puntero_auxiliar = realloc(pila->elementos, (size_t)tamanio*sizeof(void*));
	if(!puntero_auxiliar){
		return ERROR;
	} else {
		pila->elementos = puntero_auxiliar;
		pila->tamanio = tamanio;
		return EXITO;
	}
}

/* 
 * Apila un elemento.
 * Devuelve 0 si pudo o -1 en caso contrario.
 */
int pila_apilar(pila_t* pila, void* elemento){
	if(!pila) return ERROR;

	if(pila->tope == pila->tamanio){
		redimensionar_pila(pila, 2*pila->tamanio);
	}

	*(pila->elementos + pila->tope) = elemento;
	pila->tope++;

	return EXITO;
}

/* 
 * Desapila un elemento.
 * Devuelve 0 si pudo desapilar o -1 si no pudo.
 */
int pila_desapilar(pila_t* pila){
	if(!pila)return ERROR;
	if(pila_vacia(pila)) return ERROR;

	if(4*pila->tope <= pila->tamanio){
		redimensionar_pila(pila, pila->tamanio/2);
	}

	*(pila->elementos + pila->tope-1) = NULL;
	pila->tope--;

	return EXITO;
}

/* 
 * Determina si la pila está vacia.
 * Devuelve true si está vacía, false en caso contrario.
 * Si la pila no existe devolverá true.
 */
bool pila_vacia(pila_t* pila){
	if(!pila) return true;

	return pila->tope == 0;
}

/* 
 * Devuelve la cantidad de elementos almacenados en la pila.
 * Si la pila no existe devolverá 0.
 */
int pila_cantidad(pila_t* pila){
	if(!pila) return 0;

	return pila->tope;
}

/*
 * Devuelve el elemento en el tope de la pila o NULL
 * en caso de estar vacía.
 * Si la pila no existe devolverá NULL.
 */
void* pila_tope(pila_t* pila){
	if(!pila) return NULL;
	if(pila->tope == 0){
		return NULL;
	} else {
		return (*(pila->elementos + (pila->tope - 1)));
	}
}

/* 
 * Destruye la pila liberando la memoria reservada para la misma.
 */
void pila_destruir(pila_t* pila){
	if(pila){
		if(pila->elementos){
			free((*pila).elementos);
		}
		free(pila);
	}
}