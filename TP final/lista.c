#include "lista.h"
#include "pila.h"
#include <stdlib.h>
#define ERROR -1
#define EXITO 0

struct lista {
	pila_t* pila;
};

struct lista_iterador {
	lista_t* lista;
	size_t posicion_actual;
};

/*
 * Crea la lista reservando la memoria necesaria.
 * Devuelve un puntero a la lista creada o NULL en caso de error.
 */
lista_t* lista_crear(){
	lista_t* lista = malloc(sizeof(lista_t));
	if(!lista)
		return NULL;
	lista->pila = pila_crear();
	if(!lista->pila){
		free(lista);
		return NULL;
	}
	return lista;
}

/*
 * Inserta un elemento al final de la lista.
 * Devuelve 0 si pudo insertar o -1 si no pudo.
 */
int lista_insertar(lista_t* lista, void* elemento){
	if(!lista)
		return ERROR;

	pila_apilar(lista->pila, elemento);
	return EXITO;
}

/*
 * Desapila elementos de la pila 1 y los apila en la pila 2 hasta
 * dejar a la pila 1 con la cantidad de elementos indicada.
 */
void transferir_elementos(pila_t* pila_1, pila_t* pila_2, size_t cantidad_final){
	if(pila_1 && pila_2){
		while(pila_cantidad(pila_1) != cantidad_final){
			pila_apilar(pila_2, pila_tope(pila_1));
			pila_desapilar(pila_1);
		}
	}
	return;
}

/*
 * Desapila todos los elementos de la pila 1, y los apila en la pila 2
 */
void unir_pilas(pila_t* pila_1, pila_t* pila_2){
	if(pila_1 && pila_2){
		transferir_elementos(pila_1, pila_2, 0);
	}
}

/*
 * Inserta un elemento en la posicion indicada, donde 0 es insertar
 * como primer elemento y 1 es insertar luego del primer elemento.  
 * En caso de no existir la posicion indicada, lo inserta al final.
 * Devuelve 0 si pudo insertar o -1 si no pudo.
 */
int lista_insertar_en_posicion(lista_t* lista, void* elemento, size_t posicion){
    if(!lista)
		return ERROR;
	if(posicion >= lista_elementos(lista)) 
		return lista_insertar(lista, elemento);

	pila_t* pila_aux = pila_crear();
	if(!pila_aux)
		return ERROR;

	transferir_elementos(lista->pila, pila_aux, posicion);
	pila_apilar(lista->pila, elemento);
	unir_pilas(pila_aux, lista->pila);
	pila_destruir(pila_aux);
	return EXITO;
}

/*
 * Quita de la lista el elemento que se encuentra en la ultima posición.
 * Devuelve 0 si pudo eliminar o -1 si no pudo.
 */
int lista_borrar(lista_t* lista){
	if(!lista)
		return ERROR;

	return pila_desapilar(lista->pila);
}

/*
 * Quita de la lista el elemento que se encuentra en la posición
 * indicada, donde 0 es el primer elemento.  
 * En caso de no existir esa posición se intentará borrar el último
 * elemento.  
 * Devuelve 0 si pudo eliminar o -1 si no pudo.
 */
int lista_borrar_de_posicion(lista_t* lista, size_t posicion){
	if(!lista)
		return ERROR;
	if(lista_vacia(lista))
		return ERROR;
	if(posicion >= lista_elementos(lista)-1)
		return lista_borrar(lista);

	pila_t* pila_aux = pila_crear();
	if(!pila_aux)
		return ERROR;

	transferir_elementos(lista->pila, pila_aux, posicion+1);
	pila_desapilar(lista->pila);
	unir_pilas(pila_aux, lista->pila);
	pila_destruir(pila_aux);
	return EXITO;
}

/*
 * Devuelve el elemento en la posicion indicada, donde 0 es el primer
 * elemento.
 *
 * Si no existe dicha posicion devuelve NULL.
 */
void* lista_elemento_en_posicion(lista_t* lista, size_t posicion){
	if(!lista)
		return NULL;
	if(posicion >=  lista_elementos(lista))
		return NULL;
	if(posicion == lista_elementos(lista)-1)
		return pila_tope(lista->pila);

	pila_t* pila_aux = pila_crear();
	if(!pila_aux)
		return NULL;

	transferir_elementos(lista->pila, pila_aux, posicion+1);
	void* elemento = pila_tope(lista->pila);
	unir_pilas(pila_aux, lista->pila);
	pila_destruir(pila_aux);
	return elemento;
}

/* 
 * Devuelve el último elemento de la lista o NULL si la lista se
 * encuentra vacía.
 */
void* lista_ultimo(lista_t* lista){
	if(!lista)
		return NULL;
	if(lista_vacia(lista))
		return NULL;

	return pila_tope(lista->pila);
}

/* 
 * Devuelve true si la lista está vacía o false en caso contrario.
 */
bool lista_vacia(lista_t* lista){
	if(!lista)
		return true;

	return pila_vacia(lista->pila);
}

/*
 * Devuelve la cantidad de elementos almacenados en la lista.
 */
size_t lista_elementos(lista_t* lista){
	if(!lista)
		return 0;
	
	return (size_t)pila_cantidad(lista->pila);
}

/*
 * Libera la memoria reservada por la lista.
 */
void lista_destruir(lista_t* lista){
	if(lista){
		pila_destruir(lista->pila);
		free(lista);
	}
}

/*
 * Crea un iterador para una lista. El iterador creado es válido desde
 * el momento de su creación hasta que no haya mas elementos por
 * recorrer o se modifique la lista iterada (agregando o quitando
 * elementos de la lista).
 *
 * Devuelve el puntero al iterador creado o NULL en caso de error.
 */
lista_iterador_t* lista_iterador_crear(lista_t* lista){
	if(!lista)
		return NULL;

	lista_iterador_t* iterador = malloc(sizeof(lista_iterador_t));
	if(!iterador)
		return NULL;

	iterador->lista = lista;
	iterador->posicion_actual = 0;
	return iterador;
}

/*
 * Devuelve true si hay mas elementos sobre los cuales iterar o false
 * si no hay mas.
 */
bool lista_iterador_tiene_siguiente(lista_iterador_t* iterador){
	if(!iterador)
		return false;

	return iterador->posicion_actual != lista_elementos(iterador->lista);
}

/*
 * Avanza el iterador al proximo elemento y lo devuelve.
 * En caso de error devuelve NULL.
 */
void* lista_iterador_siguiente(lista_iterador_t* iterador){
	if(!iterador)
		return NULL;
	if(lista_vacia(iterador->lista))
		return NULL;
	if(!lista_iterador_tiene_siguiente(iterador))
		return NULL;

	pila_t* pila_aux = pila_crear();
	if(!pila_aux)
		return NULL;

	transferir_elementos(iterador->lista->pila, pila_aux, iterador->posicion_actual+1);
	void* elemento = pila_tope(iterador->lista->pila);
	unir_pilas(pila_aux, iterador->lista->pila);
	iterador->posicion_actual++;
	pila_destruir(pila_aux);
	return elemento;
}

/*
 * Libera la memoria reservada por el iterador.
 */
void lista_iterador_destruir(lista_iterador_t* iterador){
	if(iterador)
		free(iterador);
}
