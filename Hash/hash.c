#include "hash.h"
#include "hash_iterador.h"
#include "lista.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define EXITO 0
#define ERROR -1
#define MAX_CLAVE 30
#define FACTOR_CARGA_MAX 2

struct hash {
	hash_destruir_dato_t destructor;
	lista_t** tabla_de_hash;
	size_t capacidad;
	size_t cantidad_almacenada;
};

struct hash_iter{
	hash_t* hash;
	int posicion_actual;
	lista_iterador_t* lista_actual;
};

typedef struct clave_valor {
	void* elemento;
	char clave[MAX_CLAVE];
} clave_valor_t;

/*
Post: Devuelve el siguiente numero primo a partir del valor recibido
*/
size_t siguiente_primo(size_t n_inicial){
    size_t j = 2;
    while(n_inicial % j != 0 && j < n_inicial)
    	j++;
    
    if(j == n_inicial)
    	return j;
    else 
    	return siguiente_primo(n_inicial+1);
}

/*
 Pre: Debe existir memoria disponible en el sistema
 Post: Devuelve un puntero al hash creado o NULL en caso de no poder crearlo
 */
hash_t* hash_crear(hash_destruir_dato_t destruir_elemento, size_t capacidad){
	hash_t* hash = malloc(sizeof(hash_t));
	if(!hash)
		return NULL;
	hash->destructor = destruir_elemento;
	hash->cantidad_almacenada = 0;
	hash->capacidad = siguiente_primo(capacidad);
	hash->tabla_de_hash = malloc(hash->capacidad*(sizeof(lista_t*)));
	if(!hash->tabla_de_hash)
		return NULL;
	for(int i = 0; i < hash->capacidad; i++)
		hash->tabla_de_hash[i] = lista_crear();
	return hash;
}


size_t funcion_hasheo(const char * clave, size_t capacidad) {
	size_t hash = 409;

	while (*clave != '\0') {
		hash = ((hash << 4) + (size_t)(*clave)) % capacidad;
		clave++;
	}

	return hash % capacidad;
}

/*
Pre: Necesita que exista hash
Post: Devuelve el cociente entre la cantidad de elementos almacenados y la capacidad el hash 
*/
int factor_de_carga(hash_t* hash){
	if(!hash) 
		return ERROR;
	return (int)hash->cantidad_almacenada / (int)hash->capacidad;
}


/*
Pre: hash y nuevo hash deben existir.
	 Debe existir memoria disponible en el sistema.
Post: Transfiere todos los elementos de hash a nuevo_hash
*/
int rehasheo(hash_t* hash, hash_t* nuevo_hash){
	if(!hash || !nuevo_hash)
		return ERROR;
	hash_iterador_t* iterador = hash_iterador_crear(hash);
	if(!iterador)
		return ERROR;

	clave_valor_t elemento_actual;
	while(hash_iterador_tiene_siguiente(iterador)){
		strcpy(elemento_actual.clave, hash_iterador_siguiente(iterador));
		elemento_actual.elemento = hash_obtener(hash, elemento_actual.clave);
		hash_insertar(nuevo_hash, elemento_actual.clave, elemento_actual.elemento);
	}

	hash_iterador_destruir(iterador);
	return EXITO;
}
/*
Post: Intercambia los elementos recibidos
*/
void swap(hash_t* hash, hash_t* nuevo_hash){
	hash_t aux = *hash;
	*hash = *nuevo_hash;
	*nuevo_hash = aux;
}

/*
Pre: Necesita que exista hash y que haya memoria disponible en el sistema
Post: Crea un nuevo Hash con mayor capacidad que el recibido
	  Transfiere todos los elementos al nuevo hash 
*/
int hash_redimension(hash_t* hash){
	if(!hash) 
		return ERROR;
	
	hash_t* nuevo_hash = hash_crear(hash->destructor, siguiente_primo(hash->capacidad+1));
	if(!nuevo_hash)
		return ERROR;

	if(rehasheo(hash, nuevo_hash) == ERROR)
		return ERROR;
	swap(hash, nuevo_hash);

	nuevo_hash->destructor = NULL;
	hash_destruir(nuevo_hash);
	return EXITO;
}

