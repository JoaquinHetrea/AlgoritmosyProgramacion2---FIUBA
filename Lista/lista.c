#include "lista.h"
#include <stdlib.h>
#define ERROR -1
#define EXITO 0

typedef struct nodo {
	void* elemento;
	struct nodo* siguiente;
} nodo_t;

struct lista {
	nodo_t* nodo_inicio;
	nodo_t* nodo_fin;
	size_t cantidad;
};

struct lista_iterador {
	lista_t* lista;
	nodo_t* nodo_actual;
};

/*
 * Crea la lista reservando la memoria necesaria.
 * Devuelve un puntero a la lista creada o NULL en caso de error.
 */
lista_t* lista_crear(){
	lista_t* lista = malloc(sizeof(lista_t));
	if(!lista) return NULL;
	lista->nodo_inicio = NULL;
	lista->nodo_fin = NULL;
	lista->cantidad = 0;
	return lista;
}

/*
 * Crea un nodo reservando la memoria necesaria.
 * Devuelve un puntero al nodo creado o NULL en caso de error.
 */
nodo_t* nodo_crear(){
	nodo_t* nodo = malloc(sizeof(nodo_t));
	if(!nodo) return NULL;
	nodo->siguiente = NULL;
	return nodo;
}

/*
 * Inserta un elemento al final de la lista.
 * Devuelve 0 si pudo insertar o -1 si no pudo.
 */
int lista_insertar(lista_t* lista, void* elemento){
	if(!lista) return ERROR;

	nodo_t* nodo_nuevo = nodo_crear();
	if(!nodo_nuevo) return ERROR;

	if(lista->cantidad == 0){
		lista->nodo_fin = nodo_nuevo;
		lista->nodo_inicio = nodo_nuevo;
	} else {
		(lista->nodo_fin)->siguiente = nodo_nuevo;
		(lista->nodo_fin) = nodo_nuevo;
	}
	nodo_nuevo->elemento = elemento;
	nodo_nuevo->siguiente = NULL;
	lista->cantidad++;
	return EXITO;
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
	if(posicion >= lista->cantidad) 
		return lista_insertar(lista, elemento);
	
	nodo_t* nodo_nuevo = nodo_crear();
	if(!nodo_nuevo) 
		return ERROR;

	if(posicion == 0){
		nodo_nuevo->siguiente = lista->nodo_inicio;
		lista->nodo_inicio = nodo_nuevo;
	} else {
		nodo_t* nodo_actual = lista->nodo_inicio;
		for(int i = 0; i < posicion-1; i++)
			nodo_actual = nodo_actual->siguiente;
	
		nodo_nuevo->siguiente = nodo_actual->siguiente;
		nodo_actual->siguiente = nodo_nuevo;
	}

	nodo_nuevo->elemento = elemento;
	lista->cantidad++;
	return EXITO;
}

/*
 * Quita de la lista el elemento que se encuentra en la ultima posición.
 * Devuelve 0 si pudo eliminar o -1 si no pudo.
 */
int lista_borrar(lista_t* lista){
	if(!lista) 
		return ERROR;
	if(lista_vacia(lista))
		return ERROR;

	if(lista->cantidad == 1){
		free(lista->nodo_inicio);
		lista->nodo_inicio = NULL;
		lista->nodo_fin = NULL;
	} else {
		nodo_t* nodo_aux = lista->nodo_inicio;
		while(nodo_aux->siguiente->siguiente != NULL)
			nodo_aux = nodo_aux->siguiente;
		
		free(lista->nodo_fin);
		lista->nodo_fin = nodo_aux;
		lista->nodo_fin->siguiente = NULL;
	}
	lista->cantidad--;
	return EXITO;
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
	if(lista->cantidad == 1)
		return lista_borrar(lista);
	if(posicion >= lista->cantidad-1)
		return lista_borrar(lista);

	if(posicion == 0){
		nodo_t* nodo_aux = lista->nodo_inicio->siguiente;
		free(lista->nodo_inicio);
		lista->nodo_inicio = nodo_aux;
	} else {
		nodo_t* nodo_previo = lista->nodo_inicio;
		for(int i = 0; i < posicion-1; i++)
			nodo_previo = nodo_previo->siguiente;
		
		nodo_t* nodo_aux = nodo_previo->siguiente;
		nodo_previo->siguiente = nodo_aux->siguiente;
		free(nodo_aux);
	}
	lista->cantidad--;
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
	if(lista_vacia(lista))
		return NULL;
	if(posicion >= lista->cantidad) 
		return NULL;
	if(posicion == lista->cantidad-1)
		return lista_ultimo(lista);

	nodo_t* nodo_aux = lista->nodo_inicio;
	for(int i = 0; i < posicion; i++)
		nodo_aux = nodo_aux->siguiente;

	return nodo_aux->elemento;
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
	return lista->nodo_fin->elemento;
}

/* 
 * Devuelve true si la lista está vacía o false en caso contrario.
 */
bool lista_vacia(lista_t* lista){
	if(!lista) 
		return true;
	return lista->cantidad == 0;
}

/*
 * Devuelve la cantidad de elementos almacenados en la lista.
 */
size_t lista_elementos(lista_t* lista){
	if(!lista) 
		return 0;
	return lista->cantidad;
}

/*
 * Libera la memoria reservada por la lista.
 */
void lista_destruir(lista_t* lista){
	if(lista){
		while(!lista_vacia(lista)){
			lista_borrar_de_posicion(lista, 0);
		}
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
	iterador->nodo_actual = lista->nodo_inicio;
	return iterador;
}

/*
 * Devuelve true si hay mas elementos sobre los cuales iterar o false
 * si no hay mas.
 */
bool lista_iterador_tiene_siguiente(lista_iterador_t* iterador){
	if(!iterador) 
		return NULL;
	return iterador->nodo_actual != NULL;
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
	
	void* elemento_actual = iterador->nodo_actual->elemento;
	iterador->nodo_actual = iterador->nodo_actual->siguiente;
	
	return elemento_actual;
}

/*
 * Libera la memoria reservada por el iterador.
 */
void lista_iterador_destruir(lista_iterador_t* iterador){
	if(iterador) 
		free(iterador);
}

/*
 * Iterador interno. Recorre la lista e invoca la funcion con cada
 * elemento de la misma.
 */
void lista_con_cada_elemento(lista_t* lista, void (*funcion)(void*)){
	if(lista){
		nodo_t* nodo_actual = lista->nodo_inicio;
		while(nodo_actual != NULL){
			(*funcion)(nodo_actual->elemento);
			nodo_actual = nodo_actual->siguiente;
		}
	}
}