/*
Pre: lista debe existir.
	 clave no debe ser NULL.
Post: Devuelve un puntero al elemento cuya clave acompañante es igual a la recibida
*/
clave_valor_t* buscar_elemento(lista_t* lista, const char* clave, int* posicion){
	if(!lista || !clave)
		return NULL;

	bool lo_encontro = false;
	clave_valor_t* elemento_buscado = NULL;
	clave_valor_t* clave_valor_actual = NULL;
	lista_iterador_t* iterador_lista = lista_iterador_crear(lista);
	if(!iterador_lista)
		return NULL;
	int i = 0;
	while(lista_iterador_tiene_siguiente(iterador_lista) && !lo_encontro){
		clave_valor_actual = lista_iterador_siguiente(iterador_lista);
		if(strcmp(clave_valor_actual->clave, clave) == 0){
			lo_encontro = true;
			elemento_buscado = clave_valor_actual;
		} else 
			i++;
	}

	if(posicion != NULL && lo_encontro)
		(*posicion) = i;
	lista_iterador_destruir(iterador_lista);
	return elemento_buscado;
}

/*
Pre: 'repetido' debe ser distinto de NULL
Post: Si destructor no es NULL, invoca destructor con el elemento ha ser reemplazado  
	  Reemplaza el valor del primer elemento con el del segundo
*/
void reasignar_elemento(clave_valor_t* repetido, void* nuevo_elemento, hash_destruir_dato_t destructor){
	if(destructor)
		destructor(repetido->elemento);
	repetido->elemento = nuevo_elemento;
}

/*
 Pre: Debe existir hash y clave debe ser distinto de NULL.
      Debe existir memoria disponible en el sistema.
 Post Inserta un elemento reservando la memoria necesaria para el mismo.
 	   Devuelve 0 si pudo guardarlo o -1 si no pudo.
 */
int hash_insertar(hash_t* hash, const char* clave, void* elemento){
	if(!hash || !clave) 
		return ERROR;
	
	if(factor_de_carga(hash) >= FACTOR_CARGA_MAX){
		int redimension = hash_redimension(hash);
		if(redimension == ERROR)
			return ERROR;
	}
	
	int indice = (int)funcion_hasheo(clave, hash->capacidad);
	lista_t* lista = hash->tabla_de_hash[indice];
	clave_valor_t* repetido = buscar_elemento(lista, clave, NULL);

	if(repetido)
		reasignar_elemento(repetido, elemento, hash->destructor);
	else {
		clave_valor_t* clave_valor = malloc(sizeof(clave_valor_t));
		if(!clave_valor) 
			return ERROR;
		clave_valor->elemento = elemento;
		strcpy(clave_valor->clave, clave);
		lista_insertar_en_posicion(lista, clave_valor, 0);
		hash->cantidad_almacenada++;
	}

	return EXITO;
}

/*
Pre: hash debe existir.
	 clave no debe ser NULL.
Post: Quita un elemento del hash e invoca la funcion destructora con dicho elemento.
      Devuelve 0 si pudo eliminar el elemento o -1 si no pudo.
*/
int hash_quitar(hash_t* hash, const char* clave){
	if(!hash || !clave)
		return ERROR;
	int indice = (int)funcion_hasheo(clave, hash->capacidad);
	lista_t* lista = hash->tabla_de_hash[indice];
	int posicion = -1;

	clave_valor_t* valor_buscado = buscar_elemento(lista, clave, &posicion);
	if(posicion >= 0){
		if(hash->destructor)
			hash->destructor(valor_buscado->elemento);
		free(valor_buscado);
		lista_borrar_de_posicion(lista, (size_t)posicion);
		hash->cantidad_almacenada--;
		return EXITO;
	} else 
		return ERROR;
}

/*
Pre: hash debe existir.
	 clave no debe ser NULL.
Post: Devuelve un elemento del hash con la clave dada o NULL si dicho elemento no existe.
*/
void* hash_obtener(hash_t* hash, const char* clave){
	if(!hash || !clave)
		return NULL;
	int indice = (int)funcion_hasheo(clave, hash->capacidad);
	lista_t* lista = hash->tabla_de_hash[indice];
	clave_valor_t* valor_buscado = buscar_elemento(lista, clave, NULL);
	if(valor_buscado)
		return valor_buscado->elemento;
	else 
		return NULL;
}

/*
 * Devuelve true si el hash contiene un elemento almacenado con la
 * clave dada o false en caso contrario.
 */
bool hash_contiene(hash_t* hash, const char* clave){
	if(!hash || !clave)
		return false;
	int indice = (int)funcion_hasheo(clave, hash->capacidad);
	lista_t* lista = hash->tabla_de_hash[indice];
	clave_valor_t* elemento = buscar_elemento(lista, clave, NULL);
	return elemento != NULL;
}

/*
Pre: hash debe existir.
Post: Devuelve la cantidad de elementos almacenados en el hash.
*/
size_t hash_cantidad(hash_t* hash){
	if(!hash) 
		return 0;
	return hash->cantidad_almacenada;
}

/*
Post: Destruye el hash liberando la memoria reservada.
      Invocar la funcion destructora con cada elemento almacenado en el hash.
*/
void hash_destruir(hash_t* hash){
	if(hash){
		for(int i = 0; i < hash->capacidad; i++){
			lista_t* lista_actual = hash->tabla_de_hash[i];
			while(!lista_vacia(lista_actual)){
				clave_valor_t* clave_valor_actual = lista_elemento_en_posicion(lista_actual, 0);
				if(hash->destructor)
					hash->destructor(clave_valor_actual->elemento);
				free(clave_valor_actual);
				lista_borrar_de_posicion(lista_actual, 0);
			}
			lista_destruir(lista_actual);
		}
		free(hash->tabla_de_hash);
		free(hash);
	}
}

/*
Pre: iterador debe existir.
	 Debe existir memoria disponible en el sistema.
Post: Mueve el iterador a la siguiente lista no vacia.
	  Si no hay otra lista no vacia el iterador pasa a apuntar a NULL.
*/
void buscar_siguiente_lista_no_vacia(hash_iterador_t* iterador){
	if(iterador){
		if(iterador->lista_actual)
			lista_iterador_destruir(iterador->lista_actual);
		int i = iterador->posicion_actual+1;
		while(i < iterador->hash->capacidad && lista_vacia(iterador->hash->tabla_de_hash[i]))
			i++;

		if(i < iterador->hash->capacidad){
			iterador->posicion_actual = i;
			iterador->lista_actual = lista_iterador_crear(iterador->hash->tabla_de_hash[i]);
		} else {
			iterador->lista_actual = NULL;
		}
	}
}

/*
 Pre: Debe existir memoria disponible en el sistema
 Post: Devuelve un puntero al iterador creado o NULL en caso de no poder crearlo
 */
hash_iterador_t* hash_iterador_crear(hash_t* hash){
	if(!hash) 
		return NULL;
	hash_iterador_t* iterador = malloc(sizeof(hash_iterador_t));
	if(!iterador) 
		return NULL;
	iterador->hash = hash;
	iterador->posicion_actual = -1;
	iterador->lista_actual = NULL;
	buscar_siguiente_lista_no_vacia(iterador);
	return iterador;
}

/*
Pre: iterador debe existir
Post: Devuelve la próxima clave almacenada en el hash y avanza el iterador.
      Devuelve la clave o NULL si no habia mas.
 */
void* hash_iterador_siguiente(hash_iterador_t* iterador){
	if(!iterador || !iterador->lista_actual) 
		return NULL;
	
	if(lista_iterador_tiene_siguiente(iterador->lista_actual)){
		clave_valor_t* clave_valor = lista_iterador_siguiente(iterador->lista_actual);
		return &clave_valor->clave;
	} else {
		buscar_siguiente_lista_no_vacia(iterador);
		return hash_iterador_siguiente(iterador);
	}
}

/*
Pre: iterador debe existir.
Post: Devuelve true si quedan claves por recorrer o false en caso contrario.
 */
bool hash_iterador_tiene_siguiente(hash_iterador_t* iterador){
	if(!iterador)
		return false;
	if(lista_iterador_tiene_siguiente(iterador->lista_actual))
		return true;

	if(iterador->posicion_actual == iterador->hash->capacidad)
		return false;

	int i = iterador->posicion_actual+1;
	while(i < iterador->hash->capacidad && lista_vacia(iterador->hash->tabla_de_hash[i]))
		i++;

	return i < iterador->hash->capacidad;
}

/*
Post: Destruye el iterador del hash, liberando su memoria.
*/
void hash_iterador_destruir(hash_iterador_t* iterador){
	if(iterador){
		lista_iterador_destruir(iterador->lista_actual);
		free(iterador);
	}
}